#include <stdio.h>
#include <string.h>
#include <ctype.h> 
#include <stdbool.h>
#include <time.h>


//Initializing variables for the moment and keeping them empty
int init_ship();
int teardown();
struct mapspot userInput();


// Struct to hold letter and number
struct mapspot {
char letter;
int number;
};

//Returns empty for now
int init_ship(){
    bool carrier = false;
	while(carrier == false){
        nRow = rand()%10;
         col = rand()%10; 
        if(nRow+1 < 10 && nRow-1 >= 0){ 
            if((board[nRow][col] = '') && 
                (board[nRow+1][col] = '')){
                    board[nRow][col] = 'B';
                    board[nRow+1][col] = 'B';
                    carrier = true; 
            }
            else if((board[nRow][col] == '-') && 
                (board[nRow-1][col] == '-')){
                    board[nRow][col] = 'B'; 
                    board[nRow-1][col] = 'B';
                    carrier = true;
            }
        }
	}
    bool submarine = false;
	while (submarine == false){
		nRow = rand()%10;
		col = rand()%10;
		if((nRow+1 < 10 && nRow+2 < 10) && 
            (nRow-1 >= 0 && nRow-2 >= 0) && 
            (col+1 < 10 && col+2 < 10) && 
            (col-1 >= 0 && col-2 >= 0)){
            if((board[nRow][col] == '') && 
                (board[nRow][col+1] == '') && 
                (board[nRow][col+2] == '')){
                    board[nRow][col] = 'E';
                    board[nRow][col+1] = 'E';
                    board[nRow][col+2] = 'E';
                    submarine = true;
            }
            else if((board[nRow][col] == '') && 
                (board[nRow][col-1] == '') && 
                (board[nRow][col-2] == '')){
                    board[nRow][col] = 'E';
                    board[nRow][col-1] = 'E';
                    board[nRow][col-2] = 'E';
                    submarine = true;
            }
            else if((board[nRow][col] == '') && 
                (board[nRow+1][col] == '') && 
                (board[nRow+2][col] == '')){
                    board[nRow][col] = 'E';
                    board[nRow+1][col] = 'E';
                    board[nRow+2][col] = 'E';
                    submarine = true;
            }
            else if((board[nRow][col] == '') &&
                (board[nRow-1][col] == '') &&
                (board[nRow-2][col] == '')){
                    board[nRow][col] = 'E';
                    board[nRow-1][col] = 'E';
                    board[nRow-2][col] = 'E';
                    submarine = true;
            }
        }
	}
    bool aircraftcarrier = false;
	while (aircraftcarrier == false){
		nRow = rand()%10;
		col = rand()%10;
		if((nRow+1 < 10 && nRow+2 < 10) &&
            (nRow-1 >= 0 && nRow-2 >= 0) && 
            (col+1 < 10 && col+2 < 10) && 
            (col-1 >= 0 && col-2 >= 0)){
            if((board[nRow][col] == '') && 
                (board[nRow][col+1] == '') && 
                (board[nRow][col+2] == '')){
                    board[nRow][col] = 'C';
                    board[nRow][col+1] = 'C';
                    board[nRow][col+2] = 'C';
                    aircraftcarrier = true;
            }
            else if((board[nRow][col] == '') && 
                (board[nRow][col-1] == '') && 
                (board[nRow][col-2] == '')){
                    board[nRow][col] = 'C';
                    board[nRow][col-1] = 'C';
                    board[nRow][col-2] = 'C';
                    aircraftcarrier = true;
            }
            else if((board[nRow][col] =='') && 
                (board[nRow+1][col] == '') && 
                (board[nRow+2][col] == '')){
                    board[nRow][col] = 'C';
                    board[nRow+1][col] = 'C';
                    board[nRow+2][col] = 'C';
                    aircraftcarrier = true;
            }
            else if((board[nRow][col] == '') && 
                (board[nRow-1][col] == '') && 
                (board[nRow-2][col] == '')){
                    board[nRow][col] = 'C';
                    board[nRow-1][col] = 'C';
                    board[nRow-2][col] = 'C';
                    aircraftcarrier = true;
            }
        }
	}
    bool battleship = false;
	while (battleship == false){
		nRow = rand()%10;
		col = rand()%10;
		if((nRow+1 < 10 && nRow+2 < 9 && nRow+3 < 9) &&
            (nRow-1 >= 0 && nRow-2 >= 0 && nRow-3 >= 0) && 
			(col+1 < 10 && col+2 < 9 && col+3 < 10) && 
            (col-1 >= 0 && col-2 >= 0 && col-3 >= 0)){
            if((board[nRow][col] == '') && 
                 (board[nRow+1][col] == '') &&
                 (board[nRow+2][col] == '') &&
                 (board[nRow+3][col] == '')){
                    board[nRow][col] = 'A';
                    board[nRow+1][col] = 'A';
                    board[nRow+2][col] = 'A';
                    board[nRow+3][col] = 'A';
                    battleship = true;
            }
            else if((board[nRow][col] == '') &&
                 (board[nRow-1][col] == '') &&
                 (board[nRow-2][col] == '') &&
                 (board[nRow-3][col] == '')){
                    board[nRow][col] = 'A';
                    board[nRow-1][col] = 'A';
                    board[nRow-2][col] = 'A';
                    board[nRow-3][col] = 'A';
                    battleship = true;
            }
            else if((board[nRow][col] == '') &&
                 (board[nRow][col+1] == '') &&
                 (board[nRow][col+2] == '') &&
                 (board[nRow][col+3] == '')){
                    board[nRow][col] = 'A';
                    board[nRow][col+1] = 'A';
                    board[nRow][col+2] = 'A';
                    board[nRow][col+3] = 'A';
                    battleship = true;
            }
            else if((board[nRow][col] == '') &&
                 (board[nRow][col-1] == '') &&
                 (board[nRow][col-2] == '') &&
                 (board[nRow][col-3] == '')){
                    board[nRow][col] = 'A';
                    board[nRow][col-1] = 'A';
                    board[nRow][col-2] = 'A';
                    board[nRow][col-3] = 'A';
                    battleship = true;
            }
        }
	}
    bool destroyer = false;
	while (destroyer == false){
		nRow = rand()%10;
		col = rand()%10;
		if((nRow+1 < 10 && nRow+2 < 10 && nRow+3 < 10 && nRow+4 < 0) &&
            (nRow-1 >= 0 && nRow-2 >= 0 && nRow-3 >= 0 && nRow-4 >= 0) && 
			(col+1 < 10 && col+2 < 10 && col+3 < 10 && col+4 < 10) &&
            (col-1 >= 0 && col-2 >= 0 && col-3 >= 0 && col-4 >= 0)){
            if((board[nRow][col] == '') &&
               (board[nRow+1][col] == '') &&
               (board[nRow+2][col] == '') &&
               (board[nRow+3][col] == '') &&
               (board[nRow+4][col] == '')){
                    board[nRow][col] = 'J';
                    board[nRow+1][col] = 'J';
                    board[nRow+2][col] = 'J';
                    board[nRow+3][col] = 'J';
                    board[nRow+4][col] = 'J';
                    destroyer = true;
            }
            else if((board[nRow][col] == '') &&
                 (board[nRow-1][col] == '') &&
                 (board[nRow-2][col] == '') &&
                 (board[nRow-3][col] == '') &&
                 (board[nRow-4][col] == '')){
                    board[nRow][col] = 'J';
                    board[nRow-1][col] = 'J';
                    board[nRow-2][col] = 'J';
                    board[nRow-3][col] = 'J';
                    board[nRow-4][col] = 'J';
                    destroyer = true;
            }
            else if((board[nRow][col] == '') && 
                (board[nRow][col+1] == '') && 
                (board[nRow][col+2] == '') && 
                (board[nRow][col+3] == '') && 
                (board[nRow][col+4] == '')){
                    board[nRow][col] = 'J';
                    board[nRow][col+1] = 'J';
                    board[nRow][col+2] = 'J';
                    board[nRow][col+3] = 'J';
                    board[nRow][col+4] = 'J';
                    destroyer = true;
            }
            else if((board[nRow][col] == '') && 
                (board[nRow][col-1] == '') && 
                (board[nRow][col-2] == '') && 
                (board[nRow][col-3] == '') && 
                (board[nRow][col-4] == '')){
                    board[nRow][col] = 'J';
                    board[nRow][col-1] = 'J';
                    board[nRow][col-2] = 'J';
                    board[nRow][col-3] = 'J';
                    board[nRow][col-4] = 'J';
                    destroyer = true;
            }
        }
	}
    return board;
    }
