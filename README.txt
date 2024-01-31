Project 2: Synchronization and Concurrency

This project is a simulation of the Worcester Gompei Park (WGP), a sports facility that can house multiple
types of sports within a single facility. The simulation supports three different types of sports: baseball,
football, and rugby. The project is implemented in C and uses pthreads for concurrency.

Building the Project:

To build the project, you need to have GCC installed on your system.
You can build the project by running the following command in the terminal:

make

This will compile the source files and create an executable named 'main'.

Running the Project:

To run the project, you can use the following command:

./main

The simulation will then start and print output to the console.

Known Issues and Limitations:

1. The simulation does not keep track of which players are on which teams.
It simply assumes that the first half of the players on the field are associated
with Team 1 and the second half are associated with Team 2.

2. The simulation does not enforce a maximum game time. The game time is a
random number between 1 and 10, and a game can continue as long as there
are enough players on the field.

3. The simulation does not handle the case where the seed file cannot be
opened or the seed cannot be read. In such cases, the program will print
an error message and exit.

4. The simulation does not handle the case where the number of players is
not enough to start a game. In such cases, the players will wait indefinitely.

5. The simulation does not handle the case where a player thread is interrupted
 (e.g., by a signal) while it is waiting to enter the field. In such cases,
 the player thread may fail to enter the field even when it is allowed to do so.
