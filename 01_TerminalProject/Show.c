#include <locale.h>
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>

#define DX 7
#define DY 3

#define FRAME_HEIGHT LINES - 2 * DY
#define FRAME_WIDTH COLS - 2 * DX
#define WINDOW_HEIGHT FRAME_HEIGHT - 2
#define WINDOW_WIDTH FRAME_WIDTH - 2
#define WINDOW_DY DY + 1
#define WINDOW_DX DX + 1

typedef struct file_strings {
    char *string;
    struct file_strings *next;
} file_strings;

file_strings* initialize(FILE* file) {
    file_strings *result = NULL;
    file_strings *current_element = result;
    for (unsigned int i = 0; i < WINDOW_HEIGHT; ++i) {
        char *buffer = malloc(WINDOW_WIDTH + 1);
        size_t buffer_length = WINDOW_WIDTH + 1;
        ssize_t size = getline(&buffer, &buffer_length, file);
        if (size == -1)
            break;
        if (buffer[size - 1] == '\n')
            buffer[size - 1] = '\0';

        if (current_element == NULL) {
            current_element = malloc(sizeof(file_strings));
            result = current_element;
        } else {
            current_element->next = malloc(sizeof(file_strings));
            current_element = current_element->next;
        }
        current_element->string = buffer;
        current_element->next = NULL;
    }
    return result;
}

file_strings* update(FILE* file, file_strings* head) {
    if (head != NULL) {
        file_strings *new_head = head->next;
        free(head->string);
        free(head);
        head = new_head;
    }

    char *buffer = malloc(WINDOW_WIDTH + 1);
    size_t buffer_length = WINDOW_WIDTH + 1;
    ssize_t size = getline(&buffer, &buffer_length, file);
    if (size == -1)
        return head;

    file_strings *new_element = head;
    while (new_element->next != NULL)
        new_element = new_element->next;

    if (buffer[size - 1] == '\n')
        buffer[size - 1] = '\0';
    
    new_element->next = malloc(sizeof(file_strings));
    new_element = new_element->next;
    new_element->string = buffer;
    new_element->next = NULL;

    return head;
}

int main(int argc, char **argv) {
    FILE *file;
    char *filename;
    if (argv[1] != NULL) {
        filename = argv[1];
    } else {
        filename = "Show.c";
    }
    file = fopen(filename, "r");


    WINDOW *frame, *win;
    int c = 0;
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    cbreak();

    file_strings* head = initialize(file);

    printw("Window:");
    refresh();
    frame = newwin(LINES - 2*DY, COLS - 2*DX, DY, DX);
    box(frame, 0, 0);
    mvwaddstr(frame, 0, (int)((COLS - 2*DX - 5) / 2), "Frame");
    wrefresh(frame);
    win = newwin(LINES - 2*DY - 2, COLS - 2*DX-2, DY+1, DX+1);
    keypad(win, TRUE);
    do {
        if (c == ' ') {
            head = update(file, head);
        }
        file_strings *current_element = head;
        werase(win);
        for (int i = 0; i < WINDOW_HEIGHT && current_element != NULL; ++i) {
            wprintw(win, "%s\n", current_element->string);
            current_element = current_element->next;
        }
    } while ((c = wgetch(win)) != 27);
    while (head != NULL) {
        file_strings *old_head = head;
        head = head->next;
        free(old_head->string);
        free(old_head);
    }
    delwin(win);
    delwin(frame);
    endwin();
    return 0;
}
