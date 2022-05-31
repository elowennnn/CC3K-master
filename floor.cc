#include "floor.h"
#include "player.h"
#include "enemy.h"
#include "enemy/human.h"
#include "enemy/dwarf.h"
#include "enemy/elf.h"
#include "enemy/halfling.h"
#include "enemy/dragon.h"
#include "enemy/merchant.h"
#include "enemy/orcs.h"

#include "potion.h"

#include "treasure.h"
#include "treasure/sHoard.h"
#include "treasure/gold.h"
#include "treasure/mHoard.h"
#include "treasure/dHoard.h"

#include "chamber.h"
#include "character.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <algorithm>
#include <vector>


Floor::Floor(std::vector<std::vector<char>> grid, int id):grid{grid},id{id}{
}

Floor::Floor(int id):id{id}{
}

void Floor::print(){
    for (int i = 0; i < 25; ++i) {
        for (int j = 0; j < 79; ++j) {
            std::cout<<grid[i][j];
        }std::cout<<std::endl;
    }
    std::cout<<"Race: "<< player->getType() <<" Gold: " << player->getGold();
    std::cout<<std::setw(56)<<std::right<< "Floor "<< id+1 <<std::endl;
    std::cout<<"Hp: "<< player->getHP()<<std::endl;
    std::cout<<"Atk: "<< player->getAtk() <<std::endl;
    std::cout<<"Def: "<< player->getDF() <<std::endl;
    std::cout<<"Action: "<< action <<std::endl;
    action = "";
}

int Floor::getId(){
    return id;
}

std::shared_ptr<Player> Floor::getPlayer(){
    return player;
}

std::vector<std::shared_ptr<Enemy>> Floor::getEnemies(){
    return enemies;
}

std::vector<std::shared_ptr<Potion>> Floor::getPotions(){
    return potions;
}

std::vector<std::shared_ptr<Treasure>> Floor::getTreasures(){
    return treasures;
}

std::vector<std::shared_ptr<Chamber>> Floor::getChambers(){
    return chambers;
}

void Floor::setAction(std::string s){
    action += s;
}

bool Floor::getReachStair(){
    return reachStair;
}

void Floor::generateChambers(){
    for (int i=0; i<5; ++i) {
        auto chamber = std::make_shared<Chamber> (i, grid);
        chambers.emplace_back(chamber);
    }
}

void Floor::generatePlayer(std::shared_ptr<Player> p){
    std::srand(time(NULL));
    int i = rand() % 5;
    std::vector<int> position = (chambers[i])->generateCharRand('@');
    p->setChamber(i);
    p->setRow(position[1]);
    p->setCol(position[0]);
    p->setOrigin('.');
    player = p;
}

void Floor::generatePotion(std::shared_ptr<Potion> p){
    std::srand(time(NULL));
    int i = rand() % 5;
    std::vector<int> position = (chambers[i])->generateCharRand('P');
    p->setRow(position[1]);
    p->setCol(position[0]);
    potions.emplace_back(p);
}


void Floor::generateTreasure(std::shared_ptr<Treasure> t){
     std::srand(time(NULL));
     int i = rand() % 5;
     std::vector<int> position = (chambers[i])->generateCharRand('G');
     t->setRow(position[1]);
     t->setCol(position[0]);
     treasures.emplace_back(t);
}


void Floor::generateEnemy(std::shared_ptr<Enemy> e){
    std::srand(time(NULL));
    int i = rand() % 5;
    std::vector<int> position = (chambers[i])->generateCharRand(e->getType());
    e->setRow(position[1]);
    e->setCol(position[0]);
    enemies.emplace_back(e);
}


void Floor::generateStair(){
    int i;
    while(true){
        std::srand(time(NULL));
        i = rand() % 5;
        if(i != player->getChamberID()) break;
    }
    (chambers[i])->generateCharRand('\\');
}

