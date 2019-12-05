#
# "main" pseudo-component makefile.
#
# (Uses default behaviour of compiling all source files in directory, adding 'include' to include path.)
#

#EXTRA_COMPONENT_DIRS += $(abspath delta-tool) $(abspath mbed-cloud-client) $(abspath pal-platform) $(abspath profiles) \
#						$(abspath source)

#COMPONENT_ADD_INCLUDEDIRS += 	$(abspath delta-tool) $(abspath mbed-cloud-client) $(abspath pal-platform) $(abspath profiles) \
#								$(abspath source)
#

# Add the CXXFLAGS
CXXFLAGS += -std=c++17

##----------------------------------------------##
# Added the below flag to remove the error
# will be initialized after [-Werror=reorder]
##----------------------------------------------##
CXXFLAGS += -Wno-reorder

##--------------------------------------------------------------------##
#CFLAGS += -D__FREERTOS__
#CXXFLAGS += -D__FREERTOS__
#CFLAGS += -DMBED_CONF_NS_HAL_PAL_EVENT_LOOP_THREAD_STACK_SIZE=8192
##--------------------------------------------------------------------##

COMPONENT_ADD_INCLUDEDIRS += ../ 
COMPONENT_ADD_INCLUDEDIRS += ../components/source                                                                                                                                                                    
COMPONENT_ADD_INCLUDEDIRS += ../components/source/include                                                                                                                                                         
COMPONENT_ADD_INCLUDEDIRS += ../components/source/platform/include
COMPONENT_ADD_INCLUDEDIRS += ../components/mbed-cloud-client/factory-configurator-client/key-config-manager/source/include
COMPONENT_ADD_INCLUDEDIRS += ../components/mbed-cloud-client/factory-configurator-client/key-config-manager/key-config-manager
COMPONENT_ADD_INCLUDEDIRS += ../components/mbed-cloud-client/factory-configurator-client/factory-configurator-client/factory-configurator-client
COMPONENT_ADD_INCLUDEDIRS += ../components/mbed-cloud-client/factory-configurator-client/fcc-output-info-handler/fcc-output-info-handler
COMPONENT_ADD_INCLUDEDIRS += ../components/mbed-cloud-client/factory-configurator-client/fcc-bundle-handler/fcc-bundle-handler
COMPONENT_ADD_INCLUDEDIRS += ../components/mbed-cloud-client/factory-configurator-client/storage/storage
COMPONENT_ADD_INCLUDEDIRS += ../components/mbed-cloud-client/factory-configurator-client/mbed-client-esfs/source/include
COMPONENT_ADD_INCLUDEDIRS += ../components/mbed-cloud-client/factory-configurator-client/crypto-service/crypto-service
COMPONENT_ADD_INCLUDEDIRS += ../components/mbed-cloud-client/factory-configurator-client/mbed-trace-helper/mbed-trace-helper
COMPONENT_ADD_INCLUDEDIRS += ../components/mbed-cloud-client
COMPONENT_ADD_INCLUDEDIRS += ../components/mbed-cloud-client/mbed-cloud-client
COMPONENT_ADD_INCLUDEDIRS += ../components/mbed-cloud-client/mbed-client
COMPONENT_ADD_INCLUDEDIRS += ../components/mbed-cloud-client/mbed-client/source/include
COMPONENT_ADD_INCLUDEDIRS += ../components/mbed-cloud-client/mbed-client/source
COMPONENT_ADD_INCLUDEDIRS += ../components/mbed-cloud-client/mbed-client-randlib/mbed-client-randlib
#COMPONENT_ADD_INCLUDEDIRS += ../components/mbed-cloud-client/mbed-client/source/include
COMPONENT_ADD_INCLUDEDIRS += ../components/mbed-cloud-client/mbed-client/mbed-client-c/nsdl-c
COMPONENT_ADD_INCLUDEDIRS += ../components/mbed-cloud-client/mbed-client/mbed-client-c/source/include
COMPONENT_ADD_INCLUDEDIRS += ../components/mbed-cloud-client/mbed-client/mbed-client
COMPONENT_ADD_INCLUDEDIRS += ../components/mbed-cloud-client/mbed-trace
COMPONENT_ADD_INCLUDEDIRS += ../components/mbed-cloud-client/source
COMPONENT_ADD_INCLUDEDIRS += ../components/mbed-cloud-client/ns-hal-pal
COMPONENT_ADD_INCLUDEDIRS += ../components/mbed-cloud-client/nanostack-libservice/mbed-client-libservice
COMPONENT_ADD_INCLUDEDIRS += ../components/mbed-cloud-client/mbed-client-pal/Source
COMPONENT_ADD_INCLUDEDIRS += ../components/mbed-cloud-client/mbed-client-pal/Source/PAL-Impl/Services-API
COMPONENT_ADD_INCLUDEDIRS += ../components/mbed-cloud-client/mbed-client-pal/Configs/pal_config
#COMPONENT_ADD_INCLUDEDIRS += ../components/mbed-cloud-client/mbed-client-pal/Configs/pal_config/SXOS
COMPONENT_ADD_INCLUDEDIRS += ../components/mbed-cloud-client/mbed-client-pal/Configs/pal_config/FreeRTOS
COMPONENT_ADD_INCLUDEDIRS += ../components/mbed-cloud-client/mbed-client/mbed-client-c
COMPONENT_ADD_INCLUDEDIRS += ../components/mbed-cloud-client/mbed-coap/mbed-coap
COMPONENT_ADD_INCLUDEDIRS += ../components/mbed-cloud-client/mbed-client-randlib
COMPONENT_ADD_INCLUDEDIRS += ../components/mbed-cloud-client/nanostack-libservice
COMPONENT_ADD_INCLUDEDIRS += ../components/mbed-cloud-client/sal-stack-nanostack-eventloop
COMPONENT_ADD_INCLUDEDIRS += ../components/mbed-cloud-client/sal-stack-nanostack-eventloop/nanostack-event-loop
COMPONENT_ADD_INCLUDEDIRS += ../components/mbed-cloud-client/certificate-enrollment-client/certificate-enrollment-client
COMPONENT_ADD_INCLUDEDIRS += ../components/mbed-cloud-client/update-client-hub
COMPONENT_ADD_INCLUDEDIRS += ../components/mbed-cloud-client/update-client-hub/modules/common
COMPONENT_ADD_INCLUDEDIRS += ../components/pal-platform

