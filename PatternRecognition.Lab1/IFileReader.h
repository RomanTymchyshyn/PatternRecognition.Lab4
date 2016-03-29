#pragma once

#include <vector>
#include <string>

class IFileReader
{
	public:
		//dummyFile param just for indicating if useless number in each file with matrix is present
		virtual bool ReadMatrix(std::vector<std::vector<double>> & result, const std::string & nameOfFile = "", const int & rows = -1, const int & cols = 15, const bool & dummyFile = true) const = 0;
};