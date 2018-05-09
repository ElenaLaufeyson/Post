#include "post.h"

//bool step = true - пошагово, а false - сразу

void run(char *fout, bool step,
		 bool *tape, int *tapePointer, int tape_size, bool ifLoadTape,
		struct COMMAND *commands, bool ifLoadCommand)
{
	char save;
	bool needFile = false;
	FILE *out;
	char currentCommand; //текущая команда
	int i = 0; //индекс текущей команды (номер команды - 1)
	int maxNumberOfCommands = 100; //максимально возможное количество шагов
	int currentNumberOfCommands = 0;
	int key; //код возвращаемой клавиши
	char stepcommand[5]; // "stop" или "run"

	if (!ifLoadTape || !ifLoadCommand)
	{
		printf("Error! Commands (or tape) wasn't uploaded! \n");
		return;
	}
	printf("Save to file? [y-yes, any - no] \n");
	scanf(" %c", &save);
	if (save == 'y')
	{
		needFile = true;
		out = fopen(fout, "wt");
		if (out == NULL)
		{
			printf("File %s can not be open \n", fout);
			exit(-4);
		}
	}
	fflush(stdin);

	if(step)
		printf(" <Enter> - next step, stop - stop, run - run\n");

	printTape(stdout, tape, *tapePointer, ifLoadTape);
	if (needFile)
		printTape(out, tape, *tapePointer, ifLoadTape);

	while (1)
	{
		printf("%s \n", commands[i].commandString);
		if (needFile)
			fprintf(out, "%s \n", commands[i].commandString);
		currentCommand = commands[i].command;
		switch(currentCommand)
		{
			case '1':	mark(tape, *tapePointer);
						break;
			case '0':	unmark(tape, *tapePointer);
						break;
			case '<':	left(tapePointer);
						break;
			case '>':	right( tape_size, tapePointer, false);
						break;
		}
		if (currentCommand != '.' && currentCommand != '?')
		{
			printTape(stdout, tape, *tapePointer, ifLoadTape);
			if (needFile)
				printTape(out, tape, *tapePointer, ifLoadTape);
		}
		else if (currentCommand == '.')
		{
			printf("\n \n STOP \n \n ");
			if (needFile)
				fprintf(out, "\n \n STOP \n \n ");
			break;
		}

		i = commands[i].condition1;
		if (currentCommand == '?')
		{
			if (*(tape+(*tapePointer)) == true)
				i = commands[i].condition2;

		}
		i--;
		currentNumberOfCommands++;
		if (currentNumberOfCommands > maxNumberOfCommands)
		{
			printf("Exceeded maxNumberOfCommands %d \n", maxNumberOfCommands);
			if (needFile)
				fprintf(out, "Exceeded maxNumberOfCommands %d \n", maxNumberOfCommands);
			break;
		}
		if (step)
		{
			while(1)
			{
				key = getc(stdin);
				if(key == ENTER)
					break;
				ungetc(key,stdin); //вернуть "первый" символ обратно в поток, чтобы считать все слово
				scanf(" %s",stepcommand);
				if(!strcmp(stepcommand,"run")) // == 0
				{
					step = false;
					break;
				}
				if(!strcmp(stepcommand,"stop"))
				{
					printf("Aborted by user \n \n \n");
					if (needFile)
					{
						fprintf(out, "Aborted by user \n \n \n");
						fclose(out);
					}
					return;
				}

				printf("error");
				fflush(stdin);
			}
		} // end if (step)
	}//end while
	if (needFile)
		fclose(out);
}



