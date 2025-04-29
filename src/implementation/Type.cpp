#include "../../include/Type.hpp"

TypeProperties getTypeProperties(Type t) {
    switch (t) {
        case Type::Fire:
            return {{Type::Water, Type::Rock, Type::Ground}, {Type::Plant, Type::Ice, Type::Insect, Type::Steel, Type::Fairy}};

        case Type::Water:
            return {{Type::Plant, Type::Electric}, {Type::Fire, Type::Water, Type::Ice, Type::Steel}};

        case Type::Plant:
            return {{Type::Fire, Type::Ice, Type::Poison, Type::Flight, Type::Insect}, {Type::Water, Type::Ground, Type::Rock}};

        case Type::Electric:
            return {{Type::Ground}, {Type::Flight, Type::Steel, Type::Electric}};

        case Type::Ice:
            return {{Type::Fire, Type::Combat, Type::Rock, Type::Steel }, {Type::Ice}};
            
        case Type::Combat:
            return {{Type::Flight, Type::Psychic, Type::Fairy}, {Type::Rock, Type::Insect, Type::Darkness}};

        case Type::Poison:
            return {{Type::Ground, Type::Psychic}, {Type::Plant, Type::Fairy, Type::Combat, Type::Poison, Type::Insect}};

        case Type::Ground:
            return {{Type::Water, Type::Plant, Type::Ice}, {Type::Poison, Type::Rock}};

        case Type::Flight:
            return {{Type::Electric, Type::Ice, Type::Rock}, {Type::Plant, Type::Insect, Type::Combat}};

        case Type::Psychic:
            return {{Type::Insect, Type::Specter, Type::Darkness}, {Type::Combat, Type::Psychic}};

        case Type::Insect:
            return {{Type::Fire, Type::Flight, Type::Rock}, {Type::Plant, Type::Combat, Type::Ground}};

        case Type::Rock:
            return {{Type::Water, Type::Plant, Type::Combat, Type::Ground, Type::Steel}, {Type::Fire, Type::Flight, Type::Poison, Type::Normal}};

        case Type::Specter:
            return {{Type::Specter, Type::Darkness}, {Type::Poison, Type::Insect}};

        case Type::Dragon:
            return {{Type::Ice, Type::Dragon, Type::Fairy}, {Type::Fire, Type::Water, Type::Electric, Type::Plant}};

        case Type::Darkness:
            return {{Type::Combat, Type::Insect, Type::Fairy}, {Type::Specter, Type::Psychic, Type::Darkness}};

        case Type::Steel:
            return {{Type::Fire, Type::Combat, Type::Ground}, {Type::Normal, Type::Plant, Type::Ice, Type::Flight, Type::Psychic, Type::Insect, Type::Rock, Type::Dragon, Type::Steel, Type::Fairy}};

        case Type::Fairy:
            return {{Type::Poison, Type::Steel}, {Type::Combat, Type::Insect, Type::Darkness, Type::Dragon}};

        default:
            return {{}, {}};
    }
}

Type stringToType(const std::string& typeStr) {
    
    if(typeStr == "Feu"){
        return Type::Fire;
    }

    if(typeStr == "Eau"){
        return Type::Water;
    }

    if(typeStr == "Plante"){
        return Type::Plant;
    }

    if(typeStr == "Électrik"){
        return Type::Electric;
    }

    if(typeStr == "Glace"){
        return Type::Ice;
    }
         
    if(typeStr == "Combat"){
        return Type::Combat;
    }

    if(typeStr == "Poison"){
        return Type::Poison;
    }

    if(typeStr == "Sol"){
        return Type::Ground;
    }

    if(typeStr == "Vol"){
        return Type::Flight;
    }

    if(typeStr == "Psy"){
        return Type::Psychic;
    }

    if(typeStr == "Insecte"){
        return Type::Insect;
    }

    if(typeStr == "Roche"){
        return Type::Rock;
    }

    if(typeStr == "Spectre"){
        return Type::Specter;
    }

    if(typeStr == "Dragon"){
        return Type::Dragon;
    }

    if(typeStr == "Ténèbres"){
        return Type::Darkness;
    }

    if(typeStr == "Acier"){
        return Type::Steel;
    }

    if(typeStr == "Fée"){
        return Type::Fairy;
    }

    if(typeStr == "Normal"){
        return Type::Normal;
    }

    return Type::None;

}

std::string typeToString(Type type) {
    switch (type) {
        case Type::Fire:      return "Feu";
        case Type::Water:     return "Eau";
        case Type::Plant:     return "Plante";
        case Type::Electric:  return "Électrik";
        case Type::Ice:       return "Glace";
        case Type::Combat:    return "Combat";
        case Type::Poison:    return "Poison";
        case Type::Ground:    return "Sol";
        case Type::Flight:    return "Vol";
        case Type::Psychic:   return "Psy";
        case Type::Insect:    return "Insecte";
        case Type::Rock:      return "Roche";
        case Type::Specter:   return "Spectre";
        case Type::Dragon:    return "Dragon";
        case Type::Darkness:  return "Ténèbres";
        case Type::Steel:     return "Acier";
        case Type::Fairy:     return "Fée";
        case Type::Normal:    return "Normal";
        case Type::None:      return "None";  
        default:              return "Unknown"; 
    }
}