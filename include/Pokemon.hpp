#pragma once
#include "./Type.hpp"
#include <string>

class Pokemon {

    private:
        std::string name;
        Type type1;
        Type type2;
        int hp;
        std::string attack_name;
        int attack_power;
        std::vector<Type> weakness;
        std::vector<Type> resistance;

    public:
        Pokemon(std::string name, Type type1, Type type2, int hp, std::string attack_name,int attack);

        //Getters
        std::vector<Type> get_type() const;
        std::vector<Type> get_weakness() const;
        std::vector<Type> get_resistance() const;
        int get_hp() const;
        float get_attack_power() const;
        std::string get_attack_name() const;
        std::string get_name() const;

        //Setters
        void set_hp(int val);

        //Methods
        std::string stringify();
        void attack(Pokemon& p);
        int calculate_damage(Pokemon& p);

        //virtual void version

};

/*
// FirePokemon Class
class FirePokemon:Pokemon{
    public : 
        FirePokemon(std::string name,Type type2, int hp, int attack) : Pokemon(name, Type::Fire, type2, hp, attack, getTypeProperties(Type::Fire).Weaknesses){};
};

// WaterPokemon Class
class WaterPokemon : public Pokemon {
    public:
        WaterPokemon(std::string name, Type type2, int hp, int attack): Pokemon(name, Type::Water, type2, hp, attack, getTypeProperties(Type::Water).Weaknesses) {}
};
    
// PlantPokemon Class
class PlantPokemon : public Pokemon {
    public:
        PlantPokemon(std::string name, Type type2, int hp, int attack): Pokemon(name, Type::Plant, type2, hp, attack, getTypeProperties(Type::Plant).Weaknesses) {}
};
    
// ElectricPokemon Class
class ElectricPokemon : public Pokemon {
    public:
        ElectricPokemon(std::string name, Type type2, int hp, int attack): Pokemon(name, Type::Electric, type2, hp, attack, getTypeProperties(Type::Electric).Weaknesses) {}
};
    
// IcePokemon Class
class IcePokemon : public Pokemon {
    public:
        IcePokemon(std::string name, Type type2, int hp, int attack): Pokemon(name, Type::Ice, type2, hp, attack, getTypeProperties(Type::Ice).Weaknesses) {}
};
    
// CombatPokemon Class
class CombatPokemon : public Pokemon {
    public:
        CombatPokemon(std::string name, Type type2, int hp, int attack): Pokemon(name, Type::Combat, type2, hp, attack, getTypeProperties(Type::Combat).Weaknesses) {}
};
    
// PoisonPokemon Class
class PoisonPokemon : public Pokemon {
    public:
        PoisonPokemon(std::string name, Type type2, int hp, int attack): Pokemon(name, Type::Poison, type2, hp, attack, getTypeProperties(Type::Poison).Weaknesses) {}
};
    
// GroundPokemon Class
class GroundPokemon : public Pokemon {
    public:
        GroundPokemon(std::string name, Type type2, int hp, int attack): Pokemon(name, Type::Ground, type2, hp, attack, getTypeProperties(Type::Ground).Weaknesses) {}
};
    
// FlightPokemon Class
class FlightPokemon : public Pokemon {
    public:
        FlightPokemon(std::string name, Type type2, int hp, int attack): Pokemon(name, Type::Flight, type2, hp, attack, getTypeProperties(Type::Flight).Weaknesses) {}
};
    
// PsychicPokemon Class
class PsychicPokemon : public Pokemon {
    public:
        PsychicPokemon(std::string name, Type type2, int hp, int attack): Pokemon(name, Type::Psychic, type2, hp, attack, getTypeProperties(Type::Psychic).Weaknesses) {}
};
    
// InsectPokemon Class
class InsectPokemon : public Pokemon {
    public:
        InsectPokemon(std::string name, Type type2, int hp, int attack): Pokemon(name, Type::Insect, type2, hp, attack, getTypeProperties(Type::Insect).Weaknesses) {}
};
    
// RockPokemon Class
class RockPokemon : public Pokemon {
    public:
        RockPokemon(std::string name, Type type2, int hp, int attack): Pokemon(name, Type::Rock, type2, hp, attack, getTypeProperties(Type::Rock).Weaknesses) {}
};
    
// SpecterPokemon Class
class SpecterPokemon : public Pokemon {
    public:
        SpecterPokemon(std::string name, Type type2, int hp, int attack): Pokemon(name, Type::Specter, type2, hp, attack, getTypeProperties(Type::Specter).Weaknesses) {}
};
    
// DragonPokemon Class
class DragonPokemon : public Pokemon {
    public:
        DragonPokemon(std::string name, Type type2, int hp, int attack): Pokemon(name, Type::Dragon, type2, hp, attack, getTypeProperties(Type::Dragon).Weaknesses) {}
};
    
// DarknessPokemon Class
class DarknessPokemon : public Pokemon {
    public:
        DarknessPokemon(std::string name, Type type2, int hp, int attack): Pokemon(name, Type::Darkness, type2, hp, attack, getTypeProperties(Type::Darkness).Weaknesses) {}
};
    
// SteelPokemon Class
class SteelPokemon : public Pokemon {
    public:
        SteelPokemon(std::string name, Type type2, int hp, int attack): Pokemon(name, Type::Steel, type2, hp, attack, getTypeProperties(Type::Steel).Weaknesses) {}
};
    
// FairyPokemon Class
class FairyPokemon : public Pokemon {
    public:
        FairyPokemon(std::string name, Type type2, int hp, int attack): Pokemon(name, Type::Fairy, type2, hp, attack, getTypeProperties(Type::Fairy).Weaknesses) {}
};
*/
    
int CheckCompatibility(const Pokemon& p1,const Pokemon& p2);