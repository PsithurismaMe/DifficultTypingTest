/*
This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/
#include <ncurses.h>
#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <chrono>


// This function generates a random string
std::string randomString(int length)
{
    std::string random;
    for (int i = 0; i < length; i++)
    {
        random.push_back((char)(rand() % 95 + 32));
    }
    return random;
}

std::string randomStringWithCharset(int length, std::string charset)
{
    std::string random;
    for (int i = 0; i < length; i++)
    {
        random.push_back(charset[(rand() % charset.size()+0)]);
    }
    return random;
}


int main()
{
    srand (time(NULL));
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    int yMax, xMax; 
	getmaxyx(stdscr, yMax, xMax);
    if (has_colors() == FALSE)
    {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }
    start_color();
    
    init_pair(1, COLOR_YELLOW, COLOR_BLACK); // Not typed text
    init_pair(2, COLOR_GREEN, COLOR_BLACK); // correctly typed text
    init_pair(3, COLOR_RED, COLOR_BLACK);   // Incorrectly typed text
    init_pair(4, COLOR_CYAN, COLOR_BLACK);  // Source text
    // instructions
    clear();
    attron(COLOR_PAIR(1));
    mvprintw(0, 0, "This typing test will generate a random sequence of characters present on a QWERTY keyboard.");
    mvprintw(1, 0, "The backspace key does not do anything. Errors in typing will affect your accuracy.");
    mvprintw(2, 0, "Elapsed time will not be shown until the test is finished.");
    mvprintw(3, 0, "The amount of characters generated is equal to the width of the terminal");
    mvprintw(4, 0, "Press Ctrl+C to stop test and abandon progress.");
    mvprintw(5, 0, "Press s to start.");
    attroff(COLOR_PAIR(4));

    refresh();
    while (1)
    {
        int input = getch();
        bool stop = 0;
        switch (input)
        {
        case 115:
            stop = 1;
        default:
            break;
        }
        refresh();
        if (stop == 1)
            break;
    }
    clear();
    // print sequence
    float keysTyped {0};
    attron(COLOR_PAIR(4));
    std::string key;
    key = randomString(xMax);
    mvprintw(0, 0, "%s", key.c_str());
    attroff(COLOR_PAIR(4));
    attron(COLOR_PAIR(1));
    mvprintw(2, 0, "%s", key.c_str());
    attroff(COLOR_PAIR(1));
    mvprintw(5, 0, "Percentage complete: 0%%");
    
    

    refresh();
    std::string buffer;
    auto start = std::chrono::high_resolution_clock::now();
    while (keysTyped < xMax)
    {
        int input = getch();
        mvprintw(5, 0, "Percentage complete: %f%%", (100*(keysTyped/ (float) xMax)));
        switch (input)
        {
        case KEY_BACKSPACE:
            /*
            if (keysTyped > 0)
                keysTyped--;
                buffer.pop_back();
            */
            break;
        
        default:
            buffer.push_back(input);
            if (input == key[keysTyped])
            {
                attron(COLOR_PAIR(2));
                mvaddch(2, keysTyped, input);
                attroff(COLOR_PAIR(2));
                keysTyped++;
            } else if (input > 31 && input < 127) {
                attron(COLOR_PAIR(3));
                mvaddch(2, keysTyped, input);
                attroff(COLOR_PAIR(3));
                keysTyped++;
            }
            break;
        }
        
        refresh();
        
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    float numberator = xMax;
    const float denominator = xMax;
    for (int i = 0; i < key.size(); i++)
    {
        if (key[i] != buffer[i])
        {
            numberator--;
        }
    }

    clear();
    attron(COLOR_PAIR(1));
    float time = duration.count();
    time = time / 1000;
    mvprintw(0, 0, "Time to completion: %f seconds", (time));
    mvprintw(1, 0, "Typing Speed: %f characters per second", (keysTyped/time));
    mvprintw(2, 0, "Average english typing speed: %f words per minute", ((keysTyped/5) / time)*60);
    mvprintw(3, 0, "Accuracy: %f%%", ((100*(numberator) / (denominator))));
    mvprintw(4, 0, "Typing speed accounting for accuracy: %f characters per second", ((keysTyped/time)*(numberator) / (denominator)));
    refresh();
    for (int i = 5; i != 0; i--)
    {
        mvprintw(5, 0, "Press any key %d time(s) to exit", i);
        getch();
        refresh();
    }
    endwin();

}
