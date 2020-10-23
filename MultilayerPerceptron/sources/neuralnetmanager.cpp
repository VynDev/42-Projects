/*
* @Author: Vyn
* @Date:   2019-03-13 13:20:58
* @Last Modified by:   Vyn
* @Last Modified time: 2019-03-27 14:08:37
*/

#include <iostream>
#include <sstream>
#include <fstream>

#include "functions.h"

nn::Network	CreateNeuralNetwork()
{
	nn::Network		network;

	network.AddLayer(9, NEURON_FUNCTION_SIGMOID, 1); // input
	network.AddLayer(10, NEURON_FUNCTION_SIGMOID, 1);
	network.AddLayer(10, NEURON_FUNCTION_SIGMOID, 1);
	network.AddLayer(10, NEURON_FUNCTION_SIGMOID, 1);
	network.AddLayer(10, NEURON_FUNCTION_SIGMOID, 1);
	network.AddLayer(2, NEURON_FUNCTION_SOFTMAX); // output

	network.SetCostFunction(COST_FUNCTION_CE);
	network.SetLearningRate(0.01);
	network.SetGradientClipping(1);
	network.EnableEarlyStopping(false);
	//network.EnableNormalizedGradient(true);
	//network.SetErrorPropagationLimit(0.1);
	
	return (network);
}