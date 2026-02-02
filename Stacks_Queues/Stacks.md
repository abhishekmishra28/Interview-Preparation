# Stack Data Structure - Complete Guide

## Table of Contents
- [Introduction](#introduction)
- [What is a Stack?](#what-is-a-stack)
- [Stack Operations](#stack-operations)
- [Implementation Methods](#implementation-methods)
  - [Array-based Stack](#array-based-stack)
  - [Linked List-based Stack](#linked-list-based-stack)
  - [STL Stack](#stl-stack)
- [Types of Stacks](#types-of-stacks)
- [Applications](#applications)
- [Stack Problems](#stack-problems)
- [Advanced Concepts](#advanced-concepts)
- [Complete C++ Implementation](#complete-cpp-implementation)
- [Practice Problems](#practice-problems)

---

# Introduction

A **Stack** is a linear data structure that follows the **LIFO** (Last In, First Out) or **FILO** (First In, Last Out) principle. The element inserted last is the first one to be removed.

Think of a stack like:
- A stack of plates 🍽️
- A stack of books 📚
- The "Back" button in a browser
- Undo operation in text editors

---

# What is a Stack?

## LIFO Principle

```
         Top
         ↓
    [    5    ]  ← Last In, First Out
    [    3    ]
    [    7    ]
    [    2    ]  ← First In, Last Out
    ──────────
```

## Real-World Analogy

**Cafeteria Tray Dispenser:**
1. Clean trays are stacked on top
2. You take the **top** tray (most recent)
3. When washing, you add trays to the **top**
4. The bottom tray was added first but will be used last

## Visual Representation

```
Push 10:        Push 20:        Push 30:        Pop:
                                               
                                [30]           
                [20]            [20]            [20]
[10]            [10]            [10]            [10]
────            ────            ────            ────

After Pop, 30 is removed, 20 becomes top
```

---

# Stack Operations

## Core Operations

### 1. Push
**Add element to the top of stack**

```
Before:         After Push(40):
[30]            [40]  ← New Top
[20]            [30]
[10]            [20]
                [10]
```

### 2. Pop
**Remove element from the top of stack**

```
Before:         After Pop():
[40]            
[30]            [30]  ← New Top
[20]            [20]
[10]            [10]

Returns: 40
```

### 3. Peek/Top
**Get the top element without removing it**

```
Stack:
[40]  ← Peek returns 40
[30]
[20]
[10]

Stack remains unchanged
```

### 4. isEmpty
**Check if stack is empty**

```cpp
isEmpty() returns true if stack has no elements
isEmpty() returns false otherwise
```

### 5. isFull
**Check if stack is full (for array-based implementation)**

```cpp
isFull() returns true if stack is at maximum capacity
isFull() returns false otherwise
```

### 6. Size
**Get number of elements in stack**

```cpp
size() returns count of elements
```

## Operation Complexities

| Operation | Time Complexity | Space Complexity |
|-----------|----------------|------------------|
| Push | O(1) | O(1) |
| Pop | O(1) | O(1) |
| Peek/Top | O(1) | O(1) |
| isEmpty | O(1) | O(1) |
| isFull | O(1) | O(1) |
| Size | O(1) | O(1) |

---

# Implementation Methods

## Array-based Stack

### Advantages
✅ Simple implementation  
✅ Cache-friendly (contiguous memory)  
✅ Fast access  

### Disadvantages
❌ Fixed size (static array)  
❌ Stack overflow if exceeds capacity  
❌ Memory waste if underutilized  

### Implementation

```cpp
#include <iostream>
using namespace std;

class Stack {
private:
    int* arr;
    int top;
    int capacity;

public:
    // Constructor
    Stack(int size) {
        arr = new int[size];
        capacity = size;
        top = -1;
    }
    
    // Destructor
    ~Stack() {
        delete[] arr;
    }
    
    // Push element
    void push(int x) {
        if (isFull()) {
            cout << "Stack Overflow! Cannot push " << x << endl;
            return;
        }
        arr[++top] = x;
        cout << x << " pushed to stack\n";
    }
    
    // Pop element
    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow! Cannot pop\n";
            return -1;
        }
        return arr[top--];
    }
    
    // Peek top element
    int peek() {
        if (isEmpty()) {
            cout << "Stack is empty!\n";
            return -1;
        }
        return arr[top];
    }
    
    // Check if empty
    bool isEmpty() {
        return top == -1;
    }
    
    // Check if full
    bool isFull() {
        return top == capacity - 1;
    }
    
    // Get size
    int size() {
        return top + 1;
    }
    
    // Display stack
    void display() {
        if (isEmpty()) {
            cout << "Stack is empty!\n";
            return;
        }
        cout << "Stack elements: ";
        for (int i = top; i >= 0; i--) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};
```

### Dynamic Array Stack

```cpp
class DynamicStack {
private:
    int* arr;
    int top;
    int capacity;
    
    void resize() {
        int newCapacity = capacity * 2;
        int* newArr = new int[newCapacity];
        
        for (int i = 0; i <= top; i++) {
            newArr[i] = arr[i];
        }
        
        delete[] arr;
        arr = newArr;
        capacity = newCapacity;
    }

public:
    DynamicStack(int size = 10) {
        arr = new int[size];
        capacity = size;
        top = -1;
    }
    
    ~DynamicStack() {
        delete[] arr;
    }
    
    void push(int x) {
        if (isFull()) {
            resize();
        }
        arr[++top] = x;
    }
    
    int pop() {
        if (isEmpty()) {
            throw runtime_error("Stack Underflow");
        }
        return arr[top--];
    }
    
    int peek() {
        if (isEmpty()) {
            throw runtime_error("Stack is empty");
        }
        return arr[top];
    }
    
    bool isEmpty() {
        return top == -1;
    }
    
    bool isFull() {
        return top == capacity - 1;
    }
    
    int size() {
        return top + 1;
    }
};
```

## Linked List-based Stack

### Advantages
✅ Dynamic size (no overflow)  
✅ No memory waste  
✅ Easy to implement  

### Disadvantages
❌ Extra memory for pointers  
❌ Not cache-friendly  
❌ Slightly slower than array  

### Implementation

```cpp
#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    
    Node(int val) {
        data = val;
        next = nullptr;
    }
};

class StackLL {
private:
    Node* top;
    int count;

public:
    StackLL() {
        top = nullptr;
        count = 0;
    }
    
    ~StackLL() {
        while (!isEmpty()) {
            pop();
        }
    }
    
    void push(int x) {
        Node* newNode = new Node(x);
        newNode->next = top;
        top = newNode;
        count++;
        cout << x << " pushed to stack\n";
    }
    
    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow!\n";
            return -1;
        }
        Node* temp = top;
        int popped = top->data;
        top = top->next;
        delete temp;
        count--;
        return popped;
    }
    
    int peek() {
        if (isEmpty()) {
            cout << "Stack is empty!\n";
            return -1;
        }
        return top->data;
    }
    
    bool isEmpty() {
        return top == nullptr;
    }
    
    int size() {
        return count;
    }
    
    void display() {
        if (isEmpty()) {
            cout << "Stack is empty!\n";
            return;
        }
        Node* temp = top;
        cout << "Stack elements: ";
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};
```

## STL Stack

### C++ Standard Template Library

```cpp
#include <iostream>
#include <stack>
using namespace std;

int main() {
    stack<int> s;
    
    // Push elements
    s.push(10);
    s.push(20);
    s.push(30);
    
    // Get top element
    cout << "Top element: " << s.top() << endl;
    
    // Get size
    cout << "Size: " << s.size() << endl;
    
    // Pop element
    s.pop();
    cout << "After pop, top: " << s.top() << endl;
    
    // Check if empty
    if (s.empty()) {
        cout << "Stack is empty\n";
    } else {
        cout << "Stack is not empty\n";
    }
    
    // Display all elements
    cout << "Stack elements: ";
    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;
    
    return 0;
}
```

### STL Stack Methods

| Method | Description | Time |
|--------|-------------|------|
| `push(x)` | Add element | O(1) |
| `pop()` | Remove top element | O(1) |
| `top()` | Get top element | O(1) |
| `empty()` | Check if empty | O(1) |
| `size()` | Get number of elements | O(1) |

---

# Types of Stacks

## 1. Simple Stack (Regular Stack)

Basic stack with standard operations.

```cpp
Stack s;
s.push(10);
s.push(20);
s.pop();  // Returns 20
```

## 2. Min Stack

Stack that supports `getMin()` in O(1) time.

```cpp
class MinStack {
private:
    stack<int> s;
    stack<int> minStack;

public:
    void push(int x) {
        s.push(x);
        if (minStack.empty() || x <= minStack.top()) {
            minStack.push(x);
        }
    }
    
    void pop() {
        if (s.top() == minStack.top()) {
            minStack.pop();
        }
        s.pop();
    }
    
    int top() {
        return s.top();
    }
    
    int getMin() {
        return minStack.top();
    }
};
```

**Example:**
```
push(5):   s: [5]      minStack: [5]
push(3):   s: [5,3]    minStack: [5,3]
push(7):   s: [5,3,7]  minStack: [5,3]
getMin():  returns 3
pop():     s: [5,3]    minStack: [5,3]
getMin():  returns 3
pop():     s: [5]      minStack: [5]
getMin():  returns 5
```

## 3. Max Stack

Stack that supports `getMax()` in O(1) time.

```cpp
class MaxStack {
private:
    stack<int> s;
    stack<int> maxStack;

public:
    void push(int x) {
        s.push(x);
        if (maxStack.empty() || x >= maxStack.top()) {
            maxStack.push(x);
        }
    }
    
    void pop() {
        if (s.top() == maxStack.top()) {
            maxStack.pop();
        }
        s.pop();
    }
    
    int top() {
        return s.top();
    }
    
    int getMax() {
        return maxStack.top();
    }
};
```

## 4. Two Stacks in One Array

Efficiently implement two stacks using single array.

```cpp
class TwoStacks {
private:
    int* arr;
    int size;
    int top1, top2;

public:
    TwoStacks(int n) {
        size = n;
        arr = new int[n];
        top1 = -1;
        top2 = size;
    }
    
    void push1(int x) {
        if (top1 < top2 - 1) {
            arr[++top1] = x;
        } else {
            cout << "Stack Overflow\n";
        }
    }
    
    void push2(int x) {
        if (top1 < top2 - 1) {
            arr[--top2] = x;
        } else {
            cout << "Stack Overflow\n";
        }
    }
    
    int pop1() {
        if (top1 >= 0) {
            return arr[top1--];
        } else {
            cout << "Stack Underflow\n";
            return -1;
        }
    }
    
    int pop2() {
        if (top2 < size) {
            return arr[top2++];
        } else {
            cout << "Stack Underflow\n";
            return -1;
        }
    }
};
```

**Visualization:**
```
Array of size 10:
[_][_][_][_][_][_][_][_][_][_]
 ↑                           ↑
top1=-1                   top2=10

After push1(5), push1(10):
[5][10][_][_][_][_][_][_][_][_]
     ↑                       ↑
   top1=1                 top2=10

After push2(15), push2(20):
[5][10][_][_][_][_][_][_][20][15]
     ↑                   ↑
   top1=1              top2=8
```

## 5. K Stacks in One Array

Implement k stacks in a single array.

```cpp
class KStacks {
private:
    int* arr;      // Array to store elements
    int* top;      // Array to store top of each stack
    int* next;     // Array to store next entry in all stacks
    int n, k;      // n: size of array, k: number of stacks
    int free;      // Index of free slot

public:
    KStacks(int k, int n) {
        this->k = k;
        this->n = n;
        arr = new int[n];
        top = new int[k];
        next = new int[n];
        
        // Initialize all stacks as empty
        for (int i = 0; i < k; i++) {
            top[i] = -1;
        }
        
        // Initialize all spaces as free
        free = 0;
        for (int i = 0; i < n - 1; i++) {
            next[i] = i + 1;
        }
        next[n - 1] = -1;
    }
    
    bool isEmpty(int sn) {
        return top[sn] == -1;
    }
    
    bool isFull() {
        return free == -1;
    }
    
    void push(int item, int sn) {
        if (isFull()) {
            cout << "Stack Overflow\n";
            return;
        }
        
        int i = free;      // Get index of free slot
        free = next[i];    // Update free slot
        next[i] = top[sn]; // Update next of i to old top
        top[sn] = i;       // Update top
        arr[i] = item;     // Store item
    }
    
    int pop(int sn) {
        if (isEmpty(sn)) {
            cout << "Stack Underflow\n";
            return -1;
        }
        
        int i = top[sn];   // Get top index
        top[sn] = next[i]; // Update top
        next[i] = free;    // Add to free list
        free = i;
        
        return arr[i];
    }
};
```

## 6. Infix Stack (Expression Evaluation)

Used for converting and evaluating expressions.

```cpp
class InfixStack {
private:
    stack<char> operators;
    stack<int> operands;
    
    int precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }
    
    int applyOp(int a, int b, char op) {
        switch(op) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': return a / b;
        }
        return 0;
    }

public:
    int evaluate(string expr) {
        for (int i = 0; i < expr.length(); i++) {
            if (expr[i] == ' ') continue;
            
            if (isdigit(expr[i])) {
                int val = 0;
                while (i < expr.length() && isdigit(expr[i])) {
                    val = val * 10 + (expr[i] - '0');
                    i++;
                }
                i--;
                operands.push(val);
            }
            else if (expr[i] == '(') {
                operators.push(expr[i]);
            }
            else if (expr[i] == ')') {
                while (!operators.empty() && operators.top() != '(') {
                    int b = operands.top(); operands.pop();
                    int a = operands.top(); operands.pop();
                    char op = operators.top(); operators.pop();
                    operands.push(applyOp(a, b, op));
                }
                operators.pop();
            }
            else {
                while (!operators.empty() && 
                       precedence(operators.top()) >= precedence(expr[i])) {
                    int b = operands.top(); operands.pop();
                    int a = operands.top(); operands.pop();
                    char op = operators.top(); operators.pop();
                    operands.push(applyOp(a, b, op));
                }
                operators.push(expr[i]);
            }
        }
        
        while (!operators.empty()) {
            int b = operands.top(); operands.pop();
            int a = operands.top(); operands.pop();
            char op = operators.top(); operators.pop();
            operands.push(applyOp(a, b, op));
        }
        
        return operands.top();
    }
};
```

## 7. Monotonic Stack

Stack that maintains elements in increasing or decreasing order.

```cpp
// Monotonic Increasing Stack
vector<int> nextGreaterElement(vector<int>& arr) {
    int n = arr.size();
    vector<int> result(n, -1);
    stack<int> s;
    
    for (int i = n - 1; i >= 0; i--) {
        while (!s.empty() && s.top() <= arr[i]) {
            s.pop();
        }
        if (!s.empty()) {
            result[i] = s.top();
        }
        s.push(arr[i]);
    }
    
    return result;
}
```

**Example:**
```
Input:  [4, 5, 2, 25]
Stack operations:
i=3: s=[25]           result=[_, _, _, -1]
i=2: s=[25, 2]        result=[_, _, 25, -1]
i=1: s=[25, 5]        result=[_, 25, 25, -1]
i=0: s=[25, 5]        result=[5, 25, 25, -1]
```

---

# Applications

## 1. Function Call Management (Call Stack)

```cpp
void function3() {
    cout << "Function 3\n";
}

void function2() {
    cout << "Function 2\n";
    function3();
}

void function1() {
    cout << "Function 1\n";
    function2();
}

// Call stack:
// [function1]
// [function1, function2]
// [function1, function2, function3]
// [function1, function2]
// [function1]
// []
```

## 2. Expression Evaluation

### Infix to Postfix Conversion

```cpp
string infixToPostfix(string infix) {
    stack<char> s;
    string postfix = "";
    
    for (char c : infix) {
        if (isalnum(c)) {
            postfix += c;
        }
        else if (c == '(') {
            s.push(c);
        }
        else if (c == ')') {
            while (!s.empty() && s.top() != '(') {
                postfix += s.top();
                s.pop();
            }
            s.pop();
        }
        else {
            while (!s.empty() && precedence(s.top()) >= precedence(c)) {
                postfix += s.top();
                s.pop();
            }
            s.push(c);
        }
    }
    
    while (!s.empty()) {
        postfix += s.top();
        s.pop();
    }
    
    return postfix;
}
```

**Example:**
```
Infix:    A + B * C
Postfix:  ABC*+

Infix:    (A + B) * C
Postfix:  AB+C*
```

### Postfix Evaluation

```cpp
int evaluatePostfix(string postfix) {
    stack<int> s;
    
    for (char c : postfix) {
        if (isdigit(c)) {
            s.push(c - '0');
        }
        else {
            int b = s.top(); s.pop();
            int a = s.top(); s.pop();
            
            switch(c) {
                case '+': s.push(a + b); break;
                case '-': s.push(a - b); break;
                case '*': s.push(a * b); break;
                case '/': s.push(a / b); break;
            }
        }
    }
    
    return s.top();
}
```

## 3. Parenthesis Matching

```cpp
bool isBalanced(string expr) {
    stack<char> s;
    
    for (char c : expr) {
        if (c == '(' || c == '{' || c == '[') {
            s.push(c);
        }
        else if (c == ')' || c == '}' || c == ']') {
            if (s.empty()) return false;
            
            char top = s.top();
            s.pop();
            
            if ((c == ')' && top != '(') ||
                (c == '}' && top != '{') ||
                (c == ']' && top != '[')) {
                return false;
            }
        }
    }
    
    return s.empty();
}
```

**Examples:**
```
"{[()]}"     → Balanced ✓
"{[(])}"     → Not Balanced ✗
"((()))"     → Balanced ✓
"(()"        → Not Balanced ✗
```

## 4. Undo/Redo Functionality

```cpp
class TextEditor {
private:
    stack<string> undoStack;
    stack<string> redoStack;
    string currentText;

public:
    void write(string text) {
        undoStack.push(currentText);
        currentText = text;
        // Clear redo stack on new action
        while (!redoStack.empty()) {
            redoStack.pop();
        }
    }
    
    void undo() {
        if (!undoStack.empty()) {
            redoStack.push(currentText);
            currentText = undoStack.top();
            undoStack.pop();
        }
    }
    
    void redo() {
        if (!redoStack.empty()) {
            undoStack.push(currentText);
            currentText = redoStack.top();
            redoStack.pop();
        }
    }
    
    string getText() {
        return currentText;
    }
};
```

## 5. Browser History (Back/Forward)

```cpp
class BrowserHistory {
private:
    stack<string> backStack;
    stack<string> forwardStack;
    string currentPage;

public:
    BrowserHistory(string homepage) {
        currentPage = homepage;
    }
    
    void visit(string url) {
        backStack.push(currentPage);
        currentPage = url;
        // Clear forward history
        while (!forwardStack.empty()) {
            forwardStack.pop();
        }
    }
    
    string back() {
        if (!backStack.empty()) {
            forwardStack.push(currentPage);
            currentPage = backStack.top();
            backStack.pop();
        }
        return currentPage;
    }
    
    string forward() {
        if (!forwardStack.empty()) {
            backStack.push(currentPage);
            currentPage = forwardStack.top();
            forwardStack.pop();
        }
        return currentPage;
    }
};
```

## 6. Tower of Hanoi

```cpp
void towerOfHanoi(int n, char from, char to, char aux) {
    if (n == 1) {
        cout << "Move disk 1 from " << from << " to " << to << endl;
        return;
    }
    
    towerOfHanoi(n - 1, from, aux, to);
    cout << "Move disk " << n << " from " << from << " to " << to << endl;
    towerOfHanoi(n - 1, aux, to, from);
}
```

## 7. Depth-First Search (DFS)

```cpp
void DFS(vector<vector<int>>& graph, int start) {
    int n = graph.size();
    vector<bool> visited(n, false);
    stack<int> s;
    
    s.push(start);
    
    while (!s.empty()) {
        int node = s.top();
        s.pop();
        
        if (!visited[node]) {
            cout << node << " ";
            visited[node] = true;
            
            // Push adjacent nodes
            for (int adj : graph[node]) {
                if (!visited[adj]) {
                    s.push(adj);
                }
            }
        }
    }
}
```

---

# Stack Problems

## 1. Next Greater Element

```cpp
vector<int> nextGreaterElement(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n, -1);
    stack<int> s;
    
    for (int i = n - 1; i >= 0; i--) {
        while (!s.empty() && s.top() <= nums[i]) {
            s.pop();
        }
        if (!s.empty()) {
            result[i] = s.top();
        }
        s.push(nums[i]);
    }
    
    return result;
}
```

## 2. Stock Span Problem

```cpp
vector<int> stockSpan(vector<int>& prices) {
    int n = prices.size();
    vector<int> span(n);
    stack<int> s;
    
    for (int i = 0; i < n; i++) {
        while (!s.empty() && prices[s.top()] <= prices[i]) {
            s.pop();
        }
        span[i] = s.empty() ? (i + 1) : (i - s.top());
        s.push(i);
    }
    
    return span;
}
```

**Example:**
```
Prices: [100, 80, 60, 70, 60, 75, 85]
Span:   [  1,  1,  1,  2,  1,  4,  6]

Day 0: span = 1 (no previous day >= 100)
Day 1: span = 1 (80 < 100)
Day 6: span = 6 (85 > all previous 5 days since day 1)
```

## 3. Largest Rectangle in Histogram

```cpp
int largestRectangle(vector<int>& heights) {
    stack<int> s;
    int maxArea = 0;
    int n = heights.size();
    
    for (int i = 0; i <= n; i++) {
        int h = (i == n) ? 0 : heights[i];
        
        while (!s.empty() && h < heights[s.top()]) {
            int height = heights[s.top()];
            s.pop();
            int width = s.empty() ? i : i - s.top() - 1;
            maxArea = max(maxArea, height * width);
        }
        s.push(i);
    }
    
    return maxArea;
}
```

## 4. Trapping Rain Water

```cpp
int trap(vector<int>& height) {
    if (height.empty()) return 0;
    
    stack<int> s;
    int water = 0;
    
    for (int i = 0; i < height.size(); i++) {
        while (!s.empty() && height[i] > height[s.top()]) {
            int top = s.top();
            s.pop();
            
            if (s.empty()) break;
            
            int distance = i - s.top() - 1;
            int boundedHeight = min(height[i], height[s.top()]) - height[top];
            water += distance * boundedHeight;
        }
        s.push(i);
    }
    
    return water;
}
```

## 5. Celebrity Problem

```cpp
int findCelebrity(vector<vector<int>>& M, int n) {
    stack<int> s;
    
    // Push all people to stack
    for (int i = 0; i < n; i++) {
        s.push(i);
    }
    
    // Find potential celebrity
    while (s.size() > 1) {
        int a = s.top(); s.pop();
        int b = s.top(); s.pop();
        
        if (M[a][b] == 1) {
            s.push(b);  // a knows b, so a can't be celebrity
        } else {
            s.push(a);  // a doesn't know b, so b can't be celebrity
        }
    }
    
    int candidate = s.top();
    
    // Verify candidate
    for (int i = 0; i < n; i++) {
        if (i != candidate) {
            if (M[candidate][i] == 1 || M[i][candidate] == 0) {
                return -1;  // Not a celebrity
            }
        }
    }
    
    return candidate;
}
```

## 6. Remove K Digits

```cpp
string removeKdigits(string num, int k) {
    if (k >= num.length()) return "0";
    
    stack<char> s;
    
    for (char digit : num) {
        while (!s.empty() && k > 0 && s.top() > digit) {
            s.pop();
            k--;
        }
        s.push(digit);
    }
    
    // Remove remaining k digits from end
    while (k > 0) {
        s.pop();
        k--;
    }
    
    // Build result
    string result = "";
    while (!s.empty()) {
        result = s.top() + result;
        s.pop();
    }
    
    // Remove leading zeros
    int i = 0;
    while (i < result.length() && result[i] == '0') {
        i++;
    }
    result = result.substr(i);
    
    return result.empty() ? "0" : result;
}
```

**Example:**
```
Input: num = "1432219", k = 3
Output: "1219"

Stack operations:
'1': s = [1]
'4': s = [1, 4]
'3': 4 > 3, pop 4, s = [1, 3], k = 2
'2': 3 > 2, pop 3, s = [1, 2], k = 1
'2': s = [1, 2, 2]
'1': 2 > 1, pop 2, s = [1, 2, 1], k = 0
'9': s = [1, 2, 1, 9]

Result: "1219"
```

## 7. Decode String

```cpp
string decodeString(string s) {
    stack<int> countStack;
    stack<string> stringStack;
    string currentString = "";
    int k = 0;
    
    for (char c : s) {
        if (isdigit(c)) {
            k = k * 10 + (c - '0');
        }
        else if (c == '[') {
            countStack.push(k);
            stringStack.push(currentString);
            currentString = "";
            k = 0;
        }
        else if (c == ']') {
            string decodedString = stringStack.top();
            stringStack.pop();
            int count = countStack.top();
            countStack.pop();
            
            for (int i = 0; i < count; i++) {
                decodedString += currentString;
            }
            currentString = decodedString;
        }
        else {
            currentString += c;
        }
    }
    
    return currentString;
}
```

**Example:**
```
Input: "3[a2[c]]"
Output: "accaccacc"

Step-by-step:
- '3': k = 3
- '[': countStack = [3], stringStack = [""], currentString = ""
- 'a': currentString = "a"
- '2': k = 2
- '[': countStack = [3, 2], stringStack = ["", "a"], currentString = ""
- 'c': currentString = "c"
- ']': decodedString = "a" + "c" + "c" = "acc"
- ']': decodedString = "" + "acc" + "acc" + "acc" = "accaccacc"
```

---

# Advanced Concepts

## 1. Stack Sorting

```cpp
void sortStack(stack<int>& s) {
    stack<int> temp;
    
    while (!s.empty()) {
        int current = s.top();
        s.pop();
        
        while (!temp.empty() && temp.top() > current) {
            s.push(temp.top());
            temp.pop();
        }
        
        temp.push(current);
    }
    
    // Copy back to original stack
    while (!temp.empty()) {
        s.push(temp.top());
        temp.pop();
    }
}
```

**Example:**
```
Input stack (top to bottom): [3, 1, 4, 2]
After sorting: [1, 2, 3, 4]

Process:
Initial:  s = [3, 1, 4, 2]
Step 1:   temp = [2]
Step 2:   temp = [2, 4]
Step 3:   temp = [1, 2, 4]
Step 4:   temp = [1, 2, 3, 4]
```

## 2. Reverse Stack using Recursion

```cpp
void insertAtBottom(stack<int>& s, int item) {
    if (s.empty()) {
        s.push(item);
        return;
    }
    
    int top = s.top();
    s.pop();
    insertAtBottom(s, item);
    s.push(top);
}

void reverseStack(stack<int>& s) {
    if (s.empty()) return;
    
    int top = s.top();
    s.pop();
    reverseStack(s);
    insertAtBottom(s, top);
}
```

**Example:**
```
Input:  [1, 2, 3, 4]  (1 is top)
Output: [4, 3, 2, 1]  (4 is top)
```

## 3. Middle Element Operations

```cpp
class StackWithMiddle {
private:
    struct Node {
        int data;
        Node* next;
        Node* prev;
        Node(int d) : data(d), next(nullptr), prev(nullptr) {}
    };
    
    Node* head;
    Node* mid;
    int count;

public:
    StackWithMiddle() : head(nullptr), mid(nullptr), count(0) {}
    
    void push(int x) {
        Node* newNode = new Node(x);
        newNode->next = head;
        count++;
        
        if (head != nullptr) {
            head->prev = newNode;
        }
        
        head = newNode;
        
        if (count == 1) {
            mid = newNode;
        } else if (count % 2 == 0) {
            mid = mid->prev;
        }
    }
    
    int pop() {
        if (head == nullptr) {
            return -1;
        }
        
        int data = head->data;
        Node* temp = head;
        head = head->next;
        
        if (head != nullptr) {
            head->prev = nullptr;
        }
        
        count--;
        
        if (count % 2 == 1) {
            mid = mid->next;
        }
        
        delete temp;
        return data;
    }
    
    int findMiddle() {
        if (mid == nullptr) {
            return -1;
        }
        return mid->data;
    }
    
    void deleteMiddle() {
        if (mid == nullptr) return;
        
        if (mid->prev != nullptr) {
            mid->prev->next = mid->next;
        }
        if (mid->next != nullptr) {
            mid->next->prev = mid->prev;
        }
        
        Node* temp = mid;
        if (count % 2 == 0) {
            mid = mid->prev;
        } else {
            mid = mid->next;
        }
        
        delete temp;
        count--;
    }
};
```

## 4. Design Stack with Increment Operation

```cpp
class CustomStack {
private:
    vector<int> stack;
    vector<int> inc;
    int maxSize;

public:
    CustomStack(int maxSize) {
        this->maxSize = maxSize;
    }
    
    void push(int x) {
        if (stack.size() < maxSize) {
            stack.push_back(x);
            inc.push_back(0);
        }
    }
    
    int pop() {
        if (stack.empty()) return -1;
        
        int idx = stack.size() - 1;
        
        if (idx > 0) {
            inc[idx - 1] += inc[idx];
        }
        
        int result = stack[idx] + inc[idx];
        stack.pop_back();
        inc.pop_back();
        
        return result;
    }
    
    void increment(int k, int val) {
        int idx = min(k, (int)stack.size()) - 1;
        if (idx >= 0) {
            inc[idx] += val;
        }
    }
};
```

## 5. Stack with getMin() in O(1) - Space Optimized

```cpp
class MinStackOptimized {
private:
    stack<long long> s;
    long long minElement;

public:
    void push(int x) {
        if (s.empty()) {
            s.push(x);
            minElement = x;
        } else {
            if (x < minElement) {
                s.push(2LL * x - minElement);
                minElement = x;
            } else {
                s.push(x);
            }
        }
    }
    
    void pop() {
        if (s.empty()) return;
        
        long long top = s.top();
        s.pop();
        
        if (top < minElement) {
            minElement = 2 * minElement - top;
        }
    }
    
    int top() {
        if (s.empty()) return -1;
        
        long long top = s.top();
        return (top < minElement) ? minElement : top;
    }
    
    int getMin() {
        return minElement;
    }
};
```

---

# Complete C++ Implementation

```cpp
#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// ==================== ARRAY-BASED STACK ====================

class ArrayStack {
private:
    int* arr;
    int top;
    int capacity;

public:
    ArrayStack(int size) {
        arr = new int[size];
        capacity = size;
        top = -1;
    }
    
    ~ArrayStack() {
        delete[] arr;
    }
    
    void push(int x) {
        if (isFull()) {
            cout << "Stack Overflow!\n";
            return;
        }
        arr[++top] = x;
    }
    
    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow!\n";
            return -1;
        }
        return arr[top--];
    }
    
    int peek() {
        if (isEmpty()) {
            return -1;
        }
        return arr[top];
    }
    
    bool isEmpty() {
        return top == -1;
    }
    
    bool isFull() {
        return top == capacity - 1;
    }
    
    int size() {
        return top + 1;
    }
    
    void display() {
        if (isEmpty()) {
            cout << "Stack is empty\n";
            return;
        }
        cout << "Stack: ";
        for (int i = top; i >= 0; i--) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

// ==================== LINKED LIST STACK ====================

class Node {
public:
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class LinkedListStack {
private:
    Node* top;
    int count;

public:
    LinkedListStack() : top(nullptr), count(0) {}
    
    ~LinkedListStack() {
        while (!isEmpty()) {
            pop();
        }
    }
    
    void push(int x) {
        Node* newNode = new Node(x);
        newNode->next = top;
        top = newNode;
        count++;
    }
    
    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow!\n";
            return -1;
        }
        Node* temp = top;
        int popped = top->data;
        top = top->next;
        delete temp;
        count--;
        return popped;
    }
    
    int peek() {
        if (isEmpty()) {
            return -1;
        }
        return top->data;
    }
    
    bool isEmpty() {
        return top == nullptr;
    }
    
    int size() {
        return count;
    }
    
    void display() {
        if (isEmpty()) {
            cout << "Stack is empty\n";
            return;
        }
        Node* temp = top;
        cout << "Stack: ";
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

// ==================== UTILITY FUNCTIONS ====================

// Check balanced parentheses
bool isBalanced(string expr) {
    stack<char> s;
    for (char c : expr) {
        if (c == '(' || c == '{' || c == '[') {
            s.push(c);
        }
        else if (c == ')' || c == '}' || c == ']') {
            if (s.empty()) return false;
            char top = s.top();
            s.pop();
            if ((c == ')' && top != '(') ||
                (c == '}' && top != '{') ||
                (c == ']' && top != '[')) {
                return false;
            }
        }
    }
    return s.empty();
}

// Reverse a string using stack
string reverseString(string str) {
    stack<char> s;
    for (char c : str) {
        s.push(c);
    }
    
    string reversed = "";
    while (!s.empty()) {
        reversed += s.top();
        s.pop();
    }
    return reversed;
}

// Next Greater Element
vector<int> nextGreaterElement(vector<int>& arr) {
    int n = arr.size();
    vector<int> result(n, -1);
    stack<int> s;
    
    for (int i = n - 1; i >= 0; i--) {
        while (!s.empty() && s.top() <= arr[i]) {
            s.pop();
        }
        if (!s.empty()) {
            result[i] = s.top();
        }
        s.push(arr[i]);
    }
    
    return result;
}

// ==================== MAIN FUNCTION ====================

int main() {
    cout << "========== ARRAY-BASED STACK ==========\n";
    ArrayStack arrayStack(5);
    arrayStack.push(10);
    arrayStack.push(20);
    arrayStack.push(30);
    arrayStack.display();
    cout << "Top element: " << arrayStack.peek() << endl;
    cout << "Popped: " << arrayStack.pop() << endl;
    arrayStack.display();
    cout << "Size: " << arrayStack.size() << endl;
    
    cout << "\n========== LINKED LIST STACK ==========\n";
    LinkedListStack llStack;
    llStack.push(100);
    llStack.push(200);
    llStack.push(300);
    llStack.display();
    cout << "Top element: " << llStack.peek() << endl;
    cout << "Popped: " << llStack.pop() << endl;
    llStack.display();
    
    cout << "\n========== STL STACK ==========\n";
    stack<int> stlStack;
    stlStack.push(1);
    stlStack.push(2);
    stlStack.push(3);
    cout << "Top: " << stlStack.top() << endl;
    cout << "Size: " << stlStack.size() << endl;
    stlStack.pop();
    cout << "After pop, top: " << stlStack.top() << endl;
    
    cout << "\n========== BALANCED PARENTHESES ==========\n";
    string expr1 = "{[()]}";
    string expr2 = "{[(])}";
    cout << expr1 << " is " << (isBalanced(expr1) ? "balanced" : "not balanced") << endl;
    cout << expr2 << " is " << (isBalanced(expr2) ? "balanced" : "not balanced") << endl;
    
    cout << "\n========== REVERSE STRING ==========\n";
    string original = "Hello";
    string reversed = reverseString(original);
    cout << "Original: " << original << endl;
    cout << "Reversed: " << reversed << endl;
    
    cout << "\n========== NEXT GREATER ELEMENT ==========\n";
    vector<int> arr = {4, 5, 2, 25};
    vector<int> nge = nextGreaterElement(arr);
    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << "\nNGE:   ";
    for (int x : nge) cout << x << " ";
    cout << endl;
    
    return 0;
}
```

### Sample Output
```
========== ARRAY-BASED STACK ==========
Stack: 30 20 10 
Top element: 30
Popped: 30
Stack: 20 10 
Size: 2

========== LINKED LIST STACK ==========
Stack: 300 200 100 
Top element: 300
Popped: 300
Stack: 200 100 

========== STL STACK ==========
Top: 3
Size: 3
After pop, top: 2

========== BALANCED PARENTHESES ==========
{[()]} is balanced
{[(])} is not balanced

========== REVERSE STRING ==========
Original: Hello
Reversed: olleH

========== NEXT GREATER ELEMENT ==========
Array: 4 5 2 25 
NGE:   5 25 25 -1 
```

---

# Practice Problems

## Easy Level

1. **Implement Stack using Arrays**
2. **Implement Stack using Linked List**
3. **Check for balanced parentheses**
4. **Reverse a string using stack**
5. **Implement two stacks in an array**

## Medium Level

6. **Design Min Stack** (LeetCode 155)
7. **Valid Parentheses** (LeetCode 20)
8. **Next Greater Element** (LeetCode 496)
9. **Implement Queue using Stacks** (LeetCode 232)
10. **Daily Temperatures** (LeetCode 739)
11. **Remove K Digits** (LeetCode 402)
12. **Decode String** (LeetCode 394)
13. **Asteroid Collision** (LeetCode 735)
14. **Score of Parentheses** (LeetCode 856)
15. **Remove All Adjacent Duplicates** (LeetCode 1047)

## Hard Level

16. **Largest Rectangle in Histogram** (LeetCode 84)
17. **Trapping Rain Water** (LeetCode 42)
18. **Maximal Rectangle** (LeetCode 85)
19. **Basic Calculator** (LeetCode 224)
20. **Longest Valid Parentheses** (LeetCode 32)

## LeetCode Problems

- [20. Valid Parentheses](https://leetcode.com/problems/valid-parentheses/)
- [155. Min Stack](https://leetcode.com/problems/min-stack/)
- [232. Implement Queue using Stacks](https://leetcode.com/problems/implement-queue-using-stacks/)
- [496. Next Greater Element I](https://leetcode.com/problems/next-greater-element-i/)
- [503. Next Greater Element II](https://leetcode.com/problems/next-greater-element-ii/)
- [739. Daily Temperatures](https://leetcode.com/problems/daily-temperatures/)
- [84. Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/)
- [42. Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/)
- [394. Decode String](https://leetcode.com/problems/decode-string/)
- [402. Remove K Digits](https://leetcode.com/problems/remove-k-digits/)

---

# Key Takeaways

## When to Use Stack

✅ **Use Stack when you need:**
- LIFO behavior
- Function call management (recursion)
- Expression evaluation/conversion
- Backtracking (maze, puzzle solving)
- Undo/Redo operations
- Browser history
- Matching problems (parentheses, tags)

## Time Complexities

| Operation | Array Stack | Linked List Stack | STL Stack |
|-----------|-------------|-------------------|-----------|
| Push | O(1) | O(1) | O(1) |
| Pop | O(1) | O(1) | O(1) |
| Peek | O(1) | O(1) | O(1) |
| Search | O(n) | O(n) | O(n) |
| Space | O(n) | O(n) | O(n) |

## Common Patterns

1. **Monotonic Stack**: Maintain increasing/decreasing order
2. **Two Pointer + Stack**: Solve matching problems
3. **Stack + HashMap**: Track indices/frequencies
4. **Multiple Stacks**: Min/Max stack, undo/redo

## Interview Tips

### Pattern Recognition
- See "matching" → Think Stack
- See "most recent" → Think Stack
- See "nested structure" → Think Stack
- See "evaluation" → Think Stack

### Common Mistakes
❌ Forgetting to check isEmpty() before pop()  
❌ Not handling overflow in array-based stack  
❌ Memory leaks in linked list implementation  
❌ Not maintaining order in monotonic stack  

### Best Practices
✅ Always check if stack is empty before operations  
✅ Use STL stack for interviews (unless asked to implement)  
✅ Consider space complexity (recursive vs iterative)  
✅ Draw diagrams for complex stack problems  

---

**Master Stacks, Master LIFO! 🚀**

## Additional Resources

- **Books:**
  - "Introduction to Algorithms" (CLRS)
  - "Data Structures and Algorithms in C++" by Goodrich

- **Online:**
  - GeeksforGeeks Stack Section
  - LeetCode Stack Problems
  - Visualgo Stack Visualization

- **Practice:**
  - Solve 5 easy → 10 medium → 5 hard problems
  - Implement all variations from scratch
  - Understand time/space trade-offs

**Remember:** Stacks are fundamental to understanding recursion, DFS, and many algorithmic patterns!