return 0;

  
//Traverses through the text file
int teardown(){
    int i;
	for(i = 0; i < SIZE; i++)
		free(board[i]);
	free(board);
    int fd = ("log.txt", O_READONLY | O_CREAT);
    printf("fd = %d/n", teardown)
    

void traverse(Node* teardown) 
{ 
    if (teardown == NULL) 
       return; 
  
    traverse(teardown->next); 
}
return 0;

 }
//Grabs user input to pick coordinates when targeting ships
struct mapspot userInput(){
    char l;
    int n;
    // Grab letter
    printf("\nEnter a letter from A to J: ");
scanf(" %c", &l);
    
// Make sure it's from A to J
while ((toupper(l) < 'A') || (toupper(l) > 'J')){
printf("\nEnter a letter from A to J: ");
scanf(" %c", &l);
}
    
    // Grab number
    printf("\nEnter a number from 0 to 9: ");
scanf(" %i", &n);

// Make sure it's from 0 to 9
while ((n < 0) || (n > 9)) {
printf("\nEnter a number from 0 to 9: ");
scanf(" %i", &n);
}

struct mapspot selected;
selected.letter = toupper(l);
selected.number = n;
return selected;
}

int updateWorld(struct mapspot ms){
    if (ms.number % 2 == 0) {
        printf("\nIt's a hit!");
        return 1;
   }
   else printf("\nMissed!");
   return 0;
   else printf("\nGame Over!")
   return 1;
}
  
