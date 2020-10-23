/*
* @Author: Vyn
* @Date:   2019-03-12 12:11:21
* @Last Modified by:   Vyn
* @Last Modified time: 2019-03-16 18:43:06
*/

#include "functions.h"
#include <iterator>

void	SaveCsv(std::stringstream *csv, std::string fileName)
{
	std::ofstream file;
	file.open(fileName);
	file << csv->str();
	file.close();
}

std::vector<std::vector<std::string>>	LoadCsv(std::string csvFileName)
{
	int		nbLine = 0;
	int		nbColumn = -1;
	int		tmpNbColumn;

	PrintDebug("Loading Csv file: %s\n", csvFileName.c_str());
	std::vector<std::vector<std::string>>	csv;
	std::string	line;
	std::ifstream file(csvFileName);
	while (file.eof() == false)
	{
		std::getline(file, line);
		if (line.length() > 0)
		{
			++nbLine;
			std::vector<std::string>	csvLine;
			std::string	element;
			std::istringstream elements(line);

			tmpNbColumn = 0;
			while (elements.eof() == false)
			{
				++tmpNbColumn;
				std::getline(elements, element, ',');
				csvLine.push_back(element);
			}
			if (nbColumn == -1)
				nbColumn = tmpNbColumn;
			else if (nbColumn != tmpNbColumn)
				throw std::string("CSV: Not the same number of columns");
			csv.push_back(csvLine);
		}
	}
	PrintDebug("Csv file: %d line(s) of %d column(s)\n", nbLine, nbColumn);
	file.close();
	return (csv);
}