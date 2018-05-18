#ifndef POSTMACHINE_POST_H
#define POSTMACHINE_POST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//#define bool char
//#define false 0
//#define true 1

#define TAPE_SIZE 50
#define TAPE_RESIZE 20
#define COMMAND_SIZE 50
#define COMMAND_RESIZE 20
#define ENTER 10

int menu(int lastPoint);

void clearTape(bool **tape, int tapeSize, int *tapePointer, bool **copyTapeValue);
bool loadTape(char *fTape, bool **tape, int *tapeSize, int *tapePointer, bool **copyTapeValue);
void mark(bool *tape,int tapePointer);
void unmark(bool *tape, int tapePointer);
void right(bool **tape, int *tapeSize, int *tapePointer, bool **copyTapeValue);
void left(bool **tape, int *tapeSize, int *tapePointer, bool **copyTapeValue);
void printTape(FILE *wherePrint, bool *tape, int tapeSize, int tapePointer, bool ifLoadTape);
void copyTape(bool *what, bool *whereTo, int size);

struct COMMAND
{
	int number, condition1, condition2;
	char command;
	char *commandString;
};

void clearCommands(struct COMMAND **commands, int commandSize, int *numberOfCommands);
bool loadCommands(char *fCom,struct COMMAND **commands, int *commandSize, int *numberOfCommands);
void printCommandsList(struct COMMAND *commands, int numberOfCommands, bool ifLoadCommand);
int lennum(int num);//количество знаков в строке

void run(char *fOut, bool step,
         bool **tape, int *tapePointer, int *tapeSize, bool **copyTapeValue, bool ifLoadTape,
         struct COMMAND *commands, bool ifLoadCommand);

#endif //POSTMACHINE_POST_H
