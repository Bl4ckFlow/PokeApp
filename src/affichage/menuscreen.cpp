#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/captured_mouse.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

Component CreateMenuScreen(std::function<void(int)> onKeyPressed) {
    auto menu_component = Container::Vertical({
        Renderer([] {
            return vbox({
                filler(),
                hbox({
                    filler(),
                    vbox({
                        text("1. Press 's' to start game.")
                            | color(Color::White)
                            | bold
                            | center,
                        text("2. Press 'c' to check player stats.")
                            | color(Color::White)
                            | bold
                            | center,
                        text("3. Press 'q' to exit.")
                            | color(Color::White)
                            | bold
                            | center,
                    }) | center,
                    filler(),
                }),
                filler(),
            });
        })
    }) | vcenter;


    menu_component |= CatchEvent([onKeyPressed](Event event) {
        if (event == Event::Character('s')) {
            onKeyPressed(1);
            return true;
        }
        if (event == Event::Character('c')) {
            onKeyPressed(2);
            return true;
        }
        if (event == Event::Character('q')) {
            onKeyPressed(3);
            return true;
        }
        return false;
    });

    return menu_component;
}
