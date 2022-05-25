# Created by Kangming Yu on 5/23/22.

cmake_minimum_required(VERSION 3.18)  
project(ServerGame)     
set(CMAKE_CXX_STANDARD 17)  


file(GLOB_RECURSE ALL_HEADER_FILES *.h *.hpp *.inc) 
file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.c)

set(AllFile ${ALL_HEADER_FILES} ${ALL_SOURCE_FILES})

foreach(fileItem ${AllFile})       
    get_filename_component(PARENT_DIR "${fileItem}" DIRECTORY)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")
    string(REPLACE "/" "\\" GROUP "${GROUP}")
    set(GROUP "${GROUP}")
    source_group("${GROUP}" FILES "${fileItem}")
endforeach()


add_executable(ServerGame ${AllFile})


target_include_directories(ServerGame PUBLIC
    ${PROJECT_ROOT_DIR}
)


target_link_libraries(ServerGame PUBLIC 
    ServerCore
)


add_custom_command(TARGET ServerGame POST_BUILD
    COMMAND echo "Copying all dll libs to ServerGame Debug folder..."
)