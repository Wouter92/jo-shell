                       _                      __           __ __
                      (_)____          _____ / /_   ___   / // /
                     / // __ \ ______ / ___// __ \ / _ \ / // / 
                    / // /_/ //_____/(__  )/ / / //  __// // /  
                 __/ / \____/       /____//_/ /_/ \___//_//_/   
                /___/                                           


A proof-of-concept UNIX shell implementation.

`jsh` is free software and makes use of the `GNU Readline` library for input line editing and history.

Configuration files:
 * `~/.jshrc`: file containing commands to be executed at login
 * `~/.jsh_history`: containing the command history auto loaded and saved at login/logout
 * `~/.jsh_login`: file containing the ASCII welcome message auto printed at login of an interactive session

Supported options:
* -h, --help	display the help message
* -d, --debug	turn printing of debug messages on
* -n, --nodebug	turn printing of debug messages on
* -c, --color	turn coloring of jsh output messages on
* -o, --nocolor	turn coloring of jsh output messages off
* -f, --norc	disable autoloading of the ~/.jshrc file
* -l, --license	display licence information

The following grammar is currently supported. Note that aliases are currenly only a hack...

```
 input  :=    expr

 expr   :=    <space>expr         // expr is a logical combination
              expr<space>
              expr #comment
              (expr)
              expr ; expr
              expr && expr
              expr || expr
              cmd

 cmd    :=    cmd | cmd           // cmd is the unit of truth value evaluation
              cmd >> path         // note: pipe redirection get priority over explicit redirection
              cmd 2> path
              cmd > path
              cmd < path
              cmd &               *TODO not yet implemented
              comd

 comd   :=    alias               // alias is a symbolic link to a comd; no expr or cmd...
              comd option         // comd is a single executable; the unit of built_in / fork
              built_in            // note: built_ins get priority over cmds
              executable path
```

Currenly supported built_ins:
* `cd`
* `color`
* `debug`
* `exit`
* `history`
* `shcat`
* `alias`      * unstable
* `unalias`    * not yet implemented

To compile `jsh`, clone this respository, `cd` into it and execute `make`.

Note: to disable debug info, do one of the following:
 * type `debug off`
 * include the line "`debug off`" in `~/.jshrc`
 * change the initialisation of the `DEBUG` global variable in `jsh.c`
