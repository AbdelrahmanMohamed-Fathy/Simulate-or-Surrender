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
    int Tj;
    UnitType Type;
    int Health;
    int Power;
    int Attack_Capacity;
};