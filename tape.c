#include "post.h"

/*
    v
1110001000
*/

//очистка ленты
void clearTape(bool **tape, int tape_size, int *tapePointer, bool **copytape)
{
	if(*tape != NULL)
		free(*tape);
	*tape = (bool *)calloc(tape_size, sizeof(bool));
	if(*tape == NULL)
	{
		printf("Not enough memory for tape\n");
		exit(100);
	}

	if(*copytape != NULL)
		free(*copytape);
	*copytape = (bool *)calloc(tape_size, sizeof(bool) );
	if( *copytape == NULL )
	{
		printf("Not enough memory for copytape\n");
		exit(101);
	}
	*tapePointer = (tape_size)/2;
}

//загрузка ленты
bool loadTape(char *ftape, bool **tape, int *tape_size, int *tapePointer, bool **copytape)
{
	char tmp[81];
	int lenghtOfString, ret;
	char n; // '0' or '1'
	FILE *in;
	int v = -1;
	bool ifLoadTape = false; //лента не загружена
	bool fright;
	int resize = TAPE_RESIZE,
		oldsize = *tape_size;
	in = fopen(ftape, "rt");
	if (in == NULL)
	{
		printf("File %s not found \n", ftape);
		exit(-2);
	}

	fgets(tmp, 80, in);
	lenghtOfString = strlen(tmp);
	for(int i=0; i<lenghtOfString; i++)
	{
		if (tmp[i] == 'v')
		{
			v = i;
			break;
		}
		if (tmp[i] != ' ')
		{
			printf("Error in data file %s/ There are may be only spases or v \n", ftape);
			fclose(in);
			return ifLoadTape;
		}
	}//end for
	if (v == -1)
	{
		printf("Error in data file %s/ There are must be v \n", ftape);
		fclose(in);
		return ifLoadTape;
	}

	do
	{
		ret = fscanf(in, "%c", &n);
		if (ret == EOF) //конец файла
		{
			break;
		}
		if (ret != 1 || (n != '0' && n != '1'))
		{
			printf("Error in data file %s/ There are must be only 0 and 1 \n", ftape);
			fclose(in);
			return ifLoadTape;
		}
		if (n=='1')
		{
			mark(*tape, *tapePointer);

		}
		else
		{
			unmark(*tape, *tapePointer);
		}

		fright = right(*tape_size, tapePointer, true);
		if(!fright)
		{
			*tape_size += resize;
			*tape = realloc((bool *)*tape, *tape_size);
			if(*tape == NULL)
			{
				printf("Not enough memory for tape-2\n");
				exit(102);
			}
			*copytape = realloc((bool *)*copytape, *tape_size);
			if(*copytape == NULL)
			{
				printf("Not enough memory for copytape-2\n");
				exit(103);
			}
		}

	} while (!feof(in));
	fclose(in);
	*tapePointer = oldsize/2 + v;
	ifLoadTape = true;
	copyTape(*tape, *copytape, *tape_size);
	return ifLoadTape;
}

//поставить метку
void mark(bool *tape, int tapePointer)
{
	tape[tapePointer] = true;
}

//снять метку
void unmark(bool *tape, int tapePointer)
{
	tape[tapePointer] = false;
}

//сдвиг вправо
bool right(int tape_size, int *tapePointer, bool load)
{
	(*tapePointer)++;
	if (*tapePointer >= tape_size)
	{
		if(!load)
		{
			printf("Error.No enable space on right size of the tape \n");
			(*tapePointer)--;
		}
		return false;

	}
	return true;
}

//сдвиг влево
bool left(int *tapePointer)
{
	(*tapePointer)--;
	if (*tapePointer < 0)
	{
		printf("Error.No enable space on left size of the tape \n");
		(*tapePointer)++;
		return false;
	}
	return true;
}

void copyTape(bool *what, bool *whereTo, int size)
{
	int i;
	for (i=0; i < size; i++)
	{
		*(whereTo+i) = *(what+i);
	}
}

void printTape(FILE *wherePrint, bool *tape, int tapePointer, bool ifLoadTape)
{
	int delta = TAPE_SIZE/2;
	int i;
	if (!ifLoadTape)
	{
		printf("\n Tape wasn't load! \n");
		return;
	}

	fprintf(wherePrint, "%*c \n", delta+1, 'v');
	for (i = tapePointer - delta; i < tapePointer + delta; i++)
	{
		if (tape[i])
			fprintf(wherePrint, "1");
		else
			fprintf(wherePrint, ".");
	}
	fprintf(wherePrint, "\n \n");
}

