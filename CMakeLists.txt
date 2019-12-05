##############################################INCLUDE(CMakeForceCompiler)
# CROSS COMPILER SETTING
cmake_minimum_required (VERSION 3.5)
#############################################SET(CMAKE_SYSTEM_NAME Generic)

set(OS_BRAND FreeRTOS)
set (MBED_CLOUD_CLIENT_ESP_PORT ${CMAKE_CURRENT_LIST_DIR}/components)
############################################project(mbedCloudClientExample)

#include("${CMAKE_CURRENT_SOURCE_DIR}/components/pal-platform/common.cmake")

# Include CMake file that provides ESP-IDF CMake build system APIs.
#include($ENV{IDF_PATH}/tools/cmake/idf.cmake)
#include($ENV{IDF_PATH}/tools/cmake/project.cmake)

###########################################################################################################################################
###########################################################################################################################################
#add_definitions(-DNS_EXCLUDE_HIGHRES_TIMER)
#add_definitions(-DNS_EVENTLOOP_USE_TICK_TIMER)
#add_definitions(-DMBED_CONF_MBED_CLIENT_EVENT_LOOP_SIZE=8192)
#target_compile_definitions(${COMPONENT_TARGET} PUBLIC "-D__FREERTOS__")
###########################################################################################################################################
###########################################################################################################################################


###########################################################################################################################################
###########################################################################################################################################
# mbed-cloud-client-example
###include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
###include_directories("${CMAKE_CURRENT_SOURCE_DIR}/components/source")
###include_directories("${CMAKE_CURRENT_SOURCE_DIR}/components/source/include")
###include_directories("${CMAKE_CURRENT_SOURCE_DIR}/components/source/platform")
###include_directories("${CMAKE_CURRENT_SOURCE_DIR}/components/mbed-cloud-client/sal-stack-nanostack-eventloop")
###include_directories("${CMAKE_CURRENT_SOURCE_DIR}/components/mbed-cloud-client/source")
###
#### This is needed for compiling and linking SW.
###add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/components/source/platform")
###
###FILE(GLOB MBED_CLOUD_CLIENT_EXAMPLE_SRC
###    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
###    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
###    "${CMAKE_CURRENT_SOURCE_DIR}/components/source/*.c"
###    "${CMAKE_CURRENT_SOURCE_DIR}/components/source/*.cpp"
###    "${CMAKE_CURRENT_SOURCE_DIR}/components/source/*.h"
###    "${CMAKE_CURRENT_SOURCE_DIR}/components/mbed-cloud-client/sal-stack-nanostack-eventloop/"
###    "${CMAKE_CURRENT_SOURCE_DIR}/components/mbed-cloud-client/sal-stack-nanostack-eventloop/nanostack-event-loop/*.h"
###    "${CMAKE_CURRENT_SOURCE_DIR}/components/mbed-cloud-client/sal-stack-nanostack-eventloop/source/*.c"
###    )
###########################################################################################################################################
###########################################################################################################################################

set (COMPONENT_ADD_INCLUDEDIRS .
            "${MBED_CLOUD_CLIENT_ESP_PORT}/source"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/source/include"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/source"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/pal-platform/Device"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/pal-platform"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/pal-platform/Middleware"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client/mbed-client-mbed-tls"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client/mbed-client-classic"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client/source"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/certificate-enrollment-client"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/certificate-enrollment-client/source"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal/Utils"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal/Utils/stackUsage"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal/Source/Port"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal/Source/Port/PlatformAPI"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal/Source/Port/Reference-Impl"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal/Source/Port/Reference-Impl/Lib_Specific"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal/Source/Port/Reference-Impl/Lib_specific/mbedTLS"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal/Source/Port/Reference-Impl/Generic"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal/Source/Port/Reference-Impl/Generic/Entropy"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal/Source/Port/Reference-Impl/Generic/SST"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal/Source/Port/Reference-Impl/Generic/DRBG"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal/Source/Port/Reference-Impl/Generic/ROT"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal/Source/Port/Reference-Impl/Generic/Storage"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal/Source/Port/Reference-Impl/Generic/Storage/Flash"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal/Source"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal/Source/PAL-Impl"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal/Source/PAL-Impl/Modules"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal/Source/PAL-Impl/Services-API"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal/Configs"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal/Configs/pal_config/FreeRTOS"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/factory-configurator-client"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/factory-configurator-client/fcc-output-info-handler"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/factory-configurator-client/ftcd-comm-base"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/factory-configurator-client/ftcd-comm-socket"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/factory-configurator-client/ftcd-comm-serial"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/factory-configurator-client/factory-configurator-client"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/factory-configurator-client/storage"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/factory-configurator-client/mbed-client-esfs"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/factory-configurator-client/mbed-client-esfs/source"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/factory-configurator-client/crypto-service"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/factory-configurator-client/utils"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/factory-configurator-client/key-config-manager"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/factory-configurator-client/mbed-trace-helper"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/factory-configurator-client/psa-driver"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/factory-configurator-client/fcc-bundle-handler"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/delta-tool-internal"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/firmware-manager"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/source-http-socket"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/device-identity"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/manifest-manager"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/lwm2m-mbed"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/lwm2m-mbed/update-client-lwm2m"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/lwm2m-mbed/source"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/lwm2m-mbed/source"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/pal-target-specific"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/pal-flashiap"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/pal-flashiap/update-client-pal-flashiap"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/pal-flashiap/source"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/common"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/common/update-client-common"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/common/source"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/metadata-header"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/metadata-header/update-client-metadata-header"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/metadata-header/source"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/pal-linux"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/pal-linux/scripts"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/pal-linux/scripts/openwrt"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/pal-linux/scripts/generic"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-coap"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-coap/mbed-coap"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-coap/source"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/ns-hal-pal"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-cloud-client"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/sal-stack-nanostack-eventloop"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/sal-stack-nanostack-eventloop/source"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-trace"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/secure-device-access-client"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/secure-device-access-client/cose-c"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/secure-device-access-client/secure-device-access"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/secure-device-access-client/sda-cose"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/secure-device-access-client/sda-cose/sda-cose"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/secure-device-access-client/sda-cose/source"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/secure-device-access-client/helpers"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/secure-device-access-client/helpers/helpers"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/secure-device-access-client/helpers/source"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/secure-device-access-client/logger"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/secure-device-access-client/logger/logger"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/secure-device-access-client/logger/sources"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/secure-device-access-client/mem"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/secure-device-access-client/sda-bundle-parser"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/nanostack-libservice"
            

    }

