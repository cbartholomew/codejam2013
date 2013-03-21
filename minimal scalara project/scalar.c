#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

#define VECTORS 2

void do_populate();
void do_permutation();
void do_swap();
void do_print();

int main(int argc, char **argv)
{
	// cases
	int T = -1;
	// vector length
	int vlen = -1;
	// open file
	FILE *input = fopen("input.in","r");
	// assign case value
	fscanf(input,"%d",&T);
	// get the vector length
	fscanf(input,"%d",&vlen);
	// create vector arrays based on the length
	int vector_x[vlen];
	int vector_y[vlen];
	
	// populate the vectors
	for(int i=0;i<VECTORS;i++)
	{
		// get vector
		int *vector = (i == 0) ? vector_x : vector_y;
		do_populate(input,vector,vlen);
		do_permutation(vector,0,vlen);
	}
	
	fclose(input);
}

void do_populate(FILE *input, int *vector, int max)
{
	// populate the vector based on the input
	for(int i=0;i<max;i++)
	{
		int number = -1;
		fscanf(input,"%d",&number);
		vector[i] = number;
	}
}

void do_permutation(int *vector, int index, int max)
{
	// print the permutated vector
	if(index == max)
	{
		do_print(vector, max);
		printf("\n");
		return;
	}
	// recurse
	do_permutation(vector, index + 1, max);
	
	// swap each iteration, doing a premutation of each
	int element;
	for(element = index + 1; element < max; element++)
	{
		if(vector[index] == vector[element])
			continue;
		
		// swap
		do_swap(vector,index,element);
		// recurse
		do_permutation(vector,index + 1, max);
		// swap
		do_swap(vector,index,element);
	}	
}

void do_swap(int *vector, int pos_a, int pos_b)
{
	int n = vector[pos_a];
	vector[pos_a] = vector[pos_b];
	vector[pos_b] = n;
}

void do_print(int *vector, int len)
{
	for(int i=0;i<len;i++)
		printf("%d\n",vector[i]);
}
