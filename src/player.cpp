#include "player.h"
#include "main.h"

Player::Player(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    int num = 360;
    GLfloat vertex_buffer_data[num*9 + 90] = {
       
    };
    int j = 0;
    GLfloat radius = 0.2f;
    for(int i = 0; i < 360; i +=  1){
        vertex_buffer_data[j] =  sin(i* M_PI / 180.0)*radius ;    //X coordinate
        vertex_buffer_data[j+1] = cos(i * M_PI / 180.0)*radius ;    //Y coordinate
        vertex_buffer_data[j+2] = 0.0;                //Z coordinate
        vertex_buffer_data[j+3] = 0.0;
        vertex_buffer_data[j+4] = 0.0;
        vertex_buffer_data[j+5] = 0.0;
        vertex_buffer_data[j+6] =  sin((i+1) * M_PI / 180.0)*radius ;    //X coordinate
        vertex_buffer_data[j+7] = cos((i+1) * M_PI / 180.0)*radius ;    //Y coordinate
        vertex_buffer_data[j+8] = 0.0; 
        j += 9;      
        }
    vertex_buffer_data[j] = -radius;
    vertex_buffer_data[j+1] = 0.0f;
    vertex_buffer_data[j+2] = 0.0f;

    vertex_buffer_data[j+3] = radius;
    vertex_buffer_data[j+4] = 0.0f;
    vertex_buffer_data[j+5] = 0.0f;

    vertex_buffer_data[j + 6] = radius;
    vertex_buffer_data[j+ 7] = -(3*radius)/2;
    vertex_buffer_data[j+ 8] = 0.0f;
    j += 9;

    vertex_buffer_data[j] = -radius;
    vertex_buffer_data[j+1] = 0.0f;
    vertex_buffer_data[j+2] = 0.0f;

    vertex_buffer_data[j+3] = radius;
    vertex_buffer_data[j+4] = -(3*radius)/2;
    vertex_buffer_data[j+5] = 0.0f;

    vertex_buffer_data[j + 6] = -radius;
    vertex_buffer_data[j+ 7] = -(3*radius)/2;
    vertex_buffer_data[j+ 8] = 0.0f;
    j += 9;


    vertex_buffer_data[j] = 0;
    vertex_buffer_data[j+1] = radius/2;
    vertex_buffer_data[j+2] = 0.0f;

    vertex_buffer_data[j+3] = (3*radius)/2;
    vertex_buffer_data[j+4] = radius/2;
    vertex_buffer_data[j+5] = 0.0f;

    vertex_buffer_data[j + 6] = 0;
    vertex_buffer_data[j+ 7] = 0;
    vertex_buffer_data[j+ 8] = 0.0f;
    j += 9;

    vertex_buffer_data[j] = (3*radius)/2;
    vertex_buffer_data[j+1] = 0.0f;
    vertex_buffer_data[j+2] = 0.0f;

    vertex_buffer_data[j+3] = 0.0f;
    vertex_buffer_data[j+4] = 0.0f;
    vertex_buffer_data[j+5] = 0.0f;

    vertex_buffer_data[j + 6] = (3*radius)/2;
    vertex_buffer_data[j+ 7] = radius/2;
    vertex_buffer_data[j+ 8] = 0.0f;
    j += 9;

    vertex_buffer_data[j] = -3*radius/2;
    vertex_buffer_data[j+1] = 0.0f;
    vertex_buffer_data[j+2] = 0.0f;

    vertex_buffer_data[j+3] = -(3*radius/2);
    vertex_buffer_data[j+4] = -(radius);
    vertex_buffer_data[j+5] = 0.0f;

    vertex_buffer_data[j + 6] = -radius;
    vertex_buffer_data[j+ 7] = 0.0f;
    vertex_buffer_data[j+ 8] = 0.0f;
    j += 9;

    vertex_buffer_data[j] = -(radius);
    vertex_buffer_data[j+1] = -(radius);
    vertex_buffer_data[j+2] = 0.0f;

    vertex_buffer_data[j+3] = -(3*radius/2);
    vertex_buffer_data[j+4] = -(radius);
    vertex_buffer_data[j+5] = 0.0f;

    vertex_buffer_data[j + 6] = -radius;
    vertex_buffer_data[j+ 7] = 0.0f;
    vertex_buffer_data[j+ 8] = 0.0f;
    
    j += 9;

    vertex_buffer_data[j] = -radius;
    vertex_buffer_data[j+1] = -(3*radius)/2;
    vertex_buffer_data[j+2] = 0.0f;

    vertex_buffer_data[j+3] = -(radius/2);
    vertex_buffer_data[j+4] = -(3*radius)/2;
    vertex_buffer_data[j+5] = 0.0f;

    vertex_buffer_data[j + 6] = -(radius/2);
    vertex_buffer_data[j+ 7] = -2*radius;
    vertex_buffer_data[j+ 8] = 0.0f;
    j += 9;


    vertex_buffer_data[j] = -radius;
    vertex_buffer_data[j+1] = -(3*radius)/2;
    vertex_buffer_data[j+2] = 0.0f;

    vertex_buffer_data[j+3] = -(radius/2);
    vertex_buffer_data[j+4] = -2*radius;
    vertex_buffer_data[j+5] = 0.0f;

    vertex_buffer_data[j + 6] = -radius;
    vertex_buffer_data[j+ 7] = -2*radius;
    vertex_buffer_data[j+ 8] = 0.0f;
    j += 9;

    vertex_buffer_data[j] = radius/2;
    vertex_buffer_data[j+1] = -(3*radius)/2;
    vertex_buffer_data[j+2] = 0.0f;

    vertex_buffer_data[j+3] = radius;
    vertex_buffer_data[j+4] = -(3*radius)/2;
    vertex_buffer_data[j+5] = 0.0f;

    vertex_buffer_data[j + 6] = radius;
    vertex_buffer_data[j+ 7] = -2*radius;
    vertex_buffer_data[j+ 8] = 0.0f;
    j += 9;


    vertex_buffer_data[j] = radius/2;
    vertex_buffer_data[j+1] = -(3*radius)/2;
    vertex_buffer_data[j+2] = 0.0f;

    vertex_buffer_data[j+3] = radius;
    vertex_buffer_data[j+4] = -2*radius;
    vertex_buffer_data[j+5] = 0.0f;

    vertex_buffer_data[j + 6] = radius/2;
    vertex_buffer_data[j+ 7] = -2*radius;
    vertex_buffer_data[j+ 8] = 0.0f;
    j += 9;



    

    GLfloat color1[num*9 +90];

    for(int i = 0;i<num*9 + 18;i += 3)
    {
        color1[i] = 1.0; 
        color1[i+1] = 0.0;
        color1[i+2]  = 0.0;
    }
    for(int i = num*9 + 18;i < num*9 + 36;i = i+3)
    {
        color1[i] = 0.0; 
        color1[i+1] = 1.0;
        color1[i+2]  = 1.0;
    }
    for(int i = num*9 + 36;i<num*9+54;i = i+3)
    {
        color1[i] = 1.0; 
        color1[i+1] = 0.0;
        color1[i+2]  = 0.0;   
    }
     for(int i = num*9+54;i<num*9 + 90;i += 3)
    {
        color1[i] = 1.0; 
        color1[i+1] = 0.0;
        color1[i+2]  = 0.0;
    }
    this->object = create3DObject(GL_TRIANGLES, num*3 + 30, vertex_buffer_data, color1, GL_FILL);
}

void Player::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Player::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Player::tick() {
    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

