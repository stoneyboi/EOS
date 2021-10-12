#include <curses.h>
#include <term.h>
#include <unistd.h>

void move_cursor(int row, int col) {
    // get control characters for cursor positioning (cup)
    char *cap = tigetstr("cup");
    char *cmd = tparm(cap, row, col); // Insert row/column to the control chars
    putp(cmd);                        // Send the control chars to the terminal
    fflush(stdout);                   // flush the buffer for immediate effect
}

void initializeBoard(int row, int col, int startR, int startC) {
// creates border and divides screen evenly 1 2 is default
	//starts at top left corner
    	//populate with border
    	printf("^"); //corner piece at start
    	for(i = 0; i < row; i += 2){
    		move_cursor(i, startC);
    		printf("|"); //every other left edge
    	}
    	move_cursor(row, 0); //bottom corner
    	printf("<"); //bottom corner
    	move_cursor(0, col);
    	printf("^"); // top right corner
    	for(i = 0; i < row; i += 2){
    	move_cursor(i, col);
    	printf("|"); //right edge every other
    	}
    	move_cursor(
    	
    	
    	


int main(int row, int col, int dirRow, int dirCol) {
    	setupterm(NULL, fileno(stdout), NULL);
	// Get the screen size
   	int rows = tigetnum("lines");
    	int cols = tigetnum("cols");
    	int EachNumR = rows / row; //integer math rounds down
    	int EachNumC = cols / col; //integer math rounds down
    	// Each cell (row * col for NumCells, will be EachNumR wide and EachNumC tall
    	
    	putp(tigetstr("clear"));  // Clear screen
    	putp(tigetstr("smcup"));  // Enter cursor addressing mode
    	int startR = 0;
    	int startC = 0;
    	for(i = 0; i < row; i++){
    	for(j = 0; j < col; j++){
    	//create border
    	move_cursor(startR, startC);// starting point
    	initalizeBoard(EachNumR, EachNumC, startR, startC);
    	startC += EachNumC; // increments start position for Col
    	} //end C for loop
    	startR += EachNumR; // increments start position for row
    	}//end R for loop
    	
    	//body of function
    	putp(tigetstr("rmcup"));  // Exit cursor addressing mode
