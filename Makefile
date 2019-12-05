## ----------------------------------------------------------------------------
## Copyright 2016-2018 ARM Ltd.
##
## SPDX-License-Identifier: Apache-2.0
##
## Licensed under the Apache License, Version 2.0 (the "License");
## you may not use this file except in compliance with the License.
## You may obtain a copy of the License at
##
##     http://www.apache.org/licenses/LICENSE-2.0
##
## Unless required by applicable law or agreed to in writing, software
## distributed under the License is distributed on an "AS IS" BASIS,
## WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
## See the License for the specific language governing permissions and
## limitations under the License.
## ----------------------------------------------------------------------------

## This makefile is only for SX OS platform

## ----------------------------------------------------------- ##
## Don't touch the next line unless you know what you're doing.##
## ----------------------------------------------------------- ##

PROJECT_NAME := mbed-cloud-client-example_espressif
#EXTRA_COMPONENT_DIRS := $(realpath .)

#PROJECT_PATH :=  $(shell pwd)
#PROJECT_PATH := /home/span/esp/esp-idf-latest/esp-idf/examples/mbed-cloud-client-example-porting-on-esp32/components

#export MBED_CLOUD_SERVICE = ${PROJECT_PATH}
#export MBED_CLOUD_SERVICE := /home/span/esp/esp-idf-latest/esp-idf/examples/mbed-cloud-client-example-porting-on-esp32/components

# Name of the module
#LOCAL_NAME := ${MBED_CLOUD_SERVICE}

# list all modules APIs that are necessary to compile this module
##LOCAL_API_DEPENDS := \
##					${LOCAL_NAME}/mbed-cloud-client \
## 		 			platform/service/posix \
##					${API_PLATFORM_DEPENDS} \

######EXTRA_COMPONENT_DIRS += $(abspath source) $(abspath delta-tool) $(abspath mbed-cloud-client) $(abspath pal-platform) \
######						$(abspath profiles)

#set(inc_dir "."
#            "${CMAKE_CURRENT_SOURCE_DIR}/include"
#            "${CMAKE_CURRENT_SOURCE_DIR}/platform"
#            "${PROJECT_PATH}/components/mbed-cloud-client/mbed-coap/mbed-coap"
#            "${PROJECT_PATH}/components/mbed-cloud-client/sal-stack-nanostack-eventloop"
#            "${PROJECT_PATH}/components/mbed-cloud-client/sal-stack-nanostack-eventloop/nanostack-event-loop"
#            "${PROJECT_PATH}/components/mbed-cloud-client/sal-stack-nanostack-eventloop/nanostack-event-loop/source"
#   )
#
#set(inc_src "components/source/application_init.cpp"
#            "components/source/application_init.h"
#            "components/source/app_platform_setup.c"
#            "components/source/components/mbed-cloud-client/sal-stack-nanostack-eventloop/nanostack-event-loop/eventOS_event.h"
#            "components/source/blinky.cpp"
#            "components/source/blinky.h"
#            "components/source/certificate_enrollment_user_cb.cpp"
#            "components/source/certificate_enrollment_user_cb.h"
#            "components/source/memory_tests.cpp"
#            "components/source/memory_tests.h"
#            "components/source/simplem2mclient.h"
#			"components/source/resource.h"
#   )
#
#idf_component_register( SRCS "${inc_src}"
#                        INCLUDE_DIRS "${inc_dir}"
#                      )


#LOCAL_EXPORT_FLAG += __FreeRTOS__
#LOCAL_EXPORT_FLAG += "__FREERTOS__"
#CFLAGS += -DMBED_CONF_NS_HAL_PAL_EVENT_LOOP_THREAD_STACK_SIZE=8192
#CFLAGS += -D__FREERTOS__
CPPFLAGS += -D__FREERTOS__
CPPFLAGS += -DMBED_CONF_NS_HAL_PAL_EVENT_LOOP_THREAD_STACK_SIZE=8192

