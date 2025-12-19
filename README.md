# Simple Shell

A basic UNIX command line interpreter for Holberton School.

## What it does

This is a simple shell that executes commands. Give it a full path to a command and it runs it.

## Compile

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Usage

Interactive mode:
```bash
$ ./hsh
($) /bin/ls
file1 file2
($) 
```

Non-interactive mode:
```bash
$ echo "/bin/ls" | ./hsh
file1 file2
```

## What works right now

- Displays a prompt (#cisfun$)
- Runs commands with full paths like /bin/ls
- Handles Ctrl+D to exit
- Shows error when command not found

## Authors

Check the AUTHORS file.
