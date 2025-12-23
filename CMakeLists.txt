cmake_minimum_required(VERSION 3.20)

project(TMDB_CLI_Tool LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)  # CPR requires C++17!
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# nlohmann/json first (header-only, quick)
FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(json)

# CPR options (must be BEFORE MakeAvailable(cpr))
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)                    # Static build (single .exe)
set(CPR_FORCE_WINSSL_BACKEND ON CACHE BOOL "" FORCE)              # Use Windows built-in SSL
set(CURL_ZLIB OFF CACHE BOOL "" FORCE)                            # Disable gzip (avoids ZLIB issues)
set(CURL_BROTLI OFF CACHE BOOL "" FORCE)                          # Disable Brotli
set(CURL_USE_LIBPSL OFF CACHE BOOL "" FORCE)                      # Disable PSL
set(CPR_ENABLE_CURL_HTTP_ONLY ON CACHE BOOL "" FORCE)             # HTTP/HTTPS only (correct option)

FetchContent_Declare(
    cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG 1.14.1  # Latest stable
)
FetchContent_MakeAvailable(cpr)

add_executable(${PROJECT_NAME}
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE cpr::cpr nlohmann_json::nlohmann_json)