#include "main.h"

#ifndef POWERUP_H
#define POWERUP_H


class powerup {
public:
    powerup() {}
    powerup(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    int status = 0;
private:
    VAO *object;
};

#endif // BALL_H