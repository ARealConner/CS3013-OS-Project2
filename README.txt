Project 2: Synchronization and Concurrency

This project is a simulation of the Worcester Gompei Park (WGP), a sports facility that can house multiple
types of sports within a single facility. The simulation supports three different types of sports: baseball,
football, and rugby. The project is implemented in C and uses pthreads for concurrency.

Building the Project:

To build the project, you need to have GCC installed on your system.
You can build the project by running the following command in the terminal:

make

This will compile the source files and create an executable named 'Project2'.

Running the Project:

To run the project, you can use the following command:

./Project2

The simulation will then start and print output to the console.

Configuration:
All the configuration for the simulation is done in the 'shared.h' file.

Known Issues and Limitations:

1. The simulation does not keep track of which players are on which teams.
It simply assumes that the first half of the players on the field are associated
with Team 1 and the second half is associated with Team 2.

2. Sometimes rugby will start and end short games of two players. This is intentional
based on the requirements of the project allowing for teams of 1-15 players. However,
it can sometimes seem strange in the output as the game starts and ends almost immediately.
The reason it occurs at the end is that rugby is usually the last game with a player left,
since it is the only one that can have a non-static number of players. Thus, allowing for
more games of lesser players to be played.

3. By default, games can run back to back, but the simulation can be configured in the 'shared.h'
file to limit this by decreasing the MAX_GAMES_BEHIND. It is intentionally set to allow for
back to back games to be played because it allows for more varied output.