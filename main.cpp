#include <iostream>
#include <string>
#include <stack>
#include <stdexcept>
using namespace std;

class bad_egg : public runtime_error
{
public:
    bad_egg(const string msg) : runtime_error(msg) {}
};

class Egg
{
public:
    const char size = 'L';
    const string type = "raw";
    Egg() {}

    virtual void eat_egg()
    {
        cout << "yummy egg" << endl;
    };
};

class boiled_egg : public Egg
{
public:
    const string type = "hardboiled";
    boiled_egg() {}

    void eat_egg() override
    {
        cout << "aww damn I forgot to peel it I got eggshell in my mouth" << endl;
    }
};

class rotten_egg : public Egg
{
public:
    const string type = "rotten";
    rotten_egg() {}

    void eat_egg() override
    {
        throw bad_egg("egg is rotten!!");
    }
};

class scrambled_egg : public Egg
{
public:
    const string type = "scrambled";
    scrambled_egg() {}

    void eat_egg() override
    {
        cout << "this good but it needs a sauce" << endl;
    }
};

class Carton
{
public:
    stack<Egg *> eggs;
    Carton(stack<Egg *> vec) { eggs = vec; }
    void eat_egg()
    {
        if (eggs.empty())
        {
            cout << "no eggs left :(" << endl;
            return;
        }
        Egg *e = eggs.top();
        eggs.pop();
        try
        {
            e->eat_egg();
        }
        catch (bad_egg b)
        {
            cout << b.what() << endl;
        }
    }
};

int main()
{
    stack<Egg *> dozen;
    for (int i = 0; i < 4; i++)
    {
        dozen.push(new boiled_egg());
        dozen.push(new rotten_egg());
        dozen.push(new scrambled_egg());
    }

    Carton pack = Carton(dozen);

    for (int i = 0; i < 12; i++)
    {
        try
        {
            pack.eat_egg();
        }
        catch (bad_egg e)
        {
            cout << e.what() << endl;
        }
    }

    return 0;
}