<div align="center">

```
 ██████╗     █████╗ ██╗   ██╗████████╗██╗  ██╗     █████╗ ██████╗ ██╗
██╔════╝    ██╔══██╗██║   ██║╚══██╔══╝██║  ██║    ██╔══██╗██╔══██╗██║
██║         ███████║██║   ██║   ██║   ███████║    ███████║██████╔╝██║
██║         ██╔══██║██║   ██║   ██║   ██╔══██║    ██╔══██║██╔═══╝ ██║
╚██████╗    ██║  ██║╚██████╔╝   ██║   ██║  ██║    ██║  ██║██║     ██║
 ╚═════╝    ╚═╝  ╚═╝ ╚═════╝    ╚═╝   ╚═╝  ╚═╝    ╚═╝  ╚═╝╚═╝     ╚═╝
```

**A blazing-fast authentication server written in pure C**  
*No frameworks. No external databases. Just raw sockets and JSON.*

[![Language](https://img.shields.io/badge/Language-C-blue?style=flat-square&logo=c)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Database](https://img.shields.io/badge/Database-JSON%20File-orange?style=flat-square&logo=json)](https://www.json.org)
[![Server](https://img.shields.io/badge/Server-Raw%20Sockets-red?style=flat-square)](https://man7.org/linux/man-pages/man7/socket.7.html)
[![License](https://img.shields.io/badge/License-MIT-green?style=flat-square)](LICENSE)

</div>

---

## 📖 Overview

A lightweight authentication API handcrafted in C — no libuv, no libmicrohttpd, no magic. Just POSIX sockets, a JSON file acting as a database, and a clean modular architecture. Built for developers who want to understand what happens under the hood.

---

## ✨ Features

| Feature | Description |
|---|---|
| 🔐 **Login Endpoint** | `POST /login` with username & password |
| 📦 **JSON Database** | Flat-file storage — zero dependencies on external DBs |
| 🌐 **Raw HTTP Server** | Built on POSIX socket programming from scratch |
| ⚡ **Ultra Lightweight** | No frameworks, minimal footprint |
| 🧩 **Modular Design** | Clean separation: auth / server / file I/O |

---

## 📁 Project Structure

```
auth-api-c-json/
│
├── main.c          ← Entry point
├── db.json         ← User database (JSON)
│
├── cJSON.c         ← JSON parsing library
├── cJSON.h
│
├── server.c        ← HTTP server (raw sockets)
├── server.h
│
├── auth.c          ← Authentication logic
├── auth.h
│
├── fileio.c        ← File read/write utilities
├── fileio.h
│
└── Makefile        ← Build configuration
```

---

## 🗄️ Database Format

Users are stored in a plain `db.json` file:

```json
[
  {
    "username": "admin",
    "password": "1234"
  }
]
```

> ⚠️ **Note:** Passwords are stored in plaintext for demonstration purposes. In production, use a hashing algorithm like bcrypt or SHA-256.

---

## 🚀 Getting Started

### 1 — Clone the repository

```bash
git clone https://github.com/blaxkmiradev/auth-api-c-json.git
cd auth-api-c-json
```

### 2 — Add the cJSON library

```bash
git clone https://github.com/DaveGamble/cJSON
```

Then copy `cJSON.c` and `cJSON.h` into the project root.

### 3 — Build

```bash
make
```

### 4 — Run

```bash
make run
```

Server starts at → **`http://localhost:8080`** 🟢

---

## 🔌 API Reference

### `POST /login`

Authenticate a user with their credentials.

**Request**

```bash
curl -X POST http://localhost:8080/login \
  -d "username=admin&password=1234"
```

**Success `200 OK`**

```json
{
  "status": "success",
  "token": "fake_token_123"
}
```

**Failure `401 Unauthorized`**

```json
{
  "status": "fail"
}
```

---

## 🔄 How It Works

```
Client (curl / browser)
        │
        │  POST /login  (username + password)
        ▼
┌──────────────────┐
│   HTTP Server    │  ← Parses raw HTTP request
│   (server.c)     │
└────────┬─────────┘
         │
         ▼
┌──────────────────┐
│   Auth Module    │  ← Validates credentials
│   (auth.c)       │
└────────┬─────────┘
         │
         ▼
┌──────────────────┐
│   File I/O       │  ← Reads db.json
│   (fileio.c)     │
└────────┬─────────┘
         │
         ▼
     db.json  📄
         │
         └──→  Match found?  ✅ Return token  /  ❌ Return fail
```

---

## 🛠️ Built With

- **C** (C99 standard)
- **[cJSON](https://github.com/DaveGamble/cJSON)** — Lightweight JSON parser
- **POSIX Sockets** — Raw TCP/HTTP layer
- **GNU Make** — Build system

---

## 🤝 Contributing

Pull requests are welcome! For major changes, please open an issue first to discuss what you'd like to change.

---

<div align="center">

Made with ☕ and raw pointers

</div>
