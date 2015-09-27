//Team Member: Tong Mu mutong32@gmail.com, Jinxuan Zhao jzhao32@wustl.edu
// lab0_532.cpp :This function contains the thread function and the main functino. It also has the thread guard object.
//

#include "Play.h"
#include "Player.h"
#include "common.h"

using namespace std;

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

	list<Player> players;
    // Read play file
	Play play(playName);
    string line;
    while (getline(configFile, line))
    {
        line = trim(line);
        if (line.empty())
            continue;
        string characterName;
        string inputFileName;
        if (istringstream(line) >> characterName >> inputFileName)
        {
            players.push_back(Player(play, ifstream(fileDir + inputFileName), characterName));
        }
    }

    // Guard is unnecessary for fstream closes file upon destruction
    configFile.close();

    for (auto &player : players) {
        player.enter();
    }

    for (auto &player : players) {
        player.exit();
    }

	cout << "Finished.\n";
	getchar();

	return 0;
}



