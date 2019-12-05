cmake_minimum_required(VERSION 3.5)

set(COMPONENT_SRCS "main.cpp")
set(COMPONENT_ADD_INCLUDEDIRS ".")

register_component()


# mbed-cloud-client-example
#####include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
#####include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../components/source")
#####include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../components/source/include")
#####include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../components/source/platform")
#####include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../components/mbed-cloud-client/sal-stack-nanostack-eventloop")
#####include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../components/mbed-cloud-client/source")
#####
#####set(inc_dir "."
######            "${PROJECT_PATH}/components/source"
#####            "/home/span/esp/esp-idf-latest/esp-idf/examples/mbed-cloud-client-example-esp32-port/components/source"
#####            "${PROJECT_PATH}/components/source/include"
#####            "${PROJECT_PATH}/components/source/platform"
#####            "${PROJECT_PATH}/components/mbed-cloud-client/mbed-coap/mbed-coap"
#####            "${PROJECT_PATH}/components/mbed-cloud-client/sal-stack-nanostack-eventloop"
#####            "${PROJECT_PATH}/components/mbed-cloud-client/sal-stack-nanostack-eventloop/nanostack-event-loop"
#####            "${PROJECT_PATH}/components/mbed-cloud-client/sal-stack-nanostack-eventloop/nanostack-event-loop/source"
#####   )
#####
#####set(inc_src "main.cpp"
#####            "/home/span/esp/esp-idf-latest/esp-idf/examples/mbed-cloud-client-example-esp32-port/components/source/application_init.h"
#####            "/home/span/esp/esp-idf-latest/esp-idf/examples/mbed-cloud-client-example-esp32-port/components/source/application_init.cpp"
#####   )
#####                       
#####idf_component_register( SRCS "${inc_src}"
#####                        INCLUDE_DIRS "${inc_dir}"
#####                        REQUIRES "source"
#####                        REQUIRES "mbed-cloud-client"
#####                        REQUIRES "pal-platform"
#####                        REQUIRES "delta-tool"
#####                        REQUIRES "profiles"
#####                      )




#idf_component_register(SRCS "main.cpp"
#                       INCLUDE_DIRS "${CMAKE_CURRENT_SROURCE_DIR}/components"
#                       INCLUDE_DIRS "${CMAKE_CURRENT_SROURCE_DIR}/components/source"
#                      )



