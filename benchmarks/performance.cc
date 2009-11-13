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
#include "ctimer.h"

#include "fann.h"

#ifndef FIXEDFANN

#ifdef JNEURAL
#include "nets/backprop.h"
#endif

#ifdef LWNN
#include "lwneuralnet.h"
#endif

#ifdef JNEURAL
void performance_benchmark_jneural(FILE * out, fann_type * input,
								   unsigned int num_neurons, unsigned int seconds_per_test)
{
	unsigned int i, total_connections;
	fann_type *output;

	backprop *ann = new backprop(0.7, num_neurons, num_neurons, 2, num_neurons, num_neurons);

	total_connections = (num_neurons + 1) * num_neurons * 3;

	start_timer();

	for(i = 0; time_elapsed() < (double) seconds_per_test; i++)
	{
		ann->set_input(input);
		output = ann->query_output();
	}

	stop_timer();

	fprintf(out, "%d %.20e\n", num_neurons, getNanoPerN(i) / total_connections);
	fprintf(stderr, "%d ", num_neurons);

	delete ann;
}
#endif

#ifdef LWNN
void performance_benchmark_lwnn(FILE * out, fann_type * input,
								unsigned int num_neurons, unsigned int seconds_per_test)
{
	unsigned int i, total_connections;
	fann_type *output;

	output = (fann_type *) calloc(num_neurons, sizeof(fann_type));
	network_t *ann = net_allocate(4, num_neurons, num_neurons, num_neurons, num_neurons);

	total_connections = num_neurons * num_neurons * 3;

	start_timer();

	for(i = 0; time_elapsed() < (double) seconds_per_test; i++)
	{
		net_compute(ann, input, output);
	}

	stop_timer();

	fprintf(out, "%d %.20e\n", num_neurons, getNanoPerN(i) / total_connections);
	fprintf(stderr, "%d ", num_neurons);

	net_free(ann);
	free(output);
}
#endif

void performance_benchmark_fann_noopt(FILE * out, fann_type * input,
									  unsigned int num_neurons, unsigned int seconds_per_test)
{
	unsigned int i, total_connections;
	fann_type *output;

	struct fann *ann = fann_create_standard(4,
								   num_neurons, num_neurons, num_neurons, num_neurons);

	//just to fool the optimizer into thinking that the network is not fully connected
	ann->connection_rate = 0.9;

	total_connections = (num_neurons + 1) * num_neurons * 3;

	start_timer();

	for(i = 0; time_elapsed() < (double) seconds_per_test; i++)
	{
		output = fann_run(ann, input);
	}

	stop_timer();

	fprintf(out, "%d %.20e\n", num_neurons, getNanoPerN(i) / total_connections);
	fprintf(stderr, "%d ", num_neurons);
	fann_destroy(ann);
}

void performance_benchmark_fann_thres(FILE * out, fann_type * input,
									  unsigned int num_neurons, unsigned int seconds_per_test)
{
	unsigned int i, total_connections;
	fann_type *output;

	struct fann *ann = fann_create_standard(4,
								   num_neurons, num_neurons, num_neurons, num_neurons);

	fann_set_activation_function_hidden(ann, FANN_THRESHOLD);
	fann_set_activation_function_output(ann, FANN_THRESHOLD);

	total_connections = (num_neurons + 1) * num_neurons * 3;

	start_timer();

	for(i = 0; time_elapsed() < (double) seconds_per_test; i++)
	{
		output = fann_run(ann, input);
	}

	stop_timer();

	fprintf(out, "%d %.20e\n", num_neurons, getNanoPerN(i) / total_connections);
	fprintf(stderr, "%d ", num_neurons);
	fann_destroy(ann);
}

#endif

void performance_benchmark_fann(bool stepwise, FILE * out, fann_type * input,
								unsigned int num_neurons, unsigned int seconds_per_test)
{
	unsigned int i, total_connections;
	fann_type *output;

	struct fann *ann = fann_create_standard(4,
								   num_neurons, num_neurons, num_neurons, num_neurons);

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

	total_connections = (num_neurons + 1) * num_neurons * 3;

	start_timer();

	for(i = 0; time_elapsed() < (double) seconds_per_test; i++)
	{
		output = fann_run(ann, input);
	}

	stop_timer();

	fprintf(out, "%d %.20e\n", num_neurons, getNanoPerN(i) / total_connections);
	fprintf(stderr, "%d ", num_neurons);
	fann_destroy(ann);
}

int main(int argc, char *argv[])
{
	/* parameters */
	unsigned int num_neurons_first;
	unsigned int num_neurons_last;
	double multiplier;
	unsigned int seconds_per_test;
	FILE *out;

	fann_type *input;
	unsigned int num_neurons, i;

	if(argc != 7)
	{
		printf
			("usage %s net file_out num_neurons_first num_neurons_last multiplier seconds_per_test\n",
			 argv[0]);
		return -1;
	}

	calibrate_timer();

	num_neurons_first = atoi(argv[3]);
	num_neurons_last = atoi(argv[4]);
	multiplier = atof(argv[5]);
	seconds_per_test = atoi(argv[6]);

	if(strlen(argv[2]) == 1 && argv[2][0] == '-')
	{
		out = stdout;
	}
	else
	{
		out = fopen(argv[2], "w");
	}

	fprintf(stderr, "Performance test of %s %s ", argv[1], argv[2]);

	input = (fann_type *) calloc(num_neurons_last, sizeof(fann_type));
	for(i = 0; i < num_neurons_last; i++)
	{
		input[i] = fann_random_weight();	//fill input with random variables
	}

	for(num_neurons = num_neurons_first;
		num_neurons <= num_neurons_last; num_neurons = (int) (num_neurons * multiplier))
	{

#ifndef FIXEDFANN
		if(strcmp(argv[1], "fann") == 0)
		{
#endif
			performance_benchmark_fann(false, out, input, num_neurons, seconds_per_test);
#ifndef FIXEDFANN
		}
		else if(strcmp(argv[1], "fann_noopt") == 0)
		{
			performance_benchmark_fann_noopt(out, input, num_neurons, seconds_per_test);
		}
		else if(strcmp(argv[1], "fann_stepwise") == 0)
		{
			performance_benchmark_fann(true, out, input, num_neurons, seconds_per_test);
		}
		else if(strcmp(argv[1], "fann_thres") == 0)
		{
			performance_benchmark_fann_thres(out, input, num_neurons, seconds_per_test);
#ifdef LWNN
		}
		else if(strcmp(argv[1], "lwnn") == 0)
		{
			performance_benchmark_lwnn(out, input, num_neurons, seconds_per_test);
#endif
#ifdef JNEURAL
		}
		else if(strcmp(argv[1], "jneural") == 0)
		{
			performance_benchmark_jneural(out, input, num_neurons, seconds_per_test);
#endif
		}
		else
		{
			printf("unrecognized option %s\n", argv[1]);
		}
#endif

	}

	fprintf(stderr, "\n");
	free(input);

	return 0;
}
