#ifndef POSTMACHINE_POST_H
#define POSTMACHINE_POST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define bool char
#define false 0
#define true 1

#define TAPE_SIZE 50
#define TAPE_RESIZE 20
#define COMMAND_SIZE 50
#define COMMAND_RESIZE 20
#define ENTER 10

int menu(int lastPoint);

void clearTape(bool **tape, int tape_size, int *tapePointer, bool **copytape);
bool loadTape(char *ftape, bool **tape, int *tape_size, int *tapePointer, bool **copytape);
void mark(bool *tape,int tapePointer);
void unmark(bool *tape, int tapePointer);
bool right( int tape_size, int *tapePointer, bool load);
bool left(int *tapePointer);
void printTape(FILE *wherePrint, bool *tape, int tapePointer, bool ifLoadTape);
void copyTape(bool *what, bool *whereTo, int size);

struct COMMAND
{
	int number, condition1, condition2;
	char command;
	char *commandString;
};

void clearCommands(struct COMMAND **commands, int command_size, int *numberOfCommands);
bool loadCommands(char *fcom,struct COMMAND **commands, int *command_size, int *numberOfCommands);
void printCommandsList(struct COMMAND *commands, int numberOfCommands, bool ifLoadCommand);
int lennum(int num);//количество знаков в строке

void run(char *fout, bool step,
		 bool *tape, int *tapePointer, int tape_size, bool ifLoadTape,
		struct COMMAND *commands, bool ifLoadCommand);

#endif //POSTMACHINE_POST_H
