//Team Member: Tong Mu mutong32@gmail.com, Jinxuan Zhao jzhao32@wustl.edu
// Definition of corresponding header file.

#include <algorithm>
#include "Play.h"

using namespace std;

Play& Play::operator<< (PlayLine line)
{
	lock_guard<mutex> lock(insertionMutex);
	lines.push_back(line);
	return *this;
}

void Play::print(ostream &out)
{
	lock_guard<mutex> lock(insertionMutex);
	//First sort the lines 
	sort(lines.begin(), lines.end());
	string currentName;
	for (auto &currentLine : lines)
	{
		if (currentLine.character != currentName)
		{
			if (!currentName.empty())
				out << endl;
			currentName = currentLine.character;
			out << currentName << "." << endl;
		}
		out << currentLine.text << endl;
	}
}
