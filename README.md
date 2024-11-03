# Messaging Application

A simple console-based messaging app built with C++ that supports user registration, login, message sending, and data persistence through file storage.

> **Note**: This project is a work in progress and is not entirely complete.

## Features

- **User Registration & Login**: Register and log in with a unique username.
- **Messaging**: Send, view, edit, delete, and search messages.
- **Data Persistence**: Messages are saved to individual text files and reloaded on login.

## Code Overview

### Data Structures

- `message_structure`: Stores message content and timestamp.
- `sender_structure`: Stores user details, inbox, sent messages, and conversation threads.

### Classes

- `userHandling`: Handles registration, login, and user display.
- `messageHandling`: Manages message sending, viewing, editing, deleting, searching, and file I/O.

## Usage

1. **Setup**:
   ```bash
   g++ -o main main.cpp
   ./main
