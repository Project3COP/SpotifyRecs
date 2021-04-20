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
#include "BST.h"
#include "Node.h"

using namespace std;

Survey readSurvey();
vector<string>getGenres(string genreNums);
void readFiles(vector<song>&);

int Shellsort(song arr[], int n);


int main() {
     
    //*****Generates SongCatalog*****
    vector<song> SongCatalog;
    readFiles(SongCatalog);

    //*****Survey*****
    Survey results = readSurvey(); //reads in survey results

    //****Generates Playlist*****
    int fitCap = 10;
    playlist* playlistObj = new playlist(SongCatalog, results, fitCap);
    while(playlistObj->tree->size < 10) {
        delete playlistObj;
        playlistObj =  new playlist(SongCatalog, results, --fitCap); //generates playlist
    }
    //generates vector songQ by post order traversal
    playlistObj->songQ = playlistObj->tree->traversePostOrder(playlistObj->tree->root);
    playlistObj->shuffle();


    
    //*****ShellSort*****
    song *arr = &SongCatalog[0];
    for (size_t i = 0; i < SongCatalog.size(); ++i) {
        arr[i] = SongCatalog[i];
    }

    Shellsort(arr, SongCatalog.size());



    return 0;
}

Survey readSurvey() {

    bool invalidResult = false;
    bool surveyComplete = false;
    Survey results;

    while(!surveyComplete) {

        bool invalidResult = false;

        while (invalidResult == false) {
            cout << endl;

            cout << "What do you want to name your playlist?" << endl;
            cin >> results.playlistName;

            cout << "What are your favorite genres?" << endl;
            cout << "Input should be a list of lowercase letters without spaces, ex: R&B and Jazz  is 'dg'. " << endl;
            string genreNums;
            cout << "a.)Pop" << endl << "b.)Hip-Hop" << endl << "c.)Rap" << endl << "d.)R&B" << endl << "e.)Rock"
                 << endl << "f.)Electronic" << endl << "g.)Alternative" << endl << "h.)Instrumental" << endl <<
                 "i.)Country" << endl << "j.)Jazz" << endl << "k.)Classical" << endl << "l.)Reggae" << endl <<
                 "m.)Foreign" << endl << "n.)No preference, I enjoy all types" << endl;
            cin >> genreNums;
            results.favGenres = getGenres(genreNums);
            if (results.favGenres.size() == 0) {
                invalidResult = true;
                cout << "You're answer was not formatted correctly!" << endl;
                cout << "Generating another survey... "<< endl;
                break;
            }

            string genre;
            cout << "If you had to pick one, which is your favorite genre?" << endl;
            cout << "Type out the genre of preference, ex Jazz: 'Jazz' " << endl;
            cout << "a.)Pop" << endl << "b.)Hip-Hop" << endl << "c.)Rap" << endl << "d.)R&B" << endl << "e.)Rock"
                 << endl << "f.)Electronic" << endl << "g.)Alternative" << endl << "h.)Instrumental" << endl <<
                 "i.)Country" << endl << "j.)Jazz" << endl << "k.)Classical" << endl << "l.)Reggae" << endl <<
                 "m.)Foreign" << endl;
            cin >> genre;
            results.favGenre = getGenres(genre)[0];

            string ans;
            cout << "Do you prefer songs that are more instrumental (less lyrics, more music) or songs with more lyrics?"
                 << endl;
            cout << "Enter 1 if instrumental, 2 if more lyrics" << endl;
            cin >> ans;
            if (ans == "1")
                results.isInstrumental = true;
            else if (ans == "2")
                results.isInstrumental = false;
            else {
                invalidResult = true;
                cout << "Your answer was not formatted correctly!" << endl;
                cout << "Generating another survey... "<< endl;
                break;
            }

            cout << "Do you prefer songs that are more energetic or more calming?" << endl;
            cout << "Enter 1 if energetic, 2 if more calming" << endl;
            cin >> ans;
            if (ans == "1")
                results.isEnergetic = true;
            else if (ans == "2")
                results.isEnergetic = false;
            else {
                invalidResult = true;
                cout << "Your answer was not formatted correctly!" << endl;
                cout << "Generating another survey... "<< endl;
                break;
            }

            cout << "Do you want explicit songs to be included?" << endl;
            cout << "Enter 1 if yes, 2 if not" << endl;
            cin >> ans;
            if (ans == "1")
                results.includeExplicit = true;
            else if (ans == "2")
                results.includeExplicit = false;
            else {
                invalidResult = true;
                cout << "Your answer was not formatted correctly!" << endl;
                cout << "Generating another survey... "<< endl;
                break;
            }

            cout << "Do you prefer songs with a faster or slower tempo?" << endl;
            cout << "Enter 1 if faster, 2 if slower" << endl;
            cin >> ans;
            if (ans == "1")
                results.fastTempo = true;
            else if (ans == "2")
                results.fastTempo = false;
            else {
                invalidResult = true;
                cout << "Your answer was not formatted correctly!" << endl;
                cout << "Generating another survey... "<< endl;
                break;
            }

            cout << "What decade(s) of music do you prefer?" << endl;
            cout << "1.) 1920-1950 2.) 1960-1970 3.) 1980-1990 4.) 2000-2020 " << endl;
            cin >> ans;
            for(int i = 0; i < 4; i ++)
            {
                results.favDecades.push_back(false);
            }
            for(int i = 0; i < ans.size(); i ++)
            {
                bool valid = false;
                if (int(ans[i]) == 49)
                {
                    results.favDecades[0] = true;
                    valid = true;
                }
                if (int(ans[i]) == 50)
                {
                    results.favDecades[1] = true;
                    valid = true;
                }
                if (int(ans[i]) == 51)
                {
                    results.favDecades[2] = true;
                    valid = true;
                }
                if (int(ans[i]) == 52)
                {
                    results.favDecades[3] = true;
                    valid = true;
                }
                if(!valid) {
                    invalidResult = true;
                    cout << "Your answer was not formatted correctly!" << endl;
                    cout << "Generating another survey... " << endl;
                    break;
                }

            }

            cout << "Do you prefer happy (1) or sad music (2)?" << endl;
            cin >> ans;
            if (ans == "1")
                results.isHappy = true;
            else if (ans == "2")
                results.isHappy = false;
            else {
                invalidResult = true;
                cout << "Your answer was not formatted correctly!" << endl;
                cout << "Generating another survey... "<< endl;
                break;
            }

            cout << "Do you prefer louder (1) or quieter music (2)?" << endl;
            cin >> ans;
            if (ans == "1")
            {
                results.isLoud = true;
                invalidResult = true;
                surveyComplete = true;
            }
            else if (ans == "2")
            {
                results.isLoud = false;
                invalidResult = true;
                surveyComplete = true;
            }
            else {
                invalidResult = true;
                cout << "Your answer was not formatted correctly!" << endl;
                cout << "Generating another survey... "<< endl;
                break;
            }

        }
    }

    return results;
}

