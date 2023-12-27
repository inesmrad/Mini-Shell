# Mini-Shell

Implementation of a minimalistic Shell
I. Introduction:
The goal of this project is to implement a simple minimalistic Shell.
A Shell is a program whose primary purpose is to launch other programs. Users can type a command inside 
the textual interface provided by the shell, and get it executed by pressing the ENTER button. The (textual) 
output of the command will then be shown inside the Shell unless redirected or muted. As examples, we 
can find: “sh”, “bash”, “tcsh”, “ash”, “zsh”, “fish”, …
This project must be developed under a Linux environment and must NOT use the “system()” function
which means that the use of some “system call” functions will be needed like “open()”, “fork()”, “exec()”, 
“wait()” and other variants.
II. Basic functionalities:
The Shell must offer the user the ability to benefit from two different modes of execution:
• Interactive mode:
In this mode, the Shell will present a textual interface to the user letting him enter any command 
(simple or compound) and fire the execution by pressing the ENTER button.
Each line (for distinct commands) must start with a “prompt” that displays the current working 
directory and must end with the character “%” to delimit the “prompt” from the command that 
will be specified by the user. Examples: /path/to/dir % ls
Pressing the ENTER button will start a new child process dedicated for the execution of the 
command and the output will be displayed inside the shell. After the execution, the Shell will start 
a new “prompt” and wait for new commands.
Using the special command “quit” will force the Shell to exit.
• Batch mode:
On the other hand, this mode is meant for automation and will let a user write a text file containing 
multiple commands, each in a distinct line, and execute them sequentially all at once by only 
supplying the name of the file to the Shell. For each line, the Shell must show the full statement 
of the command, execute it, and go to the next one until it reaches the end of file or the “quit” 
special command.

A command can be a simple command that executes a single program with its specified arguments or be 
a compound command that contains special operations:
• “;” separates simple or compound commands and makes sure all the commands are executed 
sequentially. 
• “&” separates simple or compound commands and makes sure all the commands are executed in 
parallel.
• “&&” separates two simple commands but makes sure to execute the second command only if 
the first one succeeds.
• “||” separates two simple commands but makes sure to execute the second command only if the 
first command fails.
Examples of compound commands:
• cmd1 ; cmd2 ; cmd3
• cmd1 && cmd2
• cmd1 || cmd2
• cmd1 && cmd2 ; cmd3 || cmd4 ; cmd5
III. Advanced functionalities:
Improve the Shell by adding extra features and facilities:
1. Add support for pipes. Example: cmd1 | cmd2
Hint: Add extra operator to the “CommandOperator” enumeration.
2. Add support for output redirection. Example: cmd1 > file1
Hint: Add extra attributes to the “SimpleCommand” structure.
3. Handle errors:
The Shell must print adequate error messages in the “stderr” channel and exists in the 
following use cases:
• Batch file not found.
• Unexpected Shell argument.
The Shell must print adequate error messages in the “stderr” channel and continue the 
execution in the following use cases:
• Command not found.
• Command cannot be executed for some reason.
4. In interactive mode, save the history of the commands in a file named “history.txt” in the 
same working directory.

IV. Shell development 
The project must be developed by a team of 3 students. It must be written using the C programming 
language in a Linux environment and the code must be written in a modular way. To build the project, the 
“make” command must be used, so there is a need to write a dedicated “Makefile” for the project to build 
an executable named “shell”.
Each group must follow the bellow instructions:
1. Create a “main.c” file which will hold the “main” function.
This file should take care of calling the other adequate functions declared in the other files (READ 
the WHOLE instructions for details). It may be necessary to add extra helper functions.
2. Create a “Makefile” file for the project (Initially to build the “main.c” file but it must be updated 
later to support the other .c files).
3. Create “parse.h” and “parse.c” files that contains functions and structures related to structuring 
the command entered by the user.
To be able to handle all kind of commands you will need to implement a parser that analyses the user 
input (simple or compound command as text) and re-arrange it in special structures for easier 
development and maintenance. The parsing process is mainly composed of two phases:
• Phase 1, Tokenizing:
o The input is the raw text (simple or compound command)
o The output is an array of words (tokens).
o In this phase, the Shell should extract all the words (tokens) of the command. Tokens may 
be separated with spaces or tabs.
Please note that we are going to suppose that operators (; & …) must always be 
surrounded by spaces or tabs.
• Phase 2, Parsing:
o The input is an array of words (tokens) that compose a command.
o The output is a special structure that represents a command.
o In this phase, the Shell should analyze the array of tokens and re-arrange them in a 
structured manner.

