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
    
int CheckCompatibility(const Pokemon& p1,const Pokemon& p2);