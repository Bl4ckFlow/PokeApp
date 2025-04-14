#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

Component CreateUsernameScreen(std::string* username, std::function<void()> onEnterPressed) {
    auto input = Input(username, "Enter your name");

    auto container = Container::Vertical({
        input
    });
    
    

    auto renderer = Renderer(container, [input] {
        return vbox({
            filler(),
            hbox({
                filler(),
                vbox({
                    text("Please enter your username:") | center,
                    input->Render() | border | size(WIDTH, GREATER_THAN, 20)
                }) | border | size(WIDTH, GREATER_THAN, 30) | size(HEIGHT, GREATER_THAN, 5),
                filler()
            }),
            filler()
        });
    });

    renderer |= CatchEvent([onEnterPressed](Event event) {
        if (event == Event::Return) {
            onEnterPressed();  
            return true;
        }
        return false;
    });

    return renderer;
}
