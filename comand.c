#include "post.h"

/*
1.	<2
2.	?1,3
3.	>4
4.	1 5
5.	.
*/

//очистка списка команд
void clearCommands(struct COMMAND **commands, int commandSize, int *numberOfCommands)
{
    if(*commands != NULL)
        free(*commands);
    *commands = (struct COMMAND *)calloc(commandSize, sizeof(struct COMMAND));
    if(*commands == NULL)
    {
        printf("Not enough memory for commands\n");
        exit(200);
    }
    *numberOfCommands = 0;
}

//загрузка команд
bool loadCommands(char *fCom,struct COMMAND **commands, int *commandSize, int *numberOfCommands)
{
    int ret, number, condition1, condition2, length;
    int resize = COMMAND_RESIZE;
    char command;
    FILE *in;
    bool ifLoadCommand = false;
    const char *commandTypes = "<>?10";
    *numberOfCommands = 0;
    int len;

    in = fopen(fCom, "rt");
    if (in == NULL)
    {
        printf("File %s not found \n", fCom);
        exit(-3);
    }

    do
    {
        ret = fscanf(in, " %d. %c %d", &number, &command, &condition1);
        if (ret == EOF)
            break;
        if (number <= 0 || condition1 <= 0 )
        {
            printf("Error in %s file. There may be only commands from [1...] interval \n", fCom);
            fclose(in);
            return ifLoadCommand;
        }
        (*numberOfCommands)++;
        //проверка последовательности введенных команд
        if (*numberOfCommands != number)
        {
            printf("Error in %s file. Command numbers must be in order \n", fCom);
            fclose(in);
            return ifLoadCommand;
        }
        if (*numberOfCommands > *commandSize)
        {
            *commandSize += resize;
            *commands = (struct COMMAND *)realloc((struct COMMAND *)*commands, *commandSize);
        }
        (*commands+number-1)->number = number;
        (*commands+number-1)->command = command;
        (*commands+number-1)->condition1 = condition1;
        // len(number)+'.'+ ' ' + command('.') + '\0' = len(number)+4
        len = lennum(number)+4;
        if (ret == 2 && command == '.')
        {
            (*commands+number-1)->commandString=(char *)calloc(len, sizeof(char));
            sprintf((*commands+number-1)->commandString, "%d. %c", number, command);
            break;
        }
        if (ret != 3)
        {
            printf("Error in %s file. Command must have a certain structure \n", fCom);
            fclose(in);
            return ifLoadCommand;
        }
        length = strlen(commandTypes);
        int i;
        for (i=0; i < length; i++)
        {
            if (command == commandTypes[i])
                break;
        }
        if (i == length)
        {
            printf("Error in %s file. Сommand does not exist \n", fCom);
            fclose(in);
            return ifLoadCommand;
        }
        len += 1 + lennum(condition1); // ' ' + len(condition1)
        (*commands+number-1)->condition2=-1;
        if (command == '?')
        {
            ret = fscanf(in, ",%d", &condition2);
            if (ret != 1 || condition2 <= 0 || condition2 == condition1)
            {
                printf("Error in %s file. Wrong condition2 \n", fCom);
                fclose(in);
                return ifLoadCommand;
            }
            (*commands+number-1)->condition2 = condition2;
            len+= 1+ lennum(condition2); // ',' + len(condition2)
        }
        (*commands+number-1)->commandString=(char *)calloc(len, sizeof(char));
        if ((*commands+number-1)->condition2!= -1)
            sprintf((*commands+number-1)->commandString, "%d. %c %d,%d", number, command, condition1, condition2);
        else
            sprintf((*commands+number-1)->commandString, "%d. %c %d", number, command, condition1);
    } while(!feof(in));

    fclose(in);
    if ((*commands+(*numberOfCommands)-1)->command != '.')
    {
        printf("Error in %s file. No stop-command - . in last command \n", fCom);
        return ifLoadCommand;
    }

    for(int i=0; i< (*numberOfCommands); i++)
    {
        if((*commands+i)->condition1 > *numberOfCommands ||
            (*commands+i)->condition2 > *numberOfCommands)
        {
            printf("Error condition1 or condition2 in command %d \n", i+1);
            return ifLoadCommand;
        }
    }

    ifLoadCommand = true;
    return ifLoadCommand;
}

void printCommandsList(struct COMMAND *commands, int numberOfCommands, bool ifLoadCommand)
{
    if (!ifLoadCommand)
    {
        printf("\n Commands wasn't load \n");
        return;
    }
    printf("\n \n");
    for (int i=0; i < numberOfCommands; i++)
    {
        printf("%s \n", commands[i].commandString);
    }
    printf("\n \n");
}

int lennum(int num)
{
    int col =0;
    while( num )
    {
        col++;
        num=num/10;
    }
    return col;
}
