/* Project 4 template
 * Please check the comments and hints, and fill the codes.
 * You only need to write your code in this file, and you do not 
 * need to write the server and client sides in two files. 
 *
 * You also need to modify the code from project 3 accordingly to 
 * make it adapted to the network communication. 
 * */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define SIZE 10
#define backlog 10
#define MAXDATASIZE 100
#define MAXBUFLEN 100

// you can change the struct as you like
struct move{
    char letter;
    int number;
    char state[20];
    char ship[20];
    struct move *next;
};

char ipAddress[200], port[200];
int ourSocket,listensocket, new_fd,sockfd,numbytes;
char buf[MAXDATASIZE];

void generateShip(char** board, int size, char letter) {
	int noGood = 1;
	int orientation , nRow, col;
    int curRow, curCol;
	while (noGood) {
		orientation = random() %2;
		if (orientation == 0) { // Horizontal
			nRow = random() % 10;
			col = random() % (10 - size);
		} else {
			nRow = random() % (10 - size);
			col = random() % 10;
		}
		int noObstructions = 1;
		for (int i=0;i<size;i++) {
			curRow = nRow, curCol = col;
			if (orientation == 0) { // Horizontal
				curCol += i;
			} else {
				curRow += i;
			}
			if (board[curRow][curCol] != '-') 
                noObstructions = 0;	
		}
		if (noObstructions == 0) 
            continue;
		noGood = 0;
	}
	printf ("Ship %c at %c%d-%c%d, orientation = %s\n",letter, nRow+65, col,curRow+65, curCol, orientation==0?"horizontal" : "vertical");
	for (int i=0;i<size;i++) {
		curCol = col, curRow = nRow;
		if (orientation == 0) { // Horizontal
			curCol += i;
		} else {
			curRow += i;
		}
		board[curRow][curCol] = letter;
	}
}
void* get_in_addr(struct sockaddr *sa)
{
 if (sa->sa_family == AF_INET) {
 return &(((struct sockaddr_in*)sa)->sin_addr);
 }
 return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void sigchld_handler(int s)
{
	(void)s;

	// In case errno is overwritten, save errno
	int saved_errno = errno;

	while(waitpid(-1, NULL, WNOHANG) > 0);

	errno = saved_errno;
}


void createlistensocket() {
    /*write the code here, you can refer to the lab9 handout */
	
	struct addrinfo hints, *servinfo, *p;
    // Address Information
	struct sockaddr_storage their_addr;
	socklen_t sin_size;
	struct sigaction sa;
	int yes=1;
	char s[INET6_ADDRSTRLEN];
	int rv;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if ((rv = getaddrinfo(NULL, port, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
	}

	// Loop All the Results
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) {
			perror("Socket");
			continue;
		}

		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
				sizeof(int)) == -1) {
			perror("setsockopt");
			exit(1);
		}
        // Then Bind
		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("Bind");
			continue;
		}

		break;
	}

	freeaddrinfo(servinfo);

	if (p == NULL)  {
		fprintf(stderr, "Error: Cannot bind\n");
		exit(1);
	}

	if (listen(sockfd, backlog) == -1) {
		perror("Listen");
		exit(1);
	}
	
    // Reap Dead Processes
	sa.sa_handler = sigchld_handler; 
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGCHLD, &sa, NULL) == -1) {
		perror("Signal Action");
		exit(1);
	}

	printf("server: waiting for connections...\n");

    // Loop for Accept
	while(1) {  
		sin_size = sizeof their_addr;
		new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
		if (new_fd == -1) {
			perror("accept");
			continue;
		}

		inet_ntop(their_addr.ss_family,
			get_in_addr((struct sockaddr *)&their_addr),
			s, sizeof s);
		printf("server: got connection from %s\n", s);
		break;

	}
}


void createSendingSocket() {
	/*write the code here, you can refer to the lab9 handout */
    struct addrinfo hints, *servinfo, *p;

    // Address Information
	struct sockaddr_storage their_addr;
	socklen_t sin_size;
	struct sigaction sa;
	int yes=1;
	char s[INET6_ADDRSTRLEN];
	int rv;
	printf("Here 1");
	
    // set the bytes for hints to 0
	memset(&hints, 0, sizeof hints);
    // IPV4 & IPV6
	hints.ai_family = AF_UNSPEC;
    // TCP & IP
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; 
	printf("Here 2");
	// Gets address, then returns pointer to linked list
	if ((rv = getaddrinfo("127.0.0.1", port, &hints, &servinfo)) != 0) {
	fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
	exit(1);
	}
	printf("Here 3");
	
    // Create socket
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((listensocket = socket(p->ai_family, p->ai_socktype,
		p->ai_protocol)) == -1) {
		perror("server: socket");
		continue;
	}
	printf("Here 4");
	
    // Connect Socket
	if(connect(listensocket,p->ai_addr,p->ai_addrlen) == -1) {
        close(listensocket);
        printf("connection success for client\n");continue;
        }
	break;
    }
	printf("Here 5");

	freeaddrinfo(servinfo);

}



char** initialization(){
	if (ipAddress[0] == 0){
        printf("create listen socket");
        /*add function call of create listen socket*/
		createlistensocket();
    		ourSocket = new_fd;
    }
	else{
        printf("create sending socket");
        /*add function call of create sending socket*/
		createSendingSocket();
		ourSocket = listensocket;   
    }

	int i, j;
	char **board = (char**)malloc(sizeof(char*)*SIZE);
	for (i = 0; i < SIZE; i++){
		board[i] = (char*)malloc(sizeof(char)*SIZE);
	}
	for(i = 0; i < SIZE; i++){
		for(j = 0; j < SIZE; j++){
			board[i][j] = '-';
		}
	}

	generateShip(board, 2,'D');
	generateShip(board, 3,'S');
	generateShip(board, 3,'C');
	generateShip(board, 4,'B');
	generateShip(board, 5,'R');
    return board;
}



