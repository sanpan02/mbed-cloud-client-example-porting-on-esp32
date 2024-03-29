// ----------------------------------------------------------------------------
// Copyright 2016-2017 ARM Ltd.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ----------------------------------------------------------------------------

#ifndef MBED_CONF_MBED_CLOUD_CLIENT_PSA_SUPPORT
#ifdef MBED_CONF_MBED_CLOUD_CLIENT_EXTERNAL_SST_SUPPORT

#include <stdbool.h>
#include "pv_error_handling.h"
#include "pv_macros.h"
#include "storage_items.h"
#include "fcc_malloc.h"
#include "pal_sst.h"
#include "storage_internal.h"

extern bool g_kcm_initialized;


static kcm_status_e storage_get_first_cert_in_chain_name_and_info(storage_item_prefix_type_e item_prefix_type,
                                                                  const uint8_t *kcm_item_name,
                                                                  size_t kcm_item_name_len,
                                                                  char *kcm_complete_name,
                                                                  size_t kcm_complete_name_len,
                                                                  palSSTItemInfo_t *palItemInfo)
{
    kcm_status_e kcm_status = KCM_STATUS_SUCCESS;
    palStatus_t pal_status = PAL_SUCCESS;
    kcm_chain_cert_info_s cert_chain_info = { 0 };
    cert_chain_info.certificate_index = 0;
    cert_chain_info.is_last_certificate = false;

    SA_PV_ERR_RECOVERABLE_RETURN_IF((kcm_complete_name_len != STORAGE_MAX_COMPLETE_ITEM_NAME_LENGTH || kcm_complete_name == NULL), kcm_status = KCM_STATUS_INVALID_PARAMETER, "Wrong kcm_complete_name parameter");

    //Change complete certificate name to first certificate in chain with the same name
    kcm_status = storage_build_complete_working_item_name(KCM_CERTIFICATE_ITEM, item_prefix_type, kcm_item_name, kcm_item_name_len, kcm_complete_name, NULL, &cert_chain_info);
    SA_PV_ERR_RECOVERABLE_RETURN_IF((kcm_status != KCM_STATUS_SUCCESS), kcm_status, "Failed to change single certificate name");

    //Get size
    pal_status = pal_SSTGetInfo(kcm_complete_name, palItemInfo);
    if (pal_status == PAL_ERR_SST_ITEM_NOT_FOUND) {
        return  KCM_STATUS_ITEM_NOT_FOUND;
    }
    SA_PV_ERR_RECOVERABLE_RETURN_IF(pal_status != PAL_SUCCESS, kcm_status = pal_to_kcm_error_translation(pal_status), "Failed to get data size");

    SA_PV_LOG_WARN("Warning: The operation made on first certificate of the chain using single certificate API!");

    return kcm_status;
}


kcm_status_e storage_specific_init()
{
    palStatus_t pal_status = PAL_SUCCESS;
    size_t actual_size;

    SA_PV_LOG_TRACE_FUNC_ENTER_NO_ARGS();

    //check if flag file exists
    pal_status = pal_SSTGet(STORAGE_FACTORY_RESET_IN_PROGRESS_ITEM, NULL, 0, &actual_size);
    if (pal_status == PAL_ERR_SST_ITEM_NOT_FOUND) {
        //flag file was not found - positive scenario
        return KCM_STATUS_SUCCESS;
    } else if (pal_status == PAL_SUCCESS) {
        //flag file can be opened for reading
        //previous factory reset failed during execution
        //call factory reset to complete the process
        pal_status = storage_factory_reset();
    }

    SA_PV_LOG_TRACE_FUNC_EXIT_NO_ARGS();

    return pal_to_kcm_error_translation(pal_status);
}

kcm_status_e storage_specific_finalize()
{
    return KCM_STATUS_SUCCESS;
}

kcm_status_e storage_specific_reset()
{
    palStatus_t pal_status = PAL_SUCCESS;

    SA_PV_LOG_TRACE_FUNC_ENTER_NO_ARGS();

    pal_status = pal_SSTReset();
    SA_PV_ERR_RECOVERABLE_RETURN_IF((pal_status != PAL_SUCCESS), pal_to_kcm_error_translation(pal_status), "Failed pal_SSTReset  (%" PRIu32 ")", pal_status);

    SA_PV_LOG_TRACE_FUNC_EXIT_NO_ARGS();

    return KCM_STATUS_SUCCESS;
}

