cmake_minimum_required(VERSION 3.15)
project(lean CXX)

# Bring in the runtime library
add_subdirectory(../../runtime runtime_build)

# Startup executable
add_executable(lean main.cpp)

target_link_libraries(lean PRIVATE leanclr)

set_target_properties(lean PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# Optional: place binaries under build tree for convenience
set_target_properties(lean PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# WebAssembly specific configuration
if(EMSCRIPTEN)
    # Set output as .js + .wasm (no HTML wrapper)
    set_target_properties(lean PROPERTIES SUFFIX ".js")

    target_link_options(lean PRIVATE
        "SHELL:-s WASM=1"
        "SHELL:-s ALLOW_MEMORY_GROWTH=1"
        "SHELL:-s EXPORTED_FUNCTIONS=['_load_assemby','_invoke_method','_initialize_runtime']"
        # Export runtime helpers needed by JS bridge. Do not include raw wasm exports (e.g. _malloc) here.
        "SHELL:-s EXPORTED_RUNTIME_METHODS=['ccall','cwrap','getValue','setValue','allocate','intArrayFromString','HEAPU8']"
        "SHELL:-s MODULARIZE=1"
        "SHELL:-s EXPORT_NAME='createStartupModule'"
        "SHELL:-s ENVIRONMENT=web,worker"
        -O2
    )
endif()
