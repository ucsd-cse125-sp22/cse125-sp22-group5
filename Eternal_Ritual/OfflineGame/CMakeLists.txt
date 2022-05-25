# Created by Kangming Yu on 5/23/22.

cmake_minimum_required(VERSION 3.18)  
project(OfflineGame)     
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


add_executable(OfflineGame ${AllFile})


target_include_directories(OfflineGame PUBLIC
    ${PROJECT_ROOT_DIR}
)


target_link_libraries(OfflineGame PUBLIC 
    KGLEngine
    OfflineCore
)


add_custom_command(TARGET OfflineGame POST_BUILD
    COMMAND echo "Copying all dll libs to OfflineGame Debug folder..."
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${ASSIMP_LIB_BIN} $<TARGET_FILE_DIR:OfflineGame>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${FREETYPE_LIB_BIN} $<TARGET_FILE_DIR:OfflineGame>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${GLEW_LIB_BIN} $<TARGET_FILE_DIR:OfflineGame>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${GLFW_LIB_BIN} $<TARGET_FILE_DIR:OfflineGame>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SFML_LIB_BIN_AUDIO} $<TARGET_FILE_DIR:OfflineGame>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SFML_LIB_BIN_SYSTEM} $<TARGET_FILE_DIR:OfflineGame>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SFML_LIB_BIN_OPENAL} $<TARGET_FILE_DIR:OfflineGame>
)