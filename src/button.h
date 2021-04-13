#include "main.h"

#ifndef BUTTON_H
#define BUTTON_H


class button {
public:
    button() {}
    button(float x, float y, color_t color,int number);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // BALL_H