#ifndef _CHAMBER_H_
#define _CHAMBER_H_
#include <vector>
#include <memory>

// class Player;
// class Enemy;
// class Potion;
class Item;
class Character;

class Chamber{
private:
    int id;
    int topLeftX;
    int topLeftY;
    int width;
    int height;
    std::vector<std::vector<char>>& grid; //or pointer ?

public:
    Chamber(int, std::vector<std::vector<char>>&);

    ~Chamber(){}

    //Generates the char in random position within range of this Chamber, returns the position
    std::vector<int> generateCharRand(char); 

    bool validPos(int, int);
   
};

#endif
