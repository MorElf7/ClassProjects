I use the recommended struct for my implementation. I created the board by calling malloc(ROW*COL * sizeof(struct Grid)). Then I loop over the
board to assign the data and its corresponding pointer to every direction. I would access the point at (i, j) by adding COL * i + j to the 
pointer of the first struct created by malloc. The game initial position would be randomized every time. I would keep track of the position 
of the player and the AI at every stage. I had a function hasMove which would check the adjacent octagon for any possible move from the given
position, which I would use to keep track of the state of the game. 

For the AI moves, I would run a loop in every direction until I hit a '.' or 'P' or NULL pointer. At each iteration, I would be 
finding the max point and stored it. After the loop is over, I would update the AI position by using a reference as well as updating the data
in the starting and end point of every move. For player move, my function playerMove would take a string and the reference to the current
position of the player. I use strtok to break the command string into two part (the direction and the step). I will then loop over in that 
direction step times. At every iteration, I would check if the current position is NULL, '.', or 'A'; if so, I would break out of the loop.

For both my AIMove and playerMove functions, they would return the data of its landing octagon if it is valid as a char or a '0' for any invalid
move. I would then use strncat to append the return char to my char* with a '+' in front that is keeping track of the point for every move. When
the game ends, I would just print that string for the player and AI respectively. I also had a function sumOf which would calculate the sum with
the parameter is the string I mentioned aboved. I would ignore the '+' and convert the number char to an int. 

In my main function, I would run an infinite loop until the game ended. For every loop, I would use the function printBoard to print the board.
Then I would check if the game is still continuing. If it doesn't I would print the result and break out of the loop and exit the program.
If it is still continuing, I would check if the player still have a move; if so, I would ask for a move. My user input accept any input as long
as it is in the format of 2 words no matter the casing. If the user enter "direction step" then the move would be execute, if not they would 
print a message saying invalid move and ask for another one. After the player has made their move, I would check for the AI available moves.
If either the AI or player do not have any moves left, I would skip their turn and print a message saying so.   
