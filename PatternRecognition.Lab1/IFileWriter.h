#pragma once

#include <vector>
#include <string>

class IFileWriter
{
	public:
		
		virtual bool WriteMatrix(const std::string & nameOfFile, const std::vector<std::vector<double>> & matrix, bool append = false) const = 0;
		
		virtual bool WriteText(const std::string & nameOfFile, const std::string & text, bool append = false) const = 0;

		virtual bool WriteMatrix(std::ofstream & fout, const std::vector<std::vector<double>> & matrix) const = 0;
		
		virtual bool WriteText(std::ofstream & fout, const std::string & text) const = 0;

		virtual bool WriteNumber(std::ofstream & fout, const int & number) const = 0;

		virtual bool WriteNumber(std::ofstream & fout, const double & number) const = 0;

		virtual bool WriteNumber(std::ofstream & fout, const float & number) const = 0;

		virtual bool WriteNumber(const std::string & nameOfFile, const int & number, bool append = false) const = 0;

		virtual bool WriteNumber(const std::string & nameOfFile, const double & number, bool append = false) const = 0;

		virtual bool WriteNumber(const std::string & nameOfFile, const float & number, bool append = false) const = 0;
};