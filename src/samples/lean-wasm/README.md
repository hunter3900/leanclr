# Lean-WASM

Lean-WASM is a WebAssembly build of the LeanCLR runtime, enabling .NET assemblies to be executed directly in web browsers.

## Overview

This project compiles the LeanCLR runtime to WebAssembly using Emscripten, allowing you to run .NET code in browser environments. The compiled output consists of:

- `lean.js` - JavaScript glue code for loading and interacting with the WASM module
- `lean.wasm` - The compiled WebAssembly binary of the LeanCLR runtime

### Features

- Load and execute .NET assemblies in the browser
- Supports memory growth for dynamic allocation
- Modular design with JavaScript interop via `ccall`/`cwrap`

## Prerequisites

Before building the project, ensure you have the following tools installed:

### 1. CMake

CMake 3.15 or higher is required.

- **Download**: https://cmake.org/download/
- Verify installation:
  ```cmd
  cmake --version
  ```

### 2. Ninja Build System

Ninja is recommended for faster builds with Emscripten.

- **Download**: https://ninja-build.org/
- Verify installation:
  ```cmd
  ninja --version
  ```

### 3. Emscripten SDK (emsdk)

Emscripten is required to compile C++ to WebAssembly.

- **Download and Setup**:
  ```cmd
  git clone https://github.com/emscripten-core/emsdk.git
  cd emsdk
  emsdk install latest
  emsdk activate latest
  ```

- For more details, see: https://emscripten.org/docs/getting_started/downloads.html

## Building

### Step 1: Prepare Emscripten Environment

Before building, you must activate the Emscripten SDK environment. Navigate to your emsdk installation directory and run:

```cmd
emsdk_env.bat
```

This sets up the necessary environment variables (`emcc`, `emcmake`, `emmake`, etc.) for the current terminal session.

### Step 2: Build the Project

Navigate to the `lean-wasm` directory and run the build script:

```cmd
cd src/samples/lean-wasm
build-wasm.bat
```

The build script performs the following:
1. Runs `emcmake cmake` to configure the project with Emscripten toolchain
2. Runs `emmake cmake --build` to compile the project

### Build Output

After a successful build, the output files will be located in:

```
build-wasm/bin/
├── lean.js      # JavaScript module loader
└── lean.wasm    # WebAssembly binary
```

## Usage

### Running in Browser

1. Copy the built `lean.js` and `lean.wasm` files to your web server directory (e.g., `h5/`)

2. Include the JavaScript module in your HTML:
   ```html
   <script src="lean.js"></script>
   ```

3. Initialize the WASM module with configuration:
   ```javascript
   let Module = null;
   let assemblyCache = {};

   // Initialize WASM module
   const moduleConfig = {
       print: (text) => console.log(text),      // redirect stdout
       printErr: (text) => console.error(text), // redirect stderr
   };

   createStartupModule(moduleConfig).then((Module_) => {
       Module = Module_;

       // Implement load_assembly_file callback for loading .NET assemblies
       Module.load_assembly_file = function(namePtr, bufPtr, sizePtr) {
           // Read assembly name from WASM memory
           const view = Module.HEAPU8;
           let end = namePtr;
           while (view[end] !== 0) end++;
           const assemblyName = new TextDecoder('utf-8').decode(view.slice(namePtr, end));

           if (assemblyCache[assemblyName]) {
               const data = assemblyCache[assemblyName];
               // Allocate memory in WASM and copy assembly data
               const ptr = Module.allocate(data);
               Module.HEAPU8.set(data, ptr);
               Module.setValue(bufPtr, ptr, '*');
               Module.setValue(sizePtr, data.length, 'i32');
               return 0; // Success
           }
           return 1; // Not found
       };
   });
   ```

4. Pre-load .NET assembly files into cache:
   ```javascript
   async function loadAssembly(filename) {
       const response = await fetch(filename);
       const buffer = await response.arrayBuffer();
       const assemblyName = filename.replace('.dll.bytes', '');
       assemblyCache[assemblyName] = new Uint8Array(buffer);
   }

   // Load required assemblies
   await loadAssembly('mscorlib.dll.bytes');
   await loadAssembly('System.dll.bytes');
   await loadAssembly('YourAssembly.dll.bytes');
   ```

5. Initialize the runtime and execute methods:
   ```javascript
   // Initialize runtime (must be called before loading assemblies)
   const result = Module.ccall('initialize_runtime', 'number', [], []);
   if (result !== 0) {
       console.error('Runtime initialization failed:', result);
       return;
   }

   // Load assembly
   const load_assemby = Module.cwrap('load_assemby', 'number', ['string']);
   const assemblyPtr = load_assemby('YourAssembly');

   // Invoke method
   const invoke_method = Module.cwrap('invoke_method', 'number', ['number', 'string', 'string']);
   const invokeResult = invoke_method(assemblyPtr, 'Namespace.ClassName', 'MethodName');
   ```

### Demo

A working demo is available in the `h5/` directory, which includes:

- `index.html` - Demo page
- `lean.js` / `lean.wasm` - Pre-built WASM module
- `*.dll.bytes` - Sample .NET assemblies (mscorlib, System, CoreTests, etc.)

## Exported Functions

The WASM module exports the following C functions for JavaScript interop:

| Function | Description |
|----------|-------------|
| `_load_assemby` | Load a .NET assembly by name |
| `_invoke_method` | Invoke a method on a loaded assembly |
| `_initialize_runtime` | Initialize the LeanCLR runtime |

## Troubleshooting

### Common Issues

1. **`emcmake` or `emmake` not found**
   - Ensure you have run `emsdk_env.bat` in the current terminal session

2. **CMake version too old**
   - Upgrade CMake to version 3.15 or higher

3. **Build fails with memory errors**
   - The build is configured with `ALLOW_MEMORY_GROWTH=1` to handle dynamic memory allocation

## License

See the [LICENSE](../../../LICENSE) file in the project root for license information.