kcm_status_e storage_factory_reset()
{
    palStatus_t pal_status = PAL_SUCCESS;
    kcm_status_e kcm_status = KCM_STATUS_SUCCESS;
    char kcm_complete_name[STORAGE_MAX_COMPLETE_ITEM_NAME_LENGTH] = { 0 };
    palSSTIterator_t sst_iterator = 0;
    palSSTItemInfo_t item_info = { 0 };
    uint8_t* data_buffer = NULL;
    size_t actual_data_size;

    SA_PV_LOG_TRACE_FUNC_ENTER_NO_ARGS();

    // set factory reset in progress item flag
    pal_status = pal_SSTSet(STORAGE_FACTORY_RESET_IN_PROGRESS_ITEM, NULL, 0, PAL_SST_REPLAY_PROTECTION_FLAG);
    SA_PV_ERR_RECOVERABLE_GOTO_IF((pal_status != PAL_SUCCESS), kcm_status = pal_to_kcm_error_translation(pal_status), exit, "Failed pal_SSTSet  (%" PRIu32 ")", pal_status);

    //open iterator with working prefix
    pal_status = pal_SSTIteratorOpen(&sst_iterator, STORAGE_WORKING);
    SA_PV_ERR_RECOVERABLE_GOTO_IF((pal_status != PAL_SUCCESS), kcm_status = pal_to_kcm_error_translation(pal_status), exit, "Failed pal_SSTIteratorOpen  (%" PRIu32 ")", pal_status);

    //iterate over items with 'working' prefix and remove all items
    while ((pal_status = pal_SSTIteratorNext(sst_iterator, (char*)kcm_complete_name, KCM_MAX_FILENAME_SIZE)) == PAL_SUCCESS) {

        pal_status = pal_SSTRemove((const char*)kcm_complete_name);
        if (pal_status != PAL_SUCCESS) {
            // output warining in case of failure, but continue factory reset process
            SA_PV_LOG_ERR("Warning: failed to remove item. Continue factory reset...");
        }
    }

    //verify that we went over all items
    SA_PV_ERR_RECOVERABLE_GOTO_IF((pal_status != PAL_ERR_SST_ITEM_NOT_FOUND), kcm_status = pal_to_kcm_error_translation(pal_status), iterator_close_end_exit, "Failed pal_SSTIteratorNext (%" PRIu32 ")", pal_status);

    //close iterator
    pal_status = pal_SSTIteratorClose(sst_iterator);
    SA_PV_ERR_RECOVERABLE_GOTO_IF((pal_status != PAL_SUCCESS), kcm_status = pal_to_kcm_error_translation(pal_status), exit, "Failed pal_SSTIteratorClose (%" PRIu32 ")", pal_status);

    //open iterator with backup prefix
    pal_status = pal_SSTIteratorOpen(&sst_iterator, STORAGE_BACKUP);
    SA_PV_ERR_RECOVERABLE_GOTO_IF((pal_status != PAL_SUCCESS), kcm_status = pal_to_kcm_error_translation(pal_status), exit, "Failed pal_SSTIteratorOpen  (%" PRIu32 ")", pal_status);

    //iterate over items with 'backup' prefix
    while ((pal_status = pal_SSTIteratorNext(sst_iterator, (char*)kcm_complete_name, KCM_MAX_FILENAME_SIZE)) == PAL_SUCCESS) {

        //retreive item info (size and flags)
        pal_status = pal_SSTGetInfo((const char*)kcm_complete_name, &item_info);
        SA_PV_ERR_RECOVERABLE_GOTO_IF((pal_status != PAL_SUCCESS), kcm_status = pal_to_kcm_error_translation(pal_status), iterator_close_end_exit, "Failed pal_SSTGetInfo  (%" PRIu32 ")", pal_status);

        //allocate buffer for the data according to its size
        data_buffer = fcc_malloc(item_info.itemSize);
        SA_PV_ERR_RECOVERABLE_GOTO_IF((data_buffer == NULL), kcm_status = KCM_STATUS_OUT_OF_MEMORY, iterator_close_end_exit, "Failed to allocate bffer");

        //read factory item to the buffer
        pal_status = pal_SSTGet((const char*)kcm_complete_name, data_buffer, item_info.itemSize, &actual_data_size);
        SA_PV_ERR_RECOVERABLE_GOTO_IF((pal_status != PAL_SUCCESS), kcm_status = pal_to_kcm_error_translation(pal_status), free_memory_and_exit, "Failed pal_SSTGet  (%" PRIu32 ")", pal_status);
        SA_PV_ERR_RECOVERABLE_GOTO_IF((item_info.itemSize != actual_data_size), kcm_status = KCM_STATUS_FILE_CORRUPTED, free_memory_and_exit, "Failed pal_SSTGet  (%" PRIu32 ")", pal_status);

        //change item name prefix to STORAGE_DEFAULT_PATH ('working' prefix)
        memcpy(kcm_complete_name, STORAGE_WORKING, strlen(STORAGE_WORKING));

        //write item with 'working' prefix
        pal_status = pal_SSTSet((const char*)kcm_complete_name, data_buffer, item_info.itemSize, item_info.SSTFlagsBitmap);
        SA_PV_ERR_RECOVERABLE_GOTO_IF((pal_status != PAL_SUCCESS), kcm_status = pal_to_kcm_error_translation(pal_status), free_memory_and_exit, "Failed pal_SSTSet  (%" PRIu32 ")", pal_status);

        //free allocated buffer
        fcc_free(data_buffer);
    }

    //verify that we went over all items
    SA_PV_ERR_RECOVERABLE_GOTO_IF((pal_status != PAL_ERR_SST_ITEM_NOT_FOUND), kcm_status = pal_to_kcm_error_translation(pal_status), iterator_close_end_exit, "Failed pal_SSTIteratorNext (%" PRIu32 ")", pal_status);

    //close iterator
    pal_status = pal_SSTIteratorClose(sst_iterator);
    SA_PV_ERR_RECOVERABLE_GOTO_IF((pal_status != PAL_SUCCESS), kcm_status = pal_to_kcm_error_translation(pal_status), exit, "Failed pal_SSTIteratorClose (%" PRIu32 ")", pal_status);

    //delete temporary file. if failed, set special status to `kcm_backup_status` since factory reset succedeed.
    pal_status = pal_SSTRemove(STORAGE_FACTORY_RESET_IN_PROGRESS_ITEM);

    if (pal_status != PAL_SUCCESS) {
        // output warining in case of failure, but continue factory reset process
        SA_PV_LOG_ERR("Warning: failed to remove item. Continue factory reset...");
    }

    goto exit;

free_memory_and_exit:

    //free allocated memory
    fcc_free(data_buffer);

iterator_close_end_exit:

    //close iterator
    pal_status = pal_SSTIteratorClose(sst_iterator);
    SA_PV_ERR_RECOVERABLE_GOTO_IF((pal_status != PAL_SUCCESS), kcm_status = pal_to_kcm_error_translation(pal_status), exit, "Failed pal_SSTIteratorClose (%" PRIu32 ")", pal_status);

exit:

    SA_PV_LOG_TRACE_FUNC_EXIT_NO_ARGS();

    return kcm_status;
}


