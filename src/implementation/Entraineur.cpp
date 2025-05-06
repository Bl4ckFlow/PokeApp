#include "../../include/Entraineur.hpp"
#include <algorithm> 

Tamer::Tamer(std::string name, std::vector<Pokemon> liste): name(name), liste_pokemon(liste){};

Tamer::Tamer(std::string name): name(name){
    liste_pokemon = {};
};

void Tamer::setPokeList(std::vector<Pokemon> pokelist){
    liste_pokemon = pokelist;
};

std::vector<Pokemon>& Tamer::getPokeList() { return liste_pokemon; }
const std::vector<Pokemon>& Tamer::getPokeList() const { return liste_pokemon; }

std::string Tamer::getName() const {return name;}

int Tamer::getSelectedPokemonIndex() {
    return selected_pokemon_index;
}

void Tamer::setSelectedPokemonIndex(int index) {
    selected_pokemon_index = index;
}

bool Tamer::checkhp(){
    int counter =0;
    for(Pokemon p : liste_pokemon){
        if(p.get_hp() == 0){
            counter++;
        }
    }
    if(counter == liste_pokemon.size()){
        return true;
    }
    return false;
}

//Player
Player::Player(std::string name, std::vector<Pokemon> liste, int nb, int ncombat_gagnes, int ncombat_perdu) : Tamer(name, liste), nombre_badges(nb), nombre_combats_gagnes(ncombat_gagnes), nombre_combats_perdus(ncombat_perdu){};

void Player::set_nombre_badges(std::string badge){
    nombre_badges++;
    nom_badge.push_back(badge);
};

void Player::set_nombre_combats_gagnes(int v){
    nombre_combats_gagnes++;
};

void Player::set_nombre_combats_perdus(int v){
    nombre_combats_perdus++;
};

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

std::string GymLeader::getBadge() const {return badge;}

std::string GymLeader::getGymnase() const {return gymnase;}


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

