#include <pdcurses.h>
#include <string>
#include "../dynamic_array/dynamic_array.hpp"
#include "../tasks/dictionary.hpp"

DynamicArray<std::string> split_words(const std::string& str) {
    DynamicArray<std::string> words;
    std::string word;
    for (size_t i = 0; i < str.length(); i++) {
        if (str[i] == ' ' || str[i] == '\t') {
            if (word.empty() == 0) {
                words.Resize(words.GetLength() + 1);
                words.Set(words.GetLength() - 1, word);
                word.clear();
            }
        } else {
            word += str[i];
        }
    }
    if (word.empty() == 0) {
        words.Resize(words.GetLength() + 1);
        words.Set(words.GetLength() - 1, word);
    }
    return words;
}

int open_ui() {
    initscr();
    cbreak;
    noecho();
    keypad(stdscr, TRUE);
    curs_set(1);
    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    init_pair(5, COLOR_GREEN, COLOR_BLACK);
    Dictionary dict;
    DequeString input_words;
    int current_tab = 0;
    std::string input_buffer;
    std::string last_input;
    int tab_y = 0;
    int list_start_y = tab_y + 1;
    int input_y = rows - 1;
    bool running = 1;
    while (running) {
        erase();
        if (current_tab == 0) {
            attron(COLOR_PAIR(1));
            mvprintw(tab_y, 1, "[ Dictionary ]");
            attroff(COLOR_PAIR(1));
            attron(COLOR_PAIR(2));
            mvprintw(tab_y, 20, "[ Input ]");
            attroff(COLOR_PAIR(2));
        } else {
            attron(COLOR_PAIR(2));
            mvprintw(tab_y, 2, "[ Dictionary ]");
            attroff(COLOR_PAIR(2));
            attron(COLOR_PAIR(1));
            mvprintw(tab_y, 20, "[ Input ]");
            attroff(COLOR_PAIR(1));
        }
        int list_height = rows - list_start_y - 1;
        if (current_tab == 0) {
            mvprintw(list_start_y - 1, 1, "Banned words:");
            Deque<ArraySequence, std::string> temporary;
            while (!dict.empty()) {
                std::string word = dict.pop_word();
                temporary.push_back(word);
            }
            int y = list_start_y;
            size_t count = 0;
            while ((temporary.empty() == 0) && (count < list_height)) {
                std::string word = temporary.pop_front();
                attron(COLOR_PAIR(4));
                mvprintw(y, 1, "%s", word.c_str());
                attroff(COLOR_PAIR(4));
                dict.push_word(word);
                y++;
                count++;
            }
            while (temporary.empty() == 0) {
                std::string word = temporary.pop_front();
                dict.push_word(word);
            }
        } else {
            DynamicArray<std::string> all_words = split_words(last_input);
            int y = list_start_y;
            for (size_t i = 0; i < all_words.GetLength() && (y < list_start_y + list_height); i++) {
                std::string word = all_words.Get(i);
                bool already_shown = 0;
                for (size_t j = 0; j < i; j++) {
                    if (all_words.Get(j) == word) {
                        already_shown = 1;
                        break;
                    }
                }
                if (already_shown) continue;
                size_t count = 1;
                for (size_t j = i + 1; j < all_words.GetLength(); j++) {
                    if (all_words.Get(j) == word) count++;
                }
                if (dict.is_banned(word)) {
                    attron(COLOR_PAIR(4));
                    mvprintw(y, 1, "  %s: %zu", word.c_str(), count);
                    attroff(COLOR_PAIR(4));
                } else {
                    attron(COLOR_PAIR(5));
                    mvprintw(y, 1, "  %s: %zu", word.c_str(), count);
                    attroff(COLOR_PAIR(5));
                }
                y++;
            }
        }
    endwin();
    return 0;
}