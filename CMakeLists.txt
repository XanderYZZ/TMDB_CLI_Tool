cmake_minimum_required(VERSION 3.20)

project(TMDB_CLI_Tool LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG 1.14.1 
)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)            
set(CPR_FORCE_WINSSL_BACKEND ON CACHE BOOL "" FORCE)       
set(CURL_ZLIB OFF CACHE BOOL "" FORCE)                    
set(CURL_BROTLI OFF CACHE BOOL "" FORCE)                   
set(CURL_USE_LIBPSL OFF CACHE BOOL "" FORCE)               
set(HTTP_ONLY ON CACHE BOOL "" FORCE)                      
FetchContent_MakeAvailable(cpr)

add_executable(${PROJECT_NAME}
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE cpr::cpr)