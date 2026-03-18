# 🧠 30 Most Important OOP Interview Questions — C++

> **Target Audience:** Freshers to Experienced Developers  
> **Standard:** C++17 / C++20  
> **Topics Covered:** Core OOP Pillars, Constructors, Polymorphism, Inheritance, Memory Management, Design Patterns & More

---

## Table of Contents

| # | Question |
|---|----------|
| 1 | [What is Object-Oriented Programming?](#q1) |
| 2 | [What are the four pillars of OOP?](#q2) |
| 3 | [What is a Class vs an Object?](#q3) |
| 4 | [What are Constructors and their types?](#q4) |
| 5 | [What is a Destructor?](#q5) |
| 6 | [What is Encapsulation?](#q6) |
| 7 | [What is Abstraction?](#q7) |
| 8 | [What is Inheritance and its types?](#q8) |
| 9 | [What is Polymorphism?](#q9) |
| 10 | [What is Function Overloading?](#q10) |
| 11 | [What is Function Overriding?](#q11) |
| 12 | [What is a Virtual Function?](#q12) |
| 13 | [What is a Pure Virtual Function and Abstract Class?](#q13) |
| 14 | [What is a vtable and vptr?](#q14) |
| 15 | [What is the `this` pointer?](#q15) |
| 16 | [What are `static` members in a class?](#q16) |
| 17 | [What is `friend` function/class?](#q17) |
| 18 | [What is Operator Overloading?](#q18) |
| 19 | [What is Copy Constructor vs Assignment Operator?](#q19) |
| 20 | [What is the Rule of Three / Five / Zero?](#q20) |
| 21 | [What is deep copy vs shallow copy?](#q21) |
| 22 | [What is Multiple Inheritance and the Diamond Problem?](#q22) |
| 23 | [What is `virtual` inheritance?](#q23) |
| 24 | [What is an Interface in C++?](#q24) |
| 25 | [What is RTTI (Run-Time Type Information)?](#q25) |
| 26 | [What is `dynamic_cast` vs `static_cast`?](#q26) |
| 27 | [What is a Smart Pointer?](#q27) |
| 28 | [What is Object Slicing?](#q28) |
| 29 | [What is the difference between `struct` and `class`?](#q29) |
| 30 | [What are SOLID Principles in OOP?](#q30) |

---

<a name="q1"></a>
## Q1. What is Object-Oriented Programming?

**Answer:**

Object-Oriented Programming (OOP) is a programming paradigm that organizes software design around **data (objects)** rather than **functions and logic**. It models real-world entities as objects that have:

- **State** → represented by attributes/data members
- **Behavior** → represented by methods/member functions
- **Identity** → each object is a unique instance

**Key Benefits:**
- Code reusability via inheritance
- Modularity and maintainability
- Data hiding and security via encapsulation
- Flexibility via polymorphism

```cpp
#include <iostream>
using namespace std;

class Car {
public:
    string brand;
    int speed;

    void accelerate() {
        speed += 10;
        cout << brand << " accelerates to " << speed << " km/h\n";
    }
};

int main() {
    Car myCar;           // Object of class Car
    myCar.brand = "BMW";
    myCar.speed = 80;
    myCar.accelerate();  // Output: BMW accelerates to 90 km/h
}
```

---

<a name="q2"></a>
## Q2. What are the four pillars of OOP?

**Answer:**

```
┌────────────────────────────────────────────────────────────┐
│                   Four Pillars of OOP                      │
├──────────────────┬─────────────────────────────────────────┤
│ Encapsulation    │ Bundling data + methods; hiding details  │
│ Abstraction      │ Exposing only necessary interface        │
│ Inheritance      │ Deriving new classes from existing ones  │
│ Polymorphism     │ One interface, multiple behaviors        │
└──────────────────┴─────────────────────────────────────────┘
```

| Pillar | Real-world Analogy | C++ Mechanism |
|--------|-------------------|---------------|
| Encapsulation | Capsule hides medicine | `private` / `protected` access |
| Abstraction | TV remote hides circuitry | Abstract class / Interface |
| Inheritance | Child inherits from parent | `: public BaseClass` |
| Polymorphism | Shape.draw() → Circle/Square | `virtual` functions |

---

<a name="q3"></a>
## Q3. What is a Class vs an Object?

**Answer:**

| Concept | Definition | Analogy |
|---------|-----------|---------|
| **Class** | Blueprint / template | House blueprint |
| **Object** | Instance of a class | Actual house built from blueprint |

A **class** defines the structure and behavior. An **object** is a concrete entity created from that class, occupying memory.

```cpp
#include <iostream>
using namespace std;

// Class — blueprint
class BankAccount {
public:
    string owner;
    double balance;

    void deposit(double amount) {
        balance += amount;
        cout << "Deposited: " << amount << ", Balance: " << balance << "\n";
    }
};

int main() {
    BankAccount acc1;   // Object 1
    BankAccount acc2;   // Object 2 — independent copy

    acc1.owner   = "Alice";
    acc1.balance = 1000.0;
    acc1.deposit(500);  // Alice's balance → 1500

    acc2.owner   = "Bob";
    acc2.balance = 200.0;
    acc2.deposit(100);  // Bob's balance → 300
}
```

---

<a name="q4"></a>
## Q4. What are Constructors and their types?

**Answer:**

A **constructor** is a special member function called automatically when an object is created. It has:
- Same name as the class
- No return type (not even `void`)

### Types of Constructors

```cpp
#include <iostream>
using namespace std;

class Point {
public:
    int x, y;

    // 1. Default Constructor
    Point() : x(0), y(0) {
        cout << "Default Constructor\n";
    }

    // 2. Parameterized Constructor
    Point(int a, int b) : x(a), y(b) {
        cout << "Parameterized Constructor: (" << x << ", " << y << ")\n";
    }

    // 3. Copy Constructor
    Point(const Point& other) : x(other.x), y(other.y) {
        cout << "Copy Constructor\n";
    }

    // 4. Move Constructor (C++11)
    Point(Point&& other) noexcept : x(other.x), y(other.y) {
        other.x = other.y = 0;
        cout << "Move Constructor\n";
    }
};

int main() {
    Point p1;               // Default Constructor
    Point p2(3, 4);         // Parameterized Constructor
    Point p3 = p2;          // Copy Constructor
    Point p4 = std::move(p2); // Move Constructor
}
```

| Constructor Type | When Invoked |
|-----------------|--------------|
| Default | No arguments passed |
| Parameterized | Arguments provided |
| Copy | Object copied from another object |
| Move | Temporary/rvalue assigned (C++11) |
| Delegating | One constructor calls another (C++11) |

---

<a name="q5"></a>
## Q5. What is a Destructor?

**Answer:**

A **destructor** is a special member function called automatically when an object goes out of scope or is explicitly deleted. It is used to **release resources** (memory, file handles, sockets, etc.).

- Name: `~ClassName()`
- No return type, no parameters
- Only **one destructor** per class (cannot be overloaded)
- Called in **reverse order** of construction

```cpp
#include <iostream>
using namespace std;

class FileHandler {
    char* buffer;
public:
    FileHandler(int size) {
        buffer = new char[size];
        cout << "Resource acquired\n";
    }

    ~FileHandler() {         // Destructor
        delete[] buffer;     // Free heap memory
        cout << "Resource released\n";
    }
};

int main() {
    {
        FileHandler fh(1024);
        // ... use fh
    }  // <-- Destructor called here automatically
    cout << "After scope\n";
}
```

> ⚠️ **Important:** Always declare destructors as `virtual` in base classes when using polymorphism to ensure proper cleanup of derived objects.

---

<a name="q6"></a>
## Q6. What is Encapsulation?

**Answer:**

**Encapsulation** is the bundling of data (attributes) and the methods that operate on that data into a single unit (class), while **restricting direct access** to some of the object's components.

It is achieved using **access specifiers**:

| Specifier | Accessible From |
|-----------|----------------|
| `public` | Anywhere |
| `protected` | Class + derived classes |
| `private` | Only within the class |

```cpp
#include <iostream>
using namespace std;

class Employee {
private:
    double salary;      // Hidden from outside

public:
    // Controlled access via getter/setter
    void setSalary(double s) {
        if (s > 0) salary = s;
        else cout << "Invalid salary\n";
    }

    double getSalary() const {
        return salary;
    }
};

int main() {
    Employee emp;
    // emp.salary = -5000;  // ❌ Compile error — private
    emp.setSalary(50000);   // ✅ Validated setter
    cout << "Salary: " << emp.getSalary() << "\n";
}
```

**Benefits:** Data validation, security, maintainability, reduced coupling.

---

<a name="q7"></a>
## Q7. What is Abstraction?

**Answer:**

**Abstraction** means hiding complex implementation details and exposing only the **essential interface** to the user. It focuses on **what** an object does, not **how** it does it.

In C++, abstraction is achieved via:
- **Abstract classes** (with pure virtual functions)
- **Access specifiers**

```cpp
#include <iostream>
using namespace std;

// Abstract interface — hides implementation details
class Shape {
public:
    virtual double area() const = 0;    // Pure virtual
    virtual void draw() const = 0;

    virtual ~Shape() = default;
};

class Circle : public Shape {
    double radius;
public:
    Circle(double r) : radius(r) {}

    double area() const override {
        return 3.14159 * radius * radius;
    }

    void draw() const override {
        cout << "Drawing Circle with area = " << area() << "\n";
    }
};

class Rectangle : public Shape {
    double w, h;
public:
    Rectangle(double w, double h) : w(w), h(h) {}

    double area() const override { return w * h; }
    void draw() const override {
        cout << "Drawing Rectangle with area = " << area() << "\n";
    }
};

int main() {
    Shape* s1 = new Circle(5.0);
    Shape* s2 = new Rectangle(4.0, 6.0);

    s1->draw();  // User doesn't care HOW it draws
    s2->draw();

    delete s1; delete s2;
}
```

---

<a name="q8"></a>
## Q8. What is Inheritance and its types?

**Answer:**

**Inheritance** allows a class (derived/child) to acquire properties and behaviors of another class (base/parent), promoting **code reuse**.

```
Syntax:  class Derived : <access_specifier> Base { };
```

### Types of Inheritance

```
1. Single          A → B
2. Multilevel      A → B → C
3. Hierarchical    A → B, A → C
4. Multiple        A, B → C
5. Hybrid          Combination of above
```

```cpp
#include <iostream>
using namespace std;

// Base class
class Animal {
public:
    string name;
    void eat() { cout << name << " is eating\n"; }
};

// Single Inheritance
class Dog : public Animal {
public:
    void bark() { cout << name << " says: Woof!\n"; }
};

// Multilevel Inheritance
class Puppy : public Dog {
public:
    void weep() { cout << name << " says: Whimper...\n"; }
};

// Hierarchical Inheritance
class Cat : public Animal {
public:
    void meow() { cout << name << " says: Meow!\n"; }
};

int main() {
    Dog d;
    d.name = "Rex";
    d.eat();    // Inherited
    d.bark();

    Puppy p;
    p.name = "Tiny";
    p.eat();    // Inherited from Animal
    p.bark();   // Inherited from Dog
    p.weep();   // Own method
}
```

| Access Specifier in Inheritance | `public` members become | `protected` members become |
|---------------------------------|------------------------|---------------------------|
| `: public Base` | `public` | `protected` |
| `: protected Base` | `protected` | `protected` |
| `: private Base` | `private` | `private` |

---

<a name="q9"></a>
## Q9. What is Polymorphism?

**Answer:**

**Polymorphism** (Greek: "many forms") allows the same interface to behave differently based on the object. There are two types:

```
Polymorphism
├── Compile-time (Static)   → Function Overloading, Operator Overloading
└── Run-time (Dynamic)      → Virtual Functions, Function Overriding
```

```cpp
#include <iostream>
using namespace std;

class Notification {
public:
    virtual void send(const string& msg) {
        cout << "Base Notification: " << msg << "\n";
    }
    virtual ~Notification() = default;
};

class EmailNotification : public Notification {
public:
    void send(const string& msg) override {
        cout << "📧 Email: " << msg << "\n";
    }
};

class SMSNotification : public Notification {
public:
    void send(const string& msg) override {
        cout << "📱 SMS: " << msg << "\n";
    }
};

void notify(Notification* n, const string& msg) {
    n->send(msg);   // Runtime polymorphism — resolved at runtime
}

int main() {
    Notification* channels[] = {
        new EmailNotification(),
        new SMSNotification()
    };

    for (auto* ch : channels) {
        notify(ch, "Your OTP is 4821");
        delete ch;
    }
}
```

---

<a name="q10"></a>
## Q10. What is Function Overloading?

**Answer:**

**Function Overloading** is defining multiple functions with the **same name** but **different parameter lists** (number, type, or order). Resolved at **compile time** (static polymorphism).

```cpp
#include <iostream>
using namespace std;

class Calculator {
public:
    // Same name, different signatures
    int add(int a, int b) {
        return a + b;
    }

    double add(double a, double b) {
        return a + b;
    }

    int add(int a, int b, int c) {
        return a + b + c;
    }
};

int main() {
    Calculator calc;
    cout << calc.add(3, 4)          << "\n";  // int version   → 7
    cout << calc.add(3.5, 4.2)      << "\n";  // double version → 7.7
    cout << calc.add(1, 2, 3)       << "\n";  // 3-param version → 6
}
```

> ⚠️ **Note:** Return type alone cannot differentiate overloaded functions. The compiler resolves based on **argument types/count** only.

---

<a name="q11"></a>
## Q11. What is Function Overriding?

**Answer:**

**Function Overriding** occurs when a derived class provides its **own implementation** of a virtual function that exists in the base class. The function signature must match exactly.

```cpp
#include <iostream>
using namespace std;

class Vehicle {
public:
    virtual void start() {
        cout << "Vehicle starting...\n";
    }
};

class Tesla : public Vehicle {
public:
    void start() override {   // Overrides base version
        cout << "Tesla silently starting... ⚡\n";
    }
};

int main() {
    Vehicle* v = new Tesla();
    v->start();   // Output: Tesla silently starting...  ⚡ (runtime dispatch)
    delete v;
}
```

| Feature | Overloading | Overriding |
|---------|------------|-----------|
| Scope | Same class | Base + Derived class |
| Signature | Must differ | Must be identical |
| Resolution | Compile time | Runtime |
| `virtual` needed? | No | Yes (for dynamic dispatch) |

---

<a name="q12"></a>
## Q12. What is a Virtual Function?

**Answer:**

A **virtual function** is a member function declared with the `virtual` keyword in the base class. It enables **runtime polymorphism** — the correct function version is selected based on the **actual object type**, not the pointer/reference type.

```cpp
#include <iostream>
using namespace std;

class Base {
public:
    void nonVirtual() {
        cout << "Base::nonVirtual()\n";
    }

    virtual void virtualFunc() {
        cout << "Base::virtualFunc()\n";
    }
};

class Derived : public Base {
public:
    void nonVirtual() {       // Hides base — NOT overriding
        cout << "Derived::nonVirtual()\n";
    }

    void virtualFunc() override {  // True override
        cout << "Derived::virtualFunc()\n";
    }
};

int main() {
    Base* ptr = new Derived();

    ptr->nonVirtual();    // Base::nonVirtual()  ← static dispatch
    ptr->virtualFunc();   // Derived::virtualFunc() ← dynamic dispatch

    delete ptr;
}
```

> ✅ Always use `override` keyword in derived classes — it catches signature mismatches at compile time.

---

<a name="q13"></a>
## Q13. What is a Pure Virtual Function and Abstract Class?

**Answer:**

A **pure virtual function** is a virtual function with no implementation in the base class, declared by appending `= 0`. A class containing at least one pure virtual function is called an **Abstract Class**.

- Cannot instantiate an abstract class directly
- Forces derived classes to provide implementation
- Serves as an **interface** in C++

```cpp
#include <iostream>
using namespace std;

// Abstract Class — cannot be instantiated
class Logger {
public:
    virtual void log(const string& message) = 0;   // Pure virtual
    virtual void flush() = 0;                       // Pure virtual

    // Can have non-pure methods
    void logError(const string& msg) {
        log("[ERROR] " + msg);
    }

    virtual ~Logger() = default;
};

class ConsoleLogger : public Logger {
public:
    void log(const string& msg) override {
        cout << "CONSOLE: " << msg << "\n";
    }
    void flush() override {
        cout << "Console flushed\n";
    }
};

class FileLogger : public Logger {
public:
    void log(const string& msg) override {
        cout << "FILE: " << msg << "\n";
    }
    void flush() override {
        cout << "File flushed\n";
    }
};

int main() {
    // Logger l;               // ❌ Error — abstract class
    Logger* l1 = new ConsoleLogger();
    Logger* l2 = new FileLogger();

    l1->logError("Disk full");
    l2->logError("Network timeout");

    delete l1; delete l2;
}
```

---

<a name="q14"></a>
## Q14. What is a vtable and vptr?

**Answer:**

These are internal C++ mechanisms that implement **runtime polymorphism**:

- **vtable (Virtual Table):** A static array of function pointers, one per class with virtual functions. Each entry points to the most-derived override.
- **vptr (Virtual Pointer):** A hidden pointer added to every object of a class with virtual functions. It points to the class's vtable.

```
Class Shape:
  vtable → [ &Shape::area, &Shape::draw ]
  vptr   → points to Shape's vtable

Object of Circle (inherits Shape):
  vptr   → points to Circle's vtable
  Circle vtable → [ &Circle::area, &Circle::draw ]
```

```cpp
#include <iostream>
using namespace std;

class Base {
public:
    virtual void show() { cout << "Base\n"; }
    virtual void display() { cout << "Base display\n"; }
};

class Derived : public Base {
public:
    void show() override { cout << "Derived\n"; }
    // display() not overridden — vtable entry still points to Base::display
};

int main() {
    Base* ptr = new Derived();
    ptr->show();     // Derived::show() — vtable lookup
    ptr->display();  // Base::display() — vtable lookup
    delete ptr;
}
```

> 📝 **Size Impact:** Adding even one virtual function adds a hidden `vptr` (typically 8 bytes on 64-bit) to each object.

---

<a name="q15"></a>
## Q15. What is the `this` pointer?

**Answer:**

`this` is an **implicit pointer** available inside non-static member functions. It points to the **current object** on which the method was invoked.

**Use cases:**
1. Resolve name conflicts between members and parameters
2. Return the current object (method chaining)
3. Pass the current object to another function

```cpp
#include <iostream>
using namespace std;

class Builder {
    int width, height;
    string color;

public:
    // Method chaining using `this`
    Builder& setWidth(int w) {
        this->width = w;      // Disambiguates width parameter vs member
        return *this;         // Return current object
    }

    Builder& setHeight(int h) {
        this->height = h;
        return *this;
    }

    Builder& setColor(const string& c) {
        this->color = c;
        return *this;
    }

    void build() {
        cout << "Building: " << width << "x" << height
             << " in " << color << "\n";
    }
};

int main() {
    Builder b;
    b.setWidth(800).setHeight(600).setColor("Blue").build();
    // Output: Building: 800x600 in Blue
}
```

> ⚠️ `this` is **not available** in `static` member functions (no object context).

---

<a name="q16"></a>
## Q16. What are `static` members in a class?

**Answer:**

`static` members belong to the **class itself**, not to any individual object. They are shared across all instances.

| Feature | Static Data Member | Static Method |
|---------|--------------------|---------------|
| Memory | One copy for all objects | One copy per class |
| Access | Class name or object | Class name only |
| `this` pointer | N/A | Not available |

```cpp
#include <iostream>
using namespace std;

class Counter {
    static int count;   // Declaration — shared by all objects
    int id;

public:
    Counter() {
        ++count;
        id = count;
        cout << "Object " << id << " created\n";
    }

    ~Counter() {
        --count;
    }

    static int getCount() {   // Static method
        return count;
    }
};

// Definition outside class (required for static data members)
int Counter::count = 0;

int main() {
    cout << "Count: " << Counter::getCount() << "\n";  // 0

    Counter a, b, c;
    cout << "Count: " << Counter::getCount() << "\n";  // 3

    {
        Counter d;
        cout << "Count: " << Counter::getCount() << "\n";  // 4
    }

    cout << "Count: " << Counter::getCount() << "\n";  // 3
}
```

---

<a name="q17"></a>
## Q17. What is a `friend` function/class?

**Answer:**

A **`friend`** function or class is granted access to **private and protected** members of a class, even though it is not a member itself. Declared with the `friend` keyword inside the class.

> ⚠️ Friendship is **not** inherited and **not** reciprocal.

```cpp
#include <iostream>
using namespace std;

class Box {
    double length, width, height;   // private

public:
    Box(double l, double w, double h)
        : length(l), width(w), height(h) {}

    // Friend function declaration
    friend double volume(const Box& b);

    // Friend class declaration
    friend class BoxInspector;
};

// Friend function — can access private members
double volume(const Box& b) {
    return b.length * b.width * b.height;  // Direct private access
}

// Friend class
class BoxInspector {
public:
    void inspect(const Box& b) {
        cout << "Inspecting box: "
             << b.length << " x " << b.width << " x " << b.height << "\n";
    }
};

int main() {
    Box b(3.0, 4.0, 5.0);
    cout << "Volume: " << volume(b) << "\n";   // 60

    BoxInspector bi;
    bi.inspect(b);
}
```

---

<a name="q18"></a>
## Q18. What is Operator Overloading?

**Answer:**

**Operator Overloading** allows C++ operators (`+`, `-`, `==`, `<<`, etc.) to be redefined for user-defined types, making code more intuitive and expressive.

```cpp
#include <iostream>
using namespace std;

class Vector2D {
public:
    double x, y;

    Vector2D(double x = 0, double y = 0) : x(x), y(y) {}

    // Overload + operator (member function)
    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }

    // Overload == operator
    bool operator==(const Vector2D& other) const {
        return (x == other.x) && (y == other.y);
    }

    // Overload << operator (must be non-member / friend)
    friend ostream& operator<<(ostream& os, const Vector2D& v) {
        os << "(" << v.x << ", " << v.y << ")";
        return os;
    }
};

int main() {
    Vector2D v1(1.0, 2.0), v2(3.0, 4.0);

    Vector2D v3 = v1 + v2;
    cout << v1 << " + " << v2 << " = " << v3 << "\n";
    // (1, 2) + (3, 4) = (4, 6)

    cout << boolalpha << (v1 == v2) << "\n";  // false
}
```

| Operators that CAN be overloaded | Operators that CANNOT |
|----------------------------------|-----------------------|
| `+`, `-`, `*`, `/`, `%` | `::` (scope resolution) |
| `==`, `!=`, `<`, `>` | `.` (member access) |
| `[]`, `()`, `<<`, `>>` | `.*`, `?:`, `sizeof` |

---

<a name="q19"></a>
## Q19. What is Copy Constructor vs Assignment Operator?

**Answer:**

Both copy data from one object to another, but they're invoked in different situations:

| Feature | Copy Constructor | Assignment Operator (`=`) |
|---------|----------------|--------------------------|
| Called when | Creating a new object | Assigning to existing object |
| Signature | `T(const T& other)` | `T& operator=(const T& other)` |
| Return type | None | Reference to `*this` |
| Self-assignment check | Not needed | Needed |

```cpp
#include <iostream>
using namespace std;

class MyArray {
    int* data;
    int  size;

public:
    MyArray(int n) : size(n), data(new int[n]()) {
        cout << "Constructor\n";
    }

    // Copy Constructor
    MyArray(const MyArray& other) : size(other.size), data(new int[other.size]) {
        copy(other.data, other.data + size, data);
        cout << "Copy Constructor\n";
    }

    // Copy Assignment Operator
    MyArray& operator=(const MyArray& other) {
        if (this == &other) return *this;      // Self-assignment check
        delete[] data;                          // Free existing resource
        size = other.size;
        data = new int[size];
        copy(other.data, other.data + size, data);
        cout << "Assignment Operator\n";
        return *this;
    }

    ~MyArray() { delete[] data; }
};

int main() {
    MyArray a(5);
    MyArray b = a;      // Copy Constructor (new object)
    MyArray c(3);
    c = a;              // Assignment Operator (existing object)
}
```

---

<a name="q20"></a>
## Q20. What is the Rule of Three / Five / Zero?

**Answer:**

These rules guide when to define special member functions:

### Rule of Three (Pre-C++11)
If you define any one of: **Destructor**, **Copy Constructor**, **Copy Assignment Operator** — define all three.

### Rule of Five (C++11+)
Extends Rule of Three with: **Move Constructor** and **Move Assignment Operator**.

### Rule of Zero
Prefer designing classes so you don't need to define any of them — rely on smart pointers and standard containers.

```cpp
#include <iostream>
#include <utility>
using namespace std;

class Resource {
    int* data;
    size_t size;

public:
    // Constructor
    Resource(size_t n) : size(n), data(new int[n]()) { }

    // 1. Destructor
    ~Resource() { delete[] data; }

    // 2. Copy Constructor
    Resource(const Resource& other) : size(other.size), data(new int[other.size]) {
        copy(other.data, other.data + size, data);
    }

    // 3. Copy Assignment
    Resource& operator=(const Resource& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            copy(other.data, other.data + size, data);
        }
        return *this;
    }

    // 4. Move Constructor
    Resource(Resource&& other) noexcept
        : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
    }

    // 5. Move Assignment
    Resource& operator=(Resource&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }
};
```

---

<a name="q21"></a>
## Q21. What is deep copy vs shallow copy?

**Answer:**

| | Shallow Copy | Deep Copy |
|-|--------------|-----------|
| What it copies | Copies pointer value (address) | Copies entire data the pointer points to |
| Memory | Both objects share same memory | Each object has own memory |
| Risk | Double-free, dangling pointer | Safe but slower |
| Default behavior | Compiler-generated copy | Must write manually |

```
Shallow Copy:           Deep Copy:
obj1.ptr ──┐            obj1.ptr ──► [data: 42]
           ▼                          
         [data: 42]     obj2.ptr ──► [data: 42]  (separate copy)
           ▲                          
obj2.ptr ──┘            
```

```cpp
#include <iostream>
using namespace std;

class DeepCopyDemo {
    int* value;
public:
    DeepCopyDemo(int v) : value(new int(v)) {}

    // Deep Copy Constructor
    DeepCopyDemo(const DeepCopyDemo& other)
        : value(new int(*other.value)) {   // Allocate NEW memory
        cout << "Deep Copy performed\n";
    }

    void setValue(int v) { *value = v; }
    int  getValue()  const { return *value; }

    ~DeepCopyDemo() { delete value; }
};

int main() {
    DeepCopyDemo obj1(100);
    DeepCopyDemo obj2 = obj1;   // Deep Copy

    obj2.setValue(999);

    cout << "obj1: " << obj1.getValue() << "\n";  // 100 — unchanged
    cout << "obj2: " << obj2.getValue() << "\n";  // 999 — independent
}
```

---

<a name="q22"></a>
## Q22. What is Multiple Inheritance and the Diamond Problem?

**Answer:**

**Multiple Inheritance** allows a class to inherit from more than one base class simultaneously.

The **Diamond Problem** arises when two parent classes inherit from the same grandparent, and a child inherits from both parents — leading to **ambiguity** and **duplicate copies** of the grandparent's members.

```
        Animal
       /      \
    Dog        Cat
       \      /
        DogCat  ← Which Animal? Dog's or Cat's?
```

```cpp
#include <iostream>
using namespace std;

class Animal {
public:
    string name = "Animal";
    void breathe() { cout << "Breathing...\n"; }
};

class Dog : public Animal {};
class Cat : public Animal {};

// Diamond Problem
class DogCat : public Dog, public Cat {};

int main() {
    DogCat dc;
    // dc.breathe();   // ❌ Ambiguous — Dog::breathe or Cat::breathe?
    dc.Dog::breathe();  // ✅ Explicit scope resolution
    dc.Cat::breathe();  // ✅
}
```

---

<a name="q23"></a>
## Q23. What is `virtual` inheritance?

**Answer:**

**Virtual inheritance** solves the Diamond Problem by ensuring only **one copy** of the base class exists in the derived class hierarchy.

```cpp
#include <iostream>
using namespace std;

class Animal {
public:
    string name = "Animal";
    void breathe() { cout << "Animal breathing\n"; }
};

// Virtual inheritance
class Dog : virtual public Animal {};
class Cat : virtual public Animal {};

class DogCat : public Dog, public Cat {};

int main() {
    DogCat dc;
    dc.breathe();       // ✅ No ambiguity — single Animal copy
    dc.name = "Hybrid"; // ✅ Only one `name` member
    cout << dc.name << "\n";
}
```

> 📝 Virtual inheritance adds overhead (extra vptr-like mechanism) and should be used only when the diamond problem arises.

---

<a name="q24"></a>
## Q24. What is an Interface in C++?

**Answer:**

C++ doesn't have a dedicated `interface` keyword (unlike Java/C#). An **interface** is simulated using a class with **only pure virtual functions** and no data members.

```cpp
#include <iostream>
using namespace std;

// Interface — all pure virtual, no data members
class ISerializable {
public:
    virtual string serialize() const = 0;
    virtual void   deserialize(const string& data) = 0;
    virtual ~ISerializable() = default;
};

class ILoggable {
public:
    virtual void log() const = 0;
    virtual ~ILoggable() = default;
};

// Implementing multiple interfaces
class UserProfile : public ISerializable, public ILoggable {
    string username;
    int    age;
public:
    UserProfile(const string& u, int a) : username(u), age(a) {}

    string serialize() const override {
        return username + ":" + to_string(age);
    }

    void deserialize(const string& data) override {
        size_t pos = data.find(':');
        username = data.substr(0, pos);
        age = stoi(data.substr(pos + 1));
    }

    void log() const override {
        cout << "[LOG] User: " << username << ", Age: " << age << "\n";
    }
};

int main() {
    UserProfile user("Alice", 28);
    user.log();
    cout << "Serialized: " << user.serialize() << "\n";
}
```

---

<a name="q25"></a>
## Q25. What is RTTI (Run-Time Type Information)?

**Answer:**

**RTTI** is a mechanism that allows the type of an object to be determined at **runtime**. It requires at least one virtual function in the class.

Two main RTTI operators:
- `typeid` — returns the type info of an object
- `dynamic_cast` — safely casts between polymorphic types

```cpp
#include <iostream>
#include <typeinfo>
using namespace std;

class Animal { public: virtual ~Animal() {} };
class Dog : public Animal {};
class Cat : public Animal {};

int main() {
    Animal* a = new Dog();

    // typeid — query actual runtime type
    cout << typeid(*a).name() << "\n";   // Prints Dog (implementation-defined)

    if (typeid(*a) == typeid(Dog)) {
        cout << "It's a Dog!\n";
    }

    // dynamic_cast — safe downcast
    Dog* d = dynamic_cast<Dog*>(a);
    if (d != nullptr) {
        cout << "Successfully cast to Dog\n";
    }

    Cat* c = dynamic_cast<Cat*>(a);
    if (c == nullptr) {
        cout << "Cannot cast Dog to Cat\n";  // Safe — returns nullptr
    }

    delete a;
}
```

---

<a name="q26"></a>
## Q26. What is `dynamic_cast` vs `static_cast`?

**Answer:**

| Feature | `static_cast` | `dynamic_cast` |
|---------|--------------|----------------|
| Check | Compile-time | Runtime |
| Safety | No safety check | Safe — returns `nullptr` on failure |
| Requires RTTI | No | Yes (virtual function needed) |
| Performance | Faster | Slightly slower |
| Use case | Known safe conversions | Polymorphic downcasting |

```cpp
#include <iostream>
using namespace std;

class Base { public: virtual ~Base() {} };
class Derived : public Base {
public:
    void derivedMethod() { cout << "Derived method\n"; }
};
class Other : public Base {};

int main() {
    Base* basePtr = new Derived();

    // static_cast — no runtime check, undefined if wrong
    Derived* d1 = static_cast<Derived*>(basePtr);   // Works (correct type)
    d1->derivedMethod();

    // dynamic_cast — runtime check, safe
    Derived* d2 = dynamic_cast<Derived*>(basePtr);  // Returns valid ptr
    if (d2) d2->derivedMethod();

    Other* o = dynamic_cast<Other*>(basePtr);        // Returns nullptr
    if (!o) cout << "dynamic_cast failed safely\n";

    delete basePtr;
}
```

---

<a name="q27"></a>
## Q27. What is a Smart Pointer?

**Answer:**

**Smart pointers** are RAII wrappers around raw pointers that **automatically manage memory**, preventing leaks and dangling pointers. Defined in `<memory>`.

| Smart Pointer | Ownership | Use Case |
|---------------|-----------|----------|
| `unique_ptr` | Exclusive | Single owner, no sharing |
| `shared_ptr` | Shared (ref-counted) | Multiple owners |
| `weak_ptr` | Non-owning | Break circular references |

```cpp
#include <iostream>
#include <memory>
using namespace std;

class Engine {
public:
    Engine() { cout << "Engine created\n"; }
    ~Engine() { cout << "Engine destroyed\n"; }
    void start() { cout << "Engine running\n"; }
};

int main() {
    // unique_ptr — single ownership
    {
        unique_ptr<Engine> eng1 = make_unique<Engine>();
        eng1->start();
        // unique_ptr<Engine> eng2 = eng1;  // ❌ Cannot copy
        unique_ptr<Engine> eng2 = move(eng1); // ✅ Transfer ownership
    } // eng2 destroyed here automatically

    // shared_ptr — shared ownership
    {
        shared_ptr<Engine> s1 = make_shared<Engine>();
        shared_ptr<Engine> s2 = s1;  // Both share ownership
        cout << "Ref count: " << s1.use_count() << "\n"; // 2
    } // Destroyed when last shared_ptr leaves scope

    // weak_ptr — non-owning reference
    shared_ptr<Engine> sp = make_shared<Engine>();
    weak_ptr<Engine> wp = sp;

    if (auto locked = wp.lock()) {  // Check if object still exists
        locked->start();
    }
}
```

---

<a name="q28"></a>
## Q28. What is Object Slicing?

**Answer:**

**Object Slicing** occurs when a derived class object is **assigned to a base class object** (not pointer/reference). The derived-specific data is "sliced off", leaving only the base portion — and virtual dispatch is **lost**.

```cpp
#include <iostream>
using namespace std;

class Animal {
public:
    string type = "Animal";
    virtual void speak() { cout << "...\n"; }
};

class Dog : public Animal {
public:
    string breed = "Labrador";
    void speak() override { cout << "Woof! I'm a " << breed << "\n"; }
};

int main() {
    Dog d;
    d.speak();           // Woof! I'm a Labrador ✅

    Animal a = d;        // ⚠️ OBJECT SLICING — Dog data is sliced
    a.speak();           // "..." — base version, not Dog's ❌
    // a.breed;          // Error — breed doesn't exist in Animal

    // Solution: Always use pointers/references for polymorphism
    Animal* ptr = new Dog();
    ptr->speak();        // Woof! ✅ — polymorphism preserved
    delete ptr;
}
```

> ✅ **Prevention:** Use pointers (`Base*`) or references (`Base&`) when working with polymorphic objects.

---

<a name="q29"></a>
## Q29. What is the difference between `struct` and `class`?

**Answer:**

In C++, `struct` and `class` are nearly identical — the only formal differences are:

| Feature | `struct` | `class` |
|---------|----------|---------|
| Default member access | `public` | `private` |
| Default inheritance | `public` | `private` |
| Convention | POD / data aggregates | Full OOP abstractions |

```cpp
#include <iostream>
using namespace std;

struct Point {         // Default: public
    int x, y;         // Public by default
    void print() { cout << "(" << x << ", " << y << ")\n"; }
};

class Circle {         // Default: private
    double radius;     // Private by default
public:
    Circle(double r) : radius(r) {}
    double area() const { return 3.14159 * radius * radius; }
};

// struct inheriting publicly by default
struct ColoredPoint : Point {
    string color;
};

// class inheriting privately by default
class NamedCircle : Circle {  // Private by default — Circle members inaccessible
public:
    NamedCircle(double r) : Circle(r) {}
};

int main() {
    Point p{3, 4};
    p.print();           // OK — public

    Circle c(5.0);
    // c.radius;         // ❌ Private
    cout << c.area() << "\n";
}
```

---

<a name="q30"></a>
## Q30. What are SOLID Principles in OOP?

**Answer:**

**SOLID** is a set of five design principles for writing maintainable, scalable OOP code:

```
S — Single Responsibility Principle (SRP)
O — Open/Closed Principle (OCP)
L — Liskov Substitution Principle (LSP)
I — Interface Segregation Principle (ISP)
D — Dependency Inversion Principle (DIP)
```

```cpp
#include <iostream>
#include <vector>
using namespace std;

// S — Single Responsibility: Each class has ONE job
class InvoiceCalculator {
public:
    double calculate(double price, int qty) { return price * qty; }
};

class InvoicePrinter {
public:
    void print(double total) { cout << "Invoice Total: " << total << "\n"; }
};

// O — Open/Closed: Open for extension, closed for modification
class Discount {
public:
    virtual double apply(double price) const = 0;
    virtual ~Discount() = default;
};
class NoDiscount    : public Discount { public: double apply(double p) const override { return p; } };
class TenPctDiscount: public Discount { public: double apply(double p) const override { return p * 0.90; } };

// L — Liskov Substitution: Derived classes must be substitutable for base
class Bird { public: virtual void move() = 0; virtual ~Bird() = default; };
class Eagle : public Bird { public: void move() override { cout << "Eagle flies\n"; } };
class Penguin: public Bird { public: void move() override { cout << "Penguin swims\n"; } };

// I — Interface Segregation: Don't force unused interfaces
class IPrintable { public: virtual void print() = 0; virtual ~IPrintable() = default; };
class ISaveable  { public: virtual void save()  = 0; virtual ~ISaveable()  = default; };
// A report implements both; a log viewer only IPrintable — not forced to save()

// D — Dependency Inversion: Depend on abstractions, not concretes
class IStorage { public: virtual void store(const string& d) = 0; virtual ~IStorage() = default; };
class DBStorage    : public IStorage { public: void store(const string& d) override { cout << "DB: " << d << "\n"; } };
class CloudStorage : public IStorage { public: void store(const string& d) override { cout << "Cloud: " << d << "\n"; } };

class DataManager {
    IStorage& storage;  // Depends on abstraction
public:
    DataManager(IStorage& s) : storage(s) {}
    void save(const string& data) { storage.store(data); }
};

int main() {
    // SRP
    InvoiceCalculator calc;
    InvoicePrinter    printer;
    printer.print(calc.calculate(99.9, 3));

    // OCP
    TenPctDiscount disc;
    cout << "Discounted: " << disc.apply(1000.0) << "\n";

    // LSP
    vector<Bird*> birds = { new Eagle(), new Penguin() };
    for (auto* b : birds) { b->move(); delete b; }

    // DIP
    DBStorage    db;
    CloudStorage cloud;
    DataManager  dm(db);    // Swap to cloud with zero code change
    dm.save("UserRecord");
}
```

| Principle | Violation Sign | Fix |
|-----------|---------------|-----|
| SRP | Class does too many things | Split into smaller classes |
| OCP | Modify class for each new feature | Use inheritance / composition |
| LSP | Derived class breaks base assumptions | Refactor hierarchy |
| ISP | Implementing unused interface methods | Split fat interfaces |
| DIP | High-level depends on low-level | Use abstract interfaces |

---

## 📌 Quick Revision Cheat Sheet

```
┌─────────────────────────────────────────────────────────────────────┐
│                    OOP C++ — At a Glance                            │
├──────────────────────┬──────────────────────────────────────────────┤
│ Concept              │ Key Point                                     │
├──────────────────────┼──────────────────────────────────────────────┤
│ Encapsulation        │ private + getters/setters                     │
│ Abstraction          │ pure virtual = 0 → abstract class            │
│ Inheritance          │ class D : public B                            │
│ Polymorphism         │ virtual + override + base pointer             │
│ Constructor types    │ default, param, copy, move                    │
│ Rule of 5            │ dtor, copy ctor, copy=, move ctor, move=      │
│ vtable/vptr          │ runtime dispatch mechanism                    │
│ Diamond Problem      │ solved with virtual inheritance               │
│ Object Slicing       │ use pointers/refs with polymorphism           │
│ Smart Pointers       │ unique_ptr, shared_ptr, weak_ptr              │
│ SOLID                │ SRP, OCP, LSP, ISP, DIP                       │
│ struct vs class      │ default access: public vs private             │
│ RTTI                 │ typeid, dynamic_cast (needs virtual)          │
│ friend               │ access private — breaks encapsulation, use    │
│                      │ sparingly                                      │
└──────────────────────┴──────────────────────────────────────────────┘
```

---

> 💡 **Pro Tip for Interviews:** Always explain concepts with a real-world analogy first, then code. Interviewers value conceptual clarity over syntax recall.

---

*Happy Coding & Good Luck with your Interview! 🚀*
