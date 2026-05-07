# AWS Complete Advanced Guide for SDE Interviews

> A practical, interview-focused, advanced AWS guide covering fundamentals, architecture thinking, and 6 of the most common and famous AWS services:
> **EC2, S3, RDS, Lambda, DynamoDB, and IAM**

---

## Table of Contents

1. [How to Think About AWS as an SDE](#how-to-think-about-aws-as-an-sde)
2. [AWS Fundamentals](#aws-fundamentals)
   - [Cloud Service Models](#cloud-service-models)
   - [Global Infrastructure](#global-infrastructure)
   - [Shared Responsibility Model](#shared-responsibility-model)
   - [Core Networking Concepts](#core-networking-concepts)
   - [Scalability, Availability, and Durability](#scalability-availability-and-durability)
   - [Security Basics](#security-basics)
   - [Observability and Operations](#observability-and-operations)
   - [Cost Optimization Basics](#cost-optimization-basics)
   - [AWS Well-Architected Pillars](#aws-well-architected-pillars)
   - [Fundamentals Interview Questions](#fundamentals-interview-questions)
3. [Service 1: Amazon EC2](#service-1-amazon-ec2)
4. [Service 2: Amazon S3](#service-2-amazon-s3)
5. [Service 3: Amazon RDS](#service-3-amazon-rds)
6. [Service 4: AWS Lambda](#service-4-aws-lambda)
7. [Service 5: Amazon DynamoDB](#service-5-amazon-dynamodb)
8. [Service 6: AWS IAM](#service-6-aws-iam)
9. [Cross-Service Architecture Patterns for SDEs](#cross-service-architecture-patterns-for-sdes)
10. [Common AWS Mistakes in Interviews and Real Projects](#common-aws-mistakes-in-interviews-and-real-projects)
11. [Rapid Revision Cheat Sheet](#rapid-revision-cheat-sheet)
12. [Advanced Scenario-Based Interview Questions](#advanced-scenario-based-interview-questions)

---

# How to Think About AWS as an SDE

As an SDE, interviewers usually do **not** expect you to memorize every AWS service. They expect you to:

- Understand **core cloud principles**
- Pick the **right service for the right workload**
- Design for **scalability, reliability, security, and cost**
- Explain **trade-offs**
- Understand how services **integrate**
- Reason about **failure modes**
- Build systems that are **observable and maintainable**

A strong AWS answer usually includes:

1. **What problem are we solving?**
2. **What traffic pattern or workload type do we have?**
3. **Which AWS service fits best?**
4. **How will it scale?**
5. **How will it stay secure?**
6. **How will we monitor it?**
7. **What are the cost trade-offs?**
8. **What happens when something fails?**

---

# AWS Fundamentals

## Cloud Service Models

### 1. IaaS
Infrastructure as a Service gives you virtualized compute, storage, and networking.

- Example: `EC2`
- You manage:
  - OS
  - runtime
  - patches
  - application
  - scaling strategy

### 2. PaaS / Managed Services
AWS manages more of the operational burden.

- Example: `RDS`
- You focus more on:
  - schema
  - queries
  - application logic

### 3. Serverless
You only provide code or configuration. AWS manages the servers.

- Example: `Lambda`
- Good for:
  - event-driven systems
  - APIs
  - asynchronous processing
  - highly variable traffic

### Interview Insight
A common interview angle is:
- "Why choose a managed service over self-managed infrastructure?"
- Best answer: reduced operational overhead, easier scaling, faster delivery, but sometimes less control.

---

## Global Infrastructure

AWS global infrastructure is the foundation of high availability and low latency.

### Key Terms

#### Region
A physical geographic area containing multiple isolated Availability Zones.

- Example: `us-east-1`, `eu-west-1`

#### Availability Zone (AZ)
One or more discrete data centers with redundant power, networking, and connectivity.

- AZs are isolated enough to reduce correlated failures
- Used for high availability

#### Edge Location
Used primarily by AWS content delivery and DNS services like:
- CloudFront
- Route 53

### Why It Matters
- Multi-AZ deployment improves resilience
- Multi-region improves disaster recovery and geo-distribution
- Keeping data and compute close to users improves latency

### Interview Tip
Know the difference:

| Concept | Purpose |
|---|---|
| Region | Geographic isolation and deployment boundary |
| Availability Zone | High availability within a region |
| Edge Location | Fast content delivery and DNS response |

---

## Shared Responsibility Model

AWS security is divided into:

### Security **of** the Cloud — AWS Responsibility
AWS manages:
- physical data centers
- hardware
- networking infrastructure
- hypervisor
- managed service infrastructure

### Security **in** the Cloud — Customer Responsibility
You manage:
- IAM permissions
- application security
- OS patching on EC2
- network rules
- encryption settings
- data classification
- secure coding

### Example
If you run MySQL on EC2:
- AWS secures hardware and virtualization
- You secure MySQL config, users, backups, patching, and firewall rules

If you use RDS:
- AWS handles much more of the database infrastructure
- You still handle schema security, access control, and application behavior

---

## Core Networking Concepts

Even if networking is not one of the 6 selected deep-dive services, it is essential for advanced AWS understanding.

### VPC
A Virtual Private Cloud is your isolated network in AWS.

### Subnets
A subnet is a range of IP addresses in your VPC.

- **Public subnet**: typically routes to an Internet Gateway
- **Private subnet**: no direct route to the internet

### Internet Gateway (IGW)
Allows communication between your VPC and the public internet.

### NAT Gateway
Allows instances in a private subnet to access the internet for outbound traffic without exposing them publicly.

### Route Tables
Control where traffic from a subnet goes.

### Security Groups
Virtual firewalls attached to ENIs or instances.

- Stateful
- Allow rules only
- Return traffic is automatically allowed

### Network ACLs
Subnet-level firewalls.

- Stateless
- Allow and deny rules
- Good for coarse-grained control

### DNS
AWS commonly uses:
- Route 53 for DNS
- private hosted zones for internal DNS
- public hosted zones for internet-facing domains

### Security Group vs NACL

| Feature | Security Group | NACL |
|---|---|---|
| Scope | Instance/ENI level | Subnet level |
| Stateful | Yes | No |
| Rules | Allow only | Allow and Deny |
| Use Case | Primary access control | Additional subnet filtering |

### Common Interview Topic
"How do you make a backend server private but still allow updates?"
- Put EC2/RDS in private subnets
- Use NAT Gateway for outbound internet access
- Allow inbound only from application tier or bastion/VPN if needed

---

## Scalability, Availability, and Durability

### Scalability
Ability to handle growing workload.

- **Vertical scaling**: add more CPU/RAM to one server
- **Horizontal scaling**: add more servers

### Elasticity
Automatically adapting capacity to traffic changes.

### High Availability
System remains available despite failures.

- Example: deploying across multiple AZs

### Fault Tolerance
System keeps working even when components fail.

### Durability
Probability that data remains intact over time.

- S3 is designed for very high durability

### Interview Tip
Use the right word correctly:
- EC2 Auto Scaling = elasticity
- Multi-AZ RDS = high availability
- S3 = durability
- Read replicas = read scalability

---

## Security Basics

### Identity and Access
Use IAM for:
- users
- roles
- policies
- temporary credentials

### Encryption
Two major states:
- **At rest**: stored data is encrypted
- **In transit**: data moving over the network uses TLS

### KMS
AWS Key Management Service is often used with:
- S3
- RDS
- EBS
- Lambda environment encryption

### Least Privilege
Grant only the permissions required.

### Secrets Management
Never hardcode secrets in code or AMIs.
Use:
- AWS Secrets Manager
- Systems Manager Parameter Store

### Logging and Audit
Use:
- CloudTrail for API activity
- CloudWatch for metrics/logs/alarms

---

## Observability and Operations

### CloudWatch
Used for:
- metrics
- logs
- alarms
- dashboards

### CloudTrail
Records AWS API activity for auditing and security investigations.

### X-Ray
Helps trace requests in distributed systems.

### Operational Questions Interviewers Like
- How do you know your service is unhealthy?
- How do you detect high latency?
- How do you alert on failures?
- How do you trace a request across services?

A good answer mentions:
- metrics
- structured logs
- alarms
- tracing
- dashboards
- runbooks

---

## Cost Optimization Basics

Advanced AWS answers should mention cost.

### Common Cost Levers
- Use managed services when ops cost matters
- Use Auto Scaling
- Choose correct storage class in S3
- Use Spot Instances for fault-tolerant workloads
- Use Reserved Instances or Savings Plans for steady workloads
- Avoid unnecessary inter-region or internet data transfer
- Right-size EC2 and RDS instances

### Common Interview Cost Trade-Offs
- `EC2` vs `Lambda`
- `RDS` vs `DynamoDB`
- `S3 Standard` vs `Glacier`
- `On-Demand` vs `Reserved` vs `Spot`

---

## AWS Well-Architected Pillars

A strong SDE answer often aligns with these pillars:

1. **Operational Excellence**
2. **Security**
3. **Reliability**
4. **Performance Efficiency**
5. **Cost Optimization**
6. **Sustainability**

### Interview Tip
If asked to improve a design, evaluate it across these pillars.

---

## Fundamentals Interview Questions

### 1. What is the difference between a Region and an Availability Zone?
**Answer:**  
A Region is a geographic area. An Availability Zone is an isolated data center or group of data centers within a Region. Multi-AZ improves availability inside a Region.

### 2. What is the shared responsibility model?
**Answer:**  
AWS secures the underlying cloud infrastructure, while customers secure workloads, configurations, access, and data inside the cloud.

### 3. What is the difference between vertical and horizontal scaling?
**Answer:**  
Vertical scaling increases resources on one machine. Horizontal scaling adds more machines or instances.

### 4. Why are private subnets used?
**Answer:**  
To prevent direct internet exposure of internal services like application servers or databases while still allowing controlled access.

### 5. What is the difference between a Security Group and a NACL?
**Answer:**  
Security Groups are stateful and instance-level. NACLs are stateless and subnet-level, with both allow and deny rules.

### 6. When should you choose managed services?
**Answer:**  
When you want to reduce operational burden, improve reliability, and focus more on application logic than infrastructure management.

### 7. What is high availability?
**Answer:**  
Designing systems to remain accessible despite failures, often by deploying across multiple AZs.

### 8. What is durability?
**Answer:**  
The likelihood that stored data remains intact over time even if hardware fails.

### 9. What AWS services are commonly used for observability?
**Answer:**  
CloudWatch for metrics/logs/alarms, CloudTrail for API audit logs, and X-Ray for tracing.

### 10. Why is least privilege important?
**Answer:**  
It reduces the blast radius of mistakes or credential compromise by limiting permissions to only what is needed.

---

# Service 1: Amazon EC2

## What is EC2?

Amazon EC2 provides virtual machines in the cloud.

Use EC2 when you need:
- full control over the OS
- custom software installation
- long-running workloads
- legacy applications
- container hosts
- specific networking or hardware requirements

---

## Where EC2 Fits

EC2 is best for:
- web servers
- application servers
- batch processing
- workers
- self-managed databases
- custom runtimes not suitable for Lambda

Not ideal when:
- you want zero server management
- the workload is very bursty and event-driven
- you want per-request billing without server provisioning

---

## Core Concepts

### AMI
Amazon Machine Image used to launch instances.

### Instance Type
Defines CPU, memory, storage, and networking capacity.

Examples:
- General purpose
- Compute optimized
- Memory optimized
- Storage optimized
- GPU accelerated

### EBS
Elastic Block Store provides persistent block storage.

### Instance Store
Temporary storage physically attached to the host. High performance, but data is lost when the instance stops/terminates.

### Key Pair
Used for SSH access to Linux instances.

### User Data
Bootstrap scripts that run at launch.

### Elastic IP
Static public IPv4 address.

### ENI
Elastic Network Interface. Useful in advanced networking scenarios.

---

## Advanced EC2 Concepts

### Auto Scaling Group (ASG)
Maintains desired number of instances and can scale automatically based on policies.

### Launch Template
Defines instance launch settings such as:
- AMI
- instance type
- storage
- security groups
- user data

### Load Balancing
EC2 is commonly placed behind:
- Application Load Balancer (HTTP/HTTPS)
- Network Load Balancer (TCP/UDP, very high performance)

### Placement Groups
Used for advanced placement strategies:
- Cluster
- Spread
- Partition

### Spot Instances
Low-cost spare capacity with interruption risk.

Good for:
- stateless workers
- batch processing
- fault-tolerant jobs

### Reserved Instances / Savings Plans
Useful for predictable long-term workloads.

### IMDSv2
Instance Metadata Service v2 is more secure than v1 and helps reduce SSRF-related risk.

### Hibernation
Useful if you want to preserve in-memory state on supported instances.

---

## EC2 Architecture Patterns

### Pattern 1: Stateless Web App
- Route 53
- ALB
- EC2 Auto Scaling Group across multiple AZs
- RDS in private subnets
- S3 for static assets
- CloudWatch alarms

Why it works:
- horizontal scale
- health checks
- no user session stored locally if sessions are externalized

### Pattern 2: Worker Tier
- EC2 workers poll jobs from a queue
- scale based on queue depth
- good for CPU-heavy or long-running jobs

### Pattern 3: Bastion-less Administration
Instead of a bastion host:
- use SSM Session Manager
- reduce SSH exposure
- improve auditability

---

## EC2 Best Practices

- Use multiple AZs for production
- Keep instances stateless where possible
- Put secrets outside the AMI
- Use IAM roles, not hardcoded keys
- Use CloudWatch alarms
- Patch AMIs regularly
- Use IMDSv2
- Prefer Launch Templates over older Launch Configurations
- Use Auto Scaling instead of fixed fleets
- Put databases in private subnets

---

## Common EC2 Pitfalls

- Treating one EC2 instance like a permanent pet instead of cattle
- Storing critical state on local disk
- Logging into production manually for every change
- Using long-lived access keys on instances
- Running without backups or AMI strategy
- Single-AZ deployment
- No health checks or autoscaling
- Publicly exposing SSH/RDP broadly

---

## EC2 Performance and Reliability Tips

- Separate web tier and database tier
- Use EBS-optimized instances where needed
- Monitor CPU, memory, disk, and network
- Tune connection pools and thread counts
- Use warm pools or pre-baked AMIs for faster scaling
- Offload static content to S3/CloudFront
- Use Spot for non-critical workers only

---

## EC2 Interview Questions

### 1. What is the difference between stopping and terminating an EC2 instance?
**Answer:**  
Stopping shuts down the instance but keeps EBS-backed data, and it can be restarted. Terminating deletes the instance; attached EBS volumes may also be deleted depending on configuration.

### 2. When would you choose EC2 over Lambda?
**Answer:**  
Choose EC2 when you need OS-level control, long-running processes, custom runtimes, high memory or compute tuning, or software not suitable for serverless execution limits.

### 3. What is an Auto Scaling Group?
**Answer:**  
A service that automatically launches or terminates EC2 instances to maintain desired capacity and respond to load or health events.

### 4. Why place EC2 instances behind a load balancer?
**Answer:**  
To distribute traffic, improve availability, enable health checks, and support horizontal scaling.

### 5. What is the difference between Security Groups and host-level firewalls?
**Answer:**  
Security Groups work at the AWS network interface level and are managed centrally; host firewalls operate inside the OS.

### 6. What are Spot Instances and when should you use them?
**Answer:**  
Spot Instances use spare AWS capacity at lower cost but can be interrupted. Use them for batch jobs, CI workers, and fault-tolerant workloads.

### 7. Why is stateless architecture preferred on EC2 web tiers?
**Answer:**  
It allows any instance to handle any request, which makes scaling, replacement, and recovery simpler.

### 8. What is IMDSv2 and why is it important?
**Answer:**  
It is a more secure version of the instance metadata service that helps reduce risk from SSRF and credential theft.

### 9. How do you make an EC2-based system highly available?
**Answer:**  
Deploy instances across multiple AZs, use an ALB, configure Auto Scaling, externalize state, monitor health, and automate recovery.

### 10. How do you securely allow an EC2 instance to access S3?
**Answer:**  
Attach an IAM role to the EC2 instance with least-privilege permissions instead of storing access keys on the machine.

### 11. What is the difference between EBS and instance store?
**Answer:**  
EBS is persistent block storage. Instance store is ephemeral local storage that is lost when the instance stops or fails.

### 12. Why might an Auto Scaling Group replace an instance even if the OS is still running?
**Answer:**  
If load balancer health checks or EC2 health checks fail, the ASG may replace it to maintain application availability.

---

# Service 2: Amazon S3

## What is S3?

Amazon S3 is object storage for virtually unlimited amounts of data.

Use S3 for:
- images, videos, and documents
- backups
- logs
- static website assets
- data lake storage
- archival
- file uploads and downloads

---

## S3 Mental Model

S3 stores **objects** inside **buckets**.

Each object has:
- key
- value/data
- metadata
- version ID if versioning is enabled

S3 is not a block storage system and not a relational database.

---

## Core Concepts

### Buckets
Globally unique names within AWS.

### Objects
Files plus metadata.

### Keys
The path-like identifier of the object.

### Storage Classes
Common options:
- S3 Standard
- S3 Intelligent-Tiering
- S3 Standard-IA
- S3 One Zone-IA
- Glacier Instant Retrieval
- Glacier Flexible Retrieval
- Glacier Deep Archive

### Versioning
Keeps multiple versions of an object.

### Lifecycle Rules
Automatically transition or expire objects.

### Multipart Upload
Important for large files and reliable upload performance.

### Pre-signed URLs
Temporary access to private objects without exposing credentials.

---

## Advanced S3 Concepts

### Strong Consistency
S3 provides strong read-after-write consistency for object operations in modern AWS usage.

### Event Notifications
S3 can trigger:
- Lambda
- SQS
- SNS

### Replication
- Same-Region Replication (SRR)
- Cross-Region Replication (CRR)

Useful for:
- compliance
- disaster recovery
- regional proximity

### Object Lock
Supports WORM-style retention for compliance.

### Encryption Options
- SSE-S3
- SSE-KMS
- SSE-C

### Access Control Models
- IAM policies
- bucket policies
- access points
- ACLs (legacy; avoid when possible)
- Block Public Access settings

### VPC Endpoints for S3
Allow private access from VPCs without traversing the public internet.

---

## S3 Security Best Practices

- Enable Block Public Access unless public access is intentional
- Prefer bucket policies and IAM over ACLs
- Use server-side encryption
- Use versioning
- Enable lifecycle rules
- Use access logs or CloudTrail data events for sensitive buckets
- Use pre-signed URLs for controlled temporary access
- Use least privilege on object prefixes if needed

---

## S3 Performance and Design Notes

- Use multipart upload for large files
- Avoid application assumptions about directory semantics; S3 is object-based
- Design keys carefully for organization, not for old partitioning myths
- Use CloudFront for global low-latency content delivery
- Use event-driven processing after uploads
- Use S3 as a static asset layer, not as a transactional database

---

## S3 Common Use Patterns

### Pattern 1: User File Upload
- Client requests pre-signed URL
- Client uploads directly to S3
- S3 triggers Lambda for processing
- Metadata stored in a database

### Pattern 2: Static Website Assets
- Frontend files in S3
- CloudFront in front for caching and HTTPS

### Pattern 3: Log Archival
- application logs or CloudTrail logs sent to S3
- lifecycle rules move old logs to Glacier

---

## S3 Common Pitfalls

- Accidentally making buckets public
- Using S3 as if it were a POSIX filesystem
- Forgetting lifecycle rules and causing storage cost growth
- Not enabling versioning for important buckets
- Deleting without retention or backup strategy
- Storing too much frequently changing metadata externally and not planning consistency

---

## S3 Interview Questions

### 1. What is S3 used for?
**Answer:**  
S3 is object storage used for files, backups, static assets, logs, archives, and data lake storage.

### 2. What is the difference between S3 and EBS?
**Answer:**  
S3 is object storage accessed via APIs. EBS is block storage attached to EC2 instances.

### 3. What is a pre-signed URL?
**Answer:**  
A time-limited URL that grants temporary access to upload or download a private S3 object.

### 4. What is versioning in S3?
**Answer:**  
It keeps multiple versions of an object, helping recover from accidental overwrites or deletions.

### 5. How do you secure an S3 bucket?
**Answer:**  
Enable Block Public Access, use IAM and bucket policies, enable encryption, restrict access by least privilege, and monitor access logs or CloudTrail data events.

### 6. What are lifecycle policies?
**Answer:**  
Rules that automatically transition objects to cheaper storage classes or delete them after a defined period.

### 7. When would you use S3 Intelligent-Tiering?
**Answer:**  
When access patterns are unpredictable and you want AWS to optimize storage costs automatically.

### 8. What is the difference between bucket policies and IAM policies?
**Answer:**  
IAM policies are attached to identities. Bucket policies are resource-based and attached to the bucket itself.

### 9. Why use S3 with CloudFront?
**Answer:**  
CloudFront caches content closer to users, reduces latency, improves global performance, and can reduce origin load.

### 10. How can S3 trigger downstream processing?
**Answer:**  
Using S3 event notifications to invoke Lambda or send messages to SQS or SNS.

### 11. What is S3 Object Lock?
**Answer:**  
A feature that prevents object deletion or modification for a retention period, useful for compliance and immutable backups.

### 12. How can EC2 instances access S3 privately?
**Answer:**  
Using an S3 VPC endpoint and IAM role permissions, avoiding public internet paths.

---

# Service 3: Amazon RDS

## What is RDS?

Amazon RDS is a managed relational database service.

Common engines:
- MySQL
- PostgreSQL
- MariaDB
- Oracle
- SQL Server
- Aurora (AWS-managed relational engine family)

Use RDS when:
- you need SQL
- you need transactions
- your data has strong relational structure
- joins and schema constraints matter
- operational simplicity matters

---

## When to Choose RDS

Choose RDS when you need:
- ACID transactions
- relational queries
- indexing
- referential integrity
- managed backups
- managed failover
- easier patching and maintenance

Avoid RDS when:
- access patterns are key-value at very high scale with flexible schema
- you need ultra-low-ops serverless event-scale NoSQL patterns
- your workload fits DynamoDB better

---

## Core RDS Concepts

### DB Instance
The compute and memory running your database engine.

### Storage
Backed by managed storage. Performance depends on chosen class and configuration.

### Automated Backups
Provide point-in-time recovery within the retention window.

### Snapshots
Manual backups kept until deleted.

### Multi-AZ
Synchronous standby in another AZ for failover and high availability.

### Read Replicas
Asynchronous copies for read scaling.

### Parameter Groups
Engine configuration settings.

### Option Groups
Extra engine-specific features.

### Security Groups
Control network access.

---

## Advanced RDS Concepts

### Multi-AZ vs Read Replicas

| Feature | Multi-AZ | Read Replica |
|---|---|---|
| Purpose | High availability | Read scaling |
| Replication | Synchronous | Asynchronous |
| Reads served | Primary typically | Replica can serve reads |
| Failover target | Yes | Usually not the same HA mechanism |

### RDS Proxy
Useful for:
- Lambda + RDS architectures
- connection pooling
- reducing connection storms
- improving application resilience during failover

### Encryption
RDS supports encryption at rest, often via KMS.

### Performance Insights
Useful for query performance analysis and bottleneck detection.

### Maintenance Windows
Used for patching and updates.

### Backups and Recovery
Always know:
- retention window
- restore process
- RPO
- RTO

### Storage Autoscaling
Can help when capacity usage grows unexpectedly.

---

## RDS Design Best Practices

- Use Multi-AZ for production HA
- Use read replicas when read-heavy
- Keep DB instances in private subnets
- Use security groups to restrict access
- Store secrets in Secrets Manager
- Use connection pooling or RDS Proxy
- Monitor CPU, memory, IOPS, latency, connections, replication lag
- Index carefully
- Tune queries before scaling vertically
- Test failover procedures

---

## RDS Common SDE Concerns

### Connection Exhaustion
A frequent issue when many app instances or Lambdas connect directly.

Solutions:
- RDS Proxy
- proper pooling
- limiting open connections

### Slow Queries
Scaling instance size helps only after query/index design is reviewed.

### Read Scaling
Use read replicas for:
- analytics reads
- reporting
- read-heavy APIs

### Write Scaling
Harder in relational systems.
Common strategies:
- optimize schema and indexes
- partition or shard at application level if necessary
- use caching
- move non-relational workloads elsewhere

---

## RDS Security Best Practices

- Private subnets only for production databases
- No public accessibility unless absolutely necessary
- Least-privilege DB credentials
- IAM authentication where suitable
- Encryption at rest and in transit
- Backup retention enabled
- Rotate credentials

---

## RDS Interview Questions

### 1. What is RDS?
**Answer:**  
A managed relational database service that automates setup, backups, patching, scaling support, and high-availability features.

### 2. When would you choose RDS over DynamoDB?
**Answer:**  
When you need SQL, joins, ACID transactions, complex relational queries, and strong schema relationships.

### 3. What is the difference between Multi-AZ and Read Replicas?
**Answer:**  
Multi-AZ improves availability with synchronous standby replication. Read replicas improve read scalability with asynchronous replication.

### 4. Why should production RDS instances usually be in private subnets?
**Answer:**  
To reduce attack surface and ensure access only from trusted application tiers or internal networks.

### 5. What problem does RDS Proxy solve?
**Answer:**  
It manages and pools database connections, which is especially useful for serverless or highly concurrent applications.

### 6. How do backups work in RDS?
**Answer:**  
RDS supports automated backups for point-in-time recovery and manual snapshots for long-term retention.

### 7. Can a read replica replace a Multi-AZ deployment?
**Answer:**  
No. A read replica is mainly for read scaling and may have replication lag. Multi-AZ is for high availability and failover.

### 8. What metrics would you monitor for RDS?
**Answer:**  
CPU, memory, free storage, read/write latency, IOPS, DB connections, replication lag, and query performance indicators.

### 9. Why can Lambda directly connecting to RDS be problematic?
**Answer:**  
Lambda can scale rapidly and create too many DB connections, exhausting database resources.

### 10. What is point-in-time recovery?
**Answer:**  
The ability to restore the database to a specific second within the configured backup retention period.

### 11. How do you scale reads in RDS?
**Answer:**  
By using read replicas, caching, query optimization, and proper indexing.

### 12. What are some reasons a database becomes slow even after scaling instance size?
**Answer:**  
Poor indexing, bad query plans, lock contention, connection overload, or application-level inefficiencies.

---

# Service 4: AWS Lambda

## What is Lambda?

AWS Lambda is serverless compute that runs code in response to events.

Use Lambda when:
- traffic is event-driven
- you want no server management
- workloads are short-lived
- scaling needs to be automatic
- you build APIs, automations, file processors, integrations, and async jobs

---

## Lambda Execution Model

Lambda runs code in an execution environment managed by AWS.

### Important Properties
- event-driven
- stateless by design
- billed based on usage
- automatic scaling
- max execution time is limited
- execution environment may be reused, but should not be relied on for durable state

### Common Event Sources
- API Gateway
- S3
- EventBridge
- SQS
- SNS
- DynamoDB Streams

---

## Core Lambda Concepts

### Handler
The entry point for your function.

### Runtime
Language environment such as Node.js, Python, Java, etc.

### Timeout
Maximum execution duration.

### Memory
Affects both memory allocation and CPU power.

### Ephemeral Storage
Temporary storage available during execution.

### Layers
Reusable code or dependencies shared across functions.

### Environment Variables
Used for configuration, but sensitive values should still be managed securely.

---

## Advanced Lambda Concepts

### Cold Start
Extra latency when AWS must initialize a new execution environment.

Factors affecting cold starts:
- runtime
- package size
- VPC configuration
- language ecosystem
- provisioned concurrency usage

### Concurrency
Number of simultaneous executions.

Types:
- unreserved
- reserved concurrency
- provisioned concurrency

### Synchronous vs Asynchronous Invocation
- Synchronous: caller waits for response
- Asynchronous: event queued and processed later

### Event Source Mapping
Used for sources like:
- SQS
- Kinesis
- DynamoDB Streams

### Retries and Failure Handling
Important features:
- dead-letter queues
- on-failure destinations
- idempotency
- partial batch failure handling

### Lambda in a VPC
Needed when Lambda must access private resources such as RDS in private subnets.

Trade-offs:
- added network complexity
- possible cold start impact
- need for proper subnet and security group configuration

### Idempotency
Critical because retries can happen.
Your handler should safely process duplicate events.

---

## Lambda Best Practices

- Keep functions small and single-purpose
- Design for idempotency
- Minimize package size
- Reuse SDK clients outside handler when possible
- Set realistic timeout and memory
- Use least-privilege IAM roles
- Use structured logging
- Use DLQs or destinations for failed async events
- Avoid putting heavy, long-running jobs into Lambda if they exceed serverless limits
- Use provisioned concurrency only when latency requirements justify cost

---

## Lambda Common Pitfalls

- Not handling retries safely
- Using Lambda for long-running batch jobs that fit containers or EC2 better
- Connecting directly to RDS without pooling strategy
- Shipping huge deployment packages
- Ignoring cold starts in latency-sensitive systems
- Putting too much business logic in one function
- Not setting alarms for errors and throttles

---

## Typical Lambda Architectures

### Pattern 1: Serverless API
- API Gateway
- Lambda
- DynamoDB
- CloudWatch logs and alarms

### Pattern 2: File Processing Pipeline
- User uploads file to S3
- S3 triggers Lambda
- Lambda validates/transforms
- metadata stored in DynamoDB or RDS

### Pattern 3: Queue-Based Background Work
- Producer sends jobs to SQS
- Lambda consumes queue
- retries handled by queue + DLQ strategy

---

## Lambda Interview Questions

### 1. What is Lambda best suited for?
**Answer:**  
Event-driven, short-lived, automatically scaling workloads such as APIs, stream processing, file handling, and background jobs.

### 2. What is a cold start?
**Answer:**  
The latency added when AWS creates and initializes a new execution environment before running the function.

### 3. Why is idempotency important in Lambda?
**Answer:**  
Because Lambda integrations may retry events, and the function should avoid producing duplicate side effects.

### 4. What happens if a Lambda function connected to SQS fails?
**Answer:**  
The message becomes visible again after the visibility timeout unless deleted; retries occur, and eventually the message can be moved to a DLQ depending on queue configuration.

### 5. When should you avoid Lambda?
**Answer:**  
For very long-running tasks, tightly stateful applications, workloads needing deep OS control, or cases where cost/performance favors containers or EC2.

### 6. What is reserved concurrency?
**Answer:**  
A setting that guarantees and limits concurrency for a function, helping isolate critical workloads and prevent noisy-neighbor behavior.

### 7. What is provisioned concurrency?
**Answer:**  
Pre-initialized execution environments kept ready to reduce cold start latency for predictable, latency-sensitive workloads.

### 8. Why can Lambda and RDS be a problematic combination?
**Answer:**  
Rapid Lambda scaling can create too many DB connections. RDS Proxy or other pooling mechanisms are often needed.

### 9. What is the difference between synchronous and asynchronous invocation?
**Answer:**  
Synchronous means the caller waits for a response. Asynchronous means the event is queued and processed later.

### 10. How do you monitor Lambda?
**Answer:**  
Use CloudWatch metrics such as invocations, errors, duration, concurrent executions, and throttles, plus logs and tracing.

### 11. Why might increasing memory improve Lambda performance?
**Answer:**  
Because CPU allocation scales with memory, so compute-heavy functions may run faster and even become cheaper if execution time drops enough.

### 12. How do you secure a Lambda function?
**Answer:**  
Use least-privilege IAM roles, encrypt sensitive values, restrict network access when using VPC, and avoid storing secrets in code.

---

# Service 5: Amazon DynamoDB

## What is DynamoDB?

Amazon DynamoDB is a fully managed NoSQL database designed for low-latency performance at scale.

Use DynamoDB when:
- access patterns are known
- you need very high scale
- latency must stay low
- schema flexibility is useful
- operational overhead must be minimal

---

## DynamoDB Mental Model

DynamoDB is not designed like a traditional relational database.

Instead of tables + joins first, you think in terms of:
- access patterns
- partition key design
- item collections
- indexes
- denormalized models

This is one of the most important advanced interview topics.

---

## Core Concepts

### Table
Collection of items.

### Item
Equivalent to a row, but attributes can vary.

### Partition Key
Determines how data is distributed.

### Sort Key
Allows ordering and grouped access within the same partition key.

### Primary Key Types
- Simple primary key: partition key only
- Composite primary key: partition key + sort key

### Query vs Scan
- **Query**: efficient, based on key access
- **Scan**: reads every item and is expensive

### Capacity Modes
- On-demand
- Provisioned

### Consistency
- Eventually consistent reads
- Strongly consistent reads for supported patterns on base tables and LSIs, but not GSIs

---

## Advanced DynamoDB Concepts

### Access Pattern First Design
Before creating a table, ask:
- How will the application read data?
- What are the lookup keys?
- What ranges or filters matter?
- What relationships must be represented?

### Single-Table Design
Advanced DynamoDB often uses one table for multiple entity types.

Benefits:
- fewer joins
- optimized access patterns
- efficient one-query retrieval for related entities

Trade-off:
- more design complexity

### Secondary Indexes

#### GSI
Global Secondary Index
- different partition/sort keys
- supports new access patterns
- eventually consistent reads

#### LSI
Local Secondary Index
- same partition key as base table
- different sort key
- more limited and defined at table creation

### Hot Partitions
If too much traffic goes to one partition key, performance can degrade.

Mitigations:
- improve partition key cardinality
- write sharding
- random suffixes
- time bucketing
- workload redesign

### Streams
Capture item-level changes for event-driven processing.

### TTL
Time To Live automatically expires items.

### Transactions
DynamoDB supports transactional operations when needed, though with added cost and complexity.

### DAX
DynamoDB Accelerator can reduce read latency for some workloads.

---

## DynamoDB Design Best Practices

- Model around access patterns, not normalization
- Avoid scans in hot paths
- Choose high-cardinality partition keys
- Use sort keys for range queries and grouping
- Add GSIs only when needed
- Monitor throttling and hot keys
- Use TTL for ephemeral data
- Use Streams for change-driven pipelines
- Keep item size small and predictable
- Use conditional writes for optimistic concurrency

---

## DynamoDB Common Use Cases

### Pattern 1: User Session Store
- key-value access
- high throughput
- TTL cleanup

### Pattern 2: Shopping Cart
- partition by user/cart ID
- sort key for item grouping
- low-latency lookups

### Pattern 3: Event / Activity Feed
- partition by entity
- sort key by timestamp
- query recent items efficiently

### Pattern 4: Idempotency Store
- keep processed request IDs
- prevent duplicate processing in distributed systems

---

## DynamoDB Common Pitfalls

- Designing schema like SQL tables
- Using Scan for production traffic
- Choosing low-cardinality partition keys
- Adding too many GSIs without cost awareness
- Ignoring hot key patterns
- Not modeling for exact query requirements
- Assuming joins exist in the same way as relational systems

---

## DynamoDB Interview Questions

### 1. When would you choose DynamoDB over RDS?
**Answer:**  
When you need highly scalable, low-latency NoSQL access with known access patterns and minimal operational overhead.

### 2. What is the difference between Query and Scan?
**Answer:**  
Query uses keys and is efficient. Scan reads the entire table and is expensive and slow for large datasets.

### 3. Why is partition key design important?
**Answer:**  
Because it affects data distribution and throughput. Poor partition keys can cause hot partitions and throttling.

### 4. What is a GSI?
**Answer:**  
A Global Secondary Index provides an alternate key structure to support additional query patterns.

### 5. What is a hot partition?
**Answer:**  
A partition receiving disproportionate traffic due to skewed key usage, which can limit performance.

### 6. What does single-table design mean?
**Answer:**  
Modeling multiple related entity types in one table to optimize access patterns and reduce query round trips.

### 7. What consistency options does DynamoDB provide?
**Answer:**  
Eventually consistent reads by default, and strongly consistent reads for certain operations on the base table.

### 8. What is DynamoDB Streams used for?
**Answer:**  
Capturing item changes so downstream systems can react, such as triggering Lambda functions.

### 9. Why are scans discouraged in production?
**Answer:**  
They consume high read capacity, are slow on large tables, and do not scale well for latency-sensitive paths.

### 10. What is TTL in DynamoDB?
**Answer:**  
A feature that automatically removes expired items after a configured timestamp attribute.

### 11. How do you prevent duplicate writes in DynamoDB?
**Answer:**  
Use conditional writes, transactions when needed, or an idempotency key pattern.

### 12. What are the trade-offs of single-table design?
**Answer:**  
It improves performance for known access patterns but increases modeling complexity and requires careful schema planning.

### 13. Why can a GSI increase cost?
**Answer:**  
Because writes to the base table may also write to the index, and the index consumes its own storage and throughput resources.

---

# Service 6: AWS IAM

## What is IAM?

AWS Identity and Access Management controls who can do what in AWS.

This is one of the most important services in both interviews and real systems because every service interaction depends on permissions.

---

## Core IAM Concepts

### Principal
The entity making a request:
- user
- role
- federated identity
- AWS service

### Authentication
Who are you?

### Authorization
What are you allowed to do?

### IAM User
Long-term identity, usually for a human or legacy use case.

### IAM Role
Assumable identity with temporary credentials.
Preferred for:
- EC2
- Lambda
- cross-account access
- applications
- federated users

### Policy
JSON document defining permissions.

### Resource-Based Policy
Policy attached directly to a resource, such as:
- S3 bucket policy
- Lambda resource policy

### Trust Policy
Defines who can assume a role.

---

## IAM Policy Evaluation Logic

This is advanced and interview-relevant.

### Basic Rules
1. Start with implicit deny
2. An explicit allow grants access
3. An explicit deny overrides any allow

### Important Boundaries
Effective permissions may be limited by:
- identity-based policy
- resource-based policy
- session policy
- permission boundary
- Service Control Policy (SCP) in AWS Organizations

### Interview Gold Point
Even if an IAM policy allows an action, access can still fail if:
- there is an explicit deny
- the resource policy blocks it
- an SCP blocks it
- the trust relationship for role assumption is wrong

---

## Advanced IAM Concepts

### STS
Security Token Service issues temporary credentials.

### AssumeRole
Used for:
- cross-account access
- service roles
- delegation
- CI/CD pipelines

### Permission Boundaries
Maximum permission boundary for an IAM principal.

### SCPs
Used at the AWS Organizations level to restrict what accounts can do.

### ABAC
Attribute-Based Access Control uses tags to drive permissions.

### Federation
Allows identity from external providers:
- SAML
- OIDC
- enterprise identity systems

### MFA
Multi-factor authentication for stronger security.

### IAM Roles for Services
Examples:
- EC2 instance profile role
- Lambda execution role

---

## IAM Best Practices

- Prefer roles over long-term access keys
- Enforce least privilege
- Enable MFA for human users
- Use federation/SSO instead of creating many IAM users
- Rotate and eliminate unused credentials
- Use access analyzer and policy validation tools
- Separate trust policy from permission policy understanding
- Grant resource access only where needed
- Log all API actions with CloudTrail
- Avoid wildcard permissions unless truly necessary

---

## IAM Common Pitfalls

- Using `AdministratorAccess` unnecessarily
- Hardcoding AWS keys in source code or AMIs
- Confusing trust policy with permission policy
- Forgetting that explicit deny overrides allow
- Giving users direct permissions instead of role-based access
- Not restricting role assumption
- Broad `s3:*` or `*:*` access in production

---

## IAM Real-World Patterns

### Pattern 1: EC2 Accessing S3
- Attach role to EC2
- grant only required S3 actions on specific bucket/prefix

### Pattern 2: Lambda Writing to DynamoDB
- Lambda execution role allows only:
  - `PutItem`
  - `UpdateItem`
  - `GetItem`
  on the target table

### Pattern 3: Cross-Account Deployment
- CI/CD account assumes a role in target account
- trust policy in target account allows assumption
- permissions policy grants deployment actions

### Pattern 4: Fine-Grained S3 Access
- use bucket policy + IAM conditions
- restrict prefixes or tags

---

## IAM Interview Questions

### 1. What is the difference between an IAM user and an IAM role?
**Answer:**  
A user is a long-term identity with credentials. A role is assumed temporarily and provides short-lived credentials.

### 2. Why are IAM roles preferred over access keys on EC2?
**Answer:**  
Roles provide temporary credentials automatically, avoid hardcoded secrets, and are easier to rotate and audit.

### 3. What is least privilege?
**Answer:**  
Granting only the minimum permissions required to perform a task and nothing more.

### 4. What is the difference between a trust policy and a permissions policy?
**Answer:**  
The trust policy defines who can assume the role. The permissions policy defines what the role can do after assumption.

### 5. What is an explicit deny?
**Answer:**  
A deny statement that overrides any allow, even if another policy grants access.

### 6. What is STS used for?
**Answer:**  
To issue temporary security credentials, commonly used in role assumption and federated access.

### 7. What is a Service Control Policy?
**Answer:**  
An organization-level policy that sets the maximum available permissions for accounts in AWS Organizations.

### 8. What is a resource-based policy?
**Answer:**  
A policy attached to a resource rather than an identity, such as an S3 bucket policy.

### 9. How does cross-account access usually work?
**Answer:**  
A principal in one account assumes a role in another account, subject to trust policy and permissions policy rules.

### 10. What is ABAC?
**Answer:**  
Attribute-Based Access Control, where tags and attributes are used to define authorization rules.

### 11. Why should human access usually use federation/SSO instead of many IAM users?
**Answer:**  
It centralizes identity management, improves security, simplifies onboarding/offboarding, and reduces long-term credential usage.

### 12. How do you debug an IAM permission issue?
**Answer:**  
Check the identity policy, resource policy, trust policy if assuming a role, explicit denies, SCPs, permission boundaries, and CloudTrail logs.

### 13. What is the blast radius in IAM terms?
**Answer:**  
The maximum damage possible if a credential or principal is compromised. Least privilege reduces blast radius.

---

# Cross-Service Architecture Patterns for SDEs

This section goes beyond isolated services and shows how real AWS systems are built.

## Pattern 1: Highly Available Web Application

### Architecture
- Route 53
- ALB
- EC2 Auto Scaling Group across multiple AZs
- RDS Multi-AZ
- S3 for static assets
- IAM roles for EC2
- CloudWatch alarms and logs

### Why It Works
- horizontal scaling at app tier
- resilient database failover
- stateless web tier
- static asset offloading

### Interview Talking Points
- session storage externalized
- health checks
- private DB access only
- autoscaling thresholds
- backup and recovery plan

---

## Pattern 2: Serverless REST API

### Architecture
- API Gateway
- Lambda
- DynamoDB
- IAM
- CloudWatch
- S3 for file storage if needed

### Why It Works
- no server management
- scales with traffic
- low ops overhead
- ideal for bursty workloads

### Interview Talking Points
- idempotency
- retries
- throttling
- request validation
- cold start trade-offs

---

## Pattern 3: Secure File Upload and Processing

### Architecture
- frontend requests pre-signed URL
- client uploads file directly to S3
- S3 event triggers Lambda
- Lambda validates/transforms
- metadata stored in DynamoDB or RDS
- IAM controls all access

### Why It Works
- app server does not handle large uploads directly
- scalable and cost-efficient
- async processing

### Interview Talking Points
- pre-signed URL expiration
- content validation
- virus scanning pattern if needed
- event duplication handling
- dead-letter strategy

---

## Pattern 4: Read-Heavy Application

### Architecture
- EC2 or Lambda application tier
- RDS primary
- read replicas for read scaling
- S3 for static assets
- CloudWatch monitoring

### Why It Works
- transactional writes stay on primary
- heavy read traffic is offloaded

### Interview Talking Points
- replication lag
- read/write split in app
- caching strategy if needed
- failover behavior

---

## Pattern 5: Event-Driven Processing Pipeline

### Architecture
- application writes data to DynamoDB or S3
- change events trigger Lambda
- downstream enrichment or notification
- logs and alarms in CloudWatch

### Why It Works
- loose coupling
- reactive design
- easy scaling

### Interview Talking Points
- at-least-once delivery assumptions
- idempotency
- ordering requirements
- backpressure and failure handling

---

## Pattern 6: Cross-Account Deployment Model

### Architecture
- CI/CD pipeline in central account
- assumes IAM role in application account
- deploys EC2/Lambda/RDS infrastructure or code
- CloudTrail logs activity

### Why It Works
- separation of duties
- centralized deployment control
- better governance

### Interview Talking Points
- trust policy
- least privilege
- audit trails
- environment isolation

---

# Common AWS Mistakes in Interviews and Real Projects

## 1. Choosing a Service by Popularity Instead of Workload
Bad answer:
- "Use Lambda because serverless is modern."

Better answer:
- "Use Lambda because the workload is event-driven, bursty, and short-lived; otherwise EC2 may be a better fit."

---

## 2. Ignoring Security
Always mention:
- IAM roles
- encryption
- private networking where appropriate
- least privilege
- logging and audit

---

## 3. Ignoring Failure Modes
Interviewers like:
- what happens on AZ failure?
- what if Lambda retries?
- what if a DB connection pool is exhausted?
- what if uploads are duplicated?

---

## 4. Not Talking About Cost
Even in technical interviews, cost-aware design is a sign of maturity.

Examples:
- S3 lifecycle rules
- Spot for workers
- avoid overprovisioning
- choose on-demand vs provisioned intelligently

---

## 5. Using RDS for Everything or DynamoDB for Everything
Strong engineers explain trade-offs:
- relational integrity and SQL -> RDS
- massive scale, simple key access -> DynamoDB

---

## 6. Ignoring Operational Simplicity
Managed services often win because:
- less patching
- easier backups
- integrated monitoring
- faster development

---

## 7. Forgetting Observability
Every design should mention:
- metrics
- logs
- alarms
- tracing if distributed

---

# Rapid Revision Cheat Sheet

## AWS Core Concepts

| Topic | Key Point |
|---|---|
| Region | Geographic deployment boundary |
| AZ | Isolated failure domain inside a Region |
| VPC | Isolated network in AWS |
| Public subnet | Has route to Internet Gateway |
| Private subnet | No direct public internet route |
| Security Group | Stateful instance-level firewall |
| NACL | Stateless subnet-level firewall |
| IAM role | Temporary credentials for workloads |
| CloudTrail | API audit logs |
| CloudWatch | Metrics, logs, alarms |

---

## Service Selection Cheat Sheet

| Use Case | Best Fit |
|---|---|
| Full server control, custom runtime, long-running app | EC2 |
| Static files, logs, backups, archival | S3 |
| SQL database, transactions, joins | RDS |
| Event-driven short-lived compute | Lambda |
| High-scale NoSQL key-value/document access | DynamoDB |
| Authentication/authorization for AWS resources | IAM |

---

## High-Value Interview Comparisons

### EC2 vs Lambda
- EC2: more control, more ops
- Lambda: less ops, execution limits, event-driven

### S3 vs EBS
- S3: object storage
- EBS: block storage attached to EC2

### RDS vs DynamoDB
- RDS: relational, SQL, joins, transactions
- DynamoDB: NoSQL, low-latency scale, access-pattern-first design

### Multi-AZ vs Read Replica
- Multi-AZ: HA/failover
- Read Replica: read scaling

### IAM User vs Role
- User: long-term identity
- Role: temporary assumed identity

---

## Must-Say Best Practices in Interviews

- least privilege
- Multi-AZ for production
- private subnets for databases
- encryption at rest and in transit
- autoscaling where possible
- monitoring and alarms
- idempotency in event-driven systems
- backups and disaster recovery strategy
- cost-awareness

---

# Advanced Scenario-Based Interview Questions

## 1. Design an image upload service for millions of users
### Strong Answer Outline
- Store images in S3
- Use pre-signed URLs for direct uploads
- Trigger Lambda on upload for resizing/validation
- Store metadata in DynamoDB or RDS depending on query needs
- Use IAM least privilege
- Add CloudWatch alarms and S3 lifecycle where needed
- Consider CloudFront for global delivery

### Follow-Up Topics
- duplicate uploads
- large file multipart upload
- content moderation
- metadata search
- regional replication

---

## 2. Build a highly available web application with a relational database
### Strong Answer Outline
- ALB in front
- EC2 Auto Scaling Group across multiple AZs
- RDS Multi-AZ in private subnets
- S3 for static assets and backups
- IAM roles for instances
- CloudWatch for alarms
- externalize sessions

### Follow-Up Topics
- failover testing
- read replicas
- schema migrations
- zero-downtime deployments

---

## 3. Your Lambda-based API is timing out under load
### Strong Answer Outline
- inspect CloudWatch metrics and logs
- determine if issue is cold starts, downstream latency, or throttling
- increase memory if CPU-bound
- review timeout setting
- optimize package size
- check database connection behavior
- use RDS Proxy if needed
- consider moving long-running workloads to async processing

---

## 4. Your DynamoDB table is getting throttled
### Strong Answer Outline
- inspect key distribution
- identify hot partition or hot key
- review access patterns
- increase capacity or use on-demand if appropriate
- redesign partition key if skewed
- add caching or write sharding if needed
- remove scans from hot path

---

## 5. A developer says, "My IAM policy allows S3 access, but it still fails."
### Strong Answer Outline
Check:
- explicit denies
- bucket policy
- role trust relationship if role assumption is involved
- SCPs
- permission boundary
- KMS permissions if encrypted data is involved
- object path mismatch
- region/account confusion

---

## 6. Your RDS database is healthy, but application latency is still high
### Strong Answer Outline
- inspect slow queries
- check indexes
- review connection pooling
- inspect lock contention
- monitor replication lag if reading from replicas
- check app-side retries and network path
- evaluate whether static content or heavy reads should be offloaded

---

# Final Interview Strategy

## How to Answer AWS Questions Like a Strong SDE

Use this structure:

### 1. Clarify Requirements
Ask:
- traffic pattern?
- latency target?
- data model?
- consistency needs?
- budget sensitivity?
- RTO/RPO?
- public or internal system?

### 2. Choose the Core Service
Pick the primary compute, storage, and database service.

### 3. Add Reliability
Mention:
- Multi-AZ
- retries
- health checks
- backups
- failover

### 4. Add Security
Mention:
- IAM roles
- encryption
- private networking
- least privilege
- audit logging

### 5. Add Observability
Mention:
- metrics
- logs
- alarms
- dashboards
- tracing

### 6. Add Cost and Trade-Offs
Mention:
- managed vs self-managed
- scaling model
- storage class choice
- on-demand vs reserved/spot
- overengineering vs simplicity

---

# One-Page Summary

## The 6 Most Important AWS Services in This Guide

### 1. EC2
Use when you need full server control, custom runtimes, long-running apps, or specialized compute.

### 2. S3
Use for object storage, static content, backups, archives, and file pipelines.

### 3. RDS
Use for relational data, SQL, transactions, and managed database operations.

### 4. Lambda
Use for event-driven, short-lived, serverless compute that scales automatically.

### 5. DynamoDB
Use for high-scale, low-latency NoSQL workloads designed around access patterns.

### 6. IAM
Use for identity, authorization, least privilege, and secure access across AWS.

---

# What Makes an Answer "Advanced"

An advanced AWS answer does not just name a service. It explains:

- why that service fits the workload
- how it scales
- how it fails
- how it is secured
- how it is monitored
- what it costs
- what trade-offs it introduces

If you can discuss AWS with that level of reasoning, you are already giving SDE-level answers rather than beginner cloud answers.

---
