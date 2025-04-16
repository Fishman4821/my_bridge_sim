#include <iostream>
#include <vector>
#include <string.h>

#define SDL_MAIN_HANDLED

#include "my_modular_graphical_interface/mgui.cpp"

using namespace std;

int main() {
    State state = State("test", 640, 480, 120, WINDOW_RESIZEABLE | INPUT_MULTI_THREADED | ELEMENTS_ENABLE);
    while (!state.quit) {
        state.start_frame();
        state.r.rect(0, 0, 640, 480, Color(255, 255, 0));
        
        state.end_frame();
    }
}