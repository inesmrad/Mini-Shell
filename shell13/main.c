#include <stdio.h>
#include <stdlib.h>
#include "parse.h"
#include "launch.h"
#include <string.h>
#include "interactive.h"
#include "batch.h"
#define MAX_INPUT_LENGTH 100

void print_tokens(char tokens[MAX_NB_TOKENS][MAX_TOKEN_LEN], int nb_tokens)
{
    printf("Tokens are:\n");
    for (int i = 0; i < nb_tokens; ++i) {
        printf("  tokens[%d]=\"%s\"\n", i, tokens[i]);
    }
    printf("\n");
}

void print_simple_command(SimpleCommand* command)
{
    printf("SimpleCommand {\n");
    printf("  program_name = \"%s\"\n", command->program_name);
    printf("  args = {");
    for (int i = 0; i < command->nb_args; ++i) {
        printf("\"%s\"", command->args[i]);
        if (i < command->nb_args - 1) {
            printf(", ");
        }
    }
    printf("}\n");
    printf("}\n");
}

void print_compound_command(CompoundCommand* command)
{
    printf("== CompoundCommand =====\n");
    printf("cmd1 = ");
    print_simple_command(&command->cmd1);
    if (command->op != OPERATOR_NONE) {
        if (command->op == OPERATOR_AND) {
            printf("op = &&\n");
        } else {
            printf("op = ||\n");
        }

        printf("cmd2 = ");
        print_simple_command(&command->cmd2);
    }
    printf("=========================\n");
}

void print_seq_command(CommandSequence* seq)
{
    printf("++ CommandSequence +++++++++++\n");

    if (seq->in_parallel) {
        printf("  ++ in parallel ++\n");
    } else {
        printf("  ++ sequential ++\n");
    }

    for (int i = 0; i < seq->nb_cmds; ++i) {
        print_compound_command(&seq->cmds[i]);
    }

    printf("++++++++++++++++++++++++++++++\n");
}






int main(int argc, char* argv[]) {
    char tokens[MAX_NB_TOKENS][MAX_TOKEN_LEN] = { 0 };
    char input[MAX_INPUT_LENGTH];


 // Check if there are any command-line arguments
    if (argc > 1) {
        // Batch mode: execute commands from the specified files
        
            int result = batch_mode(argv+1, argc-1);
            if (result == -1) {
                printf("Error in batch mode\n");
                return 1;
            }
        
    } else {
        // Interactive mode: enter the shell's interactive mode
        int result = interactive_mode();
        if (result == -1) {
            printf("Error in interactive mode\n");
            return 1;
        }
    }

    return 0;
}
