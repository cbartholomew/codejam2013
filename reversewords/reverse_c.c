#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_LINE 1000
#define SPACE 	 32
#define NEW_LINE 10

void do_output(char *sentence[], int count, int max, FILE* fp)
{	
	if(count == max)
		return;
	
	// recurse further	
	do_output(sentence,count + 1, max, fp);	
	
	// print results befor exiting
	fprintf(fp,"%s ",sentence[count]);	
}


int main(int argc, char** argv)
{
	
	if(argc < 2)
	{
		printf("Missing Input File\n");
		return 1;
	}
	
	// read in file name
	FILE *input = fopen(argv[1],"r");
	FILE *output= fopen("output.out","w+");
	
	// allocate for lines up to 100 characters
	char *buffer = malloc(sizeof(MAX_LINE));
	
	int n 		   = 0;
	int ch 		   = 0;
	int case_count = 0;
	int word_count = 0;
	int length 	   = 0;
	
	// get amount of cases
	fscanf(input,"%d",&n);
	
	// allocate memory for string array
	char **sentence = malloc(n * sizeof(buffer));
	
	// throw away NL char
	ch = getc(input);
	
	// read in character by character, building the word
	while((ch = getc(input)))
	{		
		if((ch == SPACE) || (ch == NEW_LINE) || (ch == EOF))
		{		
			// finish string using \0
			buffer[length] 	  = '\0';
			// add the completed word to the array
			sentence[word_count] = buffer;			
			// reset memory location of buffer (memory leak)
			buffer 			  = malloc(sizeof(MAX_LINE));
			// reset character length of string
			length 			  = 0;
			// increase the word counter
			word_count++;
			
			// if it was a new line, it's time to print
			if(ch == NEW_LINE)
			{
				// increase case count
				case_count++;
				
				// specific case
				fprintf(output,"Case #%d: ",case_count);
				
				// recurse print
				do_output(sentence,0,word_count,output);
				
				// realloc memory for new sentence
				realloc(sentence,n * sizeof(buffer));
				
				// reset word count
				word_count = 0;
				
				//print char 10
				fprintf(output,"%c",ch);
			}
			
			if(ch == EOF) 
			{
				// specific case
				case_count++;
				fprintf(output,"Case #%d: ",case_count);
				do_output(sentence,0,word_count,output);
				break;
			}
					
		}
		else
		{				
			// continue building word
			buffer[length] 	 = ch;
			length++;
		}
	}
	
	// print ending new line char
	fprintf(output,"\n");
	
	// deallocate memory
	free(buffer);
	free(sentence);
	
	// close file input/output
	fclose(input);
	fclose(output);
}
