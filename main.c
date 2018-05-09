#include "post.h"

int main(int argc, char *args[])
{
    int i;
    // menu
    int pointMenu;

    // tape
    int tape_size = TAPE_SIZE;
    bool *tape = NULL;
    bool *copytape = NULL;
    int tapePointer = 0;
    int start_tapePointer=0;
    bool ifLoadTape = false; //лента не загружена

    // command
    int command_size = COMMAND_SIZE;
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
            case 1:	clearTape(&tape, tape_size, &tapePointer, &copytape);
                    ifLoadTape = loadTape(args[1], &tape, &tape_size, &tapePointer, &copytape);
                    start_tapePointer = tapePointer;
                    printTape(stdout, tape, tapePointer, ifLoadTape );
                    break;
            case 2: clearCommands(&commands, command_size, &numberOfCommands);
                    ifLoadCommand = loadCommands(args[2], &commands, &command_size, &numberOfCommands);
                    printCommandsList(commands,numberOfCommands, ifLoadCommand);
                    break;
            case 3: if(ifLoadTape)
                        printTape(stdout, tape, tapePointer, ifLoadTape);
                    else
                        printf("Tape wasn't load \n \n");
                    if(ifLoadCommand)
                        printCommandsList(commands,numberOfCommands, ifLoadCommand);
                    else
                        printf("Commands wasn't load \n \n");
                    break;
            case 4: run(args[3], false, tape, &tapePointer, tape_size, ifLoadTape, commands, ifLoadCommand);
                    break;
            case 5: run(args[3], true, tape, &tapePointer, tape_size, ifLoadTape, commands, ifLoadCommand);
                    break;
            case 6: if(!ifLoadTape)
                    {
                        printf("\n You need to load tape!!\n\n");
                        break;
                    }
                    copyTape( copytape, tape, tape_size);
                    tapePointer = start_tapePointer;
                    printTape(stdout, tape, tapePointer, ifLoadTape);
                    break;

            case 7: break;
        }
    } while (pointMenu != 7);
    if( tape != NULL )
        free(tape);
    if( copytape != NULL )
        free(copytape);
    if( commands != NULL )
        free(commands);
    printf ("\n See you later :3 \n \n \n");
    return 0;
}