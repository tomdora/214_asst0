#include "tokenizer.h"

Node * head = NULL;
int startLoc = 0;			//starting location
int currentLoc = 0;			//current iteration location


///////////////////////////////////////////////////////////////////////////////////////////////////////// ""Beep boop" beep"


//Function to create a new node. Checks to see if the head exists first.
void createNewNode(char * input, char * inputType){
	//printf("type: %s, startLoc: %d, currentLoc: %d\n", inputType, startLoc, currentLoc);
	
	//If no head exists, function passes to the function to create a head.
	if(head == NULL){
		//printf("Head is null.\n");
		
		head = malloc(sizeof(Node));
		head->data = malloc(sizeof(char) * (currentLoc - startLoc + 2));
		
		strncpy(head->data, input + startLoc, currentLoc-startLoc+1);
		head->data[currentLoc - startLoc+1] = '\0';
		head->type = inputType;
		
		currentLoc++;
		startLoc = currentLoc;
	}
	
	//Else if a head exists, the code will run as normal to create a new node.
	else{
		Node * new = malloc(sizeof(Node));
		new->data = malloc(sizeof(char) * currentLoc-startLoc+2);
		
		Node * l = head;
		while(l->next != NULL){
			l = l->next;
		}
		
		l->next = new;
		
		strncpy(new->data, input + startLoc, currentLoc-startLoc+1);
		new->data[currentLoc - startLoc+1] = '\0';
		new->type = inputType;
		
		currentLoc++;
		startLoc = currentLoc;
	}
	
	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


//Function for testing specific words
void isKeyword(char * input){
	//printf("startLoc: %d, currentLoc: %d\n", startLoc, currentLoc);
	
	//Test to see if the token can possibly be any of these operators.
	if(currentLoc-startLoc+1 > 1 && currentLoc-startLoc+1 < 9){
		//printf("Between 1 and 9\n");
		
		//Split the sizes in half for 2,3,4 or 5,6,7,8
		//This reduces the number of comparisons necessary from 7 (==2,==3,==4,==5,==6,==7,==8) to either 4 (if,==2,==3,==4) or 5 (if,==5,==6,==7,==8)
		if(currentLoc-startLoc+1 < 5){
			//Check for 2
			if(currentLoc-startLoc+1 == 2){
				if(strncmp(input + startLoc, "do", currentLoc-startLoc+1) == 0){
					createNewNode(input, "do");
				} else if(strncmp(input + startLoc, "if", currentLoc-startLoc+1) == 0){
					createNewNode(input, "if");
				} 
				
				else{
					createNewNode(input, "word");
				}
			}
			//Check for 3
			else if(currentLoc-startLoc+1 == 3){
				if(strncmp(input + startLoc, "for", currentLoc-startLoc+1) == 0){
					createNewNode(input, "for");
				} else if(strncmp(input + startLoc, "int", currentLoc-startLoc+1) == 0){
					createNewNode(input, "int");
				} 
				
				else{
					createNewNode(input, "word");
				}
			} 
			//If not 2 or 3 it must be 4
			else{
				if(strncmp(input + startLoc, "auto", currentLoc-startLoc+1) == 0){
					createNewNode(input, "auto");
				} else if(strncmp(input + startLoc, "case", currentLoc-startLoc+1) == 0){
					createNewNode(input, "case");
				} else if(strncmp(input + startLoc, "char", currentLoc-startLoc+1) == 0){
					createNewNode(input, "char");
				} else if(strncmp(input + startLoc, "else", currentLoc-startLoc+1) == 0){
					createNewNode(input, "else");
				} else if(strncmp(input + startLoc, "enum", currentLoc-startLoc+1) == 0){
					createNewNode(input, "enum");
				} else if(strncmp(input + startLoc, "goto", currentLoc-startLoc+1) == 0){
					createNewNode(input, "goto");
				} else if(strncmp(input + startLoc, "long", currentLoc-startLoc+1) == 0){
					createNewNode(input, "long");
				} else if(strncmp(input + startLoc, "void", currentLoc-startLoc+1) == 0){
					createNewNode(input, "void");
				} 
				
				else{
					createNewNode(input, "word");
				}
			}
		} else{
			//Split 4(==5,==6,==7,==8) into 2/3 (if,==5/,==6) or 2/3 (if,==7/,==8)
			if(currentLoc-startLoc+1 < 7){
				//Check if it's 5
				if(currentLoc-startLoc+1 == 5){
					if(strncmp(input + startLoc, "break", currentLoc-startLoc+1) == 0){
						createNewNode(input, "break");
					} else if(strncmp(input + startLoc, "const", currentLoc-startLoc+1) == 0){
						createNewNode(input, "const");
					} else if(strncmp(input + startLoc, "float", currentLoc-startLoc+1) == 0){
						createNewNode(input, "float");
					} else if(strncmp(input + startLoc, "short", currentLoc-startLoc+1) == 0){
						createNewNode(input, "short");
					} else if(strncmp(input + startLoc, "union", currentLoc-startLoc+1) == 0){
						createNewNode(input, "union");
					} else if(strncmp(input + startLoc, "while", currentLoc-startLoc+1) == 0){
						createNewNode(input, "while");
					}
					
					else{
						createNewNode(input, "word");
					}
				}
				//If it's not 5, it's 6.
				else{
					if(strncmp(input + startLoc, "double", currentLoc-startLoc+1) == 0){
						createNewNode(input, "double");
					} else if(strncmp(input + startLoc, "extern", currentLoc-startLoc+1) == 0){
						createNewNode(input, "extern");
					} else if(strncmp(input + startLoc, "return", currentLoc-startLoc+1) == 0){
						createNewNode(input, "return");
					} else if(strncmp(input + startLoc, "signed", currentLoc-startLoc+1) == 0){
						createNewNode(input, "signed");
					} else if(strncmp(input + startLoc, "sizeof", currentLoc-startLoc+1) == 0){
						createNewNode(input, "sizeof");
					} else if(strncmp(input + startLoc, "static", currentLoc-startLoc+1) == 0){
						createNewNode(input, "static");
					} else if(strncmp(input + startLoc, "struct", currentLoc-startLoc+1) == 0){
						createNewNode(input, "struct");
					} else if(strncmp(input + startLoc, "switch", currentLoc-startLoc+1) == 0){
						createNewNode(input, "switch");
					} 
					
					else{
						createNewNode(input, "word");
					}
				}
			} 
			else{
				//Check if it's 7
				if(currentLoc-startLoc+1 == 7){
					if(strncmp(input + startLoc, "default", currentLoc-startLoc+1) == 0){
						createNewNode(input, "default");
					} else if(strncmp(input + startLoc, "typedef", currentLoc-startLoc+1) == 0){
						createNewNode(input, "typedef");
					} 
					
					else{
						createNewNode(input, "word");
					}
				}
				//If it's not 7, it's 8
				else{
					if(strncmp(input + startLoc, "continue", currentLoc-startLoc+1) == 0){
						createNewNode(input, "continue");
					} else if(strncmp(input + startLoc, "register", currentLoc-startLoc+1) == 0){
						createNewNode(input, "register");
					} else if(strncmp(input + startLoc, "unsigned", currentLoc-startLoc+1) == 0){
						createNewNode(input, "unsigned");
					} else if(strncmp(input + startLoc, "volatile", currentLoc-startLoc+1) == 0){
						createNewNode(input, "volatile");
					} 
					
					else{
						createNewNode(input, "word");
					}
				}
			}
		}
	}
	//If it's too small or too big to be any of them, it's a word.
	else{
		createNewNode(input, "word");
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


//Function for creating a word. Due to the greedy nature of the algorithm, only needs a space or punctuation to terminate rather than any numbers.
void isWord(char * input){
	//printf("word\n");
	while(currentLoc < strlen(input)){
		//printf("currentLoc: %d\n", currentLoc);
		
		//Check to see if the character is alphanumeric. 
		if(currentLoc < strlen(input)-1 && !isalpha(input[currentLoc+1]) && !isdigit(input[currentLoc+1])){
			//printf("End of word.\n");
			
			isKeyword(input);
			
			break;
		}
		
		//Check to see if we're at the end of the string, since the function won't automatically send the rest of the string.
		else if(currentLoc == strlen(input) - 1){
			//printf("End of string.\n");
			
			isKeyword(input);
			
			break;
		}
		
		currentLoc++;
	}
	//printf("Returning\n");
	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


//Function for block comments; looks for the closing block
void isCommentBlock(char * input){
	while(currentLoc < strlen(input)){
		if(currentLoc < strlen(input)-1 && input[currentLoc] == '*' && input[currentLoc+1] == '/'){
			currentLoc += 2;
			startLoc = currentLoc;
			
			break;
		}
		
		else if(currentLoc == strlen(input)-1){
			currentLoc++;
			startLoc = currentLoc;
			
			break;
		}
		
		currentLoc++;
	}
	
	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


//Function for // comments; looks for a '\n' char
void isCommentLine(char * input){
	while(currentLoc < strlen(input)){
		if(currentLoc < strlen(input)-1 && input[currentLoc+1] == '\n'){
			currentLoc++;
			startLoc = currentLoc;
			
			break;
		}
		
		else if(currentLoc == strlen(input)-1){
			currentLoc++;
			startLoc = currentLoc;
			
			break;
		}
		
		currentLoc++;
	}
	
	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


//Function to detect an entire string. Will not do anything if there exists an invalid string.
void isString(char * input){
	while(currentLoc < strlen(input)){
		//Detect if an excaped ''' or '"' exists before we check for an ending mark
		if(currentLoc < strlen(input)-2 && input[currentLoc+1] == '\\' && input[currentLoc+2] == input[startLoc]){
			currentLoc += 2;
		}
		//Detect if the string ends
		else if(currentLoc < strlen(input)-1 && input[currentLoc+1] == input[startLoc]){
			currentLoc++;
			createNewNode(input, "string");
			
			break;
		}
		//Else check for an end to the entire input; if so, none of this is valid.
		else if(currentLoc == strlen(input)-1){
			printf("String invalid.\n");
			
			currentLoc = strlen(input);
			startLoc = currentLoc;
			
			break;
		}
		
		currentLoc++;
	}
	
	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


//Function to test for operators. 
void isPunctuation(char * input){
	//Unfortunately, we have to check each and every single one of these one by one
	//We can't break it up by size, because we don't know the size coming into this, and we can't blindly check the size first
	
	//Check for block comment before anything else
	if(currentLoc < strlen(input)-1 && input[currentLoc] == '/' && input[currentLoc+1] == '*'){
		currentLoc += 2;
		isCommentBlock(input);
	}
	//Check for line comment before anything else
	else if(currentLoc < strlen(input)-1 && input[currentLoc] == '/' && input[currentLoc+1] == '/'){
		currentLoc += 2;
		isCommentLine(input);
	}
	//Check for quotes; there must be space an ending quote.
	else if(currentLoc < strlen(input)-2 && (input[currentLoc] == '\'' || input[currentLoc] == '\"')){
		currentLoc++;
		isString(input);
	}
	
	//All operators of size 3
	else if(currentLoc < strlen(input)-2 && input[currentLoc] == '>' && input[currentLoc+1] == '>' && input[currentLoc+2] == '='){		
		currentLoc++;
		
		createNewNode(input, "shift right equals");
	} else if(currentLoc < strlen(input)-2 && input[currentLoc] == '<' && input[currentLoc+1] == '<' && input[currentLoc+2] == '='){		
		currentLoc++;
		
		createNewNode(input, "shift left equals");
	} 
	
	
	
	//All operators of size 2
	else if(currentLoc < strlen(input)-1 && input[currentLoc] == '<' && input[currentLoc+1] == '<'){		
		currentLoc++;
		
		createNewNode(input, "shift left");
	} else if(currentLoc < strlen(input)-1 && input[currentLoc] == '>' && input[currentLoc+1] == '>'){		
		currentLoc++;
		
		createNewNode(input, "shift right");
	} 
	
	else if(currentLoc < strlen(input)-1 && input[currentLoc] == '+' && input[currentLoc+1] == '='){		
		currentLoc++;
		
		createNewNode(input, "plusequals");
	} else if(currentLoc < strlen(input)-1 && input[currentLoc] == '-' && input[currentLoc+1] == '='){		
		currentLoc++;
		
		createNewNode(input, "minusequals");
	}
	
	else if(currentLoc < strlen(input)-1 && input[currentLoc] == '<' && input[currentLoc+1] == '='){		
		currentLoc++;
		
		createNewNode(input, "less than or equal test");
	} else if(currentLoc < strlen(input)-1 && input[currentLoc] == '>' && input[currentLoc+1] == '='){		
		currentLoc++;
		
		createNewNode(input, "greater than or equal test");
	}
	
	else if(currentLoc < strlen(input)-1 && input[currentLoc] == '=' && input[currentLoc+1] == '='){		
		currentLoc++;
		
		createNewNode(input, "equality test");
	} else if(currentLoc < strlen(input)-1 && input[currentLoc] == '!' && input[currentLoc+1] == '='){		
		currentLoc++;
		
		createNewNode(input, "inequality test");
	}
	
	else if(currentLoc < strlen(input)-1 && input[currentLoc] == '*' && input[currentLoc+1] == '='){		
		currentLoc++;
		
		createNewNode(input, "times equals");
	} else if(currentLoc < strlen(input)-1 && input[currentLoc] == '/' && input[currentLoc+1] == '='){		
		currentLoc++;
		
		createNewNode(input, "divide equals");
	} else if(currentLoc < strlen(input)-1 && input[currentLoc] == '%' && input[currentLoc+1] == '='){		
		currentLoc++;
		
		createNewNode(input, "mod equals");
	} else if(currentLoc < strlen(input)-1 && input[currentLoc] == '&' && input[currentLoc+1] == '='){		
		currentLoc++;
		
		createNewNode(input, "bitwise AND equals");
	} else if(currentLoc < strlen(input)-1 && input[currentLoc] == '^' && input[currentLoc+1] == '='){		
		currentLoc++;
		
		createNewNode(input, "bitwise XOR equals");
	} else if(currentLoc < strlen(input)-1 && input[currentLoc] == '|' && input[currentLoc+1] == '='){		
		currentLoc++;
		
		createNewNode(input, "bitwise OR equals");
	} 
	
	else if(currentLoc < strlen(input)-1 && input[currentLoc] == '+' && input[currentLoc+1] == '+'){		
		currentLoc++;
		
		createNewNode(input, "increment");
	} else if(currentLoc < strlen(input)-1 && input[currentLoc] == '-' && input[currentLoc+1] == '-'){		
		currentLoc++;
		
		createNewNode(input, "decrement");
	} 
	
	else if(currentLoc < strlen(input)-1 && input[currentLoc] == '-' && input[currentLoc+1] == '>'){		
		currentLoc++;
		
		createNewNode(input, "structure pointer");
	} 
	
	else if(currentLoc < strlen(input)-1 && input[currentLoc] == '&' && input[currentLoc+1] == '&'){		
		currentLoc++;
		
		createNewNode(input, "logical AND");
	} else if(currentLoc < strlen(input)-1 && input[currentLoc] == '|' && input[currentLoc+1] == '|'){		
		currentLoc++;
		
		createNewNode(input, "logical OR");
	} 
	
	
	
	//All operators of size 1
	else if(input[currentLoc] == '+'){	
		createNewNode(input, "addition");
	} else if(input[currentLoc] == '-'){
		createNewNode(input, "minus/subtract operator");
	} else if(input[currentLoc] == '*'){
		createNewNode(input, "multiply/dereference operator");
	} else if(input[currentLoc] == '/'){
		createNewNode(input, "division");
	} 
	
	else if(input[currentLoc] == '('){
		createNewNode(input, "left parenthesis");
	} else if(input[currentLoc] == ')'){
		createNewNode(input, "right parenthesis");
	} else if(input[currentLoc] == '['){
		createNewNode(input, "left bracket");
	} else if(input[currentLoc] == ']'){
		createNewNode(input, "right bracket");
	} else if(input[currentLoc] == '{'){
		createNewNode(input, "left brace");
	} else if(input[currentLoc] == '}'){
		createNewNode(input, "right brace");
	} 
	
	else if(input[currentLoc] == '.'){
		createNewNode(input, "structure member");
	} else if(input[currentLoc] == ','){
		createNewNode(input, "comma");
	} 
	
	else if(input[currentLoc] == '!'){
		createNewNode(input, "negate");
	} else if(input[currentLoc] == '~'){
		createNewNode(input, "is complement");
	} else if(input[currentLoc] == '^'){
		createNewNode(input, "bitwise XOR");
	} else if(input[currentLoc] == '|'){
		createNewNode(input, "bitwise OR");
	} 
	
	else if(input[currentLoc] == '?'){
		createNewNode(input, "conditional true");
	} else if(input[currentLoc] == ':'){
		createNewNode(input, "conditional false");
	}
	
	else if(input[currentLoc] == '<'){
		createNewNode(input, "less than test");
	} else if(input[currentLoc] == '>'){
		createNewNode(input, "greater than test");
	} 
	
	else if(input[currentLoc] == '='){
		createNewNode(input, "assignment");
	} else if(input[currentLoc] == '&'){
		createNewNode(input, "AND/address operator");
	}
	
	
	
	//If all else fails, it's punctuation
	else{
		createNewNode(input, "punctuation");
	}
	
	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


//Helper function for isFloat for if a float also has scientific notation.
void isScien(char * input){
	//printf("Scientific notation.\n");
	
	while(currentLoc < strlen(input)){
		if(currentLoc < strlen(input)-1 && !isdigit(input[currentLoc+1])){
			createNewNode(input, "floating point");
			
			break;
		}
		
		//Check to see if we're at the end of the string, since the function won't automatically send the rest of the string.
		else if(currentLoc == strlen(input) - 1){
			//printf("End of string.\n");
			
			createNewNode(input, "floating point");
			
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
			createNewNode(input, "floating point");
			
			break;
		}
		
		//Check to see if we're at the end of the string, since the function won't automatically send the rest of the string.
		else if(currentLoc == strlen(input) - 1){
			//printf("End of string.\n");
			
			createNewNode(input, "floating point");
			
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
			createNewNode(input, "decimal integer");
			
			break;
		}
		
		//Check to see if we're at the end of the string, since the function won't automatically send the rest of the string.
		else if(currentLoc == strlen(input) - 1){
			//printf("End of string.\n");
			
			createNewNode(input, "decimal integer");
			
			break;
		}
		
		currentLoc++;
	}
	
	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


void isNumber(char * input){
	//printf("Number at %d\n", currentLoc);
	
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
			
			createNewNode(input, "octal integer");
			
			break;
		}
		
		//Check to see if we're at the end of the string, since the function won't automatically send the rest of the string.
		else if(currentLoc == strlen(input) - 1){
			//printf("End of string.\n");
			
			createNewNode(input, "octal integer");
			
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
			
			createNewNode(input, "hexadecimal integer");
			
			break;
		}
		
		//Check to see if we're at the end of the string, since the function won't automatically send the rest of the string.
		else if(currentLoc == strlen(input) - 1){
			//printf("End of string.\n");
			
			createNewNode(input, "hexadecimal integer");
			
			break;
		}
		
		currentLoc++;
	}
	
	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


//Function to determine what type of token is required and sends it to the proper function
void tokenType(char * input){
	if(isspace(input[currentLoc])){
		currentLoc++;
		startLoc = currentLoc;
	} 
	else if(isalpha(input[currentLoc])){
		isWord(input);
	} 
	else if(ispunct(input[currentLoc])){
		isPunctuation(input);
	} 
	
	else if(currentLoc < strlen(input)-1 && input[currentLoc] == 48 && (input[currentLoc+1] == 'x' || input[currentLoc+1] == 'X')){
		currentLoc += 2;
		isHex(input);
	}
	else if(isdigit(input[currentLoc]) && input[currentLoc] > '7' && input[currentLoc] <= '9'){
		isDecimal(input);
	}
	else if(isdigit(input[currentLoc])){
		isNumber(input);
	}
	
	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


//Function to print the entire linked list.
void printList(){
	//printf("printing\n");
	
	if(head == NULL){ printf("Head is null.\n"); }
	Node * l = head;
	while(l != NULL){
		printf("%s \"%s\"\n", l->type, l->data);
		
		l = l->next;
	}
	
	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


//Function to free every element of the list.
void freeList(){
	Node * x;
	
	while(head != NULL){
		x = head;
		head = head->next;
		
		free(x->data);
		free(x);
	}
	
	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////





//Main function
int main(int argc, char * argv[]){
	//Check for exactly two arguments; one is not enough and more is too many
	if(argc == 2){
		//printf("strlen: %ld\n", strlen(argv[1]));
		
		char * test = "int main(int argc, char * argv[]){ printf(\"Hello there.\\n\"); }";
		
		//Tokenize the string input
		//while(startLoc < strlen(test)){
		while(startLoc < strlen(argv[1])){
			//printf("startLoc: %d, currentLoc: %d\n", startLoc, currentLoc);
			
			tokenType(argv[1]);
			//tokenType(test);
		}
		
		printList();
		
		freeList();
		
	} else if(argc <= 1){
		printf("There are no strings to tokenize.\n");
	} else if(argc > 2){
		printf("There are too many strings to tokenize.\n");
	}
	
	return EXIT_SUCCESS;
}
