#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

#define VECTORS 2

void do_populate();
void do_permutation();
void do_swap();
void do_print();
void do_store();
void do_store_compare();
void do_vector_math();
void do_free();
int do_factorial();

int **store_x 	= NULL;
int **store_y   = NULL;

int  store_x_len 	= 0;
int  store_y_len 	= 0;
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
		
	int case_count = 0;
	while(case_count != T)
	{
		// get the vector length
		fscanf(input,"%d",&vlen);
		// create vector arrays based on the length
		int vector_x[vlen];
		int vector_y[vlen];
		
		// hold the first vector objects
		// !vlen * sizeof(int)
		int vlen_factor = do_factorial(vlen);
		
		store_x = malloc((sizeof(int) * vlen_factor) * (sizeof(int) * vlen));
		store_y = malloc((sizeof(int) * vlen_factor) * (sizeof(int) * vlen));
				
		// populate the vectors
		for(int i=0;i<VECTORS;i++)
		{
			// get store
			int **store 	= (i == 0)  ? store_x  :  store_y;
			// get vector
			int *vector 	= (i == 0)  ? vector_x :  vector_y;
			int *store_len  = (i == 0)  ? &store_x_len : &store_y_len;
			
			do_populate(input,vector,vlen);
			do_permutation(vector,0,vlen,store,store_len);
		}
		
		// length shouldn't matter because the vector lengths should be the same
		do_store_compare(store_x,store_y,0,store_x_len,store_y_len,vlen);
		
		
		// print sum
		fprintf(output,"Case #%d: %d\n",case_count, sum);
		
		// free up allocated store memory
		do_free(store_x, &store_x_len);
		do_free(store_y, &store_y_len);
		
		// reset for next case
		sum 	  	= 0;
		store_x_len = 0;
		store_y_len = 0;
		tally_sum 	= false;	
		case_count++;
	}
	fclose(input);
	fclose(output);
	
	return 0;
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

void do_store_compare(int **store_x, int **store_y, int store_index, int store_x_max, int store_y_max, int vector_len)
{
	// base case
	if(store_index == store_x_max)
		return;
	
	// recurse x only
	do_store_compare(store_x,store_y,store_index + 1,store_x_max, store_y_max, vector_len);
	
	// pull x out
	int *vector_x = store_x[store_index];
	
	// compare to Y's element
	int element = 0;
	for(element = 0;element<store_y_max;element++)
	{		
		int *vector_y = store_y[element];
		do_vector_math(vector_x,vector_y,vector_len);
	}

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

void do_free(int **store, int *store_len)
{
	int len = *store_len;
	
	// be nice, free each of the allocated vectors in do_store
	for(int i=0;i<len;i++)
	{
		int *vector = store[i];
		free(vector);	
	}
	// free the store right after
	free(store);
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

void do_permutation(int *vector, int index, int max, int **store, int *store_count)
{
	// print the permutated vector
	if(index == max)
	{
		do_store(vector, max, store, store_count);		
		//do_print(vector, max); 
		//printf("\n");
		return;
	}
	// recurse
	do_permutation(vector, index + 1, max, store, store_count);
	
	// swap each iteration, doing a permutation of each
	int element;
	for(element = index + 1; element < max; element++)
	{
		// don't permute if the values are equal
		if(vector[index] == vector[element])
			continue;
		
		// swap
		do_swap(vector,index,element);
		// recurse
		do_permutation(vector,index + 1, max, store, store_count);
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

void do_store(int *vector, int len,int **store, int *store_count)
{	
	// create heap space for new 
	int *n = malloc(sizeof(int) * len);
	
	// copy array to n
	memcpy(n,vector,sizeof(int) * len);
	
	int temp_store_count = *store_count;
	// store vector
	store[temp_store_count] = n;
	
	// increase  count
	*store_count = temp_store_count + 1;
}

