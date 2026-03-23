# PART 2 — Object-Oriented JavaScript (OOJS)

---

## 10. ES6 Classes — Complete OOP

ES6 classes are **syntactic sugar** over JavaScript's prototype-based system. They make OOP patterns clean and readable.

### 10.1 Class Fundamentals

```javascript
class Animal {
    // Class field (public) — ES2022
    species = "Unknown";

    // Private field — ES2022 — truly private, not accessible outside
    #alive = true;

    // Static field — belongs to the class, not instances
    static count = 0;
    static #registry = [];

    constructor(name, sound) {
        this.name  = name;
        this.sound = sound;
        Animal.count++;
        Animal.#registry.push(this);
    }

    // Instance method
    speak() {
        console.log(`${this.name} says: ${this.sound}`);
    }

    // Getter
    get isAlive() {
        return this.#alive;
    }

    // Setter
    set isAlive(value) {
        if (typeof value !== "boolean") throw new TypeError("Must be boolean");
        this.#alive = value;
    }

    // Static method — called on the class, not instances
    static getCount() {
        return Animal.count;
    }

    static getRegistry() {
        return [...Animal.#registry];
    }

    // toString override
    toString() {
        return `Animal(${this.name})`;
    }
}

// Usage
const lion  = new Animal("Leo",  "Roar");
const tiger = new Animal("Tigger", "Growl");

lion.speak();                        // "Leo says: Roar"
console.log(lion.isAlive);           // true
lion.isAlive = false;
console.log(lion.isAlive);           // false

console.log(Animal.getCount());      // 2
console.log(Animal.getRegistry());   // [lion, tiger]

// console.log(lion.#alive);         // ❌ SyntaxError — private field
```

### 10.2 Complete Class Example — Product

