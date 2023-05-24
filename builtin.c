#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAXLINE 1024 /* maximum length of a command line */
#define PROMPT "$ " /* prompt symbol */

/**
 * main - a simple UNIX command line interpreter
 * Return: 0 on success, 1 on failure
 */
int main(void)
{
    char line[MAXLINE]; /* buffer for the command line */
    char *argv[MAXLINE]; /* array of arguments */
    int argc; /* number of arguments */
    pid_t pid; /* process id */
    int status; /* exit status of the child process */

    while (1) /* main loop */
    {
        printf(PROMPT); /* print the prompt */
        if (fgets(line, MAXLINE, stdin) == NULL) /* read a line from stdin */
        {
            printf("\n"); /* print a new line */
            break; /* exit the loop if end of file is reached */
        }
        if (line[strlen(line) - 1] == '\n') /* remove the trailing newline */
            line[strlen(line) - 1] = '\0';
        if (line[0] == '\0') /* ignore empty lines */
            continue;
        argc = 0; /* initialize the argument count */
        argv[argc++] = strtok(line, " "); /* split the line by spaces and store the first argument */
        while ((argv[argc++] = strtok(NULL, " ")) != NULL); /* store the rest of the arguments */
        argc--; /* decrement the argument count to exclude the NULL pointer */
        pid = fork(); /* create a new process */
        if (pid < 0) /* fork failed */
        {
            perror("fork"); /* print an error message */
            exit(1); /* exit with failure */
        }
        else if (pid == 0) /* child process */
        {
            execvp(argv[0], argv); /* execute the command with arguments */
            perror(argv[0]); /* print an error message if execvp failed */
            exit(1); /* exit with failure */
        }
        else /* parent process */
        {
            wait(&status); /* wait for the child to terminate */
            if (WIFEXITED(status)) /* child exited normally */
                printf("Child exited with status %d\n", WEXITSTATUS(status)); /* print the exit status */
            else if (WIFSIGNALED(status)) /* child was terminated by a signal */
                printf("Child terminated by signal %d\n", WTERMSIG(status)); /* print the signal number
*/
        }
    }
    return (0); /* exit with success */
}
