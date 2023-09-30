***PIPEX 42***

## SUMMARY

Pipex was one of my favourite programs to code, I just found working with processes very enticing and informative. 
Pipex is a C program that replicates the functionality of the shell pipe (|) command. 

It runs with the syntax:

***./pipex infile cmd1 cmd2 outfile***, simulating the behavior of the shell command *< infile cmd1 | cmd2 > outfile*.

## THE FOUR HORSEMAN OF PROCESS MANIPULATION - pipe(), fork(), dup2(), and execve():
![THE FOUR HORSEMAN OF PROCESS MANIPULATION - pipe(), fork(), dup2(), and execve()](https://upload.wikimedia.org/wikipedia/commons/thumb/e/e1/Apocalypse_vasnetsov.jpg/520px-Apocalypse_vasnetsov.jpg)

- pipe(): Creates a communication pipe between two processes.
- fork(): Splits the current process into two parallel child processes.
- dup2(): Duplicates file descriptors, enabling redirection of input and output.
- execve(): Executes a new program.

***How Pipex Works with Two Child Processes:***

Pipex employs two child processes: one for cmd1 and the other for cmd2. The parent process waits for them to complete. Key steps include:

Using pipe() to create a pipe for communication between the two child processes.
Using fork() to create child processes for cmd1 and cmd2.
Redirecting file descriptors with dup2() to ensure that infile, cmd1, cmd2, and outfile are used correctly.
Executing cmd1 and cmd2 with execve() in the child processes.

The access() Function:
To prevent executing a non-existent command, Pipex uses the access() function. It checks if a command is both present and executable before running it.


## 🚀 About Me
![*Full stack developer*](https://github.com/noci0001/noci0001/assets/79120220/73d4cda4-8371-4ad3-9bbb-8d556b8b33d7)

### Hi there 👋, my name is *Sam*
I am Sam from Berlin, I code for a living and I live to code. I really enjoy low level languages like C and I mostly code in CPP. 
You can checkout my LinkedIn profile at [my LinkedIn](https://linkedin.com/in/samuelnocita)

## Authors

@noci0001](https://www.linkedin.com/in/samuelnocita/)
