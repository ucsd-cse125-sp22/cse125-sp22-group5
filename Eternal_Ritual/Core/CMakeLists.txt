# Created by Kangming Yu on 5/23/22.

cmake_minimum_required(VERSION 3.18)
project(Core)

list(APPEND CoreAllSubDir "OfflineCore")
list(APPEND CoreAllSubDir "ServerCore")
list(APPEND CoreAllSubDir "ClientCore")


foreach(dirname ${CoreAllSubDir}) 
    add_subdirectory(${dirname})
endforeach()