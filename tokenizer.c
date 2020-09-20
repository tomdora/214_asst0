#include "tokenizer.h"

Node * head = NULL;
int currentLoc = 0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////


//Function to create a head node. Checks to see if the entire string is one single token first
int createHeadNode(char * input, char * inputType, int i, int x){
	//printf("No head.\n");
	if(currentLoc == strlen(input) - 1){
		//printf("Head is null and end of string. currentLoc = %d, strlen = %ld\n", currentLoc, strlen(input));
		
		head = malloc(sizeof(Node));
		head-> data = malloc(currentLoc-i+1);
		
		strncpy(head->data, input + i, currentLoc-i+1);
		head->type = inputType;
		
		i = strlen(input);
	} else{
		head = malloc(sizeof(Node));
		head->data = malloc(currentLoc-i);
		
		strncpy(head->data, input + i, currentLoc-i);
		head->type = inputType;
		
		currentLoc = currentLoc + x;
		i = currentLoc;
	}
	
	return i;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


int createLastNode(char * input, char * inputType, int i){
	Node * new = malloc(sizeof(Node));
	new->data = malloc(currentLoc-i+1);
	
	Node * l = head;
	while(l->next != NULL){
		l = l->next;
	}
	
	l->next = new;
	
	strncpy(new->data, input + i, currentLoc-i+1);
	new->type = inputType;
	
	i = strlen(input);
	
	return i;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


int createNewNode(char * input, char * inputType, int i, int x){
	if(head == NULL){
		printf("Head is null.\n");
		i = createHeadNode(input, inputType, i, x);
	} else if(currentLoc == strlen(input) - 1){
		printf("End of string.\n");
		i = createLastNode(input, inputType, i);
	} 
	
	else{
		Node * new = malloc(sizeof(Node));
		new->data = malloc(currentLoc-i);
		
		Node * l = head;
		while(l->next != NULL){
			l = l->next;
		}
		
		l->next = new;
		
		strncpy(new->data, input + i, currentLoc-i);
		new->type = inputType;
		
		currentLoc += x;
		i = currentLoc;
	}
	
	return i;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


int isWord(char * input, int i){
	//printf("word\n");
	while(currentLoc < strlen(input)){
		//printf("%c\n", input[currentLoc]);
		if(isspace(input[currentLoc])){						//head is not null; if program finds a space
			//printf("Found space\n");
			
			i = createNewNode(input, "word", i, 1);
			
			break;
			
		} else if(ispunct(input[currentLoc])){						//head is not null; if program finds punctuation
			//printf("Found punct\n");
			
			i = createNewNode(input, "word", i, 0);
			
			break;
			
		} else if(currentLoc == strlen(input) - 1){					//if the program reaches the end of the input string before finding a punctuation or a space
			//printf("End of string.\n");
			
			i = createNewNode(input, "word", i, 0);
			
			break;
		}
		
		currentLoc++;
	}
	//printf("Returning\n");
	return i;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


int isPunctuation(char * input, int i){
	if(input[i] == '+' && input[i+1] == '='){
		
		currentLoc += 2;
		i = createNewNode(input, "plusequals", i, 0);
		
	} 
	
	if(ispunct(input[i])){
		currentLoc += 1;
		i = createNewNode(input, "punct", i, 0);
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


int isHex(char * input, int i){
	
	
	return i;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


int isNumber(char * input, int i){
	while(currentLoc < strlen(input)){
		if(input[currentLoc] = '.' && isdigit(input[currentLoc + 1])){
			printf("Float.");
			
			i = isFloat(input, i);
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
	
	else if(input[i] == '0' && input[i+1] == ('x' || 'X')){
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
			//printf("i: %d\n", i);
			
			i = tokenType(argv[1], i);
		}
		
		printList();
		
	} else if(argc <= 1){
		printf("There are no strings to tokenize.\n");
	} else if(argc > 2){
		printf("There are too many strings to tokenize.\n");
	}
	
	return 0;
}
