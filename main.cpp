#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include "song.h"
#include "playlist.h"
#include "Survey.h"

using namespace std;

void readFiles(vector<song>&);
void readSurvey(Survey);

int main() {
    vector<song> SongCatalog;
    readFiles(SongCatalog);
    return 0;
}

void readFiles(vector<song> &SongCatalog) {
    ifstream file;
    string line;
    string lineObj;
    char delim = ',';

    file.open("/Users/veronicasoden/CLionProjects/proj3/data_w_genres.csv");
    getline(file, line); // to get columns;

    unordered_map<string, vector<string> > genreMap;
    string lineObj2;

    while(!file.eof()) {
        getline(file, line);
        istringstream iss(line);

        getline(iss, lineObj, delim);
        string temp = lineObj;

        getline(iss, lineObj, '\n');
        if(lineObj[1] != ']') {
            if(lineObj[0] == '\"') {
                istringstream  iss2(lineObj);
                getline(iss2, lineObj2, delim);
                genreMap[temp].push_back(lineObj2.substr(3, lineObj2.size()-4));
                getline(iss2, lineObj2, delim);
                while(lineObj2.find(']') == -1) {
                    genreMap[temp].push_back(lineObj2.substr(2, lineObj2.size()-3));
                    getline(iss2, lineObj2, delim);
                }
                genreMap[temp].push_back(lineObj2.substr(2, lineObj2.size()-6));
            }
            else {
                genreMap[temp].push_back(lineObj.substr(2, lineObj.size()-5));
            }
        }
    }

    file.close();

    file.open("/Users/veronicasoden/CLionProjects/proj3/OfficialDataset.csv");
    getline(file, line); // to get columns;
    song tempSong;
    string artistName;

    while(!file.eof())
    {
        getline(file,line);
        istringstream iss(line);

        getline(iss, lineObj, delim);

        unordered_map<string, vector<string> >::iterator it;

        if(lineObj[0] == '\"' && lineObj[lineObj.size()-2] != ']') //artist multiple
        {
            artistName = lineObj.substr(3, lineObj.size()-4);
            it=genreMap.find(artistName);
            if(it!=genreMap.end()) {
                tempSong.genres = genreMap[artistName];
            }
            tempSong.artists.push_back(artistName);
            getline(iss, lineObj, delim);
            while(lineObj.find(']') == -1) {
                artistName = lineObj.substr(2, lineObj.size()-3);
                it=genreMap.find(artistName);
                if(it!=genreMap.end()) {
                    for(int i = 0; i < genreMap[artistName].size(); i++) {
                        if(find(tempSong.genres.begin(), tempSong.genres.end(), genreMap[artistName][i]) == tempSong.genres.end()) {
                            tempSong.genres.push_back(genreMap[artistName][i]);
                        }
                    }
                }
                tempSong.artists.push_back(artistName);
                getline(iss, lineObj, delim);
            }
            artistName = lineObj.substr(2, lineObj.size()-5);
            it=genreMap.find(artistName);
            if(it!=genreMap.end()) {
                for(int i = 0; i < genreMap[artistName].size(); i++) {
                    if(find(tempSong.genres.begin(), tempSong.genres.end(), genreMap[artistName][i]) == tempSong.genres.end()) {
                        tempSong.genres.push_back(genreMap[artistName][i]);
                    }
                }
            }
            tempSong.artists.push_back(artistName);
        }
        else //single artist
        {
            artistName = lineObj.substr(2, lineObj.size() - 4);
            it=genreMap.find(artistName);
            if(it!=genreMap.end()) {
                tempSong.genres = genreMap[artistName];
            }
            tempSong.artists.push_back(artistName);
        }

        getline(iss, lineObj, delim);
        tempSong.danceability = stof(lineObj);

        getline(iss, lineObj, delim);
        tempSong.duration = stoi(lineObj);

        getline(iss, lineObj, delim);
        tempSong.energy = stof(lineObj);

        getline(iss, lineObj, delim);
        tempSong.explicitness = stoi(lineObj);

        getline(iss, lineObj, delim);
        tempSong.instrumentalness = stof(lineObj);

        getline(iss, lineObj, delim);
        tempSong.loudness = stof(lineObj);

        getline(iss, lineObj, delim);
        int counter = count(lineObj.begin(), lineObj.end(), '\"');
        if(lineObj[0]=='\"' && counter%2 == 1) {
            tempSong.songName = lineObj;
            getline(iss, lineObj, delim);
            counter = count(lineObj.begin(), lineObj.end(), '\"');
            while (counter%2==0)
            {
                tempSong.songName += lineObj;
                getline(iss, lineObj, delim);
                counter = count(lineObj.begin(), lineObj.end(), '\"');
            }
            tempSong.songName += lineObj;
        }
        else {
            tempSong.songName = lineObj;
        }

        getline(iss, lineObj, delim);
        tempSong.popularity = stoi(lineObj);

        getline(iss, lineObj, delim);
        tempSong.speechiness = stof(lineObj);

        getline(iss, lineObj, delim);
        tempSong.tempo = stof(lineObj);

        getline(iss, lineObj, delim);
        tempSong.valence = stof(lineObj);

        getline(iss, lineObj, '\n');
        tempSong.year = stoi(lineObj);

        SongCatalog.push_back(tempSong);
        tempSong.artists.clear();
    }
    file.close();
    return;
}

