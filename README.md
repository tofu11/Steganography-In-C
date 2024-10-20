# Steganography In C
Image Steganography In C.

Steganography Is The Process To Hide Text Files In A Image Without Altering The Original Image.
The Text Is Hidden In .BMP Image Files.

# FILES

Stegano_header.h - It Has All The Program Function Prototypes.

Steganography.c - Is The Main Function Of The Program.

Encode.c - Encoding Function

Decode.c - Decoding Function

# FOR EXECUTION OF THE PROGRAM , FOLLOW THE STEPS :-

~$ gcc Steganography.c -o Stegano

# ENCODING

~$ Stegano -E -i input_image.bmp -s secret_text.txt -o output_image.bmp

# DECODING

~$ Stegano -D -i output.bmp -o text_output.txt

// text_output.txt Is To Store The Secret Text Present In Image.

# INDEX
	-E = ENCODING
	-D = DECODING
	-i = Input Source BMP Image / Output Image
	-s = Secret Text File
	-o = Output BMP Image / Output Text File
  
  ************ THANK YOU *****************
  
  # Biswajeet Sahoo.
# EXP02: Exploratory Project 02
Due on Friday November 8, no later than 5:00 PM.

## Overview

In this project you will work with code from an open source project.  _**Remember that the project is a vehicle to allow you and your teammates to demonstrate your facility with a methodical process for both dealing with bugs and adding new features, as well as the tools to support building high quality software.

## Advice

Remember that _**completing the coding is NOT the primary focus**_ of any exercise in this course, rather it is providing evidence of having used the tools and processes we've discussed. 

Use git, branches, frequent commits, and commit comments to document what your process is.  Use your team's Kanban board in conjunction with your team's GitHub repo, to demonstrate how each member of your team is involved in this project.

When tracking down a bug you are expected to create a bugfix branch (and document the bug you're fixing in the commit comment), write tests that reveal the bug on that branch, implement a fix on that branch, and once the tests pass, add transparent testing to get up to 100% code coverage again, and then merge back into the main branch.  Apply the lessons learned, and use all the tools covered so far!

For this project you should have ample opportunity to use gdb, but suppose there is a tool like gdb and you didn't find a natural use for it.  How could you demonstrate your proficiency with the tool.  Suppose you implemented a few feature and there are no bug you can tell.  You know we want to see evidence of tool use. You can make a commit comment that you don't see any bugs in the code so you will create one on a new branch so you can demonstrate your gdb skills. On the new branch, explain what you will break in the code, and how gdb will help you track it down (e.g. maybe comment out a call to malloc so a pointer is uninitialized, or something like that). Write tests, show that the tests fail, then run the code in the debugger and demonstrate how you can use the debugger to isolate the problem (capture output from gdb which shows the problem). Fix the bug, run gbd again, show the problem is addressed, and demonstrate that the tests pass.

Make sure each team member makes frequent enough commits, with detailed enough commit comments, so that when grading happens we can clearly see that for a given bit of functionality opaque tests were written before any implementation, then an implementation was build, then gcov was used to determine code coverage, and the transparent tests were written to achieve 100% code coverage.  If some member of your team is not engaging or contributing to the project you must document this via the tools you have.  For example, early on in the process the team should meet to do an initial task breakdown of the project (which of course can be refined as the project progresses).

One collaboration model is to have each team member pick a task and document it as theirs.  Once a team member has completed a task they pick another task.  This way no one team member hoards tasks, and the productive team members document that they are progressing through tasks.  Communication is key to successful teamwork - let the team know about your constraints (e.g. a midterm coming up).  Be sensitive to the fact that no everyone will be able to jump on the project at the same time.  It's OK if during the three weeks you have for this project contributions happen at different times.

Again: communication is essential.  As is planning.  And time management.  Don't start too late!  If you need help with any of these things reach out to the course staff.


## Scenario

You are working for [Q](http://jamesbond.wikia.com/wiki/Q) at [Universal Exports](http://jamesbond.wikia.com/wiki/Universal_Exports).  You and your crack cyberteam have to find a way for [007](http://jamesbond.wikia.com/wiki/007) to communicate surreptitously communicate with [M](http://jamesbond.wikia.com/wiki/M).

You come across the idea of [steganography](https://en.wikipedia.org/wiki/Steganography), and must locate an existing implementation to start from.

Bond has uncovered a nefarious [Spectre](http://jamesbond.wikia.com/wiki/SPECTRE) plot, and needs to send both some text and a photo.  But, heavens above, Spectre may gave sabotaged the code!


## Tasks

### CODEBASE CHOICE

You will need to search GitHub (the only site you may search) for a steganography project written in C with a license which allows you to modify the code, at least for educational purposes.  For example, you may wish to try [this search](https://github.com/search?q=steganography+license%3Agpl++language%3AC&type=repositories&l=C&s=updated&o=desc) as a starting point.  You may choose any GitHub project you wish that meets these requirements, but keep in mind you will need to work with the existing codebase and you will need to either fix bugs or extend the functionality of the given code, so we suggest starting from a simple and straightforward codebase.

### MAKEFILE
Add a makefile to support proper unit testing, coverage checking, and making the code to support any other tool you need to use.


### BUGS?
Verify that the code does what it claims to do.  Write tests to verify that it either does the correct thing or that there is a bug in the code.

Attempt to fix any bugs you discover.  If you do not find any bugs in the given code, then be sure to check for bugs after any code additions you make.


### FEATURE REQUEST 1 (if not already supported)
Ensure the code permits no only text but another image to be hidden in the source image.  Spell out the
size, color depth, or other restrictions on the image to be hidden, relative to the image in which is it hidden.

Add command-line arguments "-text" or "-image" to specify whether
text or image data is to be hidden, respectively.

Try to add this feature.


### FEATURE REQUEST 2 (if not already supported)
    
Ensure the code works with images encoded in a variety of formats, such as .bmp , .jpg,
.tiff, .raw and .gif.

Have the program deduce the file type automatically from the
extension on the filename.  If an unsupported file type is used
with the program it must exit with an appropriate message.

You may use other existing libraries to help implement this
functionality (e.g. a library to convert between formats) as long
as
1. the library's licensing permits it (add the library's license as a text file to your repo), and 
2. you give proper credit.

Try to add this feature.


### FEATURE REQUEST 3 (if not already supported)
    
Ensure the code will allow embedding of text encoded in a variety of ways in an image, such as US-ASCII, UTF-8, UTF-16, etc.

Add command-line arguments such as "-US-ASCII", "-UTF-8", "-UTF-16", etc to indicate the character encoding.
