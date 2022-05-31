#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>

#include "floor.h"

#include "player.h"
#include "enemy.h"


std::string fileName ="defaultfloor.txt";

std::vector<std::shared_ptr<Floor>> floors;

std::vector<std::vector<std::vector<char>>>fileContent;

bool readFile = false;

int main(int argc, char* argv[]) {
    if (argc > 1) {
        fileName = argv[1];
        readFile = true;
    }
    std::ifstream file(fileName);
    if(!file.good()){
        std::cout<<"File is invalid.";
        exit(1);
    }
    std::vector<std::vector<char>> grid;
    std::string s;
    std::vector<char> line;
    int id = 0;
    int row = 0;
    int col = 79;
    while (std::getline(file, s)){
        for(int i=0; i<col; ++i){
            line.emplace_back(s[i]);            
            // std::cout<<"---char---"<<line[i]<<std::endl;
        }grid.emplace_back(line);
        ++row;
        s = "";
        line.clear();
        if(row==25){
            floors.emplace_back(std::make_shared<Floor>(grid, id));
            fileContent.emplace_back(grid);
            grid.clear();
            ++id;
            row = 0;
        }
    }
    bool restart= true;
    while (restart){
        restart = false;
        std::cout<<"Please choose your character: \ns for shade(defualt), d for drow, v for vampire, t for troll, g for goblin"<<std::endl;
        char playerChar;
        std::shared_ptr<Player> player;
        while (true){
            std::cin>>playerChar;
            if (playerChar == 'd'){
                player = std::make_shared<Drow>();
                break;
            }
            else if (playerChar == 'v'){
                player = std::make_shared<Vampire>();
                break;
            }
            else if (playerChar == 't'){
                player = std::make_shared<Troll>();
                break;
            }
            else if (playerChar == 'g'){
                player = std::make_shared<Goblin>();
                break;
            }
            else{
                player = std::make_shared<Shade>();
                playerChar = 's';
                break;
            }
        }
        bool exit = false;
        std::cout<<"Your character is: "<<playerChar<<std::endl;
        for(int i=0; i<5; ++i){
            std::cout << "------------------ Level "<< std::to_string(i+1)<<" ------------------" << std::endl;
            std::cout<<"Generating the floor..."<<std::endl;
            if(readFile){
                (floors[i])->readFromFile(player);
            }else (floors[i])->generateAll(player);
            floors[i]->getPlayer()->removeTempPotion();
            floors[i]->print();
            std::string cmd, arg;
            bool enemyMoving = true;
            while (std::cin>>cmd){
                if(cmd == "no" || cmd== "so" || cmd == "ea" || cmd == "we" || cmd == "ne" || cmd == "nw" || cmd == "se" || cmd == "sw"){
                    (floors[i])->playerMove(cmd);
                }
                else if (cmd == "u"){
                    std::cin>>arg;
                    (floors[i])->playerUsePotion(arg);
                }
                else if (cmd == "a"){
                    std::cin>>arg;
                    (floors[i])->playerAttack(arg);
                }
                else if (cmd == "f"){
                    enemyMoving = !enemyMoving;
                }
                else if (cmd == "q"){
                    exit = true;
                    break;
                }
                else if (cmd == "r"){
                    restart = true;
                    exit = true;
                    floors[i]->getPlayer()->removeTempPotion();
                    std::cout << "Restarts the game" << std::endl;
                    for(int j = 0; j<=i; ++j){
                        if(readFile){
                            floors[j] = std::make_shared<Floor>(fileContent[j], j);
                        }else{
                            floors[j]->clearFloor();
                        }
                    }
                    break;
                }
                else{
                    floors[i]->setAction("Invalid command. ");
                }
                floors[i]->enemyAttackPlayer();
                if (enemyMoving == true){
                    floors[i]->Enemymove();
                }
                floors[i]->print();
                if (player->getAlive() == false){
                    exit = true;
                    break;
                }
                if(floors[i]->getReachStair()){
                    if(i==4){
                        floors[i]->printScore();
                    }
                    else{
                        std::cout<< "Player reached the stair, entering the next level..."<<std::endl;
                        floors[i]->getPlayer()->removeTempPotion();
                    }
                    break;
                }
            }
            if(exit) break;
        }
    }
}