void readSurvey(Survey results) {
    ifstream file;
    string line;
    string lineObj;
    char delim = ',';

    //Results: enter the file path for the results from google forms
    file.open("/Users/maia/Documents/GitHub/potential-carnival/Test2.csv");
    getline(file, line); // to get columns

    while (!file.eof()) {
        getline(file, line);
        istringstream iss(line);

        getline(iss, lineObj, delim);

        //Playlist Name:
        getline(iss, lineObj, delim);
        results.playlistName = lineObj;

        //Favorite Genres (multiple):
        getline(iss, lineObj, delim);
        stringstream ss(lineObj);

        string substr;
        while (ss.good()) {
            getline(ss, substr, ';');
            results.favGenres.push_back(substr);
        }

        for (size_t i = 0; i < results.favGenres.size(); i++) {
            cout << "Favorite Genres: " << results.favGenres[i] << endl;
        }

        //Favorite Genre (single):
        getline(iss, lineObj, delim);
        results.favGenre = lineObj;

        //1 = Instrumental; 0 = Lyrics
        getline(iss, lineObj, delim);

        if (lineObj == "\"Instrumental\"") {
            results.isInstrumental = true;
        }
        else {
            results.isInstrumental = false;
        }

        //1 = Energetic; 0 = Calming
        getline(iss, lineObj, delim);

        if (lineObj == "\"Energetic\"") {
            results.isEnergetic = true;
        }
        else {
            results.isEnergetic = false;
        }

        //explicit: 1 = yes; 0 = no
        getline(iss, lineObj, delim);
        if (lineObj == "\"Include explicit songs\"") {
            results.includeExplicit = true;
        }
        else {
            results.includeExplicit = false;
        }

        //1 = fast; 0 = slow
        getline(iss, lineObj, delim);
        if (lineObj == "\"Fast Tempo\"") {
            results.fastTempo = true;
        }
        else {
            results.fastTempo = false;
        }
        
        //Favorite Decade(s):
        getline(iss, lineObj, delim);
        if(lineObj.find("1920") != lineObj.npos) {
            results.favDecades.push_back(true);
        }
        else {
            results.favDecades.push_back(false);
        }

        if(lineObj.find("1960") != lineObj.npos) {
            results.favDecades.push_back(true);
        }
        else {
            results.favDecades.push_back(false);
        }

        if(lineObj.find("1980") != lineObj.npos) {
            results.favDecades.push_back(true);
        }
        else {
            results.favDecades.push_back(false);
        }

        if(lineObj.find("2000") != lineObj.npos) {
            results.favDecades.push_back(true);
        }
        else {
            results.favDecades.push_back(false);
        }

        //1 = happy; 0 = sad/angry
        getline(iss, lineObj, delim);

        if (lineObj == "\"Happy\"")
        {
            results.isHappy = true;
        }
        else
        {
            results.isHappy = false;
        }
        
        //1 = loud; 0 = quiet
        getline(iss, lineObj, delim);
        if (lineObj == "\"Louder\"")
        {
            results.isLoud = true;
        }
        else
        {
            results.isLoud = false;
        }
    }
    file.close();
    return;
}
