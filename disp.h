#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include "init.h"
#include "logic.h"

#define CLEAR_ALL "\033[2J\033[?25l" // 清屏，隐藏光标

void print_point(int, int);
void print_food(int x, int y);
void disp_chess();
void print_snake(snake);

void print_point(int x, int y) {
    printf("\033[%d;%dH□\033[0m", x, y * 2);
}

void print_food(int x, int y) {
    printf("\033[%d;%dH■\033[0m", x, y * 2);
}

void disp_chess() {
    printf(CLEAR_ALL);
    int i, j;
    for(i = POINT_1; i <= POINT_1 + CHESS_WIDTH; i++) {
        for(j = POINT_2; j <= POINT_2 + CHESS_HEIGHT; j++) {
            if(i == POINT_1 || i == POINT_1 + CHESS_WIDTH || j == POINT_2 || j == POINT_2 + CHESS_HEIGHT)
                print_point(i, j);
        }
    }
}

void print_snake(snake s) {
    food *p = s.head;
    while(p) {
        print_food(p->x, p->y);
        p = p->next;
    }
}