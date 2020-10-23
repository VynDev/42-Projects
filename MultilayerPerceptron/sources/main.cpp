/*
* @Author: Vyn
* @Date:   2019-02-01 12:36:17
* @Last Modified by:   Vyn
* @Last Modified time: 2019-03-25 14:43:42
*/

#include "functions.h"
#include <iterator>

std::vector<int>	GetUsedColumn()
{
	std::vector<int> usedColumn;

	usedColumn.push_back(2);
	usedColumn.push_back(3);
	usedColumn.push_back(4);
	usedColumn.push_back(5);
	usedColumn.push_back(6);
	usedColumn.push_back(8);
	usedColumn.push_back(9);
	usedColumn.push_back(22);
	usedColumn.push_back(26);

	return (usedColumn);
}

int		main(int argc, char **argv)
{
	int				mode = 0;
	std::string		trainingSetFileName;
	std::string		validationSetFileName;
	std::string		modelFileName = "";

	srand (time(NULL));
	EnableDebug(true);

	for (int i = 1; i < argc; ++i)
	{
		if (std::string(argv[i]) == "--train")
		{
			if (i + 1 < argc)
			{
				mode = 1;
				trainingSetFileName = argv[i + 1];
				++i;
			}
			if (i + 1 < argc)
			{
				mode = 1;
				validationSetFileName = argv[i + 1];
				++i;
			}
			else
			{
				std::cout << "Missing file after '--train' (syntax is --train [TRAINING SET] [VALDIATION SET]" << std::endl;
				return (0);
			}
		}
		if (std::string(argv[i]) == "--validate")
		{
			if (i + 1 < argc)
			{
				mode = 2;
				validationSetFileName = argv[i + 1];
				++i;
			}
			else
			{
				std::cout << "Missing file after '--validate'" << std::endl;
				return (0);
			}
		}
		if (std::string(argv[i]) == "--model")
		{
			if (i + 1 < argc)
			{
				modelFileName = argv[i + 1];
				++i;
			}
			else
			{
				std::cout << "Missing file after '--model'" << std::endl;
				return (0);
			}
		}
	}
	if (mode == 0)
	{
		std::cout << "Usage:\n" << argv[0] << " [--train FILE][--validate FILE]" << std::endl;
		return (0);
	}
	try
	{
		if (mode == 1)
		{
			Train(trainingSetFileName, validationSetFileName);
		}
		if (mode == 2)
		{
			if (modelFileName == "")
			{
				std::cout << "Please provide a model with --model FILE" << std::endl;
				return (0);
			}
			Validate(validationSetFileName, modelFileName);
		}
	}
	catch (std::string const &e)
	{
		std::cout << std::endl << "[Error] " << e << std::endl;
		return (1);
	}
	return (0);
}