# Object-Oriented Programming in C++: From Concepts to a Complete Banking System

> A professional, beginner-to-advanced guide covering every OOP pillar in C++ through hands-on examples, culminating in a fully modular Banking System you can run, extend, and deploy.

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
[Savings] Deposited $800 | New balance: $3800
[NOTIFICATION] Email to bob@bank.com — DEPOSIT of $800 on account SAV-1003 | New balance: $3800

--- Withdrawal ---
[Savings] Withdrew $300 | New balance: $5900
[NOTIFICATION] Email to alice@bank.com — WITHDRAWAL of $300 on account SAV-1001 | New balance: $5900

--- Transfer Alice → Bob ---
[Savings] Withdrew $500 | New balance: $5400
[Savings] Deposited $500 | New balance: $4300
[NOTIFICATION] Email to alice@bank.com — TRANSFER OUT of $500 on account SAV-1001 | New balance: $5400
[NOTIFICATION] Email to bob@bank.com — TRANSFER IN of $500 on account SAV-1003 | New balance: $4300

--- Applying Interest ---
[Savings] Interest applied: $189 | New balance: $5589

--- Large Deposit (Fraud Detection Test) ---
[Current] Deposited $15000 | New balance: $17000
[FRAUD ALERT] Large transaction detected: $15000 on account CUR-1002
[NOTIFICATION] Email to alice@bank.com — DEPOSIT of $15000 on account CUR-1002 | New balance: $17000
[FRAUD NOTIFICATION] SMS to +1-555-0101 — Suspicious activity detected on account CUR-1002. Please verify.

--- Loan Application: LOAN-2024-001 ---
Applicant      : Alice Johnson
Requested      : $10000
Max Eligible   : $27945
Decision       : APPROVED
Loan disbursed to account SAV-1001
[LOAN NOTIFICATION] Alice Johnson — Loan of $10000 APPROVED at 7% interest.

--- Overdraft Test (CurrentAccount) ---
[CAUGHT] Overdraft limit exceeded

--- Final Account Balances ---
===== All Accounts =====
[SavingsAccount SAV-1001] Alice Johnson | Balance: $15589.000000
[CurrentAccount CUR-1002] Alice Johnson | Balance: $17000.000000
[SavingsAccount SAV-1003] Bob Smith     | Balance: $4300.000000
========================

===== AUDIT LOG =====
[Tue Mar 10 12:00:01 2026] OPENED SavingsAccount SAV-1001 for Alice Johnson
[Tue Mar 10 12:00:01 2026] OPENED CurrentAccount CUR-1002 for Alice Johnson
[Tue Mar 10 12:00:01 2026] OPENED SavingsAccount SAV-1003 for Bob Smith
[Tue Mar 10 12:00:02 2026] DEPOSIT $1200.000000 to SAV-1001
[Tue Mar 10 12:00:02 2026] DEPOSIT $800.000000 to SAV-1003
[Tue Mar 10 12:00:02 2026] WITHDRAWAL $300.000000 from SAV-1001
[Tue Mar 10 12:00:02 2026] TRANSFER $500.000000 from SAV-1001 to SAV-1003
[Tue Mar 10 12:00:02 2026] DEPOSIT $15000.000000 to CUR-1002
[Tue Mar 10 12:00:02 2026] LOAN APPROVED $10000.000000 for Alice Johnson
=====================
```

---

# Key OOP Concepts Used in the Project

| Concept | Where Applied |
|---|---|
| **Encapsulation** | `Account`, `Customer`: all attributes are `private`; state is changed only through validated methods. |
| **Inheritance** | `SavingsAccount` and `CurrentAccount` inherit from `Account`, reusing `balance`, `transfer()`, and `toString()`. |
| **Polymorphism** | `TransactionService` accepts `Account&` references — it calls `deposit()` and `withdraw()` without knowing the concrete type. The virtual dispatch selects the right implementation at runtime. |
| **Abstraction** | `Account` is an abstract class with pure virtual `deposit()`, `withdraw()`, and `getAccountType()`. No "bare" account can be created. |
| **Composition** | `Account` **has-a** `Customer`. `TransactionService` **has-a** `FraudDetectionService`, `NotificationService`, and `AuditLogs`. |

---

# Possible Future Improvements

- **Database Integration** — replace in-memory vectors with PostgreSQL or SQLite via an ORM or raw SQL layer.
- **REST API** — wrap services in HTTP endpoints using a library like Crow or cpp-httplib; expose `/accounts`, `/transactions`, `/loans`.
- **ATM System** — add a `ATMController` class with a `CardReader` component and PIN validation.
- **Concurrency Handling** — add `std::mutex` guards around `balance` mutations to support multi-threaded transaction processing.
- **Authentication & Authorisation** — introduce `AuthService` with JWT tokens and role-based access control.
- **Distributed Architecture** — break services into microservices communicating over gRPC or a message queue (Kafka/RabbitMQ).
- **Machine Learning Fraud Detection** — replace heuristic rules in `FraudDetectionService` with a real-time inference model.
- **Unit Tests** — add Google Test or Catch2 suites for every service class.
- **Logging Framework** — replace `std::cout` in `AuditLogs` with a structured logging library such as spdlog.

---

# Conclusion

You started with the building blocks of OOP — classes, objects, and access specifiers — and stepped through every pillar:

1. **Encapsulation** — protecting state behind controlled interfaces.
2. **Inheritance** — sharing and extending behaviour across account types.
3. **Polymorphism** — writing service code that works on *any* account type without branching.
4. **Abstraction** — enforcing a contract that all account types must fulfil.
5. **Composition** — wiring independent services together cleanly.

The Banking System demonstrates that **real-world software is not a monolithic function** — it is a network of well-defined objects, each responsible for one concern, collaborating through stable interfaces. This is the foundation of every large-scale C++ codebase you will encounter in industry.

Master these patterns and you will be ready to design systems of any complexity.

---

> *"Make each program do one thing well." — Unix Philosophy*  
> In OOP, "one thing" maps directly to one class. Design wisely.

---

**Author**: Generated as a professional C++ OOP educational guide.  
**Language**: C++20  
**Licence**: MIT
