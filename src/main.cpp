#include "affichage/welcome.cpp"
#include "affichage/username.cpp"
#include "./affichage/pokedec.cpp"
#include "../include/Pokemon.hpp"
#include "./pokemon_list.cpp"

using namespace ftxui;
 
int main(void) {
  
    auto screen = ScreenInteractive::Fullscreen();

    auto onEnterPressed = [&]() {
        screen.Exit(); 
    };

    Component welcome = CreateWelcomeScreen(onEnterPressed);
    screen.Loop(welcome);  

    std::string username;
    Component username_screen = CreateUsernameScreen(&username, onEnterPressed);
    screen.Loop(username_screen);

    if(username == ""){
        username = "Player1";
    }

    std::vector<Pokemon> pokemon_list = LoadPokemonFromCSV("pokemon.csv");
    std::vector<Pokemon> selected_pokemon;

    Component poke_list_ui = PokemonList(pokemon_list, &selected_pokemon);
    screen.Loop(poke_list_ui);


    return 0;
}