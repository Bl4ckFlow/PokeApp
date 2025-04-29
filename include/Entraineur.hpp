#pragma once
#include <string>
#include "./Pokemon.hpp"


class Tamer{
    private :
        std::string name;
        std::vector<Pokemon> liste_pokemon;


    public :
        Tamer(std::string name, std::vector<Pokemon> liste);
        Tamer(std::string name);

        std::string getName();
        std::vector<Pokemon> getPokeList();

        void setName(std::string name);
        void setPokeList(std::vector<Pokemon> poke_list);
};

class Player : public Tamer{
    private : 
        int nombre_badges;
        int nombre_combats_gagnes;
        int nombre_combats_perdus;

    public : 
        Player(std::string name, std::vector<Pokemon> liste, int nb, int ncombat_gagnes, int ncombat_perdu);

};

class GymLeader : public Tamer{
    private : 
        std::string badge;
        std::string gymnase;
        
    public : 
        GymLeader(std::string name, std::string badge, std::string gymnase, std::string pokemon1, std::string pokemon2, std::string pokemon3, std::string pokemon4, std::string pokemon5, std::string pokemon6, std::vector<Pokemon> poke_list);
};

class MasterTamer : public Tamer{
    public : 
        MasterTamer(std::string name, std::string pokemon1, std::string pokemon2, std::string pokemon3, std::string pokemon4, std::string pokemon5, std::string pokemon6, std::vector<Pokemon> poke_list) ;
};
