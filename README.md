# BigInt: Arbitrary-Precision Integer Library

This is an implementation of a BigInt class in C++ that allows you to work with arbitrary-length integers.
Approximate implementation time 35 hours

## Features

- **String input:** Supports entering strings in the form:
  - from decimal `12345` or `-12345`
  - from hexadecimal `hFFFF FFFF`, `HFFF FFFF`, `0x1` or `0xAaAa`
  - from binary `B1001 1100` or `b1001 1100`
- **String output:** Supports string conversion in the form:
  - `BigInt::toString("dec")`
  - `BigInt::toString("hex")`
  - `BigInt::toString("bin")`
- **Comparison Operations:** Supports basic comparison operations like `<`, `<=`, `>`, `>=`, and `==`.
- **Arithmetic Operations:** Supports basic arithmetic operations like `+`, `-`, `*`, `/`, `%`, and `BigInt::pow()`.
- **Conversion:** Supports conversion between `int`, `unsigned int`, `long long`, `unsigned long long`, `string`, and `BigInt`.
- **Shift Operations:** Supports left and right bit shift operations (`<<` and `>>`).
- **Unary Operators:** Supports unary operators like `+` and `-`.
- **Assignment Operators:** Supports compound assignment operators like `+=`, `-=`, `*=`, `/=`, `%=`, `<<=`, and `>>=`.

## Building and Running

- **Open Visual Studio**

1. Launch Visual Studio on your computer.

- **Create a new project**

1. Go to "File" > "New" > "Project".
2. In the "New Project" window, select "C++" from the left-hand menu, then choose "Console App" from the templates.
3. Give your project a name (e.g., "BigInt") and choose a location to save it, then click "Create".

- **Add your source files**

1. In the "Solution Explorer" window, right-click on the "Source Files" folder and select "Add" > "Existing Item".
2. Navigate to the location of your BigInt.cpp and tests.cpp files, select them, and click "Add".

- **Add the BigInt.h file**

1. Right-click on the "Header Files" folder in the "Solution Explorer" and select "Add" > "Existing Item".
2. Navigate to the location of your BigInt.h file, select it, and click "Add".

- **Configure the project settings**

1. Right-click on the project in the "Solution Explorer" and select "Properties".
2. In the project properties window, go to "Configuration Properties" > "C/C++" > "Language" and set the "C++ Language Standard" to "ISO C++14 Standard (/std:c++14)".
3. Click "OK" to save the changes.

- **Build and run the tests**

1. In the "Solution Explorer" window, double-click on the tests.cpp file to open it.
2. Copy the code from the test.spp file to the main file of your project.
3. Press the "Start" button to build and run the tests.
   - The test results will be displayed in the "Output" window.
