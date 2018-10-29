# Corewar

VM :

1 Parsing

2 Virtual Arena



ARCHITECTURE

Each player loaded in the virtual machine becomes a process.

{} what info to store in struct

{} how and where to store a player?

{} how to access all of the player's attributes?

{} how and where to store the memory?

{} how to represent the memory + the value at each memory address?

{} declare memory macro MEM_SIZE



1 - PARSING

{} parse entire file with read()

{} more than 1 file is ok

{} extract player's name, comment, program

{} where to store information from -dump, -n (and other options, if necessary)

{} if the program size, name length, or comment are different to header -> error! 
    Champ Errors

{} error: not a .cor file

{} error: "magic number" doesn't match header macros (4 bytes)

{} error: process name doesn't match header macros (120 bytes + 1 (for NULL termination))

{} error: process name contains irregular chars

{} error: program size doesn't match header macros (4 bytes – Zaz's is uncompliant, but it's ok to mimic his)

{} error: comment size doesn't match header macros (2000 bytes)

{} error: no name/comment; {} ok: blank name/comment

{} error: program itself

{} the header file has macro values. 


2 - VIRTUAL ARENA

{} malloc or statically allocate?
    If you malloc, when you go off the end you will segfault and be aware that it happened

{} create a separate function which determines what is a safe address to go to...
   That way you never return an unsafe number and go outside the memory.



ASM :

