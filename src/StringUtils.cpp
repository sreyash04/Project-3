#include "StringUtils.h"
#include <cstdio>
#include <cctype>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>
namespace StringUtils{

std::string Slice(const std::string &str, ssize_t start, ssize_t end) noexcept{
    return str.substr(start,str.length()-start);
}

std::string Capitalize(const std::string &str) noexcept{
    auto Copy = str;

    Copy[0] = toupper(str[0]);
    for(size_t Index = 1; Index <Copy.length(); Index++){
        Copy[Index]= tolower(Copy[Index]);
    }
    return Copy; 
}

std::string Upper(const std::string &str) noexcept{
    auto Copy = str;
    for(size_t Index = 0; Index <Copy.length(); Index++){
        Copy[Index]= toupper(Copy[Index]);
    }
    return Copy;
}

std::string Lower(const std::string &str) noexcept{
    auto Copy = str;
    for(size_t Index = 0; Index <Copy.length(); Index++){
        Copy[Index]= tolower(Copy[Index]);
    }
    return Copy;
}

std::string LStrip(const std::string &str) noexcept {
    auto Copy = str;
    //AI Generated 1 see README
    auto Index = Copy.begin();
    while (Index != Copy.end() && std::isspace(*Index)) {
        ++Index;
    }
    Copy.erase(Copy.begin(), Index);
    return Copy;
}

std::string RStrip(const std::string &str) noexcept{
    auto Copy = str;
    std::reverse(Copy.begin(), Copy.end());
    auto Index = Copy.begin();
    while (Index != Copy.end() && std::isspace(*Index)) {
        ++Index;
    }
    Copy.erase(Copy.begin(), Index);
    std::reverse(Copy.begin(), Copy.end());
    return Copy;
}

std::string Strip(const std::string &str) noexcept{
    auto Copy = str;
    auto Index = Copy.begin();
    while (Index != Copy.end() && std::isspace(*Index)) {
        ++Index;
    }
    Copy.erase(Copy.begin(), Index);
    std::reverse(Copy.begin(), Copy.end());
    auto Index2 = Copy.begin();
    while (Index2 != Copy.end() && std::isspace(*Index2)) {
        ++Index2;
    }
    Copy.erase(Copy.begin(), Index2);
    std::reverse(Copy.begin(), Copy.end());
    return Copy;
}

std::string Center(const std::string &str, int width, char fill) noexcept{
    auto Copy = str;
    int toAdd = width - Copy.length();
    int toAddLeft = toAdd/2;
    int toAddRight = toAdd/2;
    if (toAdd % 2 ==1){
        toAddRight+=1;
    }
    return std::string(toAddLeft, fill)+ Copy + std::string(toAddRight, fill) ;//string function from stackoverflow see code reference 4
}

std::string LJust(const std::string &str, int width, char fill) noexcept{
    auto Copy =str;
    int toAdd = width - Copy.length();
    return Copy + std::string(toAdd, fill); //string function from stackoverflow see code reference 4
}

std::string RJust(const std::string &str, int width, char fill) noexcept{
    auto Copy =str;
    int toAdd = width - Copy.length();
    return std::string(toAdd, fill)+ Copy; //string function from stackoverflow see code reference 4
}

std::string Replace(const std::string &str, const std::string &old, const std::string &rep) noexcept {
    if (old.empty()) { //handles replacing empty string edge case
        std::string CopyEmpty;
        for (char ch : str) {
            CopyEmpty += rep + ch;
        }
        CopyEmpty += rep; 
        return CopyEmpty;
    }

    auto copy = str;
    int oldLength = old.length();
    int oldIndex = 0;
    int startIndex = -1;

    for (size_t index = 0; index < copy.length();) {
        if (copy[index] == old[oldIndex]) {
            if (startIndex == -1) {
                startIndex = index;
            }
            oldIndex++;

            if (oldIndex == oldLength) {
                copy.replace(startIndex, oldLength, rep); //code reference 5
                index = startIndex + rep.length();
                oldIndex = 0;
                startIndex = -1;
                continue;
            }
        } else {
            if (startIndex != -1) {
                oldIndex = 0;
                index = startIndex;
                startIndex = -1;
            }
        }
        index++;
    }
    return copy;
}

std::vector< std::string > Split(const std::string &str, const std::string &splt) noexcept{
    std::vector<std::string> result;
    if (str.empty()) {
        return result; 
    }
    int start = 0;
    int end = 0;

    if (splt.empty()) { //edge case no split character given, split on whitespace
        while (start < str.size()) {
            while (start < str.size() && std::isspace(str[start])) {
                ++start;
            }
            if (start >= str.size()){
                 break;
            }
            end = start;
            while (end < str.size() && !std::isspace(str[end])) {
                ++end;
            }
            result.push_back(str.substr(start, end - start)); //code reference 7
            start = end;
        }
    } else {
        while (start < str.size()+1) { //+1 to account for split at end
            end = str.find(splt, start); // code reference 6

            if (end == std::string::npos) {
                result.push_back(str.substr(start));
                break;
            }
            result.push_back(str.substr(start, end - start));
            start = end + splt.size();
        }
    }
    return result;
}

std::string Join(const std::string &str, const std::vector< std::string > &vect) noexcept{
    std::string result;
    for (size_t Index = 0; Index < vect.size(); ++Index) {
        result += vect[Index];
        if (Index < vect.size() - 1) {
            result += str;
        }
    }
    return result;
}

std::string ExpandTabs(const std::string &str, int tabsize) noexcept{
    std::string result = str;
    int pos = 0;
    while ((pos = result.find('\t', pos)) != std::string::npos) {
        int spaces = tabsize - (pos % tabsize);
        result.replace(pos, 1, std::string(spaces, ' '));
        pos += spaces;
    }
    return result;
}
    
int EditDistance(const std::string &left, const std::string &right, bool ignorecase) noexcept{
if (left.empty()){
        return right.length();
    }
    if (right.empty()) {
        return left.length();
    }

    char leftChar;
    char rightChar;
    int distance;
    if (ignorecase) {
        leftChar = tolower(left.back()); //back function from StackOverflow see code reference 8
        rightChar = tolower(right.back());
    } else {
        leftChar = left.back();
        rightChar = right.back();
    }
    if (leftChar != rightChar) {
        distance = 1;
    } else {
        distance = 0;
    }
    return std::min({ //AI Generated 3
        EditDistance(left.substr(0, left.length() - 1), right, ignorecase) + 1, //delete
        EditDistance(left, right.substr(0, right.length() - 1), ignorecase) + 1, //inset
        EditDistance(left.substr(0, left.length() - 1), right.substr(0, right.length() - 1), ignorecase) + distance //change
    });
}

};