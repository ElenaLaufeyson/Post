#include "post.h"

//bool step = true - пошагово, а false - сразу

void run(char *fOut, bool step,
		 bool **tape, int *tapePointer, int *tapeSize, bool **copyTapeValue, bool ifLoadTape,
		struct COMMAND *commands, bool ifLoadCommand)
{
	char save;
	bool needFile = false;
	FILE *out;
	char currentCommand; //текущая команда
	int i = 0; //индекс текущей команды (номер команды - 1)
	int maxNumberOfCommands = 100; //максимально возможное количество шагов
	int currentNumberOfCommands = 0;
	int ret;
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
		out = fopen(fOut, "wt");
		if (out == NULL)
		{
			printf("File %s can not be open \n", fOut);
			exit(-4);
		}
	}
	fflush(stdin);
	printf("\n Input maxNumberOfCommands \n");
	ret = scanf(" %d", &maxNumberOfCommands);
	if (ret != 1)
		printf("Wrong value! Default maxNumberOfCommands = 100 \n");
	fflush(stdin);

	if(step)
		printf(" <Enter> - next step, stop - stop, run - run\n");

	printTape(stdout, *tape, *tapeSize, *tapePointer, ifLoadTape);
	if (needFile)
		printTape(out, *tape, *tapeSize, *tapePointer, ifLoadTape);

	while (1)
	{
		printf("%s \n", commands[i].commandString);
		if (needFile)
			fprintf(out, "%s \n", commands[i].commandString);
		currentCommand = commands[i].command;
		switch(currentCommand)
		{
			case '1':	mark(*tape, *tapePointer);
						break;
			case '0':	unmark(*tape, *tapePointer);
						break;
			case '<':	left(tape, tapeSize, tapePointer, copyTapeValue);
						break;
			case '>':	right(tape, tapeSize, tapePointer, copyTapeValue);
						break;
		}
		if (currentCommand != '.' && currentCommand != '?')
		{
			printTape(stdout, *tape, *tapeSize, *tapePointer, ifLoadTape);
			if (needFile)
				printTape(out, *tape, *tapeSize, *tapePointer, ifLoadTape);
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
			if (*(*tape+(*tapePointer)) == true)
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
				scanf(" %4s",stepcommand);
                fflush(stdin);
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



