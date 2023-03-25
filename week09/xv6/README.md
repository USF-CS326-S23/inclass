# Week06 
Week06 In-class examples

Here are the example programs added to the user directory

```fork.c```
- Basic fork()/wait() example showing address space is copied

```fork2.c```
- Variation of fork.c with parent code outside if() statement

```fork3.c```
- Variation of fork2.c with child code in a function and global x

```forkwait.c```
- Example of fork()ing two processes

```forkexec.c```
- Example of fork()ing a process and exec()ing a command in child

```forkexec2.c```
- Variation of forkexec.c with echo command and a arg

```redirect.c```
- Redirect stdout of child to a file

```redirect2.c```
- Redirect stdin of a child to come from a file

```pipe.c```
- Use a pipe to send data from child to parent

```pipe2.c```
- Use a pipe to send data from one child to another child

```pipe_redirect```
- Use a pipe to redirect output of parent to input of child command
