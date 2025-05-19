#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/dom/elements.hpp>
#include "../../include/Entraineur.hpp"

using namespace ftxui;

Component CreateStatScreen(Player& player) {
    
    auto menu_component = Container::Vertical({
        Renderer([&] {

            auto player_box = vbox({
                text(player.getName()) | bold | center,
                separator(),
                vbox([&] {
                    Elements elems;
                    const auto& player_pokemons = player.getPokeList();
                    for (size_t i = 0; i < player_pokemons.size(); ++i) {
                            elems.push_back(text("> " + player_pokemons[i].get_name()) | bold | color(Color::Green));
                    }
                    return elems;
                }())
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
        })
    });

    return menu_component;
}
