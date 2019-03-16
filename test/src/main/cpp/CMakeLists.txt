cmake_minimum_required(VERSION 3.4.1)

add_library(
        hello-jni
        SHARED
        hello-jni.cpp
)

find_library(
        log-lib
        log)

target_link_libraries(
        hello-jni
        ${log-lib}
)