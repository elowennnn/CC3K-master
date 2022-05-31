#ifndef _FLOOR_H_
#define _FLOOR_H_
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <string>

class Player;
class Enemy;
class Potion;
class Treasure;
class Chamber;
class Character;

class Floor{
private:
    std::shared_ptr<Player> player;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<std::shared_ptr<Potion>> potions;
    std::vector<std::shared_ptr<Treasure>> treasures;
    std::vector<std::shared_ptr<Chamber>> chambers;
    std::vector<std::vector<char>> grid;
    bool reachStair;
    int id;
    std::string action = "Player enters the floor";

public:
    Floor( std::vector<std::vector<char>> grid, int id);
    Floor( int id);

    ~Floor(){}

    std::shared_ptr<Player> getPlayer();
    std::vector<std::shared_ptr<Enemy>> getEnemies();
    std::vector<std::shared_ptr<Potion>> getPotions();
    std::vector<std::shared_ptr<Treasure>> getTreasures();
    std::vector<std::shared_ptr<Chamber>> getChambers();
    int getId();
    bool getReachStair();

    void setAction(std::string s);

    void print();

    void generateAll(std::shared_ptr<Player>);

    // generation
    void generateChambers();
    void generatePlayer(std::shared_ptr<Player>);
    void generatePotion(std::shared_ptr<Potion>);
    void generateTreasure(std::shared_ptr<Treasure>);
    void generateEnemy(std::shared_ptr<Enemy>);
    void generateStair();

    void clearFloor();
    void EnemymoveHelper(int);
    void Enemymove();

    //return true if there's an enemy in the current position
    int treasureAt(int row, int col);
    int potionAt(int row, int col);
    bool isRegularEnemy(int, int);
    int enemyAt(int, int);
    std::vector<int> nextMove(std::string);
    void enemyAttackPlayer();
    void playerAttack(std::string);
    void playerMove(std::string);
    void playerUsePotion(std::string);

    void printScore();

    void readFromFile(std::shared_ptr<Player>);
};

#endif
