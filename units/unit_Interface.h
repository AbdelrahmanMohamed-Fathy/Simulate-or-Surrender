#include <iostream>
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
    unsigned int firstAttackedTime;
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

    virtual void Attack() = 0;
};

ostream& operator<<(ostream& out, const unit_Interface& unit)
{
    out << (unit.getID());
    return out;
}
                                                                            