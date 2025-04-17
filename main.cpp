#include <iostream>
#include <vector>
#include <string.h>

#define SDL_MAIN_HANDLED

#include "my_modular_graphical_interface/mgui.cpp"

using namespace std;

#define LINKED_LIST_ADD(type, name) void name(type** l, type m) {type* next = (type*)malloc(sizeof(type));*next = m;if (*l == nullptr) {*l = next;return;}type* end;type* current = *l;while (current != nullptr) {end = current;current = current->next;}end->next = next;next->prev = end;}

struct Member;
struct Joint;

struct Member {
    bool solid;
    
    Member* prev;
    Member* next;
};

LINKED_LIST_ADD(Member, add_member)

struct Joint {
    bool fixed;
    Vec2 pos;
    Member* members;
    Joint* prev;
    Joint* next;
};

LINKED_LIST_ADD(Joint, add_joint)

void camera_inputs(State* state, float* v_x, float* v_y, float* z_f) {
    float s_dt = 1.0f * state->t.dt;
    if (state->i.get_key(KC_W)) {
        *v_y += s_dt;
    }
    if (state->i.get_key(KC_S)) {
        *v_y -= s_dt;
    }
    if (state->i.get_key(KC_A)) {
        *v_x -= s_dt;
    }
    if (state->i.get_key(KC_D)) {
        *v_x += s_dt;
    }
    if (state->i.get_key_pressed(KC_Q)) {
        *z_f /= 2.0f;
    }
    if (state->i.get_key_pressed(KC_E)) {
        *z_f *= 2.0f;
    }
}

void draw_background(State* state, float v_x, float v_y, float z_f) {

}

int main() {
    State state = State("test", 640, 480, 120, WINDOW_RESIZEABLE | INPUT_MULTI_THREADED | ELEMENTS_ENABLE);
    
    Member* members = nullptr;
    add_member(&members, {false, 0, 0});
    Joint* joints = nullptr;
    add_joint(&joints, {true, {0, 0}, members, 0, 0});
    add_joint(&joints, {true, {1, 0}, members, 0, 0});

    const int g_s = 25;
    float v_x = 0; 
    float v_y = 0; 
    float z_f = 1;

    while (!state.quit) {
        state.start_frame();
        camera_inputs(&state, &v_x, &v_y, &z_f);
        draw_background(&state, v_x, v_y, z_f);
        state.end_frame();
    }
}