# Representation and Processing of RGB Images

This project provides tools for the representation and processing of RGB images.

## Getting Started

These instructions will help you compile and run the project on your local machine.

### Prerequisites

Ensure you have the following software installed:

- A C++ compiler with support for C++11 (e.g., GCC or Clang)
- Make (GNU Make or compatible)

### Compilation

To compile the project, navigate to the project directory and run the following command:

`make all`


This will compile and link the source files, generating the `runscript` and `test` executables.

### Running the Test

To run the `test` program, execute the following command:

`./test`


This will run the test executable, which will test various components of the project.

### Running a Script with `runscript`

To run a script using the `runscript` program, execute the following command:

`./runscript scripts/<file_name>`


Replace `<file_name>` with the name of the script file you want to run. This will execute the `runscript` program with the specified script file.

### Cleaning Up

To clean up the build artifacts and executables generated during compilation, run the following command:

`make clean`

This will remove any executables and temporary files generated during the build process.
