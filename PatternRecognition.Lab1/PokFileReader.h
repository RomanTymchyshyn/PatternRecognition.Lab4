#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "IFileReader.h"

class PokFileReader: public IFileReader
{
	public:
		//dummyFile param just for indicating if useless number in each file with matrix is present
		//if rows == -1 then row number will be read from file
		virtual bool ReadMatrix(std::vector<std::vector<double>> & result, const std::string & nameOfFile = "", const int & rows = -1, const int & cols = 15, const bool & dummyFile = true) const;
};