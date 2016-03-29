#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "IFileWriter.h"

class FileWriter: public IFileWriter
{
	public:
		virtual bool WriteMatrix(const std::string & nameOfFile, const std::vector<std::vector<double>> & matrix, bool append = false) const;

		virtual bool WriteText(const std::string & nameOfFile, const std::string & text, bool append = false) const;

		virtual bool WriteMatrix(std::ofstream & fout, const std::vector<std::vector<double>> & matrix) const;
		
		virtual bool WriteText(std::ofstream & fout, const std::string & text) const;

		virtual bool WriteNumber(std::ofstream & fout, const int & number) const;

		virtual bool WriteNumber(std::ofstream & fout, const double & number) const;

		virtual bool WriteNumber(std::ofstream & fout, const float & number) const;

		virtual bool WriteNumber(const std::string & nameOfFile, const int & number, bool append = false) const;

		virtual bool WriteNumber(const std::string & nameOfFile, const double & number, bool append = false) const;

		virtual bool WriteNumber(const std::string & nameOfFile, const float & number, bool append = false) const;

		template<class T>
		bool Write(std::ofstream & fout, const T & text) const;

		template<class T>
		bool Write(const std::string & nameOfFile, const T & text, bool append = false) const;
};