set (COMPONENT_SRCDIRS
            "${MBED_CLOUD_CLIENT_ESP_PORT}/pal-platform/Device"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/pal-platform"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/pal-platform/Middleware"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client/mbed-client-mbed-tls"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client/mbed-client-classic"                                       
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client/source"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/certificate-enrollment-client"                                         
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/certificate-enrollment-client/source"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal"                                                       
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal/Utils"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal/Utils/stackUsage"                                      
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal/Source/Port"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal/Source/Port/PlatformAPI"                               
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal/Source/Port/Reference-Impl"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal/Source/Port/Reference-Impl/Lib_Specific"               
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal/Source/Port/Reference-Impl/Lib_specific/mbedTLS"       
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal/Source/Port/Reference-Impl/Generic"                    
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal/Source/Port/Reference-Impl/Generic/Entropy"            
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal/Source/Port/Reference-Impl/Generic/SST"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal/Source/Port/Reference-Impl/Generic/DRBG"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal/Source/Port/Reference-Impl/Generic/ROT"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal/Source/Port/Reference-Impl/Generic/Storage"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal/Source/Port/Reference-Impl/Generic/Storage/Flash"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal/Source"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal/Source/PAL-Impl"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal/Source/PAL-Impl/Modules"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal/Source/PAL-Impl/Services-API"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal/Configs"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-client-pal/Configs/pal_config/FreeRTOS"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/factory-configurator-client"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/factory-configurator-client/fcc-output-info-handler"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/factory-configurator-client/ftcd-comm-base"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/factory-configurator-client/ftcd-comm-socket"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/factory-configurator-client/ftcd-comm-serial"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/factory-configurator-client/factory-configurator-client"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/factory-configurator-client/storage"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/factory-configurator-client/mbed-client-esfs"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/factory-configurator-client/mbed-client-esfs/source"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/factory-configurator-client/crypto-service"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/factory-configurator-client/utils"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/factory-configurator-client/key-config-manager"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/factory-configurator-client/mbed-trace-helper"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/factory-configurator-client/psa-driver"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/factory-configurator-client/fcc-bundle-handler"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/delta-tool-internal"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/firmware-manager"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/source-http-socket"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/device-identity"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/manifest-manager"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/lwm2m-mbed"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/lwm2m-mbed/update-client-lwm2m"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/lwm2m-mbed/source"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/lwm2m-mbed/source"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/pal-target-specific"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/pal-flashiap"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/pal-flashiap/update-client-pal-flashiap"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/pal-flashiap/source"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/common"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/common/update-client-common"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/common/source"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/metadata-header"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/metadata-header/update-client-metadata-header"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/metadata-header/source"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/pal-linux"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/pal-linux/scripts"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/pal-linux/scripts/openwrt"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/update-client-hub/modules/pal-linux/scripts/generic"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-coap"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-coap/mbed-coap"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-coap/source"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/ns-hal-pal"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-cloud-client"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/sal-stack-nanostack-eventloop"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/sal-stack-nanostack-eventloop/source"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/mbed-trace"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/secure-device-access-client"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/secure-device-access-client/cose-c"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/secure-device-access-client/secure-device-access"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/secure-device-access-client/sda-cose"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/secure-device-access-client/sda-cose/sda-cose"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/secure-device-access-client/sda-cose/source"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/secure-device-access-client/helpers"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/secure-device-access-client/helpers/helpers"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/secure-device-access-client/helpers/source"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/secure-device-access-client/logger"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/secure-device-access-client/logger/logger"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/secure-device-access-client/logger/sources"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/secure-device-access-client/mem"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/secure-device-access-client/sda-bundle-parser"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/source"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/mbed-cloud-client/nanostack-libservice"
            "${MBED_CLOUD_CLIENT_ESP_PORT}/source"

    }

target_link_libraries("${CMAKE_CURRENT_SOURCE_DIR}")
                                                                                   
CREATE_TEST_LIBRARY(mbedCloudClientExample "${MBED_CLOUD_CLIENT_EXAMPLE_SRC}" "")
                                                                                   
add_dependencies(mbedCloudClientExample mbedCloudClient)
                                                                                   
ADDSUBDIRS()
                   
set (COMPONENT_SUBMODULES "${MBED_CLOUD_CLIENT_ESP_PORT}/components")
set (COMPONENT_REQUIRES ".")

register_component()
                                                                                   
target_compile_definitions(${COMPONENT_TARGET} PUBLIC
            -D__FREERTOS__
            -DMBED_CONF_NS_HAL_PAL_EVENT_LOOP_THREAD_STACK_SIZE=8192
            -DNS_EXCLUDE_HIGHRES_TIMER
            -DNS_EVENTLOOP_USE_TICK_TIMER
            -DMBED_CONF_MBED_CLIENT_EVENT_LOOP_SIZE
        }          
