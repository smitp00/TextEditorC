//school project for low level programming course
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 999
#define MAX_CHARS_PER_LINE 999

char text[MAX_LINES][MAX_CHARS_PER_LINE];
int num_lines = 0;
int cx = 0, cy = 0;

void init_editor() {
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
}

void draw_editor() {
    for (int i = 0; i < num_lines; i++) {
        mvprintw(i, 0, "%s", text[i]);
    }
}

void insert_char(int y, int x, char c) {
    if (text[y][x] == '\0') {
        text[y][x] = c;
        text[y][x+1] = '\0';
    } else {
        for (int i = strlen(text[y]); i >= x; i--) {
            text[y][i+1] = text[y][i];
        }
        text[y][x] = c;
    }
}

void delete_char(int y, int x) {
    if (x >= 1) {
        for (int i = x; i < strlen(text[y]); i++) {
            text[y][i-1] = text[y][i];
        }
        text[y][strlen(text[y])-1] = '\0';
        cx--;
    }
}

int main() {
    
    int ch;

    init_editor();

    while (1) {
        clear();
        draw_editor();
        move(cy, cx);

        ch = getch();
        switch(ch) {
            case KEY_UP:
                if (cy > 0) cy--;
                break;
            case KEY_DOWN:
                if (cy < num_lines - 1) cy++;
                break;
            case KEY_LEFT:
                if (cx > 0) cx--;
                break;
            case KEY_RIGHT:
                if (cx < strlen(text[cy])) cx++;
                break;
            case KEY_BACKSPACE:
            case 127:  // handle the DEL key as backspace 
                delete_char(cy, cx);
                break;
            case 27: // ESC key to end the program / text editor
                endwin();
                return 0;
                break;
            default:
                if (num_lines == 0) {
                    text[0][0] = '\0';
                    num_lines++;
                }
                insert_char(cy, cx, ch);
                cx++;
                break;
        }
    }

    endwin();
    return 0;
}