palStatus_t storage_rbp_read(
    const char *item_name,
    uint8_t *data,
    size_t data_size,
    size_t *data_actual_size_out)
{
    palStatus_t pal_status = PAL_SUCCESS;
    palSSTItemInfo_t palItemInfo;

    // Validate function parameters
    SA_PV_ERR_RECOVERABLE_RETURN_IF((item_name == NULL), PAL_ERR_INVALID_ARGUMENT, "Invalid item_name");
    SA_PV_LOG_INFO_FUNC_ENTER("item name =  %s", (char*)item_name);
    SA_PV_ERR_RECOVERABLE_RETURN_IF((data == NULL), PAL_ERR_INVALID_ARGUMENT, "Invalid data");
    SA_PV_ERR_RECOVERABLE_RETURN_IF((data_size == 0 || data_size > UINT16_MAX), PAL_ERR_INVALID_ARGUMENT, "Invalid data_length");
    SA_PV_ERR_RECOVERABLE_RETURN_IF((data_actual_size_out == NULL), PAL_ERR_INVALID_ARGUMENT, "Invalid data_actual_size_out");

    pal_status = pal_SSTGetInfo(item_name, &palItemInfo);
    if (pal_status == PAL_ERR_SST_ITEM_NOT_FOUND) {
        //item not found. Print info level error
        SA_PV_LOG_INFO("Item not found");
        return PAL_ERR_ITEM_NOT_EXIST;
    }
    SA_PV_ERR_RECOVERABLE_RETURN_IF((pal_status != PAL_SUCCESS), PAL_ERR_GENERIC_FAILURE, "pal_SSTGetInfo failed");
    SA_PV_ERR_RECOVERABLE_RETURN_IF((palItemInfo.itemSize > data_size), PAL_ERR_BUFFER_TOO_SMALL, "data_size is too small");

    pal_status = pal_SSTGet(item_name, data, data_size, data_actual_size_out);
    SA_PV_ERR_RECOVERABLE_RETURN_IF(pal_status != PAL_SUCCESS, PAL_ERR_GENERIC_FAILURE, "Failed to get data");

    return pal_status;
}

palStatus_t storage_rbp_write(
    const char *item_name,
    const uint8_t *data,
    size_t data_size,
    bool is_write_once)
{
    uint32_t flag_mask = PAL_SST_REPLAY_PROTECTION_FLAG | PAL_SST_CONFIDENTIALITY_FLAG;
    palStatus_t pal_status = PAL_SUCCESS;

    SA_PV_ERR_RECOVERABLE_RETURN_IF((item_name == NULL), PAL_ERR_INVALID_ARGUMENT, "Invalid item_name");
    SA_PV_ERR_RECOVERABLE_RETURN_IF((data_size > UINT16_MAX || data_size == 0), PAL_ERR_INVALID_ARGUMENT, "Invalid param data");
    SA_PV_LOG_INFO_FUNC_ENTER("data_size = %" PRIu32 " item_name = %s", (uint32_t)data_size, item_name);
    SA_PV_ERR_RECOVERABLE_RETURN_IF((data == NULL), PAL_ERR_INVALID_ARGUMENT, "Invalid param data");

    if (is_write_once == true) {
        flag_mask |= PAL_SST_WRITE_ONCE_FLAG;
    }

    pal_status = pal_SSTSet(item_name, data, data_size, flag_mask);
    SA_PV_ERR_RECOVERABLE_RETURN_IF((pal_status == PAL_ERR_SST_WRITE_PROTECTED), PAL_ERR_ITEM_EXIST, "Failed to write rbp data");
    SA_PV_ERR_RECOVERABLE_RETURN_IF((pal_status != PAL_SUCCESS), PAL_ERR_GENERIC_FAILURE, "Failed to write rbp data");

    SA_PV_LOG_INFO_FUNC_EXIT();
    return pal_status;
}



