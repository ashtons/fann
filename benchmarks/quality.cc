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

//uncomment lines below to benchmark the libraries

#define JNEURAL
#define LWNN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef JNEURAL
#include "nets/backprop.h"
#endif

#ifdef LWNN
#include "lwneuralnet.h"
#endif

#include "ctimer.h"
#include "floatfann.h"
#include "benchdata.h"

unsigned int num_errors = 0;
unsigned int num_bit_fail = 0;
double error_value = 0;

BenchDataCollector *train_collector = new BenchDataCollector();
BenchDataCollector *test_collector = new BenchDataCollector();

void clear_error()
{
	num_errors = 0;
	error_value = 0;
	num_bit_fail = 0;
}

void update_error(fann_type * output, fann_type * desired_output, unsigned int num_output)
{
	unsigned int i = 0;
	double error_val = 0;

	/* calculate the error */
	for(i = 0; i < num_output; i++)
	{
		error_val = (desired_output[i] - output[i]) * (desired_output[i] - output[i]);
		error_value += error_val;

		if(error_val >= 0.25)
		{
			num_bit_fail++;
		}

		num_errors++;
	}
}

double mean_error()
{
	return error_value / (double) num_errors;
}

double mean_bit_fail()
{
	return num_bit_fail / (double) num_errors;
}

void report_error(double time, unsigned int epochs, FILE * out, BenchDataCollector *collector, unsigned int numNeurons)
{
	BenchData *data = new BenchData(time, epochs, mean_error(), num_bit_fail, mean_bit_fail(), numNeurons);
	data->printBench(out);
	collector->addBench(data);
}


#ifdef JNEURAL
void quality_benchmark_jneural(struct fann_train_data *train_data,
							   struct fann_train_data *test_data,
							   FILE * train_out, FILE * test_out,
							   unsigned int num_input, unsigned int num_neurons_hidden1,
							   unsigned int num_neurons_hidden2, unsigned int num_output,
							   unsigned int seconds_of_training, double seconds_between_reports)
{
	float train_error, test_error;
	unsigned int i, train_bit_fail, test_bit_fail;
	unsigned int epochs = 0;
	double elapsed = 0;
	double total_elapsed = 0;
	fann_type *output;
	struct backprop *ann;

	if(num_neurons_hidden2)
	{
		ann = new backprop(0.7, num_input, num_output, 2, num_neurons_hidden1, num_neurons_hidden2);
	}
	else
	{
		ann = new backprop(0.7, num_input, num_output, 1, num_neurons_hidden1);
	}

	calibrate_timer();

	while(total_elapsed < (double) seconds_of_training)
	{
		/* train */
		elapsed = 0;
		start_timer();
		while(elapsed < (double) seconds_between_reports)
		{
			for(i = 0; i != train_data->num_data; i++)
			{
				ann->set_input(train_data->input[i]);
				ann->train_on(train_data->output[i]);
			}

			elapsed = time_elapsed();
			epochs++;
		}
		stop_timer();
		total_elapsed += getSecs();

		/* make report */
		clear_error();
		for(i = 0; i != train_data->num_data; i++)
		{
			ann->set_input(train_data->input[i]);
			output = ann->query_output();
			update_error(output, train_data->output[i], train_data->num_output);
		}
		train_error = mean_error();
		train_bit_fail = num_bit_fail;
		
		report_error(total_elapsed, epochs, train_out, train_collector, num_neurons_hidden1+num_neurons_hidden2);

		clear_error();
		for(i = 0; i != test_data->num_data; i++)
		{
			ann->set_input(test_data->input[i]);
			output = ann->query_output();
			update_error(output, test_data->output[i], test_data->num_output);
		}
		test_error = mean_error();
		test_bit_fail = num_bit_fail;

		report_error(total_elapsed, epochs, test_out, test_collector, num_neurons_hidden1+num_neurons_hidden2);

		fprintf(stderr, "secs: %8.2f, train: %8.6f (%4d), test: %8.6f (%4d), epochs: %5d\r",
				total_elapsed, train_error, train_bit_fail, test_error, test_bit_fail, epochs);
	}

	fprintf(stdout, "\nepochs: %d, epochs/sec: %f\n", epochs, epochs / total_elapsed);

	delete ann;
}
#endif

