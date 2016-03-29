#include <vector>
#include <iostream>
#include <time.h> 
#include "IFileReader.h"
#include "IFileWriter.h"
#include "PokFileReader.h"
#include "FileWriter.h"
#include "Helper.h"
#include "Geometry/Geometry.h"
#include "RankCalculator.h"

void PrintRanks(std::ofstream & fo, const std::vector<int> & ranks, const std::string & direction, 
	const std::string & centreChosen);

int main()
{
	clock_t time = clock();

	IFileReader* reader = new PokFileReader();
	IFileWriter* writer = new FileWriter();

	Helper* helper = new Helper(reader, writer);

	std::vector<Point2D> points = helper->ReadPoints("input.txt");

	RankCalculator* rankCalculator = new RankCalculator();

	std::ofstream fo("ranks.txt");

	std::vector<int> ranks = rankCalculator->GetRanks(points, Right, false);
	PrintRanks(fo, ranks, "Right", "Geometric");

	ranks = rankCalculator->GetRanks(points, Left, false);
	PrintRanks(fo, ranks, "Left", "Geometric");

	ranks = rankCalculator->GetRanks(points, Centre, false);
	PrintRanks(fo, ranks, "Centre", "Geometric");

	ranks = rankCalculator->GetRanks(points, Right, true);
	PrintRanks(fo, ranks, "Right", "Gravity");

	ranks = rankCalculator->GetRanks(points, Left, true);
	PrintRanks(fo, ranks, "Left", "Gravity");

	ranks = rankCalculator->GetRanks(points, Centre, true);
	PrintRanks(fo, ranks, "Centre", "Gravity");

	fo.close();

	time = clock() - time;

	double ms = double(time) / CLOCKS_PER_SEC * 1000;

	std::cout << "Finished!\nTime elapsed: " << ms << " ms" << std::endl << std::endl;
	
	delete reader;
	delete writer;

	std::cout << "Press any key.\n";
	std::cin.get();

	return 0;
}

void PrintRanks(std::ofstream & fo, const std::vector<int> & ranks, const std::string & direction, 
	const std::string & centreChosen)
{
	fo << "Compression to " << direction << ". Centre chosen - " << centreChosen << "." << std::endl;
	int size = ranks.size();
	for (int i = 0; i < size; ++i)
	{
		fo.width(4);
		fo << ranks[i];
	}
	fo << std::endl << std::endl;
}
