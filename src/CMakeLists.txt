# src/CMakeLists.txt

# Set include directories for all targets
include_directories(${CMAKE_SOURCE_DIR}/include)

# Main library
add_library(gitlab-downloader-lib
    services/GitLabService.cpp
    controllers/ApiController.cpp
)

target_include_directories(gitlab-downloader-lib
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/include/gitlab-downloader
)


target_link_libraries(gitlab-downloader-lib
    PUBLIC
        Drogon::Drogon
        JsonCpp::JsonCpp
        fmt::fmt
        OpenSSL::SSL
        OpenSSL::Crypto
        nlohmann_json::nlohmann_json
)

# Main executable
add_executable(gitlab-downloader
    main.cpp
)

target_include_directories(gitlab-downloader-lib
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/include/gitlab-downloader
)



target_link_libraries(gitlab-downloader
    PRIVATE
        gitlab-downloader-lib
)