cmake_minimum_required(VERSION 3.5)

#add_definitions(-D__FREERTOS__)

set(inc_src "."
            "delta-tool/*.*"
            "mbed-cloud-client/*.*"
            "pal-platform/*.*"
            "profiles/*.*"
            "source/*.*"
            "components/mbed-cloud-client/mbed-client/source/*.cpp"
   )

set(inc_dir "."
            "delta-tool"
            "mbed-cloud-client"
            "pal-platform"
            "profiles"
            "source"
            "components/mbed-cloud-client/mbed-client/source/*.h"
   )

#idf_component_register( SRCS         "${inc_src}"
#                        INCLUDE_DIRS "${inc_dir}"
#                      )
register_component(SRCS         "${inc_src}"
                   INCLUDE_DIRS "${inc_dir}"
                  )

target_compile_definitions(${COMPONENT_TARGET} PUBLIC
                -D__FREERTOS__
                -DMBED_CONF_NS_HAL_PAL_EVENT_LOOP_THREAD_STACK_SIZE
                -DNS_EXCLUDE_HIGHRES_TIMER 
                -DNS_EVENTLOOP_USE_TICK_TIMER
                -DMBED_CONF_MBED_CLIENT_EVENT_LOOP_SIZE=8192
        }
