enum UnitType
{
    HSoldier,
    HTank,
    HGunnery,
    ASoldier,
    AMonster,
    ADrone
};

class Unit
{
private:
    int ID;
    int JoinTime;
    UnitType Type;
    int Health;
    int Power;
    int Attack_Capacity;
public:
    Unit(int Id, int Tj, UnitType type, int Hp, int Pr, int Ac) :
        ID(Id),
        JoinTime(Tj),
        Type(type),
        Health(Hp),
        Power(Pr),
        Attack_Capacity(Ac) {};
};