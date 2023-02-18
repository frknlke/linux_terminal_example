#include <stdio.h>
#include "main.h"
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>
#include <string.h>
#include "commands.h"
#include <stdlib.h>
#include <stdbool.h>

// Author = Furkan Ülke
// Student_ID = 2018400054

int main(){

    char exit_code[10] = "exit";                                    // char array to store exit code of our shell
    char command_input[100];                                        // char array to store command input until the new line
    char username[50];                                              // char array to store the current username
    char command[50];                                               // char array to store command
    char argument1[50];                                             // char array to store first argument
    char argument2[50];                                             // char array to store second argument
    char argument3[50];                                             // char array to store third argument
    char command_history[15][100];                                  // char array to store last 15 command_input

    int num_of_command = 0;                                         // int to store number of command given since the program has started. It used for history command
    int *commandNumber = &num_of_command;
    int command_type = 0;                                           // int to store categorized command type

    bool will_continue = true;                                      // boolean value to control while loop, and terminate it when exit code is taken
    
    getlogin_r(username, 50);                                       // storing current username in a char array that is named as "chararray"
    
    int resu = 1;
    while(will_continue){                                           // while loop, it takes input from the user continuously, until user gives the exit code
        printf("%s >>> ", username);                                // prints username and " >>> "
        resu = scanf("%99[^\n]%*c", command_input);                 // takes input from the user and stores it in a char array (it takes spaces also)
        if(resu != 1){
            printf("Invalid command given\n");
            memset(command_input, 0, sizeof command_input);
            break;
        }
        //fgets(command_input,strlen(command_input),stdin);
        if(command_input[0] == 0x0A){
            printf("enter\n");
            memset(command_input, 0, sizeof command_input);
            break;
        }
        if(!(strcmp(exit_code,command_input))) {                    // compare giving command with exit code, if they are equal terminate the loop
           will_continue = false;
           continue; 
        }
        split_string(command_input, command, argument1, argument2, argument3);          // send input to split_string in order to get words
        command_type = getCommandType(command);                                         // send the command to getCommandType function to categorize command
        
        historyHandler(command_history, command_input, commandNumber);                  // add given command_input to the history
        if(*commandNumber < 15) *commandNumber = *commandNumber + 1;                    // if command number less than 15 incement it by one otherwise do not increment

        if(command_type < 0)                                                            // invalid command if command_type is less than 0
        {
            printf("Invalid command given\n");
            //
            memset(command_input, 0, sizeof command_input);
            continue;
        }
        else if(command_type == 1){                                                     // if command_type is 1 than it is a listdir command
            //atexit(listdir);
            listdir();                                                                  // call listdir function from the commands.c
        }
        else if(command_type == 2){                                                     // if command_type is 2 than it is a mycomputername command
            mycomputername();                                                           // call mycomputername command from the commands.c
        }
        else if(command_type == 3){                                                     // if command_type is 3 than it is a whatsmyip command
            whatsmyip();                                                                // call whatsmyip from the commands.c
        }
        else if(command_type == 4){                                                     // if command_type is 4 than it is a printfile command
            if((strcmp(argument2,">"))){                                                // if second argument is ">" than we should copy a file into another
                readLine(argument1);                        
            }else{
                readAndWrite(argument1,argument3);
            }
        }
        else if(command_type == 5){                                                     // If command_type is 5 than it is dididothat command
            int rslt = isInHistory(command_history, command_input);                     // check if given command_input is in the history by isInHistory function
            if(rslt == 1){
               dididothat(1);                                                           // If it is, call dididothat function with the parameter 1
            }else{
                dididothat(0);                                                          // Else, call dididothat function with parameter 0
            }
        }
        else if(command_type == 6){                                                     // IF command type is 6, than it is hellotext command
            hellotext();                                                                // call hellotext function from commands.c
        }   
        else{
            will_continue = false;
            continue;
        }

        memset(command_input, 0, sizeof command_input);             // clears the char array that is used for taking command input
        memset(command, 0, sizeof command);                         // clears the char array that is used for storing command
        memset(argument1, 0, sizeof argument1);                     // clears the char array that is used for storing first argument
        memset(argument2, 0, sizeof argument2);                     // clears the char array that is used for storing second argument
        memset(argument3, 0, sizeof argument3);                     // clears the char array that is used for storing third argument
    }
 
    return 0;
}

