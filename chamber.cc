#include "chamber.h"
#include <stdlib.h>
#include "character.h"
#include "item.h"
#include <time.h>

Chamber::Chamber(int i, std::vector<std::vector<char>>& g):id{i}, grid{g}{
switch (id){
    case 0:
        topLeftX = 3;
        topLeftY = 3;
        width = 26;
        height = 4;
        break;
    case 1:
        topLeftX = 39;
        topLeftY = 3;
        width = 37;
        height = 10;
        break;
    case 2:
        topLeftX = 38;
        topLeftY = 10;
        width = 12;
        height = 3;
        break;
    case 3:
        topLeftX = 3;
        topLeftY = 15;
        width = 21;
        height = 7;
        break;
    case 4:
        topLeftX = 37;
        topLeftY = 16;
        width = 39;
        height = 6;
        break;
    }
}

bool Chamber::validPos(int x, int y){
    bool valid = false;
    if (x < topLeftX+width && y < topLeftY+height && x>=topLeftX && y>=topLeftY){
        if (grid[y][x]=='.'){
            valid = true;
        }
    }if(id == 1){
        if(x >= topLeftX && y >= 7 && x <= 60) valid = false;
    }return valid;
}

//Generates the char in random position within range of this Chamber, returns the position
std::vector<int> Chamber::generateCharRand(char c){
    // std::cout<<"generate char"<<std::endl;
    int x;
    int y;
    while(true){
        std::srand(time(NULL));
        x = (rand() % width) + topLeftX;
        y = (rand() % height) + topLeftY;
        if (validPos(x,y)){
            grid[y][x] = c;
            break;
        }
    }std::vector<int> pos;
    pos.emplace_back(x);
    pos.emplace_back(y);
    // std::cout<<pos[0]<<" "<<pos[1]<<std::endl;
    return pos;
}
