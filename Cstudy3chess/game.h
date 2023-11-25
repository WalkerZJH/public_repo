//
// Created by Walker on 2023/9/26.
//

#ifndef CSTUDY3_GAME_H
#define CSTUDY3_GAME_H
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#define ROW 20
#define COL 20
#define X 5
void initboard(char board[ROW][COL], int row, int col);
void displayboard(char board[ROW][COL], int row, int col);
void pmove(char board[ROW][COL], int row, int col);
void cmove(char board[ROW][COL], int row, int col);
//win()判断1.玩家赢2.电脑赢3.平局4.未结束
//1 '*'
//2 '#'
//3 '-'
//4 'C'(tinue)
char win(char board[ROW][COL], int row, int col,int x);
#endif //CSTUDY3_GAME_H
