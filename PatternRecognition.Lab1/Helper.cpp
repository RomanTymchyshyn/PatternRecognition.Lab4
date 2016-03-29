#include "Helper.h"

Helper::Helper(IFileReader* reader, IFileWriter* writer)
{
	_reader = reader;
	_writer = writer;
}

std::vector<Point2D> Helper::ReadPoints(const std::string & nameOfFile)
{
	std::vector<std::vector<double>> data;
	
	_reader->ReadMatrix(data, nameOfFile, -1, 2, false);

	int pointsRead = data.size();
	std::vector<Point2D> result;

	for(int i = 0; i < pointsRead; ++i)
	{
		result.push_back(Point2D(data[i][0], data[i][1]));
	}

	return result;
}