file(GLOB_RECURSE KV_STORE_SOURCES "*.h")

add_library(kvstore INTERFACE ${KV_STORE_SOURCES})

target_include_directories(kvstore INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(WW::kvstore ALIAS kvstore)