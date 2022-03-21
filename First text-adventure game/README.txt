You can compile the code by running the make command in the terminal, then run the code with the command ./adventure

I used the recommended struct Room with some more variable that allows me to keep track of everything easier. I created all the room 
(called board) by calling malloc(sizeof(struct Room) * 9). Then I loop over the board to assign the data and its corresponding pointer 
to every direction. I would access the point at (i, j) by adding 3 * i + j to the pointer of the first struct created by malloc.

In my main function, I ran an a while loop based on the remainging clue tries. I would get the user input with the function getline().
I would then remove the "\n" at the end then separate the input into 2 chunks, the command and name if required using the processCommand()
function. In the processCommand() function, I used strtok to separate it by the " " as the delimiter. Every loop, the user would be 
prompt for a command and it would only accept the the correct format, others format would prompt the user to enter it again.

I can track the avatar current location with an int where it location would be (board + avatar) using offset. Function comments is written
in the header files.