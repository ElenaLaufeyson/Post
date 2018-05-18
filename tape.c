#include "post.h"

/*
    v
1110001000
*/

//очистка ленты
void clearTape(bool **tape, int tapeSize, int *tapePointer, bool **copyTapeValue)
{
	if(*tape != NULL)
		free(*tape);
	*tape = (bool *)calloc(tapeSize, sizeof(bool));
	if(*tape == NULL)
	{
		printf("Not enough memory for tape\n");
		exit(100);
	}

	if(*copyTapeValue != NULL)
		free(*copyTapeValue);
	*copyTapeValue = (bool *)calloc(tapeSize, sizeof(bool) );
	if( *copyTapeValue == NULL )
	{
		printf("Not enough memory for copyTapeValue\n");
		exit(101);
	}
	*tapePointer = (tapeSize)/2;
}

//загрузка ленты
bool loadTape(char *fTape, bool **tape, int *tapeSize, int *tapePointer, bool **copyTapeValue)
{
	char tmp[81];
	int lenghtOfString, ret;
	char n; // '0' or '1'
	FILE *in;
	int v = -1;
	bool ifLoadTape = false; //лента не загружена
	int resize = TAPE_RESIZE,
		oldsize = *tapeSize;
	in = fopen(fTape, "rt");
	if (in == NULL)
	{
		printf("File %s not found \n", fTape);
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
			printf("Error in data file %s/ There are may be only spases or v \n", fTape);
			fclose(in);
			return ifLoadTape;
		}
	}//end for
	if (v == -1)
	{
		printf("Error in data file %s/ There are must be v \n", fTape);
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
			printf("Error in data file %s/ There are must be only 0 and 1 \n", fTape);
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

		right(tape, tapeSize, tapePointer, copyTapeValue);

	} while (!feof(in));
	fclose(in);
	*tapePointer = oldsize/2 + v;
	ifLoadTape = true;
	copyTape(*tape, *copyTapeValue, *tapeSize);
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
void right(bool **tape, int *tapeSize, int *tapePointer, bool **copyTapeValue)
{
	(*tapePointer)++;
	if (*tapePointer < *tapeSize)
		return;
	*tapeSize += TAPE_RESIZE;
	*tape = (bool *)realloc((bool *)*tape, *tapeSize);
	if(*tape == NULL)
	{
		printf("Not enough memory for tape-right\n");
		exit(102);
	}
	*copyTapeValue = realloc((bool *)*copyTapeValue, *tapeSize);
	if(*copyTapeValue == NULL)
	{
		printf("Not enough memory for copyTapeValue-right\n");
		exit(103);
	}
}

//сдвиг влево
void left(bool **tape, int *tapeSize, int *tapePointer, bool **copyTapeValue)
{
	(*tapePointer)--;
	if (*tapePointer >= 0)
		return;
	int oldSize = *tapeSize;
	bool *oldTape = (bool *)calloc(oldSize, sizeof(bool));
	if(oldTape == NULL)
	{
		printf("Not enough memory for oldTape-left\n");
		exit(104);
	}
	copyTape(*tape, oldTape, oldSize);
	*tapeSize += TAPE_RESIZE;
	*tape = (bool *)realloc((bool *)*tape, *tapeSize);
	if(*tape == NULL)
	{
		printf("Not enough memory for tape-left\n");
		exit(105);
	}
	//копируем с конца
	for (int i = oldSize-1, j = *tapeSize-1; i>=0; i--, j--)
	{
		*(*tape+j) = *(oldTape+i);
	}
	*tapePointer = *tapeSize-oldSize-1;
	for (int i = 0; i <= *tapePointer; i++)
	{
		*(*tape+i) = false;
	}
	*copyTapeValue = realloc((bool *)*copyTapeValue, *tapeSize);
	if(*copyTapeValue == NULL)
	{
		printf("Not enough memory for copyTapeValue-left\n");
		exit(106);
	}
	free(oldTape);
}

void copyTape(bool *what, bool *whereTo, int size)
{
	int i;
	for (i=0; i < size; i++)
	{
		*(whereTo+i) = *(what+i);
	}
}

void printTape(FILE *wherePrint, bool *tape, int tapeSize, int tapePointer, bool ifLoadTape)
{
    int width = 70; //ширина поля печати
	int delta = width/2;
	int i = tapePointer - delta; //левый край печати
	if (!ifLoadTape)
	{
		printf("\n Tape wasn't load! \n");
		return;
	}

	fprintf(wherePrint, "%*c \n", delta+1, 'v');
	for (int k=0; k < width; k++, i++) //k - сколько символов напечатать
	{
		if (i<0 || i>tapeSize || tape[i] == false)
        {
            fprintf(wherePrint, "%c", '.');
        }
        else
            fprintf(wherePrint, "%c", '1');
	}
	fprintf(wherePrint, "\n \n");
}