// it takes five char pointers as parameter, one for input string and others for output words.
// splits input into words by considering whitespaces as delimeter
void split_string(char *input, char *comm, char *arg1, char *arg2, char *arg3){
        char str[100];                                              // char array to store input
        strcpy(str, input);                                         // copying input into str
        char split_string[4][40];                                   // 2D char array to store words (it has 4 rows because our command consists of at most 4 words)
        int f, j, count = 0;                                        // variables to handle indexing
  
        for(f = 0; f <= strlen(str); f++){
            if(str[f] == ' ' || str[f] == '\0'){                    // if current char is whitespace or \0 then add \0 at the end of the current word and start to write oth0er word
                split_string[count][j] = '\0';
                count = count +1 ;
                j = 0;
            }
            else{
                split_string[count][j] = str[f];                    // else add current char of input to the end of the word
                j = j+1;
            }

        }
        // copy the strings of words into input char pointers
        strcpy(comm, split_string[0]);                              
        strcpy(arg1, split_string[1]);
        strcpy(arg2, split_string[2]);
        strcpy(arg3, split_string[3]);
        
        return;

}

//It takes command input and returns unique integer values for every different command type
int getCommandType(char *input){
    if(!(strcmp(input, "listdir"))){
        return 1;
    }
    else if(!(strcmp(input, "mycomputername"))){
        return 2;
    }
    else if(!(strcmp(input, "whatsmyip"))){
        return 3;
    }
    else if(!(strcmp(input, "printfile"))){
        return 4;
    }
    else if(!(strcmp(input, "dididothat"))){
        return 5;
    }
    else if(!(strcmp(input, "hellotext"))){
        return 6;
    }
    else if(!(strcmp(input, "exit"))){
        return 7;
    }
    else{
        return -1;
    }
}

// It takes 2D history array, last command, and command number.
// If command number is 15, swaps all the 15 elements of history array with preceding element. So we deleted the oldest element and updated the history array.
// If command number is not 15, add last command to history array's "number" index
void historyHandler(char input[15][100], char *lastCmd, int *number){
    if(*number == 15){
        for(int i = 0; i<14; i++){
            strcpy(input[i], input[i+1]);
        }
        strcpy(input[14], lastCmd);
    }
    else{
        strcpy(input[*number], lastCmd);
    }
}

// Checks whether last command is in 2D history array or not
// To do this it cuts out "dididothat" string from last command then compares it.
// It return 1 if last command is in the history array, otherwise it returns 0.
int isInHistory(char input[15][100], char *lastCmd){
   char desired[strlen(lastCmd)-12];
   memcpy(desired,lastCmd+12,strlen(lastCmd)-13);
   desired[strlen(lastCmd)-13] = '\0';

    for(int i=0; i<15; i++){
        if(!strcmp(input[i], desired)){
            return 1;
        }
    }
    return 0;
}

// It takes a char pointer that stores the name of the file to be read as argument
// It takes a line from the file and calls writeLineByLine by giving readed line as parameter
// Repeats this process until the end of the line is reached
void readLine(char *fileName){
    FILE *fileOpened = fopen(fileName,"r");
    char *line;
    char input[512];
    const char s[2] = "\n";
    char *shapedLine;
    char enter;

    if(fileOpened == NULL){
        printf("Can not open the file\n");
    }
    do{
        line = fgets(input, sizeof(input), fileOpened);
        if(line){
            shapedLine = strtok(line, "\n");
            writeLinebyLine(shapedLine);
            enter = fgetc(stdin);
        }
       
    }while(line && (enter != (char)0));
}

