#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

    // Stores all the codes for commands
    // uses fork() and exec() functions to create process

    
    int listdir()
    {
        pid_t pid;
        int i;
        int y;
        pid = fork();                           // creating a child process
        
        if (pid < 0)                            // error occurred returns -1
        {  
            fprintf(stderr, "Fork Failed"); 
            return 1;
        }
        else if (pid == 0)                      // execution of the child process
        { 
            execlp("/bin/ls","ls",NULL);
        }
        else                                    // execution of the parent process
        {  
            wait(NULL);                         // parent will wait for the child to complete
            kill(pid, SIGTERM);                 // kill the parent process
        }
        return 0;
    }

    int mycomputername()
    {
        pid_t pid;
        int i;
        int y;
        pid = fork();                           // creating a child process
        
        if (pid < 0)                            // error occurred returns -1
        {  
            fprintf(stderr, "Fork Failed"); 
            return 1;
        }
        else if (pid == 0)                      // execution of the child process
        { 
            execlp("/bin/hostname","hostname",NULL);
        }
        else                                    // execution of the parent process
        {  
            wait(NULL);                         // parent will wait for the child to complete
            kill(pid, SIGTERM);                 // kill the parent process
        }
        return 0;
    }

    int whatsmyip(){
        pid_t pid;
        int i;
        int y;
        pid = fork();                           // creating a child process
        
        if (pid < 0)                            // error occurred returns -1
        {  
            fprintf(stderr, "Fork Failed"); 
            return 1;
        }
        else if (pid == 0)                      // execution of the child process
        { 
            execlp("/bin/hostname","hostname", "-I",NULL);
        }
        else                                    // execution of the parent process
        {  
            wait(NULL);                         // parent will wait for the child to complete
            kill(pid, SIGTERM);                 // kill the parent process
        }
        return 0;
    }

    int readAndShow(char *input_file){
        pid_t pid;
        pid = fork();                           // creating a child process
        
        if (pid < 0)                            // error occurred returns -1
        {  
            fprintf(stderr, "Fork Failed"); 
            return 1;
        }
        else if (pid == 0)                     // execution of the child process
        { 

            execlp("/bin/cat","cat", input_file,NULL);
        }
        else                                   // execution of the parent process
        {  
            wait(NULL);                        // parent will wait for the child to complete
            kill(pid, SIGTERM);

        }
        return 0;
}

    int readAndWrite(char *input_file, char *output_file){
        pid_t pid;
        pid = fork();                                   // creating a child process
        
        if (pid < 0)                                    // error occurred returns -1
        {  
            fprintf(stderr, "Fork Failed"); 
            return 1;
        }
        else if (pid == 0)                              // execution of the child process
        { 

            execlp("/bin/cp","cp", input_file, output_file,NULL);
        }
        else                                           // execution of the parent process
        {  
            wait(NULL);                                // parent will wait for the child to complete
            kill(pid, SIGTERM);

        }
        return 0;

    }

    int dididothat(int res){
        pid_t pid;
        pid = fork();                                  // creating a child process
        
        if (pid < 0)                                   // error occurred returns -1
        {  
            fprintf(stderr, "Fork Failed"); 
            return 1;
        }
        else if (pid == 0)                             // execution of the child process
        {
            if(res == 1){
                execlp("/bin/echo","echo", "Yes",NULL);
            }
            else{
                execlp("/bin/echo","echo", "No",NULL);
            }
            
        }
        else                                           // execution of the parent process
        {  
            wait(NULL);                                // parent will wait for the child to complete
            kill(pid, SIGTERM);                        // kill the parent process
        }
        return 0;
    }

    int hellotext(){
        pid_t pid;
        pid = fork();                                   // creating a child process
        
        if (pid < 0)                                    // error occurred returns -1
        {  
            fprintf(stderr, "Fork Failed"); 
            return 1;
        }
        else if (pid == 0)                              // execution of the child process
        {
                execlp("/bin/editor","editor",NULL);
            
        }
        else                                            // execution of the parent process
        {  
            wait(NULL);                                 // parent will wait for the child to complete
            kill(pid, SIGTERM);
        }
        return 0;
    }
    
    int writeLinebyLine(char *line){
        pid_t pid;
        pid = fork();                                   // creating a child process
        
        if (pid < 0)                                    // error occurred returns -1
        {  
            fprintf(stderr, "Fork Failed"); 
            return 1;
        }
        else if (pid == 0)                              // execution of the child process
        {
            execlp("/bin/printf","printf", line,NULL);
        }
        else                                            // execution of the parent process
        {  
            wait(NULL);                                 // parent will wait for the child to complete
            kill(pid, SIGTERM);
        }
        return 0;
    }
    