//
// Created by Veronica  Soden  on 4/17/21.
//

#include <queue>
#include <string>
#include "playlist.h"
#include "song.h"
#include "BST.h"

using namespace std;

playlist::playlist(vector<song> catalog, string nameP, vector<string> genres, string mainG, vector<bool> songTimes, bool inst, bool exp,
                   bool fastT, bool happy, bool loud) {
    this->playName = nameP;
    
    this->likedGenres = genres;
    this->mainGenre = mainG;
    this->songTimes = songTimes;
    this->instrumental = inst;
    this->explicits = exp;
    this->fastTempo = fastT;
    this->happy = happy;
    this->loud = loud;

    int points = 0;
    vector<song>::iterator it = catalog.begin();
    while(it != catalog.end()) {
        //add points for genres, 2 points if main genre
        for(int i = 0; i < it->genres.size(); i++) {
            if(it->genres[i] == mainGenre) {
                points += 2;
            }
            else if (find(likedGenres.begin(), likedGenres.end(), it->genres[i]) != likedGenres.end()) {
                points++;
            }
        }
        //song time period : 1st = 1920-1950, 2nd = 1960-1970, 3rd = 1980-1990, 4th = 2000-2020
        if(songTimes[0] && it->year < 1960) {
            points++;
        }
        else if(songTimes[1] && it->year < 1980 && it->year >= 1960) {
            points++;
        }
        else if(songTimes[2] && it->year < 2000 && it->year >= 1980) {
            points++;
        }
        else if(songTimes[3] && it->year >= 2000) {
            points++;
        }
        //instrumental bool = instrumental data and speechiness data
        if(instrumental) {
            if(it->instrumentalness >= 0.6) {
                points++;
            }
        }
        else {
            if(it->instrumentalness < 0.6) {
                points++;
            }
        }
        //explicit bool = explicit data
        if(explicits) {
            if(it->explicitness) {
                points++;
            }
        }
        else {
            if(!it->explicitness) {
                points++;
            }
        }
        //fast tempo bool = tempo data
        if(fastTempo) {
            if(it->tempo >= 100) {
                points++;
            }
        }
        else {
            if(it->tempo < 100) {
                points++;
            }
        }
        //happy bool = valence (high) data
        if(happy) {
            if(it->valence >= 0.5) {
                points++;
            }
        }
        else {
            if(it->valence < 0.5) {
                points++;
            }
        }
        //loud bool = loud data
        if(loud) {
            if(it->loudness >= -12) {
                points++;
            }
        }
        else {
            if(it->loudness < -12) {
                points++;
            }
        }
        if(points >= 5) {
            if(!tree.insert(it.base())) {
                cout << "Error for: " << it->songName << endl;
                break;
            }
        }
        it++;
    }
    tree.traverseInOrder(tree.root, this->songQ);
}