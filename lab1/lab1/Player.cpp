//
// Created by Zeneil Ambekar on 27/09/15.
//

#include <iostream>
#include <sstream>
#include "Player.h"
#include "common.h"

using namespace std;

Player::Player(Play &play, ifstream &input_file, const string &name) : 
    play(play), 
    input_file(input_file),
    name(name) {

}

void Player::read() {
    string line;
    if (!input_file) {
        cout << "unable to open file" << name << endl;
        return;
    }

    while (getline(input_file, line)) {
        istringstream iss(line);
        unsigned int  lineNumber;
        string        text;

        if (iss >> lineNumber) {
            if (getline(iss, text)) {
                trim(text);
                if (!text.empty())
                    lines.push_back(PlayLine({lineNumber, name, text}));

            }
        }
    }
}

void Player::act() {

    for(vector<PlayLine>::const_iterator playIterator = lines.begin(); playIterator != lines.end();)
        play.recite(playIterator);

}

void Player::enter() {

    player_thread = thread([this](){
        read();
        act();
    });

}

void Player::exit() {

    if(player_thread.joinable())
        player_thread.join();

}