COMPONENT_SRCDIRS += ../components/source
COMPONENT_SRCDIRS += ../components/mbed-cloud-client/mbed-client/source
COMPONENT_SRCDIRS += ../components/mbed-cloud-client/sal-stack-nanostack-eventloop/source
COMPONENT_SRCDIRS += ../components/source/platform/FreeRTOS
COMPONENT_SRCDIRS += ../components/mbed-cloud-client/nanostack-libservice/source/nsdynmemLIB
COMPONENT_SRCDIRS += ../components/mbed-cloud-client/ns-hal-pal



COMPONENT_ADD_LDFLAGS += -L$(PROJECT_PATH)/build/source/libsource.a
COMPONENT_ADD_LDFLAGS += -L$(PROJECT_PATH)/build/main/libmain.a
COMPONENT_ADD_LDFLAGS += -L$(PROJECT_PATH)/build/components/libcomponents.a
COMPONENT_ADD_LDFLAGS += -L$(PROJECT_PATH)/build/source/libsource.a
#COMPONENT_ADD_LDFLAGS += -L$(PROJECT_PATH)/build/mbed-cloud-client/libmbed-cloud-client.a
#COMPONENT_ADD_LDFLAGS = -L$(PROJECT_PATH)/build/pal-platform/libpal-platform.a
#COMPONENT_ADD_LDFLAGS = -L$(PROJECT_PATH)/build/delta-tool/libdelta-tool.a
#COMPONENT_ADD_LDFLAGS = -L$(PROJECT_PATH)/build/profiles/libprofiles.a

