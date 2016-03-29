#pragma once

#include <vector>
#include <string>
#include "IFileReader.h"
#include "IFileWriter.h"
#include "Geometry/Geometry.h"

class Helper
{
	public:

		Helper(IFileReader* reader, IFileWriter* writer);
		
		std::vector<Point2D> ReadPoints(const std::string & nameOfFile);

	private:
		
		IFileReader* _reader;
		
		IFileWriter* _writer;

};