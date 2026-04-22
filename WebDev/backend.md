# The Complete Backend Engineering Guide
### From JS/Node.js Foundations to Production-Ready Systems

> **Who this is for**: You know JavaScript, some Node.js/Express, MongoDB basics, and authentication concepts. This guide takes you from there to every topic that appears in backend engineering interviews — with real implementation code in every section.

---

## Table of Contents

| # | Topic | Difficulty |
|---|-------|-----------|
| 01 | [High-Level Architecture](#01-high-level-architecture) | 🟢 Beginner |
| 02 | [HTTP Protocol Deep Dive](#02-http-protocol-deep-dive) | 🟢 Beginner |
| 03 | [Routing](#03-routing) | 🟢 Beginner |
| 04 | [Serialisation & Deserialisation](#04-serialisation--deserialisation) | 🟡 Intermediate |
| 05 | [Authentication & Authorisation](#05-authentication--authorisation) | 🟡 Intermediate |
| 06 | [Validation & Transformation](#06-validation--transformation) | 🟡 Intermediate |
| 07 | [Middlewares](#07-middlewares) | 🟡 Intermediate |
| 08 | [Request Context](#08-request-context) | 🟡 Intermediate |
| 09 | [Handlers, Controllers & Services](#09-handlers-controllers--services) | 🟡 Intermediate |
| 10 | [CRUD Deep Dive](#10-crud-deep-dive) | 🟡 Intermediate |
| 11 | [RESTful Architecture & Best Practices](#11-restful-architecture--best-practices) | 🟡 Intermediate |
| 12 | [Databases](#12-databases) | 🟡 Intermediate |
| 13 | [Business Logic Layer (BLL)](#13-business-logic-layer-bll) | 🟡 Intermediate |
| 14 | [Caching](#14-caching) | 🔴 Advanced |
| 15 | [Transactional Emails](#15-transactional-emails) | 🟡 Intermediate |
| 16 | [Task Queuing & Scheduling](#16-task-queuing--scheduling) | 🔴 Advanced |
| 17 | [Elasticsearch](#17-elasticsearch) | 🔴 Advanced |
| 18 | [Error Handling](#18-error-handling) | 🟡 Intermediate |
| 19 | [Config Management](#19-config-management) | 🟡 Intermediate |
| 20 | [Logging, Monitoring & Observability](#20-logging-monitoring--observability) | 🔴 Advanced |
| 21 | [Graceful Shutdown](#21-graceful-shutdown) | 🔴 Advanced |
| 22 | [Security](#22-security) | 🔴 Advanced |
| 23 | [Scaling & Performance](#23-scaling--performance) | 🔴 Advanced |
| 24 | [Concurrency & Parallelism](#24-concurrency--parallelism) | 🔴 Advanced |
| 25 | [Object Storage & Large Files](#25-object-storage--large-files) | 🟡 Intermediate |
| 26 | [Real-Time Backend Systems](#26-real-time-backend-systems) | 🔴 Advanced |
| 27 | [Testing & Code Quality](#27-testing--code-quality) | 🟡 Intermediate |
| 28 | [12-Factor App](#28-12-factor-app) | 🟡 Intermediate |
| 29 | [OpenAPI Standards](#29-openapi-standards) | 🟡 Intermediate |
| 30 | [Webhooks](#30-webhooks) | 🟡 Intermediate |
| 31 | [DevOps for Backend Engineers](#31-devops-for-backend-engineers) | 🔴 Advanced |

---

## Project Setup

Every code example in this guide uses this base Express.js project. Set it up once.

```bash
mkdir backend-guide && cd backend-guide
npm init -y
npm install express mongoose redis ioredis jsonwebtoken bcryptjs zod dotenv
npm install morgan winston joi axios nodemailer bull multer
npm install -D typescript @types/node @types/express nodemon ts-node
```

```
backend-guide/
├── src/
│   ├── config/
│   ├── controllers/
│   ├── services/
│   ├── middleware/
│   ├── models/
│   ├── routes/
│   ├── utils/
│   └── app.ts
├── .env
└── package.json
```

---

## 01. High-Level Architecture

### What it is

Before writing a single line of backend code, you need a mental model of how all the pieces fit. A backend system is fundamentally a **request-processing pipeline** that sits between clients and data stores.

```
                        ┌─────────────────────────────────────────┐
                        │            BACKEND SYSTEM               │
                        │                                         │
Client (Browser/Mobile) │  Load        API         Business      │  Database
         ──────────────►│  Balancer ─► Gateway ─►  Logic    ───► │  (SQL/NoSQL)
                        │                │                        │
                        │           Middleware                    │  Cache
                        │           Pipeline                      │  (Redis)
                        │                                         │
                        │  Auth │ Logging │ Rate Limit │ CORS     │  Queue
                        └─────────────────────────────────────────┘
```

### The Request Lifecycle

Every HTTP request travels through a predictable sequence:

```
1. Client sends request
        ↓
2. DNS resolution → finds your server IP
        ↓
3. TCP handshake (or TLS for HTTPS)
        ↓
4. Load Balancer receives request → picks a server instance
        ↓
5. Your server accepts the connection
        ↓
6. Middleware pipeline runs (logging, auth, rate limiting, CORS...)
        ↓
7. Router matches URL + method → dispatches to controller
        ↓
8. Controller validates input
        ↓
9. Service layer executes business logic
        ↓
10. Repository/Model talks to database
        ↓
11. Response serialised and sent back
        ↓
12. Client receives response
```

### Layered Architecture (what you build)

```
┌────────────────────────────────────┐
│         Presentation Layer         │  Routes + Controllers
│  (HTTP concerns only)              │  Validates input, sends response
├────────────────────────────────────┤
│         Business Logic Layer       │  Services
│  (domain rules, orchestration)     │  Uses cases, workflows
├────────────────────────────────────┤
│         Data Access Layer          │  Models / Repositories
│  (database interaction)            │  Queries, ORM/ODM
├────────────────────────────────────┤
│         Infrastructure             │  Redis, S3, Email, Queues
│  (external services)               │  Adapters / Clients
└────────────────────────────────────┘
```

**Interview insight**: When asked "how would you design X?", always start by drawing this diagram and explaining what lives in each layer.

---

## 02. HTTP Protocol Deep Dive

### What it is

HTTP (HyperText Transfer Protocol) is the language clients and servers use to communicate. Every backend engineer must understand it deeply — not just GET and POST.

### HTTP Methods (Semantics Matter)

| Method | Idempotent? | Safe? | Use Case |
|--------|------------|-------|----------|
| `GET` | ✅ Yes | ✅ Yes | Read data |
| `POST` | ❌ No | ❌ No | Create, non-idempotent actions |
| `PUT` | ✅ Yes | ❌ No | Full replace of a resource |
| `PATCH` | ❌ No | ❌ No | Partial update |
| `DELETE` | ✅ Yes | ❌ No | Delete resource |
| `HEAD` | ✅ Yes | ✅ Yes | Like GET but no body |
| `OPTIONS` | ✅ Yes | ✅ Yes | CORS preflight, API discovery |

> **Idempotent**: calling it multiple times has the same effect as calling it once.  
> **Safe**: has no side effects on the server.

### HTTP Status Codes (Know All Categories)

```
1xx — Informational  (100 Continue, 101 Switching Protocols)
2xx — Success        (200 OK, 201 Created, 204 No Content)
3xx — Redirection    (301 Moved Permanently, 304 Not Modified)
4xx — Client Error   (400 Bad Request, 401 Unauthorized, 403 Forbidden,
                       404 Not Found, 409 Conflict, 422 Unprocessable,
                       429 Too Many Requests)
5xx — Server Error   (500 Internal Server Error, 502 Bad Gateway,
                       503 Service Unavailable, 504 Gateway Timeout)
```

### HTTP Headers You Must Know

```
Request Headers:
  Authorization: Bearer <token>
  Content-Type: application/json
  Accept: application/json
  X-Request-ID: uuid-here
  If-None-Match: "etag-value"        ← conditional requests
  Cache-Control: no-cache

Response Headers:
  Content-Type: application/json
  Cache-Control: max-age=3600
  ETag: "abc123"
  X-RateLimit-Limit: 100
  X-RateLimit-Remaining: 87
  X-RateLimit-Reset: 1716000000
  Location: /users/123              ← after 201 Created
  Retry-After: 60                   ← after 429
```

### HTTP/1.1 vs HTTP/2 vs HTTP/3

```
HTTP/1.1:  One request per TCP connection (slow)
           Keep-Alive allows reuse but still sequential

HTTP/2:    Multiplexing — many requests over one connection
           Header compression (HPACK)
           Server push

HTTP/3:    Runs over QUIC (UDP, not TCP)
           0-RTT connection setup
           Better for lossy networks (mobile)
```

### Implementation — Inspecting HTTP in Express

```javascript
// src/middleware/httpInspector.ts
import { Request, Response, NextFunction } from 'express';

export const httpInspector = (req: Request, res: Response, next: NextFunction) => {
  console.log({
    method:   req.method,
    url:      req.url,
    path:     req.path,
    query:    req.query,          // ?key=value parsed
    params:   req.params,         // :id route params
    headers:  req.headers,
    body:     req.body,
    ip:       req.ip,
    protocol: req.protocol,       // http | https
    secure:   req.secure,         // true if HTTPS
    hostname: req.hostname,
  });

  // Capture response details
  const originalSend = res.send.bind(res);
  res.send = (body: any) => {
    console.log({
      statusCode: res.statusCode,
      headers:    res.getHeaders(),
    });
    return originalSend(body);
  };

  next();
};
```

```javascript
// Setting proper status codes
app.post('/users', async (req, res) => {
  const user = await UserService.create(req.body);
  res
    .status(201)                          // Created
    .location(`/users/${user.id}`)        // Where to find it
    .json({ data: user });
});

app.get('/users/:id', async (req, res) => {
  const user = await UserService.findById(req.params.id);
  if (!user) return res.status(404).json({ error: 'User not found' });
  res.status(200).json({ data: user });
});

app.delete('/users/:id', async (req, res) => {
  await UserService.delete(req.params.id);
  res.status(204).send();                 // No Content — no body
});
```

---

## 03. Routing

### What it is

Routing is the mechanism that maps an incoming URL + HTTP method to a specific handler function. Good routing is organised, predictable, and versioned.

### Route Organisation Patterns

```javascript
// src/routes/index.ts — central router hub
import { Router } from 'express';
import userRoutes from './user.routes';
import productRoutes from './product.routes';
import authRoutes from './auth.routes';

const router = Router();

// Versioned API — critical for production APIs
router.use('/v1/users',    userRoutes);
router.use('/v1/products', productRoutes);
router.use('/v1/auth',     authRoutes);

export default router;
```

```javascript
// src/routes/user.routes.ts
import { Router } from 'express';
import { UserController } from '../controllers/user.controller';
import { authenticate } from '../middleware/auth';
import { authorize }    from '../middleware/rbac';
import { validate }     from '../middleware/validate';
import { createUserSchema, updateUserSchema } from '../validators/user.validator';

const router = Router();
const ctrl   = new UserController();

// Public routes
router.post('/register', validate(createUserSchema), ctrl.register);
router.post('/login',    ctrl.login);

// Protected routes — middleware applied per-route
router.get('/',        authenticate, authorize('admin'), ctrl.getAll);
router.get('/me',      authenticate,                     ctrl.getMe);
router.get('/:id',     authenticate,                     ctrl.getById);
router.put('/:id',     authenticate, validate(updateUserSchema), ctrl.update);
router.patch('/:id',   authenticate, validate(updateUserSchema), ctrl.partialUpdate);
router.delete('/:id',  authenticate, authorize('admin'), ctrl.delete);

export default router;
```

### Route Parameters — All Three Types

```javascript
// 1. Path parameters  → :id  (required, part of the URL)
router.get('/users/:userId/posts/:postId', (req, res) => {
  const { userId, postId } = req.params;
  // /users/123/posts/456  →  userId='123', postId='456'
});

// 2. Query parameters  → ?key=value  (optional filters/pagination)
router.get('/users', (req, res) => {
  const {
    page   = '1',
    limit  = '10',
    sort   = 'createdAt',
    order  = 'desc',
    search = '',
    role,
  } = req.query;
  // /users?page=2&limit=5&search=alice
});

// 3. Request body  → JSON payload  (POST/PUT/PATCH)
router.post('/users', (req, res) => {
  const { name, email, password, role } = req.body;
});
```

### Router-Level Middleware

```javascript
// Apply middleware to ALL routes in this router
router.use(authenticate);   // every route below this line is protected

router.get('/', ctrl.getAll);
router.get('/:id', ctrl.getById);
```

### Route Wildcards & Catch-All

```javascript
// Catch unmatched routes — place LAST in app.ts
app.use('*', (req, res) => {
  res.status(404).json({
    error: 'Route not found',
    path:  req.originalUrl,
    method: req.method,
  });
});
```

---

## 04. Serialisation & Deserialisation

### What it is

**Serialisation** = converting an in-memory object → a transmittable format (JSON, XML, Protobuf).  
**Deserialisation** = parsing received bytes → an in-memory object you can work with.

This sounds trivial but has real gotchas in production: dates, BigInts, circular references, sensitive field exclusion, and nested object shaping.

### The Hidden Problems

```javascript
// Problem 1: Dates become strings in JSON
const obj = { createdAt: new Date() };
JSON.stringify(obj);  // {"createdAt":"2024-01-01T00:00:00.000Z"}
// When parsed back: typeof result.createdAt === 'string'  ← NOT a Date!

// Problem 2: BigInt not supported
const obj2 = { id: 9007199254740993n };
JSON.stringify(obj2);  // TypeError: Cannot serialize BigInt

// Problem 3: Circular references
const a: any = {};
const b: any = { a };
a.b = b;
JSON.stringify(a);  // TypeError: Converting circular structure to JSON

// Problem 4: Sensitive fields leaked
const user = { name: 'Alice', email: 'a@b.com', password: 'hash123' };
res.json(user);  // ← password sent to client!
```

### Production-Grade Serialiser

```javascript
// src/utils/serializer.ts

// Custom JSON serialiser that handles edge cases
export function safeStringify(obj: unknown): string {
  const seen = new WeakSet();

  return JSON.stringify(obj, (key, value) => {
    // Handle circular references
    if (typeof value === 'object' && value !== null) {
      if (seen.has(value)) return '[Circular]';
      seen.add(value);
    }

    // Serialize BigInt
    if (typeof value === 'bigint') return value.toString();

    // Keep Dates as ISO strings (default behaviour is fine here)
    if (value instanceof Date) return value.toISOString();

    return value;
  });
}

// Custom JSON deserialiser — revive date strings back to Date objects
export function safeParse<T = unknown>(json: string): T {
  const ISO_DATE = /^\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}\.\d{3}Z$/;

  return JSON.parse(json, (key, value) => {
    if (typeof value === 'string' && ISO_DATE.test(value)) {
      return new Date(value);
    }
    return value;
  }) as T;
}
```

### Response Shaping — Strip Sensitive Fields

```javascript
// src/utils/transform.ts

// Option 1: Manual DTO (Data Transfer Object) class
export class UserDTO {
  id:        string;
  name:      string;
  email:     string;
  role:      string;
  createdAt: Date;

  constructor(user: any) {
    this.id        = user._id?.toString() ?? user.id;
    this.name      = user.name;
    this.email     = user.email;
    this.role      = user.role;
    this.createdAt = user.createdAt;
    // password, __v, internal fields → never assigned → never in output
  }

  toJSON() {
    return {
      id:        this.id,
      name:      this.name,
      email:     this.email,
      role:      this.role,
      createdAt: this.createdAt,
    };
  }
}

// Option 2: Field exclusion utility
export function exclude<T extends object, K extends keyof T>(
  obj: T,
  keys: K[]
): Omit<T, K> {
  const result = { ...obj };
  for (const key of keys) delete result[key];
  return result as Omit<T, K>;
}

// Usage
const safeUser = exclude(user, ['password', '__v', 'resetToken']);
```

```javascript
// Option 3: toJSON on Mongoose models — auto-runs on JSON serialisation
const userSchema = new mongoose.Schema({
  name:     String,
  email:    String,
  password: String,    // stored hashed
});

userSchema.methods.toJSON = function () {
  const obj = this.toObject();
  delete obj.password;
  delete obj.__v;
  obj.id = obj._id.toString();
  delete obj._id;
  return obj;
};

// Now: res.json(user)  →  password never appears
```

### Consistent API Response Shape

```javascript
// src/utils/response.ts
// Every endpoint should return the same envelope structure

interface ApiResponse<T> {
  success: boolean;
  data?:   T;
  error?:  string;
  message?: string;
  meta?:   {
    page:       number;
    limit:      number;
    total:      number;
    totalPages: number;
  };
}

export const sendSuccess = <T>(
  res: Response,
  data: T,
  statusCode = 200,
  meta?: ApiResponse<T>['meta']
) => {
  res.status(statusCode).json({
    success: true,
    data,
    ...(meta && { meta }),
  } satisfies ApiResponse<T>);
};

export const sendError = (
  res: Response,
  message: string,
  statusCode = 500
) => {
  res.status(statusCode).json({
    success: false,
    error: message,
  } satisfies ApiResponse<never>);
};

// Usage in controller
sendSuccess(res, { user }, 201);
sendError(res, 'Email already exists', 409);
```

---

## 05. Authentication & Authorisation

### The Difference (Critical for Interviews)

```
Authentication = "Who are you?"     → Verify identity (login, JWT validation)
Authorisation  = "What can you do?" → Check permissions (admin? owner? role?)
```

### JWT Authentication — Full Implementation

```javascript
// src/utils/jwt.ts
import jwt from 'jsonwebtoken';

const SECRET  = process.env.JWT_SECRET!;
const REFRESH = process.env.JWT_REFRESH_SECRET!;

export interface JwtPayload {
  userId:    string;
  email:     string;
  role:      string;
  tokenType: 'access' | 'refresh';
}

export const generateAccessToken = (payload: Omit<JwtPayload, 'tokenType'>) =>
  jwt.sign({ ...payload, tokenType: 'access' }, SECRET, { expiresIn: '15m' });

export const generateRefreshToken = (payload: Omit<JwtPayload, 'tokenType'>) =>
  jwt.sign({ ...payload, tokenType: 'refresh' }, REFRESH, { expiresIn: '7d' });

export const verifyAccessToken = (token: string): JwtPayload =>
  jwt.verify(token, SECRET) as JwtPayload;

export const verifyRefreshToken = (token: string): JwtPayload =>
  jwt.verify(token, REFRESH) as JwtPayload;
```

```javascript
// src/middleware/auth.ts
import { Request, Response, NextFunction } from 'express';
import { verifyAccessToken } from '../utils/jwt';

// Extend Express Request type to include user
declare global {
  namespace Express {
    interface Request {
      user?: JwtPayload;
    }
  }
}

export const authenticate = (req: Request, res: Response, next: NextFunction) => {
  const authHeader = req.headers.authorization;

  if (!authHeader?.startsWith('Bearer ')) {
    return res.status(401).json({ error: 'No token provided' });
  }

  const token = authHeader.split(' ')[1];

  try {
    const decoded = verifyAccessToken(token);

    if (decoded.tokenType !== 'access') {
      return res.status(401).json({ error: 'Invalid token type' });
    }

    req.user = decoded;   // attach to request context
    next();
  } catch (err: any) {
    if (err.name === 'TokenExpiredError') {
      return res.status(401).json({ error: 'Token expired', code: 'TOKEN_EXPIRED' });
    }
    return res.status(401).json({ error: 'Invalid token' });
  }
};
```

### Role-Based Access Control (RBAC)

```javascript
// src/middleware/rbac.ts
type Role = 'admin' | 'user' | 'moderator';

// Simple role check
export const authorize = (...roles: Role[]) => {
  return (req: Request, res: Response, next: NextFunction) => {
    if (!req.user) {
      return res.status(401).json({ error: 'Not authenticated' });
    }

    if (!roles.includes(req.user.role as Role)) {
      return res.status(403).json({
        error: 'Insufficient permissions',
        required: roles,
        current:  req.user.role,
      });
    }

    next();
  };
};

// Resource ownership check
export const authorizeOwner = (getResourceUserId: (req: Request) => Promise<string>) => {
  return async (req: Request, res: Response, next: NextFunction) => {
    const resourceUserId = await getResourceUserId(req);
    const isOwner  = req.user!.userId === resourceUserId;
    const isAdmin  = req.user!.role   === 'admin';

    if (!isOwner && !isAdmin) {
      return res.status(403).json({ error: 'Not the resource owner' });
    }
    next();
  };
};

// Usage in routes
router.delete('/:id', authenticate, authorize('admin'), ctrl.delete);
router.put('/:id',    authenticate, authorizeOwner(async (req) => {
  const post = await Post.findById(req.params.id);
  return post!.author.toString();
}), ctrl.update);
```

### Password Hashing

```javascript
// src/utils/password.ts
import bcrypt from 'bcryptjs';

const SALT_ROUNDS = 12;   // higher = slower = more secure (10-12 is the sweet spot)

export const hashPassword   = (plain: string): Promise<string> =>
  bcrypt.hash(plain, SALT_ROUNDS);

export const comparePassword = (plain: string, hash: string): Promise<boolean> =>
  bcrypt.compare(plain, hash);
```

### Refresh Token Flow

```javascript
// src/controllers/auth.controller.ts

class AuthController {
  // POST /auth/login
  async login(req: Request, res: Response) {
    const { email, password } = req.body;

    const user = await User.findOne({ email });
    if (!user || !(await comparePassword(password, user.password))) {
      return res.status(401).json({ error: 'Invalid credentials' });
    }

    const payload = { userId: user.id, email: user.email, role: user.role };
    const accessToken  = generateAccessToken(payload);
    const refreshToken = generateRefreshToken(payload);

    // Store refresh token in DB (so we can revoke it)
    await User.findByIdAndUpdate(user.id, {
      $push: { refreshTokens: refreshToken }
    });

    // Send refresh token in httpOnly cookie (XSS-safe)
    res.cookie('refreshToken', refreshToken, {
      httpOnly: true,
      secure:   process.env.NODE_ENV === 'production',
      sameSite: 'strict',
      maxAge:   7 * 24 * 60 * 60 * 1000,   // 7 days
    });

    res.json({ accessToken, expiresIn: 900 });   // 15 min
  }

  // POST /auth/refresh
  async refresh(req: Request, res: Response) {
    const refreshToken = req.cookies?.refreshToken;
    if (!refreshToken) return res.status(401).json({ error: 'No refresh token' });

    try {
      const decoded = verifyRefreshToken(refreshToken);

      // Verify token exists in DB (rotation / revocation)
      const user = await User.findOne({
        _id: decoded.userId,
        refreshTokens: refreshToken,
      });
      if (!user) return res.status(401).json({ error: 'Token revoked' });

      const payload     = { userId: user.id, email: user.email, role: user.role };
      const newAccess   = generateAccessToken(payload);
      const newRefresh  = generateRefreshToken(payload);

      // Rotate: remove old, add new
      await User.findByIdAndUpdate(user.id, {
        $pull: { refreshTokens: refreshToken },
        $push: { refreshTokens: newRefresh },
      });

      res.cookie('refreshToken', newRefresh, {
        httpOnly: true,
        secure:   process.env.NODE_ENV === 'production',
        sameSite: 'strict',
        maxAge:   7 * 24 * 60 * 60 * 1000,
      });

      res.json({ accessToken: newAccess, expiresIn: 900 });
    } catch {
      res.status(401).json({ error: 'Invalid refresh token' });
    }
  }

  // POST /auth/logout
  async logout(req: Request, res: Response) {
    const refreshToken = req.cookies?.refreshToken;
    if (refreshToken) {
      // Remove from DB — token can't be used again even if intercepted
      await User.findByIdAndUpdate(req.user!.userId, {
        $pull: { refreshTokens: refreshToken }
      });
    }
    res.clearCookie('refreshToken');
    res.status(204).send();
  }
}
```

---

## 06. Validation & Transformation

### What it is

**Never trust client input**. Validation ensures data is correct before your business logic touches it. Transformation normalises data (trim whitespace, lowercase email, coerce types).

### Zod — The Modern Standard

```javascript
// src/validators/user.validator.ts
import { z } from 'zod';

export const createUserSchema = z.object({
  body: z.object({
    name: z
      .string({ required_error: 'Name is required' })
      .min(2, 'Name must be at least 2 characters')
      .max(50, 'Name must be at most 50 characters')
      .trim(),                           // ← transformation: strip whitespace

    email: z
      .string({ required_error: 'Email is required' })
      .email('Invalid email format')
      .toLowerCase()                     // ← transformation: normalise to lowercase
      .trim(),

    password: z
      .string({ required_error: 'Password is required' })
      .min(8, 'Password must be at least 8 characters')
      .regex(/[A-Z]/, 'Password must contain at least one uppercase letter')
      .regex(/[0-9]/, 'Password must contain at least one number')
      .regex(/[!@#$%^&*]/, 'Password must contain a special character'),

    role: z
      .enum(['user', 'admin', 'moderator'])
      .default('user'),                  // ← transformation: set default

    age: z
      .number()
      .int('Age must be an integer')
      .min(13, 'Must be 13 or older')
      .max(120)
      .optional(),

    tags: z
      .array(z.string())
      .max(10, 'Maximum 10 tags')
      .default([]),
  }),
});

export const updateUserSchema = createUserSchema.partial();   // all fields optional

export const getUsersQuerySchema = z.object({
  query: z.object({
    page:   z.coerce.number().int().positive().default(1),    // coerce string→number
    limit:  z.coerce.number().int().min(1).max(100).default(10),
    sort:   z.enum(['name', 'email', 'createdAt']).default('createdAt'),
    order:  z.enum(['asc', 'desc']).default('desc'),
    search: z.string().optional(),
  }),
});

// Infer TypeScript types from schemas (no duplicate type definitions!)
export type CreateUserInput = z.infer<typeof createUserSchema>['body'];
export type UpdateUserInput = z.infer<typeof updateUserSchema>['body'];
export type GetUsersQuery   = z.infer<typeof getUsersQuerySchema>['query'];
```

```javascript
// src/middleware/validate.ts
import { Request, Response, NextFunction } from 'express';
import { AnyZodObject, ZodError } from 'zod';

export const validate = (schema: AnyZodObject) => {
  return async (req: Request, res: Response, next: NextFunction) => {
    try {
      // Parse and REPLACE req with validated+transformed data
      const parsed = await schema.parseAsync({
        body:   req.body,
        query:  req.query,
        params: req.params,
      });

      // Mutate request with clean, typed data
      req.body   = parsed.body   ?? req.body;
      req.query  = parsed.query  ?? req.query;
      req.params = parsed.params ?? req.params;

      next();
    } catch (error) {
      if (error instanceof ZodError) {
        // Format errors into a clean, client-friendly shape
        const errors = error.errors.map(e => ({
          field:   e.path.join('.'),
          message: e.message,
          code:    e.code,
        }));

        return res.status(422).json({
          success: false,
          error:   'Validation failed',
          errors,
        });
      }
      next(error);
    }
  };
};
```

### Advanced Validation Patterns

```javascript
// Custom validations with .refine() and .superRefine()
const passwordChangeSchema = z.object({
  currentPassword: z.string().min(1),
  newPassword:     z.string().min(8),
  confirmPassword: z.string().min(8),
}).refine(
  (data) => data.newPassword === data.confirmPassword,
  {
    message: 'Passwords do not match',
    path:    ['confirmPassword'],       // which field the error belongs to
  }
).refine(
  (data) => data.currentPassword !== data.newPassword,
  {
    message: 'New password must differ from current',
    path:    ['newPassword'],
  }
);

// Conditional validation
const paymentSchema = z.discriminatedUnion('method', [
  z.object({
    method:     z.literal('card'),
    cardNumber: z.string().length(16),
    cvv:        z.string().length(3),
    expiry:     z.string().regex(/^\d{2}\/\d{2}$/),
  }),
  z.object({
    method:     z.literal('bank'),
    accountNo:  z.string().min(8),
    routingNo:  z.string().length(9),
  }),
  z.object({
    method:  z.literal('crypto'),
    wallet:  z.string().startsWith('0x'),
  }),
]);
```

---

## 07. Middlewares

### What it is

A middleware is a function with signature `(req, res, next)` that sits in the request pipeline. It can read/modify the request, send a response (short-circuit), or pass control to the next middleware via `next()`.

```
Request → MW1 → MW2 → MW3 → Handler → Response
                ↓
          (MW2 blocks)  → Error Response
```

### The Four Types of Middleware

```javascript
// Type 1: Application-level — runs on every request
app.use(express.json());         // parse JSON bodies
app.use(express.urlencoded({ extended: true }));
app.use(cors());
app.use(morgan('combined'));     // HTTP logging

// Type 2: Route-level — runs on specific routes/routers
router.use(authenticate);       // all routes in this router

// Type 3: Error-handling — 4-argument signature
app.use((err, req, res, next) => {   // ← 4 args = error handler
  res.status(500).json({ error: err.message });
});

// Type 4: Third-party (installed via npm)
app.use(helmet());              // security headers
app.use(compression());         // gzip responses
```

### Building Production Middleware

```javascript
// src/middleware/rateLimiter.ts
// Simple in-memory rate limiter (use Redis in production)
import { Request, Response, NextFunction } from 'express';

interface RateLimitStore {
  [key: string]: {
    count:     number;
    resetTime: number;
  };
}

export const createRateLimiter = ({
  windowMs  = 60_000,    // 1 minute
  maxRequests = 100,
}: {
  windowMs?:    number;
  maxRequests?: number;
} = {}) => {
  const store: RateLimitStore = {};

  // Clean stale entries every minute
  setInterval(() => {
    const now = Date.now();
    for (const key in store) {
      if (store[key].resetTime < now) delete store[key];
    }
  }, 60_000);

  return (req: Request, res: Response, next: NextFunction) => {
    const key = req.ip ?? 'unknown';
    const now = Date.now();

    if (!store[key] || store[key].resetTime < now) {
      store[key] = { count: 1, resetTime: now + windowMs };
    } else {
      store[key].count++;
    }

    const { count, resetTime } = store[key];
    const remaining = Math.max(0, maxRequests - count);

    res.setHeader('X-RateLimit-Limit',     maxRequests);
    res.setHeader('X-RateLimit-Remaining', remaining);
    res.setHeader('X-RateLimit-Reset',     Math.ceil(resetTime / 1000));

    if (count > maxRequests) {
      return res.status(429).json({
        error:      'Too many requests',
        retryAfter: Math.ceil((resetTime - now) / 1000),
      });
    }

    next();
  };
};

// Usage
app.use('/api/', createRateLimiter({ windowMs: 60_000, maxRequests: 100 }));
app.use('/api/auth/', createRateLimiter({ windowMs: 15 * 60_000, maxRequests: 5 }));
```

```javascript
// src/middleware/requestId.ts
// Attach a unique ID to every request for distributed tracing
import { v4 as uuid } from 'uuid';

export const requestId = (req: Request, res: Response, next: NextFunction) => {
  const id = (req.headers['x-request-id'] as string) ?? uuid();
  req.id = id;                          // attach to req
  res.setHeader('X-Request-ID', id);    // echo back in response
  next();
};
```

```javascript
// src/middleware/cors.ts
// Precise CORS configuration
import cors from 'cors';

const ALLOWED_ORIGINS = [
  'https://myapp.com',
  'https://www.myapp.com',
  process.env.NODE_ENV !== 'production' && 'http://localhost:3000',
].filter(Boolean) as string[];

export const corsMiddleware = cors({
  origin: (origin, callback) => {
    // Allow non-browser requests (Postman, server-to-server)
    if (!origin) return callback(null, true);

    if (ALLOWED_ORIGINS.includes(origin)) {
      callback(null, true);
    } else {
      callback(new Error(`Origin ${origin} not allowed by CORS`));
    }
  },
  methods:          ['GET', 'POST', 'PUT', 'PATCH', 'DELETE', 'OPTIONS'],
  allowedHeaders:   ['Content-Type', 'Authorization', 'X-Request-ID'],
  exposedHeaders:   ['X-RateLimit-Limit', 'X-RateLimit-Remaining'],
  credentials:      true,        // allow cookies
  maxAge:           86400,        // preflight cache: 24 hours
});
```

### Middleware Composition Pattern

```javascript
// src/middleware/compose.ts
// Chain multiple middleware into one (useful for route-specific stacks)
import { RequestHandler } from 'express';

export const compose = (...middlewares: RequestHandler[]): RequestHandler => {
  return (req, res, next) => {
    const run = (index: number) => {
      if (index >= middlewares.length) return next();
      middlewares[index](req, res, (err) => {
        if (err) return next(err);
        run(index + 1);
      });
    };
    run(0);
  };
};

// Usage: clean route definitions
const protectedAdmin = compose(authenticate, authorize('admin'), rateLimiter);
router.get('/admin/users', protectedAdmin, ctrl.getAll);
```

---

## 08. Request Context

### What it is

Request context is data that should be accessible anywhere within a single request's lifecycle — the user's identity, a request ID, tenant ID — without passing it explicitly through every function call.

### The Problem

```javascript
// Without context — you pass req everywhere — messy
async function handleRequest(req, res) {
  await createOrder(req);
}
async function createOrder(req) {
  await chargePayment(req);
  await sendEmail(req.user.email);    // ← req leaks into business logic
}
```

### Solution 1: AsyncLocalStorage (Node.js built-in)

```javascript
// src/context/requestContext.ts
import { AsyncLocalStorage } from 'async_hooks';

interface RequestContext {
  requestId: string;
  userId?:   string;
  role?:     string;
  startTime: number;
  [key: string]: unknown;
}

// One store per app — context is isolated per async chain
const storage = new AsyncLocalStorage<RequestContext>();

export const RequestContext = {
  // Set context at the start of a request
  run: <T>(ctx: RequestContext, fn: () => T): T =>
    storage.run(ctx, fn),

  // Get context anywhere in the async chain
  get: (): RequestContext => {
    const ctx = storage.getStore();
    if (!ctx) throw new Error('Called outside a request context');
    return ctx;
  },

  // Convenience getters
  getRequestId: (): string => RequestContext.get().requestId,
  getUserId:    (): string  => RequestContext.get().userId ?? '',
};
```

```javascript
// src/middleware/context.ts
import { v4 as uuid } from 'uuid';
import { RequestContext } from '../context/requestContext';

export const contextMiddleware = (req: Request, res: Response, next: NextFunction) => {
  const ctx = {
    requestId: (req.headers['x-request-id'] as string) ?? uuid(),
    userId:    undefined,       // filled in by auth middleware
    role:      undefined,
    startTime: Date.now(),
  };

  // Set response header
  res.setHeader('X-Request-ID', ctx.requestId);

  // Run the rest of the request pipeline inside the context
  RequestContext.run(ctx, () => next());
};

// Update context after auth
export const authenticate = (req: Request, res: Response, next: NextFunction) => {
  // ...verify token...
  const decoded = verifyAccessToken(token);
  req.user = decoded;

  // Write into the already-running context
  const ctx = RequestContext.get();
  ctx.userId = decoded.userId;
  ctx.role   = decoded.role;

  next();
};
```

```javascript
// Now any service can access context WITHOUT receiving req as a parameter
// src/services/audit.service.ts
import { RequestContext } from '../context/requestContext';
import logger from '../utils/logger';

export class AuditService {
  static log(action: string, details: object) {
    const { requestId, userId } = RequestContext.get();
    // No req parameter needed
    logger.info('AUDIT', {
      requestId,
      userId,
      action,
      details,
      timestamp: new Date().toISOString(),
    });
  }
}

// Usage inside a service — clean, no req leaking into business logic
export class OrderService {
  async createOrder(data: CreateOrderInput) {
    const order = await Order.create(data);
    AuditService.log('ORDER_CREATED', { orderId: order.id });  // context auto-available
    return order;
  }
}
```

---

## 09. Handlers, Controllers & Services

### The Layer Separation Rule

```
Controller = HTTP boundary. Knows about req/res. Does NOT contain business logic.
Service    = Business logic. Knows nothing about HTTP. Knows nothing about the DB.
Repository = Database boundary. Knows about the ORM/ODM. Does NOT contain business logic.
```

```javascript
// src/controllers/user.controller.ts
// Controller: thin HTTP adapter

export class UserController {
  constructor(private readonly userService: UserService) {}

  // Only responsibilities:
  // 1. Extract input from req (validated by middleware already)
  // 2. Call service
  // 3. Send response

  getAll = async (req: Request, res: Response, next: NextFunction) => {
    try {
      const { page, limit, sort, order, search } = req.query as GetUsersQuery;
      const result = await this.userService.getAll({ page, limit, sort, order, search });
      sendSuccess(res, result.users, 200, result.meta);
    } catch (err) {
      next(err);   // pass errors to global error handler
    }
  };

  getById = async (req: Request, res: Response, next: NextFunction) => {
    try {
      const user = await this.userService.getById(req.params.id);
      if (!user) return sendError(res, 'User not found', 404);
      sendSuccess(res, new UserDTO(user));
    } catch (err) {
      next(err);
    }
  };

  create = async (req: Request, res: Response, next: NextFunction) => {
    try {
      const user = await this.userService.create(req.body as CreateUserInput);
      sendSuccess(res, new UserDTO(user), 201);
    } catch (err) {
      next(err);
    }
  };
}
```

```javascript
// src/services/user.service.ts
// Service: business logic, no HTTP knowledge

export class UserService {
  constructor(private readonly userRepo: UserRepository) {}

  async getAll(options: PaginationOptions): Promise<PaginatedResult<User>> {
    const { page, limit, sort, order, search } = options;

    // Business rule: non-admins can't list all users
    const requestingUser = RequestContext.get();
    if (requestingUser.role !== 'admin') {
      throw new ForbiddenError('Only admins can list all users');
    }

    return this.userRepo.findAll({ page, limit, sort, order, search });
  }

  async getById(id: string): Promise<User | null> {
    if (!isValidObjectId(id)) {
      throw new ValidationError('Invalid user ID format');
    }
    return this.userRepo.findById(id);
  }

  async create(data: CreateUserInput): Promise<User> {
    // Business rules live here, not in the controller
    const existing = await this.userRepo.findByEmail(data.email);
    if (existing) throw new ConflictError('Email already registered');

    const hashedPassword = await hashPassword(data.password);

    const user = await this.userRepo.create({
      ...data,
      password: hashedPassword,
    });

    // Side effects: send welcome email, create default settings, etc.
    await EmailService.sendWelcome(user.email, user.name);
    await UserSettingsService.createDefaults(user.id);

    return user;
  }
}
```

```javascript
// src/repositories/user.repository.ts
// Repository: pure database access, no business logic

export class UserRepository {
  async findAll(options: FindAllOptions): Promise<PaginatedResult<User>> {
    const { page, limit, sort, order, search } = options;
    const skip = (page - 1) * limit;

    const filter: FilterQuery<User> = search
      ? { $or: [
          { name:  { $regex: search, $options: 'i' } },
          { email: { $regex: search, $options: 'i' } },
        ]}
      : {};

    const [users, total] = await Promise.all([
      UserModel.find(filter)
        .sort({ [sort]: order === 'asc' ? 1 : -1 })
        .skip(skip)
        .limit(limit)
        .lean(),
      UserModel.countDocuments(filter),
    ]);

    return {
      users,
      meta: {
        page,
        limit,
        total,
        totalPages: Math.ceil(total / limit),
      },
    };
  }

  findById    = (id: string)        => UserModel.findById(id).lean();
  findByEmail = (email: string)     => UserModel.findOne({ email }).lean();
  create      = (data: CreateUser)  => UserModel.create(data);
  update      = (id: string, data: Partial<User>) =>
    UserModel.findByIdAndUpdate(id, data, { new: true }).lean();
  delete      = (id: string) => UserModel.findByIdAndDelete(id);
}
```

---

## 10. CRUD Deep Dive

### What it is

CRUD (Create, Read, Update, Delete) is the foundation of every backend API. But production CRUD goes beyond the basics — pagination, filtering, partial updates, and soft deletes.

### Full CRUD Implementation

```javascript
// src/models/product.model.ts
import mongoose, { Schema, Document } from 'mongoose';

interface IProduct extends Document {
  name:        string;
  description: string;
  price:       number;
  category:    string;
  stock:       number;
  tags:        string[];
  isDeleted:   boolean;   // soft delete
  deletedAt?:  Date;
  createdBy:   mongoose.Types.ObjectId;
  createdAt:   Date;
  updatedAt:   Date;
}

const productSchema = new Schema<IProduct>({
  name:        { type: String, required: true, trim: true, maxlength: 200 },
  description: { type: String, required: true, maxlength: 2000 },
  price:       { type: Number, required: true, min: 0 },
  category:    { type: String, required: true, index: true },
  stock:       { type: Number, required: true, min: 0, default: 0 },
  tags:        [{ type: String, lowercase: true, trim: true }],
  isDeleted:   { type: Boolean, default: false, index: true },
  deletedAt:   { type: Date },
  createdBy:   { type: Schema.Types.ObjectId, ref: 'User', required: true },
}, {
  timestamps: true,           // auto-manages createdAt, updatedAt
  toJSON:     { virtuals: true },
});

// Compound index for common queries
productSchema.index({ category: 1, price: 1 });
productSchema.index({ name: 'text', description: 'text' });   // text search

// Always exclude soft-deleted docs from queries unless explicitly included
productSchema.pre(/^find/, function (this: any, next) {
  if (!this._conditions.isDeleted) {
    this.where({ isDeleted: false });
  }
  next();
});

export const Product = mongoose.model<IProduct>('Product', productSchema);
```

```javascript
// src/services/product.service.ts — full CRUD

export class ProductService {

  // CREATE
  async create(data: CreateProductInput, createdBy: string) {
    return Product.create({ ...data, createdBy });
  }

  // READ (paginated, filtered, sorted)
  async getAll(query: ProductQuery) {
    const {
      page = 1, limit = 10, sort = 'createdAt', order = 'desc',
      search, category, minPrice, maxPrice, inStock,
    } = query;

    const filter: Record<string, any> = {};

    if (search) {
      filter.$text = { $search: search };           // MongoDB text search
    }
    if (category)            filter.category = category;
    if (minPrice !== undefined || maxPrice !== undefined) {
      filter.price = {};
      if (minPrice !== undefined) filter.price.$gte = minPrice;
      if (maxPrice !== undefined) filter.price.$lte = maxPrice;
    }
    if (inStock === 'true') filter.stock = { $gt: 0 };

    const skip = (page - 1) * limit;
    const sortObj = { [sort]: order === 'asc' ? 1 : -1 } as any;

    const [products, total] = await Promise.all([
      Product.find(filter).sort(sortObj).skip(skip).limit(limit).populate('createdBy', 'name email'),
      Product.countDocuments(filter),
    ]);

    return {
      products,
      meta: { page, limit, total, totalPages: Math.ceil(total / limit) },
    };
  }

  // READ ONE
  async getById(id: string) {
    return Product.findById(id).populate('createdBy', 'name email');
  }

  // UPDATE (full replace — PUT)
  async replace(id: string, data: CreateProductInput) {
    return Product.findByIdAndUpdate(id, data, {
      new:       true,     // return updated document
      runValidators: true, // run schema validators on update
    });
  }

  // UPDATE (partial — PATCH)
  async update(id: string, data: Partial<CreateProductInput>) {
    return Product.findByIdAndUpdate(id, { $set: data }, {
      new:           true,
      runValidators: true,
    });
  }

  // DELETE — soft delete
  async delete(id: string) {
    const product = await Product.findByIdAndUpdate(
      id,
      { isDeleted: true, deletedAt: new Date() },
      { new: true }
    );
    if (!product) throw new NotFoundError('Product not found');
    return product;
  }

  // Hard delete (admin only)
  async hardDelete(id: string) {
    return Product.findByIdAndDelete(id);
  }

  // BULK operations
  async bulkCreate(items: CreateProductInput[], createdBy: string) {
    return Product.insertMany(items.map(i => ({ ...i, createdBy })), {
      ordered: false,   // continue on individual failures
    });
  }

  async bulkDelete(ids: string[]) {
    return Product.updateMany(
      { _id: { $in: ids } },
      { isDeleted: true, deletedAt: new Date() }
    );
  }
}
```

---

## 11. RESTful Architecture & Best Practices

### REST Constraints

```
1. Client-Server     — separation of concerns
2. Stateless         — each request contains everything needed; no server-side session
3. Cacheable         — responses declare whether they can be cached
4. Uniform Interface — consistent URL structure and HTTP methods
5. Layered System    — client can't tell if talking to real server or load balancer
6. Code on Demand    — optional: server can send executable code (JS)
```

### URL Design Rules

```
✅ GOOD                          ❌ BAD
GET    /users                    GET /getUsers
POST   /users                    POST /createUser
GET    /users/:id                GET /user?id=123
PUT    /users/:id                POST /users/update/123
PATCH  /users/:id                POST /users/patch
DELETE /users/:id                GET  /deleteUser/123
GET    /users/:id/orders         GET /getUserOrders?userId=123
POST   /orders/:id/cancel        POST /cancelOrder

# Plural nouns, not verbs
# Nested resources for relationships
# Kebab-case for multi-word resources
GET /blog-posts           ← kebab-case for URLs
GET /blog-posts/:id/comments
```

### Versioning Strategies

```javascript
// Strategy 1: URL versioning (most common, most explicit)
app.use('/api/v1', v1Router);
app.use('/api/v2', v2Router);

// Strategy 2: Header versioning
app.use((req, res, next) => {
  const version = req.headers['api-version'] ?? 'v1';
  req.apiVersion = version;
  next();
});

// Strategy 3: Query param versioning
// GET /users?api-version=2024-01-01   ← Microsoft's approach
```

### HATEOAS (Hypermedia)

```javascript
// Responses include links to related actions — clients don't hardcode URLs
res.json({
  data: {
    id:    '123',
    name:  'Alice',
    email: 'alice@example.com',
  },
  links: {
    self:    '/api/v1/users/123',
    orders:  '/api/v1/users/123/orders',
    update:  { href: '/api/v1/users/123', method: 'PATCH' },
    delete:  { href: '/api/v1/users/123', method: 'DELETE' },
  },
});
```

### ETags & Conditional Requests

```javascript
// src/middleware/etag.ts
// Prevent unnecessary data transfer with ETags
import crypto from 'crypto';

export const etagMiddleware = (req: Request, res: Response, next: NextFunction) => {
  const originalJson = res.json.bind(res);

  res.json = (body: any) => {
    const etag = '"' + crypto
      .createHash('sha1')
      .update(JSON.stringify(body))
      .digest('hex') + '"';

    res.setHeader('ETag', etag);
    res.setHeader('Cache-Control', 'private, no-cache');

    const clientEtag = req.headers['if-none-match'];
    if (clientEtag === etag) {
      res.status(304).send();    // Not Modified — saves bandwidth
      return res;
    }

    return originalJson(body);
  };

  next();
};
```

---

## 12. Databases

### SQL vs NoSQL — Decision Framework

```
Use SQL (PostgreSQL, MySQL) when:
  ✅ Data has complex relationships
  ✅ Strong consistency is required (banking, orders)
  ✅ Complex queries, joins, aggregations
  ✅ ACID transactions are critical

Use NoSQL (MongoDB) when:
  ✅ Schema is flexible / evolving fast
  ✅ Document-centric data (user profiles, catalogs)
  ✅ Horizontal scaling is the primary goal
  ✅ Read-heavy with simple access patterns

Use Both (Polyglot Persistence):
  → PostgreSQL for orders/payments
  → MongoDB for product catalog
  → Redis for sessions/cache
  → Elasticsearch for search
```

### MongoDB with Mongoose — Production Patterns

```javascript
// src/config/database.ts
import mongoose from 'mongoose';
import logger   from '../utils/logger';

const MONGO_URI = process.env.MONGODB_URI!;

export const connectDatabase = async (): Promise<void> => {
  mongoose.set('strictQuery', true);

  // Connection event listeners
  mongoose.connection.on('connected',    () => logger.info('MongoDB connected'));
  mongoose.connection.on('disconnected', () => logger.warn('MongoDB disconnected'));
  mongoose.connection.on('error',  (err) => logger.error('MongoDB error', { err }));

  try {
    await mongoose.connect(MONGO_URI, {
      maxPoolSize:         10,     // max concurrent connections
      serverSelectionTimeoutMS: 5000,
      socketTimeoutMS:     45_000,
    });
  } catch (error) {
    logger.error('Failed to connect to MongoDB', { error });
    process.exit(1);
  }
};

export const disconnectDatabase = async (): Promise<void> => {
  await mongoose.disconnect();
};
```

```javascript
// MongoDB transactions (ACID for multi-document ops)
// src/services/order.service.ts

export class OrderService {
  async createOrder(userId: string, items: OrderItem[]) {
    const session = await mongoose.startSession();
    session.startTransaction();

    try {
      // 1. Verify and decrement stock
      for (const item of items) {
        const result = await Product.findOneAndUpdate(
          { _id: item.productId, stock: { $gte: item.quantity } },
          { $inc: { stock: -item.quantity } },
          { session, new: true }
        );
        if (!result) {
          throw new Error(`Insufficient stock for product ${item.productId}`);
        }
      }

      // 2. Calculate total
      const total = items.reduce((sum, i) => sum + i.price * i.quantity, 0);

      // 3. Create order
      const [order] = await Order.create([{
        userId,
        items,
        total,
        status: 'pending',
      }], { session });

      // 4. Debit user wallet
      await User.findByIdAndUpdate(
        userId,
        { $inc: { walletBalance: -total } },
        { session }
      );

      await session.commitTransaction();
      return order;

    } catch (error) {
      await session.abortTransaction();
      throw error;
    } finally {
      session.endSession();
    }
  }
}
```

### PostgreSQL with TypeORM

```typescript
// src/entities/User.entity.ts
import { Entity, Column, PrimaryGeneratedColumn, CreateDateColumn,
         UpdateDateColumn, OneToMany, Index } from 'typeorm';

@Entity('users')
export class User {
  @PrimaryGeneratedColumn('uuid')
  id: string;

  @Column({ length: 100 })
  name: string;

  @Index({ unique: true })
  @Column({ length: 255, unique: true })
  email: string;

  @Column({ select: false })   // never returned in queries by default
  password: string;

  @Column({ default: 'user', enum: ['user', 'admin', 'moderator'] })
  role: string;

  @OneToMany(() => Order, order => order.user)
  orders: Order[];

  @CreateDateColumn()
  createdAt: Date;

  @UpdateDateColumn()
  updatedAt: Date;
}
```

```typescript
// Repository pattern with TypeORM
import { Repository, DataSource } from 'typeorm';

export class UserRepository {
  private repo: Repository<User>;

  constructor(dataSource: DataSource) {
    this.repo = dataSource.getRepository(User);
  }

  async findPaginated(page: number, limit: number, search?: string) {
    const qb = this.repo.createQueryBuilder('user');

    if (search) {
      qb.where('user.name ILIKE :search OR user.email ILIKE :search', {
        search: `%${search}%`,
      });
    }

    const [users, total] = await qb
      .skip((page - 1) * limit)
      .take(limit)
      .orderBy('user.createdAt', 'DESC')
      .getManyAndCount();

    return { users, total, totalPages: Math.ceil(total / limit) };
  }
}
```

### Database Indexing Strategy

```javascript
// Key indexing patterns

// 1. Single field index — fast lookups on one field
db.users.createIndex({ email: 1 }, { unique: true });

// 2. Compound index — order matters! Left-to-right prefix rule
db.orders.createIndex({ userId: 1, createdAt: -1 });
// Supports: { userId } and { userId, createdAt }
// Does NOT support: { createdAt } alone

// 3. Text index — full-text search
db.products.createIndex({ name: 'text', description: 'text' });

// 4. Sparse index — only index documents that have the field
db.users.createIndex({ resetToken: 1 }, { sparse: true, expireAfterSeconds: 3600 });

// 5. Partial index — only index documents matching a filter
db.orders.createIndex(
  { status: 1 },
  { partialFilterExpression: { status: 'pending' } }
);
```

---

## 13. Business Logic Layer (BLL)

### What it is

The BLL is the heart of your application. It contains domain rules, workflows, and orchestration that make your app unique. It knows NOTHING about HTTP or databases.

### Domain Events Pattern

```javascript
// src/events/eventBus.ts
// Decouple side effects from core operations

import EventEmitter from 'events';

type EventMap = {
  'user.created':        { userId: string; email: string; name: string };
  'user.password-reset': { userId: string; token: string };
  'order.created':       { orderId: string; userId: string; total: number };
  'order.shipped':       { orderId: string; trackingNumber: string };
  'payment.failed':      { orderId: string; reason: string };
};

class TypedEventBus extends EventEmitter {
  emit<K extends keyof EventMap>(event: K, payload: EventMap[K]): boolean {
    return super.emit(event, payload);
  }

  on<K extends keyof EventMap>(event: K, handler: (payload: EventMap[K]) => void): this {
    return super.on(event, handler);
  }
}

export const eventBus = new TypedEventBus();

// Register handlers (in app.ts at startup)
eventBus.on('user.created',  async ({ email, name }) => {
  await EmailService.sendWelcome(email, name);
  await MetricsService.increment('users.created');
});

eventBus.on('order.created', async ({ orderId, userId, total }) => {
  await NotificationService.send(userId, `Order #${orderId} confirmed — $${total}`);
  await AuditService.log('ORDER_CREATED', { orderId, total });
});
```

```javascript
// src/services/user.service.ts — clean BLL
export class UserService {
  async register(data: RegisterInput): Promise<User> {
    // Step 1: Business rule validation
    const existing = await this.userRepo.findByEmail(data.email);
    if (existing) throw new ConflictError('Email already registered');

    if (data.age && data.age < 13) {
      throw new ValidationError('Must be at least 13 years old');
    }

    // Step 2: Core operation
    const hashedPassword = await hashPassword(data.password);
    const user = await this.userRepo.create({
      ...data,
      password:    hashedPassword,
      role:        'user',
      isVerified:  false,
      verifyToken: crypto.randomBytes(32).toString('hex'),
    });

    // Step 3: Emit event — side effects handled separately
    eventBus.emit('user.created', {
      userId: user.id,
      email:  user.email,
      name:   user.name,
    });

    return user;
  }
}
```

### Transaction Script vs Domain Model

```javascript
// Transaction Script: simple, procedural (fine for small apps)
async function transferMoney(fromId, toId, amount) {
  const from = await Account.findById(fromId);
  const to   = await Account.findById(toId);

  if (from.balance < amount) throw new Error('Insufficient funds');
  from.balance -= amount;
  to.balance   += amount;

  await from.save();
  await to.save();
}

// Domain Model: encapsulate rules in the model (better for complex domains)
class Account {
  constructor(public balance: number, public currency: string) {}

  debit(amount: number, currency: string): void {
    if (currency !== this.currency) throw new Error('Currency mismatch');
    if (amount <= 0)                throw new Error('Amount must be positive');
    if (this.balance < amount)      throw new Error('Insufficient funds');
    this.balance -= amount;
  }

  credit(amount: number, currency: string): void {
    if (currency !== this.currency) throw new Error('Currency mismatch');
    if (amount <= 0)                throw new Error('Amount must be positive');
    this.balance += amount;
  }
}

// Service just orchestrates; rules live in the domain object
class TransferService {
  async transfer(fromId: string, toId: string, amount: number, currency: string) {
    const from = await AccountRepo.findById(fromId);
    const to   = await AccountRepo.findById(toId);

    from.debit(amount, currency);   // rule enforced by Account itself
    to.credit(amount, currency);

    await AccountRepo.saveAll([from, to]);
  }
}
```

---

## 14. Caching

### Cache Strategies (Know All Four)

```
1. Cache-Aside (Lazy Loading)    — most common
   App checks cache → if miss, reads DB, writes to cache, returns
   Pros: Only caches what's needed
   Cons: First request always slow (cold start)

2. Write-Through
   App writes to cache AND DB simultaneously
   Pros: Cache always fresh
   Cons: Extra write latency; may cache data that's never read

3. Write-Behind (Write-Back)
   App writes to cache only, async flush to DB
   Pros: Very fast writes
   Cons: Data loss risk if cache crashes before flush

4. Read-Through
   Cache sits in front of DB; app only talks to cache
   Pros: Simple app code
   Cons: Complex cache layer
```

### Redis Implementation

```javascript
// src/config/redis.ts
import Redis from 'ioredis';
import logger from '../utils/logger';

const client = new Redis({
  host:              process.env.REDIS_HOST ?? 'localhost',
  port:              Number(process.env.REDIS_PORT) || 6379,
  password:          process.env.REDIS_PASSWORD,
  db:                0,
  retryStrategy:     (times) => Math.min(times * 50, 2000),
  enableOfflineQueue: false,   // fail fast if disconnected
});

client.on('connect',    () => logger.info('Redis connected'));
client.on('error', (e) => logger.error('Redis error', { error: e }));

export default client;
```

```javascript
// src/utils/cache.ts
// Cache utility with TTL, namespacing, and invalidation

import redis from '../config/redis';

export class Cache {
  // Serialize complex values (handles dates, nested objects)
  private static serialize   = (v: unknown) => JSON.stringify(v);
  private static deserialize = <T>(v: string): T => JSON.parse(v) as T;

  static async get<T>(key: string): Promise<T | null> {
    const value = await redis.get(key);
    return value ? Cache.deserialize<T>(value) : null;
  }

  static async set<T>(key: string, value: T, ttlSeconds = 3600): Promise<void> {
    await redis.set(key, Cache.serialize(value), 'EX', ttlSeconds);
  }

  static async del(...keys: string[]): Promise<void> {
    if (keys.length > 0) await redis.del(...keys);
  }

  // Atomic get-or-set: prevents cache stampede (multiple requests hitting DB at once)
  static async getOrSet<T>(
    key:       string,
    fetcher:   () => Promise<T>,
    ttlSeconds = 3600
  ): Promise<T> {
    const cached = await Cache.get<T>(key);
    if (cached !== null) return cached;

    const value = await fetcher();
    await Cache.set(key, value, ttlSeconds);
    return value;
  }

  // Pattern-based invalidation (invalidate all user-related cache)
  static async invalidatePattern(pattern: string): Promise<void> {
    const keys = await redis.keys(pattern);
    if (keys.length > 0) await redis.del(...keys);
  }

  // Distributed lock (prevent race conditions)
  static async lock(key: string, ttlMs = 5000): Promise<boolean> {
    const result = await redis.set(`lock:${key}`, '1', 'PX', ttlMs, 'NX');
    return result === 'OK';
  }

  static async unlock(key: string): Promise<void> {
    await redis.del(`lock:${key}`);
  }
}
```

```javascript
// src/services/product.service.ts — with caching layer
export class ProductService {
  private cacheKey = {
    one:  (id: string)  => `product:${id}`,
    list: (hash: string) => `products:list:${hash}`,
  };

  async getById(id: string) {
    return Cache.getOrSet(
      this.cacheKey.one(id),
      () => this.productRepo.findById(id),
      300    // 5 minutes
    );
  }

  async getAll(query: ProductQuery) {
    // Hash the query params to create a unique cache key
    const hash = require('crypto')
      .createHash('md5')
      .update(JSON.stringify(query))
      .digest('hex');

    return Cache.getOrSet(
      this.cacheKey.list(hash),
      () => this.productRepo.findAll(query),
      60     // 1 minute for lists (changes more often)
    );
  }

  async update(id: string, data: Partial<Product>) {
    const updated = await this.productRepo.update(id, data);

    // Invalidate this product's cache and all list caches
    await Promise.all([
      Cache.del(this.cacheKey.one(id)),
      Cache.invalidatePattern('products:list:*'),
    ]);

    return updated;
  }
}
```

```javascript
// Cache middleware — cache entire HTTP responses
// src/middleware/cacheResponse.ts
export const cacheResponse = (ttlSeconds: number) => {
  return async (req: Request, res: Response, next: NextFunction) => {
    if (req.method !== 'GET') return next();   // only cache GET

    const key = `response:${req.originalUrl}`;
    const cached = await Cache.get<string>(key);

    if (cached) {
      res.setHeader('X-Cache', 'HIT');
      return res.json(JSON.parse(cached));
    }

    // Intercept json() to cache the response
    const originalJson = res.json.bind(res);
    res.json = (body: any) => {
      Cache.set(key, JSON.stringify(body), ttlSeconds);
      res.setHeader('X-Cache', 'MISS');
      return originalJson(body);
    };

    next();
  };
};

// Usage
router.get('/products', cacheResponse(60), ctrl.getAll);
```

---

## 15. Transactional Emails

### What it is

Transactional emails are triggered by user actions: welcome emails, password resets, order confirmations. They differ from marketing emails in that they're 1:1, time-sensitive, and expected.

```javascript
// src/services/email.service.ts
import nodemailer from 'nodemailer';

interface EmailOptions {
  to:       string | string[];
  subject:  string;
  html:     string;
  text?:    string;   // plain-text fallback
  from?:    string;
}

class EmailService {
  private transporter = nodemailer.createTransport({
    // Production: use SendGrid, AWS SES, Postmark, Resend
    host:   process.env.SMTP_HOST,
    port:   Number(process.env.SMTP_PORT) || 587,
    secure: false,
    auth: {
      user: process.env.SMTP_USER,
      pass: process.env.SMTP_PASS,
    },
  });

  async send(options: EmailOptions): Promise<void> {
    await this.transporter.sendMail({
      from:    options.from ?? `"${process.env.APP_NAME}" <noreply@myapp.com>`,
      to:      Array.isArray(options.to) ? options.to.join(', ') : options.to,
      subject: options.subject,
      html:    options.html,
      text:    options.text,
    });
  }

  async sendWelcome(email: string, name: string): Promise<void> {
    await this.send({
      to:      email,
      subject: `Welcome to ${process.env.APP_NAME}, ${name}!`,
      html:    this.templates.welcome(name),
    });
  }

  async sendPasswordReset(email: string, token: string): Promise<void> {
    const resetUrl = `${process.env.FRONTEND_URL}/reset-password?token=${token}`;
    await this.send({
      to:      email,
      subject: 'Reset your password',
      html:    this.templates.passwordReset(resetUrl),
    });
  }

  async sendOrderConfirmation(email: string, order: Order): Promise<void> {
    await this.send({
      to:      email,
      subject: `Order #${order.id} confirmed`,
      html:    this.templates.orderConfirmation(order),
    });
  }

  // HTML email templates
  private templates = {
    welcome: (name: string) => `
      <div style="font-family:sans-serif;max-width:600px;margin:0 auto">
        <h1>Welcome, ${name}!</h1>
        <p>Thanks for signing up. Your account is ready.</p>
        <a href="${process.env.FRONTEND_URL}" style="background:#4F46E5;color:white;
           padding:12px 24px;text-decoration:none;border-radius:6px;display:inline-block">
          Get Started
        </a>
      </div>`,

    passwordReset: (resetUrl: string) => `
      <div style="font-family:sans-serif;max-width:600px;margin:0 auto">
        <h2>Reset your password</h2>
        <p>Click the link below. It expires in 1 hour.</p>
        <a href="${resetUrl}">Reset Password</a>
        <p>If you didn't request this, ignore this email.</p>
      </div>`,

    orderConfirmation: (order: any) => `
      <div style="font-family:sans-serif;max-width:600px;margin:0 auto">
        <h2>Order Confirmed ✅</h2>
        <p>Order #${order.id} — Total: $${order.total}</p>
      </div>`,
  };
}

export default new EmailService();
```

---

## 16. Task Queuing & Scheduling

### Why Queues?

```
Problem: Some operations are slow (sending email, resizing image, calling external API).
         Don't make the user wait for them in the HTTP response.

Solution: Queue → the API returns immediately, a worker processes later.

Also: Queues add retry logic, handle failures, prevent overloading external services.
```

### BullMQ — Production Queue Implementation

```javascript
// src/queues/email.queue.ts
import { Queue, Worker, QueueEvents } from 'bullmq';
import redis from '../config/redis';
import EmailService from '../services/email.service';
import logger from '../utils/logger';

// Job data types
interface WelcomeEmailJob  { userId: string; email: string; name: string }
interface OrderEmailJob    { orderId: string; userEmail: string }
interface ReportEmailJob   { adminEmail: string; reportData: object }

// Create queue
export const emailQueue = new Queue('emails', {
  connection: redis,
  defaultJobOptions: {
    attempts:   3,                       // retry failed jobs up to 3 times
    backoff: {
      type:   'exponential',
      delay:  2000,                      // 2s, 4s, 8s
    },
    removeOnComplete: { count: 100 },    // keep last 100 completed jobs
    removeOnFail:     { count: 500 },    // keep last 500 failed jobs
  },
});

// Create worker (can run in a separate process)
export const emailWorker = new Worker(
  'emails',
  async (job) => {
    logger.info(`Processing email job: ${job.name}`, { jobId: job.id });

    switch (job.name) {
      case 'welcome':
        await EmailService.sendWelcome(job.data.email, job.data.name);
        break;
      case 'order-confirmation':
        await EmailService.sendOrderConfirmation(job.data.userEmail, job.data.orderId);
        break;
      case 'report':
        // Generate and send report...
        break;
      default:
        throw new Error(`Unknown job type: ${job.name}`);
    }
  },
  {
    connection:  redis,
    concurrency: 5,   // process 5 jobs simultaneously
  }
);

// Worker event listeners
emailWorker.on('completed', (job) => {
  logger.info(`Email job completed: ${job.id}`);
});

emailWorker.on('failed', (job, err) => {
  logger.error(`Email job failed: ${job?.id}`, { error: err.message });
  // Alert on-call if 3 retries exhausted
  if (job?.attemptsMade >= 3) {
    AlertService.page(`Email queue job ${job.id} exhausted all retries`);
  }
});
```

```javascript
// Enqueue jobs from your service (returns immediately)
// src/services/user.service.ts

export class UserService {
  async register(data: RegisterInput) {
    const user = await this.userRepo.create(data);

    // Don't await — fire and forget into the queue
    await emailQueue.add('welcome', {
      userId: user.id,
      email:  user.email,
      name:   user.name,
    });

    return user;
  }
}
```

### Scheduled Jobs (Cron)

```javascript
// src/scheduler/jobs.ts
import { Queue } from 'bullmq';
import redis from '../config/redis';

const schedulerQueue = new Queue('scheduler', { connection: redis });

// Schedule recurring jobs
async function setupScheduledJobs() {
  // Run every day at 2am UTC
  await schedulerQueue.add(
    'daily-report',
    { type: 'dailyReport' },
    {
      repeat: { pattern: '0 2 * * *' },   // cron syntax
    }
  );

  // Run every hour
  await schedulerQueue.add(
    'cleanup-expired-tokens',
    {},
    {
      repeat: { every: 60 * 60 * 1000 },  // every 60 minutes
    }
  );

  // Run once at a specific time (future)
  const sendAt = new Date('2024-12-25T09:00:00Z');
  await schedulerQueue.add(
    'christmas-promo',
    { promoCode: 'XMAS24' },
    {
      delay: sendAt.getTime() - Date.now(),
    }
  );
}
```

---

## 17. Elasticsearch

### What it is

Elasticsearch is a distributed search engine built on Apache Lucene. Use it when MongoDB/PostgreSQL text search is too slow or too limited. It excels at full-text search, faceted filtering, and log analytics.

### When to use Elasticsearch

```
✅ Full-text search with relevance ranking
✅ Autocomplete / typeahead suggestions
✅ Faceted search (filter by category + price range simultaneously)
✅ Log aggregation (ELK Stack)
✅ Geographic search
✅ Time-series analytics

❌ Primary data store (use as a read replica)
❌ Strong ACID transactions
❌ Simple lookups by ID
```

### Integration Pattern

```javascript
// src/config/elasticsearch.ts
import { Client } from '@elastic/elasticsearch';

export const esClient = new Client({
  node:  process.env.ELASTICSEARCH_URL ?? 'http://localhost:9200',
  auth: {
    username: process.env.ES_USERNAME ?? 'elastic',
    password: process.env.ES_PASSWORD ?? '',
  },
});
```

```javascript
// src/services/search.service.ts
export class SearchService {

  // Create index with mapping (run once at setup)
  async createProductIndex(): Promise<void> {
    const exists = await esClient.indices.exists({ index: 'products' });
    if (exists) return;

    await esClient.indices.create({
      index: 'products',
      mappings: {
        properties: {
          id:          { type: 'keyword' },
          name:        { type: 'text',    analyzer: 'english' },
          description: { type: 'text',    analyzer: 'english' },
          category:    { type: 'keyword' },    // exact match
          price:       { type: 'double' },
          tags:        { type: 'keyword' },
          stock:       { type: 'integer' },
          createdAt:   { type: 'date' },
          // Autocomplete field
          nameSuggest: { type: 'completion' },
        },
      },
      settings: {
        number_of_shards:   1,
        number_of_replicas: 0,
      },
    });
  }

  // Index a product (call after create/update in MongoDB)
  async indexProduct(product: any): Promise<void> {
    await esClient.index({
      index: 'products',
      id:    product._id.toString(),
      document: {
        id:          product._id.toString(),
        name:        product.name,
        description: product.description,
        category:    product.category,
        price:       product.price,
        tags:        product.tags,
        stock:       product.stock,
        createdAt:   product.createdAt,
        nameSuggest: { input: [product.name, ...product.tags] },
      },
    });
  }

  // Full-text search with filters
  async searchProducts(query: SearchQuery) {
    const { search, category, minPrice, maxPrice, inStock, page = 1, limit = 10 } = query;

    const must:   any[] = [];
    const filter: any[] = [];

    // Full-text search on name + description
    if (search) {
      must.push({
        multi_match: {
          query:  search,
          fields: ['name^3', 'description'],    // ^3 boosts name score
          type:   'best_fields',
          fuzziness: 'AUTO',                    // handles typos
        },
      });
    }

    // Filters (don't affect relevance score)
    if (category)            filter.push({ term:  { category } });
    if (inStock)             filter.push({ range: { stock: { gt: 0 } } });
    if (minPrice || maxPrice) {
      filter.push({
        range: {
          price: {
            ...(minPrice && { gte: minPrice }),
            ...(maxPrice && { lte: maxPrice }),
          },
        },
      });
    }

    const result = await esClient.search({
      index: 'products',
      from:  (page - 1) * limit,
      size:  limit,
      query: {
        bool: { must, filter },
      },
      aggs: {
        // Facets: count results per category
        by_category: {
          terms: { field: 'category', size: 20 },
        },
        price_range: {
          stats: { field: 'price' },    // min, max, avg, sum
        },
      },
      highlight: {
        fields: {
          name:        {},
          description: { fragment_size: 150 },
        },
      },
    });

    return {
      products:   result.hits.hits.map(h => ({ ...h._source, score: h._score })),
      total:      (result.hits.total as any).value,
      facets: {
        categories: result.aggregations?.by_category,
        priceStats: result.aggregations?.price_range,
      },
    };
  }

  // Autocomplete
  async suggest(prefix: string): Promise<string[]> {
    const result = await esClient.search({
      index: 'products',
      suggest: {
        nameSuggester: {
          prefix,
          completion: { field: 'nameSuggest', size: 5, skip_duplicates: true },
        },
      },
    });

    const suggestions = (result.suggest?.nameSuggester?.[0]?.options ?? []) as any[];
    return suggestions.map((s: any) => s.text);
  }
}
```

---

## 18. Error Handling

### The Golden Rules

```
1. Never expose internal errors to clients (stack traces, DB details)
2. Always return consistent error shapes
3. Log errors with full context server-side
4. Distinguish operational errors (expected) from programmer errors (bugs)
5. Use custom error classes to carry metadata
```

### Custom Error Hierarchy

```javascript
// src/errors/AppError.ts

export class AppError extends Error {
  constructor(
    public readonly message:    string,
    public readonly statusCode: number,
    public readonly code:       string,       // machine-readable error code
    public readonly details?:   unknown,
    public readonly isOperational = true,     // vs programmer error
  ) {
    super(message);
    this.name = this.constructor.name;
    Error.captureStackTrace(this, this.constructor);
  }
}

export class ValidationError extends AppError {
  constructor(message: string, details?: unknown) {
    super(message, 422, 'VALIDATION_ERROR', details);
  }
}

export class NotFoundError extends AppError {
  constructor(resource = 'Resource') {
    super(`${resource} not found`, 404, 'NOT_FOUND');
  }
}

export class ConflictError extends AppError {
  constructor(message: string) {
    super(message, 409, 'CONFLICT');
  }
}

export class UnauthorizedError extends AppError {
  constructor(message = 'Not authenticated') {
    super(message, 401, 'UNAUTHORIZED');
  }
}

export class ForbiddenError extends AppError {
  constructor(message = 'Insufficient permissions') {
    super(message, 403, 'FORBIDDEN');
  }
}

export class TooManyRequestsError extends AppError {
  constructor(public readonly retryAfter: number) {
    super('Too many requests', 429, 'RATE_LIMITED', { retryAfter });
  }
}

export class ExternalServiceError extends AppError {
  constructor(service: string, message: string) {
    super(`${service}: ${message}`, 502, 'EXTERNAL_SERVICE_ERROR');
  }
}
```

```javascript
// src/middleware/errorHandler.ts
// Global error handler — MUST have 4 parameters

import { Request, Response, NextFunction } from 'express';
import { AppError } from '../errors/AppError';
import { ZodError } from 'zod';
import logger from '../utils/logger';

export const errorHandler = (
  err: Error,
  req: Request,
  res: Response,
  _next: NextFunction
) => {
  // 1. Log everything
  const context = {
    requestId: req.id,
    method:    req.method,
    url:       req.originalUrl,
    userId:    req.user?.userId,
    error: {
      name:    err.name,
      message: err.message,
      stack:   err.stack,
    },
  };

  // 2. Handle known error types
  if (err instanceof AppError) {
    if (!err.isOperational) {
      logger.error('Programmer error!', context);
      // Alert on-call / PagerDuty
    } else {
      logger.warn('Operational error', context);
    }

    return res.status(err.statusCode).json({
      success: false,
      error:   err.message,
      code:    err.code,
      ...(err.details && { details: err.details }),
    });
  }

  // 3. Handle Mongoose validation errors
  if (err.name === 'ValidationError') {
    const details = Object.values((err as any).errors).map((e: any) => ({
      field:   e.path,
      message: e.message,
    }));
    return res.status(422).json({ success: false, error: 'Validation failed', details });
  }

  if (err.name === 'CastError') {
    return res.status(400).json({ success: false, error: 'Invalid ID format' });
  }

  if ((err as any).code === 11000) {   // Mongoose duplicate key
    const field = Object.keys((err as any).keyValue)[0];
    return res.status(409).json({
      success: false,
      error:   `${field} already exists`,
    });
  }

  // 4. Handle JWT errors
  if (err.name === 'JsonWebTokenError')  return res.status(401).json({ success: false, error: 'Invalid token' });
  if (err.name === 'TokenExpiredError')  return res.status(401).json({ success: false, error: 'Token expired' });

  // 5. Unknown errors — don't leak details in production
  logger.error('Unhandled error', context);

  res.status(500).json({
    success: false,
    error:   process.env.NODE_ENV === 'production'
      ? 'Internal server error'
      : err.message,
    ...(process.env.NODE_ENV !== 'production' && { stack: err.stack }),
  });
};

// Catch async errors — wrap controllers or use this helper
export const asyncHandler = (fn: Function) =>
  (req: Request, res: Response, next: NextFunction) =>
    Promise.resolve(fn(req, res, next)).catch(next);
```

```javascript
// Unhandled promise rejections and exceptions — last safety net
// src/app.ts

process.on('unhandledRejection', (reason, promise) => {
  logger.error('Unhandled Rejection', { reason });
  // Graceful shutdown
  process.exit(1);
});

process.on('uncaughtException', (error) => {
  logger.error('Uncaught Exception', { error });
  process.exit(1);
});
```

---

## 19. Config Management

### The 12-Factor Way

```
All configuration comes from environment variables.
Never hardcode secrets. Never commit .env to Git.
Different values per environment (dev/staging/production).
```

```javascript
// src/config/index.ts
import { z } from 'zod';
import 'dotenv/config';

// Validate ALL env vars at startup — fail fast if anything is missing
const envSchema = z.object({
  // App
  NODE_ENV:         z.enum(['development', 'staging', 'production']).default('development'),
  PORT:             z.coerce.number().default(3000),
  APP_NAME:         z.string().default('MyApp'),
  FRONTEND_URL:     z.string().url(),

  // Database
  MONGODB_URI:      z.string().min(1, 'MONGODB_URI is required'),

  // JWT
  JWT_SECRET:       z.string().min(32, 'JWT_SECRET must be at least 32 characters'),
  JWT_REFRESH_SECRET: z.string().min(32),

  // Redis
  REDIS_HOST:       z.string().default('localhost'),
  REDIS_PORT:       z.coerce.number().default(6379),
  REDIS_PASSWORD:   z.string().optional(),

  // Email
  SMTP_HOST:        z.string().optional(),
  SMTP_PORT:        z.coerce.number().optional(),
  SMTP_USER:        z.string().optional(),
  SMTP_PASS:        z.string().optional(),

  // AWS S3
  AWS_ACCESS_KEY_ID:     z.string().optional(),
  AWS_SECRET_ACCESS_KEY: z.string().optional(),
  AWS_REGION:            z.string().default('us-east-1'),
  S3_BUCKET:             z.string().optional(),

  // Rate limiting
  RATE_LIMIT_WINDOW_MS:  z.coerce.number().default(60_000),
  RATE_LIMIT_MAX:        z.coerce.number().default(100),
});

// Parse and validate — throws at startup if invalid
const parsed = envSchema.safeParse(process.env);

if (!parsed.success) {
  console.error('❌ Invalid environment variables:');
  console.error(parsed.error.flatten().fieldErrors);
  process.exit(1);
}

export const config = parsed.data;
export type Config  = typeof config;

// Type-safe usage anywhere:
// import { config } from '../config';
// config.PORT  ← typed as number
// config.NODE_ENV  ← typed as 'development' | 'staging' | 'production'
```

### Feature Flags

```javascript
// src/config/featureFlags.ts
// Simple feature flags — use LaunchDarkly or ConfigCat in production

const flags = {
  newCheckoutFlow:     process.env.FF_NEW_CHECKOUT     === 'true',
  aiRecommendations:   process.env.FF_AI_RECOMMENDATIONS === 'true',
  maintenanceMode:     process.env.FF_MAINTENANCE       === 'true',
};

export const featureFlags = {
  isEnabled: (flag: keyof typeof flags): boolean => flags[flag] ?? false,
};

// Usage
if (featureFlags.isEnabled('newCheckoutFlow')) {
  // use new flow
} else {
  // use old flow
}
```

---

## 20. Logging, Monitoring & Observability

### The Three Pillars of Observability

```
Logs    — What happened (text records of events)
Metrics — How much / how often (numbers over time: req/s, error rate, latency)
Traces  — Where time was spent (distributed request flow across services)
```

### Structured Logging with Winston

```javascript
// src/utils/logger.ts
import winston from 'winston';
import { config } from '../config';

const { combine, timestamp, errors, json, colorize, printf } = winston.format;

// Human-readable format for development
const devFormat = combine(
  colorize(),
  timestamp({ format: 'HH:mm:ss' }),
  errors({ stack: true }),
  printf(({ level, message, timestamp, ...meta }) => {
    const metaStr = Object.keys(meta).length ? JSON.stringify(meta, null, 2) : '';
    return `${timestamp} [${level}]: ${message} ${metaStr}`;
  })
);

// Machine-readable JSON for production (ingested by Datadog, CloudWatch, etc.)
const prodFormat = combine(
  timestamp(),
  errors({ stack: true }),
  json()
);

const logger = winston.createLogger({
  level:  config.NODE_ENV === 'production' ? 'info' : 'debug',
  format: config.NODE_ENV === 'production' ? prodFormat : devFormat,
  defaultMeta: {
    service:     config.APP_NAME,
    environment: config.NODE_ENV,
  },
  transports: [
    new winston.transports.Console(),
    // In production, also ship to file or external service:
    ...(config.NODE_ENV === 'production'
      ? [new winston.transports.File({ filename: 'logs/error.log', level: 'error' }),
         new winston.transports.File({ filename: 'logs/combined.log' })]
      : []),
  ],
});

export default logger;
```

```javascript
// HTTP request logging with Morgan → Winston
import morgan from 'morgan';

const stream = {
  write: (message: string) => logger.http(message.trim()),
};

export const httpLogger = morgan(
  ':method :url :status :res[content-length] - :response-time ms',
  { stream }
);

// Log with request context
export const logWithContext = (level: string, message: string, meta: object = {}) => {
  const ctx = RequestContext.get();
  logger.log(level, message, {
    requestId: ctx?.requestId,
    userId:    ctx?.userId,
    ...meta,
  });
};
```

### Metrics with Prometheus

```javascript
// src/utils/metrics.ts
import { register, Counter, Histogram, Gauge } from 'prom-client';

// Collect default Node.js metrics (memory, CPU, event loop lag)
import { collectDefaultMetrics } from 'prom-client';
collectDefaultMetrics();

// Custom metrics
export const httpRequestCount = new Counter({
  name:    'http_requests_total',
  help:    'Total number of HTTP requests',
  labelNames: ['method', 'route', 'status_code'],
});

export const httpRequestDuration = new Histogram({
  name:    'http_request_duration_seconds',
  help:    'HTTP request duration in seconds',
  labelNames: ['method', 'route', 'status_code'],
  buckets:    [0.005, 0.01, 0.025, 0.05, 0.1, 0.25, 0.5, 1, 2.5, 5],
});

export const activeConnections = new Gauge({
  name: 'active_connections',
  help: 'Number of active connections',
});

// Middleware to record metrics
export const metricsMiddleware = (req: Request, res: Response, next: NextFunction) => {
  const start = Date.now();

  res.on('finish', () => {
    const duration = (Date.now() - start) / 1000;
    const route    = req.route?.path ?? req.path;

    httpRequestCount.inc({
      method:      req.method,
      route,
      status_code: res.statusCode,
    });

    httpRequestDuration.observe({
      method:      req.method,
      route,
      status_code: res.statusCode,
    }, duration);
  });

  next();
};

// Expose metrics endpoint for Prometheus to scrape
app.get('/metrics', async (req, res) => {
  res.setHeader('Content-Type', register.contentType);
  res.send(await register.metrics());
});
```

### Health Check Endpoint

```javascript
// src/routes/health.routes.ts
router.get('/health', async (req, res) => {
  const checks = await Promise.allSettled([
    mongoose.connection.db.admin().ping(),    // MongoDB
    redis.ping(),                             // Redis
  ]);

  const [mongoCheck, redisCheck] = checks;

  const status = {
    status:    checks.every(c => c.status === 'fulfilled') ? 'healthy' : 'degraded',
    timestamp: new Date().toISOString(),
    uptime:    process.uptime(),
    services: {
      mongodb: mongoCheck.status === 'fulfilled' ? 'up' : 'down',
      redis:   redisCheck.status === 'fulfilled' ? 'up' : 'down',
    },
    memory: {
      used:  `${Math.round(process.memoryUsage().heapUsed / 1024 / 1024)}MB`,
      total: `${Math.round(process.memoryUsage().heapTotal / 1024 / 1024)}MB`,
    },
  };

  const httpStatus = status.status === 'healthy' ? 200 : 503;
  res.status(httpStatus).json(status);
});

// Kubernetes liveness/readiness probes
router.get('/health/live',  (req, res) => res.send('OK'));
router.get('/health/ready', async (req, res) => {
  const dbOk = mongoose.connection.readyState === 1;
  dbOk ? res.send('OK') : res.status(503).send('Not ready');
});
```

---

## 21. Graceful Shutdown

### What it is

When your server receives a shutdown signal (SIGTERM from Kubernetes, SIGINT from Ctrl+C), it should:
1. Stop accepting new requests
2. Finish in-flight requests
3. Close DB connections
4. Flush logs
5. Exit cleanly

Failing to do this causes dropped requests, data corruption, and zombie connections.

```javascript
// src/utils/shutdown.ts
import http from 'http';
import logger from './logger';
import { disconnectDatabase } from '../config/database';
import redis from '../config/redis';
import { emailWorker } from '../queues/email.queue';

export function setupGracefulShutdown(server: http.Server): void {
  let isShuttingDown = false;

  const shutdown = async (signal: string) => {
    if (isShuttingDown) return;
    isShuttingDown = true;

    logger.info(`${signal} received — starting graceful shutdown`);

    // 1. Stop accepting new connections
    server.close(async () => {
      logger.info('HTTP server closed — no new connections accepted');

      try {
        // 2. Close queue workers (finish current jobs)
        await emailWorker.close();
        logger.info('Queue workers closed');

        // 3. Disconnect database
        await disconnectDatabase();
        logger.info('Database disconnected');

        // 4. Close Redis
        await redis.quit();
        logger.info('Redis disconnected');

        logger.info('Graceful shutdown complete');
        process.exit(0);
      } catch (error) {
        logger.error('Error during shutdown', { error });
        process.exit(1);
      }
    });

    // Force exit if graceful shutdown takes too long
    setTimeout(() => {
      logger.error('Forced shutdown — graceful shutdown timeout exceeded');
      process.exit(1);
    }, 30_000);  // 30 second deadline
  };

  process.on('SIGTERM', () => shutdown('SIGTERM'));  // Kubernetes sends this
  process.on('SIGINT',  () => shutdown('SIGINT'));   // Ctrl+C
}

// src/server.ts
import app    from './app';
import logger from './utils/logger';
import { config } from './config';
import { setupGracefulShutdown } from './utils/shutdown';
import { connectDatabase }  from './config/database';

async function start() {
  await connectDatabase();

  const server = app.listen(config.PORT, () => {
    logger.info(`Server running on port ${config.PORT} in ${config.NODE_ENV} mode`);
  });

  setupGracefulShutdown(server);
}

start().catch((err) => {
  logger.error('Failed to start server', { err });
  process.exit(1);
});
```

---

## 22. Security

### The Security Checklist

```
✅ HTTPS everywhere
✅ Helmet.js (security headers)
✅ Rate limiting
✅ Input validation (Zod)
✅ bcrypt for passwords (never MD5/SHA1)
✅ JWT with short expiry (15m access, 7d refresh)
✅ Refresh tokens stored httpOnly cookies
✅ CORS properly configured
✅ SQL/NoSQL injection prevention
✅ XSS prevention (sanitise HTML output)
✅ CSRF protection
✅ Secrets in env vars (never source code)
✅ Dependency auditing (npm audit)
```

```javascript
// src/app.ts — security middleware stack

import helmet    from 'helmet';
import rateLimit from 'express-rate-limit';
import mongoSanitize from 'express-mongo-sanitize';
import xss from 'xss-clean';
import hpp from 'hpp';

app.use(helmet({
  contentSecurityPolicy: {
    directives: {
      defaultSrc: ["'self'"],
      styleSrc:   ["'self'", "'unsafe-inline'"],
      scriptSrc:  ["'self'"],
      imgSrc:     ["'self'", 'data:', 'https:'],
    },
  },
  hsts: {
    maxAge:            31_536_000,   // 1 year
    includeSubDomains: true,
    preload:           true,
  },
}));

// NoSQL injection prevention — strips $ and . from inputs
app.use(mongoSanitize());

// XSS prevention — sanitises HTML tags from req.body, query, params
app.use(xss());

// HTTP Parameter Pollution prevention
app.use(hpp({ whitelist: ['sort', 'fields'] }));

// Rate limiting
app.use('/api/', rateLimit({
  windowMs: 15 * 60 * 1000,   // 15 minutes
  max:      100,
  message:  { error: 'Too many requests, please try again later' },
  standardHeaders: true,
  legacyHeaders:   false,
}));

// Auth endpoints — stricter limit
app.use('/api/v1/auth/', rateLimit({
  windowMs: 15 * 60 * 1000,
  max:      5,
  message:  { error: 'Too many auth attempts' },
}));
```

```javascript
// CSRF Protection (for cookie-based auth)
// src/middleware/csrf.ts
import crypto from 'crypto';

export const csrfProtection = {
  generateToken: (): string => crypto.randomBytes(32).toString('hex'),

  middleware: (req: Request, res: Response, next: NextFunction) => {
    if (['GET', 'HEAD', 'OPTIONS'].includes(req.method)) return next();

    const sessionToken = req.session?.csrfToken;
    const headerToken  = req.headers['x-csrf-token'] as string;

    if (!sessionToken || !headerToken || sessionToken !== headerToken) {
      return res.status(403).json({ error: 'Invalid CSRF token' });
    }
    next();
  },
};

// SQL injection — parameterised queries (with pg/mysql2)
// ❌ NEVER do this:
const bad = `SELECT * FROM users WHERE email = '${email}'`;

// ✅ Always parameterise:
const good = await db.query('SELECT * FROM users WHERE email = $1', [email]);
```

---

## 23. Scaling & Performance

### Scaling Strategies

```
Vertical Scaling   — bigger machine (more RAM, faster CPU). Simple. Has a ceiling.
Horizontal Scaling — more machines behind a load balancer. Complex. No ceiling.

Scale Up first (easy wins: caching, DB indexes, query optimization)
Scale Out second (load balancers, stateless services, sharding)
```

### Load Balancing Strategies

```
Round Robin       — requests distributed evenly (default, good for stateless apps)
Least Connections — send to server with fewest active connections
IP Hash           — same client always hits same server (sticky sessions)
Weighted          — more traffic to more powerful servers
```

### N+1 Query Problem

```javascript
// ❌ N+1: 1 query for orders + N queries for each user
const orders = await Order.find();
for (const order of orders) {
  const user = await User.findById(order.userId);   // N queries!
  order.user = user;
}

// ✅ Solution 1: Mongoose populate (2 queries total)
const orders = await Order.find().populate('userId', 'name email');

// ✅ Solution 2: Lookup all at once (1 query)
const orders = await Order.find();
const userIds = [...new Set(orders.map(o => o.userId.toString()))];
const users   = await User.find({ _id: { $in: userIds } });
const userMap = Object.fromEntries(users.map(u => [u.id, u]));
orders.forEach(o => (o.user = userMap[o.userId.toString()]));

// ✅ Solution 3: MongoDB aggregation $lookup (1 query, done in DB)
const orders = await Order.aggregate([
  { $lookup: {
    from:         'users',
    localField:   'userId',
    foreignField: '_id',
    as:           'user',
  }},
  { $unwind: '$user' },
  { $project: { 'user.password': 0 } },
]);
```

### Response Compression

```javascript
import compression from 'compression';

app.use(compression({
  filter: (req, res) => {
    if (req.headers['x-no-compression']) return false;
    return compression.filter(req, res);
  },
  level:     6,        // 0 (fastest) to 9 (best compression). 6 is the sweet spot.
  threshold: 1024,     // only compress responses > 1KB
}));
```

### Connection Pooling

```javascript
// MongoDB — already pooled via Mongoose maxPoolSize
// PostgreSQL — pgPool
import { Pool } from 'pg';

const pool = new Pool({
  connectionString: process.env.DATABASE_URL,
  max:     20,           // max connections in pool
  idleTimeoutMillis: 30_000,
  connectionTimeoutMillis: 2_000,
});

// Each query grabs a connection from the pool, returns it after
const result = await pool.query('SELECT * FROM users WHERE id = $1', [id]);
```

### Database Query Optimization

```javascript
// 1. Use .lean() in Mongoose — returns plain JS object, not Mongoose Document
//    ~3x faster for read-only operations
const users = await User.find().lean();

// 2. Only select fields you need
const user = await User.findById(id).select('name email role').lean();

// 3. Use cursor for large datasets (avoid loading all into memory)
const cursor = User.find({ isActive: true }).cursor();
for await (const user of cursor) {
  await processUser(user);
}

// 4. Explain your queries (check if indexes are being used)
const explanation = await User.find({ email: 'a@b.com' }).explain('executionStats');
console.log(explanation.executionStats);
// Look for: "stage": "IXSCAN" (good) vs "COLLSCAN" (bad — no index)

// 5. Avoid regex on non-indexed fields
// ❌ Slow: full collection scan
User.find({ name: { $regex: 'alice', $options: 'i' } });

// ✅ Fast: use text index
User.createIndex({ name: 'text' });
User.find({ $text: { $search: 'alice' } });
```

---

## 24. Concurrency & Parallelism

### JavaScript's Concurrency Model

```
JavaScript is single-threaded — only ONE thing runs at a time.
But it handles concurrency via the EVENT LOOP:
  - I/O operations (DB, network) are non-blocking
  - While waiting for I/O, the event loop processes other callbacks
  - Multiple "in-flight" operations = concurrency (not parallelism)

True parallelism in Node.js = Worker Threads (CPU-intensive tasks)
```

### Parallel vs Sequential Async Operations

```javascript
// ❌ Sequential — total time = sum of all (slow)
const user    = await UserService.getById(userId);      // 50ms
const orders  = await OrderService.getByUser(userId);   // 80ms
const reviews = await ReviewService.getByUser(userId);  // 60ms
// Total: ~190ms

// ✅ Parallel — total time = slowest operation (fast)
const [user, orders, reviews] = await Promise.all([
  UserService.getById(userId),      // \
  OrderService.getByUser(userId),   //  → all run simultaneously
  ReviewService.getByUser(userId),  // /
]);
// Total: ~80ms (slowest)

// ✅ Promise.allSettled — continues even if some fail
const results = await Promise.allSettled([
  fetchFromServiceA(),
  fetchFromServiceB(),
  fetchFromServiceC(),
]);

for (const result of results) {
  if (result.status === 'fulfilled') {
    console.log('Success:', result.value);
  } else {
    console.error('Failed:', result.reason);
  }
}

// ✅ Controlled concurrency — limit parallel operations (prevent DB overload)
import pLimit from 'p-limit';

const limit = pLimit(5);   // max 5 concurrent

const tasks = userIds.map(id =>
  limit(() => UserService.processUser(id))   // only 5 run at once
);
await Promise.all(tasks);
```

### Worker Threads (CPU-Intensive Tasks)

```javascript
// src/workers/imageProcessor.worker.ts
// Run in a separate thread — doesn't block the event loop

import { workerData, parentPort } from 'worker_threads';
import sharp from 'sharp';

const { inputPath, outputPath, width, height } = workerData;

async function processImage() {
  await sharp(inputPath)
    .resize(width, height)
    .webp({ quality: 80 })
    .toFile(outputPath);

  parentPort?.postMessage({ success: true, outputPath });
}

processImage().catch(err => {
  parentPort?.postMessage({ success: false, error: err.message });
});
```

```javascript
// src/services/image.service.ts — spawn worker thread
import { Worker } from 'worker_threads';
import path from 'path';

export const processImageInWorker = (inputPath: string): Promise<string> => {
  return new Promise((resolve, reject) => {
    const worker = new Worker(
      path.join(__dirname, '../workers/imageProcessor.worker.js'),
      {
        workerData: {
          inputPath,
          outputPath: inputPath.replace(/\.\w+$/, '.webp'),
          width:  800,
          height: 600,
        },
      }
    );

    worker.on('message', ({ success, outputPath, error }) => {
      if (success) resolve(outputPath);
      else         reject(new Error(error));
    });

    worker.on('error',  reject);
    worker.on('exit', (code) => {
      if (code !== 0) reject(new Error(`Worker exited with code ${code}`));
    });
  });
};
```

### Race Conditions & Distributed Locks

```javascript
// Problem: Two requests both check stock → both see 1 → both decrement → stock goes to -1

// ❌ Race condition
const product = await Product.findById(id);
if (product.stock < quantity) throw new Error('Out of stock');
await Product.findByIdAndUpdate(id, { $inc: { stock: -quantity } });

// ✅ Solution 1: Atomic MongoDB operation (best for single-field)
const product = await Product.findOneAndUpdate(
  { _id: id, stock: { $gte: quantity } },   // condition + update atomically
  { $inc: { stock: -quantity } },
  { new: true }
);
if (!product) throw new Error('Out of stock or not found');

// ✅ Solution 2: Redis distributed lock (for multi-step operations)
async function processOrderWithLock(orderId: string) {
  const lockKey = `lock:order:${orderId}`;
  const acquired = await Cache.lock(lockKey, 10_000);   // 10 second lock

  if (!acquired) {
    throw new ConflictError('Order is being processed by another request');
  }

  try {
    // Critical section — only one process runs this at a time
    await processOrder(orderId);
  } finally {
    await Cache.unlock(lockKey);   // always release
  }
}
```

---

## 25. Object Storage & Large Files

### Architecture: Never Store Files in Your Database

```
❌ Don't: Save file binary in MongoDB / PostgreSQL (slow, expensive)
✅ Do:    Upload to S3 (or compatible: Cloudflare R2, MinIO, GCS)
          Store only the URL/key in your database
```

### Direct Upload (Client → S3 via Presigned URL)

```
The secure, scalable pattern:

1. Client requests a presigned URL from your API
2. API generates a presigned URL (valid for 5 minutes)
3. Client uploads directly to S3 (bypasses your server!)
4. Client notifies your API that upload is complete
5. Your API stores the S3 key in the database
```

```javascript
// src/services/storage.service.ts
import {
  S3Client,
  PutObjectCommand,
  GetObjectCommand,
  DeleteObjectCommand,
} from '@aws-sdk/client-s3';
import { getSignedUrl } from '@aws-sdk/s3-request-presigner';
import { v4 as uuid } from 'uuid';
import { config } from '../config';

const s3 = new S3Client({
  region:      config.AWS_REGION,
  credentials: {
    accessKeyId:     config.AWS_ACCESS_KEY_ID!,
    secretAccessKey: config.AWS_SECRET_ACCESS_KEY!,
  },
});

export class StorageService {
  // Generate presigned URL for client-side upload
  async getUploadUrl(options: {
    folder:      string;
    fileName:    string;
    contentType: string;
    maxSizeMB?:  number;
  }): Promise<{ uploadUrl: string; key: string; publicUrl: string }> {
    const { folder, fileName, contentType, maxSizeMB = 10 } = options;

    // Sanitise filename and add unique prefix (prevent collisions)
    const ext       = fileName.split('.').pop();
    const key       = `${folder}/${uuid()}.${ext}`;

    const command   = new PutObjectCommand({
      Bucket:        config.S3_BUCKET,
      Key:           key,
      ContentType:   contentType,
      ContentLength: maxSizeMB * 1024 * 1024,   // enforce size limit
      Metadata: {
        originalName: fileName,
      },
    });

    const uploadUrl  = await getSignedUrl(s3, command, { expiresIn: 300 });   // 5 min
    const publicUrl  = `https://${config.S3_BUCKET}.s3.${config.AWS_REGION}.amazonaws.com/${key}`;

    return { uploadUrl, key, publicUrl };
  }

  // Generate presigned URL for private file download
  async getDownloadUrl(key: string, expiresIn = 3600): Promise<string> {
    const command = new GetObjectCommand({
      Bucket: config.S3_BUCKET,
      Key:    key,
    });
    return getSignedUrl(s3, command, { expiresIn });
  }

  // Delete a file
  async delete(key: string): Promise<void> {
    await s3.send(new DeleteObjectCommand({
      Bucket: config.S3_BUCKET,
      Key:    key,
    }));
  }
}
```

```javascript
// Multer for server-side uploads (when you need to process before storing)
import multer from 'multer';

// Store in memory (for small files to process, then stream to S3)
const upload = multer({
  storage: multer.memoryStorage(),
  limits:  { fileSize: 10 * 1024 * 1024 },    // 10MB
  fileFilter: (req, file, cb) => {
    const allowed = ['image/jpeg', 'image/png', 'image/webp', 'application/pdf'];
    if (allowed.includes(file.mimetype)) {
      cb(null, true);
    } else {
      cb(new ValidationError(`File type ${file.mimetype} not allowed`));
    }
  },
});

// Route
router.post('/upload/avatar',
  authenticate,
  upload.single('avatar'),    // field name in form-data
  ctrl.uploadAvatar
);
```

---

## 26. Real-Time Backend Systems

### WebSockets with Socket.io

```javascript
// src/realtime/socket.ts
import { Server } from 'socket.io';
import http from 'http';
import { verifyAccessToken } from '../utils/jwt';
import logger from '../utils/logger';

export function setupSocketIO(httpServer: http.Server): Server {
  const io = new Server(httpServer, {
    cors: {
      origin:      process.env.FRONTEND_URL,
      credentials: true,
    },
    transports: ['websocket', 'polling'],
  });

  // Auth middleware for WebSocket connections
  io.use((socket, next) => {
    const token = socket.handshake.auth.token
               ?? socket.handshake.headers.authorization?.split(' ')[1];

    if (!token) return next(new Error('Authentication required'));

    try {
      const decoded     = verifyAccessToken(token);
      socket.data.user  = decoded;
      next();
    } catch {
      next(new Error('Invalid token'));
    }
  });

  io.on('connection', (socket) => {
    const { userId, role } = socket.data.user;
    logger.info(`Socket connected: ${socket.id}`, { userId });

    // Join user-specific room (for targeted messages)
    socket.join(`user:${userId}`);

    // Join role-based room
    socket.join(`role:${role}`);

    // Handle events
    socket.on('join:room', (roomId: string) => {
      socket.join(`room:${roomId}`);
      socket.to(`room:${roomId}`).emit('user:joined', { userId, socketId: socket.id });
    });

    socket.on('chat:message', async (data: { roomId: string; message: string }) => {
      const { roomId, message } = data;

      // Save to DB
      const msg = await Message.create({ userId, roomId, content: message });

      // Broadcast to everyone in room (including sender)
      io.to(`room:${roomId}`).emit('chat:message', {
        id:        msg.id,
        userId,
        message,
        timestamp: msg.createdAt,
      });
    });

    socket.on('disconnect', () => {
      logger.info(`Socket disconnected: ${socket.id}`, { userId });
    });
  });

  return io;
}

// Send to specific user from anywhere in your app
export const sendToUser = (io: Server, userId: string, event: string, data: any) => {
  io.to(`user:${userId}`).emit(event, data);
};

// Send to all users with a role
export const sendToRole = (io: Server, role: string, event: string, data: any) => {
  io.to(`role:${role}`).emit(event, data);
};
```

### Server-Sent Events (SSE) — For One-Way Streams

```javascript
// Good for: live dashboards, notification feeds, progress updates
// No library needed — built into HTTP

router.get('/events', authenticate, (req: Request, res: Response) => {
  // SSE headers
  res.writeHead(200, {
    'Content-Type':  'text/event-stream',
    'Cache-Control': 'no-cache',
    'Connection':    'keep-alive',
    'X-Accel-Buffering': 'no',   // disable nginx buffering
  });

  // Send a comment every 15s to keep the connection alive
  const heartbeat = setInterval(() => {
    res.write(': heartbeat\n\n');
  }, 15_000);

  // Helper to send events
  const sendEvent = (event: string, data: unknown) => {
    res.write(`event: ${event}\n`);
    res.write(`data: ${JSON.stringify(data)}\n\n`);
  };

  sendEvent('connected', { userId: req.user!.userId });

  // Subscribe to relevant events for this user
  const onOrderUpdate = (data: any) => sendEvent('order:update', data);
  eventBus.on('order.shipped', onOrderUpdate);

  // Cleanup when client disconnects
  req.on('close', () => {
    clearInterval(heartbeat);
    eventBus.off('order.shipped', onOrderUpdate);
  });
});
```

---

## 27. Testing & Code Quality

### The Testing Pyramid

```
           /\
          /  \
         / E2E \         Few — slow, expensive, test full flows
        /────────\
       / Integration \    Some — test services + DB together
      /──────────────\
     /   Unit Tests   \   Many — fast, isolated, test one function
    /──────────────────\
```

### Unit Tests with Jest

```javascript
// src/services/__tests__/user.service.test.ts
import { UserService } from '../user.service';
import { UserRepository } from '../../repositories/user.repository';
import { hashPassword } from '../../utils/password';
import { ConflictError } from '../../errors/AppError';

// Mock the dependencies
jest.mock('../../repositories/user.repository');
jest.mock('../../utils/password');
jest.mock('../../services/email.service');

describe('UserService', () => {
  let service: UserService;
  let mockRepo: jest.Mocked<UserRepository>;

  beforeEach(() => {
    mockRepo = new UserRepository() as jest.Mocked<UserRepository>;
    service  = new UserService(mockRepo);
    jest.clearAllMocks();
  });

  describe('create()', () => {
    const input = {
      name:     'Alice Johnson',
      email:    'alice@example.com',
      password: 'Password123!',
    };

    it('creates a user when email is unique', async () => {
      mockRepo.findByEmail.mockResolvedValue(null);   // email not found
      mockRepo.create.mockResolvedValue({ id: '1', ...input, password: 'hashed' } as any);
      (hashPassword as jest.Mock).mockResolvedValue('hashed');

      const result = await service.create(input);

      expect(mockRepo.findByEmail).toHaveBeenCalledWith(input.email);
      expect(hashPassword).toHaveBeenCalledWith(input.password);
      expect(mockRepo.create).toHaveBeenCalledWith(
        expect.objectContaining({ email: input.email, password: 'hashed' })
      );
      expect(result.password).toBeUndefined();   // password stripped in DTO
    });

    it('throws ConflictError when email already exists', async () => {
      mockRepo.findByEmail.mockResolvedValue({ id: '2', email: input.email } as any);

      await expect(service.create(input)).rejects.toThrow(ConflictError);
      expect(mockRepo.create).not.toHaveBeenCalled();
    });
  });
});
```

### Integration Tests (Supertest)

```javascript
// src/__tests__/auth.integration.test.ts
import request from 'supertest';
import mongoose from 'mongoose';
import app from '../app';
import { User } from '../models/user.model';

beforeAll(async () => {
  await mongoose.connect(process.env.MONGODB_TEST_URI!);
});

afterAll(async () => {
  await mongoose.connection.db.dropDatabase();
  await mongoose.disconnect();
});

afterEach(async () => {
  await User.deleteMany({});   // clean up between tests
});

describe('POST /api/v1/auth/register', () => {
  const validPayload = {
    name:     'Test User',
    email:    'test@example.com',
    password: 'Password123!',
  };

  it('returns 201 and a token on success', async () => {
    const res = await request(app)
      .post('/api/v1/auth/register')
      .send(validPayload);

    expect(res.status).toBe(201);
    expect(res.body.success).toBe(true);
    expect(res.body.data).toHaveProperty('accessToken');
    expect(res.body.data.user).not.toHaveProperty('password');
  });

  it('returns 422 on invalid email', async () => {
    const res = await request(app)
      .post('/api/v1/auth/register')
      .send({ ...validPayload, email: 'not-an-email' });

    expect(res.status).toBe(422);
    expect(res.body.errors[0].field).toBe('email');
  });

  it('returns 409 when email is already taken', async () => {
    await request(app).post('/api/v1/auth/register').send(validPayload);
    const res = await request(app).post('/api/v1/auth/register').send(validPayload);

    expect(res.status).toBe(409);
  });
});
```

```javascript
// package.json scripts
{
  "scripts": {
    "test":           "jest --runInBand",
    "test:unit":      "jest src/services src/utils --coverage",
    "test:integration": "jest src/__tests__ --runInBand",
    "test:watch":     "jest --watch",
    "test:coverage":  "jest --coverage --coverageThreshold='{\"global\":{\"branches\":80,\"functions\":80,\"lines\":80}}'"
  }
}
```

---

## 28. 12-Factor App

The 12-Factor methodology defines how to build apps that are **portable**, **scalable**, and **maintainable**. Know all 12 for interviews.

```
Factor 1:  Codebase       — One codebase in VCS, many deploys (git)
Factor 2:  Dependencies   — Explicitly declare (package.json, not global installs)
Factor 3:  Config         — Store config in environment variables (not code)
Factor 4:  Backing Services— DB, Redis, email = attached resources (swap via env var)
Factor 5:  Build/Run      — Strictly separate build (npm build) and run (node dist/)
Factor 6:  Processes      — Stateless processes; store state in Redis/DB, not memory
Factor 7:  Port Binding   — App exposes itself via a port (app.listen(PORT))
Factor 8:  Concurrency    — Scale out via process model (PM2, Kubernetes)
Factor 9:  Disposability  — Fast startup, graceful shutdown (SIGTERM handling)
Factor 10: Dev/Prod Parity— Keep dev, staging, prod as similar as possible
Factor 11: Logs           — Treat logs as event streams (stdout, not files)
Factor 12: Admin Processes— Run admin tasks as one-off processes (migrations)
```

---

## 29. OpenAPI Standards

### What it is

OpenAPI (formerly Swagger) is a specification for describing REST APIs in a machine-readable format (YAML/JSON). It generates interactive documentation and client SDKs automatically.

```yaml
# openapi.yaml
openapi: 3.0.3
info:
  title: My Backend API
  version: 1.0.0
  description: Production-grade API

servers:
  - url: https://api.myapp.com/v1
  - url: http://localhost:3000/api/v1

security:
  - BearerAuth: []

components:
  securitySchemes:
    BearerAuth:
      type: http
      scheme: bearer
      bearerFormat: JWT

  schemas:
    User:
      type: object
      properties:
        id:        { type: string, format: uuid }
        name:      { type: string, minLength: 2, maxLength: 50 }
        email:     { type: string, format: email }
        role:      { type: string, enum: [user, admin, moderator] }
        createdAt: { type: string, format: date-time }

    Error:
      type: object
      required: [success, error]
      properties:
        success: { type: boolean, example: false }
        error:   { type: string }
        code:    { type: string }

paths:
  /users:
    get:
      summary: List all users
      tags: [Users]
      parameters:
        - name: page
          in: query
          schema: { type: integer, default: 1 }
        - name: limit
          in: query
          schema: { type: integer, default: 10, maximum: 100 }
        - name: search
          in: query
          schema: { type: string }
      responses:
        '200':
          description: List of users
          content:
            application/json:
              schema:
                type: object
                properties:
                  success: { type: boolean }
                  data:
                    type: array
                    items: { $ref: '#/components/schemas/User' }
        '401': { description: Not authenticated }

    post:
      summary: Create a user
      tags: [Users]
      security: []   # public endpoint
      requestBody:
        required: true
        content:
          application/json:
            schema:
              type: object
              required: [name, email, password]
              properties:
                name:     { type: string }
                email:    { type: string, format: email }
                password: { type: string, minLength: 8 }
      responses:
        '201': { description: User created }
        '409': { description: Email already exists }
        '422': { description: Validation error }
```

```javascript
// Auto-serve Swagger UI from your Express app
import swaggerUi from 'swagger-ui-express';
import YAML from 'yamljs';

const swaggerDocument = YAML.load('./openapi.yaml');
app.use('/api/docs', swaggerUi.serve, swaggerUi.setup(swaggerDocument));

// Now visit http://localhost:3000/api/docs for interactive documentation
```

---

## 30. Webhooks

### What it is

Webhooks are HTTP callbacks — instead of your app polling an external service (Stripe, GitHub, Shopify) for updates, the external service sends an HTTP POST to your server when something happens.

```
Polling (bad):    Your server → "Any updates?" → External service (every 5s, wasted)
Webhooks (good):  External service → POST to your server → when something happens
```

```javascript
// src/routes/webhooks/stripe.webhook.ts
import Stripe from 'stripe';
import express from 'express';
import { OrderService } from '../../services/order.service';
import logger from '../../utils/logger';

const stripe = new Stripe(process.env.STRIPE_SECRET_KEY!, { apiVersion: '2023-10-16' });

// IMPORTANT: Stripe needs the RAW body to verify the signature
// Mount this BEFORE express.json() or use express.raw() on this route
export const stripeWebhook = express.Router();

stripeWebhook.post(
  '/webhooks/stripe',
  express.raw({ type: 'application/json' }),   // raw buffer, NOT parsed JSON
  async (req, res) => {
    const signature = req.headers['stripe-signature'] as string;

    let event: Stripe.Event;

    try {
      // Verify the webhook signature — prevents fake webhook attacks
      event = stripe.webhooks.constructEvent(
        req.body,                                   // raw buffer
        signature,
        process.env.STRIPE_WEBHOOK_SECRET!
      );
    } catch (err: any) {
      logger.warn('Stripe webhook signature verification failed', { error: err.message });
      return res.status(400).json({ error: `Webhook signature invalid: ${err.message}` });
    }

    // Idempotency: Stripe can deliver the same event multiple times
    // Check if we've already processed this event
    const alreadyProcessed = await ProcessedEvent.findOne({ eventId: event.id });
    if (alreadyProcessed) {
      logger.info('Duplicate webhook event — skipping', { eventId: event.id });
      return res.status(200).json({ received: true });
    }

    logger.info('Stripe webhook received', { type: event.type, id: event.id });

    // Handle events
    try {
      switch (event.type) {
        case 'payment_intent.succeeded': {
          const paymentIntent = event.data.object as Stripe.PaymentIntent;
          const orderId       = paymentIntent.metadata.orderId;
          await OrderService.markAsPaid(orderId, paymentIntent.id);
          break;
        }

        case 'payment_intent.payment_failed': {
          const paymentIntent = event.data.object as Stripe.PaymentIntent;
          const orderId       = paymentIntent.metadata.orderId;
          await OrderService.markAsPaymentFailed(orderId);
          break;
        }

        case 'customer.subscription.deleted': {
          const subscription = event.data.object as Stripe.Subscription;
          await UserService.downgradeToFree(subscription.metadata.userId);
          break;
        }

        default:
          logger.info(`Unhandled Stripe event: ${event.type}`);
      }

      // Record that we've processed this event
      await ProcessedEvent.create({ eventId: event.id, type: event.type });

      res.status(200).json({ received: true });
    } catch (error) {
      logger.error('Webhook handler error', { eventId: event.id, error });
      // Return 500 — Stripe will retry the webhook
      res.status(500).json({ error: 'Webhook handler failed' });
    }
  }
);
```

```javascript
// Sending webhooks to your users (outbound)
// src/services/webhook.service.ts

import axios from 'axios';
import crypto from 'crypto';

export class WebhookService {
  // Send an event to a customer's registered webhook URL
  async dispatch(
    url:       string,
    event:     string,
    payload:   object,
    secretKey: string
  ): Promise<void> {
    const body      = JSON.stringify({ event, data: payload, timestamp: Date.now() });
    const signature = crypto
      .createHmac('sha256', secretKey)
      .update(body)
      .digest('hex');

    try {
      await axios.post(url, body, {
        headers: {
          'Content-Type':      'application/json',
          'X-Webhook-Event':   event,
          'X-Webhook-Signature': `sha256=${signature}`,
        },
        timeout: 10_000,   // 10 second timeout
      });
    } catch (error) {
      // Queue for retry with exponential backoff
      await webhookRetryQueue.add('retry', { url, event, payload, secretKey }, {
        attempts: 5,
        backoff:  { type: 'exponential', delay: 5000 },
      });
    }
  }
}
```

---

## 31. DevOps for Backend Engineers

### Dockerfile — Production-Ready

```dockerfile
# Multi-stage build — smaller final image
FROM node:20-alpine AS builder

WORKDIR /app

# Copy package files first (better layer caching)
COPY package*.json ./
RUN npm ci --only=production

# Copy source
COPY tsconfig.json ./
COPY src/ ./src/
RUN npm run build

# ─── Production stage ──────────────────────────────────────────
FROM node:20-alpine AS production

# Security: don't run as root
RUN addgroup -g 1001 -S nodejs && adduser -S nodejs -u 1001

WORKDIR /app

# Copy only what's needed to run
COPY --from=builder --chown=nodejs:nodejs /app/node_modules ./node_modules
COPY --from=builder --chown=nodejs:nodejs /app/dist         ./dist
COPY --chown=nodejs:nodejs package.json   ./

USER nodejs

EXPOSE 3000

# Health check for Docker / Kubernetes
HEALTHCHECK --interval=30s --timeout=5s --start-period=10s --retries=3 \
  CMD wget -qO- http://localhost:3000/health/live || exit 1

CMD ["node", "dist/server.js"]
```

### Docker Compose (Local Development)

```yaml
# docker-compose.yml
version: '3.9'

services:
  api:
    build:
      context: .
      target:  builder   # use builder stage for dev (has devDeps)
    command:   npm run dev
    ports:
      - '3000:3000'
    environment:
      - NODE_ENV=development
      - MONGODB_URI=mongodb://mongo:27017/myapp
      - REDIS_HOST=redis
    volumes:
      - ./src:/app/src    # hot reload
    depends_on:
      mongo: { condition: service_healthy }
      redis: { condition: service_healthy }

  mongo:
    image: mongo:7
    ports:
      - '27017:27017'
    volumes:
      - mongo_data:/data/db
    healthcheck:
      test:     ['CMD', 'mongosh', '--eval', 'db.adminCommand("ping")']
      interval: 10s
      timeout:  5s
      retries:  5

  redis:
    image: redis:7-alpine
    ports:
      - '6379:6379'
    healthcheck:
      test:     ['CMD', 'redis-cli', 'ping']
      interval: 10s
      timeout:  5s
      retries:  5

volumes:
  mongo_data:
```

### GitHub Actions CI/CD Pipeline

```yaml
# .github/workflows/ci.yml
name: CI/CD Pipeline

on:
  push:
    branches: [main, develop]
  pull_request:
    branches: [main]

env:
  REGISTRY:    ghcr.io
  IMAGE_NAME:  ${{ github.repository }}

jobs:
  test:
    runs-on: ubuntu-latest

    services:
      mongodb:
        image: mongo:7
        ports:  ['27017:27017']
      redis:
        image: redis:7-alpine
        ports:  ['6379:6379']

    steps:
      - uses: actions/checkout@v4

      - name: Setup Node.js
        uses: actions/setup-node@v4
        with:
          node-version: '20'
          cache:        'npm'

      - name: Install dependencies
        run:  npm ci

      - name: Type check
        run:  npx tsc --noEmit

      - name: Lint
        run:  npm run lint

      - name: Unit tests
        run:  npm run test:unit

      - name: Integration tests
        run:  npm run test:integration
        env:
          MONGODB_TEST_URI: mongodb://localhost:27017/testdb
          JWT_SECRET:       test-secret-at-least-32-characters-long
          JWT_REFRESH_SECRET: test-refresh-secret-32-chars-minimum

      - name: Upload coverage
        uses: codecov/codecov-action@v3

  build-and-push:
    needs:    test
    runs-on:  ubuntu-latest
    if:       github.ref == 'refs/heads/main'

    permissions:
      contents: read
      packages: write

    steps:
      - uses: actions/checkout@v4

      - name: Log in to Container Registry
        uses: docker/login-action@v3
        with:
          registry: ${{ env.REGISTRY }}
          username: ${{ github.actor }}
          password: ${{ secrets.GITHUB_TOKEN }}

      - name: Extract Docker metadata
        id: meta
        uses: docker/metadata-action@v5
        with:
          images: ${{ env.REGISTRY }}/${{ env.IMAGE_NAME }}
          tags:   |
            type=sha,prefix=main-
            type=raw,value=latest

      - name: Build and push
        uses: docker/build-push-action@v5
        with:
          context:   .
          target:    production
          push:      true
          tags:      ${{ steps.meta.outputs.tags }}
          cache-from: type=gha
          cache-to:   type=gha,mode=max

  deploy:
    needs:   build-and-push
    runs-on: ubuntu-latest
    if:      github.ref == 'refs/heads/main'

    steps:
      - name: Deploy to production
        run: |
          # Example: deploy to a VPS via SSH
          echo "Deploying image ${{ env.REGISTRY }}/${{ env.IMAGE_NAME }}:latest"
          # Add your actual deploy command here:
          # ssh user@host "docker pull ... && docker-compose up -d"
          # or: kubectl set image deployment/api api=...
```

### Kubernetes Deployment

```yaml
# k8s/deployment.yaml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: backend-api
spec:
  replicas: 3
  selector:
    matchLabels:
      app: backend-api
  template:
    metadata:
      labels:
        app: backend-api
    spec:
      containers:
        - name: api
          image: ghcr.io/myorg/backend:latest
          ports:
            - containerPort: 3000
          env:
            - name: NODE_ENV
              value: production
            - name: MONGODB_URI
              valueFrom:
                secretKeyRef:
                  name: app-secrets
                  key:  MONGODB_URI
            - name: JWT_SECRET
              valueFrom:
                secretKeyRef:
                  name: app-secrets
                  key:  JWT_SECRET
          resources:
            requests:
              memory: 256Mi
              cpu:    250m
            limits:
              memory: 512Mi
              cpu:    500m
          livenessProbe:
            httpGet:
              path: /health/live
              port: 3000
            initialDelaySeconds: 10
            periodSeconds:       10
          readinessProbe:
            httpGet:
              path: /health/ready
              port: 3000
            initialDelaySeconds: 5
            periodSeconds:       5
          lifecycle:
            preStop:
              exec:
                # Give in-flight requests 15s to complete before SIGTERM
                command: ['/bin/sleep', '15']
---
apiVersion: v1
kind: Service
metadata:
  name: backend-api-service
spec:
  selector:
    app: backend-api
  ports:
    - port: 80
      targetPort: 3000
---
apiVersion: autoscaling/v2
kind: HorizontalPodAutoscaler
metadata:
  name: backend-api-hpa
spec:
  scaleTargetRef:
    apiVersion: apps/v1
    kind:       Deployment
    name:       backend-api
  minReplicas: 2
  maxReplicas: 10
  metrics:
    - type: Resource
      resource:
        name: cpu
        target:
          type:               Utilization
          averageUtilization: 70
```

---

## Interview Cheat Sheet

Use these definitions when asked in interviews:

```
Idempotency      — Same request can be made multiple times with the same result
Statelessness    — Server holds no client state between requests (auth via tokens)
ACID             — Atomicity, Consistency, Isolation, Durability (DB transactions)
CAP Theorem      — In distributed systems: you can only pick 2 of 3:
                   Consistency, Availability, Partition Tolerance
N+1 Problem      — Loading a list of N items then making N individual queries
Rate Limiting    — Restricting how many requests a client can make in a time window
Circuit Breaker  — Stop calling a failing service to allow it to recover
Cache Stampede   — Multiple requests miss cache simultaneously, all hit DB
Idempotency Key  — Unique ID sent by client to prevent duplicate processing
Soft Delete      — Mark records as deleted instead of removing them from DB
Dead Letter Queue— Queue for messages that failed processing repeatedly
Saga Pattern     — Distributed transaction via sequence of local transactions + events
CQRS             — Separate models for reading (Query) and writing (Command)
Event Sourcing   — Store events not current state; derive state by replaying events
```

---

## Quick Reference: HTTP Status Codes

```
200 OK               — Request succeeded
201 Created          — Resource created (POST, PUT that creates)
204 No Content       — Success with no body (DELETE)
301 Moved Permanently— Redirect (update bookmarks)
304 Not Modified     — Cached response is still valid (ETag)
400 Bad Request      — Malformed request syntax
401 Unauthorized     — Not authenticated (no token / invalid token)
403 Forbidden        — Authenticated but not authorised
404 Not Found        — Resource doesn't exist
409 Conflict         — State conflict (duplicate email)
410 Gone             — Resource permanently deleted
422 Unprocessable    — Validation failed (correct syntax, bad data)
429 Too Many Requests— Rate limited
500 Internal Error   — Server bug (unexpected error)
502 Bad Gateway      — Upstream service returned invalid response
503 Unavailable      — Service down / overloaded
504 Gateway Timeout  — Upstream service timed out
```

---

## Learning Path Going Forward

```
Week 1-2:   Chapters 1-10  (HTTP, routing, auth, validation, middleware)
Week 3-4:   Chapters 11-18 (REST, DB, BLL, caching, queues, error handling)
Week 5-6:   Chapters 19-24 (config, logging, security, scaling, concurrency)
Week 7-8:   Chapters 25-31 (files, real-time, testing, devops, webhooks)

After this guide:
→ Study system design (Designing Data-Intensive Applications by Kleppmann)
→ Build one production project implementing all concepts
→ Learn about microservices, event-driven architecture, and distributed systems
```

---

*All code examples use Node.js 20 LTS with TypeScript 5. Install dependencies with `npm install` and run with `npm run dev`.*
