#include "./affichage/welcome.cpp"
#include "./affichage/username.cpp"
#include "./affichage/pokedec.cpp"
#include "./affichage/menuscreen.cpp"
#include "../include/Entraineur.hpp"
#include "./load_func.cpp"

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

    int user_choice;
    auto onKeyPressed = [&](int choice) {
        user_choice = choice;
        if (choice == 1) {
            
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