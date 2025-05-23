#include "./affichage/welcome.cpp"
#include "./affichage/username.cpp"
#include "./affichage/pokedec.cpp"
#include "./affichage/menuscreen.cpp"
#include "./affichage/fightscreen.cpp"
#include "./affichage/statscreen.cpp"
#include "./affichage/fightschoicescreen.cpp"
#include "../include/Entraineur.hpp"
#include "./load_func.cpp"
#include <iostream>

using namespace ftxui;

std::vector<Pokemon> poke_list = LoadPokemonFromCSV("pokemon.csv");
std::vector<GymLeader> leader_list = LoadGymLeaderFromCSV("leaders.csv", poke_list);
std::vector<MasterTamer> master_list = LoadMasterTamerFromCSV("maitres.csv", poke_list);
 

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

    player.setSelectedPokemonIndex(0);
    
    bool is_player_turn = true;

    int user_choice;
    auto onKeyPressed = [&](int choice) {
        user_choice = choice;
        if (choice == 1) {
            int selected_index = 0;
            bool exit_fight_choice = false;
            bool opponent_selected = false;
            Tamer* selected_tamer = nullptr;

            auto fight_onKeyPressed = [&](int index) {
                switch (index) {
                    case 10: 
                        break;

                    case 11:
                        break;

                    case -1:
                        exit_fight_choice = true;
                        screen.Exit();
                        break;

                    default:
                        bool can_fight_master = playerHasAllBadges(player, leader_list);
                
                        if (!can_fight_master) {
                            if (index >= 0 && index < static_cast<int>(leader_list.size())) {
                                selected_tamer = &leader_list[index];
                                opponent_selected = true;
                                screen.Exit();
                            }
                        } else {
                            if (index >= 0 && index < static_cast<int>(master_list.size())) {
                                selected_tamer = &master_list[index];
                                opponent_selected = true;
                                screen.Exit();
                            }
                        }
                        break;
                }
            };

            auto fight_choice_pair = CreateFightChoiceScreen(player, leader_list, master_list, selected_index, fight_onKeyPressed);
            Component fight_choice_component = fight_choice_pair.second;
            screen.Loop(fight_choice_component);

            if(!playerHasAllBadges(player, leader_list)){
                if (opponent_selected && selected_tamer != nullptr) {
                    GymLeader* selected_leader = dynamic_cast<GymLeader*>(selected_tamer);
                    selected_leader->setSelectedPokemonIndex(0);
                    std::vector<Pokemon> opponent_pokelist_backup = selected_leader->getPokeList();

                    while (!exit_fight_choice) {
                        std::vector<Pokemon>& player_pokemons = player.getPokeList();
                        std::vector<Pokemon>& opponent_pokemons = selected_leader->getPokeList();
                        
                        int player_index = player.getSelectedPokemonIndex();
                        int opponent_index = selected_leader->getSelectedPokemonIndex();

                        Component fight_screen = CreateFightScreen(player, *selected_leader, is_player_turn, player_pokemons, opponent_pokemons);
                        screen.Loop(fight_screen);
                        
                        if(is_player_turn){
                            player_pokemons[player_index].attack(opponent_pokemons[opponent_index]);
                        }else{
                            opponent_pokemons[opponent_index].attack(player_pokemons[player_index]);
                        }
                        
                        if (player.checkhp() || selected_leader->checkhp()) {
                            if(selected_leader->checkhp()){
                                player.set_nombre_badges(selected_leader->getBadge());
                                player.set_nombre_combats_gagnes(1);
                                player.setPokeList(selected_pokemon);
                                player.setSelectedPokemonIndex(0);
                                selected_leader->setPokeList(opponent_pokelist_backup);
                                selected_leader->setSelectedPokemonIndex(0);
                                is_player_turn = true;
                            }
                            if(player.checkhp()){
                                player.set_nombre_combats_perdus(1);
                                player.setPokeList(selected_pokemon);
                                player.setSelectedPokemonIndex(0);
                                selected_leader->setPokeList(opponent_pokelist_backup);
                                selected_leader->setSelectedPokemonIndex(0);
                                is_player_turn = true;
                            }
                            exit_fight_choice = true;
                            break;
                        }

                        if (player_pokemons[player_index].get_hp() == 0) {
                            player.setSelectedPokemonIndex(player_index + 1);
                        }
                        if (opponent_pokemons[opponent_index].get_hp() == 0) {
                            selected_leader->setSelectedPokemonIndex(opponent_index + 1);
                        }

                        is_player_turn = !is_player_turn;
                    }
                }
            }
            else{
                if (opponent_selected && selected_tamer != nullptr) {
                    MasterTamer* selected_master = dynamic_cast<MasterTamer*>(selected_tamer);
                    selected_master->setSelectedPokemonIndex(0);
                    std::vector<Pokemon> opponent_pokelist_backup = selected_master->getPokeList();

                    while (!exit_fight_choice) {
                        std::vector<Pokemon>& player_pokemons = player.getPokeList();
                        std::vector<Pokemon>& opponent_pokemons = selected_master->getPokeList();
                        
                        int player_index = player.getSelectedPokemonIndex();
                        int opponent_index = selected_master->getSelectedPokemonIndex();

                        Component fight_screen = CreateFightScreen(player, *selected_master, is_player_turn, player_pokemons, opponent_pokemons);
                        screen.Loop(fight_screen);
                        
                        if(is_player_turn){
                            player_pokemons[player_index].attack(opponent_pokemons[opponent_index]);
                        }else{
                            opponent_pokemons[opponent_index].attack(player_pokemons[player_index]);
                        }
                        
                        if (player.checkhp() || selected_master->checkhp()) {
                            if(selected_master->checkhp()){
                                player.set_nombre_combats_gagnes(1);
                                player.setPokeList(selected_pokemon);
                                player.setSelectedPokemonIndex(0);
                                selected_tamer->setPokeList(opponent_pokelist_backup);
                                selected_tamer->setSelectedPokemonIndex(0);
                                is_player_turn = true;
                            }
                            if(player.checkhp()){
                                player.set_nombre_combats_perdus(1);
                                player.setPokeList(selected_pokemon);
                                player.setSelectedPokemonIndex(0);
                                selected_tamer->setPokeList(opponent_pokelist_backup);
                                selected_tamer->setSelectedPokemonIndex(0);
                                is_player_turn = true;
                            }
                            exit_fight_choice = true;
                            break;
                        }

                        if (player_pokemons[player_index].get_hp() == 0) {
                            player.setSelectedPokemonIndex(player_index + 1);
                        }
                        if (opponent_pokemons[opponent_index].get_hp() == 0) {
                            selected_master->setSelectedPokemonIndex(opponent_index + 1);
                        }

                        is_player_turn = !is_player_turn;
                    }
                }
            }
            screen.Exit();
        }
        else if (choice == 2) {
            bool exit_stat_screen = false;
            int selected_index = 0;

            auto stat_onKeyPressed = [&](int key_choice) {
                switch (key_choice) {
                    case 1: 
                        // up
                        break;
                    case 2:
                        // down
                        break;
                    case 3: 
                        // move up
                        break;
                    case 4 :
                        // move down
                        break;
                    case 0:
                        exit_stat_screen = true;
                        break;
                    default:
                        break;
                }
            };

            while (!exit_stat_screen) {
                Component stat_screen = CreateStatScreen(player, selected_index, stat_onKeyPressed);
                screen.Loop(stat_screen);
            }
        } 
        
        else if (choice == 3) {
            
            screen.Exit();
        }
    };

    
    do{
        Component menu = CreateMenuScreen(onKeyPressed);
        screen.Loop(menu);

    }while(user_choice != 3);

    return 0;
}