#LOCAL_EXPORT_FLAG += "MBED_CONF_NS_HAL_PAL_EVENT_LOOP_THREAD_STACK_SIZE=8192"
#LOCAL_EXPORT_FLAG += "'PAL_USER_DEFINED_CONFIGURATION=\"FreeRTOS/FreeRTOS_default.h\"'"
#LOCAL_EXPORT_FLAG += "'MBED_CLIENT_USER_CONFIG_FILE=\"mbed_cloud_client_user_config.h\"'"
#LOCAL_EXPORT_FLAG += "'MBED_CLOUD_CLIENT_USER_CONFIG_FILE=\"mbed_cloud_client_user_config.h\"'"
#
#LOCAL_EXPORT_FLAG += "'MBED_CONF_MBED_CLIENT_EVENT_LOOP_SIZE=12000'"
#LOCAL_EXPORT_FLAG += "PAL_SIMULATOR_FLASH_OVER_FILE_SYSTEM=1"
#LOCAL_EXPORT_FLAG += "MBED_CONF_APP_CLOUD_MODE=1"
#LOCAL_EXPORT_FLAG += "MBED_CONF_APP_DEVELOPER_MODE=1"
#
## not yet
#LOCAL_EXPORT_FLAG += "MBED_CONF_MBED_CLOUD_CLIENT_DISABLE_CERTIFICATE_ENROLLMENT=1"
#
## Disable code using STL as it not available on SDK
#LOCAL_EXPORT_FLAG += "MBED_CLOUD_CLIENT_STL_API=0"
#LOCAL_EXPORT_FLAG += "MBED_CLOUD_CLIENT_STD_NAMESPACE_POLLUTION=0"
#
## Compile the sub-modules, except when the "service" must be used as a library.
## list all the modules that need to be compiled prior to using this module
#
#LOCAL_MODULE_DEPENDS += \
#					${LOCAL_NAME}/mbed-cloud-client \
#
## One can compile and run the PAL unit tests instead of example-app
## by "PAL_UNIT_TESTING=1 ctmake CT_PRODUCT=20180930 dbmerge -j" command.
##
## By default, the example app itself is built. By having the PAL tests in
## same makefile, one can easily be sure the configuration is the same and
## the changes in PAL during porting can be tested by its own unit tests and
## then running the example itself. 
#ifndef PAL_UNIT_TESTING
#
## this enables the mbed_cloud_application_entrypoint(void) from main.cpp
#LOCAL_EXPORT_FLAG += MBED_CLOUD_APPLICATION_NONSTANDARD_ENTRYPOINT
#
#else
## the PAL tests have mbed_cloud_application_entrypoint(void) too, which is enabled
## from pal_tests_nonstandard_entrypoint.c by PAL_UNIT_TESTING_NONSTANDARD_ENTRYPOINT.
#LOCAL_EXPORT_FLAG += "PAL_UNIT_TESTING_NONSTANDARD_ENTRYPOINT"
#
## the PAL tests can be run one suite at a time by defining PAL_UNIT_TEST_<suite name> flag
## or all suites by omitting said flags and only giving PAL_UNIT_TESTING flag.
## here, export all PAL_UNIT_TEST_* -flags to enable the singe suite testing feature
#$(foreach v, $(filter PAL_UNIT_TEST_%,$(.VARIABLES)), $(eval LOCAL_EXPORT_FLAG += "$(v)=$($(v))"))
#
## build the tests
#LOCAL_MODULE_DEPENDS += ${LOCAL_NAME}/mbed-cloud-client/mbed-client-pal/Test
#
## These are needed for building PAL SOTP tests. Note: the flag is renamed on yet-to-be-merged 
## version of esfs without backwards compatibility, so we need to have both here for some time.
#LOCAL_EXPORT_FLAG += "SOTP_TESTING"
#LOCAL_EXPORT_FLAG += "RBP_TESTING"
#endif
#
## Generate the revision (version) file automatically during the make process.
#AUTO_GEN_REVISION_HEADER := no
#
## This is a top-level module
#IS_TOP_LEVEL := yes
#
## Generates the CoolWatcher headers automatically.
#AUTO_XMD2H ?= no
#
## code is not in one "src/" directory as SDK expects by default
#USE_DIFFERENT_SOURCE_LAYOUT := yes
#USE_DIFFERENT_SOURCE_LAYOUT_ARM := yes
#
#C_SRC := ${wildcard *.c}
#C++_SRC := ${wildcard *.cpp}
#
#C_SRC += ${wildcard source/*.c}
#C++_SRC += ${wildcard source/*.cpp}
#
#C_SRC += ${wildcard source/platform/SXOS/*.c}
#C++_SRC += ${wildcard source/platform/SXOS/*.cpp}
#
#C_SRC += ${wildcard mbed-cloud-client/mbed-trace/source/*.c}
#C_SRC += ${wildcard mbed-cloud-client/nanostack-libservice/source/libip6string/*.c}


## ------------------------------------- ##
##  Do Not touch below this line         ##
## ------------------------------------- ##
include $(IDF_PATH)/make/project.mk


