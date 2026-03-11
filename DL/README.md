# 🧠 Deep Learning: The Complete Guide
> A comprehensive, beginner-to-advanced guide covering every core concept of Deep Learning — from neurons to neural networks, perceptrons to gradient descent, with real Python code examples.

---

## 📚 Table of Contents

1. [What is Deep Learning?](#1-what-is-deep-learning)
2. [AI vs Machine Learning vs Deep Learning](#2-ai-vs-machine-learning-vs-deep-learning)
3. [Factors Behind Deep Learning](#3-factors-behind-deep-learning)
4. [Neural Networks](#4-neural-networks)
5. [Types of Neural Networks](#5-types-of-neural-networks)
6. [History of Deep Learning](#6-history-of-deep-learning)
7. [Applications of Deep Learning](#7-applications-of-deep-learning)
8. [What is a Perceptron?](#8-what-is-a-perceptron)
9. [Neuron vs Perceptron](#9-neuron-vs-perceptron)
10. [Geometric Intuition](#10-geometric-intuition)
11. [Code Example — Python & Scikit-Learn](#11-code-example--python--scikit-learn)
12. [The Perceptron Trick](#12-the-perceptron-trick)
    - [How to Label Regions](#121-how-to-label-regions)
    - [Transformations](#122-transformations)
    - [Coding the Algorithm](#123-coding-the-algorithm)
    - [Problem with the Perceptron Trick](#124-problem-with-the-perceptron-trick)
    - [Loss Functions](#125-loss-functions)
    - [Perceptron Loss Function](#126-perceptron-loss-function)
    - [Scikit-Learn Docs Reference](#127-scikit-learn-docs-reference)
    - [Explanation of Loss Functions](#128-explanation-of-loss-functions)
    - [Gradient Descent](#129-gradient-descent)
    - [Code Demo](#1210-code-demo)
13. [Next Up: MLP (Multilayer Perceptron)](#13-next-up-mlp--multilayer-perceptron)

---

# 1. What is Deep Learning?

**Deep Learning (DL)** is a subfield of Machine Learning that uses **artificial neural networks** with many layers (hence "deep") to learn representations of data with multiple levels of abstraction.

Rather than hand-engineering features, deep learning models automatically discover the features needed for classification, detection, or generation directly from raw data — images, text, audio, or video.

```
Raw Data  →  [Layer 1: Edges]  →  [Layer 2: Shapes]  →  [Layer 3: Objects]  →  Output
```

### 🔑 Key Characteristics

| Property | Description |
|---|---|
| **Automatic Feature Extraction** | No manual feature engineering required |
| **Depth** | Multiple hidden layers learn hierarchical representations |
| **Scale** | Performs better with more data and more compute |
| **End-to-End Learning** | Input goes in, output comes out — the model learns everything in between |
| **Versatility** | Same architecture adapts to vision, language, audio, and more |

### 💡 Simple Analogy

> Think of deep learning like teaching a child to recognise a cat. You don't give them a rulebook of features — you show them thousands of cats and they learn the concept automatically. Deep learning does the same thing with layered mathematical transformations.

### 📌 Formal Definition

Given input **X** and output **Y**, deep learning learns a function:

```
f(X) = Y
```

through a composition of many non-linear transformations across multiple layers:

```
Y = fₙ( fₙ₋₁( ... f₂( f₁(X) ) ... ) )
```

Each `fᵢ` is a layer that applies weights, biases, and an activation function.

---

# 2. AI vs Machine Learning vs Deep Learning

These three terms are often used interchangeably — but they are **not the same thing**. They exist in a hierarchical relationship.

### 🗂️ The Hierarchy

```
┌─────────────────────────────────────────────────────────┐
│                  ARTIFICIAL INTELLIGENCE                 │
│   (Any technique that enables machines to mimic human   │
│    intelligence — rule-based systems, search, logic)    │
│                                                         │
│   ┌─────────────────────────────────────────────────┐   │
│   │             MACHINE LEARNING                    │   │
│   │  (Systems that learn from data without being   │   │
│   │   explicitly programmed — SVM, trees, etc.)    │   │
│   │                                                 │   │
│   │   ┌───────────────────────────────────────┐    │   │
│   │   │          DEEP LEARNING                │    │   │
│   │   │  (ML using multi-layer neural nets    │    │   │
│   │   │   to learn hierarchical features)     │    │   │
│   │   └───────────────────────────────────────┘    │   │
│   └─────────────────────────────────────────────────┘   │
└─────────────────────────────────────────────────────────┘
```

### 📊 Comparison Table

| Dimension | Artificial Intelligence | Machine Learning | Deep Learning |
|---|---|---|---|
| **Definition** | Machines simulating human intelligence | Systems learning from data | Neural networks with many layers |
| **Approach** | Rules, logic, search | Statistical models | Representation learning |
| **Feature Engineering** | Manual | Manual/Semi-auto | Automatic |
| **Data Requirement** | Low | Medium | Very High |
| **Compute Requirement** | Low | Medium | Very High |
| **Examples** | Chess engines, chatbots | Linear Regression, SVM, Decision Trees | CNNs, RNNs, Transformers |
| **Performance with More Data** | Plateaus | Improves moderately | Improves dramatically |
| **Interpretability** | High | Medium | Low (black box) |

### 📈 Performance vs Data Volume

```
Performance
     │
High │                                   ●  Deep Learning
     │                             ●
     │                        ●
     │              ●  Machine Learning
     │         ●●●●
     │   ●●  AI
Low  └──────────────────────────────────────────
              Less Data          More Data
```

> **Key Insight**: Deep Learning shines when you have massive datasets. With small data, classical ML often wins.

---

# 3. Factors Behind Deep Learning

Deep Learning has become dominant in the 2010s–2020s due to the convergence of three critical factors:

```
        Big Data
           ●
          / \
         /   \
        /     \
       ●───────●
  Compute    Algorithms
  (GPUs)    (Better Architectures)
```

### 🗂️ Factor 1 — Big Data

The explosion of the internet, smartphones, sensors, and social media created **unprecedented volumes of labelled data**:

- ImageNet: 14 million labelled images
- Common Crawl: petabytes of web text
- YouTube: 500 hours of video uploaded every minute

Deep networks need vast amounts of data to generalise. More data = better performance.

### ⚡ Factor 2 — Computational Power (GPUs & TPUs)

| Hardware | Role |
|---|---|
| **GPU (Graphics Processing Unit)** | Massively parallel matrix operations — the core of neural network training |
| **TPU (Tensor Processing Unit)** | Google's custom chip designed specifically for TensorFlow operations |
| **Cloud Computing** | AWS, GCP, Azure made GPU clusters accessible to everyone |

Training a modern language model on a CPU would take years. On a cluster of GPUs — days.

### 🧮 Factor 3 — Algorithmic Advances

Several breakthroughs unlocked the potential of deep networks:

| Innovation | Impact |
|---|---|
| **ReLU Activation** | Solved the vanishing gradient problem in deep networks |
| **Dropout** | Regularisation technique that prevents overfitting |
| **Batch Normalisation** | Stabilised and accelerated training |
| **Adam Optimiser** | Adaptive learning rates for faster convergence |
| **Residual Networks (ResNets)** | Skip connections enabling 100+ layer networks |
| **Attention Mechanism** | Foundation of modern Transformers and LLMs |

### 📦 Factor 4 — Open Source Ecosystem

| Tool | Role |
|---|---|
| **TensorFlow** | Google's production-grade DL framework |
| **PyTorch** | Facebook's research-friendly dynamic graph framework |
| **Keras** | High-level API for rapid prototyping |
| **Hugging Face** | Pre-trained model hub (BERT, GPT, etc.) |
| **CUDA** | NVIDIA's parallel computing platform for GPUs |

---

# 4. Neural Networks

A **Neural Network** is a computational system loosely inspired by the human brain. It is composed of interconnected **nodes (neurons)** organised in **layers** that transform input data into output predictions.

### 🧱 Structure of a Neural Network

```
     INPUT LAYER      HIDDEN LAYER(S)       OUTPUT LAYER
     ┌─────────┐      ┌─────────────┐       ┌──────────┐
     │  x₁ ●──┼──────┼──→ ● ──────┼───────┼──→ ●  ŷ  │
     │         │      │    ●        │       │          │
     │  x₂ ●──┼──────┼──→ ● ──────┼───────┤          │
     │         │      │    ●        │       │          │
     │  x₃ ●──┼──────┼──→ ● ──────┼───────┘          │
     └─────────┘      └─────────────┘                  
```

### 🔢 Layers Explained

| Layer | Role |
|---|---|
| **Input Layer** | Receives raw features (pixels, words, numbers) |
| **Hidden Layer(s)** | Learns abstract representations through weighted transformations |
| **Output Layer** | Produces final prediction (class probability, number, token) |

### ⚙️ How a Single Neuron Works

```
Inputs        Weights           Bias
  x₁ ──── w₁ ─┐
  x₂ ──── w₂ ─┼──→  Σ(wᵢxᵢ + b)  ──→  Activation f()  ──→  Output
  x₃ ──── w₃ ─┘
```

**Step 1 — Weighted Sum:**
```
z = w₁x₁ + w₂x₂ + w₃x₃ + b
```

**Step 2 — Activation:**
```
output = f(z)
```

Where `f` is a non-linear activation function (ReLU, Sigmoid, Tanh, etc.)

### 🔥 Common Activation Functions

| Function | Formula | Use Case |
|---|---|---|
| **Sigmoid** | `1 / (1 + e⁻ˣ)` | Binary classification output |
| **Tanh** | `(eˣ - e⁻ˣ) / (eˣ + e⁻ˣ)` | Hidden layers (zero-centered) |
| **ReLU** | `max(0, x)` | Default hidden layer activation |
| **Leaky ReLU** | `max(0.01x, x)` | Fixes dying ReLU problem |
| **Softmax** | `eˣᵢ / Σeˣⱼ` | Multi-class classification output |

```
Sigmoid          ReLU             Tanh
   1 ┤  ────      │  /             1 ┤  ────
     │ /          │ /                │ /
 0.5 ┤/           │/           0    ┤
     │            └────        -1   ┤────/
   0 └────
```

### 🔁 Forward & Backward Pass

```
FORWARD PASS  →  Compute predictions layer by layer
LOSS          →  Measure how wrong the prediction is
BACKWARD PASS →  Compute gradients (how much each weight contributed to the error)
UPDATE        →  Adjust weights using gradient descent
```

This cycle repeats for every **batch** of training data across many **epochs**.

---

# 5. Types of Neural Networks

```
Neural Networks
├── Feedforward Neural Network (FNN / MLP)
├── Convolutional Neural Network (CNN)
├── Recurrent Neural Network (RNN)
│   ├── LSTM
│   └── GRU
├── Transformer
├── Autoencoder
├── Generative Adversarial Network (GAN)
├── Graph Neural Network (GNN)
└── Diffusion Models
```

### 1️⃣ Feedforward Neural Network (FNN / MLP)

- Information flows **in one direction**: input → hidden → output
- No cycles or feedback loops
- Used for: tabular data, classification, regression

### 2️⃣ Convolutional Neural Network (CNN)

```
Image → [Conv Layer] → [Pooling] → [Conv Layer] → [Pooling] → [FC Layer] → Class
```

- Uses **convolutional filters** to detect local spatial patterns
- Parameter sharing makes them efficient on image data
- Used for: image classification, object detection, medical imaging

### 3️⃣ Recurrent Neural Network (RNN)

```
x₁ → [RNN] → h₁
x₂ → [RNN] → h₂   (h₁ fed back in)
x₃ → [RNN] → h₃   (h₂ fed back in)
```

- Maintains a **hidden state** across time steps — has memory
- Suffers from vanishing gradients on long sequences
- Used for: time series, basic NLP

### 4️⃣ LSTM & GRU (Gated RNNs)

- **Long Short-Term Memory (LSTM)**: uses gates (forget, input, output) to control memory
- **Gated Recurrent Unit (GRU)**: simplified version of LSTM, fewer parameters
- Used for: language modelling, speech recognition, machine translation

### 5️⃣ Transformer

```
Input → [Embedding] → [Multi-Head Attention] → [Feed Forward] → Output
```

- Replaces recurrence with **self-attention** — processes all tokens in parallel
- Foundation of GPT, BERT, T5, LLaMA, and all modern LLMs
- Used for: NLP, code generation, image generation (Vision Transformers)

### 6️⃣ Autoencoder

```
Input → [Encoder] → Latent Space → [Decoder] → Reconstructed Output
```

- Learns a **compressed representation** of data (dimensionality reduction)
- Used for: anomaly detection, denoising, compression

### 7️⃣ Generative Adversarial Network (GAN)

```
Random Noise → [Generator] → Fake Image ──┐
                                           ├──→ [Discriminator] → Real / Fake?
Real Images ───────────────────────────────┘
```

- Two networks compete: Generator creates fakes, Discriminator detects them
- Used for: image synthesis, deepfakes, data augmentation, style transfer

### 8️⃣ Graph Neural Network (GNN)

- Operates on **graph-structured data** (nodes and edges)
- Used for: social network analysis, drug discovery, recommendation systems

### 9️⃣ Diffusion Models

- Learn to **reverse a noise process** to generate data
- State-of-the-art for image, audio, and video generation
- Used for: Stable Diffusion, DALL-E, Sora

### 📊 Quick Reference

| Network | Best For | Key Feature |
|---|---|---|
| FNN/MLP | Tabular data | Simplicity |
| CNN | Images, Video | Spatial feature extraction |
| RNN | Sequences | Temporal memory |
| LSTM/GRU | Long sequences | Gated memory |
| Transformer | NLP, Vision | Self-attention |
| Autoencoder | Compression | Latent representation |
| GAN | Generation | Adversarial training |
| GNN | Graphs | Node/edge learning |
| Diffusion | Image/Video gen | Noise reversal |

---

# 6. History of Deep Learning

```
Timeline of Deep Learning
══════════════════════════════════════════════════════════════════

1943  ── McCulloch & Pitts           First mathematical neuron model
1958  ── Frank Rosenblatt            Perceptron invented
1969  ── Minsky & Papert             "Perceptrons" book — XOR problem
         ↓ (AI Winter 1)
1986  ── Rumelhart, Hinton, Williams Backpropagation popularised
1989  ── Yann LeCun                  CNNs applied to digit recognition
1997  ── Sepp Hochreiter             LSTM invented
         ↓ (AI Winter 2)
2006  ── Geoffrey Hinton             Deep Belief Networks — DL renaissance
2009  ── Fei-Fei Li                  ImageNet dataset released
2012  ── Krizhevsky, Hinton          AlexNet wins ImageNet — CNN dominance begins
2014  ── Goodfellow et al.           GANs introduced
2015  ── He et al.                   ResNets — 152-layer networks
2017  ── Vaswani et al.              "Attention Is All You Need" — Transformers
2018  ── Google AI                   BERT — bidirectional transformers
2019  ── OpenAI                      GPT-2
2020  ── OpenAI                      GPT-3 — 175B parameters
2021  ── OpenAI / CLIP               Multimodal models
2022  ── Stability AI / OpenAI       Stable Diffusion, ChatGPT
2023  ── OpenAI / Google / Meta      GPT-4, Gemini, LLaMA
2024+ ── Industry Wide               Multimodal, Agents, On-device AI

══════════════════════════════════════════════════════════════════
```

### 🧊 The Two AI Winters

**First AI Winter (1969–1986)**: Minsky and Papert proved Perceptrons could not solve non-linearly separable problems (XOR). Funding dried up. Research stalled.

**Second AI Winter (1987–2005)**: Despite backpropagation, networks were too slow to train on available hardware. Support Vector Machines dominated ML.

### 🌅 The Deep Learning Renaissance (2006–present)

Hinton's 2006 paper on Deep Belief Networks reignited interest. Then in 2012, **AlexNet** — trained on GPUs — shattered the ImageNet record by a wide margin. The modern deep learning era had begun.

---

# 7. Applications of Deep Learning

Deep Learning has transformed nearly every field of technology and science.

### 👁️ Computer Vision

| Application | Example |
|---|---|
| Image Classification | "Is this a cat or a dog?" |
| Object Detection | Self-driving car detecting pedestrians |
| Face Recognition | iPhone Face ID, surveillance systems |
| Medical Imaging | Detecting tumours in X-rays or MRIs |
| Optical Character Recognition | Scanning documents to text |
| Image Generation | DALL-E, Midjourney, Stable Diffusion |

### 🗣️ Natural Language Processing

| Application | Example |
|---|---|
| Machine Translation | Google Translate, DeepL |
| Sentiment Analysis | Analysing product reviews |
| Chatbots & Assistants | ChatGPT, Gemini, Claude |
| Text Summarisation | TL;DR tools, news summarisers |
| Code Generation | GitHub Copilot, Cursor |
| Question Answering | Search engines, RAG systems |

### 🎵 Audio & Speech

| Application | Example |
|---|---|
| Speech Recognition | Siri, Alexa, Google Assistant |
| Text-to-Speech | ElevenLabs, OpenAI TTS |
| Music Generation | Suno, Udio |
| Speaker Identification | Voice authentication |
| Audio Denoising | Noise cancellation in calls |

### 🎮 Other Domains

| Domain | Application |
|---|---|
| Healthcare | Drug discovery, protein folding (AlphaFold) |
| Finance | Fraud detection, algorithmic trading |
| Autonomous Vehicles | Tesla Autopilot, Waymo |
| Robotics | Manipulation, navigation |
| Recommendation Systems | Netflix, Spotify, YouTube |
| Climate Science | Weather forecasting, climate modelling |
| Gaming | AlphaGo, AlphaStar, OpenAI Five |

---

# 8. What is a Perceptron?

The **Perceptron** is the fundamental building block of all neural networks. It is the simplest form of an artificial neuron — a binary classifier that learns a linear decision boundary.

Invented by **Frank Rosenblatt in 1958**, the Perceptron was the first algorithm capable of learning from data.

### 🔢 Mathematical Definition

Given input vector **x = [x₁, x₂, ..., xₙ]**, the Perceptron computes:

```
Step 1 — Weighted Sum:
    z = w₁x₁ + w₂x₂ + ... + wₙxₙ + b
      = wᵀx + b

Step 2 — Step Function (Activation):
    ŷ = 1   if z ≥ 0
    ŷ = 0   if z < 0
```

### 🏗️ Architecture Diagram

```
         x₁  ──── w₁ ──┐
         x₂  ──── w₂ ──┼──→  Σ(wᵢxᵢ + b)  ──→  Step()  ──→  ŷ (0 or 1)
         x₃  ──── w₃ ──┘
                         ↑
                         b (bias)
```

### 📐 The Decision Boundary

The Perceptron draws a **hyperplane** in the input space that separates two classes:

```
For 2D input (x₁, x₂):
    w₁x₁ + w₂x₂ + b = 0   ← This is the decision boundary (a line)

Points above the line → Class 1
Points below the line → Class 0
```

### ✅ Perceptron Convergence Theorem

> If the data is **linearly separable**, the Perceptron algorithm is **guaranteed to converge** to a solution in a finite number of steps.

If the data is **not** linearly separable — it will never converge. This was the famous limitation exposed by Minsky & Papert (1969).

### 🔄 Perceptron Learning Rule

```
For each misclassified sample:
    wᵢ  ←  wᵢ  +  η · (y - ŷ) · xᵢ
    b   ←  b   +  η · (y - ŷ)

Where:
    η     = learning rate (e.g. 0.01)
    y     = true label
    ŷ     = predicted label
    xᵢ   = input feature
```

---

# 9. Neuron vs Perceptron

### 🧠 Biological Neuron

```
Dendrites (receive signals)
      │
      ▼
  Cell Body (soma — sums signals)
      │
      ▼
  Axon (if threshold exceeded, fires signal)
      │
      ▼
  Synapses → Next Neuron's Dendrites
```

### 🤖 Artificial Perceptron

```
Inputs (features)
      │
      ▼
  Weighted Sum (w₁x₁ + w₂x₂ + b)
      │
      ▼
  Activation Function (threshold)
      │
      ▼
  Output (0 or 1)
```

### 📊 Side-by-Side Comparison

| Aspect | Biological Neuron | Artificial Perceptron |
|---|---|---|
| **Input** | Electrical signals from dendrites | Numerical feature values |
| **Weights** | Synaptic strengths | Learnable weight parameters |
| **Summation** | Ion channels in cell body | Weighted dot product: `wᵀx + b` |
| **Threshold** | Action potential (~−55 mV) | Step function at 0 |
| **Output** | Fires or doesn't (all-or-nothing) | 1 or 0 |
| **Learning** | Synaptic plasticity (Hebb's rule) | Gradient-based weight updates |
| **Connections** | ~7,000 synapses per neuron | Configurable (any number of inputs) |
| **Speed** | ~1–100 Hz firing rate | Microseconds (limited by hardware) |
| **Count in Brain** | ~86 billion neurons | Configurable |

### 🔑 Key Differences

1. **Biological neurons** communicate via spikes (binary events in time). **Perceptrons** compute a single real-valued weighted sum.
2. **Biological neurons** have complex dendritic computations. **Perceptrons** are simplified to a linear combination.
3. **Biological learning** is Hebbian ("neurons that fire together wire together"). **Perceptron learning** is error-driven (supervised).
4. **Biological neurons** are analogue and noisy. **Perceptrons** are precise and deterministic.

---

# 10. Geometric Intuition

Understanding deep learning geometrically helps build powerful intuition for what these models actually do.

### 📍 Perceptron as a Line (2D)

In 2D, the Perceptron finds a **straight line** that separates two classes:

```
  x₂
   │      ✦ ✦  (Class 1)
   │   ✦
   │  ──────────── ← Decision boundary: w₁x₁ + w₂x₂ + b = 0
   │ ○   ○
   │  ○     ○  (Class 0)
   └──────────────── x₁
```

- Points on one side → predicted Class 1
- Points on the other → predicted Class 0
- The **weights (w₁, w₂)** define the **orientation** of the line
- The **bias (b)** defines the **position** (how far from the origin)

### 📍 In 3D — A Plane

In 3D input space, the decision boundary becomes a **plane**:

```
      x₃
       │    ✦ ✦
       │  ✦      ← Hyperplane (w₁x₁ + w₂x₂ + w₃x₃ + b = 0)
       │ ──────
       │○  ○
       └──────── x₁
      /
    x₂
```

### 📍 In N Dimensions — A Hyperplane

Generalising: in N-dimensional space, the Perceptron learns an **(N-1)-dimensional hyperplane**.

### 🧩 What Hidden Layers Do — Geometric View

Each hidden layer applies a **non-linear transformation** to the input space — folding, stretching, or rotating it — until the classes become linearly separable in the final layer.

```
Input Space       After Layer 1       After Layer 2        Output
 ○ ✦ mixed   →   regions bent   →   classes separated  →  correct prediction
```

This is why **depth matters**: more layers = more powerful transformations = more complex decision boundaries.

### 🌀 XOR Problem — Why Single Perceptron Fails

```
Input:    (0,0)→0   (0,1)→1   (1,0)→1   (1,1)→0

  x₂
  1 │  ✦             ○
    │
  0 │  ○             ✦
    └───────────────── x₁
       0             1

No single straight line can separate ✦ from ○ here!
```

XOR is **not linearly separable** — this is why we need **multiple layers** (MLP), which can draw curved, composite boundaries.

---

# 11. Code Example — Python & Scikit-Learn

### 🔧 Setup

```python
# Install required libraries
# pip install scikit-learn numpy matplotlib
```

### 📦 Imports

```python
import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import Perceptron
from sklearn.datasets import make_classification, load_iris
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import (
    accuracy_score,
    classification_report,
    confusion_matrix,
    ConfusionMatrixDisplay
)
```

### 🗂️ Example 1 — Linearly Separable Data (AND Gate)

```python
# Define AND gate truth table
X_and = np.array([[0, 0],
                   [0, 1],
                   [1, 0],
                   [1, 1]])

y_and = np.array([0, 0, 0, 1])   # AND output

# Train Perceptron
clf = Perceptron(max_iter=1000, eta0=0.1, random_state=42)
clf.fit(X_and, y_and)

# Predict
print("AND Gate Predictions:", clf.predict(X_and))
print("True Labels:         ", y_and)
print("Accuracy:", accuracy_score(y_and, clf.predict(X_and)))

# Output:
# AND Gate Predictions: [0 0 0 1]
# True Labels:          [0 0 0 1]
# Accuracy: 1.0
```

### 🗂️ Example 2 — Real Dataset (Iris Classification)

```python
# Load dataset
iris = load_iris()
X, y = iris.data, iris.target

# Binary classification: class 0 vs class 1
mask = y < 2
X, y = X[mask], y[mask]

# Split
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)

# Scale features
scaler = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_test  = scaler.transform(X_test)

# Train Perceptron
clf = Perceptron(max_iter=1000, eta0=0.1, random_state=42)
clf.fit(X_train, y_train)

# Evaluate
y_pred = clf.predict(X_test)
print(f"Accuracy: {accuracy_score(y_test, y_pred):.4f}")
print("\nClassification Report:")
print(classification_report(y_test, y_pred,
      target_names=['Setosa', 'Versicolor']))
```

### 🗂️ Example 3 — Visualising the Decision Boundary

```python
from sklearn.datasets import make_blobs

# Generate 2D linearly separable data
X, y = make_blobs(n_samples=200, centers=2, random_state=42,
                   cluster_std=1.2)

# Scale
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)

# Train
clf = Perceptron(max_iter=1000, eta0=0.1, random_state=42)
clf.fit(X_scaled, y)

# Create mesh grid for decision boundary
x_min, x_max = X_scaled[:, 0].min() - 1, X_scaled[:, 0].max() + 1
y_min, y_max = X_scaled[:, 1].min() - 1, X_scaled[:, 1].max() + 1
xx, yy = np.meshgrid(np.linspace(x_min, x_max, 300),
                      np.linspace(y_min, y_max, 300))

Z = clf.predict(np.c_[xx.ravel(), yy.ravel()])
Z = Z.reshape(xx.shape)

# Plot
plt.figure(figsize=(10, 6))
plt.contourf(xx, yy, Z, alpha=0.3, cmap='RdYlBu')
plt.scatter(X_scaled[:, 0], X_scaled[:, 1],
            c=y, cmap='RdYlBu', edgecolors='k', s=50)
plt.title('Perceptron Decision Boundary', fontsize=14)
plt.xlabel('Feature 1')
plt.ylabel('Feature 2')
plt.colorbar(label='Class')
plt.tight_layout()
plt.show()
```

### 🗂️ Example 4 — Perceptron from Scratch (NumPy)

```python
import numpy as np

class PerceptronScratch:
    """Single-layer Perceptron implemented from scratch."""

    def __init__(self, learning_rate: float = 0.01, n_epochs: int = 1000):
        self.lr       = learning_rate
        self.n_epochs = n_epochs
        self.weights  = None
        self.bias     = None
        self.errors_  = []

    def _step(self, z: np.ndarray) -> np.ndarray:
        """Binary step activation function."""
        return np.where(z >= 0, 1, 0)

    def fit(self, X: np.ndarray, y: np.ndarray) -> "PerceptronScratch":
        n_samples, n_features = X.shape
        self.weights = np.zeros(n_features)
        self.bias    = 0.0

        for epoch in range(self.n_epochs):
            epoch_errors = 0
            for xᵢ, yᵢ in zip(X, y):
                z    = np.dot(xᵢ, self.weights) + self.bias
                ŷᵢ  = self._step(z)
                delta = self.lr * (yᵢ - ŷᵢ)
                self.weights += delta * xᵢ
                self.bias    += delta
                epoch_errors += int(delta != 0)
            self.errors_.append(epoch_errors)
            if epoch_errors == 0:
                print(f"Converged at epoch {epoch + 1}")
                break
        return self

    def predict(self, X: np.ndarray) -> np.ndarray:
        z = np.dot(X, self.weights) + self.bias
        return self._step(z)


# ── Demo ─────────────────────────────────────────────────────────
from sklearn.datasets import make_blobs
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import accuracy_score

X, y = make_blobs(n_samples=300, centers=2, random_state=0)
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2,
                                                      random_state=42)
scaler  = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_test  = scaler.transform(X_test)

p = PerceptronScratch(learning_rate=0.01, n_epochs=1000)
p.fit(X_train, y_train)

print(f"Test Accuracy: {accuracy_score(y_test, p.predict(X_test)):.4f}")
print(f"Weights: {p.weights}")
print(f"Bias:    {p.bias:.4f}")
```

---

# 12. The Perceptron Trick

The **Perceptron Trick** is the iterative update rule that moves the decision boundary towards misclassified points.

---

## 12.1 How to Label Regions

The decision boundary (`w₁x₁ + w₂x₂ + b = 0`) divides the plane into two **half-spaces**:

```
Region Scoring:
    score(x) = w₁x₁ + w₂x₂ + b

    score > 0  →  Positive region (Class 1 predicted)
    score < 0  →  Negative region (Class 0 predicted)
    score = 0  →  On the boundary
```

### 📍 Labelling Rules

```
  x₂
   │    +++ (score > 0) → Predict Class 1
   │  +++
   │─────────────────── ← boundary (score = 0)
   │ ---
   │  --- (score < 0) → Predict Class 0
   └──────────────────── x₁
```

**For each point, we check:**

| True Label | Predicted | Correct? | Action |
|---|---|---|---|
| 1 | 1 | ✅ Yes | No update |
| 0 | 0 | ✅ Yes | No update |
| 1 | 0 | ❌ No | Move boundary toward point |
| 0 | 1 | ❌ No | Move boundary away from point |

---

## 12.2 Transformations

The Perceptron Trick applies a **geometric transformation** to the decision boundary on every misclassification.

### Updating Weights = Rotating/Shifting the Boundary

**Case 1: Point is Class 1 but predicted Class 0 (false negative)**
```
The point lies in the negative region but should be positive.
Action: Add the point's coordinates to the weight vector.

    w ← w + η · x
    b ← b + η

Effect: Rotates/shifts boundary so the point now lies in the positive region.
```

**Case 2: Point is Class 0 but predicted Class 1 (false positive)**
```
The point lies in the positive region but should be negative.
Action: Subtract the point's coordinates from the weight vector.

    w ← w − η · x
    b ← b − η

Effect: Rotates/shifts boundary so the point now lies in the negative region.
```

### Unified Formula

```
w ← w + η · (y − ŷ) · x
b ← b + η · (y − ŷ)

Where (y − ŷ) is:
    0   if correct (no update)
   +1   if false negative (add x)
   −1   if false positive (subtract x)
```

---

## 12.3 Coding the Algorithm

```python
import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_blobs

def perceptron_trick(X: np.ndarray,
                     y: np.ndarray,
                     lr: float = 0.1,
                     n_epochs: int = 50):
    """
    Perceptron learning algorithm with full training trace.
    y must be in {0, 1}.
    """
    n_samples, n_features = X.shape
    w = np.zeros(n_features)
    b = 0.0
    history = []

    for epoch in range(n_epochs):
        mistakes = 0
        for xᵢ, yᵢ in zip(X, y):
            score  = np.dot(w, xᵢ) + b
            ŷᵢ    = 1 if score >= 0 else 0
            error  = yᵢ - ŷᵢ

            if error != 0:
                w += lr * error * xᵢ
                b += lr * error
                mistakes += 1

        history.append({'epoch': epoch + 1,
                         'mistakes': mistakes,
                         'weights': w.copy(),
                         'bias': b})
        if mistakes == 0:
            print(f"✅ Converged at epoch {epoch + 1}")
            break

    return w, b, history


# ── Run ──────────────────────────────────────────────────────────
X, y = make_blobs(n_samples=100, centers=2, random_state=42)

# Normalise to [0,1] labels
y = (y > 0).astype(int)

# Standardise
from sklearn.preprocessing import StandardScaler
X = StandardScaler().fit_transform(X)

w, b, history = perceptron_trick(X, y, lr=0.1, n_epochs=100)

print(f"\nFinal Weights : {w}")
print(f"Final Bias    : {b:.4f}")
print(f"Epochs Run    : {len(history)}")

# Plot mistakes per epoch
epochs   = [h['epoch']   for h in history]
mistakes = [h['mistakes'] for h in history]

plt.figure(figsize=(10, 4))
plt.plot(epochs, mistakes, 'r-o', linewidth=2, markersize=5)
plt.title('Perceptron: Misclassifications per Epoch')
plt.xlabel('Epoch')
plt.ylabel('Number of Mistakes')
plt.grid(True, alpha=0.3)
plt.tight_layout()
plt.show()
```

---

## 12.4 Problem with the Perceptron Trick

The Perceptron Trick has two fundamental limitations:

### ❌ Problem 1 — Only Works on Linearly Separable Data

```
XOR data:
  ✦ at (0,1) and (1,0) → Class 1
  ○ at (0,0) and (1,1) → Class 0

No single line can separate these. The algorithm will loop forever.
```

### ❌ Problem 2 — Not Unique Solution

When data IS linearly separable, many valid boundaries exist. The Perceptron finds **one of them arbitrarily** — not necessarily the best one (maximum margin).

```
  ✦ ✦                         ✦ ✦
      ─────   or this?  ────         Any of these work.
  ○ ○                         ○ ○   SVM finds the BEST one.
```

### ❌ Problem 3 — No Probabilistic Output

The Perceptron outputs only 0 or 1 — it gives no **confidence** in its prediction. Logistic Regression and softmax fix this.

### ❌ Problem 4 — Sensitive to Learning Rate

Too high → overshoots, oscillates.
Too low → too slow to converge, gets stuck.

### ❌ Problem 5 — No Hidden Layers = Cannot Learn Complex Patterns

A single Perceptron is a **linear classifier**. It cannot learn:
- XOR
- Circular decision boundaries
- Any non-linearly separable pattern

**Solution**: Stack multiple Perceptrons → Multilayer Perceptron (MLP) with non-linear activations.

---

## 12.5 Loss Functions

A **Loss Function** (also called a cost function or objective function) measures **how wrong the model's predictions are** compared to the true labels.

The goal of training is to **minimise the loss**.

```
Loss Function
      │
      ▼
L(y, ŷ)  =  some measure of distance between y (true) and ŷ (predicted)
```

### Why Do We Need a Loss Function?

1. **Quantifies error** — gives a single number representing model performance
2. **Enables optimisation** — we compute gradients of loss w.r.t. weights to update them
3. **Guides learning** — different loss functions suit different problems

### Common Loss Functions

| Loss | Formula | Used For |
|---|---|---|
| **Mean Squared Error (MSE)** | `(1/n) Σ(y - ŷ)²` | Regression |
| **Binary Cross-Entropy** | `-[y·log(ŷ) + (1-y)·log(1-ŷ)]` | Binary classification |
| **Categorical Cross-Entropy** | `-Σ yᵢ·log(ŷᵢ)` | Multi-class classification |
| **Hinge Loss** | `max(0, 1 - y·ŷ)` | SVM / Perceptron |
| **Huber Loss** | Quadratic near 0, linear far | Robust regression |

---

## 12.6 Perceptron Loss Function

The **Perceptron Loss** (also called Hinge Loss) is defined as:

```
L(y, ŷ) = max(0, -y · score(x))

Where:
    score(x) = wᵀx + b
    y ∈ {-1, +1}   (labels encoded as -1 and +1)
```

### Intuition

```
Case 1: Point correctly classified
    y · score > 0   →   loss = 0   (no penalty)

Case 2: Point misclassified
    y · score < 0   →   loss = |y · score|   (proportional to distance from boundary)
```

### Visualisation

```
Loss
  │
  │\
  │ \      Perceptron Loss = max(0, -y·score)
  │  \
  │   \
  │    ─────────────────────── 
  └──────────────────────────── y·score
      negative    0   positive
  (misclassified)  (boundary)  (correctly classified)
```

### The Full Perceptron Objective

```
Total Loss = (1/n) Σ max(0, -yᵢ · (wᵀxᵢ + b))

We want to minimise this over all training examples.
```

```python
import numpy as np

def perceptron_loss(X: np.ndarray,
                    y: np.ndarray,
                    w: np.ndarray,
                    b: float) -> float:
    """
    Compute total Perceptron loss.
    y must be encoded as {-1, +1}.
    """
    scores = X @ w + b
    losses = np.maximum(0, -y * scores)
    return float(np.mean(losses))


# Example
np.random.seed(42)
X = np.random.randn(100, 2)
y = np.where(X[:, 0] + X[:, 1] > 0, 1, -1)   # {-1, +1} labels

w = np.array([0.5, 0.3])
b = 0.1

loss = perceptron_loss(X, y, w, b)
print(f"Perceptron Loss: {loss:.4f}")
```

---

## 12.7 Scikit-Learn Docs Reference

Scikit-Learn's `Perceptron` is a linear classifier equivalent to `SGDClassifier` with `loss='perceptron'`.

### Key Parameters

```python
from sklearn.linear_model import Perceptron

clf = Perceptron(
    penalty=None,        # Regularisation: 'l1', 'l2', 'elasticnet', or None
    alpha=0.0001,        # Regularisation strength (when penalty is not None)
    fit_intercept=True,  # Whether to fit bias term (b)
    max_iter=1000,       # Maximum number of passes over training data
    tol=1e-3,            # Stopping criterion tolerance
    shuffle=True,        # Whether to shuffle training data each epoch
    eta0=1.0,            # Learning rate (constant for Perceptron)
    random_state=42,     # Random seed for reproducibility
    early_stopping=False,# Stop training when validation score stops improving
    validation_fraction=0.1,  # Fraction of training data for validation
    n_iter_no_change=5,  # Epochs with no improvement before stopping
    class_weight=None,   # 'balanced' or dict for imbalanced classes
    warm_start=False     # Reuse previous fit as initialisation
)
```

### Key Attributes After Fitting

```python
clf.fit(X_train, y_train)

print(clf.coef_)          # Shape: (1, n_features) — the weight vector
print(clf.intercept_)     # Shape: (1,) — the bias term
print(clf.n_iter_)        # Actual number of iterations run
print(clf.classes_)       # Unique class labels
```

### Methods

```python
clf.predict(X_test)           # Returns class labels
clf.decision_function(X_test) # Returns raw scores (wᵀx + b) — not probabilities
clf.score(X_test, y_test)     # Returns accuracy
```

### Full Pipeline Example

```python
from sklearn.pipeline import Pipeline
from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import Perceptron
from sklearn.datasets import load_breast_cancer
from sklearn.model_selection import cross_val_score

X, y = load_breast_cancer(return_X_y=True)

pipeline = Pipeline([
    ('scaler',     StandardScaler()),
    ('perceptron', Perceptron(max_iter=1000,
                               eta0=0.1,
                               random_state=42,
                               early_stopping=True))
])

scores = cross_val_score(pipeline, X, y, cv=5, scoring='accuracy')
print(f"CV Accuracy: {scores.mean():.4f} ± {scores.std():.4f}")
```

---

## 12.8 Explanation of Loss Functions

### 🔍 Deep Dive: Why Loss Functions Shape Learning

The choice of loss function determines **what the model optimises for** and how gradients flow during backpropagation.

#### Mean Squared Error (MSE)

```
L = (1/n) Σ (yᵢ − ŷᵢ)²
```

```python
def mse_loss(y_true, y_pred):
    return np.mean((y_true - y_pred) ** 2)

# Properties:
# - Penalises large errors MORE (squared)
# - Smooth gradient everywhere → easy to optimise
# - Sensitive to outliers
# - Used for regression tasks
```

#### Binary Cross-Entropy (Log Loss)

```
L = -(1/n) Σ [yᵢ·log(ŷᵢ) + (1−yᵢ)·log(1−ŷᵢ)]
```

```python
def binary_cross_entropy(y_true, y_pred):
    eps = 1e-15  # Prevent log(0)
    y_pred = np.clip(y_pred, eps, 1 - eps)
    return -np.mean(y_true * np.log(y_pred) +
                    (1 - y_true) * np.log(1 - y_pred))

# Properties:
# - Measures divergence between predicted probability and true label
# - Large gradient when prediction is confidently wrong
# - Natural pairing with Sigmoid output
# - Used for binary classification
```

#### Categorical Cross-Entropy

```
L = -(1/n) Σᵢ Σⱼ yᵢⱼ · log(ŷᵢⱼ)
```

```python
def categorical_cross_entropy(y_true_onehot, y_pred_probs):
    eps = 1e-15
    y_pred_probs = np.clip(y_pred_probs, eps, 1)
    return -np.mean(np.sum(y_true_onehot * np.log(y_pred_probs), axis=1))

# Properties:
# - Generalisation of binary CE to K classes
# - Natural pairing with Softmax output
# - Used for multi-class classification
```

#### Hinge Loss (SVM / Perceptron)

```
L = (1/n) Σ max(0, 1 − yᵢ · ŷᵢ)     y ∈ {-1, +1}
```

```python
def hinge_loss(y_true, y_scores):
    # y_true must be {-1, +1}
    return np.mean(np.maximum(0, 1 - y_true * y_scores))

# Properties:
# - Zero loss for correctly classified points (margin satisfied)
# - Linear penalty for violations
# - Not differentiable at 0 → requires subgradient methods
# - Used for SVMs and Perceptrons
```

### 📊 Loss Landscape Visualisation

```python
import numpy as np
import matplotlib.pyplot as plt

scores = np.linspace(-3, 3, 300)

# MSE (y=1, ŷ=sigmoid(score))
sigmoid = 1 / (1 + np.exp(-scores))
mse     = (1 - sigmoid) ** 2

# Binary Cross-Entropy (y=1)
bce     = -np.log(np.clip(sigmoid, 1e-15, 1))

# Hinge (y=+1)
hinge   = np.maximum(0, 1 - scores)

plt.figure(figsize=(12, 5))
plt.plot(scores, mse,   label='MSE',                  linewidth=2)
plt.plot(scores, bce,   label='Binary Cross-Entropy',  linewidth=2)
plt.plot(scores, hinge, label='Hinge Loss',            linewidth=2)
plt.axvline(0, color='gray', linestyle='--', alpha=0.5, label='Boundary')
plt.title('Loss Functions Compared (True Label = 1)', fontsize=14)
plt.xlabel('Score (wᵀx + b)')
plt.ylabel('Loss')
plt.legend()
plt.grid(True, alpha=0.3)
plt.ylim(-0.1, 4)
plt.tight_layout()
plt.show()
```

---

## 12.9 Gradient Descent

**Gradient Descent** is the optimisation algorithm used to minimise the loss function by iteratively updating model parameters in the direction of the **steepest decrease** in loss.

### 🏔️ The Mountain Analogy

> You are blindfolded on a hilly landscape and want to reach the lowest valley. You feel the slope under your feet and always take a step in the downhill direction. Repeat until you stop descending. This is gradient descent.

### 📐 The Mathematics

The gradient of the loss with respect to weight `w` tells us the direction of steepest **increase**. We step in the **opposite** direction:

```
w ← w − η · ∂L/∂w
b ← b − η · ∂L/∂b

Where:
    η (eta) = learning rate — controls step size
    ∂L/∂w  = partial derivative of loss w.r.t. weight
```

### 🔢 Gradient for Perceptron Loss

For loss `L = max(0, −y·(wᵀx + b))`:

```
∂L/∂w = −y·x   if y·(wᵀx + b) < 0   (misclassified)
∂L/∂w =  0     otherwise

∂L/∂b = −y     if y·(wᵀx + b) < 0
∂L/∂b =  0     otherwise
```

### ⚖️ Variants of Gradient Descent

| Variant | Batch Size | Pros | Cons |
|---|---|---|---|
| **Batch GD** | All data | Stable convergence | Very slow for large datasets |
| **Stochastic GD (SGD)** | 1 sample | Fast updates, can escape local minima | Noisy, oscillates |
| **Mini-Batch GD** | 32–512 samples | Best of both — GPU efficient | Tuning batch size needed |

```
Batch GD:
    for each epoch:
        gradient = ∂L/∂w computed over ALL n samples
        w ← w − η · gradient

Stochastic GD:
    for each epoch:
        for each sample xᵢ:
            gradient = ∂L/∂w computed over xᵢ only
            w ← w − η · gradient

Mini-Batch GD:
    for each epoch:
        for each mini-batch B:
            gradient = ∂L/∂w computed over B samples
            w ← w − η · gradient
```

### 📉 Learning Rate Impact

```
Loss
 │ η too high       │ η just right     │ η too low
 │ /\/\/\/\/        │ \                │ \
 │ oscillates       │  ──────          │  \
 │                  │  converges       │   \
 └──────────────    └────────────      └────────────
       Epoch              Epoch              Epoch
```

### 🚀 Advanced Optimisers

| Optimiser | Key Idea | Formula |
|---|---|---|
| **Momentum** | Accumulates velocity in gradient direction | `v ← βv + η·∇L; w ← w − v` |
| **RMSProp** | Divides lr by moving average of squared gradients | `w ← w − (η/√v)·∇L` |
| **Adam** | Combines Momentum + RMSProp (most popular) | `w ← w − (η/√v̂)·m̂` |
| **AdaGrad** | Adapts lr per parameter | `w ← w − (η/√G)·∇L` |

---

## 12.10 Code Demo

### Demo 1 — Gradient Descent from Scratch

```python
import numpy as np
import matplotlib.pyplot as plt

class GradientDescentPerceptron:
    """
    Perceptron trained with explicit gradient descent on Perceptron Loss.
    Uses {-1, +1} label encoding.
    """

    def __init__(self, lr: float = 0.01, n_epochs: int = 200):
        self.lr       = lr
        self.n_epochs = n_epochs
        self.w        = None
        self.b        = 0.0
        self.loss_history: list[float] = []

    def _loss(self, X: np.ndarray, y: np.ndarray) -> float:
        scores = X @ self.w + self.b
        return float(np.mean(np.maximum(0, -y * scores)))

    def fit(self, X: np.ndarray, y: np.ndarray) -> "GradientDescentPerceptron":
        n_samples, n_features = X.shape
        self.w = np.zeros(n_features)

        for epoch in range(self.n_epochs):
            scores     = X @ self.w + self.b
            misclassed = (y * scores) < 0              # Boolean mask

            grad_w = -np.mean(y[misclassed, None] * X[misclassed], axis=0) \
                     if misclassed.any() else np.zeros(n_features)
            grad_b = -np.mean(y[misclassed]) \
                     if misclassed.any() else 0.0

            self.w -= self.lr * grad_w
            self.b -= self.lr * grad_b

            self.loss_history.append(self._loss(X, y))

        return self

    def predict(self, X: np.ndarray) -> np.ndarray:
        return np.where(X @ self.w + self.b >= 0, 1, -1)


# ── Run Demo ─────────────────────────────────────────────────────
from sklearn.datasets import make_blobs
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import accuracy_score

# Generate data
X, y_raw = make_blobs(n_samples=300, centers=2, random_state=42)
y = np.where(y_raw == 0, -1, 1)   # Encode as {-1, +1}

scaler = StandardScaler()
X      = scaler.fit_transform(X)

# Train
model = GradientDescentPerceptron(lr=0.05, n_epochs=200)
model.fit(X, y)

preds    = model.predict(X)
accuracy = accuracy_score(y, preds)
print(f"Training Accuracy: {accuracy:.4f}")
print(f"Final Loss       : {model.loss_history[-1]:.6f}")

# Plot loss curve
plt.figure(figsize=(10, 4))
plt.plot(model.loss_history, 'b-', linewidth=2)
plt.title('Perceptron: Training Loss (Gradient Descent)', fontsize=14)
plt.xlabel('Epoch')
plt.ylabel('Perceptron Loss')
plt.grid(True, alpha=0.3)
plt.tight_layout()
plt.show()
```

### Demo 2 — Comparing Learning Rates

```python
import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_blobs
from sklearn.preprocessing import StandardScaler

X, y_raw = make_blobs(n_samples=300, centers=2, random_state=42)
y = np.where(y_raw == 0, -1, 1)
X = StandardScaler().fit_transform(X)

learning_rates = [0.001, 0.01, 0.1, 0.5]
plt.figure(figsize=(12, 5))

for lr in learning_rates:
    model = GradientDescentPerceptron(lr=lr, n_epochs=200)
    model.fit(X, y)
    plt.plot(model.loss_history, label=f'η = {lr}', linewidth=2)

plt.title('Effect of Learning Rate on Convergence', fontsize=14)
plt.xlabel('Epoch')
plt.ylabel('Loss')
plt.legend()
plt.grid(True, alpha=0.3)
plt.tight_layout()
plt.show()
```

### Demo 3 — Mini-Batch Gradient Descent

```python
import numpy as np
from sklearn.datasets import make_blobs
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import accuracy_score

def mini_batch_perceptron(X, y, lr=0.01, n_epochs=100, batch_size=32):
    """
    Mini-batch gradient descent for Perceptron.
    y must be {-1, +1}.
    """
    n_samples, n_features = X.shape
    w = np.zeros(n_features)
    b = 0.0
    loss_history = []

    for epoch in range(n_epochs):
        # Shuffle
        idx = np.random.permutation(n_samples)
        X_shuffled, y_shuffled = X[idx], y[idx]

        epoch_loss = 0.0
        for start in range(0, n_samples, batch_size):
            Xb = X_shuffled[start:start + batch_size]
            yb = y_shuffled[start:start + batch_size]

            scores     = Xb @ w + b
            misclassed = (yb * scores) < 0

            if misclassed.any():
                grad_w = -np.mean(yb[misclassed, None] * Xb[misclassed], axis=0)
                grad_b = -np.mean(yb[misclassed])
                w -= lr * grad_w
                b -= lr * grad_b

            epoch_loss += np.mean(np.maximum(0, -yb * (Xb @ w + b)))

        loss_history.append(epoch_loss / (n_samples // batch_size))

    return w, b, loss_history


# ── Run ──────────────────────────────────────────────────────────
X, y_raw = make_blobs(n_samples=1000, centers=2, random_state=42)
y = np.where(y_raw == 0, -1, 1)
X = StandardScaler().fit_transform(X)

w, b, history = mini_batch_perceptron(X, y,
                                       lr=0.05,
                                       n_epochs=100,
                                       batch_size=32)

preds = np.where(X @ w + b >= 0, 1, -1)
print(f"Accuracy     : {accuracy_score(y, preds):.4f}")
print(f"Final Loss   : {history[-1]:.6f}")
```

---

# 13. Next Up: MLP — Multilayer Perceptron

The **Multilayer Perceptron (MLP)** solves the key limitation of the single Perceptron: it stacks multiple layers of neurons with non-linear activations, allowing it to learn arbitrarily complex decision boundaries.

### 🏗️ Architecture

```
INPUT LAYER        HIDDEN LAYER 1       HIDDEN LAYER 2      OUTPUT LAYER
   x₁ ─────────→ ● ────────────────→ ● ─────────────────→ ●
                  ● ────────────────→ ● ─────────────────→ ●  →  ŷ
   x₂ ─────────→ ● ────────────────→ ●
                  ●
   x₃ ─────────→ ●
```

### 🆕 What Changes vs Single Perceptron

| Feature | Single Perceptron | MLP |
|---|---|---|
| **Layers** | 1 (input → output) | 2+ (input → hidden(s) → output) |
| **Activation** | Step function | ReLU, Sigmoid, Tanh |
| **Decision Boundary** | Linear (hyperplane) | Non-linear (any shape) |
| **Learning** | Perceptron rule | Backpropagation + Gradient Descent |
| **Can solve XOR?** | ❌ No | ✅ Yes |
| **Universal Approx.** | ❌ No | ✅ Yes (with enough neurons) |

### 🔮 Coming Up in the MLP Chapter

```
✅ Forward Pass — Computing predictions layer by layer
✅ Backpropagation — Computing gradients via chain rule
✅ Activation Functions — ReLU, Sigmoid, Softmax in depth
✅ Weight Initialisation — Xavier, He initialisation
✅ Regularisation — Dropout, L1/L2
✅ Batch Normalisation — Stabilising deep networks
✅ Full MLP from Scratch in NumPy
✅ MLP with PyTorch — nn.Module
✅ MLP with Scikit-Learn — MLPClassifier
✅ Real-World Projects — MNIST, Tabular Data
```

### 🔭 Sneak Peek — MLP in PyTorch

```python
import torch
import torch.nn as nn

class MLP(nn.Module):
    def __init__(self, input_dim: int, hidden_dim: int, output_dim: int):
        super().__init__()
        self.network = nn.Sequential(
            nn.Linear(input_dim, hidden_dim),
            nn.ReLU(),
            nn.Linear(hidden_dim, hidden_dim),
            nn.ReLU(),
            nn.Linear(hidden_dim, output_dim)
        )

    def forward(self, x: torch.Tensor) -> torch.Tensor:
        return self.network(x)


# Instantiate
model = MLP(input_dim=784, hidden_dim=256, output_dim=10)
print(model)
print(f"Parameters: {sum(p.numel() for p in model.parameters()):,}")
```

> 🚀 The MLP chapter begins next — where single neurons become a **full deep learning system**.

---

## 📎 Quick Reference Cheat Sheet

```
┌──────────────────────────────────────────────────────────────────────┐
│                    DEEP LEARNING CHEAT SHEET                         │
├────────────────────┬─────────────────────────────────────────────────┤
│ Perceptron         │ z = wᵀx + b;  ŷ = step(z)                      │
│ Activation (ReLU)  │ f(z) = max(0, z)                                │
│ Activation (Sig.)  │ f(z) = 1 / (1 + e⁻ᶻ)                          │
│ Forward Pass       │ a⁽ˡ⁾ = f(W⁽ˡ⁾a⁽ˡ⁻¹⁾ + b⁽ˡ⁾)                  │
│ Loss (MSE)         │ L = (1/n)Σ(y - ŷ)²                             │
│ Loss (BCE)         │ L = -[y·log(ŷ) + (1-y)·log(1-ŷ)]              │
│ Loss (Perceptron)  │ L = max(0, -y·score)                            │
│ Gradient Descent   │ w ← w - η·∂L/∂w                                │
│ Learning Rate      │ Typical range: 0.0001 – 0.1                     │
│ Batch Size         │ Typical: 32, 64, 128, 256                       │
│ Epochs             │ Full passes through training data                │
├────────────────────┴─────────────────────────────────────────────────┤
│ NETWORKS:  FNN │ CNN │ RNN │ LSTM │ GRU │ Transformer │ GAN │ AE    │
│ OPTIMISERS: SGD │ Momentum │ RMSProp │ Adam │ AdaGrad               │
│ FRAMEWORKS: PyTorch │ TensorFlow │ Keras │ JAX │ Scikit-Learn        │
└──────────────────────────────────────────────────────────────────────┘
```

---

## 📚 Further Reading & Resources

| Resource | Type | Link |
|---|---|---|
| Deep Learning (Goodfellow, Bengio, Courville) | Book | deeplearningbook.org |
| fast.ai Practical Deep Learning | Course | fast.ai |
| CS231n: CNNs for Visual Recognition | Course | cs231n.stanford.edu |
| PyTorch Official Tutorials | Docs | pytorch.org/tutorials |
| Scikit-Learn Perceptron Docs | Docs | scikit-learn.org |
| 3Blue1Brown Neural Networks | Video | youtube.com/@3blue1brown |
| Andrej Karpathy's Neural Nets: Zero to Hero | Video | youtube.com/@AndrejKarpathy |

---

## 🏷️ Tags

`deep-learning` `neural-networks` `perceptron` `gradient-descent` `machine-learning` `python` `scikit-learn` `numpy` `pytorch` `computer-vision` `nlp` `ai`

---

**Author**: Deep Learning Complete Guide  
**Language**: Python 3.10+  
**Libraries**: NumPy · Scikit-Learn · Matplotlib · PyTorch  
**Licence**: MIT
