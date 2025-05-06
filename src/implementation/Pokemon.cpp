#include "../../include/Pokemon.hpp"
#include <algorithm>
#include <iterator>

Pokemon::Pokemon(std::string name, Type type1, Type type2, int hp, std::string attack_name,int attack) : name(name), type1(type1), type2(type2), hp(hp), attack_name(attack_name),attack_power(attack){
    TypeProperties type1_properties = getTypeProperties(type1);
    TypeProperties type2_properties = getTypeProperties(type2);

    weakness = type1_properties.Weaknesses;
    resistance = type1_properties.Resistance;

    weakness.insert(weakness.end(), type2_properties.Weaknesses.begin(), type2_properties.Weaknesses.end());
    resistance.insert(resistance.end(), type2_properties.Resistance.begin(), type2_properties.Resistance.end());

    std::sort(weakness.begin(), weakness.end());
    weakness.erase(std::unique(weakness.begin(), weakness.end()), weakness.end());

    std::sort(resistance.begin(), resistance.end());
    resistance.erase(std::unique(resistance.begin(), resistance.end()), resistance.end());
}

std::string Pokemon::stringify() {return "name: " + name + ", Type1: " + typeToString(type1) + ", Type2: " + typeToString(type2) + ", AP: "+ std::to_string(attack_power) + ", Attack Name: " + attack_name + ", HP: " + std::to_string(hp) ;}

std::vector<Type> Pokemon::get_type() const {return {type1, type2};};
int Pokemon::get_hp() const { return hp; }
float Pokemon::get_attack_power() const { return attack_power; }
std::string Pokemon::get_attack_name() const { return attack_name; }
std::string Pokemon::get_name() const { return name; }
std::vector<Type> Pokemon::get_weakness() const { return weakness;}
std::vector<Type> Pokemon::get_resistance() const { return resistance;}


void Pokemon::set_hp(int val) {hp = val;}


int CheckCompatibility(const Pokemon& p1, const Pokemon& p2) {
    std::vector<Type> p1_types = p1.get_type(); 
    std::vector<Type> p2_weakness = p2.get_weakness();
    std::vector<Type> p2_resistance = p2.get_resistance();

    bool type1_weak = false;
    bool type1_resist = false;

    bool type2_resist = false;
    bool type2_weak = false;

    if (!p1_types.empty()) {
        Type type1 = p1_types[0];
        if (std::find(p2_weakness.begin(), p2_weakness.end(), type1) != p2_weakness.end())
            type1_weak = true;
        if (std::find(p2_resistance.begin(), p2_resistance.end(), type1) != p2_resistance.end())
            type1_resist = true;

        if (p1_types.size() > 1) {
            Type type2 = p1_types[1];
            if (std::find(p2_weakness.begin(), p2_weakness.end(), type2) != p2_weakness.end())
                type2_weak = true;
            if (std::find(p2_resistance.begin(), p2_resistance.end(), type2) != p2_resistance.end())
                type2_resist = true;
        }
    }


    if ((type1_weak && type2_resist)) return 2;   
    if ((type1_resist && type2_weak)) return -2;  
    if (type1_weak || type2_weak) return -1;    
    if (type1_resist || type2_resist) return 1;   

    return 0;
}

int Pokemon::calculate_damage(Pokemon& p){
    int comp = CheckCompatibility(*this, p);

    if(comp ==  2){
        return attack_power*1.6;
    }
    else if(comp ==  -2){
        return attack_power*0.8;
    }
    else if(comp ==  1){
        return attack_power*0.5;
    }
    else if(comp == -1){
        return attack_power*2;
    }
    else{
        return attack_power;
    }    
}

void Pokemon::attack(Pokemon& p) {

    int comp = CheckCompatibility(*this, p);

    if(comp ==  2){
        int val = p.get_hp() - attack_power*1.6;
        if (val <0) p.set_hp(0);
        else p.set_hp(val);
    }
    else if(comp ==  -2){
        int val = p.get_hp() - attack_power*0.8;
        if (val <0) p.set_hp(0);
        else p.set_hp(val);
    }
    else if(comp ==  1){
        int val = p.get_hp() - attack_power*0.5;
        if (val <0) p.set_hp(0);
        else p.set_hp(val);
    }
    else if(comp == -1){
        int val = p.get_hp() - attack_power*2;
        if (val <0) p.set_hp(0);
        else p.set_hp(val);
    }
    else{
        int val = p.get_hp() - attack_power;
        if (val <0) p.set_hp(0);
        else p.set_hp(val);
    }    
}