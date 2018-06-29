#include <stdio.h>
#include <unistd.h>
#include <termio.h>
#include "disp.h"
#include "init.h"

int main(){
    srand((unsigned)time(NULL));
    snake s = initial();
    gen_food();
    while(1) {
        printf(CLEAR_ALL);
        disp_chess();
        move(s);
        print_food(f.x, f.y);
        sleep(0.1);
    }
    return 0;
}