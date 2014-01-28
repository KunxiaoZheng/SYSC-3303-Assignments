To run the program, first open up the partA.c using a terminal. Inside the terminal, first compile the code using makefile, then 
type in "./partA 5000" to start the program. The 5000 is the socket number and it can be modified. Now starts up a new terminal, 
this one first compiles the client_udp.c using the makefile and then type in "./client_udp localhost 5000" to start the whole program. 
The 5000 in this file is the socket number and it have to be the same as the number in the partA.c. 
When the program starts, the 
client_udp.c will send datagrams to the partA.c, client_udp.c's terminal will display which number is being sent and the partA.c's 
terminal  will display which number is being received.
