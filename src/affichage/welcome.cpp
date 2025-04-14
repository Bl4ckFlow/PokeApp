#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;


Component CreateWelcomeScreen(std::function<void()> onEnterPressed) {
    auto welcome_component = Container::Vertical({
        Renderer([] {
            return vbox({
                filler(),
                hbox({
                    filler(),
                    vbox({
                        text("Welcome To PokeBattle") | bold | center,
                        text("Press Enter to continue...") | center
                    }),
                    filler()
                }),
                filler()
            });
        })
    });
    

    welcome_component |= CatchEvent([onEnterPressed](Event event) {
        if (event == Event::Return) {
            onEnterPressed();  
            return true;
        }
        return false;
    });
    
    return welcome_component;
}


