[Github Commit](https://github.com/jacobnb/EGP-410/commit/c6de05c8ba8d3aff2b73765e57bc21ef1d2f1d9b)

# To compile and link the project:
1. open EGP-410\GameAI\component steering SDL\steering.sln using Visual Studio
2. Compile using visual studio. either Build > Build Solution 
or click on the "Local Windows Debugger" button at the top of the screen
3. I haven't found any linking or targetting problems on the lab computers, 
but you may have to retarget projects for your windows SDK version

# Keyboard Inputs
Left Click = player travels to click location
Enter = Spawn an enemy unit that wanders and chases the player
D = Delete a random enemy unit
Esc = Quit the game


# Student Version
Code modified and accidentally obfuscated by Jacob B.

# EGP-410
Template projects for base code for EGP 410 assignments.

# This repository contains three major directories:
 * DeanLib - Base utility library provided by Dean Lawson. Memory tracking and basic vector mathematics utilities.
 * External Libs - Allegro 5.0.10 support libraries.
 * Game AI - Base source code for EGP 410 Assignments
   * pathfinding
   * state machine
   * steering

Building instructions are left up to the student. 

