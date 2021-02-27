#include <vector>
#include <string>

class Item{
    public:
    Item();
    int get_sellprice();
    virtual std::string get_string(){return name;}
    virtual void use(){}
    std::vector<std::string> tags;
    float rarity;
    std::string name;
};