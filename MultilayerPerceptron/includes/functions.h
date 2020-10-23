#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <string>
#include "NeuralNetwork.h"

namespace nn = vyn::neuralnetwork;

void									EnableDebug(bool newValue);
void									PrintDebug(const char *szFormat, ...);

std::vector<std::vector<nn::value_t>>	ExtractOutputs(std::vector<std::vector<std::string>> dataset);
std::vector<std::vector<nn::value_t>>	ExtractInputs(std::vector<std::vector<std::string>> dataset, std::vector<int> usedColumn);

nn::Network								CreateNeuralNetwork();

std::vector<int>						GetUsedColumn();
void									Train(std::string trainingSetFileName, std::string validationSetFileName);
void									Validate(std::string fileName, std::string modelFileName);

void									SaveCsv(std::stringstream *csv, std::string fileName);
std::vector<std::vector<std::string>>	LoadCsv(std::string csvFileName);

void									SaveScaleDatas(std::vector<nn::scale::ScaleData_t> scaleDatas, std::string fileName);
std::vector<nn::scale::ScaleData_t>		LoadScaleDatas(std::string fileName);

#endif