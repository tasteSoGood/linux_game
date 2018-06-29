#include <windows.h>
#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node {
    int x, y;
    struct node *next;
} food;

typedef struct list {
    food *head;
    int length;
} snake;

snake initial() {
    // 初始化
    snake s;
    s.head = (food *)malloc(sizeof(food));
    s.head->x = randint(0, 10);
    s.head->y = randint(0, 10);
    s.length = 0;
}

void update(snake s) {
    // 更新
    food *p = s.head, *q = p->next;
    int s_x = p->x, s_y = p->y, t_x = q->x, t_y = q->y;
    while(q) {
        q->x = s_x, q->y = s_y;
        s_x = t_x, s_y = t_y;
        q = q->next;
        if(q) {
            t_x = q->x, t_y = q->y;
        }
    }
}

int randint(int a, int b) {
    return (int)(((float)rand() / INT_MAX) * (b - a) + a);
}

int main() {
    srand((unsigned int)time(NULL));
    return 0;
}