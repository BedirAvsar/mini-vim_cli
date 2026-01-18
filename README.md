# Mini-Vim

Mini-Vim is a small terminal-based text editor written entirely in C.

This project was created as a learning exercise to understand how text editors work internally at a low level where the program interacts directly with the terminal and the operating system. By intentionally avoiding libraries such as ncurses and graphical toolkits, Mini-Vim focuses on providing a clean and understandable editor core that demonstrates raw terminal control.

Mini-Vim is not intended to be a full-featured editor like Vim or Nano.  
Instead, it focuses on building the essential functionality of an editor from scratch.

---

## Video Demo

https://youtu.be/IolFu1iid_4 
---

## Motivation

Modern text editors abstract away many important details using libraries and frameworks. As a junior developer switching from mechanical engineering to software development, I wanted to understand:

- How terminals handle keyboard input in real time  
- How text editors react instantly without buffering lines  
- How text is stored, extended, and modified dynamically  
- How screens are redrawn manually using escape sequences  
- How raw mode overrides normal terminal behavior  

This project was designed to answer all of these questions through direct implementation using only C and POSIX system calls.

---

## Features

Mini-Vim implements the foundational parts of a text editor:

### ✔ Raw Mode Terminal Control
The program switches the terminal into raw mode by disabling:

- Character echoing  
- Canonical line mode  
- Ctrl-C / Ctrl-Z signals  
- Software flow control (Ctrl-S / Ctrl-Q)  
- Output post-processing  

This gives full control over all input and output.

### ✔ Keyboard Input Handling
Input is read **byte-by-byte**, allowing:

- Arrow key movement  
- ESC sequence decoding  
- Custom key mappings  
- CTRL-key combinations (e.g., Ctrl-X to exit)  

### ✔ Text Buffer System
Text is stored in a dynamically allocated structure:

```c
typedef struct erow {
    int size;
    char *chars;
} erow;
```

This buffer grows with user input and supports:

- Adding characters  
- Appending rows  
- Storing lines independently  

### ✔ Screen Rendering Engine
The screen is fully redrawn on each key press using ANSI escape codes:

- Clear screen  
- Move cursor  
- Draw buffer rows  
- Restore cursor position  

This mimics the low-level behavior of editors like Vim.

---

## High-Level Program Flow

1. Initialize global editor state  
2. Enable terminal raw mode  
3. Enter input loop:
   - Read one key
   - Process editor state
   - Redraw entire screen  
4. Exit editor and restore terminal settings  

This loop continues until the user presses **Ctrl-X**.

---

## Real-World Learning Outcomes

Building Mini-Vim helped me understand fundamental systems programming concepts such as:

- Low-level terminal I/O  
- Event-driven program design  
- Memory allocation and management in C  
- Screen rendering without graphics libraries  
- Multicomponent project organization  
- POSIX escape sequences and termios  

These skills are applicable to shells, debuggers, log viewers, and many other low-level tools.

---

## Build & Run Instructions

Requirements:

- GCC or Clang
- Linux or macOS terminal environment

### Build:

```bash
make
```

### Run:

```bash
./mini-vim
```

### Exit Mini-Vim:

```
CTRL + X
```

---
## Run with Docker

```bash
docker build -t mini-vim .
docker run -it mini-vim
```

This project uses a multi-stage Docker build to produce a small, clean runtime image containing only the compiled binary.

## Project Structure

```
mini-vim/
├── include/
│   ├── editor.h      # Editor state and screen logic
│   ├── input.h       # Raw input and key decoding
│   ├── buffer.h      # Text buffer structures
│   └── syntax.h      # Placeholder for future syntax highlighting
├── src/
│   ├── main.c        # Entry point and main loop
│   ├── editor.c      # Raw mode, rendering, cursor movement
│   ├── input.c       # Reading and decoding keystrokes
│   └── buffer.c      # Row/character management
├── tests/            # Future test scripts
├── Makefile
└── README.md
```

---

## Current Status (v1)

The core editor is fully functional:

- Raw mode input  
- Cursor movement  
- Dynamic buffer  
- Screen refresh  

Possible future improvements:

- Saving files  
- Loading files  
- Multiple rows editing  
- Scrolling support  
- Syntax highlighting  
- Status bar  

---

## What I Learned

During this project, I gained hands-on experience with:

- Raw terminal handling  
- Escape sequences  
- Memory reallocation  
- Buffer management  
- Modular C programming  
- Terminal rendering performance  
- Understanding how editors like Vim work internally  

This project significantly increased my confidence in low-level C programming and systems development.

---

## Notes

This project is inspired by the famous "kilo" text editor by Salvatore Sanfilippo (antirez).  
While the structure is similar, I rewrote major parts, reorganized the code, and added my own explanations and comments to reinforce understanding.

---

## Conclusion

Mini-Vim is a foundational systems programming project that demonstrates how a text editor works from the inside out. It was both challenging and highly educational, giving me deeper insight into terminal behavior, event loops, memory management, and low-level C programming.

Thank you for reviewing my CS50 Final Project!
