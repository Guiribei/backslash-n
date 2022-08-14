# backslash-n
A 42 project meant to Get the Next Line '\n'

The aim of this project was to allow me to build my own mechanism to access the next line in a certain file through determined file descriptor. So I’ve programmed a function that returns a line read from a fd. Through the understanding of a static variable concept, it was possible to make a buffer that would keep the information read from previous call of the function to a subsequent call. This also allowed the function to read the entire file (when called multiple times until EOF) with different buffer sizes.


The main lessons learned from this project were about the use of static variables and the understanding of mechanisms to find and avoid memory leaks (yes, we met valgrind for the first time here, now I guess we are almost close friends).
