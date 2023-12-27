#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h" // Include the necessary headers for parsing and launching commands
#include "launch.h"

void print_seq_command(CommandSequence* seq_cmd);
void print_tokens(char tokens[MAX_NB_TOKENS][MAX_TOKEN_LEN], int nb_tokens);


int interactive_mode() {
    char tokens[MAX_NB_TOKENS][MAX_TOKEN_LEN] = { 0 };
    char input[MAX_INPUT_LENGTH];
	
    while (1) {
         printf("Shell> "); // Display the prompt

        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';  // Remove newline character

        int nb_tokens = tokenize(input, tokens);
        if (nb_tokens == -1) {
            printf("Error while tokenizing:\n%s\n", input);
            return -1;
        } else {
		print_tokens(tokens, nb_tokens);



            CommandSequence seq_cmd;
            int consumed = parse(tokens, nb_tokens, &seq_cmd);
            if (consumed == -1) {
                printf("Error while parsing CommandSequence\n");
                return -1;
            } else {
                // Print the parsed command sequence
                print_seq_command(&seq_cmd);
                printf("consumed  = %d\n", consumed);
                printf("remaining = %d\n", nb_tokens - consumed);

                // Launch the command sequence
                int success = launch_command(&seq_cmd);
                if (success == 0) {
                    printf("Command sequence executed successfully\n");
                } else {
                    printf("Error while executing command sequence\n");
                    return -1;
                }
            }
        }
    }

    return 0;
}
