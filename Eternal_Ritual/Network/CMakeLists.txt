# Created by Kangming Yu on 5/23/22.

cmake_minimum_required(VERSION 3.18) 
project(Network)  
set(CMAKE_CXX_STANDARD 17)  


file(GLOB_RECURSE ALL_HEADER_FILES *.h *.hpp *.inc) 
file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.c *.cc)

set(AllFile ${ALL_HEADER_FILES} ${ALL_SOURCE_FILES})

foreach(fileItem ${AllFile})       
    get_filename_component(PARENT_DIR "${fileItem}" DIRECTORY)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")
    string(REPLACE "/" "\\" GROUP "${GROUP}")
    set(GROUP "${GROUP}")
    source_group("${GROUP}" FILES "${fileItem}")
endforeach()


add_library(Network STATIC ${AllFile})


set_target_properties(Network PROPERTIES FOLDER "Component")


target_include_directories(Network PUBLIC 
    ${PROJECT_ROOT_DIR}
    ${GLM_LIB_INCLUDE}
    ${PROTOBUF_LIB_INCLUDE}
)


target_link_libraries(Network PUBLIC 
    ws2_32
)

#target_link_libraries(Network PUBLIC debug
#    ${PROTOBUF_LIB_LIBS_DEBUG}
#)

target_link_libraries(Network PUBLIC
    ${PROTOBUF_LIB_LIBS_RELEASE}
)