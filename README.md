# # Menu System Application

This is a lightweight Windows GUI application written in C++ that features a graphical menu and user management using a local JSON file (`users.json`) as a simple database.

## Features

- Graphical menu system built with WinAPI and custom C++ classes
- Local user data handling with a JSON file (`users.json`)
- Modular and extendable structure
- Fast and lightweight – no external database or server required

## Screenshots

**Folder Structure:**

https://prnt.sc/YseRfHhIDdG-

**Application Running:**

https://prnt.sc/f0c6-r6cQCGo

## File Overview

- `main.cpp`: Application entry point. Initializes the menu system.
- `Menu.h` / `Menu.cpp`: Handles creation and interaction of the graphical menu interface.
- `users.json`: Stores user data such as usernames, passwords, and possibly status or preferences. Acts as a lightweight user database.
- `json.hpp`: [nlohmann/json](https://github.com/nlohmann/json) single-header library used for parsing and manipulating JSON in C++.

## Sample `users.json` Structure

```json
[
   {
        "entryTime": "2025-05-05 12:34:14",
        "expectedExitTime": "2025-05-05 14:34:14",
        "login": "viole",
        "name": "Jonathan Coutinho de Moura Cruz",
        "password": "123",
        "placa": "JJJ-123"
    }
]
