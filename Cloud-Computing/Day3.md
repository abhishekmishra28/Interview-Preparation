# ☁️ Cloud Computing Basics (Quick Notes)

---

## 💳 Pay-as-you-go Model (AWS / Cloud)

### 🔹 What it means
Pay only for the resources you use — no upfront cost, no fixed pricing.

### 🔹 Simple analogy
Like an electricity bill:
- Use more → pay more
- Use less → pay less

### 🔹 In AWS:
You are charged for:
- Compute (EC2 instances running time)
- Storage (S3 buckets, EBS volumes)
- Network usage (data transfer)

### 🔹 Example
- Run a server for 2 hours → pay for 2 hours only  
- Store 5GB data → pay only for 5GB

### 🔹 Why it's powerful
- No need to buy expensive hardware
- Scales automatically with usage
- Cost-efficient for startups and projects

---

## 🖥️ Client-Server Workflow

### 🔹 Basic Idea
A system where:
- **Client** → Requests service
- **Server** → Provides service

### 🔹 Flow (Step-by-step)
1. User opens a browser/app (Client)
2. Client sends request (HTTP/HTTPS)
3. Server receives request
4. Server processes it (logic, DB, etc.)
5. Server sends response back
6. Client displays result

### 🔹 Example
- You open a website → request sent
- Server fetches data → sends HTML/JSON
- Browser displays page

### 🔹 Key Components
- Client: Browser, Mobile App
- Server: Backend (Node.js, Java, etc.)
- Database: Stores data
- Network: Internet

---

## 🖥️ Virtual Machines (VMs)

### 🔹 What is a VM?
A **software-based computer** running inside a physical computer.

### 🔹 Concept
One physical machine → Multiple virtual machines

### 🔹 Each VM has:
- OS (Linux/Windows)
- CPU (virtual)
- RAM (allocated)
- Storage

### 🔹 How it works
- Hypervisor creates and manages VMs
- Examples: VMware, VirtualBox, AWS EC2

### 🔹 Example in AWS
- Launch an EC2 instance → it's a VM
- You can SSH into it and use like a real server

### 🔹 Why VMs are useful
- Isolation (each VM is independent)
- Efficient resource usage
- Easy to scale and deploy

---

## 🔁 Quick Summary

| Concept           | Key Idea                          |
|------------------|----------------------------------|
| Pay-as-you-go    | Pay only for what you use        |
| Client-Server    | Request → Process → Response     |
| Virtual Machine  | Software version of a computer   |

---

## 💡 Interview Tip
Try to connect all 3:
Client → Server → Runs on VM → Charged via Pay-as-you-go
