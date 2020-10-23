/*
* @Author: Vyn
* @Date:   2019-03-17 16:36:01
* @Last Modified by:   Vyn
* @Last Modified time: 2019-03-27 13:43:11
*/

#include "functions.h"
#include <iterator>

void	Train(std::string trainingSetFileName, std::string validationSetFileName)
{
	nn::Network								network;
	nn::TrainingParameters_t				parameters;
	std::vector<std::vector<std::string>>	trainingDataset;
	std::vector<std::vector<std::string>>	validationDataset;

	std::vector<int>						usedColumn;
	std::stringstream 						trainingCsv;
	std::stringstream 						validationCsv;
	std::vector<nn::scale::ScaleData_t>		scaleDatas;

	network = CreateNeuralNetwork();

	usedColumn = GetUsedColumn();

	trainingDataset = LoadCsv(trainingSetFileName);
	parameters.trainingSetInputs = ExtractInputs(trainingDataset, usedColumn);
	parameters.trainingSetOutputs = ExtractOutputs(trainingDataset);
	scaleDatas = nn::scale::MeanNormalisation(parameters.trainingSetInputs);
	parameters.trainingCsv = &trainingCsv;

	validationDataset = LoadCsv(validationSetFileName);
	parameters.validationSetInputs = ExtractInputs(validationDataset, usedColumn);
	parameters.validationSetOutputs = ExtractOutputs(validationDataset);
	nn::scale::MeanNormalisation(parameters.validationSetInputs, scaleDatas);
	parameters.validationCsv = &validationCsv;

	network.Fit(parameters, 1, 5000);
	SaveCsv(&trainingCsv, "training_csv.txt");
	SaveCsv(&validationCsv, "validation_csv.txt");
	SaveScaleDatas(scaleDatas, "scaleDatas.conf");
	network.SaveTo("model.vnn");
}