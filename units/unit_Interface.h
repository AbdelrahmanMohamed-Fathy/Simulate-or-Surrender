class unit_Interface
{
private:
    const int ID;
    int JoinTime;
    int Health;
    int Power;
    int Attack_Capacity;
public:
    unit_Interface(int Id, int Tj, int Hp, int Pr, int Ac) :
        ID(Id),
        JoinTime(Tj),
        Health(Hp),
        Power(Pr),
        Attack_Capacity(Ac) {};
    virtual void Attack() = 0;
};