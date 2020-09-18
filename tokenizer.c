#include "tokenizer.h"

Node * head = NULL;
int currenetLoc = 0;

int isWord(char * input, int i){
	while(currenetLoc < strlen(input)){
		//printf("%c\n", input[currenetLoc]);
		
		if((ispunct(input[currenetLoc]) || isspace(input[currenetLoc])) && head == NULL){			//if head is null and program reaches a punctuation or space
			//printf("No head, is punct or space\n");
			
			head = malloc(sizeof(Node));
			head->data = malloc(currenetLoc-i);
			
			strncpy(head->data, input + i, currenetLoc-i);
			head->type = "word";
			
			i = currenetLoc+1;
			currenetLoc++;
			
			break;
			
		} else if(ispunct(input[currenetLoc]) || isspace(input[currenetLoc])){						//head is not null; if program finds a punctuation or a space
			//printf("Found punct/space\n");
			
			Node * new = malloc(sizeof(Node));
			new->data = malloc(currenetLoc-i);
			
			Node * l = head;
			while(l->next != NULL){
				l = l->next;
			}
			
			l->next = new;
			
			strncpy(new->data, input + i, currenetLoc-i);
			new->type = "word";
			
			i = currenetLoc+1;
			currenetLoc++;
			
			break;
			
		} else if(currenetLoc == strlen(input) - 1){							//if the program reaches the end of the input string before finding a punctuation or a space
			Node * new = malloc(sizeof(Node));
			new->data = malloc(currenetLoc-i);
			
			Node * l = head;
			while(l->next != NULL){
				l = l->next;
			}
			
			l->next = new;
			
			strncpy(new->data, input + i, currenetLoc-i+1);
			new->type = "word";
			
			i = strlen(input);
		}
		
		currenetLoc++;
	}
	
	//printf("Returning\n");
	return i;
}

int tokenType(char * input, int i){
	if(isalpha(input[i])){
		i = isWord(input, i);
	}
	
	return i;
}

void printList(){
	if(head == NULL){ printf("Head is null.\n"); }
	Node * l = head;
	while(l != NULL){
		printf("%s \"%s\"\n", l->type, l->data);
		
		l = l->next;
	}
}



int main(int argc, char * argv[]){
	//Node * head = NULL;
	
	if(argc == 2){
		int i = 0;
		
		while(i != strlen(argv[1])){
			//printf("%d\n", i);
			
			i = tokenType(argv[1], i);
		}
		
		printList(head);
		
	} else if(argc <= 1){
		printf("There are no strings to tokenize.\n");
	} else if(argc > 2){
		printf("There are too many strings to tokenize.\n");
	}
	
	return 0;
}
