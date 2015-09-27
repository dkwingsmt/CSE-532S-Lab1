// Team Member: Tong Mu mutong32@gmail.com, Jinxuan Zhao jzhao32@wustl.edu
// [File description]
// class Play, to organize the lines from different characters and 
//      construct a printable score. 
// struct PlayLine, a line from a play.

#ifndef __PLAY_H__
#define __PLAY_H__

#include <fstream>
#include <vector>
#include <string>
#include <mutex>

using namespace std;

// Structured lines of the play, which contains order, the character by which 
//it belongs to and the text.
struct PlayLine {
	unsigned int order;
	string character;
	string text;

	bool operator< (const PlayLine &b) const {
		return order < b.order;
	}
};

// class Play, to organize the lines from different characters and 
//      construct a printable score. 
class Play
{
	mutex insertionMutex;
	string name;
	vector<PlayLine> lines;

public:
	Play(string playName) : name(playName) {}

    //The insertion method inserts PlayLine struct into vector data of Play object 
	Play& operator<< (PlayLine line);

    //The print method takes a reference to an ostream, and uses the ostream and 
    //the structured lines stored in its member container to print out a properly 
    //ordered script
	void print(ostream &out);

};

#endif  // header guard
