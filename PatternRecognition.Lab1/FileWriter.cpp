#include "FileWriter.h"

bool FileWriter::WriteMatrix(const std::string & nameOfFile, const std::vector<std::vector<double>> & matrix, bool append) const
{
	std::ofstream fout;
	try
	{
		if (append)
			fout.open(nameOfFile, std::fstream::app);
		else
			fout.open(nameOfFile, std::fstream::trunc);

		bool success = WriteMatrix(fout, matrix);

		fout.close();

		return success;
	}
	catch(const std::exception &)
	{
		if (fout.is_open())
			fout.close();

		return false;
	}
}

bool FileWriter::WriteMatrix(std::ofstream & fout, const std::vector<std::vector<double>> & matrix) const
{
	try
	{
		if (!fout)
			return false;

		int numOfRows = matrix.size();
		fout.precision(10);

		for (int i = 0; i < numOfRows; ++i)
		{
			int numOfColumns = matrix[i].size();
			
			for (int j = 0; j < numOfColumns; ++j)
			{
				fout.width(15);
				fout << std::right << matrix[i][j];
			}
			
			if (i != numOfRows - 1)
				fout<< std::endl;
		}
		return true;
	}
	catch(const std::exception &)
	{
		return false;
	}
}

bool FileWriter::WriteText(const std::string & nameOfFile, const std::string & text, bool append) const
{
	return Write(nameOfFile, text, append);
}

bool FileWriter::WriteText(std::ofstream & fout, const std::string & text) const
{
	return Write(fout, text);
}

bool FileWriter::WriteNumber(std::ofstream & fout, const int & number) const
{
	return Write(fout, number);
}

bool FileWriter::WriteNumber(std::ofstream & fout, const double & number) const
{
	return Write(fout, number);
}

bool FileWriter::WriteNumber(std::ofstream & fout, const float & number) const
{
	return Write(fout, number);
}

bool FileWriter::WriteNumber(const std::string & nameOfFile, const int & number, bool append) const
{
	return Write(nameOfFile, number, append);
}

bool FileWriter::WriteNumber(const std::string & nameOfFile, const double & number, bool append) const
{
	return Write(nameOfFile, number, append);
}

bool FileWriter::WriteNumber(const std::string & nameOfFile, const float & number, bool append) const
{
	return Write(nameOfFile, number, append);
}

template<class T>
bool FileWriter::Write(std::ofstream & fout, const T & text) const
{
	try
	{
		if (!fout)
			return false;

		fout << text;

		return true;
	}
	catch(const std::exception &)
	{
		return false;
	}
}

template<class T>
bool FileWriter::Write(const std::string & nameOfFile, const T & text, bool append) const
{
	std::ofstream fout;
	try
	{
		if (append)
			fout.open(nameOfFile, std::fstream::app);
		else
			fout.open(nameOfFile, std::fstream::trunc);

		bool success = Write(fout, text);

		fout.close();

		return success;
	}
	catch(const std::exception &)
	{
		if (fout.is_open())
			fout.close();

		return false;
	}
}