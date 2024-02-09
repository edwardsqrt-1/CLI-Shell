# nextShell

## Introduction
Description: This program aims to create a Command Line Interface to be used on top of both Windows and UNIX/UNIX-like systems, all the while using the Windows syntax to allow Windows users to transition over to Linux and related systems without having to learn an entirely new command set (though you should anyway). 

Fun fact: Much of this was coded in OpenStep, who knew even ancient systems can help complete modern college assignments! This program mainly being done using OpenStep (a later version of NeXTStep is why I decided to give it the name of nextShell).

## System Requirements
While I have not tested compiling this on many systems with different operating systems, there's really not much that this program needs in terms of operating systems. As long as you have GCC (or in the case of NeXTStep/OpenStep, CC), you can theoretically compile this program on any 32bit or 64bit version of Windows, Linux, or any UNIX system, provided you install the MSYS2 library and set the path to your MinGW's bin folder.

## How to Compile
Using whichever method you prefer (either by clonging the repository or downloading the zip directly), all you need are the two files next.c and next.h. Place them in the same directory, and in a terminal use the command `gcc next.c -o next` to compile if you are using gcc (for cc, replace gcc with cc). This will generate an executable called "next" which upon opening will load the program.

## How to Use
Here are a list of commands you may use with this program:

`dir` - List contents of current directory 

`cd` - Display current directory

`cd [directory]` - Change to another directory

`mkdir [directory]` - Create a new directory

`echo [message]` - Print out a message

`type [filename]` - List out the contents of a file

`menu` - Pulls up this display 

`cls` - Clear the screen

`quit` - Exit the shell

## Notes