```javascript
class Product {
    static #nextId = 1;
    static #all    = new Map();

    #id;
    #name;
    #price;
    #stock;
    #createdAt;

    constructor({ name, price, stock = 0 }) {
        if (!name)        throw new TypeError("Product name is required");
        if (price < 0)    throw new RangeError("Price cannot be negative");

        this.#id        = Product.#nextId++;
        this.#name      = name;
        this.#price     = price;
        this.#stock     = stock;
        this.#createdAt = new Date();

        Product.#all.set(this.#id, this);
    }

    // Getters
    get id()        { return this.#id; }
    get name()      { return this.#name; }
    get price()     { return this.#price; }
    get stock()     { return this.#stock; }
    get createdAt() { return this.#createdAt; }
    get inStock()   { return this.#stock > 0; }

    // Setters with validation
    set price(value) {
        if (value < 0) throw new RangeError("Price cannot be negative");
        this.#price = value;
    }

    // Methods
    addStock(qty) {
        if (qty <= 0) throw new RangeError("Quantity must be positive");
        this.#stock += qty;
        return this;   // Method chaining
    }

    removeStock(qty) {
        if (qty > this.#stock) throw new Error("Insufficient stock");
        this.#stock -= qty;
        return this;
    }

    toJSON() {
        return {
            id:        this.#id,
            name:      this.#name,
            price:     this.#price,
            stock:     this.#stock,
            inStock:   this.inStock,
            createdAt: this.#createdAt.toISOString()
        };
    }

    toString() {
        return `Product[${this.#id}]: ${this.#name} ($${this.#price}) — ${this.#stock} in stock`;
    }

    // Static methods
    static findById(id)   { return Product.#all.get(id); }
    static getAll()       { return [...Product.#all.values()]; }
    static findByName(n)  { return Product.getAll().filter(p => p.name.includes(n)); }

    static get totalProducts() { return Product.#all.size; }
}

// Practice
const laptop  = new Product({ name: "MacBook Pro", price: 1999, stock: 5 });
const phone   = new Product({ name: "iPhone 15",   price: 999,  stock: 10 });
const tablet  = new Product({ name: "iPad Air",    price: 599,  stock: 0  });

laptop.addStock(3).removeStock(2);   // Method chaining

console.log(laptop.toString());
console.log(JSON.stringify(phone.toJSON(), null, 2));
console.log(`Total products: ${Product.totalProducts}`);
console.log(Product.findById(1).name);   // "MacBook Pro"
```

---

## 11. Inheritance & Polymorphism

### 11.1 Class Inheritance with `extends`

```javascript
class Shape {
    #colour;
    #filled;

    constructor(colour = "black", filled = true) {
        if (new.target === Shape) {
            throw new Error("Shape is abstract — cannot instantiate directly");
        }
        this.#colour = colour;
        this.#filled = filled;
    }

    get colour() { return this.#colour; }
    get filled()  { return this.#filled; }

    // Template method (to be overridden)
    area()      { throw new Error(`${this.constructor.name} must implement area()`); }
    perimeter() { throw new Error(`${this.constructor.name} must implement perimeter()`); }

    describe() {
        return `${this.constructor.name}: colour=${this.#colour}, ` +
               `area=${this.area().toFixed(2)}, perimeter=${this.perimeter().toFixed(2)}`;
    }

    toString() {
        return this.describe();
    }
}

class Circle extends Shape {
    #radius;

    constructor(radius, colour, filled) {
        super(colour, filled);   // Must call super() before using this
        if (radius <= 0) throw new RangeError("Radius must be positive");
        this.#radius = radius;
    }

    get radius() { return this.#radius; }

    area()      { return Math.PI * this.#radius ** 2; }
    perimeter() { return 2 * Math.PI * this.#radius; }

    scale(factor) {
        return new Circle(this.#radius * factor, this.colour, this.filled);
    }
}

class Rectangle extends Shape {
    #width;
    #height;

    constructor(width, height, colour, filled) {
        super(colour, filled);
        this.#width  = width;
        this.#height = height;
    }

    get width()  { return this.#width; }
    get height() { return this.#height; }

    area()      { return this.#width * this.#height; }
    perimeter() { return 2 * (this.#width + this.#height); }

    isSquare()  { return this.#width === this.#height; }
}

class Triangle extends Shape {
    #a; #b; #c;   // Side lengths

    constructor(a, b, c, colour, filled) {
        super(colour, filled);
        if (a + b <= c || a + c <= b || b + c <= a) {
            throw new Error("Invalid triangle sides");
        }
        this.#a = a; this.#b = b; this.#c = c;
    }

    perimeter() { return this.#a + this.#b + this.#c; }

    area() {
        const s = this.perimeter() / 2;   // Semi-perimeter (Heron's formula)
        return Math.sqrt(s * (s - this.#a) * (s - this.#b) * (s - this.#c));
    }
}

// Polymorphism in action
const shapes = [
    new Circle(5, "red"),
    new Rectangle(4, 6, "blue"),
    new Triangle(3, 4, 5, "green"),
    new Circle(3, "purple"),
    new Rectangle(5, 5, "orange"),
];

// Same method call → different behaviour per type
shapes.forEach(s => console.log(s.describe()));

// Total area of all shapes
const totalArea = shapes.reduce((sum, s) => sum + s.area(), 0);
console.log(`Total area: ${totalArea.toFixed(2)}`);

// instanceof checks
shapes.forEach(s => {
    console.log(`${s.constructor.name} is Shape: ${s instanceof Shape}`);
});
```

### 11.2 Method Overriding & super

```javascript
class Vehicle {
    #make;
    #model;
    #year;
    #speed = 0;

    constructor(make, model, year) {
        this.#make  = make;
        this.#model = model;
        this.#year  = year;
    }

    get make()  { return this.#make; }
    get model() { return this.#model; }
    get year()  { return this.#year; }
    get speed() { return this.#speed; }

    accelerate(amount) {
        this.#speed = Math.min(this.#speed + amount, this.maxSpeed);
        return this;
    }

    brake(amount) {
        this.#speed = Math.max(this.#speed - amount, 0);
        return this;
    }

    get maxSpeed() { return 200; }

    toString() {
        return `${this.#year} ${this.#make} ${this.#model} @ ${this.#speed}km/h`;
    }
}

class Car extends Vehicle {
    #doors;
    #fuel = 100;

    constructor(make, model, year, doors = 4) {
        super(make, model, year);
        this.#doors = doors;
    }

    get maxSpeed() { return 220; }   // Override

    accelerate(amount) {
        this.#fuel -= amount * 0.1;   // Burns fuel
        return super.accelerate(amount);  // Call parent method
    }

    get fuelLevel() { return this.#fuel; }

    toString() {
        return `${super.toString()}, ${this.#doors} doors, fuel: ${this.#fuel.toFixed(1)}%`;
    }
}

class ElectricCar extends Car {
    #batteryLevel;

    constructor(make, model, year, batteryLevel = 100) {
        super(make, model, year, 4);
        this.#batteryLevel = batteryLevel;
    }

    get maxSpeed() { return 250; }

    accelerate(amount) {
        // Electric cars work differently — bypass Car's fuel logic
        this.#batteryLevel -= amount * 0.05;
        return Vehicle.prototype.accelerate.call(this, amount);
    }

    charge(amount) {
        this.#batteryLevel = Math.min(this.#batteryLevel + amount, 100);
        return this;
    }

    toString() {
        return `${super.toString()} [ELECTRIC, battery: ${this.#batteryLevel.toFixed(1)}%]`;
    }
}

const car  = new Car("Toyota", "Camry", 2024);
const tesla = new ElectricCar("Tesla", "Model 3", 2024);

car.accelerate(60).accelerate(40).brake(20);
tesla.accelerate(80).charge(5);

console.log(car.toString());
console.log(tesla.toString());
```

---

## 12. Encapsulation & Private Fields

### 12.1 The Module Pattern (Closure-based)

```javascript
// Pre-ES2022: Use closures for privacy
const BankAccount = (() => {
    // Private symbol for internal methods
    const _validate = Symbol("validate");

    return class {
        #balance;
        #transactions = [];
        #owner;

        constructor(owner, initialBalance = 0) {
            this.#owner   = owner;
            this.#balance = this[_validate](initialBalance);
        }

        [_validate](amount) {
            if (typeof amount !== "number" || isNaN(amount)) {
                throw new TypeError("Amount must be a number");
            }
            if (amount < 0) throw new RangeError("Amount cannot be negative");
            return amount;
        }

        deposit(amount) {
            this[_validate](amount);
            this.#balance += amount;
            this.#transactions.push({ type: "deposit", amount, date: new Date() });
            return this;
        }

        withdraw(amount) {
            this[_validate](amount);
            if (amount > this.#balance) throw new Error("Insufficient funds");
            this.#balance -= amount;
            this.#transactions.push({ type: "withdrawal", amount, date: new Date() });
            return this;
        }

        transfer(amount, targetAccount) {
            this.withdraw(amount);
            targetAccount.deposit(amount);
            return this;
        }

        get balance() { return this.#balance; }
        get owner()   { return this.#owner; }

        getStatement() {
            return this.#transactions.map(t =>
                `${t.type.padEnd(12)} $${t.amount.toFixed(2).padStart(10)}  ${t.date.toLocaleDateString()}`
            ).join("\n");
        }
    };
})();

const alice = new BankAccount("Alice", 5000);
const bob   = new BankAccount("Bob",   2000);

alice.deposit(1000).deposit(500);
alice.transfer(800, bob);
alice.withdraw(200);

console.log(`Alice: $${alice.balance}`);
console.log(`Bob:   $${bob.balance}`);
console.log("\nAlice's Statement:");
console.log(alice.getStatement());
```

---

## 13. Mixins & Composition

### 13.1 Mixin Pattern

```javascript
// Mixins add reusable behaviour without inheritance chains

// Serialisable mixin
const Serialisable = (Base) => class extends Base {
    toJSON() {
        return JSON.stringify(this, null, 2);
    }

    static fromJSON(json) {
        const data = JSON.parse(json);
        return Object.assign(new this(), data);
    }
};

// Timestamped mixin
const Timestamped = (Base) => class extends Base {
    #createdAt = new Date();
    #updatedAt = new Date();

    touch() {
        this.#updatedAt = new Date();
        return this;
    }

    get createdAt() { return this.#createdAt; }
    get updatedAt() { return this.#updatedAt; }
};

// Validatable mixin
const Validatable = (Base) => class extends Base {
    #errors = [];

    validate() { return this.#errors.length === 0; }
    get errors() { return [...this.#errors]; }

    addError(field, message) {
        this.#errors.push({ field, message });
        return this;
    }

    clearErrors() {
        this.#errors = [];
        return this;
    }
};

// Compose mixins onto a base class
class Model {}

class User extends Serialisable(Timestamped(Validatable(Model))) {
    constructor({ name, email, age }) {
        super();
        this.name  = name;
        this.email = email;
        this.age   = age;
    }

    validate() {
        this.clearErrors();
        if (!this.name)             this.addError("name", "Name is required");
        if (!this.email?.includes("@")) this.addError("email", "Invalid email");
        if (this.age < 0 || this.age > 150) this.addError("age", "Invalid age");
        return super.validate();
    }
}

const user = new User({ name: "Alice", email: "alice@example.com", age: 28 });
user.touch();

console.log(user.validate());          // true
console.log(user.createdAt);
console.log(user.toJSON());
```

---

## 14. Design Patterns in JS

### 14.1 Singleton

```javascript
class DatabaseConnection {
    static #instance = null;

    #connection;
    #queryCount = 0;

    constructor(connectionString) {
        if (DatabaseConnection.#instance) {
            return DatabaseConnection.#instance;
        }
        this.#connection = connectionString;
        DatabaseConnection.#instance = this;
    }

    query(sql) {
        this.#queryCount++;
        console.log(`[Query #${this.#queryCount}] ${sql}`);
        return { rows: [], count: 0 };
    }

    static getInstance(cs = "localhost:5432") {
        if (!DatabaseConnection.#instance) {
            new DatabaseConnection(cs);
        }
        return DatabaseConnection.#instance;
    }
}

const db1 = DatabaseConnection.getInstance();
const db2 = DatabaseConnection.getInstance();
console.log(db1 === db2);  // true
db1.query("SELECT * FROM users");
db2.query("SELECT * FROM products");  // same connection
```

### 14.2 Observer (Event Emitter)

```javascript
class EventEmitter {
    #listeners = new Map();

    on(event, listener) {
        if (!this.#listeners.has(event)) {
            this.#listeners.set(event, new Set());
        }
        this.#listeners.get(event).add(listener);
        return () => this.off(event, listener);   // Returns unsubscribe fn
    }

    once(event, listener) {
        const wrapper = (...args) => {
            listener(...args);
            this.off(event, wrapper);
        };
        return this.on(event, wrapper);
    }

    off(event, listener) {
        this.#listeners.get(event)?.delete(listener);
    }

    emit(event, ...args) {
        this.#listeners.get(event)?.forEach(fn => fn(...args));
    }
}

class Store extends EventEmitter {
    #state;

    constructor(initialState) {
        super();
        this.#state = initialState;
    }

    get state() { return { ...this.#state }; }

    setState(updates) {
        const prevState = this.#state;
        this.#state = { ...this.#state, ...updates };
        this.emit("change", this.#state, prevState);
    }
}

const store = new Store({ user: null, theme: "dark", cart: [] });

const unsubscribe = store.on("change", (newState, prevState) => {
    console.log("State changed:", newState);
});

store.setState({ user: { name: "Alice" } });
store.setState({ theme: "light" });
unsubscribe();  // Stop listening
store.setState({ cart: [{ id: 1 }] });  // Not logged
```

### 14.3 Factory Pattern

```javascript
class NotificationFactory {
    static #creators = new Map();

    static register(type, creator) {
        NotificationFactory.#creators.set(type, creator);
    }

    static create(type, options) {
        const creator = NotificationFactory.#creators.get(type);
        if (!creator) throw new Error(`Unknown notification type: ${type}`);
        return creator(options);
    }
}

// Register notification types
NotificationFactory.register("email", ({ to, subject, body }) => ({
    type: "email",
    send() { console.log(`📧 Email to ${to}: ${subject}\n${body}`); }
}));

NotificationFactory.register("sms", ({ to, message }) => ({
    type: "sms",
    send() { console.log(`📱 SMS to ${to}: ${message}`); }
}));

NotificationFactory.register("push", ({ userId, title, body }) => ({
    type: "push",
    send() { console.log(`🔔 Push to user ${userId}: ${title} — ${body}`); }
}));

// Usage — consumer doesn't know concrete classes
const email = NotificationFactory.create("email", {
    to: "alice@example.com", subject: "Welcome!", body: "Thanks for joining."
});
const sms = NotificationFactory.create("sms", {
    to: "+91-9876543210", message: "Your OTP is 482910"
});

email.send();
sms.send();
```

### 14.4 Strategy Pattern

```javascript
class Sorter {
    #strategy;

    constructor(strategy) {
        this.#strategy = strategy;
    }

    setStrategy(strategy) {
        this.#strategy = strategy;
    }

    sort(data) {
        return this.#strategy.sort([...data]);
    }
}

// Concrete strategies
const bubbleSort = {
    name: "Bubble Sort",
    sort(arr) {
        const n = arr.length;
        for (let i = 0; i < n - 1; i++) {
            for (let j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) [arr[j], arr[j + 1]] = [arr[j + 1], arr[j]];
            }
        }
        return arr;
    }
};

const quickSort = {
    name: "Quick Sort",
    sort(arr) {
        if (arr.length <= 1) return arr;
        const pivot = arr[Math.floor(arr.length / 2)];
        const left  = arr.filter(x => x < pivot);
        const mid   = arr.filter(x => x === pivot);
        const right = arr.filter(x => x > pivot);
        return [...this.sort(left), ...mid, ...this.sort(right)];
    }
};

const data = [64, 34, 25, 12, 22, 11, 90];
const sorter = new Sorter(quickSort);
console.log(sorter.sort(data));

sorter.setStrategy(bubbleSort);
console.log(sorter.sort(data));
```

---

# PART 3 — Async JavaScript

---

## 15. Callbacks & Callback Hell

```javascript
// Callbacks: functions passed as arguments, called when async work is done

// Simple callback
function fetchData(id, callback) {
    setTimeout(() => {
        const data = { id, name: "Alice", age: 28 };
        callback(null, data);    // Node.js convention: (error, result)
    }, 1000);
}

fetchData(1, (err, user) => {
    if (err) return console.error(err);
    console.log(user);
});

// ── CALLBACK HELL (Pyramid of Doom) ──────────────────────────────
// Hard to read, error-prone, impossible to maintain
fetchUser(userId, (err, user) => {
    if (err) return handleError(err);
    fetchOrders(user.id, (err, orders) => {
        if (err) return handleError(err);
        fetchProductDetails(orders[0].productId, (err, product) => {
            if (err) return handleError(err);
            fetchReviews(product.id, (err, reviews) => {
                if (err) return handleError(err);
                // Finally do something... but we're 4 levels deep!
                console.log({ user, orders, product, reviews });
            });
        });
    });
});

// ── Solution: Promises (see next section) ────────────────────────
```

---

## 16. Promises

A **Promise** represents a value that will be available in the future.

```javascript
// Creating a Promise
const fetchUser = (id) => new Promise((resolve, reject) => {
    setTimeout(() => {
        if (id <= 0) {
            reject(new Error("Invalid ID"));
        } else {
            resolve({ id, name: "Alice", age: 28 });
        }
    }, 500);
});

// Consuming
fetchUser(1)
    .then(user => {
        console.log("Got user:", user);
        return user.id;   // Value passed to next .then()
    })
    .then(id => console.log("User ID:", id))
    .catch(err => console.error("Error:", err.message))
    .finally(() => console.log("Done (always runs)"));

// ── Promise Chaining — flat, readable ────────────────────────────
const fetchOrders  = (userId) => new Promise(res => setTimeout(() => res([
    { id: 1, productId: 10, amount: 99 },
    { id: 2, productId: 20, amount: 149 }
]), 300));

const fetchProduct = (id) => new Promise(res => setTimeout(() => res(
    { id, name: "Laptop", price: 999 }
), 200));

fetchUser(1)
    .then(user  => fetchOrders(user.id))
    .then(orders => fetchProduct(orders[0].productId))
    .then(product => console.log("Product:", product))
    .catch(err => console.error(err));

// ── Promise.all — run in parallel, wait for all ───────────────────
Promise.all([
    fetchUser(1),
    fetchUser(2),
    fetchUser(3)
])
.then(([user1, user2, user3]) => console.log(user1, user2, user3))
.catch(err => console.error("One failed:", err));   // Rejects if ANY fails

// ── Promise.allSettled — wait for all, even failures ─────────────
Promise.allSettled([
    fetchUser(1),
    fetchUser(-1),   // Will reject
    fetchUser(3)
]).then(results => {
    results.forEach(result => {
        if (result.status === "fulfilled") console.log("✅", result.value);
        else console.log("❌", result.reason.message);
    });
});

// ── Promise.race — first to settle wins ──────────────────────────
const timeout = (ms) => new Promise((_, reject) =>
    setTimeout(() => reject(new Error("Timeout")), ms)
);

Promise.race([fetchUser(1), timeout(300)])
    .then(user => console.log("Fast enough:", user))
    .catch(err => console.error("Too slow:", err.message));

// ── Promise.any — first to SUCCEED wins ──────────────────────────
Promise.any([
    Promise.reject("fail1"),
    Promise.resolve("success!"),
    Promise.resolve("also success")
]).then(first => console.log("First success:", first));
```

---

## 17. Async / Await

`async/await` is syntactic sugar over Promises — it makes async code look synchronous.

```javascript
// Mark function as async → it returns a Promise
async function fetchUserData(userId) {
    try {
        const user    = await fetchUser(userId);          // Wait for Promise
        const orders  = await fetchOrders(user.id);       // Wait for next
        const product = await fetchProduct(orders[0].productId);

        return { user, orders, product };   // Automatically wrapped in Promise
    } catch (err) {
        console.error("Failed:", err.message);
        throw err;   // Re-throw to caller
    }
}

// Call it
fetchUserData(1).then(data => console.log(data));

// Or inside another async function
async function main() {
    const data = await fetchUserData(1);
    console.log(data);
}
main();

// ── Parallel execution with async/await ──────────────────────────
async function fetchAll() {
    // Sequential — slow (each waits for previous)
    const user1 = await fetchUser(1);
    const user2 = await fetchUser(2);
    const user3 = await fetchUser(3);
    // Total: ~1500ms

    // Parallel — fast (all run simultaneously)
    const [u1, u2, u3] = await Promise.all([
        fetchUser(1),
        fetchUser(2),
        fetchUser(3)
    ]);
    // Total: ~500ms

    return [u1, u2, u3];
}

// ── Async IIFE ───────────────────────────────────────────────────
(async () => {
    const result = await fetchUserData(1);
    console.log(result);
})();

// ── for...of with await ──────────────────────────────────────────
async function processUsersSequentially(ids) {
    const results = [];
    for (const id of ids) {
        const user = await fetchUser(id);   // Waits between each
        results.push(user);
    }
    return results;
}

// ── Retry logic ──────────────────────────────────────────────────
async function fetchWithRetry(fn, maxRetries = 3, delay = 1000) {
    for (let attempt = 1; attempt <= maxRetries; attempt++) {
        try {
            return await fn();
        } catch (err) {
            if (attempt === maxRetries) throw err;
            console.log(`Attempt ${attempt} failed. Retrying in ${delay}ms...`);
            await new Promise(res => setTimeout(res, delay * attempt));
        }
    }
}
```

---

## 18. Error Handling

```javascript
// ── Custom Error Classes ──────────────────────────────────────────
class AppError extends Error {
    constructor(message, code, statusCode = 500) {
        super(message);
        this.name       = this.constructor.name;
        this.code       = code;
        this.statusCode = statusCode;
        if (Error.captureStackTrace) Error.captureStackTrace(this, this.constructor);
    }
}

class ValidationError extends AppError {
    #fields;
    constructor(message, fields = {}) {
        super(message, "VALIDATION_ERROR", 400);
        this.#fields = fields;
    }
    get fields() { return this.#fields; }
}

class NotFoundError extends AppError {
    constructor(resource, id) {
        super(`${resource} with id ${id} not found`, "NOT_FOUND", 404);
        this.resource = resource;
    }
}

class AuthError extends AppError {
    constructor(message = "Unauthorised") {
        super(message, "UNAUTHORISED", 401);
    }
}

// ── Using custom errors ──────────────────────────────────────────
async function getUser(id) {
    if (typeof id !== "number") throw new ValidationError("Invalid ID type", { id: "Must be number" });
    if (id <= 0) throw new ValidationError("ID out of range", { id: "Must be > 0" });

    const user = await fetchUser(id);
    if (!user) throw new NotFoundError("User", id);
    return user;
}

// ── Error boundary pattern ────────────────────────────────────────
async function safeExecute(fn, fallback = null) {
    try {
        return { data: await fn(), error: null };
    } catch (err) {
        return { data: fallback, error: err };
    }
}

const { data, error } = await safeExecute(() => getUser(1));
if (error) {
    if (error instanceof ValidationError) console.log("Validation:", error.fields);
    else if (error instanceof NotFoundError) console.log("Not found:", error.resource);
    else console.log("Unknown error:", error.message);
}
```

---

# PART 4 — Modern JavaScript (ES6–ES2024)

---

## 19. Modules — import / export

```javascript
// ── math.js ──────────────────────────────────────────────────────
// Named exports
export const PI = 3.14159;
export const E  = 2.71828;

export function add(a, b)      { return a + b; }
export function subtract(a, b) { return a - b; }
export function multiply(a, b) { return a * b; }
export function divide(a, b) {
    if (b === 0) throw new Error("Division by zero");
    return a / b;
}

// Default export (one per file)
export default class Calculator {
    #history = [];

    compute(a, op, b) {
        const result = { add, subtract, multiply, divide }[op]?.(a, b);
        if (result === undefined) throw new Error(`Unknown operator: ${op}`);
        this.#history.push({ a, op, b, result });
        return result;
    }

    get history() { return [...this.#history]; }
}

// ── main.js ──────────────────────────────────────────────────────
import Calculator, { add, PI, E } from "./math.js";      // Default + named
import * as MathUtils from "./math.js";                   // Namespace import
import { multiply as times } from "./math.js";            // Rename

const calc = new Calculator();
console.log(calc.compute(10, "add", 5));       // 15
console.log(calc.compute(10, "multiply", 3));  // 30

console.log(MathUtils.PI);      // 3.14159
console.log(times(3, 4));       // 12

// Dynamic import (lazy loading)
async function loadModule() {
    const { add } = await import("./math.js");
    console.log(add(2, 3));
}
```

---

## 20. Iterators & Generators

```javascript
// ── Custom Iterator ──────────────────────────────────────────────
class Range {
    constructor(start, end, step = 1) {
        this.start = start;
        this.end   = end;
        this.step  = step;
    }

    [Symbol.iterator]() {
        let current = this.start;
        return {
            next: () => {
                if (current <= this.end) {
                    const value = current;
                    current += this.step;
                    return { value, done: false };
                }
                return { value: undefined, done: true };
            }
        };
    }
}

const range = new Range(1, 10, 2);
for (const n of range) process.stdout.write(n + " ");  // 1 3 5 7 9
console.log([...range]);    // [1, 3, 5, 7, 9]

// ── Generators ───────────────────────────────────────────────────
function* fibonacci() {
    let [a, b] = [0, 1];
    while (true) {
        yield a;
        [a, b] = [b, a + b];
    }
}

function take(iterable, n) {
    const result = [];
    for (const item of iterable) {
        result.push(item);
        if (result.length === n) break;
    }
    return result;
}

const fib = fibonacci();
console.log(take(fib, 10));   // [0, 1, 1, 2, 3, 5, 8, 13, 21, 34]

// Async generator
async function* streamPages(url, pages = 3) {
    for (let page = 1; page <= pages; page++) {
        const response = await fetch(`${url}?page=${page}`);
        const data     = await response.json();
        yield data;
    }
}

(async () => {
    for await (const page of streamPages("/api/users")) {
        console.log("Page:", page);
    }
})();
```

---

# PART 5 — JavaScript in the Browser (Frontend)

---

## 23. DOM Manipulation

```javascript
// ── SELECTING ELEMENTS ────────────────────────────────────────────
const byId     = document.getElementById("app");
const first    = document.querySelector(".card");        // First match
const all      = document.querySelectorAll(".card");     // NodeList
const allCards = [...document.querySelectorAll(".card")];// Convert to array

// ── CREATING & INSERTING ──────────────────────────────────────────
function createCard({ title, body, id }) {
    const card = document.createElement("div");
    card.className = "card";
    card.dataset.id = id;

    card.innerHTML = `
        <h3 class="card__title">${title}</h3>
        <p class="card__body">${body}</p>
        <button class="card__btn" data-action="delete">Delete</button>
    `;
    return card;
}

const container = document.querySelector("#container");
const card = createCard({ title: "Hello", body: "World", id: 1 });
container.appendChild(card);

// insertAdjacentHTML — more efficient than innerHTML for appending
container.insertAdjacentHTML("beforeend", `<div class="card">New Card</div>`);

// ── MODIFYING ─────────────────────────────────────────────────────
const el = document.querySelector(".card");

el.textContent  = "Safe text (no XSS)";
el.innerHTML    = "<strong>HTML content</strong>";
el.className    = "card card--active";
el.classList.add("highlight");
el.classList.remove("highlight");
el.classList.toggle("active");
el.classList.replace("old-class", "new-class");
el.classList.contains("active");   // boolean

el.setAttribute("data-id", "42");
el.getAttribute("data-id");        // "42"
el.removeAttribute("disabled");

el.style.color     = "red";
el.style.fontSize  = "16px";
el.style.cssText   = "color: red; font-size: 16px;";  // Multiple at once

// ── TRAVERSAL ────────────────────────────────────────────────────
el.parentElement;
el.children;             // HTMLCollection
el.firstElementChild;
el.lastElementChild;
el.nextElementSibling;
el.previousElementSibling;
el.closest(".container");   // Walk up DOM tree
```

---

## 24. Events & Event Delegation

```javascript
// ── ADDING EVENTS ─────────────────────────────────────────────────
const btn = document.querySelector("#btn");

btn.addEventListener("click", function(event) {
    console.log("Clicked!", event.target);
    event.preventDefault();    // Prevent default browser action
    event.stopPropagation();   // Stop bubbling
});

// ── EVENT DELEGATION — attach ONE listener to parent ─────────────
// Instead of adding listeners to each child (expensive!)
document.querySelector("#list").addEventListener("click", function(event) {
    const item   = event.target.closest("li");
    const action = event.target.dataset.action;

    if (!item) return;

    switch (action) {
        case "delete":
            item.remove();
            break;
        case "edit":
            item.contentEditable = true;
            item.focus();
            break;
        case "toggle":
            item.classList.toggle("done");
            break;
    }
});

// ── COMMON EVENT TYPES ────────────────────────────────────────────
// Mouse events
el.addEventListener("click",      e => {});
el.addEventListener("dblclick",   e => {});
el.addEventListener("mouseenter", e => {});
el.addEventListener("mouseleave", e => {});
el.addEventListener("mousemove",  e => { console.log(e.clientX, e.clientY); });

// Keyboard events
document.addEventListener("keydown", e => {
    if (e.key === "Enter" && e.ctrlKey) submitForm();
    if (e.key === "Escape") closeModal();
    console.log(e.key, e.code, e.ctrlKey, e.shiftKey);
});

// Form events
const form = document.querySelector("form");
form.addEventListener("submit", async e => {
    e.preventDefault();
    const data = Object.fromEntries(new FormData(form));
    console.log(data);
});

const input = document.querySelector("input");
input.addEventListener("input",  e => console.log(e.target.value));   // Every keystroke
input.addEventListener("change", e => console.log(e.target.value));   // On blur
input.addEventListener("focus",  e => {});
input.addEventListener("blur",   e => {});

// ── CUSTOM EVENTS ─────────────────────────────────────────────────
const event = new CustomEvent("user:login", {
    detail: { userId: 1, name: "Alice" },
    bubbles: true
});
document.dispatchEvent(event);

document.addEventListener("user:login", e => {
    console.log("User logged in:", e.detail);
});
```

---

## 25. Fetch API & REST Calls

```javascript
// ── Basic Fetch ──────────────────────────────────────────────────
async function getUsers() {
    const response = await fetch("https://jsonplaceholder.typicode.com/users");
    if (!response.ok) throw new Error(`HTTP ${response.status}`);
    return response.json();
}

// ── HTTP Client Class ────────────────────────────────────────────
class HttpClient {
    #baseURL;
    #headers;

    constructor(baseURL, defaultHeaders = {}) {
        this.#baseURL  = baseURL.replace(/\/$/, "");
        this.#headers  = {
            "Content-Type": "application/json",
            ...defaultHeaders
        };
    }

    setAuthToken(token) {
        this.#headers["Authorization"] = `Bearer ${token}`;
        return this;
    }

    async #request(method, path, body = null, options = {}) {
        const url = `${this.#baseURL}${path}`;
        const config = {
            method,
            headers: { ...this.#headers, ...options.headers },
            signal: options.signal,
        };
        if (body) config.body = JSON.stringify(body);

        const response = await fetch(url, config);

        if (!response.ok) {
            const error = await response.json().catch(() => ({}));
            throw Object.assign(new Error(error.message || `HTTP ${response.status}`), {
                status: response.status,
                data:   error
            });
        }

        if (response.status === 204) return null;  // No Content
        return response.json();
    }

    get(path, options)           { return this.#request("GET",    path, null,  options); }
    post(path, body, options)    { return this.#request("POST",   path, body,  options); }
    put(path, body, options)     { return this.#request("PUT",    path, body,  options); }
    patch(path, body, options)   { return this.#request("PATCH",  path, body,  options); }
    delete(path, options)        { return this.#request("DELETE", path, null,  options); }
}

// Usage
const api = new HttpClient("https://api.example.com");
api.setAuthToken("my-jwt-token");

const users    = await api.get("/users");
const newUser  = await api.post("/users", { name: "Alice", email: "alice@example.com" });
const updated  = await api.patch(`/users/${newUser.id}`, { name: "Alice Smith" });
await api.delete(`/users/${newUser.id}`);

// ── Abort Controller (cancel requests) ────────────────────────────
function createCancellable(requestFn) {
    const controller = new AbortController();
    const promise    = requestFn(controller.signal);
    return { promise, cancel: () => controller.abort() };
}

const { promise, cancel } = createCancellable(signal =>
    api.get("/slow-endpoint", { signal })
);
setTimeout(cancel, 2000);   // Cancel after 2s
```

---

## 26. LocalStorage, SessionStorage & Cookies

```javascript
class Storage {
    static #prefix = "app_";

    static #key(k) { return `${this.#prefix}${k}`; }

    static set(key, value) {
        try {
            localStorage.setItem(this.#key(key), JSON.stringify(value));
        } catch { /* Storage full — handle gracefully */ }
    }

    static get(key, fallback = null) {
        try {
            const item = localStorage.getItem(this.#key(key));
            return item ? JSON.parse(item) : fallback;
        } catch { return fallback; }
    }

    static remove(key) { localStorage.removeItem(this.#key(key)); }
    static clear()     { localStorage.clear(); }

    // Session (cleared when tab closes)
    static setSession(key, value) {
        sessionStorage.setItem(this.#key(key), JSON.stringify(value));
    }

    static getSession(key, fallback = null) {
        const item = sessionStorage.getItem(this.#key(key));
        return item ? JSON.parse(item) : fallback;
    }
}

Storage.set("user", { name: "Alice", theme: "dark" });
console.log(Storage.get("user"));   // { name: "Alice", theme: "dark" }
```

---

# PART 6 — Node.js (Backend)

---

## 27. Node.js Core Concepts

```javascript
// Node.js runs JS outside the browser — no window/document, but has:
// process, require (CommonJS), fs, http, path, os, events, streams

// ── process ─────────────────────────────────────────────────────
console.log(process.env.NODE_ENV);   // "development" / "production"
console.log(process.argv);           // Command line args
console.log(process.cwd());          // Current working directory
process.exit(0);                     // Exit with success code

// ── path ─────────────────────────────────────────────────────────
import path from "path";
import { fileURLToPath } from "url";

const __filename = fileURLToPath(import.meta.url);
const __dirname  = path.dirname(__filename);

path.join(__dirname, "data", "file.txt");     // OS-safe path
path.resolve("./data/file.txt");              // Absolute path
path.extname("file.txt");                     // ".txt"
path.basename("path/to/file.txt");            // "file.txt"
path.dirname("path/to/file.txt");             // "path/to"
```

---

## 28. File System & Streams

```javascript
import { promises as fs } from "fs";
import { createReadStream, createWriteStream } from "fs";
import { pipeline } from "stream/promises";
import { createGzip } from "zlib";

// ── Async file operations ─────────────────────────────────────────
async function fileOps() {
    // Write
    await fs.writeFile("output.txt", "Hello, Node.js!", "utf8");

    // Append
    await fs.appendFile("output.txt", "\nMore content");

    // Read
    const content = await fs.readFile("output.txt", "utf8");
    console.log(content);

    // Read directory
    const files = await fs.readdir(".");
    console.log(files);

    // File stats
    const stats = await fs.stat("output.txt");
    console.log(stats.size, stats.mtime);

    // Delete
    await fs.unlink("output.txt");

    // Mkdir
    await fs.mkdir("data/cache", { recursive: true });
}

// ── Streams (efficient for large files) ──────────────────────────
async function compressFile(input, output) {
    await pipeline(
        createReadStream(input),
        createGzip(),
        createWriteStream(output)
    );
    console.log("Compressed!");
}

compressFile("large.txt", "large.txt.gz");
```

---

## 29. Building a REST API with Express

```javascript
// ── server.js ────────────────────────────────────────────────────
import express           from "express";
import cors              from "cors";
import helmet            from "helmet";
import morgan            from "morgan";
import { body, param, validationResult } from "express-validator";

const app = express();

// ── Middleware ────────────────────────────────────────────────────
app.use(express.json());
app.use(express.urlencoded({ extended: true }));
app.use(cors({ origin: process.env.FRONTEND_URL || "*" }));
app.use(helmet());
app.use(morgan("dev"));

// ── In-Memory DB (replace with real DB later) ─────────────────────
class UserRepository {
    #users = new Map();
    #nextId = 1;

    create(data) {
        const user = { id: this.#nextId++, ...data, createdAt: new Date() };
        this.#users.set(user.id, user);
        return user;
    }

    findAll()     { return [...this.#users.values()]; }
    findById(id)  { return this.#users.get(id) ?? null; }
    findByEmail(email) {
        return [...this.#users.values()].find(u => u.email === email) ?? null;
    }

    update(id, data) {
        const user = this.findById(id);
        if (!user) return null;
        const updated = { ...user, ...data, updatedAt: new Date() };
        this.#users.set(id, updated);
        return updated;
    }

    delete(id) {
        const exists = this.#users.has(id);
        this.#users.delete(id);
        return exists;
    }
}

const userRepo = new UserRepository();

// ── Controller ────────────────────────────────────────────────────
class UserController {
    constructor(repo) {
        this.repo = repo;
        // Bind methods for use as route handlers
        this.getAll   = this.getAll.bind(this);
        this.getById  = this.getById.bind(this);
        this.create   = this.create.bind(this);
        this.update   = this.update.bind(this);
        this.remove   = this.remove.bind(this);
    }

    getAll(req, res) {
        const { page = 1, limit = 10, search } = req.query;
        let users = this.repo.findAll();
        if (search) users = users.filter(u =>
            u.name.toLowerCase().includes(search.toLowerCase())
        );
        const start  = (page - 1) * limit;
        const paged  = users.slice(start, start + Number(limit));
        res.json({
            data:  paged,
            total: users.length,
            page:  Number(page),
            pages: Math.ceil(users.length / limit)
        });
    }

    getById(req, res) {
        const user = this.repo.findById(Number(req.params.id));
        if (!user) return res.status(404).json({ error: "User not found" });
        res.json(user);
    }

    create(req, res) {
        const errors = validationResult(req);
        if (!errors.isEmpty()) return res.status(400).json({ errors: errors.array() });

        if (this.repo.findByEmail(req.body.email)) {
            return res.status(409).json({ error: "Email already exists" });
        }
        const user = this.repo.create(req.body);
        res.status(201).json(user);
    }

    update(req, res) {
        const errors = validationResult(req);
        if (!errors.isEmpty()) return res.status(400).json({ errors: errors.array() });

        const updated = this.repo.update(Number(req.params.id), req.body);
        if (!updated) return res.status(404).json({ error: "User not found" });
        res.json(updated);
    }

    remove(req, res) {
        const deleted = this.repo.delete(Number(req.params.id));
        if (!deleted) return res.status(404).json({ error: "User not found" });
        res.status(204).send();
    }
}

// ── Validation Middleware ─────────────────────────────────────────
const validateUser = [
    body("name").trim().notEmpty().withMessage("Name is required")
                .isLength({ min: 2 }).withMessage("Name too short"),
    body("email").isEmail().normalizeEmail().withMessage("Invalid email"),
    body("age").optional().isInt({ min: 0, max: 150 }).withMessage("Invalid age"),
];

// ── Router ────────────────────────────────────────────────────────
const userController = new UserController(userRepo);
const router         = express.Router();

router.get("/",            userController.getAll);
router.get("/:id",         param("id").isInt(), userController.getById);
router.post("/",           validateUser, userController.create);
router.put("/:id",         validateUser, userController.update);
router.patch("/:id",       userController.update);
router.delete("/:id",      param("id").isInt(), userController.remove);

app.use("/api/users", router);

// ── Error Handler ─────────────────────────────────────────────────
app.use((err, req, res, next) => {
    console.error(err.stack);
    res.status(err.statusCode ?? 500).json({
        error: err.message,
        ...(process.env.NODE_ENV === "development" && { stack: err.stack })
    });
});

app.listen(3000, () => console.log("🚀 Server on http://localhost:3000"));
```

---

## 30. Middleware, Auth & JWT

```javascript
import jwt    from "jsonwebtoken";
import bcrypt from "bcryptjs";

const JWT_SECRET  = process.env.JWT_SECRET || "dev-secret-change-in-prod";
const JWT_EXPIRES = "7d";

// ── Auth Utilities ────────────────────────────────────────────────
const AuthUtils = {
    async hashPassword(password) {
        return bcrypt.hash(password, 12);
    },
    async comparePassword(password, hash) {
        return bcrypt.compare(password, hash);
    },
    signToken(payload) {
        return jwt.sign(payload, JWT_SECRET, { expiresIn: JWT_EXPIRES });
    },
    verifyToken(token) {
        return jwt.verify(token, JWT_SECRET);
    }
};

// ── Auth Middleware ───────────────────────────────────────────────
function authenticate(req, res, next) {
    const header = req.headers.authorization;
    if (!header?.startsWith("Bearer ")) {
        return res.status(401).json({ error: "No token provided" });
    }
    try {
        const token   = header.split(" ")[1];
        req.user      = AuthUtils.verifyToken(token);
        next();
    } catch {
        res.status(401).json({ error: "Invalid or expired token" });
    }
}

function authorise(...roles) {
    return (req, res, next) => {
        if (!roles.includes(req.user.role)) {
            return res.status(403).json({ error: "Forbidden" });
        }
        next();
    };
}

// Rate limiting middleware
function rateLimit({ windowMs = 60000, max = 100 } = {}) {
    const requests = new Map();

    return (req, res, next) => {
        const ip  = req.ip;
        const now = Date.now();

        if (!requests.has(ip)) requests.set(ip, []);
        const log = requests.get(ip).filter(t => now - t < windowMs);
        log.push(now);
        requests.set(ip, log);

        res.setHeader("X-RateLimit-Limit",     max);
        res.setHeader("X-RateLimit-Remaining", Math.max(0, max - log.length));

        if (log.length > max) {
            return res.status(429).json({ error: "Too many requests" });
        }
        next();
    };
}

// ── Auth Routes ───────────────────────────────────────────────────
const authRouter = express.Router();

authRouter.post("/register", async (req, res) => {
    const { name, email, password } = req.body;
    // ... validate, check existing, hash, save
    const hash = await AuthUtils.hashPassword(password);
    const user = userRepo.create({ name, email, password: hash, role: "user" });
    const token = AuthUtils.signToken({ id: user.id, email, role: user.role });
    res.status(201).json({ token, user: { id: user.id, name, email } });
});

authRouter.post("/login", async (req, res) => {
    const { email, password } = req.body;
    const user = userRepo.findByEmail(email);
    if (!user) return res.status(401).json({ error: "Invalid credentials" });

    const valid = await AuthUtils.comparePassword(password, user.password);
    if (!valid) return res.status(401).json({ error: "Invalid credentials" });

    const token = AuthUtils.signToken({ id: user.id, email, role: user.role });
    res.json({ token, user: { id: user.id, name: user.name, email } });
});

// Protected route
authRouter.get("/me", authenticate, (req, res) => {
    const user = userRepo.findById(req.user.id);
    res.json(user);
});

app.use("/api/auth", rateLimit({ windowMs: 60000, max: 10 }), authRouter);

// Protected API example
app.get("/api/admin", authenticate, authorise("admin"), (req, res) => {
    res.json({ message: "Admin only data" });
});
```

---

## 31. Working with Databases (MongoDB & SQL)

```javascript
// ── Repository Pattern (Database-Agnostic) ────────────────────────

// Abstract repository interface
class Repository {
    create(data)       { throw new Error("Not implemented"); }
    findAll(query)     { throw new Error("Not implemented"); }
    findById(id)       { throw new Error("Not implemented"); }
    update(id, data)   { throw new Error("Not implemented"); }
    delete(id)         { throw new Error("Not implemented"); }
}

// MongoDB implementation
import { MongoClient, ObjectId } from "mongodb";

class MongoUserRepository extends Repository {
    #collection;

    constructor(db) {
        super();
        this.#collection = db.collection("users");
    }

    async create(data) {
        const result = await this.#collection.insertOne({
            ...data,
            createdAt: new Date()
        });
        return this.findById(result.insertedId.toString());
    }

    async findAll({ search, page = 1, limit = 10 } = {}) {
        const filter = search
            ? { $or: [{ name: /search/i }, { email: /search/i }] }
            : {};
        const skip = (page - 1) * limit;
        return this.#collection.find(filter).skip(skip).limit(limit).toArray();
    }

    async findById(id) {
        return this.#collection.findOne({ _id: new ObjectId(id) });
    }

    async update(id, data) {
        const result = await this.#collection.findOneAndUpdate(
            { _id: new ObjectId(id) },
            { $set: { ...data, updatedAt: new Date() } },
            { returnDocument: "after" }
        );
        return result.value;
    }

    async delete(id) {
        const result = await this.#collection.deleteOne({ _id: new ObjectId(id) });
        return result.deletedCount > 0;
    }
}

// ── Service Layer (business logic) ───────────────────────────────
class UserService {
    #repo;

    constructor(userRepository) {
        this.#repo = userRepository;
    }

    async createUser({ name, email, password, role = "user" }) {
        const existing = await this.#repo.findByEmail(email);
        if (existing) throw new Error("Email already registered");

        const hashed = await AuthUtils.hashPassword(password);
        return this.#repo.create({ name, email, password: hashed, role });
    }

    async getUsers(query) { return this.#repo.findAll(query); }
    async getUserById(id) {
        const user = await this.#repo.findById(id);
        if (!user) throw new NotFoundError("User", id);
        return user;
    }

    async updateUser(id, data) {
        await this.getUserById(id);   // Verify exists
        return this.#repo.update(id, data);
    }

    async deleteUser(id) {
        await this.getUserById(id);
        return this.#repo.delete(id);
    }
}
```

---

# PART 7 — Real-World Projects

---

## 32. Project: OOP Task Manager (Frontend)

```javascript
// ── models/Task.js ─────────────────────────────────────────────────
class Task {
    static #nextId = 1;

    #id;
    #title;
    #description;
    #done;
    #priority;
    #tags;
    #createdAt;
    #dueDate;

    constructor({ title, description = "", priority = "medium", tags = [], dueDate = null }) {
        if (!title?.trim()) throw new TypeError("Task title is required");

        this.#id          = Task.#nextId++;
        this.#title       = title.trim();
        this.#description = description;
        this.#done        = false;
        this.#priority    = priority;
        this.#tags        = [...tags];
        this.#createdAt   = new Date();
        this.#dueDate     = dueDate ? new Date(dueDate) : null;
    }

    get id()          { return this.#id; }
    get title()       { return this.#title; }
    get description() { return this.#description; }
    get done()        { return this.#done; }
    get priority()    { return this.#priority; }
    get tags()        { return [...this.#tags]; }
    get createdAt()   { return this.#createdAt; }
    get dueDate()     { return this.#dueDate; }
    get isOverdue()   { return this.#dueDate && !this.#done && new Date() > this.#dueDate; }

    toggle() {
        this.#done = !this.#done;
        return this;
    }

    update({ title, description, priority, dueDate }) {
        if (title)       this.#title       = title.trim();
        if (description !== undefined) this.#description = description;
        if (priority)    this.#priority    = priority;
        if (dueDate !== undefined) this.#dueDate = dueDate ? new Date(dueDate) : null;
        return this;
    }

    addTag(tag) {
        if (!this.#tags.includes(tag)) this.#tags.push(tag);
        return this;
    }

    toJSON() {
        return {
            id: this.#id, title: this.#title, description: this.#description,
            done: this.#done, priority: this.#priority, tags: this.#tags,
            createdAt: this.#createdAt, dueDate: this.#dueDate, isOverdue: this.isOverdue
        };
    }
}

// ── store/TaskStore.js ─────────────────────────────────────────────
class TaskStore extends EventEmitter {
    #tasks = new Map();

    #save() {
        localStorage.setItem("tasks", JSON.stringify([...this.#tasks.values()].map(t => t.toJSON())));
    }

    add(data) {
        const task = new Task(data);
        this.#tasks.set(task.id, task);
        this.#save();
        this.emit("add", task);
        return task;
    }

    toggle(id) {
        const task = this.#tasks.get(id);
        if (!task) throw new Error(`Task ${id} not found`);
        task.toggle();
        this.#save();
        this.emit("update", task);
        return task;
    }

    remove(id) {
        const task = this.#tasks.get(id);
        if (!task) throw new Error(`Task ${id} not found`);
        this.#tasks.delete(id);
        this.#save();
        this.emit("remove", id);
    }

    getAll({ filter = "all", priority, search } = {}) {
        let tasks = [...this.#tasks.values()];

        if (filter === "active")    tasks = tasks.filter(t => !t.done);
        if (filter === "done")      tasks = tasks.filter(t => t.done);
        if (filter === "overdue")   tasks = tasks.filter(t => t.isOverdue);
        if (priority)               tasks = tasks.filter(t => t.priority === priority);
        if (search) {
            const q = search.toLowerCase();
            tasks = tasks.filter(t =>
                t.title.toLowerCase().includes(q) ||
                t.tags.some(tag => tag.toLowerCase().includes(q))
            );
        }

        return tasks.sort((a, b) => {
            const order = { high: 0, medium: 1, low: 2 };
            return order[a.priority] - order[b.priority];
        });
    }

    get stats() {
        const all     = [...this.#tasks.values()];
        const total   = all.length;
        const done    = all.filter(t => t.done).length;
        const overdue = all.filter(t => t.isOverdue).length;
        return { total, done, pending: total - done, overdue };
    }
}

// ── ui/TaskUI.js ───────────────────────────────────────────────────
class TaskUI {
    #store;
    #currentFilter = "all";

    constructor(store) {
        this.#store = store;
        this.#init();
    }

    #init() {
        this.#store.on("add",    () => this.#render());
        this.#store.on("update", () => this.#render());
        this.#store.on("remove", () => this.#render());
        this.#bindEvents();
        this.#render();
    }

    #bindEvents() {
        document.querySelector("#task-form").addEventListener("submit", e => {
            e.preventDefault();
            const data = Object.fromEntries(new FormData(e.target));
            this.#store.add(data);
            e.target.reset();
        });

        document.querySelector("#filter-bar").addEventListener("click", e => {
            const btn = e.target.closest("[data-filter]");
            if (!btn) return;
            this.#currentFilter = btn.dataset.filter;
            this.#render();
        });

        document.querySelector("#task-list").addEventListener("click", e => {
            const id = Number(e.target.closest("[data-id]")?.dataset.id);
            if (!id) return;

            if (e.target.closest(".task__toggle")) this.#store.toggle(id);
            if (e.target.closest(".task__delete")) this.#store.remove(id);
        });
    }

    #render() {
        const tasks    = this.#store.getAll({ filter: this.#currentFilter });
        const stats    = this.#store.stats;
        const list     = document.querySelector("#task-list");
        const statEl   = document.querySelector("#stats");

        statEl.textContent = `Total: ${stats.total} | Done: ${stats.done} | Pending: ${stats.pending} | Overdue: ${stats.overdue}`;

        if (!tasks.length) {
            list.innerHTML = `<li class="empty">No tasks found.</li>`;
            return;
        }

        list.innerHTML = tasks.map(task => `
            <li class="task task--${task.priority} ${task.done ? "task--done" : ""} ${task.isOverdue ? "task--overdue" : ""}"
                data-id="${task.id}">
                <button class="task__toggle" aria-label="Toggle">
                    ${task.done ? "✅" : "⬜"}
                </button>
                <div class="task__content">
                    <span class="task__title">${task.title}</span>
                    ${task.tags.map(t => `<span class="task__tag">#${t}</span>`).join("")}
                    ${task.isOverdue ? `<span class="task__overdue">⚠️ Overdue</span>` : ""}
                </div>
                <button class="task__delete" aria-label="Delete">🗑</button>
            </li>
        `).join("");
    }
}

// ── main.js ───────────────────────────────────────────────────────
const store = new TaskStore();
const ui    = new TaskUI(store);

// Seed some tasks
store.add({ title: "Learn JavaScript OOP",  priority: "high",   tags: ["js", "study"] });
store.add({ title: "Build REST API",         priority: "high",   tags: ["node", "backend"] });
store.add({ title: "Write unit tests",       priority: "medium", tags: ["testing"] });
store.add({ title: "Deploy to production",   priority: "low",    tags: ["devops"] });
```

---

## 33. Project: REST API with OOP Architecture (Backend)

```javascript
// ── Complete Express API with OOP Architecture ─────────────────────

// app/config/index.js
export const config = {
    port:     process.env.PORT     || 3000,
    nodeEnv:  process.env.NODE_ENV || "development",
    jwtSecret: process.env.JWT_SECRET || "change-me",
    db: {
        url:  process.env.DATABASE_URL || "mongodb://localhost:27017/myapp"
    }
};

// app/errors/index.js
export class HttpError extends Error {
    constructor(message, statusCode = 500, code = "INTERNAL_ERROR") {
        super(message);
        this.statusCode = statusCode;
        this.code       = code;
        this.name       = this.constructor.name;
    }
}
export class BadRequest  extends HttpError { constructor(m, c) { super(m, 400, c || "BAD_REQUEST"); } }
export class Unauthorised extends HttpError { constructor(m) { super(m || "Unauthorised", 401, "UNAUTHORISED"); } }
export class Forbidden   extends HttpError { constructor(m) { super(m || "Forbidden", 403, "FORBIDDEN"); } }
export class NotFound    extends HttpError { constructor(r) { super(`${r} not found`, 404, "NOT_FOUND"); } }
export class Conflict    extends HttpError { constructor(m) { super(m, 409, "CONFLICT"); } }

// app/middleware/index.js
export const asyncHandler = fn => (req, res, next) =>
    Promise.resolve(fn(req, res, next)).catch(next);

export const errorHandler = (err, req, res, next) => {
    const status = err.statusCode || 500;
    const response = {
        error:   err.message,
        code:    err.code || "INTERNAL_ERROR",
    };
    if (config.nodeEnv === "development") response.stack = err.stack;
    res.status(status).json(response);
};

export const notFoundHandler = (req, res) => {
    res.status(404).json({ error: `Route ${req.method} ${req.path} not found` });
};

// app/routes/users.js
import { Router }       from "express";
import { asyncHandler } from "../middleware/index.js";
import { authenticate, authorise } from "../middleware/auth.js";

export function createUserRouter(userService) {
    const router = Router();

    router.get("/", asyncHandler(async (req, res) => {
        const users = await userService.getUsers(req.query);
        res.json(users);
    }));

    router.get("/:id", asyncHandler(async (req, res) => {
        const user = await userService.getUserById(req.params.id);
        res.json(user);
    }));

    router.post("/", asyncHandler(async (req, res) => {
        const user = await userService.createUser(req.body);
        res.status(201).json(user);
    }));

    router.put("/:id", authenticate, asyncHandler(async (req, res) => {
        const user = await userService.updateUser(req.params.id, req.body);
        res.json(user);
    }));

    router.delete("/:id", authenticate, authorise("admin"), asyncHandler(async (req, res) => {
        await userService.deleteUser(req.params.id);
        res.status(204).send();
    }));

    return router;
}

// app/app.js
import express from "express";
import cors    from "cors";
import helmet  from "helmet";
import morgan  from "morgan";
import { createUserRouter }  from "./routes/users.js";
import { createAuthRouter }  from "./routes/auth.js";
import { UserService }       from "./services/UserService.js";
import { InMemoryUserRepo }  from "./repositories/InMemoryUserRepo.js";
import { errorHandler, notFoundHandler } from "./middleware/index.js";

export function createApp() {
    const app  = express();

    // DI: wire up dependencies
    const userRepo    = new InMemoryUserRepo();
    const userService = new UserService(userRepo);

    // Middleware
    app.use(express.json());
    app.use(cors());
    app.use(helmet());
    app.use(morgan("dev"));

    // Routes
    app.use("/api/auth",  createAuthRouter(userService));
    app.use("/api/users", createUserRouter(userService));

    // Health check
    app.get("/health", (req, res) => res.json({
        status: "ok",
        env:    config.nodeEnv,
        uptime: process.uptime()
    }));

    // 404 & error handlers (must be last)
    app.use(notFoundHandler);
    app.use(errorHandler);

    return app;
}

// server.js
import { createApp } from "./app/app.js";
import { config }    from "./app/config/index.js";

const app = createApp();
app.listen(config.port, () => {
    console.log(`🚀 Server running on http://localhost:${config.port}`);
    console.log(`📝 Environment: ${config.nodeEnv}`);
});

export default app;   // For testing
```

---

## Quick Reference — JavaScript Cheat Sheet

```
┌──────────────────────────────────────────────────────────────────────────────┐
│                        JAVASCRIPT CHEAT SHEET                                │
├──────────────────────┬───────────────────────────────────────────────────────┤
│ Variables            │ const > let > never var                               │
│ Types                │ number, string, boolean, null, undefined, symbol,     │
│                      │ bigint, object (includes arrays/functions)            │
│ Equality             │ Always === never ==                                   │
│ Falsy values         │ false, 0, -0, 0n, "", null, undefined, NaN           │
│ Function types       │ declaration (hoisted) | expression | arrow (lexical  │
│                      │ this) | generator | async                             │
│ Array methods        │ map, filter, reduce, find, findIndex, some, every,   │
│                      │ flat, flatMap, sort, includes                         │
│ Object utilities     │ keys, values, entries, assign, freeze, fromEntries,  │
│                      │ structuredClone                                       │
│ OOP                  │ class, extends, super, static, #private, get/set     │
│ Async                │ Promise, async/await, Promise.all, allSettled, race  │
│ Modules              │ import/export, default export, dynamic import()       │
│ Prototype chain      │ obj → Class.prototype → Object.prototype → null      │
│ this rules           │ method→obj, new→instance, call/apply/bind→explicit,  │
│                      │ arrow→lexical, global→window/undefined               │
├──────────────────────┴───────────────────────────────────────────────────────┤
│ PATTERNS: Singleton │ Observer │ Factory │ Strategy │ Module │ Repository   │
│ FRONTEND: DOM │ Events │ Fetch │ localStorage │ Custom Events               │
│ BACKEND:  Express │ Middleware │ JWT │ bcrypt │ Repository Pattern           │
│ TOOLS:    Node.js │ npm │ ESModules │ VS Code │ Postman │ Jest              │
└──────────────────────────────────────────────────────────────────────────────┘
```

---

## Resources

| Resource | Type |
|---|---|
| MDN Web Docs — javascript | Reference |
| javascript.info | Tutorial |
| You Don't Know JS (Kyle Simpson) | Book (free on GitHub) |
| Eloquent JavaScript | Book (free online) |
| Node.js Official Docs | Reference |
| Express.js Official Docs | Reference |
| Clean Code JavaScript | GitHub |

---

**Language**: JavaScript (ES2024) + Node.js 20  
**Licence**: MIT
