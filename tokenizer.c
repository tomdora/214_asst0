#include "tokenizer.h"

Node * head = NULL;
int currentLoc = 0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////


//Function to create a head node. Checks to see if the entire string is one single token first.
int createHeadNode(char * input, char * inputType, int i){
	//printf("No head.\n");
	
	//createHeadNode checks to see if this is the only token
	//if true, it creates a head node that is also the last node
	if(currentLoc == strlen(input) - 1){
		//printf("Head is null and end of string. currentLoc = %d, strlen = %ld\n", currentLoc, strlen(input));
		
		head = (Node*)malloc(sizeof(Node));
		head-> data = (char*)malloc(currentLoc-i+1);
		
		strncpy(head->data, input + i, currentLoc-i+1);
		head->type = inputType;
		
		i = strlen(input);
	}
	
	//Otherwise, it creates the head node and continues the program
	else{
		head = (Node*)malloc(sizeof(Node));
		head->data = (char*)malloc(currentLoc-i);
		
		strncpy(head->data, input + i, currentLoc-i);
		head->type = inputType;
		
		i = currentLoc;
	}
	
	return i;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


//Function to create the last node.
int createLastNode(char * input, char * inputType, int i){
	//Because createHeadNode already has code to handle being the only token
	//createLastNode will check if the head is null and send the code over there.
	if(head == NULL){
		i = createHeadNode(input, inputType, i);
	} 
	
	//Otherwise, we already have a head node and can fulfill the code here.
	else{
		//printf("Last node.\n");
		
		Node * new = (Node*)malloc(sizeof(Node));
		new->data = (char*)malloc(currentLoc-i+1);
		
		Node * l = head;
		while(l->next != NULL){
			l = l->next;
		}
		
		l->next = new;
		
		strncpy(new->data, input + i, currentLoc-i+1);
		new->type = inputType;
		
		i = strlen(input);
	}
	
	return i;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


//Function to create a new node. Checks to see if the head exists first.
int createNewNode(char * input, char * inputType, int i){
	//printf("i: %d, currentLoc: %d\n", i, currentLoc);
	
	//If no head exists, function passes to the function to create a head.
	if(head == NULL){
		printf("Head is null.\n");
		i = createHeadNode(input, inputType, i);
	} 
	
	//Else if a head exists, the code will run as normal to create a new node.
	else{
		Node * new = (Node*)malloc(sizeof(Node));
		new->data = (char*)malloc(currentLoc-i);
		
		Node * l = head;
		while(l->next != NULL){
			l = l->next;
		}
		
		l->next = new;
		
		strncpy(new->data, input + i, currentLoc-i);
		new->type = inputType;
		
		i = currentLoc;
	}
	
	return i;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


//Function for creating a word. Due to the greedy nature of the algorithm, only needs a space or punctuation to terminate rather than any numbers.
int isWord(char * input, int i){
	//printf("word\n");
	while(currentLoc < strlen(input)){
		printf("currentLoc: %d\n", currentLoc);
		
		//Check to see if the character is alphanumeric. 
		if(!isalpha(input[currentLoc]) && !isdigit(input[currentLoc])){
			i = createNewNode(input, "word", i);
			
			break;
		}
		
		//Check to see if we're at the end of the string, since the function won't automatically send the rest of the string.
		else if(currentLoc == strlen(input) - 1){
			//printf("End of string.\n");
			
			i = createLastNode(input, "word", i);
			
			break;
		}
		
		currentLoc++;
	}
	//printf("Returning\n");
	return i;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


//Function to test for punctuation.
//Also tests to make sure it doesn't overflow the length of the string.
int isPunctuation(char * input, int i){
	if(currentLoc < strlen(input) && input[i] == '+' && input[i+1] == '='){		//checks for plusequals
		
		currentLoc += 2;
		i = createNewNode(input, "plusequals", i);
	} 
	
	else{
		currentLoc += 1;
		i = createNewNode(input, "punct", i);
	}
	
	return i;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


int isFloat(char * input, int i){
	while(currentLoc < strlen(input)){
		
	}
	
	return i;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


//Function for a known hex token. Goes until it finds a non-hex character.
int isHex(char * input, int i){
	printf("Hex.\n");
	while(currentLoc < strlen(input)){
		//printf("i: %d, currentLoc: %d\n", i, currentLoc);
		
		//Checks for a non-hex character
		if(!isxdigit(input[currentLoc])){
			printf("Non-hex found\n");
			
			i = createNewNode(input, "hex", i);
			
			break;
		}
		
		//Check to see if we're at the end of the string, since the function won't automatically send the rest of the string.
		else if(currentLoc == strlen(input) - 1){
			printf("End of string.\n");
			
			i = createLastNode(input, "hex", i);
			
			break;
		}
		
		currentLoc++;
	}
	
	return i;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


int isNumber(char * input, int i){
	printf("Number.\n");
	while(currentLoc < strlen(input)){
		if(input[currentLoc] = '.' && isdigit(input[currentLoc + 1])){
			printf("Float.");
			
			i = isFloat(input, i);
			
			break;
		}
		
		currentLoc++;
	}
	
	return i;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


//Function to determine what type of token is required and sends it to the proper function
int tokenType(char * input, int i){
	if(isspace(input[i])){
		i++;
		currentLoc++;
	} 
	else if(isalpha(input[i])){
		i = isWord(input, i);
	} 
	else if(ispunct(input[i])){
		i = isPunctuation(input, i);
	} 
	
	else if(input[i] == '0' && input[i+1] == 'x' || 'X'){
		currentLoc += 2;
		i = isHex(input, i);
	}else if(isdigit(input[i])){
		i = isNumber(input, i);
	}
	
	return i;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


//Function to print the entire linked list
void printList(){
	if(head == NULL){ printf("Head is null.\n"); }
	Node * l = head;
	while(l != NULL){
		printf("%s \"%s\"\n", l->type, l->data);
		
		l = l->next;
	}
}





/////////////////////////////////////////////////////////////////////////////////////////////////////////





//Main function
int main(int argc, char * argv[]){
	//Node * head = NULL;
	
	//Check for exactly two arguments; one is not enough and more is too many
	if(argc == 2){
		int i = 0;
		
		//Tokenize the string input
		while(i < strlen(argv[1])){
			//printf("i: %d, currentLoc: %d\n", i, currentLoc);
			
			i = tokenType(argv[1], i);
		}
		
		printList();
		
	} else if(argc <= 1){
		printf("There are no strings to tokenize.\n");
	} else if(argc > 2){
		printf("There are too many strings to tokenize.\n");
	}
	
	return EXIT_SUCCESS;
}
