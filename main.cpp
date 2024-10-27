#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
#include "song.h"


int global = 0;
vector <int> globalIndexVector;
ifstream inFS("input.txt");
ofstream outFS("output.txt");  

int damerau_levenshtein(const string s1, const string s2) 
{
    const int len1 = s1.length(), len2 = s2.length();
    vector<vector<int>> dist(len1 + 1, vector<int>(len2 + 1, 0));
    for (int i = 0; i <= len1; ++i) {
        dist[i][0] = i;
    }
    for (int j = 0; j <= len2; ++j) {
        dist[0][j] = j;
    }
    for (int i = 1; i <= len1; ++i) {
        for (int j = 1; j <= len2; ++j) {
            int cost = s1[i - 1] == s2[j - 1] ? 0 : 1;
            dist[i][j] = min({dist[i - 1][j] + 1, dist[i][j - 1] + 1, dist[i - 1][j - 1] + cost});
            if (i > 1 && j > 1 && s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1]) 
            {
                dist[i][j] = min(dist[i][j], dist[i - 2][j - 2] + cost);
            }
        }
    }
    return dist[len1][len2];
}

int updated_levenshtein(string longerstr, string shorterstr)
{
    if (shorterstr.size() > longerstr.size())
    {
        return updated_levenshtein(shorterstr,longerstr);
    }
    int i  = shorterstr.size();
    string temp;
    vector<int> levenval;
    for (int j = 0; j <= longerstr.size() - i; j++) 
    {
        temp = longerstr.substr(j, i);
        levenval.push_back(damerau_levenshtein(temp,shorterstr));
    }
    if (*min_element(levenval.begin(),levenval.end()) > damerau_levenshtein(longerstr,shorterstr))
    {
        return damerau_levenshtein(longerstr,shorterstr);
    }
    return *min_element(levenval.begin(),levenval.end());
}

void sortAndRemoveDuplicates(vector<int>& v) 
{
    sort(v.begin(), v.end());
    auto last = unique(v.begin(), v.end());
    v.erase(last, v.end());
}

void minimizeVec(vector<Song>& newV, vector<int>& temp)
{
    sortAndRemoveDuplicates(temp);
    for (unsigned int i = 0;i < temp.size();i++)
    {
        newV.erase(newV.begin() + temp.at(i));
        for (unsigned int j = i+1;j < temp.size();++j)
        {
            temp.at(j) -= 1;
        }
    }
    temp.resize(0);
}

int smallerOfTwo(Song x)
{
    if (x.getNameOnlyStatus())
    {
        return x.getName().size();
    }
    else
    {
        if (x.getArtist().size() < x.getTitle().size())
        {
            return x.getArtist().size();
        }
        else
        {
            return x.getTitle().size();
        }
    }
}

int largerOfTwo(Song x)
{
    if (x.getNameOnlyStatus())
    {
        return x.getName().size();
    }
    else
    {
        if (x.getArtist().size() > x.getTitle().size())
        {
            return x.getArtist().size();
        }
        else
        {
            return x.getTitle().size();
        }
        
    }
}

string largerOfTwoString(Song x)
{
    if (x.getNameOnlyStatus())
    {
        return x.getName();
    }
    else
    {
        if (x.getArtist().size() > x.getTitle().size())
        {
            return x.getArtist();
        }
        else
        {
            return x.getTitle();
        }
        
    }
}

bool compareStringSizes(Song x,Song y)
{
    if (smallerOfTwo(x) != smallerOfTwo(y))
    {
        return (smallerOfTwo(x) < smallerOfTwo(y));
    }
    return (largerOfTwo(x) < largerOfTwo(y));

}

bool compareSongSimilarityIdentical(Song a, Song b)
{
    if (a.getOriginalName() == b.getOriginalName())
    {
        return true;
    }
    return false;
}

bool compareSongSimilarity(Song a, Song b)
{
    
    
    
    if ((global != 0) && (smallerOfTwo(a) <= 5 || smallerOfTwo(b) <= 5 || a.getTitle() == "intro" || a.getTitle() == "outro" || b.getTitle() == "intro" || b.getTitle() == "outro"  ))
    {
        return false;
    }
    

    if (!((a.getTitle() == "intro" && b.getTitle() == "outro")||(a.getTitle() == "outro" && b.getTitle() == "intro")))
    {
        
        if (a.getNameOnlyStatus() == b.getNameOnlyStatus())
        {
            if (a.getNameOnlyStatus())
            {
                if (updated_levenshtein(a.getName(),b.getName()) <= global)
                {
                    //outFS << a.getOriginalName() << endl;
                    //outFS << b.getOriginalName() << endl << endl;
                    return true;
                }
            }
            else
            {
                if ((updated_levenshtein(a.getArtist(),b.getArtist()) <= global) && (updated_levenshtein(a.getTitle(),b.getTitle())) <= global)
                {
                    //outFS << a.getOriginalName() << endl;
                    //outFS << b.getOriginalName() << endl << endl;
                    return true;
                }
            }
        }
        else
        {
            if (a.getNameOnlyStatus())
            {
                return compareSongSimilarity(b,a);
            }
            else
            {
                if (updated_levenshtein(a.getArtist(),b.getName()) <= global && updated_levenshtein(a.getTitle(),b.getName()) <= global)
                {
                    //outFS << a.getOriginalName() << endl;
                    //outFS << b.getOriginalName() << endl << endl;
                    return true;
                }
            }
        }
    }
    return false;
}

