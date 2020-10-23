/*
* @Author: Vyn
* @Date:   2019-03-17 16:36:34
* @Last Modified by:   Vyn
* @Last Modified time: 2019-03-23 20:18:36
*/

#include "functions.h"
#include <iterator>
#include <float.h>

void	Validate(std::string fileName, std::string modelFileName)
{
	nn::Network		network;

	std::vector<std::vector<std::string>>	dataset;
	std::vector<std::vector<nn::value_t>>	dataset_inputs;
	std::vector<std::vector<nn::value_t>>	dataset_outputs;
	std::vector<nn::scale::ScaleData_t>		scaleDatas;
	std::vector<int>						usedColumn;
	std::stringstream 						csv;

	int										total = 0;
	int										good = 0;
	bool									isGood;

	network = nn::Load(modelFileName);

	usedColumn = GetUsedColumn();

	dataset = LoadCsv(fileName);
	dataset_inputs = ExtractInputs(dataset, usedColumn);
	dataset_outputs = ExtractOutputs(dataset);

	scaleDatas = LoadScaleDatas("scaleDatas.conf");
	nn::scale::MeanNormalisation(dataset_inputs, scaleDatas);
	for (int i = 0; i < dataset_inputs.size(); ++i)
	{
		std::vector<nn::value_t>	outputs;
		nn::value_t					cost;

		++total;
		isGood = true;
		outputs = network.Predict(dataset_inputs[i]);
		std::cout << network.GetCost(dataset_outputs[i]) << std::endl;
		for (int j = 0; j < outputs.size(); ++ j)
		{
			int custom = -1;
			if (outputs[j] > 0.5)
				custom = 1;
			else if (outputs[j] < 0.5)
				custom = 0;
			if (custom != dataset_outputs[i][j])
			{
				std::cout << outputs[j] << " vs " << dataset_outputs[i][j] << std::endl;
				isGood = false;
			}
		}
		if (isGood)
			++good;
	}
	std::cout << good << "/" << total << " (" << (double)good/(double)total * 100 << "%) correct(s)" << std::endl;
}