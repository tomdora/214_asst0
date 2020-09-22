#include "tokenizer.h"

Node * head = NULL;
int startLoc = 0;			//starting location
int currentLoc = 0;			//current iteration location

/////////////////////////////////////////////////////////////////////////////////////////////////////////


//Function to create a head node. Checks to see if the entire string is one single token first.
void createHeadNode(char * input, char * inputType){
	//printf("No head.\n");
	
	head = (Node*)malloc(sizeof(Node));
	head->data = (char*)malloc(currentLoc-startLoc+1);
	
	strncpy(head->data, input + startLoc, currentLoc-startLoc+1);
	head->type = inputType;
	
	currentLoc++;
	startLoc = currentLoc;
	
	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


//Function to create a new node. Checks to see if the head exists first.
void createNewNode(char * input, char * inputType){
	//printf("i: %d, currentLoc: %d\n", i, currentLoc);
	
	//If no head exists, function passes to the function to create a head.
	if(head == NULL){
		//printf("Head is null.\n");
		createHeadNode(input, inputType);
	} 
	
	//Else if a head exists, the code will run as normal to create a new node.
	else{
		Node * new = (Node*)malloc(sizeof(Node));
		new->data = (char*)malloc(currentLoc-startLoc+1);
		
		Node * l = head;
		while(l->next != NULL){
			l = l->next;
		}
		
		l->next = new;
		
		strncpy(new->data, input + startLoc, currentLoc-startLoc+1);
		new->type = inputType;
		
		currentLoc++;
		startLoc = currentLoc;
	}
	
	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


//Function for creating a word. Due to the greedy nature of the algorithm, only needs a space or punctuation to terminate rather than any numbers.
void isWord(char * input){
	//printf("word\n");
	while(currentLoc < strlen(input)){
		//printf("currentLoc: %d\n", currentLoc);
		
		//Check to see if the character is alphanumeric. 
		if(currentLoc < strlen(input)-1 && !isalpha(input[currentLoc+1]) && !isdigit(input[currentLoc+1])){
			createNewNode(input, "word");
			
			break;
		}
		
		//Check to see if we're at the end of the string, since the function won't automatically send the rest of the string.
		else if(currentLoc == strlen(input) - 1){
			//printf("End of string.\n");
			
			createNewNode(input, "word");
			
			break;
		}
		
		currentLoc++;
	}
	//printf("Returning\n");
	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


//Function to test for punctuation.
//Also tests to make sure it doesn't overflow the length of the string.
void isPunctuation(char * input){
	if(currentLoc < strlen(input)-1 && input[startLoc] == '+' && input[startLoc+1] == '='){		//checks for plusequals
		currentLoc++;
		
		createNewNode(input, "plusequals");
	} else if(currentLoc < strlen(input)-1 && input[startLoc] == '+' && input[startLoc+1] == '+'){		//checks for plusequals
		currentLoc++;
		
		createNewNode(input, "increment");
	} 
	
	else{
		createNewNode(input, "punct");
	}
	
	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


//Helper function for isFloat for if a float also has scientific notation.
void isScien(char * input){
	//printf("Scientific notation.\n");
	
	while(currentLoc < strlen(input)){
		if(currentLoc < strlen(input)-1 && !isdigit(input[currentLoc+1])){
			createNewNode(input, "float");
			
			break;
		}
		
		//Check to see if we're at the end of the string, since the function won't automatically send the rest of the string.
		else if(currentLoc == strlen(input) - 1){
			//printf("End of string.\n");
			
			createNewNode(input, "float");
			
			break;
		}
		
		currentLoc++;
	}
	
	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


void isFloat(char * input){
	//printf("Float.\n");
	
	while(currentLoc < strlen(input)){
		//First check for scientific notation
		if(currentLoc < strlen(input)-3 && (input[currentLoc+1] == 'e' || input[currentLoc+1] == 'E') && (input[currentLoc+2] == '-' || input[currentLoc+2] == '+') && isdigit(input[currentLoc+3])){
			currentLoc += 3;
			
			isScien(input);
			
			break;
		}
		
		else if(currentLoc < strlen(input)-2 && (input[currentLoc+1] == 'e' || input[currentLoc+1] == 'E') && isdigit(input[currentLoc+2])){
			currentLoc += 2;
			
			isScien(input);
			
			break;
		}
		
		//Check for a non-numerical character
		else if(currentLoc < strlen(input)-1 && !isdigit(input[currentLoc+1])){
			createNewNode(input, "float");
			
			break;
		}
		
		//Check to see if we're at the end of the string, since the function won't automatically send the rest of the string.
		else if(currentLoc == strlen(input) - 1){
			//printf("End of string.\n");
			
			createNewNode(input, "float");
			
			break;
		}
		
		currentLoc++;
	}
	
	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


void isDecimal(char * input){
	//printf("Decimal.\n");
	
	while(currentLoc < strlen(input)){
		//Check to see if the string is a float with a decimal point.
		if(currentLoc < strlen(input)-2 && (input[currentLoc+1] == '.' && isdigit(input[currentLoc + 2]))){
			//If there exists a decimal point and a digit after, increment currentLoc and send to isFloat.
			currentLoc++;
			
			isFloat(input);
			
			break;
		}
		
		else if(currentLoc < strlen(input)-1 && !isdigit(input[currentLoc+1])){
			createNewNode(input, "decimal");
			
			break;
		}
		
		//Check to see if we're at the end of the string, since the function won't automatically send the rest of the string.
		else if(currentLoc == strlen(input) - 1){
			//printf("End of string.\n");
			
			createNewNode(input, "decimal");
			
			break;
		}
		
		currentLoc++;
	}
	
	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


void isNumber(char * input){
	//printf("Number.\n");
	
	while(currentLoc < strlen(input)){
		//Check to see if the string is a float with a decimal point.
		if(currentLoc < strlen(input)-2 && (input[currentLoc+1] == '.' && isdigit(input[currentLoc + 2]))){
			//If there exists a decimal point and a digit after, increment currentLoc and send to isFloat.
			currentLoc++;
			
			isFloat(input);
			
			break;
		}
		
		//else if(input[currentLoc] > 55 && input[currentLoc] < 58){
		else if(currentLoc < strlen(input)-1 && input[currentLoc+1] > '7' && input[currentLoc+1] <= '9'){
			currentLoc++;
			
			isDecimal(input);
			
			break;
		}
		
		else if(currentLoc < strlen(input)-1 && !isdigit(input[currentLoc+1])){
			//printf("Octal.\n");
			
			createNewNode(input, "octal");
			
			break;
		}
		
		//Check to see if we're at the end of the string, since the function won't automatically send the rest of the string.
		else if(currentLoc == strlen(input) - 1){
			//printf("End of string.\n");
			
			createNewNode(input, "octal");
			
			break;
		}
		
		currentLoc++;
	}
	
	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


//Function for a known hex token. Goes until it finds a non-hex character.
void isHex(char * input){
	//printf("Hex.\n");
	while(currentLoc < strlen(input)){
		//printf("i: %d, currentLoc: %d\n", i, currentLoc);
		
		//Checks for a non-hex character
		if(currentLoc < strlen(input)-1 && !isxdigit(input[currentLoc+1])){
			//printf("Non-hex found\n");
			
			createNewNode(input, "hex");
			
			break;
		}
		
		//Check to see if we're at the end of the string, since the function won't automatically send the rest of the string.
		else if(currentLoc == strlen(input) - 1){
			//printf("End of string.\n");
			
			createNewNode(input, "hex");
			
			break;
		}
		
		currentLoc++;
	}
	
	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


//Function to determine what type of token is required and sends it to the proper function
void tokenType(char * input){
	if(isspace(input[startLoc])){
		startLoc++;
		currentLoc++;
	} 
	else if(isalpha(input[startLoc])){
		isWord(input);
	} 
	else if(ispunct(input[startLoc])){
		isPunctuation(input);
	} 
	
	else if(currentLoc < strlen(input)-1 && input[startLoc] == 48 && (input[startLoc+1] == 'x' || input[startLoc+1] == 'X')){
		currentLoc += 2;
		isHex(input);
	}
	else if(isdigit(input[startLoc]) && input[currentLoc] > '7' && input[currentLoc] <= '9'){
		isDecimal(input);
	}
	else if(isdigit(input[startLoc])){
		isNumber(input);
	}
	
	return;
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
		//Tokenize the string input
		while(startLoc < strlen(argv[1])){
			//printf("i: %d, currentLoc: %d\n", i, currentLoc);
			
			tokenType(argv[1]);
		}
		
		printList();
		
	} else if(argc <= 1){
		printf("There are no strings to tokenize.\n");
	} else if(argc > 2){
		printf("There are too many strings to tokenize.\n");
	}
	
	return EXIT_SUCCESS;
}