kcm_status_e storage_item_store_impl(const uint8_t * kcm_item_name,
                                     size_t kcm_item_name_len,
                                     kcm_item_type_e kcm_item_type,
                                     bool kcm_item_is_factory,
                                     bool kcm_item_is_encrypted,
                                     storage_item_prefix_type_e item_prefix_type,
                                     const uint8_t * kcm_item_data,
                                     size_t kcm_item_data_size)
{
    char kcm_complete_name[STORAGE_MAX_COMPLETE_ITEM_NAME_LENGTH] = { 0 };
    kcm_status_e kcm_status = KCM_STATUS_SUCCESS;
    palStatus_t pal_status = PAL_SUCCESS;
    palSSTItemInfo_t palItemInfo;
    uint32_t flag_mask = 0;

    //Build complete data name (also checks name validity)
    kcm_status = storage_build_complete_working_item_name(kcm_item_type, item_prefix_type, kcm_item_name, kcm_item_name_len, kcm_complete_name, NULL, NULL);
    SA_PV_ERR_RECOVERABLE_RETURN_IF((kcm_status != KCM_STATUS_SUCCESS), kcm_status, "Failed to build complete data name");

    pal_status = pal_SSTGetInfo(kcm_complete_name, &palItemInfo);
    SA_PV_ERR_RECOVERABLE_RETURN_IF((pal_status == PAL_SUCCESS), kcm_status = KCM_STATUS_FILE_EXIST, "Data already exists");

    //Check if certificate chain with the same name is exists, if yes -> return an error
    if (kcm_item_type == KCM_CERTIFICATE_ITEM) {
        kcm_chain_cert_info_s cert_name_info = { 0 };
        cert_name_info.certificate_index = 0;
        cert_name_info.is_last_certificate = false;

        //Build complete name of first chain certificate
        kcm_status = storage_build_complete_working_item_name(kcm_item_type, item_prefix_type, kcm_item_name, kcm_item_name_len, kcm_complete_name, NULL, &cert_name_info);
        SA_PV_ERR_RECOVERABLE_RETURN_IF((kcm_status != KCM_STATUS_SUCCESS), kcm_status, "Failed to change single certificate name");

        pal_status = pal_SSTGetInfo(kcm_complete_name, &palItemInfo);
        SA_PV_ERR_RECOVERABLE_RETURN_IF((pal_status == PAL_SUCCESS), kcm_status = KCM_STATUS_FILE_EXIST, "Data already exists");
        SA_PV_ERR_RECOVERABLE_RETURN_IF((pal_status != PAL_ERR_SST_ITEM_NOT_FOUND), kcm_status = pal_to_kcm_error_translation(pal_status), "pal_SSTGetInfo FAILED");

        //Revert the name to certificate complete name
        //Build complete name of single certificate
        kcm_status = storage_build_complete_working_item_name(kcm_item_type, item_prefix_type, kcm_item_name, kcm_item_name_len, kcm_complete_name, NULL, NULL);
        SA_PV_ERR_RECOVERABLE_RETURN_IF((kcm_status != KCM_STATUS_SUCCESS), kcm_status, "Failed to change first certificate name");
    }

    //Create flag mask
    if (kcm_item_is_encrypted == true) {
        flag_mask |= PAL_SST_CONFIDENTIALITY_FLAG;
    }

    if (kcm_item_is_factory == true) {
        //Set the complete name to backup path
        kcm_status = build_complete_backup_item_name(kcm_item_type, item_prefix_type, kcm_item_name, kcm_item_name_len, kcm_complete_name, NULL);
        SA_PV_ERR_RECOVERABLE_RETURN_IF((kcm_status != KCM_STATUS_SUCCESS), kcm_status, "Failed to change first certificate name to backup path");

        //Write the data to backup path
        pal_status = pal_SSTSet(kcm_complete_name, kcm_item_data, kcm_item_data_size, flag_mask);
        SA_PV_ERR_RECOVERABLE_RETURN_IF((pal_status != PAL_SUCCESS), kcm_status = pal_to_kcm_error_translation(pal_status), "Failed to write data to backup");

        //Set the backup path back to working
        kcm_status = storage_build_complete_working_item_name(kcm_item_type, item_prefix_type, kcm_item_name, kcm_item_name_len, kcm_complete_name, NULL, NULL);
        SA_PV_ERR_RECOVERABLE_RETURN_IF((kcm_status != KCM_STATUS_SUCCESS), kcm_status, "Failed to change first certificate nameFailed to change to backup path");

    }

    //Write the data to working path
    pal_status = pal_SSTSet(kcm_complete_name, kcm_item_data, kcm_item_data_size, flag_mask);
    SA_PV_ERR_RECOVERABLE_RETURN_IF((pal_status != PAL_SUCCESS), kcm_status = pal_to_kcm_error_translation(pal_status), "Failed to write data");

    SA_PV_LOG_INFO_FUNC_EXIT_NO_ARGS();
    return kcm_status;
}


