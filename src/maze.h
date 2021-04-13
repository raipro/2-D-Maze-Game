#include "main.h"
#include <ctime>
#include "cell.h"

#ifndef maze_H
#define maze_H


class maze {
public:
    maze() {}
    maze(float x, float y, color_t color, cell cell1[10][10],char light[4],int cellx,int celly);
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