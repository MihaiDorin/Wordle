#!/bin/bash

MSG="Usage: ./install.sh [option]\n\n\tOptions: -u (uninstall) | -h (help)\n\n\tType ./install.sh to install xterm and compile the game.\n\n\t\
Use 'make run' to play the game.\n\n\tType './install.sh -u' to uninstall xterm and clean the workspace.\n"

if test $# == 0; then
    sudo apt-get update

    # install ncurses
    sudo apt-get install -y libncurses5-dev libncursesw5-dev

    # install xterm
    if test -f /usr/bin/xterm 2> /dev/null; then
        echo "XTerm is already installed"
    else
        sudo apt-get install -y xterm
    fi

    # compile the game
    make
fi

if test $# == 1; then
    if test $1 = -u; then
        # clean the workspace
        make clean
    elif test $1 = -h; then
        echo -e $MSG
    else
        echo -e $MSG
    fi
fi
