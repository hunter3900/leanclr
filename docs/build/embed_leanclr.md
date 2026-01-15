# Embedding LeanCLR into Your Project

This document describes how to integrate the LeanCLR runtime into your C++ project.

> ⚠️ **Note**: LeanCLR does not yet provide a standard embedding API. The current embedding approach described in this document is temporary and subject to change. The API will be refined and improved in future versions.

## Overview

LeanCLR is designed to be easily embedded into any C++ project. It is built as a static library with a clean C++ API.

## Prerequisites

- LeanCLR runtime built successfully (see [build_runtime.md](./build_runtime.md))
- C++17 compatible compiler
- CMake 3.15+ (recommended)

## Integration Methods

### Method 1: CMake add_subdirectory (Recommended)

The simplest way to integrate LeanCLR is using CMake's `add_subdirectory`.

#### Project Structure

```
your_project/
├── CMakeLists.txt
├── src/
│   └── main.cpp
└── leanclr/              # LeanCLR source (or as submodule)
    └── src/
        └── runtime/
```

#### CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.15)
project(your_project CXX)

# Add LeanCLR runtime
add_subdirectory(leanclr/src/runtime runtime_build)

# Your executable
add_executable(your_app src/main.cpp)

# Link against LeanCLR
target_link_libraries(your_app PRIVATE leanclr)

set_target_properties(your_app PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
```

### Method 2: Pre-built Library

If you prefer to use a pre-built library:

#### CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.15)
project(your_project CXX)

# Find pre-built LeanCLR
set(LEANCLR_ROOT "/path/to/leanclr")
set(LEANCLR_INCLUDE_DIR "${LEANCLR_ROOT}/src/runtime")
set(LEANCLR_LIBRARY "${LEANCLR_ROOT}/src/runtime/build/Release/leanclr.lib")

add_executable(your_app src/main.cpp)

target_include_directories(your_app PRIVATE ${LEANCLR_INCLUDE_DIR})
target_link_libraries(your_app PRIVATE ${LEANCLR_LIBRARY})

set_target_properties(your_app PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
```

## Basic Usage

### Initializing the Runtime

```cpp
#include "vm/runtime.h"
#include "vm/settings.h"
#include "vm/assembly.h"

using namespace leanclr;

// Custom assembly loader callback
RtResult<utils::Span<byte>> my_assembly_loader(const char* assembly_name) {
    // Load assembly bytes from file, memory, or network
    // Return the raw bytes of the .NET assembly
    // ...
}

int main() {
    // Set the assembly loader
    vm::Settings::set_assembly_loader(my_assembly_loader);
    
    // Initialize the runtime
    auto init_result = vm::Runtime::initialize();
    if (init_result.is_err()) {
        // Handle initialization error
        return -1;
    }
    
    // Load an assembly
    auto ass_result = vm::Assembly::load_by_name("MyAssembly");
    if (ass_result.is_err()) {
        // Handle load error
        return -1;
    }
    
    // Get the module
    auto* mod = ass_result.unwrap()->mod;
    
    // ... invoke methods, etc.
    
    return 0;
}
```

### Loading Assemblies from File

```cpp
#include <fstream>
#include <vector>
#include "alloc/general_allocation.h"

RtResult<utils::Span<byte>> file_assembly_loader(const char* assembly_name) {
    std::string path = std::string(assembly_name) + ".dll";
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    
    if (!file.is_open()) {
        return RtErr::FileNotFound;
    }
    
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    
    auto* buffer = static_cast<uint8_t*>(
        alloc::GeneralAllocation::malloc(size)
    );
    
    if (!buffer) {
        return RtErr::OutOfMemory;
    }
    
    if (!file.read(reinterpret_cast<char*>(buffer), size)) {
        alloc::GeneralAllocation::free(buffer);
        return RtErr::FileNotFound;
    }
    
    return utils::Span<byte>(buffer, static_cast<size_t>(size));
}
```

### Invoking Methods

```cpp
#include "vm/method.h"
#include "vm/class.h"

// Find and invoke a static method
void invoke_entry_point(metadata::RtModuleDef* mod, 
                        const char* class_name, 
                        const char* method_name) {
    // Find the class
    auto class_result = mod->get_class_by_nested_full_name(
        class_name, false, true
    );
    if (class_result.is_err()) {
        return;
    }
    auto* klass = class_result.unwrap();
    
    // Initialize the class
    vm::Class::initialize_all(klass);
    
    // Find the method
    auto* method = vm::Method::find_matched_method_in_class_by_name(
        klass, method_name
    );
    if (!method) {
        return;
    }
    
    // Invoke the method
    auto result = vm::Runtime::invoke_array_arguments_with_run_cctor(
        method, nullptr, nullptr
    );
    if (result.is_err()) {
        // Handle invocation error
    }
}
```

## WebAssembly Integration

For WebAssembly projects, additional JavaScript interop is required.

### Exported Functions

When building for WebAssembly, export the following functions:

```cmake
target_link_options(your_app PRIVATE
    "SHELL:-s EXPORTED_FUNCTIONS=['_initialize_runtime','_load_assemby','_invoke_method']"
    "SHELL:-s EXPORTED_RUNTIME_METHODS=['ccall','cwrap']"
)
```

### JavaScript Usage

```javascript
createStartupModule().then(function(Module) {
    // Implement assembly loading callback
    Module.load_assembly_file = function(namePtr, bufPtr, sizePtr) {
        // Load assembly and return bytes
    };
    
    // Initialize runtime
    Module.ccall('initialize_runtime', 'number', [], []);
    
    // Load assembly
    const load = Module.cwrap('load_assemby', 'number', ['string']);
    const assembly = load('MyAssembly');
    
    // Invoke method
    const invoke = Module.cwrap('invoke_method', 'number', 
        ['number', 'string', 'string']);
    invoke(assembly, 'MyNamespace.MyClass', 'Main');
});
```

## Sample Projects

For complete working examples, refer to:

- [startup sample](../../src/samples/startup/) - Win64 native sample
- [lean-wasm sample](../../src/samples/lean-wasm/) - WebAssembly sample
- [lean tool](../../src/tools/lean/) - Command-line tool embedding LeanCLR

## Best Practices

### Memory Management

- LeanCLR manages its own memory for metadata and managed objects
- Use `alloc::GeneralAllocation` for allocating assembly data
- Do not free memory returned by LeanCLR APIs

### Error Handling

- All LeanCLR APIs return `RtResult<T>` which is either a success value or an error
- Always check `is_err()` before unwrapping results
- Handle errors gracefully to prevent undefined behavior

### Threading (Universal Edition)

- The Universal edition is single-threaded
- Do not call LeanCLR APIs from multiple threads simultaneously
- All runtime operations should be on a single thread

## Troubleshooting

### Common Issues

1. **Linker errors about undefined symbols**
   - Ensure all LeanCLR include directories are added
   - Check that you're linking against `leanclr.lib` (Windows) or `libleanclr.a` (Linux/macOS)

2. **Runtime initialization fails**
   - Verify that the assembly loader callback is properly set
   - Check that mscorlib.dll is accessible

3. **Method invocation fails**
   - Ensure the class is fully initialized before method invocation
   - Verify method signature matches (static, no parameters, etc.)

4. **Assembly not found**
   - Check assembly search paths in your loader
   - Verify assembly name matches (without .dll extension)