void quality_benchmark_fann(bool stepwise, fann_train_enum training_algorithm,
							char *filename,
							struct fann_train_data *train_data,
							struct fann_train_data *test_data,
							FILE * train_out, FILE * test_out,
							unsigned int num_input, unsigned int num_neurons_hidden1,
							unsigned int num_neurons_hidden2, unsigned int num_output,
							unsigned int seconds_of_training, double seconds_between_reports, 
							float momentum = 0)
{
	float train_error, test_error;
	unsigned int i, decimal_point, j, train_bit_fail, test_bit_fail;
	unsigned int epochs = 0;
	double elapsed = 0;
	double total_elapsed = 0;
	fann_type *output;
	struct fann *ann;
	char fixed_point_file[256];

	if(num_neurons_hidden2)
	{
		ann = fann_create_standard(4,
						  num_input, num_neurons_hidden1, num_neurons_hidden2, num_output);
	}
	else
	{
		ann = fann_create_standard(3, num_input, num_neurons_hidden1, num_output);
	}

	fann_set_training_algorithm(ann, training_algorithm);
	fann_set_learning_momentum(ann, momentum);

	if(stepwise)
	{
		fann_set_activation_function_hidden(ann, FANN_SIGMOID_STEPWISE);
		fann_set_activation_function_output(ann, FANN_SIGMOID_STEPWISE);
	}
	else
	{
		fann_set_activation_function_hidden(ann, FANN_SIGMOID);
		fann_set_activation_function_output(ann, FANN_SIGMOID);
	}

	if(training_algorithm == FANN_TRAIN_INCREMENTAL || training_algorithm == FANN_TRAIN_QUICKPROP)
	{
		fann_set_train_error_function(ann, FANN_ERRORFUNC_LINEAR);
	}

	calibrate_timer();

	while(total_elapsed < (double) seconds_of_training)
	{
		/* train */
		elapsed = 0;
		start_timer();
		while(elapsed < (double) seconds_between_reports)
		{
			fann_train_epoch(ann, train_data);

			elapsed = time_elapsed();
			epochs++;
		}
		stop_timer();
		total_elapsed += getSecs();

		/* make report */
		clear_error();
		for(i = 0; i != test_data->num_data; i++)
		{
			output = fann_run(ann, test_data->input[i]);
			update_error(output, test_data->output[i], test_data->num_output);
		}
		test_error = mean_error();
		test_bit_fail = num_bit_fail;

		report_error(total_elapsed, epochs, test_out, test_collector, num_neurons_hidden1+num_neurons_hidden2);

		clear_error();
		for(i = 0; i != train_data->num_data; i++)
		{
			output = fann_run(ann, train_data->input[i]);
			update_error(output, train_data->output[i], train_data->num_output);
		}
		train_error = mean_error();
		train_bit_fail = num_bit_fail;

		report_error(total_elapsed, epochs, train_out, train_collector, num_neurons_hidden1+num_neurons_hidden2);
	
		fprintf(stderr, "secs: %8.2f, train: %8.6f (%4d), test: %8.6f (%4d), epochs: %5d\r",
				total_elapsed, train_error, train_bit_fail, test_error, test_bit_fail, epochs);

		/* Save the data as fixed point, to allow for drawing of
		 * a fixed point graph */
		if(filename)
		{
			/* buffer overflow could occur here */
			sprintf(fixed_point_file, "%08d_%f_%s_fixed.net", epochs, total_elapsed, filename);
			decimal_point = fann_save_to_fixed(ann, fixed_point_file);

			sprintf(fixed_point_file, "%s_fixed_train_%d", filename, decimal_point);
			fann_save_train_to_fixed(train_data, fixed_point_file, decimal_point);

			sprintf(fixed_point_file, "%s_fixed_test_%d", filename, decimal_point);
			fann_save_train_to_fixed(test_data, fixed_point_file, decimal_point);
		}
	}

	fprintf(stdout, "\nepochs: %d, epochs/sec: %f\n", epochs, epochs / total_elapsed);

	fann_destroy(ann);
}