kcm_status_e storage_item_get_data_size(
    const uint8_t * kcm_item_name,
    size_t kcm_item_name_len,
    kcm_item_type_e kcm_item_type,
    storage_item_prefix_type_e item_prefix_type,
    size_t * kcm_item_data_size_out)
{
    char kcm_complete_name[STORAGE_MAX_COMPLETE_ITEM_NAME_LENGTH] = { 0 };
    kcm_status_e kcm_status = KCM_STATUS_SUCCESS;
    palSSTItemInfo_t palItemInfo;
    palStatus_t pal_status = PAL_SUCCESS;

    // Validate function parameters
    SA_PV_ERR_RECOVERABLE_RETURN_IF((kcm_item_name == NULL), KCM_STATUS_INVALID_PARAMETER, "Invalid kcm_item_name");
    SA_PV_ERR_RECOVERABLE_RETURN_IF((kcm_item_name_len == 0), KCM_STATUS_INVALID_PARAMETER, "Invalid kcm_item_name_len");
    SA_PV_LOG_INFO_FUNC_ENTER("item name = %.*s len=%" PRIu32 "", (int)kcm_item_name_len, (char*)kcm_item_name, (uint32_t)kcm_item_name_len);
    SA_PV_ERR_RECOVERABLE_RETURN_IF((kcm_item_type >= KCM_LAST_ITEM), KCM_STATUS_INVALID_PARAMETER, "Invalid kcm_item_type");
    SA_PV_ERR_RECOVERABLE_RETURN_IF((kcm_item_data_size_out == NULL), KCM_STATUS_INVALID_PARAMETER, "Kcm size out pointer is NULL");
    SA_PV_ERR_RECOVERABLE_RETURN_IF((item_prefix_type != STORAGE_ITEM_PREFIX_KCM && item_prefix_type != STORAGE_ITEM_PREFIX_CE), KCM_STATUS_INVALID_PARAMETER, "Invalid origin_type");

    // Check if KCM initialized, if not initialize it
    if (!g_kcm_initialized) {
        kcm_status = kcm_init();
        SA_PV_ERR_RECOVERABLE_RETURN_IF((kcm_status != KCM_STATUS_SUCCESS), kcm_status, "KCM initialization failed\n");
    }

    //Build complete data name
    kcm_status = storage_build_complete_working_item_name(kcm_item_type, item_prefix_type, kcm_item_name, kcm_item_name_len, kcm_complete_name, NULL, NULL);
    SA_PV_ERR_RECOVERABLE_RETURN_IF((kcm_status != KCM_STATUS_SUCCESS), kcm_status, "Failed to to build complete name");

    //Try to get data info
    pal_status = pal_SSTGetInfo(kcm_complete_name, &palItemInfo);
    SA_PV_ERR_RECOVERABLE_RETURN_IF((pal_status != PAL_SUCCESS && pal_status != PAL_ERR_SST_ITEM_NOT_FOUND), kcm_status = pal_to_kcm_error_translation(pal_status), "Failed to get data size");

    if (pal_status == PAL_ERR_SST_ITEM_NOT_FOUND) {
        if (kcm_item_type == KCM_CERTIFICATE_ITEM) {
            kcm_status = storage_get_first_cert_in_chain_name_and_info(item_prefix_type, kcm_item_name, kcm_item_name_len, kcm_complete_name, sizeof(kcm_complete_name), &palItemInfo);
            if (kcm_status == KCM_STATUS_ITEM_NOT_FOUND) {
                //We don't want print log in case the item wasn't found
                return kcm_status;
            }
            SA_PV_ERR_RECOVERABLE_RETURN_IF((kcm_status != KCM_STATUS_SUCCESS), kcm_status, "Failed to check single certificate name");
            pal_status = PAL_SUCCESS;
        } else {//not certificate
            SA_PV_LOG_INFO("Item not found");
            return KCM_STATUS_ITEM_NOT_FOUND;
        }
    }

    //Set value of data size
    *kcm_item_data_size_out = palItemInfo.itemSize;

    SA_PV_LOG_INFO_FUNC_EXIT("kcm data size = %" PRIu32 "", (uint32_t)*kcm_item_data_size_out);
    return kcm_status;
}

