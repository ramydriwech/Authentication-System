# User Authentication System

A simple user authentication system in C++ that implements user registration and login with password hashing and salting.

---

## Table of Contents
1. [Technologies Used](#technologies-used)
2. [Solution Description](#solution-description)
3. [Functional Explanation](#functional-explanation)
4. [Features](#features)
5. [Installation](#installation)
6. [Usage](#usage)
7. [Future Improvements](#future-improvements)
8. [License](#license)

---

## Technologies Used
- C++
- File Handling
- Secure Hashing (`std::hash` for demonstration, replaceable with OpenSSL or bcrypt for better security)
- Random salt generation

---

## Solution Description
This project solves the problem of basic authentication by:
- Implementing a **secure hashing mechanism** using a combination of a password and a unique salt.
- Enforcing **strong password policies** to enhance security.
- Storing user credentials in a **structured text file** to simulate a simple database.
- Providing an **easy-to-use interface** for user registration and login.

---

## Functional Explanation
This authentication system consists of three main components:

### 1. User Registration
- The user provides a username and a password.
- The password is checked for strength.
- A random salt is generated and appended to the password before hashing.
- The username, hashed password, and salt are stored in a file.

### 2. User Login
- The user provides their username and password.
- The system retrieves the stored salt and hashes the input password with it.
- If the hash matches the stored hashed password, the login is successful.

### 3. File Management
- User credentials are stored in a text file.
- Each line contains a username, hashed password, and salt, separated by commas.

---

## Features
- User registration with password hashing and salting.
- Secure salt generation.
- Strong password validation (minimum 8 characters, including uppercase, lowercase, digit, and special character).
- User login with password verification.
- Stores user data in a text file.

---

## Installation
### Prerequisites
- A C++ compiler (GCC, Clang, or MSVC)

### Clone the Repository
```sh
git clone https://github.com/yourusername/authentication-system.git
cd authentication-system
```

### Compile the Program
```sh
g++ -o auth_system main.cpp
```

### Run the Program
```sh
./auth_system
```

---

## Usage
1. Run the program.
2. Choose an option:
   - **1**: Register a new user.
   - **2**: Login as an existing user.
   - **3**: Exit.

---

## Future Improvements
- Implement SHA-256 or bcrypt hashing for stronger security.
- Store user data in a database instead of a text file.
- Improve error handling and input validation.


