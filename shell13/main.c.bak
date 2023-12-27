#include "parse.h"
#include "stdio.h"

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

int main(int argc, char const* argv[])
{
    // The following is for testing purposes

    char tokens[MAX_NB_TOKENS][MAX_TOKEN_LEN] = { 0 };

    // Test SimpleCommand
    {

        const char* SIMPLE_CMD = " ls -a -l";
        printf("Simple cmd = %s\n", SIMPLE_CMD);

        int nb_tokens = tokenize(SIMPLE_CMD, tokens);
        if (nb_tokens == -1) {
            printf("Error while tokenizing:\n%s", SIMPLE_CMD);
        } else {
            print_tokens(tokens, nb_tokens);

            SimpleCommand simple_cmd;
            int consumed = parse_simple_command(tokens, nb_tokens, &simple_cmd);
            if (consumed == -1) {
                printf("###### Error while parsing SimpleCommand\n");
            } else {
                print_simple_command(&simple_cmd);
                printf("consumed  = %d\n", consumed);
                printf("remaining = %d\n", nb_tokens - consumed);
            }
        }
    }

    printf("\n\n\n");

    // Test CompoundCommand
    {
        const char* COMPOUND_CMD = "ls -a -l && pwd";
        printf("Compound cmd = %s\n", COMPOUND_CMD);

        int nb_tokens = tokenize(COMPOUND_CMD, tokens);
        if (nb_tokens == -1) {
            printf("Error while tokenizing:\n%s", COMPOUND_CMD);
        } else {
            print_tokens(tokens, nb_tokens);

            CompoundCommand compound_cmd;
            int consumed = parse_compound_command(tokens, nb_tokens, &compound_cmd);
            if (consumed == -1) {
                printf("###### Error while parsing CompoundCommand\n");
            } else {
                print_compound_command(&compound_cmd);
                printf("consumed  = %d\n", consumed);
                printf("remaining = %d\n", nb_tokens - consumed);
            }
        }
    }

    printf("\n\n\n");

    // Test CompoundCommand
    {
        const char* COMPOUND_CMD = "false || mkdir /root/project";
        printf("Compound cmd = %s\n", COMPOUND_CMD);

        int nb_tokens = tokenize(COMPOUND_CMD, tokens);
        if (nb_tokens == -1) {
            printf("Error while tokenizing:\n%s", COMPOUND_CMD);
        } else {
            print_tokens(tokens, nb_tokens);

            CompoundCommand compound_cmd;
            int consumed = parse_compound_command(tokens, nb_tokens, &compound_cmd);
            if (consumed == -1) {
                printf("###### Error while parsing CompoundCommand\n");
            } else {
                print_compound_command(&compound_cmd);
                printf("consumed  = %d\n", consumed);
                printf("remaining = %d\n", nb_tokens - consumed);
            }
        }
    }

    printf("\n\n\n");

    // Test CompoundCommand
    {
        const char* COMPOUND_CMD = "ls -a -l";
        printf("Compound cmd = %s\n", COMPOUND_CMD);

        int nb_tokens = tokenize(COMPOUND_CMD, tokens);
        if (nb_tokens == -1) {
            printf("Error while tokenizing:\n%s", COMPOUND_CMD);
        } else {
            print_tokens(tokens, nb_tokens);

            CompoundCommand compound_cmd;
            int consumed = parse_compound_command(tokens, nb_tokens, &compound_cmd);
            if (consumed == -1) {
                printf("###### Error while parsing CompoundCommand\n");
            } else {
                print_compound_command(&compound_cmd);
                printf("consumed  = %d\n", consumed);
                printf("remaining = %d\n", nb_tokens - consumed);
            }
        }
    }

    printf("\n\n\n");

    // Test CommandSequence
    {
        const char* SEQ_CMD = "ls -a -l && pwd ; hostname || mkdir -p /root/project";
        printf("Seq cmd = %s\n", SEQ_CMD);

        int nb_tokens = tokenize(SEQ_CMD, tokens);
        if (nb_tokens == -1) {
            printf("Error while tokenizing:\n%s", SEQ_CMD);
        } else {
            print_tokens(tokens, nb_tokens);

            CommandSequence seq_cmd;
            int consumed = parse(tokens, nb_tokens, &seq_cmd);
            if (consumed == -1) {
                printf("###### Error while parsing CommandSequence\n");
            } else {
                print_seq_command(&seq_cmd);
                printf("consumed  = %d\n", consumed);
                printf("remaining = %d\n", nb_tokens - consumed);
            }
        }
    }

    printf("\n\n\n");

    // Test CommandSequence
    {
        const char* SEQ_CMD = "ls -a -l & pwd & hostname || mkdir -p /root/project";
        printf("Seq cmd = %s\n", SEQ_CMD);

        int nb_tokens = tokenize(SEQ_CMD, tokens);
        if (nb_tokens == -1) {
            printf("Error while tokenizing:\n%s", SEQ_CMD);
        } else {
            print_tokens(tokens, nb_tokens);

            CommandSequence seq_cmd;
            int consumed = parse(tokens, nb_tokens, &seq_cmd);
            if (consumed == -1) {
                printf("###### Error while parsing CommandSequence\n");
            } else {
                print_seq_command(&seq_cmd);
                printf("consumed  = %d\n", consumed);
                printf("remaining = %d\n", nb_tokens - consumed);
            }
        }
    }

    printf("\n\n\n");

    // Test CommandSequence
    {
        const char* SEQ_CMD = "ls -a -l";
        printf("Seq cmd = %s\n", SEQ_CMD);

        int nb_tokens = tokenize(SEQ_CMD, tokens);
        if (nb_tokens == -1) {
            printf("Error while tokenizing:\n%s", SEQ_CMD);
        } else {
            print_tokens(tokens, nb_tokens);

            CommandSequence seq_cmd;
            int consumed = parse(tokens, nb_tokens, &seq_cmd);
            if (consumed == -1) {
                printf("###### Error while parsing CommandSequence\n");
            } else {
                print_seq_command(&seq_cmd);
                printf("consumed  = %d\n", consumed);
                printf("remaining = %d\n", nb_tokens - consumed);
            }
        }
    }

    printf("\n\n\n");

    // Test CommandSequence
    {
        const char* SEQ_CMD = "ls -a -l &";
        printf("Seq cmd = %s\n", SEQ_CMD);

        int nb_tokens = tokenize(SEQ_CMD, tokens);
        if (nb_tokens == -1) {
            printf("Error while tokenizing:\n%s", SEQ_CMD);
        } else {
            print_tokens(tokens, nb_tokens);

            CommandSequence seq_cmd;
            int consumed = parse(tokens, nb_tokens, &seq_cmd);
            if (consumed == -1) {
                printf("###### Error while parsing CommandSequence\n");
            } else {
                print_seq_command(&seq_cmd);
                printf("consumed  = %d\n", consumed);
                printf("remaining = %d\n", nb_tokens - consumed);
            }
        }
    }

    printf("\n\n\n");

    // Test CommandSequence ERROR
    {
        const char* SEQ_CMD = "ls -a -l &&";
        printf("Seq cmd = %s\n", SEQ_CMD);

        int nb_tokens = tokenize(SEQ_CMD, tokens);
        if (nb_tokens == -1) {
            printf("Error while tokenizing:\n%s", SEQ_CMD);
        } else {
            print_tokens(tokens, nb_tokens);

            CommandSequence seq_cmd;
            int consumed = parse(tokens, nb_tokens, &seq_cmd);
            if (consumed == -1) {
                printf("###### Error while parsing CommandSequence\n");
            } else {
                print_seq_command(&seq_cmd);
                printf("consumed  = %d\n", consumed);
                printf("remaining = %d\n", nb_tokens - consumed);
            }
        }
    }

    return 0;
}