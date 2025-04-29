#include "../../include/Entraineur.hpp"

Tamer::Tamer(std::string name, std::vector<Pokemon> liste): name(name), liste_pokemon(liste){};

Tamer::Tamer(std::string name): name(name){
    liste_pokemon = {};
};

void Tamer::setPokeList(std::vector<Pokemon> pokelist){
    liste_pokemon = pokelist;
};

std::vector<Pokemon> Tamer::getPokeList(){ return liste_pokemon;}

std::string Tamer::getName(){return name;}

//Player
Player::Player(std::string name, std::vector<Pokemon> liste, int nb, int ncombat_gagnes, int ncombat_perdu) : Tamer(name, liste), nombre_badges(nb), nombre_combats_gagnes(ncombat_gagnes), nombre_combats_perdus(ncombat_perdu){};


//Gymleader
GymLeader::GymLeader(std::string name, std::string badge, std::string gymnase, std::string pokemon1, std::string pokemon2, std::string pokemon3, std::string pokemon4, std::string pokemon5, std::string pokemon6, std::vector<Pokemon> poke_list) : Tamer(name), gymnase(gymnase), badge(badge) {
    std::vector<Pokemon> customized_pokelist;

    for(Pokemon p : poke_list){
        if(p.get_name() == pokemon1 || p.get_name() == pokemon2 || p.get_name() == pokemon3 || p.get_name() == pokemon4 || p.get_name() == pokemon5 || p.get_name() == pokemon6 ){
            customized_pokelist.push_back(p);
        }
    }
    this->setPokeList(customized_pokelist);
};


//MasterTamer
MasterTamer::MasterTamer(std::string name, std::string pokemon1, std::string pokemon2, std::string pokemon3, std::string pokemon4, std::string pokemon5, std::string pokemon6, std::vector<Pokemon> poke_list) : Tamer(name) {
    std::vector<Pokemon> customized_pokelist;

    for(Pokemon p : poke_list){
        if(p.get_name() == pokemon1 || p.get_name() == pokemon2 || p.get_name() == pokemon3 || p.get_name() == pokemon4 || p.get_name() == pokemon5 || p.get_name() == pokemon6 ){
            customized_pokelist.push_back(p);
        }
    }
    this->setPokeList(customized_pokelist);
};

