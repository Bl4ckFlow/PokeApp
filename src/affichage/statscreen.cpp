#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/event.hpp>
#include <vector>
#include <string>
#include "../../include/Entraineur.hpp"

using namespace ftxui;

Component CreateStatScreen(Player& player, int& selected_index, std::function<void(int)> onKeyPressed) {
    auto stat_component = Container::Vertical({
        Renderer([&] {
            Elements pokemon_elements;
            const auto& pokemons = player.getPokeList();
            for (size_t i = 0; i < pokemons.size(); ++i) {
                const auto& pokemon = pokemons[i];
                const auto& name = pokemon.get_name();
                int hp = pokemon.get_hp();
                std::vector<Type> types = pokemon.get_type();

                std::string type_str;
                if (!types.empty()) {
                    type_str = typeToString(types[0]);
                    if (types.size() > 1) {
                        type_str += ", " + typeToString(types[1]);
                    }
                }

                std::string display_text = name + " (HP: " + std::to_string(hp) + ") [" + type_str + "]";

                if (static_cast<int>(i) == selected_index) {
                    pokemon_elements.push_back(text("> " + display_text) | bold | color(Color::Green));
                } else {
                    pokemon_elements.push_back(text("  " + display_text) | color(Color::Red));
                }
            }

            auto player_box = vbox({
                text(player.getName()) | bold | center,
                separator(),
                vbox(pokemon_elements)
            }) | border | size(WIDTH, GREATER_THAN, 30);

            Elements badge_elements;
            const auto& badges = player.get_nom_badge();
            for (const auto& badge : badges) {
                badge_elements.push_back(text("- " + badge));
            }

            auto stats_box = vbox({
                text("Stats") | bold | center,
                separator(),
                text("Fights Won: " + std::to_string(player.get_nombre_combats_gagnes())),
                text("Fights Lost: " + std::to_string(player.get_nombre_combats_perdus())),
                separator(),
                text("Badges:"),
                vbox(badge_elements)
            }) | border | size(WIDTH, GREATER_THAN, 30);

            return vbox({
                filler(),
                hbox({
                    filler(),
                    vbox({
                        text("Player Stats Screen") | center | bold,
                        separator(),
                        hbox({
                            player_box | flex,
                            stats_box | flex,
                        }),
                    }) | border | size(WIDTH, GREATER_THAN, 70) | size(HEIGHT, GREATER_THAN, 10),
                    filler()
                }),
                filler()
            });
        })
    });

    // Attach event handler to the container
    stat_component |= CatchEvent([onKeyPressed, &selected_index, &player](Event event) {
        const int max_index = static_cast<int>(player.getPokeList().size()) - 1;
        if (event == Event::Character('z')) {
            if (selected_index > 0) {
                selected_index--;
            }
            onKeyPressed(1); // up
            return true;
        }
        else if (event == Event::Character('s')) {
            if (selected_index < max_index) {
                selected_index++;
            }
            onKeyPressed(2); // down
            return true;
        }
        else if (event == Event::Character('e')) { 
            player.movePokemonUp(selected_index);
            if(selected_index <6 && selected_index >0){
                selected_index--;
            }
            onKeyPressed(3); // move up
            return true;
        }
        else if (event == Event::Character('d')) {
            player.movePokemonDown(selected_index);
            if(selected_index >=0 && selected_index <5){
                selected_index++;
            }
            onKeyPressed(4); // move down
            return true;
        }
        else if (event == Event::Character('q')) {
            onKeyPressed(0); // exit signal
            return true;
        }
        else{
            return true;
        }
    });

    return stat_component;
}

