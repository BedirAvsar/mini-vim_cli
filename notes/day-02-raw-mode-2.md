## Day 2 – Raw Mode & Input Handling

Today I focused on low-level terminal input handling and editor foundations.

### Implemented
- Switched terminal from canonical mode to raw mode using `termios`
- Disabled echo, signal handling, and input post-processing
- Implemented byte-level input reading with `read()`
- Added timeout-based non-blocking input (`VMIN`, `VTIME`)
- Implemented Ctrl-key mapping using bitwise operations
- Parsed ANSI escape sequences for arrow keys
- Introduced editor-level key enums to avoid ASCII collisions

### Key Learnings
- Arrow keys are sent as multi-byte escape sequences, not single ASCII characters
- Raw mode is essential for real-time input handling in terminal applications
- Proper terminal state restoration is critical to avoid broken shells

This marks the foundation of the editor's input engine.