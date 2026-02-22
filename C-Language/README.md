# Complete C Programming Guide for SDE Placements

## Table of Contents

### Part 1: Fundamentals
- [Introduction to C](#introduction-to-c)
- [Development Environment Setup](#development-environment-setup)
- [Basic Syntax & Structure](#basic-syntax--structure)
- [Data Types & Variables](#data-types--variables)
- [Operators](#operators)
- [Input/Output](#inputoutput)
- [Control Flow](#control-flow)

### Part 2: Advanced Concepts
- [Functions](#functions)
- [Arrays](#arrays)
- [Strings](#strings)
- [Pointers](#pointers)
- [Structures & Unions](#structures--unions)
- [Dynamic Memory Allocation](#dynamic-memory-allocation)
- [File Handling](#file-handling)
- [Preprocessor Directives](#preprocessor-directives)

### Part 3: Interview Topics
- [Time & Space Complexity](#time--space-complexity)
- [Common Patterns](#common-patterns)
- [Bit Manipulation](#bit-manipulation)
- [Recursion](#recursion)
- [Memory Layout](#memory-layout)
- [Common Pitfalls & Best Practices](#common-pitfalls--best-practices)
- [Interview Questions](#interview-questions)

---

# Introduction to C

## Why C for SDE Interviews?

```
✅ Foundation language for system programming
✅ Direct hardware manipulation & memory management
✅ Understanding C → Understanding how computers work
✅ Required for embedded systems, OS development
✅ Many companies test C fundamentals (especially for SDE roles)
✅ Gateway to C++, understanding OOP better
```

## C Language Features

```
• Procedural programming paradigm
• Low-level memory access
• Fast execution (compiled language)
• Portable across platforms
• Rich library support
• Minimal runtime overhead
```

---

# Development Environment Setup

## Installation

```bash
# Linux/Mac
sudo apt-get install gcc        # Ubuntu/Debian
sudo yum install gcc            # CentOS/RHEL
brew install gcc                # macOS

# Windows
# Install MinGW or use WSL (Windows Subsystem for Linux)
```

## Compilation & Execution

```bash
# Basic compilation
gcc program.c -o program
./program

# With warnings enabled (ALWAYS USE IN INTERVIEWS)
gcc -Wall -Wextra -o program program.c
./program

# With debugging symbols
gcc -g -o program program.c
gdb ./program

# With optimization
gcc -O2 -o program program.c
```

## Hello World

```c
#include <stdio.h>

int main() {
    printf("Hello, World!\n");
    return 0;
}
```

**Compilation:**
```bash
gcc hello.c -o hello
./hello
```

---

# Basic Syntax & Structure

## Program Structure

```c
/* 
 * Multi-line comment
 * Program structure demonstration
 */

// Single-line comment (C99 onwards)

#include <stdio.h>      // Preprocessor directive
#include <stdlib.h>

#define MAX 100         // Macro definition

int globalVar = 10;     // Global variable

// Function declaration
int add(int a, int b);

// Main function - entry point
int main() {
    int localVar = 20;  // Local variable
    
    printf("Global: %d, Local: %d\n", globalVar, localVar);
    
    int result = add(5, 3);
    printf("Sum: %d\n", result);
    
    return 0;           // Return status to OS
}

// Function definition
int add(int a, int b) {
    return a + b;
}
```

## Header Files

```c
// Common standard headers
#include <stdio.h>      // Standard I/O
#include <stdlib.h>     // Memory allocation, conversion
#include <string.h>     // String operations
#include <math.h>       // Mathematical functions
#include <time.h>       // Time functions
#include <ctype.h>      // Character type functions
#include <limits.h>     // Integer limits
#include <float.h>      // Float limits
#include <stdbool.h>    // Boolean type (C99)
#include <stdint.h>     // Fixed-width integers (C99)
```

---

# Data Types & Variables

## Primitive Data Types

```c
#include <stdio.h>
#include <limits.h>
#include <float.h>

int main() {
    // ═══════════════════════════════════════════════════
    // INTEGER TYPES
    // ═══════════════════════════════════════════════════
    
    char c = 'A';                    // 1 byte, -128 to 127
    unsigned char uc = 255;          // 1 byte, 0 to 255
    
    short s = 32000;                 // 2 bytes, -32768 to 32767
    unsigned short us = 65000;       // 2 bytes, 0 to 65535
    
    int i = 2147483647;              // 4 bytes (usually)
    unsigned int ui = 4294967295U;   // 4 bytes, 0 to 4294967295
    
    long l = 2147483647L;            // 4 or 8 bytes (platform dependent)
    unsigned long ul = 4294967295UL; // 4 or 8 bytes
    
    long long ll = 9223372036854775807LL;  // 8 bytes (C99)
    unsigned long long ull = 18446744073709551615ULL;
    
    // ═══════════════════════════════════════════════════
    // FLOATING POINT TYPES
    // ═══════════════════════════════════════════════════
    
    float f = 3.14f;                 // 4 bytes, ~7 decimal digits
    double d = 3.141592653589793;    // 8 bytes, ~15 decimal digits
    long double ld = 3.141592653589793238L;  // 10-16 bytes
    
    // ═══════════════════════════════════════════════════
    // BOOLEAN (C99)
    // ═══════════════════════════════════════════════════
    
    _Bool b1 = 1;                    // 0 or 1
    // OR with stdbool.h:
    // bool b2 = true;
    
    // ═══════════════════════════════════════════════════
    // PRINT SIZES
    // ═══════════════════════════════════════════════════
    
    printf("Size of char: %zu bytes\n", sizeof(char));
    printf("Size of int: %zu bytes\n", sizeof(int));
    printf("Size of long: %zu bytes\n", sizeof(long));
    printf("Size of long long: %zu bytes\n", sizeof(long long));
    printf("Size of float: %zu bytes\n", sizeof(float));
    printf("Size of double: %zu bytes\n", sizeof(double));
    
    // ═══════════════════════════════════════════════════
    // LIMITS
    // ═══════════════════════════════════════════════════
    
    printf("INT_MIN: %d\n", INT_MIN);
    printf("INT_MAX: %d\n", INT_MAX);
    printf("LONG_MIN: %ld\n", LONG_MIN);
    printf("LONG_MAX: %ld\n", LONG_MAX);
    
    return 0;
}
```

## Type Modifiers

```c
// Signed vs Unsigned
signed int x = -100;      // Can be negative
unsigned int y = 100;     // Only positive

// Short vs Long
short int a = 10;         // Shorter range
long int b = 10L;         // Longer range

// Can omit 'int' keyword
short a = 10;
long b = 10L;
unsigned c = 10U;
```

## Constants

```c
// Using const keyword
const int MAX_SIZE = 100;
const float PI = 3.14159f;

// Using #define (preprocessor)
#define BUFFER_SIZE 256
#define NEWLINE '\n'

// Enumeration
enum Day {
    SUNDAY,      // 0
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
```

## Type Casting

```c
int main() {
    // ═══════════════════════════════════════════════════
    // IMPLICIT CASTING (Automatic)
    // ═══════════════════════════════════════════════════
    
    int i = 10;
    float f = i;              // int → float (no data loss)
    printf("%f\n", f);        // 10.000000
    
    // ═══════════════════════════════════════════════════
    // EXPLICIT CASTING (Manual)
    // ═══════════════════════════════════════════════════
    
    float x = 9.8f;
    int y = (int)x;           // float → int (data loss: .8)
    printf("%d\n", y);        // 9
    
    // ═══════════════════════════════════════════════════
    // COMMON CASTING SCENARIOS
    // ═══════════════════════════════════════════════════
    
    // Integer division
    int a = 5, b = 2;
    float result1 = a / b;                  // 2.0 (int division first!)
    float result2 = (float)a / b;           // 2.5 (correct)
    printf("Result1: %f, Result2: %f\n", result1, result2);
    
    // Character to ASCII
    char c = 'A';
    int ascii = (int)c;                     // 65
    printf("ASCII of %c: %d\n", c, ascii);
    
    // Pointer casting
    int num = 42;
    void* ptr = &num;
    int* intPtr = (int*)ptr;
    printf("Value: %d\n", *intPtr);
    
    return 0;
}
```

---

# Operators

## Arithmetic Operators

```c
int main() {
    int a = 10, b = 3;
    
    printf("Addition: %d\n", a + b);        // 13
    printf("Subtraction: %d\n", a - b);     // 7
    printf("Multiplication: %d\n", a * b);  // 30
    printf("Division: %d\n", a / b);        // 3 (integer division)
    printf("Modulus: %d\n", a % b);         // 1 (remainder)
    
    // Integer vs Float division
    float c = (float)a / b;
    printf("Float division: %.2f\n", c);    // 3.33
    
    // Increment/Decrement
    int x = 5;
    printf("x++: %d\n", x++);  // Prints 5, then x becomes 6
    printf("++x: %d\n", ++x);  // x becomes 7, then prints 7
    
    int y = 5;
    printf("y--: %d\n", y--);  // Prints 5, then y becomes 4
    printf("--y: %d\n", --y);  // y becomes 3, then prints 3
    
    return 0;
}
```

## Relational Operators

```c
int main() {
    int a = 10, b = 20;
    
    printf("a == b: %d\n", a == b);  // 0 (false)
    printf("a != b: %d\n", a != b);  // 1 (true)
    printf("a > b: %d\n", a > b);    // 0 (false)
    printf("a < b: %d\n", a < b);    // 1 (true)
    printf("a >= b: %d\n", a >= b);  // 0 (false)
    printf("a <= b: %d\n", a <= b);  // 1 (true)
    
    return 0;
}
```

## Logical Operators

```c
int main() {
    int a = 1, b = 0;  // 1 = true, 0 = false
    
    printf("a && b: %d\n", a && b);  // 0 (AND)
    printf("a || b: %d\n", a || b);  // 1 (OR)
    printf("!a: %d\n", !a);          // 0 (NOT)
    
    // Short-circuit evaluation
    int x = 5, y = 0;
    if (y != 0 && x / y > 1) {  // Second part not evaluated!
        printf("This won't crash\n");
    }
    
    return 0;
}
```

## Bitwise Operators

```c
int main() {
    unsigned int a = 60;  // 0011 1100
    unsigned int b = 13;  // 0000 1101
    
    printf("a & b: %u\n", a & b);   // 12 (0000 1100) AND
    printf("a | b: %u\n", a | b);   // 61 (0011 1101) OR
    printf("a ^ b: %u\n", a ^ b);   // 49 (0011 0001) XOR
    printf("~a: %u\n", ~a);         // Bitwise NOT
    printf("a << 2: %u\n", a << 2); // 240 (left shift)
    printf("a >> 2: %u\n", a >> 2); // 15 (right shift)
    
    return 0;
}
```

## Assignment Operators

```c
int main() {
    int a = 10;
    
    a += 5;   // a = a + 5;  → 15
    a -= 3;   // a = a - 3;  → 12
    a *= 2;   // a = a * 2;  → 24
    a /= 4;   // a = a / 4;  → 6
    a %= 4;   // a = a % 4;  → 2
    
    // Bitwise compound assignment
    a &= 3;   // a = a & 3;
    a |= 4;   // a = a | 4;
    a ^= 2;   // a = a ^ 2;
    a <<= 1;  // a = a << 1;
    a >>= 1;  // a = a >> 1;
    
    return 0;
}
```

## Conditional (Ternary) Operator

```c
int main() {
    int a = 10, b = 20;
    
    // condition ? value_if_true : value_if_false
    int max = (a > b) ? a : b;
    printf("Max: %d\n", max);  // 20
    
    // Nested ternary (use sparingly!)
    int x = 5;
    char* result = (x > 0) ? "positive" : 
                   (x < 0) ? "negative" : "zero";
    printf("%s\n", result);
    
    return 0;
}
```

## Operator Precedence (Highest to Lowest)

```c
/*
 * OPERATOR PRECEDENCE TABLE
 * 
 * Priority  Operators              Description
 * ════════  ═══════════════════════════════════════════════
 * 1         ()  []  ->  .          Postfix
 * 2         ++  --  !  ~  +  -  *  Unary (prefix)
 * 3         *  /  %                Multiplicative
 * 4         +  -                   Additive
 * 5         <<  >>                 Bitwise shift
 * 6         <  <=  >  >=           Relational
 * 7         ==  !=                 Equality
 * 8         &                      Bitwise AND
 * 9         ^                      Bitwise XOR
 * 10        |                      Bitwise OR
 * 11        &&                     Logical AND
 * 12        ||                     Logical OR
 * 13        ?:                     Ternary
 * 14        =  +=  -=  etc.        Assignment
 * 15        ,                      Comma
 */

int main() {
    int a = 10, b = 5, c = 2;
    
    // Example: 10 + 5 * 2 = 10 + 10 = 20 (not 30!)
    int result = a + b * c;
    printf("%d\n", result);  // 20
    
    // Use parentheses for clarity
    int result2 = (a + b) * c;
    printf("%d\n", result2);  // 30
    
    return 0;
}
```

---

# Input/Output

## printf() - Formatted Output

```c
#include <stdio.h>

int main() {
    // ═══════════════════════════════════════════════════
    // BASIC FORMAT SPECIFIERS
    // ═══════════════════════════════════════════════════
    
    int i = 42;
    unsigned int u = 42;
    float f = 3.14159f;
    double d = 3.14159265359;
    char c = 'A';
    char str[] = "Hello";
    void* ptr = &i;
    
    printf("Integer: %d\n", i);
    printf("Unsigned: %u\n", u);
    printf("Hexadecimal: %x\n", i);
    printf("Octal: %o\n", i);
    printf("Float: %f\n", f);
    printf("Double: %lf\n", d);
    printf("Character: %c\n", c);
    printf("String: %s\n", str);
    printf("Pointer: %p\n", ptr);
    
    // ═══════════════════════════════════════════════════
    // WIDTH AND PRECISION
    // ═══════════════════════════════════════════════════
    
    printf("%5d\n", 42);       // "   42" (right-aligned, width 5)
    printf("%-5d\n", 42);      // "42   " (left-aligned)
    printf("%05d\n", 42);      // "00042" (zero-padded)
    
    printf("%.2f\n", 3.14159); // "3.14" (2 decimal places)
    printf("%10.2f\n", 3.14);  // "      3.14" (width 10, precision 2)
    
    // ═══════════════════════════════════════════════════
    // LONG AND LONG LONG
    // ═══════════════════════════════════════════════════
    
    long l = 1234567890L;
    long long ll = 1234567890123456789LL;
    
    printf("Long: %ld\n", l);
    printf("Long long: %lld\n", ll);
    
    // ═══════════════════════════════════════════════════
    // SIZE_T (for sizeof results)
    // ═══════════════════════════════════════════════════
    
    printf("Size: %zu bytes\n", sizeof(int));
    
    return 0;
}
```

## scanf() - Formatted Input

```c
#include <stdio.h>

int main() {
    int age;
    float height;
    char name[50];
    
    // ═══════════════════════════════════════════════════
    // BASIC INPUT
    // ═══════════════════════════════════════════════════
    
    printf("Enter age: ");
    scanf("%d", &age);  // Note: & (address-of operator)
    
    printf("Enter height: ");
    scanf("%f", &height);
    
    // ═══════════════════════════════════════════════════
    // STRING INPUT
    // ═══════════════════════════════════════════════════
    
    printf("Enter name: ");
    scanf("%s", name);  // No & for arrays!
    
    // Safer: limit input length
    scanf("%49s", name);  // Read at most 49 chars
    
    // ═══════════════════════════════════════════════════
    // MULTIPLE INPUTS
    // ═══════════════════════════════════════════════════
    
    int x, y, z;
    printf("Enter three numbers: ");
    scanf("%d %d %d", &x, &y, &z);
    
    // ═══════════════════════════════════════════════════
    // CLEAR INPUT BUFFER
    // ═══════════════════════════════════════════════════
    
    int num;
    char ch;
    
    printf("Enter number: ");
    scanf("%d", &num);
    
    // Clear newline left by scanf
    while (getchar() != '\n');
    
    printf("Enter character: ");
    scanf("%c", &ch);
    
    return 0;
}
```

## Other I/O Functions

```c
#include <stdio.h>

int main() {
    char str[100];
    char ch;
    
    // ═══════════════════════════════════════════════════
    // CHARACTER I/O
    // ═══════════════════════════════════════════════════
    
    printf("Enter a character: ");
    ch = getchar();  // Read single character
    putchar(ch);     // Print single character
    putchar('\n');
    
    // ═══════════════════════════════════════════════════
    // STRING I/O
    // ═══════════════════════════════════════════════════
    
    printf("Enter a line: ");
    gets(str);   // DEPRECATED! Unsafe!
    
    // Use fgets instead (safer)
    fgets(str, sizeof(str), stdin);
    puts(str);   // Print string with newline
    
    // Remove trailing newline from fgets
    str[strcspn(str, "\n")] = '\0';
    
    return 0;
}
```

---

# Control Flow

## if-else Statements

```c
#include <stdio.h>

int main() {
    int age;
    printf("Enter age: ");
    scanf("%d", &age);
    
    // ═══════════════════════════════════════════════════
    // SIMPLE IF
    // ═══════════════════════════════════════════════════
    
    if (age >= 18) {
        printf("You are an adult.\n");
    }
    
    // ═══════════════════════════════════════════════════
    // IF-ELSE
    // ═══════════════════════════════════════════════════
    
    if (age >= 18) {
        printf("Adult\n");
    } else {
        printf("Minor\n");
    }
    
    // ═══════════════════════════════════════════════════
    // IF-ELSE IF-ELSE
    // ═══════════════════════════════════════════════════
    
    if (age < 13) {
        printf("Child\n");
    } else if (age < 20) {
        printf("Teenager\n");
    } else if (age < 60) {
        printf("Adult\n");
    } else {
        printf("Senior\n");
    }
    
    // ═══════════════════════════════════════════════════
    // NESTED IF
    // ═══════════════════════════════════════════════════
    
    int marks;
    printf("Enter marks: ");
    scanf("%d", &marks);
    
    if (marks >= 40) {
        if (marks >= 90) {
            printf("Grade A+\n");
        } else if (marks >= 80) {
            printf("Grade A\n");
        } else if (marks >= 70) {
            printf("Grade B\n");
        } else {
            printf("Grade C\n");
        }
    } else {
        printf("Fail\n");
    }
    
    return 0;
}
```

## switch Statement

```c
#include <stdio.h>

int main() {
    int day;
    printf("Enter day (1-7): ");
    scanf("%d", &day);
    
    // ═══════════════════════════════════════════════════
    // BASIC SWITCH
    // ═══════════════════════════════════════════════════
    
    switch (day) {
        case 1:
            printf("Monday\n");
            break;
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
        default:
            printf("Invalid day\n");
    }
    
    // ═══════════════════════════════════════════════════
    // FALL-THROUGH (no break)
    // ═══════════════════════════════════════════════════
    
    switch (day) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            printf("Weekday\n");
            break;
        case 6:
        case 7:
            printf("Weekend\n");
            break;
        default:
            printf("Invalid\n");
    }
    
    // ═══════════════════════════════════════════════════
    // SWITCH WITH CHAR
    // ═══════════════════════════════════════════════════
    
    char grade;
    printf("Enter grade: ");
    scanf(" %c", &grade);  // Space before %c to skip whitespace
    
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

## Loops

### for Loop

```c
#include <stdio.h>

int main() {
    // ═══════════════════════════════════════════════════
    // BASIC FOR LOOP
    // ═══════════════════════════════════════════════════
    
    for (int i = 0; i < 5; i++) {
        printf("%d ", i);  // 0 1 2 3 4
    }
    printf("\n");
    
    // ═══════════════════════════════════════════════════
    // REVERSE LOOP
    // ═══════════════════════════════════════════════════
    
    for (int i = 5; i > 0; i--) {
        printf("%d ", i);  // 5 4 3 2 1
    }
    printf("\n");
    
    // ═══════════════════════════════════════════════════
    // STEP BY 2
    // ═══════════════════════════════════════════════════
    
    for (int i = 0; i < 10; i += 2) {
        printf("%d ", i);  // 0 2 4 6 8
    }
    printf("\n");
    
    // ═══════════════════════════════════════════════════
    // MULTIPLE VARIABLES
    // ═══════════════════════════════════════════════════
    
    for (int i = 0, j = 10; i < j; i++, j--) {
        printf("i=%d j=%d\n", i, j);
    }
    
    // ═══════════════════════════════════════════════════
    // NESTED LOOPS
    // ═══════════════════════════════════════════════════
    
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            printf("(%d,%d) ", i, j);
        }
        printf("\n");
    }
    
    // ═══════════════════════════════════════════════════
    // INFINITE LOOP (use with break)
    // ═══════════════════════════════════════════════════
    
    for (;;) {
        printf("Enter 0 to exit: ");
        int n;
        scanf("%d", &n);
        if (n == 0) break;
    }
    
    return 0;
}
```

### while Loop

```c
#include <stdio.h>

int main() {
    // ═══════════════════════════════════════════════════
    // BASIC WHILE
    // ═══════════════════════════════════════════════════
    
    int i = 0;
    while (i < 5) {
        printf("%d ", i);
        i++;
    }
    printf("\n");
    
    // ═══════════════════════════════════════════════════
    // INPUT VALIDATION
    // ═══════════════════════════════════════════════════
    
    int age;
    printf("Enter age (1-100): ");
    scanf("%d", &age);
    
    while (age < 1 || age > 100) {
        printf("Invalid! Enter again: ");
        scanf("%d", &age);
    }
    
    // ═══════════════════════════════════════════════════
    // SENTINEL-CONTROLLED LOOP
    // ═══════════════════════════════════════════════════
    
    int num;
    int sum = 0;
    
    printf("Enter numbers (0 to stop):\n");
    scanf("%d", &num);
    
    while (num != 0) {
        sum += num;
        scanf("%d", &num);
    }
    
    printf("Sum: %d\n", sum);
    
    return 0;
}
```

### do-while Loop

```c
#include <stdio.h>

int main() {
    // ═══════════════════════════════════════════════════
    // BASIC DO-WHILE (executes at least once)
    // ═══════════════════════════════════════════════════
    
    int i = 0;
    do {
        printf("%d ", i);
        i++;
    } while (i < 5);
    printf("\n");
    
    // ═══════════════════════════════════════════════════
    // MENU-DRIVEN PROGRAM
    // ═══════════════════════════════════════════════════
    
    int choice;
    
    do {
        printf("\n=== MENU ===\n");
        printf("1. Add\n");
        printf("2. Subtract\n");
        printf("3. Multiply\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Addition selected\n");
                break;
            case 2:
                printf("Subtraction selected\n");
                break;
            case 3:
                printf("Multiplication selected\n");
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 4);
    
    return 0;
}
```

## break and continue

```c
#include <stdio.h>

int main() {
    // ═══════════════════════════════════════════════════
    // BREAK - Exit loop immediately
    // ═══════════════════════════════════════════════════
    
    for (int i = 0; i < 10; i++) {
        if (i == 5) {
            break;  // Exit loop when i is 5
        }
        printf("%d ", i);  // 0 1 2 3 4
    }
    printf("\n");
    
    // ═══════════════════════════════════════════════════
    // CONTINUE - Skip to next iteration
    // ═══════════════════════════════════════════════════
    
    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            continue;  // Skip even numbers
        }
        printf("%d ", i);  // 1 3 5 7 9
    }
    printf("\n");
    
    // ═══════════════════════════════════════════════════
    // BREAK IN NESTED LOOPS (only breaks inner loop)
    // ═══════════════════════════════════════════════════
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (j == 2) break;  // Breaks inner loop only
            printf("(%d,%d) ", i, j);
        }
        printf("\n");
    }
    
    // ═══════════════════════════════════════════════════
    // FIND FIRST OCCURRENCE
    // ═══════════════════════════════════════════════════
    
    int arr[] = {10, 20, 30, 40, 50};
    int target = 30;
    int found = 0;
    
    for (int i = 0; i < 5; i++) {
        if (arr[i] == target) {
            printf("Found at index %d\n", i);
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("Not found\n");
    }
    
    return 0;
}
```

## goto Statement (Avoid in Modern Code)

```c
#include <stdio.h>

int main() {
    // ═══════════════════════════════════════════════════
    // GOTO - Jump to labeled statement
    // ═══════════════════════════════════════════════════
    
    int i = 0;
    
start:
    printf("%d ", i);
    i++;
    
    if (i < 5) {
        goto start;  // Jump back to 'start' label
    }
    printf("\n");
    
    // ═══════════════════════════════════════════════════
    // BREAK FROM NESTED LOOPS (one valid use case)
    // ═══════════════════════════════════════════════════
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == 1 && j == 1) {
                goto end;  // Break out of both loops
            }
            printf("(%d,%d) ", i, j);
        }
    }
    
end:
    printf("\nExited nested loops\n");
    
    // NOTE: In modern C, avoid goto. Use functions/flags instead.
    
    return 0;
}
```

---

*[Part 1 Complete - Functions, Arrays, Strings, Pointers continue in next section]*
# C Programming Guide - Part 2

# Functions

## Function Basics

```c
#include <stdio.h>

// ═══════════════════════════════════════════════════════════
// FUNCTION DECLARATION (Prototype)
// ═══════════════════════════════════════════════════════════

int add(int a, int b);           // Declaration
void greet(void);                // No parameters
double square(double x);

// ═══════════════════════════════════════════════════════════
// MAIN FUNCTION
// ═══════════════════════════════════════════════════════════

int main() {
    int result = add(5, 3);
    printf("Sum: %d\n", result);
    
    greet();
    
    double sq = square(4.5);
    printf("Square: %.2f\n", sq);
    
    return 0;
}

// ═══════════════════════════════════════════════════════════
// FUNCTION DEFINITIONS
// ═══════════════════════════════════════════════════════════

int add(int a, int b) {
    return a + b;
}

void greet(void) {
    printf("Hello, World!\n");
}

double square(double x) {
    return x * x;
}
```

## Pass by Value vs Pass by Reference

```c
#include <stdio.h>

// ═══════════════════════════════════════════════════════════
// PASS BY VALUE (Copy of value)
// ═══════════════════════════════════════════════════════════

void modifyValue(int x) {
    x = 100;  // Only modifies local copy
    printf("Inside function: %d\n", x);
}

// ═══════════════════════════════════════════════════════════
// PASS BY REFERENCE (Using pointers)
// ═══════════════════════════════════════════════════════════

void modifyReference(int* x) {
    *x = 100;  // Modifies original value
    printf("Inside function: %d\n", *x);
}

// ═══════════════════════════════════════════════════════════
// SWAP FUNCTION
// ═══════════════════════════════════════════════════════════

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int num = 50;
    
    // Pass by value - original unchanged
    modifyValue(num);
    printf("After modifyValue: %d\n", num);  // Still 50
    
    // Pass by reference - original changed
    modifyReference(&num);
    printf("After modifyReference: %d\n", num);  // Now 100
    
    // Swap example
    int x = 10, y = 20;
    printf("Before swap: x=%d, y=%d\n", x, y);
    swap(&x, &y);
    printf("After swap: x=%d, y=%d\n", x, y);
    
    return 0;
}
```

## Recursion

```c
#include <stdio.h>

// ═══════════════════════════════════════════════════════════
// FACTORIAL
// ═══════════════════════════════════════════════════════════

int factorial(int n) {
    if (n <= 1) return 1;         // Base case
    return n * factorial(n - 1);  // Recursive call
}

// ═══════════════════════════════════════════════════════════
// FIBONACCI
// ═══════════════════════════════════════════════════════════

int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// ═══════════════════════════════════════════════════════════
// GCD (Greatest Common Divisor)
// ═══════════════════════════════════════════════════════════

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// ═══════════════════════════════════════════════════════════
// POWER FUNCTION
// ═══════════════════════════════════════════════════════════

int power(int base, int exp) {
    if (exp == 0) return 1;
    return base * power(base, exp - 1);
}

int main() {
    printf("5! = %d\n", factorial(5));         // 120
    printf("fib(7) = %d\n", fibonacci(7));     // 13
    printf("gcd(48, 18) = %d\n", gcd(48, 18)); // 6
    printf("2^5 = %d\n", power(2, 5));         // 32
    
    return 0;
}
```

---

# Arrays

## One-Dimensional Arrays

```c
#include <stdio.h>

int main() {
    // ═══════════════════════════════════════════════════
    // DECLARATION & INITIALIZATION
    // ═══════════════════════════════════════════════════
    
    int arr1[5];                           // Uninitialized
    int arr2[5] = {1, 2, 3, 4, 5};        // Full initialization
    int arr3[5] = {1, 2};                  // Partial (rest = 0)
    int arr4[] = {1, 2, 3, 4, 5};         // Size inferred
    
    // ═══════════════════════════════════════════════════
    // ACCESSING ELEMENTS
    // ═══════════════════════════════════════════════════
    
    arr1[0] = 10;
    arr1[1] = 20;
    printf("arr1[0] = %d\n", arr1[0]);
    
    // ═══════════════════════════════════════════════════
    // ITERATING THROUGH ARRAY
    // ═══════════════════════════════════════════════════
    
    int numbers[5] = {10, 20, 30, 40, 50};
    
    // Method 1: Using index
    for (int i = 0; i < 5; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    
    // Method 2: Using sizeof
    int size = sizeof(numbers) / sizeof(numbers[0]);
    for (int i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    
    // ═══════════════════════════════════════════════════
    // COMMON OPERATIONS
    // ═══════════════════════════════════════════════════
    
    // Sum of elements
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += numbers[i];
    }
    printf("Sum: %d\n", sum);
    
    // Find maximum
    int max = numbers[0];
    for (int i = 1; i < 5; i++) {
        if (numbers[i] > max) {
            max = numbers[i];
        }
    }
    printf("Max: %d\n", max);
    
    // Linear search
    int target = 30;
    int found = -1;
    for (int i = 0; i < 5; i++) {
        if (numbers[i] == target) {
            found = i;
            break;
        }
    }
    printf("Found at index: %d\n", found);
    
    return 0;
}
```

## Multi-Dimensional Arrays

```c
#include <stdio.h>

int main() {
    // ═══════════════════════════════════════════════════
    // 2D ARRAY DECLARATION
    // ═══════════════════════════════════════════════════
    
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    // ═══════════════════════════════════════════════════
    // ACCESSING ELEMENTS
    // ═══════════════════════════════════════════════════
    
    printf("Element at [1][2]: %d\n", matrix[1][2]);  // 7
    
    // ═══════════════════════════════════════════════════
    // ITERATING 2D ARRAY
    // ═══════════════════════════════════════════════════
    
    int rows = 3, cols = 4;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
    
    // ═══════════════════════════════════════════════════
    // 3D ARRAY
    // ═══════════════════════════════════════════════════
    
    int cube[2][3][4] = {
        {{1,2,3,4}, {5,6,7,8}, {9,10,11,12}},
        {{13,14,15,16}, {17,18,19,20}, {21,22,23,24}}
    };
    
    printf("cube[1][2][3] = %d\n", cube[1][2][3]);  // 24
    
    return 0;
}
```

## Passing Arrays to Functions

```c
#include <stdio.h>

// ═══════════════════════════════════════════════════════════
// 1D ARRAY AS PARAMETER
// ═══════════════════════════════════════════════════════════

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int sumArray(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

// ═══════════════════════════════════════════════════════════
// 2D ARRAY AS PARAMETER (must specify column size)
// ═══════════════════════════════════════════════════════════

void print2DArray(int arr[][4], int rows) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    printArray(numbers, size);
    printf("Sum: %d\n", sumArray(numbers, size));
    
    int matrix[3][4] = {{1,2,3,4}, {5,6,7,8}, {9,10,11,12}};
    print2DArray(matrix, 3);
    
    return 0;
}
```

---

# Strings

## String Basics

```c
#include <stdio.h>
#include <string.h>

int main() {
    // ═══════════════════════════════════════════════════
    // STRING DECLARATION
    // ═══════════════════════════════════════════════════
    
    char str1[] = "Hello";              // Array notation
    char str2[20] = "World";            // With size
    char str3[] = {'H','e','l','l','o','\0'};  // Character by character
    
    // ═══════════════════════════════════════════════════
    // STRING INPUT/OUTPUT
    // ═══════════════════════════════════════════════════
    
    char name[50];
    
    printf("Enter name: ");
    scanf("%s", name);           // Stops at whitespace
    printf("Hello, %s!\n", name);
    
    // Reading line with spaces
    printf("Enter full name: ");
    scanf(" %[^\n]", name);      // Read until newline
    // OR: fgets(name, sizeof(name), stdin);
    
    // ═══════════════════════════════════════════════════
    // STRING LENGTH
    // ═══════════════════════════════════════════════════
    
    printf("Length: %lu\n", strlen(str1));  // 5
    
    return 0;
}
```

## String Functions

```c
#include <stdio.h>
#include <string.h>

int main() {
    char str1[50] = "Hello";
    char str2[50] = "World";
    char str3[50];
    
    // ═══════════════════════════════════════════════════
    // COPY
    // ═══════════════════════════════════════════════════
    
    strcpy(str3, str1);          // str3 = "Hello"
    strncpy(str3, str1, 3);      // Copy first 3 chars
    
    // ═══════════════════════════════════════════════════
    // CONCATENATION
    // ═══════════════════════════════════════════════════
    
    strcat(str1, str2);          // str1 = "HelloWorld"
    strncat(str1, str2, 3);      // Append first 3 chars
    
    // ═══════════════════════════════════════════════════
    // COMPARISON
    // ═══════════════════════════════════════════════════
    
    int cmp = strcmp("ABC", "ABC");  // 0 (equal)
    cmp = strcmp("ABC", "XYZ");      // < 0 (first < second)
    cmp = strcmp("XYZ", "ABC");      // > 0 (first > second)
    
    // Case-insensitive comparison
    cmp = strcasecmp("Hello", "HELLO");  // 0 (Linux/Mac)
    // Windows: _stricmp
    
    // ═══════════════════════════════════════════════════
    // SEARCH
    // ═══════════════════════════════════════════════════
    
    char text[] = "Hello World";
    
    // Find character
    char* ptr = strchr(text, 'o');        // First 'o'
    printf("Found at: %ld\n", ptr - text);  // 4
    
    ptr = strrchr(text, 'o');             // Last 'o'
    printf("Found at: %ld\n", ptr - text);  // 7
    
    // Find substring
    ptr = strstr(text, "World");
    if (ptr != NULL) {
        printf("Found: %s\n", ptr);
    }
    
    // ═══════════════════════════════════════════════════
    // TOKENIZATION
    // ═══════════════════════════════════════════════════
    
    char sentence[] = "Hello,World,C,Programming";
    char* token = strtok(sentence, ",");
    
    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, ",");
    }
    
    return 0;
}
```

## Custom String Functions

```c
#include <stdio.h>

// ═══════════════════════════════════════════════════════════
// STRING LENGTH
// ═══════════════════════════════════════════════════════════

int stringLength(char* str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

// ═══════════════════════════════════════════════════════════
// STRING COPY
// ═══════════════════════════════════════════════════════════

void stringCopy(char* dest, char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// ═══════════════════════════════════════════════════════════
// STRING COMPARISON
// ═══════════════════════════════════════════════════════════

int stringCompare(char* s1, char* s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) {
            return s1[i] - s2[i];
        }
        i++;
    }
    return s1[i] - s2[i];
}

// ═══════════════════════════════════════════════════════════
// STRING REVERSE
// ═══════════════════════════════════════════════════════════

void stringReverse(char* str) {
    int len = stringLength(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

int main() {
    char str1[50] = "Hello";
    char str2[50];
    
    printf("Length: %d\n", stringLength(str1));
    
    stringCopy(str2, str1);
    printf("Copied: %s\n", str2);
    
    printf("Compare: %d\n", stringCompare("ABC", "ABC"));
    
    stringReverse(str1);
    printf("Reversed: %s\n", str1);
    
    return 0;
}
```

---

# Pointers

## Pointer Basics

```c
#include <stdio.h>

int main() {
    // ═══════════════════════════════════════════════════
    // POINTER DECLARATION & INITIALIZATION
    // ═══════════════════════════════════════════════════
    
    int x = 10;
    int* ptr = &x;    // ptr stores address of x
    
    printf("Value of x: %d\n", x);
    printf("Address of x: %p\n", &x);
    printf("Value of ptr: %p\n", ptr);
    printf("Value at ptr: %d\n", *ptr);  // Dereferencing
    
    // ═══════════════════════════════════════════════════
    // MODIFYING THROUGH POINTER
    // ═══════════════════════════════════════════════════
    
    *ptr = 20;  // Changes x to 20
    printf("New value of x: %d\n", x);
    
    // ═══════════════════════════════════════════════════
    // NULL POINTER
    // ═══════════════════════════════════════════════════
    
    int* nullPtr = NULL;
    if (nullPtr == NULL) {
        printf("Pointer is null\n");
    }
    
    // ═══════════════════════════════════════════════════
    // POINTER ARITHMETIC
    // ═══════════════════════════════════════════════════
    
    int arr[] = {10, 20, 30, 40, 50};
    int* p = arr;  // Points to first element
    
    printf("*p = %d\n", *p);      // 10
    printf("*(p+1) = %d\n", *(p+1)); // 20
    printf("*(p+2) = %d\n", *(p+2)); // 30
    
    p++;  // Move to next element
    printf("*p after increment: %d\n", *p);  // 20
    
    return 0;
}
```

## Pointers and Arrays

```c
#include <stdio.h>

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int* ptr = arr;  // Array name is a pointer
    
    // ═══════════════════════════════════════════════════
    // ARRAY ACCESS USING POINTERS
    // ═══════════════════════════════════════════════════
    
    // Method 1: Array notation
    printf("%d %d %d\n", arr[0], arr[1], arr[2]);
    
    // Method 2: Pointer notation
    printf("%d %d %d\n", *ptr, *(ptr+1), *(ptr+2));
    
    // Method 3: Array with pointer
    printf("%d %d %d\n", ptr[0], ptr[1], ptr[2]);
    
    // ═══════════════════════════════════════════════════
    // ITERATING WITH POINTERS
    // ═══════════════════════════════════════════════════
    
    int size = sizeof(arr) / sizeof(arr[0]);
    
    for (int i = 0; i < size; i++) {
        printf("%d ", *(ptr + i));
    }
    printf("\n");
    
    // Using pointer increment
    ptr = arr;  // Reset pointer
    for (int i = 0; i < size; i++) {
        printf("%d ", *ptr);
        ptr++;
    }
    printf("\n");
    
    return 0;
}
```

## Pointer to Pointer

```c
#include <stdio.h>

int main() {
    int x = 100;
    int* ptr1 = &x;        // Pointer to int
    int** ptr2 = &ptr1;    // Pointer to pointer
    
    printf("x = %d\n", x);
    printf("*ptr1 = %d\n", *ptr1);
    printf("**ptr2 = %d\n", **ptr2);
    
    // Modify through double pointer
    **ptr2 = 200;
    printf("x after modification: %d\n", x);
    
    return 0;
}
```

## Function Pointers

```c
#include <stdio.h>

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

int main() {
    // ═══════════════════════════════════════════════════
    // FUNCTION POINTER DECLARATION
    // ═══════════════════════════════════════════════════
    
    int (*operation)(int, int);  // Pointer to function
    
    // ═══════════════════════════════════════════════════
    // USING FUNCTION POINTER
    // ═══════════════════════════════════════════════════
    
    operation = add;
    printf("10 + 5 = %d\n", operation(10, 5));
    
    operation = subtract;
    printf("10 - 5 = %d\n", operation(10, 5));
    
    operation = multiply;
    printf("10 * 5 = %d\n", operation(10, 5));
    
    return 0;
}
```

---

# Structures & Unions

## Structures

```c
#include <stdio.h>
#include <string.h>

// ═══════════════════════════════════════════════════════════
// STRUCTURE DEFINITION
// ═══════════════════════════════════════════════════════════

struct Student {
    int id;
    char name[50];
    float marks;
};

// Using typedef
typedef struct {
    int x;
    int y;
} Point;

int main() {
    // ═══════════════════════════════════════════════════
    // STRUCTURE VARIABLE DECLARATION
    // ═══════════════════════════════════════════════════
    
    struct Student s1;
    Point p1;
    
    // ═══════════════════════════════════════════════════
    // INITIALIZATION
    // ═══════════════════════════════════════════════════
    
    // Method 1: Member-by-member
    s1.id = 101;
    strcpy(s1.name, "Alice");
    s1.marks = 85.5;
    
    // Method 2: During declaration
    struct Student s2 = {102, "Bob", 90.0};
    
    // Method 3: Designated initializers (C99)
    struct Student s3 = {.id = 103, .name = "Charlie", .marks = 88.0};
    
    // ═══════════════════════════════════════════════════
    // ACCESSING MEMBERS
    // ═══════════════════════════════════════════════════
    
    printf("ID: %d, Name: %s, Marks: %.2f\n", s1.id, s1.name, s1.marks);
    
    // ═══════════════════════════════════════════════════
    // ARRAY OF STRUCTURES
    // ═══════════════════════════════════════════════════
    
    struct Student students[3] = {
        {101, "Alice", 85.5},
        {102, "Bob", 90.0},
        {103, "Charlie", 88.0}
    };
    
    for (int i = 0; i < 3; i++) {
        printf("%d: %s - %.2f\n", 
               students[i].id, students[i].name, students[i].marks);
    }
    
    // ═══════════════════════════════════════════════════
    // POINTER TO STRUCTURE
    // ═══════════════════════════════════════════════════
    
    struct Student* ptr = &s1;
    
    // Access using pointer
    printf("ID: %d\n", (*ptr).id);   // Method 1
    printf("Name: %s\n", ptr->name); // Method 2 (arrow operator)
    
    // ═══════════════════════════════════════════════════
    // NESTED STRUCTURES
    // ═══════════════════════════════════════════════════
    
    struct Date {
        int day, month, year;
    };
    
    struct Employee {
        int id;
        char name[50];
        struct Date joinDate;
    };
    
    struct Employee emp = {101, "John", {15, 6, 2023}};
    printf("Joined: %d/%d/%d\n", 
           emp.joinDate.day, emp.joinDate.month, emp.joinDate.year);
    
    return 0;
}
```

## Unions

```c
#include <stdio.h>

// ═══════════════════════════════════════════════════════════
// UNION DEFINITION (Shares memory among members)
// ═══════════════════════════════════════════════════════════

union Data {
    int i;
    float f;
    char str[20];
};

int main() {
    union Data data;
    
    // ═══════════════════════════════════════════════════
    // USING UNION
    // ═══════════════════════════════════════════════════
    
    data.i = 10;
    printf("data.i: %d\n", data.i);
    
    data.f = 3.14;  // Overwrites previous value!
    printf("data.f: %f\n", data.f);
    printf("data.i: %d\n", data.i);  // Garbage now!
    
    // ═══════════════════════════════════════════════════
    // SIZE COMPARISON
    // ═══════════════════════════════════════════════════
    
    struct Example1 {
        int i;
        float f;
        char c;
    };
    
    union Example2 {
        int i;
        float f;
        char c;
    };
    
    printf("Size of struct: %zu\n", sizeof(struct Example1));  // 12
    printf("Size of union: %zu\n", sizeof(union Example2));    // 4
    
    return 0;
}
```

---

# Dynamic Memory Allocation

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // ═══════════════════════════════════════════════════
    // malloc() - Allocate memory
    // ═══════════════════════════════════════════════════
    
    int* ptr1 = (int*)malloc(5 * sizeof(int));
    if (ptr1 == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    for (int i = 0; i < 5; i++) {
        ptr1[i] = i * 10;
        printf("%d ", ptr1[i]);
    }
    printf("\n");
    
    // ═══════════════════════════════════════════════════
    // calloc() - Allocate and initialize to zero
    // ═══════════════════════════════════════════════════
    
    int* ptr2 = (int*)calloc(5, sizeof(int));
    if (ptr2 == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    for (int i = 0; i < 5; i++) {
        printf("%d ", ptr2[i]);  // All zeros
    }
    printf("\n");
    
    // ═══════════════════════════════════════════════════
    // realloc() - Resize allocated memory
    // ═══════════════════════════════════════════════════
    
    ptr1 = (int*)realloc(ptr1, 10 * sizeof(int));
    if (ptr1 == NULL) {
        printf("Reallocation failed!\n");
        return 1;
    }
    
    for (int i = 5; i < 10; i++) {
        ptr1[i] = i * 10;
    }
    
    for (int i = 0; i < 10; i++) {
        printf("%d ", ptr1[i]);
    }
    printf("\n");
    
    // ═══════════════════════════════════════════════════
    // free() - Deallocate memory (ALWAYS DO THIS!)
    // ═══════════════════════════════════════════════════
    
    free(ptr1);
    free(ptr2);
    ptr1 = NULL;  // Good practice
    ptr2 = NULL;
    
    // ═══════════════════════════════════════════════════
    // DYNAMIC 2D ARRAY
    // ═══════════════════════════════════════════════════
    
    int rows = 3, cols = 4;
    int** matrix = (int**)malloc(rows * sizeof(int*));
    
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }
    
    // Use matrix
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = i * cols + j;
            printf("%2d ", matrix[i][j]);
        }
        printf("\n");
    }
    
    // Free matrix
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    
    return 0;
}
```

---

# File Handling

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE* fp;
    
    // ═══════════════════════════════════════════════════
    // WRITING TO FILE
    // ═══════════════════════════════════════════════════
    
    fp = fopen("output.txt", "w");  // Write mode
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    
    fprintf(fp, "Hello, File!\n");
    fprintf(fp, "Number: %d\n", 42);
    fputs("Another line\n", fp);
    fputc('A', fp);
    
    fclose(fp);
    
    // ═══════════════════════════════════════════════════
    // READING FROM FILE
    // ═══════════════════════════════════════════════════
    
    fp = fopen("output.txt", "r");  // Read mode
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }
    
    fclose(fp);
    
    // ═══════════════════════════════════════════════════
    // APPEND MODE
    // ═══════════════════════════════════════════════════
    
    fp = fopen("output.txt", "a");  // Append mode
    fprintf(fp, "Appended line\n");
    fclose(fp);
    
    // ═══════════════════════════════════════════════════
    // BINARY FILE I/O
    // ═══════════════════════════════════════════════════
    
    int numbers[] = {1, 2, 3, 4, 5};
    
    // Write binary
    fp = fopen("data.bin", "wb");
    fwrite(numbers, sizeof(int), 5, fp);
    fclose(fp);
    
    // Read binary
    int readNumbers[5];
    fp = fopen("data.bin", "rb");
    fread(readNumbers, sizeof(int), 5, fp);
    fclose(fp);
    
    for (int i = 0; i < 5; i++) {
        printf("%d ", readNumbers[i]);
    }
    printf("\n");
    
    return 0;
}
```

---

# Preprocessor Directives

```c
#include <stdio.h>

// ═══════════════════════════════════════════════════════════
// MACRO DEFINITIONS
// ═══════════════════════════════════════════════════════════

#define PI 3.14159
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define SQUARE(x) ((x) * (x))

// ═══════════════════════════════════════════════════════════
// CONDITIONAL COMPILATION
// ═══════════════════════════════════════════════════════════

#define DEBUG 1

#if DEBUG
    #define LOG(msg) printf("DEBUG: %s\n", msg)
#else
    #define LOG(msg)
#endif

// ═══════════════════════════════════════════════════════════
// HEADER GUARDS
// ═══════════════════════════════════════════════════════════

#ifndef MYHEADER_H
#define MYHEADER_H
// ... header content ...
#endif

int main() {
    printf("PI = %f\n", PI);
    printf("MAX(5, 10) = %d\n", MAX(5, 10));
    printf("SQUARE(4) = %d\n", SQUARE(4));
    
    LOG("This is a debug message");
    
    // Predefined macros
    printf("File: %s\n", __FILE__);
    printf("Line: %d\n", __LINE__);
    printf("Date: %s\n", __DATE__);
    printf("Time: %s\n", __TIME__);
    
    return 0;
}
```

---

*[Part 2 Complete - Interview topics continue in Part 3]*
# C Programming Guide - Part 3: Interview Topics

# Time & Space Complexity

## Big O Notation

```c
/*
 * TIME COMPLEXITY EXAMPLES
 * 
 * O(1)      - Constant      - Array access, arithmetic
 * O(log n)  - Logarithmic   - Binary search
 * O(n)      - Linear        - Single loop
 * O(n log n)- Linearithmic  - Merge sort, Quick sort
 * O(n²)     - Quadratic     - Nested loops
 * O(n³)     - Cubic         - Triple nested loops
 * O(2^n)    - Exponential   - Fibonacci (naive)
 * O(n!)     - Factorial     - Permutations
 */

// O(1) - Constant
int getElement(int arr[], int index) {
    return arr[index];
}

// O(n) - Linear
int sumArray(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
}

// O(n²) - Quadratic
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// O(log n) - Logarithmic
int binarySearch(int arr[], int n, int target) {
    int left = 0, right = n - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    
    return -1;
}
```

---

# Common Patterns

## Pattern 1: Two Pointers

```c
#include <stdio.h>

// Pair with given sum in sorted array
int findPair(int arr[], int n, int target) {
    int left = 0, right = n - 1;
    
    while (left < right) {
        int sum = arr[left] + arr[right];
        
        if (sum == target) {
            printf("Pair: %d, %d\n", arr[left], arr[right]);
            return 1;
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }
    
    return 0;
}

// Remove duplicates from sorted array
int removeDuplicates(int arr[], int n) {
    if (n == 0) return 0;
    
    int unique = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] != arr[unique]) {
            unique++;
            arr[unique] = arr[i];
        }
    }
    
    return unique + 1;
}
```

## Pattern 2: Sliding Window

```c
// Maximum sum subarray of size k
int maxSumSubarray(int arr[], int n, int k) {
    if (n < k) return -1;
    
    int windowSum = 0;
    for (int i = 0; i < k; i++) {
        windowSum += arr[i];
    }
    
    int maxSum = windowSum;
    
    for (int i = k; i < n; i++) {
        windowSum += arr[i] - arr[i - k];
        if (windowSum > maxSum) {
            maxSum = windowSum;
        }
    }
    
    return maxSum;
}
```

## Pattern 3: Fast & Slow Pointers (Floyd's Cycle)

```c
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Detect cycle in linked list
int hasCycle(Node* head) {
    if (head == NULL) return 0;
    
    Node* slow = head;
    Node* fast = head;
    
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        
        if (slow == fast) {
            return 1;  // Cycle detected
        }
    }
    
    return 0;
}
```

---

# Bit Manipulation

```c
#include <stdio.h>

// ═══════════════════════════════════════════════════════════
// BASIC BIT OPERATIONS
// ═══════════════════════════════════════════════════════════

// Set bit at position i
int setBit(int num, int i) {
    return num | (1 << i);
}

// Clear bit at position i
int clearBit(int num, int i) {
    return num & ~(1 << i);
}

// Toggle bit at position i
int toggleBit(int num, int i) {
    return num ^ (1 << i);
}

// Check if bit at position i is set
int checkBit(int num, int i) {
    return (num & (1 << i)) != 0;
}

// ═══════════════════════════════════════════════════════════
// COMMON BIT TRICKS
// ═══════════════════════════════════════════════════════════

// Check if number is power of 2
int isPowerOfTwo(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}

// Count set bits (Brian Kernighan's Algorithm)
int countSetBits(int n) {
    int count = 0;
    while (n) {
        n &= (n - 1);  // Removes rightmost set bit
        count++;
    }
    return count;
}

// Find single number (all others appear twice)
int findSingle(int arr[], int n) {
    int result = 0;
    for (int i = 0; i < n; i++) {
        result ^= arr[i];  // XOR cancels duplicates
    }
    return result;
}

// Swap two numbers without temp variable
void swap(int* a, int* b) {
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

// Get rightmost set bit
int getRightmostSetBit(int n) {
    return n & -n;
}

// Turn off rightmost set bit
int turnOffRightmost(int n) {
    return n & (n - 1);
}

// Check if number is odd
int isOdd(int n) {
    return n & 1;
}

// Multiply by 2^k
int multiplyByPowerOf2(int n, int k) {
    return n << k;
}

// Divide by 2^k
int divideByPowerOf2(int n, int k) {
    return n >> k;
}

int main() {
    printf("Set bit 2 in 5: %d\n", setBit(5, 2));        // 7
    printf("Clear bit 2 in 7: %d\n", clearBit(7, 2));    // 3
    printf("Toggle bit 1 in 5: %d\n", toggleBit(5, 1));  // 7
    printf("Check bit 2 in 5: %d\n", checkBit(5, 2));    // 1
    
    printf("Is 16 power of 2? %d\n", isPowerOfTwo(16));  // 1
    printf("Count bits in 7: %d\n", countSetBits(7));    // 3
    
    return 0;
}
```

---

# Recursion

```c
#include <stdio.h>

// ═══════════════════════════════════════════════════════════
// TAIL RECURSION
// ═══════════════════════════════════════════════════════════

// Factorial with tail recursion
int factorialTail(int n, int acc) {
    if (n <= 1) return acc;
    return factorialTail(n - 1, n * acc);
}

int factorial(int n) {
    return factorialTail(n, 1);
}

// ═══════════════════════════════════════════════════════════
// BACKTRACKING
// ═══════════════════════════════════════════════════════════

// Generate all permutations
void permute(int arr[], int l, int r) {
    if (l == r) {
        for (int i = 0; i <= r; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
        return;
    }
    
    for (int i = l; i <= r; i++) {
        // Swap
        int temp = arr[l];
        arr[l] = arr[i];
        arr[i] = temp;
        
        permute(arr, l + 1, r);
        
        // Backtrack
        temp = arr[l];
        arr[l] = arr[i];
        arr[i] = temp;
    }
}

// ═══════════════════════════════════════════════════════════
// DIVIDE AND CONQUER
// ═══════════════════════════════════════════════════════════

// Merge sort
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    
    int L[n1], R[n2];
    
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    
    int i = 0, j = 0, k = l;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}
```

---

# Memory Layout

```c
/*
 * MEMORY LAYOUT OF C PROGRAM
 * 
 * ┌──────────────────────┐  High Address
 * │   Command Line Args  │
 * │   & Environment Vars │
 * ├──────────────────────┤
 * │        Stack         │  ← Grows downward
 * │   (Local variables)  │
 * │   (Function calls)   │
 * ├──────────────────────┤
 * │          ↓           │
 * │                      │
 * │          ↑           │
 * ├──────────────────────┤
 * │        Heap          │  ← Grows upward
 * │   (Dynamic memory)   │
 * ├──────────────────────┤
 * │   Uninitialized Data │
 * │        (BSS)         │
 * │ (Global uninit vars) │
 * ├──────────────────────┤
 * │   Initialized Data   │
 * │ (Global/static vars) │
 * ├──────────────────────┤
 * │   Text (Code)        │
 * │  (Instructions)      │
 * └──────────────────────┘  Low Address
 */

#include <stdio.h>
#include <stdlib.h>

int globalVar = 10;          // Initialized data segment
int uninitVar;               // BSS segment
static int staticVar = 20;   // Initialized data segment

void function() {
    int localVar = 30;       // Stack
    static int staticLocal = 40;  // Initialized data segment
    
    int* heapVar = (int*)malloc(sizeof(int));  // Heap
    *heapVar = 50;
    
    printf("Addresses:\n");
    printf("Global: %p\n", &globalVar);
    printf("Uninit: %p\n", &uninitVar);
    printf("Static: %p\n", &staticVar);
    printf("Local: %p\n", &localVar);
    printf("Static Local: %p\n", &staticLocal);
    printf("Heap: %p\n", heapVar);
    printf("Function: %p\n", function);
    
    free(heapVar);
}
```

---

# Common Pitfalls & Best Practices

## Pitfall 1: Array Index Out of Bounds

```c
// ❌ WRONG
int arr[5];
arr[5] = 10;  // Out of bounds! Undefined behavior

// ✅ CORRECT
int arr[5];
arr[4] = 10;  // Last valid index is n-1
```

## Pitfall 2: Uninitialized Variables

```c
// ❌ WRONG
int x;
printf("%d\n", x);  // Garbage value!

// ✅ CORRECT
int x = 0;
printf("%d\n", x);
```

## Pitfall 3: Memory Leaks

```c
// ❌ WRONG
void function() {
    int* ptr = (int*)malloc(sizeof(int));
    *ptr = 10;
    // No free() - memory leak!
}

// ✅ CORRECT
void function() {
    int* ptr = (int*)malloc(sizeof(int));
    *ptr = 10;
    free(ptr);
    ptr = NULL;
}
```

## Pitfall 4: Dangling Pointers

```c
// ❌ WRONG
int* ptr = (int*)malloc(sizeof(int));
free(ptr);
*ptr = 10;  // Dangling pointer! Undefined behavior

// ✅ CORRECT
int* ptr = (int*)malloc(sizeof(int));
free(ptr);
ptr = NULL;  // Set to NULL after free
if (ptr != NULL) {
    *ptr = 10;
}
```

## Pitfall 5: Buffer Overflow

```c
// ❌ WRONG
char str[5];
scanf("%s", str);  // User can input more than 5 chars!

// ✅ CORRECT
char str[5];
scanf("%4s", str);  // Limit input to 4 chars + null terminator
```

## Pitfall 6: Integer Division

```c
// ❌ WRONG
int a = 5, b = 2;
float result = a / b;  // Result is 2.0 (integer division first!)

// ✅ CORRECT
int a = 5, b = 2;
float result = (float)a / b;  // Result is 2.5
```

## Pitfall 7: Comparing Floats

```c
// ❌ WRONG
float a = 0.1 + 0.1 + 0.1;
if (a == 0.3) {  // Might fail due to floating-point precision!
    printf("Equal\n");
}

// ✅ CORRECT
#include <math.h>
float a = 0.1 + 0.1 + 0.1;
float epsilon = 0.00001;
if (fabs(a - 0.3) < epsilon) {
    printf("Equal\n");
}
```

---

# Interview Questions

## Q1: Reverse a String

```c
void reverseString(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}
```

## Q2: Check if String is Palindrome

```c
int isPalindrome(char* str) {
    int left = 0;
    int right = strlen(str) - 1;
    
    while (left < right) {
        if (str[left] != str[right]) {
            return 0;
        }
        left++;
        right--;
    }
    
    return 1;
}
```

## Q3: Find Maximum in Array

```c
int findMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}
```

## Q4: Rotate Array by K positions

```c
void reverse(int arr[], int start, int end) {
    while (start < end) {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

void rotateArray(int arr[], int n, int k) {
    k = k % n;  // Handle k > n
    reverse(arr, 0, n - 1);
    reverse(arr, 0, k - 1);
    reverse(arr, k, n - 1);
}
```

## Q5: Find Missing Number in Array (1 to n)

```c
int findMissing(int arr[], int n) {
    int expectedSum = (n + 1) * (n + 2) / 2;
    int actualSum = 0;
    
    for (int i = 0; i < n; i++) {
        actualSum += arr[i];
    }
    
    return expectedSum - actualSum;
}
```

## Q6: Remove Duplicates from Sorted Array

```c
int removeDuplicates(int arr[], int n) {
    if (n == 0) return 0;
    
    int unique = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] != arr[unique]) {
            unique++;
            arr[unique] = arr[i];
        }
    }
    
    return unique + 1;
}
```

## Q7: Merge Two Sorted Arrays

```c
void merge(int arr1[], int n1, int arr2[], int n2, int result[]) {
    int i = 0, j = 0, k = 0;
    
    while (i < n1 && j < n2) {
        if (arr1[i] <= arr2[j]) {
            result[k++] = arr1[i++];
        } else {
            result[k++] = arr2[j++];
        }
    }
    
    while (i < n1) result[k++] = arr1[i++];
    while (j < n2) result[k++] = arr2[j++];
}
```

## Q8: Find Second Largest Element

```c
int findSecondLargest(int arr[], int n) {
    if (n < 2) return -1;
    
    int first = arr[0], second = -1;
    
    for (int i = 1; i < n; i++) {
        if (arr[i] > first) {
            second = first;
            first = arr[i];
        } else if (arr[i] > second && arr[i] != first) {
            second = arr[i];
        }
    }
    
    return second;
}
```

## Q9: Check if Array is Sorted

```c
int isSorted(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return 0;
        }
    }
    return 1;
}
```

## Q10: Count Frequency of Elements

```c
void countFrequency(int arr[], int n) {
    int visited[n];
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }
    
    for (int i = 0; i < n; i++) {
        if (visited[i] == 1) continue;
        
        int count = 1;
        for (int j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) {
                count++;
                visited[j] = 1;
            }
        }
        
        printf("%d occurs %d times\n", arr[i], count);
    }
}
```

---

# Practice Strategy

## Phase 1: Fundamentals (Week 1-2)
- Master syntax, data types, operators
- Understand pointers thoroughly
- Practice basic array problems
- Learn string manipulation

## Phase 2: Data Structures (Week 3-4)
- Implement linked list, stack, queue
- Understand structures and unions
- Master dynamic memory allocation
- Practice file handling

## Phase 3: Algorithms (Week 5-6)
- Sorting algorithms (bubble, merge, quick)
- Searching (binary search)
- Recursion and backtracking
- Bit manipulation tricks

## Phase 4: Interview Prep (Week 7-8)
- Solve 50+ coding problems
- Practice pattern recognition
- Time yourself on problems
- Mock interviews

---

# Key Interview Topics Checklist

**Core Concepts:**
- [ ] Pointers and pointer arithmetic
- [ ] Dynamic memory allocation
- [ ] Structures and unions
- [ ] Function pointers
- [ ] Preprocessor directives

**Common Algorithms:**
- [ ] Binary search
- [ ] Merge sort
- [ ] Quick sort
- [ ] Two pointer technique
- [ ] Sliding window

**Bit Manipulation:**
- [ ] Set/clear/toggle bit
- [ ] Check power of 2
- [ ] Count set bits
- [ ] XOR properties

**String Operations:**
- [ ] Reverse string
- [ ] Palindrome check
- [ ] Anagram check
- [ ] String tokenization

**Array Problems:**
- [ ] Rotate array
- [ ] Remove duplicates
- [ ] Find missing number
- [ ] Kadane's algorithm
- [ ] Two sum problem

---

# Final Tips for Interviews

1. **Always check edge cases:**
   - Empty array/string
   - Single element
   - All elements same
   - Negative numbers
   - NULL pointers

2. **Memory management:**
   - Always free allocated memory
   - Check malloc return value
   - Avoid memory leaks

3. **Code clarity:**
   - Use meaningful variable names
   - Add comments for complex logic
   - Follow consistent indentation

4. **Testing:**
   - Test with small inputs first
   - Consider boundary conditions
   - Dry run your code

5. **Communication:**
   - Think aloud during interviews
   - Explain your approach first
   - Ask clarifying questions

---

**End of Complete C Programming Guide for SDE Placements** 🚀
