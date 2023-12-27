#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"
#include "launch.h"
#include "batch.h"
#include "interactive.h"
void print_seq_command(CommandSequence* seq_cmd);
void print_tokens(char tokens[MAX_NB_TOKENS][MAX_TOKEN_LEN], int nb_tokens);


int batch_mode(char* file_names[], int num_files) {

     for (int i = 0; i < num_files; i++) {
        char* file_name = file_names[i];
	FILE* file = fopen(file_name, "r");
	if (file == NULL) {
        	printf("Error opening file: %s\n", file_name);
        	return -1;
	}

    char line[MAX_INPUT_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0';  // Remove newline character

        char tokens[MAX_NB_TOKENS][MAX_TOKEN_LEN] = { 0 };
        int nb_tokens = tokenize(line, tokens);
        if (nb_tokens == -1) {
            printf("Error while tokenizing:\n%s\n", line);
            fclose(file);
            return -1;
        }
	print_tokens(tokens, nb_tokens);

        CommandSequence seq_cmd;
        int consumed = parse(tokens, nb_tokens, &seq_cmd);
        if (consumed == -1) {
            printf("Error while parsing CommandSequence\n");
            fclose(file);
            return -1;
        }
	print_seq_command(&seq_cmd);

        // Launch the command sequence
        int success = launch_command(&seq_cmd);
        if (success == 0) {
            printf("Command sequence executed successfully\n");
        } else {
            printf("Error while executing command sequence\n");
            fclose(file);
            return -1;
        }
    }

    fclose(file);
}
 // Call the interactive mode function
    int result = interactive_mode();
    if (result == -1) {
        printf("Error in interactive mode\n");
        return -1;
    }

    return 0;
}
