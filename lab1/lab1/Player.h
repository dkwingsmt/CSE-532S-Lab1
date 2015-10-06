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

    void read();

    void act();

public:
    Player(Play &play, ifstream input_file, const string &name) : 
        play(play), 
        input_file(move(input_file)),
        name(name) 
    { }

    Player(Player &) = delete;
    Player(Player &&tmp) :
        name(tmp.name),
        input_file(move(tmp.input_file)),
        lines(move(tmp.lines)),
        play(tmp.play),
        player_thread(move(tmp.player_thread))
    {}

    ~Player() {
        exit();
    }

    void enter();

    void exit();

};


#endif //LAB1_PLAYER_H