void Floor::generateAll(std::shared_ptr<Player> p){
    action = "Player enters the floor";
    generateChambers();
    generatePlayer(p);
    generateStair();
    // generate 10 rand potions
    for(int i=0; i<10; ++i){
        std::srand(time(NULL));
        int type = rand() % 6;
        std::shared_ptr<Potion> potion = std::make_shared<Potion>(0, 0, type);
        generatePotion(potion);
    }
    // gold: 5/8 chance of normal, 1/8 dragon hoard, 2/8 small hoard
    //6 - normal gold pile, 7 - small hoard, 8 - merchant hoard (DNE), 9 - dragon hoard
    for(int i=0; i<10; ++i){
        std::srand(time(NULL));
        int type = rand() % 8;
        std::shared_ptr<Treasure> t;
        std::shared_ptr<Dragon> d;
        if(type < 5){
            t = std::make_shared<Gold>();
        }
        else if (type <= 5){
            std::shared_ptr<Dhoard> hoard;
            hoard = std::make_shared<Dhoard>();
            d = std::make_shared<Dragon>();
            d->setDhoard(hoard);
            enemies.emplace_back(d);
            generateTreasure(hoard);
            int pos = treasures.size();
            int y = treasures[pos-1]->getRow();
            int x = treasures[pos-1]->getCol();
            int acc = 0;
            for (int i = y-1; i <= y+1; i++){
                if (acc == 1){
                    break;
                }
                for (int j = x-1; j <= x+1; j++){
                    if (grid[i][j] == '.'){
                        d->setRow(i);
                        d->setCol(j);
                        grid[i][j] = 'D';
                        acc++;
                        break;
                    }
                }
            }
            continue;
        }
        else{
            t = std::make_shared<Shoard>();
        }
        generateTreasure(t);
    }
    for(int i=0; i<20; ++i){
        concreteType t{'H'};
        std::shared_ptr<Enemy> e;
        std::srand(time(NULL));
        int type = rand() % 18;
        if(type < 4){
            t.setType('H');
            e = t.getEnemy();
        }
        else if (type < 7){
            t.setType('W');
            e = t.getEnemy();
        }
        else if (type < 12){
            t.setType('L');
            e = t.getEnemy();
        }
        else if (type < 14){
            t.setType('E');
            e = t.getEnemy();
        }
        else if (type < 16){
            t.setType('O');
            e = t.getEnemy();
        }
        else{
            t.setType('M');
            e = t.getEnemy();
        }
        generateEnemy(e);
    }
}

int Floor::treasureAt(int row, int col){
    int sizeTreasure = treasures.size();
    int at = -1;
    for(int i = 0; i < sizeTreasure; i++){
        if(treasures[i]->getCol() == col && treasures[i]->getRow() == row){
            at = i;
            break;
        }
    }
    return at;
}

int Floor::potionAt(int row, int col){
    int sizePotion = potions.size();
    int at = -1;
    for(int i = 0; i < sizePotion; i++){
        if(potions[i]->getCol() == col && potions[i]->getRow() == row){
            at = i;
            break;
        }
    }
    return at;
}

//helper
bool Floor::isRegularEnemy(int row, int col){
    if (grid[row][col] == 'W' || grid[row][col] == 'E' || grid[row][col] == 'O' || grid[row][col] == 'L'){
            return true;
        }
    else{
        return false;
    }
}

// return the index of enemy at grid[row][col] in the vector of enemies. 
int Floor::enemyAt(int row, int col){
    int sizeEnemy = enemies.size();
    int at = -1;
    for(int i = 0; i < sizeEnemy; i++){
        if(enemies[i]->getCol() == col && enemies[i]->getRow() == row){
            at = i;
            break;
        }
    }
    return at;
}

// Enemies detect whether there's player within 1 block around. 
void Floor::enemyAttackPlayer(){
    int prow = player->getRow();
    int pcol = player->getCol();
    int acc = -1;
    for (int y = prow-1; y <= prow+1; y++){
        for (int x = pcol-1; x <= pcol+1; x++){
            if (isRegularEnemy(y, x) || grid[y][x] == 'H' || grid[y][x] == 'M' || grid[y][x] == 'D'){
                int at = enemyAt(y, x);
                if (at == acc){
                    break;
                }
                if (enemies[at]->getHostile() == true){
                    player->accept(*enemies[at]);
                    char c = enemies[at]->getType();
                    std::string s;
                    s.push_back(c);
                    action += "Enemy " + s+ " attacked player. ";
                    acc = at;
                }
            }
            else if (grid[y][x] == 'G'){
                int at = treasureAt(y, x);
                if (treasures[at]->getType() == 9){
                    int size = enemies.size();
                    for(int i = 0; i < size; i++){
                        if (i == acc){
                            break;
                        }
                        std::shared_ptr<Dragon> dragon;
                        if (enemies[i]->getType() == 'D'){
                            dragon = std::dynamic_pointer_cast<Dragon> (enemies[i]);
                        }
                        else{
                            continue;
                        }
                        if (dragon->getDhoard() == treasures[at]){
                            player->accept(*enemies[i]);
                            acc = i;
                            break;
                        }
                    }
                }
            }
        }
    }
    if (player->getHP() <= 0){
        player->setAlive(false);
        action += "\nYour character is dead. GG";
    }
}

