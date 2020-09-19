#ifndef TOKENIZER_H_
#define TOKENIZER_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node{
	char * data;
	char * type;
	struct Node * next;
} Node;

#endif
