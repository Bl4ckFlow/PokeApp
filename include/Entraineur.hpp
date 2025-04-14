#pragma once
#include <string>
#include "./Pokemon.hpp"


class Tamer{
    private :
        std::string name;
        std::vector<Pokemon> liste_pokemon;


    public :
        Tamer(std::string name, std::vector<Pokemon> liste): name(name), liste_pokemon(liste){};

};

class Player : Tamer{
    private : 
        int nombre_badges;
        int nombre_combats_gagnes;
        int nombre_combats_perdus;

    public : 
};

class GymLeader : Tamer{
    private : 
        int nombre_badges;
        int nombre_combats_gagnes;
        int nombre_combats_perdus;

    public : 
};

class MasterTamer : Tamer{
    private : 
        int nombre_badges;
        int nombre_combats_gagnes;
        int nombre_combats_perdus;

    public : 
};