kcm_status_e storage_item_get_data(
    const uint8_t * kcm_item_name,
    size_t kcm_item_name_len,
    kcm_item_type_e kcm_item_type,
    storage_item_prefix_type_e item_prefix_type,
    uint8_t *kcm_item_data_out,
    size_t kcm_item_data_max_size,
    size_t *kcm_item_data_act_size_out)
{
    char kcm_complete_name[STORAGE_MAX_COMPLETE_ITEM_NAME_LENGTH] = { 0 };
    kcm_status_e kcm_status = KCM_STATUS_SUCCESS;
    palStatus_t pal_status = PAL_SUCCESS;
    palSSTItemInfo_t palItemInfo;

    // Validate function parameters
    SA_PV_ERR_RECOVERABLE_RETURN_IF((kcm_item_name == NULL), KCM_STATUS_INVALID_PARAMETER, "Invalid kcm_item_name");
    SA_PV_ERR_RECOVERABLE_RETURN_IF((kcm_item_name_len == 0), KCM_STATUS_INVALID_PARAMETER, "Invalid kcm_item_name_len");
    SA_PV_LOG_INFO_FUNC_ENTER("item name = %.*s len = %" PRIu32 ", data max size = %" PRIu32 "", (int)kcm_item_name_len, (char*)kcm_item_name, (uint32_t)kcm_item_name_len, (uint32_t)kcm_item_data_max_size);
    SA_PV_ERR_RECOVERABLE_RETURN_IF((item_prefix_type != STORAGE_ITEM_PREFIX_KCM && item_prefix_type != STORAGE_ITEM_PREFIX_CE), KCM_STATUS_INVALID_PARAMETER, "Invalid origin_type");
    SA_PV_ERR_RECOVERABLE_RETURN_IF((kcm_item_type >= KCM_LAST_ITEM), KCM_STATUS_INVALID_PARAMETER, "Invalid kcm_item_type");
    SA_PV_ERR_RECOVERABLE_RETURN_IF((kcm_item_data_act_size_out == NULL), KCM_STATUS_INVALID_PARAMETER, "Invalid kcm_item_data_act_size_out");
    SA_PV_ERR_RECOVERABLE_RETURN_IF(((kcm_item_data_out == NULL) && (kcm_item_data_max_size > 0)), KCM_STATUS_INVALID_PARAMETER, "Provided kcm_item_data NULL and kcm_item_data_size greater than 0");

    // Check if KCM initialized, if not initialize it
    if (!g_kcm_initialized) {
        kcm_status = kcm_init();
        SA_PV_ERR_RECOVERABLE_RETURN_IF((kcm_status != KCM_STATUS_SUCCESS), kcm_status, "KCM initialization failed\n");
    }

    //Build complete data name
    kcm_status = storage_build_complete_working_item_name(kcm_item_type, item_prefix_type, kcm_item_name, kcm_item_name_len, kcm_complete_name, NULL, NULL);
    SA_PV_ERR_RECOVERABLE_RETURN_IF((kcm_status != KCM_STATUS_SUCCESS), kcm_status, "Failed to to build complete name");

    //Get size
    pal_status = pal_SSTGetInfo(kcm_complete_name, &palItemInfo);
    SA_PV_ERR_RECOVERABLE_RETURN_IF((pal_status != PAL_SUCCESS && pal_status != PAL_ERR_SST_ITEM_NOT_FOUND), kcm_status = pal_to_kcm_error_translation(pal_status), "Failed to get data size");

    if (pal_status == PAL_ERR_SST_ITEM_NOT_FOUND) {

        if (kcm_item_type == KCM_CERTIFICATE_ITEM) {
            kcm_status = storage_get_first_cert_in_chain_name_and_info(item_prefix_type, kcm_item_name, kcm_item_name_len, kcm_complete_name, sizeof(kcm_complete_name), &palItemInfo);
            SA_PV_ERR_RECOVERABLE_RETURN_IF((kcm_status != KCM_STATUS_SUCCESS), kcm_status, "Failed to check single certificate name");
            pal_status = PAL_SUCCESS;
        } else {
            //item not found. Print info level error
            SA_PV_LOG_INFO("Item not found");
            return KCM_STATUS_ITEM_NOT_FOUND;
        }
    }
    //Check buffer size for the data
    SA_PV_ERR_RECOVERABLE_RETURN_IF((palItemInfo.itemSize > kcm_item_data_max_size), kcm_status = KCM_STATUS_INSUFFICIENT_BUFFER, "Data out buffer too small");

    pal_status = pal_SSTGet(kcm_complete_name, kcm_item_data_out, kcm_item_data_max_size, kcm_item_data_act_size_out);
    SA_PV_ERR_RECOVERABLE_RETURN_IF((pal_status != PAL_SUCCESS), kcm_status = pal_to_kcm_error_translation(pal_status), "Failed to get data ");

    SA_PV_LOG_INFO_FUNC_EXIT_NO_ARGS();
    return kcm_status;
}

