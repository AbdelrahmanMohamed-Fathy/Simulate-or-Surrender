#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class unit_Interface
{
protected:
    const unsigned int ID;
    static unsigned int deathCount;

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
    unsigned int firstAttackedDelay;
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
    int getFirstAttackedDelay() const;
    int getDestructionDelay() const;
    int getBattleTime();
    static int getDeathCount();
    
    //Setters:
    void setDestructionTime(int dt);
    void setfirstAttackedTime(int at);

    //This function is reserved for deathList usage only
    string generateUnitLine() const;
    
    virtual void Attack() {};
};

static ostream& operator<<(ostream& out, const unit_Interface *unit)
{
    out << unit->getID();
    return out;
}

static ofstream& operator<<(ofstream& out, const unit_Interface *unit)
{
    out << unit->generateUnitLine();
    return out;
}

static ostream& operator<<(ostream& out, const unit_Interface& unit)
{
    out << unit.getID();
    return out;
}

static ofstream& operator<<(ofstream& out, const unit_Interface& unit)
{
    out << unit.generateUnitLine();
    return out;
}