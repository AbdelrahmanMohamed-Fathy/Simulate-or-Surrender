#include <iostream>
using namespace std;

class unit_Interface
{
private:
    const int ID;

    //Attributes:
    int health;
    int power;
    int attackCapacity;

    //Time stats:
    int joinTime;
    int destructionTime;
    int firstAttackedTime;
    int battleTime;

    //Delays:
    int firstAttackDelay;
    int destructionDelay;

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

    virtual void Attack() = 0;
};

ostream& operator<<(ostream& out, const unit_Interface& unit)
{
    out << (unit.getID());
    return out;
}