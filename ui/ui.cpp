#include <pdcurses.h>
#include <cstdlib>
#include "../array_sequence/array_sequence.hpp"

void array_sequence_menu() {
    ArraySequence<int> sequence;
    int in_progress = 1;
    char buff[15];
    while (in_progress) {
        clear();
        printw("ARRAY SEQUENCE\n");
        printw("Current sequence: ");
        if (sequence.GetLength() == 0) {
            printw("[]");
        } else {
            printw("[");
            for (size_t i = 0; i < sequence.GetLength(); i++) {
                printw("%d", sequence.Get(i));
                if (i < sequence.GetLength() - 1) printw(", ");
            }
            printw("]");
        }
        printw("\n1. Append\n");
        printw("2. Prepend\n");
        printw("3. InsertAt\n");
        printw("4. Back\n");
        printw("Choose:\n");
        refresh();
        int ch = getch();
        switch(ch) {
            case '1':
                echo();
                curs_set(1);
                printw("\nEnter number: ");
                refresh();
                scanw("%s", buff);
                noecho();
                curs_set(0);
                try {
                    char* endptr;
                    errno = 0;
                    long value = strtol(buff, &endptr, 10);
                    if (errno != 0 || *endptr != '\0') {
                        throw InvalidArgumentError("invalid input");
                    }
                    auto new_sequence = sequence.Append(value);
                    sequence = *new_sequence;
                    delete new_sequence;
                } catch (InvalidArgumentError& error){
                    printw("\nError occured: %s", error.what());
                    refresh();
                    getch();
                }
                break;
            case '2':
                echo();
                curs_set(1);
                printw("\nEnter number: ");
                refresh();
                scanw("%s", buff);
                noecho();
                curs_set(0);
                try {
                    char* endptr;
                    errno = 0;
                    long value = strtol(buff, &endptr, 10);
                    if (errno != 0 || *endptr != '\0') {
                        throw InvalidArgumentError("invalid input");
                    }
                    auto new_sequence = sequence.Prepend(value);
                    sequence = *new_sequence;
                    delete new_sequence;
                } catch (InvalidArgumentError& error){
                    printw("\nError occured: %s", error.what());
                    refresh();
                    getch();
                }
                break; 
            case '3':
                echo();
                curs_set(1);
                printw("\nEnter number: ");
                refresh();
                scanw("%s", buff);
                noecho();
                int index;
                try {
                    char* endptr;
                    errno = 0;
                    long value = strtol(buff, &endptr, 10);
                    if (errno != 0 || *endptr != '\0') {
                        throw InvalidArgumentError("invalid input");
                    }
                    auto new_sequence = sequence.InsertAt(value, index);
                    sequence = *new_sequence;
                    delete new_sequence;
                } catch (InvalidArgumentError& error){
                    printw("\nError occured: %s", error.what());
                    refresh();
                    getch();
                    break;
                }
                printw("\nEnter number: ");
                refresh();
                scanw("%s", buff);
                noecho();
                curs_set(0);
                try {
                    char* endptr;
                    errno = 0;
                    long value = strtol(buff, &endptr, 10);
                    if (errno != 0 || *endptr != '\0') {
                        throw InvalidArgumentError("invalid input");
                    }
                    auto new_sequence = sequence.Prepend(value);
                    sequence = *new_sequence;
                    delete new_sequence;
                } catch (InvalidArgumentError& error){
                    printw("\nError occured: %s", error.what());
                    refresh();
                    getch();
                }
                break;
            case '4':
                in_progress = 0;
                break;
        }
    }
}

void open_ui() {
    initscr();
    noecho();
    curs_set(0);
    int in_progress = 1;
    while (in_progress) {
        clear();
        printw("ARRAY SEQUENCE\n");
        printw("1. Array sequence\n");
        printw("2. Exit\n");
        printw("Choose a mode:\n");
        switch(getch()) {
            case '1':
                array_sequence_menu();
                break;
            case '2':
                in_progress = 0;
                break;
        }
    }
    endwin();
}