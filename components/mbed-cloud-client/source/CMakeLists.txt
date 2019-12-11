set(inc_src "*.c"
            "*.cpp"
            )
set(inc_dirs "include"
             "${CMAKE_CURRENT_SOURCE_DIR}/../mbed-client/mbed-client")

idf_component_register(SRCS "${inc_src}"
                       INCLUDE_DIRS "${inc_dirs}"
                      ) 
