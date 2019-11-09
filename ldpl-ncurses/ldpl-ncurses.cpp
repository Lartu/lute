#include <stdlib.h>
#include <ncurses.h>
#include <curses.h>
#include <signal.h>
#include "ldpl-types.h"

static void finish(int sig)
{
    nocbreak();
    endwin();

    /* do your non-curses wrapup here */

    exit(0);
}

void NCURSES_LDPLLIB_INITIALIZE_SCREEN(){
    setlocale(LC_ALL, "");
    initscr();
    nonl();
    keypad(stdscr, TRUE);
    signal(SIGINT, finish);
    cbreak();
    refresh();
}

void NCURSES_LDPLLIB_END_SCREEN(){
    nocbreak();
    endwin();
}

/*void NCURSES_LDPLLIB_MODE_CBREAK(){
    cbreak();
}

void NCURSES_LDPLLIB_MODE_COOKED(){
    nocbreak();
}*/

void NCURSES_LDPLLIB_MODE_ECHO(){
    echo();
}

void NCURSES_LDPLLIB_MODE_NOECHO(){
    noecho();
}

void NCURSES_LDPLLIB_MODE_GET_BLOCKING(){
    nodelay(stdscr, FALSE);
}

void NCURSES_LDPLLIB_MODE_GET_NOTBLOCKING(){
    nodelay(stdscr, TRUE);
}

void NCURSES_LDPLLIB_REFRESH(){
    refresh();
}

void NCURSES_LDPLLIB_ENABLE_COLOR(){
    if (has_colors())
    {
        start_color();
        init_pair( 1, COLOR_RED,     COLOR_BLACK);
        init_pair( 2, COLOR_GREEN,   COLOR_BLACK);
        init_pair( 3, COLOR_YELLOW,  COLOR_BLACK);
        init_pair( 4, COLOR_BLUE,    COLOR_BLACK);
        init_pair( 5, COLOR_CYAN,    COLOR_BLACK);
        init_pair( 6, COLOR_MAGENTA, COLOR_BLACK);
        init_pair( 7, COLOR_WHITE,   COLOR_BLACK);
        
        init_pair( 8, COLOR_GREEN,   COLOR_RED);
        init_pair( 9, COLOR_YELLOW,  COLOR_RED);
        init_pair(10, COLOR_BLUE,    COLOR_RED);
        init_pair(11, COLOR_CYAN,    COLOR_RED);
        init_pair(12, COLOR_MAGENTA, COLOR_RED);
        init_pair(13, COLOR_WHITE,   COLOR_RED);
        init_pair(13, COLOR_BLACK,   COLOR_RED);
        
        init_pair(14, COLOR_RED,     COLOR_GREEN);
        init_pair(15, COLOR_YELLOW,  COLOR_GREEN);
        init_pair(16, COLOR_BLUE,    COLOR_GREEN);
        init_pair(17, COLOR_CYAN,    COLOR_GREEN);
        init_pair(18, COLOR_MAGENTA, COLOR_GREEN);
        init_pair(19, COLOR_WHITE,   COLOR_GREEN);
        init_pair(20, COLOR_BLACK,   COLOR_GREEN);
        
        init_pair(21, COLOR_RED,     COLOR_YELLOW);
        init_pair(22, COLOR_GREEN,   COLOR_YELLOW);
        init_pair(23, COLOR_BLUE,    COLOR_YELLOW);
        init_pair(24, COLOR_CYAN,    COLOR_YELLOW);
        init_pair(25, COLOR_MAGENTA, COLOR_YELLOW);
        init_pair(26, COLOR_WHITE,   COLOR_YELLOW);
        init_pair(27, COLOR_BLACK,   COLOR_YELLOW);
        
        init_pair(28, COLOR_RED,     COLOR_BLUE);
        init_pair(29, COLOR_GREEN,   COLOR_BLUE);
        init_pair(30, COLOR_YELLOW,  COLOR_BLUE);
        init_pair(31, COLOR_CYAN,    COLOR_BLUE);
        init_pair(32, COLOR_MAGENTA, COLOR_BLUE);
        init_pair(33, COLOR_WHITE,   COLOR_BLUE);
        init_pair(34, COLOR_BLACK,   COLOR_BLUE);
        
        init_pair(35, COLOR_RED,     COLOR_CYAN);
        init_pair(36, COLOR_GREEN,   COLOR_CYAN);
        init_pair(37, COLOR_YELLOW,  COLOR_CYAN);
        init_pair(38, COLOR_BLUE,    COLOR_CYAN);
        init_pair(39, COLOR_MAGENTA, COLOR_CYAN);
        init_pair(40, COLOR_WHITE,   COLOR_CYAN);
        init_pair(41, COLOR_BLACK,   COLOR_CYAN);
        
        init_pair(42, COLOR_RED,     COLOR_MAGENTA);
        init_pair(43, COLOR_GREEN,   COLOR_MAGENTA);
        init_pair(44, COLOR_YELLOW,  COLOR_MAGENTA);
        init_pair(45, COLOR_BLUE,    COLOR_MAGENTA);
        init_pair(46, COLOR_CYAN,    COLOR_MAGENTA);
        init_pair(47, COLOR_WHITE,   COLOR_MAGENTA);
        init_pair(48, COLOR_BLACK,   COLOR_MAGENTA);
        
        init_pair(49, COLOR_RED,     COLOR_WHITE);
        init_pair(50, COLOR_GREEN,   COLOR_WHITE);
        init_pair(51, COLOR_YELLOW,  COLOR_WHITE);
        init_pair(52, COLOR_BLUE,    COLOR_WHITE);
        init_pair(53, COLOR_CYAN,    COLOR_WHITE);
        init_pair(54, COLOR_MAGENTA, COLOR_WHITE);
        init_pair(55, COLOR_BLACK,   COLOR_WHITE);
    }
}

