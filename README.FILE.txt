# 🥤 Vending Machine (C++)

A console-based **Vending Machine simulation** built in C++ as part of a **Programming Fundamentals** course project. This project demonstrates core procedural programming concepts including arrays, loops, functions, and conditional logic — without using OOP (classes/objects).

---

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Concepts Demonstrated](#concepts-demonstrated)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
  - [Running the Program](#running-the-program)
- [Usage Guide](#usage-guide)
- [Sample Products](#sample-products)
- [Admin Panel](#admin-panel)
- [Future Improvements](#future-improvements)
- [License](#license)
- [Author](#author)

---

## 📖 Overview

This project simulates a real-world vending machine through a simple text-based menu system. Users can browse available products, purchase items by inserting money, and receive change. An admin panel allows restocking and viewing total earnings.

The program is intentionally written using **only basic C++ constructs** — arrays, functions, loops, and switch/if-else statements — making it ideal for beginners learning Programming Fundamentals.

---

## ✨ Features

- 📦 View all available products with price and stock
- 💰 Purchase a product with cash-insertion simulation and automatic change calculation
- 🔐 Password-protected Admin Panel
- 🔄 Restock existing products
- 📊 View total earnings
- ✅ Input validation for invalid choices, amounts, and product codes

---

## 🧠 Concepts Demonstrated

| Concept              | Usage in Project                              |
|----------------------|------------------------------------------------|
| Arrays               | Storing product codes, names, prices, quantities |
| Functions            | Modular code for menus, purchases, admin actions |
| Loops                | `for`, `while`, `do-while` for menus and searches |
| Conditionals         | `if-else` and `switch-case` for decision making |
| Basic I/O            | `cin` / `cout` for user interaction              |

> This project deliberately avoids Object-Oriented Programming (classes/objects) to focus on foundational procedural programming skills.

---

## 📁 Project Structure

```
VendingMachine/
│
├── main.cpp        # Complete source code
└── README.md        # Project documentation
```

---

## 🚀 Getting Started

### Prerequisites

You need a C++ compiler installed on your system:

- **Windows**: [MinGW](https://www.mingw-w64.org/) or [MSYS2](https://www.msys2.org/)
- **macOS**: Run `xcode-select --install` in Terminal
- **Linux**: Install via `sudo apt install g++`

Verify installation:
```bash
g++ --version
```

### Installation

Clone this repository:
```bash
git clone https://github.com/<your-username>/VendingMachine.git
cd VendingMachine
```

### Running the Program

Compile and run using g++:
```bash
g++ -o vending main.cpp
./vending
```

On Windows:
```bash
g++ -o vending main.cpp
vending.exe
```

**Using VS Code:**
1. Install the **C/C++ extension** (by Microsoft) from the Extensions Marketplace.
2. Open this folder in VS Code (`File > Open Folder`).
3. Open the integrated terminal (`` Ctrl+` ``) and run the commands above.

---

## 🕹️ Usage Guide

Upon running the program, you'll see the main menu:

```
1. View Products
2. Buy a Product
3. Admin Panel
4. Exit
```

- **View Products** — Lists all items with code, price, and stock.
- **Buy a Product** — Enter a product code, insert money (can be done in multiple installments), and receive your item plus change.
- **Admin Panel** — Requires a password to access restocking and earnings tools.
- **Exit** — Closes the program.

---

## 🛒 Sample Products

| Code | Item         | Price (Rs.) | Stock |
|------|--------------|--------------|-------|
| 101  | Coca-Cola    | 80.00        | 10    |
| 102  | Water Bottle | 40.00        | 15    |
| 103  | Chips        | 60.00        | 12    |
| 104  | Chocolate    | 100.00       | 8     |
| 105  | Biscuits     | 50.00        | 20    |
| 106  | Juice        | 70.00        | 10    |

---

## 🔐 Admin Panel

The Admin Panel is password-protected.

**Default password:** `admin123`

Available admin actions:
- View all products
- Restock an existing product
- View total earnings

> ⚠️ Note: Since the project uses fixed-size arrays instead of dynamic data structures, new product codes cannot be added at runtime — only existing products can be restocked.

---

## 🔮 Future Improvements

- Support for adding new products dynamically (using vectors or dynamic arrays)
- Persistent storage using file handling (save/load inventory and earnings)
- Multiple payment denominations and exact-change validation
- A graphical user interface (GUI) version

---

## 📄 License

This project is open-source and available for educational use under the [MIT License](LICENSE).

---

## 👤 Author

Developed as a **Programming Fundamentals** course project.

Feel free to fork, modify, and use this project for learning purposes. Contributions and suggestions are welcome!
