#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/event.hpp>
#include <vector>
#include <string>
#include <utility>
#include "../../include/Entraineur.hpp"

using namespace ftxui;

bool playerHasAllBadges(const Player& player, const std::vector<GymLeader>& leader_list) {
    auto player_badges = player.get_nom_badge();
    for (const auto& leader : leader_list) {
        bool found = false;
        for (const auto& badge : player_badges) {
            if (badge == leader.getBadge()) {
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}

std::pair<Tamer*, Component> CreateFightChoiceScreen(Player& player, std::vector<GymLeader>& leader_list, std::vector<MasterTamer>& master_list, int& selected_index, std::function<void(int)> onKeyPressed) {

    auto fight_choice_component = Container::Vertical({
        Renderer([&] {

            bool can_fight_master = playerHasAllBadges(player, leader_list);
            int total_gym_leaders = static_cast<int>(leader_list.size());
            int total_master_tamers = static_cast<int>(master_list.size());

            Elements gym_elements;
            Elements master_elements;

            if (!can_fight_master) {
                for (int i = 0; i < total_gym_leaders; ++i) {
                    const auto& leader = leader_list[i];
                    std::string display_text = "Gym Leader: " + leader.getName();
                    if (i == selected_index) {
                        gym_elements.push_back(text("> " + display_text) | bold | color(Color::Green));
                    } else {
                        gym_elements.push_back(text("  " + display_text) | color(Color::Red));
                    }
                }
                for (int i = 0; i < total_master_tamers; ++i) {
                    const auto& master = master_list[i];
                    std::string display_text = "Master Tamer: " + master.getName();
                    master_elements.push_back(text("  " + display_text) | color(Color::GrayLight));
                }
            } else {
                for (int i = 0; i < total_gym_leaders; ++i) {
                    const auto& leader = leader_list[i];
                    std::string display_text = "Gym Leader: " + leader.getName();
                    gym_elements.push_back(text("  " + display_text) | color(Color::GrayLight));
                }
                
                for (int i = 0; i < total_master_tamers; ++i) {
                    const auto& master = master_list[i];
                    std::string display_text = "Master Tamer: " + master.getName();
                    if (i == selected_index) {
                        master_elements.push_back(text("> " + display_text) | bold | color(Color::Blue));
                    } else {
                        master_elements.push_back(text("  " + display_text) | color(Color::Purple));
                    }
                }
            }

            return vbox({
                text("Choose your opponent") | bold | center,
                separator(),
                hbox({
                    vbox(gym_elements) | border | flex,
                    separator(),
                    vbox(master_elements) | border | flex
                }) | size(WIDTH, GREATER_THAN, 50) | size(HEIGHT, GREATER_THAN, 20)
            });
        })
    });

    fight_choice_component |= CatchEvent([&, onKeyPressed](Event event) {
        bool can_fight_master = playerHasAllBadges(player, leader_list);
        int total_items = can_fight_master ? static_cast<int>(master_list.size()) : static_cast<int>(leader_list.size());
        
        if (event == Event::Character('z') || event == Event::ArrowUp) {
            if (selected_index > 0) {
                selected_index--;
            }
            onKeyPressed(10);
            return true;
        } else if (event == Event::Character('s') || event == Event::ArrowDown) {
            if (selected_index < total_items - 1) {
                selected_index++;
            }
            onKeyPressed(11);
            return true;
        } else if (event == Event::Character('q') || event == Event::Escape) {

            onKeyPressed(-1); 
            return true;
        } else if (event == Event::Return || event == Event::Character(' ')) {
            onKeyPressed(selected_index);
            return true;
        }
        return false;
    });

    bool can_fight_master = playerHasAllBadges(player, leader_list);
    
    if (!can_fight_master) {
        if (selected_index >= 0 && selected_index < static_cast<int>(leader_list.size())) {
            Tamer* opponent = &leader_list[selected_index];
            return {opponent, fight_choice_component};
        } else {
            selected_index = 0;
            return {&leader_list[0], fight_choice_component};
        }
    } else {
        if (selected_index >= 0 && selected_index < static_cast<int>(master_list.size())) {
            Tamer* opponent = &master_list[selected_index];
            return {opponent, fight_choice_component};
        } else {
            selected_index = 0;
            return {&master_list[0], fight_choice_component};
        }
    }

}
