#ifndef MODIFIED_H
#define MODIFIED_H

#include <iostream> 
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

void removeMP3(string & str)
{
    if (str.length() >= 4 && str.substr(str.length() - 4) == ".mp3") 
    {
        str.erase(str.length() - 4);
    }
}

void removeParentheses(string & str) 
{
    vector <char > start = {'(','{','[',};
    vector <char> end = {')','}',']',};
    for (unsigned int i = 0;i  < 3;++i)
    {
        size_t start_pos = str.find(start.at(i));
        size_t end_pos = str.find(end.at(i));
        while (start_pos != string::npos && end_pos != string::npos && end_pos > start_pos) 
        {
            str.erase(start_pos, end_pos - start_pos + 1);
            start_pos = str.find(start.at(i));
            end_pos = str.find(end.at(i));
        }
    }
}

void makeLowerCase(string& s) 
{
    transform(s.begin(), s.end(), s.begin(), ::tolower);
}

void replaceString(string& str, const string& oldStr, const string& newStr)
{
    size_t pos = 0;
    while ((pos = str.find(oldStr, pos)) != string::npos) 
    {
        str.replace(pos, oldStr.length(), newStr);
        pos += newStr.length();
    }
}

void addSpaces(string& str) 
{
    str = " " + str + " ";
}

void removeStrings(string & s)
{
    size_t pos;
    //" outro "," intro "," shouts out "," shout out "," shouts "," shout "," skit "," mix ",
    vector <string> words = {" vol."," ft."," pt."," feat."};
    for (unsigned int i = 0;i < words.size();++i)
    {
        pos = s.find(words.at(i));
        while (pos != string::npos) 
        {
            s.erase(pos + 1, words.at(i).size());
            pos = s.find(words.at(i), pos);
        }
    }
    words = {"☠","＂","：","？","’""","`","+","!","&",":", "\"","'",".",",","?","(",")","[","]","{","}",};
    for (unsigned int i = 0;i < words.size();++i)
    {
        pos = s.find(words.at(i));
        while (pos != string::npos) 
        {
            s.erase(pos, words.at(i).size());
            pos = s.find(words.at(i), pos);
        }
    }
    words = {"z ","s "," presents "," greatest hits "," track "," volume "," and "," that "," dat "," part "," remix "," click "," klick "," clique "," by "," the "," da "," ft ", " pt "," dj "," productions "," produced "," dragged "," chopped "," screwed "," production "," tha ", " family ", " mafia "," instrumental ", " dis ", " this "};
    for (unsigned int i = 0;i < words.size();++i)
    {
        pos = s.find(words.at(i));
        while (pos != string::npos) 
        {
            s.erase(pos, words.at(i).size() - 1);
            //cout << s << endl;
            pos = s.find(words.at(i), pos);
        }
    }


}

void removeExtraSpaces(string& s) {
    string result;
    bool previous_space = false;
    for (char c : s) 
    {
        if (c == ' ') {
            if (!previous_space) 
            {
                result += c;
            }
            previous_space = true;
        }
        else 
        {
            result += c;
            previous_space = false;
        }
    }
    s = result;
}

void trimSpaces(string& str) 
{
    while (!str.empty() && str.front() == ' ') 
    {
        str.erase(0, 1);
    }
    while (!str.empty() && str.back() == ' ') 
    {
        str.erase(str.length() - 1, 1);
    }
}

string noYear(string &str)
{
    size_t pos = 0;
    while ((pos = str.find(" ", pos)) != string::npos) {
        if (isdigit(str[pos + 1]) && isdigit(str[pos + 2]) && isdigit(str[pos + 3]) && isdigit(str[pos + 4])) {
            str.erase(pos + 1, 5);
        } else {
            ++pos;
        }
    }
    return str;
}



string modifiedString(string input)
{
    removeMP3(input);
    removeParentheses(input);
    makeLowerCase(input);
    addSpaces(input);
    noYear(input);
    removeStrings(input);
    replaceString(input,"-"," ");
    replaceString(input,"/"," ");
    replaceString(input,"⧸"," ");
    replaceString(input,"in ","ing ");
    replaceString(input,"en ","ing ");
    replaceString(input,"cc ","ck ");
    replaceString(input," u "," you ");
    replaceString(input," your "," you ");
    replaceString(input," ya "," you ");
    replaceString(input," yo "," you ");
    replaceString(input,"z ","s ");
    replaceString(input," 2 "," to ");
    replaceString(input," too "," to ");
    removeExtraSpaces(input);
    trimSpaces(input);
    if (input == " ")
    {
        input = "";
    }

    return input;
}

#endif