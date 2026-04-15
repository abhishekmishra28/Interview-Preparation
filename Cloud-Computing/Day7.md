# ☁️ AWS EC2 – Complete Guide (Interview Ready)

---

## 📌 What is EC2?

**EC2 (Elastic Compute Cloud)** is a web service that provides **virtual servers (instances)** in the cloud to run applications.

👉 Think of it as:

> “Renting a computer in the cloud”

---

## 🎯 Key Features

* Scalable (increase/decrease capacity anytime)
* Pay-as-you-go pricing
* Full control over OS and configuration
* Supports multiple instance types

---

## 🧠 Core Concepts of EC2

---

### 🖥 1. Instance

A **virtual machine** running in AWS.

👉 Example:

* Linux instance
* Windows instance

---

### 📦 2. AMI (Amazon Machine Image)

A **pre-configured template** used to launch instances.

👉 Includes:

* OS (Linux/Windows)
* Software (Node.js, Python, etc.)

---

### ⚙️ 3. Instance Types

Define **CPU, RAM, Storage, Networking** capacity.

👉 Examples:

* t2.micro (Free tier)
* m5.large (General purpose)
* c5 (Compute optimized)

---

### 🔐 4. Key Pair

Used to securely connect to EC2.

👉 Types:

* Public key (stored in AWS)
* Private key (.pem file – with user)

---

### 🌐 5. Security Groups

Acts like a **firewall** for EC2.

👉 Controls:

* Inbound traffic (incoming)
* Outbound traffic (outgoing)

---

### 💾 6. EBS (Elastic Block Store)

Storage attached to EC2.

👉 Think:

> Hard disk of your virtual machine

---

## 🚀 How EC2 Works (Flow)

```id="ec2flow1"
Choose AMI → Select Instance Type → Configure → Add Storage → Set Security Group → Launch Instance
```

---

## 🔥 Steps to Launch EC2 Instance

1. Go to AWS Console
2. Select EC2 service
3. Click “Launch Instance”
4. Choose AMI (e.g., Ubuntu)
5. Select instance type (t2.micro)
6. Configure security group (allow SSH/HTTP)
7. Create/download key pair
8. Launch instance

---

## 🔑 Connecting to EC2

### For Linux:

```bash id="ec2cmd1"
ssh -i key.pem ubuntu@your-public-ip
```

---

## 🌍 Public IP vs Private IP

| Type       | Usage                      |
| ---------- | -------------------------- |
| Public IP  | Access from internet       |
| Private IP | Internal AWS communication |

---

## 💡 Common Use Cases

* Hosting web applications
* Running backend servers
* Testing environments
* Microservices deployment

---

## 🔥 EC2 + DevOps Example

```id="ec2flow2"
GitHub → Jenkins → Build → Docker → EC2 → Deploy Application
```

---

## ⚖️ EC2 Pricing Models

* On-Demand → Pay per usage
* Reserved → Long-term discount
* Spot Instances → Cheapest (but can be terminated anytime)

---

## 🔐 Security Best Practices

* Never expose port 22 (SSH) to everyone
* Use IAM roles instead of hardcoding credentials
* Enable security groups properly
* Use key pairs securely

---

## 🧠 Interview Questions

---

### ❓ What is EC2?

EC2 is a cloud service that provides scalable virtual servers.

---

### ❓ What is AMI?

A template used to launch EC2 instances.

---

### ❓ What is Security Group?

A virtual firewall controlling traffic.

---

### ❓ Difference between Security Group and NACL?

| Feature | Security Group | NACL         |
| ------- | -------------- | ------------ |
| Level   | Instance level | Subnet level |
| Rules   | Allow only     | Allow & Deny |

---

### ❓ What is EBS?

Persistent storage attached to EC2.

---

## 📌 Summary

```id="ec2summary"
EC2 → Virtual server
AMI → Template
Instance Type → Hardware config
Security Group → Firewall
EBS → Storage
```

---

## 🎯 Next Steps

After EC2, learn:

1. S3 (Storage)
2. VPC (Networking)
3. Load Balancer
4. Auto Scaling

---

## 📚 Conclusion

EC2 is the backbone of AWS compute services and is widely used to host scalable applications in the cloud.

---
