/*
* @Author: Vyn
* @Date:   2019-03-13 13:15:18
* @Last Modified by:   Vyn
* @Last Modified time: 2019-03-13 13:16:35
*/

#include "functions.h"

std::vector<std::vector<nn::value_t>>	ExtractOutputs(std::vector<std::vector<std::string>> dataset)
{
	std::vector<std::vector<nn::value_t>>	outputs;

	for (int i = 0; i < dataset.size(); ++i)
	{
		std::vector<nn::value_t>	output;

		if (dataset[i][1] == "B")
		{
			output.push_back(1);
			output.push_back(0);
		}
		else if (dataset[i][1] == "M")
		{
			output.push_back(0);
			output.push_back(1);
		}
		outputs.push_back(output);
	}
	return (outputs);
}

std::vector<std::vector<nn::value_t>>	ExtractInputs(std::vector<std::vector<std::string>> dataset, std::vector<int> usedColumn)
{
	std::vector<std::vector<nn::value_t>>	inputs;

	for (int i = 0; i < dataset.size(); ++i)
	{
		std::vector<nn::value_t>	input;

		for (int j = 0; j < usedColumn.size(); ++j)
		{
			input.push_back(std::stod(dataset[i][usedColumn[j]]));
		}
		inputs.push_back(input);
	}
	return (inputs);
}