void Floor::EnemymoveHelper(int at){
    std::vector<int> pos;
    int acc = 0;
    int erow = enemies[at]->getRow();
    int ecol = enemies[at]->getCol();
    for(int i = erow-1; i <= erow+1; i++){
        for(int j = ecol-1; j <= ecol+1; j++){
            if (grid[i][j] == '.'){
                acc += 1;
                pos.emplace_back(i);
                pos.emplace_back(j);
            }
        }
    }
    std::srand(time(NULL));
    int k = rand() % acc;
    k *= 2;
    int y = pos[k];
    int x = pos[k+1];
    enemies[at]->setRow(y);
    enemies[at]->setCol(x);
    grid[y][x] = enemies[at]->getType();
    grid[erow][ecol] = '.';
}

void Floor::Enemymove(){
    std::vector<int> track;
    for(int y = 0; y < 25; y++){
        for (int x = 0; x < 79; x++){
            if (isRegularEnemy(y,x) || grid[y][x] == 'H' || grid[y][x] == 'M'){
                int prow = player->getRow();
                int pcol = player->getCol();
                if (y >= prow-1 && y <= prow + 1 && x >= pcol-1 && x <= pcol + 1){
                    break;
                }
                int at = enemyAt(y, x);
                std::vector<int>::iterator it = std::find(track.begin(), track.end(), at);
                if (it == track.end()){
                    track.emplace_back(at);
                    EnemymoveHelper(at);
                }
            }
        }
    }
}

std::vector<int> Floor::nextMove(std::string str){
    std::vector<int> pos;
    int row = player->getRow();
    int col = player->getCol();
    if (str == "no"){
        row -= 1;
    }
    else if (str == "so"){
        row += 1;
    }
    else if (str == "ea"){
        col += 1;
    }
    else if (str == "we"){
        col -= 1;
    }
    else if (str == "ne"){
        row -= 1;
        col += 1;
    }
    else if (str == "nw"){
        row -= 1;
        col -= 1;
    }
    else if (str == "se"){
        row += 1;
        col += 1;
    }
    else if (str == "sw"){
        row += 1;
        col -= 1;
    }
    pos.emplace_back(row);
    pos.emplace_back(col);
    return pos;
}

void Floor::playerAttack(std::string str){
    std::vector<int> pos = nextMove(str);
    int y = pos[0];
    int x = pos[1];
    if (isRegularEnemy(y, x) || grid[y][x] == 'H' || grid[y][x] == 'M' || grid[y][x] == 'D'){
        int at = enemyAt(y, x);
        player->attackEnemy(enemies[at]);
        char c = enemies[at]->getType();
        std::string s;
        s.push_back(c);
        action += "Player attacked enemy " + s + ". ";
        // if the enemy that player attack is a merchant, all merchants are set to be hostile.  
        if (grid[y][x] == 'M'){
            int s = enemies.size();
            for(int i = 0; i < s; i++){
                if (enemies[i]->getType() == 'M'){
                    enemies[i]->setHostile(true);
                }
            }
        }
        if(enemies[at]->getHP() <= 0){
            action += s + " is defeated!! ";
            if (isRegularEnemy(y,x)){
                std::srand(time(NULL));
                int i = rand() % 2;
                if (i == 0){
                    player->addGold(1);
                    action += "You gained a small pile of gold. ";
                }
                else{
                    player->addGold(2);
                    action += "You gained a normal pile of gold. " ;
                }
                grid[y][x] = '.';
            }
            else if (grid[y][x] == 'H'){
                grid[y][x] = 'G';
                auto normal1 = std::make_shared<Gold>();
                normal1->setRow(y);
                normal1->setCol(x);
                treasures.emplace_back(normal1);
                int acc = 0;
                // Another normal pile a generated nearby. 
                for(int i = y-1 ; i <= y+1; i++){
                    if (acc == 1){
                        break;
                    }
                    for(int j = x-1 ; j <= x+1; j++){
                        if (grid[i][j] == '.'){
                            grid[i][j] = 'G';
                            auto normal = std::make_shared<Gold>();
                            normal->setRow(i);
                            normal->setCol(j);
                            treasures.emplace_back(normal);
                            acc += 1;
                            break;
                        }
                    }
                }
                std::cout<< "Two normal piles of gold are dropped. " << std::endl;
            }
            else if (grid[y][x] == 'M'){
                auto merchantH = std::make_shared<Mhoard>();
                grid[y][x] = 'G';
                merchantH->setRow(y);
                merchantH->setCol(x);
                treasures.emplace_back(merchantH);
                std::cout << "A Merchant Hoard is dropped! " << std::endl;
            }
            else{
                std::shared_ptr<Dragon> dragon = std::dynamic_pointer_cast<Dragon> (enemies[at]);
                grid[y][x] = '.';
                dragon->getDhoard()->setPick(true);
                std::cout << "Dragon Hoard can be picked now! " << std::endl;
            }
            enemies.erase(enemies.begin()+at);
        }
    }
    else{
        action += "No enemy in this direction. ";
    }
}

