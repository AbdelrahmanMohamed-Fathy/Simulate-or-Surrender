enum UnitType;
//any created unit should inherit this interface
class Unit_Interface
{
    protected:
        int ID;
        int Tj;
        UnitType Type;
        int Health;
        int Power;
        int Attack_Capacity;
};

enum UnitType
{
    HSoldier,
    HTank,
    HGunnery,
    ASoldier,
    AMonster,
    ADrone
};