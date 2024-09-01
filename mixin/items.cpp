#include <cassert>
#include <vector>
#include <string>
#include <utility>

// implement everything here
namespace details{

    template<typename T>
    auto damage(const T* t, double dmg, int) -> decltype(t->damage(dmg)){
        return t->damage(dmg);
    }
    template<typename T>
    auto damage(const T* t, double dmg, double){
        return dmg;
    }
    template<typename T>
    auto defense(const T* t, double def, int) -> decltype(t->defense(def)){
        return t->defense(def);
    }
    template<typename T>
    auto defense(const T* t, double def, double){
        return def;
    }

}



class Item_Base
{
public:
    virtual ~Item_Base() = default;
    virtual double damage() const = 0;
    virtual double defense() const = 0;
};

template<typename... MixinsT>
class Item: public Item_Base, public MixinsT...{
public:
    Item(MixinsT&&... components)
    : MixinsT(std::forward<MixinsT>(components))... {}
    double damage() const override{
        double total_dmg{};
        ((total_dmg = details::damage<MixinsT>(this, total_dmg, 0)), ...);
        return total_dmg;
    }
    double defense() const override{
        double total_def{};
        ((total_def = details::defense<MixinsT>(this, total_def, 0)), ...);
        return total_def;
    }
};

class Attack {
public:
    double damage(double) const { return dmg; }
    double dmg{};
};

class Defend {
public:
    double defense(double) const { return def; }
    double def{};
};

struct Damage_Multiplier
{
    double damage(double dmg) const
    {
        return factor * dmg;
    }
    double factor{1.0};
};

struct Defense_Multiplier
{
    double defense(double def) const
    {
        return factor * def;
    }
    double factor{1.0};
};

struct Named
{
    std::string name{};
};

using Weapon = Item<Attack>;
using Armor = Item<Defend>;
using Shield = Item<Defend, Attack, Defense_Multiplier>;
using Sword  = Item<Named, Attack, Damage_Multiplier>;



int main()
{
    std::vector<Item_Base*> items {
        new Weapon {
            Attack{5.0}
        },
        new Armor {
            Defend{10.0}
        },
        new Shield {
            Defend{2.0},
            Attack{2.5},
            Defense_Multiplier{2.5}
        },
        new Sword {
            Named{"Excalibur"},
            Attack{5.0},
            Damage_Multiplier{5.0}
        }
    };

    assert(items[0]->damage() == 5.0);

    assert(items[1]->defense() == 10.0);

    assert(items[2]->damage() == 2.5);
    assert(items[2]->defense() == 5.0);
    
    assert(static_cast<Sword*>(items[3])->name == "Excalibur");
    assert(items[3]->damage() == 25.0);
}