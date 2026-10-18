# Mini Shell in C

A simple command-line shell written in C for learning processes, system calls, and command execution on macOS.

## Features

- Read and execute commands in a loop
- Split input into a command and arguments
- Run external programs using `fork()` and `execvp()`
- Wait for commands to finish using `waitpid()`
- Change directories with the built-in `cd` command
- Go to the home directory with `cd` without arguments
- Exit using `exit` or Ctrl+D on an empty input line
- Display errors when commands or directory changes fail
- Reject input lines that exceed the supported length
- Reject commands with more than 63 tokens, including the command name
- Keep the shell running when Ctrl+C interrupts an external command
- Retry waiting for a child process if `waitpid()` is interrupted by a signal

## Requirements

- macOS
- Clang compiler

## Build and Run

Open a terminal in the project folder and compile:

```bash
clang main.c -o mini-shell
```

Run the shell:

```bash
./mini-shell
```

## Example Usage

```text
mini-shell> echo Hello
Hello
mini-shell> cd /tmp
mini-shell> pwd
/private/tmp
mini-shell> cd
mini-shell> cd /tmp /Users
cd: too many arguments
mini-shell> exit
```

On macOS, `/tmp` may resolve to `/private/tmp`.

## How It Works

1. Read a line using `fgets()`.
2. Remove the trailing newline.
3. Split the input into tokens using `strtok()`.
4. Handle built-in commands in the shell process.
5. Create a child process with `fork()` for external commands.
6. Replace the child process with the requested program using `execvp()`.
7. Wait for the child process to finish before reading another command.

The `cd` command runs in the parent process so that the shell's working directory changes.

## Current Limitations

- Arguments are separated by spaces and tabs; quoted strings and escaping are not supported.
- Input uses a fixed 1024-byte buffer. A newline must fit in the buffer, allowing up to 1022 bytes before Enter.
- Input without a trailing newline is currently rejected, even if it is short.
- Commands are limited to 63 tokens, including the program name.
- Pipes, redirection, and background execution are not supported.
- Command history, arrow-key navigation, and tab completion are not supported.
- Ctrl+C is ignored at the prompt; clearing the current input line is not implemented.

## Learning Goals

- C strings, arrays, and pointers
- Command parsing
- Parent and child processes
- POSIX system calls
- Error handling
- Git and GitHub basics
