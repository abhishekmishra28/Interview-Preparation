# ☁️ Day 2: Introduction to AWS & Global Infrastructure

Welcome to Day 2! Now that we understand the concept of the Cloud, we are going to look at the biggest player in the industry: **Amazon Web Services (AWS)**.

---

## 1. What is AWS?

**Amazon Web Services (AWS)** is the world's most comprehensive and broadly adopted cloud platform.
*   **Launched:** 2006
*   **Market Position:** Market leader (ahead of Azure and Google Cloud).
*   **Offering:** Over 200 fully featured services (Compute, Storage, AI, IoT, etc.).

> **Key Concept:** AWS provides "IT Infrastructure as a Service." You don't buy servers; you rent them by the second or hour.

---

## 2. AWS Global Infrastructure (Crucial!)

To understand how to build on AWS, you must understand how physically organized it is. The infrastructure is built around **Regions** and **Availability Zones**.

### A. Regions 🌍
A **Region** is a physical location in the world where AWS clusters data centers.
*   **Examples:** `us-east-1` (N. Virginia), `eu-west-1` (Ireland), `ap-south-1` (Mumbai).
*   **Choosing a Region:** You choose a region based on:
    1.  **Latency:** How close is it to your users?
    2.  **Compliance:** Data sovereignty laws (e.g., GDPR requires data to stay in Europe).
    3.  **Cost:** Some regions are cheaper than others.

### B. Availability Zones (AZs) 🏢
Inside every Region, there are multiple **Availability Zones**.
*   An AZ consists of one or more discrete data centers with redundant power, networking, and connectivity.
*   **Isolation:** If one AZ fails (due to fire, flood, power loss), the other AZs in that region keep working.
*   **Best Practice:** Always deploy your applications across *multiple* AZs for high availability.

### C. Edge Locations ⚡
These are smaller sites located in major cities around the world, used specifically for **CDN (Content Delivery Network)** via a service called **Amazon CloudFront**.
*   They cache content (images, videos) closer to users to reduce load times.

> **Hierarchy Summary:**
> Global Map → **Regions** → **Availability Zones** → **Data Centers**

---

## 3. How to Access AWS

There are three ways to interact with AWS:

1.  **AWS Management Console (Web)**
    *   The website interface (GUI).
    *   Best for: Beginners, visual navigation, and quick tests.
2.  **AWS CLI (Command Line Interface)**
    *   A tool to manage AWS services from your terminal.
    *   Best for: Automation and power users.
3.  **SDK (Software Development Kit)**
    *   Using code (Python, Java, Node.js) to manage resources.
    *   Best for: Developers writing application code.

---

## 4. Key Services Overview (The Building Blocks)

AWS has 200+ services, but as a beginner, you need to know the core pillars:

### 🖥️ Compute (Processing Power)
*   **EC2 (Elastic Compute Cloud):** Virtual servers. You choose the OS (Windows/Linux) and size (RAM/CPU). This is *IaaS*.
*   **Lambda:** Serverless computing. You upload code, and it runs only when triggered. You don't manage any servers. This is *Function-as-a-Service*.

### 💾 Storage (Holding Data)
*   **S3 (Simple Storage Service):** Object storage. Great for files, images, backups, and hosting static websites. (Think Google Drive for apps).
*   **EBS (Elastic Block Store):** Virtual hard drives that attach to your EC2 instances.

### 🗄️ Databases (Organizing Data)
*   **RDS (Relational Database Service):** Managed SQL databases (MySQL, PostgreSQL, Oracle). AWS handles backups and patching.
*   **DynamoDB:** A NoSQL (Key-Value) database. incredibly fast and scalable.

### 🌐 Networking
*   **VPC (Virtual Private Cloud):** Your isolated section of the AWS cloud. You control the network configuration (IP ranges, subnets, firewalls).

---

## 5. Security: IAM (Identity and Access Management)

**IAM** is the first service you interact with. It controls "Who can do what" in your AWS account.

### The "Root" Account ⚠️
*   When you first sign up, you are the **Root User**.
*   **Golden Rule:** **NEVER** use the Root user for daily tasks. It has unlimited power. Create a separate Admin user immediately.

### IAM Components:
1.  **Users:** Physical people (e.g., "Alice").
2.  **Groups:** Collections of users (e.g., "Developers").
3.  **Roles:** Permissions assigned to *services* or temporary users (e.g., allowing an EC2 server to access S3).
4.  **Policies:** JSON documents defining permissions (e.g., "Allow Read-Only access").

---

## 6. AWS Free Tier 💸

AWS offers a Free Tier for new accounts (usually for 12 months).
*   **750 hours/month** of EC2 (micro instances).
*   **5GB** of S3 Storage.
*   **750 hours/month** of RDS Databases.

> **Warning:** Always set up a **Billing Alarm** immediately so you get an email if you accidentally cross the free tier limits.

---

## ✅ Summary of Day 2

1.  **AWS** is the leading cloud provider.
2.  **Infrastructure:** Regions (Geography) contain Availability Zones (Data Centers).
3.  **Access:** You can use the Console (Web), CLI, or SDK.
4.  **Core Services:** EC2 (Compute), S3 (Storage), RDS (Database), VPC (Network).
5.  **IAM:** Manage users and permissions. Secure your Root account!

---
*Next Up: Day 3 - Hands-on! Setting up your account, Securing it with MFA, and launching your first Virtual Machine (EC2).*
