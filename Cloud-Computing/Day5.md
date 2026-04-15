# ☁️ AWS Basics – Regions, Availability Zones & IAM

---

## 📌 Introduction

Amazon Web Services (AWS) is a cloud computing platform that provides scalable, reliable, and secure infrastructure services.

This document covers:

* AWS Regions
* Availability Zones (AZs)
* Identity and Access Management (IAM)

---

## 🌍 AWS Regions

### 📌 Definition

An **AWS Region** is a physical geographic location where AWS has multiple data centers.

### 📍 Examples

* Asia Pacific (Mumbai) → ap-south-1
* US East (N. Virginia) → us-east-1

---

### 🎯 Key Features

* Each region is **isolated and independent**
* Data is **not automatically shared** between regions
* Choose region based on:

  * Latency (closer region = better performance)
  * Compliance requirements
  * Cost

---

### 💡 Interview Point

A region is a **geographical area containing multiple Availability Zones**.

---

## 🏢 Availability Zones (AZs)

### 📌 Definition

An **Availability Zone (AZ)** is a data center (or group of data centers) within a region.

### 📍 Example

* ap-south-1a
* ap-south-1b
* ap-south-1c

---

### 🎯 Key Features

* Physically separate locations
* Connected with high-speed private network
* Designed for **fault isolation**

---

### 🔥 Importance

* Enables **high availability**
* If one AZ fails → application continues in another AZ

---

### 💡 Interview Point

An Availability Zone is an **isolated data center within a region used for fault tolerance**.

---

## 🧠 Region vs Availability Zone

| Feature   | Region              | Availability Zone        |
| --------- | ------------------- | ------------------------ |
| Scope     | Geographic area     | Inside a region          |
| Structure | Multiple AZs        | One or more data centers |
| Purpose   | Global distribution | High availability        |

---

## 🔐 AWS IAM (Identity and Access Management)

### 📌 Definition

IAM is a service that allows you to **securely control access to AWS resources**.

---

## 🎯 Core Components

### 👤 1. Users

* Individual identities (person or application)

---

### 👥 2. Groups

* Collection of users with similar permissions

---

### 🎭 3. Roles

* Temporary access with defined permissions
* Used by AWS services or applications

---

### 📜 4. Policies

* JSON documents defining permissions

#### Example Policy:

```json
{
  "Effect": "Allow",
  "Action": "s3:ListBucket",
  "Resource": "*"
}
```

---

## 🔑 Key Concepts

### 🔐 Authentication vs Authorization

* Authentication → Who you are
* Authorization → What you can access

---

### ⚖️ Principle of Least Privilege

Grant only the permissions required to perform a task.

---

### 🔒 Multi-Factor Authentication (MFA)

Adds an extra layer of security.

---

## 🔥 Real-World Example

### Scenario:

* An EC2 instance needs to access S3

### Solution:

* Create an IAM Role
* Attach S3 access policy
* Assign role to EC2

👉 No need to store credentials in code

---

## 📌 Summary

```
Region → Geographic area (multiple AZs)
AZ → Data centers for high availability
IAM → Access control and security
```

---

## 🎯 Next Steps

To continue learning AWS:

1. EC2 (Virtual Servers)
2. S3 (Storage Service)
3. VPC (Networking)
4. Hands-on IAM setup

---

## 📚 Conclusion

Understanding Regions, Availability Zones, and IAM is fundamental to building secure, scalable, and highly available applications on AWS.

---
