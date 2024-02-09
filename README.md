# nextShell

## Introduction
This program aims to create a Command Line Interface to be used on top of both Windows and UNIX/UNIX-like systems, all the while using the Windows syntax to allow Windows users to transition over to Linux and related systems without having to learn an entirely new command set (though you should anyway). 

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
One of the most challenging things I have learned while doing this project is not implementing the system calls, but making sure that no malformed system calls get through that have the potential of screwing something up due to a typo. While no systems were bricked in the making of thsi program, I have had my fair share of moments where the program spirals into an infinite loop and requires a termination of the program entirely. While there are not any deletion commands in this program for an accidental deletion of system files to happen (not to mention that as long as you run it as a user and not an admin/root, it will not harm your core system files), implementing them would be a risky task to take if you do not do it right. After all, the system() function is whhat allows a program to talk to the operating system directly!

Also you might notice moments where I have used C preprocessor directives to di9fferentiate between Windows and UNIX systems, while I will admit they could have been implemented better, I wanted to give compiling for any system a try considering they use different command sets at times.