void quality_benchmark_cascade(struct fann_train_data *train_data,
							   struct fann_train_data *test_data,
							   FILE * train_out, FILE * test_out,
							   unsigned int num_input, unsigned int num_output,
							   unsigned int seconds_of_training, double seconds_between_reports, 
							   enum fann_train_enum train_function, bool multi)
{
	float train_error = 0;
	float test_error = 0;
	unsigned int i, train_bit_fail, test_bit_fail;
	unsigned int epochs = 0;
	double elapsed = 0;
	double total_elapsed = 0;
	fann_type *output;
	struct fann *ann;

	ann = fann_create_shortcut(2, num_input, num_output);

	fann_set_training_algorithm(ann, train_function);
	fann_set_activation_function_hidden(ann, FANN_SIGMOID_SYMMETRIC);
	fann_set_activation_function_output(ann, FANN_LINEAR);
	fann_set_train_error_function(ann, FANN_ERRORFUNC_LINEAR);

	if(!multi)
	{
		fann_type steepness = 0.5;
		fann_set_cascade_activation_steepnesses(ann, &steepness, 1);
		fann_activationfunc_enum activation = FANN_SIGMOID;
		fann_set_cascade_activation_functions(ann, &activation, 1);
		
		fann_set_cascade_num_candidate_groups(ann, 8);
	}

/*
	fann_set_activation_steepness_hidden(ann, 0.5);
	fann_set_activation_steepness_output(ann, 0.5);

	fann_set_rprop_increase_factor(ann, 1.2);
	fann_set_rprop_decrease_factor(ann, 0.5);
	fann_set_rprop_delta_min(ann, 0.0);
	fann_set_rprop_delta_max(ann, 50.0);

	fann_set_cascade_weight_multiplier(ann, 0.4);
 	fann_set_cascade_candidate_limit(ann, 1000.0);
	fann_set_cascade_max_out_epochs(ann, 150);
	fann_set_cascade_max_cand_epochs(ann, 150);
*/

	calibrate_timer();

	while(total_elapsed < (double) seconds_of_training)
	{
		/* Train with FANN_LINEAR */
		fann_set_activation_function_output(ann, FANN_LINEAR);
		/* train */
		elapsed = 0;
		start_timer();
		while(elapsed < (double) seconds_between_reports)
		{
			epochs += fann_train_outputs(ann, train_data, 0);

			if(fann_initialize_candidates(ann) == -1)
				break;
	
			epochs += fann_train_candidates(ann, train_data);

			fann_install_candidate(ann);

			elapsed = time_elapsed();
		}
		stop_timer();
		total_elapsed += getSecs();

		/* make report */
		/* But test with FANN_LINEAR_PIECE */
		fann_set_activation_function_output(ann, FANN_LINEAR_PIECE);
		clear_error();
		for(i = 0; i != test_data->num_data; i++)
		{
			output = fann_run(ann, test_data->input[i]);
			update_error(output, test_data->output[i], test_data->num_output);
		}
		test_error = mean_error();
		test_bit_fail = num_bit_fail;
		
		report_error(total_elapsed, epochs, test_out, test_collector, ann->total_neurons-ann->num_input-ann->num_output);

		clear_error();
		for(i = 0; i != train_data->num_data; i++)
		{
			output = fann_run(ann, train_data->input[i]);
			update_error(output, train_data->output[i], train_data->num_output);
		}
		train_error = mean_error();
		train_bit_fail = num_bit_fail;
		
		report_error(total_elapsed, epochs, train_out, train_collector, ann->total_neurons-ann->num_input-ann->num_output);

		fprintf(stderr, "secs: %8.2f, train: %8.6f (%4d), test: %8.6f (%4d), epochs: %5d, neurons: %d\r",
				total_elapsed, train_error, train_bit_fail, test_error, test_bit_fail, epochs, ann->total_neurons-ann->num_input-ann->num_output);
	}