vector<string>getGenres(string genreNums) {
    vector<string>favGenres;
    for (int i = 0; i < genreNums.size(); i++) {
        bool valid = false;
        if(int(genreNums[i]) == 110) {
            favGenres = {"pop", "hip hop", "rap", "r&b", "rock", "electro", "alternative",
                         "instrumental", "country", "jazz", "classical", "reggae", "foreign"};
            valid = true;
            break;
        }
        if (int(genreNums[i]) == 97)
        {
            favGenres.push_back("pop");
            valid = true;
        }
        if (int(genreNums[i]) == 98)
        {
            favGenres.push_back("hip hop");
            valid = true;
        }
        if (int(genreNums[i]) == 99)
        {
            favGenres.push_back("rap");
            valid = true;
        }
        if (int(genreNums[i]) == 100)
        {
            favGenres.push_back("r&b");
            valid = true;
        }

        if (int(genreNums[i]) == 101)
        {
            favGenres.push_back("rock");
            valid = true;
        }
        if (int(genreNums[i]) == 102)
        {
            favGenres.push_back("electro");
            valid = true;
        }
        if (int(genreNums[i]) == 103)
        {
            favGenres.push_back("alternative");
            valid = true;
        }
        if (int(genreNums[i]) == 104)
        {
            favGenres.push_back("instrumental");
            valid = true;
        }
        if (int(genreNums[i]) == 105)
        {
            favGenres.push_back("country");
            valid = true;
        }
        if (int(genreNums[i]) == 106)
        {
            favGenres.push_back("jazz");
            valid = true;
        }
        if (int(genreNums[i]) == 107)
        {
            favGenres.push_back("classical");
            valid = true;
        }
        if (int(genreNums[i]) == 108)
        {
            favGenres.push_back("reggae");
            valid = true;
        }
        if (int(genreNums[i]) == 109)
        {
            favGenres.push_back("foreign");
            valid = true;
        }
        if(!valid)
        {
            favGenres.empty();
            return favGenres;
        }
    }
    return favGenres;
}

