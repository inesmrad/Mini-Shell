#include "launch.h"
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>   // Include for perror and printf
#include <stdlib.h>  // Include for exit and EXIT_FAILURE
#include <string.h> 



// Execute a simple or compound command
// Returns 0 if there is no error, or -1 if there is an error
// It calls the other related launch_* functions
int launch_command(CommandSequence* command)
{
    int num_cmds = command->nb_cmds;
    int success = 0;

    for (int i = 0; i < num_cmds; i++) {
        CompoundCommand* compound_cmd = &command->cmds[i];
        SimpleCommand* cmd1 = &compound_cmd->cmd1;
        SimpleCommand* cmd2 = &compound_cmd->cmd2;

        // Execute cmd1
        success = launch_simple_command(cmd1);
        if (success == -1) {
            printf("Error executing command: %s\n", cmd1->program_name);
            return -1;
        }

        // Check the operator and execute cmd2 if necessary
        if (compound_cmd->op == OPERATOR_AND && success != -1) {
            // Execute cmd2 only if cmd1 succeeded
            success = launch_simple_command(cmd2);
            if (success == -1) {
                printf("Error executing command: %s\n", cmd2->program_name);
                return -1;
            }
        } else if (compound_cmd->op == OPERATOR_OR && success == -1) {
            // Execute cmd2 only if cmd1 failed
            success = launch_simple_command(cmd2);
            if (success == -1) {
                printf("Error executing command: %s\n", cmd2->program_name);
                return -1;
            }
        }
    }

    return success;
}
// Execute a compound command
// Returns 0 if there is no error, or -1 if there is an error
// It calls the other related launch_* functions
int launch_compound_command(CompoundCommand* command)
{
  // Execute the first command
    int success = launch_simple_command(&command->cmd1);
    if (success == -1) {
        // Error occurred while executing the first command
        return -1;
    }

    // Check the operator type and execute the second command if necessary
    if (command->op != OPERATOR_NONE) {
        if (command->op == OPERATOR_AND) {
            // Execute the second command only if the first command succeeded
            if (success == 0) {
                success = launch_simple_command(&command->cmd2);
            }
        } else {
            // Execute the second command only if the first command failed
            if (success != 0) {
                success = launch_simple_command(&command->cmd2);
            }
        }
    }


return success;
}

// Execute a simple command
// Returns 0 if there is no error, or -1 if there is an error
int launch_simple_command(SimpleCommand* command)
{
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        char* argv[MAX_NB_ARGS + 2];
        argv[0] = command->program_name;

        for (int i = 0; i < command->nb_args; i++) {
            argv[i + 1] = command->args[i];
        }
        argv[command->nb_args + 1] = NULL;

        execvp(command->program_name, argv);

        // If execvp fails, an error occurred
        perror("execvp");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Parent process
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            // Child process exited normally
            int exit_status = WEXITSTATUS(status);
            printf("Child process exited with status: %d\n", exit_status);
            return 0;
        } else if (WIFSIGNALED(status)) {
            // Child process was terminated by a signal
            int term_signal = WTERMSIG(status);
            printf("Child process terminated by signal: %d\n", term_signal);
            return -1;
        }
    } else {
        // Fork failed
        perror("fork");
        return -1;
    }

    return -1;
}