ldpl_number NCURSES_LDPLLIB_COLOR = 12;

void NCURSES_LDPLLIB_SET_CHARCOLOR(){
    if(NCURSES_LDPLLIB_COLOR <= 0) NCURSES_LDPLLIB_COLOR = 1;
    else if(NCURSES_LDPLLIB_COLOR > 49) NCURSES_LDPLLIB_COLOR = 49;
    attrset(COLOR_PAIR((short int)NCURSES_LDPLLIB_COLOR));
}

ldpl_number NCURSES_LDPLLIB_W = 0;
ldpl_number NCURSES_LDPLLIB_H = 0;
void NCURSES_LDPLLIB_SIZE(){
    getmaxyx(stdscr, NCURSES_LDPLLIB_H, NCURSES_LDPLLIB_W);
}

ldpl_number NCURSES_LDPLLIB_X = 0;
ldpl_number NCURSES_LDPLLIB_Y = 0;
void NCURSES_LDPLLIB_MOVE(){
    move((int) NCURSES_LDPLLIB_Y, (int) NCURSES_LDPLLIB_X);
}

ldpl_text NCURSES_LDPLLIB_TEXT = "";
void NCURSES_LDPLLIB_WRITE(){
    addstr(NCURSES_LDPLLIB_TEXT.str_rep().c_str());
}

void NCURSES_LDPLLIB_SHOWCURSOR(){
    curs_set(1);
}

void NCURSES_LDPLLIB_HIDECURSOR(){
    curs_set(0);
}

std::string UnicodeToUTF8(unsigned int codepoint)
{
    //Taken from https://stackoverflow.com/questions/19968705/unsigned-integer-as-utf-8-value
    //Written by Mark Ransom

    std::string out;

    if (codepoint <= 0x7f)
        out.append(1, static_cast<char>(codepoint));
    else if (codepoint <= 0x7ff)
    {
        out.append(1, static_cast<char>(0xc0 | ((codepoint >> 6) & 0x1f)));
        out.append(1, static_cast<char>(0x80 | (codepoint & 0x3f)));
    }
    else if (codepoint <= 0xffff)
    {
        out.append(1, static_cast<char>(0xe0 | ((codepoint >> 12) & 0x0f)));
        out.append(1, static_cast<char>(0x80 | ((codepoint >> 6) & 0x3f)));
        out.append(1, static_cast<char>(0x80 | (codepoint & 0x3f)));
    }
    else
    {
        out.append(1, static_cast<char>(0xf0 | ((codepoint >> 18) & 0x07)));
        out.append(1, static_cast<char>(0x80 | ((codepoint >> 12) & 0x3f)));
        out.append(1, static_cast<char>(0x80 | ((codepoint >> 6) & 0x3f)));
        out.append(1, static_cast<char>(0x80 | (codepoint & 0x3f)));
    }
    return out;
}