void retrieve(vector <Song> &p)
{
    
    string name;
    while (getline(inFS,name))
    {
        
        if (name.size() != 0)
        {
            Song current = Song(name);
            p.push_back(current);
        }
        
    }
}

void output(vector <Song> p, ofstream& file)
{
    for (unsigned int i = 0;i < p.size();++i)
    {
        file << p.at(i).getOriginalName() << endl;
    }
}

bool compareVectorSize(vector <Song> x, vector <Song> y)
{
    return (x.size() > y.size());
}

bool compareVectorAlpha(Song x, Song y)
{
    if (x.getNameOnlyStatus() == x.getNameOnlyStatus())
    {
        if (x.getNameOnlyStatus())
        {
            return x.getOriginalName() < y.getOriginalName();
        }
        else
        {
            if (x.getOriginalTitle() != y.getOriginalTitle())
            {
                return x.getOriginalTitle() < y.getOriginalTitle();
            }
            return x.getOriginalArtist() < y.getOriginalArtist();
        }
    }
    else
    {
        if (x.getNameOnlyStatus())
        {
            return compareVectorAlpha(y,x);
        }
        else
        {
            return x.getOriginalArtist() < y.getOriginalName();
        }
    }
}

void printDoubleVec(vector <vector <Song>> &x, vector <Song>& playlist)
{
    minimizeVec(playlist,globalIndexVector);
    sort(x.begin(), x.end(), compareVectorSize);
    int count = 0;
    for (unsigned int i = 0;i < x.size();++i)
    {
        if ((x.at(i).size() > 50) && (global != 0))
        {
            playlist.insert(playlist.end(),x.at(i).begin(),x.at(i).end());
            x.at(i).clear();
        }
        if (x.at(i).size() > 1)
        {
            sort(x.at(i).begin(),x.at(i).end(), compareStringSizes);
            for (unsigned int j = 0;j < x.at(i).size();++j)
            {
                outFS << x.at(i).at(j).getOriginalName() << endl;
                ++count;
            }
        outFS << endl;
        }
    }
    outFS << count << endl;
}

void match(vector <vector <Song>> &x, Song song,bool ((*c)(Song,Song)))
{
    bool matched = false;
    bool other = false;
    int markerOuter;
    for (unsigned int i = 0;i < x.size();++i)
    {
        for (unsigned int j = 0;j < x.at(i).size();++j)
        {
            if (c(x.at(i).at(j),song))
            {
                globalIndexVector.push_back(song.getIndex());
                globalIndexVector.push_back(x.at(i).at(j).getIndex());
                matched = true;
                if (other)
                {
                    x.at(i).insert(x.at(i).end(),x.at(markerOuter).begin(),x.at(markerOuter).end());
                    x.at(markerOuter).clear();
                }
                else
                {
                    x.at(i).push_back(song);
                    other = true;
                }
                markerOuter = i; 
                break;
            }
        }
    }
    if (!matched)
    {
        vector <Song> vec = {song};
        x.push_back(vec);
    }
}

void compareSongs(vector <Song> &x)
{
    vector <vector<Song>> groups;
    for (unsigned int i = 0; i < x.size();++i)
    {
        match(groups,x.at(i),compareSongSimilarity);
    }
    printDoubleVec(groups,x);
}

void compareSongsIdentical(vector <Song> &x)
{
    vector <vector<Song>> groups;
    for (unsigned int i = 0; i < x.size();++i)
    {
        match(groups,x.at(i),compareSongSimilarityIdentical);
    }
    printDoubleVec(groups,x);
}

void setIndexes(vector <Song>& x)
{
    for (unsigned int i = 0; i < x.size();++i)
    {
        x.at(i).setIndex(i);
    }
}
//int argc, char *argv[]
int main() 
{
    vector <Song> playlist;
    retrieve(playlist);
    setIndexes(playlist);
    compareSongsIdentical(playlist);

    for (unsigned int i = 1;i < 5;++i)
    {
        global = i;
        outFS << global << " |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<< endl;
        outFS << playlist.size() << endl;
        setIndexes(playlist);
        compareSongs(playlist);
    }
    for (unsigned int i = 0;i < playlist.size();++i)
    {
        outFS << playlist.at(i).getOriginalName() << endl;
    }
/*
    
    

    outFS << global << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<< endl;
    comparePlaylist(playlist,compareSongSimilarity,indexes);
    outFS << playlist.size() << " songs compared" << endl; 
    outFS << indexes.size() << " songs matched" << endl;
    minimizeVec(playlist,indexes);
    outFS << playlist.size() << " songs left" << endl;
    */
}
