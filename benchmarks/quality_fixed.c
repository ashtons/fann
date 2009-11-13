/*
Fast Artificial Neural Network Library (fann)
Copyright (C) 2003 Steffen Nissen (lukesky@diku.dk)

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <stdio.h>
#include <string.h>
#include "fixedfann.h"

int main(int argc, char *argv[])
{
	struct fann_train_data *train_data, *test_data;
	FILE *train_out, *test_out;
	struct fann *ann;
	float train_error, test_error;
	unsigned int j;
	unsigned int epochs = 0;
	double total_elapsed = 0;
	char file[256];

	if(argc < 6)
	{
		printf("usage %s train_file test_file train_file_out test_file_out fixed_conf_files\n",
			   argv[0]);
		return -1;
	}

	if(strlen(argv[3]) == 1 && argv[3][0] == '-')
	{
		train_out = stdout;
	}
	else
	{
		train_out = fopen(argv[3], "w");
	}

	if(strlen(argv[4]) == 1 && argv[4][0] == '-')
	{
		test_out = stdout;
	}
	else
	{
		test_out = fopen(argv[4], "w");
	}

	fprintf(stderr, "Quality test of fixed point ");

	for(j = 5; j < argc; j++)
	{
		ann = fann_create_from_file(argv[j]);

		sprintf(file, "%s_%d", argv[1], fann_get_decimal_point(ann));
		train_data = fann_read_train_from_file(file);
		train_error = fann_test_data(ann, train_data);
		fann_destroy_train(train_data);

		sprintf(file, "%s_%d", argv[2], fann_get_decimal_point(ann));
		test_data = fann_read_train_from_file(file);
		test_error = fann_test_data(ann, test_data);
		fann_destroy_train(test_data);

		sscanf(argv[j], "%d_%lf", &epochs, &total_elapsed);
		fprintf(train_out, "%f %.20e %d\n", total_elapsed, train_error, epochs);
		fprintf(test_out, "%f %.20e %d\n", total_elapsed, test_error, epochs);
		fprintf(stderr, ".");

		fann_destroy(ann);
	}

	fprintf(stderr, "\n");

	return 0;
}
