> *This project has been created as part of the 42 curriculum by tseche, rcompain*

---

# Minishell

---

## Description

**Minishell** is a project at 42 School designed to help students understand the inner workings of a Unix shell. The goal is to create a simple yet functional shell that can execute commands, handle pipes, redirections, environment variables, and built-in commands. This project deepens your knowledge of process creation, file descriptors, and system calls in C.

---

## Features

- **Command Execution:** Run simple commands (e.g., `ls`, `cat`, `echo`).
- **Pipes (`|`):** Chain commands using pipes.
- **Redirections (`>`, `>>`, `<`):** Redirect input/output to/from files.
- **Environment Variables:** Handle and expand environment variables.
- **Built-in Commands:** Implement built-in commands like `cd`, `echo`, `env`, `exit`, `export`, and `unset`.
- **Signal Handling:** Manage signals like `Ctrl+C`, `Ctrl+D`, and `Ctrl+\`.
- **History:** Keep track of command history.
- **Priorities (`(`,`)`):** Gave some commands some priorities for execution.
- **Wildcards (`*`):** Match vraiable to current file directory
- **Conditional (`&&`, `||`):** Implementation of boolean expression

---

## Instructions

### Compilation

1. Clone the repository:
  ```bash
   git clone git@github.com:Remi-cpn/minishell.git
   cd minishell
  ```
2. Compile the project:
  ```bash
   make
  ```

### Execution

Run the shell:

```bash
./minishell
```

### Usage

Once the shell is running, type commands as you would in a standard Unix shell. For example:

```bash
$ ls -l
$ cat file.txt | grep "pattern"
$ echo "Hello, World!" > output.txt
```

### Exiting the Shell

To exit the shell, use the `exit` command or press `Ctrl+D`.

---

## Resources

### Documentation & References

- [Bash Manual](https://www.gnu.org/software/bash/manual/)
- [Advanced Programming in the UNIX Environment](https://www.apuebook.com/)
- [TLPI (The Linux Programming Interface)](https://man7.org/tlpi/)
- [Bash GNU implemetation](https://cgit.git.savannah.gnu.org/cgit/bash.git/tree/)

### AI Usage

AI tools were used for:

- **Research:** Gathering information about shell implementation, system calls, and process management.
- **Debugging:** Assisting in identifying and resolving bugs in the code.
- **Documentation:** Helping draft and structure the README and project documentation.

---

