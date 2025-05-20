#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/event.hpp>
#include <vector>
#include <string>
#include "../../include/Entraineur.hpp"

using namespace ftxui;

Component CreateStatScreen(Player& player, int& selected_index, char* key){

    auto menu_component = Container::Vertical({
        CatchEvent(Renderer([&] {
            Elements elems;
            const auto& pokemons = player.getPokeList();
            for (size_t i = 0; i < pokemons.size(); ++i) {
                if (static_cast<int>(i) == selected_index) {
                    elems.push_back(text("> " + pokemons[i].get_name()) | bold | color(Color::Green));
                } else {
                    elems.push_back(text("  " + pokemons[i].get_name()));
                }
            }

            auto player_box = vbox({
                text(player.getName()) | bold | center,
                separator(),
                vbox(elems) | border | flex
            }) | border | flex;

            // Player's fights won/lost and badges info
            auto stats_box = vbox({
                text("Stats") | bold | center,
                separator(),
                text("Fights Won: " + std::to_string(player.get_nombre_combats_gagnes())),
                text("Fights Lost: " + std::to_string(player.get_nombre_combats_perdus())),
                separator(),
                text("Badges:"),
                vbox([&] {
                    Elements badge_elems;
                    const auto& badges = player.get_nom_badge();
                    for (const auto& badge : badges) {
                        badge_elems.push_back(text("- " + badge));
                    }
                    return badge_elems;
                }())
            }) | border | flex;

            return vbox({
                text("Player Stats Screen") | center | bold,
                separator(),
                hbox({
                    player_box | flex | flex_grow,
                    stats_box | flex | flex_grow
                }),
                separator(),
                filler()
            });
        }),
        [&](Event event) {
            if (event.is_character()) {
                *key = event.character()[0];
            }
            return true;
        }
        )
    });

    return menu_component;
}