void Floor::clearFloor(){   
    // int a = enemies.size();
    // for (int i = 0; i < a; i++){
    //     int x = enemies[0]->getCol();
    //     int y = enemies[0]->getRow();
    //     grid[y][x] = '.';
    //     enemies.erase(enemies.begin());
    // }
    enemies.clear();
    // a = treasures.size();
    // for (int i = 0; i < a; i++){
    //     int x = treasures[0]->getCol();
    //     int y = treasures[0]->getRow();
    //     grid[y][x] = '.';
    //     treasures.erase(treasures.begin());
    // }
    treasures.clear();
    // a = potions.size();
    // for (int i = 0; i < a; i++){
    //     int x = potions[0]->getCol();
    //     int y = potions[0]->getRow();
    //     grid[y][x] = '.';
    //     potions.erase(potions.begin());
    // }
    potions.clear();
    chambers.clear();
    for (int i = 0; i < 25; i++){
        for(int j=0; j<79; ++j){
            if(grid[i][j]!='.'&&grid[i][j]!='-'&&grid[i][j]!='|'&&grid[i][j]!='+'&&grid[i][j]!='#'&&grid[i][j]!=' '){
                grid[i][j]='.';
            }
        }
    }
    reachStair = false;
    // int x = player->getCol();
    // int y = player->getRow();
    // grid[y][x] = '.';
}


void Floor::playerMove(std::string str){
    std::vector<int> pos = nextMove(str);
    int y = pos[0];
    int x = pos[1];
    int r = player->getRow();
    int c = player->getCol();
    if (grid[y][x] == '.' || grid[y][x] == '+' ||  grid[y][x] == '#'){
        player->move(str);
        grid[r][c] = player->getOrigin();
        player->setOrigin(grid[y][x]);
        grid[y][x] = '@';
        action += "Player moved in "+str+" direction. ";
    }
    else if(grid[y][x] == '\\'){
        reachStair = true;
        grid[r][c] = player->getOrigin();
        grid[y][x] = '@';
    }
    else if (grid[y][x] == 'G'){
        int at = treasureAt(y, x);
        if (treasures[at]->getPick() == true){
            int amt = treasures[at]->getAmt();
            player->addGold(amt);
            action= "Player picked up "+std::to_string(amt);
            action +=" gold. ";
            player->move(str);
            grid[r][c] = player->getOrigin();
            player->setOrigin('.');
            grid[y][x] = '@';
            treasures.erase(treasures.begin()+at);
        }
        else{
            action += "Treasure cannot be picked. ";
        }
    }
    else{
        action += "Invalid movement. ";
    }
}

