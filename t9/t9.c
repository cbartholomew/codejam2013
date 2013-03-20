#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#define ALPHABET 26
#define NEW_LINE 10

typedef struct num
{
	int  digit;
	int  clicks;
	char letter;
} num;

// an array of pointer nums
num *alphanums[ALPHABET];

void do_load()
{	
	char ch;
	int  clicks = 0;
	int  digit  = 1;
	for(int i=0;i<ALPHABET;i++)
	{
		// get real char representation
		ch = (i + 'a'); 
		
		// malloc memory for num struct on heap for usage later
		num *new_num = malloc(sizeof(num));
		
		// special cases on s & z, which require 4 clicks vs 3 clicks
		if((ch == 's') || (ch == 'z'))
		{
			// increase click count
			clicks++;

			// associate new num members
			new_num->clicks = clicks;
			new_num->letter = ch;		
			// on z, make sure to not incrase the digit
			new_num->digit = (ch == 'z') ? digit -1 : digit;
			
			// place in array position
			alphanums[i] = new_num;
			// increase digit count
			digit++;
			// reset click count because their shouln't be one now
			clicks = 0;
		}
		else
		{		
			// remainder of zero means we are on a new digit		
			if((i % 3 == 0))
				digit++;
				
			// if we reach 3 clicks, then we are maxed (unless special case) - reset to 1 click
			if(clicks == 3)
				clicks = 1;
			else
				clicks++;
									
			// associate new num members
			new_num->clicks = clicks;
			new_num->letter = ch;
			// special case v & y - minus digit by 1 to accomidate for s & z 
			new_num->digit = ((ch == 'v') || (ch == 'y')) ? digit -1 : digit;
			
			// place in array position
			alphanums[i] = new_num;
			//printf("%c clicks %d digit %d\n",ch, clicks,digit);
		}
	}	
}

void do_free()
{
	for(int i=0;i<ALPHABET;i++)
	{
		num *n = alphanums[i];
		free(n);
	}
}

int main(int argc, char** argv)
{
	// load up phone hash data structure
	do_load();
	
	// check file
	if(argc < 2)
	{
		printf("Missing Input File\n");
		return 1;
	}
	
	// open files
	FILE* input = fopen(argv[1],"r");
	FILE* output = fopen("output.out","w+");
	
	// init var
	int last_digit = 0; 
	int ch = 0;
	int N  = 0;
	int case_count = 1;
	
	// get total cases
	fscanf(input,"%d",&N);
	
	// dump new line char
	ch = getc(input);
	
	// begin case count printing
	fprintf(output,"Case #%d: ",case_count);
	
	// iterate through each char 
	while((ch = getc(input)) != EOF)
	{	
		// either space or new line character	
		if(isspace(ch))
		{			
			// double spaces (0)
			if(last_digit == ch)
				fprintf(output," ");
			
			// depending on if it's a new line or space, we write different things
			(ch == NEW_LINE)  ? fprintf(output,"\n") : fprintf(output,"0");
			
			// on new line, begin new case
			if((ch == NEW_LINE) && (case_count != N))
			{
				case_count++;
				fprintf(output,"Case #%d: ",case_count);
			}
			
			// associate the last char w/ new char
			last_digit = ch;
		}
		else
		{
			// create temp struct via pointer 
			num *n = alphanums[(ch - 'a') % ALPHABET];
			
			// if it's the same digit, we need a space between 
			if(last_digit == n->digit)
				fprintf(output," ");
			
			// write out the digit based on it's click count
			for(int i=0;i<n->clicks;i++)
				fprintf(output,"%d",n->digit);	
			
			// keep track of previous digit
			last_digit = n->digit;
		}
	}
	
	// free hash table and close out files
	do_free();
	fclose(output);
	fclose(input);
	
	return 0;
}