void insert_move(struct move **head, struct move **tail,struct move *temp){
     if (*head == NULL){
        /* List is currently empty. */
        *head = *tail = temp;
    }
    else{
        (*tail)->next = temp;
        *tail = (*tail)->next;
    }
}

void update_state(char* state, char ** board, struct move** head,struct move** tail, struct move* temp){
	int nRow, i, j;
    char letter = temp->letter;
    int col = temp->number;
    nRow = letter % 65;
    if(board[nRow][col] == '-'){
        strcpy(state, "MISS");
        strcpy(temp->state, "MISS");
        strcpy(temp->ship, "  ");
    }
    else{
        strcpy(state, "HIT");
        strcpy(temp->state, "HIT!");
        switch (board[nRow][col]){
            case 'C':  strcpy(temp->ship, "Crusier"); break;
            case 'R':  strcpy(temp->ship, "Carrier"); break;
            case 'B':  strcpy(temp->ship, "Battleship"); break;
            case 'S':  strcpy(temp->ship, "Submarine"); break;
            case 'D':  strcpy(temp->ship, "Destroyer"); break;
        }
        board[nRow][col]='X';
    }

    insert_move(head,tail,temp);
    int counter = 0;
    for(i=0; i < SIZE; i++){
        for(j=0; j < SIZE; j++){
            if(board[i][j] == '-' || board[i][j] == 'X')
                counter += 1;
        }
    }
    if(counter == SIZE * SIZE)
        strcpy(state, "GAME OVER!");
}

struct move* accept_input(){
    char letter;
    int number;
    bool flag = true;
    do{
        printf("Enter a letter A-J and number 0-9 ex. B4 - enter Z0 to end\n");
        int size = scanf(" %c%d", &letter, &number);
        if(size != 2){
            printf("INVALID INPUT\n");
            continue;
        }
        letter = toupper(letter);
        if(letter == 'Z' && number == 0)
            break;
        if (letter < 65 || letter > 74)
            printf("INVALID INPUT\n");
        else if (number <0 || number >9)
            printf("INVALID INPUT\n");
        else
            flag = false;
	}while(flag);

     struct move *temp;
     temp = (struct move *)malloc(sizeof(struct move));
     temp->letter = letter;
     temp->number = number;
    return temp;
}

void display_state(char* state, char** board){
	int i, j;
    printf("**** %s ****\n\n", state);

	printf(" 0 1 2 3 4 5 6 7 8 9\n");
	for (i = 0; i < SIZE; i++){
        printf("%c ", 65+i);
		for (j = 0; j < SIZE; j++){
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
}

int teardown(char ** board,struct move* head){
	int i;
    struct move* temp;
	for(i = 0; i < SIZE; i++)
		free(board[i]);
	free(board);
	FILE *fptr;

    fptr = fopen("log.txt", "w");
     if (fptr == NULL)
     {
         exit(-1);
     }

    
     if (head==NULL){
         printf("The list is empty");
     }
     else{
         while (head != NULL){
            fprintf(fptr, "Fired at %c%d %s %s \n", head->letter, head->number, head->state, head->ship);
            temp = head;
            head = head->next;
            free(temp);
         }
     }
     fclose(fptr);
	return 0;
}


int main(int argc, char **argv) {
	if (argc != 3 && argc != 2) { printf ("usage: battleship [ipaddress] port\n"); return 1; }
	if (argc == 3) {
        // if there are two ccompiler line arguments, where
        // first is the ipaddress and 
        // second is the port, then we initialize 
        // the client side in initialization() function
		strcpy(ipAddress,argv[1]);
		strcpy(port,argv[2]);

	}
	else {
        // if there is only one ccompiler line argument, 
        // then we initialize the server side in initialization
        // function
		memset(ipAddress,0,200);
		strcpy(port,argv[1]);
	}

	srand(time(NULL));
	char** board;
    char state[] = "GAME START";
    char flag[] = "GAME OVER!";

    struct move *head, *tail, *ourMove;
    head = tail = NULL;
    
    /*modify the initialization function */
	board = initialization();

	do{
		display_state(state, board);
		ourMove = accept_input();

        /*add code to store our moves (letter, number, and result) into linked list*/
        tail->next=ourMove;
		tail=tail->next;

        /*add code below to send our move to the other player*/
	    send(ourSocket, (char *)ourMove , sizeof(struct move) , 0 );

        /*add code below to receive theirMove from the other player */
		if ((numbytes = recv(ourSocket, buf, MAXDATASIZE-1, 0)) == -1) {
		    perror("recv1");
		    exit(1);
		}
        
        
        /* kept having pointer error with struct, update_state, and send */
        
        // struct move theirMove;
        
        /*modify the update_state function to check theirMove is HIT or MISS
         * and send the state back to the other player */
		
        // update_state(state,board,head,tail,theirMove);
		// send(ourSocket, state , strlen(state) , 0 );        
        
        /* receive the result of our move */
              
		if ((numbytes = recv(ourSocket, buf, MAXDATASIZE-1, 0)) == -1) {
		perror("recv2");
		exit(1);
		}
		
	} while(strcmp(state, flag));
	close(sockfd);
	close(new_fd);
	teardown(board, head);
	return 0;
}
