# 42sh - A bash-like UNIX Shell
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/3b06508057f24125af6d991b9f25f021)](https://app.codacy.com/manual/acuD1/42sh?utm_source=github.com&utm_medium=referral&utm_content=acuD1/42sh&utm_campaign=Badge_Grade_Dashboard)

Documentation in progress ...

This is our final branch project at 42 School, an UNIX shell with several POSIX builtins.

---

## Getting started

```
$ git submodule update && git submodule init
$ make
$ ./42sh
```
***

## Help

```
make help
./42sh -h
```

***

## Command line editing

1.  Clipboard
    -   Copy : ```CTRL + K```
    -   Paste : ```CTRL + P```
    -   Cut : ```CTRL + X```

2.  Selection mode
    -   Right : ```CTRL + SHIFT + RIGHT ARROW```
    -   Left : ```CTRL + SHIFT + LEFT ARROW```

3.  Move in line
    -    Start : ```HOME``` or ```CTRL + A```
    -    End : ```END``` or ```CTRL + E```

4.  Clear end of line : ```CTRL + N```

5.  Move word
    -    Forward : ```CTRL + F```
    -    Backward : ```CTRL + B```

6.  Clear screen : ```CTRL + L```

7.  Move cursor in column
    -    Up : ```SHIFT + ARROW UP```
    -    Down : ```SHIFT + ARROW DOWN```

***

## Builtins

This is a list of all builtins available in 42sh. Builtins options are POSIX compliant. See man for futher informations.

*  ```bg```
*  ```cd [-PL]```
*  ```echo```
*  ```exit```
*  ```export```
*  ```fc [-e ename] [-lnr] [first] [last] or fc -s [pat=rep] [command]```
*  ```fg```
*  ```hash [-rl] [-p pathname] [-dt] [name ...]```
*  ```jobs [-lp]```
*  ```pwd [-PL]```
*  ```set```
*  ```test [-bcdefgLprSsuwxz=!=eqnegeltlw]```
*  ```type```
*  ```unset```

***

## Execution and Job Control

The execution receives a linked list of jobs (created in the LPA), each link contains a linked list of processes.

We define jobs as following:
*  One or more processes
*  Delimited by `;`, `&` or `\n`
*  Can be stopped by `pressing cltr + z`
*  Can be put in **background** with `bg` or `&` (example: 'ls -lR / &') or in **foreground** with `fg`

And processes:
*  One or more redirections and/or one assignation and/or one program/builtin call
*  Delimited by `;`, `&`, `||`, `&&`, `|` or newline
*  Can be part of a condition or piped in another process


***

## Shell command language

...

***

