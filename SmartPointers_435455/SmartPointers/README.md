# Programming Language II

&nbsp;

## Laboratory - upload of the results

Zip the complete C++ module (like Basics) and upload to UPEL to proper destination. \
Add your Student Identifier as the suffix to the filename. \
Filename pattern: \<ModuleName\>\_\<StudentIdentifier\>.zip \
Example filename: **Basics_284818.zip** \
The results **must** be uploaded within the deadline set in the course platform, otherwise, they will not be considered. \
A file with a file name which not fulfill the required pattern will be **rejected**.
&nbsp;

## Requirements

**Compiler**: GCC 13 \
**System**: Ubuntu 24.04 or Debian13 (native instalation / wsl2 / docker)

## Docker - Windows/Linux/Mac

1. Install Docker engine on your machine
2. Install VSCode on your machine
3. Look here: https://code.visualstudio.com/docs/devcontainers/containers
4. Follow tutorial from here: https://code.visualstudio.com/docs/devcontainers/tutorial but instead "New dev Container" click "Open Folder in Container" - The package with workspace contains Dockerfile and .devcontainer.json, "Open Folder in Container" will use it.

## Ubuntu 24.04

### Required system packages install command

```bash
sudo apt install -y gcc-13 g++-13 gdb cmake clang-format
```

## Workspace configuration

### Clang formatter

How to configure default C++ formatter:

1. Open any C++ file
2. Crtl + Shift + P
3. Find 'Format document with' and press Enter
4. Select 'Configure default formatter'
5. Select 'Clang-Format'

**Formatter usage:** Ctrl + Shift + I

## Building single test file

1. Open the CMake extension tab on the left side
2. Configure your project (needed only at the very first time or after build directory removal)
3. Find the desired test target you would like to build
4. Use 'Build' option to build a test from the specified source file
   **Important**: Verify if your build was successful - check terminal output, there should not be any errors
   &nbsp;

## Running single test file (after build)

1. Open the Testing extension tab on the left side
2. Choose test/tests you would like to run
3. Run your test using option 'Run Test' or 'Run Tests
4. When you did a good job, the test will be marked with green color, red otherwise.
5. When one of the tests will fail, you can check the reason by clicking on the red status icon.
   **Important**: You **must** rebuild every test after changing something in your code. Otherwise, you will be testing the older version of the code.
   &nbsp;
