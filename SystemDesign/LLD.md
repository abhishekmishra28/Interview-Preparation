# Low Level Design (LLD) — The Complete Guide
### Concepts · SOLID · Design Patterns · 3 Interview-Ready C++ Projects

> A structured, interview-focused guide covering every LLD concept from first principles, all 23 GoF design patterns in C++, and three complete, production-quality LLD problems: Parking Lot, Snake & Ladder, and Library Management System.

---

## 📚 Table of Contents

| # | Section | Level |
|---|---|---|
| **PART 1 — Foundations** | | |
| 1 | [What is LLD? HLD vs LLD](#1-what-is-lld-hld-vs-lld) | Beginner |
| 2 | [OOP Pillars — Quick Recall](#2-oop-pillars--quick-recall) | Beginner |
| 3 | [SOLID Principles — Deep Dive](#3-solid-principles--deep-dive) | Intermediate |
| 4 | [UML Class Diagrams — Reading & Writing](#4-uml-class-diagrams--reading--writing) | Intermediate |
| 5 | [How to Approach Any LLD Interview](#5-how-to-approach-any-lld-interview) | Intermediate |
| **PART 2 — Design Patterns** | | |
| 6 | [Creational Patterns](#6-creational-patterns) | Intermediate |
| 7 | [Structural Patterns](#7-structural-patterns) | Intermediate |
| 8 | [Behavioural Patterns](#8-behavioural-patterns) | Advanced |
| **PART 3 — LLD Interview Problems** | | |
| 9 | [Parking Lot System](#9-lld-problem-1-parking-lot-system) | Advanced |
| 10 | [Snake & Ladder Game](#10-lld-problem-2-snake--ladder-game) | Advanced |
| 11 | [Library Management System](#11-lld-problem-3-library-management-system) | Advanced |

---

# PART 1 — Foundations

---

## 1. What is LLD? HLD vs LLD

### The Big Picture

Software design happens at two levels. Understanding where each ends and the other begins is the first thing an interviewer checks.

```
PROBLEM STATEMENT
       │
       ▼
┌─────────────────────────────────────────────────────────────────┐
│              HIGH LEVEL DESIGN  (HLD)                           │
│                                                                 │
│  • System architecture (microservices, monolith)                │
│  • Technology choices (Kafka, Redis, Cassandra)                 │
│  • Data flow between services                                   │
│  • Scalability, availability, consistency trade-offs            │
│  • Capacity estimation (10M users, 1TB/day)                     │
│  • CDN, load balancers, caches, message queues                  │
│                                                                 │
│  Output: Architecture diagram, technology justification         │
└────────────────────────┬────────────────────────────────────────┘
                         │ each service/module gets designed at:
                         ▼
┌─────────────────────────────────────────────────────────────────┐
│              LOW LEVEL DESIGN  (LLD)                            │
│                                                                 │
│  • Classes and their attributes                                 │
│  • Methods, their signatures, return types                      │
│  • Relationships: inheritance, composition, aggregation         │
│  • Design patterns applied                                      │
│  • SOLID principles compliance                                  │
│  • Data structures chosen and why                               │
│  • Thread safety considerations                                 │
│  • Error handling strategy                                      │
│                                                                 │
│  Output: UML class diagram + compilable code                    │
└─────────────────────────────────────────────────────────────────┘
```

### HLD vs LLD — Side by Side

| Dimension | HLD | LLD |
|---|---|---|
| **Scope** | Entire system | One module/service |
| **Focus** | Architecture | Code structure |
| **Audience** | Architects, PMs | Senior engineers |
| **Output** | Block diagrams | Class diagrams + code |
| **Questions** | "Which DB?" "How to scale?" | "Which class owns this?" "Which pattern?" |
| **Example Q** | "Design Instagram's feed" | "Design a Parking Lot" |

### What Interviewers Evaluate in LLD

```
LLD Interview Rubric
├── Requirement Clarity     — Did you ask the right clarifying questions?
├── Class Identification    — Did you find the right entities?
├── Responsibility          — Is each class doing ONE thing?
├── Relationships           — Correct use of inheritance vs composition?
├── Design Patterns         — Applied naturally, not forced?
├── SOLID Compliance        — Is the design extensible?
├── Data Structures         — Right choice for the problem?
├── Code Quality            — Clean, readable, no redundancy?
└── Edge Cases              — Concurrency, null safety, overflow?
```

---

## 2. OOP Pillars — Quick Recall

These four pillars are the vocabulary of every LLD discussion. You must be able to articulate each one and demonstrate it in your class design.

### The Four Pillars

```
┌─────────────────────────────────────────────────────────────────┐
│                     OOP PILLARS                                 │
│                                                                 │
│  ENCAPSULATION          ABSTRACTION                             │
│  "Protect the data"     "Hide the how, show the what"           │
│  ─────────────────      ────────────────────────────            │
│  Private members        Abstract classes / interfaces           │
│  Public interface       Pure virtual functions                  │
│  Getters/setters        Implementation hidden from user         │
│                                                                 │
│  INHERITANCE            POLYMORPHISM                            │
│  "Reuse & extend"       "Same interface, different behavior"    │
│  ────────────────       ───────────────────────────────────     │
│  Is-a relationship      Virtual dispatch (runtime)              │
│  Base → Derived         Function overloading (compile-time)     │
│  Code reuse             One pointer, many types                 │
└─────────────────────────────────────────────────────────────────┘
```

```cpp
// Quick C++ recap of all four pillars in one example

// Abstraction — defines WHAT, not HOW
class IPayment {
public:
    virtual bool process(double amount) = 0;
    virtual std::string getProvider() const = 0;
    virtual ~IPayment() = default;
};

// Encapsulation — protects internal state
class CreditCard : public IPayment {
private:                          // ← Encapsulation
    std::string cardNumber;
    double      creditLimit;
    double      balance = 0;

public:
    CreditCard(std::string num, double limit)
        : cardNumber(std::move(num)), creditLimit(limit) {}

    // Abstraction — implements the contract
    bool process(double amount) override {
        if (balance + amount > creditLimit) return false;
        balance += amount;
        return true;
    }
    std::string getProvider() const override { return "Visa"; }
};

// Inheritance — reuses and extends
class PremiumCreditCard : public CreditCard {
private:
    double cashbackRate;
public:
    PremiumCreditCard(std::string num, double limit, double rate)
        : CreditCard(std::move(num), limit), cashbackRate(rate) {}

    std::string getProvider() const override { return "Visa Infinite"; }
};

// Polymorphism — same call, different behavior
void checkout(IPayment& payment, double amount) {   // Works for ANY payment
    if (payment.process(amount))
        std::cout << "Paid via " << payment.getProvider() << "\n";
    else
        std::cout << "Payment failed\n";
}
```

---

## 3. SOLID Principles — Deep Dive

SOLID is the backbone of every good LLD. In interviews, you should proactively mention which SOLID principle your design choice honours.

```
S — Single Responsibility Principle
O — Open/Closed Principle
L — Liskov Substitution Principle
I — Interface Segregation Principle
D — Dependency Inversion Principle
```

---

### S — Single Responsibility Principle (SRP)

> **"A class should have one, and only one, reason to change."**

Every class should do exactly one job. If you can describe a class with the word "and", it violates SRP.

```
❌ BAD: "The Order class processes orders AND sends emails AND logs to DB"
✅ GOOD: Order | EmailService | OrderRepository — each one job
```

```cpp
// ❌ VIOLATION — One class, too many reasons to change
class Order {
public:
    void calculateTotal()  { /* pricing logic */ }
    void saveToDatabase()  { /* DB logic      */ }  // ← different concern
    void sendConfirmation(){ /* email logic    */ }  // ← different concern
    void generateInvoice() { /* PDF logic      */ }  // ← different concern
};

// ✅ SRP APPLIED — Each class has one job
class Order {
private:
    std::vector<OrderItem> items;
    std::string            customerId;
public:
    double calculateTotal() const;
    OrderStatus getStatus() const;
};

class OrderRepository {           // Reason to change: database layer changes
public:
    void save(const Order& order);
    Order findById(const std::string& id);
};

class EmailService {              // Reason to change: email provider changes
public:
    void sendOrderConfirmation(const Order& order, const std::string& email);
};

class InvoiceGenerator {          // Reason to change: invoice format changes
public:
    std::string generatePDF(const Order& order);
};

// Orchestrator — thin, just wires the pieces
class OrderService {
    OrderRepository& repo;
    EmailService&    emailSvc;
    InvoiceGenerator& invoiceGen;
public:
    OrderService(OrderRepository& r, EmailService& e, InvoiceGenerator& i)
        : repo(r), emailSvc(e), invoiceGen(i) {}

    void placeOrder(Order& order, const std::string& email) {
        repo.save(order);
        emailSvc.sendOrderConfirmation(order, email);
    }
};
```

---

### O — Open/Closed Principle (OCP)

> **"Software entities should be open for extension, but closed for modification."**

You should be able to add new behaviour without touching existing, tested code.

```
❌ BAD: Add new shape → must modify existing area() function with new if/else
✅ GOOD: Add new shape → just add a new class, existing code untouched
```

```cpp
// ❌ VIOLATION — Adding new discount type requires modifying existing code
class DiscountCalculator {
public:
    double calculate(const std::string& type, double price) {
        if (type == "seasonal")   return price * 0.10;
        else if (type == "employee") return price * 0.20;
        else if (type == "vip")   return price * 0.30;
        // Adding new type = modify this function = violates OCP
        return 0;
    }
};

// ✅ OCP APPLIED — New discount type = new class, zero modification
class IDiscountStrategy {
public:
    virtual double calculate(double price) const = 0;
    virtual ~IDiscountStrategy() = default;
};

class SeasonalDiscount : public IDiscountStrategy {
public:
    double calculate(double price) const override { return price * 0.10; }
};

class EmployeeDiscount : public IDiscountStrategy {
public:
    double calculate(double price) const override { return price * 0.20; }
};

class VIPDiscount : public IDiscountStrategy {
public:
    double calculate(double price) const override { return price * 0.30; }
};

// Adding "LoyaltyDiscount" → just a new class, nothing else changes
class LoyaltyDiscount : public IDiscountStrategy {
public:
    double calculate(double price) const override { return price * 0.15; }
};

class DiscountCalculator {
public:
    double calculate(const IDiscountStrategy& strategy, double price) {
        return strategy.calculate(price);
    }
};
```

---

### L — Liskov Substitution Principle (LSP)

> **"Subtypes must be substitutable for their base types without altering the correctness of the program."**

If S is a subtype of T, then wherever T is used, S can be used without breaking anything.

```
The classic violation: Square IS-A Rectangle (geometrically true)
but Square BREAKS Rectangle's behaviour (setWidth also sets height)
```

```cpp
// ❌ VIOLATION — Square breaks Rectangle's contract
class Rectangle {
protected:
    int width, height;
public:
    virtual void setWidth(int w)  { width  = w; }
    virtual void setHeight(int h) { height = h; }
    int area() const { return width * height; }
};

class Square : public Rectangle {
public:
    // Square's constraint: width must equal height
    void setWidth(int w) override  { width = height = w; }  // Surprise!
    void setHeight(int h) override { width = height = h; }  // Breaks caller
};

// This function works for Rectangle but BREAKS for Square
void testRectangle(Rectangle& r) {
    r.setWidth(5);
    r.setHeight(3);
    assert(r.area() == 15);  // FAILS for Square — area is 9!
}

// ✅ LSP APPLIED — Don't force Square into Rectangle hierarchy
class Shape {
public:
    virtual int area() const = 0;
    virtual ~Shape() = default;
};

class Rectangle : public Shape {
    int width, height;
public:
    Rectangle(int w, int h) : width(w), height(h) {}
    int area() const override { return width * height; }
    void setWidth(int w)  { width = w; }
    void setHeight(int h) { height = h; }
};

class Square : public Shape {
    int side;
public:
    explicit Square(int s) : side(s) {}
    int area() const override { return side * side; }
    void setSide(int s) { side = s; }
};
// Both are Shapes. Substitutable for Shape. Neither breaks the other.
```

---

### I — Interface Segregation Principle (ISP)

> **"Clients should not be forced to depend on interfaces they do not use."**

Keep interfaces small and focused. A class should not be forced to implement methods it doesn't need.

```cpp
// ❌ VIOLATION — Fat interface forces irrelevant implementations
class IWorker {
public:
    virtual void work()   = 0;
    virtual void eat()    = 0;   // Robots don't eat!
    virtual void sleep()  = 0;   // Robots don't sleep!
    virtual ~IWorker() = default;
};

class Robot : public IWorker {
public:
    void work()  override { /* works fine */ }
    void eat()   override { /* STUB — makes no sense! */ }
    void sleep() override { /* STUB — makes no sense! */ }
};

// ✅ ISP APPLIED — Segregated, focused interfaces
class IWorkable {
public:
    virtual void work() = 0;
    virtual ~IWorkable() = default;
};

class IFeedable {
public:
    virtual void eat()  = 0;
    virtual void sleep()= 0;
    virtual ~IFeedable() = default;
};

class HumanWorker : public IWorkable, public IFeedable {
public:
    void work()  override { std::cout << "Human working\n"; }
    void eat()   override { std::cout << "Human eating\n"; }
    void sleep() override { std::cout << "Human sleeping\n"; }
};

class RobotWorker : public IWorkable {
public:
    void work() override { std::cout << "Robot working 24/7\n"; }
    // No eat/sleep — and no stubs needed!
};
```

---

### D — Dependency Inversion Principle (DIP)

> **"High-level modules should not depend on low-level modules. Both should depend on abstractions."**

Point your dependencies at interfaces, not concrete classes.

```
❌ BAD:  OrderService → MySQLDatabase   (concrete)
✅ GOOD: OrderService → IDatabase       (abstraction)
                           ↑
                     MySQLDatabase implements IDatabase
                     MongoDatabase implements IDatabase
```

```cpp
// ❌ VIOLATION — High-level class depends on concrete low-level class
class MySQLDatabase {
public:
    void save(const std::string& data) { /* MySQL-specific */ }
    std::string load(const std::string& id) { /* MySQL-specific */ return ""; }
};

class UserService {
    MySQLDatabase db;   // ← Tight coupling! Can't swap to Mongo without editing this
public:
    void createUser(const std::string& name) { db.save(name); }
};

// ✅ DIP APPLIED — Both depend on the abstraction
class IDatabase {
public:
    virtual void save(const std::string& data)              = 0;
    virtual std::string load(const std::string& id)         = 0;
    virtual ~IDatabase() = default;
};

class MySQLDatabase : public IDatabase {
public:
    void save(const std::string& data) override { /* MySQL  */ }
    std::string load(const std::string& id) override { return ""; }
};

class MongoDatabase : public IDatabase {
public:
    void save(const std::string& data) override { /* Mongo  */ }
    std::string load(const std::string& id) override { return ""; }
};

class InMemoryDatabase : public IDatabase {   // Great for testing!
    std::unordered_map<std::string,std::string> store;
public:
    void save(const std::string& data) override { store["latest"] = data; }
    std::string load(const std::string& id) override { return store[id]; }
};

// High-level module depends only on IDatabase abstraction
class UserService {
    IDatabase& db;   // ← Depends on abstraction, injected from outside
public:
    explicit UserService(IDatabase& database) : db(database) {}
    void createUser(const std::string& name) { db.save(name); }
};

// Wiring (Composition Root)
int main() {
    MySQLDatabase mysql;
    UserService   svc(mysql);   // Inject MySQL

    // Later, swap to Mongo with ZERO changes to UserService
    MongoDatabase mongo;
    UserService   svc2(mongo);
}
```

---

### SOLID Summary

```
┌──────────────────────────────────────────────────────────────────────┐
│  SOLID — Quick Reference                                             │
├───────┬──────────────────────────────┬─────────────────────────────┐ │
│  S    │ One class, one reason to     │ Split Order + EmailSvc      │ │
│       │ change                       │ + OrderRepo                  │ │
├───────┼──────────────────────────────┼─────────────────────────────┤ │
│  O    │ Extend without modifying     │ Strategy pattern             │ │
│       │ existing code                │ Add new class, not if/else   │ │
├───────┼──────────────────────────────┼─────────────────────────────┤ │
│  L    │ Subtypes must be             │ Don't put Square in          │ │
│       │ substitutable for base types │ Rectangle hierarchy          │ │
├───────┼──────────────────────────────┼─────────────────────────────┤ │
│  I    │ Don't force unused method    │ IWorkable + IFeedable        │ │
│       │ implementations              │ instead of fat IWorker       │ │
├───────┼──────────────────────────────┼─────────────────────────────┤ │
│  D    │ Depend on abstractions,      │ IDatabase, not MySQLDatabase │ │
│       │ not concrete classes         │ Inject via constructor       │ │
└───────┴──────────────────────────────┴─────────────────────────────┘ │
└──────────────────────────────────────────────────────────────────────┘
```

---

## 4. UML Class Diagrams — Reading & Writing

UML class diagrams are the language of LLD interviews. You'll draw these on whiteboards.

### Notation Reference

```
┌─────────────────────────┐
│      ClassName          │  ← Class name (bold/centered)
├─────────────────────────┤
│ - privateField: Type    │  ← Attributes
│ # protectedField: Type  │     - = private
│ + publicField: Type     │     # = protected
│ $ staticField: Type     │     + = public
├─────────────────────────┤
│ + publicMethod(): Type  │  ← Methods (return type after colon)
│ - helper(): void        │
│ $ staticMethod(): void  │
│ + abstract(): void {A}  │  ← Abstract method
└─────────────────────────┘
```

### Relationship Notation

```
INHERITANCE (is-a)
  Dog ──────────▷ Animal          Hollow triangle arrow
  "Dog IS-A Animal"

IMPLEMENTATION
  Car - - - - - ▷ IVehicle        Dashed hollow triangle
  "Car IMPLEMENTS IVehicle"

COMPOSITION (strong has-a, part cannot exist without whole)
  Car ◆──────── Engine            Filled diamond at owner
  "Car HAS-A Engine (Engine dies if Car dies)"

AGGREGATION (weak has-a, part can exist independently)
  Team ◇──────── Player           Hollow diamond at owner
  "Team HAS Players (Players exist without the team)"

ASSOCIATION (uses-a)
  Customer ──────── Order         Plain arrow
  "Customer places Orders"

DEPENDENCY (uses temporarily)
  OrderService - - - → EmailUtil  Dashed arrow
  "OrderService uses EmailUtil"

MULTIPLICITY
  1     = exactly one
  *     = zero or many
  1..*  = one or many
  0..1  = zero or one
  m..n  = m to n
```

### Example — Parking Lot UML Sketch

```
┌──────────────────┐           ┌──────────────────────┐
│  ParkingLot      │◆──1──────*│  ParkingFloor        │
├──────────────────┤           ├──────────────────────┤
│ -name: string    │           │ -floorNo: int        │
│ -address: string │           │ -spots: vector<Spot> │
├──────────────────┤           ├──────────────────────┤
│ +getSpot()       │           │ +getFreeSpot()       │
│ +addFloor()      │           │ +getSpotCount()      │
└──────────────────┘           └──────────┬───────────┘
                                          │◆ 1..*
                               ┌──────────▼───────────┐
                               │  ParkingSpot         │
                               ├──────────────────────┤
                               │ -spotId: string      │
                               │ -type: SpotType      │
                               │ -status: SpotStatus  │
                               ├──────────────────────┤
                               │ +isFree(): bool      │
                               │ +assignVehicle()     │
                               └──────────────────────┘

               ┌──────────────────────┐
               │  «interface»         │
               │  IVehicle            │
               ├──────────────────────┤
               │ +getPlate(): string  │
               │ +getType(): VehicType│
               └──────────┬───────────┘
                          △ (implements)
           ┌──────────────┼──────────────┐
           │              │              │
    ┌──────┴──┐    ┌──────┴──┐    ┌──────┴──┐
    │  Car    │    │  Bike   │    │  Truck  │
    └─────────┘    └─────────┘    └─────────┘
```

---

## 5. How to Approach Any LLD Interview

A structured 6-step framework to follow in every interview:

```
Step 1 — CLARIFY REQUIREMENTS           (2–3 minutes)
         Ask functional + non-functional questions
         Agree on scope: what's IN, what's OUT

Step 2 — IDENTIFY ENTITIES / NOUNS      (3–4 minutes)
         Read requirements, underline nouns → these become classes
         Underline verbs → these become methods

Step 3 — DEFINE RELATIONSHIPS           (3–4 minutes)
         Inheritance vs Composition vs Association
         Multiplicity (1:1, 1:N, M:N)

Step 4 — APPLY DESIGN PATTERNS          (2–3 minutes)
         Which patterns solve the problem naturally?
         Don't force — let requirements suggest patterns

Step 5 — DRAW UML / CLASS DIAGRAM       (5–7 minutes)
         Classes, attributes, methods, relationships
         Discuss trade-offs aloud

Step 6 — WRITE CODE                     (15–20 minutes)
         Start with interfaces and enums
         Then models, then services
         Show working main() demo
```

### Clarifying Questions Checklist

```
For ANY LLD problem, ask:

  Actors & Users
  ├── Who are the actors? (admin, user, system)
  └── What are their primary use cases?

  Core Flows
  ├── What is the happy path?
  └── What are the failure cases?

  Constraints
  ├── Scale: concurrent users? requests/sec?
  ├── Persistence: in-memory OK or need DB?
  └── Concurrency: thread safety needed?

  Scope Boundaries
  ├── What is OUT of scope?
  ├── Any external integrations?
  └── Any payment/auth needed?
```

---

# PART 2 — Design Patterns

Design patterns are proven, reusable solutions to commonly occurring problems in software design. The GoF (Gang of Four) defined 23 patterns across 3 categories.

```
DESIGN PATTERNS
├── Creational  — How objects are created
│   ├── Singleton
│   ├── Factory Method
│   ├── Abstract Factory
│   ├── Builder
│   └── Prototype
│
├── Structural  — How objects are composed
│   ├── Adapter
│   ├── Bridge
│   ├── Composite
│   ├── Decorator
│   ├── Facade
│   ├── Flyweight
│   └── Proxy
│
└── Behavioural — How objects communicate
    ├── Chain of Responsibility
    ├── Command
    ├── Iterator
    ├── Mediator
    ├── Memento
    ├── Observer
    ├── State
    ├── Strategy
    ├── Template Method
    ├── Visitor
    └── Interpreter
```

---

## 6. Creational Patterns

### 6.1 Singleton

**Intent**: Ensure a class has only one instance and provide global access to it.

**When to use**: Logger, Configuration, Thread Pool, Connection Pool, Registry.

```
Class ──────▷ Instance (only one ever)
             ↑
     All callers get the same object
```

```cpp
#include <iostream>
#include <mutex>
#include <string>
#include <sstream>
#include <fstream>
#include <chrono>

// Thread-safe Singleton Logger
class Logger {
private:
    static Logger*   instance;
    static std::mutex mtx;

    std::ofstream logFile;

    // Private constructor — no one can create Logger externally
    Logger() {
        logFile.open("app.log", std::ios::app);
    }

    std::string timestamp() {
        auto now = std::chrono::system_clock::now();
        auto t   = std::chrono::system_clock::to_time_t(now);
        std::string ts = std::ctime(&t);
        ts.pop_back();  // Remove newline
        return ts;
    }

public:
    // Delete copy constructor and assignment
    Logger(const Logger&)            = delete;
    Logger& operator=(const Logger&) = delete;

    static Logger* getInstance() {
        if (instance == nullptr) {
            std::lock_guard<std::mutex> lock(mtx);
            if (instance == nullptr) {    // Double-checked locking
                instance = new Logger();
            }
        }
        return instance;
    }

    void log(const std::string& level, const std::string& msg) {
        std::lock_guard<std::mutex> lock(mtx);
        std::string entry = "[" + timestamp() + "][" + level + "] " + msg;
        std::cout << entry << "\n";
        if (logFile.is_open()) logFile << entry << "\n";
    }

    void info(const std::string& msg)  { log("INFO",  msg); }
    void warn(const std::string& msg)  { log("WARN",  msg); }
    void error(const std::string& msg) { log("ERROR", msg); }

    ~Logger() { if (logFile.is_open()) logFile.close(); }
};

Logger*    Logger::instance = nullptr;
std::mutex Logger::mtx;

// Usage
int main() {
    Logger::getInstance()->info("Application started");
    Logger::getInstance()->warn("Low memory");
    Logger::getInstance()->error("Connection failed");

    // Both point to the SAME instance
    Logger* l1 = Logger::getInstance();
    Logger* l2 = Logger::getInstance();
    std::cout << std::boolalpha << (l1 == l2) << "\n";  // true
}
```

---

### 6.2 Factory Method

**Intent**: Define an interface for creating objects, but let subclasses decide which class to instantiate.

**When to use**: When you don't know ahead of time what class you want to create. Document factories, UI factories, database connectors.

```
Creator ────────── creates ──────────▷ Product (interface)
    ▲                                      ▲
    │                                      │
ConcreteCreatorA ──── creates ──── ConcreteProductA
ConcreteCreatorB ──── creates ──── ConcreteProductB
```

```cpp
#include <iostream>
#include <memory>
#include <string>

// Product interface
class IButton {
public:
    virtual void render() const  = 0;
    virtual void onClick() const = 0;
    virtual ~IButton() = default;
};

// Concrete products
class WindowsButton : public IButton {
public:
    void render()  const override { std::cout << "[Windows] Rendering button\n"; }
    void onClick() const override { std::cout << "[Windows] Click!\n"; }
};

class MacButton : public IButton {
public:
    void render()  const override { std::cout << "[Mac] Rendering button\n"; }
    void onClick() const override { std::cout << "[Mac] Click!\n"; }
};

class LinuxButton : public IButton {
public:
    void render()  const override { std::cout << "[Linux] Rendering button\n"; }
    void onClick() const override { std::cout << "[Linux] Click!\n"; }
};

// Creator (abstract factory method)
class Dialog {
public:
    virtual std::unique_ptr<IButton> createButton() = 0;  // Factory Method

    void render() {   // Template method uses the factory
        auto button = createButton();
        button->render();
    }
    virtual ~Dialog() = default;
};

// Concrete creators
class WindowsDialog : public Dialog {
public:
    std::unique_ptr<IButton> createButton() override {
        return std::make_unique<WindowsButton>();
    }
};

class MacDialog : public Dialog {
public:
    std::unique_ptr<IButton> createButton() override {
        return std::make_unique<MacButton>();
    }
};

// Client code — works with any Dialog
void clientCode(Dialog& dialog) {
    dialog.render();
    auto btn = dialog.createButton();
    btn->onClick();
}

int main() {
    WindowsDialog winDlg;
    MacDialog     macDlg;
    clientCode(winDlg);
    clientCode(macDlg);
}
```

---

### 6.3 Abstract Factory

**Intent**: Provide an interface for creating families of related objects without specifying their concrete classes.

**When to use**: UI theme kits (Dark/Light), cross-platform widgets, database driver families.

```cpp
#include <iostream>
#include <memory>

// Abstract products
class IButton { public: virtual void paint() = 0; virtual ~IButton() = default; };
class ICheckbox { public: virtual void paint() = 0; virtual ~ICheckbox() = default; };

// Dark theme products
class DarkButton : public IButton {
public: void paint() override { std::cout << "Dark Button\n"; }
};
class DarkCheckbox : public ICheckbox {
public: void paint() override { std::cout << "Dark Checkbox\n"; }
};

// Light theme products
class LightButton : public IButton {
public: void paint() override { std::cout << "Light Button\n"; }
};
class LightCheckbox : public ICheckbox {
public: void paint() override { std::cout << "Light Checkbox\n"; }
};

// Abstract factory interface
class IUIFactory {
public:
    virtual std::unique_ptr<IButton>   createButton()   = 0;
    virtual std::unique_ptr<ICheckbox> createCheckbox() = 0;
    virtual ~IUIFactory() = default;
};

// Concrete factories (families)
class DarkThemeFactory : public IUIFactory {
public:
    std::unique_ptr<IButton>   createButton()   override { return std::make_unique<DarkButton>(); }
    std::unique_ptr<ICheckbox> createCheckbox() override { return std::make_unique<DarkCheckbox>(); }
};

class LightThemeFactory : public IUIFactory {
public:
    std::unique_ptr<IButton>   createButton()   override { return std::make_unique<LightButton>(); }
    std::unique_ptr<ICheckbox> createCheckbox() override { return std::make_unique<LightCheckbox>(); }
};

class Application {
    std::unique_ptr<IButton>   button;
    std::unique_ptr<ICheckbox> checkbox;
public:
    Application(IUIFactory& factory) {
        button   = factory.createButton();
        checkbox = factory.createCheckbox();
    }
    void render() { button->paint(); checkbox->paint(); }
};

int main() {
    DarkThemeFactory darkFactory;
    Application app(darkFactory);
    app.render();
}
```

---

### 6.4 Builder

**Intent**: Separate the construction of a complex object from its representation, so the same construction process can create different representations.

**When to use**: Building complex objects step-by-step with many optional parameters (HTTP request, query builder, config objects).

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <optional>

// Complex product
class HttpRequest {
public:
    std::string method;
    std::string url;
    std::vector<std::pair<std::string,std::string>> headers;
    std::optional<std::string> body;
    int    timeoutMs  = 30000;
    bool   followRedirects = true;

    void print() const {
        std::cout << method << " " << url << "\n";
        for (auto& [k, v] : headers) std::cout << "  " << k << ": " << v << "\n";
        if (body) std::cout << "Body: " << *body << "\n";
        std::cout << "Timeout: " << timeoutMs << "ms\n";
    }
};

// Builder
class HttpRequestBuilder {
    HttpRequest req;
public:
    HttpRequestBuilder& method(const std::string& m)   { req.method = m; return *this; }
    HttpRequestBuilder& url(const std::string& u)       { req.url    = u; return *this; }
    HttpRequestBuilder& header(const std::string& k, const std::string& v) {
        req.headers.emplace_back(k, v); return *this;
    }
    HttpRequestBuilder& body(const std::string& b)     { req.body   = b; return *this; }
    HttpRequestBuilder& timeout(int ms)                { req.timeoutMs = ms; return *this; }
    HttpRequestBuilder& noRedirects()                  { req.followRedirects = false; return *this; }

    HttpRequest build() {
        if (req.method.empty()) throw std::runtime_error("Method required");
        if (req.url.empty())    throw std::runtime_error("URL required");
        return req;
    }
};

// Director (optional — pre-built configurations)
class RequestDirector {
public:
    static HttpRequest buildJsonPost(const std::string& url, const std::string& body) {
        return HttpRequestBuilder()
            .method("POST")
            .url(url)
            .header("Content-Type", "application/json")
            .header("Accept", "application/json")
            .body(body)
            .timeout(5000)
            .build();
    }
};

int main() {
    // Fluent builder
    auto req = HttpRequestBuilder()
        .method("GET")
        .url("https://api.example.com/users")
        .header("Authorization", "Bearer token123")
        .header("Accept", "application/json")
        .timeout(3000)
        .build();
    req.print();

    // Director
    auto post = RequestDirector::buildJsonPost(
        "https://api.example.com/users",
        R"({"name":"Alice","age":28})"
    );
    post.print();
}
```

---

### 6.5 Prototype

**Intent**: Specify the kinds of objects to create using a prototypical instance and create new objects by copying this prototype.

```cpp
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

class IShape {
public:
    virtual std::unique_ptr<IShape> clone() const = 0;
    virtual void draw() const = 0;
    virtual ~IShape() = default;
};

class Circle : public IShape {
    int radius; std::string colour;
public:
    Circle(int r, std::string c) : radius(r), colour(std::move(c)) {}
    std::unique_ptr<IShape> clone() const override {
        return std::make_unique<Circle>(*this);  // Copy constructor
    }
    void draw() const override {
        std::cout << "Circle(r=" << radius << ", colour=" << colour << ")\n";
    }
};

// Prototype Registry
class ShapeRegistry {
    std::unordered_map<std::string, std::unique_ptr<IShape>> registry;
public:
    void add(const std::string& key, std::unique_ptr<IShape> proto) {
        registry[key] = std::move(proto);
    }
    std::unique_ptr<IShape> get(const std::string& key) const {
        return registry.at(key)->clone();
    }
};

int main() {
    ShapeRegistry reg;
    reg.add("red_circle",  std::make_unique<Circle>(10, "red"));
    reg.add("blue_circle", std::make_unique<Circle>(20, "blue"));

    auto c1 = reg.get("red_circle");
    auto c2 = reg.get("red_circle");  // Independent copy
    c1->draw();
    c2->draw();
}
```

---

## 7. Structural Patterns

### 7.1 Adapter

**Intent**: Convert the interface of a class into another interface that clients expect. Lets incompatible interfaces work together.

```
Client → ITarget → Adapter → Adaptee (existing, incompatible)
```

```cpp
#include <iostream>
#include <string>
#include <memory>

// What the client expects
class ILogger {
public:
    virtual void log(const std::string& level, const std::string& msg) = 0;
    virtual ~ILogger() = default;
};

// Existing, incompatible legacy logger
class LegacyLogger {
public:
    void writeLog(int severity, const std::string& message) {
        std::cout << "[Legacy severity=" << severity << "] " << message << "\n";
    }
};

// Adapter — wraps LegacyLogger and speaks ILogger
class LegacyLoggerAdapter : public ILogger {
    LegacyLogger legacy;

    int severityFromLevel(const std::string& level) {
        if (level == "ERROR") return 1;
        if (level == "WARN")  return 2;
        return 3;
    }
public:
    void log(const std::string& level, const std::string& msg) override {
        legacy.writeLog(severityFromLevel(level), msg);
    }
};

// Client code — works with ILogger
void process(ILogger& logger) {
    logger.log("INFO",  "Processing started");
    logger.log("ERROR", "Something failed");
}

int main() {
    LegacyLoggerAdapter adapter;
    process(adapter);  // Old logger, new interface
}
```

---

### 7.2 Decorator

**Intent**: Attach additional responsibilities to an object dynamically. Provides a flexible alternative to subclassing for extending functionality.

```
IComponent
    ↑ implements
BaseComponent         ConcreteDecorator
                          - wraps IComponent
                          - adds behaviour before/after
```

```cpp
#include <iostream>
#include <memory>
#include <string>

class ITextProcessor {
public:
    virtual std::string process(const std::string& text) = 0;
    virtual ~ITextProcessor() = default;
};

// Base component
class PlainText : public ITextProcessor {
public:
    std::string process(const std::string& text) override { return text; }
};

// Base decorator
class TextDecorator : public ITextProcessor {
protected:
    std::unique_ptr<ITextProcessor> wrapped;
public:
    explicit TextDecorator(std::unique_ptr<ITextProcessor> w) : wrapped(std::move(w)) {}
};

// Concrete decorators — each adds ONE behaviour
class UpperCaseDecorator : public TextDecorator {
public:
    using TextDecorator::TextDecorator;
    std::string process(const std::string& text) override {
        std::string result = wrapped->process(text);
        for (char& c : result) c = toupper(c);
        return result;
    }
};

class TrimDecorator : public TextDecorator {
public:
    using TextDecorator::TextDecorator;
    std::string process(const std::string& text) override {
        std::string result = wrapped->process(text);
        size_t start = result.find_first_not_of(" \t\n");
        size_t end   = result.find_last_not_of(" \t\n");
        return (start == std::string::npos) ? "" : result.substr(start, end - start + 1);
    }
};

class PrefixDecorator : public TextDecorator {
    std::string prefix;
public:
    PrefixDecorator(std::unique_ptr<ITextProcessor> w, std::string p)
        : TextDecorator(std::move(w)), prefix(std::move(p)) {}

    std::string process(const std::string& text) override {
        return prefix + wrapped->process(text);
    }
};

int main() {
    // Stack decorators: Trim → UpperCase → Prefix
    auto processor =
        std::make_unique<PrefixDecorator>(
            std::make_unique<UpperCaseDecorator>(
                std::make_unique<TrimDecorator>(
                    std::make_unique<PlainText>()
                )
            ),
            "[LOG] "
        );

    std::cout << processor->process("  hello world  ") << "\n";
    // [LOG] HELLO WORLD
}
```

---

### 7.3 Facade

**Intent**: Provide a simplified interface to a complex subsystem.

```
Client ──────▶ Facade ──┬──▶ SubsystemA
                        ├──▶ SubsystemB
                        └──▶ SubsystemC
```

```cpp
#include <iostream>
#include <string>

// Complex subsystem classes
class VideoDecoder {
public: void decode(const std::string& file) { std::cout << "Decoding " << file << "\n"; }
};
class AudioMixer {
public: void mix()  { std::cout << "Mixing audio\n"; }
};
class SubtitleLoader {
public: void load() { std::cout << "Loading subtitles\n"; }
};
class VideoPlayer {
public: void play() { std::cout << "Playing video\n"; }
};

// Facade — one simple interface for the whole subsystem
class MediaPlayerFacade {
    VideoDecoder  decoder;
    AudioMixer    mixer;
    SubtitleLoader subtitles;
    VideoPlayer   player;
public:
    void playMovie(const std::string& file) {
        std::cout << "=== Starting movie ===\n";
        decoder.decode(file);
        mixer.mix();
        subtitles.load();
        player.play();
        std::cout << "=== Enjoy! ===\n";
    }
};

int main() {
    MediaPlayerFacade media;
    media.playMovie("inception.mp4");  // One call, all the complexity hidden
}
```

---

### 7.4 Composite

**Intent**: Compose objects into tree structures to represent part-whole hierarchies. Lets clients treat individual objects and compositions uniformly.

```
IComponent
    ▲
    ├── Leaf         (no children)
    └── Composite    (has children: vector<IComponent*>)
```

```cpp
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <numeric>

class IFileSystemItem {
public:
    virtual void print(int indent = 0) const = 0;
    virtual long long size() const = 0;
    virtual std::string name() const = 0;
    virtual ~IFileSystemItem() = default;
};

// Leaf
class File : public IFileSystemItem {
    std::string fileName;
    long long   fileSize;
public:
    File(std::string n, long long s) : fileName(std::move(n)), fileSize(s) {}
    void print(int indent) const override {
        std::cout << std::string(indent, ' ') << "📄 " << fileName
                  << " (" << fileSize << " bytes)\n";
    }
    long long size()  const override { return fileSize; }
    std::string name() const override { return fileName; }
};

// Composite
class Directory : public IFileSystemItem {
    std::string dirName;
    std::vector<std::unique_ptr<IFileSystemItem>> children;
public:
    explicit Directory(std::string n) : dirName(std::move(n)) {}

    void add(std::unique_ptr<IFileSystemItem> item) {
        children.push_back(std::move(item));
    }

    void print(int indent = 0) const override {
        std::cout << std::string(indent, ' ') << "📁 " << dirName << "/\n";
        for (const auto& child : children) child->print(indent + 2);
    }

    long long size() const override {
        long long total = 0;
        for (const auto& child : children) total += child->size();
        return total;
    }
    std::string name() const override { return dirName; }
};

int main() {
    auto root = std::make_unique<Directory>("root");
    auto src  = std::make_unique<Directory>("src");
    src->add(std::make_unique<File>("main.cpp",   2048));
    src->add(std::make_unique<File>("utils.cpp",  1024));
    root->add(std::move(src));
    root->add(std::make_unique<File>("README.md", 512));

    root->print();
    std::cout << "Total size: " << root->size() << " bytes\n";
}
```

---

## 8. Behavioural Patterns

### 8.1 Observer

**Intent**: Define a one-to-many dependency so that when one object changes state, all dependents are notified and updated automatically.

```
Subject ────── notifies ──────▶ Observer (interface)
                                     ▲
                              ┌──────┴──────┐
                         ConcreteObserverA  ConcreteObserverB
```

```cpp
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>

class IStockObserver {
public:
    virtual void onPriceChange(const std::string& stock, double price) = 0;
    virtual ~IStockObserver() = default;
};

class StockMarket {
    std::vector<IStockObserver*> observers;
    std::unordered_map<std::string, double> prices;
public:
    void subscribe(IStockObserver* obs)   { observers.push_back(obs); }
    void unsubscribe(IStockObserver* obs) {
        observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
    }

    void setPrice(const std::string& stock, double price) {
        prices[stock] = price;
        for (auto* obs : observers) obs->onPriceChange(stock, price);
    }
};

class MobileApp : public IStockObserver {
    std::string userId;
public:
    explicit MobileApp(std::string id) : userId(std::move(id)) {}
    void onPriceChange(const std::string& stock, double price) override {
        std::cout << "[Mobile:" << userId << "] " << stock << " → $" << price << "\n";
    }
};

class TradingBot : public IStockObserver {
    double threshold;
public:
    explicit TradingBot(double t) : threshold(t) {}
    void onPriceChange(const std::string& stock, double price) override {
        if (price > threshold)
            std::cout << "[Bot] BUY ALERT: " << stock << " at $" << price << "\n";
    }
};

int main() {
    StockMarket market;
    MobileApp alice("alice"), bob("bob");
    TradingBot bot(150.0);

    market.subscribe(&alice);
    market.subscribe(&bob);
    market.subscribe(&bot);

    market.setPrice("AAPL", 145.50);
    market.setPrice("AAPL", 155.00);  // Bot triggers

    market.unsubscribe(&bob);
    market.setPrice("GOOG", 100.00);  // Bob doesn't get this
}
```

---

### 8.2 Strategy

**Intent**: Define a family of algorithms, encapsulate each one, and make them interchangeable. Strategy lets the algorithm vary independently from clients that use it.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

// Strategy interface
class ISortStrategy {
public:
    virtual void sort(std::vector<int>& data) = 0;
    virtual std::string name() const = 0;
    virtual ~ISortStrategy() = default;
};

class BubbleSort : public ISortStrategy {
public:
    std::string name() const override { return "Bubble Sort"; }
    void sort(std::vector<int>& data) override {
        int n = data.size();
        for (int i = 0; i < n - 1; i++)
            for (int j = 0; j < n - i - 1; j++)
                if (data[j] > data[j + 1]) std::swap(data[j], data[j + 1]);
    }
};

class QuickSort : public ISortStrategy {
    void quicksort(std::vector<int>& data, int lo, int hi) {
        if (lo >= hi) return;
        int pivot = data[hi], i = lo - 1;
        for (int j = lo; j < hi; j++)
            if (data[j] <= pivot) std::swap(data[++i], data[j]);
        std::swap(data[i + 1], data[hi]);
        int p = i + 1;
        quicksort(data, lo, p - 1);
        quicksort(data, p + 1, hi);
    }
public:
    std::string name() const override { return "Quick Sort"; }
    void sort(std::vector<int>& data) override {
        if (!data.empty()) quicksort(data, 0, data.size() - 1);
    }
};

class STLSort : public ISortStrategy {
public:
    std::string name() const override { return "STL Sort"; }
    void sort(std::vector<int>& data) override { std::sort(data.begin(), data.end()); }
};

class Sorter {
    ISortStrategy* strategy;
public:
    explicit Sorter(ISortStrategy* s) : strategy(s) {}
    void setStrategy(ISortStrategy* s) { strategy = s; }
    void sort(std::vector<int>& data) {
        std::cout << "Using: " << strategy->name() << "\n";
        strategy->sort(data);
    }
};

int main() {
    std::vector<int> data = {64, 34, 25, 12, 22, 11, 90};
    BubbleSort bubble; QuickSort quick; STLSort stl;

    Sorter sorter(&quick);
    sorter.sort(data);

    data = {5, 3, 8, 1, 9, 2};
    sorter.setStrategy(&stl);
    sorter.sort(data);
}
```

---

### 8.3 State

**Intent**: Allow an object to alter its behaviour when its internal state changes. The object will appear to change its class.

```
Context ──── has ────▶ IState
                           ▲
               ┌───────────┼───────────┐
           StateA       StateB      StateC
```

```cpp
#include <iostream>
#include <memory>
#include <string>

class VendingMachine;  // Forward declaration

// State interface
class IVendingState {
public:
    virtual void insertCoin(VendingMachine& m)      = 0;
    virtual void selectProduct(VendingMachine& m)   = 0;
    virtual void dispense(VendingMachine& m)         = 0;
    virtual std::string stateName() const           = 0;
    virtual ~IVendingState() = default;
};

class VendingMachine {
    std::unique_ptr<IVendingState> state;
    int    itemCount;
    double balance = 0;

public:
    explicit VendingMachine(int items);
    void setState(std::unique_ptr<IVendingState> s) { state = std::move(s); }
    void insertCoin()    { state->insertCoin(*this);    }
    void selectProduct() { state->selectProduct(*this); }
    void dispense()      { state->dispense(*this);      }

    int     getItemCount() const    { return itemCount; }
    double  getBalance() const      { return balance; }
    void    setBalance(double b)    { balance = b; }
    void    decrementItems()        { itemCount--; }
    std::string getCurrentState() const { return state->stateName(); }
};

// Concrete States
class IdleState : public IVendingState {
public:
    std::string stateName() const override { return "Idle"; }
    void insertCoin(VendingMachine& m) override;
    void selectProduct(VendingMachine& m) override {
        std::cout << "Please insert a coin first\n";
    }
    void dispense(VendingMachine& m) override {
        std::cout << "No coin inserted\n";
    }
};

class HasCoinState : public IVendingState {
public:
    std::string stateName() const override { return "HasCoin"; }
    void insertCoin(VendingMachine& m) override {
        std::cout << "Coin already inserted\n";
    }
    void selectProduct(VendingMachine& m) override;
    void dispense(VendingMachine& m) override {
        std::cout << "Select a product first\n";
    }
};

class DispensingState : public IVendingState {
public:
    std::string stateName() const override { return "Dispensing"; }
    void insertCoin(VendingMachine& m) override {
        std::cout << "Wait, dispensing in progress\n";
    }
    void selectProduct(VendingMachine& m) override {
        std::cout << "Already dispensing\n";
    }
    void dispense(VendingMachine& m) override;
};

class SoldOutState : public IVendingState {
public:
    std::string stateName() const override { return "SoldOut"; }
    void insertCoin(VendingMachine& m) override {
        std::cout << "Machine is sold out\n";
    }
    void selectProduct(VendingMachine& m) override {
        std::cout << "Machine is sold out\n";
    }
    void dispense(VendingMachine& m) override {
        std::cout << "Machine is sold out\n";
    }
};

// Implementations after all states are defined
void IdleState::insertCoin(VendingMachine& m) {
    m.setBalance(m.getBalance() + 1.0);
    std::cout << "Coin inserted. Balance: $" << m.getBalance() << "\n";
    m.setState(std::make_unique<HasCoinState>());
}

void HasCoinState::selectProduct(VendingMachine& m) {
    if (m.getBalance() >= 1.0) {
        std::cout << "Product selected\n";
        m.setState(std::make_unique<DispensingState>());
    } else {
        std::cout << "Insufficient balance\n";
    }
}

void DispensingState::dispense(VendingMachine& m) {
    std::cout << "Dispensing product!\n";
    m.decrementItems();
    m.setBalance(0);
    if (m.getItemCount() == 0)
        m.setState(std::make_unique<SoldOutState>());
    else
        m.setState(std::make_unique<IdleState>());
}

VendingMachine::VendingMachine(int items) : itemCount(items) {
    state = std::make_unique<IdleState>();
}

int main() {
    VendingMachine vm(2);
    std::cout << "State: " << vm.getCurrentState() << "\n";

    vm.insertCoin();
    vm.selectProduct();
    vm.dispense();
    std::cout << "State: " << vm.getCurrentState() << "\n";

    vm.insertCoin();
    vm.selectProduct();
    vm.dispense();
    std::cout << "State: " << vm.getCurrentState() << "\n";  // SoldOut
}
```

---

### 8.4 Command

**Intent**: Encapsulate a request as an object, allowing undo/redo, queuing, and logging of requests.

```cpp
#include <iostream>
#include <stack>
#include <memory>
#include <string>

class ICommand {
public:
    virtual void execute() = 0;
    virtual void undo()    = 0;
    virtual std::string description() const = 0;
    virtual ~ICommand() = default;
};

class TextEditor {
    std::string text;
public:
    void insert(const std::string& str, int pos) {
        text.insert(pos, str);
    }
    void erase(int pos, int len) {
        text.erase(pos, len);
    }
    std::string getText() const { return text; }
};

class InsertCommand : public ICommand {
    TextEditor& editor;
    std::string text;
    int pos;
public:
    InsertCommand(TextEditor& e, std::string t, int p)
        : editor(e), text(std::move(t)), pos(p) {}

    void execute() override { editor.insert(text, pos); }
    void undo()    override { editor.erase(pos, text.size()); }
    std::string description() const override {
        return "Insert '" + text + "' at " + std::to_string(pos);
    }
};

// Command History (Undo/Redo)
class CommandHistory {
    std::stack<std::unique_ptr<ICommand>> undoStack;
    std::stack<std::unique_ptr<ICommand>> redoStack;
public:
    void execute(std::unique_ptr<ICommand> cmd) {
        cmd->execute();
        undoStack.push(std::move(cmd));
        while (!redoStack.empty()) redoStack.pop();  // Clear redo on new action
    }

    void undo() {
        if (undoStack.empty()) { std::cout << "Nothing to undo\n"; return; }
        auto& cmd = undoStack.top();
        std::cout << "Undoing: " << cmd->description() << "\n";
        cmd->undo();
        redoStack.push(std::move(cmd));
        undoStack.pop();
    }

    void redo() {
        if (redoStack.empty()) { std::cout << "Nothing to redo\n"; return; }
        auto& cmd = redoStack.top();
        std::cout << "Redoing: " << cmd->description() << "\n";
        cmd->execute();
        undoStack.push(std::move(cmd));
        redoStack.pop();
    }
};

int main() {
    TextEditor editor;
    CommandHistory history;

    history.execute(std::make_unique<InsertCommand>(editor, "Hello",  0));
    history.execute(std::make_unique<InsertCommand>(editor, " World", 5));
    std::cout << "Text: " << editor.getText() << "\n";  // Hello World

    history.undo();
    std::cout << "Text: " << editor.getText() << "\n";  // Hello

    history.redo();
    std::cout << "Text: " << editor.getText() << "\n";  // Hello World
}
```

---

### 8.5 Template Method

**Intent**: Define the skeleton of an algorithm in a base class, deferring some steps to subclasses.

```cpp
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

// Abstract class with Template Method
class DataProcessor {
public:
    // Template Method — defines the algorithm skeleton
    // Non-virtual — subclasses cannot override the order
    void process(const std::string& source) {
        auto raw  = readData(source);    // Step 1 — varies
        auto data = parseData(raw);       // Step 2 — varies
        validateData(data);              // Step 3 — common (can override)
        auto result = processData(data); // Step 4 — varies
        saveResult(result);              // Step 5 — varies
        std::cout << "Processing complete\n";
    }

protected:
    virtual std::string readData(const std::string& source) = 0;
    virtual std::vector<std::string> parseData(const std::string& raw) = 0;
    virtual std::string processData(const std::vector<std::string>& data) = 0;
    virtual void saveResult(const std::string& result) = 0;

    // Hook — has default, can be overridden
    virtual void validateData(const std::vector<std::string>& data) {
        std::cout << "Default validation: " << data.size() << " records\n";
    }
    virtual ~DataProcessor() = default;
};

class CSVProcessor : public DataProcessor {
protected:
    std::string readData(const std::string& src) override {
        return "name,age\nAlice,28\nBob,32";  // Simulate file read
    }
    std::vector<std::string> parseData(const std::string& raw) override {
        std::vector<std::string> rows;
        std::string row; std::istringstream ss(raw);
        while (std::getline(ss, row)) rows.push_back(row);
        return rows;
    }
    std::string processData(const std::vector<std::string>& data) override {
        return "Processed " + std::to_string(data.size()) + " CSV rows";
    }
    void saveResult(const std::string& result) override {
        std::cout << "CSV Result: " << result << "\n";
    }
};

int main() {
    CSVProcessor csv;
    csv.process("data.csv");
}
```

---

### 8.6 Chain of Responsibility

**Intent**: Pass a request along a chain of handlers. Each handler decides to process it or pass it to the next.

```
Request → HandlerA → HandlerB → HandlerC → NULL
            handles?    handles?    handles?
```

```cpp
#include <iostream>
#include <memory>
#include <string>

class IHandler {
protected:
    std::unique_ptr<IHandler> next;
public:
    IHandler* setNext(std::unique_ptr<IHandler> n) {
        next = std::move(n);
        return next.get();
    }
    virtual bool handle(int level, const std::string& msg) {
        if (next) return next->handle(level, msg);
        return false;
    }
    virtual ~IHandler() = default;
};

class InfoHandler : public IHandler {
public:
    bool handle(int level, const std::string& msg) override {
        if (level == 1) { std::cout << "[INFO] " << msg << "\n"; return true; }
        return IHandler::handle(level, msg);
    }
};

class WarnHandler : public IHandler {
public:
    bool handle(int level, const std::string& msg) override {
        if (level == 2) { std::cout << "[WARN] " << msg << "\n"; return true; }
        return IHandler::handle(level, msg);
    }
};

class ErrorHandler : public IHandler {
public:
    bool handle(int level, const std::string& msg) override {
        if (level == 3) { std::cout << "[ERROR] " << msg << " — Alerting team!\n"; return true; }
        return IHandler::handle(level, msg);
    }
};

int main() {
    auto info  = std::make_unique<InfoHandler>();
    auto warn  = std::make_unique<WarnHandler>();
    auto error = std::make_unique<ErrorHandler>();

    // Build chain
    auto* infoPtr = info.get();
    auto* warnPtr = warn.get();
    infoPtr->setNext(std::move(warn))->setNext(std::move(error));

    info->handle(1, "App started");
    info->handle(2, "High memory usage");
    info->handle(3, "Database connection lost");
    info->handle(9, "Unknown level");   // Falls through all
}
```

---

# PART 3 — LLD Interview Problems

---

## 9. LLD Problem 1: Parking Lot System

### 9.1 Requirements Gathering

**Functional Requirements**
```
✅ Multiple floors, each with multiple parking spots
✅ Spot types: Compact, Large, Motorcycle, Electric
✅ Vehicle types: Car, Motorcycle, Truck, Electric Vehicle
✅ Assign the nearest available spot to a vehicle
✅ Issue a ticket on entry; calculate fee on exit
✅ Pricing: per-hour rates differ by spot type
✅ Support for monthly passes (flat rate)
✅ Display board showing availability per floor
```

**Non-Functional Requirements**
```
✅ Thread-safe: multiple entry/exit gates can operate concurrently
✅ Extensible: new vehicle/spot types without modifying core
✅ In-memory for interview; repository can swap to DB
```

**Out of Scope**
```
❌ Payment gateway integration
❌ CCTV / license plate recognition
❌ Online reservation
```

### 9.2 Entity Identification

```
Nouns from requirements → Classes:
  ParkingLot, ParkingFloor, ParkingSpot, Vehicle, ParkingTicket,
  EntryGate, ExitGate, FeeStrategy, DisplayBoard, ParkingAttendant

Verbs → Methods:
  park(vehicle), unpark(ticket), findSpot(), calculateFee(),
  issueTicket(), processExit(), updateDisplay()
```

### 9.3 UML Class Diagram

```
┌─────────────────────┐         ┌──────────────────────┐
│     ParkingLot      │◆───1..*─│    ParkingFloor      │
├─────────────────────┤         ├──────────────────────┤
│ -name: string       │         │ -floorNo: int        │
│ -address: string    │         │ -spots: vector<Spot> │
├─────────────────────┤         ├──────────────────────┤
│ +park(v): Ticket    │         │ +findFreeSpot()      │
│ +unpark(t): Receipt │         │ +getAvailCount()     │
│ +getDisplay()       │         └──────────┬───────────┘
└─────────────────────┘                    │◆ 1..*
                                ┌──────────▼───────────┐
                                │    ParkingSpot       │
                                ├──────────────────────┤
                                │ -id: string          │
                                │ -type: SpotType      │
                                │ -status: SpotStatus  │
                                │ -vehicle: Vehicle*   │
                                ├──────────────────────┤
                                │ +isFree(): bool      │
                                │ +assign(v)           │
                                │ +release()           │
                                └──────────────────────┘

     «interface»
     IVehicle                    «interface»
     +getType()                  IFeeStrategy
     +getPlate()                 +calculate(hrs, type)
          ▲                           ▲
     ┌────┴────┐              ┌──────┴──────┐
   Car  Motorcycle Truck    HourlyFee  MonthlyPass
```

### 9.4 Complete C++ Implementation

```cpp
#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <string>
#include <chrono>
#include <mutex>
#include <optional>
#include <algorithm>
#include <iomanip>
#include <stdexcept>
#include <sstream>

// ═══════════════════════════════════════════════════════════════
// ENUMS
// ═══════════════════════════════════════════════════════════════

enum class VehicleType { CAR, MOTORCYCLE, TRUCK, ELECTRIC };
enum class SpotType    { COMPACT, LARGE, MOTORCYCLE, ELECTRIC };
enum class SpotStatus  { FREE, OCCUPIED, OUT_OF_SERVICE };

inline std::string vehicleTypeStr(VehicleType t) {
    switch (t) {
        case VehicleType::CAR:        return "Car";
        case VehicleType::MOTORCYCLE: return "Motorcycle";
        case VehicleType::TRUCK:      return "Truck";
        case VehicleType::ELECTRIC:   return "Electric";
    }
    return "Unknown";
}

inline std::string spotTypeStr(SpotType t) {
    switch (t) {
        case SpotType::COMPACT:    return "Compact";
        case SpotType::LARGE:      return "Large";
        case SpotType::MOTORCYCLE: return "Motorcycle";
        case SpotType::ELECTRIC:   return "Electric";
    }
    return "Unknown";
}

// ═══════════════════════════════════════════════════════════════
// VEHICLE HIERARCHY
// ═══════════════════════════════════════════════════════════════

class Vehicle {
protected:
    std::string licensePlate;
    VehicleType vehicleType;
public:
    Vehicle(std::string plate, VehicleType type)
        : licensePlate(std::move(plate)), vehicleType(type) {}

    virtual std::string      getLicensePlate() const { return licensePlate; }
    virtual VehicleType      getType()         const { return vehicleType; }
    virtual SpotType         getRequiredSpotType() const = 0;
    virtual std::string      toString() const {
        return vehicleTypeStr(vehicleType) + "[" + licensePlate + "]";
    }
    virtual ~Vehicle() = default;
};

class Car : public Vehicle {
public:
    explicit Car(std::string plate) : Vehicle(std::move(plate), VehicleType::CAR) {}
    SpotType getRequiredSpotType() const override { return SpotType::COMPACT; }
};

class Motorcycle : public Vehicle {
public:
    explicit Motorcycle(std::string plate) : Vehicle(std::move(plate), VehicleType::MOTORCYCLE) {}
    SpotType getRequiredSpotType() const override { return SpotType::MOTORCYCLE; }
};

class Truck : public Vehicle {
public:
    explicit Truck(std::string plate) : Vehicle(std::move(plate), VehicleType::TRUCK) {}
    SpotType getRequiredSpotType() const override { return SpotType::LARGE; }
};

class ElectricVehicle : public Vehicle {
public:
    explicit ElectricVehicle(std::string plate) : Vehicle(std::move(plate), VehicleType::ELECTRIC) {}
    SpotType getRequiredSpotType() const override { return SpotType::ELECTRIC; }
};

// ═══════════════════════════════════════════════════════════════
// PARKING SPOT
// ═══════════════════════════════════════════════════════════════

class ParkingSpot {
    std::string spotId;
    SpotType    type;
    SpotStatus  status;
    Vehicle*    parkedVehicle;
    int         floorNo;
    int         spotNo;

public:
    ParkingSpot(std::string id, SpotType t, int floor, int spot)
        : spotId(std::move(id)), type(t), status(SpotStatus::FREE),
          parkedVehicle(nullptr), floorNo(floor), spotNo(spot) {}

    bool       isFree()    const { return status == SpotStatus::FREE; }
    SpotType   getType()   const { return type; }
    SpotStatus getStatus() const { return status; }
    std::string getId()    const { return spotId; }
    int        getFloor()  const { return floorNo; }
    int        getSpotNo() const { return spotNo; }
    Vehicle*   getVehicle() const { return parkedVehicle; }

    bool assign(Vehicle* vehicle) {
        if (!isFree()) return false;
        parkedVehicle = vehicle;
        status = SpotStatus::OCCUPIED;
        return true;
    }

    void release() {
        parkedVehicle = nullptr;
        status = SpotStatus::FREE;
    }

    void markOutOfService() { status = SpotStatus::OUT_OF_SERVICE; }

    std::string toString() const {
        std::ostringstream oss;
        oss << "Spot[" << spotId << " F" << floorNo << " "
            << spotTypeStr(type) << " "
            << (isFree() ? "FREE" : "OCCUPIED") << "]";
        return oss.str();
    }
};

// ═══════════════════════════════════════════════════════════════
// PARKING TICKET
// ═══════════════════════════════════════════════════════════════

class ParkingTicket {
    static int ticketCounter;

    std::string ticketId;
    std::string spotId;
    std::string vehiclePlate;
    VehicleType vehicleType;
    SpotType    spotType;
    int         floorNo;
    std::chrono::system_clock::time_point entryTime;
    bool        paid = false;

public:
    ParkingTicket(const std::string& spot, const Vehicle& vehicle, int floor, SpotType st)
        : spotId(spot), vehiclePlate(vehicle.getLicensePlate()),
          vehicleType(vehicle.getType()), spotType(st),
          floorNo(floor), entryTime(std::chrono::system_clock::now()) {
        ticketId = "TKT-" + std::to_string(++ticketCounter);
    }

    std::string                              getTicketId()  const { return ticketId; }
    std::string                              getSpotId()    const { return spotId; }
    std::string                              getVehiclePlate() const { return vehiclePlate; }
    SpotType                                 getSpotType()  const { return spotType; }
    int                                      getFloorNo()   const { return floorNo; }
    std::chrono::system_clock::time_point    getEntryTime() const { return entryTime; }
    bool                                     isPaid()       const { return paid; }
    void                                     markPaid()           { paid = true; }

    double getHoursParked() const {
        auto now  = std::chrono::system_clock::now();
        auto diff = std::chrono::duration_cast<std::chrono::seconds>(now - entryTime).count();
        return std::max(1.0, diff / 3600.0);  // Minimum 1 hour
    }

    void print() const {
        auto t = std::chrono::system_clock::to_time_t(entryTime);
        std::cout << "┌─────────────────────────────────┐\n";
        std::cout << "│  PARKING TICKET                 │\n";
        std::cout << "│  ID:      " << std::setw(22) << std::left << ticketId << "│\n";
        std::cout << "│  Vehicle: " << std::setw(22) << vehiclePlate  << "│\n";
        std::cout << "│  Spot:    " << std::setw(22) << spotId        << "│\n";
        std::cout << "│  Floor:   " << std::setw(22) << floorNo       << "│\n";
        std::cout << "│  Entry:   " << std::setw(22) << std::string(std::ctime(&t)).substr(0,19) << "│\n";
        std::cout << "└─────────────────────────────────┘\n";
    }
};
int ParkingTicket::ticketCounter = 0;

// ═══════════════════════════════════════════════════════════════
// FEE STRATEGY (OCP — add new strategies without modifying core)
// ═══════════════════════════════════════════════════════════════

class IFeeStrategy {
public:
    virtual double calculate(double hours, SpotType spotType) const = 0;
    virtual ~IFeeStrategy() = default;
};

class HourlyFeeStrategy : public IFeeStrategy {
    std::unordered_map<SpotType, double> hourlyRates;
public:
    HourlyFeeStrategy() {
        hourlyRates[SpotType::MOTORCYCLE] = 1.0;
        hourlyRates[SpotType::COMPACT]    = 2.0;
        hourlyRates[SpotType::LARGE]      = 3.5;
        hourlyRates[SpotType::ELECTRIC]   = 2.5;
    }
    double calculate(double hours, SpotType spotType) const override {
        return hours * hourlyRates.at(spotType);
    }
};

class WeekendSurchargeStrategy : public IFeeStrategy {
    IFeeStrategy& base;
    double surchargeMultiplier;
public:
    WeekendSurchargeStrategy(IFeeStrategy& b, double mult = 1.5)
        : base(b), surchargeMultiplier(mult) {}
    double calculate(double hours, SpotType spotType) const override {
        return base.calculate(hours, spotType) * surchargeMultiplier;
    }
};

// ═══════════════════════════════════════════════════════════════
// PARKING FLOOR
// ═══════════════════════════════════════════════════════════════

class ParkingFloor {
    int floorNo;
    std::vector<std::unique_ptr<ParkingSpot>> spots;
    mutable std::mutex floorMutex;

public:
    explicit ParkingFloor(int no) : floorNo(no) {}

    void addSpot(std::unique_ptr<ParkingSpot> spot) {
        spots.push_back(std::move(spot));
    }

    // Find the first free spot matching the required type
    ParkingSpot* findFreeSpot(SpotType required) {
        std::lock_guard<std::mutex> lock(floorMutex);
        for (auto& spot : spots) {
            if (spot->getType() == required && spot->isFree())
                return spot.get();
        }
        return nullptr;
    }

    ParkingSpot* findSpotById(const std::string& id) {
        for (auto& s : spots)
            if (s->getId() == id) return s.get();
        return nullptr;
    }

    int getAvailableCount(SpotType type) const {
        std::lock_guard<std::mutex> lock(floorMutex);
        int count = 0;
        for (const auto& spot : spots)
            if (spot->getType() == type && spot->isFree()) count++;
        return count;
    }

    int getTotalCount(SpotType type) const {
        int count = 0;
        for (const auto& spot : spots)
            if (spot->getType() == type) count++;
        return count;
    }

    int getFloorNo() const { return floorNo; }
    size_t spotCount() const { return spots.size(); }
};

// ═══════════════════════════════════════════════════════════════
// DISPLAY BOARD
// ═══════════════════════════════════════════════════════════════

class DisplayBoard {
public:
    void show(const std::vector<std::unique_ptr<ParkingFloor>>& floors) const {
        std::cout << "\n╔══════════════════════════════════════╗\n";
        std::cout <<   "║       PARKING LOT AVAILABILITY       ║\n";
        std::cout <<   "╠══════════╦══════╦══════╦══════╦══════╣\n";
        std::cout <<   "║  Floor   ║ Moto ║ Comp ║ Lrge ║ Elec ║\n";
        std::cout <<   "╠══════════╬══════╬══════╬══════╬══════╣\n";
        for (const auto& floor : floors) {
            printf("║  Floor %-2d║  %3d ║  %3d ║  %3d ║  %3d ║\n",
                floor->getFloorNo(),
                floor->getAvailableCount(SpotType::MOTORCYCLE),
                floor->getAvailableCount(SpotType::COMPACT),
                floor->getAvailableCount(SpotType::LARGE),
                floor->getAvailableCount(SpotType::ELECTRIC)
            );
        }
        std::cout << "╚══════════╩══════╩══════╩══════╩══════╝\n\n";
    }
};

// ═══════════════════════════════════════════════════════════════
// PARKING LOT — MAIN FACADE
// ═══════════════════════════════════════════════════════════════

class ParkingLot {
    std::string name;
    std::string address;
    std::vector<std::unique_ptr<ParkingFloor>> floors;
    std::unordered_map<std::string, ParkingTicket> activeTickets;
    std::unique_ptr<IFeeStrategy> feeStrategy;
    DisplayBoard displayBoard;
    mutable std::mutex lotMutex;

public:
    ParkingLot(std::string n, std::string addr, std::unique_ptr<IFeeStrategy> fee)
        : name(std::move(n)), address(std::move(addr)), feeStrategy(std::move(fee)) {}

    void addFloor(std::unique_ptr<ParkingFloor> floor) {
        floors.push_back(std::move(floor));
    }

    // ENTRY: Find spot → assign → issue ticket
    std::optional<ParkingTicket> park(Vehicle& vehicle) {
        std::lock_guard<std::mutex> lock(lotMutex);
        SpotType required = vehicle.getRequiredSpotType();

        // Search floors in order (ground floor first)
        for (auto& floor : floors) {
            ParkingSpot* spot = floor->findFreeSpot(required);
            if (spot) {
                spot->assign(&vehicle);
                ParkingTicket ticket(spot->getId(), vehicle, floor->getFloorNo(), required);
                activeTickets.emplace(ticket.getTicketId(), ticket);
                std::cout << "✅ " << vehicle.toString()
                          << " parked at " << spot->toString() << "\n";
                return ticket;
            }
        }
        std::cout << "❌ No available spot for " << vehicle.toString() << "\n";
        return std::nullopt;
    }

    // EXIT: Look up ticket → calculate fee → release spot
    double unpark(const std::string& ticketId) {
        std::lock_guard<std::mutex> lock(lotMutex);
        auto it = activeTickets.find(ticketId);
        if (it == activeTickets.end()) {
            throw std::runtime_error("Invalid ticket: " + ticketId);
        }

        ParkingTicket& ticket = it->second;
        double hours = ticket.getHoursParked();
        double fee   = feeStrategy->calculate(hours, ticket.getSpotType());

        // Release the spot
        for (auto& floor : floors) {
            ParkingSpot* spot = floor->findSpotById(ticket.getSpotId());
            if (spot) { spot->release(); break; }
        }

        ticket.markPaid();

        std::cout << "🚗 Vehicle " << ticket.getVehiclePlate()
                  << " exited. Hours: " << std::fixed << std::setprecision(2) << hours
                  << "h. Fee: $" << std::fixed << std::setprecision(2) << fee << "\n";

        activeTickets.erase(it);
        return fee;
    }

    void showDisplay() const { displayBoard.show(floors); }

    std::string getName() const { return name; }
};

// ═══════════════════════════════════════════════════════════════
// FACTORY — Build Parking Lot (Builder Pattern)
// ═══════════════════════════════════════════════════════════════

class ParkingLotBuilder {
    std::unique_ptr<ParkingLot> lot;
    int spotIdCounter = 0;

    std::string nextSpotId() { return "S" + std::to_string(++spotIdCounter); }

public:
    ParkingLotBuilder(const std::string& name, const std::string& address) {
        lot = std::make_unique<ParkingLot>(name, address,
              std::make_unique<HourlyFeeStrategy>());
    }

    ParkingLotBuilder& addFloor(int floorNo,
        int motorcycle, int compact, int large, int electric) {

        auto floor = std::make_unique<ParkingFloor>(floorNo);

        for (int i = 0; i < motorcycle; i++)
            floor->addSpot(std::make_unique<ParkingSpot>(
                nextSpotId(), SpotType::MOTORCYCLE, floorNo, spotIdCounter));
        for (int i = 0; i < compact; i++)
            floor->addSpot(std::make_unique<ParkingSpot>(
                nextSpotId(), SpotType::COMPACT, floorNo, spotIdCounter));
        for (int i = 0; i < large; i++)
            floor->addSpot(std::make_unique<ParkingSpot>(
                nextSpotId(), SpotType::LARGE, floorNo, spotIdCounter));
        for (int i = 0; i < electric; i++)
            floor->addSpot(std::make_unique<ParkingSpot>(
                nextSpotId(), SpotType::ELECTRIC, floorNo, spotIdCounter));

        lot->addFloor(std::move(floor));
        return *this;
    }

    std::unique_ptr<ParkingLot> build() { return std::move(lot); }
};

// ═══════════════════════════════════════════════════════════════
// DEMO
// ═══════════════════════════════════════════════════════════════

int main() {
    std::cout << "════════ PARKING LOT SYSTEM DEMO ════════\n\n";

    // Build the parking lot
    auto lot = ParkingLotBuilder("City Centre Parking", "123 Main St")
        .addFloor(0, /*moto*/2, /*compact*/4, /*large*/2, /*electric*/2)
        .addFloor(1, /*moto*/2, /*compact*/6, /*large*/2, /*electric*/2)
        .build();

    lot->showDisplay();

    // Create vehicles
    Car         car1("KA-01-AB-1234");
    Car         car2("DL-04-CD-5678");
    Motorcycle  moto1("MH-02-EF-9999");
    Truck       truck1("TN-09-GH-0001");
    ElectricVehicle ev1("GJ-05-IJ-3333");

    // Park vehicles
    auto t1 = lot->park(car1);
    auto t2 = lot->park(car2);
    auto t3 = lot->park(moto1);
    auto t4 = lot->park(truck1);
    auto t5 = lot->park(ev1);

    if (t1) t1->print();

    lot->showDisplay();

    // Exit vehicles
    if (t1) lot->unpark(t1->getTicketId());
    if (t3) lot->unpark(t3->getTicketId());
    if (t4) lot->unpark(t4->getTicketId());

    lot->showDisplay();

    return 0;
}
```

### 9.5 Design Decisions — Interview Talking Points

```
Question: "Why did you use composition over inheritance for ParkingFloor in ParkingLot?"
Answer:   ParkingLot HAS-A ParkingFloor, not IS-A. Composition gives us runtime
          flexibility to add floors dynamically.

Question: "How does your design handle new vehicle types?"
Answer:   Add a new Vehicle subclass (e.g., Van), override getRequiredSpotType().
          Zero changes to ParkingLot, ParkingFloor, or ParkingSpot — OCP satisfied.

Question: "How is thread safety handled?"
Answer:   std::mutex in ParkingFloor for spot assignment and in ParkingLot for
          ticket management. lock_guard ensures RAII-style release.

Question: "How would you add dynamic pricing?"
Answer:   IFeeStrategy (Strategy pattern). WeekendSurchargeStrategy already decorates
          HourlyFeeStrategy. New pricing = new class only.
```

---

## 10. LLD Problem 2: Snake & Ladder Game

### 10.1 Requirements Gathering

**Functional Requirements**
```
✅ Configurable board size (default 100 cells, 10×10)
✅ Multiple players (2–4)
✅ Configurable snakes and ladders
✅ Dice roll (1–6, configurable faces)
✅ Player wins when they reach exactly the last cell
✅ Landing exactly on a snake head → slides down
✅ Landing exactly on a ladder bottom → climbs up
✅ Turn-based gameplay with console output
✅ Game history / move log
```

**Non-Functional**
```
✅ Extensible: weighted dice, special cells, power-ups
✅ Testable: injectable random number generator
```

### 10.2 UML Class Diagram

```
┌──────────────────┐       ┌────────────────────┐
│      Game        │◆─────▶│      Board         │
├──────────────────┤       ├────────────────────┤
│ -players         │       │ -size: int         │
│ -currentPlayer   │       │ -snakes: map       │
│ -status          │       │ -ladders: map      │
├──────────────────┤       ├────────────────────┤
│ +start()         │       │ +getNextCell()     │
│ +playTurn()      │       │ +addSnake()        │
│ +isOver(): bool  │       │ +addLadder()       │
└────────┬─────────┘       └────────────────────┘
         │◆
    ┌────▼─────┐    ┌──────────────────────┐
    │  Player  │    │     Dice             │
    ├──────────┤    ├──────────────────────┤
    │ -name    │    │ -faces: int          │
    │ -pos     │    ├──────────────────────┤
    ├──────────┤    │ +roll(): int         │
    │ +move()  │    └──────────────────────┘
    └──────────┘

    «interface»                   «interface»
    ICell                         IDice
    +getNext(pos): int            +roll(): int
         ▲                              ▲
    ┌────┴─────┐              ┌─────────┴──────┐
  SnakeCell  LadderCell    FairDice    WeightedDice
```

### 10.3 Complete C++ Implementation

```cpp
#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <string>
#include <random>
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <functional>

// ═══════════════════════════════════════════════════════════════
// DICE — Strategy Pattern (injectable, testable)
// ═══════════════════════════════════════════════════════════════

class IDice {
public:
    virtual int roll() = 0;
    virtual int getFaces() const = 0;
    virtual ~IDice() = default;
};

class FairDice : public IDice {
    int faces;
    std::mt19937 rng;
    std::uniform_int_distribution<int> dist;
public:
    explicit FairDice(int f = 6)
        : faces(f), rng(std::random_device{}()), dist(1, f) {}

    int roll() override { return dist(rng); }
    int getFaces() const override { return faces; }
};

// Deterministic dice for testing
class MockDice : public IDice {
    std::vector<int> sequence;
    size_t           index = 0;
public:
    explicit MockDice(std::vector<int> seq) : sequence(std::move(seq)) {}
    int roll() override {
        if (index >= sequence.size()) index = 0;
        return sequence[index++];
    }
    int getFaces() const override { return 6; }
};

// ═══════════════════════════════════════════════════════════════
// CELL — Represents what happens when you land on a cell
// ═══════════════════════════════════════════════════════════════

class ICell {
public:
    virtual int getStart() const = 0;
    virtual int getEnd()   const = 0;
    virtual std::string getDescription() const = 0;
    virtual ~ICell() = default;
};

class Snake : public ICell {
    int head, tail;
public:
    Snake(int h, int t) : head(h), tail(t) {
        if (h <= t) throw std::invalid_argument("Snake head must be above tail");
    }
    int getStart() const override { return head; }
    int getEnd()   const override { return tail; }
    std::string getDescription() const override {
        return "🐍 Snake: " + std::to_string(head) + " → " + std::to_string(tail);
    }
};

class Ladder : public ICell {
    int bottom, top;
public:
    Ladder(int b, int t) : bottom(b), top(t) {
        if (b >= t) throw std::invalid_argument("Ladder top must be above bottom");
    }
    int getStart() const override { return bottom; }
    int getEnd()   const override { return top; }
    std::string getDescription() const override {
        return "🪜 Ladder: " + std::to_string(bottom) + " → " + std::to_string(top);
    }
};

// ═══════════════════════════════════════════════════════════════
// PLAYER
// ═══════════════════════════════════════════════════════════════

class Player {
    std::string name;
    int         position;  // 0 = not on board yet, 1..N = on board

public:
    explicit Player(std::string n) : name(std::move(n)), position(0) {}

    std::string getName()     const { return name; }
    int         getPosition() const { return position; }

    void moveTo(int pos) { position = pos; }

    std::string toString() const {
        return name + " @ " + std::to_string(position);
    }
};

// ═══════════════════════════════════════════════════════════════
// MOVE LOG
// ═══════════════════════════════════════════════════════════════

struct MoveRecord {
    std::string playerName;
    int         fromPos;
    int         rolled;
    int         landedAt;
    int         finalPos;
    std::string event;    // "Snake", "Ladder", ""
};

// ═══════════════════════════════════════════════════════════════
// BOARD
// ═══════════════════════════════════════════════════════════════

class Board {
    int boardSize;
    std::unordered_map<int, std::unique_ptr<ICell>> cells;

public:
    explicit Board(int size = 100) : boardSize(size) {}

    void addSnake(int head, int tail) {
        cells[head] = std::make_unique<Snake>(head, tail);
    }

    void addLadder(int bottom, int top) {
        cells[bottom] = std::make_unique<Ladder>(bottom, top);
    }

    // Returns the final position after applying any snake/ladder
    int getNextPosition(int current, int roll) const {
        int next = current + roll;
        if (next > boardSize) return current;  // Can't overshoot the end
        if (next == boardSize) return next;     // Win!
        auto it = cells.find(next);
        if (it != cells.end()) return it->second->getEnd();
        return next;
    }

    // Returns event string if any special cell
    std::string getEvent(int pos) const {
        auto it = cells.find(pos);
        if (it == cells.end()) return "";
        return it->second->getDescription();
    }

    int getSize() const { return boardSize; }

    void printBoard() const {
        std::cout << "\n=== Board Configuration ===\n";
        std::cout << "Board Size: " << boardSize << "\n";
        for (const auto& [k, v] : cells)
            std::cout << "  " << v->getDescription() << "\n";
        std::cout << "===========================\n\n";
    }
};

// ═══════════════════════════════════════════════════════════════
// GAME STATE — State Pattern
// ═══════════════════════════════════════════════════════════════

enum class GameStatus { WAITING, IN_PROGRESS, FINISHED };

// ═══════════════════════════════════════════════════════════════
// GAME — Orchestrator
// ═══════════════════════════════════════════════════════════════

class SnakeLadderGame {
    Board                       board;
    std::unique_ptr<IDice>      dice;
    std::vector<Player>         players;
    int                         currentPlayerIdx;
    GameStatus                  status;
    std::vector<MoveRecord>     moveHistory;
    std::string                 winner;

    // Observer callbacks (extensibility)
    std::vector<std::function<void(const MoveRecord&)>> moveObservers;

    void notifyObservers(const MoveRecord& record) {
        for (auto& cb : moveObservers) cb(record);
    }

public:
    SnakeLadderGame(Board b, std::unique_ptr<IDice> d)
        : board(std::move(b)), dice(std::move(d)),
          currentPlayerIdx(0), status(GameStatus::WAITING) {}

    void addPlayer(const std::string& name) {
        if (status != GameStatus::WAITING)
            throw std::runtime_error("Cannot add player after game started");
        if (players.size() >= 4)
            throw std::runtime_error("Maximum 4 players");
        players.emplace_back(name);
    }

    void onMove(std::function<void(const MoveRecord&)> cb) {
        moveObservers.push_back(std::move(cb));
    }

    void start() {
        if (players.size() < 2)
            throw std::runtime_error("Need at least 2 players");
        status = GameStatus::IN_PROGRESS;
        std::cout << "🎲 Game started with "
                  << players.size() << " players!\n\n";
    }

    // Returns true if game is over
    bool playTurn() {
        if (status != GameStatus::IN_PROGRESS)
            throw std::runtime_error("Game is not in progress");

        Player& current = players[currentPlayerIdx];
        int rolled      = dice->roll();
        int fromPos     = current.getPosition();
        int landedAt    = fromPos + rolled;
        std::string event;

        int finalPos;

        if (landedAt > board.getSize()) {
            // Overshoot — stay put
            finalPos = fromPos;
            event    = "Overshoot! Stay at " + std::to_string(fromPos);
        } else {
            // Check for snake or ladder at landedAt
            finalPos = board.getNextPosition(fromPos, rolled);
            event    = board.getEvent(landedAt);
        }

        current.moveTo(finalPos);

        MoveRecord record{ current.getName(), fromPos, rolled,
                           landedAt, finalPos, event };
        moveHistory.push_back(record);
        notifyObservers(record);

        // Print turn
        std::cout << "🎲 " << current.getName()
                  << " rolled " << rolled
                  << " | " << fromPos << " → " << landedAt;
        if (!event.empty()) std::cout << " (" << event << ")";
        std::cout << " | Final: " << finalPos << "\n";

        // Check win
        if (finalPos == board.getSize()) {
            status = GameStatus::FINISHED;
            winner = current.getName();
            std::cout << "\n🏆 " << winner << " WINS! 🏆\n";
            printLeaderboard();
            return true;
        }

        // Advance to next player
        currentPlayerIdx = (currentPlayerIdx + 1) % players.size();
        return false;
    }

    void playFullGame() {
        start();
        while (status != GameStatus::FINISHED) {
            playTurn();
        }
    }

    void printLeaderboard() const {
        std::cout << "\n=== Final Positions ===\n";
        for (const auto& p : players)
            std::cout << "  " << p.getName() << ": "
                      << p.getPosition() << "\n";
    }

    void printMoveHistory() const {
        std::cout << "\n=== Move History ===\n";
        for (const auto& m : moveHistory) {
            std::cout << m.playerName << ": rolled " << m.rolled
                      << " | " << m.fromPos << "→" << m.finalPos;
            if (!m.event.empty()) std::cout << " [" << m.event << "]";
            std::cout << "\n";
        }
    }

    const std::string& getWinner() const { return winner; }
    GameStatus         getStatus() const { return status; }
    int getTotalMoves() const { return (int)moveHistory.size(); }
};

// ═══════════════════════════════════════════════════════════════
// GAME BUILDER — Builder Pattern
// ═══════════════════════════════════════════════════════════════

class GameBuilder {
    Board              board;
    std::unique_ptr<IDice> dice;
    std::vector<std::string> playerNames;

public:
    GameBuilder() : board(100), dice(std::make_unique<FairDice>()) {}

    GameBuilder& withBoardSize(int n)   { board = Board(n); return *this; }
    GameBuilder& withDice(std::unique_ptr<IDice> d) { dice = std::move(d); return *this; }
    GameBuilder& withPlayer(const std::string& name) {
        playerNames.push_back(name); return *this;
    }
    GameBuilder& withSnake(int head, int tail) {
        board.addSnake(head, tail); return *this;
    }
    GameBuilder& withLadder(int bottom, int top) {
        board.addLadder(bottom, top); return *this;
    }

    std::unique_ptr<SnakeLadderGame> build() {
        auto game = std::make_unique<SnakeLadderGame>(
            std::move(board), std::move(dice)
        );
        for (const auto& name : playerNames) game->addPlayer(name);
        return game;
    }
};

// ═══════════════════════════════════════════════════════════════
// DEMO
// ═══════════════════════════════════════════════════════════════

int main() {
    std::cout << "════════ SNAKE & LADDER GAME DEMO ════════\n\n";

    // Build a game with fixed dice for reproducibility
    auto game = GameBuilder()
        .withPlayer("Alice")
        .withPlayer("Bob")
        .withPlayer("Charlie")
        .withSnake(99, 5)
        .withSnake(70, 15)
        .withSnake(52, 23)
        .withSnake(25, 7)
        .withLadder(4, 56)
        .withLadder(13, 46)
        .withLadder(33, 88)
        .withLadder(65, 90)
        .build();

    // Register a move observer — extensibility demo
    game->onMove([](const MoveRecord& r) {
        if (!r.event.empty())
            std::cout << "   ↳ [Event] " << r.event << "\n";
    });

    game->playFullGame();

    std::cout << "\nTotal moves played: " << game->getTotalMoves() << "\n";

    return 0;
}
```

### 10.4 Design Decisions

```
Question: "How does your design allow dice to be testable?"
Answer:   IDice is an interface. MockDice injects a known sequence,
          enabling deterministic unit tests without randomness.

Question: "How do you add a new special cell like a Teleporter?"
Answer:   Create class Teleporter : public ICell, implement getStart()/getEnd().
          Add to Board via addCell(). Zero changes to Game, Board, or Player.

Question: "Where is the State pattern used?"
Answer:   GameStatus enum (WAITING/IN_PROGRESS/FINISHED) controls what operations
          are legal. playTurn() throws if not IN_PROGRESS. This could be formalised
          into full State classes for more complex rules.
```

---

## 11. LLD Problem 3: Library Management System

### 11.1 Requirements Gathering

**Functional Requirements**
```
✅ Add/remove books (by ISBN, multiple copies supported)
✅ Member registration and management
✅ Borrow and return books
✅ Fine calculation for late returns
✅ Search books by title, author, ISBN, genre
✅ Reserve books when all copies are checked out
✅ Notification when reserved book becomes available
✅ Borrowing limit per member (max 5 books)
✅ Book catalogue with metadata
```

**Non-Functional**
```
✅ SOLID, OCP for member types (Student, Faculty with different limits)
✅ Observer for reservation notifications
✅ Strategy for fine calculation
```

### 11.2 UML Class Diagram

```
┌─────────────────┐         ┌──────────────────────┐
│    Library      │◆───────▶│   BookCatalogue      │
├─────────────────┤         ├──────────────────────┤
│ -name: string   │         │ -books: map          │
├─────────────────┤         ├──────────────────────┤
│ +addBook()      │         │ +search()            │
│ +registerMember │         │ +findByISBN()        │
│ +borrow()       │         └──────────────────────┘
│ +returnBook()   │
│ +reserve()      │         ┌──────────────────────┐
└─────────────────┘◆───────▶│   MemberRegistry     │
                             ├──────────────────────┤
                             │ +addMember()         │
                             │ +findMember()        │
                             └──────────────────────┘
«interface»
IMember
+getBorrowLimit()
+getMemberId()
       ▲
  ┌────┴──────┐
Student   Faculty    ← Different limits (OCP)

BookItem (physical copy)
 -barcode: string
 -status: BookStatus
 -dueDate: optional<date>
```

### 11.3 Complete C++ Implementation

```cpp
#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <string>
#include <optional>
#include <chrono>
#include <algorithm>
#include <stdexcept>
#include <functional>
#include <queue>
#include <iomanip>
#include <sstream>
#include <ctime>

using Clock     = std::chrono::system_clock;
using TimePoint = std::chrono::system_clock::time_point;

// ═══════════════════════════════════════════════════════════════
// UTILITIES
// ═══════════════════════════════════════════════════════════════

inline std::string formatDate(const TimePoint& tp) {
    auto t = Clock::to_time_t(tp);
    std::string s = std::ctime(&t);
    if (!s.empty() && s.back() == '\n') s.pop_back();
    return s;
}

inline TimePoint daysFromNow(int days) {
    return Clock::now() + std::chrono::hours(24 * days);
}

inline double daysBetween(const TimePoint& a, const TimePoint& b) {
    return std::abs(std::chrono::duration_cast<std::chrono::hours>(b - a).count() / 24.0);
}

// ═══════════════════════════════════════════════════════════════
// ENUMS
// ═══════════════════════════════════════════════════════════════

enum class BookItemStatus { AVAILABLE, BORROWED, RESERVED, LOST };
enum class MemberStatus   { ACTIVE, SUSPENDED, EXPIRED };

inline std::string statusStr(BookItemStatus s) {
    switch (s) {
        case BookItemStatus::AVAILABLE: return "Available";
        case BookItemStatus::BORROWED:  return "Borrowed";
        case BookItemStatus::RESERVED:  return "Reserved";
        case BookItemStatus::LOST:      return "Lost";
    }
    return "";
}

// ═══════════════════════════════════════════════════════════════
// FINE STRATEGY — OCP
// ═══════════════════════════════════════════════════════════════

class IFineStrategy {
public:
    virtual double calculateFine(double daysLate) const = 0;
    virtual ~IFineStrategy() = default;
};

class FixedDailyFine : public IFineStrategy {
    double ratePerDay;
public:
    explicit FixedDailyFine(double rate = 1.0) : ratePerDay(rate) {}
    double calculateFine(double daysLate) const override {
        return std::max(0.0, daysLate) * ratePerDay;
    }
};

class TieredFine : public IFineStrategy {
public:
    double calculateFine(double daysLate) const override {
        if (daysLate <= 0)  return 0.0;
        if (daysLate <= 7)  return daysLate * 0.50;   // $0.50/day first week
        if (daysLate <= 30) return 3.50 + (daysLate - 7) * 1.00;  // $1/day next
        return 3.50 + 23.00 + (daysLate - 30) * 2.00; // $2/day after a month
    }
};

// ═══════════════════════════════════════════════════════════════
// BOOK CATALOGUE ITEM (metadata)
// ═══════════════════════════════════════════════════════════════

class Book {
    std::string isbn;
    std::string title;
    std::string author;
    std::string genre;
    int         year;
    std::string publisher;

public:
    Book(std::string isbn, std::string title, std::string author,
         std::string genre, int year, std::string publisher = "")
        : isbn(std::move(isbn)), title(std::move(title)), author(std::move(author)),
          genre(std::move(genre)), year(year), publisher(std::move(publisher)) {}

    const std::string& getISBN()      const { return isbn; }
    const std::string& getTitle()     const { return title; }
    const std::string& getAuthor()    const { return author; }
    const std::string& getGenre()     const { return genre; }
    int                getYear()      const { return year; }

    std::string toString() const {
        return "\"" + title + "\" by " + author + " [" + isbn + "]";
    }
};

// ═══════════════════════════════════════════════════════════════
// BOOK ITEM (physical copy)
// ═══════════════════════════════════════════════════════════════

class BookItem {
    static int barcodeCounter;

    std::string      barcode;
    std::string      isbn;
    BookItemStatus   status;
    std::optional<TimePoint> dueDate;
    std::string      borrowedByMemberId;

public:
    explicit BookItem(const std::string& bookIsbn)
        : barcode("BC-" + std::to_string(++barcodeCounter)),
          isbn(bookIsbn), status(BookItemStatus::AVAILABLE) {}

    const std::string& getBarcode()  const { return barcode; }
    const std::string& getISBN()     const { return isbn; }
    BookItemStatus     getStatus()   const { return status; }
    bool               isAvailable() const { return status == BookItemStatus::AVAILABLE; }

    std::optional<TimePoint> getDueDate() const { return dueDate; }
    const std::string& getBorrowedBy() const { return borrowedByMemberId; }

    void checkout(const std::string& memberId, int loanDays = 14) {
        status             = BookItemStatus::BORROWED;
        borrowedByMemberId = memberId;
        dueDate            = daysFromNow(loanDays);
    }

    void returnItem() {
        status             = BookItemStatus::AVAILABLE;
        borrowedByMemberId = "";
        dueDate            = std::nullopt;
    }

    double getOverdueDays() const {
        if (status != BookItemStatus::BORROWED || !dueDate) return 0;
        auto now = Clock::now();
        if (now <= *dueDate) return 0;
        return daysBetween(*dueDate, now);
    }

    std::string toString() const {
        std::string s = "BookItem[" + barcode + " " + statusStr(status) + "]";
        if (dueDate) s += " due:" + formatDate(*dueDate);
        return s;
    }
};
int BookItem::barcodeCounter = 0;

// ═══════════════════════════════════════════════════════════════
// NOTIFICATION — Observer
// ═══════════════════════════════════════════════════════════════

class INotificationObserver {
public:
    virtual void onBookAvailable(const std::string& memberId,
                                  const std::string& bookTitle) = 0;
    virtual ~INotificationObserver() = default;
};

class ConsoleNotifier : public INotificationObserver {
public:
    void onBookAvailable(const std::string& memberId,
                          const std::string& bookTitle) override {
        std::cout << "📬 NOTIFICATION → Member [" << memberId
                  << "]: \"" << bookTitle << "\" is now available!\n";
    }
};

// ═══════════════════════════════════════════════════════════════
// MEMBER HIERARCHY — OCP (new member types = new class)
// ═══════════════════════════════════════════════════════════════

class Member {
protected:
    std::string memberId;
    std::string name;
    std::string email;
    MemberStatus status;
    std::vector<std::string> borrowedBarcodes;

public:
    Member(std::string id, std::string n, std::string e)
        : memberId(std::move(id)), name(std::move(n)), email(std::move(e)),
          status(MemberStatus::ACTIVE) {}

    virtual int    getBorrowLimit()    const = 0;
    virtual int    getLoanDays()       const = 0;
    virtual std::string getMemberType() const = 0;
    virtual ~Member() = default;

    const std::string& getMemberId() const { return memberId; }
    const std::string& getName()     const { return name; }
    const std::string& getEmail()    const { return email; }
    MemberStatus       getStatus()   const { return status; }
    bool               isActive()    const { return status == MemberStatus::ACTIVE; }

    int getBorrowedCount() const { return (int)borrowedBarcodes.size(); }
    bool canBorrow()       const { return isActive() && getBorrowedCount() < getBorrowLimit(); }

    void addBorrowedBook(const std::string& barcode) {
        borrowedBarcodes.push_back(barcode);
    }
    void removeBorrowedBook(const std::string& barcode) {
        borrowedBarcodes.erase(
            std::remove(borrowedBarcodes.begin(), borrowedBarcodes.end(), barcode),
            borrowedBarcodes.end()
        );
    }
    const std::vector<std::string>& getBorrowedBarcodes() const {
        return borrowedBarcodes;
    }

    void suspend() { status = MemberStatus::SUSPENDED; }

    std::string toString() const {
        return getMemberType() + "[" + memberId + "] " + name +
               " | Borrowed: " + std::to_string(getBorrowedCount()) +
               "/" + std::to_string(getBorrowLimit());
    }
};

class StudentMember : public Member {
public:
    using Member::Member;
    int         getBorrowLimit()    const override { return 3; }
    int         getLoanDays()       const override { return 14; }
    std::string getMemberType()     const override { return "Student"; }
};

class FacultyMember : public Member {
public:
    using Member::Member;
    int         getBorrowLimit()    const override { return 10; }
    int         getLoanDays()       const override { return 60; }
    std::string getMemberType()     const override { return "Faculty"; }
};

class GuestMember : public Member {
public:
    using Member::Member;
    int         getBorrowLimit()    const override { return 1; }
    int         getLoanDays()       const override { return 7; }
    std::string getMemberType()     const override { return "Guest"; }
};

// ═══════════════════════════════════════════════════════════════
// LOAN RECORD
// ═══════════════════════════════════════════════════════════════

struct LoanRecord {
    std::string loanId;
    std::string memberId;
    std::string barcode;
    std::string isbn;
    TimePoint   borrowDate;
    TimePoint   dueDate;
    std::optional<TimePoint> returnDate;
    double      fine = 0.0;

    bool isActive() const { return !returnDate.has_value(); }
};

// ═══════════════════════════════════════════════════════════════
// BOOK CATALOGUE
// ═══════════════════════════════════════════════════════════════

class BookCatalogue {
    // isbn → Book metadata
    std::unordered_map<std::string, Book> books;
    // isbn → list of physical copies
    std::unordered_map<std::string, std::vector<std::unique_ptr<BookItem>>> copies;
    // isbn → queue of member IDs waiting for the book
    std::unordered_map<std::string, std::queue<std::string>> reservations;

public:
    void addBook(Book book) {
        std::string isbn = book.getISBN();
        books.emplace(isbn, std::move(book));
        copies[isbn];       // Ensure entry exists
    }

    void addCopy(const std::string& isbn) {
        if (books.find(isbn) == books.end())
            throw std::runtime_error("Book ISBN not in catalogue: " + isbn);
        copies[isbn].push_back(std::make_unique<BookItem>(isbn));
    }

    // Returns first available copy, or nullptr
    BookItem* findAvailableCopy(const std::string& isbn) {
        auto it = copies.find(isbn);
        if (it == copies.end()) return nullptr;
        for (auto& item : it->second)
            if (item->isAvailable()) return item.get();
        return nullptr;
    }

    BookItem* findByBarcode(const std::string& barcode) {
        for (auto& [isbn, items] : copies)
            for (auto& item : items)
                if (item->getBarcode() == barcode) return item.get();
        return nullptr;
    }

    const Book* findByISBN(const std::string& isbn) const {
        auto it = books.find(isbn);
        return (it != books.end()) ? &it->second : nullptr;
    }

    std::vector<const Book*> searchByTitle(const std::string& query) const {
        std::vector<const Book*> results;
        for (const auto& [isbn, book] : books) {
            std::string title = book.getTitle();
            std::string q     = query;
            std::transform(title.begin(), title.end(), title.begin(), ::tolower);
            std::transform(q.begin(),     q.end(),     q.begin(),     ::tolower);
            if (title.find(q) != std::string::npos) results.push_back(&book);
        }
        return results;
    }

    std::vector<const Book*> searchByAuthor(const std::string& author) const {
        std::vector<const Book*> results;
        for (const auto& [isbn, book] : books) {
            std::string a = book.getAuthor();
            std::string q = author;
            std::transform(a.begin(), a.end(), a.begin(), ::tolower);
            std::transform(q.begin(), q.end(), q.begin(), ::tolower);
            if (a.find(q) != std::string::npos) results.push_back(&book);
        }
        return results;
    }

    void addReservation(const std::string& isbn, const std::string& memberId) {
        reservations[isbn].push(memberId);
    }

    std::optional<std::string> popNextReservation(const std::string& isbn) {
        auto it = reservations.find(isbn);
        if (it == reservations.end() || it->second.empty()) return std::nullopt;
        std::string next = it->second.front();
        it->second.pop();
        return next;
    }

    bool hasReservations(const std::string& isbn) const {
        auto it = reservations.find(isbn);
        return it != reservations.end() && !it->second.empty();
    }

    int getCopyCount(const std::string& isbn) const {
        auto it = copies.find(isbn);
        return it != copies.end() ? (int)it->second.size() : 0;
    }

    int getAvailableCount(const std::string& isbn) const {
        auto it = copies.find(isbn);
        if (it == copies.end()) return 0;
        return std::count_if(it->second.begin(), it->second.end(),
            [](const auto& item){ return item->isAvailable(); });
    }

    void printCatalogue() const {
        std::cout << "\n╔══════════════════════════════════════════════╗\n";
        std::cout <<   "║              BOOK CATALOGUE                  ║\n";
        std::cout <<   "╠══════════════════════════════════════════════╣\n";
        for (const auto& [isbn, book] : books) {
            printf("║  %-44s ║\n", book.toString().substr(0,44).c_str());
            printf("║    Copies: %d total, %d available               ║\n",
                getCopyCount(isbn), getAvailableCount(isbn));
        }
        std::cout << "╚══════════════════════════════════════════════╝\n\n";
    }
};

// ═══════════════════════════════════════════════════════════════
// MEMBER REGISTRY
// ═══════════════════════════════════════════════════════════════

class MemberRegistry {
    std::unordered_map<std::string, std::unique_ptr<Member>> members;
    static int memberCounter;
public:
    std::string addMember(std::unique_ptr<Member> member) {
        std::string id = member->getMemberId();
        members[id]    = std::move(member);
        return id;
    }

    Member* findById(const std::string& id) {
        auto it = members.find(id);
        return it != members.end() ? it->second.get() : nullptr;
    }

    static std::string generateId() {
        return "MBR-" + std::to_string(++memberCounter);
    }
};
int MemberRegistry::memberCounter = 0;

// ═══════════════════════════════════════════════════════════════
// LOAN MANAGER
// ═══════════════════════════════════════════════════════════════

class LoanManager {
    static int loanCounter;
    std::unordered_map<std::string, LoanRecord> loans;  // loanId → record
    IFineStrategy& fineStrategy;

public:
    explicit LoanManager(IFineStrategy& strategy) : fineStrategy(strategy) {}

    LoanRecord createLoan(const std::string& memberId,
                           const std::string& barcode,
                           const std::string& isbn,
                           int loanDays) {
        LoanRecord record;
        record.loanId     = "LOAN-" + std::to_string(++loanCounter);
        record.memberId   = memberId;
        record.barcode    = barcode;
        record.isbn       = isbn;
        record.borrowDate = Clock::now();
        record.dueDate    = daysFromNow(loanDays);
        loans[record.loanId] = record;
        return record;
    }

    LoanRecord* findActiveLoanByBarcode(const std::string& barcode) {
        for (auto& [id, loan] : loans)
            if (loan.barcode == barcode && loan.isActive())
                return &loan;
        return nullptr;
    }

    double closeLoan(const std::string& loanId) {
        auto it = loans.find(loanId);
        if (it == loans.end()) throw std::runtime_error("Loan not found: " + loanId);

        LoanRecord& loan = it->second;
        loan.returnDate = Clock::now();
        double daysLate  = daysBetween(loan.dueDate, *loan.returnDate);
        loan.fine        = fineStrategy.calculateFine(daysLate);
        return loan.fine;
    }

    std::vector<const LoanRecord*> getActiveLoansByMember(const std::string& memberId) const {
        std::vector<const LoanRecord*> result;
        for (const auto& [id, loan] : loans)
            if (loan.memberId == memberId && loan.isActive())
                result.push_back(&loan);
        return result;
    }
};
int LoanManager::loanCounter = 0;

// ═══════════════════════════════════════════════════════════════
// LIBRARY — Main Facade
// ═══════════════════════════════════════════════════════════════

class Library {
    std::string      name;
    BookCatalogue    catalogue;
    MemberRegistry   memberRegistry;
    LoanManager      loanManager;
    std::unique_ptr<INotificationObserver> notifier;

public:
    Library(std::string n, IFineStrategy& fineStrategy,
            std::unique_ptr<INotificationObserver> notif = nullptr)
        : name(std::move(n)), loanManager(fineStrategy),
          notifier(std::move(notif)) {}

    // ── Book Management ──────────────────────────────────────────
    void addBookToCatalogue(Book book) {
        std::cout << "📚 Added to catalogue: " << book.toString() << "\n";
        catalogue.addBook(std::move(book));
    }

    void addCopy(const std::string& isbn) {
        catalogue.addCopy(isbn);
        std::cout << "📖 Added copy for ISBN: " << isbn << "\n";
    }

    // ── Member Management ────────────────────────────────────────
    std::string registerMember(std::unique_ptr<Member> member) {
        std::string id = member->getMemberId();
        std::cout << "👤 Registered: " << member->toString() << "\n";
        return memberRegistry.addMember(std::move(member));
    }

    // ── Borrowing ────────────────────────────────────────────────
    std::optional<LoanRecord> borrowBook(const std::string& memberId,
                                          const std::string& isbn) {
        Member* member = memberRegistry.findById(memberId);
        if (!member) throw std::runtime_error("Member not found: " + memberId);
        if (!member->canBorrow()) {
            std::cout << "❌ " << member->getName()
                      << " cannot borrow (limit reached or suspended)\n";
            return std::nullopt;
        }

        const Book* book = catalogue.findByISBN(isbn);
        if (!book) throw std::runtime_error("Book not in catalogue: " + isbn);

        BookItem* item = catalogue.findAvailableCopy(isbn);
        if (!item) {
            std::cout << "📋 No copies available. Adding reservation for "
                      << member->getName() << "\n";
            catalogue.addReservation(isbn, memberId);
            return std::nullopt;
        }

        item->checkout(memberId, member->getLoanDays());
        member->addBorrowedBook(item->getBarcode());

        auto record = loanManager.createLoan(
            memberId, item->getBarcode(), isbn, member->getLoanDays()
        );

        std::cout << "✅ " << member->getName() << " borrowed \""
                  << book->getTitle() << "\" | Barcode: "
                  << item->getBarcode() << " | Due: "
                  << formatDate(*item->getDueDate()) << "\n";

        return record;
    }

    // ── Returning ────────────────────────────────────────────────
    double returnBook(const std::string& barcode) {
        BookItem* item = catalogue.findByBarcode(barcode);
        if (!item) throw std::runtime_error("Barcode not found: " + barcode);

        std::string memberId = item->getBorrowedBy();
        Member* member = memberRegistry.findById(memberId);

        LoanRecord* loan = loanManager.findActiveLoanByBarcode(barcode);
        if (!loan) throw std::runtime_error("No active loan for barcode: " + barcode);

        double fine = loanManager.closeLoan(loan->loanId);
        item->returnItem();
        if (member) member->removeBorrowedBook(barcode);

        const Book* book = catalogue.findByISBN(item->getISBN());
        std::string title = book ? book->getTitle() : "Unknown";

        std::cout << "📥 Returned: \"" << title << "\" | Barcode: " << barcode;
        if (fine > 0)
            std::cout << " | Fine: $" << std::fixed << std::setprecision(2) << fine;
        std::cout << "\n";

        // Notify next person in reservation queue
        if (catalogue.hasReservations(item->getISBN()) && notifier) {
            auto nextMemberId = catalogue.popNextReservation(item->getISBN());
            if (nextMemberId) {
                notifier->onBookAvailable(*nextMemberId, title);
            }
        }

        return fine;
    }

    // ── Search ───────────────────────────────────────────────────
    void searchByTitle(const std::string& query) const {
        auto results = catalogue.searchByTitle(query);
        std::cout << "\n🔍 Search results for title \"" << query << "\":\n";
        if (results.empty()) { std::cout << "  No results found.\n"; return; }
        for (const auto* book : results) {
            std::cout << "  " << book->toString()
                      << " [Available: " << catalogue.getAvailableCount(book->getISBN())
                      << "/" << catalogue.getCopyCount(book->getISBN()) << "]\n";
        }
    }

    void searchByAuthor(const std::string& author) const {
        auto results = catalogue.searchByAuthor(author);
        std::cout << "\n🔍 Books by author \"" << author << "\":\n";
        for (const auto* book : results)
            std::cout << "  " << book->toString() << "\n";
    }

    void showMemberStatus(const std::string& memberId) const {
        Member* m = const_cast<Library*>(this)->memberRegistry.findById(memberId);
        if (!m) { std::cout << "Member not found\n"; return; }
        std::cout << "\n👤 " << m->toString() << "\n";
        auto loans = loanManager.getActiveLoansByMember(memberId);
        for (const auto* loan : loans)
            std::cout << "   Barcode: " << loan->barcode
                      << " | Due: " << formatDate(loan->dueDate) << "\n";
    }

    void showCatalogue() const { catalogue.printCatalogue(); }
};

// ═══════════════════════════════════════════════════════════════
// DEMO
// ═══════════════════════════════════════════════════════════════

int main() {
    std::cout << "════════ LIBRARY MANAGEMENT SYSTEM DEMO ════════\n\n";

    TieredFine      fineStrategy;
    ConsoleNotifier notifier;

    Library lib("City Central Library", fineStrategy,
                 std::make_unique<ConsoleNotifier>());

    // ── Add books ────────────────────────────────────────────────
    lib.addBookToCatalogue({ "978-0-13-110362-7", "The C Programming Language",
                              "Kernighan & Ritchie", "Programming", 1978 });
    lib.addBookToCatalogue({ "978-0-20-135043-0", "The Pragmatic Programmer",
                              "Hunt & Thomas", "Software Engineering", 1999 });
    lib.addBookToCatalogue({ "978-0-59-651798-1", "Clean Code",
                              "Robert C. Martin", "Software Engineering", 2008 });

    // Add copies
    lib.addCopy("978-0-13-110362-7");
    lib.addCopy("978-0-13-110362-7");  // 2 copies
    lib.addCopy("978-0-20-135043-0");  // 1 copy
    lib.addCopy("978-0-59-651798-1");

    lib.showCatalogue();

    // ── Register members ─────────────────────────────────────────
    auto studentId = lib.registerMember(
        std::make_unique<StudentMember>("MBR-001", "Alice Kumar", "alice@uni.edu"));
    auto facultyId = lib.registerMember(
        std::make_unique<FacultyMember>("MBR-002", "Dr. Bob Singh", "bob@uni.edu"));
    auto guestId   = lib.registerMember(
        std::make_unique<GuestMember>("MBR-003", "Carol Guest", "carol@email.com"));

    std::cout << "\n";

    // ── Borrow books ─────────────────────────────────────────────
    auto loan1 = lib.borrowBook("MBR-001", "978-0-13-110362-7");
    auto loan2 = lib.borrowBook("MBR-002", "978-0-13-110362-7");  // 2nd copy
    auto loan3 = lib.borrowBook("MBR-003", "978-0-20-135043-0");

    // This should queue a reservation (both copies of C book are out)
    lib.borrowBook("MBR-002", "978-0-13-110362-7");  // Queue reservation

    lib.showMemberStatus("MBR-001");
    lib.showMemberStatus("MBR-002");

    // ── Search ────────────────────────────────────────────────────
    lib.searchByTitle("clean");
    lib.searchByAuthor("martin");

    // ── Return books ──────────────────────────────────────────────
    std::cout << "\n";
    if (loan1) lib.returnBook(loan1->barcode);  // Triggers reservation notification
    if (loan3) lib.returnBook(loan3->barcode);

    lib.showCatalogue();

    return 0;
}
```

### 11.4 Design Decisions

```
Question: "Why separate Book from BookItem?"
Answer:   Book = metadata (one per ISBN). BookItem = physical copy (many per ISBN).
          This mirrors real-world libraries. Multiplicity: 1 Book → many BookItems.

Question: "How does adding a new member type (e.g., Premium) work?"
Answer:   Create class PremiumMember : public Member, override getBorrowLimit()
          and getLoanDays(). Zero changes to Library, LoanManager, or BookCatalogue.
          This is OCP at its best.

Question: "How are reservations handled?"
Answer:   BookCatalogue maintains a std::queue<string> per ISBN. On return,
          Library::returnBook() pops the front of the queue and notifies via
          INotificationObserver. Observer pattern decouples notification channel.

Question: "How would you make this production-ready?"
Answer:   - Replace in-memory maps with IBookRepository, IMemberRepository interfaces
          - Inject concrete DB implementations via DIP
          - Add transaction management for borrow/return atomicity
          - Replace ConsoleNotifier with EmailNotifier / SMSNotifier
          - Add audit logging via Decorator on LoanManager
```

---

# LLD Interview Cheat Sheet

```
╔═══════════════════════════════════════════════════════════════════════════╗
║                    LLD INTERVIEW CHEAT SHEET                              ║
╠════════════════════════════╦══════════════════════════════════════════════╣
║  SOLID                     ║  DESIGN PATTERNS (Most Common in LLD)        ║
║  ──────                    ║  ─────────────────────────────────────────── ║
║  S: One reason to change   ║  Creational:                                 ║
║  O: Extend, don't modify   ║    Singleton (Logger, Config)                ║
║  L: Subtypes substitutable ║    Factory (object creation)                 ║
║  I: Small interfaces       ║    Builder (complex object step-by-step)     ║
║  D: Depend on abstractions ║                                              ║
║                            ║  Structural:                                 ║
║  RELATIONSHIPS             ║    Adapter (incompatible interfaces)         ║
║  ─────────────             ║    Decorator (add behaviour dynamically)     ║
║  IS-A → Inheritance        ║    Facade (simplify complex subsystem)       ║
║  HAS-A strong → Composition║    Composite (tree structures)               ║
║  HAS-A weak → Aggregation  ║                                              ║
║  USES-A → Dependency       ║  Behavioural:                                ║
║                            ║    Observer (event-driven systems)           ║
║  LLD INTERVIEW STEPS       ║    Strategy (swappable algorithms)           ║
║  ──────────────────        ║    State (FSM — vending machine, game)       ║
║  1. Clarify requirements   ║    Command (undo/redo, queue)                ║
║  2. Identify entities      ║    Template Method (algorithm skeleton)      ║
║  3. Define relationships   ║    Chain of Responsibility (middleware)      ║
║  4. Apply patterns         ║                                              ║
║  5. Draw UML               ║  INTERVIEW TIPS                              ║
║  6. Write code             ║  ─────────────────────────────────────────── ║
║                            ║  • Start with interfaces, not classes        ║
║  KEY C++ TOOLS             ║  • Say "is-a" and "has-a" out loud          ║
║  ─────────                 ║  • Mention SOLID explicitly                  ║
║  virtual + override        ║  • Show extensibility: "to add X, just..."  ║
║  = 0 for pure virtual      ║  • Use smart pointers (unique_ptr)           ║
║  unique_ptr / shared_ptr   ║  • Handle edge cases: null, concurrent       ║
║  mutex for thread safety   ║  • Always write a working main() demo        ║
║  enum class                ║                                              ║
╚════════════════════════════╩══════════════════════════════════════════════╝
```

---

## Common LLD Interview Problems & Their Key Patterns

| Problem | Key Entities | Key Patterns |
|---|---|---|
| **Parking Lot** | Lot, Floor, Spot, Vehicle, Ticket | Strategy (fee), Builder, Factory |
| **Snake & Ladder** | Board, Player, Dice, Cell | State, Strategy (dice), Observer |
| **Library System** | Book, BookItem, Member, Loan | Observer, Strategy (fine), Template |
| **ATM Machine** | Card, Account, Transaction, Cash | State (idle/verifying/dispensing), Command |
| **Chess** | Board, Piece, Player, Move | Factory (pieces), Command (moves) |
| **Elevator System** | Elevator, Floor, Request, Scheduler | State, Strategy (scheduling) |
| **Hotel Booking** | Room, Guest, Booking, Payment | Factory, Observer, Strategy |
| **Ride Sharing (Uber)** | Trip, Driver, Rider, Pricing | Observer, Strategy (pricing), State (trip) |
| **Movie Ticket Booking** | Seat, Show, Booking, Payment | Singleton (seat lock), State |
| **Inventory System** | Item, Warehouse, Order, Supplier | Observer (restock), Command |

---

**Language**: C++17  
**Paradigm**: Object-Oriented Design  
**Licence**: MIT
