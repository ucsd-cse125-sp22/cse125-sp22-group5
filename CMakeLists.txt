# Created by Kangming Yu on 5/23/22.

cmake_minimum_required(VERSION 3.18)
project(Eternal_Ritual)


list(APPEND allSubDir "Eternal_Ritual/KGLEngine")
list(APPEND allSubDir "Eternal_Ritual/Game")
list(APPEND allSubDir "Eternal_Ritual/Network")
list(APPEND allSubDir "Eternal_Ritual/Core")
list(APPEND allSubDir "Eternal_Ritual/OfflineGame")
list(APPEND allSubDir "Eternal_Ritual/ClientGame")
list(APPEND allSubDir "Eternal_Ritual/ServerGame")


set(PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Eternal_Ritual)


set(THIRD_PARTY_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty)

set(ASSIMP_LIB_INCLUDE ${THIRD_PARTY_LIB_DIR}/assimp/include)
set(ASSIMP_LIB_LIBS ${THIRD_PARTY_LIB_DIR}/assimp/libs/assimp-vc143-mt.lib)
set(ASSIMP_LIB_BIN ${THIRD_PARTY_LIB_DIR}/assimp/bin/assimp-vc143-mt.dll)

set(FREETYPE_LIB_INCLUDE ${THIRD_PARTY_LIB_DIR}/freetype/include/freetype)
set(FREETYPE_LIB_LIBS ${THIRD_PARTY_LIB_DIR}/freetype/libs/freetype.lib)
set(FREETYPE_LIB_BIN ${THIRD_PARTY_LIB_DIR}/freetype/bin/freetype.dll)

set(GLEW_LIB_INCLUDE ${THIRD_PARTY_LIB_DIR}/glew/include)
set(GLEW_LIB_LIBS ${THIRD_PARTY_LIB_DIR}/glew/libs/glew32.lib)
set(GLEW_LIB_BIN ${THIRD_PARTY_LIB_DIR}/glew/bin/glew32.dll)

set(GLFW_LIB_INCLUDE ${THIRD_PARTY_LIB_DIR}/glfw/include)
set(GLFW_LIB_LIBS ${THIRD_PARTY_LIB_DIR}/glfw/libs/glfw3dll.lib)
set(GLFW_LIB_BIN ${THIRD_PARTY_LIB_DIR}/glfw/bin/glfw3.dll)

set(GLM_LIB_INCLUDE ${THIRD_PARTY_LIB_DIR}/glm/include)

set(SFML_LIB_INCLUDE ${THIRD_PARTY_LIB_DIR}/SFML/include)
list(APPEND SFML_LIB_LIBS ${THIRD_PARTY_LIB_DIR}/SFML/libs/sfml-audio.lib)
list(APPEND SFML_LIB_LIBS ${THIRD_PARTY_LIB_DIR}/SFML/libs/sfml-system.lib)
set(SFML_LIB_BIN_AUDIO ${THIRD_PARTY_LIB_DIR}/SFML/bin/sfml-audio-2.dll)
set(SFML_LIB_BIN_SYSTEM ${THIRD_PARTY_LIB_DIR}/SFML/bin/sfml-system-2.dll)
set(SFML_LIB_BIN_OPENAL ${THIRD_PARTY_LIB_DIR}/SFML/bin/openal32.dll)

set(PROTOBUF_LIB_INCLUDE ${THIRD_PARTY_LIB_DIR}/protobuf/include)
set(PROTOBUF_LIB_LIBS_RELEASE ${THIRD_PARTY_LIB_DIR}/protobuf/libs/libprotobuf.lib)
set(PROTOBUF_LIB_LIBS_DEBUG ${THIRD_PARTY_LIB_DIR}/protobuf/libs/libprotobufd.lib)


option(USE_SOLUTION_FOLDERS "USE_SOLUTION_FOLDERS" ON)

if(USE_SOLUTION_FOLDERS)
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
  set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakeTargets")
endif()


option(GROUP_BY_EXPLORER "GROUP_BY_EXPLORER" ON)


foreach(dirname ${allSubDir})
    add_subdirectory(${dirname})
endforeach()
