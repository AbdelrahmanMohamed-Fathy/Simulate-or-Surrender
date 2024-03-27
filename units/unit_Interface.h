#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class unit_Interface
{
private:
    const unsigned int ID;

    //Attributes:
    int health;
    unsigned int power;
    unsigned int attackCapacity;

    //Time stats:
    unsigned int joinTime;
    unsigned int destructionTime;
    int firstAttackedTime = -1;
    unsigned int battleTime;

    //Delays:
    unsigned int firstAttackDelay;
    unsigned int destructionDelay;

public:
    unit_Interface(int iD, int Hp, int Pr, int Ac, int Tj)
        :ID(iD)

        ,health(Hp)
        ,power(Pr)
        ,attackCapacity(Ac)

        ,joinTime(Tj)
    {};

    //Getters:
    int getID() const;
    
    //Setters:
    void setDestructionTime(int dt);
    void setfirstAttackedTime(int at);

    //This function is reserved for deathList usage only
    string generateUnitLine() const;
    
    virtual void Attack() = 0;
};

inline ostream& operator<<(ostream& out, const unit_Interface& unit)
{
    out << unit.getID();
    return out;
}

inline ofstream& operator<<(ofstream& out, const unit_Interface& unit)
{
    out << unit.generateUnitLine();
    return out;
}