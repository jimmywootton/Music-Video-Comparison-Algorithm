#ifndef SONG_H
#define SONG_H

#include <iostream> 
#include <string>
using namespace std;
#include "modified.h"

class Song
{
    private:
        string originalName;
        string originalArtist;
        string originalTitle;
        string name;
        string artist;
        string title;
        bool nameOnly;
        int index;
    public:
        Song(string x);
        /*
        void setOriginalName(string x);
        void setOriginalArtist(string x);
        void setOriginalTitle(string x);
        void setName(string x);
        void setArtist(string x);
        void setTitle(string x);
        */
        int getIndex() const;
        void setIndex(int i);
        bool getNameOnlyStatus() const;
        string getOriginalName() const;
        string getOriginalArtist() const;
        string getOriginalTitle() const;
        string getName() const;
        string getArtist() const;
        string getTitle() const;
};

Song::Song(string x)
{
    removeMP3(x);
    nameOnly = true;
    originalName = x;

    name = modifiedString(x);

    if (x.find(" - ") != string::npos)
    {
        
        nameOnly = false;
        string tempArtist = x.substr(0,x.find(" - "));
        string tempTitle = x.substr(x.find(" - ") + 3);
        originalArtist = tempArtist;
        originalTitle = tempTitle;
        artist = modifiedString(tempArtist);
        title = modifiedString(tempTitle);
        if (title.size() == 0)
        {
            *this = Song(originalArtist);
        }
        else if (artist.size() == 0)
        {
            *this = Song(originalTitle);
        }
    }

}
/*
void Song::setOriginalName(string x)
{
    originalName = x;
}

void Song::setOriginalArtist(string x)
{
    originalArtist = x;
}

void Song::setOriginalTitle(string x)
{
    originalTitle = x;
}

void Song::setName(string x)
{
    name = x;
}

void Song::setArtist(string x)
{
    artist = x;
}

void Song::setTitle(string x)
{
    title = x;
}
*/

void Song::setIndex(int i)
{
    index = i;
}

int Song::getIndex() const
{
    return index;
}

bool Song::getNameOnlyStatus() const
{
    return nameOnly;
}

string Song::getOriginalName() const
{
    return originalName;
}

string Song::getOriginalArtist() const
{
    return originalArtist;
}

string Song::getOriginalTitle() const
{
    return originalTitle;
}

string Song::getName() const
{
    return name;
}

string Song::getArtist() const
{
    return artist;
}

string Song::getTitle() const
{
    return title;
}

#endif