kcm_status_e storage_item_delete(
    const uint8_t * kcm_item_name,
    size_t kcm_item_name_len,
    kcm_item_type_e kcm_item_type,
    storage_item_prefix_type_e item_prefix_type)
{
    char kcm_complete_name[STORAGE_MAX_COMPLETE_ITEM_NAME_LENGTH] = { 0 };
    kcm_status_e kcm_status = KCM_STATUS_SUCCESS;
    palStatus_t pal_status = PAL_SUCCESS;
    palSSTItemInfo_t palItemInfo;

    // Validate function parameters
    SA_PV_ERR_RECOVERABLE_RETURN_IF((kcm_item_name == NULL), KCM_STATUS_INVALID_PARAMETER, "Invalid kcm_item_name");
    SA_PV_ERR_RECOVERABLE_RETURN_IF((kcm_item_name_len == 0), KCM_STATUS_INVALID_PARAMETER, "Invalid kcm_item_name_len");
    SA_PV_LOG_INFO_FUNC_ENTER("item name = %.*s len = %" PRIu32 "", (int)kcm_item_name_len, (char*)kcm_item_name, (uint32_t)kcm_item_name_len);
    SA_PV_ERR_RECOVERABLE_RETURN_IF((kcm_item_type >= KCM_LAST_ITEM), KCM_STATUS_INVALID_PARAMETER, "Invalid kcm_item_type");
    SA_PV_ERR_RECOVERABLE_RETURN_IF((item_prefix_type != STORAGE_ITEM_PREFIX_KCM && item_prefix_type != STORAGE_ITEM_PREFIX_CE), KCM_STATUS_INVALID_PARAMETER, "Invalid origin_type");

    // Check if KCM initialized, if not initialize it
    if (!g_kcm_initialized) {
        kcm_status = kcm_init();
        SA_PV_ERR_RECOVERABLE_RETURN_IF((kcm_status != KCM_STATUS_SUCCESS), kcm_status, "KCM initialization failed\n");
    }

    //Build complete data name
    kcm_status = storage_build_complete_working_item_name(kcm_item_type, item_prefix_type, kcm_item_name, kcm_item_name_len, kcm_complete_name, NULL, NULL);
    SA_PV_ERR_RECOVERABLE_RETURN_IF((kcm_status != KCM_STATUS_SUCCESS), kcm_status, "Failed to to build complete name");

    //Get size
    pal_status = pal_SSTGetInfo(kcm_complete_name, &palItemInfo);
    SA_PV_ERR_RECOVERABLE_RETURN_IF((pal_status != PAL_SUCCESS && pal_status != PAL_ERR_SST_ITEM_NOT_FOUND), kcm_status = pal_to_kcm_error_translation(pal_status), "Failed to get data size");

    if (pal_status == PAL_ERR_SST_ITEM_NOT_FOUND) {

        if (kcm_item_type == KCM_CERTIFICATE_ITEM) {
            kcm_status = storage_get_first_cert_in_chain_name_and_info(item_prefix_type, kcm_item_name, kcm_item_name_len, kcm_complete_name, sizeof(kcm_complete_name), &palItemInfo);
            SA_PV_ERR_RECOVERABLE_RETURN_IF((kcm_status != KCM_STATUS_SUCCESS), kcm_status, "Failed to check single certificate name");
            pal_status = PAL_SUCCESS;
        } else {
            SA_PV_LOG_INFO("Item not found");
            return  KCM_STATUS_ITEM_NOT_FOUND;
        }
    }

    //Remove the item name
    pal_status = pal_SSTRemove(kcm_complete_name);
    SA_PV_ERR_RECOVERABLE_RETURN_IF(pal_status != PAL_SUCCESS, kcm_status = pal_to_kcm_error_translation(pal_status), "Failed to delete data");

    SA_PV_LOG_INFO_FUNC_EXIT_NO_ARGS();
    return kcm_status;

}


kcm_status_e check_certificate_existance(const uint8_t *kcm_chain_name, size_t kcm_chain_name_len, storage_item_prefix_type_e item_prefix_type)
{

    kcm_status_e kcm_status = KCM_STATUS_SUCCESS;
    char kcm_complete_name[STORAGE_MAX_COMPLETE_ITEM_NAME_LENGTH] = { 0 };
    palStatus_t pal_status = PAL_SUCCESS;
    palSSTItemInfo_t palItemInfo = { 0 };
    kcm_chain_cert_info_s cert_name_info = { 0 };

    //Build complete name of single certificate with given certificate chain name
    kcm_status = storage_build_complete_working_item_name(KCM_CERTIFICATE_ITEM, item_prefix_type, kcm_chain_name, kcm_chain_name_len, kcm_complete_name, NULL, NULL);
    SA_PV_ERR_RECOVERABLE_RETURN_IF((kcm_status != KCM_STATUS_SUCCESS), kcm_status, "Failed to build complete data name");

    //If single certificate with the chain name is exists in the data base - return an error
    pal_status = pal_SSTGetInfo(kcm_complete_name, &palItemInfo);
    SA_PV_ERR_RECOVERABLE_RETURN_IF((pal_status == PAL_SUCCESS), kcm_status = KCM_STATUS_FILE_EXIST, "Data with the same name already exists");

    //Build complete name of first certificate name in the chain
    cert_name_info.certificate_index = 0;
    cert_name_info.is_last_certificate = false;
    kcm_status = storage_build_complete_working_item_name(KCM_CERTIFICATE_ITEM, item_prefix_type, kcm_chain_name, kcm_chain_name_len, kcm_complete_name, NULL, &cert_name_info);
    SA_PV_ERR_RECOVERABLE_RETURN_IF((kcm_status != KCM_STATUS_SUCCESS), kcm_status, "Failed to build complete data name");

    //If first certificate with the chain name is exists in the data base - return an error
    pal_status = pal_SSTGetInfo(kcm_complete_name, &palItemInfo);
    SA_PV_ERR_RECOVERABLE_RETURN_IF((pal_status == PAL_SUCCESS), kcm_status = KCM_STATUS_FILE_EXIST, "Data with the same name already exists");

    return kcm_status;
}

