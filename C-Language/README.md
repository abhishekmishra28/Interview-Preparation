# Complete C Programming Guide for SDE Placements (C-Core Focus)

## Table of Contents

### Part 1: Fundamentals
- [Introduction to C](#introduction-to-c)
- [Development Environment Setup](#development-environment-setup)
- [Basic Syntax & Structure](#basic-syntax--structure)
- [Data Types, Variables & Storage Classes](#data-types-variables--storage-classes)
- [Operators](#operators)
- [Input/Output](#inputoutput)
- [Control Flow](#control-flow)

### Part 2: Advanced C Concepts
- [Functions & the Call Stack](#functions--the-call-stack)
- [Arrays & Array-Pointer Duality](#arrays--array-pointer-duality)
- [Strings & Null Termination](#strings--null-termination)
- [Pointers - The Heart of C](#pointers---the-heart-of-c)
- [Structures, Unions & Memory Alignment](#structures-unions--memory-alignment)
- [Dynamic Memory Allocation (Heap Management)](#dynamic-memory-allocation-heap-management)
- [File Handling](#file-handling)
- [Preprocessor Directives](#preprocessor-directives)

---

# Part 1: Fundamentals

# Introduction to C

## Why C for SDE Interviews?

```
✅ Foundation language for system programming, OS, embedded systems.
   Understanding C is crucial for roles involving low-level programming.
✅ Direct hardware manipulation & fine-grained memory management.
   No automatic garbage collection or sophisticated runtime. You control everything.
✅ Understanding C → Understanding how computers work at a fundamental level.
   It reveals the "mechanics" abstracted away by higher-level languages (like C++'s smart pointers or STL containers).
✅ Many companies test C fundamentals for SDE roles, especially for core engineering positions.
✅ Gateway to C++: A strong C foundation makes understanding C++'s advanced features (RAII, OOP implementation details, STL internals) much clearer.
✅ Minimal runtime overhead: C compiles directly to machine code, providing maximum performance control.
```

## C Language Features

```
• Procedural programming paradigm
• Low-level memory access (via pointers)
• Fast execution (compiled language)
• Portable across platforms
• Rich standard library (libc)
• Minimal runtime overhead
• Static typing
• Manual memory management
```

---

# Development Environment Setup

## Installation

```bash
# Linux/Mac (GCC is the standard C compiler)
sudo apt-get install gcc        # Ubuntu/Debian
sudo yum install gcc            # CentOS/RHEL
brew install gcc                # macOS

# Windows
# Option 1: Install MinGW (Minimalist GNU for Windows)
#    - Download installer from mingw-w64.org
#    - Select `gcc` and `g++` during installation
# Option 2: Use WSL (Windows Subsystem for Linux)
#    - Install WSL and a Linux distribution (e.g., Ubuntu)
#    - Then follow Linux/Mac instructions
```
**Explanation:** `gcc` (GNU Compiler Collection) is the most common compiler for C. It translates your C source code into an executable program. MinGW provides the GNU toolchain for Windows.

## Compilation & Execution

```bash
# Compile 'program.c' into an executable named 'program'
gcc program.c -o program
./program  # Execute the compiled program

# With warnings enabled (ALWAYS USE! Catches common errors early)
gcc -Wall -Wextra -o program program.c
./program

# With debugging symbols (for use with a debugger like GDB)
gcc -g -o program program.c
gdb ./program

# With optimization level 2 (often used for production code)
gcc -O2 -o program program.c

# Compile multiple source files (e.g., main.c and helper.c)
gcc main.c helper.c -o myapp
```
**Explanation:**
*   `gcc`: Invokes the GNU C compiler.
*   `-o program`: Specifies the output executable name.
*   `-Wall`, `-Wextra`: Enable a comprehensive set of warning messages. These are crucial for writing robust C code.
*   `-g`: Includes debugging information, allowing debuggers to map machine code back to source code.
*   `-O2`: Applies various optimizations during compilation to make the resulting program run faster. Higher optimization levels exist (`-O3`, `-Os` for size).

## Hello World

```c
#include <stdio.h> // Include standard input/output library

int main() {       // Main function, entry point of the program
    printf("Hello, World!\n"); // Print string to console
    return 0;      // Indicate successful execution
}
```
**Compilation:**
```bash
gcc hello.c -o hello
./hello
```
**Explanation:**
*   `#include <stdio.h>`: This is a preprocessor directive. It tells the C preprocessor to include the contents of the `stdio.h` header file before compilation. This file provides declarations for standard input/output functions like `printf`.
*   `int main() { ... }`: The `main` function is the entry point of every C program. Execution begins here. `int` indicates that the function returns an integer status code to the operating system. `0` typically signifies successful execution.
*   `printf("Hello, World!\n");`: `printf` is a standard library function used for formatted output to the console. `\n` is the newline character.

---

# Basic Syntax & Structure

## Program Structure

```c
/*
 * Multi-line comment (C-style)
 * This program demonstrates basic C structure.
 */

// Single-line comment (C99 onwards, widely supported)

#include <stdio.h>      // Preprocessor directive: Includes standard I/O library
#include <stdlib.h>     // Preprocessor directive: Includes standard utility functions

#define MAX_VALUE 100   // Macro definition: A symbolic constant, replaced by preprocessor

// Global variable: Accessible from any function in this file. Stored in Data or BSS segment.
int globalVar = 10;

// Function declaration (Prototype): Informs the compiler about a function's signature.
// This allows `main` to call `add` even if `add` is defined later.
int add(int a, int b);

// Main function - The entry point of the program.
int main() {
    // Local variable: Exists only within `main` function. Stored on the Stack.
    int localVar = 20;

    printf("Global: %d, Local: %d\n", globalVar, localVar);

    int result = add(5, 3); // Function call
    printf("Sum: %d\n", result);

    return 0;           // Return status to the OS (0 for success)
}

// Function definition: Provides the actual implementation of the function.
int add(int a, int b) {
    return a + b;
}
```
**Explanation:**
*   **Comments:** Used to explain code. `/* ... */` for multi-line, `//` for single-line.
*   **`#include`:** Brings in declarations from header files. Without `<stdio.h>`, `printf` would be an undeclared function.
*   **`#define`:** A preprocessor directive for defining macros. These are simple text substitutions performed *before* compilation. `MAX_VALUE` will literally be replaced with `100` wherever it appears.
*   **Global Variables:** Declared outside any function. Their lifetime is the entire program duration.
*   **Function Prototype:** Declares a function's return type, name, and parameter types *before* its definition. This is necessary if the function is called before it's defined (e.g., `add` called in `main` but defined after `main`).
*   **`main` Function:** The program's starting point.
*   **Local Variables:** Declared inside a function. Their lifetime is limited to that function's execution.
*   **Function Definition:** The actual code block for a function.
*   **`return 0;`:** Standard way to indicate successful program execution. Non-zero values usually indicate an error.

## Header Files

```c
// Common standard headers, organized by functionality:

#include <stdio.h>      // Standard I/O (printf, scanf, fopen, fclose, etc.)
#include <stdlib.h>     // Standard utilities (malloc, free, exit, atoi, etc.)
#include <string.h>     // String manipulation (strlen, strcpy, strcmp, etc.)
#include <math.h>       // Mathematical functions (sqrt, sin, cos, pow, etc.)
#include <time.h>       // Time functions (time, clock, difftime, etc.)
#include <ctype.h>      // Character type functions (isdigit, isalpha, tolower, etc.)
#include <limits.h>     // Integer type limits (INT_MIN, INT_MAX, CHAR_BIT, etc.)
#include <float.h>      // Floating-point type limits (FLT_EPSILON, DBL_MAX, etc.)
#include <stdbool.h>    // Boolean type (`bool`, `true`, `false`) (C99 standard)
#include <stdint.h>     // Fixed-width integer types (int8_t, uint32_t, etc.) (C99 standard)
#include <stddef.h>     // Standard definitions (size_t, ptrdiff_t)
```
**Explanation:** Header files contain declarations (function prototypes, macros, type definitions) for standard library functions. They don't contain the actual implementation (which is in library files linked during compilation). Including them ensures the compiler knows how to use these standard features.

---

# Data Types, Variables & Storage Classes

## Primitive Data Types

```c
#include <stdio.h>
#include <limits.h>   // For INT_MIN, INT_MAX, etc.
#include <float.h>    // For DBL_MAX, etc.
#include <stdbool.h>  // For bool, true, false (C99)
#include <stdint.h>   // For fixed-width integers (C99)

int main() {
    // ═══════════════════════════════════════════════════
    // INTEGER TYPES (Signed by default)
    // ═══════════════════════════════════════════════════
    // char:   Typically 1 byte. Can hold a single character or small integer.
    char c = 'A';                    // Stored as ASCII value (e.g., 65)
    unsigned char uc = 255;          // 0 to 255 (if 1 byte)

    // short:  Typically 2 bytes. Smaller range than int.
    short s = 32000;
    unsigned short us = 65000;

    // int:    Typically 4 bytes. Most common integer type.
    int i = 2147483647;
    unsigned int ui = 4294967295U;   // 'U' suffix for unsigned literals

    // long:   Typically 4 or 8 bytes (platform dependent). Guaranteed to be at least as wide as int.
    long l = 2147483647L;            // 'L' suffix for long literals
    unsigned long ul = 4294967295UL;

    // long long: Guaranteed to be at least 8 bytes (C99). For very large integers.
    long long ll = 9223372036854775807LL;  // 'LL' suffix for long long literals
    unsigned long long ull = 18446744073709551615ULL;

    // ═══════════════════════════════════════════════════
    // FLOATING POINT TYPES (Approximate real numbers)
    // ═══════════════════════════════════════════════════
    // float:   Typically 4 bytes. Single precision.
    float f = 3.14f;                 // 'f' suffix for float literals

    // double:  Typically 8 bytes. Double precision. Default for floating point literals.
    double d = 3.141592653589793;

    // long double: Typically 10-16 bytes. Extended precision.
    long double ld = 3.141592653589793238L;  // 'L' suffix for long double literals

    // ═══════════════════════════════════════════════════
    // BOOLEAN (C99 standard, requires <stdbool.h>)
    // ═══════════════════════════════════════════════════
    bool b1 = true;
    bool b2 = false; // Internally represented as 1 and 0

    // ═══════════════════════════════════════════════════
    // FIXED-WIDTH INTEGERS (C99 standard, requires <stdint.h>)
    // Guarantees specific bit widths regardless of platform.
    // E.g., int32_t is always 32 bits, uint64_t always 64 bits.
    // Useful for exact data representation (e.g., network protocols).
    int8_t  _i8 = 127;
    uint16_t _u16 = 65535;
    int32_t _i32 = -2147483648;
    uint64_t _u64 = 18446744073709551615ULL;

    // ═══════════════════════════════════════════════════
    // The `sizeof` operator: Returns the size in bytes of a type or variable.
    // Its return type is `size_t` (an unsigned integer type defined in <stddef.h>).
    // Use `%zu` format specifier for `size_t`.
    // ═══════════════════════════════════════════════════
    printf("\n--- Sizes of Data Types (on this system) ---\n");
    printf("Size of char: %zu bytes\n", sizeof(char));
    printf("Size of short: %zu bytes\n", sizeof(short));
    printf("Size of int: %zu bytes\n", sizeof(int));
    printf("Size of long: %zu bytes\n", sizeof(long));
    printf("Size of long long: %zu bytes\n", sizeof(long long));
    printf("Size of float: %zu bytes\n", sizeof(float));
    printf("Size of double: %zu bytes\n", sizeof(double));
    printf("Size of long double: %zu bytes\n", sizeof(long double));
    printf("Size of bool: %zu bytes\n", sizeof(bool));
    printf("Size of int8_t: %zu bytes\n", sizeof(int8_t));


    // ═══════════════════════════════════════════════════
    // LIMITS of Data Types (from <limits.h> and <float.h>)
    // ═══════════════════════════════════════════════════
    printf("\n--- Limits of Data Types ---\n");
    printf("INT_MIN: %d\n", INT_MIN);
    printf("INT_MAX: %d\n", INT_MAX);
    printf("LONG_MIN: %ld\n", LONG_MIN);
    printf("LONG_MAX: %ld\n", LONG_MAX);
    printf("DBL_MAX: %e\n", DBL_MAX); // Largest representable double
    printf("DBL_EPSILON: %e\n", DBL_EPSILON); // Smallest x such that 1.0 + x != 1.0
                                             // Crucial for float comparisons.

    return 0;
}
```
**Explanation:**
*   **Data Types:** C provides a set of fundamental data types to represent different kinds of values. Their exact sizes can vary between compilers and architectures, but minimum sizes are guaranteed by the C standard. `sizeof` is used to determine the size of any type or variable in bytes.
*   **`unsigned`:** This keyword indicates that a variable can only hold non-negative values, effectively doubling its positive range (e.g., `char` from -128 to 127, `unsigned char` from 0 to 255).
*   **Type Suffixes:** `U`, `L`, `LL`, `f`, `l` are used to explicitly specify the type of a literal constant, preventing unintended type promotions or overflows.
*   **`stdbool.h` and `stdint.h`:** C99 introduced `bool` (true/false) and fixed-width integers (`intN_t`, `uintN_t`) for better code portability and precise control over data representation.
*   **`limits.h` and `float.h`:** These headers define constants that represent the minimum and maximum values (and other properties) that various data types can hold. `DBL_EPSILON` is particularly important for understanding floating-point precision issues.

## Storage Classes

Storage classes in C determine the scope, lifetime, initial value, and storage location of variables.

```c
#include <stdio.h>
#include <stdlib.h> // For malloc/free

// ═══════════════════════════════════════════════════
// 1. `auto` (Automatic Storage Class)
//    - Default for local variables.
//    - Stored on the stack.
//    - Scope: Local to the block in which they are defined.
//    - Lifetime: Created upon entering block, destroyed upon exiting.
//    - Initial Value: Garbage (unless explicitly initialized).
// ═══════════════════════════════════════════════════

void demonstrateAuto() {
    auto int a = 10; // 'auto' is rarely used explicitly as it's the default
    int b;           // Equivalent to auto int b; (contains garbage)

    printf("Inside demonstrateAuto:\n");
    printf("  a (auto, initialized): %d\n", a);
    printf("  b (auto, uninitialized): %d (potentially garbage)\n", b);
    // a and b are destroyed when function exits
}

// ═══════════════════════════════════════════════════
// 2. `static` (Static Storage Class)
//    - Scope: Depends on where it's declared (local or global).
//    - Lifetime: Entire program duration.
//    - Initial Value: 0 (or null for pointers) if uninitialized.
//    - Storage: Data segment (initialized) or BSS segment (uninitialized).
// ═══════════════════════════════════════════════════

// Global static variable:
// - Scope: File scope (only visible within this .c file).
// - Lifetime: Program duration.
static int fileScopeStatic = 50;

void demonstrateStaticLocal() {
    // Local static variable:
    // - Scope: Local to the function.
    // - Lifetime: Program duration (value persists between calls).
    // - Initialized only ONCE at the start of the program.
    static int count = 0;
    count++;
    printf("  Static local count: %d\n", count);
}

// ═══════════════════════════════════════════════════
// 3. `extern` (External Storage Class)
//    - Declares a variable defined in another file (or later in the same file).
//    - Tells the compiler that the variable exists elsewhere.
//    - Does not allocate memory; it's a declaration, not a definition.
// ═══════════════════════════════════════════════════

// Example: If `anotherGlobalVar` is defined in `other_file.c`:
// extern int anotherGlobalVar; // Declares that 'anotherGlobalVar' exists

// For this example, let's declare it within the same file for demonstration
// (but typically extern is for cross-file declarations)
int globalFromExtern = 99; // Definition

void demonstrateExtern() {
    extern int globalFromExtern; // Declaration: uses the global variable defined above
    printf("  Value from extern declaration: %d\n", globalFromExtern);
}


// ═══════════════════════════════════════════════════
// 4. `register` (Register Storage Class)
//    - Suggests to the compiler to store the variable in a CPU register.
//    - Faster access than memory, but limited number of registers.
//    - Compiler usually ignores `register` for modern optimizations if it finds better ways.
//    - Cannot take address of a `register` variable (`&` operator not allowed).
// ═══════════════════════════════════════════════════

void demonstrateRegister() {
    register int counter = 0;
    for (int i = 0; i < 5; i++) {
        counter++;
    }
    printf("  Register variable counter: %d\n", counter);
    // int* ptr = &counter; // ERROR: cannot take address of register variable
}

int main() {
    printf("--- Storage Class Demonstrations ---\n");

    demonstrateAuto();
    printf("After demonstrateAuto, 'a' and 'b' are gone from stack.\n\n");

    printf("File scope static variable: %d\n", fileScopeStatic); // Accessible in main
    printf("Demonstrating static local variable:\n");
    demonstrateStaticLocal(); // count = 1
    demonstrateStaticLocal(); // count = 2 (value persists!)
    demonstrateStaticLocal(); // count = 3
    printf("\n");

    demonstrateExtern();
    printf("\n");

    demonstrateRegister();
    printf("\n");

    return 0;
}
```
**Explanation of Storage Classes:**
*   **`auto`**: The default for local variables. They reside on the *stack* and are destroyed when their scope ends. Their initial value is *garbage*.
*   **`static`**:
    *   **Local `static`**: Its value persists between function calls. It has local scope (only visible within its function) but global lifetime. Stored in the *data segment* (if initialized) or *BSS segment* (if uninitialized).
    *   **Global `static`**: Limits the variable's visibility to the current translation unit (the `.c` file it's defined in). It has global lifetime and is stored in the data/BSS segment. This prevents naming conflicts when linking multiple `.c` files.
*   **`extern`**: Used to declare a global variable that is *defined* in another source file or later in the current file. It informs the compiler that the variable exists but doesn't allocate memory for it. Essential for sharing global variables across multiple `.c` files.
*   **`register`**: A hint to the compiler to store the variable in a CPU register for faster access. Modern compilers are often better at optimizing register usage than manual hints, so it's less commonly used. You *cannot* take the address of a `register` variable, as it doesn't reside in main memory.

## Constants

```c
// Using const keyword
// `const` variables are compile-time constants. Their value cannot be changed after initialization.
// The compiler can sometimes optimize these by replacing their use with the actual value.
const int MAX_USERS = 100;
const float PI_CONST = 3.14159f;

// Using #define (preprocessor macro)
// `#define` performs a simple text substitution before compilation.
// It doesn't participate in C's type system or scoping.
#define BUFFER_SIZE 256
#define NEWLINE '\n'

// Enumeration (`enum`)
// Creates a set of named integer constants. By default, they start from 0 and increment.
// Can be explicitly assigned values. Improves readability.
enum Day {
    SUNDAY,      // 0 (default)
    MONDAY,      // 1
    TUESDAY,     // 2
    WEDNESDAY,   // 3
    THURSDAY,    // 4
    FRIDAY,      // 5
    SATURDAY     // 6
};

enum Color {
    RED = 1,
    GREEN = 5,
    BLUE = 10
};

// Example usage
int main() {
    printf("Max users: %d\n", MAX_USERS);
    printf("Buffer size: %d\n", BUFFER_SIZE);

    enum Day today = MONDAY;
    printf("Today is day number: %d\n", today); // Prints 1

    enum Color favoriteColor = BLUE;
    printf("Favorite color value: %d\n", favoriteColor); // Prints 10

    return 0;
}
```
**Explanation:**
*   **`const` keyword:** Defines a variable whose value cannot be changed after initialization. It's type-checked by the compiler. Often preferred over `#define` for type safety and scope control.
*   **`#define`:** A preprocessor directive for creating symbolic constants (macros). The preprocessor literally replaces the macro name with its value before compilation. No type checking is done. Can lead to subtle bugs if not used carefully (e.g., `SQUARE(x)` macro vs function).
*   **`enum`:** A user-defined data type that consists of a set of named integer constants. Enhances code readability by providing meaningful names for integral values.

## Type Casting

```c
#include <stdio.h>

int main() {
    // ═══════════════════════════════════════════════════
    // IMPLICIT CASTING (Automatic Type Conversion)
    // Occurs when the compiler automatically converts one data type to another,
    // typically from a "smaller" type to a "larger" type to prevent data loss.
    // ═══════════════════════════════════════════════════

    int i = 10;
    float f = i;              // int (4 bytes) is promoted to float (4 bytes, but can represent 10.0 precisely)
    printf("Implicit: int to float: %f\n", f);        // 10.000000

    double d_val = 5.5;
    int i_val = 10;
    double result_implicit = d_val + i_val; // int i_val is implicitly converted to double
    printf("Implicit: double + int: %f\n", result_implicit); // 15.500000

    // ═══════════════════════════════════════════════════
    // EXPLICIT CASTING (Manual Type Conversion)
    // Programmer explicitly tells the compiler to convert one data type to another.
    // This is often necessary when converting to a "smaller" type (potential data loss)
    // or to force a specific arithmetic operation.
    // Syntax: (target_type) expression
    // ═══════════════════════════════════════════════════

    float x = 9.8f;
    int y = (int)x;           // float (9.8) explicitly converted to int (9). Fractional part is truncated.
    printf("Explicit: float to int: %d\n", y);        // 9

    // ═══════════════════════════════════════════════════
    // COMMON CASTING SCENARIOS
    // ═══════════════════════════════════════════════════

    // Integer division vs. Floating-point division
    int a_div = 5, b_div = 2;
    float result1 = a_div / b_div;                  // `a_div / b_div` performs integer division (5/2 = 2).
                                                    // The integer result (2) is then implicitly converted to float (2.0).
    float result2 = (float)a_div / b_div;           // `(float)a_div` explicitly converts `a_div` to float (5.0f).
                                                    // Then `5.0f / 2` performs floating-point division (5.0f / 2.0f = 2.5).
    float result3 = a_div / (float)b_div;           // Same as result2, forcing floating-point division.
    printf("Integer division then float: %f\n", result1); // 2.000000
    printf("Float division (explicit cast): %f\n", result2); // 2.500000
    printf("Float division (explicit cast on denom): %f\n", result3); // 2.500000


    // Character to ASCII value
    char char_val = 'A';
    int ascii = (int)char_val;                      // 'A' (char) explicitly converted to 65 (int).
    printf("ASCII of %c: %d\n", char_val, ascii); // ASCII of A: 65

    // Pointer casting (crucial for dynamic memory allocation and generic functions)
    // `void*` is a generic pointer that can point to any data type.
    int num_ptr = 42;
    void* generic_ptr = &num_ptr; // `int*` implicitly converts to `void*`
    // printf("Value: %d\n", *generic_ptr); // ERROR: Cannot dereference a void* directly (compiler doesn't know its size)

    // To use a void* pointer, you must explicitly cast it back to a specific type.
    int* intPtr = (int*)generic_ptr;
    printf("Value through casted pointer: %d\n", *intPtr); // Value: 42

    char char_arr[] = "Hello";
    void* char_generic_ptr = char_arr; // Points to the first character of the string
    printf("Character at generic_ptr (after cast): %c\n", *((char*)char_generic_ptr)); // H

    return 0;
}
```
**Explanation:**
*   **Implicit Casting (Coercion):** Done automatically by the compiler to ensure type compatibility in expressions or assignments. It generally promotes "smaller" types to "larger" types to avoid data loss (e.g., `int` to `float`). However, `int` to `float` can sometimes lose precision for very large integers.
*   **Explicit Casting:** Done manually by the programmer using the `(type)` operator. This is necessary when you want to force a conversion that might involve data loss (e.g., `float` to `int` truncates the decimal part) or to specify how an arithmetic operation should behave (e.g., forcing floating-point division).
*   **Pointer Casting:** Especially important with `void*` pointers, which are "generic" pointers that can hold the address of any data type. You must explicitly cast a `void*` to a specific data pointer type (`int*`, `char*`, etc.) before dereferencing it, as the compiler needs to know the size of the data it's pointing to.

---

# Operators

## Arithmetic Operators

```c
#include <stdio.h>

int main() {
    int a = 10, b = 3;

    printf("Addition (a + b): %d\n", a + b);        // 13
    printf("Subtraction (a - b): %d\n", a - b);     // 7
    printf("Multiplication (a * b): %d\n", a * b);  // 30
    printf("Division (a / b): %d\n", a / b);        // 3 (integer division: 10 / 3 = 3)
    printf("Modulus (a %% b): %d\n", a % b);         // 1 (remainder of 10 / 3)

    // Integer vs Float division (revisited)
    float c = (float)a / b;
    printf("Float division ((float)a / b): %.2f\n", c);    // 3.33

    // Increment/Decrement Operators: Affect the variable's value by 1.
    // Pre-increment/decrement: Modify, then use the value.
    // Post-increment/decrement: Use the value, then modify.
    int x = 5;
    printf("x is 5.\n");
    printf("x++ (post-increment): %d\n", x++);  // Prints 5, then x becomes 6
    printf("Current x: %d\n", x);               // Prints 6
    printf("++x (pre-increment): %d\n", ++x);   // x becomes 7, then prints 7
    printf("Current x: %d\n", x);               // Prints 7

    int y = 5;
    printf("y is 5.\n");
    printf("y-- (post-decrement): %d\n", y--);  // Prints 5, then y becomes 4
    printf("Current y: %d\n", y);               // Prints 4
    printf("--y (pre-decrement): %d\n", --y);   // y becomes 3, then prints 3
    printf("Current y: %d\n", y);               // Prints 3

    return 0;
}
```
**Explanation:**
*   **`/` (Division):** For integer operands, `a / b` performs integer division (truncates any fractional part). For float/double operands (or if one operand is cast), it performs floating-point division.
*   **`%` (Modulus):** Returns the remainder of an integer division. Can only be used with integer operands.
*   **`++` and `--`:** These unary operators increment or decrement a variable by 1. The position (prefix or postfix) matters when they are used within an expression, as it determines whether the variable's value is used *before* or *after* the modification.

## Relational Operators

```c
#include <stdio.h>

int main() {
    int a = 10, b = 20;

    // Relational operators return 0 for false and 1 for true in C.
    printf("a == b (10 == 20): %d\n", a == b);  // 0 (false)
    printf("a != b (10 != 20): %d\n", a != b);  // 1 (true)
    printf("a > b (10 > 20): %d\n", a > b);    // 0 (false)
    printf("a < b (10 < 20): %d\n", a < b);    // 1 (true)
    printf("a >= b (10 >= 20): %d\n", a >= b);  // 0 (false)
    printf("a <= b (10 <= 20): %d\n", a <= b);  // 1 (true)

    return 0;
}
```
**Explanation:** These operators compare two values. In C, `true` is represented by any non-zero integer, and `false` is represented by `0`. Relational operations typically yield `1` for true and `0` for false.

## Logical Operators

```c
#include <stdio.h>

int main() {
    int a = 1, b = 0;  // In C, non-zero is true, 0 is false.

    // && (Logical AND): Returns 1 if both operands are non-zero, else 0.
    printf("a && b (1 && 0): %d\n", a && b);  // 0

    // || (Logical OR): Returns 1 if at least one operand is non-zero, else 0.
    printf("a || b (1 || 0): %d\n", a || b);  // 1

    // ! (Logical NOT): Returns 1 if the operand is 0, else 0.
    printf("!a (!1): %d\n", !a);          // 0
    printf("!b (!0): %d\n", !b);          // 1

    // Short-circuit evaluation:
    // In `A && B`, if A is false (0), B is not evaluated.
    // In `A || B`, if A is true (non-zero), B is not evaluated.
    int x = 5, y = 0;
    // This condition `y != 0 && x / y > 1` would crash if `y != 0` wasn't checked first.
    // Due to short-circuiting, `x / y` is never evaluated because `y != 0` is false.
    if (y != 0 && x / y > 1) {
        printf("This won't print as y is 0.\n");
    } else {
        printf("Short-circuiting prevented division by zero.\n");
    }

    return 0;
}
```
**Explanation:** Logical operators combine or negate boolean (true/false) conditions. C uses `0` for false and any non-zero value for true.
*   **Short-circuit Evaluation:** A critical optimization where the second operand of `&&` or `||` is not evaluated if the result can be determined solely from the first operand. This is often used to prevent runtime errors (like division by zero) or to optimize performance.

## Bitwise Operators

```c
#include <stdio.h>

int main() {
    // These operators work on the individual bits of integer operands.
    // Useful for low-level programming, optimizations, and specific algorithms.

    unsigned int a = 60;  // Binary: 0011 1100
    unsigned int b = 13;  // Binary: 0000 1101

    // & (Bitwise AND): Sets bit if both corresponding bits are 1.
    printf("a & b: %u (0000 1100 = 12)\n", a & b);   // 12

    // | (Bitwise OR): Sets bit if at least one corresponding bit is 1.
    printf("a | b: %u (0011 1101 = 61)\n", a | b);   // 61

    // ^ (Bitwise XOR): Sets bit if corresponding bits are different.
    printf("a ^ b: %u (0011 0001 = 49)\n", a ^ b);   // 49

    // ~ (Bitwise NOT): Inverts all bits. Unsigned values behave as expected.
    // For signed values, it's 2's complement negation - 1 (e.g., ~5 is -6).
    // Using unsigned here for clearer bit inversion example.
    printf("~a (bitwise NOT of 60): %u (depends on int size, usually large number)\n", ~a); // Example: if 32-bit int, 11111111111111111111111111000011 = 4294967235

    // << (Left Shift): Shifts bits to the left, fills with zeros on the right.
    // Equivalent to multiplying by 2 for each shift (if no overflow).
    printf("a << 2 (60 << 2): %u (1111 0000 = 240)\n", a << 2); // 240

    // >> (Right Shift): Shifts bits to the right.
    // For unsigned: Fills with zeros on the left (logical shift).
    // For signed: Fills with sign bit (arithmetic shift) or zeros (logical shift) - implementation defined.
    printf("a >> 2 (60 >> 2): %u (0000 1111 = 15)\n", a >> 2); // 15

    // Practical use: Checking if a number is even/odd quickly
    int num = 7;
    if (num & 1) { // If the least significant bit is 1, it's odd.
        printf("%d is odd.\n", num);
    } else {
        printf("%d is even.\n", num);
    }

    return 0;
}
```
**Explanation:** These operators manipulate data at the bit level.
*   **`&`, `|`, `^`:** Perform bitwise AND, OR, and XOR operations respectively on corresponding bits of two operands.
*   **`~` (Bitwise NOT):** Inverts all the bits of its operand. For unsigned integers, this behaves as expected. For signed integers, it's equivalent to `-(n+1)` due to two's complement representation.
*   **`<<` (Left Shift):** Shifts bits to the left. `n << k` is generally equivalent to `n * (2^k)`. Overflows can occur if bits are shifted out of the most significant position.
*   **`>>` (Right Shift):** Shifts bits to the right. `n >> k` is generally equivalent to `n / (2^k)`. Behavior for signed integers (whether it fills with sign bit or zero) is implementation-defined for negative numbers, but usually arithmetic shift (fills with sign bit). For unsigned integers, it always fills with zeros (logical shift).

## Assignment Operators

```c
#include <stdio.h>

int main() {
    int a = 10;
    printf("Initial a: %d\n", a);

    a += 5;   // Equivalent to: a = a + 5;  (a is now 15)
    printf("a += 5: %d\n", a);

    a -= 3;   // Equivalent to: a = a - 3;  (a is now 12)
    printf("a -= 3: %d\n", a);

    a *= 2;   // Equivalent to: a = a * 2;  (a is now 24)
    printf("a *= 2: %d\n", a);

    a /= 4;   // Equivalent to: a = a / 4;  (a is now 6)
    printf("a /= 4: %d\n", a);

    a %= 4;   // Equivalent to: a = a % 4;  (a is now 2)
    printf("a %%= 4: %d\n", a);

    // Bitwise compound assignment operators also exist:
    // &=, |=, ^=, <<=, >>=
    int b = 10; // Binary: 1010
    b &= 3;     // b = b & 3; (1010 & 0011 = 0010 = 2)
    printf("b &= 3: %d\n", b); // b is now 2

    b |= 4;     // b = b | 4; (0010 | 0100 = 0110 = 6)
    printf("b |= 4: %d\n", b); // b is now 6

    b <<= 1;    // b = b << 1; (0110 << 1 = 1100 = 12)
    printf("b <<= 1: %d\n", b); // b is now 12

    return 0;
}
```
**Explanation:** These are shorthand operators that perform an operation and then assign the result back to the left operand (e.g., `a += 5` is equivalent to `a = a + 5`). They exist for arithmetic, bitwise, and logical operators.

## Conditional (Ternary) Operator

```c
#include <stdio.h>

int main() {
    int a = 10, b = 20;

    // Syntax: condition ? value_if_true : value_if_false
    // If 'condition' is true (non-zero), the expression evaluates to 'value_if_true'.
    // Otherwise, it evaluates to 'value_if_false'.
    int max = (a > b) ? a : b;
    printf("Max: %d\n", max);  // 20

    // Can be chained, but use sparingly for readability.
    int x = 0;
    char* result = (x > 0) ? "positive" :
                   (x < 0) ? "negative" : "zero";
    printf("%d is %s\n", x, result); // 0 is zero

    return 0;
}
```
**Explanation:** The only ternary (three-operand) operator in C. It's a concise way to write simple `if-else` expressions, returning one of two values based on a condition.

## Operator Precedence (Highest to Lowest)

```c
/*
 * OPERATOR PRECEDENCE TABLE (Simplified common operators)
 *
 * Priority  Operators              Associativity   Description
 * ════════  ═══════════════════════════════════════════════
 * 1         ()  []  ->  .          Left-to-right   Postfix (function call, array subscript, member access)
 * 2         ++  --  !  ~  +  -  *  Right-to-left   Unary (pre-increment/decrement, logical NOT, bitwise NOT, unary plus/minus, dereference)
 *           (type) sizeof                           Cast, Sizeof
 * 3         *  /  %                Left-to-right   Multiplicative
 * 4         +  -                   Left-to-right   Additive
 * 5         <<  >>                 Left-to-right   Bitwise shift
 * 6         <  <=  >  >=           Left-to-right   Relational
 * 7         ==  !=                 Left-to-right   Equality
 * 8         &                      Left-to-right   Bitwise AND
 * 9         ^                      Left-to-right   Bitwise XOR
 * 10        |                      Left-to-right   Bitwise OR
 * 11        &&                     Left-to-right   Logical AND
 * 12        ||                     Left-to-right   Logical OR
 * 13        ?:                     Right-to-left   Ternary
 * 14        =  +=  -=  *= etc.     Right-to-left   Assignment
 * 15        ,                      Left-to-right   Comma (evaluates expressions left-to-right, returns rightmost value)
 */

int main() {
    int a = 10, b = 5, c = 2;

    // Example: 10 + 5 * 2
    // Multiplication (*) has higher precedence than Addition (+).
    // So, 5 * 2 is evaluated first (10), then 10 + 10 = 20.
    int result = a + b * c;
    printf("a + b * c: %d\n", result);  // 20

    // Use parentheses to override precedence or for clarity.
    // (a + b) is evaluated first (15), then 15 * 2 = 30.
    int result2 = (a + b) * c;
    printf("(a + b) * c: %d\n", result2);  // 30

    // Example of Associativity (Right-to-left for assignment)
    int x, y, z;
    x = y = z = 5; // Evaluates as x = (y = (z = 5));
    printf("x=%d, y=%d, z=%d\n", x, y, z); // x=5, y=5, z=5

    return 0;
}
```
**Explanation:**
*   **Precedence:** Determines which operator is evaluated first in an expression (e.g., `*` before `+`).
*   **Associativity:** Determines the order of evaluation when operators of the same precedence appear in an expression (e.g., `a + b + c` is left-to-right, `a = b = c` is right-to-left).
*   **Parentheses `()`:** Always override precedence and associativity, forcing a specific order of evaluation. Use them liberally to ensure correctness and improve code readability, even if the default precedence would produce the same result.

---

# Input/Output

## `printf()` - Formatted Output

```c
#include <stdio.h>

int main() {
    // ═══════════════════════════════════════════════════
    // BASIC FORMAT SPECIFIERS
    // `printf` uses format specifiers to interpret and display variables.
    // ═══════════════════════════════════════════════════

    int i = 42;
    unsigned int u = 42;
    float f = 3.14159f;
    double d = 3.14159265359;
    char c = 'A';
    char str[] = "Hello";
    void* ptr = &i; // A generic pointer, address of 'i'

    printf("Integer (d): %d\n", i);             // Decimal integer
    printf("Unsigned (u): %u\n", u);            // Unsigned decimal integer
    printf("Hexadecimal (x): %x (lowercase)\n", i); // Hexadecimal integer (lowercase letters)
    printf("Hexadecimal (X): %X (uppercase)\n", i); // Hexadecimal integer (uppercase letters)
    printf("Octal (o): %o\n", i);               // Octal integer
    printf("Float (f): %f\n", f);               // Decimal floating point
    printf("Double (lf): %lf\n", d);             // Double (historically 'lf' for scanf, 'f' for printf, but 'f' is fine for double too)
    printf("Scientific (e): %e\n", d);           // Scientific notation (lowercase 'e')
    printf("Character (c): %c\n", c);           // Single character
    printf("String (s): %s\n", str);            // Null-terminated string
    printf("Pointer (p): %p\n", ptr);           // Pointer address (implementation-defined format)
    printf("Percent sign (%%): %%\n");            // To print a literal '%'

    // ═══════════════════════════════════════════════════
    // WIDTH, PRECISION, AND FLAGS
    // Control how the output is formatted (padding, decimal places, alignment).
    // Syntax: %[flags][width][.precision][length]type
    // ═══════════════════════════════════════════════════

    printf("\n--- Width, Precision, Flags ---\n");
    printf("Width 5 for int: '%5d'\n", 42);         // "   42" (right-aligned, padded with spaces)
    printf("Left-align width 5: '%-5d'\n", 42);     // "42   " (left-aligned)
    printf("Zero-padded width 5: '%05d'\n", 42);    // "00042" (padded with zeros)

    printf("Precision .2 for float: '%.2f'\n", 3.14159); // "3.14" (2 decimal places)
    printf("Width 10, precision 2: '%10.2f'\n", 3.14);  // "      3.14" (width 10, precision 2)
    printf("Precision for string: '%.3s'\n", "HelloWorld"); // "Hel" (print only first 3 characters)

    // ═══════════════════════════════════════════════════
    // LENGTH MODIFIERS (for specific integer types)
    // ═══════════════════════════════════════════════════
    long l_val = 1234567890L;
    long long ll_val = 1234567890123456789LL;
    size_t s_val = sizeof(int); // `sizeof` returns `size_t`

    printf("Long (ld): %ld\n", l_val);
    printf("Long long (lld): %lld\n", ll_val);
    printf("Size_t (zu): %zu bytes\n", s_val); // `size_t` is an unsigned integer type

    return 0;
}
```
**Explanation:**
*   **Format Specifiers:** The heart of `printf`. They tell `printf` how to interpret the corresponding argument's type and how to format its output. Mismatched specifiers and argument types lead to *undefined behavior*.
*   **Width:** Specifies the minimum field width for the output. If the value is shorter, it's padded (default: spaces, right-aligned).
*   **Precision:**
    *   For floating-point numbers: Number of digits after the decimal point.
    *   For strings: Maximum number of characters to print.
    *   For integers: Minimum number of digits to print (padded with leading zeros).
*   **Flags:** Control alignment (`-`), zero-padding (`0`), sign display (`+`, ` `), etc.
*   **Length Modifiers:** Used to specify the size of integer arguments (e.g., `l` for `long`, `ll` for `long long`, `z` for `size_t`). The `lf` modifier is for `double` with `scanf`, but for `printf`, `f` works for both `float` and `double` because `float` arguments are promoted to `double` in variadic functions.

## `scanf()` - Formatted Input

```c
#include <stdio.h>

int main() {
    int age;
    float height;
    char firstName[50]; // Character array for string input
    char initial;
    int num1, num2;

    // ═══════════════════════════════════════════════════
    // BASIC INPUT - Using the address-of operator `&`
    // `scanf` requires the ADDRESS of the variable to store the input.
    // For arrays (like strings), the array name itself is an address, so `&` is not used.
    // ═══════════════════════════════════════════════════

    printf("Enter age (integer): ");
    scanf("%d", &age);  // `&age` provides the memory address of 'age'
    printf("Age entered: %d\n", age);

    printf("Enter height (float, e.g., 1.75): ");
    scanf("%f", &height); // `&height`
    printf("Height entered: %.2f\n", height);

    printf("Enter your first name (no spaces): ");
    scanf("%s", firstName); // `firstName` (array name) decays to a pointer to its first element
    printf("First name entered: %s\n", firstName);

    // ═══════════════════════════════════════════════════
    // Multiple inputs in one `scanf` call
    // ═══════════════════════════════════════════════════

    printf("Enter two integers (e.g., 10 20): ");
    scanf("%d %d", &num1, &num2);
    printf("You entered: %d and %d\n", num1, num2);

    // ═══════════════════════════════════════════════════
    // Issues with `scanf` and character input (newline in buffer)
    // `scanf("%c", ...)` reads the next available character, which might be a leftover newline.
    // The space before `%c` (` " %c" `) tells scanf to skip any whitespace characters
    // (including spaces, tabs, and newlines) before reading the character.
    // ═══════════════════════════════════════════════════

    printf("Enter an initial (character): ");
    scanf(" %c", &initial); // Note the space before %c!
    printf("Initial entered: %c\n", initial);

    // ═══════════════════════════════════════════════════
    // Input String Safely (limiting length)
    // `%49s` reads at most 49 characters, ensuring space for the null terminator `\0`.
    // This prevents buffer overflows.
    // ═══════════════════════════════════════════════════
    char safeName[50];
    printf("Enter a name (max 49 chars): ");
    scanf("%49s", safeName);
    printf("Safe name: %s\n", safeName);


    // ═══════════════════════════════════════════════════
    // Reading an entire line with spaces using `scanf` (less common/idiomatic than `fgets`)
    // ` %[^\n]` reads characters until a newline is encountered, then `*c` discards it.
    // Make sure to clear the buffer before using this again after other `scanf` calls.
    // ═══════════════════════════════════════════════════
    char line[100];
    printf("Enter a line of text (with spaces): ");
    // Clear any leftover newline from previous scanf.
    // while (getchar() != '\n' && getchar() != EOF); // Consume until newline or EOF
    scanf(" %[^\n]%*c", line); // Reads up to newline, then discards the newline
    printf("Line read: \"%s\"\n", line);


    return 0;
}
```
**Explanation:**
*   **Address-of Operator (`&`):** `scanf` needs to know *where* in memory to store the input value. For simple variables (`int`, `float`, `char`, etc.), you must provide their memory address using `&`. Array names (like `firstName`) inherently represent the address of their first element, so `&` is not used for them.
*   **Format Specifiers:** Similar to `printf`, but for input. `lf` is explicitly needed for `double` in `scanf` (whereas `f` works for `double` in `printf`).
*   **Whitespace Handling:** `scanf` generally skips leading whitespace for numeric and string inputs (`%d`, `%f`, `%s`). However, `%c` *does not* skip leading whitespace, which can cause issues if a newline (`\n`) character is left in the input buffer from a previous `scanf` or `printf`. The space before `%c` (`" %c"`) resolves this.
*   **Buffer Overflows:** `scanf("%s", ...)` is inherently unsafe as it doesn't know the size of the buffer and can write past its end if the input string is too long. To prevent this, limit the number of characters to read (e.g., `"%49s"`).
*   **Reading Lines:** While `scanf(" %[^\n]%*c", ...)` can read lines with spaces, `fgets` is generally preferred for safety and ease of use when reading entire lines.

## Other I/O Functions (`getchar`, `putchar`, `gets`, `fgets`, `puts`)

```c
#include <stdio.h>
#include <string.h> // For strcspn

int main() {
    char ch_in, ch_out;
    char str_buffer[100];

    // ═══════════════════════════════════════════════════
    // CHARACTER I/O
    // ═══════════════════════════════════════════════════

    printf("\n--- Character I/O ---\n");
    printf("Enter a character: ");
    ch_in = getchar();  // Reads a single character from stdin
    printf("You entered: ");
    putchar(ch_in);     // Prints a single character to stdout
    putchar('\n');      // Prints a newline character

    // Important: `getchar()` often leaves the newline character in the buffer.
    // Clear the input buffer to prevent issues with subsequent inputs.
    while ((ch_out = getchar()) != '\n' && ch_out != EOF);

    // ═══════════════════════════════════════════════════
    // STRING I/O
    // ═══════════════════════════════════════════════════

    printf("\n--- String I/O ---\n");

    // --- `gets()` ---
    // DEPRECATED and UNSAFE! Never use in modern C code.
    // It reads an entire line but performs no bounds checking, making it highly susceptible
    // to buffer overflows.
    // char unsafe_str[10];
    // printf("Enter an UNSAFE string: ");
    // gets(unsafe_str); // AVOID! This can cause security vulnerabilities.

    // --- `fgets()` ---
    // The SAFE alternative to `gets()`.
    // Syntax: `char *fgets(char *str, int size, FILE *stream);`
    // `str`: buffer to store the string.
    // `size`: maximum number of characters to read (including null terminator).
    // `stream`: input stream (usually `stdin` for console input).
    // Reads up to `size-1` characters or until newline/EOF. It *includes* the newline if read.
    printf("Enter a safe string (max 99 chars, will include newline): ");
    if (fgets(str_buffer, sizeof(str_buffer), stdin) != NULL) {
        printf("fgets read: \"%s\"", str_buffer); // Note: It prints the newline from input
    }

    // `fgets` often captures the newline character from the input.
    // You might want to remove it for cleaner string processing.
    // `strcspn` finds the index of the first occurrence of any character from a set.
    str_buffer[strcspn(str_buffer, "\n")] = '\0'; // Replace newline with null terminator
    printf("After removing newline: \"%s\"\n", str_buffer);

    // --- `puts()` ---
    // Prints a null-terminated string to stdout, followed by a newline character.
    // It automatically adds a newline, so you don't need `\n` in the string itself.
    printf("Using puts(): ");
    puts(str_buffer); // Prints content of str_buffer and adds a newline

    // `fgetc`, `fputc`, `fscanf`, `fprintf` are file-specific versions
    // `fgetc` reads char from FILE stream
    // `fputc` writes char to FILE stream
    // `fscanf` reads formatted input from FILE stream
    // `fprintf` writes formatted output to FILE stream

    return 0;
}
```
**Explanation:**
*   **`getchar()` / `putchar()`:** Used for single-character input/output. `getchar()` reads the next character from the standard input buffer (including newlines). `putchar()` writes a single character to standard output.
*   **`gets()`:** **Extremely dangerous and deprecated.** It reads an entire line from standard input until a newline, but it *doesn't* take a buffer size argument. This makes it impossible to prevent buffer overflows if the user enters more characters than the buffer can hold, leading to security vulnerabilities. **NEVER USE `gets()`**.
*   **`fgets()`:** The **safe replacement** for `gets()`. It takes a maximum size argument, preventing buffer overflows. A key difference is that `fgets()` *includes* the newline character (`\n`) if it's read from the input, which often needs to be explicitly removed by the programmer (e.g., using `strcspn`).
*   **`puts()`:** A simple function to print a null-terminated string to standard output. It automatically appends a newline character to the output.

---

# Control Flow

## `if-else` Statements

```c
#include <stdio.h>

int main() {
    int age;
    printf("Enter age: ");
    scanf("%d", &age);

    // ═══════════════════════════════════════════════════
    // SIMPLE IF STATEMENT
    // Executes a block of code if the condition is true (non-zero).
    // ═══════════════════════════════════════════════════

    if (age >= 18) {
        printf("Condition: age >= 18 is true.\n");
        printf("You are an adult.\n");
    }

    // ═══════════════════════════════════════════════════
    // IF-ELSE STATEMENT
    // Executes one block if condition is true, another if false.
    // ═══════════════════════════════════════════════════

    if (age >= 18) {
        printf("Adult\n");
    } else {
        printf("Minor\n");
    }

    // ═══════════════════════════════════════════════════
    // IF-ELSE IF-ELSE LADDER
    // Checks multiple conditions sequentially. Only the first true block executes.
    // ═══════════════════════════════════════════════════

    printf("Age group: ");
    if (age < 13) {
        printf("Child\n");
    } else if (age < 20) { // Condition: age is 13-19
        printf("Teenager\n");
    } else if (age < 60) { // Condition: age is 20-59
        printf("Adult\n");
    } else {              // Condition: age is 60 or older
        printf("Senior\n");
    }

    // ═══════════════════════════════════════════════════
    // NESTED IF STATEMENTS
    // An `if` (or `else if`) statement inside another.
    // ═══════════════════════════════════════════════════

    int marks;
    printf("Enter marks (0-100): ");
    scanf("%d", &marks);

    if (marks >= 0 && marks <= 100) { // Outer check for valid marks
        if (marks >= 90) {
            printf("Grade A+\n");
        } else if (marks >= 80) {
            printf("Grade A\n");
        } else if (marks >= 70) {
            printf("Grade B\n");
        } else if (marks >= 60) {
            printf("Grade C\n");
        } else {
            printf("Fail\n");
        }
    } else {
        printf("Invalid marks entered.\n");
    }

    return 0;
}
```
**Explanation:**
*   **`if`:** Executes a block of code if its condition evaluates to true (any non-zero value).
*   **`else`:** Provides an alternative block of code to execute if the `if` condition is false.
*   **`else if`:** Allows checking multiple conditions in sequence. Once a condition is true, its block executes, and the rest of the `else if` / `else` ladder is skipped.
*   **Nesting:** `if-else` statements can be nested to handle more complex decision logic.

## `switch` Statement

```c
#include <stdio.h>

int main() {
    int day;
    printf("Enter day number (1-7): ");
    scanf("%d", &day);

    // ═══════════════════════════════════════════════════
    // BASIC SWITCH STATEMENT
    // Evaluates an expression (must be an integer type) and compares its value
    // against `case` labels.
    // ═══════════════════════════════════════════════════

    printf("Using basic switch: ");
    switch (day) {
        case 1:
            printf("Monday\n");
            break; // Exits the switch block
        case 2:
            printf("Tuesday\n");
            break;
        case 3:
            printf("Wednesday\n");
            break;
        case 4:
            printf("Thursday\n");
            break;
        case 5:
            printf("Friday\n");
            break;
        case 6:
            printf("Saturday\n");
            break;
        case 7:
            printf("Sunday\n");
            break;
        default: // Executed if no case matches
            printf("Invalid day number\n");
    }

    // ═══════════════════════════════════════════════════
    // FALL-THROUGH BEHAVIOR (when `break` is omitted)
    // If `break` is missing, execution "falls through" to the next `case` block.
    // This can be used intentionally to group cases.
    // ═══════════════════════════════════════════════════

    printf("Using switch with fall-through: ");
    switch (day) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            printf("Weekday\n"); // If day is 1, it falls through to 2, 3, 4, then executes here.
            break;
        case 6:
        case 7:
            printf("Weekend\n");
            break;
        default:
            printf("Invalid\n");
    }

    // ═══════════════════════════════════════════════════
    // SWITCH WITH CHARACTER
    // Character literals are essentially integer values (their ASCII codes).
    // ═══════════════════════════════════════════════════

    char grade;
    // Clear buffer after previous scanf
    while (getchar() != '\n');
    printf("Enter grade (A, B, C, D, F): ");
    scanf(" %c", &grade); // Space before %c to consume leftover newline

    printf("Grade status: ");
    switch (grade) {
        case 'A':
            printf("Excellent\n");
            break;
        case 'B':
            printf("Good\n");
            break;
        case 'C':
            printf("Average\n");
            break;
        case 'D':
            printf("Poor\n");
            break;
        case 'F':
            printf("Fail\n");
            break;
        default:
            printf("Invalid grade\n");
    }

    return 0;
}
```
**Explanation:**
*   **`switch`:** A multi-way branching statement that allows choosing one of many code blocks to execute based on the value of an integer expression.
*   **`case`:** Labels a block of code to be executed if the switch expression matches its constant value. `case` labels must be integral constant expressions (integers, chars, enums).
*   **`break`:** Essential for exiting the `switch` statement after a `case` block is executed. Without `break`, execution "falls through" to the next `case` label.
*   **`default`:** An optional label that specifies the code to be executed if none of the `case` labels match the switch expression.

## Loops

### `for` Loop

```c
#include <stdio.h>

int main() {
    // ═══════════════════════════════════════════════════
    // BASIC FOR LOOP
    // Syntax: `for (initialization; condition; update)`
    // 1. Initialization: Executed once at the beginning.
    // 2. Condition: Checked before each iteration. If false, loop terminates.
    // 3. Update: Executed after each iteration.
    // ═══════════════════════════════════════════════════

    printf("Basic for loop (0-4): ");
    for (int i = 0; i < 5; i++) { // i is block-scoped (C99)
        printf("%d ", i);  // 0 1 2 3 4
    }
    printf("\n");

    // ═══════════════════════════════════════════════════
    // REVERSE LOOP
    // ═══════════════════════════════════════════════════

    printf("Reverse loop (5-1): ");
    for (int i = 5; i > 0; i--) {
        printf("%d ", i);  // 5 4 3 2 1
    }
    printf("\n");

    // ═══════════════════════════════════════════════════
    // STEP BY 2
    // ═══════════════════════════════════════════════════

    printf("Loop step by 2 (0-8): ");
    for (int i = 0; i < 10; i += 2) {
        printf("%d ", i);  // 0 2 4 6 8
    }
    printf("\n");

    // ═══════════════════════════════════════════════════
    // MULTIPLE VARIABLES in loop control (using comma operator)
    // ═══════════════════════════════════════════════════

    printf("Loop with multiple variables:\n");
    for (int i = 0, j = 10; i < j; i++, j--) {
        printf("  i=%d j=%d\n", i, j);
    }

    // ═══════════════════════════════════════════════════
    // NESTED LOOPS
    // One loop inside another. Inner loop completes all its iterations for each
    // iteration of the outer loop.
    // ═══════════════════════════════════════════════════

    printf("Nested loops (3x3 grid):\n");
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            printf("(%d,%d) ", i, j);
        }
        printf("\n");
    }

    // ═══════════════════════════════════════════════════
    // INFINITE LOOP (requires `break` to exit)
    // Condition is always true (or omitted).
    // ═══════════════════════════════════════════════════

    printf("\nInfinite loop example (enter 0 to exit):\n");
    for (;;) { // Or `for(;;)`
        printf("Enter a number: ");
        int n;
        scanf("%d", &n);
        if (n == 0) {
            printf("Exiting infinite loop.\n");
            break; // Exits the loop
        }
    }

    return 0;
}
```
**Explanation:**
*   The `for` loop is ideal for situations where you know the number of iterations in advance or have a clear initialization, condition, and update sequence.
*   **Initialization:** Executed once at the beginning of the loop. Variables declared here (`int i = 0;`) have scope only within the loop (from C99 onwards).
*   **Condition:** Evaluated before *each* iteration. If true (non-zero), the loop body executes. If false (zero), the loop terminates.
*   **Update:** Executed *after* each iteration of the loop body.
*   Any of the three parts (initialization, condition, update) can be omitted, but the semicolons are required. Omitting the condition makes it an infinite loop.

### `while` Loop

```c
#include <stdio.h>

int main() {
    // ═══════════════════════════════════════════════════
    // BASIC WHILE LOOP
    // Syntax: `while (condition)`
    // The condition is checked *before* each iteration.
    // If the condition is initially false, the loop body never executes.
    // ═══════════════════════════════════════════════════

    printf("Basic while loop (0-4): ");
    int i = 0; // Initialize loop control variable *before* the loop
    while (i < 5) {
        printf("%d ", i);
        i++; // Update loop control variable *inside* the loop
    }
    printf("\n");

    // ═══════════════════════════════════════════════════
    // INPUT VALIDATION (Loop continues until valid input)
    // ═══════════════════════════════════════════════════

    int age;
    printf("\nEnter age (1-100): ");
    scanf("%d", &age);

    while (age < 1 || age > 100) { // Keep looping while age is invalid
        printf("Invalid age! Please enter a value between 1 and 100: ");
        scanf("%d", &age);
    }
    printf("Valid age entered: %d\n", age);

    // ═══════════════════════════════════════════════════
    // SENTINEL-CONTROLLED LOOP
    // Loop continues until a specific "sentinel" value is entered.
    // ═══════════════════════════════════════════════════

    int num_sum;
    int sum = 0;

    printf("\nEnter numbers to sum (enter 0 to stop):\n");
    // "Priming read" - read the first value before the loop.
    // This allows the condition to be checked correctly for the first time.
    scanf("%d", &num_sum);

    while (num_sum != 0) { // Loop as long as the number is not 0
        sum += num_sum;
        scanf("%d", &num_sum); // Read next value at end of loop
    }

    printf("Sum of entered numbers: %d\n", sum);

    return 0;
}
```
**Explanation:**
*   The `while` loop is suitable when the number of iterations is unknown and depends on a condition being met.
*   **Condition:** Evaluated *before* each iteration. If true (non-zero), the loop body executes. If false (zero), the loop terminates.
*   It's crucial to initialize any variables used in the condition *before* the loop and to ensure the condition *changes* inside the loop to avoid an infinite loop.

### `do-while` Loop

```c
#include <stdio.h>

int main() {
    // ═══════════════════════════════════════════════════
    // BASIC DO-WHILE LOOP
    // Syntax: `do { ... } while (condition);`
    // The loop body executes *at least once*, then the condition is checked.
    // ═══════════════════════════════════════════════════

    printf("Basic do-while loop (0-4): ");
    int i = 0;
    do {
        printf("%d ", i);
        i++;
    } while (i < 5); // Condition checked *after* first iteration
    printf("\n");

    // Example where do-while executes once even if condition is false initially:
    printf("Do-while with false initial condition: ");
    int j = 10;
    do {
        printf("%d ", j); // This will execute once, printing 10
        j++;
    } while (j < 5); // Condition is immediately false, so loop stops after first iteration
    printf("\n");


    // ═══════════════════════════════════════════════════
    // MENU-DRIVEN PROGRAM (Common use case for do-while)
    // Ensures the menu is displayed at least once.
    // ═══════════════════════════════════════════════════

    int choice;

    do {
        printf("\n=== MENU ===\n");
        printf("1. Add\n");
        printf("2. Subtract\n");
        printf("3. Multiply\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: printf("Addition selected\n"); break;
            case 2: printf("Subtraction selected\n"); break;
            case 3: printf("Multiplication selected\n"); break;
            case 4: printf("Exiting...\n"); break;
            default: printf("Invalid choice, please try again.\n");
        }
    } while (choice != 4); // Continue looping until the user chooses to exit

    return 0;
}
```
**Explanation:**
*   The `do-while` loop guarantees that the loop body executes at least once, even if the condition is initially false.
*   **Execution Flow:** The loop body is executed, *then* the condition is evaluated. If the condition is true (non-zero), the loop continues. If false (zero), the loop terminates.
*   This makes it particularly useful for scenarios like menu-driven programs, where you want to display options and get input at least once before checking if the user wants to continue.

## `break` and `continue` Statements

```c
#include <stdio.h>

int main() {
    // ═══════════════════════════════════════════════════
    // `break` - Terminates the innermost loop or switch statement immediately.
    // Execution resumes at the statement immediately following the loop/switch.
    // ═══════════════════════════════════════════════════

    printf("--- `break` example ---\n");
    printf("Counting up to 10, but stops at 5:\n");
    for (int i = 0; i < 10; i++) {
        if (i == 5) {
            printf("  Breaking loop at i = %d\n", i);
            break;  // Exits the `for` loop entirely
        }
        printf("%d ", i);  // Prints 0 1 2 3 4
    }
    printf("\nLoop finished after break.\n\n");

    // `break` in nested loops only affects the innermost loop
    printf("`break` in nested loops (outer loop continues):\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (j == 1) {
                printf("  Inner loop break (i=%d, j=%d)\n", i, j);
                break; // Breaks only the inner `for` loop
            }
            printf("(%d,%d) ", i, j);
        }
        printf("\n"); // This printf is part of the outer loop
    }
    printf("Nested loops finished.\n\n");


    // ═══════════════════════════════════════════════════
    // `continue` - Skips the remainder of the current iteration of the loop.
    // Execution proceeds to the next iteration (evaluating the loop condition/update).
    // ═══════════════════════════════════════════════════

    printf("--- `continue` example ---\n");
    printf("Printing odd numbers up to 9:\n");
    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) { // If i is even...
            continue;    // ...skip the rest of this iteration and go to the next.
        }
        printf("%d ", i);  // Prints 1 3 5 7 9 (even numbers are skipped)
    }
    printf("\nLoop finished after continue.\n\n");

    return 0;
}
```
**Explanation:**
*   **`break`:** Provides an immediate exit from the innermost `for`, `while`, `do-while` loop, or `switch` statement. Control transfers to the statement immediately following the terminated construct.
*   **`continue`:** Skips the rest of the current iteration of the innermost loop and proceeds to the next iteration. For `for` loops, this means the update expression is evaluated next. For `while`/`do-while` loops, the condition is evaluated next.

## `goto` Statement (Generally Avoid in Modern Code)

```c
#include <stdio.h>

int main() {
    // ═══════════════════════════════════════════════════
    // `goto` - Unconditional jump to a labeled statement within the same function.
    // Labels are identifiers followed by a colon.
    // ═══════════════════════════════════════════════════

    printf("--- `goto` example ---\n");
    int i = 0;

start_loop: // This is a label
    printf("%d ", i);
    i++;

    if (i < 5) {
        goto start_loop; // Jump back to the `start_loop` label
    }
    printf("\n");

    printf("Execution after loop.\n\n");

    // ═══════════════════════════════════════════════════
    // A rare, potentially acceptable use case: Breaking out of deeply nested loops.
    // This avoids using multiple `break` statements or complex flag variables.
    // Even here, consider refactoring into functions.
    // ═══════════════════════════════════════════════════

    printf("--- `goto` for exiting nested loops ---\n");
    int found_value = 0;
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            for (int z = 0; z < 3; z++) {
                printf("(%d,%d,%d) ", x, y, z);
                if (x == 1 && y == 1 && z == 1) {
                    found_value = 1;
                    goto end_nested_loops; // Jumps out of all three loops
                }
            }
        }
    }

end_nested_loops: // Label for `goto`
    if (found_value) {
        printf("\nTarget found and exited nested loops with goto.\n");
    } else {
        printf("\nTarget not found.\n");
    }

    // ═══════════════════════════════════════════════════
    // General Advice: AVOID `goto`.
    // - Makes code harder to read and debug ("spaghetti code").
    // - Obscures program flow.
    // - Can lead to resource leaks if jumps bypass cleanup code.
    // Structured control flow (`if`, `else`, `while`, `for`, `switch`, `break`, `continue`, functions)
    // is almost always preferable.
    // ═══════════════════════════════════════════════════

    return 0;
}
```
**Explanation:**
*   **`goto`:** An unconditional jump statement that transfers control to a specified label within the same function.
*   **Labels:** An identifier followed by a colon (`:`), marking a destination for `goto`.
*   **Why to Avoid:** `goto` statements lead to "spaghetti code" that is notoriously difficult to follow, debug, and maintain. They violate structured programming principles.
*   **Rare Exceptions:** In very specific scenarios, like breaking out of multiple nested loops or implementing error handling/cleanup routines, `goto` might be used by experienced C programmers when other structured approaches become overly cumbersome. However, even these cases often have cleaner solutions (e.g., refactoring into functions, using flags). For SDE interviews, it's best to show proficiency in structured control flow.

---
# Part 2: Advanced C Concepts

# Functions & the Call Stack

## Function Basics

```c
#include <stdio.h>
#include <assert.h>

// ═══════════════════════════════════════════════════════════════════════
// FUNCTION ANATOMY
// A function consists of:
// 1. Return type: The data type of the value returned (void if nothing)
// 2. Function name: Identifier following C naming conventions
// 3. Parameter list: Comma-separated list of parameters (can be empty)
// 4. Function body: The code block executed when function is called
// ═══════════════════════════════════════════════════════════════════════

// Function declaration (prototype) - tells compiler about function signature
int add(int a, int b);  // Parameters: 'a' and 'b' are formal parameters

// Function definition - provides the implementation
int add(int a, int b) {
    return a + b;  // Return statement sends value back to caller
}

// ═══════════════════════════════════════════════════════════════════════
// DIFFERENT FUNCTION TYPES
// ═══════════════════════════════════════════════════════════════════════

// 1. Function with no parameters and no return value
void printHeader(void) {  // 'void' parameter list means no parameters
    printf("════════════════════════════\n");
    printf("    Welcome to C Programming\n");
    printf("════════════════════════════\n");
}

// 2. Function with parameters but no return value
void printSum(int x, int y) {
    printf("Sum of %d and %d is: %d\n", x, y, x + y);
}

// 3. Function with no parameters but with return value
int getRandomNumber(void) {
    static int seed = 5;  // Static variable persists between calls
    seed = (seed * 1103515245 + 12345) % 2147483648;  // Simple LCG
    return seed % 100;  // Return number between 0-99
}

// 4. Function with parameters and return value
float calculateAverage(int arr[], int size) {
    if (size <= 0) return 0.0f;  // Guard clause
    
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return (float)sum / size;  // Cast to float for accurate division
}

// ═══════════════════════════════════════════════════════════════════════
// FUNCTION WITH MULTIPLE RETURN POINTS
// ═══════════════════════════════════════════════════════════════════════

int findMax(int a, int b, int c) {
    // Multiple return statements are allowed
    // Function exits at first return encountered
    if (a >= b && a >= c) return a;
    if (b >= a && b >= c) return b;
    return c;
}

// ═══════════════════════════════════════════════════════════════════════
// INLINE FUNCTIONS (C99)
// Suggests to compiler to expand function body at call site
// Reduces function call overhead for small, frequently called functions
// ═══════════════════════════════════════════════════════════════════════

inline int square(int x) {
    return x * x;
}

// ═══════════════════════════════════════════════════════════════════════
// STATIC FUNCTIONS
// Limits function scope to current translation unit (file)
// Provides encapsulation and prevents naming conflicts
// ═══════════════════════════════════════════════════════════════════════

static int helperFunction(int x) {
    return x * 2;  // Only accessible within this file
}

int main() {
    // Function calls - arguments are actual parameters
    int result = add(5, 3);  // 5 and 3 are actual parameters (arguments)
    printf("add(5, 3) = %d\n", result);
    
    printHeader();
    printSum(10, 20);
    
    printf("Random number: %d\n", getRandomNumber());
    printf("Another random: %d\n", getRandomNumber());
    
    int numbers[] = {10, 20, 30, 40, 50};
    float avg = calculateAverage(numbers, 5);
    printf("Average: %.2f\n", avg);
    
    printf("Max of (15, 27, 9): %d\n", findMax(15, 27, 9));
    printf("Square of 7: %d\n", square(7));
    
    return 0;
}
```

**Key Concepts Explained:**
- **Function Declaration vs Definition:** Declaration tells the compiler about the function's existence and signature. Definition provides the actual implementation.
- **Formal vs Actual Parameters:** Formal parameters are placeholders in function definition. Actual parameters (arguments) are the real values passed during function call.
- **Return Statement:** Immediately exits the function and optionally returns a value to the caller.
- **`void` Keyword:** Used to indicate "no value" - either no parameters or no return value.
- **`inline` Functions:** A hint to the compiler to replace function calls with the function body itself, eliminating call overhead.
- **`static` Functions:** Restrict function visibility to the current source file, providing encapsulation.

## Pass by Value vs Pass by Reference (Simulated)

```c
#include <stdio.h>

// ═══════════════════════════════════════════════════════════════════════
// C ONLY SUPPORTS PASS BY VALUE
// However, we can simulate pass by reference using pointers
// ═══════════════════════════════════════════════════════════════════════

// ─────────────────────────────────────────────────────────────────────
// PASS BY VALUE - A copy of the value is passed
// ─────────────────────────────────────────────────────────────────────

void modifyValue(int x) {
    printf("  Inside modifyValue: x = %d (address: %p)\n", x, (void*)&x);
    x = 100;  // This modifies the LOCAL COPY only
    printf("  Inside modifyValue after modification: x = %d\n", x);
}

// ─────────────────────────────────────────────────────────────────────
// SIMULATED PASS BY REFERENCE - Pass address (pointer)
// The pointer itself is passed by value, but it points to the original
// ─────────────────────────────────────────────────────────────────────

void modifyValueByPointer(int *ptr) {
    printf("  Inside modifyValueByPointer: ptr points to %p\n", (void*)ptr);
    printf("  Value at that address: %d\n", *ptr);
    *ptr = 100;  // Modifies the value at the address ptr points to
    printf("  After modification, value at address: %d\n", *ptr);
}

// ─────────────────────────────────────────────────────────────────────
// SWAPPING VALUES - Classic example showing the difference
// ─────────────────────────────────────────────────────────────────────

// This DOESN'T work - swaps local copies only
void swapWrong(int a, int b) {
    printf("  swapWrong - Before: a=%d, b=%d\n", a, b);
    int temp = a;
    a = b;
    b = temp;
    printf("  swapWrong - After: a=%d, b=%d (only local copies swapped)\n", a, b);
}

// This WORKS - swaps values at the addresses
void swapCorrect(int *a, int *b) {
    printf("  swapCorrect - Values before: *a=%d, *b=%d\n", *a, *b);
    int temp = *a;
    *a = *b;
    *b = temp;
    printf("  swapCorrect - Values after: *a=%d, *b=%d\n", *a, *b);
}

// ─────────────────────────────────────────────────────────────────────
// ARRAYS ARE SPECIAL - Array name decays to pointer
// ─────────────────────────────────────────────────────────────────────

void modifyArray(int arr[], int size) {  // arr[] is actually int*
    printf("  Inside modifyArray: arr points to %p\n", (void*)arr);
    for (int i = 0; i < size; i++) {
        arr[i] *= 2;  // This DOES modify the original array
    }
}

// To demonstrate that array parameter is really a pointer
void arrayIsPointer(int *arr, int size) {  // Equivalent to int arr[]
    printf("  Size of arr parameter: %zu bytes (pointer size)\n", sizeof(arr));
    arr[0] = 999;  // Still modifies original
}

// ─────────────────────────────────────────────────────────────────────
// STRUCT PASS BY VALUE vs POINTER
// ─────────────────────────────────────────────────────────────────────

typedef struct {
    int x;
    int y;
    char name[20];
} Point;

// Pass by value - entire struct is copied (expensive for large structs!)
void movePointByValue(Point p, int dx, int dy) {
    printf("  Size being copied: %zu bytes\n", sizeof(Point));
    p.x += dx;  // Modifies local copy only
    p.y += dy;
    printf("  Inside function: Point at (%d, %d)\n", p.x, p.y);
}

// Pass by pointer - only 8 bytes (on 64-bit) copied, more efficient
void movePointByPointer(Point *p, int dx, int dy) {
    printf("  Size being copied: %zu bytes (pointer)\n", sizeof(Point*));
    p->x += dx;  // Modifies original struct
    p->y += dy;
    printf("  Inside function: Point at (%d, %d)\n", p->x, p->y);
}

// ─────────────────────────────────────────────────────────────────────
// RETURNING MULTIPLE VALUES (using pointers)
// ─────────────────────────────────────────────────────────────────────

// Function that returns multiple values through pointer parameters
int divmod(int dividend, int divisor, int *quotient, int *remainder) {
    if (divisor == 0) {
        return -1;  // Error code
    }
    *quotient = dividend / divisor;
    *remainder = dividend % divisor;
    return 0;  // Success code
}

int main() {
    printf("════════════════════════════════════════════════════════\n");
    printf("PASS BY VALUE VS SIMULATED PASS BY REFERENCE\n");
    printf("════════════════════════════════════════════════════════\n\n");

    // ─── Pass by Value Demo ───
    printf("1. PASS BY VALUE:\n");
    int num = 42;
    printf("Original num: %d (address: %p)\n", num, (void*)&num);
    modifyValue(num);
    printf("After modifyValue: num = %d (unchanged!)\n\n", num);

    // ─── Simulated Pass by Reference Demo ───
    printf("2. SIMULATED PASS BY REFERENCE (using pointers):\n");
    num = 42;
    printf("Original num: %d (address: %p)\n", num, (void*)&num);
    modifyValueByPointer(&num);
    printf("After modifyValueByPointer: num = %d (changed!)\n\n", num);

    // ─── Swap Demo ───
    printf("3. SWAPPING VALUES:\n");
    int x = 10, y = 20;
    printf("Original: x=%d, y=%d\n", x, y);
    
    swapWrong(x, y);
    printf("After swapWrong: x=%d, y=%d (unchanged!)\n", x, y);
    
    swapCorrect(&x, &y);
    printf("After swapCorrect: x=%d, y=%d (swapped!)\n\n", x, y);

    // ─── Array Demo ───
    printf("4. ARRAYS (always passed as pointers):\n");
    int arr[] = {1, 2, 3, 4, 5};
    printf("Original array address: %p\n", (void*)arr);
    printf("Original array: ");
    for (int i = 0; i < 5; i++) printf("%d ", arr[i]);
    printf("\n");
    
    modifyArray(arr, 5);
    printf("After modifyArray: ");
    for (int i = 0; i < 5; i++) printf("%d ", arr[i]);
    printf(" (modified!)\n");
    
    arrayIsPointer(arr, 5);
    printf("After arrayIsPointer: arr[0] = %d\n\n", arr[0]);

    // ─── Struct Demo ───
    printf("5. STRUCT PASSING:\n");
    Point pt = {5, 10, "Origin"};
    printf("Original point: (%d, %d)\n", pt.x, pt.y);
    
    movePointByValue(pt, 3, 4);
    printf("After movePointByValue: (%d, %d) (unchanged!)\n", pt.x, pt.y);
    
    movePointByPointer(&pt, 3, 4);
    printf("After movePointByPointer: (%d, %d) (changed!)\n\n", pt.x, pt.y);

    // ─── Multiple Return Values Demo ───
    printf("6. RETURNING MULTIPLE VALUES:\n");
    int quot, rem;
    if (divmod(17, 5, &quot, &rem) == 0) {
        printf("17 / 5 = %d remainder %d\n", quot, rem);
    }

    return 0;
}
```

**Critical Understanding:**
- **C is ALWAYS pass by value:** Even when passing pointers, the pointer value (address) itself is copied.
- **Simulating Pass by Reference:** By passing addresses (pointers), we can modify the original data.
- **Arrays are Special:** Array names decay to pointers when passed to functions, so modifications affect the original.
- **Performance Implications:** Passing large structs by value is expensive (entire struct is copied). Pass pointers for efficiency.
- **Multiple Returns:** Use pointer parameters to return multiple values from a function.

## The Call Stack Deep Dive

```c
#include <stdio.h>
#include <stdlib.h>

// ═══════════════════════════════════════════════════════════════════════
// UNDERSTANDING THE CALL STACK
// The call stack is a LIFO (Last In, First Out) data structure that stores:
// 1. Function parameters
// 2. Return addresses (where to return after function completes)
// 3. Local variables
// 4. Saved register values
// Each function call creates a new "stack frame" or "activation record"
// ═══════════════════════════════════════════════════════════════════════

// ─────────────────────────────────────────────────────────────────────
// VISUALIZING STACK FRAMES
// ─────────────────────────────────────────────────────────────────────

void showStackAddress(const char* varName, void* address) {
    static void* firstAddress = NULL;
    if (firstAddress == NULL) {
        firstAddress = address;
    }
    
    long offset = (char*)firstAddress - (char*)address;
    printf("  %-20s: %p [Offset from first: %+ld bytes]\n", 
           varName, address, offset);
}

void functionC(int c_param) {
    printf("\n=== In functionC (Stack Frame 4) ===\n");
    int c_local1 = 300;
    int c_local2 = 301;
    
    showStackAddress("c_param", &c_param);
    showStackAddress("c_local1", &c_local1);
    showStackAddress("c_local2", &c_local2);
    
    printf("functionC executing with param: %d\n", c_param);
    // When functionC returns, its stack frame is destroyed
}

void functionB(int b_param) {
    printf("\n=== In functionB (Stack Frame 3) ===\n");
    int b_local = 200;
    
    showStackAddress("b_param", &b_param);
    showStackAddress("b_local", &b_local);
    
    printf("functionB calling functionC...\n");
    functionC(b_param + 10);
    
    printf("Back in functionB after functionC returned\n");
}

void functionA(int a_param) {
    printf("\n=== In functionA (Stack Frame 2) ===\n");
    int a_local = 100;
    
    showStackAddress("a_param", &a_param);
    showStackAddress("a_local", &a_local);
    
    printf("functionA calling functionB...\n");
    functionB(a_param + 5);
    
    printf("Back in functionA after functionB returned\n");
}

// ─────────────────────────────────────────────────────────────────────
// STACK OVERFLOW DEMONSTRATION
// ─────────────────────────────────────────────────────────────────────

int recursionDepth = 0;

void infiniteRecursion(int n) {
    recursionDepth++;
    
    // Show progress every 10000 calls
    if (recursionDepth % 10000 == 0) {
        int local = n;  // Local variable to consume stack space
        printf("Recursion depth: %d, Stack address: %p\n", 
               recursionDepth, (void*)&local);
    }
    
    // WARNING: This will cause stack overflow!
    // Uncomment carefully and be ready to terminate
    // infiniteRecursion(n + 1);
}

// ─────────────────────────────────────────────────────────────────────
// PROPER RECURSION WITH BASE CASE
// ─────────────────────────────────────────────────────────────────────

unsigned long factorial(int n, int depth) {
    // Visualize stack growth
    int local_n = n;
    printf("%*sFactorial(%d) - Stack at: %p\n", 
           depth * 2, "", n, (void*)&local_n);
    
    // BASE CASE - stops recursion
    if (n <= 1) {
        printf("%*sReturning 1 (base case)\n", depth * 2, "");
        return 1;
    }
    
    // RECURSIVE CASE
    unsigned long result = n * factorial(n - 1, depth + 1);
    printf("%*sReturning %d * factorial(%d) = %lu\n", 
           depth * 2, "", n, n-1, result);
    return result;
}

// ─────────────────────────────────────────────────────────────────────
// TAIL RECURSION OPTIMIZATION
// ─────────────────────────────────────────────────────────────────────

// Non-tail recursive (accumulates multiplication after recursive call)
int multiplyNonTail(int a, int b) {
    if (b == 0) return 0;
    return a + multiplyNonTail(a, b - 1);  // Operation AFTER recursive call
}

// Tail recursive (last operation is the recursive call)
// Compiler can optimize this to iteration (tail call optimization)
int multiplyTailHelper(int a, int b, int accumulator) {
    if (b == 0) return accumulator;
    return multiplyTailHelper(a, b - 1, accumulator + a);  // Last operation
}

int multiplyTail(int a, int b) {
    return multiplyTailHelper(a, b, 0);
}

// ─────────────────────────────────────────────────────────────────────
// STACK VS HEAP ALLOCATION
// ─────────────────────────────────────────────────────────────────────

void demonstrateStackVsHeap() {
    printf("\n=== STACK vs HEAP ALLOCATION ===\n");
    
    // Stack allocation - automatic, fast, limited size
    int stackArray[5] = {1, 2, 3, 4, 5};  // Allocated on stack
    printf("Stack array address: %p\n", (void*)stackArray);
    
    // Heap allocation - manual, slower, larger size available
    int* heapArray = (int*)malloc(5 * sizeof(int));  // Allocated on heap
    if (heapArray != NULL) {
        printf("Heap array address:  %p\n", (void*)heapArray);
        
        // Initialize heap array
        for (int i = 0; i < 5; i++) {
            heapArray[i] = (i + 1) * 10;
        }
        
        // Stack addresses typically grow downward (high to low)
        // Heap addresses typically grow upward (low to high)
        printf("\nAddress comparison:\n");
        printf("Stack variable:   %p\n", (void*)&stackArray);
        printf("Heap memory:      %p\n", (void*)heapArray);
        
        if ((void*)&stackArray > (void*)heapArray) {
            printf("Stack is at higher address (typical)\n");
        }
        
        free(heapArray);  // MUST free heap memory manually
    }
}

// ─────────────────────────────────────────────────────────────────────
// VARIABLE LIFETIME AND SCOPE
// ─────────────────────────────────────────────────────────────────────

int* dangerousFunction() {
    int local = 42;  // Local variable on stack
    return &local;   // WARNING: Returning address of local variable!
}  // 'local' is destroyed here, returned pointer is now dangling

int* safeFunction() {
    int* heapVar = (int*)malloc(sizeof(int));  // Heap allocation
    *heapVar = 42;
    return heapVar;  // Safe: heap memory persists after function returns
}  // Caller must remember to free() the returned pointer

// ─────────────────────────────────────────────────────────────────────
// DEMONSTRATING STACK FRAME CLEANUP
// ─────────────────────────────────────────────────────────────────────

void showStackCleanup() {
    int beforeCall;
    printf("\n=== STACK FRAME CLEANUP DEMO ===\n");
    printf("Variable before calls: %p\n", (void*)&beforeCall);
    
    // Make a function call
    void innerFunction() {
        int innerVar1 = 111;
        int innerVar2 = 222;
        printf("Inside inner: var1=%p, var2=%p\n", 
               (void*)&innerVar1, (void*)&innerVar2);
    }
    
    innerFunction();
    
    // After return, the stack space is reclaimed
    int afterCall;
    printf("Variable after calls:  %p (likely reusing same stack space)\n", 
           (void*)&afterCall);
}

int main() {
    printf("════════════════════════════════════════════════════════\n");
    printf("THE CALL STACK IN ACTION\n");
    printf("════════════════════════════════════════════════════════\n");
    
    // Show main's stack frame
    printf("\n=== In main (Stack Frame 1) ===\n");
    int main_local = 10;
    showStackAddress("main_local", &main_local);
    
    // Demonstrate nested function calls and stack growth
    printf("\nCalling functionA...\n");
    functionA(5);
    printf("\nBack in main after all functions returned\n");
    
    // Demonstrate recursion and stack
    printf("\n════════════════════════════════════════════════════════\n");
    printf("RECURSION AND THE STACK\n");
    printf("════════════════════════════════════════════════════════\n");
    
    printf("\nCalculating factorial(5):\n");
    printf("Result: %lu\n", factorial(5, 0));
    
    // Stack vs Heap
    demonstrateStackVsHeap();
    
    // Stack cleanup
    showStackCleanup();
    
    // Warning about stack overflow (commented out for safety)
    printf("\n════════════════════════════════════════════════════════\n");
    printf("STACK OVERFLOW (demonstration commented out for safety)\n");
    printf("Uncomment infiniteRecursion() call to see stack overflow\n");
    printf("════════════════════════════════════════════════════════\n");
    // infiniteRecursion(0);  // WARNING: Will crash program!
    
    return 0;
}
```

**Call Stack Key Concepts:**
- **Stack Frames:** Each function call creates a new frame containing local variables, parameters, and return address.
- **LIFO Nature:** Last function called is first to return (Last In, First Out).
- **Stack Growth:** Stack typically grows downward in memory (from high to low addresses).
- **Automatic Cleanup:** When function returns, its entire stack frame is automatically reclaimed.
- **Stack Overflow:** Occurs when stack space is exhausted (too many function calls or large local variables).
- **Stack vs Heap:** Stack is fast but limited; heap is slower but provides more space and persistent allocation.

## Function Pointers

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ═══════════════════════════════════════════════════════════════════════
// FUNCTION POINTERS - Pointers that store addresses of functions
// Enables:
// 1. Callbacks and event handlers
// 2. Dynamic function dispatch
// 3. Implementing polymorphism in C
// 4. Function tables/arrays for state machines
// ═══════════════════════════════════════════════════════════════════════

// ─────────────────────────────────────────────────────────────────────
// BASIC FUNCTION POINTER SYNTAX
// ─────────────────────────────────────────────────────────────────────

// Regular functions to point to
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

int divide_int(int a, int b) {
    if (b == 0) {
        printf("Error: Division by zero!\n");
        return 0;
    }
    return a / b;
}

void demonstrateBasicFunctionPointers() {
    printf("\n=== BASIC FUNCTION POINTERS ===\n");
    
    // Declaring a function pointer
    // Syntax: return_type (*pointer_name)(parameter_types)
    int (*operation)(int, int);
    
    // Method 1: Assign function address explicitly
    operation = &add;  // & is optional for function names
    printf("5 + 3 = %d\n", operation(5, 3));
    
    // Method 2: Assign without & (function name decays to pointer)
    operation = subtract;
    printf("5 - 3 = %d\n", (*operation)(5, 3));  // * is optional when calling
    
    // Both calling methods work
    operation = multiply;
    printf("5 * 3 = %d (called with operation())\n", operation(5, 3));
    printf("5 * 3 = %d (called with (*operation)())\n", (*operation)(5, 3));
}

// ─────────────────────────────────────────────────────────────────────
// TYPEDEF FOR FUNCTION POINTERS (Improves readability)
// ─────────────────────────────────────────────────────────────────────

// Define a type for function pointers
typedef int (*BinaryOperation)(int, int);
typedef void (*VoidFunction)(void);
typedef void (*Callback)(int);

void demonstrateTypedefFunctionPointers() {
    printf("\n=== TYPEDEF FUNCTION POINTERS ===\n");
    
    // Much cleaner syntax with typedef
    BinaryOperation op = add;
    printf("Using typedef: 10 + 20 = %d\n", op(10, 20));
    
    // Can easily swap functions
    op = multiply;
    printf("Same variable, different function: 10 * 20 = %d\n", op(10, 20));
}

// ─────────────────────────────────────────────────────────────────────
// FUNCTION POINTER ARRAYS (Jump tables, dispatch tables)
// ─────────────────────────────────────────────────────────────────────

void demonstrateFunctionPointerArrays() {
    printf("\n=== FUNCTION POINTER ARRAYS ===\n");
    
    // Array of function pointers - useful for calculators, state machines
    BinaryOperation operations[] = {add, subtract, multiply, divide_int};
    const char* op_names[] = {"Add", "Subtract", "Multiply", "Divide"};
    
    int a = 12, b = 4;
    
    for (int i = 0; i < 4; i++) {
        printf("%s: %d and %d = %d\n", 
               op_names[i], a, b, operations[i](a, b));
    }
    
    // Calculator using function pointer array
    printf("\nSimple Calculator:\n");
    printf("0: Add, 1: Sub, 2: Mul, 3: Div\n");
    printf("Enter operation (0-3): ");
    int choice = 2;  // Simulating user input
    printf("%d\n", choice);  // Echo the choice
    
    if (choice >= 0 && choice < 4) {
        printf("Result: %d\n", operations[choice](20, 5));
    }
}

// ─────────────────────────────────────────────────────────────────────
// CALLBACKS - Passing functions as arguments
// ─────────────────────────────────────────────────────────────────────

// Generic array processor that accepts a callback
void processArray(int arr[], int size, void (*process)(int)) {
    for (int i = 0; i < size; i++) {
        process(arr[i]);
    }
}

// Different callback functions
void printValue(int value) {
    printf("%d ", value);
}

void printSquare(int value) {
    printf("%d ", value * value);
}

void printHex(int value) {
    printf("0x%X ", value);
}

// Generic sorting function using comparison callback
void bubbleSortGeneric(void* arr, int size, int elemSize,
                       int (*compare)(const void*, const void*)) {
    char* array = (char*)arr;  // Treat as byte array for generic access
    void* temp = malloc(elemSize);  // Temporary storage for swapping
    
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            void* elem1 = array + j * elemSize;
            void* elem2 = array + (j + 1) * elemSize;
            
            if (compare(elem1, elem2) > 0) {
                // Swap elements
                memcpy(temp, elem1, elemSize);
                memcpy(elem1, elem2, elemSize);
                memcpy(elem2, temp, elemSize);
            }
        }
    }
    free(temp);
}

// Comparison functions for different sorting orders
int compareAscending(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

int compareDescending(const void* a, const void* b) {
    return *(int*)b - *(int*)a;
}

void demonstrateCallbacks() {
    printf("\n=== CALLBACKS ===\n");
    
    int arr[] = {1, 2, 3, 4, 5};
    
    printf("Original values: ");
    processArray(arr, 5, printValue);
    printf("\n");
    
    printf("Squared values:  ");
    processArray(arr, 5, printSquare);
    printf("\n");
    
    printf("Hex values:      ");
    processArray(arr, 5, printHex);
    printf("\n");
    
    // Sorting with callbacks
    int numbers[] = {64, 34, 25, 12, 22, 11, 90};
    int n = 7;
    
    printf("\nOriginal array: ");
    for (int i = 0; i < n; i++) printf("%d ", numbers[i]);
    printf("\n");
    
    bubbleSortGeneric(numbers, n, sizeof(int), compareAscending);
    printf("Sorted ascending: ");
    for (int i = 0; i < n; i++) printf("%d ", numbers[i]);
    printf("\n");
    
    bubbleSortGeneric(numbers, n, sizeof(int), compareDescending);
    printf("Sorted descending: ");
    for (int i = 0; i < n; i++) printf("%d ", numbers[i]);
    printf("\n");
}

// ─────────────────────────────────────────────────────────────────────
// FUNCTION POINTERS IN STRUCTS (Object-oriented style programming)
// ─────────────────────────────────────────────────────────────────────

typedef struct {
    int x, y;
    
    // Function pointers as "methods"
    void (*print)(int, int);
    int (*calculate_distance)(int, int);
} Point;

void printPoint(int x, int y) {
    printf("Point(%d, %d)\n", x, y);
}

int manhattanDistance(int x, int y) {
    return abs(x) + abs(y);
}

// "Constructor" function
Point createPoint(int x, int y) {
    Point p = {
        .x = x,
        .y = y,
        .print = printPoint,
        .calculate_distance = manhattanDistance
    };
    return p;
}

void demonstrateStructFunctionPointers() {
    printf("\n=== FUNCTION POINTERS IN STRUCTS ===\n");
    
    Point p1 = createPoint(3, 4);
    
    // Call "methods" through function pointers
    printf("Point p1: ");
    p1.print(p1.x, p1.y);
    
    printf("Distance from origin: %d\n", 
           p1.calculate_distance(p1.x, p1.y));
}

// ─────────────────────────────────────────────────────────────────────
// STATE MACHINE USING FUNCTION POINTERS
// ─────────────────────────────────────────────────────────────────────

typedef enum {
    STATE_IDLE,
    STATE_RUNNING,
    STATE_PAUSED,
    STATE_STOPPED
} State;

typedef State (*StateHandler)(void);

State handleIdle(void) {
    printf("State: IDLE -> Starting...\n");
    return STATE_RUNNING;
}

State handleRunning(void) {
    static int counter = 0;
    printf("State: RUNNING (iteration %d)\n", ++counter);
    if (counter >= 3) {
        counter = 0;
        return STATE_PAUSED;
    }
    return STATE_RUNNING;
}

State handlePaused(void) {
    printf("State: PAUSED -> Stopping...\n");
    return STATE_STOPPED;
}

State handleStopped(void) {
    printf("State: STOPPED (terminal state)\n");
    return STATE_STOPPED;
}

void demonstrateStateMachine() {
    printf("\n=== STATE MACHINE WITH FUNCTION POINTERS ===\n");
    
    // Function pointer table indexed by state
    StateHandler stateHandlers[] = {
        handleIdle,
        handleRunning,
        handlePaused,
        handleStopped
    };
    
    State currentState = STATE_IDLE;
    
    // Run state machine for several iterations
    for (int i = 0; i < 8; i++) {
        currentState = stateHandlers[currentState]();
        
        if (currentState == STATE_STOPPED) {
            printf("State machine terminated.\n");
            break;
        }
    }
}

// ─────────────────────────────────────────────────────────────────────
// RETURNING FUNCTION POINTERS FROM FUNCTIONS
// ─────────────────────────────────────────────────────────────────────

BinaryOperation getOperation(char op) {
    switch(op) {
        case '+': return add;
        case '-': return subtract;
        case '*': return multiply;
        case '/': return divide_int;
        default:  return NULL;
    }
}

void demonstrateFunctionReturningFunctionPointer() {
    printf("\n=== FUNCTIONS RETURNING FUNCTION POINTERS ===\n");
    
    char operators[] = {'+', '-', '*', '/'};
    
    for (int i = 0; i < 4; i++) {
        BinaryOperation op = getOperation(operators[i]);
        if (op != NULL) {
            printf("10 %c 3 = %d\n", operators[i], op(10, 3));
        }
    }
}

int main() {
    printf("════════════════════════════════════════════════════════\n");
    printf("FUNCTION POINTERS - ADVANCED C PROGRAMMING\n");
    printf("════════════════════════════════════════════════════════\n");
    
    demonstrateBasicFunctionPointers();
    demonstrateTypedefFunctionPointers();
    demonstrateFunctionPointerArrays();
    demonstrateCallbacks();
    demonstrateStructFunctionPointers();
    demonstrateStateMachine();
    demonstrateFunctionReturningFunctionPointer();
    
    return 0;
}
```

**Function Pointer Mastery:**
- **Syntax:** `return_type (*name)(params)` - The parentheses around `*name` are crucial.
- **typedef:** Makes function pointer syntax much more readable.
- **Callbacks:** Enable generic programming by passing behavior as arguments.
- **Jump Tables:** Arrays of function pointers for efficient dispatch based on index.
- **Virtual Functions:** Simulating OOP by storing function pointers in structs.
- **State Machines:** Clean implementation using function pointer tables.

---

# Arrays & Array-Pointer Duality

## Static Arrays

```c
#include <stdio.h>
#include <string.h>
#include <limits.h>

// ═══════════════════════════════════════════════════════════════════════
// ARRAYS IN C - FUNDAMENTAL CONCEPTS
// Arrays are:
// 1. Contiguous blocks of memory
// 2. Fixed size (determined at compile time for static arrays)
// 3. Zero-indexed
// 4. Not bounds-checked (can access beyond array limits - undefined behavior)
// 5. Array name represents the address of first element
// ═══════════════════════════════════════════════════════════════════════

void demonstrateArrayBasics() {
    printf("\n=== ARRAY BASICS ===\n");
    
    // ─────────────────────────────────────────────────────────────────
    // ARRAY DECLARATION AND INITIALIZATION
    // ─────────────────────────────────────────────────────────────────
    
    // Method 1: Declare then initialize
    int arr1[5];  // Uninitialized - contains garbage values
    arr1[0] = 10;
    arr1[1] = 20;
    arr1[2] = 30;
    arr1[3] = 40;
    arr1[4] = 50;
    
    // Method 2: Initialize at declaration
    int arr2[5] = {10, 20, 30, 40, 50};
    
    // Method 3: Partial initialization (rest filled with zeros)
    int arr3[5] = {10, 20};  // arr3 = {10, 20, 0, 0, 0}
    
    // Method 4: Zero initialization
    int arr4[5] = {0};  // All elements set to 0
    
    // Method 5: Compiler deduces size
    int arr5[] = {1, 2, 3, 4, 5};  // Size = 5
    
    // Method 6: Designated initializers (C99)
    int arr6[5] = {[0] = 10, [2] = 30, [4] = 50};  // {10, 0, 30, 0, 50}
    
    // Print arrays to demonstrate initialization
    printf("arr2 (full init):    ");
    for (int i = 0; i < 5; i++) printf("%d ", arr2[i]);
    printf("\n");
    
    printf("arr3 (partial init): ");
    for (int i = 0; i < 5; i++) printf("%d ", arr3[i]);
    printf("\n");
    
    printf("arr6 (designated):   ");
    for (int i = 0; i < 5; i++) printf("%d ", arr6[i]);
    printf("\n");
    
    // ─────────────────────────────────────────────────────────────────
    // ARRAY SIZE AND MEMORY LAYOUT
    // ─────────────────────────────────────────────────────────────────
    
    printf("\n--- Array Memory Layout ---\n");
    int arr[5] = {100, 200, 300, 400, 500};
    
    printf("Array size: %zu bytes\n", sizeof(arr));
    printf("Element size: %zu bytes\n", sizeof(arr[0]));
    printf("Number of elements: %zu\n", sizeof(arr) / sizeof(arr[0]));
    
    printf("\nMemory addresses (contiguous):\n");
    for (int i = 0; i < 5; i++) {
        printf("arr[%d] = %3d at address %p\n", i, arr[i], (void*)&arr[i]);
    }
    
    // Notice: addresses differ by sizeof(int), typically 4 bytes
    printf("\nAddress difference: %ld bytes\n", 
           (char*)&arr[1] - (char*)&arr[0]);
}

// ─────────────────────────────────────────────────────────────────────
// MULTIDIMENSIONAL ARRAYS
// ─────────────────────────────────────────────────────────────────────

void demonstrateMultidimensionalArrays() {
    printf("\n=== MULTIDIMENSIONAL ARRAYS ===\n");
    
    // 2D array - stored in row-major order (rows are contiguous)
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    // Alternative initialization (flattened)
    int matrix2[3][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    
    // Partial initialization
    int matrix3[3][4] = {{1, 2}, {5}};  // Rest filled with zeros
    
    // Print 2D array
    printf("Matrix:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
    
    // Memory layout of 2D array (row-major order)
    printf("\n2D Array Memory Layout (Row-Major):\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            printf("matrix[%d][%d] = %2d at %p\n", 
                   i, j, matrix[i][j], (void*)&matrix[i][j]);
        }
    }
    
    // Accessing 2D array as 1D (since it's contiguous)
    printf("\nAccessing as 1D array:\n");
    int* ptr = &matrix[0][0];  // or (int*)matrix
    for (int i = 0; i < 12; i++) {
        printf("%d ", ptr[i]);
    }
    printf("\n");
    
    // 3D arrays and beyond
    int cube[2][3][4] = {
        {{1,2,3,4}, {5,6,7,8}, {9,10,11,12}},
        {{13,14,15,16}, {17,18,19,20}, {21,22,23,24}}
    };
    
    printf("\n3D Array first element: %d\n", cube[0][0][0]);
    printf("3D Array size: %zu bytes\n", sizeof(cube));
}

// ─────────────────────────────────────────────────────────────────────
// VARIABLE LENGTH ARRAYS (VLAs) - C99
// ─────────────────────────────────────────────────────────────────────

void demonstrateVLAs(int n) {
    printf("\n=== VARIABLE LENGTH ARRAYS (C99) ===\n");
    
    // VLA - size determined at runtime
    // Note: VLAs are allocated on stack, be careful with large sizes!
    int vla[n];  // Size = n (runtime value)
    
    // Initialize VLA
    for (int i = 0; i < n; i++) {
        vla[i] = i * i;
    }
    
    printf("VLA of size %d: ", n);
    for (int i = 0; i < n; i++) {
        printf("%d ", vla[i]);
    }
    printf("\n");
    
    // 2D VLA
    int rows = 3, cols = 4;
    int vla2d[rows][cols];
    
    // Initialize 2D VLA
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            vla2d[i][j] = i * cols + j;
        }
    }
    
    printf("\n2D VLA (%dx%d):\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%3d ", vla2d[i][j]);
        }
        printf("\n");
    }
    
    // Warning: sizeof(VLA) is computed at runtime
    printf("\nVLA size (computed at runtime): %zu bytes\n", sizeof(vla));
}

// ─────────────────────────────────────────────────────────────────────
// ARRAY BOUNDS AND COMMON PITFALLS
// ─────────────────────────────────────────────────────────────────────

void demonstrateArrayBounds() {
    printf("\n=== ARRAY BOUNDS AND SAFETY ===\n");
    
    int arr[5] = {10, 20, 30, 40, 50};
    
    printf("Valid array access:\n");
    for (int i = 0; i < 5; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
    
    // WARNING: No bounds checking in C!
    printf("\n⚠️  DANGEROUS: Accessing out of bounds:\n");
    printf("arr[-1] = %d (before array)\n", arr[-1]);  // Undefined behavior!
    printf("arr[5] = %d (after array)\n", arr[5]);     // Undefined behavior!
    
    // Buffer overflow example (DANGEROUS - commented for safety)
    // char buffer[10];
    // strcpy(buffer, "This string is way too long for the buffer!");  // OVERFLOW!
    
    // Safe alternative using strncpy
    char safeBuffer[10];
    strncpy(safeBuffer, "Hello", sizeof(safeBuffer) - 1);
    safeBuffer[sizeof(safeBuffer) - 1] = '\0';  // Ensure null termination
    printf("\nSafe string copy: %s\n", safeBuffer);
}

// ─────────────────────────────────────────────────────────────────────
// ARRAY INITIALIZATION PATTERNS AND TECHNIQUES
// ─────────────────────────────────────────────────────────────────────

void demonstrateArrayPatterns() {
    printf("\n=== ARRAY PATTERNS AND TECHNIQUES ===\n");
    
    // Initialize with a pattern
    int fibonacci[10];
    fibonacci[0] = 0;
    fibonacci[1] = 1;
    for (int i = 2; i < 10; i++) {
        fibonacci[i] = fibonacci[i-1] + fibonacci[i-2];
    }
    
    printf("Fibonacci sequence: ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", fibonacci[i]);
    }
    printf("\n");
    
    // Creating a frequency table
    int freq[256] = {0};  // For ASCII characters
    char str[] = "hello world";
    
    for (int i = 0; str[i] != '\0'; i++) {
        freq[(unsigned char)str[i]]++;
    }
    
    printf("\nCharacter frequencies in \"%s\":\n", str);
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            printf("'%c': %d times\n", i, freq[i]);
        }
    }
    
    // Lookup table for fast computation
    const int squares[11] = {0, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100};
    printf("\nSquare lookup table: 7^2 = %d\n", squares[7]);
    
    // Circular buffer pattern
    int circularBuffer[5] = {0};
    int writeIndex = 0;
    
    printf("\nCircular buffer writes:\n");
    for (int value = 1; value <= 8; value++) {
        circularBuffer[writeIndex] = value;
        printf("Write %d at index %d\n", value, writeIndex);
        writeIndex = (writeIndex + 1) % 5;  // Wrap around
    }
    
    printf("Final buffer state: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", circularBuffer[i]);
    }
    printf("\n");
}

// ─────────────────────────────────────────────────────────────────────
// CONST ARRAYS AND ARRAY PARAMETERS
// ─────────────────────────────────────────────────────────────────────

void processArray(const int arr[], int size) {
    // arr[0] = 100;  // ERROR: cannot modify const array
    
    // Can still read values
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    printf("Sum of array elements: %d\n", sum);
}

void modifyArray(int arr[], int size) {
    // CAN modify array elements (arr is a pointer to non-const)
    for (int i = 0; i < size; i++) {
        arr[i] *= 2;
    }
}

void demonstrate2DArrayParameter(int rows, int cols, int arr[][cols]) {
    // For 2D arrays as parameters, must specify all dimensions except first
    // Or use VLA syntax (C99)
    printf("2D array parameter:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

void demonstrateConstArrays() {
    printf("\n=== CONST ARRAYS ===\n");
    
    // Const array - elements cannot be modified
    const int constArr[] = {1, 2, 3, 4, 5};
    // constArr[0] = 10;  // ERROR: assignment of read-only location
    
    int normalArr[] = {1, 2, 3, 4, 5};
    
    printf("Before modification: ");
    for (int i = 0; i < 5; i++) printf("%d ", normalArr[i]);
    printf("\n");
    
    modifyArray(normalArr, 5);
    
    printf("After modification:  ");
    for (int i = 0; i < 5; i++) printf("%d ", normalArr[i]);
    printf("\n");
    
    processArray(constArr, 5);  // Pass const array to function
    
    // 2D array example
    int matrix[2][3] = {{1,2,3}, {4,5,6}};
    demonstrate2DArrayParameter(2, 3, matrix);
}

int main() {
    printf("════════════════════════════════════════════════════════\n");
    printf("COMPREHENSIVE ARRAY GUIDE\n");
    printf("════════════════════════════════════════════════════════\n");
    
    demonstrateArrayBasics();
    demonstrateMultidimensionalArrays();
    demonstrateVLAs(7);
    demonstrateArrayBounds();
    demonstrateArrayPatterns();
    demonstrateConstArrays();
    
    return 0;
}
```

## Array-Pointer Relationship

```c
#include <stdio.h>
#include <stdlib.h>

// ═══════════════════════════════════════════════════════════════════════
// THE ARRAY-POINTER DUALITY
// Key Concepts:
// 1. Array name "decays" to pointer to first element in most contexts
// 2. Pointer arithmetic is scaled by the size of pointed-to type
// 3. Array notation arr[i] is syntactic sugar for *(arr + i)
// 4. Arrays and pointers are NOT the same (different types, behaviors)
// ═══════════════════════════════════════════════════════════════════════

void demonstrateArrayPointerBasics() {
    printf("\n=== ARRAY-POINTER RELATIONSHIP BASICS ===\n");
    
    int arr[5] = {10, 20, 30, 40, 50};
    int *ptr = arr;  // Array name decays to pointer to first element
    
    // CRITICAL: arr and &arr[0] are equivalent in most contexts
    printf("arr     = %p (array name as pointer)\n", (void*)arr);
    printf("&arr[0] = %p (address of first element)\n", (void*)&arr[0]);
    printf("ptr     = %p (pointer to first element)\n", (void*)ptr);
    
    // But &arr is different - it's pointer to entire array!
    printf("&arr    = %p (address of entire array)\n", (void*)&arr);
    
    // Size difference reveals the distinction
    printf("\nsizeof(arr) = %zu bytes (entire array)\n", sizeof(arr));
    printf("sizeof(ptr) = %zu bytes (just a pointer)\n", sizeof(ptr));
    
    // ─────────────────────────────────────────────────────────────────
    // ARRAY INDEXING vs POINTER ARITHMETIC
    // ─────────────────────────────────────────────────────────────────
    
    printf("\n--- Array Indexing vs Pointer Arithmetic ---\n");
    
    // These are ALL equivalent ways to access array elements:
    printf("arr[2]     = %d\n", arr[2]);        // Array indexing
    printf("*(arr + 2) = %d\n", *(arr + 2));    // Pointer arithmetic
    printf("ptr[2]     = %d\n", ptr[2]);        // Pointer used with array syntax
    printf("*(ptr + 2) = %d\n", *(ptr + 2));    // Pointer arithmetic
    printf("2[arr]     = %d\n", 2[arr]);        // Weird but valid! (arr[2] = 2[arr])
    
    // Pointer arithmetic in action
    printf("\nPointer arithmetic traversal:\n");
    for (int i = 0; i < 5; i++) {
        printf("ptr + %d points to %d at address %p\n", 
               i, *(ptr + i), (void*)(ptr + i));
    }
}

// ─────────────────────────────────────────────────────────────────────
// POINTER ARITHMETIC DEEP DIVE
// ─────────────────────────────────────────────────────────────────────

void demonstratePointerArithmetic() {
    printf("\n=== POINTER ARITHMETIC IN DETAIL ===\n");
    
    // Different data types to show scaling
    char charArr[] = "ABCDE";
    int intArr[] = {100, 200, 300, 400, 500};
    double doubleArr[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    
    char *charPtr = charArr;
    int *intPtr = intArr;
    double *doublePtr = doubleArr;
    
    printf("Pointer arithmetic scaling by type size:\n");
    printf("Type    | Size | ptr | ptr+1 | Difference\n");
    printf("--------|------|-----|-------|------------\n");
    
    printf("char    | %zu   | %p | %p | %ld bytes\n", 
           sizeof(char), (void*)charPtr, (void*)(charPtr + 1),
           (char*)(charPtr + 1) - charPtr);
    
    printf("int     | %zu   | %p | %p | %ld bytes\n",
           sizeof(int), (void*)intPtr, (void*)(intPtr + 1),
           (char*)(intPtr + 1) - (char*)intPtr);
    
    printf("double  | %zu   | %p | %p | %ld bytes\n",
           sizeof(double), (void*)doublePtr, (void*)(doublePtr + 1),
           (char*)(doublePtr + 1) - (char*)doublePtr);
    
    // ─────────────────────────────────────────────────────────────────
    // POINTER SUBTRACTION
    // ─────────────────────────────────────────────────────────────────
    
    printf("\n--- Pointer Subtraction ---\n");
    int *start = &intArr[0];
    int *end = &intArr[4];
    
    ptrdiff_t diff = end - start;  // Type for pointer differences
    printf("end - start = %td elements\n", diff);
    printf("Actual byte difference: %ld bytes\n", 
           (char*)end - (char*)start);
    
    // Finding element index using pointer subtraction
    int *current = &intArr[2];
    printf("Index of current element: %td\n", current - intArr);
}

// ─────────────────────────────────────────────────────────────────────
// ARRAYS vs POINTERS: KEY DIFFERENCES
// ─────────────────────────────────────────────────────────────────────

void demonstrateArrayPointerDifferences() {
    printf("\n=== ARRAYS vs POINTERS: KEY DIFFERENCES ===\n");
    
    int arr[5] = {1, 2, 3, 4, 5};
    int *ptr = arr;
    int *heapPtr = (int*)malloc(5 * sizeof(int));
    
    // Difference 1: sizeof operator
    printf("1. sizeof behavior:\n");
    printf("   sizeof(arr) = %zu (whole array)\n", sizeof(arr));
    printf("   sizeof(ptr) = %zu (pointer size)\n", sizeof(ptr));
    
    // Difference 2: & operator
    printf("\n2. Address-of operator:\n");
    printf("   &arr = %p (address of array)\n", (void*)&arr);
    printf("   &ptr = %p (address of pointer variable)\n", (void*)&ptr);
    printf("   arr  = %p (array decays to pointer)\n", (void*)arr);
    printf("   ptr  = %p (pointer value)\n", (void*)ptr);
    
    // Difference 3: Assignment
    printf("\n3. Assignment:\n");
    // arr = ptr;  // ERROR: Cannot assign to array
    ptr = arr;     // OK: Can assign to pointer
    printf("   Arrays cannot be assigned to (arr = ptr is illegal)\n");
    printf("   Pointers can be reassigned (ptr = arr is OK)\n");
    
    // Difference 4: Arithmetic on array name vs pointer
    printf("\n4. Arithmetic:\n");
    // arr++;  // ERROR: Cannot modify array name
    ptr++;     // OK: Can modify pointer
    printf("   Cannot do arr++ (array name is not modifiable)\n");
    printf("   Can do ptr++ (pointer is modifiable)\n");
    ptr = arr; // Reset ptr
    
    // Difference 5: String literals
    printf("\n5. String literal behavior:\n");
    char strArr[] = "Hello";  // Array: modifiable copy
    char *strPtr = "World";   // Pointer: to read-only string literal
    
    strArr[0] = 'h';  // OK: Array is modifiable
    // strPtr[0] = 'w';  // UNDEFINED: Attempting to modify string literal
    
    printf("   char strArr[] = \"Hello\"; // Modifiable array\n");
    printf("   char *strPtr = \"World\";  // Pointer to read-only literal\n");
    
    free(heapPtr);
}

// ─────────────────────────────────────────────────────────────────────
// PASSING ARRAYS TO FUNCTIONS - THE DECAY
// ─────────────────────────────────────────────────────────────────────

void functionWithArrayParam(int arr[10]) {  // The 10 is ignored!
    printf("In function - sizeof(arr): %zu (pointer size, not array!)\n", 
           sizeof(arr));
}

void functionWithPointerParam(int *arr) {  // Equivalent to above
    printf("In function - sizeof(arr): %zu (pointer size)\n", 
           sizeof(arr));
}

// For 2D arrays, need to specify column dimension
void function2DArray(int arr[][4], int rows) {  // Must specify columns
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

// Alternative: pass as pointer with manual indexing
void function2DAsPointer(int *arr, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", arr[i * cols + j]);  // Manual 2D indexing
        }
        printf("\n");
    }
}

void demonstrateArrayDecay() {
    printf("\n=== ARRAY DECAY IN FUNCTION CALLS ===\n");
    
    int arr[10] = {0};
    printf("In main - sizeof(arr): %zu (full array)\n", sizeof(arr));
    
    functionWithArrayParam(arr);
    functionWithPointerParam(arr);
    
    // 2D array example
    printf("\n2D Array Passing:\n");
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    printf("Method 1 - Array notation:\n");
    function2DArray(matrix, 3);
    
    printf("\nMethod 2 - Pointer with manual indexing:\n");
    function2DAsPointer(&matrix[0][0], 3, 4);
}

// ─────────────────────────────────────────────────────────────────────
// DYNAMIC ARRAYS USING POINTERS
// ─────────────────────────────────────────────────────────────────────

void demonstrateDynamicArrays() {
    printf("\n=== DYNAMIC ARRAYS USING POINTERS ===\n");
    
    // Dynamic 1D array
    int n = 5;
    int *dynamicArr = (int*)malloc(n * sizeof(int));
    
    if (dynamicArr == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    
    // Initialize and use like regular array
    for (int i = 0; i < n; i++) {
        dynamicArr[i] = i * 10;  // Can use array notation!
    }
    
    printf("Dynamic array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", dynamicArr[i]);
    }
    printf("\n");
    
    // Dynamic 2D array - Method 1: Array of pointers
    int rows = 3, cols = 4;
    int **dynamic2D = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        dynamic2D[i] = (int*)malloc(cols * sizeof(int));
    }
    
    // Initialize 2D array
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            dynamic2D[i][j] = i * cols + j;
        }
    }
    
    printf("\nDynamic 2D array (array of pointers):\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%2d ", dynamic2D[i][j]);
        }
        printf("\n");
    }
    
    // Clean up 2D array
    for (int i = 0; i < rows; i++) {
        free(dynamic2D[i]);
    }
    free(dynamic2D);
    
    // Dynamic 2D array - Method 2: Single allocation (contiguous)
    int *dynamic2DFlat = (int*)malloc(rows * cols * sizeof(int));
    
    // Access using manual indexing
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            dynamic2DFlat[i * cols + j] = i * cols + j;
        }
    }
    
    printf("\nDynamic 2D array (contiguous):\n");
    for (int i = 0; i < rows * cols; i++) {
        if (i % cols == 0 && i > 0) printf("\n");
        printf("%2d ", dynamic2DFlat[i]);
    }
    printf("\n");
    
    free(dynamicArr);
    free(dynamic2DFlat);
}

// ─────────────────────────────────────────────────────────────────────
// POINTER TO ARRAY vs ARRAY OF POINTERS
// ─────────────────────────────────────────────────────────────────────

void demonstratePointerToArray() {
    printf("\n=== POINTER TO ARRAY vs ARRAY OF POINTERS ===\n");
    
    // Array of pointers
    int *arrOfPtrs[3];  // Array of 3 pointers to int
    int a = 10, b = 20, c = 30;
    arrOfPtrs[0] = &a;
    arrOfPtrs[1] = &b;
    arrOfPtrs[2] = &c;
    
    printf("Array of pointers:\n");
    for (int i = 0; i < 3; i++) {
        printf("arrOfPtrs[%d] points to %d\n", i, *arrOfPtrs[i]);
    }
    
    // Pointer to array
    int arr[3] = {100, 200, 300};
    int (*ptrToArr)[3] = &arr;  // Pointer to array of 3 ints
    
    printf("\nPointer to array:\n");
    printf("(*ptrToArr)[0] = %d\n", (*ptrToArr)[0]);
    printf("(*ptrToArr)[1] = %d\n", (*ptrToArr)[1]);
    printf("(*ptrToArr)[2] = %d\n", (*ptrToArr)[2]);
    
    // Pointer arithmetic with pointer to array
    int matrix[2][3] = {{1,2,3}, {4,5,6}};
    int (*ptrToRow)[3] = matrix;  // Points to first row
    
    printf("\nPointer to array in 2D context:\n");
    printf("First row: ");
    for (int i = 0; i < 3; i++) {
        printf("%d ", (*ptrToRow)[i]);
    }
    
    ptrToRow++;  // Move to next row (advances by entire row)
    printf("\nSecond row: ");
    for (int i = 0; i < 3; i++) {
        printf("%d ", (*ptrToRow)[i]);
    }
    printf("\n");
}

int main() {
    printf("════════════════════════════════════════════════════════\n");
    printf("ARRAY-POINTER DUALITY: THE HEART OF C\n");
    printf("════════════════════════════════════════════════════════\n");
    
    demonstrateArrayPointerBasics();
    demonstratePointerArithmetic();
    demonstrateArrayPointerDifferences();
    demonstrateArrayDecay();
    demonstrateDynamicArrays();
    demonstratePointerToArray();
    
    return 0;
}
```

**Array-Pointer Mastery Points:**
- **Array Decay:** Arrays decay to pointers in most contexts (except with `sizeof` and `&` operators).
- **Pointer Arithmetic:** Scaled by the size of the pointed-to type.
- **Equivalence:** `arr[i]` is exactly equivalent to `*(arr + i)`.
- **Key Differences:** Arrays have fixed size and location; pointers are variables that can be reassigned.
- **Function Parameters:** Array parameters are actually pointer parameters.
- **Dynamic Arrays:** Use pointers with `malloc`/`free` for runtime-sized arrays.

---
