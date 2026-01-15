cmake_minimum_required(VERSION 3.15)
project(leanclr CXX)

set(RUNTIME_DIRS
    alloc
    core
    gc
    icalls
    interp
    intrinsics
    metadata
    os
    utils
    vm
    misc
)

set(RUNTIME_SOURCES)
foreach(dir ${RUNTIME_DIRS})
    file(GLOB dir_sources "${CMAKE_CURRENT_LIST_DIR}/${dir}/*.cpp")
    list(APPEND RUNTIME_SOURCES ${dir_sources})
endforeach()

add_library(leanclr STATIC ${RUNTIME_SOURCES})

set(_include_dirs ${CMAKE_CURRENT_LIST_DIR})
foreach(dir ${RUNTIME_DIRS})
    list(APPEND _include_dirs "${CMAKE_CURRENT_LIST_DIR}/${dir}")
endforeach()

target_include_directories(leanclr PUBLIC ${_include_dirs})
target_include_directories(leanclr PUBLIC ${CMAKE_CURRENT_LIST_DIR}/3rd)

set_target_properties(leanclr PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if(MSVC)
    string(REGEX REPLACE "/EHsc" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    target_compile_options(leanclr PRIVATE /EHs-c-)
elseif(EMSCRIPTEN)
    # WebAssembly (Emscripten) 配置
    target_compile_options(leanclr PRIVATE
        -fno-exceptions
        -fno-rtti
        -O2
    )
    # 链接器选项必须在 target_link_options 中，不能在 COMPILE_FLAGS
    target_link_options(leanclr PRIVATE
        "SHELL: -s WASM=1"
        "SHELL: -s ALLOW_MEMORY_GROWTH=1"
        -O2
    )

else()
    target_compile_options(leanclr PRIVATE -fno-exceptions)
endif()
