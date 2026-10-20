# Mini Shell in C

A simple command-line shell written in C to learn command parsing, process management, and POSIX system calls.

Developed and tested on macOS.

## Features

- Read and execute commands in a loop
- Split commands and arguments using spaces and tabs
- Execute external programs using `fork()` and `execvp()`
- Wait for child processes using `waitpid()`
- Retry waiting when interrupted by a signal
- Change directories with the built-in `cd` command
- Go to the home directory when `cd` is used without arguments
- Exit using `exit` or Ctrl+D on an empty input line
- Keep the shell running when Ctrl+C interrupts an external command
- Reject oversized input and excessive tokens
- Display errors for failed commands and directory changes
- Redirect external command output with `command > file`

## Requirements

- A POSIX-compatible operating system, such as macOS or Linux
- A C compiler, such as Clang or GCC

Currently tested on macOS.

## Build and Run

Open a terminal in the project folder and compile:

```bash
clang -Wall -Wextra main.c -o mini-shell
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
mini-shell> echo hello > output.txt
mini-shell> cat output.txt
hello
mini-shell> exit
```

On macOS, `/tmp` may resolve to `/private/tmp`.

## Built-in Commands

### cd

Change the shell's working directory:

```text
cd /tmp
```

Use `cd` without arguments to go to the directory specified by the `HOME` environment variable.

Only one directory argument is accepted.

### exit

Close the shell:

```text
exit
```

## Output Redirection

Use `>` to write an external command's standard output to a file:

```text
echo hello > output.txt
```

The file is created if it does not exist. If it already exists, its contents are overwritten.

The supported form is:

```text
command arguments > filename
```

- Separate `>` from surrounding tokens with spaces.
- Place one output redirection at the end of the command.
- Standard error remains connected to the terminal.
- Redirection for built-in commands is not supported.

## How It Works

1. Display the prompt and flush standard output.
2. Read a line using `fgets()`.
3. Remove the newline, or discard and reject input without one.
4. Split the input into tokens using `strtok()`.
5. Check token limits and output redirection syntax.
6. Handle `cd` and `exit` in the shell process.
7. Create a child process using `fork()` for external commands.
8. Restore the default Ctrl+C behavior in the child.
9. If requested, open the output file and connect it to standard output using `dup2()`.
10. Execute the requested program using `execvp()`.
11. Wait for the child process to finish before accepting another command.

The `cd` command runs in the parent process because it must change the shell's own working directory.

Output redirection runs in the child process so that the shell's prompt stays connected to the terminal.

## Current Limitations

- Quoted strings and escaping are not supported.
- Input uses a fixed 1024-byte buffer. Up to 1022 bytes before the newline are accepted.
- Input without a trailing newline is rejected, even when it is short.
- Input is limited to 63 tokens, including the command name and any redirection tokens.
- Only a single trailing `> filename` output redirection is supported.
- Input redirection (`<`), append redirection (`>>`), and pipes (`|`) are not supported.
- Background execution and job control are not supported.
- Environment variable expansion, wildcard expansion, and tilde expansion are not supported.
- Command history, arrow-key navigation, and tab completion are not supported.
- Ctrl+C is ignored at the prompt; a custom input-line reset is not implemented.

## Learning Goals

- C strings, arrays, and pointers
- Command parsing
- Parent and child processes
- POSIX system calls
- File descriptors and output redirection
- Basic signal handling
- Error handling
- Git and GitHub basics