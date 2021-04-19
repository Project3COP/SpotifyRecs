#include <queue>
#include <vector>
#include <string>
#include <algorithm>
#include "song.h"
#include "BST.h"
#include "Survey.h"
#include "Node.h"
#include "BST.h"

using namespace std;

//playlist constructor
playlist::playlist(vector<song> catalog, Survey surveyRes, int cap) {
    this->playName = surveyRes.playlistName;

    this->likedGenres = surveyRes.favGenres;
    this->mainGenre = surveyRes.favGenre;
    this->songTimes = surveyRes.favDecades;
    this->instrumental = surveyRes.isInstrumental;
    this->explicits = surveyRes.includeExplicit;
    this->fastTempo = surveyRes.fastTempo;
    this->happy = surveyRes.isHappy;
    this->loud = surveyRes.isLoud;

    this->tree = new BST();

    int genreCount = 0;
    int points = 0;

    vector<song>::iterator it = catalog.begin();
    while(it != catalog.end()) {
        //add points for genres, 2 points if main genre, cap at 5 points for genres
        //if they like all genres dont need to enter for loop
        if(it->genres.size() == 13) {
            points = 5;
            genreCount = 5;
        }
        else {
            for(int i = 0; i < it->genres.size(); i++) {
                if (genreCount > 4) {
                    break;
                }
                if (it->genres[i].find(mainGenre) != string::npos) {
                    points += 2;
                    genreCount += 2;
                }
                for (int j = 0; j < likedGenres.size(); j++) {
                    if (it->genres[i].find(likedGenres[j]) != string::npos) {
                        points++;
                        genreCount++;
                    }
                }
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
        //explicit bool = explicit data
        if(!explicits) {
            if(it->explicitness) {
                points = 0;
            }
        }
        it->fitness = points;
        if(points >= cap) {
            if(!this->tree->insert(it.base())) {
                cout << "Error for: " << it->songName << endl;
                break;
            }
        }
        it++;
        points = 0;
        genreCount = 0;
    }
}

//shuffles songs using random generator to insert random songs into new tree unbalanced BST
//and then calling post order traversal again
void playlist::shuffle() {
    vector<song> songsToShuffle = this->songQ;
    delete(this->tree);
    this->tree = new BST();
    int insertSong = rand() % songsToShuffle.size();
    while(songsToShuffle.size()) {
        if(!this->tree->insert(&songsToShuffle[insertSong])) {
            cout << "Error for: " << songsToShuffle[insertSong].songName << endl;
            break;
        }
        songsToShuffle.erase(songsToShuffle.begin() + insertSong);
        if(!songsToShuffle.empty()) {
            insertSong = rand() % songsToShuffle.size();
        }
    }
    this->songQ = this->tree->traversePostOrder(this->tree->root);
    return;
}
