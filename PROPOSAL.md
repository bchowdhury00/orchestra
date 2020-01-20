# Orchestra

Systems Proposal - Biraj Chowdhury, Leo Shestakov, Alex Thompson

### A statement of the problem you are solving and/or a high level description of the project.

We want to create a program that acts as a virtual orchestra. This means our program will have one computer host the server, acting as the conductor, and other computers that play the separate audio files for the instrumentals.

### User Interface

Upon running the program, our user will be directed to a list of musical pieces that our program has the capacity to play. After selecting a piece, the host will direct each computer in the network to play the music.

### Technical Design
How you will be using the topics covered in class in the project?

#### Allocating memory

We need to be able to read in some form of user input to mark instrument selection per process.

#### Working with files

The process will select a single music track to be played from a library of tracks depending on user input.

#### Finding information about files

We will show information about each of the available music tracks to aid the user in selecting one.

#### Networking

We need to use networking to connect multiple computers to play each piece in a synchronized way.

#### Shared Memory

We will have to utilize shared memory so that each process is able to determine which audio file it is responsible for playing and no instrument is used more than once.

### Project Breakdown

  Biraj - Will work on incorporating the networking.

  Alex - Responsible for implementation of shared memory and facilitating the interprocess communication.

  Leo - Responsible for creating the program that plays the audio file.

### Algorithms/Data Structures

-Semaphores will indicate the number of active users/instruments in the orchestra. The accessible shared resource for them is the library of instruments.

-Linked Lists will be used to store the various songs available to be played from our virtual orchestra with each of their parts

### Timeline with expected completion dates of parts of the project:

-Monday 1/6/2019: Connect Multiple computers and display some sort of output.

-Friday 1/11/2019: Be able to run an audio file on each computer while connected

-Monday 1/14/2019: Be able to run an actual piece of music using multiple computers

-Thursday 1/17/2019: Project Due! Clean up user interface and add multiple songs to our library. Test Functionality.
