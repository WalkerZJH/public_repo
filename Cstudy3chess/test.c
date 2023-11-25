//
// Created by Walker on 2023/9/26.
//
#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>

#include "game.h"
int getnums() {
    int input;
    if (scanf("%d", &input) != 1) {
        printf("%s\n", "Invalid input, please try again.");
        while (getchar() != '\n'); // 清除输入缓冲区
        return getnums(); // 递归调用自身，重新获取输入
    }
    return input;
}

void menu()
{
    printf("%s","******************************\n");
    printf("%s","******1. play    0. exit******\n");
    printf("%s","******************************\n");
}
void game()
{
    char ret;
    char board[ROW][COL] = {0};
    initboard(board, ROW, COL);
    displayboard(board, ROW, COL);
//循环
    while(1)
    {
//玩家下棋
        pmove(board, ROW,COL);
//判断输赢
        ret = win(board, ROW,COL,X);
        if(ret!='C')
        {
            break;
        }

//电脑下棋
        cmove(board, ROW, COL);
        displayboard(board, ROW, COL);
        ret = win(board, ROW,COL,X);
        if(ret!='C')
        {
            break;
        }
//判断输赢

    }
    if(ret == '*')
    {
        printf("%s\n", "you win!!");
    } else if(ret =='#')
    {
        printf("%s\n", "you lose!!");
    } else
    {
        printf("%s\n", "nobody win,try again?");
    }
}
void test()
{
    srand((unsigned int )time(NULL));
    int input;
    do {
        menu();

        printf("%s\n", "choose!");

//        防止非法字符
        input = getnums();
        switch (input) {
            case 1:
                printf("%s\n", "play.");
                game();
                break;
            case 0:
                printf("%s\n", "exit.");
                break;
            default:
                printf("%s\n", "invalid input,try again.");
                menu();
                break;

        }
    }while(input);

}
int main(){
    setlocale(LC_ALL, "zh_CN.UTF-8");
    test();
    return 0;
}

