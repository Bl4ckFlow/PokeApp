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

