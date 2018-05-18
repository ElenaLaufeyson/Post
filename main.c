#include "post.h"

int main(int argc, char *args[])
{
    // menu
    int pointMenu;

    // tape
    int tapeSize = TAPE_SIZE;
    bool *tape = NULL;
    bool *copyTapeValue = NULL;
    int tapePointer = 0;
    int start_tapePointer=0;
    bool ifLoadTape = false; //лента не загружена

    // command
    int commandSize = COMMAND_SIZE;
    struct COMMAND *commands=NULL;
    int numberOfCommands=0;
    bool ifLoadCommand = false;

    if (argc != 4)
    {
        printf("post.exe ftape.txt fcom.txt out.txt \n");
        return -1;
    }

    do
    {
        pointMenu = menu(7);
        switch (pointMenu)
        {
            case 1:	clearTape(&tape, tapeSize, &tapePointer, &copyTapeValue);
                    ifLoadTape = loadTape(args[1], &tape, &tapeSize, &tapePointer, &copyTapeValue);
                    start_tapePointer = tapePointer;
                    printTape(stdout, tape, tapeSize, tapePointer, ifLoadTape );
                    break;
            case 2: clearCommands(&commands, commandSize, &numberOfCommands);
                    ifLoadCommand = loadCommands(args[2], &commands, &commandSize, &numberOfCommands);
                    printCommandsList(commands,numberOfCommands, ifLoadCommand);
                    break;
            case 3: if(ifLoadTape)
                        printTape(stdout, tape, tapeSize, tapePointer, ifLoadTape);
                    else
                        printf("Tape wasn't load \n \n");
                    if(ifLoadCommand)
                        printCommandsList(commands,numberOfCommands, ifLoadCommand);
                    else
                        printf("Commands wasn't load \n \n");
                    break;
            case 4: run(args[3], false, &tape, &tapePointer, &tapeSize, &copyTapeValue, ifLoadTape, commands, ifLoadCommand);
                    break;
            case 5: run(args[3], true, &tape, &tapePointer, &tapeSize, &copyTapeValue, ifLoadTape, commands, ifLoadCommand);
                    break;
            case 6: if(!ifLoadTape)
                    {
                        printf("\n You need to load tape!!\n\n");
                        break;
                    }
                    copyTape( copyTapeValue, tape, tapeSize);
                    tapePointer = start_tapePointer;
                    printTape(stdout, tape, tapeSize, tapePointer, ifLoadTape);
                    break;

            case 7: break;
        }
    } while (pointMenu != 7);
    if( tape != NULL )
        free(tape);
    if( copyTapeValue != NULL )
        free(copyTapeValue);
    if( commands != NULL )
        free(commands);
    printf ("\n See you later :3 \n \n \n");
    return 0;
}