void Floor::playerUsePotion(std::string str){
    std::vector<int> pos = nextMove(str);
    int y = pos[0];
    int x = pos[1];
    if (grid[y][x] == 'P'){
        int at = potionAt(y, x);
        if (potions[at]->getType() == 1 || potions[at]->getType() == 2 || potions[at]->getType() == 4 || potions[at]->getType() == 5){
            player->addPotion(potions[at]);
        }
        player->usePotion(potions[at]);
        std::string temp;
        switch(potions[at]->getType()){
        case 0:
            temp = "RH";
            break;
        
        case 1:
            temp = "BA";
            break;

        case 2:
            temp = "BD";
            break;
        
        case 3:
            temp = "PH";
            break;
                
        case 4:
            temp = "WA";
            break;
            
        case 5:
            temp = "WD";
            break;
        }
        action += "Player used potion " + temp + ". ";
        potions.erase(potions.begin()+at);
        grid[y][x] = '.';
    }
    else{
        action += "No potion in this direction. ";
    }
}

void Floor::printScore(){
    double gold = player->getGold();
    if(player->getType()=="Shade"){
        gold = gold * 1.5;
    }
    std::cout<<"Congratulations, you won! Your score is "<<gold<<std::endl;
}

void Floor::readFromFile(std::shared_ptr<Player> p){
    player = p;
    for(int row = 0; row<25; ++row){
        for(int col = 0; col<79; ++col){
            if(grid[row][col]=='@'){
                player->setRow(row);
                player->setCol(col);
                player->setOrigin('.');
            }else if(grid[row][col]=='M'){
                std::shared_ptr<Merchant> e = std::make_shared<Merchant>();
                e->setRow(row);
                e->setCol(col);
                e->setOrigin('.');
                enemies.emplace_back(e);
            }else if(grid[row][col]=='O'){
                std::shared_ptr<Orcs> e = std::make_shared<Orcs>();
                e->setRow(row);
                e->setCol(col);
                e->setOrigin('.');
                enemies.emplace_back(e);
            }else if(grid[row][col]=='D'){
                std::shared_ptr<Dragon> e = std::make_shared<Dragon>();
                e->setRow(row);
                e->setCol(col);
                e->setOrigin('.');
                std::shared_ptr<Dhoard> t = std::make_shared<Dhoard>();
                for(int r=row-1; r<=row+1; ++r){
                    for(int c=col-1; c<=col+1; ++c){
                        if(grid[r][c]=='9'){
                            t->setRow(r);
                            t->setCol(c);
                            grid[r][c] = 'G';
                            break;
                        }
                    }
                }
                t->setOrigin('.');
                e->setDhoard(t);
                enemies.emplace_back(e);
                treasures.emplace_back(t);
            }else if(grid[row][col]=='W'){
                std::shared_ptr<Dwarf> e = std::make_shared<Dwarf>();
                e->setRow(row);
                e->setCol(col);
                e->setOrigin('.');
                enemies.emplace_back(e);
            }else if(grid[row][col]=='E'){
                std::shared_ptr<Elf> e = std::make_shared<Elf>();
                e->setRow(row);
                e->setCol(col);
                e->setOrigin('.');
                enemies.emplace_back(e);
            }else if(grid[row][col]=='L'){
                std::shared_ptr<Halfling> e = std::make_shared<Halfling>();
                e->setRow(row);
                e->setCol(col);
                e->setOrigin('.');
                enemies.emplace_back(e);
            }else if(grid[row][col]=='H'){
                std::shared_ptr<Human> e = std::make_shared<Human>();
                e->setRow(row);
                e->setCol(col);
                e->setOrigin('.');
                enemies.emplace_back(e);
            }else if(grid[row][col]=='6'){
                std::shared_ptr<Gold> g = std::make_shared<Gold>();
                g->setRow(row);
                g->setCol(col);
                g->setOrigin('.');
                treasures.emplace_back(g);
                grid[row][col]='G';
            }else if(grid[row][col]=='7'){
                grid[row][col]='G';
                std::shared_ptr<Shoard> g = std::make_shared<Shoard>();
                g->setRow(row);
                g->setCol(col);
                g->setOrigin('.');
                treasures.emplace_back(g);
            }else if(grid[row][col]=='0'||grid[row][col]=='1'||grid[row][col]=='2'||grid[row][col]=='3'||grid[row][col]=='4'||grid[row][col]=='5'){
                int a = grid[row][col] - '0';
                std::shared_ptr<Potion> p = std::make_shared<Potion>(row, col, a);
                potions.emplace_back(p);
                grid[row][col]='P';
            }
        }
    }
    reachStair = false;
}