	fprintf(stdout, "\nepochs: %d, epochs/sec: %f\n", epochs, epochs / total_elapsed);
 
	fann_destroy(ann);
}

#ifdef LWNN
void quality_benchmark_lwnn(struct fann_train_data *train_data,
							struct fann_train_data *test_data,
							FILE * train_out, FILE * test_out,
							unsigned int num_input, unsigned int num_neurons_hidden1,
							unsigned int num_neurons_hidden2, unsigned int num_output,
							unsigned int seconds_of_training, double seconds_between_reports)
{
	float train_error = 0;
	float test_error = 0;
	unsigned int i, train_bit_fail, test_bit_fail;
	unsigned int epochs = 0;
	double elapsed = 0;
	double total_elapsed = 0;
	fann_type *output;
	network_t *ann;

	if(num_neurons_hidden2)
	{
		ann = net_allocate(4, num_input, num_neurons_hidden1, num_neurons_hidden2, num_output);
	}
	else
	{
		ann = net_allocate(3, num_input, num_neurons_hidden1, num_output);
	}

	net_set_learning_rate(ann, 0.7);

	calibrate_timer();

	output = (fann_type *) calloc(num_output, sizeof(fann_type));

	while(total_elapsed < (double) seconds_of_training)
	{
		/* train */
		elapsed = 0;
		start_timer();
		while(elapsed < (double) seconds_between_reports)
		{
			for(i = 0; i != train_data->num_data; i++)
			{
				/* compute the outputs for inputs(i) */
				net_compute(ann, train_data->input[i], output);

				/* find the error with respect to targets(i) */
				net_compute_output_error(ann, train_data->output[i]);

				/* train the network one step */
				net_train(ann);
			}

			elapsed = time_elapsed();
			epochs++;
		}
		stop_timer();
		total_elapsed += getSecs();

		/* make report */

		clear_error();
		for(i = 0; i != train_data->num_data; i++)
		{
			net_compute(ann, train_data->input[i], output);
			update_error(output, train_data->output[i], train_data->num_output);
		}
		train_error = mean_error();
		train_bit_fail = num_bit_fail;

		report_error(total_elapsed, epochs, train_out, train_collector, num_neurons_hidden1+num_neurons_hidden2);

		clear_error();
		for(i = 0; i != test_data->num_data; i++)
		{
			net_compute(ann, test_data->input[i], output);
			update_error(output, test_data->output[i], test_data->num_output);
		}
		test_error = mean_error();
		test_bit_fail = num_bit_fail;

		report_error(total_elapsed, epochs, test_out, test_collector, num_neurons_hidden1+num_neurons_hidden2);

		fprintf(stderr, "secs: %8.2f, train: %8.6f (%4d), test: %8.6f (%4d), epochs: %5d\r",
				total_elapsed, train_error, train_bit_fail, test_error, test_bit_fail, epochs);
	}

	fprintf(stdout, "\nepochs: %d, epochs/sec: %f\n", epochs, epochs / total_elapsed);

	net_free(ann);
}
#endif

