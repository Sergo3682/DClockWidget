# DClockWidget
## Motivation

I made this app because I wanted to make a clock widget for personal use. It should come with a script to run it with my settings after log in. I'm working on the script but for now this is just a borderless digital clock window. Obviously there's a lot left to be done.

## Compiling
The code is written using SDL2 library. So you have to install it in order to compile it. After you've made sure you have SDL2 and can link it you can use Makefile of compile yourself. You can check which flags to use  with the following command:
>$ pkg-config --libs sdl2 

It should output something like 
> -lSDL2

After you've done it simply run
> $ make

or this command:
> $ gcc -lSDL2 -std=c99 ./src/*.c -o ./app

from DClockWidget directory. (You can change ./app to whatever name you like.)

## Usage
Run the program by running either
> ./app

or whatever name you gave the program at the previous step.
The program supports several flags. (Keep in ind that '-h' stands for height parameter and there for requires a numeric value to follow it). To get help you'll have to write '-\-help' or enter any unknown flag. 
| flag | long flag | description | value |
|------|-----------|---------------------------------------|-|
| -x | -\-pos_x| Window position coordinate X| integer |
| -y | -\-pos_y | Window position coordinate Y| integer|
| -w | -\-width | Window width | integer|
|-h| -\-height| Window height | integer
| \- | \-\-help | Show help | \-|


Tip: It is generally a good idea to set x:y ratio to about 7:1. Otherwithe the window looks hella funny =-]

## Exit

Right now the only way to exit is to press ctrl+C