ldpl_text NCURSES_LDPLLIB_CHAR = "";
void NCURSES_LDPLLIB_GETCHAR(){
    wint_t wchar;
    int isKeycode = get_wch(&wchar);
    if(isKeycode == KEY_CODE_YES){
        switch(wchar){
            case KEY_UP:
                NCURSES_LDPLLIB_CHAR = "UP";
                break;
            case KEY_LEFT:
                NCURSES_LDPLLIB_CHAR = "LEFT";
                break;
            case KEY_RIGHT:
                NCURSES_LDPLLIB_CHAR = "RIGHT";
                break;
            case KEY_DOWN:
                NCURSES_LDPLLIB_CHAR = "DOWN";
                break;
            case KEY_NPAGE:
                NCURSES_LDPLLIB_CHAR = "PAGEDOWN";
                break;
            case KEY_PPAGE:
                NCURSES_LDPLLIB_CHAR = "PAGEUP";
                break;
            case KEY_HOME:
                NCURSES_LDPLLIB_CHAR = "HOME";
                break;
            case KEY_END:
                NCURSES_LDPLLIB_CHAR = "END";
                break;
            case KEY_IC:
                NCURSES_LDPLLIB_CHAR = "INSERT";
                break;
            case KEY_DC:
                NCURSES_LDPLLIB_CHAR = "DELETE";
                break;
            case KEY_BACKSPACE:
                NCURSES_LDPLLIB_CHAR = "BACKSPACE";
                break;
            case KEY_ENTER:
                NCURSES_LDPLLIB_CHAR = "ENTER";
                break;
        }
    }else if(isKeycode == OK){
        if((unsigned int) wchar == ('q' & 0x1f)){
                NCURSES_LDPLLIB_CHAR = "C-Q";
                return;
        }else if((unsigned int) wchar == ('w' & 0x1f)){
                NCURSES_LDPLLIB_CHAR = "C-W";
                return;
        }else if((unsigned int) wchar == ('e' & 0x1f)){
                NCURSES_LDPLLIB_CHAR = "C-E";
                return;
        }else if((unsigned int) wchar == ('r' & 0x1f)){
                NCURSES_LDPLLIB_CHAR = "C-R";
                return;
        }else if((unsigned int) wchar == ('t' & 0x1f)){
                NCURSES_LDPLLIB_CHAR = "C-T";
                return;
        }else if((unsigned int) wchar == ('y' & 0x1f)){
                NCURSES_LDPLLIB_CHAR = "C-Y";
                return;
        }else if((unsigned int) wchar == ('u' & 0x1f)){
                NCURSES_LDPLLIB_CHAR = "C-U";
                return;
        }else if((unsigned int) wchar == ('i' & 0x1f)){
                NCURSES_LDPLLIB_CHAR = "C-I";
                return;
        }else if((unsigned int) wchar == ('o' & 0x1f)){
                NCURSES_LDPLLIB_CHAR = "C-O";
                return;
        }else if((unsigned int) wchar == ('p' & 0x1f)){
                NCURSES_LDPLLIB_CHAR = "C-P";
                return;
        }else if((unsigned int) wchar == ('a' & 0x1f)){
                NCURSES_LDPLLIB_CHAR = "C-A";
                return;
        }else if((unsigned int) wchar == ('s' & 0x1f)){
                NCURSES_LDPLLIB_CHAR = "C-S";
                return;
        }else if((unsigned int) wchar == ('d' & 0x1f)){
                NCURSES_LDPLLIB_CHAR = "C-D";
                return;
        }else if((unsigned int) wchar == ('f' & 0x1f)){
                NCURSES_LDPLLIB_CHAR = "C-F";
                return;
        }else if((unsigned int) wchar == ('g' & 0x1f)){
                NCURSES_LDPLLIB_CHAR = "C-G";
                return;
        }else if((unsigned int) wchar == ('h' & 0x1f)){
                NCURSES_LDPLLIB_CHAR = "C-H";
                return;
        }else if((unsigned int) wchar == ('j' & 0x1f)){
                NCURSES_LDPLLIB_CHAR = "C-J";
                return;
        }else if((unsigned int) wchar == ('k' & 0x1f)){
                NCURSES_LDPLLIB_CHAR = "C-K";
                return;
        }else if((unsigned int) wchar == ('l' & 0x1f)){
                NCURSES_LDPLLIB_CHAR = "C-L";
                return;
        }else if((unsigned int) wchar == ('z' & 0x1f)){
                NCURSES_LDPLLIB_CHAR = "C-Z";
                return;
        }else if((unsigned int) wchar == ('x' & 0x1f)){
                NCURSES_LDPLLIB_CHAR = "C-X";
                return;
        }else if((unsigned int) wchar == ('c' & 0x1f)){
                NCURSES_LDPLLIB_CHAR = "C-C";
                return;
        }else if((unsigned int) wchar == ('v' & 0x1f)){
                NCURSES_LDPLLIB_CHAR = "C-V";
                return;
        }else if((unsigned int) wchar == ('b' & 0x1f)){
                NCURSES_LDPLLIB_CHAR = "C-B";
                return;
        }else if((unsigned int) wchar == ('n' & 0x1f)){
                NCURSES_LDPLLIB_CHAR = "C-N";
                return;
        }else if((unsigned int) wchar == ('m' & 0x1f)){
                NCURSES_LDPLLIB_CHAR = "C-M";
                return;
        }else if((unsigned int) wchar == 13){
                NCURSES_LDPLLIB_CHAR = "ENTER";
                return;
        }
        NCURSES_LDPLLIB_CHAR = UnicodeToUTF8((unsigned int) wchar);
    }else{
        NCURSES_LDPLLIB_CHAR = "";
    }
}