#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/captured_mouse.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/dom/elements.hpp>
#include "../../include/Entraineur.hpp"
#include <typeinfo>

using namespace ftxui;

/*
Pokemon Fight(Pokemon& p1, Pokemon& p2){
    bool turn = true;
}
*/


Component CreateFightScreen(Player& player,Tamer& opponent, bool& is_player_turn, std::vector<Pokemon>& player_pokemons, std::vector<Pokemon>& opponent_pokemons) {

    auto menu_component = Container::Vertical({
        Renderer([&] {

            int player_selected_index = player.getSelectedPokemonIndex();
            int opponent_selected_index = opponent.getSelectedPokemonIndex();

            std::string turn_message;
            std::string attack_details;

            if (is_player_turn) {
                turn_message = "Player's Turn";
                attack_details = "Player attacks " + opponent_pokemons[opponent_selected_index].get_name() +
                                " with " + player_pokemons[player_selected_index].get_name() +
                                " using " + player_pokemons[player_selected_index].get_attack_name() +
                                " inflicting " + std::to_string(player_pokemons[player_selected_index].get_attack_power()) + " damage!";
            } else {
                turn_message = "Opponent's Turn";
                attack_details = "Opponent attacks " + player_pokemons[player_selected_index].get_name() +
                                " with " + opponent_pokemons[opponent_selected_index].get_name() +
                                " using " + opponent_pokemons[opponent_selected_index].get_attack_name() +
                                " inflicting " + std::to_string(opponent_pokemons[opponent_selected_index].get_attack_power()) + " damage!";
            }


            auto player_box = vbox({
                text(player.getName()) | bold | center,
                separator(),
                vbox([&] {
                    Elements elems;
                    for (size_t i = 0; i < player_pokemons.size(); ++i) {
                        if (i == player_selected_index) {
                            elems.push_back(text("> " + player_pokemons[i].get_name()) | bold | color(Color::Green));
                        } else {
                            elems.push_back(text("  " + player_pokemons[i].get_name()));
                        }
                    }
                    return elems;
                }())
            }) | border | flex;

            auto opponent_box = vbox({
                text(opponent.getName()) | bold | center,
                separator(),
                [&] {
                    Elements elems;
                    if(typeid(opponent) == typeid(GymLeader)) {
                        const GymLeader& gym_leader = static_cast<const GymLeader&>(opponent);
                        elems.push_back(text("Badge: " + gym_leader.getBadge()) | bold | center);
                        elems.push_back(text("Gym: " + gym_leader.getGymnase()) | bold | center);
                        elems.push_back(separator());
                    }
                    for (size_t i = 0; i < opponent_pokemons.size(); ++i) {
                        if (i == opponent_selected_index) {
                            elems.push_back(text("> " + opponent_pokemons[i].get_name()) | bold | color(Color::Red));
                        } else {
                            elems.push_back(text("  " + opponent_pokemons[i].get_name()));
                        }
                    }
                    return vbox(std::move(elems));
                }()
            }) | border | flex;

            auto selected_pokemon_box = vbox({
                text("Selected Pokemons") | bold | center,
                separator(),
                hbox({
                    vbox({
                        text("Player") | bold | center,
                        text("Name: " + player_pokemons[player_selected_index].get_name()),
                        text("HP: " + std::to_string(player_pokemons[player_selected_index].get_hp())),
                        text("AP: " + std::to_string(static_cast<int>(player_pokemons[player_selected_index].get_attack_power()))),
                        text("Type1: " + typeToString(player_pokemons[player_selected_index].get_type()[0])),
                        text("Type2: " + typeToString(player_pokemons[player_selected_index].get_type()[1])),
                        text("Attack: " + player_pokemons[player_selected_index].get_attack_name())
                    }) | border | flex,
                    filler(),
                    vbox({
                        text("Opponent") | bold | center,
                        text("Name: " + opponent_pokemons[opponent_selected_index].get_name()),
                        text("HP: " + std::to_string(opponent_pokemons[opponent_selected_index].get_hp())),
                        text("AP: " + std::to_string(static_cast<int>(opponent_pokemons[opponent_selected_index].get_attack_power()))),
                        text("Type1: " + typeToString(opponent_pokemons[opponent_selected_index].get_type()[0])),
                        text("Type2: " + typeToString(opponent_pokemons[opponent_selected_index].get_type()[1])),
                        text("Attack: " + opponent_pokemons[opponent_selected_index].get_attack_name())
                    }) | border | flex
                })
            });

            auto turn_message_box = vbox({
                text(turn_message) | bold | center,
                separator(),
                text(attack_details) | center
            });

            return vbox({
                text("Let The Fight Begin") | center,
                text(player.getName() + " VS " + opponent.getName()) | bold | center,
                separator(),
                hbox({
                    player_box | flex | flex_grow,
                    selected_pokemon_box | flex | flex_grow,
                    opponent_box | flex | flex_grow
                }),
                separator(),
                filler(),
                turn_message_box
            });
        })
    });

    return menu_component; 
}
