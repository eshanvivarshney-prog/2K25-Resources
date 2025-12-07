# DESCRIPTION

## Usage

To compile the program, run it in the directory where the Makefile is present

```bash
make all
```

Note: The file uses a simple makefile that compiles everything and runs it.

## Assumptions

The size of the username, content and caption will be fixed at a finite value, say 100 characters. Can be easily changed using the macros defined in header files.

Assuming createPlatform is the first command to be called. Also assuming it is called just once.

Assuming every input is given on a different line.

In inputs involving nth recent posts/comments/replies, n will be positive integer greater than 0
