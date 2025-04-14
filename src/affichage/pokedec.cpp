#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/dom/elements.hpp>
#include "../../include/Pokemon.hpp"
#include <array>
#include <iomanip>  
#include <sstream>
#include <memory>
#include <numeric>

using namespace ftxui;

Decorator findColor(Type t){
    switch (t) {
        case Type::Fire:      return color(Color::Red);
        case Type::Water:     return color(Color::Blue);
        case Type::Plant:     return color(Color::Green);
        case Type::Electric:  return color(Color::Yellow);
        case Type::Ice:       return color(Color::Green);
        case Type::Combat:    return color(Color::Gold1);
        case Type::Poison:    return color(Color::MediumPurple);
        case Type::Ground:    return color(Color::SandyBrown);
        case Type::Flight:    return color(Color::SkyBlue1);
        case Type::Psychic:   return color(Color::HotPink);
        case Type::Insect:    return color(Color::DarkOliveGreen1);
        case Type::Rock:      return color(Color::DarkGoldenrod);
        case Type::Specter:   return color(Color::MediumPurple4);
        case Type::Dragon:    return color(Color::MediumPurple1);
        case Type::Darkness:  return color(Color::GrayDark);
        case Type::Steel:     return color(Color::LightSlateGrey);
        case Type::Fairy:     return color(Color::Pink1);
        case Type::Normal:    return color(Color::GrayLight);
        case Type::None:      return color(Color::Grey30);  
        default:              return color(Color::Green); 
    }
}

Component PokemonList(std::vector<Pokemon> const &poke_list, std::vector<Pokemon>* selected_pokemons_out) {

    auto checked = std::make_shared<std::vector<int>>(poke_list.size(), 0);

    auto get_selected_count = [checked]() {
        return std::count(checked->begin(), checked->end(), 1);
    };

    std::vector<Component> checkbox_components;

    for (size_t i = 0; i < poke_list.size(); ++i) {
        
        const Pokemon& p = poke_list[i];

        CheckboxOption option;
        option.checked = &(*checked)[i];

        option.transform = [checked, get_selected_count, i, &p](const EntryState& s) {
            bool limit_reached = get_selected_count() >= 6;
            bool is_disabled = !(*checked)[i] && limit_reached;
    
            auto element = hbox({
                text((*checked)[i] ? "[X]" : "[ ]"),
                text(" "),
                text(p.get_name())                             | size(WIDTH, EQUAL, 12),
                text("|"),
                text(typeToString(p.get_type()[0]))            | size(WIDTH, EQUAL, 10) | findColor(p.get_type()[0]),
                text("|"),
                text(typeToString(p.get_type()[1]))            | size(WIDTH, EQUAL, 10) | findColor(p.get_type()[1]),
                text("|"),
                text(std::to_string(p.get_hp()))               | size(WIDTH, EQUAL, 8)  | color(Color::Green),
                text("|"),
                text(std::to_string(p.get_attack_power()))     | size(WIDTH, EQUAL, 10) | color(Color::Red),
                text("|"),
                text(p.get_attack_name())                      | size(WIDTH, EQUAL, 15) | color(Color::Grey30),
            });

            if (s.active) element |= inverted;
            if (is_disabled) element |= dim;
            return element;
        };
    
        option.on_change = [checked, get_selected_count, i]() {
            if ((*checked)[i] == 0 && get_selected_count() >= 6)
                return;
            (*checked)[i] = 1 - (*checked)[i];
        };

        auto checkbox = Checkbox(option);
        checkbox_components.push_back(checkbox);
    }

    auto list_container  = Container::Vertical(checkbox_components);

    auto continue_button = Button("Continue", [checked, selected_pokemons_out, &poke_list]() {
        if (std::count(checked->begin(), checked->end(), 1) == 6) {
        for (size_t i = 0; i < checked->size(); ++i) {
            if ((*checked)[i]) {
                selected_pokemons_out->push_back(poke_list[i]);
            }
        }
        ScreenInteractive::Active()->Exit();
    }
    });

    auto main_container = Container::Vertical({
        list_container,
        continue_button
    });

    auto renderer = Renderer(main_container, [list_container, continue_button] {
        
        auto checkbox_box = list_container->Render() |
                            vscroll_indicator |
                            frame |
                            size(HEIGHT, EQUAL, 5);

        auto layout = vbox({
            text("Select up to 6 Pokémon") | bold | center,
            separator(),
            checkbox_box,
            separator(),
            hbox({ filler(), continue_button->Render(), filler() }),
        }) | border | center | vcenter;

        return layout;
    });

    return renderer;
}


