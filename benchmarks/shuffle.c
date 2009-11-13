#include "fann.h"

int main(int argc, char *argv[])
{
	struct fann_train_data *train, *test, *all;
	unsigned int i, j;
	unsigned int length, half_length;
	
	if(argc == 2)
	{
		train = fann_read_train_from_file(argv[1]);
		fann_shuffle_train_data(train);
		fann_scale_train_data(train, 0, 1);
		fann_save_train(train, argv[1]);
		return 0;
	}
	else if(argc == 3)
	{
		train = fann_read_train_from_file(argv[1]);
		test = fann_read_train_from_file(argv[2]);
		all = fann_merge_train_data(train, test);
		
		fann_shuffle_train_data(all);
		
		for(i = 0; i < train->num_data; i++)
		{
			for(j = 0; j < train->num_input; j++)
			{
				train->input[i][j] = all->input[i][j];
			}
			
			for(j = 0; j < train->num_output; j++)
			{
				train->output[i][j] = all->output[i][j];
			}
		}
		
		for(i = 0; i < test->num_data; i++)
		{
			for(j = 0; j < test->num_input; j++)
			{
				test->input[i][j] = all->input[i + train->num_data][j];
			}
			
			for(j = 0; j < test->num_output; j++)
			{
				test->output[i][j] = all->output[i + train->num_data][j];
			}
		}
		
		fann_save_train(train, argv[1]);
		fann_save_train(test, argv[2]);
	}
	else if(argc == 4)
	{
		all = fann_read_train_from_file(argv[1]);
		fann_shuffle_train_data(all);
		fann_scale_train_data(all, 0, 1);
		length = fann_length_train_data(all);
		half_length = length/2;

		train = fann_subset_train_data(all, 0, half_length);
		test = fann_subset_train_data(all, half_length, length-half_length);		

		fann_save_train(train, argv[2]);
		fann_save_train(test, argv[3]);
	}
	else
	{
		printf("usage: %s train_file\n", argv[0]);
		printf("will shuffle the data in the file.\n");
		printf("usage: %s train_file test_file\n", argv[0]);
		printf("will shuffle the data in the two files and save the new data back to them.\n");
		printf("usage: %s input_file train_file test_file\n", argv[0]);
		printf("will shuffle the data in the input_file, and split it in two files and save the new data back to them.\n\n");
		return -1;
	}
	
	
	return 0;
}
