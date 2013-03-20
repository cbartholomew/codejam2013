#include <stdio.h>
#include <stdbool.h>

int main(int arc, char** argv)
{
	FILE *input_file;
	FILE *output_file;
	
	input_file = fopen(argv[1], "r");	
	output_file = fopen("output.txt", "w+");
	
	if(input_file == NULL)
		return 1;
	
	if(output_file == NULL)
		return 1;
		
	// init the total cases
	int total_cases = -1;
	
	// get total cases (first line)
	fscanf(input_file,"%d",&total_cases);
	
	// run through the total cases
	for(int c = 0; c<total_cases; c++)
	{
		// set case and credit size
		int case_credit = -1;	
		int case_size 	= -1;
		
		// get the case credit and size
		fscanf(input_file,"%d",&case_credit);
		fscanf(input_file,"%d",&case_size);
		
		// init array size of the case based on input
		int n[case_size];
		
		// populate the array
		for(int p=0;p<case_size;p++)
			fscanf(input_file,"%d",&n[p]);
		
		// set initial positions
		int pos1 = 0;
		int pos2 = 0;
		
		// find the sum within positions
		for(int i=0;i<case_size;i++)
		{
		    bool correct_sum = false;
			for(int j=0;j<case_size;j++)
			{
				bool correct_sum = ((n[i] + n[j]) == case_credit) ? true : false;
				
				// There's only one copy of each item in the store; therefore, you can't purchase the same time
				if(i != j) 
				{
					if(correct_sum)
					{
						// adjust the position to accomidate for zero index
						pos1 = i + 1;
						pos2 = j + 1;
						break;
					}
				}
			}
			if(correct_sum)
				break;
		}
		
		// swap position based on the lowest position
		if(pos1 < pos2)
			fprintf(output_file,"Case #%d: %d %d\n",(c + 1),pos1, pos2);
		else
			fprintf(output_file,"Case #%d: %d %d\n",(c + 1),pos2, pos1);
		
	}
    
    // close file
	fclose(input_file);
	fclose(output_file);
	
	return 0;
	
}
