/*Hello World, this is my first personal project and I've tried to explain
what's happening here as clearly as possible.
General comments are English and my explanation is in Turkish.*/

#include <unistd.h>  // read(), STDIN_FILENO
#include <termios.h> // struct termios, tcgetattr(), tcsetattr()
#include <stdlib.h>  // atexit(), exit()
#include <stdio.h>   // perror()
#include <errno.h>   // error code
#include <ctype.h>   // iscntrl()

#define CTRL_KEY(k) ((k) & 0x1f) // Swap 

// SPECIAL ENUM
enum editorKey {
    ARROW_LEFT = 1000,
    ARROW_RIGHT,
    ARROW_UP,
    ARROW_DOWN
};

struct termios orig_termios; // Original terminal state 

void die(const char *s) { 
    perror(s);
    exit(1);
}

// Restore terminal to original state
void disableRawMode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1) {
    die("tcsetattr");  
    }
}

void enableRawMode() {
    // Get current attributes
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) {
        perror("tcgetattr");
        exit(1);
    }
    atexit(disableRawMode); // Restore on exit

    struct termios raw = orig_termios; // Don't touch original settings

    // Input flags: Disable Ctrl-S/Q, fix Ctrl-M
    raw.c_iflag &= ~(ICRNL | IXON);

    // Output flags: Disable processing
    raw.c_oflag &= ~(OPOST);

    // Local flags: Disable echo, canonical mode, signals
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

    // Control flags: Set 8-bit characters
    raw.c_cflag |= (CS8);

    // Time rules
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    // Apply new attributes
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
        perror("tcsetattr");
        exit(1);
    }
}

int editorReadKey(void) {
    char c;
    int nread;

    while ((nread = read(STDERR_FILENO, &c, 1)) != 1) {
        if (nread == -1 && errno != EAGAIN) {
            die("read");
        }
    }
    
    // ESCAPE SEQUENCE?
    if (c == '\x1b') {
        char seq[3];

        // ESC
        if (read(STDIN_FILENO, &seq[0], 1) != 1) return '\x1b';
        if (read(STDIN_FILENO, &seq[1], 1) != 1) return '\x1b';

        if (seq[0] == '[') {
            switch (seq[1]) {
                case 'A': return ARROW_UP;
                case 'B': return ARROW_DOWN;
                case 'C': return ARROW_RIGHT;
                case 'D': return ARROW_LEFT;
            }
        }
        return '\x1b';
    }
    return c;
}

int main(void) {
    enableRawMode(); 

    char c;
    // Read byte-by-byte until 'q'
    while (1) { 
        char c;
        int nread = read(STDIN_FILENO, &c, 1);  
        if ( nread == -1 && errno != EAGAIN) {  
            die("read");
        }
        if (iscntrl (c)) { // ASCII CONTROL
            printf("%d\r\n", c);  // Print Value
        }
        else {
            printf("%d ('%c')\r\n", c, c);
        }
        if (c == CTRL_KEY('q'))

        break;
    }    
    return 0;
}