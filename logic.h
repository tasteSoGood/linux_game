#include <malloc.h>
#include "init.h"
#include "function.h"

typedef struct node {
	int x;
	int y;
	struct node *next;
} food;
typedef struct stack {
	food *head;
	int length;
} snake;

int cursor;
int direction = 0;
food f;
snake initial();
void update_snake(snake);
void move(snake);
void gen_food();
void add_snake(snake);

snake initial() {
	snake s;
	s.head = (food *)malloc(sizeof(food));
	s.head->x = randint(POINT_1 + 1, POINT_1 + CHESS_WIDTH);
	s.head->y = randint(POINT_2 + 1, POINT_2 + CHESS_HEIGHT);
	s.head->next = NULL;
	s.length = 1;
	return s;
}

void update_snake(snake s) {
	// 更新
	if(s.length == 1)
		return;
	else {
		food *p = s.head, *q = p->next;
		int pre_x, pre_y, tail_x, tail_y;
		pre_x = p->x, pre_y = p->y, tail_x = q->x, tail_y = q->y;
		while(q) {
			q->x = pre_x, q->y = pre_y;
			pre_x = tail_x, pre_y = tail_y;
			if(q->next)
				pre_x = q->next->x, pre_y = q->y;
			p = p->next, q = q->next;
		}
	}
}

void move(snake s) {
	switch (scanKeyboard()) {
		case 65: direction = 0; break;
		case 66: direction = 1; break;
		case 68: direction = 2; break;
		case 67: direction = 3; break;
		default: break;
	}
	update_snake(s); // 更新一步
	switch(direction) {
		case 0:s.head->x -= 1; break;//上
		case 1:s.head->x += 1; break;//下
		case 2:s.head->y -= 1; break;//左
		case 3:s.head->y += 1; break;//右
		default: break;
	}
	//边缘检测
	if(s.head->x == f.x && s.head->y == f.y) {
		add_snake(s);
		gen_food();
	}
}

void gen_food() {
	food temp;
	temp.x = randint(POINT_1 + 1, POINT_1 + CHESS_WIDTH);
	temp.y = randint(POINT_2 + 1, POINT_2 + CHESS_HEIGHT);
	f = temp;
}

void add_snake(snake s) {
	food *p = s.head;
	food *temp = (food *)malloc(sizeof(food));
	while(p->next != NULL) {
		p = p->next;
	}
	p->next = temp;
	temp->x = p->x;
	temp->y = p->y;
	temp->next = NULL;
	s.length++;
}
