# Startup Project

This README provides instructions on how to build the `startup` project.

## Generating the Visual Studio Solution

1. Open a terminal and navigate to the currrent directory:

   ```cmd
   cd <leanclr root dir>/src/samples/startup
   ```

2. Run the `generate-runtime-vs-sln.bat` script:

   ```cmd
   generate-runtime-vs-sln.bat
   ```

   This will generate the Visual Studio solution file for the `startup` project.

## Building the Project

1. Open the generated solution file in Visual Studio.

2. In the Solution Explorer, locate the `startup` project under the `samples` folder.

3. Set the `startup` project as the startup project by right-clicking on it and selecting `Set as Startup Project`.

4. Build the solution by pressing `Ctrl+Shift+B` or selecting `Build > Build Solution` from the menu.

5. Alternatively, you can directly run the `build.bat` script to build the project:

   ```cmd
   build.bat
   ```

6. If the build succeeds, the output binaries will be located in the `build/Release` directory.

## Notes

- Ensure that you have the required dependencies and tools installed, such as CMake and a compatible version of Visual Studio.
- If you encounter any issues, check the logs in the Visual Studio Output window for more details.