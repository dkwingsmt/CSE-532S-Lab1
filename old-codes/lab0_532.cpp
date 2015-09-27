//Team Member: Tong Mu mutong32@gmail.com, Jinxuan Zhao jzhao32@wustl.edu
// lab0_532.cpp :This function contains the thread function and the main functino. It also has the thread guard object.
//

#include "Play.h"
#include "../common.h"

using namespace std;


// The procedure to run in threads, which reads different files and inserts 
// lines into play object. 
void threadFunction(Play &playObject, string characterName, ifstream &inFile)
{
	string line;
	if (!inFile)
	{
		cout << "unable to open file" << characterName << endl;
		return;
	}

	while (getline(inFile, line))
	{
		istringstream iss(line);
		unsigned int lineNumber;
		string text;
		if (iss >> lineNumber)
		{
			if (getline(iss, text))
                trim(text);
				playObject << PlayLine({ lineNumber, characterName, text });
		}
	}
	inFile.close();
}

int main(int argc, char *  argv[])
{
    // Parse command line arguments
	if (argc < 2  || argc > 2) {
		cout << "usage: " << argv[0] << " <config file>" << endl;
		return 0;
	}

	ifstream configFile(argv[1]);
	if (!configFile) {
		cout << "Unable to open file " << argv[1] << endl;
		return 1;
	}

	string playName;
	while (playName.empty() && getline(configFile, playName));  // empty body
	if (playName.empty()) {
		cout << "No play name available." << endl;
		return 2;
	}
	cout << "[PlayName: " << playName << "]" << endl;

    const string &&fileDir = dirnameOf(argv[1]);

	list<ifstream> l;
    // Read play file
	Play currentPlay(playName);
	{
		vector<thread> parsingThreads;
		TGuard join_guard([&]{
			for (auto &currentThread : parsingThreads) {
				if (currentThread.joinable())
					currentThread.join();
			}
		});
		string line;
		while (getline(configFile, line))
		{
			if (line.empty())
				continue;
			string characterName;
			string inputFileName;
			if (istringstream(line) >> characterName >> inputFileName)
			{
				l.push_back(ifstream(fileDir + inputFileName));
				parsingThreads.push_back(thread(threadFunction,
					ref(currentPlay),
					characterName,
					ref(l.back())
					));
			}
		}

        // Guard is unnecessary for fstream closes file upon destruction
        configFile.close();
	}

	currentPlay.print(cout);

	return 0;

}



