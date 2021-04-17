#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

class song
{
public:
    vector<string> artists; //if more than one it's " if one it starts with bracket [ and name is still ex: ['artist name']
    //if more than one artist: "['artist 1', 'artist 2']"
    float danceability;
    int duration;
    float energy;
    bool explicitness;
    float instrumentalness;
    float loudness;
    string songName;
    int popularity;
    float speechiness;
    float tempo;
    float valence;
    int year;
    vector<string> genres;
};

int main()

{
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
                genreMap[temp].push_back(lineObj.substr(2, lineObj.size()-3));
            }
        }
    }

    file.close();

    vector<song>SongCatalog;

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
                        tempSong.genres.push_back(genreMap[artistName][i]);
                    }
                }
                tempSong.artists.push_back(artistName);
                getline(iss, lineObj, delim);
            }
            artistName = lineObj.substr(3, lineObj.size()-5);
            it=genreMap.find(artistName);
            if(it!=genreMap.end()) {
                for(int i = 0; i < genreMap[artistName].size(); i++) {
                    tempSong.genres.push_back(genreMap[artistName][i]);
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
    
    return 0;
}