int main(int argc, char *argv[])
{
	/* parameters */
	char output_file[256];

	if(argc != 11)
	{
		printf
			("usage %s net train_file test_file train_file_out test_file_out num_hidden1 num_hidden2 seconds_of_training seconds_between_reports number_of_runs\n",
			 argv[0]);
		return -1;
	}

	unsigned int num_neurons_hidden1 = atoi(argv[6]);
	unsigned int num_neurons_hidden2 = atoi(argv[7]);
	unsigned int seconds_of_training = atoi(argv[8]);
	double seconds_between_reports = atof(argv[9]);
	unsigned int number_of_runs = atoi(argv[10]);

	fann_train_data *train_data = fann_read_train_from_file(argv[2]);
	fann_train_data *test_data = fann_read_train_from_file(argv[3]);

	char *train_out_file = argv[4];
	char *test_out_file = argv[5];
	FILE *train_out = 0;
	FILE *test_out = 0;

	for(int i = 0; i < number_of_runs; i++)
	{
		test_collector->newCollection();
		train_collector->newCollection();
		
		if(strlen(train_out_file) == 1 && train_out_file[0] == '-')
			train_out = stdout;
		else
		{
			if(number_of_runs == 1)
				train_out = fopen(train_out_file, "w");
			else
			{
				sprintf(output_file, "%s_%d_run", train_out_file, i);
				train_out = fopen(output_file, "w");
			}
		}
	
		if(strlen(test_out_file) == 1 && test_out_file[0] == '-')
			test_out = stdout;
		else
		{
			if(number_of_runs == 1)
				test_out = fopen(test_out_file, "w");
			{
				sprintf(output_file, "%s_%d_run", test_out_file, i);
				test_out = fopen(output_file, "w");
			}
		}

		fprintf(stdout, "Quality test of %s %s\n", argv[1], argv[2]);
	
		if(strcmp(argv[1], "fann_incremental") == 0)
		{
			quality_benchmark_fann(false, FANN_TRAIN_INCREMENTAL, NULL, train_data, test_data,
								   train_out, test_out,
								   train_data->num_input, num_neurons_hidden1,
								   num_neurons_hidden2, train_data->num_output,
								   seconds_of_training, seconds_between_reports);
		}
		else if(strcmp(argv[1], "fann_incremental_stepwise") == 0)
		{
			quality_benchmark_fann(true, FANN_TRAIN_INCREMENTAL, NULL, train_data, test_data,
								   train_out, test_out,
								   train_data->num_input, num_neurons_hidden1,
								   num_neurons_hidden2, train_data->num_output,
								   seconds_of_training, seconds_between_reports);
		}
		else if(strcmp(argv[1], "fann_incremental_momentum") == 0)
		{
			quality_benchmark_fann(false, FANN_TRAIN_INCREMENTAL, NULL, train_data, test_data,
								   train_out, test_out,
								   train_data->num_input, num_neurons_hidden1,
								   num_neurons_hidden2, train_data->num_output,
								   seconds_of_training, seconds_between_reports, 0.4);
		}
		else if(strcmp(argv[1], "fann_quickprop") == 0)
		{
			quality_benchmark_fann(false, FANN_TRAIN_QUICKPROP, NULL, train_data, test_data,
								   train_out, test_out,
								   train_data->num_input, num_neurons_hidden1,
								   num_neurons_hidden2, train_data->num_output,
								   seconds_of_training, seconds_between_reports);
		}
		else if(strcmp(argv[1], "fann_quickprop_stepwise") == 0)
		{
			quality_benchmark_fann(true, FANN_TRAIN_QUICKPROP, NULL, train_data, test_data,
								   train_out, test_out,
								   train_data->num_input, num_neurons_hidden1,
								   num_neurons_hidden2, train_data->num_output,
								   seconds_of_training, seconds_between_reports);
		}
		else if(strcmp(argv[1], "fann_batch") == 0)
		{
			quality_benchmark_fann(false, FANN_TRAIN_BATCH, NULL, train_data, test_data,
								   train_out, test_out,
								   train_data->num_input, num_neurons_hidden1,
								   num_neurons_hidden2, train_data->num_output,
								   seconds_of_training, seconds_between_reports);
		}
		else if(strcmp(argv[1], "fann_batch_stepwise") == 0)
		{
			quality_benchmark_fann(true, FANN_TRAIN_BATCH, NULL, train_data, test_data,
								   train_out, test_out,
								   train_data->num_input, num_neurons_hidden1,
								   num_neurons_hidden2, train_data->num_output,
								   seconds_of_training, seconds_between_reports);
		}
		else if(strcmp(argv[1], "fann_rprop") == 0)
		{
			quality_benchmark_fann(false, FANN_TRAIN_RPROP, NULL, train_data, test_data,
								   train_out, test_out,
								   train_data->num_input, num_neurons_hidden1,
								   num_neurons_hidden2, train_data->num_output,
								   seconds_of_training, seconds_between_reports);
		}
		else if(strcmp(argv[1], "fann_rprop_stepwise") == 0)
		{
			quality_benchmark_fann(true, FANN_TRAIN_RPROP, argv[4], train_data, test_data,
								   train_out, test_out,
								   train_data->num_input, num_neurons_hidden1,
								   num_neurons_hidden2, train_data->num_output,
								   seconds_of_training, seconds_between_reports);
		}
		else if(strcmp(argv[1], "fann_cascade_rprop_one_activation") == 0)
		{
			quality_benchmark_cascade(train_data, test_data,
									  train_out, test_out,
									  train_data->num_input, train_data->num_output,
									  seconds_of_training, seconds_between_reports, FANN_TRAIN_RPROP, false);
		}
		else if(strcmp(argv[1], "fann_cascade_rprop_multi_activation") == 0)
		{
			quality_benchmark_cascade(train_data, test_data,
									  train_out, test_out,
									  train_data->num_input, train_data->num_output,
									  seconds_of_training, seconds_between_reports, FANN_TRAIN_RPROP, true);
		}
		else if(strcmp(argv[1], "fann_cascade_quickprop_one_activation") == 0)
		{
			quality_benchmark_cascade(train_data, test_data,
									  train_out, test_out,
									  train_data->num_input, train_data->num_output,
									  seconds_of_training, seconds_between_reports, FANN_TRAIN_QUICKPROP, false);
		}
		else if(strcmp(argv[1], "fann_cascade_quickprop_multi_activation") == 0)
		{
			quality_benchmark_cascade(train_data, test_data,
									  train_out, test_out,
									  train_data->num_input, train_data->num_output,
									  seconds_of_training, seconds_between_reports, FANN_TRAIN_QUICKPROP, true);
		}
		else if(strcmp(argv[1], "fann_cascade_batch_one_activation") == 0)
		{
			quality_benchmark_cascade(train_data, test_data,
									  train_out, test_out,
									  train_data->num_input, train_data->num_output,
									  seconds_of_training, seconds_between_reports, FANN_TRAIN_BATCH, false);
		}
		else if(strcmp(argv[1], "fann_cascade_batch_multi_activation") == 0)
		{
			quality_benchmark_cascade(train_data, test_data,
									  train_out, test_out,
									  train_data->num_input, train_data->num_output,
									  seconds_of_training, seconds_between_reports, FANN_TRAIN_BATCH, true);
#ifdef LWNN
		}
		else if(strcmp(argv[1], "lwnn") == 0)
		{
			quality_benchmark_lwnn(train_data, test_data,
								   train_out, test_out,
								   train_data->num_input, num_neurons_hidden1,
								   num_neurons_hidden2, train_data->num_output,
								   seconds_of_training, seconds_between_reports);
#endif
	
#ifdef JNEURAL
		}
		else if(strcmp(argv[1], "jneural") == 0)
		{
			quality_benchmark_jneural(train_data, test_data,
									  train_out, test_out,
									  train_data->num_input, num_neurons_hidden1,
									  num_neurons_hidden2, train_data->num_output,
									  seconds_of_training, seconds_between_reports);
#endif
		}
		else
		{
			printf("unrecognized option %s\n", argv[1]);
		}
		
		fclose(train_out);
		fclose(test_out);
	}

	if(strlen(train_out_file) == 1 && train_out_file[0] == '-')
		train_out = stdout;
	else
		train_out = fopen(train_out_file, "w");
	
	if(strlen(test_out_file) == 1 && test_out_file[0] == '-')
		test_out = stdout;
	else
		test_out = fopen(test_out_file, "w");

	train_collector->printAvgCollection(train_out, train_out_file);
	test_collector->printAvgCollection(test_out, test_out_file);
		
	fann_destroy_train(train_data);
	fann_destroy_train(test_data);

	return 0;
}
