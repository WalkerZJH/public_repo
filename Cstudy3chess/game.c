//
// Created by Walker on 2023/9/26.
//
#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include "game.h"
int getnum() {
    int input;
    if (scanf("%d", &input) != 1) {
        printf("%s\n", "Invalid input, please try again.");
        while (getchar() != '\n'); // 清除输入缓冲区
        return getnum(); // 递归调用自身，重新获取输入
    }
    return input;
}

void initboard(char board[ROW][COL],int row, int col)
{
    for(int i = 0;i<row;i++)
    {
        for(int j = 0;j<col;j++)
        {
            board[i][j] = ' ';
        }
    }

}
void displayboard(char board[ROW][COL], int row, int col)
{
    int j,i;
    for (i = 0; i < row; i++) {
        if (i == row - 1) {
            for (j = 0; j < col; j++)
            {
                if (j == col - 1)
                {
                    printf( " %c \n", board[i][j]);
                    break;
                }
                else
                {
                    printf( " %c |",board[i][j]);
                }
            }
            continue;
        }
        for (j = 0; j < col; j++)
        {
            if (j == col - 1)
            {
                printf(" %c \n", board[i][j]);
            }
            else
            {
                printf( " %c |",board[i][j]);
            }
        }
        for (j = 0; j < col; j++)
        {
            if (j == col-1)
            {
                printf("%s", "---\n");
                break;
            }
            else
            {
                printf("%s", "---|");
            }
        }
    }

}
void pmove(char board[ROW][COL], int row, int col)
{
    int x = 0,y = 0;
    printf("%s\n", "player's turn!");
    while(1)
    {
        printf("%s\n","where?\nrow(enter)\ncol(enter)");
        x = getnum();
        y = getnum();
        if (x>=1 && x<=row && y>=1 && y<=col)
        {
            if(board[x-1][y-1]==' ') {
                board[x - 1][y - 1] = '*';
                break;
            } else
            {
                printf("%s\n", "you can't place your stone here,it's occupied.");

            }
        }else
        {
            printf("%s\n", "invalid input,try again!");


        }
    }
}

void cmove(char board[ROW][COL], int row, int col) {
    printf("%s\n", "computer's turn!");
    while (1) {
        int x = rand() % row;
        int y = rand() % col;
        if (board[x][y] == ' ') {
            board[x][y] = '#';
            break;
        }
    }
}
char isRow(char arr[][COL], int row, int col, int x) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j <= col - x; j++) {
            bool Equal = true;

            for (int k = 1; k < x; k++) {
                if (arr[i][j + k] != arr[i][j + k - 1]) {
                    Equal = false;
                    break;
                }
            }

            if (Equal && arr[i][j] != ' ') {
                return arr[i][j];
            }
        }
    }
    return 'x';
}

//判断列
char isCol(char arr[][COL], int row, int col, int x) {
    for (int j = 0; j < col; j++) {
        for (int i = 0; i <= row - x; i++) {
            bool Equal = true;
            for (int k = 1; k < x; k++) {
                if (arr[i + k][j] != arr[i + k - 1][j]) {
                    Equal = false;
                    break;
                }
            }

            if (Equal && arr[i][j] != ' ') {
                return arr[i][j];
            }
        }
    }
    return 'x';
}

char isDiagonal(char arr[][COL], int row, int col, int x) {
    for (int i = 0; i <= row - x; i++) {
        for (int j = 0; j <= col - x; j++) {
            bool Equal = true;

            for (int k = 1; k < x; k++) {
                if (arr[i + k][j + k] != arr[i + k - 1][j + k - 1]) {
                    Equal = false;
                    break;
                }
            }

            if (Equal && arr[i][j] != ' ') {
                return arr[i][j];
            }
        }
    }
    return 'x';
}

char isSDiagonal(char arr[][COL], int row, int col, int x) {
    for (int i = 0; i <= row - x; i++) {
        for (int j = col - 1; j >= x - 1; j--) {
            bool Equal = true;

            for (int k = 1; k < x; k++) {
                if (arr[i + k][j - k] != arr[i + k - 1][j - k + 1]) {
                    Equal = false;
                    break;
                }
            }

            if (Equal && arr[i][j] != ' ') {
                return arr[i][j];
            }
        }
    }
    return 'x';
}


//判断棋盘是否满了
bool isfull(char board[ROW][COL], int row, int col)
{
    for(int i=0; i<row; i++)
    {
        for (int j = 0; j < col; ++j)
        {
            if(board[i][j]==' ')
            {
                return false;
            }
        }
    }
    return true;
}
char win(char board[ROW][COL], int row, int col,int x)
{
    if(isRow(board,row,col,x)!='x')
    {
        return isRow(board,row,col,x);
    }
    else if (isCol(board,row,col,x)!='x')
    {
        return isCol(board,row,col,x);
    }
    else if (isDiagonal(board,row,col,x)!='x')
    {
        return isDiagonal(board,row,col,x);
    }
    else if (isSDiagonal(board,row,col,x)!='x')
    {
        return isSDiagonal(board,row,col,x);
    }
    if (isfull(board, ROW , COL))
    {
        return '-';
    }
    return 'C';
}
