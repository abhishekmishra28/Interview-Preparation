# 🐳 Docker — Complete Guide for SDE Interviews
### Node.js / Express · Windows · GitHub CI/CD · System Design

> Beginner-friendly theory → practical usage → interview-ready answers. You won't master Docker, but you'll understand it deeply enough to use it confidently and defend every decision in an interview.

---

## Table of Contents

1. [The Problem Docker Solves](#1-the-problem-docker-solves)
2. [Core Concepts — Mental Models First](#2-core-concepts--mental-models-first)
3. [How Docker Actually Works Internally](#3-how-docker-actually-works-internally)
4. [Docker vs Virtual Machines](#4-docker-vs-virtual-machines)
5. [Installing Docker on Windows](#5-installing-docker-on-windows)
6. [Essential Docker Commands](#6-essential-docker-commands)
7. [Writing a Dockerfile for Node/Express](#7-writing-a-dockerfile-for-nodeexpress)
8. [Docker Compose — Multi-Container Apps](#8-docker-compose--multi-container-apps)
9. [Docker Networking Explained](#9-docker-networking-explained)
10. [Docker Volumes — Persistent Data](#10-docker-volumes--persistent-data)
11. [Docker in System Design](#11-docker-in-system-design)
12. [GitHub Actions CI/CD with Docker](#12-github-actions-cicd-with-docker)
13. [Interview Questions & Answers](#13-interview-questions--answers)
14. [Quick Reference Cheat Sheet](#14-quick-reference-cheat-sheet)

---

## 1. The Problem Docker Solves

Before Docker existed, deploying software was painful. Let's understand *why* through a story.

### "It Works On My Machine"

You build a Node.js app on your Windows laptop. It works perfectly. You push it to a Linux server. It crashes immediately. The error? The server has Node.js v14, you built with v20. Or a native npm package compiled for Windows doesn't run on Linux. Or an environment variable is set differently.

```
Developer's Laptop          Production Server
──────────────────          ─────────────────
Node v20                    Node v14   ← mismatch!
npm v10                     npm v6     ← mismatch!
Windows 11                  Ubuntu 20  ← different OS!
PORT=3000 in .env           PORT=8080  ← mismatch!
mongodb@localhost            mongodb@db-server ← different!
```

This "works on my machine" problem has existed since software began. Teams wasted days on environment setup instead of writing code.

### The Old Solution: Virtual Machines

"Just ship the whole OS" — package your app with a full operating system. Problem solved, but bloated: a simple Node app now ships with 20GB of Windows or Ubuntu. Slow to start (minutes), heavy on RAM, expensive.

### The Docker Solution: Containers

Docker packages your application with **just what it needs** to run — the runtime, libraries, config, code — but **shares the host OS kernel** instead of duplicating it.

```
Your App
  + Node v20
  + Your node_modules
  + Your source code
  + Your environment variables
  + Your start command
= One portable container that runs identically everywhere
```

Run it on your Windows laptop, your colleague's Mac, a Linux cloud server — it behaves exactly the same. That's the entire value proposition.

---

## 2. Core Concepts — Mental Models First

Docker has about 6 concepts you need to internalize. Everything else is just detail on top of these.

### Concept 1: Image — The Blueprint

An **image** is a read-only template — a snapshot of a filesystem with everything your app needs. Think of it like a **class** in OOP, or a **recipe**. The image itself never runs; it's just a definition.

```
Image = Recipe
  - Ingredients: Node v20, your code, your dependencies
  - Instructions: RUN npm install, CMD ["node", "server.js"]
  - Fixed, immutable, shareable
```

Images are stored in **registries** (Docker Hub is the public one, like GitHub but for images). You pull images from registries, and push your own images to them.

### Concept 2: Container — The Running Instance

A **container** is a running instance of an image — like an **object** created from a class. One image can spawn many containers simultaneously. Each container is isolated: its own filesystem, network, process space.

```
Image ────► Container 1 (running)
       ├──► Container 2 (running)
       └──► Container 3 (stopped)

Same blueprint, multiple independent instances.
This is exactly how you scale: run more containers.
```

### Concept 3: Dockerfile — The Recipe Card

A **Dockerfile** is a text file with instructions that tell Docker how to build your image. It's like a script that Docker executes step by step, creating a new filesystem layer at each step.

```dockerfile
FROM node:20-alpine        # Start from official Node image
WORKDIR /app               # Set working directory inside container
COPY package*.json ./      # Copy package files
RUN npm install            # Install dependencies (baked into image)
COPY . .                   # Copy your source code
EXPOSE 3000                # Document that port 3000 is used
CMD ["node", "server.js"]  # Command to run when container starts
```

### Concept 4: Registry — The Library

A **registry** is a server that stores and distributes images. Docker Hub (`hub.docker.com`) is the default public registry — it's where `FROM node:20-alpine` pulls from. GitHub Container Registry (GHCR) and AWS ECR are alternatives.

```
docker pull node:20-alpine   ← downloads from Docker Hub
docker push myapp:v1.0       ← uploads your image to a registry
```

### Concept 5: Docker Compose — Orchestrating Multiple Containers

Real apps aren't a single container. A Node/Express app needs:
- The Node app container
- A MongoDB or PostgreSQL container
- Maybe a Redis container

**Docker Compose** lets you define all these containers, their connections, and their configs in one `docker-compose.yml` file. One command (`docker compose up`) starts everything.

### Concept 6: Volume — Persistent Storage

Containers are **ephemeral** — when a container stops or is deleted, its internal filesystem is gone. But you don't want your database data deleted when you restart the database container. **Volumes** are the solution: a storage location that lives outside the container and persists independently.

```
Container (ephemeral)     Volume (persistent)
     /data  ←────────────── /var/lib/docker/volumes/mydata
     
Container deleted? Volume survives. Container restarted? Volume reattaches.
```

---

## 3. How Docker Actually Works Internally

Understanding this earns you major interview points. Most candidates can use Docker; few can explain what's actually happening.

### The Host OS Kernel

Docker doesn't virtualize hardware like a VM does. Instead, all containers **share the host OS kernel** directly. The isolation between containers comes from Linux kernel features:

```
Physical Hardware
       ↓
Host OS Kernel (Windows runs a lightweight Linux kernel via WSL2)
       ↓  ↓  ↓
   [Container A] [Container B] [Container C]
   
All containers talk to the SAME kernel.
Each container THINKS it's isolated — the kernel enforces this illusion.
```

### Namespaces — The Isolation Mechanism

Linux **namespaces** create the illusion of isolation. Each container gets its own view of:

| Namespace | What It Isolates |
|-----------|-----------------|
| **PID** | Process IDs — container's process 1 is actually process 5234 on host |
| **NET** | Network interfaces, IP addresses, routing tables |
| **MNT** | Filesystem mount points — container sees its own filesystem |
| **UTS** | Hostname — container can have a different hostname |
| **IPC** | Inter-process communication — shared memory isolation |
| **USER** | User IDs — root inside container ≠ root on host |

### cgroups — The Resource Limiter

**Control Groups (cgroups)** enforce resource limits on containers:
- This container can use at most 512MB RAM
- This container can use at most 0.5 CPU cores
- This container can read/write disk at max 100MB/s

Without cgroups, one misbehaving container could starve all others of CPU or memory.

### Layers — How Images Are Built Efficiently

Every line in a Dockerfile creates a new **read-only layer** on top of the previous one. Docker caches these layers. If you rebuild an image and a layer hasn't changed, Docker reuses the cached version — this makes rebuilds extremely fast.

```
Layer 5: [COPY . .]              ← your source code (changes often)
Layer 4: [RUN npm install]       ← dependencies (changes rarely)
Layer 3: [COPY package*.json ./] ← package files (changes rarely)
Layer 2: [WORKDIR /app]          ← working directory
Layer 1: [FROM node:20-alpine]   ← base image (almost never changes)

On code change: only Layer 5 is rebuilt. Layers 1-4 are cached. Fast!
On package.json change: Layers 3, 4, 5 rebuild. Layer 1, 2 cached.
```

This layering is why **COPY package*.json** comes before **COPY . .** in Dockerfiles — it's a deliberate cache optimization.

### Union Filesystem

These layers are stacked using a **union filesystem** (like OverlayFS on Linux). The container sees a single unified filesystem even though it's really multiple stacked read-only layers plus one read-write layer on top.

```
Read-Write Layer      ← container writes go here (ephemeral)
─────────────────
Layer 5 (read-only)   ← your code
Layer 4 (read-only)   ← npm install
Layer 3 (read-only)   ← package.json copy
Layer 2 (read-only)   ← workdir
Layer 1 (read-only)   ← node:20-alpine base
```

---

## 4. Docker vs Virtual Machines

This comparison comes up in almost every Docker interview question.

```
Virtual Machine                    Docker Container
────────────────                   ────────────────
App                                App
Libraries/Dependencies             Libraries/Dependencies
Guest OS (full Linux/Windows)      ← NO GUEST OS
Hypervisor (VMware/Hyper-V)        Docker Engine
Host OS                            Host OS
Hardware                           Hardware
```

| Aspect | Virtual Machine | Docker Container |
|--------|-----------------|------------------|
| **Boot time** | Minutes | Milliseconds to seconds |
| **Size** | GBs (full OS) | MBs (just the app + deps) |
| **RAM per instance** | GBs | MBs |
| **Isolation** | Complete — separate kernel | Process-level — shared kernel |
| **Security** | Stronger (separate kernel) | Weaker (shared kernel, but improving) |
| **Performance** | Slower (hardware emulation) | Near-native (direct kernel access) |
| **Portability** | Less (OS-specific) | High (run anywhere Docker runs) |
| **Use case** | Run different OS, strong isolation | Microservices, CI/CD, scale fast |

**The key interview answer**: "Docker containers are lighter and faster than VMs because they share the host kernel instead of emulating hardware. You can run 10x more containers than VMs on the same hardware. The tradeoff is weaker isolation — a kernel vulnerability affects all containers."

---

## 5. Installing Docker on Windows

### What Happens on Windows

Docker natively runs on Linux. On Windows, Docker Desktop installs and manages a lightweight Linux VM via **WSL2 (Windows Subsystem for Linux 2)**. Your containers run inside this Linux environment. From your perspective, it's seamless — Docker commands in PowerShell or CMD work exactly as if you were on Linux.

```
Windows 11 / Windows 10
       ↓
WSL2 (lightweight Linux kernel from Microsoft)
       ↓
Docker Engine (running inside WSL2)
       ↓
Your Containers
```

### Steps

**1. Enable WSL2** (run PowerShell as Administrator):
```powershell
wsl --install
# Restart your computer after this
```

**2. Download Docker Desktop** from `https://www.docker.com/products/docker-desktop/`

**3. Install** — during setup, ensure "Use WSL2 instead of Hyper-V" is selected.

**4. Verify installation** (in PowerShell or CMD):
```powershell
docker --version
# Docker version 26.x.x, build ...

docker run hello-world
# Pulls a test image and runs it — if you see "Hello from Docker!" it's working
```

### Docker Desktop Settings Worth Knowing

- **Resources → Memory**: Docker Desktop gets 2GB RAM by default. Increase this for heavier apps.
- **Resources → CPUs**: Controls how many CPU cores Docker can use.
- **WSL Integration**: Ensure your WSL distro (Ubuntu) has Docker integration enabled.

---

## 6. Essential Docker Commands

Commands are organized by what you're doing — not alphabetically.

### Working with Images

```powershell
# Pull an image from Docker Hub
docker pull node:20-alpine

# List all images on your machine
docker images
# or
docker image ls

# Remove an image
docker rmi node:20-alpine

# Remove ALL unused images (cleanup)
docker image prune -a

# Build an image from Dockerfile in current directory
docker build -t myapp:v1.0 .
#             ↑ tag name    ↑ build context (current dir)

# Build with a specific Dockerfile location
docker build -f Dockerfile.prod -t myapp:prod .

# Inspect image layers and metadata
docker inspect myapp:v1.0

# See image history (layers)
docker history myapp:v1.0
```

### Working with Containers

```powershell
# Run a container from an image
docker run node:20-alpine

# Run with port mapping: host:container
docker run -p 3000:3000 myapp:v1.0
#              ↑ your laptop port maps to ↑ container port

# Run in detached (background) mode
docker run -d -p 3000:3000 myapp:v1.0

# Run with a custom name (easier to reference)
docker run -d -p 3000:3000 --name my-node-app myapp:v1.0

# Run with environment variables
docker run -d -p 3000:3000 \
  -e NODE_ENV=production \
  -e PORT=3000 \
  -e MONGODB_URI=mongodb://localhost:27017/mydb \
  myapp:v1.0

# Run with a volume mounted
docker run -d -p 3000:3000 \
  -v C:\myproject:/app \
  myapp:v1.0
#  ↑ Windows path  ↑ container path

# Run interactively with a terminal (great for debugging)
docker run -it node:20-alpine sh

# List running containers
docker ps

# List ALL containers (including stopped)
docker ps -a

# Stop a running container (graceful — sends SIGTERM)
docker stop my-node-app

# Kill immediately (sends SIGKILL)
docker kill my-node-app

# Remove a stopped container
docker rm my-node-app

# Remove container when it exits automatically
docker run --rm myapp:v1.0

# Remove ALL stopped containers
docker container prune
```

### Inspecting and Debugging

```powershell
# See container logs
docker logs my-node-app

# Follow logs in real time (like tail -f)
docker logs -f my-node-app

# See last 50 lines of logs
docker logs --tail 50 my-node-app

# Run a command inside a RUNNING container
docker exec -it my-node-app sh
# Now you're inside the container — explore filesystem, run commands

# Run a specific command inside container
docker exec my-node-app ls /app

# See container resource usage (CPU, memory, network)
docker stats

# See container stats once (no streaming)
docker stats --no-stream

# See detailed info about a container
docker inspect my-node-app

# See port mappings
docker port my-node-app
```

### Working with Registries

```powershell
# Login to Docker Hub
docker login

# Login to GitHub Container Registry
docker login ghcr.io -u YOUR_GITHUB_USERNAME

# Tag an image for pushing to a registry
docker tag myapp:v1.0 yourusername/myapp:v1.0
docker tag myapp:v1.0 ghcr.io/yourusername/myapp:v1.0

# Push to Docker Hub
docker push yourusername/myapp:v1.0

# Push to GitHub Container Registry
docker push ghcr.io/yourusername/myapp:v1.0
```

### System Cleanup

```powershell
# Remove everything unused (images, containers, networks, cache)
docker system prune

# Remove everything including volumes (DANGEROUS — deletes data!)
docker system prune --volumes

# See disk usage by Docker
docker system df
```

---

## 7. Writing a Dockerfile for Node/Express

### Basic Dockerfile

```dockerfile
# ── Stage: Base image ──────────────────────────────────────────────────────
# 'alpine' is a minimal Linux distro (~5MB vs ~900MB for full ubuntu)
# Always pin a specific version — never use 'latest' in production
FROM node:20-alpine

# ── Set working directory inside the container ─────────────────────────────
# All subsequent commands run from /app
# /app is created if it doesn't exist
WORKDIR /app

# ── Copy dependency files FIRST (layer cache optimization) ─────────────────
# We copy package.json and package-lock.json before copying source code.
# Why? If source code changes but package.json doesn't, Docker reuses the
# cached 'npm install' layer — much faster rebuilds.
COPY package*.json ./

# ── Install dependencies ────────────────────────────────────────────────────
# --omit=dev skips devDependencies (nodemon, jest, etc.) in production
RUN npm ci --omit=dev
# npm ci is preferred over npm install in CI/CD:
# - Uses package-lock.json exactly (reproducible)
# - Deletes node_modules first (clean install)

# ── Copy source code ────────────────────────────────────────────────────────
# After npm install so source changes don't invalidate the install cache
COPY . .

# ── Document the port your app listens on ──────────────────────────────────
# EXPOSE doesn't actually publish the port — it's documentation
# The actual publishing happens with -p in docker run
EXPOSE 3000

# ── The command to run when the container starts ───────────────────────────
# CMD uses exec form (JSON array) — preferred over shell form
# Shell form: CMD "node server.js"  ← runs as /bin/sh -c "node server.js"
# Exec form:  CMD ["node", "server.js"] ← runs node directly, proper signal handling
CMD ["node", "server.js"]
```

### Production Dockerfile (Multi-Stage Build)

Multi-stage builds are important to know — they produce much smaller final images by separating build-time tools from runtime.

```dockerfile
# ═══════════════════════════════════════════════════════════════
# STAGE 1: Builder — install everything including devDependencies
# ═══════════════════════════════════════════════════════════════
FROM node:20-alpine AS builder

WORKDIR /app
COPY package*.json ./
RUN npm ci                   # install ALL deps including devDeps for build
COPY . .
RUN npm run build            # compile TypeScript, bundle, etc.

# ═══════════════════════════════════════════════════════════════
# STAGE 2: Production — only the built output and prod dependencies
# ═══════════════════════════════════════════════════════════════
FROM node:20-alpine AS production

# Create a non-root user for security (never run as root in prod)
RUN addgroup -g 1001 -S nodejs && \
    adduser  -S nodeuser -u 1001

WORKDIR /app

# Copy only what we need from the builder stage
COPY --from=builder /app/package*.json ./
COPY --from=builder /app/dist ./dist        # compiled output
# or for non-TypeScript:
# COPY --from=builder /app/src ./src

RUN npm ci --omit=dev        # only production dependencies

# Switch to non-root user
USER nodeuser

EXPOSE 3000
CMD ["node", "dist/server.js"]

# Final image has: node runtime + your compiled code + prod deps only
# Builder stage is DISCARDED — its node_modules (including devDeps) not included
```

### .dockerignore — What to Exclude

This file tells Docker what NOT to copy when you do `COPY . .`. Without it, you'd accidentally copy `node_modules` (huge), `.git`, `.env` files, etc.

```
# .dockerignore

node_modules        # always exclude — npm install runs inside container
.git                # git history not needed
.gitignore
.env                # NEVER bake secrets into images
.env.local
.env.development
npm-debug.log
*.md
coverage            # test coverage reports
.nyc_output
dist                # if you have a local build output
Dockerfile          # no need to copy Dockerfile into itself
docker-compose*.yml
README.md
.vscode
.idea
```

### Environment Variables — The Right Way

```dockerfile
# In Dockerfile — set defaults (non-sensitive)
ENV NODE_ENV=production
ENV PORT=3000

# Override at runtime — for secrets NEVER hardcode in image
# docker run -e MONGODB_URI=mongodb://... myapp
```

```powershell
# Pass env file at runtime (contains secrets, not committed to git)
docker run -d --env-file .env.production myapp:v1.0

# Single variable
docker run -d -e JWT_SECRET=mysecret myapp:v1.0
```

**Interview point**: "We never bake secrets into Docker images because images are often pushed to registries. Anyone who can pull the image could run `docker inspect` and read the hardcoded secrets. Secrets are injected at runtime via environment variables, Docker secrets, or secret managers like AWS Secrets Manager."

---

## 8. Docker Compose — Multi-Container Apps

### Why Docker Compose

Running a Node/Express app with MongoDB in production means:

```powershell
# Without Compose — you'd have to run all of this manually:
docker network create myapp-network

docker run -d \
  --name mongodb \
  --network myapp-network \
  -v mongo-data:/data/db \
  -e MONGO_INITDB_ROOT_USERNAME=admin \
  -e MONGO_INITDB_ROOT_PASSWORD=password \
  mongo:7

docker run -d \
  --name myapp \
  --network myapp-network \
  -p 3000:3000 \
  -e MONGODB_URI=mongodb://admin:password@mongodb:27017/mydb \
  myapp:v1.0
```

That's painful and easy to get wrong. Docker Compose collapses this into one file.

### docker-compose.yml for Node + MongoDB + Redis

```yaml
# docker-compose.yml
version: "3.9"

services:

  # ── Node/Express Application ──────────────────────────────────────────────
  app:
    build:
      context: .            # build from Dockerfile in current directory
      dockerfile: Dockerfile
    container_name: express-app
    ports:
      - "3000:3000"         # host:container port mapping
    environment:
      - NODE_ENV=development
      - PORT=3000
      - MONGODB_URI=mongodb://admin:password@mongodb:27017/mydb?authSource=admin
      - REDIS_URL=redis://redis:6379
    env_file:
      - .env.local          # additional env vars from a file
    depends_on:
      mongodb:
        condition: service_healthy    # wait until mongodb passes healthcheck
      redis:
        condition: service_started
    volumes:
      - .:/app                        # mount source code (for hot reload in dev)
      - /app/node_modules             # keep container's node_modules (not host's)
    networks:
      - app-network
    restart: unless-stopped           # auto-restart on crash

  # ── MongoDB ───────────────────────────────────────────────────────────────
  mongodb:
    image: mongo:7                    # use official image — no Dockerfile needed
    container_name: mongodb
    ports:
      - "27017:27017"                 # expose for local tools like MongoDB Compass
    environment:
      MONGO_INITDB_ROOT_USERNAME: admin
      MONGO_INITDB_ROOT_PASSWORD: password
      MONGO_INITDB_DATABASE: mydb
    volumes:
      - mongo-data:/data/db           # named volume — data persists between restarts
    networks:
      - app-network
    healthcheck:
      test: ["CMD", "mongosh", "--eval", "db.adminCommand('ping')"]
      interval: 10s         # check every 10 seconds
      timeout: 5s           # fail if no response in 5 seconds
      retries: 5            # try 5 times before marking unhealthy
      start_period: 30s     # give container 30s to start before health checks begin

  # ── Redis (for caching / sessions) ───────────────────────────────────────
  redis:
    image: redis:7-alpine
    container_name: redis
    ports:
      - "6379:6379"
    volumes:
      - redis-data:/data
    networks:
      - app-network

# ── Named Volumes ─────────────────────────────────────────────────────────
volumes:
  mongo-data:       # Docker manages this on the host
  redis-data:

# ── Networks ──────────────────────────────────────────────────────────────
networks:
  app-network:
    driver: bridge  # default network driver for single-host setups
```

### Docker Compose Commands

```powershell
# Start everything (builds if needed, runs in background)
docker compose up -d

# Start and FORCE rebuild images (use after Dockerfile changes)
docker compose up -d --build

# Stop all containers (keeps containers and volumes)
docker compose stop

# Stop AND remove containers, networks (keeps volumes)
docker compose down

# Stop AND remove containers, networks, AND volumes (deletes data!)
docker compose down -v

# See logs from all services
docker compose logs

# Follow logs from specific service
docker compose logs -f app

# See status of all services
docker compose ps

# Run a command inside a running service container
docker compose exec app sh
docker compose exec app npm run migrate

# Run a one-off command (starts a temporary container)
docker compose run --rm app npm test

# Scale a service (run 3 instances of app)
docker compose up -d --scale app=3
```

### Separate Compose Files for Dev vs Production

```yaml
# docker-compose.yml — base (shared between environments)
services:
  app:
    build: .
    networks:
      - app-network
  mongodb:
    image: mongo:7
    networks:
      - app-network

networks:
  app-network:
```

```yaml
# docker-compose.dev.yml — development overrides
services:
  app:
    volumes:
      - .:/app               # hot reload: mount source code
      - /app/node_modules
    environment:
      - NODE_ENV=development
    command: npm run dev     # use nodemon for hot reload
    ports:
      - "3000:3000"
      - "9229:9229"          # Node.js debugger port
  mongodb:
    ports:
      - "27017:27017"        # expose in dev for MongoDB Compass access
```

```yaml
# docker-compose.prod.yml — production overrides
services:
  app:
    image: ghcr.io/yourusername/myapp:latest    # use pre-built image, not build
    environment:
      - NODE_ENV=production
    ports:
      - "3000:3000"
    restart: always
  mongodb:
    # No port exposure in production — only accessible within Docker network
    restart: always
```

```powershell
# Run dev environment
docker compose -f docker-compose.yml -f docker-compose.dev.yml up

# Run production environment
docker compose -f docker-compose.yml -f docker-compose.prod.yml up -d
```

---

## 9. Docker Networking Explained

### Why Containers Need Networking

Containers are isolated — by default they can't talk to each other or the outside world. Docker networking is how you control what can talk to what.

### Network Types

| Driver | Description | When to Use |
|--------|-------------|-------------|
| **bridge** | Default. Creates a private network; containers communicate by name. | Single-host, most apps |
| **host** | Container shares host's network directly. No isolation. | Linux only, high performance |
| **none** | No network. Completely isolated. | Security-sensitive tasks |
| **overlay** | Spans multiple Docker hosts. | Docker Swarm, multi-host |

### How Container-to-Container Communication Works

When containers are on the same Docker network, they can reach each other **by service name** (in Compose) or **by container name**. Docker has a built-in DNS server that resolves these names.

```
Your App Container wants to connect to MongoDB:

WRONG: mongodb://localhost:27017    ← 'localhost' means inside the app container
RIGHT: mongodb://mongodb:27017      ← 'mongodb' is the service name, Docker DNS resolves it

This is why your MONGODB_URI has the service name, not 'localhost'.
```

```
Docker Network: app-network
  ┌─────────────────────────────────────────────┐
  │                                             │
  │  [app container]    [mongodb container]     │
  │  IP: 172.18.0.2     IP: 172.18.0.3         │
  │  name: "app"        name: "mongodb"         │
  │         │                  ↑                │
  │         └──────────────────┘                │
  │         app can reach mongodb by name       │
  │                                             │
  └─────────────────────────────────────────────┘
         ↑
  Only ports explicitly mapped (-p 3000:3000) 
  are reachable from your host machine
```

### Port Mapping

```
-p 3000:3000
 ↑ host port  ↑ container port

Your browser → localhost:3000 (host) → 3000 (inside container) → Express app

MongoDB: -p 27017:27017
  → Only do this in development so MongoDB Compass on your host can connect
  → In production, DON'T expose MongoDB's port — only your app container needs it
```

---

## 10. Docker Volumes — Persistent Data

### The Problem: Container Ephemerality

```
Scenario: MongoDB runs in a container. You insert 10,000 user records.
You do: docker stop mongodb && docker rm mongodb
You do: docker run mongo:7  ← fresh container

All your data is GONE. The container filesystem was ephemeral.
```

### Volumes vs Bind Mounts

| | Named Volume | Bind Mount |
|---|---|---|
| **Definition** | Docker manages storage location | You specify a host path |
| **Location** | `/var/lib/docker/volumes/` | Anywhere on your host |
| **Syntax** | `- mongo-data:/data/db` | `- ./src:/app/src` |
| **Best for** | Database data, production | Development hot-reload |
| **Performance** | Better (Docker optimized) | Slightly slower on Windows |
| **Portability** | High (Docker manages path) | Low (absolute host paths) |

### Named Volumes (Production Data)

```yaml
# docker-compose.yml
services:
  mongodb:
    volumes:
      - mongo-data:/data/db   # Docker manages where 'mongo-data' lives on host

volumes:
  mongo-data:                  # declare the named volume
```

```powershell
# List all volumes
docker volume ls

# Inspect where a volume lives on host
docker volume inspect mongo-data

# Remove a specific volume (deletes data!)
docker volume rm mongo-data

# Remove all unused volumes
docker volume prune
```

### Bind Mounts (Development Hot Reload)

```yaml
# docker-compose.dev.yml
services:
  app:
    volumes:
      - .:/app                # bind mount: your host project folder → /app in container
      - /app/node_modules     # IMPORTANT: this is an anonymous volume that "shadows"
                              # /app/node_modules — keeps container's node_modules
                              # instead of replacing with host's (possibly Windows) node_modules
```

**Why the `node_modules` trick**: When you bind mount `.` to `/app`, it overwrites `/app/node_modules` with your host's `node_modules`. This causes issues because native modules compiled for Linux won't work on Windows. The anonymous volume `/app/node_modules` takes precedence, keeping the container's (Linux-compiled) `node_modules` untouched.

---

## 11. Docker in System Design

This section is what elevates your interview answers from junior to senior.

### Microservices Architecture

```
API Gateway (nginx container)
       │
       ├── User Service (Node container)
       │         └── Users DB (PostgreSQL container)
       │
       ├── Order Service (Node container)
       │         └── Orders DB (MongoDB container)
       │
       ├── Payment Service (Node container)
       │         └── Payments DB (PostgreSQL container)
       │
       └── Notification Service (Node container)
                 └── Redis container (queue)

Each service:
  - Is its own Docker image
  - Scales independently (run 3 Order Service containers during sales)
  - Deploys independently (update Payment Service without touching others)
  - Fails independently (Order Service down doesn't crash User Service)
```

### Horizontal Scaling with Containers

```
Load Balancer (nginx)
       │
       ├── app:1 (container) ─┐
       ├── app:2 (container)  ├── All talk to same MongoDB volume
       ├── app:3 (container) ─┘
       └── app:4 (container)

docker compose up --scale app=4

For stateless apps (no session stored in memory), this works immediately.
Sessions stored in Redis (external to container) → all instances share session.
```

### Why Docker Matters for System Design Interviews

When asked about how you'd deploy a system, mentioning Docker shows:

1. **Environment consistency** — same behavior in dev, staging, prod
2. **Fast deployments** — containers start in milliseconds
3. **Rollbacks** — keep old image tags; `docker pull myapp:v1.0` to rollback
4. **Resource efficiency** — pack more services per server than VMs
5. **CI/CD integration** — build image once, promote same image through envs

### Container Orchestration (Beyond Docker)

In interviews, you'll encounter **Kubernetes**. Know this distinction:

```
Docker          = building and running individual containers
Docker Compose  = orchestrating containers on ONE machine
Kubernetes (K8s) = orchestrating containers across MANY machines
                   handles: auto-scaling, self-healing, rolling deployments,
                            load balancing, secrets management

For small teams: Docker Compose on a VM is often enough
For large scale: Kubernetes (EKS on AWS, GKE on Google Cloud)
```

**Interview phrasing**: "For our Node.js services, we containerize with Docker and manage them with Docker Compose for development. In production, we'd use Kubernetes for auto-scaling and self-healing, or a managed service like AWS ECS which handles orchestration without the Kubernetes operational overhead."

---

## 12. GitHub Actions CI/CD with Docker

### What CI/CD Means in Docker Terms

```
CI (Continuous Integration):
  Every push to GitHub →
    1. Checkout code
    2. Build Docker image (catches build errors early)
    3. Run tests inside the container
    4. Push image to registry with a tag

CD (Continuous Deployment):
  After CI passes →
    5. Pull new image on production server
    6. docker compose up -d --build (or Kubernetes rolling update)
    7. Old containers stop, new ones start
    8. Zero (or near-zero) downtime
```

### File Structure

```
your-project/
├── .github/
│   └── workflows/
│       ├── ci.yml          ← runs on every push/PR (build + test)
│       └── deploy.yml      ← runs on push to main (deploy to production)
├── Dockerfile
├── docker-compose.yml
├── docker-compose.dev.yml
├── src/
│   └── server.js
└── package.json
```

### Workflow 1: CI — Build, Test, Push Image

```yaml
# .github/workflows/ci.yml

name: CI — Build, Test & Push

# When does this run?
on:
  push:
    branches: [main, develop]
  pull_request:
    branches: [main]

# Environment variables available to all jobs
env:
  REGISTRY: ghcr.io
  IMAGE_NAME: ${{ github.repository }}   # e.g., yourusername/myapp

jobs:

  # ─── Job 1: Run Tests ───────────────────────────────────────────────────
  test:
    name: Run Tests
    runs-on: ubuntu-latest    # GitHub-hosted Linux runner (Docker runs natively here)

    steps:
      - name: Checkout code
        uses: actions/checkout@v4

      - name: Set up Node.js
        uses: actions/setup-node@v4
        with:
          node-version: "20"
          cache: "npm"

      - name: Install dependencies
        run: npm ci

      - name: Run unit tests
        run: npm test

      - name: Run linter
        run: npm run lint

  # ─── Job 2: Build & Push Docker Image ──────────────────────────────────
  build-and-push:
    name: Build & Push Docker Image
    runs-on: ubuntu-latest
    needs: test              # only runs if 'test' job passes
    
    # Required permissions for pushing to GitHub Container Registry
    permissions:
      contents: read
      packages: write

    steps:
      - name: Checkout code
        uses: actions/checkout@v4

      # Docker Buildx enables multi-platform builds and BuildKit features
      - name: Set up Docker Buildx
        uses: docker/setup-buildx-action@v3

      # Login to GitHub Container Registry using GITHUB_TOKEN (automatic secret)
      - name: Login to GitHub Container Registry
        uses: docker/login-action@v3
        with:
          registry: ghcr.io
          username: ${{ github.actor }}
          password: ${{ secrets.GITHUB_TOKEN }}

      # Extract metadata for tagging the image intelligently
      - name: Extract image metadata (tags and labels)
        id: meta
        uses: docker/metadata-action@v5
        with:
          images: ${{ env.REGISTRY }}/${{ env.IMAGE_NAME }}
          tags: |
            # Tag with branch name: ghcr.io/user/myapp:main
            type=ref,event=branch
            # Tag with PR number: ghcr.io/user/myapp:pr-42
            type=ref,event=pr
            # Tag with semantic version when you push a tag: ghcr.io/user/myapp:v1.2.3
            type=semver,pattern={{version}}
            # Always tag with short git SHA: ghcr.io/user/myapp:sha-abc1234
            type=sha,prefix=sha-,format=short

      # Build the Docker image and push to GHCR
      - name: Build and push Docker image
        uses: docker/build-push-action@v5
        with:
          context: .
          file: ./Dockerfile
          push: ${{ github.event_name != 'pull_request' }}   # don't push for PRs
          tags: ${{ steps.meta.outputs.tags }}
          labels: ${{ steps.meta.outputs.labels }}
          # Cache layers from registry for faster subsequent builds
          cache-from: type=gha
          cache-to: type=gha,mode=max
```

### Workflow 2: CD — Deploy to Production

```yaml
# .github/workflows/deploy.yml

name: CD — Deploy to Production

on:
  push:
    branches: [main]      # only deploy when code reaches main
  workflow_dispatch:      # allow manual trigger from GitHub UI

jobs:
  deploy:
    name: Deploy to Production Server
    runs-on: ubuntu-latest
    environment: production    # links to GitHub environment with protection rules
    
    steps:
      - name: Checkout code
        uses: actions/checkout@v4

      # SSH into your production server and run deployment commands
      - name: Deploy via SSH
        uses: appleboy/ssh-action@v1.0.0
        with:
          host: ${{ secrets.PROD_SERVER_HOST }}       # your server IP/hostname
          username: ${{ secrets.PROD_SERVER_USER }}   # e.g., ubuntu
          key: ${{ secrets.PROD_SSH_PRIVATE_KEY }}    # your SSH private key
          script: |
            # Navigate to your project on the server
            cd /opt/myapp

            # Login to GHCR on the server
            echo ${{ secrets.GITHUB_TOKEN }} | docker login ghcr.io \
              -u ${{ github.actor }} --password-stdin

            # Pull the latest image
            docker pull ghcr.io/${{ github.repository }}:main

            # Update and restart containers
            docker compose -f docker-compose.yml -f docker-compose.prod.yml \
              up -d --no-deps app

            # Clean up old images
            docker image prune -f

            echo "✅ Deployment complete"

      # Optional: notify team in Slack or Discord
      - name: Notify deployment success
        if: success()
        run: |
          curl -X POST ${{ secrets.SLACK_WEBHOOK }} \
            -H 'Content-type: application/json' \
            --data '{"text":"✅ myapp deployed to production (commit: ${{ github.sha }})"}'
```

### Workflow 3: Full Pipeline with Staging Environment

```yaml
# .github/workflows/pipeline.yml

name: Full CI/CD Pipeline

on:
  push:
    branches: [main, staging]
  pull_request:
    branches: [main]

jobs:
  test:
    name: Test
    runs-on: ubuntu-latest
    services:
      # Spin up a real MongoDB for integration tests inside GitHub Actions!
      mongodb:
        image: mongo:7
        ports:
          - 27017:27017
        options: >-
          --health-cmd "mongosh --eval 'db.adminCommand({ping:1})'"
          --health-interval 10s
          --health-timeout 5s
          --health-retries 5

    steps:
      - uses: actions/checkout@v4
      - uses: actions/setup-node@v4
        with:
          node-version: "20"
          cache: "npm"
      - run: npm ci
      - name: Run all tests
        env:
          MONGODB_URI: mongodb://localhost:27017/testdb
          NODE_ENV: test
        run: npm test

  build:
    name: Build Image
    needs: test
    runs-on: ubuntu-latest
    permissions:
      contents: read
      packages: write
    outputs:
      image-tag: ${{ steps.meta.outputs.version }}    # pass tag to deploy job
    steps:
      - uses: actions/checkout@v4
      - uses: docker/setup-buildx-action@v3
      - uses: docker/login-action@v3
        with:
          registry: ghcr.io
          username: ${{ github.actor }}
          password: ${{ secrets.GITHUB_TOKEN }}
      - id: meta
        uses: docker/metadata-action@v5
        with:
          images: ghcr.io/${{ github.repository }}
          tags: |
            type=sha,prefix=sha-,format=short
            type=ref,event=branch
      - uses: docker/build-push-action@v5
        with:
          context: .
          push: true
          tags: ${{ steps.meta.outputs.tags }}
          cache-from: type=gha
          cache-to: type=gha,mode=max

  deploy-staging:
    name: Deploy to Staging
    needs: build
    runs-on: ubuntu-latest
    environment: staging
    if: github.ref == 'refs/heads/staging'
    steps:
      - name: Deploy to staging server
        uses: appleboy/ssh-action@v1.0.0
        with:
          host: ${{ secrets.STAGING_HOST }}
          username: ${{ secrets.STAGING_USER }}
          key: ${{ secrets.STAGING_SSH_KEY }}
          script: |
            cd /opt/myapp
            docker pull ghcr.io/${{ github.repository }}:staging
            docker compose up -d --no-deps app

  deploy-production:
    name: Deploy to Production
    needs: build
    runs-on: ubuntu-latest
    environment: production    # requires manual approval if configured in GitHub
    if: github.ref == 'refs/heads/main'
    steps:
      - name: Deploy to production server
        uses: appleboy/ssh-action@v1.0.0
        with:
          host: ${{ secrets.PROD_HOST }}
          username: ${{ secrets.PROD_USER }}
          key: ${{ secrets.PROD_SSH_KEY }}
          script: |
            cd /opt/myapp
            docker pull ghcr.io/${{ github.repository }}:main
            docker compose up -d --no-deps app
            docker image prune -f
```

### Setting Up GitHub Secrets

Go to: **Repository → Settings → Secrets and variables → Actions**

| Secret Name | Value |
|-------------|-------|
| `PROD_SERVER_HOST` | Your server IP or domain |
| `PROD_SERVER_USER` | SSH username (e.g., `ubuntu`) |
| `PROD_SSH_PRIVATE_KEY` | Your private SSH key (`cat ~/.ssh/id_rsa`) |
| `SLACK_WEBHOOK` | Slack webhook URL for notifications |

`GITHUB_TOKEN` is **automatically provided** by GitHub Actions — you don't need to create it.

---

## 13. Interview Questions & Answers

Organized by topic. Answers are crafted to be conversational but technically precise.

---

### Fundamentals

**Q: What is Docker and why would you use it?**

> "Docker is a containerization platform that packages an application with its dependencies — runtime, libraries, configuration — into a standardized unit called a container. The key benefit is environment consistency: a container runs identically on any machine with Docker installed, eliminating 'works on my machine' problems. It's also much lighter than VMs because containers share the host OS kernel instead of emulating hardware, so you get millisecond startup times and much better resource density."

---

**Q: What's the difference between an image and a container?**

> "An image is an immutable, read-only blueprint — like a class in OOP. It defines what the container should contain: the OS layer, dependencies, your code. A container is a running instance of that image — like an object. You can run many containers from one image, each fully isolated. The image lives on disk; containers are running processes."

---

**Q: What's the difference between Docker and a Virtual Machine?**

> "VMs virtualize hardware and run a full guest OS — great for strong isolation but heavy (GBs, minutes to boot). Docker containers virtualize at the OS level — they share the host kernel and only package what the app needs. This makes containers much lighter (MBs, seconds to start) and more efficient. The tradeoff is weaker isolation since a kernel exploit affects all containers. For most microservice workloads, containers are the right choice."

---

**Q: Explain Docker layers and why they matter.**

> "Every instruction in a Dockerfile creates a new immutable filesystem layer. Docker caches these layers, so if a layer's content hasn't changed, Docker reuses the cached version on rebuild. This makes incremental builds very fast. The order of instructions matters — put infrequently changing steps (like `FROM` and `RUN npm install`) before frequently changing ones (like `COPY . .`) so that cache hits happen as late in the process as possible."

---

### Dockerfile & Best Practices

**Q: Why do we copy `package.json` before copying source code in a Dockerfile?**

> "It's a layer caching optimization. `npm install` is slow and its result only changes when `package.json` or `package-lock.json` changes. If we copy package files first, run `npm install`, and then copy source code, the `npm install` layer gets cached. On the next build, if only source code changed, Docker reuses the cached install layer and only rebuilds from `COPY . .` onwards — much faster. If we copied everything first, any source code change would invalidate the cache and force npm install to re-run."

---

**Q: What is a multi-stage build and when would you use it?**

> "A multi-stage build uses multiple `FROM` instructions in one Dockerfile to produce a smaller final image. For example, in TypeScript: the first stage (builder) installs all dependencies including devDependencies and compiles TypeScript to JavaScript. The second stage (production) starts fresh, copies only the compiled output and installs only production dependencies. The final image is significantly smaller because all build tools, devDependencies, and intermediate files are discarded. This directly impacts deployment speed and attack surface."

---

**Q: Why should you never store secrets in a Docker image?**

> "Docker images can be pushed to registries — if secrets are baked into an image, anyone who pulls the image can run `docker inspect` or `docker history` and potentially read them. Also, images are often stored in git history or shared registries. Secrets should be injected at runtime via environment variables, Docker secrets, or external secret managers like AWS Secrets Manager or HashiCorp Vault."

---

**Q: What is `.dockerignore` and why is it important?**

> "`.dockerignore` tells Docker what files to exclude from the build context sent to the daemon. Without it, `COPY . .` would include `node_modules` (potentially hundreds of MBs), `.git` history, `.env` files with secrets, and other irrelevant files. This slows down builds and can accidentally leak sensitive data into images. It's analogous to `.gitignore` and equally important."

---

### Docker Compose & Networking

**Q: What is Docker Compose and when would you use it over plain `docker run`?**

> "Docker Compose lets you declaratively define a multi-container application in a `docker-compose.yml` file and manage it with a single command. Instead of manually running `docker network create`, `docker run` with 10 flags for each service, and tracking dependencies, Compose handles all of that. I'd use it any time my app has more than one container — even in development with just a Node app and a database."

---

**Q: How do containers communicate with each other in Docker Compose?**

> "Containers in Docker Compose are automatically placed on a shared network. Docker includes an embedded DNS server, so containers can reach each other using their service name as the hostname. For example, if I have a service called `mongodb`, my Node app connects to `mongodb://mongodb:27017` — not `localhost:27017`. `localhost` in a container means inside that container, not the host machine."

---

**Q: What's the difference between a named volume and a bind mount?**

> "A named volume is managed by Docker — Docker decides where to store the data on the host, usually under `/var/lib/docker/volumes/`. It's the right choice for database data in production because it's optimized and portable. A bind mount maps a specific host path into the container — I use these in development to mount my source code so changes reflect immediately without rebuilding the image. The downside of bind mounts is they're OS-path-specific and slightly slower on Windows/Mac due to filesystem translation."

---

### CI/CD

**Q: Describe a Docker-based CI/CD pipeline.**

> "In our pipeline: on every push, GitHub Actions checks out the code, builds the Docker image using `docker build`, runs tests inside a container to match production conditions, and if tests pass, pushes the image to our container registry (GHCR or ECR) tagged with the git SHA. On merge to main, a separate workflow SSHs into the production server, pulls the new image, and runs `docker compose up -d --no-deps app` to replace only the app container. The old image is kept so we can rollback by pulling a previous tag. This whole process usually takes 3-5 minutes."

---

**Q: How do you do zero-downtime deployments with Docker?**

> "At the compose level, you'd use `docker compose up -d --no-deps app` which replaces containers one at a time. For true zero-downtime, you'd combine Docker with a load balancer (like nginx). Start a new container on a different port, health-check it, then update the load balancer to route traffic to the new container, then stop the old one. Kubernetes handles this automatically with rolling deployments. The key is that containers start in milliseconds, so the window of downtime is very short."

---

**Q: How do you handle environment-specific configuration in Docker?**

> "We maintain separate docker-compose override files: `docker-compose.dev.yml` for development (bind mounts for hot reload, exposed database ports, nodemon) and `docker-compose.prod.yml` for production (no bind mounts, restart policies, production image from registry). Environment variables are injected at runtime — never baked into images. Secrets use GitHub Actions secrets injected at deploy time, and on the server we use a `.env.production` file that's not committed to git."

---

### System Design

**Q: How does Docker support microservices architecture?**

> "Docker makes microservices practical by packaging each service with its own dependencies — Service A can use Node v18 and Service B can use Node v20 without conflict. Each service has its own Docker image and can be scaled independently. `docker compose scale app=5` spins up 5 instances of the app. In Kubernetes, this becomes a Deployment with autoscaling. Containers also fail independently — a crash in the Notification service doesn't take down the User service."

---

**Q: What are the limitations of Docker that you should know?**

> "A few important ones: First, containers share the host kernel, so isolation is weaker than VMs — a kernel exploit affects all containers. Second, stateful services like databases work in Docker but require careful volume management for data persistence and backups. Third, Docker Compose is single-host; for multi-host orchestration you need Kubernetes or Docker Swarm. Fourth, Windows-native Docker is still slightly heavier than Linux Docker because of the WSL2 layer. Finally, debugging distributed systems across many containers is harder than a monolith."

---

**Q: When would you NOT use Docker?**

> "If the team is tiny and deploying a single simple app to a managed platform like Heroku or Railway, Docker adds complexity without much benefit — those platforms handle environment consistency for you. For Lambda functions or serverless workloads, Docker isn't the default fit (though AWS Lambda supports container images). And for desktop GUI applications, Docker isn't designed for that use case. Docker shines for backend services, APIs, and microservices — exactly the Node/Express use case."

---

## 14. Quick Reference Cheat Sheet

### Essential Commands in 30 Seconds

```powershell
# BUILD
docker build -t myapp:v1 .                  # build image
docker compose up -d --build                # build + start all services

# RUN
docker run -d -p 3000:3000 --name app myapp:v1     # run detached
docker compose up -d                               # start compose services

# INSPECT
docker ps                                   # running containers
docker logs -f my-container                 # follow logs
docker exec -it my-container sh             # shell into container
docker stats                                # resource usage

# STOP / CLEAN
docker stop my-container                    # graceful stop
docker compose down                         # stop + remove containers
docker system prune                         # clean unused resources

# REGISTRY
docker tag myapp:v1 user/myapp:v1          # tag for registry
docker push user/myapp:v1                  # push to Docker Hub
docker pull user/myapp:v1                  # pull from registry
```

### Dockerfile Skeleton for Node/Express

```dockerfile
FROM node:20-alpine
WORKDIR /app
COPY package*.json ./
RUN npm ci --omit=dev
COPY . .
EXPOSE 3000
CMD ["node", "server.js"]
```

### docker-compose.yml Skeleton

```yaml
version: "3.9"
services:
  app:
    build: .
    ports: ["3000:3000"]
    environment:
      - MONGODB_URI=mongodb://mongodb:27017/mydb
    depends_on: [mongodb]
    networks: [app-net]
  mongodb:
    image: mongo:7
    volumes: [mongo-data:/data/db]
    networks: [app-net]
volumes:
  mongo-data:
networks:
  app-net:
```

### GitHub Actions Skeleton

```yaml
name: CI
on: [push]
jobs:
  build:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
      - uses: docker/login-action@v3
        with:
          registry: ghcr.io
          username: ${{ github.actor }}
          password: ${{ secrets.GITHUB_TOKEN }}
      - uses: docker/build-push-action@v5
        with:
          push: true
          tags: ghcr.io/${{ github.repository }}:latest
```

### Key Concepts at a Glance

| Term | One-Line Definition |
|------|---------------------|
| **Image** | Read-only blueprint for a container (like a class) |
| **Container** | Running instance of an image (like an object) |
| **Dockerfile** | Recipe to build an image |
| **Registry** | Storage for images (Docker Hub, GHCR, ECR) |
| **Compose** | Tool for multi-container apps (one YAML file) |
| **Volume** | Persistent storage outside container |
| **Bind Mount** | Map host folder into container (dev hot-reload) |
| **Network** | How containers talk to each other |
| **Layer** | Cached filesystem snapshot from one Dockerfile instruction |
| **Namespace** | Linux feature that creates process isolation |
| **cgroup** | Linux feature that limits CPU/memory per container |
| **Multi-stage** | Multiple FROM stages to produce slim final image |
| **Lazy Propagation** | Push pending updates only when children are accessed |

### The Argument for Docker in an Interview

> "Docker solves three problems for us. First, **environment parity** — dev, staging, and prod run the same image, so 'works on my machine' bugs disappear. Second, **fast deployments** — containers start in seconds, so deployments take minutes not hours, and rollbacks are trivial (just tag the previous image). Third, **scalability** — our Node services are stateless and containerized, so scaling means running more containers behind a load balancer, which Kubernetes or even Docker Compose can handle automatically."

---

*End of Docker — Complete Guide for SDE Interviews*
