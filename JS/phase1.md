# JavaScript Complete Guide
### From Fundamentals to Full-Stack — Frontend, Backend & OOP

> A comprehensive, practice-first guide covering every core concept of JavaScript — variables to closures, OOP to Node.js, async to REST APIs. Every section ships with runnable code you can practise immediately.

---

## 📚 Table of Contents

| # | Topic | Level |
|---|---|---|
| **PART 1 — Core JavaScript** | | |
| 1 | [Variables, Data Types & Type Coercion](#1-variables-data-types--type-coercion) | Beginner |
| 2 | [Operators & Control Flow](#2-operators--control-flow) | Beginner |
| 3 | [Functions — All Forms](#3-functions--all-forms) | Beginner |
| 4 | [Arrays — Full Reference](#4-arrays--full-reference) | Beginner |
| 5 | [Objects — Deep Dive](#5-objects--deep-dive) | Beginner |
| 6 | [Destructuring, Spread & Rest](#6-destructuring-spread--rest) | Intermediate |
| 7 | [Scope, Closures & Hoisting](#7-scope-closures--hoisting) | Intermediate |
| 8 | [The `this` Keyword](#8-the-this-keyword) | Intermediate |
| 9 | [Prototypes & Prototype Chain](#9-prototypes--prototype-chain) | Intermediate |
| **PART 2 — Object-Oriented JavaScript** | | |
| 10 | [ES6 Classes — Complete OOP](#10-es6-classes--complete-oop) | Intermediate |
| 11 | [Inheritance & Polymorphism](#11-inheritance--polymorphism) | Intermediate |
| 12 | [Encapsulation & Private Fields](#12-encapsulation--private-fields) | Intermediate |
| 13 | [Mixins & Composition](#13-mixins--composition) | Advanced |
| 14 | [Design Patterns in JS](#14-design-patterns-in-js) | Advanced |
| **PART 3 — Async JavaScript** | | |
| 15 | [Callbacks & Callback Hell](#15-callbacks--callback-hell) | Intermediate |
| 16 | [Promises](#16-promises) | Intermediate |
| 17 | [Async / Await](#17-async--await) | Intermediate |
| 18 | [Error Handling](#18-error-handling) | Intermediate |
| **PART 4 — Modern JavaScript (ES6–ES2024)** | | |
| 19 | [Modules — import / export](#19-modules--import--export) | Intermediate |
| 20 | [Iterators & Generators](#20-iterators--generators) | Advanced |
| 21 | [Symbols, WeakMap & WeakSet](#21-symbols-weakmap--weakset) | Advanced |
| 22 | [Proxy & Reflect](#22-proxy--reflect) | Advanced |
| **PART 5 — JavaScript in the Browser (Frontend)** | | |
| 23 | [DOM Manipulation](#23-dom-manipulation) | Intermediate |
| 24 | [Events & Event Delegation](#24-events--event-delegation) | Intermediate |
| 25 | [Fetch API & REST Calls](#25-fetch-api--rest-calls) | Intermediate |
| 26 | [LocalStorage, SessionStorage & Cookies](#26-localstorage-sessionstorage--cookies) | Intermediate |
| **PART 6 — Node.js (Backend)** | | |
| 27 | [Node.js Core Concepts](#27-nodejs-core-concepts) | Intermediate |
| 28 | [File System & Streams](#28-file-system--streams) | Intermediate |
| 29 | [Building a REST API with Express](#29-building-a-rest-api-with-express) | Advanced |
| 30 | [Middleware, Auth & JWT](#30-middleware-auth--jwt) | Advanced |
| 31 | [Working with Databases (MongoDB & SQL)](#31-working-with-databases-mongodb--sql) | Advanced |
| **PART 7 — Real-World Projects** | | |
| 32 | [Project: OOP Task Manager (Frontend)](#32-project-oop-task-manager-frontend) | Advanced |
| 33 | [Project: REST API with OOP Architecture (Backend)](#33-project-rest-api-with-oop-architecture-backend) | Advanced |

---

# PART 1 — Core JavaScript

---

## 1. Variables, Data Types & Type Coercion

### 1.1 Variable Declarations

JavaScript has three ways to declare variables. Understanding the difference is critical.

```javascript
// ── var ──────────────────────────────────────────────────────────
// Function-scoped, hoisted, re-declarable — AVOID in modern code
var name = "Alice";
var name = "Bob";   // No error! Re-declaration allowed
console.log(name);  // "Bob"

// ── let ──────────────────────────────────────────────────────────
// Block-scoped, NOT hoisted (TDZ), cannot be re-declared
let age = 25;
// let age = 30;   // SyntaxError: Identifier 'age' already declared
age = 30;          // Re-assignment is fine

// ── const ────────────────────────────────────────────────────────
// Block-scoped, must be initialised, binding cannot be reassigned
const PI = 3.14159;
// PI = 3;   // TypeError: Assignment to constant variable

// ⚠️ const does NOT mean immutable for objects/arrays
const user = { name: "Alice" };
user.name = "Bob";    // ✅ This works — object properties can change
user.age  = 25;       // ✅ This works too

const nums = [1, 2, 3];
nums.push(4);   // ✅ Array contents can change
// nums = [];   // ❌ Re-assigning the binding fails
```

**Decision Rule:**
```
Always use const  →  unless you need to reassign
Use let           →  when you need to reassign
Never use var     →  in modern code
```

### 1.2 Data Types

JavaScript has **8 data types**: 7 primitives + 1 object type.

```javascript
// ── PRIMITIVE TYPES ───────────────────────────────────────────────
// Primitives are immutable values stored by value

// 1. Number  (64-bit IEEE 754 float — no separate int type)
const integer  = 42;
const float    = 3.14;
const negative = -100;
const infinity = Infinity;
const nanVal   = NaN;           // "Not a Number" — still typeof 'number'!
const bigSafe  = Number.MAX_SAFE_INTEGER;  // 9007199254740991

console.log(typeof 42);         // "number"
console.log(0.1 + 0.2);        // 0.30000000000000004 (floating point!)
console.log(0.1 + 0.2 === 0.3);// false — NEVER compare floats with ===

// 2. BigInt  (arbitrary precision integers)
const huge   = 9007199254740992n;
const bigNum = BigInt("123456789012345678901234567890");
console.log(typeof huge);       // "bigint"

// 3. String
const single  = 'Hello';
const double  = "World";
const template = `${single}, ${double}!`;   // Template literal
const multiline = `Line 1
Line 2
Line 3`;
console.log(typeof "hi");       // "string"

// 4. Boolean
const isActive = true;
const isAdmin  = false;
console.log(typeof true);       // "boolean"

// 5. undefined  (declared but not assigned)
let x;
console.log(x);                 // undefined
console.log(typeof x);         // "undefined"

// 6. null  (intentional absence of value)
let user = null;
console.log(typeof null);      // "object" ← famous JS bug, but it's in the spec

// 7. Symbol  (unique, immutable identifier)
const sym1 = Symbol("id");
const sym2 = Symbol("id");
console.log(sym1 === sym2);     // false — always unique
console.log(typeof sym1);      // "symbol"

// ── OBJECT TYPE ──────────────────────────────────────────────────
// Everything else is an object (stored by reference)

const obj    = { key: "value" };
const arr    = [1, 2, 3];
const fn     = function() {};
const date   = new Date();
const regex  = /pattern/g;

console.log(typeof obj);   // "object"
console.log(typeof arr);   // "object"  (arrays ARE objects)
console.log(typeof fn);    // "function" (special case)
console.log(Array.isArray(arr));  // true — use this to detect arrays
```

### 1.3 Type Coercion — JavaScript's Wild Side

```javascript
// ── IMPLICIT COERCION ────────────────────────────────────────────
// JS automatically converts types — often unexpectedly

console.log("5" + 3);       // "53"   (number → string, + is concatenation)
console.log("5" - 3);       // 2      (string → number, - is always math)
console.log("5" * "3");     // 15     (both → number)
console.log(true + 1);      // 2      (true → 1)
console.log(false + 1);     // 1      (false → 0)
console.log(null + 1);      // 1      (null → 0)
console.log(undefined + 1); // NaN    (undefined → NaN)
console.log("" + null);     // "null" (null → "null")

// ── EQUALITY: == vs === ──────────────────────────────────────────
// == (loose equality) — performs type coercion before comparing
console.log(0  == false);    // true  (false → 0)
console.log("" == false);    // true  (both → 0)
console.log(null == undefined); // true (special rule)
console.log(1  == "1");      // true  ("1" → 1)

// === (strict equality) — NO coercion — ALWAYS use this
console.log(0   === false);  // false
console.log(1   === "1");    // false
console.log(null === undefined); // false

// ── FALSY VALUES ─────────────────────────────────────────────────
// Only these 8 values are falsy in JS:
if (!false)     console.log("false is falsy");
if (!0)         console.log("0 is falsy");
if (!-0)        console.log("-0 is falsy");
if (!0n)        console.log("0n is falsy");
if (!"")        console.log("empty string is falsy");
if (!null)      console.log("null is falsy");
if (!undefined) console.log("undefined is falsy");
if (!NaN)       console.log("NaN is falsy");
// Everything else is TRUTHY — including "0", [], {}

// ── EXPLICIT CONVERSION ──────────────────────────────────────────
console.log(Number("42"));        // 42
console.log(Number(""));          // 0
console.log(Number(null));        // 0
console.log(Number(undefined));   // NaN
console.log(Number(true));        // 1
console.log(Number("abc"));       // NaN

console.log(String(42));          // "42"
console.log(String(null));        // "null"
console.log(String(undefined));   // "undefined"
console.log(String(true));        // "true"

console.log(Boolean(0));          // false
console.log(Boolean(""));         // false
console.log(Boolean("hello"));    // true
console.log(Boolean({}));         // true  (empty object is truthy!)
console.log(Boolean([]));         // true  (empty array is truthy!)

// ── parseInt & parseFloat ────────────────────────────────────────
console.log(parseInt("42px"));     // 42  (stops at first non-numeric char)
console.log(parseInt("3.14"));     // 3   (truncates decimal)
console.log(parseFloat("3.14em")); // 3.14
console.log(parseInt("0xFF", 16)); // 255 (hexadecimal)
console.log(parseInt("abc"));      // NaN
```

### 🏋️ Practice Exercises

```javascript
// Exercise 1: Predict the output before running
console.log(typeof null);
console.log(typeof undefined);
console.log(typeof NaN);
console.log(typeof []);
console.log(typeof function(){});
console.log(null == undefined);
console.log(null === undefined);
console.log(NaN === NaN);
console.log([] == false);
console.log({} == false);

// Exercise 2: Fix the buggy comparisons
function isAdult(age) {
    return age >= 18;  // But what if age = "20"? What if age = null?
}

// Exercise 3: Safe type checking utility
function getType(value) {
    if (value === null) return "null";
    if (Array.isArray(value)) return "array";
    return typeof value;
}

console.log(getType(null));          // "null"
console.log(getType([]));            // "array"
console.log(getType({}));            // "object"
console.log(getType("hello"));       // "string"
console.log(getType(42));            // "number"
```

---

## 2. Operators & Control Flow

### 2.1 Operators

```javascript
// ── ARITHMETIC ────────────────────────────────────────────────────
console.log(10 + 3);    // 13
console.log(10 - 3);    // 7
console.log(10 * 3);    // 30
console.log(10 / 3);    // 3.3333...
console.log(10 % 3);    // 1   (remainder/modulo)
console.log(10 ** 3);   // 1000 (exponentiation)

let n = 5;
n++;    // Post-increment: use n then increment
++n;    // Pre-increment: increment then use n
n--;    // Post-decrement
--n;    // Pre-decrement

// ── ASSIGNMENT ────────────────────────────────────────────────────
let x = 10;
x += 5;    // x = x + 5  = 15
x -= 3;    // x = x - 3  = 12
x *= 2;    // x = x * 2  = 24
x /= 4;    // x = x / 4  = 6
x **= 2;   // x = x ** 2 = 36
x %= 10;   // x = x % 10 = 6

// ── LOGICAL ──────────────────────────────────────────────────────
console.log(true && true);   // true
console.log(true && false);  // false
console.log(false || true);  // true
console.log(!true);          // false

// Short-circuit evaluation
console.log(false && anything); // false  (right side never evaluated)
console.log(true  || anything); // true   (right side never evaluated)

// Practical short-circuit patterns
const username = user?.name || "Guest";      // fallback
const log = isDev && console.log;            // conditional execution
log && log("debug message");

// ── NULLISH COALESCING (??) ──────────────────────────────────────
// Returns right side only if left is null OR undefined (not 0, "", false)
const port = process.env.PORT ?? 3000;
const name = user.name ?? "Anonymous";

console.log(0    ?? "default");   // 0         (0 is not null/undefined)
console.log("")  ?? "default");   // ""        ("" is not null/undefined)
console.log(null ?? "default");   // "default"
console.log(undefined ?? "default"); // "default"

// ── OPTIONAL CHAINING (?.) ───────────────────────────────────────
// Safely access deeply nested properties
const user = { address: { city: "Delhi" } };
console.log(user?.address?.city);     // "Delhi"
console.log(user?.phone?.number);     // undefined (no error!)
console.log(user?.getName?.());       // undefined (safe method call)
console.log(user?.scores?.[0]);       // undefined (safe index access)

// ── TERNARY ──────────────────────────────────────────────────────
const status = age >= 18 ? "adult" : "minor";

// Nested ternary (use sparingly — prefer if/else for clarity)
const grade = score >= 90 ? "A"
            : score >= 80 ? "B"
            : score >= 70 ? "C"
            : "F";
```

### 2.2 Control Flow

```javascript
// ── if / else if / else ──────────────────────────────────────────
function classify(score) {
    if (score >= 90) {
        return "Excellent";
    } else if (score >= 70) {
        return "Good";
    } else if (score >= 50) {
        return "Average";
    } else {
        return "Below Average";
    }
}

// ── switch ────────────────────────────────────────────────────────
function getDayName(day) {
    switch (day) {
        case 0: return "Sunday";
        case 1: return "Monday";
        case 2: return "Tuesday";
        case 3: return "Wednesday";
        case 4: return "Thursday";
        case 5: return "Friday";
        case 6: return "Saturday";
        default: return "Invalid day";
    }
}

// Fall-through (intentional grouping)
function isWeekend(day) {
    switch (day) {
        case 0:
        case 6:
            return true;   // Both 0 and 6 fall through to here
        default:
            return false;
    }
}

// ── LOOPS ─────────────────────────────────────────────────────────

// for loop
for (let i = 0; i < 5; i++) {
    console.log(i);   // 0, 1, 2, 3, 4
}

// while loop
let count = 0;
while (count < 5) {
    console.log(count);
    count++;
}

// do...while — always executes at least once
let input;
do {
    input = prompt("Enter a number > 0:");
} while (input <= 0);

// for...of — iterate over iterables (arrays, strings, maps, sets)
const fruits = ["apple", "banana", "cherry"];
for (const fruit of fruits) {
    console.log(fruit);
}

// for...of with index using entries()
for (const [index, fruit] of fruits.entries()) {
    console.log(`${index}: ${fruit}`);
}

// for...in — iterate over object keys (use with caution)
const person = { name: "Alice", age: 25, city: "Delhi" };
for (const key in person) {
    console.log(`${key}: ${person[key]}`);
}
// ⚠️ for...in also iterates inherited properties — prefer Object.keys()

// ── LOOP CONTROL ─────────────────────────────────────────────────
for (let i = 0; i < 10; i++) {
    if (i === 3) continue;   // Skip 3
    if (i === 7) break;      // Stop at 7
    console.log(i);          // 0, 1, 2, 4, 5, 6
}

// Labelled break (for nested loops)
outer: for (let i = 0; i < 3; i++) {
    for (let j = 0; j < 3; j++) {
        if (i === 1 && j === 1) break outer;  // Breaks both loops
        console.log(i, j);
    }
}
```

---

## 3. Functions — All Forms

Functions are **first-class citizens** in JavaScript — they can be passed as arguments, returned from other functions, and assigned to variables.

### 3.1 All Ways to Define a Function

```javascript
// 1. Function Declaration
// Hoisted — can be called before it's defined in the file
function add(a, b) {
    return a + b;
}
console.log(add(2, 3));   // 5

// 2. Function Expression
// NOT hoisted — must be defined before calling
const subtract = function(a, b) {
    return a - b;
};

// Named function expression (name useful for debugging/recursion)
const factorial = function fact(n) {
    return n <= 1 ? 1 : n * fact(n - 1);
};

// 3. Arrow Function
// Concise, lexical `this` binding — no own `this`, `arguments`, `super`
const multiply = (a, b) => a * b;           // Implicit return
const square   = x => x * x;               // Single param, no parens needed
const greet    = () => "Hello!";            // No params
const divide   = (a, b) => {               // Block body — explicit return
    if (b === 0) throw new Error("Division by zero");
    return a / b;
};

// 4. IIFE (Immediately Invoked Function Expression)
// Runs immediately — classic module pattern
(function() {
    const privateVar = "I'm private";
    console.log(privateVar);
})();
// privateVar is not accessible here

// Arrow IIFE
(() => {
    console.log("Arrow IIFE");
})();
```

### 3.2 Parameters: Defaults, Rest & Destructuring

```javascript
// Default parameters
function createUser(name, role = "user", active = true) {
    return { name, role, active };
}
console.log(createUser("Alice"));             // { name: "Alice", role: "user", active: true }
console.log(createUser("Bob", "admin"));      // { name: "Bob", role: "admin", active: true }

// Rest parameters — collect remaining args into an array
function sum(...numbers) {
    return numbers.reduce((total, n) => total + n, 0);
}
console.log(sum(1, 2, 3, 4, 5));    // 15

function logAll(first, second, ...rest) {
    console.log("First:", first);
    console.log("Second:", second);
    console.log("Rest:", rest);      // Array of remaining args
}
logAll(1, 2, 3, 4, 5);

// Destructured parameters
function displayUser({ name, age, city = "Unknown" }) {
    console.log(`${name}, ${age}, ${city}`);
}
displayUser({ name: "Alice", age: 25, city: "Mumbai" });

function getFirstTwo([first, second]) {
    return [first, second];
}
console.log(getFirstTwo([10, 20, 30]));  // [10, 20]
```

### 3.3 Higher-Order Functions

```javascript
// Functions that accept functions as arguments
function applyTwice(fn, value) {
    return fn(fn(value));
}
const double = x => x * 2;
console.log(applyTwice(double, 3));   // 12  (3 → 6 → 12)

// Functions that return functions — Factory / Closure pattern
function multiplier(factor) {
    return (number) => number * factor;
}
const triple  = multiplier(3);
const times10 = multiplier(10);
console.log(triple(7));    // 21
console.log(times10(7));   // 70

// Function composition
const compose  = (...fns) => x => fns.reduceRight((v, f) => f(v), x);
const pipe     = (...fns) => x => fns.reduce((v, f) => f(v), x);

const addOne   = x => x + 1;
const doubleIt = x => x * 2;
const squareIt = x => x * x;

const transform = pipe(addOne, doubleIt, squareIt);
console.log(transform(3));   // ((3+1)*2)² = 64

// Memoization
function memoize(fn) {
    const cache = new Map();
    return function(...args) {
        const key = JSON.stringify(args);
        if (cache.has(key)) {
            console.log("Cache hit!");
            return cache.get(key);
        }
        const result = fn.apply(this, args);
        cache.set(key, result);
        return result;
    };
}

const expensiveSquare = memoize(n => {
    console.log(`Computing ${n}²`);
    return n * n;
});
expensiveSquare(5);   // Computing 25
expensiveSquare(5);   // Cache hit!
expensiveSquare(6);   // Computing 36
```

### 3.4 The `arguments` Object vs Rest

```javascript
function oldStyle() {
    console.log(arguments);          // Arguments object (array-like, NOT an array)
    console.log(Array.from(arguments));  // Convert to real array
}

// Arrow functions do NOT have their own arguments
const arrowFn = () => {
    // console.log(arguments);  // ReferenceError in strict mode
};

// Always prefer rest parameters over arguments
function modern(...args) {
    console.log(args);        // Real array — can use .map(), .filter(), etc.
    return args.reduce((a, b) => a + b, 0);
}
```

---

## 4. Arrays — Full Reference

### 4.1 Creation & Basic Operations

```javascript
// Creating arrays
const empty    = [];
const numbers  = [1, 2, 3, 4, 5];
const mixed    = [1, "hello", true, null, { name: "Alice" }];
const fromFunc = Array.from({ length: 5 }, (_, i) => i * 2); // [0, 2, 4, 6, 8]
const filled   = new Array(3).fill(0);                         // [0, 0, 0]

// Basic operations
numbers.length;          // 5
numbers[0];              // 1  (zero-indexed)
numbers[numbers.length - 1]; // 5 (last element)
numbers.at(-1);          // 5  (modern — negative indexing)
numbers.at(-2);          // 4

// Mutating methods (change original array)
const arr = [1, 2, 3];
arr.push(4);             // Append to end → [1, 2, 3, 4]  returns new length
arr.pop();               // Remove from end → [1, 2, 3]    returns removed element
arr.unshift(0);          // Prepend to start → [0, 1, 2, 3]
arr.shift();             // Remove from start → [1, 2, 3]
arr.splice(1, 1);        // Remove 1 element at index 1 → [1, 3]
arr.splice(1, 0, 2);     // Insert 2 at index 1 → [1, 2, 3]
arr.splice(1, 1, 99);    // Replace index 1 with 99 → [1, 99, 3]
arr.reverse();           // Reverse in-place → [3, 99, 1]
arr.sort();              // Sorts in-place (lexicographic by default!)
arr.fill(0, 1, 3);       // Fill [1..3) with 0
```

### 4.2 Functional Array Methods — The Power Tools

```javascript
const products = [
    { id: 1, name: "Laptop",  price: 999,  category: "electronics", inStock: true  },
    { id: 2, name: "Phone",   price: 699,  category: "electronics", inStock: true  },
    { id: 3, name: "Desk",    price: 299,  category: "furniture",   inStock: false },
    { id: 4, name: "Chair",   price: 199,  category: "furniture",   inStock: true  },
    { id: 5, name: "Monitor", price: 399,  category: "electronics", inStock: true  },
];

// ── map() — transform every element, returns new array ────────────
const names  = products.map(p => p.name);
// ["Laptop", "Phone", "Desk", "Chair", "Monitor"]

const pricesWithTax = products.map(p => ({
    ...p,
    priceWithTax: +(p.price * 1.18).toFixed(2)
}));

// ── filter() — keep elements matching condition ───────────────────
const inStock    = products.filter(p => p.inStock);
const affordable = products.filter(p => p.price < 500);
const electronics = products.filter(p => p.category === "electronics");

// Chain them
const affordableElectronics = products
    .filter(p => p.category === "electronics")
    .filter(p => p.price < 800);

// ── reduce() — accumulate to a single value ───────────────────────
const totalValue = products.reduce((sum, p) => sum + p.price, 0);
// 2595

const byCategory = products.reduce((groups, product) => {
    const key = product.category;
    if (!groups[key]) groups[key] = [];
    groups[key].push(product);
    return groups;
}, {});
// { electronics: [...], furniture: [...] }

const maxPrice = products.reduce((max, p) => p.price > max ? p.price : max, 0);

// ── find() & findIndex() — locate first match ─────────────────────
const laptop  = products.find(p => p.name === "Laptop");       // object or undefined
const laptopI = products.findIndex(p => p.name === "Laptop");  // index or -1

// ── some() & every() — boolean checks ────────────────────────────
const anyOutOfStock  = products.some(p => !p.inStock);    // true
const allInStock     = products.every(p => p.inStock);    // false
const allHaveId      = products.every(p => p.id != null); // true

// ── flat() & flatMap() ─────────────────────────────────────────────
const nested = [1, [2, 3], [4, [5, 6]]];
console.log(nested.flat());     // [1, 2, 3, 4, [5, 6]]
console.log(nested.flat(2));    // [1, 2, 3, 4, 5, 6]
console.log(nested.flat(Infinity)); // fully flatten

const sentences = ["Hello World", "Foo Bar"];
const words = sentences.flatMap(s => s.split(" "));
// ["Hello", "World", "Foo", "Bar"]

// ── sort() — custom comparator ────────────────────────────────────
const byPriceAsc  = [...products].sort((a, b) => a.price - b.price);
const byPriceDesc = [...products].sort((a, b) => b.price - a.price);
const byName      = [...products].sort((a, b) => a.name.localeCompare(b.name));

// ── includes() & indexOf() ───────────────────────────────────────
const nums = [1, 2, 3, 4, 5];
nums.includes(3);         // true
nums.indexOf(3);          // 2
nums.lastIndexOf(3);      // 2

// ── Array.from() & Array.of() ─────────────────────────────────────
Array.from("Hello");                // ["H", "e", "l", "l", "o"]
Array.from({length: 3}, (_, i) => i + 1);  // [1, 2, 3]
Array.from(new Set([1, 1, 2, 2, 3]));      // [1, 2, 3]
Array.of(1, 2, 3);                  // [1, 2, 3]

// ── Spread vs concat ────────────────────────────────────────────
const a = [1, 2, 3];
const b = [4, 5, 6];
const combined1 = [...a, ...b];         // [1, 2, 3, 4, 5, 6]
const combined2 = a.concat(b);         // Same result

// ── Practical Pattern: Immutable array operations ────────────────
const todos = [
    { id: 1, text: "Learn JS",   done: false },
    { id: 2, text: "Build app",  done: false },
    { id: 3, text: "Deploy",     done: false },
];

// Add item (immutable)
const added = [...todos, { id: 4, text: "Test", done: false }];

// Remove item (immutable)
const removed = todos.filter(t => t.id !== 2);

// Update item (immutable)
const updated = todos.map(t => t.id === 1 ? { ...t, done: true } : t);
```

---

## 5. Objects — Deep Dive

### 5.1 Creating & Accessing Objects

```javascript
// Object literal
const person = {
    firstName: "Alice",
    lastName:  "Johnson",
    age:       28,
    address: {
        city:    "Mumbai",
        country: "India"
    },

    // Method shorthand (ES6)
    getFullName() {
        return `${this.firstName} ${this.lastName}`;
    },

    // Computed property key
    ["key_" + Math.random().toFixed(4)]: "dynamic key"
};

// Access
console.log(person.firstName);           // Dot notation
console.log(person["lastName"]);         // Bracket notation (dynamic keys)
console.log(person.address.city);        // Nested access
console.log(person.getFullName());       // Method call
console.log(person.phone);              // undefined (no error)
console.log(person?.phone?.number);     // undefined (safe chain)

// Dynamic property access
const key = "firstName";
console.log(person[key]);    // "Alice"

// Modify
person.age = 29;
person["address"]["city"] = "Delhi";
person.email = "alice@example.com";  // Add new property
delete person.email;                  // Remove property

// Check property existence
console.log("firstName" in person);          // true
console.log(person.hasOwnProperty("age"));  // true (own property)
console.log("toString" in person);           // true (inherited!)
```

### 5.2 Object Methods & Utilities

```javascript
const obj = { a: 1, b: 2, c: 3 };

// Keys, values, entries
Object.keys(obj);     // ["a", "b", "c"]
Object.values(obj);   // [1, 2, 3]
Object.entries(obj);  // [["a", 1], ["b", 2], ["c", 3]]

// Iterate
for (const [key, value] of Object.entries(obj)) {
    console.log(`${key}: ${value}`);
}

// Object.assign — shallow copy / merge
const defaults = { theme: "dark", lang: "en", fontSize: 14 };
const userPrefs = { theme: "light", fontSize: 16 };
const config = Object.assign({}, defaults, userPrefs);
// { theme: "light", lang: "en", fontSize: 16 }

// Spread (modern equivalent, cleaner)
const config2 = { ...defaults, ...userPrefs };

// Object.freeze — make immutable (shallow)
const CONSTANTS = Object.freeze({ PI: 3.14159, E: 2.71828 });
CONSTANTS.PI = 99;   // Silently ignored (or TypeError in strict mode)

// Object.fromEntries — convert entries back to object
const entries = [["a", 1], ["b", 2], ["c", 3]];
const rebuilt = Object.fromEntries(entries);  // { a: 1, b: 2, c: 3 }

// Map entries to new object
const doubled = Object.fromEntries(
    Object.entries(obj).map(([k, v]) => [k, v * 2])
);  // { a: 2, b: 4, c: 6 }

// Deep clone (modern way)
const original = { a: 1, b: { c: 2 } };
const deepCopy = structuredClone(original);  // ES2022 — no library needed!
deepCopy.b.c = 99;
console.log(original.b.c);  // 2 (unaffected)
```

### 5.3 Property Descriptors & Getters/Setters

```javascript
// Property descriptors give fine-grained control
const product = {};

Object.defineProperty(product, "id", {
    value:        "PROD-001",
    writable:     false,    // Cannot change
    enumerable:   true,     // Shows in for...in and Object.keys
    configurable: false     // Cannot delete or redefine
});

// Getters and Setters
const temperature = {
    _celsius: 0,

    get fahrenheit() {
        return this._celsius * 9/5 + 32;
    },

    set fahrenheit(f) {
        this._celsius = (f - 32) * 5/9;
    },

    get celsius() {
        return this._celsius;
    },

    set celsius(c) {
        if (c < -273.15) throw new RangeError("Below absolute zero!");
        this._celsius = c;
    }
};

temperature.celsius = 100;
console.log(temperature.fahrenheit);  // 212
temperature.fahrenheit = 32;
console.log(temperature.celsius);     // 0
```

---

## 6. Destructuring, Spread & Rest

### 6.1 Array Destructuring

```javascript
// Basic
const [first, second, third] = [1, 2, 3];
console.log(first, second, third);    // 1 2 3

// Skip elements
const [a, , b] = [10, 20, 30];       // Skip 20
console.log(a, b);   // 10 30

// Default values
const [x = 0, y = 0] = [5];
console.log(x, y);   // 5 0

// Rest
const [head, ...tail] = [1, 2, 3, 4, 5];
console.log(head, tail);   // 1 [2, 3, 4, 5]

// Swap variables
let p = 1, q = 2;
[p, q] = [q, p];
console.log(p, q);   // 2 1

// Nested destructuring
const matrix = [[1, 2], [3, 4]];
const [[r1c1, r1c2], [r2c1, r2c2]] = matrix;

// From function return
function minMax(arr) {
    return [Math.min(...arr), Math.max(...arr)];
}
const [min, max] = minMax([3, 1, 4, 1, 5, 9, 2, 6]);
console.log(min, max);   // 1 9
```

### 6.2 Object Destructuring

```javascript
const user = {
    id:   1,
    name: "Alice",
    age:  28,
    address: {
        city:    "Mumbai",
        country: "India",
        zip:     "400001"
    },
    roles: ["user", "editor"]
};

// Basic
const { name, age } = user;

// Rename (alias)
const { name: userName, age: userAge } = user;
console.log(userName, userAge);   // "Alice" 28

// Default values
const { name: n, email = "N/A" } = user;
console.log(email);   // "N/A"

// Nested destructuring
const { address: { city, country } } = user;
console.log(city, country);   // "Mumbai" "India"

// Rest
const { id, ...rest } = user;
console.log(id);    // 1
console.log(rest);  // { name, age, address, roles }

// Combined with arrays
const { roles: [primaryRole, secondaryRole] } = user;
console.log(primaryRole);   // "user"

// Function parameter destructuring — very common in React/Node
function renderUser({ name, age, address: { city } = {}, role = "user" }) {
    console.log(`${name}, ${age}, ${city}, ${role}`);
}
renderUser(user);

// Destructuring in loops
const users = [
    { id: 1, name: "Alice", age: 28 },
    { id: 2, name: "Bob",   age: 32 },
];
for (const { id, name } of users) {
    console.log(`${id}: ${name}`);
}
```

### 6.3 Spread Operator

```javascript
// Array spread
const nums1 = [1, 2, 3];
const nums2 = [4, 5, 6];
const all   = [...nums1, ...nums2];        // [1, 2, 3, 4, 5, 6]
const copy  = [...nums1];                  // Shallow copy
const withExtra = [0, ...nums1, 99];       // [0, 1, 2, 3, 99]

// Object spread
const base   = { a: 1, b: 2 };
const extra  = { c: 3, d: 4 };
const merged = { ...base, ...extra };      // { a: 1, b: 2, c: 3, d: 4 }
const overridden = { ...base, b: 99 };    // { a: 1, b: 99 }

// Clone and modify
const original = { name: "Alice", age: 28 };
const updated  = { ...original, age: 29 }; // { name: "Alice", age: 29 }

// Function call spread
function add(a, b, c) { return a + b + c; }
const args = [1, 2, 3];
console.log(add(...args));   // 6

// Spread with Math functions
const scores = [78, 92, 85, 96, 71];
console.log(Math.max(...scores));   // 96
console.log(Math.min(...scores));   // 71
```

---

## 7. Scope, Closures & Hoisting

### 7.1 Scope

```javascript
// ── GLOBAL SCOPE ─────────────────────────────────────────────────
const globalVar = "I'm global";

function outer() {
    // ── FUNCTION SCOPE ───────────────────────────────────────────
    const outerVar = "I'm in outer";

    function inner() {
        // ── INNER FUNCTION SCOPE (Closure) ───────────────────────
        const innerVar = "I'm in inner";
        console.log(globalVar);  // ✅ Can access global
        console.log(outerVar);   // ✅ Can access outer (closure)
        console.log(innerVar);   // ✅ Can access own
    }

    inner();
    // console.log(innerVar);  // ❌ ReferenceError
}

outer();
// console.log(outerVar);  // ❌ ReferenceError

// ── BLOCK SCOPE (let/const) ──────────────────────────────────────
{
    var blockVar  = "var is function-scoped (leaks out!)";
    let blockLet  = "let is block-scoped";
    const blockConst = "const is block-scoped";
}
console.log(blockVar);    // ✅ "var is function-scoped (leaks out!)"
// console.log(blockLet); // ❌ ReferenceError

// Loop scope
for (let i = 0; i < 3; i++) {
    setTimeout(() => console.log(i), 100);   // Prints 0, 1, 2 ✅
}
for (var i = 0; i < 3; i++) {
    setTimeout(() => console.log(i), 100);   // Prints 3, 3, 3 ❌
}
```

### 7.2 Hoisting

```javascript
// ── FUNCTION DECLARATIONS are fully hoisted ──────────────────────
console.log(hoisted());   // ✅ "I work!" — called before declaration
function hoisted() { return "I work!"; }

// ── var is hoisted (declaration only, not value) ─────────────────
console.log(x);   // undefined (NOT ReferenceError — it's hoisted as undefined)
var x = 5;
console.log(x);   // 5

// Equivalent to:
// var x;
// console.log(x);  // undefined
// x = 5;

// ── let/const have Temporal Dead Zone (TDZ) ─────────────────────
// console.log(y);  // ❌ ReferenceError: Cannot access 'y' before initialization
let y = 10;

// ── Function expressions are NOT hoisted ─────────────────────────
// console.log(notHoisted());  // ❌ TypeError: notHoisted is not a function
var notHoisted = function() { return "late!"; };
```

### 7.3 Closures — The Most Powerful Concept

A **closure** is a function that remembers its outer scope even after the outer function has returned.

```javascript
// Basic closure
function counter() {
    let count = 0;     // Private to this closure

    return {
        increment() { count++; },
        decrement() { count--; },
        getCount()  { return count; }
    };
}

const c1 = counter();
const c2 = counter();   // Independent instance

c1.increment();
c1.increment();
c1.increment();
c2.increment();

console.log(c1.getCount());  // 3
console.log(c2.getCount());  // 1

// ── Closure for private state ────────────────────────────────────
function createBankAccount(initialBalance) {
    let balance = initialBalance;   // "private"

    return {
        deposit(amount) {
            if (amount > 0) balance += amount;
            return balance;
        },
        withdraw(amount) {
            if (amount > balance) throw new Error("Insufficient funds");
            balance -= amount;
            return balance;
        },
        getBalance() { return balance; }
    };
}

const account = createBankAccount(1000);
account.deposit(500);
account.withdraw(200);
console.log(account.getBalance());  // 1300
// console.log(balance);              // ❌ ReferenceError — truly private

// ── Closure in loops — the classic gotcha ────────────────────────
// Problem: all closures share the same `i` variable
const fns = [];
for (var i = 0; i < 3; i++) {
    fns.push(function() { return i; });  // captures reference to i
}
console.log(fns[0](), fns[1](), fns[2]());  // 3 3 3  ❌

// Fix 1: Use let (block-scoped per iteration)
const fns2 = [];
for (let i = 0; i < 3; i++) {
    fns2.push(() => i);  // each iteration has its own i
}
console.log(fns2[0](), fns2[1](), fns2[2]());  // 0 1 2  ✅

// Fix 2: IIFE to capture current value
const fns3 = [];
for (var i = 0; i < 3; i++) {
    fns3.push((function(j) { return () => j; })(i));
}

// ── Memoization with closures ────────────────────────────────────
function memoize(fn) {
    const cache = {};
    return function(...args) {
        const key = JSON.stringify(args);
        if (key in cache) return cache[key];
        return (cache[key] = fn(...args));
    };
}

const fib = memoize(function(n) {
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);
});

console.log(fib(40));   // Instant, even for large n
```

---

## 8. The `this` Keyword

`this` is one of JavaScript's most confusing concepts. Its value depends entirely on **how** a function is called.

```javascript
// ── RULE 1: Global context ────────────────────────────────────────
console.log(this);          // Browser: window  |  Node: {}

// ── RULE 2: Object method — this = the object before the dot ──────
const user = {
    name: "Alice",
    greet() {
        console.log(`Hello, I'm ${this.name}`);  // this = user
    }
};
user.greet();   // "Hello, I'm Alice"

// ── RULE 3: Extracted method loses this ──────────────────────────
const greetFn = user.greet;
greetFn();   // "Hello, I'm undefined" — this = global/undefined

// ── RULE 4: new — this = newly created object ────────────────────
function Person(name) {
    this.name = name;
    this.sayHi = function() { console.log(`Hi, I'm ${this.name}`); };
}
const alice = new Person("Alice");
alice.sayHi();   // "Hi, I'm Alice"

// ── RULE 5: call, apply, bind — explicit binding ─────────────────
function introduce(greeting, punctuation) {
    console.log(`${greeting}, I'm ${this.name}${punctuation}`);
}
const bob = { name: "Bob" };

introduce.call(bob, "Hello", "!");        // call: args one by one
introduce.apply(bob, ["Hey", "."]);       // apply: args as array
const boundFn = introduce.bind(bob, "Hi");// bind: returns new fn
boundFn("!!");

// ── RULE 6: Arrow functions — lexical this ────────────────────────
// Arrow functions do NOT have their own this — they inherit from enclosing scope
const timer = {
    seconds: 0,

    start() {
        // ❌ Regular function loses this
        // setInterval(function() { this.seconds++; }, 1000);

        // ✅ Arrow function inherits this from start()
        setInterval(() => {
            this.seconds++;
            console.log(this.seconds);
        }, 1000);
    }
};

// ── RULE 7: Class methods ─────────────────────────────────────────
class Button {
    constructor(label) {
        this.label = label;
        // Bind in constructor for event handlers
        this.handleClick = this.handleClick.bind(this);
    }

    handleClick() {
        console.log(`${this.label} clicked`);  // this = Button instance
    }

    // Or use arrow function class field (no bind needed)
    handleHover = () => {
        console.log(`${this.label} hovered`);
    }
}

// ── Practical: React-like component ──────────────────────────────
class Component {
    constructor(state) {
        this.state = state;
    }

    // This works correctly when passed as callback
    handleEvent = (event) => {
        console.log(this.state, event);
    }
}
```

---

## 9. Prototypes & Prototype Chain

### 9.1 Understanding the Chain

```javascript
// Every object has a hidden [[Prototype]] link
// This forms the "prototype chain"

const animal = {
    breathe() { console.log("Breathing..."); }
};

const dog = Object.create(animal);   // dog's prototype is animal
dog.bark = function() { console.log("Woof!"); };

dog.bark();     // ✅ Own method
dog.breathe();  // ✅ Found on prototype (animal)
// dog → animal → Object.prototype → null

console.log(dog.hasOwnProperty("bark"));     // true
console.log(dog.hasOwnProperty("breathe"));  // false (inherited)
console.log(Object.getPrototypeOf(dog) === animal);  // true
```

### 9.2 Constructor Functions & Prototype

```javascript
// Old-school OOP in JavaScript (pre-ES6)
function Animal(name, sound) {
    this.name  = name;    // Own properties — created per instance
    this.sound = sound;
}

// Shared methods on prototype — defined ONCE, shared by all instances
Animal.prototype.speak = function() {
    console.log(`${this.name} says ${this.sound}`);
};

Animal.prototype.toString = function() {
    return `Animal(${this.name})`;
};

function Dog(name) {
    Animal.call(this, name, "Woof");  // Call parent constructor
    this.tricks = [];
}

// Set up inheritance chain
Dog.prototype = Object.create(Animal.prototype);
Dog.prototype.constructor = Dog;   // Fix constructor reference

OBOBOBOBOBOBDog.prototype.learn = function(trick) {
OBOB    this.tricks.push(trick);
    console.log(`${this.name} learned ${trick}`);
};
OBOB
OBOBOBconst rex = new Dog("Rex");
rex.speak();           // "Rex says Woof"  (from Animal.prototype)
OBOBrex.learn("sit");      // "Rex learned sit"
OBOB
console.log(rex instanceof Dog);     // true
OBOBconsole.log(rex instanceof Animal);  // true
OBOBOB```
OBOB
OBOB> 💡 **Note**: In modern JS, use **ES6 Classes** (Part 2) instead. They are syntactic sugar over the prototype system but much cleaner.
OBOB
---
