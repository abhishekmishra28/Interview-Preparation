# Complete C++ Language Revision Notes

## Table of Contents
1. [Introduction & Compilers](#1-introduction--compilers)
2. [Basics of C++](#2-basics-of-c)
3. [Program Structure](#3-program-structure)
4. [Compound Data Types](#4-compound-data-types)
5. [Object-Oriented Programming (Classes)](#5-object-oriented-programming-classes)
6. [Other Language Features](#6-other-language-features)
7. [Standard Library](#7-standard-library)

---

## 1. Introduction & Compilers

### What is C++?
C++ is a powerful, high-performance programming language that extends C with object-oriented features.

**Key Characteristics:**
- **Compiled Language**: Source code is translated directly into machine code before execution
- **Statically Typed**: Variable types are determined at compile-time
- **Multi-Paradigm**: Supports procedural, object-oriented, and generic programming
- **Performance**: Provides low-level memory manipulation and high execution speed
- **Backward Compatible**: Most C code is valid C++ code
- **Standard Library**: Rich set of built-in functions and classes (STL)

**History:**
- Created by Bjarne Stroustrup in 1979 at Bell Labs
- Originally called "C with Classes"
- Renamed to C++ in 1983 (++ is the increment operator)
- Major standards: C++98, C++03, C++11, C++14, C++17, C++20, C++23

### Compilation Process (Detailed)

```
┌─────────────┐
│ Source Code │  .cpp, .h files
│  (Human)    │
└──────┬──────┘
       │
       ▼
┌─────────────┐
│Preprocessor │  Handles #include, #define, #ifdef
└──────┬──────┘
       │
       ▼
┌─────────────┐
│  Compiler   │  Translates to assembly/machine code
│             │  Performs syntax checking and optimization
└──────┬──────┘
       │
       ▼
┌─────────────┐
│ Object Code │  .o (Linux) or .obj (Windows)
│  (Machine)  │  Binary but not yet executable
└──────┬──────┘
       │
       ▼
┌─────────────┐
│   Linker    │  Combines object files
│             │  Links library functions
│             │  Resolves external references
└──────┬──────┘
       │
       ▼
┌─────────────┐
│ Executable  │  .exe (Windows) or no extension (Linux)
│   (Final)   │  Ready to run
└─────────────┘
```

**Compilation Steps Explained:**

1. **Preprocessing**: 
   - Removes comments
   - Expands macros (#define)
   - Includes header files (#include)
   - Handles conditional compilation (#ifdef)
   - Output: Pure C++ code without preprocessor directives

2. **Compilation**:
   - Parses the preprocessed code
   - Checks for syntax errors
   - Performs semantic analysis
   - Generates assembly code
   - Optimizes code (if optimization flags used)
   - Output: Assembly code or object code

3. **Assembly** (sometimes separate):
   - Converts assembly to machine code
   - Output: Object files (.o or .obj)

4. **Linking**:
   - Combines multiple object files
   - Links standard library functions
   - Resolves function calls between files
   - Handles external dependencies
   - Output: Executable program

**Compilation Commands:**

```bash
# GCC/G++ Compilation
g++ program.cpp -o program          # Compile and link
g++ -c file1.cpp -o file1.o         # Compile only (create object)
g++ file1.o file2.o -o program      # Link object files

# With optimization and warnings
g++ -Wall -O2 program.cpp -o program

# C++ standard version
g++ -std=c++17 program.cpp -o program

# Debug information
g++ -g program.cpp -o program
```

### Console Programs
Console programs are text-based applications that interact through command-line interface.

**Characteristics:**
- Use standard input (stdin) for reading data
- Use standard output (stdout) for displaying results
- Use standard error (stderr) for error messages
- Platform-independent (work on Windows, Linux, macOS)
- Fast development and testing
- Lightweight with minimal overhead

**Structure of a Console Program:**
```cpp
#include <iostream>
using namespace std;

int main() {
    // Input
    cout << "Enter your name: ";
    string name;
    getline(cin, name);
    
    // Processing
    string greeting = "Hello, " + name + "!";
    
    // Output
    cout << greeting << endl;
    
    return 0;  // Exit status (0 = success)
}
```

**Standard Streams:**
- `cin` - Standard input (keyboard)
- `cout` - Standard output (screen)
- `cerr` - Standard error (unbuffered)
- `clog` - Standard log (buffered)

### Popular Compilers

#### 1. **GCC (GNU Compiler Collection)**
- **Platform**: Linux, Unix, macOS (via Xcode)
- **Command**: `g++` for C++
- **Features**: 
  - Open source and free
  - Excellent optimization
  - Supports latest C++ standards
  - Cross-platform compilation
- **Installation**:
  ```bash
  # Ubuntu/Debian
  sudo apt-get install g++
  
  # macOS (via Homebrew)
  brew install gcc
  ```

#### 2. **Clang/LLVM**
- **Platform**: Cross-platform (Linux, macOS, Windows)
- **Command**: `clang++`
- **Features**:
  - Fast compilation
  - Excellent error messages
  - Better diagnostics than GCC
  - Used by Apple for Xcode
  - Modular architecture
- **Advantages**: More readable error messages, faster compilation

#### 3. **MSVC (Microsoft Visual C++)**
- **Platform**: Windows
- **IDE**: Visual Studio, VS Code
- **Features**:
  - Integrated debugger
  - Windows API support
  - Excellent IDE integration
  - IntelliSense support
- **Versions**: Community (free), Professional, Enterprise

#### 4. **MinGW (Minimalist GNU for Windows)**
- **Platform**: Windows
- **Purpose**: Port of GCC to Windows
- **Features**:
  - Creates native Windows applications
  - No dependency on external DLLs
  - Lightweight
- **Variants**: MinGW, MinGW-w64 (64-bit support)

#### 5. **Intel C++ Compiler (ICC)**
- **Platform**: Cross-platform
- **Features**:
  - Highly optimized for Intel processors
  - Excellent performance
  - Commercial (paid)

### Integrated Development Environments (IDEs)

**Popular C++ IDEs:**

1. **Visual Studio** (Windows)
   - Professional IDE with debugger
   - IntelliSense code completion
   - Built-in compiler (MSVC)

2. **Code::Blocks** (Cross-platform)
   - Lightweight and free
   - Multiple compiler support
   - Good for beginners

3. **CLion** (Cross-platform)
   - JetBrains product
   - Excellent refactoring tools
   - Commercial but free for students

4. **Eclipse CDT** (Cross-platform)
   - Open source
   - Extensible with plugins
   - Good debugging tools

5. **VS Code** (Cross-platform)
   - Lightweight
   - Extensive extensions
   - Good for modern C++ development

### Compilation Flags and Options

**Common GCC/G++ Flags:**

```bash
# Warning flags
-Wall              # Enable all warnings
-Wextra            # Extra warnings
-Werror            # Treat warnings as errors
-pedantic          # Strict ISO C++ compliance

# Optimization flags
-O0                # No optimization (default)
-O1                # Basic optimization
-O2                # Moderate optimization
-O3                # Aggressive optimization
-Os                # Optimize for size

# Debugging flags
-g                 # Generate debug information
-ggdb              # GDB-specific debug info

# Standard version
-std=c++11         # Use C++11 standard
-std=c++14         # Use C++14 standard
-std=c++17         # Use C++17 standard
-std=c++20         # Use C++20 standard

# Linking
-l<library>        # Link with library
-L<directory>      # Add library search path
-I<directory>      # Add include search path

# Other useful flags
-c                 # Compile only, don't link
-o <file>          # Output file name
-D<macro>          # Define preprocessor macro
-E                 # Preprocess only
-S                 # Generate assembly code
```

**Example Compilation:**
```bash
g++ -Wall -Wextra -std=c++17 -O2 -o myprogram main.cpp utils.cpp
```

### Build Systems

For larger projects, use build systems:

**Make (Makefile):**
```makefile
CXX = g++
CXXFLAGS = -Wall -std=c++17 -O2

program: main.o utils.o
	$(CXX) $(CXXFLAGS) -o program main.o utils.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

utils.o: utils.cpp
	$(CXX) $(CXXFLAGS) -c utils.cpp

clean:
	rm -f *.o program
```

**CMake (Modern approach):**
```cmake
cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(program main.cpp utils.cpp)
```

---

## 2. Basics of C++

### 2.1 Structure of a Program

```cpp
// Comment: explains code
#include <iostream>    // Preprocessor directive
using namespace std;   // Namespace declaration

int main() {           // Main function - entry point
    cout << "Hello World!";  // Statement
    return 0;          // Return value
}
```

**Key Components:**
- **Comments**: `//` (single line) or `/* */` (multi-line)
- **Preprocessor directives**: Begin with `#`, processed before compilation
- **Main function**: Every C++ program must have exactly one `main()` function
- **Statements**: End with semicolon `;`
- **Blocks**: Code enclosed in `{ }`

### 2.2 Variables and Types

#### Fundamental Data Types (Detailed)

| Type | Size (typical) | Range | Precision | Description |
|------|----------------|-------|-----------|-------------|
| `char` | 1 byte (8 bits) | -128 to 127 or 0 to 255 | N/A | Single character or small integer |
| `unsigned char` | 1 byte | 0 to 255 | N/A | Unsigned character |
| `short` | 2 bytes (16 bits) | -32,768 to 32,767 | N/A | Short integer |
| `unsigned short` | 2 bytes | 0 to 65,535 | N/A | Unsigned short integer |
| `int` | 4 bytes (32 bits) | -2,147,483,648 to 2,147,483,647 | N/A | Standard integer |
| `unsigned int` | 4 bytes | 0 to 4,294,967,295 | N/A | Unsigned integer |
| `long` | 4/8 bytes | System dependent | N/A | Long integer |
| `unsigned long` | 4/8 bytes | System dependent | N/A | Unsigned long |
| `long long` | 8 bytes (64 bits) | -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807 | N/A | Extended long (C++11) |
| `unsigned long long` | 8 bytes | 0 to 18,446,744,073,709,551,615 | N/A | Unsigned long long |
| `float` | 4 bytes | ±3.4e±38 | ~7 decimal digits | Single precision floating point |
| `double` | 8 bytes | ±1.7e±308 | ~15 decimal digits | Double precision floating point |
| `long double` | 8/12/16 bytes | Extended precision | ~18-19 decimal digits | Extended double precision |
| `bool` | 1 byte | true (1) or false (0) | N/A | Boolean value |
| `wchar_t` | 2/4 bytes | Wide character | N/A | Wide character (Unicode) |
| `char16_t` | 2 bytes | UTF-16 character | N/A | Unicode character (C++11) |
| `char32_t` | 4 bytes | UTF-32 character | N/A | Unicode character (C++11) |

**Important Notes:**
- Sizes can vary by platform (32-bit vs 64-bit)
- Use `sizeof(type)` to check actual size on your system
- `int` is typically 4 bytes on modern systems
- `long` is 4 bytes on Windows, 8 bytes on 64-bit Linux/Mac

**Checking Sizes:**
```cpp
#include <iostream>
#include <limits>
using namespace std;

int main() {
    cout << "Size of char: " << sizeof(char) << " byte(s)" << endl;
    cout << "Size of int: " << sizeof(int) << " byte(s)" << endl;
    cout << "Size of float: " << sizeof(float) << " byte(s)" << endl;
    cout << "Size of double: " << sizeof(double) << " byte(s)" << endl;
    
    // Using limits library
    cout << "Int min: " << numeric_limits<int>::min() << endl;
    cout << "Int max: " << numeric_limits<int>::max() << endl;
    cout << "Double max: " << numeric_limits<double>::max() << endl;
    
    return 0;
}
```

#### Type Modifiers (Detailed)

**Signed vs Unsigned:**
```cpp
// Signed (default) - can store negative and positive
signed int a = -100;    // Can be negative
int b = -50;            // 'signed' is implicit

// Unsigned - only positive values
unsigned int c = 100;   // Cannot be negative
unsigned int d = -5;    // WARNING! Wraps around to large positive number

// Why use unsigned?
unsigned int age = 25;          // Age can't be negative
unsigned char pixel = 255;      // RGB values (0-255)
size_t arraySize = 100;         // Array sizes (always positive)
```

**Important Unsigned Behavior:**
```cpp
unsigned int x = 5;
unsigned int y = 10;
unsigned int result = x - y;  // Result is NOT -5!
// Result wraps around: 4,294,967,291 (large positive number)

// Be careful in loops!
for (unsigned int i = 10; i >= 0; i--) {  // INFINITE LOOP!
    // i never becomes negative, wraps to max value
}
```

**Short and Long:**
```cpp
short int s = 32000;        // Or just: short s = 32000;
long int l = 2000000000L;   // Or just: long l = 2000000000L;
long long ll = 9000000000000000000LL;  // C++11

// When to use?
short s;        // When memory is critical (embedded systems)
int i;          // Default choice for integers
long l;         // When you need larger range
long long ll;   // For very large numbers (timestamps, file sizes)
```

#### Variable Declaration and Initialization (Detailed)

**Declaration:**
```cpp
// Basic declaration (uninitialized - contains garbage value)
int x;
double pi;
char letter;

// Multiple declarations
int a, b, c;
double x, y, z;

// Mixed (declaration + initialization)
int p = 5, q, r = 10;  // p=5, q=garbage, r=10
```

**Initialization Methods:**

1. **C-like Initialization (Copy Initialization):**
```cpp
int x = 5;
double pi = 3.14159;
char grade = 'A';
string name = "John";

// Can cause narrowing (data loss)
int num = 3.7;  // num = 3, fractional part lost (no warning!)
```

2. **Constructor Initialization (Direct Initialization):**
```cpp
int x(5);
double pi(3.14159);
string name("John");

// Useful for objects
vector<int> v(10);        // Vector of 10 elements
complex<double> c(1, 2);  // Complex number (1 + 2i)
```

3. **Uniform Initialization (Brace Initialization - C++11):**
```cpp
int x{5};
double pi{3.14159};
string name{"John"};

// Prevents narrowing conversions (compile error!)
int num{3.7};  // ERROR! Narrowing conversion not allowed

// Empty braces = default initialization (0 for primitives)
int x{};      // x = 0
double y{};   // y = 0.0
string s{};   // s = "" (empty string)

// Initialize containers
vector<int> v{1, 2, 3, 4, 5};
map<string, int> m{{"apple", 5}, {"banana", 3}};
```

**Why Prefer Uniform Initialization?**
- Prevents narrowing conversions (safer)
- Works consistently for all types
- Can distinguish between default and value initialization
- Prevents "most vexing parse" problem

4. **Copy List Initialization (C++11):**
```cpp
int x = {5};      // Same as int x{5};
auto y = {1, 2};  // y is initializer_list<int>
```

#### Type Deduction (C++11 and beyond)

**auto Keyword:**
```cpp
auto x = 5;            // int
auto y = 3.14;         // double
auto z = 'a';          // char
auto s = "Hello";      // const char*
auto str = string("Hi"); // string

// auto with complex types
auto v = vector<int>{1, 2, 3};
auto m = map<string, int>{{"a", 1}};

// auto with iterators (very useful!)
vector<int> vec = {1, 2, 3};
auto it = vec.begin();  // Instead of: vector<int>::iterator it

// auto in loops
for (auto x : vec) {           // Copy
    cout << x;
}
for (auto& x : vec) {          // Reference (can modify)
    x *= 2;
}
for (const auto& x : vec) {    // Const reference (efficient, read-only)
    cout << x;
}

// auto with function return types (C++14)
auto add(int a, int b) {
    return a + b;  // Return type deduced as int
}
```

**auto Rules:**
```cpp
const int x = 5;
auto a = x;        // a is int (const removed)
const auto b = x;  // b is const int

int& ref = x;
auto c = ref;      // c is int (reference removed)
auto& d = ref;     // d is int& (reference kept)

int* ptr = &x;
auto e = ptr;      // e is int*
auto* f = ptr;     // f is int* (equivalent)
```

**decltype Keyword:**
```cpp
int x = 5;
decltype(x) y = 10;  // y has same type as x (int)

vector<int> v;
decltype(v.begin()) it = v.begin();  // Preserves exact type

// decltype with functions
int func() { return 0; }
decltype(func()) result;  // result is int

// decltype(auto) - C++14 (preserves references and cv-qualifiers)
const int& getRef();
decltype(auto) x = getRef();  // x is const int& (not int)
```

#### Variable Scope and Lifetime

**Local Variables:**
```cpp
void function() {
    int x = 5;  // Local to function
    // x is destroyed when function exits
}
```

**Global Variables:**
```cpp
int globalVar = 10;  // Accessible from anywhere

void func() {
    cout << globalVar;  // Can access
    globalVar = 20;     // Can modify
}
```

**Static Variables:**
```cpp
void counter() {
    static int count = 0;  // Initialized only once
    count++;
    cout << count;  // Persists between function calls
}

int main() {
    counter();  // Prints 1
    counter();  // Prints 2
    counter();  // Prints 3
}
```

**Block Scope:**
```cpp
int main() {
    int x = 10;
    
    {
        int x = 20;  // Different variable (shadows outer x)
        cout << x;   // Prints 20
    }
    
    cout << x;  // Prints 10
}
```

#### Storage Classes

```cpp
// auto (default, local variables) - C++11 changed meaning!
// auto is now for type deduction

// register (hint to compiler, mostly obsolete)
register int counter = 0;

// static (internal linkage, one copy per program)
static int fileScope;  // Visible only in this file

// extern (external linkage, shared across files)
extern int sharedVariable;  // Declared elsewhere

// thread_local (C++11) - one copy per thread
thread_local int threadSpecific = 0;
```

**Example with Multiple Files:**

*file1.cpp:*
```cpp
int globalVar = 100;  // Definition
```

*file2.cpp:*
```cpp
extern int globalVar;  // Declaration (refers to file1.cpp)

void func() {
    cout << globalVar;  // Uses globalVar from file1.cpp
}
```

#### Type Qualifiers

**const:**
```cpp
const int MAX = 100;        // Cannot be modified
MAX = 200;                  // ERROR!

const int* ptr1;            // Pointer to const int
int* const ptr2 = &x;       // Const pointer to int
const int* const ptr3;      // Const pointer to const int
```

**volatile:**
```cpp
volatile int sensorValue;   // Value can change unexpectedly
// Prevents compiler optimizations
// Used for hardware registers, signal handlers
```

**mutable:**
```cpp
class MyClass {
    mutable int counter;    // Can be modified in const methods
    
    void increment() const {
        counter++;          // OK, even though method is const
    }
};
```

#### Type Aliases (Advanced)

**typedef (Traditional):**
```cpp
typedef unsigned long ulong;
typedef int* IntPtr;
typedef vector<string> StringVector;

ulong bigNumber = 1000000UL;
IntPtr p = &x;
StringVector names;
```

**using (Modern C++11):**
```cpp
using ulong = unsigned long;
using IntPtr = int*;
using StringVector = vector<string>;

// Better for templates
template<typename T>
using Vec = vector<T>;

Vec<int> numbers;     // Same as vector<int>
Vec<string> words;    // Same as vector<string>
```

#### Special Integer Types (C++11)

```cpp
#include <cstdint>

// Fixed-width integers (guaranteed size)
int8_t    i8;    // Exactly 8 bits
int16_t   i16;   // Exactly 16 bits
int32_t   i32;   // Exactly 32 bits
int64_t   i64;   // Exactly 64 bits

uint8_t   u8;    // Unsigned 8 bits
uint16_t  u16;   // Unsigned 16 bits
uint32_t  u32;   // Unsigned 32 bits
uint64_t  u64;   // Unsigned 64 bits

// Fast integer types (at least N bits, optimized for speed)
int_fast8_t   fast8;
int_fast16_t  fast16;
int_fast32_t  fast32;

// Least integer types (at least N bits, smallest size)
int_least8_t  least8;
int_least16_t least16;

// Maximum width types
intmax_t  maxInt;
uintmax_t maxUint;

// Size type (for array indexing)
size_t arrayIndex;      // Unsigned, typically 32/64 bit
ptrdiff_t ptrDiff;      // Signed difference between pointers
```

### 2.3 Constants (Detailed)

Constants are values that cannot be modified after initialization.

#### const Keyword

**Basic const Variables:**
```cpp
const double PI = 3.14159265359;
const int MAX_SIZE = 100;
const char NEWLINE = '\n';

PI = 3.14;  // ERROR! Cannot modify const

// Must be initialized at declaration
const int x;  // ERROR! const must be initialized
```

**const with Different Types:**
```cpp
// Integer constants
const int hours = 24;
const unsigned int MAX_USERS = 1000;

// Floating-point constants
const float GRAVITY = 9.81f;  // f suffix for float
const double E = 2.71828;

// Character constants
const char TAB = '\t';
const char NULL_CHAR = '\0';

// String constants
const string GREETING = "Hello, World!";
const char* MESSAGE = "Welcome";  // Pointer to const string
```

**const with Pointers (Important!):**
```cpp
int value = 100;

// 1. Pointer to const int (cannot change value through pointer)
const int* ptr1 = &value;
*ptr1 = 200;     // ERROR! Cannot modify value
ptr1 = &other;   // OK, can point to different address

// 2. Const pointer to int (cannot change where pointer points)
int* const ptr2 = &value;
*ptr2 = 200;     // OK, can modify value
ptr2 = &other;   // ERROR! Cannot change pointer address

// 3. Const pointer to const int (cannot change either)
const int* const ptr3 = &value;
*ptr3 = 200;     // ERROR! Cannot modify value
ptr3 = &other;   // ERROR! Cannot change pointer

// Mnemonic: Read right to left
// const int* ptr = "pointer to const int"
// int* const ptr = "const pointer to int"
```

**const with References:**
```cpp
int x = 10;

// const reference
const int& ref = x;
ref = 20;  // ERROR! Cannot modify through const reference

// Useful for function parameters (efficient, safe)
void printValue(const int& value) {
    cout << value;
    // value = 100;  // ERROR! Cannot modify
}

// Can bind to temporary values
const int& r = 42;  // OK! Extends lifetime of temporary
```

**const Member Functions (in Classes):**
```cpp
class MyClass {
    int value;
    
public:
    int getValue() const {  // const member function
        return value;       // Can read
        // value = 10;      // ERROR! Cannot modify member variables
    }
    
    void setValue(int v) {
        value = v;  // Non-const function can modify
    }
};

const MyClass obj;
obj.getValue();   // OK, const object can call const functions
obj.setValue(5);  // ERROR! Cannot call non-const function on const object
```

#### #define Preprocessor Directive

**Basic Macros:**
```cpp
#define PI 3.14159
#define MAX_SIZE 100
#define NEWLINE '\n'

// Text replacement before compilation
double area = PI * radius * radius;
// Becomes: double area = 3.14159 * radius * radius;
```

**Macros vs const:**
```cpp
// Using #define
#define MAX 100
// Pros: No memory used, simple text replacement
// Cons: No type checking, no scope, debugging difficult

// Using const
const int MAX = 100;
// Pros: Type-safe, has scope, debugger-friendly
// Cons: Uses memory (though usually optimized away)

// PREFER const over #define for constants!
```

**Function-like Macros:**
```cpp
#define SQUARE(x) ((x) * (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int result = SQUARE(5);  // Expands to: ((5) * (5))

// DANGER: Side effects!
int x = 5;
int y = SQUARE(x++);  // Expands to: ((x++) * (x++))
// x is incremented TWICE! Unexpected behavior!

// Use inline functions instead:
inline int square(int x) { return x * x; }
```

**Common Preprocessor Constants:**
```cpp
#define TRUE 1
#define FALSE 0
#define NULL 0  // In C++, prefer nullptr

#define DEBUG
#define VERSION "1.0.0"
#define AUTHOR "John Doe"
```

**Undefining Macros:**
```cpp
#define TEMP_VALUE 100
// Use TEMP_VALUE...
#undef TEMP_VALUE
// TEMP_VALUE no longer defined
```

#### constexpr (C++11) - Compile-Time Constants

**Basic constexpr:**
```cpp
constexpr int SIZE = 10;
constexpr double PI = 3.14159;

// Evaluated at compile-time
int arr[SIZE];  // OK, SIZE is compile-time constant

// Difference from const:
const int runtime_value = getUserInput();  // OK, runtime value
constexpr int compile_value = getUserInput();  // ERROR! Must be compile-time
```

**constexpr Functions:**
```cpp
// Function evaluated at compile-time if arguments are compile-time constants
constexpr int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

// Compile-time evaluation
constexpr int result = factorial(5);  // Computed at compile-time

// Runtime evaluation (if needed)
int n = getUserInput();
int runtime_result = factorial(n);  // Computed at runtime
```

**constexpr vs const:**
```cpp
const int x = 10;          // Runtime or compile-time constant
constexpr int y = 10;      // Always compile-time constant

const int a = getInput();  // OK, runtime constant
constexpr int b = getInput();  // ERROR! Must be compile-time evaluable
```

**Advanced constexpr:**
```cpp
// constexpr with classes (C++11)
class Point {
    int x_, y_;
public:
    constexpr Point(int x, int y) : x_(x), y_(y) {}
    constexpr int x() const { return x_; }
    constexpr int y() const { return y_; }
};

constexpr Point p(10, 20);
constexpr int px = p.x();  // Compile-time evaluation

// if constexpr (C++17)
template<typename T>
auto getValue(T t) {
    if constexpr (std::is_integral_v<T>) {
        return t + 1;
    } else {
        return t;
    }
}
```

#### Literal Constants

**Integer Literals:**
```cpp
int decimal = 42;          // Decimal (base 10)
int octal = 052;           // Octal (base 8, starts with 0)
int hex = 0x2A;            // Hexadecimal (base 16, starts with 0x)
int binary = 0b101010;     // Binary (base 2, C++14, starts with 0b)

// Suffixes
long lng = 42L;            // Long
long long llng = 42LL;     // Long long
unsigned uint = 42U;       // Unsigned
unsigned long ulng = 42UL; // Unsigned long

// Digit separators (C++14)
int million = 1'000'000;
int hex_val = 0xFF'00'FF;
```

**Floating-Point Literals:**
```cpp
double d1 = 3.14;
double d2 = 3.14159;
double d3 = 314.159e-2;    // Scientific notation: 314.159 × 10^-2

// Suffixes
float f = 3.14f;           // Float (without f, it's double)
long double ld = 3.14L;    // Long double

// Hexadecimal floating-point (C++17)
double hex_float = 0x1.2p3;  // 1.2 × 2^3 = 9.6
```

**Character Literals:**
```cpp
char ch1 = 'A';            // Character
char ch2 = '\n';           // Newline
char ch3 = '\t';           // Tab
char ch4 = '\\';           // Backslash
char ch5 = '\'';           // Single quote
char ch6 = '\0';           // Null character
char ch7 = '\x41';         // Hex value (A)
char ch8 = '\101';         // Octal value (A)

// Wide character
wchar_t wch = L'A';
char16_t c16 = u'A';       // UTF-16
char32_t c32 = U'A';       // UTF-32
```

**String Literals:**
```cpp
const char* str1 = "Hello";           // C-string
string str2 = "World";                // C++ string

// Escape sequences
const char* msg = "Line 1\nLine 2\tTabbed";

// Raw strings (C++11) - no escape processing
string path = R"(C:\folder\file.txt)";  // No need to escape \
string json = R"({"name": "John", "age": 30})";

// Multi-line raw strings
string html = R"(
    <html>
        <body>Hello</body>
    </html>
)";

// Custom delimiter (if string contains )")
string special = R"delimiter(Text with )" inside)delimiter";

// Wide/Unicode strings
wchar_t* wstr = L"Wide string";
const char16_t* u16str = u"UTF-16 string";
const char32_t* u32str = U"UTF-32 string";
const char* u8str = u8"UTF-8 string";
```

**Boolean Literals:**
```cpp
bool flag1 = true;
bool flag2 = false;

// Any non-zero value is true
bool b1 = 42;    // true
bool b2 = 0;     // false
```

**Pointer Literals:**
```cpp
int* ptr1 = nullptr;       // Modern C++ (C++11)
int* ptr2 = NULL;          // Old style (actually 0)
int* ptr3 = 0;             // Even older style

// nullptr is type-safe
void func(int x);
void func(int* ptr);

func(NULL);     // Ambiguous! Might call func(int)
func(nullptr);  // Calls func(int*) - unambiguous
```

#### Enumeration Constants

**Traditional enum:**
```cpp
enum Color {
    RED,      // 0
    GREEN,    // 1
    BLUE      // 2
};

enum Status {
    OK = 200,
    NOT_FOUND = 404,
    ERROR = 500
};

Color myColor = RED;
if (myColor == GREEN) { /* ... */ }
```

**Scoped enum (enum class - C++11):**
```cpp
enum class TrafficLight {
    Red,
    Yellow,
    Green
};

TrafficLight light = TrafficLight::Red;

// Type-safe
// int x = TrafficLight::Red;  // ERROR! No implicit conversion
int x = static_cast<int>(TrafficLight::Red);  // Explicit conversion OK

enum class FileMode : unsigned char {  // Specify underlying type
    Read = 0x01,
    Write = 0x02,
    Append = 0x04
};
```

#### Best Practices for Constants

```cpp
// ✓ GOOD: Use const for runtime constants
const int userChoice = getUserInput();

// ✓ GOOD: Use constexpr for compile-time constants
constexpr double PI = 3.14159;
constexpr int SIZE = 100;

// ✓ GOOD: Use enum class for related constants
enum class ErrorCode { Success, FileNotFound, PermissionDenied };

// ✗ AVOID: Using #define for constants
#define MAX 100  // No type safety, no scope

// ✓ GOOD: Use inline variables (C++17) in headers
inline constexpr double PI = 3.14159;  // No multiple definition errors

// ✓ GOOD: Naming convention - UPPER_CASE for constants
const int MAX_CONNECTIONS = 100;
constexpr double SPEED_OF_LIGHT = 299792458.0;

// ✓ GOOD: Use constexpr for better performance
constexpr int factorial(int n) {
    return n <= 1 ? 1 : n * factorial(n - 1);
}
constexpr int val = factorial(10);  // Computed at compile-time!
```

### 2.4 Operators (Comprehensive Guide)

#### Arithmetic Operators

```cpp
// Basic arithmetic
int a = 10, b = 3;

int sum = a + b;         // Addition: 13
int diff = a - b;        // Subtraction: 7
int product = a * b;     // Multiplication: 30
int quotient = a / b;    // Integer division: 3 (not 3.333...)
int remainder = a % b;   // Modulo (remainder): 1

// Floating-point division
double x = 10.0, y = 3.0;
double result = x / y;   // 3.333...

// Mixed type operations
double mixed = 10 / 3;      // 3.0 (int division, then converted)
double correct = 10.0 / 3;  // 3.333... (double division)
double also_correct = 10 / 3.0;  // 3.333...

// Negative numbers
int neg = -a;            // Unary minus: -10

// Increment/Decrement
int i = 5;
i++;    // Post-increment: use value, then increment (i becomes 6)
++i;    // Pre-increment: increment, then use value (i becomes 7)
i--;    // Post-decrement: use value, then decrement
--i;    // Pre-decrement: decrement, then use value

// Difference between pre and post
int x = 5;
int y = x++;    // y = 5, x = 6 (post: use then increment)
int z = ++x;    // z = 7, x = 7 (pre: increment then use)

// Modulo with negative numbers (careful!)
int r1 = 10 % 3;     // 1
int r2 = -10 % 3;    // -1 (implementation-defined in older C++)
int r3 = 10 % -3;    // 1
int r4 = -10 % -3;   // -1
```

#### Assignment Operators

```cpp
int x = 10;

// Basic assignment
x = 20;

// Compound assignment operators
x += 5;   // x = x + 5   (Addition assignment)
x -= 3;   // x = x - 3   (Subtraction assignment)
x *= 2;   // x = x * 2   (Multiplication assignment)
x /= 4;   // x = x / 4   (Division assignment)
x %= 3;   // x = x % 3   (Modulo assignment)

// Bitwise compound assignment
x &= 0xFF;   // x = x & 0xFF   (AND assignment)
x |= 0x0F;   // x = x | 0x0F   (OR assignment)
x ^= 0xAA;   // x = x ^ 0xAA   (XOR assignment)
x <<= 2;     // x = x << 2     (Left shift assignment)
x >>= 1;     // x = x >> 1     (Right shift assignment)

// Multiple assignment (right-to-left)
int a, b, c;
a = b = c = 10;  // All become 10

// Assignment returns a value
int x;
if ((x = getValue()) != 0) {  // Assignment within condition
    // Use x
}
```

#### Comparison (Relational) Operators

```cpp
int a = 10, b = 20;

// Comparison operators return bool (true or false)
bool equal = (a == b);          // Equal to: false
bool notEqual = (a != b);       // Not equal to: true
bool less = (a < b);            // Less than: true
bool greater = (a > b);         // Greater than: false
bool lessEqual = (a <= b);      // Less than or equal: true
bool greaterEqual = (a >= b);   // Greater than or equal: false

// Three-way comparison (C++20 - spaceship operator)
#include <compare>
auto result = a <=> b;  // Returns ordering category
// result < 0: a < b
// result == 0: a == b
// result > 0: a > b

// Floating-point comparisons (be careful!)
double x = 0.1 + 0.2;
double y = 0.3;
if (x == y) {  // May be false due to floating-point precision!
    // Might not execute
}

// Better approach for floating-point
#include <cmath>
const double EPSILON = 1e-9;
if (abs(x - y) < EPSILON) {  // Compare with tolerance
    // Nearly equal
}

// Comparing strings
string s1 = "apple";
string s2 = "banana";
if (s1 < s2) {  // Lexicographic comparison
    cout << "apple comes before banana";
}

// Chaining comparisons (DON'T DO THIS - undefined behavior in C++)
// if (a < b < c) { }  // WRONG! Evaluates (a < b) as 0 or 1, then compares with c

// Correct way
if (a < b && b < c) {  // Use logical AND
    // a < b < c
}
```

#### Logical Operators

```cpp
bool a = true, b = false;

// Logical AND (&&) - true only if both are true
bool result1 = a && b;  // false
bool result2 = true && true;  // true

// Logical OR (||) - true if at least one is true
bool result3 = a || b;  // true
bool result4 = false || false;  // false

// Logical NOT (!) - inverts boolean value
bool result5 = !a;  // false
bool result6 = !b;  // true

// Short-circuit evaluation
int x = 0;
if (x != 0 && 10 / x > 1) {  // Second part NOT evaluated (short-circuit)
    // Safe from division by zero
}

if (ptr != nullptr && ptr->value > 0) {  // Checks pointer first
    // Safe access
}

// Truth table
// a     b     a && b    a || b    !a
// T     T       T         T        F
// T     F       F         T        F
// F     T       F         T        T
// F     F       F         F        T

// Combining logical operators
if ((a || b) && !(c && d)) {
    // Complex condition
}

// Common patterns
bool isValid = (age >= 18 && age <= 65);
bool hasAccess = (isAdmin || isModerator);
bool isInRange = (x >= min && x <= max);
```

#### Bitwise Operators

```cpp
unsigned int a = 0b1100;  // 12 in binary
unsigned int b = 0b1010;  // 10 in binary

// Bitwise AND (&) - 1 if both bits are 1
unsigned int and_result = a & b;  // 0b1000 = 8
// 1100
// 1010
// ----
// 1000

// Bitwise OR (|) - 1 if at least one bit is 1
unsigned int or_result = a | b;   // 0b1110 = 14
// 1100
// 1010
// ----
// 1110

// Bitwise XOR (^) - 1 if bits are different
unsigned int xor_result = a ^ b;  // 0b0110 = 6
// 1100
// 1010
// ----
// 0110

// Bitwise NOT (~) - Inverts all bits (1's complement)
unsigned int not_result = ~a;  // 0b...11110011 (all bits flipped)

// Left shift (<<) - Shifts bits left, fills with 0
unsigned int left = a << 1;   // 0b11000 = 24 (multiply by 2)
unsigned int left2 = a << 2;  // 0b110000 = 48 (multiply by 4)

// Right shift (>>) - Shifts bits right
unsigned int right = a >> 1;  // 0b0110 = 6 (divide by 2)
unsigned int right2 = a >> 2; // 0b0011 = 3 (divide by 4)

// Practical uses
// 1. Checking if a number is even/odd
bool isOdd = (n & 1);  // Last bit is 1 for odd numbers

// 2. Multiplying/dividing by powers of 2 (faster)
int x = 5;
int doubled = x << 1;   // x * 2
int quadrupled = x << 2;  // x * 4
int halved = x >> 1;    // x / 2

// 3. Setting specific bits (flags)
unsigned int flags = 0;
const unsigned int FLAG_READ = 0x01;    // 0b0001
const unsigned int FLAG_WRITE = 0x02;   // 0b0010
const unsigned int FLAG_EXECUTE = 0x04; // 0b0100

flags |= FLAG_READ;      // Set read flag
flags |= FLAG_WRITE;     // Set write flag
bool canRead = flags & FLAG_READ;     // Check if read flag is set
flags &= ~FLAG_WRITE;    // Clear write flag
flags ^= FLAG_EXECUTE;   // Toggle execute flag

// 4. Bit masking
unsigned int color = 0xRRGGBB;  // RGB color
unsigned int red = (color >> 16) & 0xFF;    // Extract red
unsigned int green = (color >> 8) & 0xFF;   // Extract green
unsigned int blue = color & 0xFF;           // Extract blue

// 5. Swap without temp variable
int x = 5, y = 10;
x ^= y;
y ^= x;
x ^= y;
// Now x = 10, y = 5

// 6. Power of 2 check
bool isPowerOf2 = (n > 0) && ((n & (n - 1)) == 0);
```

#### Ternary Conditional Operator (?:)

```cpp
// Syntax: condition ? value_if_true : value_if_false

int a = 10, b = 20;
int max = (a > b) ? a : b;  // max = 20

// Equivalent to:
int max;
if (a > b)
    max = a;
else
    max = b;

// Nested ternary (less readable, avoid excessive nesting)
int x = 5;
string grade = (x >= 90) ? "A" :
               (x >= 80) ? "B" :
               (x >= 70) ? "C" :
               (x >= 60) ? "D" : "F";

// Common uses
// 1. Assign different values
int absValue = (num < 0) ? -num : num;

// 2. Select function to call
(isValid ? processValid : processInvalid)(data);

// 3. Return different values
return (count > 0) ? count : 0;

// 4. In expressions
cout << "You have " << (count == 1 ? "1 item" : to_string(count) + " items");

// Can be chained but affects readability
int result = (a > b) ? (a > c ? a : c) : (b > c ? b : c);  // Max of three
```

#### Comma Operator (,)

```cpp
// Evaluates left operand, then right operand, returns right operand

int x = (5, 10);  // x = 10 (5 is evaluated but discarded)

// Common use: in for loops
for (int i = 0, j = 10; i < j; i++, j--) {
    // Multiple operations in increment section
}

// Multiple variable declarations
int a = 1, b = 2, c = 3;  // This is NOT comma operator (just declaration)

// Function arguments (NOT comma operator - just separator)
func(a, b, c);

// Rarely used elsewhere (can make code confusing)
int y = (x++, x + 5);  // y = x + 5 (after x is incremented)
```

#### Member Access Operators

```cpp
struct Point {
    int x, y;
    void print() { cout << x << ", " << y; }
};

Point p;
Point* ptr = &p;

// Dot operator (.) - for objects
p.x = 10;
p.y = 20;
p.print();

// Arrow operator (->) - for pointers
ptr->x = 30;       // Equivalent to: (*ptr).x = 30
ptr->y = 40;       // Equivalent to: (*ptr).y = 40
ptr->print();      // Equivalent to: (*ptr).print()

// Member pointer operators (advanced)
int Point::*pmem = &Point::x;  // Pointer to member
p.*pmem = 50;      // Access member through object

int (Point::*pfunc)() = &Point::print;  // Pointer to member function
(p.*pfunc)();      // Call through object
```

#### Scope Resolution Operator (::)

```cpp
// 1. Access global variable when local has same name
int value = 100;  // Global

void func() {
    int value = 50;  // Local (shadows global)
    cout << value;    // Prints 50 (local)
    cout << ::value;  // Prints 100 (global)
}

// 2. Access class members
class MyClass {
public:
    static int staticVar;
    static void staticFunc();
};

int MyClass::staticVar = 10;  // Definition
void MyClass::staticFunc() { }  // Definition

// Access without object
cout << MyClass::staticVar;
MyClass::staticFunc();

// 3. Namespace resolution
namespace Math {
    const double PI = 3.14159;
}

double area = Math::PI * r * r;

// 4. Nested classes/namespaces
namespace Outer {
    namespace Inner {
        int value = 42;
    }
}

cout << Outer::Inner::value;
```

#### sizeof Operator

```cpp
// Returns size in bytes

// With types
size_t intSize = sizeof(int);        // Typically 4
size_t doubleSize = sizeof(double);  // Typically 8
size_t charSize = sizeof(char);      // Always 1 (by definition)

// With variables
int x;
size_t xSize = sizeof(x);            // Size of x (same as sizeof(int))

// With arrays
int arr[10];
size_t arrSize = sizeof(arr);        // 40 bytes (10 * 4)
size_t elementCount = sizeof(arr) / sizeof(arr[0]);  // 10

// With expressions (does NOT evaluate expression!)
int i = 0;
size_t size = sizeof(i++);  // i is NOT incremented! (only type is checked)

// With strings
char str[] = "Hello";
size_t strSize = sizeof(str);  // 6 (includes null terminator '\0')

string cppStr = "Hello";
size_t cppStrSize = sizeof(cppStr);  // Size of string object (not content!)

// With structures
struct MyStruct {
    int a;      // 4 bytes
    char b;     // 1 byte (+ 3 padding)
    double c;   // 8 bytes
};
size_t structSize = sizeof(MyStruct);  // Typically 16 (with padding)

// With pointers (all pointers have same size)
int* ptr;
size_t ptrSize = sizeof(ptr);  // 4 on 32-bit, 8 on 64-bit systems

// In templates
template<typename T>
void checkSize() {
    cout << "Size: " << sizeof(T) << endl;
}
```

#### Type Casting Operators

```cpp
// 1. C-style cast (avoid in C++)
int x = (int)3.14;
char c = (char)65;

// 2. static_cast (compile-time cast)
double d = 3.14;
int i = static_cast<int>(d);  // Truncates to 3

float f = 3.7f;
int j = static_cast<int>(f);  // 3

// Upcasting/downcasting in inheritance
class Base {};
class Derived : public Base {};

Derived* d = new Derived();
Base* b = static_cast<Base*>(d);  // Upcast (safe)

// 3. dynamic_cast (runtime cast with type checking)
Base* basePtr = new Derived();
Derived* derivedPtr = dynamic_cast<Derived*>(basePtr);
if (derivedPtr) {
    // Successful cast
}

// 4. const_cast (add/remove const)
const int* constPtr = &value;
int* ptr = const_cast<int*>(constPtr);  // Remove const (dangerous!)

// 5. reinterpret_cast (low-level reinterpretation)
int* intPtr = &someInt;
char* charPtr = reinterpret_cast<char*>(intPtr);
// Reinterprets bit pattern (use with caution!)
```

#### Other Operators

```cpp
// Address-of operator (&)
int x = 10;
int* ptr = &x;  // Get address of x

// Dereference operator (*)
int value = *ptr;  // Get value at address

// new and delete (dynamic memory)
int* p = new int(5);     // Allocate
delete p;                // Deallocate

int* arr = new int[10];  // Allocate array
delete[] arr;            // Deallocate array

// typeid operator (RTTI - Run-Time Type Information)
#include <typeinfo>
int x = 5;
cout << typeid(x).name();  // Prints type name

// noexcept operator (C++11) - checks if expression can throw
bool canThrow = noexcept(func());
```

#### Operator Precedence and Associativity

```cpp
// Higher precedence operators evaluate first
int result = 2 + 3 * 4;  // 14 (not 20) - * before +

// Use parentheses for clarity
int result = (2 + 3) * 4;  // 20

// Associativity - left-to-right vs right-to-left
int x = 10 - 5 - 2;  // 3 (left-to-right: (10-5)-2)
int y = a = b = 5;   // right-to-left: a = (b = 5)

/*
Precedence (high to low):
1.  :: (scope)
2.  () [] . -> ++ -- (postfix)
3.  ++ -- + - ! ~ * & sizeof (prefix/unary)
4.  * / %
5.  + -
6.  << >>
7.  < <= > >=
8.  == !=
9.  &
10. ^
11. |
12. &&
13. ||
14. ?:
15. = += -= *= /= etc. (assignment)
16. ,
*/
```

#### Common Operator Patterns and Idioms

```cpp
// 1. Swap using XOR (no temp variable)
a ^= b ^= a ^= b;  // Swaps a and b

// 2. Toggle boolean
flag = !flag;

// 3. Clamp value
value = min(max(value, minVal), maxVal);

// 4. Check range
bool inRange = (value >= min && value <= max);

// 5. Set/clear/toggle bit
flags |= (1 << n);   // Set bit n
flags &= ~(1 << n);  // Clear bit n
flags ^= (1 << n);   // Toggle bit n

// 6. Check if bit is set
bool isSet = (flags & (1 << n)) != 0;

// 7. Round to nearest multiple
int rounded = ((value + multiple / 2) / multiple) * multiple;

// 8. Absolute value (for integers)
int abs = (x < 0) ? -x : x;
// Or using bit manipulation:
int abs = (x ^ (x >> 31)) - (x >> 31);

// 9. Sign function
int sign = (x > 0) - (x < 0);  // -1, 0, or 1

// 10. Max/min without branches
int max = a ^ ((a ^ b) & -(a < b));
int min = b ^ ((a ^ b) & -(a < b));
```

### 2.5 Basic Input/Output

```cpp
#include <iostream>
using namespace std;

// Output
cout << "Hello";           // Output text
cout << variable;          // Output variable
cout << "x = " << x << endl;  // Chain outputs

// Input
cin >> variable;           // Input to variable
cin >> a >> b >> c;        // Multiple inputs

// String input with spaces
string name;
getline(cin, name);        // Read entire line

// Common manipulators
#include <iomanip>
cout << setw(10) << value;      // Set field width
cout << setprecision(2) << pi;  // Set decimal precision
cout << fixed << 3.14159;       // Fixed-point notation
```

---

## 3. Program Structure

### 3.1 Control Structures (Comprehensive Guide)

#### If-Else Statement (Detailed)

**Basic If:**
```cpp
if (condition) {
    // Executes if condition is true
}

// Single statement (braces optional but recommended)
if (x > 0)
    cout << "Positive";
```

**If-Else:**
```cpp
if (condition) {
    // Executes if condition is true
} else {
    // Executes if condition is false
}

// Example
int age = 18;
if (age >= 18) {
    cout << "Adult";
} else {
    cout << "Minor";
}
```

**If-Else If-Else Chain:**
```cpp
if (condition1) {
    // Executes if condition1 is true
} else if (condition2) {
    // Executes if condition1 is false and condition2 is true
} else if (condition3) {
    // Executes if previous conditions false and condition3 true
} else {
    // Executes if all conditions are false
}

// Example: Grade calculator
int score = 85;
if (score >= 90) {
    cout << "Grade: A";
} else if (score >= 80) {
    cout << "Grade: B";
} else if (score >= 70) {
    cout << "Grade: C";
} else if (score >= 60) {
    cout << "Grade: D";
} else {
    cout << "Grade: F";
}
```

**Nested If:**
```cpp
if (condition1) {
    if (condition2) {
        // Both conditions true
    } else {
        // condition1 true, condition2 false
    }
} else {
    // condition1 false
}

// Example: Login system
if (usernameCorrect) {
    if (passwordCorrect) {
        cout << "Login successful";
    } else {
        cout << "Wrong password";
    }
} else {
    cout << "Username not found";
}
```

**If with Initializer (C++17):**
```cpp
// Declare variable in if statement
if (int result = calculate(); result > 0) {
    // Use result here
    cout << result;
}
// result out of scope here

// Useful for checking optional values
if (auto it = map.find(key); it != map.end()) {
    // Use it here
}

// Multiple declarations
if (int x = getValue(), y = getOther(); x > y) {
    // Use x and y
}
```

**Common Patterns:**
```cpp
// 1. Range checking
if (x >= min && x <= max) {
    // x is in range [min, max]
}

// 2. Null pointer check
if (ptr != nullptr) {
    ptr->doSomething();
}

// 3. String empty check
if (!str.empty()) {
    // String has content
}

// 4. Container empty check
if (!vec.empty()) {
    // Vector has elements
}

// 5. Multiple conditions with grouping
if ((isWeekend || isHoliday) && !isWorking) {
    cout << "Relaxing!";
}
```

#### Ternary Conditional Operator (Advanced)

```cpp
// Basic syntax
result = (condition) ? value_if_true : value_if_false;

// Examples
int max = (a > b) ? a : b;
string status = (loggedIn) ? "Online" : "Offline";
int absValue = (x < 0) ? -x : x;

// Nested ternary (be careful - can be hard to read!)
int max3 = (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);

// Better formatting for nested ternary
string grade = (score >= 90) ? "A" :
               (score >= 80) ? "B" :
               (score >= 70) ? "C" :
               (score >= 60) ? "D" : "F";

// In function calls
cout << (count == 1 ? "1 item" : to_string(count) + " items") << endl;

// Assigning function pointers
auto func = (condition) ? func1 : func2;
func();  // Calls selected function

// Return statements
return (valid) ? processData() : nullptr;

// Can be used for lvalues (assignment targets)
(x > y ? x : y) = 10;  // Assigns 10 to the larger value
```

#### Switch Statement (Detailed)

**Basic Switch:**
```cpp
switch (expression) {
    case constant1:
        // code
        break;
    case constant2:
        // code
        break;
    default:
        // code (executed if no case matches)
}

// Example
int day = 3;
switch (day) {
    case 1:
        cout << "Monday";
        break;
    case 2:
        cout << "Tuesday";
        break;
    case 3:
        cout << "Wednesday";
        break;
    default:
        cout << "Other day";
}
```

**Fall-through (Intentional):**
```cpp
switch (month) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        days = 31;
        break;
    case 4: case 6: case 9: case 11:
        days = 30;
        break;
    case 2:
        days = isLeapYear ? 29 : 28;
        break;
}

// Or with explicit fall-through
switch (value) {
    case 1:
        doFirst();
        [[fallthrough]];  // C++17 attribute - documents intentional fall-through
    case 2:
        doBoth();
        break;
}
```

**Switch with Initialization (C++17):**
```cpp
switch (int value = getValue(); value) {
    case 1:
        // Use value
        break;
    case 2:
        // Use value
        break;
}
// value out of scope here
```

**Switch with Enums:**
```cpp
enum class Color { Red, Green, Blue };

Color c = Color::Green;
switch (c) {
    case Color::Red:
        cout << "Red";
        break;
    case Color::Green:
        cout << "Green";
        break;
    case Color::Blue:
        cout << "Blue";
        break;
}
```

**Important Switch Rules:**
- Expression must be integral or enumeration type
- Case labels must be constant expressions
- No duplicate case values
- Break statement exits switch (if omitted, falls through)
- Default case is optional
- Cases can be in any order

**Switch vs If-Else:**
```cpp
// Use switch when:
// - Comparing same variable against multiple constant values
// - Using enums
// - Need efficient jump table (compiler optimization)

// Use if-else when:
// - Complex conditions (ranges, multiple variables)
// - Floating-point comparisons
// - String comparisons (in C++, before C++20)
// - Need to evaluate expressions
```

#### While Loop (Detailed)

**Basic While:**
```cpp
while (condition) {
    // code
    // Must eventually make condition false to avoid infinite loop
}

// Example: Count down
int count = 10;
while (count > 0) {
    cout << count << " ";
    count--;
}
// Prints: 10 9 8 7 6 5 4 3 2 1

// Infinite loop (intentional)
while (true) {
    // Must have break statement inside
    if (exitCondition) break;
}
```

**Common Patterns:**
```cpp
// 1. Input validation
int age;
cout << "Enter age (1-120): ";
cin >> age;
while (age < 1 || age > 120) {
    cout << "Invalid! Enter age (1-120): ";
    cin >> age;
}

// 2. Reading until sentinel value
int num;
cout << "Enter numbers (-1 to stop): ";
cin >> num;
while (num != -1) {
    processNumber(num);
    cin >> num;
}

// 3. Event loop
while (!quit) {
    Event event = getEvent();
    handleEvent(event);
}

// 4. Processing data
while (!dataQueue.empty()) {
    Data d = dataQueue.front();
    processData(d);
    dataQueue.pop();
}

// 5. Game loop
while (isRunning) {
    handleInput();
    update();
    render();
}
```

#### Do-While Loop (Detailed)

**Basic Do-While:**
```cpp
do {
    // code
    // Executes at least once (condition checked after)
} while (condition);

// Example: Menu system
int choice;
do {
    cout << "1. Option A\n2. Option B\n3. Exit\n";
    cin >> choice;
    switch (choice) {
        case 1: optionA(); break;
        case 2: optionB(); break;
        case 3: cout << "Goodbye!"; break;
        default: cout << "Invalid choice";
    }
} while (choice != 3);
```

**While vs Do-While:**
```cpp
// While - may not execute at all
int x = 10;
while (x < 5) {  // False initially
    cout << x;   // Never executes
}

// Do-While - always executes at least once
int y = 10;
do {
    cout << y;   // Executes once
} while (y < 5); // Then checks condition
```

**Use Cases for Do-While:**
```cpp
// 1. Input validation (always need at least one input)
do {
    cout << "Enter password: ";
    cin >> password;
} while (!isValidPassword(password));

// 2. Processing at least once
do {
    processData();
    result = checkResult();
} while (result != SUCCESS);

// 3. Game rounds
do {
    playRound();
    cout << "Play again? (y/n): ";
    cin >> choice;
} while (choice == 'y');
```

#### For Loop (Comprehensive)

**Basic For Loop:**
```cpp
for (initialization; condition; increment) {
    // code
}

// Example
for (int i = 0; i < 10; i++) {
    cout << i << " ";
}
// Prints: 0 1 2 3 4 5 6 7 8 9

// Equivalent while loop:
int i = 0;           // initialization
while (i < 10) {     // condition
    cout << i << " ";
    i++;             // increment
}
```

**For Loop Variations:**
```cpp
// 1. Count down
for (int i = 10; i > 0; i--) {
    cout << i << " ";
}

// 2. Step by 2
for (int i = 0; i < 10; i += 2) {
    cout << i << " ";  // 0 2 4 6 8
}

// 3. Multiple variables
for (int i = 0, j = 10; i < j; i++, j--) {
    cout << i << "," << j << " ";
}

// 4. Empty parts (infinite loop)
for (;;) {  // All parts optional
    // Infinite loop
    if (condition) break;
}

// 5. Complex condition
for (int i = 0; i < n && arr[i] != target; i++) {
    // Loop until end or target found
}

// 6. Iterating containers
vector<int> vec = {1, 2, 3, 4, 5};
for (int i = 0; i < vec.size(); i++) {
    cout << vec[i] << " ";
}

// 7. Reverse iteration
for (int i = vec.size() - 1; i >= 0; i--) {
    cout << vec[i] << " ";
}

// 8. Using iterators
for (auto it = vec.begin(); it != vec.end(); ++it) {
    cout << *it << " ";
}
```

**Common Patterns:**
```cpp
// 1. Nested loops (2D array)
for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
        matrix[i][j] = i * cols + j;
    }
}

// 2. Triangle pattern
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= i; j++) {
        cout << "*";
    }
    cout << endl;
}

// 3. Processing with index
for (size_t i = 0; i < data.size(); i++) {
    if (data[i] < threshold) {
        cout << "Index " << i << " is below threshold";
    }
}

// 4. Early termination
for (int i = 0; i < n; i++) {
    if (arr[i] == target) {
        cout << "Found at index " << i;
        break;
    }
}
```

#### Range-Based For Loop (C++11)

**Basic Syntax:**
```cpp
for (type variable : container) {
    // Use variable
}

// Example
vector<int> numbers = {1, 2, 3, 4, 5};
for (int num : numbers) {
    cout << num << " ";
}
```

**Different Styles:**
```cpp
vector<string> names = {"Alice", "Bob", "Charlie"};

// 1. By value (copy) - can't modify original
for (string name : names) {
    name += "!";  // Modifies copy only
}

// 2. By reference - can modify original
for (string& name : names) {
    name += "!";  // Modifies original
}

// 3. By const reference - efficient, can't modify
for (const string& name : names) {
    cout << name;  // Read-only
}

// 4. Auto keyword (preferred)
for (auto name : names) {          // Copy
for (auto& name : names) {         // Reference
for (const auto& name : names) {   // Const reference
```

**When to Use Each:**
```cpp
// Copy (auto) - for small types (int, char, bool, pointers)
vector<int> numbers = {1, 2, 3};
for (auto n : numbers) {  // Cheap to copy
    cout << n;
}

// Const reference (const auto&) - for large objects (strings, vectors, etc.)
vector<string> strings = {"Hello", "World"};
for (const auto& s : strings) {  // Avoid copying
    cout << s;
}

// Reference (auto&) - when you need to modify
vector<int> values = {1, 2, 3};
for (auto& v : values) {
    v *= 2;  // Double each value
}
```

**Range-Based For with Different Containers:**
```cpp
// Arrays
int arr[] = {1, 2, 3, 4, 5};
for (auto x : arr) {
    cout << x << " ";
}

// Vectors
vector<double> vec = {1.1, 2.2, 3.3};
for (auto x : vec) {
    cout << x << " ";
}

// Maps
map<string, int> scores = {{"Alice", 90}, {"Bob", 85}};
for (const auto& pair : scores) {
    cout << pair.first << ": " << pair.second << endl;
}

// Or with structured bindings (C++17)
for (const auto& [name, score] : scores) {
    cout << name << ": " << score << endl;
}

// Sets
set<int> numbers = {1, 2, 3};
for (auto x : numbers) {
    cout << x << " ";
}

// Strings
string text = "Hello";
for (char c : text) {
    cout << c << " ";
}

// Initializer lists
for (auto x : {1, 2, 3, 4, 5}) {
    cout << x << " ";
}
```

**Limitations:**
```cpp
// Can't get index directly
vector<int> vec = {10, 20, 30};
for (auto x : vec) {
    // No easy way to get index
}

// Solution: use traditional for loop or enumerate pattern
for (size_t i = 0; i < vec.size(); i++) {
    cout << "Index " << i << ": " << vec[i] << endl;
}

// Can't modify container size during iteration
for (auto x : vec) {
    vec.push_back(x * 2);  // Undefined behavior!
}
```

#### Jump Statements (Detailed)

**break Statement:**
```cpp
// Exits innermost loop or switch

// 1. Exit loop early
for (int i = 0; i < 100; i++) {
    if (arr[i] == target) {
        cout << "Found at index " << i;
        break;  // Exit loop
    }
}

// 2. Exit nested loop (only innermost)
for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
        if (matrix[i][j] == target) {
            found = true;
            break;  // Only exits inner loop
        }
    }
    if (found) break;  // Exit outer loop too
}

// 3. Exit infinite loop
while (true) {
    int input = getInput();
    if (input == -1) break;
    process(input);
}

// 4. In switch statements
switch (choice) {
    case 1:
        optionA();
        break;  // Exit switch
    case 2:
        optionB();
        break;
}
```

**continue Statement:**
```cpp
// Skips rest of current iteration, goes to next iteration

// 1. Skip specific values
for (int i = 0; i < 10; i++) {
    if (i % 2 == 0) continue;  // Skip even numbers
    cout << i << " ";  // Only prints odd: 1 3 5 7 9
}

// 2. Input validation
for (int i = 0; i < n; i++) {
    int value = getValue();
    if (value < 0) {
        cout << "Invalid, skipping...";
        continue;  // Skip to next iteration
    }
    processValue(value);
}

// 3. Skip processing based on condition
for (const auto& item : items) {
    if (!item.isValid()) continue;  // Skip invalid items
    if (item.isProcessed()) continue;  // Skip already processed
    processItem(item);
}

// 4. Multiple skip conditions
for (int i = 0; i < data.size(); i++) {
    if (data[i] == 0) continue;      // Skip zeros
    if (data[i] < 0) continue;       // Skip negatives
    if (data[i] > MAX) continue;     // Skip too large
    processData(data[i]);
}
```

**goto Statement (Avoid!):**
```cpp
// Jumps to labeled statement (considered harmful, rarely use)

// Example (DON'T DO THIS)
for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
        if (matrix[i][j] == target) {
            goto found;  // Jump out of nested loops
        }
    }
}
cout << "Not found";
return;

found:
    cout << "Found!";

// Better alternative: use function with return
bool search() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == target) {
                return true;  // Cleaner than goto
            }
        }
    }
    return false;
}

// Or use flag variable
bool found = false;
for (int i = 0; i < rows && !found; i++) {
    for (int j = 0; j < cols && !found; j++) {
        if (matrix[i][j] == target) {
            found = true;
        }
    }
}
```

**return Statement (in functions):**
```cpp
// Exits function immediately

int findIndex(const vector<int>& vec, int target) {
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] == target) {
            return i;  // Exit function, return value
        }
    }
    return -1;  // Not found
}

// Multiple return points
int processValue(int x) {
    if (x < 0) return -1;     // Error code
    if (x == 0) return 0;     // Special case
    return x * 2;             // Normal case
}

// Early return for validation
void processData(const string& data) {
    if (data.empty()) return;      // Guard clause
    if (!isValid(data)) return;    // Guard clause
    // Main processing logic
}
```

#### Loop Control Best Practices

```cpp
// 1. Prefer range-based for when possible
for (const auto& item : container) {  // Clear and safe
    process(item);
}

// 2. Use meaningful variable names
for (int studentIndex = 0; studentIndex < numStudents; studentIndex++) {
    // Better than: for (int i = 0; i < n; i++)
}

// 3. Avoid modifying loop counter inside loop
for (int i = 0; i < n; i++) {
    // Don't do: i += 2; (confusing)
}

// 4. Be careful with unsigned types in loops
for (unsigned int i = 10; i >= 0; i--) {  // INFINITE LOOP!
    // i never becomes negative
}

// Fix: use signed type
for (int i = 10; i >= 0; i--) {  // OK
}

// 5. Don't compare floating-point with ==
for (double x = 0; x != 1.0; x += 0.1) {  // May be infinite!
    // 0.1 can't be represented exactly
}

// Fix: use <
for (double x = 0; x < 1.0; x += 0.1) {  // OK
}

// 6. Cache container size if not changing
int size = vec.size();  // Cache size
for (int i = 0; i < size; i++) {
    // Better than calling vec.size() every iteration
}

// 7. Use const correctness
for (const auto& item : items) {  // Can't accidentally modify
    // Read-only access
}
```

### 3.2 Functions

```cpp
// Function declaration (prototype)
return_type function_name(parameters);

// Function definition
return_type function_name(parameters) {
    // function body
    return value;
}

// Example
int add(int a, int b) {
    return a + b;
}

// Void function (no return value)
void printMessage() {
    cout << "Hello!";
}

// Function with default parameters
int multiply(int a, int b = 2) {
    return a * b;
}
```

#### Pass by Value vs Pass by Reference
```cpp
// Pass by value (copy)
void func1(int x) {
    x = 10;  // Original unchanged
}

// Pass by reference
void func2(int &x) {
    x = 10;  // Original modified
}

// Pass by const reference (efficient, read-only)
void func3(const string &str) {
    // Cannot modify str
}
```

#### Inline Functions
```cpp
inline int square(int x) {
    return x * x;
}
// Suggests compiler to insert code directly (optimization)
```

#### Recursion
```cpp
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}
```

### 3.3 Overloads and Templates

#### Function Overloading
```cpp
int sum(int a, int b) {
    return a + b;
}

double sum(double a, double b) {
    return a + b;
}

int sum(int a, int b, int c) {
    return a + b + c;
}
```

#### Function Templates
```cpp
template <typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}

// Usage
int i = maximum(10, 20);        // T = int
double d = maximum(3.5, 2.1);   // T = double
```

#### Multiple Template Parameters
```cpp
template <typename T, typename U>
T maximum(T a, U b) {
    return (a > b) ? a : static_cast<T>(b);
}
```

### 3.4 Name Visibility (Namespaces)

```cpp
// Define namespace
namespace MyNamespace {
    int value = 5;
    void myFunction() {
        // code
    }
}

// Using namespace
using namespace MyNamespace;
value = 10;  // Direct access

// Scope resolution
MyNamespace::value = 10;
MyNamespace::myFunction();

// Using specific elements
using MyNamespace::value;

// Nested namespaces
namespace Outer {
    namespace Inner {
        int x = 5;
    }
}
```

---

## 4. Compound Data Types

### 4.1 Arrays

```cpp
// Declaration
int arr[5];                    // Uninitialized
int arr[5] = {1, 2, 3, 4, 5}; // Initialized
int arr[] = {1, 2, 3};        // Size inferred
int arr[5] = {1, 2};          // Partial initialization (rest = 0)

// Access elements
arr[0] = 10;
int x = arr[2];

// Multidimensional arrays
int matrix[3][4];  // 3 rows, 4 columns
int matrix[2][3] = {{1, 2, 3}, {4, 5, 6}};

// Array as function parameter
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
}
```

### 4.2 Character Sequences (C-Strings)

```cpp
// C-style strings (null-terminated)
char str1[20];
char str2[] = "Hello";
char str3[10] = {'H', 'i', '\0'};

// String functions (#include <cstring>)
strlen(str);      // Length
strcpy(dest, src); // Copy
strcat(dest, src); // Concatenate
strcmp(s1, s2);   // Compare
strncpy, strncat, strncmp // Safe versions with length limit

// C++ string class (#include <string>)
string str = "Hello";
str = str + " World";  // Concatenation
str += "!";
int len = str.length();
str[0] = 'h';
string sub = str.substr(0, 5);  // Substring
```

### 4.3 Pointers (Comprehensive Guide)

Pointers are one of the most powerful and important features in C++. They store memory addresses.

#### Pointer Basics

**Declaration and Initialization:**
```cpp
// Declaration
int *ptr;          // Pointer to int (uninitialized - dangerous!)
double *dptr;      // Pointer to double
char *cptr;        // Pointer to char

// Better: Initialize immediately
int *ptr = nullptr;  // C++11 (preferred)
int *ptr = NULL;     // Older C++ (macro, value is 0)
int *ptr = 0;        // Even older style

// Pointer to variable
int x = 42;
int *ptr = &x;       // ptr now holds address of x

// Multiple pointers
int *p1, *p2, *p3;   // All are pointers
int* p1, p2, p3;     // Only p1 is pointer! (p2, p3 are int)
```

**Address-of Operator (&):**
```cpp
int value = 100;
int *ptr = &value;   // Get address of value

cout << value;       // Prints: 100
cout << &value;      // Prints: memory address (e.g., 0x7ffd5e8b9abc)
cout << ptr;         // Prints: same memory address
```

**Dereference Operator (*):**
```cpp
int x = 42;
int *ptr = &x;

// Dereference to get value
cout << *ptr;        // Prints: 42 (value at address)

// Modify through pointer
*ptr = 100;          // Changes x to 100
cout << x;           // Prints: 100

// Reading: "ptr points to x, *ptr gives us x's value"
```

**Pointer Size:**
```cpp
// All pointers have the same size (depends on architecture)
int *p1;
double *p2;
char *p3;

cout << sizeof(p1);  // 4 bytes (32-bit) or 8 bytes (64-bit)
cout << sizeof(p2);  // Same size
cout << sizeof(p3);  // Same size

// Size of pointer vs size of pointed type
int x = 42;
int *ptr = &x;
cout << sizeof(ptr);   // Size of pointer (4 or 8)
cout << sizeof(*ptr);  // Size of int (4)
cout << sizeof(x);     // Size of int (4)
```

#### Null Pointers

```cpp
// Different ways to represent null
int *ptr1 = nullptr;  // C++11 (type-safe, preferred)
int *ptr2 = NULL;     // C macro (#define NULL 0)
int *ptr3 = 0;        // Integer zero

// Why nullptr is better
void func(int x);
void func(int *ptr);

func(NULL);      // Ambiguous! Which function?
func(nullptr);   // Unambiguous - calls func(int*)

// Always check before dereferencing
if (ptr != nullptr) {
    *ptr = 42;  // Safe
}

// Or simply
if (ptr) {      // Implicitly checks != nullptr
    *ptr = 42;
}
```

#### Pointer Arithmetic

```cpp
int arr[] = {10, 20, 30, 40, 50};
int *ptr = arr;  // Points to first element

// Addition
ptr + 1;         // Points to next element (arr[1])
ptr + 2;         // Points to arr[2]

// The "1" means 1 element, not 1 byte!
// For int (4 bytes), ptr+1 means address+4

cout << ptr;     // Address of arr[0]
cout << ptr+1;   // Address of arr[1] (4 bytes higher)

// Dereferencing with arithmetic
cout << *ptr;       // 10 (arr[0])
cout << *(ptr+1);   // 20 (arr[1])
cout << *(ptr+2);   // 30 (arr[2])

// Prefix/postfix with pointers
int *p = arr;
cout << *p++;       // Print arr[0], then move to arr[1]
cout << *++p;       // Move to arr[2], then print

cout << (*p)++;     // Print arr[2], then increment value
cout << ++(*p);     // Increment value, then print

// Subtraction
int *p1 = &arr[4];
int *p2 = &arr[1];
ptrdiff_t diff = p1 - p2;  // 3 (element difference)

// Array indexing is pointer arithmetic!
arr[i]  <==>  *(arr + i)
ptr[i]  <==>  *(ptr + i)

// Comparison
if (ptr1 < ptr2) {  // ptr1 points to earlier element
    // ...
}
```

**Pointer Arithmetic Example:**
```cpp
int numbers[] = {10, 20, 30, 40, 50};
int *ptr = numbers;

// Traverse array using pointer
for (int i = 0; i < 5; i++) {
    cout << *(ptr + i) << " ";  // 10 20 30 40 50
}

// Or increment pointer
ptr = numbers;
for (int i = 0; i < 5; i++) {
    cout << *ptr << " ";
    ptr++;  // Move to next element
}

// Traversing backwards
ptr = &numbers[4];  // Last element
for (int i = 0; i < 5; i++) {
    cout << *ptr << " ";
    ptr--;  // Move backwards
}
```

#### Pointers and Arrays

```cpp
int arr[5] = {1, 2, 3, 4, 5};

// Array name is a pointer to first element
int *ptr = arr;  // Same as: int *ptr = &arr[0];

// These are equivalent:
arr[i]          // Array indexing
*(arr + i)      // Pointer arithmetic
ptr[i]          // Pointer indexing
*(ptr + i)      // Pointer arithmetic

// Important difference: array name is constant pointer
arr = ptr;       // ERROR! Can't reassign array name
ptr = arr;       // OK, ptr is a regular pointer

// Passing arrays to functions (actually passes pointer)
void func(int arr[]) {  // Actually: int *arr
    // arr is a pointer, not an array
    // sizeof(arr) gives size of pointer, not array!
}

// Better: pass size explicitly
void func(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i];
    }
}
```

#### Pointer to Pointer (Multiple Indirection)

```cpp
int x = 42;
int *ptr = &x;       // Pointer to int
int **pptr = &ptr;   // Pointer to pointer to int

cout << x;           // 42 (value)
cout << *ptr;        // 42 (dereference once)
cout << **pptr;      // 42 (dereference twice)

cout << &x;          // Address of x
cout << ptr;         // Address of x (same as above)
cout << *pptr;       // Address of x (same as above)
cout << &ptr;        // Address of ptr
cout << pptr;        // Address of ptr (same as above)

// Modification through double pointer
**pptr = 100;        // Changes x to 100
*pptr = nullptr;     // Changes ptr to nullptr

// Use case: 2D arrays (arrays of pointers)
int rows = 3, cols = 4;
int **matrix = new int*[rows];
for (int i = 0; i < rows; i++) {
    matrix[i] = new int[cols];
}

// Access: matrix[i][j]

// Cleanup
for (int i = 0; i < rows; i++) {
    delete[] matrix[i];
}
delete[] matrix;
```

#### const with Pointers (Very Important!)

```cpp
int value = 100;
int other = 200;

// 1. Pointer to const int
//    Can't change value through pointer, but can change what it points to
const int *ptr1 = &value;
int const *ptr1 = &value;    // Same as above
*ptr1 = 50;       // ERROR! Can't modify value
ptr1 = &other;    // OK, can point to different address

// 2. Const pointer to int
//    Can change value, but can't change what it points to
int * const ptr2 = &value;
*ptr2 = 50;       // OK, can modify value
ptr2 = &other;    // ERROR! Can't change address

// 3. Const pointer to const int
//    Can't change value OR what it points to
const int * const ptr3 = &value;
*ptr3 = 50;       // ERROR! Can't modify value
ptr3 = &other;    // ERROR! Can't change address

// Mnemonic: Read right to left
// const int *ptr = "pointer to const int"
// int * const ptr = "const pointer to int"
// const int * const ptr = "const pointer to const int"

// Practical use: Function parameters
void print(const int *arr, int size) {
    // arr points to const int - can't modify array
    for (int i = 0; i < size; i++) {
        cout << arr[i];
        // arr[i] = 0;  // ERROR! Can't modify
    }
}

// Why use const?
// - Prevents accidental modification
// - Allows passing const arrays to functions
// - Compiler can optimize better
// - Documents intent
```

#### Pointers and Functions

**Returning Pointers:**
```cpp
// Return pointer to static variable (OK)
int* getStaticValue() {
    static int value = 42;  // Static - persists after function returns
    return &value;          // Safe
}

// Return pointer to local variable (DANGER!)
int* getDangerousValue() {
    int value = 42;         // Local - destroyed when function returns
    return &value;          // DANGEROUS! Dangling pointer
}

// Return dynamically allocated memory (OK, but caller must delete)
int* createArray(int size) {
    int *arr = new int[size];
    return arr;  // OK, but caller responsible for delete[]
}

// Using the function
int *ptr = createArray(10);
// Use ptr...
delete[] ptr;  // Caller must remember to delete!

// Modern C++: Use smart pointers instead
unique_ptr<int[]> createArray(int size) {
    return make_unique<int[]>(size);  // Automatic cleanup
}
```

**Pass by Pointer:**
```cpp
// Allows function to modify original variable
void increment(int *ptr) {
    (*ptr)++;  // Parentheses needed due to precedence
}

int x = 10;
increment(&x);  // Pass address
cout << x;      // 11 (modified)

// Compare with pass by value
void incrementValue(int val) {
    val++;  // Modifies copy only
}

int y = 10;
incrementValue(y);  // Pass value (copy)
cout << y;          // 10 (unchanged)

// Pass by reference (modern alternative)
void incrementRef(int &ref) {
    ref++;  // No pointer syntax needed
}

int z = 10;
incrementRef(z);  // Cleaner syntax
cout << z;        // 11 (modified)
```

#### Pointers to Functions

```cpp
// Function pointer declaration
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }

// Declare function pointer
int (*funcPtr)(int, int);

// Assign function address
funcPtr = add;
funcPtr = &add;  // Same as above (& is optional)

// Call through function pointer
int result = funcPtr(5, 3);      // 8
int result = (*funcPtr)(5, 3);   // Same (explicit dereference)

// Using typedef for readability
typedef int (*BinaryOp)(int, int);
BinaryOp operation = add;
result = operation(10, 5);

// Using (modern, preferred)
using BinaryOp = int (*)(int, int);

// Array of function pointers
int (*operations[])(int, int) = {add, subtract};
result = operations[0](10, 5);  // Calls add
result = operations[1](10, 5);  // Calls subtract

// Passing function pointer to function
void calculate(int (*op)(int, int), int a, int b) {
    cout << op(a, b);
}

calculate(add, 5, 3);      // Pass add function
calculate(subtract, 5, 3); // Pass subtract function

// Callback example
void forEach(int arr[], int size, void (*callback)(int)) {
    for (int i = 0; i < size; i++) {
        callback(arr[i]);
    }
}

void printDouble(int x) {
    cout << x * 2 << " ";
}

int nums[] = {1, 2, 3, 4, 5};
forEach(nums, 5, printDouble);  // Prints: 2 4 6 8 10
```

#### Void Pointers (Generic Pointers)

```cpp
// void* can point to any type
void *vptr;

int x = 42;
double y = 3.14;
char c = 'A';

vptr = &x;  // OK, points to int
vptr = &y;  // OK, points to double
vptr = &c;  // OK, points to char

// Can't dereference void* directly
// cout << *vptr;  // ERROR!

// Must cast before dereferencing
int *iptr = (int*)vptr;
cout << *iptr;  // OK after cast

// Modern C++: Use static_cast
iptr = static_cast<int*>(vptr);

// Use case: Generic functions (like malloc)
void* allocate(size_t size) {
    return malloc(size);
}

int *arr = (int*)allocate(10 * sizeof(int));

// C++: Prefer templates over void* for type safety
template<typename T>
T* allocate(size_t count) {
    return new T[count];
}
```

#### Smart Pointers (Modern C++ Alternative)

```cpp
#include <memory>

// unique_ptr - Exclusive ownership
unique_ptr<int> uptr = make_unique<int>(42);
*uptr = 100;
// Automatically deleted when out of scope

// Can't copy unique_ptr
// unique_ptr<int> uptr2 = uptr;  // ERROR!

// But can move
unique_ptr<int> uptr2 = move(uptr);  // Transfer ownership

// shared_ptr - Shared ownership (reference counting)
shared_ptr<int> sptr1 = make_shared<int>(42);
shared_ptr<int> sptr2 = sptr1;  // Both own the object
cout << sptr1.use_count();  // 2

// Object deleted when last shared_ptr is destroyed

// weak_ptr - Non-owning reference (breaks cycles)
weak_ptr<int> wptr = sptr1;  // Doesn't increase ref count
if (auto locked = wptr.lock()) {  // Try to get shared_ptr
    // Use locked pointer
}

// Prefer smart pointers over raw pointers!
```

#### Common Pointer Pitfalls and Best Practices

**Dangling Pointers:**
```cpp
// 1. Pointing to deleted memory
int *ptr = new int(42);
delete ptr;
*ptr = 100;  // DANGER! Dangling pointer

// Fix: Set to nullptr after delete
ptr = nullptr;

// 2. Pointing to out-of-scope variable
int* getPointer() {
    int x = 42;
    return &x;  // DANGER! x is destroyed
}

// 3. Using after array goes out of scope
int* getArray() {
    int arr[5];
    return arr;  // DANGER! arr is destroyed
}
```

**Memory Leaks:**
```cpp
// Forgetting to delete
int *ptr = new int(42);
// ... use ptr ...
// Forgot: delete ptr;  // Memory leak!

// Losing pointer before deleting
ptr = new int(10);
ptr = new int(20);  // Memory leak! Lost first allocation

// Fix: Delete before reassigning
delete ptr;
ptr = new int(20);
```

**Wild Pointers:**
```cpp
// Uninitialized pointer
int *ptr;  // Contains garbage address
*ptr = 42; // DANGER! Writing to random memory

// Fix: Always initialize
int *ptr = nullptr;
```

**Best Practices:**
```cpp
// 1. Always initialize pointers
int *ptr = nullptr;  // ✓ Good
int *ptr;            // ✗ Bad

// 2. Check before dereferencing
if (ptr != nullptr) {
    *ptr = 42;
}

// 3. Set to nullptr after delete
delete ptr;
ptr = nullptr;

// 4. Use smart pointers when possible
unique_ptr<int> ptr = make_unique<int>(42);  // No manual delete needed!

// 5. Prefer references over pointers
void func(int& ref);  // Better than: void func(int* ptr);

// 6. Use const correctness
void process(const int *ptr);  // Can't modify through ptr

// 7. Delete[] for arrays, delete for single objects
int *single = new int;
int *array = new int[10];
delete single;   // ✓
delete[] array;  // ✓
delete array;    // ✗ Undefined behavior!

// 8. Avoid pointer arithmetic on non-arrays
int x = 42;
int *ptr = &x;
ptr++;  // ✗ Undefined behavior! (x is not an array)

// 9. Check return values
int *ptr = new (nothrow) int[huge_size];
if (ptr == nullptr) {
    // Allocation failed
}

// 10. RAII - Resource Acquisition Is Initialization
// Let objects manage resources (constructors/destructors)
class ArrayWrapper {
    int *arr;
public:
    ArrayWrapper(int size) : arr(new int[size]) {}
    ~ArrayWrapper() { delete[] arr; }  // Automatic cleanup
};
```

### 4.4 Dynamic Memory

```cpp
// new operator - allocate memory
int *ptr = new int;           // Single int
*ptr = 5;

int *arr = new int[10];       // Array of 10 ints
arr[0] = 1;

// delete operator - deallocate memory
delete ptr;                   // Delete single object
delete[] arr;                 // Delete array

// Check allocation
int *ptr = new (nothrow) int[1000000];
if (ptr == nullptr) {
    // Allocation failed
}

// Memory management example
int *data = new int[size];
// Use data...
delete[] data;
data = nullptr;  // Good practice
```

### 4.5 Data Structures (Structs)

```cpp
// Define structure
struct Product {
    int weight;
    double price;
    string name;
};

// Declare and initialize
Product apple;
apple.weight = 200;
apple.price = 1.99;

// Initialize at declaration
Product banana = {150, 0.99, "Banana"};

// C++11 uniform initialization
Product orange{300, 2.49, "Orange"};

// Array of structures
Product inventory[100];
inventory[0].weight = 250;

// Pointers to structures
Product *pProduct = &apple;
pProduct->weight = 220;        // Arrow operator
(*pProduct).price = 2.49;      // Equivalent using dot

// Nested structures
struct Date {
    int day, month, year;
};

struct Person {
    string name;
    Date birthdate;
};

Person p;
p.birthdate.year = 1990;

// typedef for convenience
typedef struct Product Item;
Item myItem;
```

### 4.6 Other Data Types

#### Unions
```cpp
union MyUnion {
    int i;
    float f;
    char c;
};
// All members share same memory location
```

#### Enumerations
```cpp
enum Color { RED, GREEN, BLUE };  // 0, 1, 2
enum Status { OK = 200, NOT_FOUND = 404, ERROR = 500 };

Color myColor = RED;

// Enum class (C++11) - type-safe
enum class TrafficLight { Red, Yellow, Green };
TrafficLight light = TrafficLight::Red;
```

#### Type Aliases
```cpp
typedef unsigned long ulong;
using uint = unsigned int;  // C++11 style
```

---

## 5. Object-Oriented Programming (Classes)

### 5.1 Classes (I) - Basics

```cpp
class Rectangle {
private:
    int width, height;  // Private members
    
public:
    // Constructor
    Rectangle(int w, int h) : width(w), height(h) {}
    
    // Member functions
    void setDimensions(int w, int h) {
        width = w;
        height = h;
    }
    
    int area() {
        return width * height;
    }
    
    int getWidth() { return width; }
    int getHeight() { return height; }
};

// Usage
Rectangle rect(10, 5);
cout << rect.area();  // 50
```

#### Access Specifiers
- **private**: Accessible only within class (default for class)
- **public**: Accessible from anywhere
- **protected**: Accessible in class and derived classes

#### Member Functions
```cpp
class MyClass {
public:
    // Declaration inside class
    void method1() {
        // Implementation inside
    }
    
    // Declaration only
    void method2();
};

// Definition outside class
void MyClass::method2() {
    // Implementation outside
}
```

#### Constructors
```cpp
class MyClass {
public:
    // Default constructor
    MyClass() {
        // Initialize members
    }
    
    // Parameterized constructor
    MyClass(int x, int y) : a(x), b(y) {
        // Member initializer list
    }
    
    // Copy constructor
    MyClass(const MyClass &obj) {
        a = obj.a;
        b = obj.b;
    }
    
private:
    int a, b;
};
```

### 5.2 Classes (II) - Templates

#### Class Templates
```cpp
template <typename T>
class Pair {
private:
    T first, second;
    
public:
    Pair(T a, T b) : first(a), second(b) {}
    
    T getMax() {
        return (first > second) ? first : second;
    }
};

// Usage
Pair<int> intPair(10, 20);
Pair<double> doublePair(3.5, 2.8);
```

#### Multiple Template Parameters
```cpp
template <typename T, typename U>
class Pair {
    T first;
    U second;
public:
    Pair(T a, U b) : first(a), second(b) {}
};

Pair<int, string> p(1, "Hello");
```

#### Template Specialization
```cpp
template <typename T>
class Container {
    T element;
public:
    T increase() { return ++element; }
};

// Specialization for char
template <>
class Container<char> {
    char element;
public:
    char uppercase() {
        if (element >= 'a' && element <= 'z')
            element += 'A' - 'a';
        return element;
    }
};
```

### 5.3 Special Members

#### Destructor
```cpp
class MyClass {
public:
    MyClass() {
        data = new int[100];
    }
    
    ~MyClass() {  // Destructor
        delete[] data;
    }
    
private:
    int *data;
};
```

#### Copy Constructor and Assignment Operator
```cpp
class MyClass {
public:
    // Copy constructor
    MyClass(const MyClass &obj) {
        data = new int[100];
        // Deep copy
        for (int i = 0; i < 100; i++)
            data[i] = obj.data[i];
    }
    
    // Assignment operator
    MyClass& operator=(const MyClass &obj) {
        if (this != &obj) {  // Self-assignment check
            delete[] data;
            data = new int[100];
            // Deep copy
            for (int i = 0; i < 100; i++)
                data[i] = obj.data[i];
        }
        return *this;
    }
    
private:
    int *data;
};
```

#### Move Semantics (C++11)
```cpp
class MyClass {
public:
    // Move constructor
    MyClass(MyClass &&obj) noexcept {
        data = obj.data;
        obj.data = nullptr;
    }
    
    // Move assignment
    MyClass& operator=(MyClass &&obj) noexcept {
        if (this != &obj) {
            delete[] data;
            data = obj.data;
            obj.data = nullptr;
        }
        return *this;
    }
    
private:
    int *data;
};
```

#### Operator Overloading
```cpp
class Complex {
private:
    double real, imag;
    
public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}
    
    // Overload + operator
    Complex operator+(const Complex &c) {
        return Complex(real + c.real, imag + c.imag);
    }
    
    // Overload << operator (friend function)
    friend ostream& operator<<(ostream &out, const Complex &c) {
        out << c.real << " + " << c.imag << "i";
        return out;
    }
};
```

### 5.4 Friendship and Inheritance

#### Friend Functions and Classes
```cpp
class Box {
private:
    double width;
    
public:
    Box(double w) : width(w) {}
    
    // Friend function
    friend void printWidth(Box &b);
    
    // Friend class
    friend class BoxPrinter;
};

void printWidth(Box &b) {
    cout << b.width;  // Can access private member
}

class BoxPrinter {
public:
    void print(Box &b) {
        cout << b.width;  // Can access private member
    }
};
```

#### Inheritance
```cpp
// Base class
class Shape {
protected:
    int width, height;
    
public:
    void setDimensions(int w, int h) {
        width = w;
        height = h;
    }
};

// Derived class
class Rectangle : public Shape {
public:
    int area() {
        return width * height;
    }
};

// Multiple inheritance
class Square : public Rectangle, public Drawable {
    // Inherits from both
};
```

#### Types of Inheritance
```cpp
class Derived : public Base { };     // Public inheritance
class Derived : protected Base { };  // Protected inheritance
class Derived : private Base { };    // Private inheritance
```

### 5.5 Polymorphism

#### Virtual Functions
```cpp
class Base {
public:
    virtual void display() {  // Virtual function
        cout << "Base display";
    }
    
    virtual ~Base() {}  // Virtual destructor
};

class Derived : public Base {
public:
    void display() override {  // Override keyword (C++11)
        cout << "Derived display";
    }
};

// Polymorphism in action
Base *ptr = new Derived();
ptr->display();  // Calls Derived::display()
delete ptr;
```

#### Pure Virtual Functions (Abstract Classes)
```cpp
class Shape {
public:
    virtual double area() = 0;  // Pure virtual function
    virtual ~Shape() {}
};

class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(double r) : radius(r) {}
    
    double area() override {
        return 3.14159 * radius * radius;
    }
};

// Cannot instantiate Shape (abstract class)
// Shape s;  // Error!
Circle c(5.0);
```

#### Virtual Destructors
```cpp
class Base {
public:
    virtual ~Base() {
        // Cleanup base
    }
};

class Derived : public Base {
public:
    ~Derived() {
        // Cleanup derived
    }
};

Base *ptr = new Derived();
delete ptr;  // Calls both destructors correctly
```

---

## 6. Other Language Features

### 6.1 Type Conversions

#### Implicit Conversion
```cpp
int i = 10;
double d = i;  // Implicit conversion (promotion)

double x = 3.14;
int y = x;  // Implicit conversion (truncation)
```

#### Explicit Conversion (Casting)

**C-Style Cast**
```cpp
double d = 3.14;
int i = (int)d;
```

**C++ Style Casts**
```cpp
// static_cast - compile-time cast
double d = 3.14;
int i = static_cast<int>(d);

// dynamic_cast - runtime cast (for polymorphism)
Base *basePtr = new Derived();
Derived *derivedPtr = dynamic_cast<Derived*>(basePtr);
if (derivedPtr) {
    // Cast successful
}

// const_cast - remove const qualifier
const int *constPtr = &value;
int *ptr = const_cast<int*>(constPtr);

// reinterpret_cast - low-level reinterpretation
int i = 10;
int *ptr = &i;
char *charPtr = reinterpret_cast<char*>(ptr);
```

### 6.2 Exceptions

#### Try-Catch Block
```cpp
try {
    // Code that may throw exception
    if (denominator == 0)
        throw runtime_error("Division by zero");
    result = numerator / denominator;
}
catch (runtime_error &e) {
    cout << "Error: " << e.what() << endl;
}
catch (exception &e) {
    cout << "General exception: " << e.what() << endl;
}
catch (...) {
    cout << "Unknown exception" << endl;
}
```

#### Standard Exception Classes
```cpp
#include <stdexcept>

logic_error          // Logic errors
    invalid_argument
    domain_error
    length_error
    out_of_range

runtime_error        // Runtime errors
    range_error
    overflow_error
    underflow_error
```

#### Custom Exceptions
```cpp
class MyException : public exception {
private:
    string message;
    
public:
    MyException(const string &msg) : message(msg) {}
    
    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Usage
try {
    throw MyException("Custom error occurred");
}
catch (MyException &e) {
    cout << e.what() << endl;
}
```

#### Exception Specifications
```cpp
// noexcept specifier (C++11)
void myFunction() noexcept {
    // Guaranteed not to throw
}

// Conditional noexcept
template <typename T>
void process(T value) noexcept(noexcept(T())) {
    // noexcept if T's constructor is noexcept
}
```

### 6.3 Preprocessor Directives

#### Include Directives
```cpp
#include <iostream>   // System header
#include "myheader.h" // User header
```

#### Macro Definitions
```cpp
#define PI 3.14159
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define SQUARE(x) ((x) * (x))

// Undefine
#undef PI
```

#### Conditional Compilation
```cpp
#define DEBUG

#ifdef DEBUG
    cout << "Debug mode" << endl;
#endif

#ifndef MYHEADER_H
#define MYHEADER_H
    // Header content
#endif

#if defined(WINDOWS)
    // Windows-specific code
#elif defined(LINUX)
    // Linux-specific code
#else
    // Other platforms
#endif
```

#### Predefined Macros
```cpp
__FILE__     // Current filename
__LINE__     // Current line number
__DATE__     // Compilation date
__TIME__     // Compilation time
__cplusplus  // C++ standard version
```

#### Pragma Directives
```cpp
#pragma once  // Include guard (alternative to #ifndef)
#pragma pack(1)  // Structure packing
```

---

## 7. Standard Library

### 7.1 Input/Output with Files

#### File Streams
```cpp
#include <fstream>

// Output file stream
ofstream outFile;
outFile.open("output.txt");
outFile << "Writing to file" << endl;
outFile.close();

// Input file stream
ifstream inFile;
inFile.open("input.txt");
if (inFile.is_open()) {
    string line;
    while (getline(inFile, line)) {
        cout << line << endl;
    }
    inFile.close();
}

// File stream (both input and output)
fstream file;
file.open("data.txt", ios::in | ios::out);
```

#### File Open Modes
```cpp
ios::in      // Input (read)
ios::out     // Output (write)
ios::app     // Append to end
ios::ate     // Set position at end
ios::trunc   // Truncate file
ios::binary  // Binary mode

// Combine modes with |
file.open("file.txt", ios::out | ios::app);
```

#### File Operations
```cpp
// Check if file opened successfully
if (!file.is_open()) {
    cerr << "Error opening file" << endl;
}

// Check end of file
while (!file.eof()) {
    // Read data
}

// Get file position
streampos position = file.tellg();  // Get read position
streampos position = file.tellp();  // Get write position

// Set file position
file.seekg(0, ios::beg);  // Beginning
file.seekg(0, ios::end);  // End
file.seekg(10, ios::cur); // 10 bytes from current

// Read/Write binary data
struct Data {
    int id;
    double value;
};

Data d = {1, 3.14};
file.write((char*)&d, sizeof(Data));
file.read((char*)&d, sizeof(Data));
```

### 7.2 Standard Template Library (STL)

#### Containers

**Vector** (Dynamic Array)
```cpp
#include <vector>

vector<int> v;
v.push_back(10);       // Add element
v.pop_back();          // Remove last element
v.size();              // Number of elements
v.empty();             // Check if empty
v.clear();             // Remove all elements
v[0] = 5;              // Access element
v.at(0) = 5;           // Access with bounds checking

// Initialize
vector<int> v1(10);           // 10 elements, default value
vector<int> v2(10, 5);        // 10 elements, all 5
vector<int> v3 = {1, 2, 3};   // Initializer list
```

**List** (Doubly Linked List)
```cpp
#include <list>

list<int> lst;
lst.push_back(10);
lst.push_front(5);
lst.pop_back();
lst.pop_front();
lst.sort();
lst.reverse();
```

**Deque** (Double-Ended Queue)
```cpp
#include <deque>

deque<int> dq;
dq.push_back(10);
dq.push_front(5);
dq.pop_back();
dq.pop_front();
```

**Stack** (LIFO)
```cpp
#include <stack>

stack<int> s;
s.push(10);
int top = s.top();
s.pop();
s.empty();
s.size();
```

**Queue** (FIFO)
```cpp
#include <queue>

queue<int> q;
q.push(10);
int front = q.front();
int back = q.back();
q.pop();
```

**Priority Queue** (Heap)
```cpp
#include <queue>

priority_queue<int> pq;  // Max heap by default
pq.push(10);
int top = pq.top();
pq.pop();

// Min heap
priority_queue<int, vector<int>, greater<int>> minHeap;
```

**Set** (Ordered Unique Elements)
```cpp
#include <set>

set<int> s;
s.insert(10);
s.erase(10);
s.find(10);  // Returns iterator
s.count(10); // 0 or 1
s.size();

// Unordered set (hash table)
#include <unordered_set>
unordered_set<int> us;
```

**Map** (Key-Value Pairs)
```cpp
#include <map>

map<string, int> m;
m["apple"] = 5;
m.insert({"banana", 3});
m.erase("apple");
m.find("banana");  // Returns iterator
m.count("apple");  // 0 or 1

// Iterate
for (auto &pair : m) {
    cout << pair.first << ": " << pair.second << endl;
}

// Unordered map (hash table)
#include <unordered_map>
unordered_map<string, int> um;
```

**Pair**
```cpp
#include <utility>

pair<int, string> p(1, "Hello");
cout << p.first << " " << p.second;

// Make pair
auto p2 = make_pair(2, "World");
```

#### Iterators
```cpp
vector<int> v = {1, 2, 3, 4, 5};

// Iterator types
vector<int>::iterator it;
vector<int>::const_iterator cit;
vector<int>::reverse_iterator rit;

// Basic iteration
for (auto it = v.begin(); it != v.end(); ++it) {
    cout << *it << " ";
}

// Reverse iteration
for (auto rit = v.rbegin(); rit != v.rend(); ++rit) {
    cout << *rit << " ";
}

// Range-based for loop (C++11)
for (int x : v) {
    cout << x << " ";
}

// With reference (modify elements)
for (int &x : v) {
    x *= 2;
}
```

#### Algorithms
```cpp
#include <algorithm>

vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};

// Sorting
sort(v.begin(), v.end());           // Ascending
sort(v.begin(), v.end(), greater<int>()); // Descending

// Searching
auto it = find(v.begin(), v.end(), 5);
bool found = binary_search(v.begin(), v.end(), 5);

// Min/Max
int minVal = *min_element(v.begin(), v.end());
int maxVal = *max_element(v.begin(), v.end());

// Reverse
reverse(v.begin(), v.end());

// Count
int count = count(v.begin(), v.end(), 1);

// Unique (remove consecutive duplicates)
sort(v.begin(), v.end());
auto last = unique(v.begin(), v.end());
v.erase(last, v.end());

// Transform
transform(v.begin(), v.end(), v.begin(), [](int x) { return x * 2; });

// Accumulate (sum)
#include <numeric>
int sum = accumulate(v.begin(), v.end(), 0);

// For each
for_each(v.begin(), v.end(), [](int x) { cout << x << " "; });
```

#### Lambda Expressions (C++11)
```cpp
// Basic lambda
auto lambda = []() { cout << "Hello"; };
lambda();

// With parameters
auto add = [](int a, int b) { return a + b; };
int result = add(5, 3);

// Capture clause
int x = 10;
auto func1 = [x]() { return x; };      // Capture by value
auto func2 = [&x]() { x++; };          // Capture by reference
auto func3 = [=]() { return x + y; };  // Capture all by value
auto func4 = [&]() { x++; y++; };      // Capture all by reference
auto func5 = [x, &y]() { };            // Mixed capture

// Use with algorithms
vector<int> v = {1, 2, 3, 4, 5};
sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
```

#### Smart Pointers (C++11)
```cpp
#include <memory>

// unique_ptr - exclusive ownership
unique_ptr<int> ptr1(new int(5));
unique_ptr<int> ptr2 = make_unique<int>(10);
*ptr2 = 20;
// Cannot copy, but can move
unique_ptr<int> ptr3 = move(ptr2);

// shared_ptr - shared ownership
shared_ptr<int> sptr1 = make_shared<int>(5);
shared_ptr<int> sptr2 = sptr1;  // Reference count = 2
sptr1.use_count();  // Get reference count

// weak_ptr - non-owning reference
weak_ptr<int> wptr = sptr1;
if (auto sptr = wptr.lock()) {  // Convert to shared_ptr
    // Use sptr
}
```

#### String Operations
```cpp
#include <string>

string str = "Hello World";

// Basic operations
str.length() or str.size();
str.empty();
str.clear();

// Access
str[0];
str.at(0);
str.front();
str.back();

// Modification
str.append(" C++");
str += " Programming";
str.insert(5, ",");
str.erase(5, 1);
str.replace(0, 5, "Hi");

// Substring
string sub = str.substr(0, 5);

// Find
size_t pos = str.find("World");
if (pos != string::npos) {
    // Found
}

// Compare
str.compare("Hello");
str1 == str2;

// Conversion
int num = stoi("123");
double d = stod("3.14");
string s = to_string(123);
```

---

## Additional C++11/14/17 Features

### Auto Keyword
```cpp
auto x = 5;           // int
auto y = 3.14;        // double
auto s = "Hello";     // const char*
auto v = vector<int>(); // vector<int>
```

### Range-Based For Loop
```cpp
vector<int> v = {1, 2, 3, 4, 5};
for (int x : v) {
    cout << x << " ";
}
```

### nullptr
```cpp
int *ptr = nullptr;  // Better than NULL
```

### Enum Class
```cpp
enum class Color { Red, Green, Blue };
Color c = Color::Red;
```

### Uniform Initialization
```cpp
int x{5};
vector<int> v{1, 2, 3, 4, 5};
```

### Move Semantics
```cpp
vector<int> v1 = {1, 2, 3};
vector<int> v2 = move(v1);  // v1 is now empty
```

### Variadic Templates
```cpp
template<typename... Args>
void print(Args... args) {
    (cout << ... << args);  // C++17 fold expression
}
```

### constexpr
```cpp
constexpr int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}
```

---

## Best Practices

### Memory Management
- Always delete dynamically allocated memory
- Use RAII (Resource Acquisition Is Initialization)
- Prefer smart pointers over raw pointers
- Set pointers to nullptr after deletion

### Code Organization
- Use header files (.h) for declarations
- Use source files (.cpp) for implementations
- Include guards or #pragma once in headers
- Keep functions small and focused

### Naming Conventions
- Classes: PascalCase (MyClass)
- Variables: camelCase or snake_case
- Constants: UPPER_CASE
- Private members: prefix with m_ or trailing underscore

### Error Handling
- Use exceptions for exceptional cases
- Check return values and error codes
- Validate input parameters
- Use RAII for resource management

### Performance
- Pass large objects by const reference
- Use move semantics when appropriate
- Reserve vector capacity when size is known
- Use appropriate data structures

### Modern C++
- Prefer auto when type is obvious
- Use range-based for loops
- Use nullptr instead of NULL
- Use smart pointers
- Use constexpr for compile-time computation

---

## Common Patterns and Idioms

### RAII (Resource Acquisition Is Initialization)
```cpp
class FileHandle {
    FILE *file;
public:
    FileHandle(const char *filename) {
        file = fopen(filename, "r");
    }
    ~FileHandle() {
        if (file) fclose(file);
    }
};
```

### Singleton Pattern
```cpp
class Singleton {
private:
    static Singleton *instance;
    Singleton() {}
    
public:
    static Singleton* getInstance() {
        if (!instance)
            instance = new Singleton();
        return instance;
    }
};
```

### Factory Pattern
```cpp
class Shape {
public:
    virtual void draw() = 0;
};

class ShapeFactory {
public:
    static Shape* createShape(string type) {
        if (type == "circle") return new Circle();
        if (type == "square") return new Square();
        return nullptr;
    }
};
```

---

## Quick Reference Tables

### Operator Precedence (High to Low)
1. `::` (scope)
2. `()` `[]` `.` `->` (postfix)
3. `++` `--` `!` `~` (unary)
4. `*` `/` `%`
5. `+` `-`
6. `<<` `>>`
7. `<` `<=` `>` `>=`
8. `==` `!=`
9. `&` (bitwise AND)
10. `^` (bitwise XOR)
11. `|` (bitwise OR)
12. `&&` (logical AND)
13. `||` (logical OR)
14. `?:` (ternary)
15. `=` `+=` `-=` etc. (assignment)

### Common Header Files
```cpp
#include <iostream>    // Input/output
#include <fstream>     // File streams
#include <string>      // String class
#include <vector>      // Vector container
#include <algorithm>   // STL algorithms
#include <cmath>       // Math functions
#include <ctime>       // Time functions
#include <cstdlib>     // Standard library
#include <memory>      // Smart pointers
```

---

**End of C++ Revision Notes**
