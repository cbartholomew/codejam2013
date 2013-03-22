#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

#define VECTORS 2

void do_populate();
void do_swap();
void do_print();
void do_vector_math();
int do_factorial();
int *do_permutation();
int  sum			= 0;
bool tally_sum		= false;

int main(int argc, char **argv)
{
	// cases
	int T = -1;
	// vector length
	int vlen = -1;
	
	if(argc < 2)
	{
		printf("You forgot the input file, dummy.");
		return 1;
	}
	
	// open file
	FILE *input = fopen(argv[1],"r");
	FILE *output= fopen("output.out","w+");
	// assign case value
	fscanf(input,"%d",&T);
		
	int case_count = 1;
	while(case_count <= T)
	{
		// get the vector length
		fscanf(input,"%d",&vlen);
		// create vector arrays based on the length
		int *vector_x = malloc(sizeof(int) * vlen);
		int *vector_y = malloc(sizeof(int) * vlen);
		
		// hold the first vector objects
		// !vlen * sizeof(int)
		int vlen_factor = do_factorial(vlen);
				
		// populate the vectors
		for(int i=0;i<VECTORS;i++)
		{
			// get vector
			int *vector 	= (i == 0)  ? vector_x :  vector_y;		
			do_populate(input,vector,vlen);
		}
		
		// run vector math on the output of both permutations at the same time
		do_vector_math(do_permutation(vector_x,vector_y,0,vlen),do_permutation(vector_y,vector_x,0,vlen),vlen);
			
		// print sum
		fprintf(output,"Case #%d: %d\n",case_count, sum);
		
		// reset for next case
		sum 	  	= 0;
		free(vector_x);
		free(vector_y);
		tally_sum 	= false;	
		case_count++;
	}
	fclose(input);
	fclose(output);
	
	return 0;
}

void do_vector_math(int *vector_x, int *vector_y, int vector_len)
{
	// get a temp sum
	int temp_sum = 0;
	
	// check every associated element - get a product and a sum it up
	for(int i=0;i<vector_len;i++)
	{
		int x 		 = vector_x[i];
		int y 	     = vector_y[i];
		int product  = x * y;
		temp_sum += product;		
	}
	
	// haven't started yet - assign first value as the sum
	if(!tally_sum)
	{
		sum = temp_sum;
		tally_sum = true;
	}
	else
	{	
		// is the temp sum less than sum?
		sum = (temp_sum < sum) ? temp_sum : sum;
	}
}

// modified to return vecntor integer, also accept both alpha and beta vectors
int *do_permutation(int *vector_a, int *vector_b, int index, int max)
{
	// print the permutated vector
	if(index == max)
	{	
		//do_print(vector, max);
		// run math on permutated alpha against non-permutated beta
		do_vector_math(vector_a,vector_b,max);
		return vector_a;
	}
	// recurse
	vector_a = do_permutation(vector_a,vector_b,index + 1, max);
	// run math on permutated alpha against non-permutated beta
	do_vector_math(vector_a,vector_b,max);
	
	// swap each iteration, doing a permutation of each
	int element;
	for(element = index + 1; element < max; element++)
	{
		// don't permute if the values are equal
		if(vector_a[index] == vector_a[element])
			continue;
		
		// swap
		do_swap(vector_a,index,element);
		// recurse
		vector_a = do_permutation(vector_a,vector_b,index + 1, max);
		// run math on permutated alpha against non-permutated beta
		do_vector_math(vector_a,vector_b,max);
		// swap
		do_swap(vector_a,index,element);
	}	
	// return alpha vector to the parent function
	return vector_a;
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

// fucking c
int do_factorial(int n)
{
	  int c;
	  int result = 1;

	  for (c = 1; c <= n; c++)
	    result = result * c;

	  return result;	
}
