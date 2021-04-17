//
// Created by Veronica  Soden  on 4/17/21.
//

#ifndef PROJ3_PLAYLIST_H
#define PROJ3_PLAYLIST_H

#include <queue>
#include <string>
#include "song.h"
#include "BST.h"

using namespace std;

class playlist {
public:
    BST tree;
    queue<song> songQ;
    string playName;

    playlist(vector<song> catalog, string nameP, vector<string> genres, string mainG, vector<bool> songTimes, bool inst, bool exp,
            bool fastT, bool happy, bool loud);

private:
    vector<string> likedGenres;
    string mainGenre;
    vector<bool> songTimes;
    bool instrumental;
    bool energy;
    bool explicits;
    bool fastTempo;
    bool happy;
    bool loud;

};

#endif //PROJ3_PLAYLIST_H
