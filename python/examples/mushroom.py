#!/usr/bin/python
import os
import sys
from pyfann import libfann

def print_callback(epochs, error):
	print "Epochs     %8d. Current MSE-Error: %.10f\n" % (epochs, error)
	return 0

# initialize network parameters
connection_rate = 1
learning_rate = 0.7
num_neurons_hidden = 32
desired_error = 0.000001
max_iterations = 300
iterations_between_reports = 1

# create training data, and ann object
print "Creating network."	
train_data = libfann.training_data()
train_data.read_train_from_file(os.path.join("..","..","benchmarks","datasets","mushroom.train"))
ann = libfann.neural_net()
ann.create_sparse_array(connection_rate, (len(train_data.get_input()[0]), num_neurons_hidden, len(train_data.get_output()[0])))
ann.set_learning_rate(learning_rate)


# start training the network
print "Training network"
ann.set_activation_function_hidden(libfann.SIGMOID_SYMMETRIC_STEPWISE)
ann.set_activation_function_output(libfann.SIGMOID_STEPWISE)
ann.set_training_algorithm(libfann.TRAIN_INCREMENTAL)
	
ann.train_on_data(train_data, max_iterations, iterations_between_reports, desired_error)
	
# test outcome
print "Testing network"
test_data = libfann.training_data()
test_data.read_train_from_file(os.path.join("..","..","benchmarks","datasets","mushroom.test"))

ann.reset_MSE()
ann.test_data(test_data)
print "MSE error on test data: %f" % ann.get_MSE()


print "Testing network again"
ann.reset_MSE()
input=test_data.get_input()
output=test_data.get_output()
for i in range(len(input)):
    ann.test(input[i], output[i])
print "MSE error on test data: %f" % ann.get_MSE()


# save network to disk
print "Saving network"
ann.save(os.path.join("nets","mushroom_float.net"))

