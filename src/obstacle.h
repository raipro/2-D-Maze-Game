#include "main.h"

#ifndef OBSTACLE_H
#define OBSTACLE_H


class obstacle {
public:
    obstacle() {}
    obstacle(float x, float y, color_t color);
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