# Drum Orchestra

Biraj Chowdhury (5th), Leo Shestakov (10th), Alex Thompson (10th)

We utilized network programming to create a server that acts as a conductor and instructs separate clients to play separate instruments as part of a composition/orchestra. The "instruments" are individual drum samples that form a beat. There are 5 (max) possible instruments/clients.

We originally intended to be able to split a single audio (or midi) file, but determined that it was an unlikely goal. Instead, we are using files uploaded to JukeHost to play individually uploaded mp3 files (of separate instruments) through the default browser.

Each client will open up a different file to play.

There are no required libraries for this project.

### Techniques Implemented

Allocating memory, working with files, working with processes, networking

### How to use our project (User Interface)

First, create the server on one system. These are the commands:
```
make
make select
./server
```

Then, on each client system, compile in this order:
```
make
make select
./client
```
Immediately after compiling, your client's link will be opened in the default browser (on Ubuntu machines).
