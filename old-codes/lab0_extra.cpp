//Team Member: Tong Mu mutong32@gmail.com, Jinxuan Zhao jzhao32@wustl.edu
// lab0_extra.cpp : The program for extracredit. 
//

#include "../common.h"

//This function generates script for each character
//It returns a vector, which contains vectors of lines for each character.
//The order of elements in the vector is same as passed vector of characters. 
vector<vector<string>> process_play(ifstream &playfile, vector<string> &characters) {
	map<string, int> char2id;
	vector<vector<string>> seperate_play;

	string line;
	int currentChar = -1;
	int lineno = 0;
    bool previousLineEmpty = true;
	while (getline(playfile, line)) {
		line = trim(line);
        if (line[0] == '[') {   // Character movement indication
            continue;
        }
		 
		if (line.empty()) {
            previousLineEmpty = true;
        }
        //If the previous line is empty and current line is not, 
        //it should be a character name. (Except for first line)
        else if (previousLineEmpty) {
            // Character name
            if (line.back() == '.') {
                auto itquery = char2id.emplace(line, char2id.size());
                if (itquery.second) {
                    const string &name = itquery.first->first;
                    // Ignore end-of-line dot.
                    characters.push_back(name.substr(0, name.size()-1));
                    seperate_play.push_back({});
                }
                currentChar = itquery.first->second;
            }
            previousLineEmpty = false;
        }
        else if (currentChar != -1) {
            //Only increment when the line is a valid dialog.
            lineno++;
            ostringstream oss;
            oss << lineno << ' ' << line;
            seperate_play[currentChar].push_back(oss.str());
        }
	}
	return seperate_play;
}

int main(int argc, char *  argv[])
{
	if (argc < 4) {
		cout << "usage: " << argv[0] << " <play file> <config file> <play name>" << endl;
 		return 0;
	}

	ifstream playFile(argv[1]);
	if (!playFile) {
		cout << "Unable to open play file " << argv[1] << endl;
		return 1;
	}

	//Take the rest of arguments as play name
	string playName = argv[3];
	for (int i = 4; i < argc; i++)
	{
		playName = playName+" "+argv[i];
	}
	string configFile = argv[2];

    // Character files are placed in the same directory as the config file  
    const string &&fileDir = dirnameOf(configFile);

	//Extract lines for each character.
    vector<string> characters;
	auto &&seperate_play = process_play(playFile, characters);
	playFile.close();

	// Generate script file for each character. 
	for (size_t i = 0; i < characters.size(); i++) {
		string fileName = fileDir+characters[i]+".txt";\
		ofstream charFile(fileName);
		if (!charFile) {
			cout << "Unable to open file " << fileName << endl;
			return 2;
		}
		for (string &s : seperate_play[i]) {
			charFile << s << endl;
		}
		charFile.close();
	}

    // Output config file
	ofstream out(configFile);
	out << playName << "\n";
	for (size_t i = 0; i < characters.size(); i++)
	{
		out << characters[i] << " " << characters[i] + ".txt" << "\n";
	}
	out.close();


	return 0;

}



