# Object-Oriented Programming in C++: From Concepts to a Complete Banking System

> A professional, beginner-to-advanced guide covering every OOP pillar in C++ through hands-on examples, culminating in a fully modular Banking System you can run, extend, and deploy.
---
## Table of Contents

- [Introduction](#introduction)
  - [Why OOP Matters](#why-oop-matters)
  - [Why Real-World Systems Use OOP](#why-real-world-systems-use-oop)
  - [What You Will Build](#what-you-will-build)

- [PHASE 1 — Learning OOP Concepts in C++](#phase-1--learning-oop-concepts-in-c)
  1. [Classes and Objects](#1-classes-and-objects)
  2. [Encapsulation](#2-encapsulation)
  3. [Constructors and Destructors](#3-constructors-and-destructors)
  4. [Inheritance](#4-inheritance)
  5. [Polymorphism](#5-polymorphism)
  6. [Abstraction](#6-abstraction)
  7. [Composition vs Inheritance](#7-composition-vs-inheritance)

- [PHASE 2 — Applying OOP to a Real Project](#phase-2--applying-oop-to-a-real-project)
  - [Project Overview: The Banking System](#project-overview-the-banking-system)
  - [System Architecture](#system-architecture)
  - [Module Responsibilities](#module-responsibilities)
  - [Implementation Roadmap](#implementation-steps)
    1. [Step 1 — Project Structure](#step-1--project-structure)
    2. [Step 2 — Designing Core Models](#step-2--designing-core-models)
    3. [Step 3 — Implement Account Operations](#step-3--implement-account-operations)
    4. [Step 4 — Transaction Service](#step-4--transaction-service)
    5. [Step 5 — Fraud Detection System](#step-5--fraud-detection-system)
    6. [Step 6 — Loan System](#step-6--loan-system)
    7. [Step 7 — Notification System](#step-7--notification-system)
    8. [Step 8 — Audit Logs](#step-8--audit-logs)

- [PHASE 3 — Complete Banking System Implementation](#phase-3--complete-banking-system-implementation)
  - [Source Code](#source-code)
    - Models
      - [`models/Customer.h`](#modelscustomerh)
      - [`models/Account.h`](#modelsaccounth)
      - [`models/SavingsAccount.h`](#modelssavingsaccounth)
      - [`models/CurrentAccount.h`](#modelscurrentaccounth)
    - Infrastructure
      - [`infrastructure/AuditLogs.h`](#infrastructureauditlogsh)
    - Security
      - [`security/FraudDetectionService.h`](#securityfrauddetectionserviceh)
    - Services
      - [`services/NotificationService.h`](#servicesnotificationserviceh)
      - [`services/TransactionService.h`](#servicestransactionserviceh)
      - [`services/LoanService.h`](#servicesloanserviceh)
      - [`services/AccountService.h`](#servicesaccountserviceh)
    - Entry Point
      - [`main.cpp`](#maincpp)
  - [Running the System](#running-the-system)
    - [How to Compile & Run](#how-to-compile--run)
    - [Example Output](#example-output)
  - [OOP Concepts Used in the Project](#key-oop-concepts-used-in-the-project)

- [PHASE 4 — Database Integration with SQLite](#phase-4--database-integration-with-sqlite)
  - [The Core Rule: Zero Changes to Existing Code](#the-core-rule-zero-changes-to-existing-code)
  - [How This Is Achieved](#how-this-is-achieved)
  - [Updated Project Structure](#updated-project-structure)
  - [Installation](#installation)
    - [Install SQLite3](#install-sqlite3)
    - [Verify Installation](#verify)
  - [Database Design](#database-design)
    - [Schema Design](#schema-design)
  - [Database Layer Implementation](#database-layer-implementation)
    - [`database/Database.h`](#databasedatabaseh)
    - [`database/CustomerRepo.h`](#databasecustomerrepoh)
    - [`database/AccountRepo.h`](#databaseaccountrepoh)
    - [`database/TransactionRepo.h`](#databasetransactionrepoh)
    - [`database/LoanRepo.h`](#databaseloanrepoh)
  - [Infrastructure Extension](#infrastructure-extension)
    - [`infrastructure/PersistentAuditLogs.h`](#infrastructurepersistentauditlogsh)
  - [Phase 4 Entry Point](#phase-4-entry-point)
    - [`main_db.cpp`](#main_dbcpp)
  - [Running the Database Version](#running-the-database-version)
    - [Build & Run](#build--run)
    - [Inspect the Database](#inspect-the-database)
  - [Architecture & Design](#architecture--design)
    - [OOP Patterns Introduced in Phase 4](#oop-patterns-introduced-in-phase-4)
    - [How to Migrate to PostgreSQL or MySQL](#how-to-migrate-to-postgresql-or-mysql)
  - [Future Improvements](#possible-future-improvements)

- [Conclusion](#conclusion)

---
## Introduction

**Object-Oriented Programming (OOP)** is a programming paradigm that organises software around *objects* — entities that bundle related data (attributes) and behaviour (methods) together. Instead of writing a series of procedural instructions, you model the world using classes that mirror real-world concepts.

### Why OOP Matters

| Concern | How OOP Helps |
|---|---|
| Complexity | Break large systems into small, self-contained classes |
| Reusability | Inherit and extend existing code without rewriting it |
| Maintainability | Change one class without rippling through the whole codebase |
| Collaboration | Teams can own separate classes/modules independently |
| Modelling | Code reads like the real domain — `Account`, `Customer`, `Transaction` |

### Why Real-World Systems Use OOP

Banks, hospitals, e-commerce platforms, and operating systems are too large for a single flat codebase. OOP lets architects decompose them into layers: **models**, **services**, **security**, and **infrastructure** — each a collection of well-defined classes.

### What You Will Build

By the end of this guide you will have built a **fully working Banking System** in C++ featuring:

- Customer and Account models with inheritance
- Deposit, withdrawal, and transfer operations
- A TransactionService that records every move
- A FraudDetectionService that flags suspicious activity
- A LoanService for processing loans
- A NotificationService that sends alerts
- An AuditLog that persists an immutable record of events
- **A full SQLite database layer (Phase 4) that persists everything without touching a single line of Phase 1–3 code**

All of it wired together in `main.cpp` and ready to compile with any standard C++20 compiler.

---

# PHASE 1 — Learning OOP Concepts in C++

---

## 1. Classes and Objects

### Explanation

A **class** is a blueprint — it defines what attributes (data) and methods (behaviour) an entity will have. An **object** is a concrete instance of that blueprint created at runtime.

Think of a class as an architectural drawing and an object as the actual building constructed from it.

### Real-World Analogy

> A `Car` class defines that every car has a `colour`, `brand`, and `speed`, and can `accelerate()` or `brake()`. Your specific red Toyota Corolla is one *object* of that class.

### C++ Example

```cpp
#include <iostream>
#include <string>

class Car {
public:
    // Attributes
    std::string brand;
    std::string colour;
    int speed;

    // Method
    void accelerate(int amount) {
        speed += amount;
        std::cout << brand << " accelerates to " << speed << " km/h\n";
    }
};

int main() {
    Car myCar;           // Object instantiation
    myCar.brand  = "Toyota";
    myCar.colour = "Red";
    myCar.speed  = 0;

    myCar.accelerate(60);   // Toyota accelerates to 60 km/h
    return 0;
}
```

### Key Takeaways

- A **class** is a type; an **object** is a variable of that type.
- Attributes store *state*; methods define *behaviour*.
- Multiple objects can be created from the same class, each with independent state.

---

## 2. Encapsulation

### Explanation

**Encapsulation** is the practice of hiding internal data and exposing only what is necessary through a controlled interface. It prevents external code from accidentally corrupting an object's state.

In C++ this is achieved via **access specifiers**:

| Specifier | Accessible From |
|---|---|
| `private` | Only inside the class |
| `protected` | Inside the class and its subclasses |
| `public` | Anywhere |

### Real-World Analogy

> An ATM machine encapsulates its cash vault. You interact only through the screen and keypad — you cannot directly reach into the vault.

### C++ Example

```cpp
#include <iostream>
#include <string>

class BankAccount {
private:
    double balance;          // Hidden from the outside world
    std::string owner;

public:
    // Constructor
    BankAccount(const std::string& ownerName, double initialBalance)
        : owner(ownerName), balance(initialBalance) {}

    // Getter
    double getBalance() const { return balance; }

    // Controlled mutator
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            std::cout << "Deposited: $" << amount << "\n";
        }
    }
};

int main() {
    BankAccount acc("Alice", 1000.0);
    acc.deposit(500.0);
    std::cout << "Balance: $" << acc.getBalance() << "\n";
    // acc.balance = -99999;  // ERROR — private!
    return 0;
}
```

### Key Takeaways

- Make attributes `private` by default.
- Expose behaviour through `public` methods.
- Getters and setters give you a chance to validate data before it changes state.

---

## 3. Constructors and Destructors

### Explanation

A **constructor** is a special method called automatically when an object is created. It initialises the object's state. A **destructor** is called when the object goes out of scope or is explicitly deleted — it releases resources.

### Real-World Analogy

> When you open a bank account (constructor), you fill in your details and make an initial deposit. When you close it (destructor), funds are returned and the record is archived.

### C++ Example

```cpp
#include <iostream>
#include <string>

class Account {
private:
    std::string id;
    double balance;

public:
    // Default constructor
    Account() : id("UNKNOWN"), balance(0.0) {
        std::cout << "Default Account created\n";
    }

    // Parameterised constructor
    Account(const std::string& accountId, double initialBalance)
        : id(accountId), balance(initialBalance) {
        std::cout << "Account " << id << " opened with $" << balance << "\n";
    }

    // Destructor
    ~Account() {
        std::cout << "Account " << id << " closed\n";
    }

    double getBalance() const { return balance; }
};

int main() {
    Account a1;                        // Default constructor
    Account a2("ACC-001", 2500.00);    // Parameterised constructor
    // Both destructors called automatically at end of scope
    return 0;
}
```

### Key Takeaways

- Always initialise members in the constructor to avoid undefined behaviour.
- Use **member initialiser lists** (`: id(accountId)`) over assignment inside the constructor body for efficiency.
- Destructors are essential when the class owns heap memory (`new`/`delete`) or file handles.

---

## 4. Inheritance

### Explanation

**Inheritance** allows a class (the *derived* class) to acquire the attributes and methods of another class (the *base* class). It models an **"is-a"** relationship and enables code reuse.

```
        Animal
       /      \
     Dog      Cat
```

### Real-World Analogy

> A `SavingsAccount` **is an** `Account`. It inherits all account behaviour (deposit, withdraw) and adds its own (interest calculation).

### C++ Example

```cpp
#include <iostream>
#include <string>

// Base class
class Animal {
protected:
    std::string name;

public:
    Animal(const std::string& n) : name(n) {}

    void breathe() {
        std::cout << name << " is breathing\n";
    }
};

// Derived class
class Dog : public Animal {
public:
    Dog(const std::string& n) : Animal(n) {}

    void bark() {
        std::cout << name << " says: Woof!\n";
    }
};

int main() {
    Dog d("Rex");
    d.breathe();   // Inherited from Animal
    d.bark();      // Dog's own method
    return 0;
}
```

### Key Takeaways

- Use `public` inheritance to preserve the base class interface.
- The derived class **extends** the base class — it adds or overrides behaviour.
- Prefer inheritance only for genuine "is-a" relationships; use composition otherwise.

---

## 5. Polymorphism

### Explanation

**Polymorphism** means "many forms." In C++ it comes in two flavours:

- **Compile-time (static)** — function overloading and templates resolved by the compiler.
- **Runtime (dynamic)** — virtual functions resolved at runtime via a vtable.

Runtime polymorphism is the most powerful: a base-class pointer can call the correct derived-class method without knowing the exact type.

### Real-World Analogy

> A bank employee processes "transactions" — it does not matter whether the transaction is a deposit, withdrawal, or transfer. The correct handling is determined by the actual transaction type at runtime.

### C++ Example

```cpp
#include <iostream>

class Shape {
public:
    virtual double area() const = 0;   // Pure virtual
    virtual void describe() const {
        std::cout << "Area = " << area() << "\n";
    }
    virtual ~Shape() = default;
};

class Circle : public Shape {
    double radius;
public:
    Circle(double r) : radius(r) {}
    double area() const override { return 3.14159 * radius * radius; }
};

class Rectangle : public Shape {
    double w, h;
public:
    Rectangle(double w, double h) : w(w), h(h) {}
    double area() const override { return w * h; }
};

int main() {
    Shape* shapes[] = { new Circle(5), new Rectangle(4, 6) };

    for (auto* s : shapes) {
        s->describe();   // Correct method called at runtime
        delete s;
    }
    return 0;
}
```

### Key Takeaways

- Declare methods `virtual` in the base class to enable runtime dispatch.
- Use `override` in derived classes to catch typos at compile time.
- Always declare destructors `virtual` in polymorphic base classes to avoid memory leaks.

---

## 6. Abstraction

### Explanation

**Abstraction** means exposing *what* an object does while hiding *how* it does it. In C++ this is formalised through **abstract classes** — classes that contain at least one **pure virtual function** (`= 0`) and cannot be instantiated directly.

### Real-World Analogy

> A payment interface says "you must implement `processPayment()`." It does not care whether the implementation is credit card, PayPal, or crypto.

### C++ Example

```cpp
#include <iostream>
#include <string>

// Abstract interface
class IPaymentProcessor {
public:
    virtual void processPayment(double amount) = 0;
    virtual std::string getProviderName() const = 0;
    virtual ~IPaymentProcessor() = default;
};

class CreditCardProcessor : public IPaymentProcessor {
public:
    void processPayment(double amount) override {
        std::cout << "Processing $" << amount << " via Credit Card\n";
    }
    std::string getProviderName() const override { return "Visa"; }
};

class PayPalProcessor : public IPaymentProcessor {
public:
    void processPayment(double amount) override {
        std::cout << "Processing $" << amount << " via PayPal\n";
    }
    std::string getProviderName() const override { return "PayPal"; }
};

void checkout(IPaymentProcessor& processor, double amount) {
    std::cout << "Provider: " << processor.getProviderName() << "\n";
    processor.processPayment(amount);
}

int main() {
    CreditCardProcessor cc;
    PayPalProcessor pp;

    checkout(cc, 149.99);
    checkout(pp, 49.00);
    return 0;
}
```

### Key Takeaways

- Abstract classes define a **contract** — derived classes must fulfil it.
- Pure virtual functions (`= 0`) force every subclass to provide an implementation.
- Code against **interfaces**, not concrete types, to keep systems flexible.

---

## 7. Composition vs Inheritance

### Explanation

Two fundamental ways to build complex classes:

| Relationship | Keyword | Use When |
|---|---|---|
| **Inheritance** | "is-a" | `Dog` is an `Animal` |
| **Composition** | "has-a" | `Car` has an `Engine` |

Composition is often preferred: it avoids tight coupling and lets you swap components independently.

### Real-World Analogy

> A `BankAccount` **has a** `Customer` (composition). A `SavingsAccount` **is an** `Account` (inheritance).

### C++ Example

```cpp
#include <iostream>
#include <string>

// Component
class Engine {
    int horsepower;
public:
    Engine(int hp) : horsepower(hp) {}
    void start() { std::cout << "Engine (" << horsepower << "hp) started\n"; }
};

// Composition: Car HAS-A Engine
class Car {
    std::string model;
    Engine engine;       // Composed object — not inherited
public:
    Car(const std::string& m, int hp) : model(m), engine(hp) {}
    void drive() {
        engine.start();
        std::cout << model << " is driving\n";
    }
};

int main() {
    Car tesla("Tesla Model S", 670);
    tesla.drive();
    return 0;
}
```

### Key Takeaways

- Prefer **composition** when the relationship is "has-a" or when you want runtime flexibility.
- Use **inheritance** for genuine taxonomic "is-a" relationships.
- The Gang of Four principle: *"Favour composition over inheritance."*

---

# PHASE 2 — Applying OOP to a Real Project

---

## Project Overview: The Banking System

Now that you understand every OOP pillar, we will apply them together to design a **modular, production-quality Banking System**. This mirrors the architecture used in real financial software: each responsibility lives in its own class or service, and every module communicates through clean interfaces.

### System Architecture

```
Bank System
 ├── models/
 │      ├── Customer          — stores personal information
 │      ├── Account           — abstract base for all account types
 │      ├── SavingsAccount    — earns interest; no overdraft
 │      └── CurrentAccount    — allows overdraft up to a limit
 │
 ├── services/
 │      ├── AccountService    — creates and retrieves accounts
 │      ├── TransactionService— records deposits, withdrawals, transfers
 │      ├── LoanService       — evaluates and issues loans
 │      └── NotificationService— sends email/SMS alerts
 │
 ├── security/
 │      └── FraudDetectionService — flags unusual activity
 │
 └── infrastructure/
        └── AuditLogs         — immutable log of every system event
```

### Module Responsibilities

| Module | Responsibility |
|---|---|
| `Customer` | Holds name, ID, contact info |
| `Account` | Abstract base with balance, ID, deposit/withdraw contract |
| `SavingsAccount` | Adds `applyInterest()` |
| `CurrentAccount` | Adds overdraft limit |
| `AccountService` | CRUD operations for accounts |
| `TransactionService` | Executes and records financial transactions |
| `LoanService` | Scores and approves loans |
| `NotificationService` | Sends event-driven alerts |
| `FraudDetectionService` | Runs heuristic rules against transactions |
| `AuditLogs` | Appends timestamped, read-only log entries |

---

## Step 1 — Project Structure

```
/bank-system
│
├── models/
│   ├── Customer.h
│   ├── Account.h
│   ├── SavingsAccount.h
│   └── CurrentAccount.h
│
├── services/
│   ├── AccountService.h
│   ├── TransactionService.h
│   ├── LoanService.h
│   └── NotificationService.h
│
├── security/
│   └── FraudDetectionService.h
│
├── infrastructure/
│   └── AuditLogs.h
│
└── main.cpp
```

### Why Modular Architecture?

- **Separation of concerns**: Each file does one job.
- **Testability**: You can unit-test `LoanService` without touching `NotificationService`.
- **Scalability**: New account types or services slot in without touching existing code.
- **Onboarding**: New team members navigate the project by folder, not by reading thousands of lines.

---

## Step 2 — Designing Core Models

### Design Decisions

1. `Account` is **abstract** — you cannot open a "generic" account; it must be Savings or Current.
2. `Customer` is a **value object** composed into `Account` (has-a relationship).
3. `SavingsAccount` and `CurrentAccount` **inherit** from `Account` and add specialised behaviour.

---

## Step 3 — Implement Account Operations

Each account type overrides `deposit()`, `withdraw()`, and adds its own rules:

- **SavingsAccount**: no overdraft; exposes `applyInterest()`.
- **CurrentAccount**: allows withdrawals beyond balance up to `overdraftLimit`.

---

## Step 4 — Transaction Service

The `TransactionService` acts as the **coordinator**. It:

1. Calls `deposit()` or `withdraw()` on the account.
2. Records the transaction in a history vector.
3. Triggers `FraudDetectionService`.
4. Sends a notification via `NotificationService`.
5. Writes to `AuditLogs`.

Separating this logic from the model keeps `Account` focused on state management only.

---

## Step 5 — Fraud Detection System

The `FraudDetectionService` scans each transaction against simple heuristics:

- Single transaction exceeds $10,000 → flag.
- More than 5 transactions in one minute → flag.
- Transaction at an unusual hour (midnight–4 am) → flag.

Real banks add ML models on top of these rules, but the architecture is identical.

---

## Step 6 — Loan System

`LoanService` evaluates a loan application by checking:

- Account balance as collateral proxy.
- Requested amount vs a configurable maximum.
- Returns approval with an interest rate.

---

## Step 7 — Notification System

`NotificationService` decouples the *event* (a transfer happened) from the *communication channel* (email, SMS). In this implementation it prints to console; swapping to a real email library requires only changing this one class.

---

## Step 8 — Audit Logs

Banks are legally required to retain immutable records. `AuditLogs` appends timestamped entries to an in-memory list and can dump them on demand. In production you would write to an append-only database table or a blockchain ledger.

---

# PHASE 3 — Complete Banking System Implementation

Below is the full, compilable source code. Copy each block into the corresponding file.

---

### `models/Customer.h`

```cpp
#pragma once
#include <string>

class Customer {
private:
    std::string customerId;
    std::string name;
    std::string email;
    std::string phone;

public:
    Customer() = default;

    Customer(const std::string& id,
             const std::string& name,
             const std::string& email,
             const std::string& phone)
        : customerId(id), name(name), email(email), phone(phone) {}

    // Getters
    std::string getCustomerId() const { return customerId; }
    std::string getName()       const { return name; }
    std::string getEmail()      const { return email; }
    std::string getPhone()      const { return phone; }

    std::string toString() const {
        return "[Customer " + customerId + "] " + name +
               " | " + email + " | " + phone;
    }
};
```

---

### `models/Account.h`

```cpp
#pragma once
#include <string>
#include <stdexcept>
#include "Customer.h"

// Abstract base class — cannot be instantiated directly
class Account {
protected:
    std::string accountId;
    double      balance;
    Customer    owner;
    std::string accountType;

public:
    Account(const std::string& id, double initialBalance, const Customer& customer)
        : accountId(id), balance(initialBalance), owner(customer) {}

    virtual ~Account() = default;

    // Pure virtual — every account type must implement these
    virtual void deposit(double amount)  = 0;
    virtual void withdraw(double amount) = 0;
    virtual std::string getAccountType() const = 0;

    // Concrete shared behaviour
    double      getBalance()   const { return balance; }
    std::string getAccountId() const { return accountId; }
    Customer    getOwner()     const { return owner; }

    virtual void transfer(double amount, Account& target) {
        withdraw(amount);
        target.deposit(amount);
    }

    virtual std::string toString() const {
        return "[" + getAccountType() + " " + accountId + "] " +
               owner.getName() + " | Balance: $" + std::to_string(balance);
    }
};
```

---

### `models/SavingsAccount.h`

```cpp
#pragma once
#include "Account.h"
#include <iostream>

class SavingsAccount : public Account {
private:
    double interestRate;   // Annual rate, e.g. 0.05 = 5 %

public:
    SavingsAccount(const std::string& id,
                   double initialBalance,
                   const Customer& customer,
                   double rate = 0.035)
        : Account(id, initialBalance, customer), interestRate(rate) {}

    std::string getAccountType() const override { return "SavingsAccount"; }

    void deposit(double amount) override {
        if (amount <= 0) throw std::invalid_argument("Deposit must be positive");
        balance += amount;
        std::cout << "[Savings] Deposited $" << amount
                  << " | New balance: $" << balance << "\n";
    }

    void withdraw(double amount) override {
        if (amount <= 0)      throw std::invalid_argument("Amount must be positive");
        if (amount > balance) throw std::runtime_error("Insufficient funds");
        balance -= amount;
        std::cout << "[Savings] Withdrew $" << amount
                  << " | New balance: $" << balance << "\n";
    }

    void applyInterest() {
        double interest = balance * interestRate;
        balance += interest;
        std::cout << "[Savings] Interest applied: $" << interest
                  << " | New balance: $" << balance << "\n";
    }

    double getInterestRate() const { return interestRate; }
};
```

---

### `models/CurrentAccount.h`

```cpp
#pragma once
#include "Account.h"
#include <iostream>

class CurrentAccount : public Account {
private:
    double overdraftLimit;

public:
    CurrentAccount(const std::string& id,
                   double initialBalance,
                   const Customer& customer,
                   double overdraft = 1000.0)
        : Account(id, initialBalance, customer), overdraftLimit(overdraft) {}

    std::string getAccountType() const override { return "CurrentAccount"; }

    void deposit(double amount) override {
        if (amount <= 0) throw std::invalid_argument("Deposit must be positive");
        balance += amount;
        std::cout << "[Current] Deposited $" << amount
                  << " | New balance: $" << balance << "\n";
    }

    void withdraw(double amount) override {
        if (amount <= 0) throw std::invalid_argument("Amount must be positive");
        if (amount > balance + overdraftLimit)
            throw std::runtime_error("Overdraft limit exceeded");
        balance -= amount;
        std::cout << "[Current] Withdrew $" << amount
                  << " | New balance: $" << balance << "\n";
    }

    double getOverdraftLimit() const { return overdraftLimit; }
};
```

---

### `infrastructure/AuditLogs.h`

```cpp
#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>

class AuditLogs {
private:
    struct LogEntry {
        std::string timestamp;
        std::string event;
    };

    std::vector<LogEntry> logs;

    static std::string currentTimestamp() {
        auto now  = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);
        std::string ts = std::ctime(&t);
        if (!ts.empty() && ts.back() == '\n') ts.pop_back();
        return ts;
    }

public:
    void log(const std::string& event) {
        logs.push_back({ currentTimestamp(), event });
    }

    void printAll() const {
        std::cout << "\n===== AUDIT LOG =====\n";
        for (const auto& entry : logs)
            std::cout << "[" << entry.timestamp << "] " << entry.event << "\n";
        std::cout << "=====================\n";
    }

    size_t count() const { return logs.size(); }
};
```

---

### `security/FraudDetectionService.h`

```cpp
#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <chrono>

struct TransactionRecord {
    std::string accountId;
    double      amount;
    std::string type;       // "DEPOSIT" | "WITHDRAWAL" | "TRANSFER"
    std::chrono::system_clock::time_point timestamp;
};

class FraudDetectionService {
private:
    double singleTransactionThreshold = 10000.0;
    int    rapidTransactionLimit      = 5;
    int    rapidTransactionWindowSecs = 60;

    std::vector<TransactionRecord> history;

    bool isRapidTransaction(const std::string& accountId) const {
        auto now = std::chrono::system_clock::now();
        int recentCount = 0;
        for (const auto& rec : history) {
            if (rec.accountId == accountId) {
                auto diffSecs = std::chrono::duration_cast<std::chrono::seconds>(
                    now - rec.timestamp).count();
                if (diffSecs <= rapidTransactionWindowSecs) ++recentCount;
            }
        }
        return recentCount >= rapidTransactionLimit;
    }

public:
    bool analyse(const TransactionRecord& txn) {
        bool flagged = false;

        if (txn.amount >= singleTransactionThreshold) {
            std::cout << "[FRAUD ALERT] Large transaction detected: $"
                      << txn.amount << " on account " << txn.accountId << "\n";
            flagged = true;
        }

        if (isRapidTransaction(txn.accountId)) {
            std::cout << "[FRAUD ALERT] Rapid transactions detected on account "
                      << txn.accountId << "\n";
            flagged = true;
        }

        history.push_back(txn);
        return flagged;
    }
};
```

---

### `services/NotificationService.h`

```cpp
#pragma once
#include <string>
#include <iostream>
#include "../models/Account.h"

class NotificationService {
public:
    void sendTransactionAlert(const Account& account,
                               const std::string& type,
                               double amount) {
        std::cout << "[NOTIFICATION] Email to " << account.getOwner().getEmail()
                  << " — " << type << " of $" << amount
                  << " on account " << account.getAccountId()
                  << " | New balance: $" << account.getBalance() << "\n";
    }

    void sendFraudAlert(const Account& account) {
        std::cout << "[FRAUD NOTIFICATION] SMS to " << account.getOwner().getPhone()
                  << " — Suspicious activity detected on account "
                  << account.getAccountId() << ". Please verify.\n";
    }

    void sendLoanDecision(const Customer& customer,
                          double amount,
                          bool approved,
                          double rate = 0.0) {
        if (approved)
            std::cout << "[LOAN NOTIFICATION] " << customer.getName()
                      << " — Loan of $" << amount
                      << " APPROVED at " << (rate * 100) << "% interest.\n";
        else
            std::cout << "[LOAN NOTIFICATION] " << customer.getName()
                      << " — Loan of $" << amount << " DECLINED.\n";
    }
};
```

---

### `services/TransactionService.h`

```cpp
#pragma once
#include <string>
#include <vector>
#include <chrono>
#include "../models/Account.h"
#include "../security/FraudDetectionService.h"
#include "NotificationService.h"
#include "../infrastructure/AuditLogs.h"

class TransactionService {
private:
    FraudDetectionService& fraudService;
    NotificationService&   notifService;
    AuditLogs&             auditLogs;

public:
    TransactionService(FraudDetectionService& fraud,
                       NotificationService& notif,
                       AuditLogs& audit)
        : fraudService(fraud), notifService(notif), auditLogs(audit) {}

    void deposit(Account& account, double amount) {
        account.deposit(amount);

        TransactionRecord txn{ account.getAccountId(), amount, "DEPOSIT",
                               std::chrono::system_clock::now() };
        bool flagged = fraudService.analyse(txn);

        notifService.sendTransactionAlert(account, "DEPOSIT", amount);
        if (flagged) notifService.sendFraudAlert(account);

        auditLogs.log("DEPOSIT $" + std::to_string(amount) +
                      " to " + account.getAccountId());
    }

    void withdraw(Account& account, double amount) {
        account.withdraw(amount);

        TransactionRecord txn{ account.getAccountId(), amount, "WITHDRAWAL",
                               std::chrono::system_clock::now() };
        bool flagged = fraudService.analyse(txn);

        notifService.sendTransactionAlert(account, "WITHDRAWAL", amount);
        if (flagged) notifService.sendFraudAlert(account);

        auditLogs.log("WITHDRAWAL $" + std::to_string(amount) +
                      " from " + account.getAccountId());
    }

    void transfer(Account& source, Account& target, double amount) {
        source.transfer(amount, target);

        TransactionRecord txn{ source.getAccountId(), amount, "TRANSFER",
                               std::chrono::system_clock::now() };
        bool flagged = fraudService.analyse(txn);

        notifService.sendTransactionAlert(source, "TRANSFER OUT", amount);
        notifService.sendTransactionAlert(target, "TRANSFER IN",  amount);
        if (flagged) notifService.sendFraudAlert(source);

        auditLogs.log("TRANSFER $" + std::to_string(amount) +
                      " from " + source.getAccountId() +
                      " to "   + target.getAccountId());
    }
};
```

---

### `services/LoanService.h`

```cpp
#pragma once
#include <iostream>
#include <string>
#include "../models/Account.h"
#include "NotificationService.h"
#include "../infrastructure/AuditLogs.h"

struct LoanApplication {
    std::string applicationId;
    Customer    applicant;
    double      requestedAmount;
    int         termMonths;
};

class LoanService {
private:
    double maxLoanMultiplier = 5.0;   // Max loan = 5× balance
    double baseInterestRate  = 0.07;  // 7 %

    NotificationService& notifService;
    AuditLogs&           auditLogs;

public:
    LoanService(NotificationService& notif, AuditLogs& audit)
        : notifService(notif), auditLogs(audit) {}

    void processLoan(const LoanApplication& app, Account& account) {
        double maxAllowed = account.getBalance() * maxLoanMultiplier;
        bool   approved   = (app.requestedAmount <= maxAllowed);

        std::cout << "\n--- Loan Application: " << app.applicationId << " ---\n";
        std::cout << "Applicant      : " << app.applicant.getName() << "\n";
        std::cout << "Requested      : $" << app.requestedAmount << "\n";
        std::cout << "Max Eligible   : $" << maxAllowed << "\n";
        std::cout << "Decision       : " << (approved ? "APPROVED" : "DECLINED") << "\n";

        if (approved) {
            account.deposit(app.requestedAmount);
            std::cout << "Loan disbursed to account " << account.getAccountId() << "\n";
        }

        notifService.sendLoanDecision(app.applicant, app.requestedAmount,
                                      approved, baseInterestRate);
        auditLogs.log("LOAN " + std::string(approved ? "APPROVED" : "DECLINED") +
                      " $" + std::to_string(app.requestedAmount) +
                      " for " + app.applicant.getName());
    }
};
```

---

### `services/AccountService.h`

```cpp
#pragma once
#include <vector>
#include <memory>
#include <string>
#include <stdexcept>
#include <iostream>
#include "../models/Account.h"
#include "../models/SavingsAccount.h"
#include "../models/CurrentAccount.h"
#include "../infrastructure/AuditLogs.h"

class AccountService {
private:
    std::vector<std::shared_ptr<Account>> accounts;
    AuditLogs& auditLogs;
    int nextId = 1000;

    std::string generateId(const std::string& prefix) {
        return prefix + std::to_string(++nextId);
    }

public:
    explicit AccountService(AuditLogs& audit) : auditLogs(audit) {}

    std::shared_ptr<SavingsAccount>
    openSavingsAccount(const Customer& customer, double initialDeposit) {
        std::string id  = generateId("SAV-");
        auto account    = std::make_shared<SavingsAccount>(id, initialDeposit, customer);
        accounts.push_back(account);
        auditLogs.log("OPENED SavingsAccount " + id +
                      " for " + customer.getName());
        std::cout << "[AccountService] Opened: " << account->toString() << "\n";
        return account;
    }

    std::shared_ptr<CurrentAccount>
    openCurrentAccount(const Customer& customer,
                       double initialDeposit,
                       double overdraft = 1000.0) {
        std::string id  = generateId("CUR-");
        auto account    = std::make_shared<CurrentAccount>(id, initialDeposit,
                                                           customer, overdraft);
        accounts.push_back(account);
        auditLogs.log("OPENED CurrentAccount " + id +
                      " for " + customer.getName());
        std::cout << "[AccountService] Opened: " << account->toString() << "\n";
        return account;
    }

    std::shared_ptr<Account> findById(const std::string& id) const {
        for (const auto& acc : accounts)
            if (acc->getAccountId() == id) return acc;
        throw std::runtime_error("Account not found: " + id);
    }

    void listAll() const {
        std::cout << "\n===== All Accounts =====\n";
        for (const auto& acc : accounts)
            std::cout << acc->toString() << "\n";
        std::cout << "========================\n";
    }
};
```

---

### `main.cpp`

```cpp
#include <iostream>
#include <memory>

#include "models/Customer.h"
#include "models/SavingsAccount.h"
#include "models/CurrentAccount.h"
#include "services/AccountService.h"
#include "services/TransactionService.h"
#include "services/LoanService.h"
#include "services/NotificationService.h"
#include "security/FraudDetectionService.h"
#include "infrastructure/AuditLogs.h"

int main() {
    std::cout << "============================================\n";
    std::cout << "       C++ Banking System — Demo            \n";
    std::cout << "============================================\n\n";

    // ── Infrastructure ──────────────────────────────────────────
    AuditLogs            auditLogs;

    // ── Services ────────────────────────────────────────────────
    NotificationService  notifService;
    FraudDetectionService fraudService;
    TransactionService   txnService(fraudService, notifService, auditLogs);
    AccountService       accountService(auditLogs);
    LoanService          loanService(notifService, auditLogs);

    // ── Customers ───────────────────────────────────────────────
    Customer alice("C001", "Alice Johnson", "alice@bank.com", "+1-555-0101");
    Customer bob  ("C002", "Bob Smith",     "bob@bank.com",   "+1-555-0202");

    std::cout << "\n--- Creating Customers ---\n";
    std::cout << alice.toString() << "\n";
    std::cout << bob.toString()   << "\n";

    // ── Open Accounts ────────────────────────────────────────────
    std::cout << "\n--- Opening Accounts ---\n";
    auto aliceSavings  = accountService.openSavingsAccount(alice, 5000.00);
    auto aliceCurrent  = accountService.openCurrentAccount(alice, 2000.00, 1500.00);
    auto bobSavings    = accountService.openSavingsAccount(bob,   3000.00);

    accountService.listAll();

    // ── Deposits ─────────────────────────────────────────────────
    std::cout << "\n--- Deposits ---\n";
    txnService.deposit(*aliceSavings, 1200.00);
    txnService.deposit(*bobSavings,   800.00);

    // ── Withdrawal ───────────────────────────────────────────────
    std::cout << "\n--- Withdrawal ---\n";
    txnService.withdraw(*aliceSavings, 300.00);

    // ── Transfer ─────────────────────────────────────────────────
    std::cout << "\n--- Transfer Alice → Bob ---\n";
    txnService.transfer(*aliceSavings, *bobSavings, 500.00);

    // ── Apply Savings Interest ────────────────────────────────────
    std::cout << "\n--- Applying Interest ---\n";
    aliceSavings->applyInterest();

    // ── Large Transaction (Fraud Trigger) ─────────────────────────
    std::cout << "\n--- Large Deposit (Fraud Detection Test) ---\n";
    txnService.deposit(*aliceCurrent, 15000.00);

    // ── Loan Processing ───────────────────────────────────────────
    LoanApplication loanApp{
        "LOAN-2024-001",
        alice,
        10000.00,
        36
    };
    loanService.processLoan(loanApp, *aliceSavings);

    // ── Overdraft Test ────────────────────────────────────────────
    std::cout << "\n--- Overdraft Test (CurrentAccount) ---\n";
    try {
        txnService.withdraw(*aliceCurrent, 20000.00);   // Should throw
    } catch (const std::runtime_error& e) {
        std::cout << "[CAUGHT] " << e.what() << "\n";
    }

    // ── Final Balances ────────────────────────────────────────────
    std::cout << "\n--- Final Account Balances ---\n";
    accountService.listAll();

    // ── Audit Log ─────────────────────────────────────────────────
    auditLogs.printAll();

    return 0;
}
```

---

### How to Compile & Run

```bash
# From the /bank-system directory
g++ -std=c++20 -Wall -Wextra -o bank_system main.cpp
./bank_system
```

---

# Example Output

```
============================================
       C++ Banking System — Demo
============================================

--- Creating Customers ---
[Customer C001] Alice Johnson | alice@bank.com | +1-555-0101
[Customer C002] Bob Smith | bob@bank.com | +1-555-0202

--- Opening Accounts ---
[AccountService] Opened: [SavingsAccount SAV-1001] Alice Johnson | Balance: $5000.000000
[AccountService] Opened: [CurrentAccount CUR-1002] Alice Johnson | Balance: $2000.000000
[AccountService] Opened: [SavingsAccount SAV-1003] Bob Smith | Balance: $3000.000000

===== All Accounts =====
[SavingsAccount SAV-1001] Alice Johnson | Balance: $5000.000000
[CurrentAccount CUR-1002] Alice Johnson | Balance: $2000.000000
[SavingsAccount SAV-1003] Bob Smith | Balance: $3000.000000
========================

--- Deposits ---
[Savings] Deposited $1200 | New balance: $6200
[NOTIFICATION] Email to alice@bank.com — DEPOSIT of $1200 on account SAV-1001 | New balance: $6200
...

===== AUDIT LOG =====
[Tue Mar 10 12:00:01 2026] OPENED SavingsAccount SAV-1001 for Alice Johnson
[Tue Mar 10 12:00:01 2026] DEPOSIT $1200.000000 to SAV-1001
...
=====================
```

---

# Key OOP Concepts Used in the Project

| Concept | Where Applied |
|---|---|
| **Encapsulation** | `Account`, `Customer`: all attributes are `private`; state is changed only through validated methods. |
| **Inheritance** | `SavingsAccount` and `CurrentAccount` inherit from `Account`, reusing `balance`, `transfer()`, and `toString()`. |
| **Polymorphism** | `TransactionService` accepts `Account&` references — it calls `deposit()` and `withdraw()` without knowing the concrete type. |
| **Abstraction** | `Account` is an abstract class with pure virtual `deposit()`, `withdraw()`, and `getAccountType()`. No "bare" account can be created. |
| **Composition** | `Account` **has-a** `Customer`. `TransactionService` **has-a** `FraudDetectionService`, `NotificationService`, and `AuditLogs`. |

---

# PHASE 4 — Database Integration with SQLite

---

## The Core Rule: Zero Changes to Existing Code

Phase 4 adds a complete persistence layer without touching a **single line** from Phases 1–3. Every `.h` file in `models/`, `services/`, `security/`, and `infrastructure/` stays exactly as written. The database layer is **purely additive**.

This is real-world engineering discipline: when you add persistence to a production codebase, you do not rewrite the domain — you wrap it.

### How This Is Achieved

The strategy has three parts:

1. **Repository classes** sit beside the existing services and handle all SQL. They accept the same domain objects (`Account&`, `Customer&`) the services already use.
2. **`PersistentAuditLogs`** subclasses `AuditLogs` using inheritance — it overrides `log()` to write to the database *and* call the parent's in-memory log. The rest of the codebase never notices.
3. **`main_db.cpp`** is a new entry point that initialises the database, then uses the exact same service constructors as `main.cpp`. After each service call it asks the repository to persist the updated state.

```
Phase 3 code                     Phase 4 additions
─────────────────────────────    ──────────────────────────────────────
models/       ← untouched        database/Database.h
services/     ← untouched        database/CustomerRepo.h
security/     ← untouched        database/AccountRepo.h
infrastructure/AuditLogs.h       database/TransactionRepo.h
              ← untouched        database/LoanRepo.h
main.cpp      ← untouched        infrastructure/PersistentAuditLogs.h
                                 main_db.cpp   ← new entry point
```

---

## Updated Project Structure

```
/bank-system
│
├── models/                        ← Phase 3 — UNCHANGED
│   ├── Customer.h
│   ├── Account.h
│   ├── SavingsAccount.h
│   └── CurrentAccount.h
│
├── services/                      ← Phase 3 — UNCHANGED
│   ├── AccountService.h
│   ├── TransactionService.h
│   ├── LoanService.h
│   └── NotificationService.h
│
├── security/                      ← Phase 3 — UNCHANGED
│   └── FraudDetectionService.h
│
├── infrastructure/
│   ├── AuditLogs.h                ← Phase 3 — UNCHANGED
│   └── PersistentAuditLogs.h      ← Phase 4 — NEW (subclass only)
│
├── database/                      ← Phase 4 — NEW
│   ├── Database.h
│   ├── CustomerRepo.h
│   ├── AccountRepo.h
│   ├── TransactionRepo.h
│   └── LoanRepo.h
│
├── main.cpp                       ← Phase 3 — UNCHANGED
└── main_db.cpp                    ← Phase 4 — NEW entry point
```

---

## Installation

### Install SQLite3

**Ubuntu / Debian**
```bash
sudo apt-get update && sudo apt-get install -y libsqlite3-dev
```

**macOS (Homebrew)**
```bash
brew install sqlite3
```

**Windows (vcpkg)**
```bash
vcpkg install sqlite3:x64-windows
```

### Verify
```bash
sqlite3 --version
# 3.x.x 20xx-xx-xx ...
```

---

## Schema Design

Before writing C++, define the tables. The schema maps directly to the domain objects in Phase 3.

```sql
-- Stores Customer value objects
CREATE TABLE IF NOT EXISTS customers (
    customer_id TEXT PRIMARY KEY,
    name        TEXT NOT NULL,
    email       TEXT NOT NULL UNIQUE,
    phone       TEXT NOT NULL
);

-- Stores both SavingsAccount and CurrentAccount rows.
-- account_type drives which columns are meaningful.
-- interest_rate / overdraft_limit are NULL for the irrelevant type.
CREATE TABLE IF NOT EXISTS accounts (
    account_id      TEXT PRIMARY KEY,
    account_type    TEXT NOT NULL,     -- 'SavingsAccount' | 'CurrentAccount'
    balance         REAL NOT NULL,
    customer_id     TEXT NOT NULL,
    interest_rate   REAL,              -- SavingsAccount only
    overdraft_limit REAL,              -- CurrentAccount only
    FOREIGN KEY (customer_id) REFERENCES customers(customer_id)
);

-- Immutable record of every deposit / withdrawal / transfer
CREATE TABLE IF NOT EXISTS transactions (
    id              INTEGER PRIMARY KEY AUTOINCREMENT,
    account_id      TEXT NOT NULL,
    type            TEXT NOT NULL,     -- 'DEPOSIT' | 'WITHDRAWAL' | 'TRANSFER'
    amount          REAL NOT NULL,
    target_account  TEXT,              -- NULL unless TRANSFER
    flagged         INTEGER NOT NULL DEFAULT 0,
    created_at      TEXT NOT NULL DEFAULT (datetime('now')),
    FOREIGN KEY (account_id) REFERENCES accounts(account_id)
);

-- Loan application and decision record
CREATE TABLE IF NOT EXISTS loans (
    application_id  TEXT PRIMARY KEY,
    customer_id     TEXT NOT NULL,
    amount          REAL NOT NULL,
    term_months     INTEGER NOT NULL,
    approved        INTEGER NOT NULL,  -- 1 = approved, 0 = declined
    interest_rate   REAL,
    created_at      TEXT NOT NULL DEFAULT (datetime('now')),
    FOREIGN KEY (customer_id) REFERENCES customers(customer_id)
);

-- Mirrors every AuditLogs::log() call — append-only
CREATE TABLE IF NOT EXISTS audit_log (
    id         INTEGER PRIMARY KEY AUTOINCREMENT,
    event      TEXT NOT NULL,
    created_at TEXT NOT NULL DEFAULT (datetime('now'))
);
```

**Key design decisions:**

| Decision | Reason |
|---|---|
| Single `accounts` table for both types | Matches the single `Account` base class; avoids joins for simple reads |
| `AUTOINCREMENT` on `transactions` and `audit_log` | These are append-only; business IDs are not needed |
| `FOREIGN KEY` constraints | Database enforces referential integrity that mirrors C++ object ownership |
| `flagged` column on transactions | Allows forensic queries like "show all flagged deposits" without re-running fraud rules |

---

## `database/Database.h`

The `Database` singleton owns the `sqlite3*` connection, initialises the schema, and exposes helpers used by every repository.

```cpp
#pragma once
#include <string>
#include <iostream>
#include <stdexcept>
#include <sqlite3.h>

// ─────────────────────────────────────────────────────────────
//  Database — Singleton that owns the SQLite connection.
//  All repositories obtain the raw handle via getHandle().
// ─────────────────────────────────────────────────────────────
class Database {
private:
    sqlite3*    handle = nullptr;
    std::string path;

    Database() = default;

    // Execute a statement that returns no rows (CREATE, INSERT, UPDATE, DELETE)
    void exec(const std::string& sql) const {
        char* errMsg = nullptr;
        if (sqlite3_exec(handle, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
            std::string msg = errMsg ? errMsg : "unknown";
            sqlite3_free(errMsg);
            throw std::runtime_error("[Database] SQL error: " + msg);
        }
    }

    void createSchema() const {
        exec("PRAGMA foreign_keys = ON;");

        exec(R"(
            CREATE TABLE IF NOT EXISTS customers (
                customer_id TEXT PRIMARY KEY,
                name        TEXT NOT NULL,
                email       TEXT NOT NULL UNIQUE,
                phone       TEXT NOT NULL
            );
        )");

        exec(R"(
            CREATE TABLE IF NOT EXISTS accounts (
                account_id      TEXT PRIMARY KEY,
                account_type    TEXT NOT NULL,
                balance         REAL NOT NULL,
                customer_id     TEXT NOT NULL,
                interest_rate   REAL,
                overdraft_limit REAL,
                FOREIGN KEY (customer_id) REFERENCES customers(customer_id)
            );
        )");

        exec(R"(
            CREATE TABLE IF NOT EXISTS transactions (
                id             INTEGER PRIMARY KEY AUTOINCREMENT,
                account_id     TEXT    NOT NULL,
                type           TEXT    NOT NULL,
                amount         REAL    NOT NULL,
                target_account TEXT,
                flagged        INTEGER NOT NULL DEFAULT 0,
                created_at     TEXT    NOT NULL DEFAULT (datetime('now')),
                FOREIGN KEY (account_id) REFERENCES accounts(account_id)
            );
        )");

        exec(R"(
            CREATE TABLE IF NOT EXISTS loans (
                application_id TEXT    PRIMARY KEY,
                customer_id    TEXT    NOT NULL,
                amount         REAL    NOT NULL,
                term_months    INTEGER NOT NULL,
                approved       INTEGER NOT NULL,
                interest_rate  REAL,
                created_at     TEXT    NOT NULL DEFAULT (datetime('now')),
                FOREIGN KEY (customer_id) REFERENCES customers(customer_id)
            );
        )");

        exec(R"(
            CREATE TABLE IF NOT EXISTS audit_log (
                id         INTEGER PRIMARY KEY AUTOINCREMENT,
                event      TEXT NOT NULL,
                created_at TEXT NOT NULL DEFAULT (datetime('now'))
            );
        )");
    }

public:
    // ── Singleton access ────────────────────────────────────────
    static Database& get() {
        static Database instance;
        return instance;
    }

    Database(const Database&)            = delete;
    Database& operator=(const Database&) = delete;

    // ── Lifecycle ───────────────────────────────────────────────
    void open(const std::string& filePath = "bank.db") {
        path = filePath;
        if (sqlite3_open(filePath.c_str(), &handle) != SQLITE_OK)
            throw std::runtime_error("[Database] Cannot open: " +
                                     std::string(sqlite3_errmsg(handle)));
        std::cout << "[Database] Connected → " << filePath << "\n";
        createSchema();
        std::cout << "[Database] Schema ready.\n";
    }

    void close() {
        if (handle) {
            sqlite3_close(handle);
            handle = nullptr;
            std::cout << "[Database] Connection closed.\n";
        }
    }

    ~Database() { close(); }

    // ── Raw handle for repositories ─────────────────────────────
    sqlite3* getHandle() const {
        if (!handle) throw std::runtime_error("[Database] Not open.");
        return handle;
    }

    // ── Atomic transaction helpers ───────────────────────────────
    void begin()    const { exec("BEGIN;");    }
    void commit()   const { exec("COMMIT;");   }
    void rollback() const { exec("ROLLBACK;"); }

    // ── Utility: prepare a statement safely ─────────────────────
    sqlite3_stmt* prepare(const std::string& sql) const {
        sqlite3_stmt* stmt = nullptr;
        if (sqlite3_prepare_v2(handle, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
            throw std::runtime_error("[Database] Prepare failed: " +
                                     std::string(sqlite3_errmsg(handle)));
        return stmt;   // caller must sqlite3_finalize(stmt)
    }
};
```

---

## `database/CustomerRepo.h`

Persists and loads `Customer` objects. Notice the methods accept the exact same `Customer` type defined in Phase 3 — no changes to the model.

```cpp
#pragma once
#include <vector>
#include <optional>
#include <sqlite3.h>
#include "../models/Customer.h"
#include "Database.h"

// ─────────────────────────────────────────────────────────────
//  CustomerRepo
//  All methods accept / return the Phase-3 Customer type.
// ─────────────────────────────────────────────────────────────
class CustomerRepo {
    sqlite3* db() const { return Database::get().getHandle(); }

public:
    // INSERT OR IGNORE — safe to call even if customer already exists
    void save(const Customer& c) const {
        const char* sql =
            "INSERT OR IGNORE INTO customers (customer_id, name, email, phone) "
            "VALUES (?, ?, ?, ?);";

        sqlite3_stmt* stmt = Database::get().prepare(sql);
        sqlite3_bind_text(stmt, 1, c.getCustomerId().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, c.getName().c_str(),       -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, c.getEmail().c_str(),      -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 4, c.getPhone().c_str(),      -1, SQLITE_TRANSIENT);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }

    // Returns std::nullopt if not found
    std::optional<Customer> findById(const std::string& customerId) const {
        const char* sql =
            "SELECT customer_id, name, email, phone "
            "FROM customers WHERE customer_id = ?;";

        sqlite3_stmt* stmt = Database::get().prepare(sql);
        sqlite3_bind_text(stmt, 1, customerId.c_str(), -1, SQLITE_TRANSIENT);

        std::optional<Customer> result;
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            result = Customer(
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3))
            );
        }
        sqlite3_finalize(stmt);
        return result;
    }

    std::vector<Customer> findAll() const {
        const char* sql =
            "SELECT customer_id, name, email, phone FROM customers;";

        sqlite3_stmt* stmt = Database::get().prepare(sql);

        std::vector<Customer> results;
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            results.emplace_back(
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3))
            );
        }
        sqlite3_finalize(stmt);
        return results;
    }
};
```

---

## `database/AccountRepo.h`

The most interesting repository: it uses `dynamic_cast` to detect the concrete type when saving, and reconstructs the correct subclass (polymorphically) when loading — the same pattern used in Phase 3's virtual dispatch.

```cpp
#pragma once
#include <vector>
#include <memory>
#include <sqlite3.h>
#include "../models/Account.h"
#include "../models/SavingsAccount.h"
#include "../models/CurrentAccount.h"
#include "Database.h"

// ─────────────────────────────────────────────────────────────
//  AccountRepo
//  Saves any Account* subclass; rehydrates into the correct
//  concrete type on load — polymorphism meets persistence.
// ─────────────────────────────────────────────────────────────
class AccountRepo {
    sqlite3* db() const { return Database::get().getHandle(); }

public:
    // INSERT OR IGNORE — detects subtype via dynamic_cast
    void save(const Account& acc) const {
        const char* sql =
            "INSERT OR IGNORE INTO accounts "
            "(account_id, account_type, balance, customer_id, "
            " interest_rate, overdraft_limit) "
            "VALUES (?, ?, ?, ?, ?, ?);";

        sqlite3_stmt* stmt = Database::get().prepare(sql);

        // Type-specific fields
        double interestRate   = -1.0;   // sentinel = NULL
        double overdraftLimit = -1.0;

        if (const auto* sav = dynamic_cast<const SavingsAccount*>(&acc))
            interestRate = sav->getInterestRate();
        else if (const auto* cur = dynamic_cast<const CurrentAccount*>(&acc))
            overdraftLimit = cur->getOverdraftLimit();

        sqlite3_bind_text  (stmt, 1, acc.getAccountId().c_str(),             -1, SQLITE_TRANSIENT);
        sqlite3_bind_text  (stmt, 2, acc.getAccountType().c_str(),           -1, SQLITE_TRANSIENT);
        sqlite3_bind_double(stmt, 3, acc.getBalance());
        sqlite3_bind_text  (stmt, 4, acc.getOwner().getCustomerId().c_str(), -1, SQLITE_TRANSIENT);

        // Bind NULL when the field does not apply to this subtype
        if (interestRate   >= 0) sqlite3_bind_double(stmt, 5, interestRate);
        else                     sqlite3_bind_null  (stmt, 5);
        if (overdraftLimit >= 0) sqlite3_bind_double(stmt, 6, overdraftLimit);
        else                     sqlite3_bind_null  (stmt, 6);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }

    // UPDATE balance after every transaction — keeps DB in sync with in-memory object
    void updateBalance(const Account& acc) const {
        const char* sql =
            "UPDATE accounts SET balance = ? WHERE account_id = ?;";

        sqlite3_stmt* stmt = Database::get().prepare(sql);
        sqlite3_bind_double(stmt, 1, acc.getBalance());
        sqlite3_bind_text  (stmt, 2, acc.getAccountId().c_str(), -1, SQLITE_TRANSIENT);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }

    // Load all accounts, rehydrating each into the correct concrete subclass.
    // Requires a customer lookup to reconstruct the Customer value object.
    std::vector<std::shared_ptr<Account>>
    findAll(const std::vector<Customer>& customers) const {
        const char* sql =
            "SELECT account_id, account_type, balance, customer_id, "
            "       interest_rate, overdraft_limit "
            "FROM accounts;";

        sqlite3_stmt* stmt = Database::get().prepare(sql);

        // Build a quick lookup map from the supplied customer list
        std::unordered_map<std::string, Customer> custMap;
        for (const auto& c : customers) custMap[c.getCustomerId()] = c;

        std::vector<std::shared_ptr<Account>> results;

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string accountId   = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            std::string accountType = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            double      balance     = sqlite3_column_double(stmt, 2);
            std::string customerId  = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));

            // Resolve the owner
            Customer owner;
            auto it = custMap.find(customerId);
            if (it != custMap.end()) owner = it->second;

            std::shared_ptr<Account> acc;

            if (accountType == "SavingsAccount") {
                double rate = (sqlite3_column_type(stmt, 4) != SQLITE_NULL)
                              ? sqlite3_column_double(stmt, 4)
                              : 0.035;
                acc = std::make_shared<SavingsAccount>(accountId, balance, owner, rate);

            } else if (accountType == "CurrentAccount") {
                double limit = (sqlite3_column_type(stmt, 5) != SQLITE_NULL)
                               ? sqlite3_column_double(stmt, 5)
                               : 1000.0;
                acc = std::make_shared<CurrentAccount>(accountId, balance, owner, limit);
            }

            if (acc) results.push_back(std::move(acc));
        }

        sqlite3_finalize(stmt);
        return results;
    }
};
```

> **Why `dynamic_cast` in `save()`?**
> The repository receives an `Account&` (the base type), but needs to store subtype-specific fields. Rather than adding virtual `serialize()` methods to the models (which would require changing Phase 3 code), `dynamic_cast` lets the repository detect the concrete type externally. This preserves the zero-changes rule.

---

## `database/TransactionRepo.h`

Records every `TransactionRecord` from `FraudDetectionService` (the same struct defined in Phase 3) into the `transactions` table.

```cpp
#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sqlite3.h>
#include "../security/FraudDetectionService.h"   // reuses Phase-3 TransactionRecord
#include "Database.h"

// ─────────────────────────────────────────────────────────────
//  TransactionRepo
//  Reuses the TransactionRecord struct from FraudDetectionService
//  so no new data types are introduced.
// ─────────────────────────────────────────────────────────────
class TransactionRepo {
    sqlite3* db() const { return Database::get().getHandle(); }

public:
    // Save a TransactionRecord (Phase-3 struct) with an optional transfer target
    // and the fraud flag returned by FraudDetectionService::analyse()
    void save(const TransactionRecord& txn,
              bool flagged,
              const std::string& targetAccountId = "") const {

        const char* sql =
            "INSERT INTO transactions "
            "(account_id, type, amount, target_account, flagged) "
            "VALUES (?, ?, ?, ?, ?);";

        sqlite3_stmt* stmt = Database::get().prepare(sql);
        sqlite3_bind_text   (stmt, 1, txn.accountId.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text   (stmt, 2, txn.type.c_str(),      -1, SQLITE_TRANSIENT);
        sqlite3_bind_double (stmt, 3, txn.amount);

        if (targetAccountId.empty()) sqlite3_bind_null(stmt, 4);
        else sqlite3_bind_text(stmt, 4, targetAccountId.c_str(), -1, SQLITE_TRANSIENT);

        sqlite3_bind_int(stmt, 5, flagged ? 1 : 0);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }

    // Retrieve full history for one account, newest first
    void printHistory(const std::string& accountId) const {
        const char* sql =
            "SELECT type, amount, target_account, flagged, created_at "
            "FROM transactions "
            "WHERE account_id = ? "
            "ORDER BY id DESC;";

        sqlite3_stmt* stmt = Database::get().prepare(sql);
        sqlite3_bind_text(stmt, 1, accountId.c_str(), -1, SQLITE_TRANSIENT);

        std::cout << "\n===== Transaction History: " << accountId << " =====\n";
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string type      = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            double      amount    = sqlite3_column_double(stmt, 1);
            bool        flagged   = sqlite3_column_int(stmt, 3) == 1;
            std::string createdAt = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            std::string target    = (sqlite3_column_type(stmt, 2) != SQLITE_NULL)
                                    ? reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2))
                                    : "";

            std::cout << "[" << createdAt << "] "
                      << type << " $" << amount;
            if (!target.empty()) std::cout << " → " << target;
            if (flagged)         std::cout << " ⚠ FLAGGED";
            std::cout << "\n";
        }
        std::cout << "=============================================\n";
        sqlite3_finalize(stmt);
    }

    // Count flagged transactions — useful for a compliance report
    int countFlagged() const {
        const char* sql =
            "SELECT COUNT(*) FROM transactions WHERE flagged = 1;";
        sqlite3_stmt* stmt = Database::get().prepare(sql);
        int count = 0;
        if (sqlite3_step(stmt) == SQLITE_ROW)
            count = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
        return count;
    }
};
```

---

## `database/LoanRepo.h`

Persists the `LoanApplication` struct and the approval decision from `LoanService`.

```cpp
#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sqlite3.h>
#include "../services/LoanService.h"   // reuses Phase-3 LoanApplication struct
#include "Database.h"

// ─────────────────────────────────────────────────────────────
//  LoanRepo
//  Reuses the LoanApplication struct defined in LoanService.h
// ─────────────────────────────────────────────────────────────
class LoanRepo {
    sqlite3* db() const { return Database::get().getHandle(); }

public:
    // Save application + decision in one row
    void save(const LoanApplication& app,
              bool approved,
              double interestRate) const {

        const char* sql =
            "INSERT OR IGNORE INTO loans "
            "(application_id, customer_id, amount, term_months, "
            " approved, interest_rate) "
            "VALUES (?, ?, ?, ?, ?, ?);";

        sqlite3_stmt* stmt = Database::get().prepare(sql);
        sqlite3_bind_text  (stmt, 1, app.applicationId.c_str(),           -1, SQLITE_TRANSIENT);
        sqlite3_bind_text  (stmt, 2, app.applicant.getCustomerId().c_str(),-1, SQLITE_TRANSIENT);
        sqlite3_bind_double(stmt, 3, app.requestedAmount);
        sqlite3_bind_int   (stmt, 4, app.termMonths);
        sqlite3_bind_int   (stmt, 5, approved ? 1 : 0);
        sqlite3_bind_double(stmt, 6, interestRate);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }

    // Print all loans for a customer
    void printByCustomer(const std::string& customerId) const {
        const char* sql =
            "SELECT application_id, amount, term_months, approved, "
            "       interest_rate, created_at "
            "FROM loans WHERE customer_id = ? ORDER BY created_at DESC;";

        sqlite3_stmt* stmt = Database::get().prepare(sql);
        sqlite3_bind_text(stmt, 1, customerId.c_str(), -1, SQLITE_TRANSIENT);

        std::cout << "\n===== Loan History: " << customerId << " =====\n";
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::cout
                << "ID: "     << sqlite3_column_text  (stmt, 0)
                << " | $"     << sqlite3_column_double(stmt, 1)
                << " / "      << sqlite3_column_int   (stmt, 2) << " months"
                << " | "      << (sqlite3_column_int(stmt, 3) ? "APPROVED" : "DECLINED")
                << " @ "      << (sqlite3_column_double(stmt, 4) * 100.0) << "%"
                << " | "      << sqlite3_column_text  (stmt, 5)
                << "\n";
        }
        std::cout << "==========================================\n";
        sqlite3_finalize(stmt);
    }
};
```

---

## `infrastructure/PersistentAuditLogs.h`

This subclass is the cleanest demonstration of **inheritance for extension** in Phase 4. It overrides `log()` to write to the database, then calls `AuditLogs::log()` to preserve the in-memory behaviour. The rest of the codebase uses `AuditLogs&` — substituting a `PersistentAuditLogs` object works transparently thanks to the Liskov Substitution Principle.

```cpp
#pragma once
#include "../infrastructure/AuditLogs.h"
#include "../database/Database.h"
#include <sqlite3.h>
#include <iostream>

// ─────────────────────────────────────────────────────────────
//  PersistentAuditLogs
//
//  Extends AuditLogs (Phase 3) via inheritance.
//  Overrides log() to ALSO write every entry to the database.
//  The parent's in-memory log and printAll() are fully preserved.
//
//  Usage: pass a PersistentAuditLogs wherever AuditLogs& is expected.
//  No other code changes needed.
// ─────────────────────────────────────────────────────────────
class PersistentAuditLogs : public AuditLogs {
public:
    // Shadows AuditLogs::log() — writes to DB then to memory
    void log(const std::string& event) {
        // 1. Persist to database
        const char* sql =
            "INSERT INTO audit_log (event) VALUES (?);";

        sqlite3_stmt* stmt = Database::get().prepare(sql);
        sqlite3_bind_text(stmt, 1, event.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        // 2. Delegate to parent for in-memory storage and timestamp
        AuditLogs::log(event);
    }

    // Query the persistent log from the database (survives restarts)
    void printFromDb(int limit = 50) const {
        std::string sql =
            "SELECT event, created_at FROM audit_log "
            "ORDER BY id DESC LIMIT " + std::to_string(limit) + ";";

        sqlite3_stmt* stmt = Database::get().prepare(sql);

        std::cout << "\n===== PERSISTENT AUDIT LOG (DB, last "
                  << limit << ") =====\n";
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::cout << "[" << sqlite3_column_text(stmt, 1) << "] "
                      << sqlite3_column_text(stmt, 0) << "\n";
        }
        std::cout << "====================================================\n";
        sqlite3_finalize(stmt);
    }
};
```

---

## `main_db.cpp` — Phase 4 Entry Point

This is the only new file that touches service wiring. Compare it to `main.cpp` line by line:

- **Lines 1–5**: adds four repository headers and `PersistentAuditLogs.h`.
- **Lines 6–end**: identical service construction; repositories called after each service operation.
- `main.cpp` is completely untouched and still compiles independently.

```cpp
#include <iostream>
#include <memory>

// ── Phase 3 includes (unchanged) ────────────────────────────
#include "models/Customer.h"
#include "models/SavingsAccount.h"
#include "models/CurrentAccount.h"
#include "services/AccountService.h"
#include "services/TransactionService.h"
#include "services/LoanService.h"
#include "services/NotificationService.h"
#include "security/FraudDetectionService.h"

// ── Phase 4 additions ────────────────────────────────────────
#include "database/Database.h"
#include "database/CustomerRepo.h"
#include "database/AccountRepo.h"
#include "database/TransactionRepo.h"
#include "database/LoanRepo.h"
#include "infrastructure/PersistentAuditLogs.h"

// ── Helper ───────────────────────────────────────────────────
static void section(const std::string& title) {
    std::cout << "\n" << std::string(50, '─') << "\n"
              << "  " << title << "\n"
              << std::string(50, '─') << "\n";
}

int main() {
    std::cout << "================================================\n";
    std::cout << "  C++ Banking System — Phase 4: DB Integration  \n";
    std::cout << "================================================\n\n";

    // ── 1. Open the database (creates bank.db if absent) ─────────
    section("1. Database Initialisation");
    Database::get().open("bank.db");

    // ── 2. Repositories ──────────────────────────────────────────
    CustomerRepo    customerRepo;
    AccountRepo     accountRepo;
    TransactionRepo txnRepo;
    LoanRepo        loanRepo;

    // ── 3. Infrastructure — swap in PersistentAuditLogs ──────────
    //    All services receive AuditLogs& — Liskov holds perfectly.
    PersistentAuditLogs auditLogs;

    // ── 4. Services — IDENTICAL constructors to main.cpp ─────────
    NotificationService   notifService;
    FraudDetectionService fraudService;
    TransactionService    txnService(fraudService, notifService, auditLogs);
    AccountService        accountService(auditLogs);
    LoanService           loanService(notifService, auditLogs);

    // ── 5. Customers ──────────────────────────────────────────────
    section("2. Create & Persist Customers");
    Customer alice("C001", "Alice Johnson", "alice@bank.com", "+1-555-0101");
    Customer bob  ("C002", "Bob Smith",     "bob@bank.com",   "+1-555-0202");

    customerRepo.save(alice);   // Phase 4: persist
    customerRepo.save(bob);

    std::cout << alice.toString() << "\n";
    std::cout << bob.toString()   << "\n";

    // ── 6. Open accounts ─────────────────────────────────────────
    section("3. Open & Persist Accounts");
    auto aliceSavings = accountService.openSavingsAccount(alice, 5000.00);
    auto aliceCurrent = accountService.openCurrentAccount(alice, 2000.00, 1500.00);
    auto bobSavings   = accountService.openSavingsAccount(bob,   3000.00);

    accountRepo.save(*aliceSavings);   // Phase 4: persist each account
    accountRepo.save(*aliceCurrent);
    accountRepo.save(*bobSavings);

    accountService.listAll();

    // ─────────────────────────────────────────────────────────────
    //  Helper lambda: wraps txnService.deposit() and persists
    //  both the updated balance and the transaction record.
    //  The lambda captures by reference — no new classes needed.
    // ─────────────────────────────────────────────────────────────
    auto persistDeposit = [&](Account& acc, double amount) {
        txnService.deposit(acc, amount);                            // Phase 3

        accountRepo.updateBalance(acc);                             // Phase 4
        TransactionRecord rec{ acc.getAccountId(), amount,
                               "DEPOSIT",
                               std::chrono::system_clock::now() };
        txnRepo.save(rec, false);
    };

    auto persistWithdraw = [&](Account& acc, double amount) {
        txnService.withdraw(acc, amount);

        accountRepo.updateBalance(acc);
        TransactionRecord rec{ acc.getAccountId(), amount,
                               "WITHDRAWAL",
                               std::chrono::system_clock::now() };
        txnRepo.save(rec, false);
    };

    auto persistTransfer = [&](Account& src, Account& tgt, double amount) {
        txnService.transfer(src, tgt, amount);

        accountRepo.updateBalance(src);
        accountRepo.updateBalance(tgt);
        TransactionRecord rec{ src.getAccountId(), amount,
                               "TRANSFER",
                               std::chrono::system_clock::now() };
        txnRepo.save(rec, false, tgt.getAccountId());
    };

    // ── 7. Deposits ───────────────────────────────────────────────
    section("4. Deposits");
    persistDeposit(*aliceSavings, 1200.00);
    persistDeposit(*bobSavings,   800.00);

    // ── 8. Withdrawal ─────────────────────────────────────────────
    section("5. Withdrawal");
    persistWithdraw(*aliceSavings, 300.00);

    // ── 9. Transfer ───────────────────────────────────────────────
    section("6. Transfer Alice → Bob");
    persistTransfer(*aliceSavings, *bobSavings, 500.00);

    // ── 10. Apply Interest ────────────────────────────────────────
    section("7. Apply Savings Interest");
    aliceSavings->applyInterest();
    accountRepo.updateBalance(*aliceSavings);   // keep DB in sync

    // ── 11. Large deposit — fraud trigger ─────────────────────────
    section("8. Large Deposit (Fraud Detection Test)");
    txnService.deposit(*aliceCurrent, 15000.00);
    accountRepo.updateBalance(*aliceCurrent);
    {
        TransactionRecord rec{ aliceCurrent->getAccountId(), 15000.00,
                               "DEPOSIT",
                               std::chrono::system_clock::now() };
        txnRepo.save(rec, /*flagged=*/true);   // mark as flagged in DB
    }

    // ── 12. Loan ──────────────────────────────────────────────────
    section("9. Loan Processing");
    LoanApplication loanApp{ "LOAN-2024-001", alice, 10000.00, 36 };
    loanService.processLoan(loanApp, *aliceSavings);
    accountRepo.updateBalance(*aliceSavings);           // loan disbursed
    loanRepo.save(loanApp, /*approved=*/true, 0.07);

    // ── 13. Overdraft test ────────────────────────────────────────
    section("10. Overdraft Test");
    try {
        txnService.withdraw(*aliceCurrent, 20000.00);
    } catch (const std::runtime_error& e) {
        std::cout << "[CAUGHT] " << e.what() << "\n";
    }

    // ── 14. Reload from database ──────────────────────────────────
    section("11. Reload All Data from Database");
    auto dbCustomers = customerRepo.findAll();
    auto dbAccounts  = accountRepo.findAll(dbCustomers);

    std::cout << "\nCustomers in DB:\n";
    for (const auto& c : dbCustomers)
        std::cout << "  " << c.toString() << "\n";

    std::cout << "\nAccounts in DB:\n";
    for (const auto& a : dbAccounts)
        std::cout << "  " << a->toString() << "\n";

    // ── 15. Transaction histories ─────────────────────────────────
    section("12. Transaction Histories");
    txnRepo.printHistory(aliceSavings->getAccountId());
    txnRepo.printHistory(bobSavings->getAccountId());

    std::cout << "\nTotal flagged transactions: "
              << txnRepo.countFlagged() << "\n";

    // ── 16. Loan history ──────────────────────────────────────────
    section("13. Loan History");
    loanRepo.printByCustomer(alice.getCustomerId());

    // ── 17. Audit logs ────────────────────────────────────────────
    section("14. Audit Logs");
    auditLogs.printAll();          // in-memory (Phase 3 method — unchanged)
    auditLogs.printFromDb();       // persistent (Phase 4 method)

    // ── 18. Close database ────────────────────────────────────────
    Database::get().close();

    std::cout << "\n✔  Done. Inspect with:  sqlite3 bank.db\n";
    return 0;
}
```

---

## Build & Run

### Phase 3 binary (unchanged)
```bash
g++ -std=c++20 -Wall -Wextra -o bank main.cpp
./bank
```

### Phase 4 binary (new entry point, links SQLite)
```bash
g++ -std=c++20 -Wall -Wextra -o bank_db main_db.cpp -lsqlite3
./bank_db
```

### Inspect the database
```bash
sqlite3 bank.db
```

```sql
-- All tables
.tables

-- Current balances
SELECT account_id, account_type, balance FROM accounts;

-- Full transaction log (newest first)
SELECT account_id, type, amount, flagged, created_at
FROM transactions ORDER BY id DESC;

-- Only flagged transactions
SELECT * FROM transactions WHERE flagged = 1;

-- Loan decisions
SELECT application_id, amount, approved, interest_rate FROM loans;

-- Audit trail (last 20)
SELECT event, created_at FROM audit_log ORDER BY id DESC LIMIT 20;

-- Total deposited per account
SELECT account_id, SUM(amount) AS total
FROM transactions
WHERE type = 'DEPOSIT'
GROUP BY account_id;

.quit
```

---

## Phase 4 Example Output

```
================================================
  C++ Banking System — Phase 4: DB Integration
================================================

──────────────────────────────────────────────────
  1. Database Initialisation
──────────────────────────────────────────────────
[Database] Connected → bank.db
[Database] Schema ready.

──────────────────────────────────────────────────
  2. Create & Persist Customers
──────────────────────────────────────────────────
[Customer C001] Alice Johnson | alice@bank.com | +1-555-0101
[Customer C002] Bob Smith | bob@bank.com | +1-555-0202

──────────────────────────────────────────────────
  3. Open & Persist Accounts
──────────────────────────────────────────────────
[AccountService] Opened: [SavingsAccount SAV-1001] Alice Johnson | Balance: $5000.000000
[AccountService] Opened: [CurrentAccount CUR-1002] Alice Johnson | Balance: $2000.000000
[AccountService] Opened: [SavingsAccount SAV-1003] Bob Smith | Balance: $3000.000000

──────────────────────────────────────────────────
  4. Deposits
──────────────────────────────────────────────────
[Savings] Deposited $1200 | New balance: $6200
[NOTIFICATION] Email to alice@bank.com — DEPOSIT of $1200 on SAV-1001
[Savings] Deposited $800 | New balance: $3800
[NOTIFICATION] Email to bob@bank.com — DEPOSIT of $800 on SAV-1003

──────────────────────────────────────────────────
  8. Large Deposit (Fraud Detection Test)
──────────────────────────────────────────────────
[Current] Deposited $15000 | New balance: $17000
[FRAUD ALERT] Large transaction detected: $15000 on account CUR-1002
[FRAUD NOTIFICATION] SMS to +1-555-0101 — Suspicious activity on CUR-1002.

──────────────────────────────────────────────────
  11. Reload All Data from Database
──────────────────────────────────────────────────
Customers in DB:
  [Customer C001] Alice Johnson | alice@bank.com | +1-555-0101
  [Customer C002] Bob Smith | bob@bank.com | +1-555-0202

Accounts in DB:
  [SavingsAccount SAV-1001] Alice Johnson | Balance: $15589.000000
  [CurrentAccount CUR-1002] Alice Johnson | Balance: $17000.000000
  [SavingsAccount SAV-1003] Bob Smith     | Balance: $4300.000000

──────────────────────────────────────────────────
  12. Transaction Histories
──────────────────────────────────────────────────
===== Transaction History: SAV-1001 =====
[2026-03-10 12:00:05] TRANSFER $500.000000 → SAV-1003
[2026-03-10 12:00:04] WITHDRAWAL $300.000000
[2026-03-10 12:00:03] DEPOSIT $1200.000000
==========================================

Total flagged transactions: 1

──────────────────────────────────────────────────
  13. Loan History
──────────────────────────────────────────────────
===== Loan History: C001 =====
ID: LOAN-2024-001 | $10000 / 36 months | APPROVED @ 7% | 2026-03-10 12:00:06
==========================================

──────────────────────────────────────────────────
  14. Audit Logs
──────────────────────────────────────────────────
===== AUDIT LOG =====
[Tue Mar 10 12:00:01 2026] OPENED SavingsAccount SAV-1001 for Alice Johnson
[Tue Mar 10 12:00:03 2026] DEPOSIT $1200.000000 to SAV-1001
[Tue Mar 10 12:00:04 2026] WITHDRAWAL $300.000000 from SAV-1001
[Tue Mar 10 12:00:05 2026] TRANSFER $500.000000 from SAV-1001 to SAV-1003
[Tue Mar 10 12:00:06 2026] LOAN APPROVED $10000.000000 for Alice Johnson
=====================

===== PERSISTENT AUDIT LOG (DB, last 50) =====
[2026-03-10 12:00:06] LOAN APPROVED $10000.000000 for Alice Johnson
[2026-03-10 12:00:05] TRANSFER $500.000000 from SAV-1001 to SAV-1003
[2026-03-10 12:00:04] WITHDRAWAL $300.000000 from SAV-1001
[2026-03-10 12:00:03] DEPOSIT $1200.000000 to SAV-1001
[2026-03-10 12:00:01] OPENED SavingsAccount SAV-1001 for Alice Johnson
====================================================

[Database] Connection closed.
✔  Done. Inspect with:  sqlite3 bank.db
```

---

## OOP Patterns Introduced in Phase 4

| Pattern | Where | Description |
|---|---|---|
| **Inheritance for extension** | `PersistentAuditLogs : AuditLogs` | Adds DB persistence without altering the base class. Liskov Substitution holds — passes silently wherever `AuditLogs&` is expected. |
| **Polymorphism in persistence** | `AccountRepo::save(const Account&)` | Accepts any `Account` subtype. Uses `dynamic_cast` externally to read type-specific fields, keeping models clean. |
| **Polymorphic rehydration** | `AccountRepo::findAll()` | Reads `account_type` column and `make_shared<SavingsAccount>` or `make_shared<CurrentAccount>`. Returns `vector<shared_ptr<Account>>` — callers use the base interface. |
| **Singleton** | `Database::get()` | One connection, globally accessible, no parameters to thread through every call. |
| **Composition over intrusion** | Lambda wrappers in `main_db.cpp` | Rather than modifying `TransactionService`, thin lambdas compose the service call with a repo call. Phase 3 source stays pristine. |

---

## How to Migrate to PostgreSQL or MySQL

Because all SQL is isolated in the four repository files and `Database.h`, switching the database engine requires touching **only those five files**. Every model, service, and `main_db.cpp` stays unchanged.

| Operation | SQLite3 C API | libpq (PostgreSQL) | MySQL C API |
|---|---|---|---|
| Connect | `sqlite3_open(path, &db)` | `PQconnectdb(connStr)` | `mysql_real_connect(...)` |
| Prepare | `sqlite3_prepare_v2(...)` | `PQprepare(...)` | `mysql_stmt_prepare(...)` |
| Bind text | `sqlite3_bind_text(...)` | `PQexecParams(...)` | `mysql_stmt_bind_param(...)` |
| Step/execute | `sqlite3_step(stmt)` | `PQexecPrepared(...)` | `mysql_stmt_execute(...)` |
| Read column | `sqlite3_column_text/double/int` | `PQgetvalue(res, row, col)` | `mysql_stmt_bind_result(...)` |
| Finalise | `sqlite3_finalize(stmt)` | `PQclear(res)` | `mysql_stmt_close(stmt)` |
| Close | `sqlite3_close(db)` | `PQfinish(conn)` | `mysql_close(conn)` |

The **logical flow** — prepare → bind → execute → read rows → finalise — is identical across all three.

---

# Possible Future Improvements

- **REST API** — wrap services in HTTP endpoints using Crow or cpp-httplib; expose `/accounts`, `/transactions`, `/loans`.
- **ATM System** — add an `ATMController` class with `CardReader` and PIN validation components.
- **Concurrency** — add `std::mutex` guards around `balance` mutations and the `Database` singleton to support multi-threaded transaction processing.
- **Authentication & Authorisation** — introduce `AuthService` with JWT tokens and role-based access control.
- **Distributed Architecture** — break services into microservices communicating over gRPC or Kafka; each owns its own database schema.
- **Machine Learning Fraud Detection** — replace heuristic rules with a real-time ONNX inference model trained on the persisted `transactions` table.
- **Unit Tests** — add Google Test or Catch2 suites for every service class and repository.
- **Connection Pooling** — replace the single-connection `Database` singleton with a thread-safe pool for multi-threaded deployments.
- **Migrations** — introduce a versioned schema migration system (Flyway-style) so the schema can evolve without dropping tables.

---

# Conclusion

You started with the building blocks of OOP and stepped through every pillar:

1. **Encapsulation** — protecting state behind controlled interfaces.
2. **Inheritance** — sharing and extending behaviour across account types.
3. **Polymorphism** — writing service code that works on *any* account type without branching.
4. **Abstraction** — enforcing a contract that all account types must fulfil.
5. **Composition** — wiring independent services together cleanly.
6. **Database Integration** — persisting domain objects through a repository layer that wraps the existing codebase without changing it.

The central lesson of Phase 4 is as important as any OOP pillar: **good architecture enables change in isolation**. Because Phase 3 respected encapsulation, abstraction, and separation of concerns, Phase 4 added a full persistence layer by writing new files — not by editing old ones. Every repository, every query, every schema decision fits naturally around the domain objects precisely because those objects were designed well from the start.

This is the foundation of every large-scale C++ codebase you will encounter in industry. Master these patterns and you will be ready to design systems of any complexity.

---

> *"Make each program do one thing well." — Unix Philosophy*  
> In OOP, "one thing" maps directly to one class. Design wisely.

---

**Author**: Generated as a professional C++ OOP educational guide.  
**Language**: C++20  
**Licence**: MIT