void readFiles(vector<song> &SongCatalog) {
    ifstream file;
    string line;
    string lineObj;
    char delim = ',';

    file.open("./data_w_genres.csv");
    std::getline(file, line); // to get columns;

    unordered_map<string, vector<string> > genreMap;
    string lineObj2;

    while(!file.eof()) {
        std::getline(file, line);
        istringstream iss(line);

        std::getline(iss, lineObj, delim);
        string temp = lineObj;

        std::getline(iss, lineObj, '\n');
        if(lineObj[1] != ']') {
            if(lineObj[0] == '\"') {
                istringstream  iss2(lineObj);
                std::getline(iss2, lineObj2, delim);
                genreMap[temp].push_back(lineObj2.substr(3, lineObj2.size()-4));
                std::getline(iss2, lineObj2, delim);
                while(lineObj2.find(']') == -1) {
                    genreMap[temp].push_back(lineObj2.substr(2, lineObj2.size()-3));
                    std::getline(iss2, lineObj2, delim);
                }
                genreMap[temp].push_back(lineObj2.substr(2, lineObj2.size()-6));
            }
            else {
                genreMap[temp].push_back(lineObj.substr(2, lineObj.size()-5));
            }
        }
    }

    file.close();

    file.open("./OfficialDataset.csv");
    std::getline(file, line); // to get columns;
    song tempSong;
    string artistName;

    while(!file.eof())
    {
        std::getline(file,line);
        istringstream iss(line);

        std::getline(iss, lineObj, delim);

        unordered_map<string, vector<string> >::iterator it;

        if(lineObj[0] == '\"' && lineObj[lineObj.size()-2] != ']') //artist multiple
        {
            artistName = lineObj.substr(3, lineObj.size()-4);
            it=genreMap.find(artistName);
            if(it!=genreMap.end()) {
                tempSong.genres = genreMap[artistName];
            }
            tempSong.artists.push_back(artistName);
            std::getline(iss, lineObj, delim);
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
                std::getline(iss, lineObj, delim);
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

        std::getline(iss, lineObj, delim);
        tempSong.danceability = stof(lineObj);

        std::getline(iss, lineObj, delim);
        tempSong.duration = stoi(lineObj);

        std::getline(iss, lineObj, delim);
        tempSong.energy = stof(lineObj);

        std::getline(iss, lineObj, delim);
        tempSong.explicitness = stoi(lineObj);

        std::getline(iss, lineObj, delim);
        tempSong.instrumentalness = stof(lineObj);

        std::getline(iss, lineObj, delim);
        tempSong.loudness = stof(lineObj);

        std::getline(iss, lineObj, delim);
        int counter = count(lineObj.begin(), lineObj.end(), '\"');
        if(lineObj[0]=='\"' && counter%2 == 1) {
            tempSong.songName = lineObj;
            std::getline(iss, lineObj, delim);
            counter = count(lineObj.begin(), lineObj.end(), '\"');
            while (counter%2==0)
            {
                tempSong.songName += lineObj;
                std::getline(iss, lineObj, delim);
                counter = count(lineObj.begin(), lineObj.end(), '\"');
            }
            tempSong.songName += lineObj;
        }
        else {
            tempSong.songName = lineObj;
        }

        std::getline(iss, lineObj, delim);
        tempSong.popularity = stoi(lineObj);

        std::getline(iss, lineObj, delim);
        tempSong.speechiness = stof(lineObj);

        std::getline(iss, lineObj, delim);
        tempSong.tempo = stof(lineObj);

        std::getline(iss, lineObj, delim);
        tempSong.valence = stof(lineObj);

        std::getline(iss, lineObj, '\n');
        tempSong.year = stoi(lineObj);

        SongCatalog.push_back(tempSong);
        tempSong.artists.clear();
    }
    file.close();
    return;
}

int Shellsort(song arr[], int n)
{
/* From Lecture Slides on Shellsort in Module 6
 * 1. Set the initial value of gapto n / 2
 * 2. while gap > 0
 * 3. foreach array element from position gap to the last element
 * 4. Insert this element where it belongs in its subarray.
 * 5. if gap is 2, set it to 1
 * 6. else gap = gap / 2.2.
 */

    int gap = n/2;
    while(gap > 0)
    {
        for (int i = gap; i < n; i += 1)
        {

            song temp = arr[i];


            int j;
            for (j = i; j >= gap && arr[j - gap].duration > temp.duration; j -= gap)
                arr[j] = arr[j - gap];

            arr[j] = temp;
        }
        gap = gap/2;
    }
    return 0;
}

