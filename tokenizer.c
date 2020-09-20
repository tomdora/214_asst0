#include "tokenizer.h"

Node * head = NULL;
int currentLoc = 0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////

int isWord(char * input, int i){
	while(currentLoc < strlen(input)){
		//printf("%c\n", input[currentLoc]);
		if(isspace(input[currentLoc]) && head == NULL){			//if head is null and program reaches a space
			//printf("No head, is space\n");
			
			head = malloc(sizeof(Node));
			head->data = malloc(currentLoc-i);
			
			strncpy(head->data, input + i, currentLoc-i);
			head->type = "word";
			
			i = currentLoc+1;
			currentLoc++;
			
			break;
			
		} else if(ispunct(input[currentLoc]) && head == NULL){				//if head is null and program reaches punctuation
			//printf("No head, is punct\n");
			
			head = malloc(sizeof(Node));
			head->data = malloc(currentLoc-i);
			
			strncpy(head->data, input + i, currentLoc-i);
			head->type = "word";
			
			i = currentLoc;
			
			break;
			
		} else if(isspace(input[currentLoc])){						//head is not null; if program finds a space
			//printf("Found space\n");
			
			Node * new = malloc(sizeof(Node));
			new->data = malloc(currentLoc-i);
			
			Node * l = head;
			while(l->next != NULL){
				l = l->next;
			}
			
			l->next = new;
			
			strncpy(new->data, input + i, currentLoc-i);
			new->type = "word";
			
			i = currentLoc+1;
			currentLoc++;
			
			break;
			
		} else if(ispunct(input[currentLoc])){						//head is not null; if program finds punctuation
			//printf("Found punct\n");
			
			Node * new = malloc(sizeof(Node));
			new->data = malloc(currentLoc-i);
			
			Node * l = head;
			while(l->next != NULL){
				l = l->next;
			}
			
			l->next = new;
			
			strncpy(new->data, input + i, currentLoc-i);
			new->type = "word";
			
			i = currentLoc;
			
			break;
			
		} else if(currentLoc == strlen(input) - 1){							//if the program reaches the end of the input string before finding a punctuation or a space
			Node * new = malloc(sizeof(Node));
			new->data = malloc(currentLoc-i);
			
			Node * l = head;
			while(l->next != NULL){
				l = l->next;
			}
			
			l->next = new;
			
			strncpy(new->data, input + i, currentLoc-i+1);
			new->type = "word";
			
			i = strlen(input);
		}
		
		currentLoc++;
	}
	//printf("Returning\n");
	return i;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


int isPunctuation(char * input, int i){
	if(input[i] == '+' && input[i+1] == '='){
		Node * new = malloc(sizeof(Node));
		new->data = malloc(2);
		
		Node * l = head;
		while(l->next != NULL){
			l = l->next;
		}
		
		l->next = new;
		
		strncpy(new->data, input + i, 2);
		new->type = "plusequals";
		
		currentLoc = currentLoc	+ 2;
		i = currentLoc;
	}
	
	if(ispunct(input[i])){
		Node * new = malloc(sizeof(Node));
		new->data = malloc(1);
		
		Node * l = head;
		while(l->next != NULL){
			l = l->next;
		}
		
		l->next = new;
		
		strncpy(new->data, input + i, 1);
		new->type = "punct";
		
		i = currentLoc+1;
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
	} else if(isalpha(input[i])){
		i = isWord(input, i);
	} else if(ispunct(input[i])){
		i = isPunctuation(input, i);
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
		while(i != strlen(argv[1])){
			//printf("%d\n", i);
			
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