int stateofWorld(int result){
    if (result)
        printf("\nThe spot was hit!");
    else printf("\nThe spot wasn't hit.");
}

//Initializing the main method while calling empty strings. 
int main() {
init_ship();
int flag = 0;
int result;
struct mapspot ms;

while (!flag) {
        ms = userInput();
        result = updateWorld(ms);
        stateofWorld(result);
        if (result) {
            flag = 1;
        }
}

teardown();


//main function

 
    struct boardGame *boardPtr = NULL;

    struct coordinatesFlag *coordsAndFlagPtr = (struct coordinateswithflag *)malloc(sizeof(struct coordinatesFlag));

    
    bool gameFlag = 1;


    char *stateofWorldStr = (char *)malloc(sizeof(char) * 10);

    boardPtr = Initialization();

    DisplayWorld(boardPtr, stateofWorldStr);

    while (Flag)
    {
        coordsAndFlagPtr = AcceptInput(coordsAndFlagPtr);

        if (coordsAndFlagPtr->flag == 0)
        {
            Flag = 0;
        }
        else
        {
            stateofWorldStr = updateWorld(coordsAndFlagPtr, boardPtr, stateofWorldStr); // get string
            DisplayPlayersView(boardPtr, stateofWorldStr);
        }

    }

    Termination(coordsAndFlagPtr, stateofWorldStr, boardPtr);

    return 0;

struct boardSpace
{
    bool shotsFired;
    char stationed;

};

struct coordinatesWflag
{
    unsigned short int number;
    char letter;
    bool flag;
};

//displays world
void display_stateofworld(char* state, char** board){
	int x, y;
    printf("*\n %s *\n", state);
	printf("  0 1 2 3 4 5 6 7 8 9\n");
	for (x = 0; x < SIZE; x++){
        printf("%c ", 65+x);
		for (y = 0; y < SIZE; y++){
			printf("%c ", board[x][y]); 
		}
		printf("\n");
	}
}

//prints the board game
void DisplayWorld(struct board *bdPtr, char * outputStr)
{
    int x, y;
    int k = 65; // ASCII value for character 'A'

    printf("Placing boats:\n");
    printf("(This is not visible to the player)\n");

    printf("   1   2   3   4   5   6   7   8   9   10\n");

    for (y = 0; y < BOARD_HEIGHT; y++)
    {
        printf("%c ", z);
        for (x = 0; x < BOARD_WIDTH; x++)
        {
            if ((bdPtr + y*BOARD_HEIGHT + x)->shotFired == 0)
            {
                printf("[%c] ", (bdPtr + y * BOARD_HEIGHT + x)->occupiedBy);
            }
            else if ((bdPtr + y*BOARD_HEIGHT + x)->shotFired == 1)
            {
                if ((bdPtr + y*BOARD_HEIGHT + x)->occupiedBy == ' ')
                {
                    printf("[ ] ");
                }
                else
                {
                    printf("[%c] ", (bdPtr + y * BOARD_HEIGHT + x)->occupiedBy);
                }
            }
        }
        printf("\n");
        z++;
    }
}





int server_fd, new_socket, valread; 
    struct socktraverser_in traverseress; 
    int opt = 1; 
    int traverserlen = sizeof(traverseress); 
    char buffer[1024] = {0}; 
    char *hello = "Hello from server"; 
       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEtraverseR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsock"); 
        exit(EXIT_FAILURE); 
    } 
    traverseress.sin_family = AF_INET; 
    traverseress.sin_traverser.s_traverser = INtraverseR_ANY; 
    traverseress.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct socktraverser *)&traverseress,  
                                 sizeof(traverseress))<0) 
    { 
        perror("failed binding"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listensocket"); 
        exit(EXIT_FAILURE); 
    } 
    if ((new_socket = accept(server_fd, (struct socktraverser *)&traverseress,  
                       (socklen_t*)&traverserlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 
    valread = read( new_socket , buffer, 1024); 
    printf("%s\n",buffer ); 
    send(new_socket , hello , strlen(hello) , 0 ); 
    printf("Hello message sent\n"); 
    return 0; 
} 

