/*
* @Author: Vyn
* @Date:   2019-03-22 12:42:38
* @Last Modified by:   Vyn
* @Last Modified time: 2019-03-22 13:08:51
*/

#include "functions.h"
#include <iterator>

void								SaveScaleDatas(std::vector<nn::scale::ScaleData_t> scaleDatas, std::string fileName)
{
	std::ofstream file;
	file.open(fileName);
	for (int i = 0; i < scaleDatas.size(); ++i)
	{
		file << scaleDatas[i].min << " " << scaleDatas[i].max << " " << scaleDatas[i].mean << std::endl;
	}
	file.close();
}

std::vector<nn::scale::ScaleData_t>	LoadScaleDatas(std::string fileName)
{
	std::vector<nn::scale::ScaleData_t>		scaleDatas;
	int										nbLine = 0;

	PrintDebug("Loading Scale data file: %s\n", fileName.c_str());
	std::string	line;
	std::ifstream file(fileName);
	while (file.eof() == false)
	{
		std::getline(file, line);
		if (line.length() > 0)
		{
			nn::scale::ScaleData_t	scaleData;
			std::string				element;
			std::istringstream 		elements(line);

			std::getline(elements, element, ' ');
			scaleData.min = std::stod(element);
			std::getline(elements, element, ' ');
			scaleData.max = std::stod(element);
			std::getline(elements, element, ' ');
			scaleData.mean = std::stod(element);

			++nbLine;
			
			scaleDatas.push_back(scaleData);
		}
	}
	file.close();
	return (scaleDatas);
}