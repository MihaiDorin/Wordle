# Wordle
Wordle game implementation using `ncurses`.
# Installation
If you can't execute the installation script, you have to give executable permision to it. You can do it with:

    chmod +x install.sh

After that, just run the script. You have to enter your password for xterm installation.

For additional help use:

    ./install.sh -h
# Game rules
You are given a random generated 5 letters word and you have to guess it. You tipe your word and press ENTER. After pressing ETNER the letters will have the following
colors:

${\color{red}\text{red}}$ if the letter exists in the word and it's on the good position;

${\color{yellow}\text{yellow}}$ if the letter exists in the word but it's not on the good position;

${\color{green}\text{green}}$ if the letter doesn't exist in the word;

You have 6 chances to guess the word. If not, a "GAME OVER" menu appears. You have to choose if you want to give up or try to guess another word.
If you win you also have to choose if you want to play again or, if you got bored of guessing words, quit and do something else.
