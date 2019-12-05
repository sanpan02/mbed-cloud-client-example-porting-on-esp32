cmake_minimum_required(VERSION 3.5)                                                                                                                                                                                                                 

set(inc_dir "."
            "${CMAKE_CURRENT_SOURCE_DIR}/include"
            "${CMAKE_CURRENT_SOURCE_DIR}/platform"
            "${PROJECT_PATH}/components/mbed-cloud-client/mbed-coap/mbed-coap"
            "${PROJECT_PATH}/components/mbed-cloud-client/sal-stack-nanostack-eventloop"
            "${PROJECT_PATH}/components/mbed-cloud-client/sal-stack-nanostack-eventloop/nanostack-event-loop"
            "${PROJECT_PATH}/components/mbed-cloud-client/sal-stack-nanostack-eventloop/nanostack-event-loop/source"
            )

        
set(inc_src "application_init.cpp"
            "application_init.h"
            "app_platform_setup.c"
            "components/mbed-cloud-client/sal-stack-nanostack-eventloop/nanostack-event-loop/eventOS_event.h"
            "blinky.cpp"
            "blinky.h"
            "certificate_enrollment_user_cb.cpp"
            "certificate_enrollment_user_cb.h"
            "memory_tests.cpp"
            "memory_tests.h"
            "resource.cpp"
            "resource.h"
            "simplem2mclient.h"
                )
         
idf_component_register( SRCS "${inc_src}"
                        INCLUDE_DIRS "${inc_dir}"
                      )
