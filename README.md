# Pipex Project

## Project Description

The Pipex project is a simple implementation of a pipe mechanism in Unix-like systems. It executes two commands in sequence, using the output of the first command as the input for the second. The program is designed to mimic the behavior of the following shell command:

```bash
< file1 cmd1 | cmd2 > file2
```

## Usage

The program is executed with four arguments:

```bash
./pipex file1 cmd1 cmd2 file2
```

where:

- `file1` and `file2` are filenames,
- `cmd1` and `cmd2` are shell commands with their parameters.

For example:

```bash
./pipex infile "ls -l" "wc -l" outfile
```

This command should behave like: 

```bash
< infile ls -l | wc -l > outfile
```

## Compilation

A Makefile is provided to compile the source files. The Makefile will not relink files that have already been compiled.

## Error Handling

The program is designed to handle errors thoroughly and should never exit unexpectedly due to segmentation faults, bus errors, double frees, etc. It also ensures no memory leaks occur.

## Bonus Features

Bonus points will be awarded for the following additional features:

- **Handling Multiple Pipes**: The program should be able to handle multiple commands in sequence, such as:

    ```bash
    ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
    ```

    This should behave like:

    ```bash
    < file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2
    ```

- **Support for Here Documents and Append Output Redirection**: The program should support the `<<` (here document) and `>>` (append output redirection) symbols when the first parameter is "here_doc". For example:

    ```bash
    ./pipex here_doc LIMITER cmd cmd1 file
    ```

    This should behave like:

    ```bash
    cmd << LIMITER | cmd1 >> file
    ```