The Shell source code must use the following structures:
#define MAX_NB_TOKENS 1000
#define MAX_TOKEN_LEN 50
#define MAX_NB_ARGS 10
#define MAX_NB_CMDS 10
struct SimpleCommand
{
 char program_name[MAX_TOKEN_LEN];
 char args[MAX_NB_ARGS][MAX_TOKEN_LEN];
 int nb_args;
}
typedef struct SimpleCommand SimpleCommand;
enum CommandOperator
{
 OPERATOR_NONE,
 OPERATOR_AND,
 OPERATOR_OR
};
typedef enum CommandOperator CommandOperator;
struct CompoundCommand
{
 SimpleCommand cmd1;
 SimpleCommand cmd2;
 CommandOperator op;
};
typedef struct CompoundCommand CompoundCommand;
struct CommandSequence
{
 CompoundCommand cmds[MAX_NB_CMDS];
 int nb_cmds;
 bool in_parallel;
};
typedef struct CommandSequence CommandSequence;

Every user input (textual command) must be tokenized to create an array of tokens then parsed into a one 
unique “CommandSequence” structure.
The following functions must be implemented (Other functions could be added if there is any need):
// Tokenize the input of the user
// Returns the number of tokens if there is no error, or -1 if there is an error
int tokenize(
 char* input,
 char tokens[MAX_NB_TOKENS][MAX_TOKEN_LEN]
);
// Parse tokens into CommandSequence
// Returns the number of consumed tokens, if there is no error, or -1 if there is an error
// It calls the other related parse_* functions
int parse(
 char tokens[MAX_NB_TOKENS][MAX_TOKEN_LEN],
 int nb_tokens,
 CommandSequence* command
);
// Parse tokens into CompoundCommand
// Returns the number of consumed tokens, if there is no error, or -1 if there is an error
// It calls the other related parse_* functions
// Take not that if there is one SimpleCommand, the CompoundCommand must have
// op = OPERATOR_NONE which means that cmd2 is not filled.
int parse_compound_command(
 char tokens[MAX_NB_TOKENS][MAX_TOKEN_LEN],
 int nb_tokens,
 CompoundCommand* command,
);
// Parse tokens into SimpleCommand
// Returns the number of consumed tokens, if there is no error, or -1 if there is an error
int parse_simple_command(
 char tokens[MAX_NB_TOKENS][MAX_TOKEN_LEN],
 int nb_tokens,
 SimpleCommand* command,
);

4. Create “launch.h” and “launch.c” files that contains functions related to launching a command 
entered by the user.
The following functions must be implemented (Other functions could be added if there is any need):
// Execute a simple or compound command
// Returns 0 if there is no error, or -1 if there is an error
// It calls the other related launch_* functions
int launch_command(CommandSequence* command);
// Execute a compound command
// Returns 0 if there is no error, or -1 if there is an error
// It calls the other related launch_* functions
int launch_compound_command(CompoundCommand* command);
// Execute a simple command
// Returns 0 if there is no error, or -1 if there is an error
int launch_simple_command(SimpleCommand* command);
5. Create “interactive.h” and “interactive.c” files and implement a function dedicated for running the 
Shell in interactive mode: Show the Shell user interface, display the prompt, read the input of the 
user, and call the adequate functions to start the execution.
// Run the Shell in interactive mode
// Returns 0 if there is no error, or -1 if there is an error
int interactive_mode();
6. Create “batch.h” and “batch.c” files and implement a function dedicated for running the Shell in 
batch mode: Read a text file containing a list of commands (each in a distinct line) and launch 
them one by one sequentially by calling the adequate functions.
// Run the Shell in interactive mode
// Returns 0 if there is no error, or -1 if there is an error
int batch_mode(char* file_name);
7. The program must consider the fact that the user may provide zero, one or multiple file names as 
arguments. Those files, once specified, are supposed to contain commands to be executed by the 
shell in batch mode.
In case the user, executes the shell without any arguments, it gets executed in interactive mode.
$ shell

In case the user, executes the shell with some arguments (file names), it gets executed in batch mode.
$ shell file1 file2
The “file1” file could contain multiple (simple or compound) commands each in a distinct line like the 
following:
ls -l
sleep 10 & sleep 5 & sleep 2
ps | grep sleep > output
V. Project submission
The project must be submitted by one of the members of the team on Moodle. All the files must be packed 
into an archive file (“.tar” extension, using “tar” command). The file name must be in the following format:
“shell-TEAM_NUMBER.tar” replacing “TEAM_NUMBER” by the number of the team published earlier.
The archive must include a textual file named “team.txt” containing the @medtech.tn emails of the team 
members each in a distinct line.
The deadline for the submissions is November 19th, at 23h00. It will be followed by an “On-PC
Exam” to check that every member of the teams understands all the aspects of the project. The 
exam will be held on your regular lab sessions in the week 11 (from November 20th to 24th).
IMPORTANT NOTES:
• The archive file must NOT contain any compiled files (object files and executable)!
• Except for the files named in the project specification, you are not allowed to create extra files!
• If the batch mode is NOT implemented, the team will get severe penalties!
• Any team that submits a project with the following problems will get an immediate ZERO without 
any further evaluation:
o The archive name is NOT correct.
o The project does NOT compile.
o The shell executable, once compiled, is NOT named “shell”.
o The project files specified in the project specification are NOT named correctly.
o The required function signatures do NOT match the project specification.
o The required structure names do NOT match the project specification.
o The emails, contained in the “team.txt” file, are NOT correct.
Good work !
