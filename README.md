# Simple Shell

> A command-line interpreter that lets Linux and Unix users control their operating systems through a simple shell interface.

<p align="center">
  <img src="https://img.shields.io/badge/Language-C-blue?style=for-the-badge" alt="Language">
  <img src="https://img.shields.io/badge/Developed%20on-Arch%20Linux-1793D1?style=for-the-badge&logo=archlinux&logoColor=white" alt="Developed on">
  <img src="https://img.shields.io/badge/Tested%20on-Ubuntu%2022.04%20%7C%20Arch-orange?style=for-the-badge" alt="Tested on">
</p>

---

## Quick Start

```bash
git clone https://github.com/starfruitone/holbertonschool-simple_shell.git
cd holbertonschool-simple_shell
./hsh
```

> **Note:** The repository includes a pre-compiled binary (`hsh`). To compile it yourself, remove the existing binary first with `rm hsh`, then run the compile command below.

---

## Compilation

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

---

## Usage

### Interactive Mode

```bash
$ ./hsh
$ ls
AUTHORS  hsh  main.c  README.md  shell.h  tokenizer-pro-max.c
$ pwd
/home/user/holbertonschool-simple_shell
$ echo Hello World
Hello World
$ env
USER=user
HOME=/home/user
PATH=/usr/local/bin:/usr/bin:/bin
...
$ exit
```

### Non-Interactive Mode

```bash
$ echo "ls" | ./hsh
$ echo "pwd" | ./hsh
$ cat commands.txt | ./hsh
```

---

## Built-in Commands

| Command | Description |
|:-------:|:------------|
| `exit`  | Exit the shell |

---

## Flowchart

<details>
<summary>Click to expand</summary>

```mermaid
flowchart TD
    A[Start] --> B{Interactive Mode?}
    B -->|Yes| C[Display Prompt '$']
    B -->|No| D[Read Input]
    C --> D
    D --> E{EOF / Ctrl+D?}
    E -->|Yes| F[Print Newline if Interactive]
    F --> G[Free Line Buffer & Exit]
    E -->|No| H[Remove Trailing Newline]
    H --> I{Empty Input?}
    I -->|Yes| C
    I -->|No| J[Tokenize Input]
    J --> K{Tokens Valid?}
    K -->|No| L[Free Tokens]
    L --> C
    K -->|Yes| M{Command = 'exit'?}
    M -->|Yes| N[Free Tokens & Exit]
    M -->|No| O[Search Command in PATH]
    O --> P{Command Found?}
    P -->|No| Q[Print Error]
    Q --> L
    P -->|Yes| R[Fork Process]
    R --> S{Fork Failed?}
    S -->|Yes| T[Print Error & Cleanup]
    T --> C
    S -->|No| U{Child Process?}
    U -->|Yes| V[execve Command]
    U -->|No| W[Wait for Child]
    W --> X[Free Tokens & cmd_path]
    X --> C
    V --> Y[Command Executes]
```

</details>

---

## File Structure

| File | Description |
|:-----|:------------|
| `main.c` | Entry point, main loop, PATH search, command execution |
| `tokenizer-pro-max.c` | Tokenizes user input into argument array |
| `shell.h` | Header file with function prototypes and includes |
| `man_1_simple_shell` | Manual page for the shell |

---

## Requirements

| Requirement | Details |
|:------------|:--------|
| Editors | `vi`, `vim`, `emacs` |
| Compiler | `gcc` on Ubuntu 20.04 LTS |
| Flags | `-Wall -Werror -Wextra -pedantic -std=gnu89` |
| Style | Betty |
| Memory | No leaks |
| Functions | Max 5 per file |
| Headers | Include guarded |

---

## Man Page

```bash
man ./man_1_simple_shell
```

---

## Authors

<table>
  <tr>
    <td align="center">
      <a href="https://github.com/starfruitone">
        <b>Alexander Durant</b>
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/Nano420x">
        <b>Nano420X</b>
      </a>
    </td>
  </tr>
</table>
