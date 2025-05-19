#include "../include/Entraineur.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <type_traits>
#include <iostream>


std::vector<Pokemon> LoadPokemonFromCSV(const std::string& filename) {
    std::vector<Pokemon> pokemons;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file " << filename << std::endl;
        return pokemons;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name, type1 = "", type2 = "", hp_str, atk_name, atk_str;

        std::getline(ss, name, ',');
        std::getline(ss, type1, ',');
        std::getline(ss, type2, ',');
        std::getline(ss, hp_str, ',');
        std::getline(ss, atk_name, ',');
        std::getline(ss, atk_str, '\n');

        Type ftype1 = stringToType(type1);
        Type ftype2 = stringToType(type2);
        int ihp = std::stoi(hp_str);
        std::string attack_name = atk_name;
        int iattack = std::stoi(atk_str);

        Pokemon p(name, ftype1, ftype2, ihp, attack_name, iattack);

        pokemons.push_back(p);
    }

    return pokemons;
}

std::vector<GymLeader> LoadGymLeaderFromCSV(const std::string& filename, std::vector<Pokemon> poke_list) {
    std::vector<GymLeader> gymlead;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file " << filename << std::endl;
        return gymlead;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        
        std::stringstream ss(line);
        std::string name, gymnase = "", badge = "", pokemon1 = "", pokemon2 = "", pokemon3 = "", pokemon4 = "", pokemon5 = "", pokemon6 = "";

        std::getline(ss, name, ',');
        std::getline(ss, badge, ',');
        std::getline(ss, gymnase, ',');
        std::getline(ss, pokemon1, ',');
        std::getline(ss, pokemon2, ',');
        std::getline(ss, pokemon3, ',');
        std::getline(ss, pokemon4, ',');
        std::getline(ss, pokemon5, ',');
        std::getline(ss, pokemon6, '\n');

        GymLeader g(name, badge, gymnase, pokemon1, pokemon2, pokemon3, pokemon4, pokemon5, pokemon6, poke_list);

        gymlead.push_back(g);
    }

    return gymlead;
}

std::vector<MasterTamer> LoadMasterTamerFromCSV(const std::string& filename, std::vector<Pokemon> poke_list) {
    std::vector<MasterTamer> mastertamer;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file " << filename << std::endl;
        return mastertamer;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name, pokemon1 = "", pokemon2 = "", pokemon3 = "", pokemon4 = "", pokemon5 = "", pokemon6 = "";

        std::getline(ss, name, ',');
        std::getline(ss, pokemon1, ',');
        std::getline(ss, pokemon2, ',');
        std::getline(ss, pokemon3, ',');
        std::getline(ss, pokemon4, ',');
        std::getline(ss, pokemon5, ',');
        std::getline(ss, pokemon6, '\n');

        MasterTamer m(name, pokemon1, pokemon2, pokemon3, pokemon4, pokemon5, pokemon6, poke_list);

        mastertamer.push_back(m);
    }

    return mastertamer;
}


