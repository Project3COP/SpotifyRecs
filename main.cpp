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
vector<string>getGenres(string genreNums) {
    vector<string>favGenres;
    for (int i = 0; i < genreNums.size(); i++) {
        bool valid = false;
        if (int(genreNums[i]) == 49)
        {
            favGenres.push_back("Pop");
            valid = true;
        }
        if (int(genreNums[i]) == 50)
        {
            favGenres.push_back("Hip-Hop/Rap");
            valid = true;
        }
        if (int(genreNums[i]) == 51)
        {
            favGenres.push_back("R&B");
            valid = true;
        }
        if (int(genreNums[i]) == 52)
        {
            favGenres.push_back("Rock");
            valid = true;
        }

        if (int(genreNums[i]) == 53)
        {
            favGenres.push_back("Electronic");
            valid = true;
        }
        if (int(genreNums[i]) == 54)
        {
            favGenres.push_back("Alternative");
            valid = true;
        }
        if (int(genreNums[i]) == 56)
        {
            favGenres.push_back("Instrumental");
            valid = true;
        }
        if (int(genreNums[i]) == 57)
        {
            favGenres.push_back("Country");
            valid = true;
        }
        if (int(genreNums[i]) == 58)
        {
            favGenres.push_back("Jazz");
            valid = true;
        }
        if (int(genreNums[i]) == 59)
        {
            favGenres.push_back("Classical");
            valid = true;
        }
        if (int(genreNums[i]) == 60)
        {
            favGenres.push_back("Reggae");
            valid = true;
        }
        if (int(genreNums[i]) == 61)
        {
            favGenres.push_back("Foreign");
            valid = true;
        }
        if (int(genreNums[i]) == 62)
        {
            favGenres.push_back("No preference, I enjoy all types");
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
            cout << "Input should be a list of numbers without spaces, ex: R&B and Jazz  is '39'. " << endl;
            string genreNums;
            cout << "1.)Pop 2.)Hip-Hop/Rap 3.)R&B 4.)Rock 5.)Electronic 6.)Alternative 7.)Instrumental 8.)Country 9.)Jazz"
                    "10.)Classical 11.)Reggae 12.)Foreign 13.)No preference, I enjoy all types" << endl;
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
            cout << "1.)Pop 2.)Hip-Hop/Rap 3.)R&B 4.)Rock 5.)Electronic 6.)Alternative 7.)Instrumental 8.)Country 9.)Jazz"
                    "10.)Classical 11.)Reggae 12.)Foreign 13.)No preference, I enjoy all types" << endl;
            cin >> results.favGenre;


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

int main() {
    Survey results = readSurvey(); //reads in survey results

    vector<song> SongCatalog;
    readFiles(SongCatalog);

    playlist playlsit = playlist(SongCatalog, results); //generates playlist

    song *arr = &SongCatalog[0];
    for (size_t i = 0; i < SongCatalog.size(); ++i) {
        arr[i] = SongCatalog[i];
    }

   Shellsort(arr, SongCatalog.size());
   for(int i = 0; i < SongCatalog.size(); i ++)
    {
        cout << arr[i].duration << " ";
    }

    return 0;
}

void readFiles(vector<song> &SongCatalog) {
    ifstream file;
    string line;
    string lineObj;
    char delim = ',';

    file.open("../data_w_genres.csv");
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

    file.open("../OfficialDataset.csv");
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

