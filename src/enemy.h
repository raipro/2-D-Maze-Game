#include "main.h"

#ifndef ENEMY_H
#define ENEMY_H


class enemy {
public:
    enemy() {}
    enemy(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    int status = 1;
private:
    VAO *object;
};

#endif // BALL_H