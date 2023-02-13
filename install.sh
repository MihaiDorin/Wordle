#!/bin/bash

# install xterm required for playing the game
if test $# == 0; then
    if test -f /usr/bin/xterm 2> /dev/null; then
        echo "XTerm is already installed"
    else
        sudo apt update
        sudo apt install xterm
    fi
    # compile the game
        make
fi

if test $1 == uninstall; then
    make clean
fi