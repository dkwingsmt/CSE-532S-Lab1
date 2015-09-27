//Team Member: Tong Mu mutong32@gmail.com, Jinxuan Zhao jzhao32@wustl.edu
// Definition of corresponding header file.

#include <algorithm>
#include <iostream>
#include "Play.h"

using namespace std;

void recite(list<PlayLine>::const_iterator &line) {
    unique_lock<mutex> ul(reciteMutex);
    cv.wait(ul, [&]{ return counter >= line.order; });
    if (counter == line.order) {
        if (currentPlayer != line.character) {
            cout << "\n" << line.character << "." << endl;
            currentPlayer = line.character;
        }
        cout << line.
        counter++;
    }
    else {
        cerr << "ERROR: Unexpected PlayLine order. [character= " << line->character << 
            " line.order= " << line->order << " play.counter= " << counter << "\n";
    }
    line++;
    ul.unlock();
    cv.notify_all();
}
