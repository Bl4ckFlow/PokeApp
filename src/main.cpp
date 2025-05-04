#include "./affichage/welcome.cpp"
#include "./affichage/username.cpp"
#include "./affichage/pokedec.cpp"
#include "./affichage/menuscreen.cpp"
#include "./affichage/fightscreen.cpp"
#include "../include/Entraineur.hpp"
#include "./load_func.cpp"
#include <iostream>

using namespace ftxui;

std::vector<Pokemon> poke_list = LoadPokemonFromCSV("pokemon.csv");
std::vector<GymLeader> leader_list = LoadGymLeaderFromCSV("leaders.csv", poke_list);
std::vector<MasterTamer> master_list = LoadMasterTamerFromCSV("maitres.csv", poke_list);
 
#include <iostream>

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
        
    std::vector<Pokemon> selected_pokemon;

    Component poke_list_ui = PokemonList(poke_list, &selected_pokemon);
    screen.Loop(poke_list_ui);

    Player player = Player(username, selected_pokemon, 0, 0, 0);
    GymLeader* opponent  = &leader_list[0];

    player.setSelectedPokemonIndex(0);
    opponent->setSelectedPokemonIndex(0);
    
    bool is_player_turn = true;

    int user_choice;
    auto onKeyPressed = [&](int choice) {
        user_choice = choice;
        if (choice == 1) {
            bool fight_over = false;
            
            while (!fight_over) {


                std::vector<Pokemon>& player_pokemons = player.getPokeList();
                std::vector<Pokemon>& opponent_pokemons = opponent->getPokeList();
                
                int player_index = player.getSelectedPokemonIndex();
                int opponent_index = opponent->getSelectedPokemonIndex();

                Component fight_screen = CreateFightScreen(player, *opponent, is_player_turn, player_pokemons, opponent_pokemons);
                screen.Loop(fight_screen);
                
                if(is_player_turn){
                    player_pokemons[player_index].attack(opponent_pokemons[opponent_index]);
                }else{
                    opponent_pokemons[opponent_index].attack(player_pokemons[player_index]);
                }
                
                //à changer la condition d'arret 
                if (player.checkhp() || opponent->checkhp()) {
                    fight_over = true;
                    break;
                }

                if (player_pokemons[player_index].get_hp() == 0) {
                    player.setSelectedPokemonIndex(player_index + 1);
                }
                if (opponent_pokemons[opponent_index].get_hp() == 0) {
                    opponent->setSelectedPokemonIndex(player_index + 1);
                }

                is_player_turn = !is_player_turn;

            }
            screen.Exit();
        } else if (choice == 2) {
            
            screen.Exit();
        } else if (choice == 3) {
            
            screen.Exit();
        }
    };

    
    do{
        Component menu = CreateMenuScreen(onKeyPressed);
        screen.Loop(menu);

    }while(user_choice != 3);

    return 0;
}
