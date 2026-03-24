# ⚛️ 30 Most Important React.js Interview Questions — SDE Intern

> **Target Audience:** SDE Intern / Junior Frontend Developer  
> **React Version:** React 18+  
> **Topics Covered:** Core Concepts, Hooks, State Management, Performance, Patterns & More

---

## Table of Contents

| # | Question |
|---|----------|
| 1 | [What is React and why is it used?](#q1) |
| 2 | [What is JSX?](#q2) |
| 3 | [What is the Virtual DOM and how does it work?](#q3) |
| 4 | [What are Components? Functional vs Class Components?](#q4) |
| 5 | [What are Props?](#q5) |
| 6 | [What is State? useState Hook?](#q6) |
| 7 | [What is the Component Lifecycle?](#q7) |
| 8 | [What is the useEffect Hook?](#q8) |
| 9 | [What is the useRef Hook?](#q9) |
| 10 | [What is the useContext Hook and Context API?](#q10) |
| 11 | [What is useReducer?](#q11) |
| 12 | [What are useMemo and useCallback?](#q12) |
| 13 | [What are Custom Hooks?](#q13) |
| 14 | [What is Lifting State Up?](#q14) |
| 15 | [What are Controlled vs Uncontrolled Components?](#q15) |
| 16 | [What is Event Handling in React?](#q16) |
| 17 | [What are Keys in React lists?](#q17) |
| 18 | [What is Conditional Rendering?](#q18) |
| 19 | [What are Higher-Order Components (HOC)?](#q19) |
| 20 | [What are React Portals?](#q20) |
| 21 | [What are Error Boundaries?](#q21) |
| 22 | [What is Code Splitting and React.lazy?](#q22) |
| 23 | [What is React.memo?](#q23) |
| 24 | [What is Prop Drilling and how to avoid it?](#q24) |
| 25 | [What is React Router?](#q25) |
| 26 | [What is Reconciliation and the Diffing Algorithm?](#q26) |
| 27 | [What are Fragments?](#q27) |
| 28 | [What is the Strict Mode in React?](#q28) |
| 29 | [What is React 18's Concurrent Mode and key features?](#q29) |
| 30 | [Common React Performance Optimization Techniques](#q30) |

---

<a name="q1"></a>
## Q1. What is React and why is it used?

**Answer:**

**React** is an open-source **JavaScript library** (not a full framework) developed by Meta (Facebook) for building **fast, interactive user interfaces**, primarily for single-page applications (SPAs).

### Key Characteristics

```
┌──────────────────────────────────────────────────────────────────┐
│                         React                                    │
├──────────────────┬───────────────────────────────────────────────┤
│ Declarative      │ Describe WHAT the UI should look like,        │
│                  │ React figures out HOW to update the DOM       │
├──────────────────┼───────────────────────────────────────────────┤
│ Component-Based  │ UI split into reusable, composable pieces     │
├──────────────────┼───────────────────────────────────────────────┤
│ Virtual DOM      │ Efficient DOM updates via diffing algorithm   │
├──────────────────┼───────────────────────────────────────────────┤
│ Unidirectional   │ Data flows one way: parent → child via props  │
│ Data Flow        │                                               │
├──────────────────┼───────────────────────────────────────────────┤
│ Learn Once,      │ React Native for mobile, React DOM for web    │
│ Write Anywhere   │                                               │
└──────────────────┴───────────────────────────────────────────────┘
```

### Why React Over Vanilla JS?

```javascript
// Vanilla JS — Imperative (tell HOW to do it)
const btn = document.getElementById('btn');
const count = document.getElementById('count');
let n = 0;
btn.addEventListener('click', () => {
  n++;
  count.textContent = n;     // Manually update DOM
});

// React — Declarative (tell WHAT it should look like)
function Counter() {
  const [count, setCount] = useState(0);
  return (
    <div>
      <p>{count}</p>
      <button onClick={() => setCount(count + 1)}>Click</button>
    </div>
  );
  // React handles DOM updates automatically ✅
}
```

### React Ecosystem
```
React Core          → UI rendering
React Router        → Client-side navigation
Redux / Zustand     → Global state management
React Query         → Server state / data fetching
Next.js / Remix     → Full-stack React frameworks
Vite / CRA          → Build tools
```

---

<a name="q2"></a>
## Q2. What is JSX?

**Answer:**

**JSX (JavaScript XML)** is a syntax extension for JavaScript that lets you write HTML-like markup directly inside JavaScript code. JSX is **not HTML** — it is syntactic sugar that gets transformed into `React.createElement()` calls by Babel.

```jsx
// JSX (what you write):
const element = <h1 className="title">Hello, {name}!</h1>;

// What Babel compiles it to:
const element = React.createElement(
  'h1',
  { className: 'title' },
  'Hello, ',
  name,
  '!'
);
```

### JSX Rules

```jsx
// 1. Must return a single root element (use Fragment if needed)
return (
  <>
    <h1>Title</h1>
    <p>Paragraph</p>
  </>
);

// 2. Use className instead of class (reserved JS keyword)
<div className="container">...</div>

// 3. Use camelCase for HTML attributes
<input onChange={handler} readOnly={true} tabIndex={1} />

// 4. Self-close empty elements
<img src="photo.jpg" alt="photo" />
<br />
<input type="text" />

// 5. Embed any JS expression with curly braces {}
const user = { name: "Alice", age: 22 };
return (
  <div>
    <p>Name: {user.name}</p>
    <p>Age: {user.age}</p>
    <p>Is adult: {user.age >= 18 ? 'Yes' : 'No'}</p>
    <p>Square: {Math.pow(4, 2)}</p>
  </div>
);

// 6. Inline styles use objects with camelCase
<div style={{ backgroundColor: 'blue', fontSize: '16px' }}>...</div>

// 7. Comments inside JSX use {/* */}
return (
  <div>
    {/* This is a JSX comment */}
    <p>Hello</p>
  </div>
);
```

### JSX Prevents XSS
React automatically **escapes** values embedded in JSX — user input cannot inject script tags:
```jsx
const userInput = '<script>alert("XSS")</script>';
return <div>{userInput}</div>;
// Renders as plain text, not executable script ✅
```

---

<a name="q3"></a>
## Q3. What is the Virtual DOM and how does it work?

**Answer:**

The **Virtual DOM (VDOM)** is a lightweight **in-memory representation** of the actual DOM. React uses it to compute the minimal set of real DOM updates needed, making UI updates fast.

### The Problem with Direct DOM Manipulation
```
Real DOM operations are expensive:
  document.getElementById('x').style.color = 'red';
  → Triggers layout recalculation
  → Triggers style recalculation
  → Triggers paint
  → Triggers composite
  → Slow if done thousands of times per second
```

### How Virtual DOM Works

```
Step 1: Initial Render
  React builds a Virtual DOM tree (plain JS objects)
  → Commits it to the real DOM

Step 2: State/Prop Change
  React builds a NEW Virtual DOM tree

Step 3: Diffing (Reconciliation)
  React compares OLD vdom vs NEW vdom
  → Finds exactly what changed

Step 4: Patch
  React updates ONLY the changed parts in the real DOM
  → Minimal, batched DOM writes

Example:
Old VDOM:  <ul> <li>A</li> <li>B</li> <li>C</li> </ul>
New VDOM:  <ul> <li>A</li> <li>B</li> <li>D</li> </ul>
Diff:      Only <li>C</li> → <li>D</li> changed
Update:    Only that one text node updated in real DOM ✅
```

### Virtual DOM Object Structure
```javascript
// JSX: <div className="box"><p>Hello</p></div>
// VDOM object (React element):
{
  type: 'div',
  props: {
    className: 'box',
    children: {
      type: 'p',
      props: { children: 'Hello' }
    }
  }
}
```

### Virtual DOM vs Real DOM

| Feature | Real DOM | Virtual DOM |
|---------|----------|-------------|
| Manipulation | Slow (triggers reflow/repaint) | Fast (plain JS objects) |
| Memory | Low | Slightly higher |
| Update strategy | Manual, entire subtree | Automated, minimal diff |
| Direct access | Yes (document API) | No (managed by React) |

---

<a name="q4"></a>
## Q4. What are Components? Functional vs Class Components?

**Answer:**

A **component** is the fundamental building block of a React application — a reusable, self-contained piece of UI that can accept inputs (props) and return JSX to render.

### Functional Components (Modern Standard — Preferred)

```jsx
// Simple functional component
function Greeting({ name, age }) {
  return (
    <div>
      <h1>Hello, {name}!</h1>
      <p>You are {age} years old.</p>
    </div>
  );
}

// Arrow function syntax
const Button = ({ label, onClick, variant = 'primary' }) => (
  <button className={`btn btn-${variant}`} onClick={onClick}>
    {label}
  </button>
);

// Usage
<Greeting name="Alice" age={22} />
<Button label="Submit" onClick={handleSubmit} variant="danger" />
```

### Class Components (Legacy — Still valid, rarely written new)

```jsx
import React, { Component } from 'react';

class Counter extends Component {
  constructor(props) {
    super(props);
    this.state = { count: 0 };            // State in constructor
  }

  increment = () => {
    this.setState({ count: this.state.count + 1 });
  };

  render() {
    return (
      <div>
        <p>Count: {this.state.count}</p>
        <button onClick={this.increment}>+</button>
      </div>
    );
  }
}
```

### Functional vs Class Components

| Feature | Functional Component | Class Component |
|---------|---------------------|----------------|
| Syntax | Simple function | ES6 class extending Component |
| State | `useState` hook | `this.state` + `this.setState` |
| Lifecycle | `useEffect` hook | `componentDidMount`, etc. |
| `this` keyword | Not needed | Required everywhere |
| Performance | Slightly better | Slightly heavier |
| Code length | Shorter | Verbose |
| Modern React | ✅ Preferred | ❌ Legacy |
| Hooks | ✅ Fully supported | ❌ Cannot use hooks |

### Component Composition

```jsx
// Building complex UIs from small, composable components
function App() {
  return (
    <Layout>
      <Header title="My App" />
      <Sidebar>
        <NavItem to="/home" label="Home" />
        <NavItem to="/about" label="About" />
      </Sidebar>
      <MainContent>
        <UserCard user={currentUser} />
      </MainContent>
    </Layout>
  );
}
```

---

<a name="q5"></a>
## Q5. What are Props?

**Answer:**

**Props (properties)** are the mechanism for passing data from a **parent component to a child component**. Props are **read-only** — a child component must never modify its own props.

```jsx
// Parent passes props
function App() {
  return <UserCard name="Alice" age={22} isOnline={true} />;
}

// Child receives and uses props
function UserCard({ name, age, isOnline }) {
  return (
    <div className="card">
      <h2>{name}</h2>
      <p>Age: {age}</p>
      <span>{isOnline ? '🟢 Online' : '🔴 Offline'}</span>
    </div>
  );
}
```

### Types of Props

```jsx
// 1. String (without curly braces)
<Component title="Hello" />

// 2. Number, Boolean, Object, Array (with curly braces)
<Component count={42} active={true} user={{ name: 'Alice' }} items={[1,2,3]} />

// 3. Function (event handler / callback)
<Button onClick={() => console.log('clicked')} />

// 4. JSX / Component (children)
<Card><p>I am a child!</p></Card>

// 5. Spreading props
const props = { name: 'Alice', age: 22 };
<UserCard {...props} />   // Same as: <UserCard name="Alice" age={22} />
```

### Default Props

```jsx
function Button({ label, variant = 'primary', size = 'md', disabled = false }) {
  return (
    <button className={`btn-${variant} btn-${size}`} disabled={disabled}>
      {label}
    </button>
  );
}

// Or using defaultProps (legacy class component style):
Button.defaultProps = { variant: 'primary', size: 'md' };
```

### children Prop

```jsx
function Card({ title, children }) {
  return (
    <div className="card">
      <h3>{title}</h3>
      <div className="card-body">{children}</div>
    </div>
  );
}

// Usage:
<Card title="Info">
  <p>Any content here becomes children</p>
  <button>Click me</button>
</Card>
```

### Props vs State

| Feature | Props | State |
|---------|-------|-------|
| Who sets it | Parent component | The component itself |
| Mutable? | No (read-only) | Yes (via setState/useState) |
| Triggers re-render | Yes (when parent re-renders) | Yes (when updated) |
| Scope | Passed down | Local to component |

---

<a name="q6"></a>
## Q6. What is State? useState Hook?

**Answer:**

**State** is data that belongs to and is managed by a component. When state changes, React **re-renders** the component to reflect the new UI. State is **local and private** to the component.

### useState Syntax

```jsx
const [state, setState] = useState(initialValue);
//     ↑            ↑              ↑
//  current    setter function   initial value
//  value
```

### Basic Examples

```jsx
import { useState } from 'react';

function Counter() {
  const [count, setCount] = useState(0);

  return (
    <div>
      <p>Count: {count}</p>
      <button onClick={() => setCount(count + 1)}>+</button>
      <button onClick={() => setCount(count - 1)}>-</button>
      <button onClick={() => setCount(0)}>Reset</button>
    </div>
  );
}
```

### Functional Update (use when new state depends on old state)

```jsx
// ❌ Stale closure bug (may use outdated count)
setCount(count + 1);
setCount(count + 1);   // Both use same 'count', result: +1 not +2

// ✅ Functional update — guaranteed latest state
setCount(prev => prev + 1);
setCount(prev => prev + 1);   // result: +2 ✅
```

### State with Objects and Arrays

```jsx
function Form() {
  const [form, setForm] = useState({ name: '', email: '' });

  // ✅ Always spread existing state when updating objects
  const handleChange = (e) => {
    setForm(prev => ({
      ...prev,
      [e.target.name]: e.target.value
    }));
  };
}

function TodoList() {
  const [todos, setTodos] = useState([]);

  // ✅ Never mutate arrays directly
  const addTodo = (text) => {
    setTodos(prev => [...prev, { id: Date.now(), text, done: false }]);
  };

  const toggleTodo = (id) => {
    setTodos(prev =>
      prev.map(todo => todo.id === id ? { ...todo, done: !todo.done } : todo)
    );
  };

  const deleteTodo = (id) => {
    setTodos(prev => prev.filter(todo => todo.id !== id));
  };
}
```

### Key Rules of State
```
1. Never mutate state directly:
   ❌ state.name = 'Alice'
   ✅ setState({ ...state, name: 'Alice' })

2. State updates are asynchronous (batched in React 18)

3. Each useState call is independent

4. Initial value is only used on the FIRST render
```

---

<a name="q7"></a>
## Q7. What is the Component Lifecycle?

**Answer:**

Every React component goes through a **lifecycle**: mounting (created), updating (re-rendered), and unmounting (removed). In functional components, **useEffect** handles all lifecycle phases.

### Lifecycle Phases

```
MOUNTING                UPDATING              UNMOUNTING
────────────────────    ──────────────────    ──────────────────
Component created       Props/State changed   Component removed
     │                        │                     │
  render()               render() again         Cleanup runs
     │                        │                     │
 DOM updated             DOM updated           DOM removed
     │                        │
componentDidMount()    componentDidUpdate()
(useEffect run)        (useEffect run)
```

### Class Component Lifecycle Methods

```jsx
class MyComponent extends React.Component {
  // Mounting
  constructor(props) { super(props); }          // 1. Initialize
  static getDerivedStateFromProps() { }         // 2. Sync state from props
  render() { }                                  // 3. Render JSX
  componentDidMount() { }                       // 4. After DOM insert (API calls here)

  // Updating
  shouldComponentUpdate(nextProps, nextState) { } // Optimization
  getSnapshotBeforeUpdate() { }                 // Before DOM update
  componentDidUpdate(prevProps, prevState) { }  // After DOM update

  // Unmounting
  componentWillUnmount() { }                    // Cleanup (clear timers, cancel requests)
}
```

### Functional Component Lifecycle (useEffect)

```jsx
import { useEffect } from 'react';

function MyComponent({ userId }) {
  // componentDidMount (runs once after first render)
  useEffect(() => {
    console.log('Component mounted');
  }, []);  // empty dependency array = run once

  // componentDidMount + componentDidUpdate (runs when userId changes)
  useEffect(() => {
    fetchUser(userId);
  }, [userId]);  // runs when userId changes

  // componentWillUnmount (cleanup function)
  useEffect(() => {
    const timer = setInterval(() => tick(), 1000);

    return () => {
      clearInterval(timer);   // cleanup on unmount ✅
      console.log('Component unmounted');
    };
  }, []);

  // Runs after every render (no deps array)
  useEffect(() => {
    document.title = `Count: ${count}`;
  });
}
```

### Lifecycle Mapping

| Class Method | useEffect Equivalent |
|-------------|---------------------|
| `componentDidMount` | `useEffect(() => {}, [])` |
| `componentDidUpdate` | `useEffect(() => {}, [dep])` |
| `componentWillUnmount` | `useEffect(() => { return () => cleanup() }, [])` |
| `shouldComponentUpdate` | `React.memo` / `useMemo` |

---

<a name="q8"></a>
## Q8. What is the useEffect Hook?

**Answer:**

**useEffect** lets you perform **side effects** in functional components — operations that interact with the outside world (API calls, DOM manipulation, timers, subscriptions).

```jsx
useEffect(effectFunction, dependencyArray);
//         ↑                    ↑
//    what to run          when to re-run
```

### Dependency Array Behavior

```jsx
// 1. No dependency array → runs after EVERY render
useEffect(() => {
  console.log('Runs after every render');
});

// 2. Empty array [] → runs ONCE after first render (mount)
useEffect(() => {
  fetchInitialData();
}, []);

// 3. With deps → runs when ANY dependency changes
useEffect(() => {
  fetchUser(userId);
}, [userId]);   // Re-runs when userId changes

// 4. Cleanup function → runs before next effect + on unmount
useEffect(() => {
  const subscription = subscribe(topic);
  return () => {
    subscription.unsubscribe();   // Cleanup ✅
  };
}, [topic]);
```

### Common useEffect Patterns

```jsx
// Data fetching
function UserProfile({ userId }) {
  const [user, setUser] = useState(null);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);

  useEffect(() => {
    let cancelled = false;   // Prevent state update on unmounted component

    setLoading(true);
    fetch(`/api/users/${userId}`)
      .then(res => res.json())
      .then(data => {
        if (!cancelled) {
          setUser(data);
          setLoading(false);
        }
      })
      .catch(err => {
        if (!cancelled) setError(err.message);
      });

    return () => { cancelled = true; };  // Cleanup: cancel on unmount/re-run
  }, [userId]);

  if (loading) return <p>Loading...</p>;
  if (error)   return <p>Error: {error}</p>;
  return <div>{user?.name}</div>;
}

// Event listeners
useEffect(() => {
  const handleResize = () => setWidth(window.innerWidth);
  window.addEventListener('resize', handleResize);
  return () => window.removeEventListener('resize', handleResize);  // cleanup ✅
}, []);

// localStorage sync
useEffect(() => {
  localStorage.setItem('theme', theme);
}, [theme]);
```

### Common Mistakes

```jsx
// ❌ Missing dependency → stale closure
useEffect(() => {
  setInterval(() => console.log(count), 1000);
}, []);  // count never updates in the log!

// ✅ Include all used values
useEffect(() => {
  const id = setInterval(() => console.log(count), 1000);
  return () => clearInterval(id);
}, [count]);

// ❌ Infinite loop — object created inline changes every render
useEffect(() => {
  fetchData(options);
}, [{ id: 1 }]);  // New object every render!

// ✅ Use primitive values or useMemo
useEffect(() => {
  fetchData({ id: userId });
}, [userId]);
```

---

<a name="q9"></a>
## Q9. What is the useRef Hook?

**Answer:**

**useRef** returns a mutable ref object whose `.current` property persists across renders. It has two main use cases: **accessing DOM elements directly** and **storing mutable values** that don't trigger re-renders.

```jsx
const ref = useRef(initialValue);
// ref.current → the stored value
```

### Use Case 1 — DOM Access

```jsx
import { useRef, useEffect } from 'react';

function AutoFocusInput() {
  const inputRef = useRef(null);

  useEffect(() => {
    inputRef.current.focus();   // Focus input on mount
  }, []);

  return <input ref={inputRef} placeholder="Auto-focused!" />;
}

// Video player control
function VideoPlayer({ src }) {
  const videoRef = useRef(null);

  const play  = () => videoRef.current.play();
  const pause = () => videoRef.current.pause();

  return (
    <>
      <video ref={videoRef} src={src} />
      <button onClick={play}>Play</button>
      <button onClick={pause}>Pause</button>
    </>
  );
}
```

### Use Case 2 — Mutable Value Without Re-render

```jsx
function Timer() {
  const [time, setTime] = useState(0);
  const intervalRef = useRef(null);   // Stores timer ID — changes don't trigger re-render

  const start = () => {
    intervalRef.current = setInterval(() => {
      setTime(t => t + 1);
    }, 1000);
  };

  const stop = () => {
    clearInterval(intervalRef.current);
  };

  return (
    <div>
      <p>Time: {time}s</p>
      <button onClick={start}>Start</button>
      <button onClick={stop}>Stop</button>
    </div>
  );
}

// Track previous value
function usePrevious(value) {
  const prevRef = useRef();
  useEffect(() => {
    prevRef.current = value;   // Update AFTER render, so it lags one render
  });
  return prevRef.current;      // Returns previous render's value
}
```

### useState vs useRef

| Feature | useState | useRef |
|---------|----------|--------|
| Triggers re-render | ✅ Yes | ❌ No |
| Persists across renders | ✅ Yes | ✅ Yes |
| Mutable `.current` | N/A | ✅ Directly mutable |
| DOM access | ❌ No | ✅ Yes (via `ref` prop) |
| Use case | UI state | DOM access, timers, prev values |

---

<a name="q10"></a>
## Q10. What is the useContext Hook and Context API?

**Answer:**

**Context API** provides a way to pass data through the component tree **without prop drilling** — accessible to any component that subscribes, regardless of nesting depth.

### Without Context (Prop Drilling)

```jsx
// Data has to pass through every intermediate component
<App theme="dark">
  <Page theme="dark">           {/* doesn't use theme */}
    <Section theme="dark">      {/* doesn't use theme */}
      <Button theme="dark" />   {/* finally uses theme */}
    </Section>
  </Page>
</App>
```

### With Context API

```jsx
import { createContext, useContext, useState } from 'react';

// Step 1: Create context
const ThemeContext = createContext('light');   // 'light' is default value

// Step 2: Provide context at top level
function App() {
  const [theme, setTheme] = useState('dark');

  return (
    <ThemeContext.Provider value={{ theme, setTheme }}>
      <Page />   {/* No prop passing needed! */}
    </ThemeContext.Provider>
  );
}

// Step 3: Consume context anywhere in the tree
function Button() {
  const { theme, setTheme } = useContext(ThemeContext);

  return (
    <button
      className={`btn-${theme}`}
      onClick={() => setTheme(t => t === 'dark' ? 'light' : 'dark')}
    >
      Toggle Theme (current: {theme})
    </button>
  );
}

// Page and Section don't need to know about theme at all ✅
function Page()    { return <Section />; }
function Section() { return <Button />; }
```

### Real-World Context Pattern (with custom hook)

```jsx
// auth-context.js
const AuthContext = createContext(null);

export function AuthProvider({ children }) {
  const [user, setUser] = useState(null);

  const login  = (userData) => setUser(userData);
  const logout = () => setUser(null);

  return (
    <AuthContext.Provider value={{ user, login, logout }}>
      {children}
    </AuthContext.Provider>
  );
}

// Custom hook for cleaner consumption
export function useAuth() {
  const ctx = useContext(AuthContext);
  if (!ctx) throw new Error('useAuth must be used within AuthProvider');
  return ctx;
}

// Usage anywhere:
function NavBar() {
  const { user, logout } = useAuth();
  return user ? <button onClick={logout}>Logout ({user.name})</button> : null;
}
```

### When to use Context vs Props

| Use Props | Use Context |
|-----------|-------------|
| 1–2 levels deep | 3+ levels deep |
| Component-specific data | App-wide data |
| Explicit data flow preferred | Auth, theme, language, cart |

---

<a name="q11"></a>
## Q11. What is useReducer?

**Answer:**

**useReducer** is an alternative to `useState` for managing **complex state logic** — especially when next state depends on the previous state or when multiple related state variables need to change together.

```jsx
const [state, dispatch] = useReducer(reducer, initialState);
```

### Counter Example

```jsx
import { useReducer } from 'react';

// Reducer: pure function (state, action) → newState
function counterReducer(state, action) {
  switch (action.type) {
    case 'INCREMENT': return { count: state.count + 1 };
    case 'DECREMENT': return { count: state.count - 1 };
    case 'RESET':     return { count: 0 };
    case 'SET':       return { count: action.payload };
    default:          return state;  // Always have a default!
  }
}

function Counter() {
  const [state, dispatch] = useReducer(counterReducer, { count: 0 });

  return (
    <div>
      <p>Count: {state.count}</p>
      <button onClick={() => dispatch({ type: 'INCREMENT' })}>+</button>
      <button onClick={() => dispatch({ type: 'DECREMENT' })}>-</button>
      <button onClick={() => dispatch({ type: 'RESET' })}>Reset</button>
      <button onClick={() => dispatch({ type: 'SET', payload: 10 })}>Set 10</button>
    </div>
  );
}
```

### Shopping Cart Example (Complex State)

```jsx
const cartReducer = (state, action) => {
  switch (action.type) {
    case 'ADD_ITEM':
      const exists = state.items.find(i => i.id === action.payload.id);
      if (exists) {
        return {
          ...state,
          items: state.items.map(i =>
            i.id === action.payload.id ? { ...i, qty: i.qty + 1 } : i
          )
        };
      }
      return { ...state, items: [...state.items, { ...action.payload, qty: 1 }] };

    case 'REMOVE_ITEM':
      return { ...state, items: state.items.filter(i => i.id !== action.payload) };

    case 'CLEAR':
      return { items: [] };

    default: return state;
  }
};
```

### useState vs useReducer

| Scenario | useState | useReducer |
|----------|----------|------------|
| Simple values | ✅ Perfect | Overkill |
| Multiple related state | Gets messy | ✅ Clean |
| Next state depends on previous | Use functional update | ✅ Natural |
| Complex update logic | Scattered | ✅ Centralized in reducer |
| Testing state logic | Hard | ✅ Easy (pure function) |

---

<a name="q12"></a>
## Q12. What are useMemo and useCallback?

**Answer:**

Both are **performance optimization hooks** that avoid unnecessary recomputations and re-creations across renders.

### useMemo — Memoize a Computed Value

```jsx
const memoizedValue = useMemo(() => computeExpensiveValue(a, b), [a, b]);
//                             ↑ function returning value   ↑ deps
// Only recomputes when a or b changes
```

```jsx
import { useMemo, useState } from 'react';

function ProductList({ products, filterText }) {
  // ❌ Without useMemo: filters entire list on EVERY render
  // const filtered = products.filter(p => p.name.includes(filterText));

  // ✅ With useMemo: only re-filters when products or filterText changes
  const filtered = useMemo(() =>
    products.filter(p => p.name.toLowerCase().includes(filterText.toLowerCase())),
    [products, filterText]
  );

  return <ul>{filtered.map(p => <li key={p.id}>{p.name}</li>)}</ul>;
}
```

### useCallback — Memoize a Function

```jsx
const memoizedFn = useCallback(() => doSomething(a, b), [a, b]);
// Same function reference across renders as long as a and b don't change
```

```jsx
import { useCallback, useState, memo } from 'react';

// Child component wrapped in React.memo — only re-renders if props change
const Button = memo(({ onClick, label }) => {
  console.log('Button rendered:', label);
  return <button onClick={onClick}>{label}</button>;
});

function Parent() {
  const [count, setCount] = useState(0);
  const [text,  setText]  = useState('');

  // ❌ Without useCallback: new function reference on every render
  //    → Button always re-renders even when count changes
  // const increment = () => setCount(c => c + 1);

  // ✅ With useCallback: stable function reference
  //    → Button only re-renders when the function truly needs to change
  const increment = useCallback(() => {
    setCount(c => c + 1);
  }, []);  // No deps — this function never needs to change

  return (
    <div>
      <p>Count: {count}</p>
      <input value={text} onChange={e => setText(e.target.value)} />
      <Button onClick={increment} label="Increment" />  {/* Doesn't re-render on text change ✅ */}
    </div>
  );
}
```

### useMemo vs useCallback

| Hook | Memoizes | Returns | Use Case |
|------|----------|---------|----------|
| `useMemo` | A **value** (result of calling fn) | Computed value | Expensive calculations, derived data |
| `useCallback` | A **function** itself | The function | Event handlers passed to memoized children |

> **Rule of thumb:** Don't premature-optimize. Use these only when you have a measurable performance issue. Memoization itself has a cost.

---

<a name="q13"></a>
## Q13. What are Custom Hooks?

**Answer:**

**Custom Hooks** are JavaScript functions that start with `use` and can call other hooks. They let you **extract and reuse stateful logic** across multiple components without changing component hierarchy.

```
Custom Hook = Reusable stateful logic extracted into a function
```

### Example — useFetch

```jsx
// hooks/useFetch.js
import { useState, useEffect } from 'react';

function useFetch(url) {
  const [data,    setData]    = useState(null);
  const [loading, setLoading] = useState(true);
  const [error,   setError]   = useState(null);

  useEffect(() => {
    let cancelled = false;
    setLoading(true);
    setError(null);

    fetch(url)
      .then(res => {
        if (!res.ok) throw new Error(`HTTP ${res.status}`);
        return res.json();
      })
      .then(json => { if (!cancelled) { setData(json); setLoading(false); } })
      .catch(err => { if (!cancelled) { setError(err.message); setLoading(false); } });

    return () => { cancelled = true; };
  }, [url]);

  return { data, loading, error };
}

// Usage in any component — zero boilerplate!
function UserList() {
  const { data: users, loading, error } = useFetch('/api/users');

  if (loading) return <p>Loading...</p>;
  if (error)   return <p>Error: {error}</p>;
  return <ul>{users.map(u => <li key={u.id}>{u.name}</li>)}</ul>;
}

function Posts() {
  const { data: posts, loading } = useFetch('/api/posts');
  // Same logic, zero duplication ✅
}
```

### More Custom Hook Examples

```jsx
// useLocalStorage
function useLocalStorage(key, initialValue) {
  const [value, setValue] = useState(() => {
    try { return JSON.parse(localStorage.getItem(key)) ?? initialValue; }
    catch { return initialValue; }
  });

  const setStoredValue = (newValue) => {
    setValue(newValue);
    localStorage.setItem(key, JSON.stringify(newValue));
  };

  return [value, setStoredValue];
}

// useDebounce
function useDebounce(value, delay = 500) {
  const [debounced, setDebounced] = useState(value);

  useEffect(() => {
    const timer = setTimeout(() => setDebounced(value), delay);
    return () => clearTimeout(timer);
  }, [value, delay]);

  return debounced;
}

// useWindowSize
function useWindowSize() {
  const [size, setSize] = useState({ w: window.innerWidth, h: window.innerHeight });

  useEffect(() => {
    const handler = () => setSize({ w: window.innerWidth, h: window.innerHeight });
    window.addEventListener('resize', handler);
    return () => window.removeEventListener('resize', handler);
  }, []);

  return size;
}
```

### Rules of Hooks (apply to custom hooks too)
```
1. Only call hooks at the TOP LEVEL — never inside loops, conditions, nested functions
2. Only call hooks from REACT FUNCTIONS — functional components or custom hooks
3. Custom hooks MUST start with 'use'
```

---

<a name="q14"></a>
## Q14. What is Lifting State Up?

**Answer:**

**Lifting state up** means moving state to the **closest common ancestor** of components that need to share it. This is the primary React pattern for sharing state between sibling components.

### Problem: Siblings Need to Share State

```jsx
// ❌ Each component has its own state — can't share
function TempCelsius() {
  const [temp, setTemp] = useState(0);
  return <input value={temp} onChange={e => setTemp(e.target.value)} />;
}

function TempFahrenheit() {
  const [temp, setTemp] = useState(32);
  return <input value={temp} onChange={e => setTemp(e.target.value)} />;
}
// These two inputs are completely independent ❌
```

### Solution: Lift State to Common Parent

```jsx
// ✅ Parent owns the state, passes down via props
function TemperatureConverter() {
  const [celsius, setCelsius] = useState('');

  const fahrenheit = celsius !== '' ? (celsius * 9/5 + 32).toFixed(1) : '';

  return (
    <div>
      <h2>Temperature Converter</h2>
      <label>
        Celsius:
        <input
          value={celsius}
          onChange={e => setCelsius(e.target.value)}
          type="number"
        />
      </label>
      <label>
        Fahrenheit:
        <input
          value={fahrenheit}
          onChange={e => setCelsius(((e.target.value - 32) * 5/9).toFixed(1))}
          type="number"
        />
      </label>
      <p>{celsius}°C = {fahrenheit}°F</p>
    </div>
  );
}
```

### When to Lift State

```
Ask: "Which components need to read or write this state?"
     ↓
Find their closest common ancestor
     ↓
Put state there, pass down via props (read) and callbacks (write)

Component A ─┐
             ├── Common Parent (owns state) → pass data as props
Component B ─┘                             → pass setter as callback
```

---

<a name="q15"></a>
## Q15. What are Controlled vs Uncontrolled Components?

**Answer:**

This distinction applies mainly to **form elements** (`input`, `textarea`, `select`).

### Controlled Component
React **controls** the form element's value via state. The element's value always reflects the React state — single source of truth.

```jsx
function ControlledForm() {
  const [name, setName] = useState('');
  const [email, setEmail] = useState('');

  const handleSubmit = (e) => {
    e.preventDefault();
    console.log({ name, email });   // State is the source of truth
  };

  return (
    <form onSubmit={handleSubmit}>
      <input
        value={name}                          // ← React controls the value
        onChange={e => setName(e.target.value)}  // ← Update state on change
        placeholder="Name"
      />
      <input
        value={email}
        onChange={e => setEmail(e.target.value)}
        type="email"
      />
      <button type="submit">Submit</button>
    </form>
  );
}
```

### Uncontrolled Component
The DOM controls its own state. React accesses the value via a **ref** only when needed (e.g., on submit).

```jsx
import { useRef } from 'react';

function UncontrolledForm() {
  const nameRef  = useRef();
  const emailRef = useRef();

  const handleSubmit = (e) => {
    e.preventDefault();
    console.log({
      name:  nameRef.current.value,    // Read from DOM on demand
      email: emailRef.current.value
    });
  };

  return (
    <form onSubmit={handleSubmit}>
      <input ref={nameRef} defaultValue="" placeholder="Name" />
      <input ref={emailRef} defaultValue="" type="email" />
      <button type="submit">Submit</button>
    </form>
  );
}
```

### Controlled vs Uncontrolled

| Feature | Controlled | Uncontrolled |
|---------|-----------|--------------|
| Source of truth | React state | DOM |
| Access value | Any time (from state) | On demand (via ref) |
| Validation | Easy (on each keystroke) | Only on submit |
| Instant feedback | ✅ Easy | ❌ Hard |
| Simplicity | More code | Less code |
| Recommended | ✅ Default choice | File inputs, performance-critical |

> **React recommends Controlled components** for most use cases as they provide predictable behavior and easier testing.

---

<a name="q16"></a>
## Q16. What is Event Handling in React?

**Answer:**

React uses **SyntheticEvents** — a cross-browser wrapper around the browser's native events. React attaches a **single event listener** at the root (event delegation) rather than on each individual element.

```jsx
// HTML: onclick (lowercase)
// React: onClick (camelCase)

function EventDemo() {
  // 1. Basic click handler
  const handleClick = (e) => {
    e.preventDefault();      // Prevent default browser behavior
    e.stopPropagation();     // Stop event bubbling
    console.log('Clicked!', e.target);
  };

  // 2. Handler with parameter
  const handleItemClick = (id) => (e) => {
    console.log('Item clicked:', id);
  };

  // 3. Inline handler (avoid for complex logic)
  return (
    <div onClick={() => console.log('div clicked')}>  {/* Bubbles up */}
      <button onClick={handleClick}>Click me</button>
      <button onClick={handleItemClick(42)}>Item 42</button>

      {/* Form events */}
      <input
        onChange={e => console.log(e.target.value)}
        onFocus={() => console.log('focused')}
        onBlur={() => console.log('blurred')}
        onKeyDown={e => e.key === 'Enter' && handleSubmit()}
      />

      {/* Mouse events */}
      <div
        onMouseEnter={() => console.log('enter')}
        onMouseLeave={() => console.log('leave')}
        onMouseMove={e => console.log(e.clientX, e.clientY)}
      />
    </div>
  );
}
```

### Passing Arguments to Handlers

```jsx
// ✅ Using arrow function (creates new fn each render — ok for most cases)
<button onClick={() => handleDelete(item.id)}>Delete</button>

// ✅ Using curried function (no new fn each render)
const handleDelete = (id) => () => { /* delete logic */ };
<button onClick={handleDelete(item.id)}>Delete</button>

// ❌ Wrong — calls function immediately instead of on click
<button onClick={handleDelete(item.id)}>Delete</button>
// Fix: wrap in arrow function OR curry
```

### Event Delegation in React
```
React 17+: Attaches one listener per event type to the ROOT container
React < 17: Attaches to document

Benefits:
  - Memory efficient (not one listener per element)
  - Works with dynamically added elements
  - Enables React's event system (batching, synthetic events)
```

---

<a name="q17"></a>
## Q17. What are Keys in React lists?

**Answer:**

**Keys** are special string attributes that help React identify which items in a list have **changed, been added, or been removed**. They must be **unique among siblings**.

```jsx
// ✅ Always provide keys when rendering lists
function TodoList({ todos }) {
  return (
    <ul>
      {todos.map(todo => (
        <li key={todo.id}>          {/* key = stable, unique ID */}
          {todo.text}
        </li>
      ))}
    </ul>
  );
}
```

### Why Keys Matter — Without Keys

```
Old list:  [A, B, C]
New list:  [X, A, B, C]  (insert X at beginning)

Without key: React compares by position
  Position 0: A → X (update DOM) ← unnecessary
  Position 1: B → A (update DOM) ← unnecessary
  Position 2: C → B (update DOM) ← unnecessary
  Position 3: -- → C (insert)    ← adds at end
  Result: 3 updates + 1 insert = 4 operations ❌

With key: React compares by identity
  key=X: new → insert at beginning
  key=A: same → no DOM change
  key=B: same → no DOM change
  key=C: same → no DOM change
  Result: 1 insert = 1 operation ✅
```

### Common Key Mistakes

```jsx
// ❌ Using array index as key — BAD for reordering/inserting
{items.map((item, index) => (
  <Item key={index} value={item} />   // index changes when list reorders!
))}

// ✅ Use stable, unique IDs
{items.map(item => (
  <Item key={item.id} value={item} />
))}

// ❌ Non-unique keys (same key in siblings)
<li key="item">First</li>
<li key="item">Second</li>  // Duplicate key! ❌

// ✅ Keys must only be unique among SIBLINGS (not globally)
// Keys in different lists don't conflict
```

### When index as key is acceptable
```
Only use index as key when:
  1. The list is static and will never reorder or filter
  2. Items have no stable IDs
  3. The list will never be re-rendered (rare)
```

---

<a name="q18"></a>
## Q18. What is Conditional Rendering?

**Answer:**

React can **conditionally render components or elements** based on state, props, or any JavaScript expression.

```jsx
// 1. if/else (for complex conditions, outside JSX)
function UserGreeting({ user }) {
  if (!user) {
    return <p>Please log in.</p>;
  }
  if (user.isAdmin) {
    return <AdminPanel user={user} />;
  }
  return <UserDashboard user={user} />;
}

// 2. Ternary operator (inline, for simple two-way)
function Status({ isOnline }) {
  return (
    <span style={{ color: isOnline ? 'green' : 'red' }}>
      {isOnline ? '🟢 Online' : '🔴 Offline'}
    </span>
  );
}

// 3. Logical && (render only if true)
function Notification({ count }) {
  return (
    <div>
      <h1>Inbox</h1>
      {count > 0 && <p>You have {count} new messages</p>}
      {/* If count=0, renders nothing (0 renders "0"!) */}
    </div>
  );
}

// ⚠️ Gotcha: count=0 would render "0" — use !! or convert to boolean
{!!count && <p>{count} messages</p>}  // ✅ 0 → false → renders nothing

// 4. Nullish coalescing / optional render
{user?.premium && <PremiumBadge />}

// 5. Switch-based pattern (for multiple conditions)
function Alert({ type, message }) {
  const icons = {
    success: '✅',
    error:   '❌',
    warning: '⚠️',
    info:    'ℹ️'
  };
  return (
    <div className={`alert alert-${type}`}>
      {icons[type]} {message}
    </div>
  );
}
```

---

<a name="q19"></a>
## Q19. What are Higher-Order Components (HOC)?

**Answer:**

A **Higher-Order Component** is a function that takes a component and returns a **new enhanced component**. It's a pattern for reusing component logic without changing the original component.

```
HOC: Component → Enhanced Component
hoc(WrappedComponent) → NewComponent
```

```jsx
// HOC: withLoading — adds loading state to any component
function withLoading(WrappedComponent) {
  return function WithLoadingComponent({ isLoading, ...props }) {
    if (isLoading) {
      return (
        <div className="loading-wrapper">
          <span>Loading...</span>
        </div>
      );
    }
    return <WrappedComponent {...props} />;
  };
}

// Usage
function UserList({ users }) {
  return <ul>{users.map(u => <li key={u.id}>{u.name}</li>)}</ul>;
}

const UserListWithLoading = withLoading(UserList);

function App() {
  const { data, loading } = useFetch('/api/users');
  return <UserListWithLoading isLoading={loading} users={data} />;
}

// HOC: withAuth — protect routes
function withAuth(WrappedComponent) {
  return function AuthenticatedComponent(props) {
    const { user } = useAuth();
    if (!user) return <Navigate to="/login" />;
    return <WrappedComponent {...props} />;
  };
}

const ProtectedDashboard = withAuth(Dashboard);
```

### HOC Rules
```
1. Don't mutate the wrapped component — return a new one
2. Pass through all props with {...props}
3. Copy static methods (or use hoist-non-react-statics library)
4. Display name for debugging: WrappedComponent.displayName
```

### HOC vs Custom Hooks (Modern Alternative)
```
HOC:          Adds to component tree (extra wrapper)
Custom Hook:  Logic only, no extra DOM node (preferred in modern React)

Both solve the same problem differently.
Use Custom Hooks first; HOC when you need to wrap JSX.
```

---

<a name="q20"></a>
## Q20. What are React Portals?

**Answer:**

**Portals** let you render a child component into a **DOM node outside the parent component's DOM hierarchy**, while still maintaining React's event bubbling and context.

### The Problem
```
App DOM tree:
  <div id="root">            ← React renders everything here
    <Modal>                  ← Modal is trapped inside a parent with overflow:hidden
      ...                       or z-index issues
    </Modal>
  </div>

Solution: Render Modal at document.body level (or any other node)
```

### Creating a Portal

```jsx
import { createPortal } from 'react-dom';

function Modal({ isOpen, onClose, children }) {
  if (!isOpen) return null;

  return createPortal(
    // JSX to render
    <div className="modal-overlay" onClick={onClose}>
      <div className="modal-content" onClick={e => e.stopPropagation()}>
        <button className="modal-close" onClick={onClose}>✕</button>
        {children}
      </div>
    </div>,
    // DOM node to render into
    document.body   // Rendered outside #root, no z-index/overflow issues ✅
  );
}

// Usage
function App() {
  const [showModal, setShowModal] = useState(false);

  return (
    <div style={{ overflow: 'hidden' }}>   {/* Would trap normal modal */}
      <button onClick={() => setShowModal(true)}>Open Modal</button>

      <Modal isOpen={showModal} onClose={() => setShowModal(false)}>
        <h2>I'm in document.body!</h2>
        <p>Even though I'm rendered in App, I escape the overflow:hidden</p>
      </Modal>
    </div>
  );
}
```

### Key Portal Behaviors
```
✅ Event bubbling works normally through React tree (not DOM tree)
✅ Context values are available inside portal
✅ Works with React lifecycle
✅ Use cases: Modals, tooltips, dropdowns, toast notifications
```

---

<a name="q21"></a>
## Q21. What are Error Boundaries?

**Answer:**

**Error Boundaries** are class components that catch JavaScript errors anywhere in their child component tree and display a **fallback UI** instead of crashing the entire application.

```jsx
import { Component } from 'react';

class ErrorBoundary extends Component {
  constructor(props) {
    super(props);
    this.state = { hasError: false, error: null };
  }

  // Called when a child throws an error
  static getDerivedStateFromError(error) {
    return { hasError: true, error };
  }

  // Called for logging the error
  componentDidCatch(error, errorInfo) {
    console.error('Error caught:', error);
    console.error('Component stack:', errorInfo.componentStack);
    // logErrorToService(error, errorInfo);  // Send to Sentry, etc.
  }

  render() {
    if (this.state.hasError) {
      return (
        <div className="error-fallback">
          <h2>Something went wrong 😕</h2>
          <p>{this.state.error?.message}</p>
          <button onClick={() => this.setState({ hasError: false, error: null })}>
            Try Again
          </button>
        </div>
      );
    }
    return this.props.children;
  }
}

// Usage — wrap risky parts of your app
function App() {
  return (
    <ErrorBoundary>
      <Header />
      <ErrorBoundary fallback={<p>Feed failed to load</p>}>
        <NewsFeed />          {/* If this crashes, only this section shows error */}
      </ErrorBoundary>
      <ErrorBoundary>
        <Sidebar />
      </ErrorBoundary>
    </ErrorBoundary>
  );
}
```

### What Error Boundaries DON'T catch
```
❌ Event handlers (use try-catch inside handler)
❌ Async code (setTimeout, promises) — use try-catch
❌ Server-side rendering
❌ Errors in the error boundary itself
✅ Render errors
✅ Lifecycle method errors
✅ Constructor errors in child tree
```

> **Note:** There is no functional component equivalent for error boundaries yet — you must use class components (or a library like `react-error-boundary`).

---

<a name="q22"></a>
## Q22. What is Code Splitting and React.lazy?

**Answer:**

**Code splitting** breaks your bundle into smaller chunks that are **loaded on demand** rather than all upfront. **React.lazy** enables component-level code splitting.

```jsx
import { lazy, Suspense } from 'react';

// ❌ Without code splitting — entire app loaded upfront
import HeavyDashboard from './HeavyDashboard';

// ✅ With lazy — Dashboard chunk only loaded when needed
const HeavyDashboard = lazy(() => import('./HeavyDashboard'));
// import() returns a Promise → dynamic import

function App() {
  return (
    <Suspense fallback={<div>Loading dashboard...</div>}>
      {/* HeavyDashboard JS chunk loaded only when this renders */}
      <HeavyDashboard />
    </Suspense>
  );
}
```

### Route-Based Code Splitting (Best Practice)

```jsx
import { lazy, Suspense } from 'react';
import { BrowserRouter, Routes, Route } from 'react-router-dom';

// Each route loads its own chunk
const Home      = lazy(() => import('./pages/Home'));
const About     = lazy(() => import('./pages/About'));
const Dashboard = lazy(() => import('./pages/Dashboard'));
const Settings  = lazy(() => import('./pages/Settings'));

function App() {
  return (
    <BrowserRouter>
      <Suspense fallback={<PageLoader />}>
        <Routes>
          <Route path="/"          element={<Home />} />
          <Route path="/about"     element={<About />} />
          <Route path="/dashboard" element={<Dashboard />} />
          <Route path="/settings"  element={<Settings />} />
        </Routes>
      </Suspense>
    </BrowserRouter>
  );
}
// Initial bundle is tiny — other routes load only when navigated to ✅
```

### Benefits
```
Before: app.bundle.js → 2MB (user downloads everything)
After:
  main.bundle.js  → 200KB (initial load — fast!)
  dashboard.chunk → 400KB (loaded only when /dashboard visited)
  settings.chunk  → 150KB (loaded only when /settings visited)
```

---

<a name="q23"></a>
## Q23. What is React.memo?

**Answer:**

**React.memo** is a Higher-Order Component that **memoizes** a functional component. A memoized component will **skip re-rendering** if its props haven't changed (shallow comparison).

```jsx
import { memo } from 'react';

// Without memo — re-renders whenever parent re-renders
function ExpensiveCard({ user }) {
  console.log('ExpensiveCard rendered');
  return <div>{user.name}: {computeHeavyMetric(user)}</div>;
}

// With memo — only re-renders when user prop changes
const ExpensiveCard = memo(function ExpensiveCard({ user }) {
  console.log('ExpensiveCard rendered');
  return <div>{user.name}: {computeHeavyMetric(user)}</div>;
});

// Parent
function Dashboard() {
  const [count, setCount] = useState(0);
  const user = { id: 1, name: 'Alice' };  // ← Problem: new object each render!

  return (
    <div>
      <button onClick={() => setCount(c => c + 1)}>Count: {count}</button>
      <ExpensiveCard user={user} />  {/* Still re-renders! New object reference ❌ */}
    </div>
  );
}
```

### Fix: Stable References with useMemo/useCallback

```jsx
function Dashboard() {
  const [count, setCount] = useState(0);

  // ✅ useMemo → stable object reference
  const user = useMemo(() => ({ id: 1, name: 'Alice' }), []);

  // ✅ useCallback → stable function reference
  const handleUpdate = useCallback(() => { /* ... */ }, []);

  return (
    <div>
      <button onClick={() => setCount(c => c + 1)}>Count: {count}</button>
      <ExpensiveCard user={user} onUpdate={handleUpdate} />
      {/* Now truly skips re-render when count changes ✅ */}
    </div>
  );
}
```

### Custom Comparison Function

```jsx
const UserCard = memo(
  function UserCard({ user }) {
    return <div>{user.name}</div>;
  },
  // Custom comparison: re-render only when id or name changes
  (prevProps, nextProps) =>
    prevProps.user.id   === nextProps.user.id &&
    prevProps.user.name === nextProps.user.name
);
```

---

<a name="q24"></a>
## Q24. What is Prop Drilling and how to avoid it?

**Answer:**

**Prop drilling** is passing data through many intermediate components that don't need it, just to get it to a deeply nested component that does.

```jsx
// ❌ Prop drilling — theme passed through 4 levels
function App() {
  const [theme] = useState('dark');
  return <Page theme={theme} />;            // Page doesn't use theme
}
function Page({ theme }) {
  return <Section theme={theme} />;         // Section doesn't use theme
}
function Section({ theme }) {
  return <Widget theme={theme} />;          // Widget doesn't use theme
}
function Widget({ theme }) {
  return <div className={`widget-${theme}`}>Finally using theme!</div>;
}
```

### Solutions

#### 1. Context API (Best for truly global data)
```jsx
const ThemeContext = createContext('light');

function App() {
  return (
    <ThemeContext.Provider value="dark">
      <Page />  {/* No prop needed */}
    </ThemeContext.Provider>
  );
}

function Widget() {
  const theme = useContext(ThemeContext);  // Directly access ✅
  return <div className={`widget-${theme}`}>No drilling!</div>;
}
```

#### 2. Component Composition (Children Pattern)
```jsx
// ✅ Pass components as children — avoids intermediate passing
function App() {
  const [theme] = useState('dark');
  return (
    <Page>
      <Section>
        <Widget theme={theme} />  {/* Direct — no intermediaries */}
      </Section>
    </Page>
  );
}
function Page({ children })    { return <div>{children}</div>; }
function Section({ children }) { return <div>{children}</div>; }
```

#### 3. State Management Library (Redux, Zustand, Jotai)
```jsx
// Zustand store
const useStore = create(set => ({
  theme: 'dark',
  setTheme: (t) => set({ theme: t })
}));

// Any component can access directly
function Widget() {
  const theme = useStore(state => state.theme);
  return <div className={`widget-${theme}`}>Zustand!</div>;
}
```

---

<a name="q25"></a>
## Q25. What is React Router?

**Answer:**

**React Router** is the standard routing library for React, enabling **client-side navigation** in Single Page Applications without full page reloads.

```bash
npm install react-router-dom
```

### Basic Setup (React Router v6)

```jsx
import { BrowserRouter, Routes, Route, Link,
         useNavigate, useParams, NavLink } from 'react-router-dom';

function App() {
  return (
    <BrowserRouter>
      <nav>
        <NavLink to="/"       end>Home</NavLink>  {/* end = exact match */}
        <NavLink to="/about"     >About</NavLink>
        <NavLink to="/users"     >Users</NavLink>
      </nav>

      <Routes>
        <Route path="/"              element={<Home />} />
        <Route path="/about"         element={<About />} />
        <Route path="/users"         element={<UserList />} />
        <Route path="/users/:id"     element={<UserDetail />} />  {/* Dynamic segment */}
        <Route path="*"              element={<NotFound />} />   {/* 404 */}
      </Routes>
    </BrowserRouter>
  );
}

// Access URL params
function UserDetail() {
  const { id } = useParams();   // /users/42 → id = "42"
  const { data: user } = useFetch(`/api/users/${id}`);
  return <div>{user?.name}</div>;
}

// Programmatic navigation
function LoginForm() {
  const navigate = useNavigate();

  const handleLogin = async () => {
    await login();
    navigate('/dashboard');          // Redirect after login
    navigate(-1);                    // Go back (like history.back())
    navigate('/dashboard', { replace: true });  // Replace in history
  };
}

// Nested Routes
<Route path="/dashboard" element={<DashboardLayout />}>
  <Route index          element={<DashboardHome />} />     {/* /dashboard */}
  <Route path="profile" element={<Profile />} />           {/* /dashboard/profile */}
  <Route path="settings" element={<Settings />} />         {/* /dashboard/settings */}
</Route>
```

---

<a name="q26"></a>
## Q26. What is Reconciliation and the Diffing Algorithm?

**Answer:**

**Reconciliation** is the process React uses to update the DOM when state or props change. The **diffing algorithm** compares the old and new Virtual DOM trees to find the minimal set of changes needed.

### Diffing Rules

#### Rule 1: Different element types → Tear down and rebuild
```jsx
// Old: <div><Counter /></div>
// New: <span><Counter /></span>
// → div → span: different type → destroy entire subtree (including Counter state!)
//   and rebuild from scratch
```

#### Rule 2: Same element type → Update attributes only
```jsx
// Old: <div className="before" title="a" />
// New: <div className="after"  title="a" />
// → Same 'div' type → only update className, title stays ✅
```

#### Rule 3: Keys help with list reconciliation
```jsx
// Old: [<li key="A">, <li key="B">, <li key="C">]
// New: [<li key="A">, <li key="X">, <li key="B">, <li key="C">]
// With keys: React inserts X at position 1, keeps A, B, C ✅
// Without keys: React would update all 4 items ❌
```

### Fiber Architecture (React 16+)
```
React Fiber = complete rewrite of reconciliation engine

Old (Stack Reconciler): Synchronous — once started, couldn't be interrupted
New (Fiber):            Asynchronous — work split into units, can pause/resume/abort

Enables:
  - Concurrent Mode (React 18)
  - Priority-based rendering
  - Suspense
  - Time-slicing
```

### Tree Comparison Heuristics
```
O(n³) → naive tree diff: too slow for UI
O(n)  → React's heuristic diff:
  1. Only compare nodes at same level (no cross-level moves)
  2. Same type = update, different type = rebuild
  3. Keys identify children in lists
```

---

<a name="q27"></a>
## Q27. What are Fragments?

**Answer:**

**Fragments** let you group multiple elements without adding extra nodes to the DOM. Every component must return a single root — Fragments solve this without wrapping divs.

```jsx
// ❌ Extra div pollutes DOM — breaks CSS (flexbox, grid), adds nesting
function TableRows() {
  return (
    <div>           {/* Not valid in <tbody> context! */}
      <tr><td>Name</td></tr>
      <tr><td>Age</td></tr>
    </div>
  );
}

// ✅ Fragment — no extra DOM node
function TableRows() {
  return (
    <>
      <tr><td>Name</td></tr>
      <tr><td>Age</td></tr>
    </>
  );
}

// ✅ Explicit Fragment syntax (needed when passing key)
function ItemList({ items }) {
  return items.map(item => (
    <React.Fragment key={item.id}>   {/* key only works on React.Fragment, not <> */}
      <dt>{item.term}</dt>
      <dd>{item.description}</dd>
    </React.Fragment>
  ));
}
```

---

<a name="q28"></a>
## Q28. What is Strict Mode in React?

**Answer:**

**React.StrictMode** is a tool for **highlighting potential problems** in your application during development. It does not render any visible UI and has **no effect in production**.

```jsx
import { StrictMode } from 'react';

const root = ReactDOM.createRoot(document.getElementById('root'));
root.render(
  <StrictMode>
    <App />
  </StrictMode>
);
```

### What Strict Mode Does (Development Only)

```
1. Double-invokes render and lifecycle methods
   → Detects side effects in render (renders are expected to be pure)
   → Why: Future Concurrent Mode may render components multiple times

2. Warns about deprecated lifecycle methods
   → componentWillMount, componentWillReceiveProps, componentWillUpdate

3. Warns about legacy string ref API
   → ref="myRef"  ← deprecated
   → Use useRef() instead

4. Warns about findDOMNode usage
   → Deprecated, use refs

5. Detects unexpected side effects
   → useEffect cleanup called twice on mount to verify correctness

6. Detects legacy Context API usage
```

### Why Double-Invoke?
```jsx
// React calls render() TWICE to detect:
function Counter() {
  const value = expensiveSideEffect();  // ← If this runs, it'll be caught!
  return <div>{value}</div>;
}
// Renders should be pure — no side effects!
// This is preparation for Concurrent Mode (React 18)
```

---

<a name="q29"></a>
## Q29. What is React 18's Concurrent Mode and key features?

**Answer:**

**Concurrent Mode** is React 18's major architectural upgrade. It makes rendering **interruptible** — React can pause, resume, or abandon renders to keep the UI responsive.

### Key React 18 Features

#### 1. Automatic Batching
```jsx
// React 17: Only batches inside React event handlers
setTimeout(() => {
  setCount(c => c + 1);  // Re-render 1
  setFlag(f => !f);      // Re-render 2  ← 2 separate renders ❌
}, 1000);

// React 18: Batches EVERYWHERE (timeouts, promises, native events)
setTimeout(() => {
  setCount(c => c + 1);  // ─┐
  setFlag(f => !f);      //  ├─ Only 1 re-render ✅
}, 1000);                //  ┘
```

#### 2. useTransition — Mark Updates as Non-Urgent
```jsx
import { useState, useTransition } from 'react';

function SearchResults({ items }) {
  const [query, setQuery] = useState('');
  const [results, setResults] = useState(items);
  const [isPending, startTransition] = useTransition();

  const handleSearch = (e) => {
    setQuery(e.target.value);         // Urgent: update input immediately

    startTransition(() => {
      // Non-urgent: can be interrupted/deferred
      setResults(items.filter(i => i.includes(e.target.value)));
    });
  };

  return (
    <>
      <input value={query} onChange={handleSearch} />
      {isPending && <p>Updating...</p>}
      <ul>{results.map(r => <li key={r}>{r}</li>)}</ul>
    </>
  );
}
```

#### 3. useDeferredValue — Defer a Value
```jsx
import { useDeferredValue } from 'react';

function App() {
  const [text, setText] = useState('');
  const deferredText = useDeferredValue(text);  // Lags behind text

  return (
    <>
      <input value={text} onChange={e => setText(e.target.value)} />
      <SlowList query={deferredText} />  {/* Uses deferred value — won't block typing */}
    </>
  );
}
```

#### 4. New Root API
```jsx
// React 17 (legacy)
ReactDOM.render(<App />, document.getElementById('root'));

// React 18 (new root API — enables concurrent features)
import { createRoot } from 'react-dom/client';
const root = createRoot(document.getElementById('root'));
root.render(<App />);
```

---

<a name="q30"></a>
## Q30. Common React Performance Optimization Techniques

**Answer:**

Performance optimization in React revolves around **avoiding unnecessary re-renders** and **reducing work per render**.

### 1. React.memo — Skip Re-renders
```jsx
const MemoizedComponent = memo(MyComponent);
// Only re-renders when props change (shallow comparison)
```

### 2. useMemo / useCallback — Stable References
```jsx
const value = useMemo(() => expensiveCalc(data), [data]);
const fn     = useCallback(() => handleSubmit(id), [id]);
```

### 3. Code Splitting — Reduce Bundle Size
```jsx
const HeavyPage = lazy(() => import('./HeavyPage'));
```

### 4. Virtualization — Render Only Visible Items
```jsx
// Without virtualization: 10,000 DOM nodes = laggy
// With react-window: only ~20 visible DOM nodes rendered

import { FixedSizeList } from 'react-window';

<FixedSizeList height={600} itemCount={10000} itemSize={50}>
  {({ index, style }) => <div style={style}>Item {index}</div>}
</FixedSizeList>
```

### 5. Avoid Anonymous Functions / Objects in JSX (when using memo)
```jsx
// ❌ New reference on every render — breaks React.memo
<Button onClick={() => handleClick(id)} style={{ color: 'red' }} />

// ✅ Stable references
const handleClickMemo = useCallback(() => handleClick(id), [id]);
const buttonStyle = useMemo(() => ({ color: 'red' }), []);
<Button onClick={handleClickMemo} style={buttonStyle} />
```

### 6. State Colocation — Keep State Close to Where It's Used
```jsx
// ❌ Lifting state too high causes unnecessary parent re-renders
function App() {
  const [inputValue, setInputValue] = useState('');   // Only Search needs this
  return <><Search value={inputValue} onChange={setInputValue} /><Header /></>;
}

// ✅ Keep state local — Header never re-renders
function Search() {
  const [value, setValue] = useState('');
  return <input value={value} onChange={e => setValue(e.target.value)} />;
}
```

### 7. Key Placement — Force Remount When Needed
```jsx
// Reset a component's state by changing its key
<Form key={userId} userId={userId} />
// When userId changes, React unmounts and remounts Form with fresh state
```

### 8. Production Build
```bash
npm run build  # Minified, optimized, no dev warnings
# Development build is 2-3x slower than production
```

### Performance Checklist

```
✅ Use React DevTools Profiler to identify bottlenecks
✅ React.memo on expensive pure components
✅ useCallback for functions passed to memoized children
✅ useMemo for expensive computations
✅ Code split at route level (React.lazy + Suspense)
✅ Virtualize long lists (react-window / react-virtual)
✅ Avoid unnecessary state lifts
✅ Batch related state updates
✅ Avoid deep object/array state when shallow works
✅ Use production build for benchmarking
```

---

## 📌 Quick Revision Cheat Sheet

```
┌──────────────────────────────────────────────────────────────────────────┐
│                     React.js — At a Glance                               │
├──────────────────────────┬───────────────────────────────────────────────┤
│ JSX                      │ HTML-like syntax → React.createElement()      │
│ Virtual DOM              │ JS object tree → diff → minimal real DOM patch│
│ Component                │ Function returning JSX; composable + reusable  │
│ Props                    │ Parent → Child, read-only                      │
│ State (useState)         │ Local mutable data, triggers re-render         │
│ useEffect                │ Side effects; deps control when to run        │
│ useRef                   │ DOM access + mutable non-render-triggering val │
│ useContext               │ Global data without prop drilling              │
│ useReducer               │ Complex state logic (Redux-like)               │
│ useMemo                  │ Memoize computed value                         │
│ useCallback              │ Memoize function reference                     │
│ Custom Hook              │ Reusable stateful logic (starts with 'use')    │
│ Lifting State Up         │ Move shared state to common ancestor           │
│ Controlled Component     │ React state = single source of truth for input │
│ Keys                     │ Help React identify list items efficiently      │
│ React.memo               │ Skip re-render if props unchanged (HOC)        │
│ HOC                      │ Fn that takes+returns enhanced component       │
│ Portal                   │ Render child outside parent DOM hierarchy      │
│ Error Boundary           │ Catch render errors, show fallback UI          │
│ React.lazy + Suspense    │ Dynamic import + loading fallback              │
│ Context API              │ createContext → Provider → useContext          │
│ React Router v6          │ Routes, Route, useParams, useNavigate         │
│ Reconciliation           │ Virtual DOM diff → minimal real DOM updates   │
│ Strict Mode              │ Dev tool: double-invokes renders, warns legacy │
│ React 18                 │ Auto batching, useTransition, useDeferredValue │
│ Fragment                 │ <></> — group without extra DOM node           │
│ Rules of Hooks           │ Only top-level, only React functions           │
└──────────────────────────┴───────────────────────────────────────────────┘
```

---

> 💡 **Pro Interview Tips for Internship:**
> - Be clear on **when and why** to use each hook — don't just memorize syntax
> - For `useEffect`, always talk about the **cleanup function** — shows maturity
> - Know **controlled vs uncontrolled** — almost always asked for form questions
> - Explain **Virtual DOM** with the analogy: "it's a draft, React only publishes minimal changes"
> - **Keys in lists** — always mention why index is a bad key (reordering issues)
> - If asked about performance, mention **React DevTools Profiler** first — measure before optimizing

---

*Happy Coding & Good Luck with your Internship Interview! 🚀*
