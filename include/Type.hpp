#pragma once
#include <vector>
#include <string>

enum class Type {
    Fire,
    Water,
    Plant,
    Electric,
    Ice,
    Combat,
    Poison,
    Ground,
    Flight,
    Psychic,
    Insect,
    Rock,
    Specter,
    Dragon,
    Darkness,
    Steel,
    Fairy,
    Normal,
    None
};

struct TypeProperties {
    std::vector<Type> Weaknesses;
    std::vector<Type> Resistance;
};

TypeProperties getTypeProperties(Type t);
Type stringToType(const std::string& typeStr);
std::string typeToString(Type type);