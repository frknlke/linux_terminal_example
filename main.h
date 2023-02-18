#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
int x = 6;
void split_string(char *input, char *comm, char *arg1, char *arg2, char *arg3);
int getCommandType(char *input);
void historyHandler(char input[15][100], char *lastCmd, int *number);
int isInHistory(char input[15][100], char *lastCmd);
void readLine(char *fileName);
#endif