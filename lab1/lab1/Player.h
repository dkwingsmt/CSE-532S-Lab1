//
// Created by Zeneil Ambekar on 27/09/15.
//

#ifndef LAB1_PLAYER_H
#define LAB1_PLAYER_H

#include <string>
#include <vector>
#include <thread>
#include "Play.h"

using namespace std;


class Player {

private:
    const string     name;
    ifstream         input_file;
    vector<PlayLine> lines;
    Play             &play;
    thread           player_thread;

public:
    Player(Play &play, const vector<PlayLine> &lines, const ifstream &input_file, const string &name);

    void read();

    void act();

    void enter();

    void exit();

};


#endif //LAB1_PLAYER_H