kcm_status_e set_certificates_info(storage_cert_chain_context_s *chain_context, storage_item_prefix_type_e item_prefix_type)
{
    kcm_status_e kcm_status = KCM_STATUS_SUCCESS;
    char kcm_complete_name[STORAGE_MAX_COMPLETE_ITEM_NAME_LENGTH] = { 0 };
    palSSTItemInfo_t palItemInfo = { 0 };
    kcm_chain_cert_info_s cert_name_info = { 0, false };
    palStatus_t pal_status = PAL_SUCCESS;
    int certificate_index = 0;

    //Try to read all certificate in the chain, retrieve the number of certificates in the chain and their sizes
    for (certificate_index = 0; (certificate_index < KCM_MAX_NUMBER_OF_CERTITICATES_IN_CHAIN) && (cert_name_info.is_last_certificate == false); certificate_index++) {
        cert_name_info.certificate_index = (uint32_t)certificate_index;

        //Build certificate name according to its index in certificate chain
        kcm_status = storage_build_complete_working_item_name(KCM_LAST_ITEM, item_prefix_type, chain_context->chain_name, chain_context->chain_name_len, kcm_complete_name, NULL, &cert_name_info);
        SA_PV_ERR_RECOVERABLE_RETURN_IF((kcm_status != KCM_STATUS_SUCCESS), kcm_status, "Failed to build complete data name");

        //Try to read certificate as not last certificate
        pal_status = pal_SSTGetInfo((const char*)kcm_complete_name, &palItemInfo);
        //If current name wasn't found, try to read the certificate as last one in the chain
        if (pal_status == PAL_ERR_SST_ITEM_NOT_FOUND) {

            cert_name_info.is_last_certificate = true;

            //Set the name certificate as last certificate in the chain
            kcm_status = storage_build_complete_working_item_name(KCM_LAST_ITEM, item_prefix_type, chain_context->chain_name, chain_context->chain_name_len, kcm_complete_name, NULL, &cert_name_info);
            SA_PV_ERR_RECOVERABLE_RETURN_IF((kcm_status != KCM_STATUS_SUCCESS), kcm_status, "Failed to build complete data name");

            //retrieve item info (size and flags)
            pal_status = pal_SSTGetInfo((const char*)kcm_complete_name, &palItemInfo);

            //Indication for last certificate
            if (pal_status == PAL_SUCCESS) {
                cert_name_info.is_last_certificate = true;
            }

        }
        if (pal_status == PAL_ERR_SST_ITEM_NOT_FOUND) {
            //We don't want print log in case the item wasn't found
            kcm_status = pal_to_kcm_error_translation(pal_status);
            return kcm_status;
        }
        SA_PV_ERR_RECOVERABLE_RETURN_IF((pal_status != PAL_SUCCESS), kcm_status = pal_to_kcm_error_translation(pal_status), "Failed pal_SSTGetInfo  (%" PRIu32 ")", pal_status);

        //Set in certificate info array the size of current index
        chain_context->certificates_info[certificate_index] = palItemInfo.itemSize;
    }
    SA_PV_ERR_RECOVERABLE_RETURN_IF((cert_name_info.is_last_certificate != true), kcm_status = KCM_STATUS_INVALID_NUM_OF_CERT_IN_CHAIN, "Failed to set size of certificate chain");

    chain_context->num_of_certificates_in_chain = (uint32_t)(certificate_index);
    return kcm_status;
}

void chain_delete(storage_cert_chain_context_s *chain_context, storage_item_prefix_type_e item_prefix_type)
{
    kcm_status_e kcm_status = KCM_STATUS_SUCCESS;
    kcm_chain_cert_info_s cert_name_info = { 0, false };
    char kcm_complete_name[STORAGE_MAX_COMPLETE_ITEM_NAME_LENGTH] = { 0 };

    do {
        cert_name_info.certificate_index = chain_context->current_cert_index;

        //Set the name of the certificate in working
        kcm_status = storage_build_complete_working_item_name(KCM_CERTIFICATE_ITEM,
                                                              item_prefix_type,
                                                              chain_context->chain_name,
                                                              chain_context->chain_name_len,
                                                              kcm_complete_name,
                                                              NULL,
                                                              &cert_name_info);

        //we don't check the result of storage_file_delete, as it is possible that not all certificates were saved to the storage
        if (kcm_status == KCM_STATUS_SUCCESS) {
            pal_SSTRemove(kcm_complete_name);
        }

        //Only in case of invalid create operation we will remove wrong chain from backup path too
        if (chain_context->operation_type == STORAGE_CHAIN_OP_TYPE_CREATE) {
            //Set the name the  certificate in backup (factory)
            kcm_status = build_complete_backup_item_name(KCM_CERTIFICATE_ITEM,
                                                         item_prefix_type,
                                                         chain_context->chain_name,
                                                         chain_context->chain_name_len,
                                                         kcm_complete_name,
                                                         &cert_name_info);

            //we don't check the result of storage_file_delete, as it is possible that not all certificates were saved to the storage
            if (kcm_status == KCM_STATUS_SUCCESS) {
                pal_SSTRemove(kcm_complete_name);
            }
        }

        if (chain_context->current_cert_index == 0) {
            break;
        }

        //
        chain_context->current_cert_index--;
    } while (true);
}

#endif
#endif //#ifndef MBED_CONF_MBED_CLOUD_CLIENT_PSA_SUPPORT