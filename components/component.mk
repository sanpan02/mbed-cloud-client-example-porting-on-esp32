#  
#  # "main" pseudo-component makefile.
#  
#  # (Uses default behaviour of compiling all source files in directory, adding 'include' to include path.)
#  
#     
#

#COMPONENT_ADD_LDFLAGS = -lstdc++ -L$(COMPONENT_NAME)

#COMPONENT_ADD_LDFLAGS := -Lmbed-cloud-client -Lsource -Lmain -L$(PROJECT_PATH)/*.lib 
#CFLAGS += -D__FREERTOS__

#COMPONENT_SRCDIRS := . 
#COMPONENT_ADD_INCLUDEDIRS += .
#COMPONENT_ADD_INCLUDEDIRS += ../ 
#COMPONENT_ADD_INCLUDEDIRS += source                                                                                                                                                                    
#COMPONENT_ADD_INCLUDEDIRS += source/include                                                                                                                                                         
#COMPONENT_ADD_INCLUDEDIRS += source/platform/include
#COMPONENT_ADD_INCLUDEDIRS += mbed-cloud-client/factory-configurator-client/key-config-manager/source/include
#COMPONENT_ADD_INCLUDEDIRS += mbed-cloud-client/factory-configurator-client/key-config-manager/key-config-manager
#COMPONENT_ADD_INCLUDEDIRS += mbed-cloud-client/factory-configurator-client/factory-configurator-client/factory-configurator-client
#COMPONENT_ADD_INCLUDEDIRS += mbed-cloud-client/factory-configurator-client/fcc-output-info-handler/fcc-output-info-handler
#COMPONENT_ADD_INCLUDEDIRS += mbed-cloud-client/factory-configurator-client/fcc-bundle-handler/fcc-bundle-handler
#COMPONENT_ADD_INCLUDEDIRS += mbed-cloud-client/factory-configurator-client/storage/storage
#COMPONENT_ADD_INCLUDEDIRS += mbed-cloud-client/factory-configurator-client/mbed-client-esfs/source/include
#COMPONENT_ADD_INCLUDEDIRS += mbed-cloud-client/factory-configurator-client/crypto-service/crypto-service
#COMPONENT_ADD_INCLUDEDIRS += mbed-cloud-client/factory-configurator-client/mbed-trace-helper/mbed-trace-helper
#COMPONENT_ADD_INCLUDEDIRS += mbed-cloud-client
#COMPONENT_ADD_INCLUDEDIRS += mbed-cloud-client/mbed-cloud-client
#COMPONENT_ADD_INCLUDEDIRS += mbed-cloud-client/mbed-client
#COMPONENT_ADD_INCLUDEDIRS += mbed-cloud-client/mbed-client/mbed-client
#COMPONENT_ADD_INCLUDEDIRS += mbed-cloud-client/mbed-trace
#COMPONENT_ADD_INCLUDEDIRS += mbed-cloud-client/source
#COMPONENT_ADD_INCLUDEDIRS += mbed-cloud-client/ns-hal-pal
#COMPONENT_ADD_INCLUDEDIRS += mbed-cloud-client/nanostack-libservice/mbed-client-libservice
#COMPONENT_ADD_INCLUDEDIRS += mbed-cloud-client/mbed-client-pal/Source
#COMPONENT_ADD_INCLUDEDIRS += mbed-cloud-client/mbed-client-pal/Source/PAL-Impl/Services-API
#COMPONENT_ADD_INCLUDEDIRS += mbed-cloud-client/mbed-client-pal/Configs/pal_config
##COMPONENT_ADD_INCLUDEDIRS += mbed-cloud-client/mbed-client-pal/Configs/pal_config/SXOS
#COMPONENT_ADD_INCLUDEDIRS += mbed-cloud-client/mbed-client-pal/Configs/pal_config/FreeRTOS
#COMPONENT_ADD_INCLUDEDIRS += mbed-cloud-client/mbed-client/mbed-client-c
#COMPONENT_ADD_INCLUDEDIRS += mbed-cloud-client/mbed-coap/mbed-coap
#COMPONENT_ADD_INCLUDEDIRS += mbed-cloud-client/mbed-client-randlib
#COMPONENT_ADD_INCLUDEDIRS += mbed-cloud-client/nanostack-libservice
#COMPONENT_ADD_INCLUDEDIRS += mbed-cloud-client/sal-stack-nanostack-eventloop
#COMPONENT_ADD_INCLUDEDIRS += mbed-cloud-client/sal-stack-nanostack-eventloop/nanostack-event-loop
#COMPONENT_ADD_INCLUDEDIRS += mbed-cloud-client/certificate-enrollment-client/certificate-enrollment-client
#COMPONENT_ADD_INCLUDEDIRS += mbed-cloud-client/update-client-hub
#COMPONENT_ADD_INCLUDEDIRS += mbed-cloud-client/update-client-hub/modules/common

#add_definitions(-D__FREERTOS__)
