#include <fstream>
#include <sstream>
#include <vector>
#include "../include/Pokemon.hpp"
#include "../include/Type.hpp"
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