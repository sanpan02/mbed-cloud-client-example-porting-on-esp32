COMPONENT_SRCDIRS := .	\
				include	\
				platform/include \
				platform/FreeRTOS \

					
COMPONENT_ADD_INCLUDEDIRS += $(COMPONENT_SRCDIRS) 
COMPONENT_ADD_INCLUDEDIRS += ../mbed-cloud-client/mbed-coap/mbed-coap
COMPONENT_ADD_INCLUDEDIRS += ../mbed-cloud-client/sal-stack-nanostack-eventloop
COMPONENT_ADD_INCLUDEDIRS += ../mbed-cloud-client/sal-stack-nanostack-eventloop/nanostack-event-loop
COMPONENT_ADD_INCLUDEDIRS += ../mbed-cloud-client/sal-stack-nanostack-eventloop/source

