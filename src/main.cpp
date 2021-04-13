#include "main.h"
#include "timer.h"
#include "player.h"
#include "maze.h"
#include "enemy.h"
#include "button.h"
#include "powerup.h"
#include "obstacle.h"
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/
int cellx,celly;
int tasks = 2;
int time1 = 300;
char light[4] = "on";
int spawn = 0;
int gend = 0;
Player Player1;
maze maze1;
enemy enemy1;
button button1;
button button2;
powerup powerup1;
powerup powerup2;
obstacle obstacle1;
obstacle obstacle2;
cell cell1[10][10];
int ltime = 0;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 90;

int program1ID;
void RenderText(std::string text, float x, float y, float scale, glm::vec3 color,glm::mat4 MVP);
Timer t10(1.0 / 10);
unsigned int VAO1, VBO1;

struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // Size of glyph
    glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
};
std::map<GLchar, Character> Characters;
/* Render the scene with openGL */
/* Edit this function according to your assignment */
void BellmanFord() {
   int move = -1;
    int cellp1x = -1,cellp1y = -1,cellp2x = -1,cellp2y = -1,cello1x = -1,cello1y = -1,cello2x = -1,cello2y = -1; 
  int cellb1x = (int)(button1.position[0]*10);
   int cellb1y = (int)(button1.position[1]*10);
   cellb1x = (int)((cellb1x + 27)/6);
   cellb1y = (int)((cellb1y + 27)/6);

   int cellb2x = (int)(button2.position[0]*10);
   int cellb2y = (int)(button2.position[1]*10);
   cellb2x = (int)((cellb2x + 27)/6);
   cellb2y = (int)((cellb2y + 27)/6);

    if(spawn==1)
    {
        if(powerup1.status==1)
        {     
            cellp1x = (int)(powerup1.position[0]*10);
            cellp1y = (int)(powerup1.position[1]*10);
            cellp1x = (int)((cellp1x + 27)/6);
            cellp1y = (int)((cellp1y + 27)/6);
        }

        if(powerup2.status==1)
        {
            cellp2x = (int)(powerup2.position[0]*10);
            cellp2y = (int)(powerup2.position[1]*10);
            cellp2x = (int)((cellp2x + 27)/6);
            cellp2y = (int)((cellp2y + 27)/6);
        }
        
        cello1x = (int)(obstacle1.position[0]*10);
        cello1y = (int)(obstacle1.position[1]*10);
        cello1x = (int)((cello1x + 27)/6);
        cello1y = (int)((cello1y + 27)/6);

        cello2x = (int)(obstacle2.position[0]*10);
        cello2y = (int)(obstacle2.position[1]*10);
        cello2x = (int)((cello2x + 27)/6);
        cello2y = (int)((cello2y + 27)/6);
    }
   int cellex = (int)(enemy1.position[0]*10);
   int celley = (int)(enemy1.position[1]*10);
   cellex = (int)((cellex + 27)/6);
   celley = (int)((celley + 26)/6);
   std::cout<<powerup1.position[0]<<" "<<powerup1.position[1]<<" "<<cellp1x<<" "<<cellp1y<<std::endl;
    

    int dist[100];
    for(int i=0;i<=99;i++)
    {
        dist[i] = 10000;
    }
    // std::cout<<celly<<" "<<cellx<<std::endl;
    dist[10*celly + cellx] = 0;
    vector<pair<int,int>>edges;
    for(int i=0;i<=99;i++)
    {
       
        if(i==0)
        {
            if(cell1[0][0].north == 0)
            {
                
                edges.push_back(make_pair(i,10+i));
            }
            if(cell1[0][0].east == 0)
            {
                edges.push_back(make_pair(i,i+1));
            }
        }
        else if(i == 99)
        {
             if(cell1[9][9].south == 0)
            {
                edges.push_back(make_pair(i,i - 10));
            }
            if(cell1[9][9].west == 0)
            {
                edges.push_back(make_pair(i,i-1));
            }
        }
        else 
        {
            if(cell1[(i%10)][(i/10)].north == 0)
            {
                edges.push_back(make_pair(i,10+i));
            }
             if(cell1[(i%10)][(i/10)].east == 0)
            {
                edges.push_back(make_pair(i,i+1));
            }
             if(cell1[(i%10)][(i/10)].south == 0)
            {
                edges.push_back(make_pair(i,i - 10));
            }
            if(cell1[(i%10)][(i/10)].west == 0)
            {
                edges.push_back(make_pair(i,i-1));
            }

        }
    }

    // std::cout<<" goti"<<std::endl;
    vector<int> vec(edges.size(),0);
    for(int i=0;i<edges.size();i++)
    {
    if( edges[i].first== 10*cellb1y + cellb1x || edges[i].first== 10*cellb2y + cellb2x || edges[i].first== 10*cellp1y + cellp1x || edges[i].first== 10*cellp2y + cellp2x || edges[i].first== 10*cello1y + cello1x || edges[i].first== 10*cello2y + cello2x)
       {
            // std::cout<<" kartik "<<std::endl;
            // edges.erase(std::remove(edges.begin(), edges.end(), edges[i]), edges.end());
            // i--;
            vec[i] = 1;
       }
      else if( edges[i].second== 10*cellb1y + cellb1x || edges[i].second== 10*cellb2y + cellb2x || edges[i].second== 10*cellp1y + cellp1x || edges[i].second== 10*cellp2y + cellp2x || edges[i].second== 10*cello1y + cello1x || edges[i].second== 10*cello2y + cello2x)
       {
        //    std::cout<<" shreyash "<<std::endl;
        //     edges.erase(std::remove(edges.begin(), edges.end(), edges[i]), edges.end());
        //     i--;
        vec[i] = 1;
       }          
    
    }
    int num= 0;
    for(int i=0;i<edges.size();i++)
    {
        if(vec[i] == 0)
        {
            num++;
        }
    }
    // std::cout<<num<<" "<<edges.size()<<std::endl;
    for(int j=0;j<99;j++)
    {
    for(int i = 0;i<edges.size();i++)
    {
      
      if (vec[i]==0 && (dist[edges[i].second] > (dist[edges[i].first] + 1)))
      {
          if(edges[i].second == 10*celley + cellex)
          {
            //  std::cout<<edges[i].first<<" "<<edges[i].second<<std::endl;  
            move = i;
            //  std::cout<<move.first<<" "<<move.second<<std::endl;
          }
          dist[edges[i].second] = dist[edges[i].first] + 1;
      }  
    }
    }
    if(move == -1)
    {
        // std::cout<<"fuck"<<std::endl;
        return;
    }
    enemy1.position[0]  = (6*(edges[move].first%10) - 27) / 10.0;
    enemy1.position[1]  = (6*(edges[move].first/10) - 26) / 10.0; 
    std::cout<<enemy1.position[0]<<"  "<<enemy1.position[1]<<std::endl;
}
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) ); 
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    if(gend == 1 || gend == 2)
    {
        GLfloat vertex_buffer_data[]= {
            4.0f,4.0f,0.0f,
            -4.0f,4.0f,0.0f,
            -4.0f,-4.0f,0.0f,

            -4.0f,-4.0f,0.0f,
            4.0f,4.0f,0.0f,
            4.0f,-4.0f,0.0f
        };        
        struct VAO* object = create3DObject(GL_TRIANGLES, 24, vertex_buffer_data, COLOR_BLACK, GL_FILL);
        Matrices.model = glm::mat4(1.0f);
        // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
        // rotate          = rotate * glm::translate(glm::v3(0, -0.6, 0));
        glm::mat4 MVP = VP * Matrices.model;
        glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
        draw3DObject(object);
    }
    else
    {
    if(!strcmp(light,"off"))
    {   int j1 = 0;
        GLfloat vertex_buffer_data[72] = {}; 
        vertex_buffer_data[j1] = 3.0f;
        vertex_buffer_data[j1+1] = 3.0f;
        vertex_buffer_data[j1+2] = 0.6f;
        
        vertex_buffer_data[j1+3] = -3.0f;
        vertex_buffer_data[j1+4] = 3.0f;
        vertex_buffer_data[j1+5] = 0.6f;

        vertex_buffer_data[j1+6] = -3.0f;
        vertex_buffer_data[j1+7] = 0.6*(celly+2) - 3;
        vertex_buffer_data[j1+8] = 0.6f;
        j1 += 9;

        vertex_buffer_data[j1] = 3.0f;
        vertex_buffer_data[j1+1] = 3.0f;
        vertex_buffer_data[j1+2] = 0.6f;
        
        vertex_buffer_data[j1+3] = -3.0f;
        vertex_buffer_data[j1+4] = 0.6*(celly+2) -3;
        vertex_buffer_data[j1+5] = 0.6f;

        vertex_buffer_data[j1+6] = 3.0f;
        vertex_buffer_data[j1+7] = 0.6*(celly+2) - 3;
        vertex_buffer_data[j1+8] = 0.6f;
        j1 += 9;

        vertex_buffer_data[j1] = -3.0f;
        vertex_buffer_data[j1+1] = -3.0f;
        vertex_buffer_data[j1+2] = 0.6f;
        
        vertex_buffer_data[j1+3] = 3.0f;
        vertex_buffer_data[j1+4] = -3.0f;
        vertex_buffer_data[j1+5] = 0.6f;

        vertex_buffer_data[j1+6] = -3.0f;
        vertex_buffer_data[j1+7] = 0.6*(celly-1) - 3;
        vertex_buffer_data[j1+8] = 0.6f;
        j1 += 9;

        vertex_buffer_data[j1] = 3.0f;
        vertex_buffer_data[j1+1] = -3.0f;
        vertex_buffer_data[j1+2] = 0.6f;
        
        vertex_buffer_data[j1+3] = -3.0f;
        vertex_buffer_data[j1+4] = 0.6*(celly-1) -3;
        vertex_buffer_data[j1+5] = 0.6f;

        vertex_buffer_data[j1+6] = 3.0f;
        vertex_buffer_data[j1+7] = 0.6*(celly-1) - 3;
        vertex_buffer_data[j1+8] = 0.6f;
        j1 += 9;

        vertex_buffer_data[j1] = -3.0f;
        vertex_buffer_data[j1+1] = 0.6*(celly+2)-3;
        vertex_buffer_data[j1+2] = 0.6f;
        
        vertex_buffer_data[j1+3] = 0.6*(cellx -1)-3;
        vertex_buffer_data[j1+4] = 0.6*(celly+2)-3;
        vertex_buffer_data[j1+5] = 0.6f;

        vertex_buffer_data[j1+6] = 0.6*(cellx-1)-3;
        vertex_buffer_data[j1+7] = 0.6*(celly-1) - 3;
        vertex_buffer_data[j1+8] = 0.6f;
        j1 += 9;

        vertex_buffer_data[j1] = -3.0f;
        vertex_buffer_data[j1+1] = 0.6*(celly+2)-3;
        vertex_buffer_data[j1+2] = 0.6f;
        
        vertex_buffer_data[j1+3] = -3.0f;
        vertex_buffer_data[j1+4] = 0.6*(celly-1) -3;
        vertex_buffer_data[j1+5] = 0.6f;

        vertex_buffer_data[j1+6] = 0.6*(cellx-1) -3;
        vertex_buffer_data[j1+7] = 0.6*(celly-1) - 3;
        vertex_buffer_data[j1+8] = 0.6f;
        j1 += 9;

        vertex_buffer_data[j1] =  3.0f;
        vertex_buffer_data[j1+1] = (GLfloat)0.6*(celly+2)-3.0;
        vertex_buffer_data[j1+2] = 0.6f;
        
        vertex_buffer_data[j1+3] = (GLfloat)0.6*(cellx+2.0) - 3.0;
        vertex_buffer_data[j1+4] = (GLfloat)0.6*(celly+2.0) - 3.0;
        vertex_buffer_data[j1+5] = 0.6f;

        vertex_buffer_data[j1+6] = (GLfloat)0.6*(cellx+2) - 3.0;
        vertex_buffer_data[j1+7] = (GLfloat)0.6*(celly-1) - 3.0;
        vertex_buffer_data[j1+8] = 0.6f;
        j1 += 9;

        vertex_buffer_data[j1] =  3.0f;
        vertex_buffer_data[j1+1] = (GLfloat)0.6*(celly+2)-3.0;
        vertex_buffer_data[j1+2] = 0.6f;

        vertex_buffer_data[j1+3] = 3.0f;
        vertex_buffer_data[j1+4] = (GLfloat)0.6*(celly-1) - 3.0;
        vertex_buffer_data[j1+5] = 0.6f;

        vertex_buffer_data[j1+6] = (GLfloat)0.6*(cellx +2) - 3.0;
        vertex_buffer_data[j1+7] = (GLfloat)0.6*(celly-1) - 3.0;
        vertex_buffer_data[j1+8] = 0.6f;
        j1 += 9;

    


    // maze object;
    struct VAO* object = create3DObject(GL_TRIANGLES, 24, vertex_buffer_data, COLOR_BLACK, GL_FILL);
    Matrices.model = glm::mat4(1.0f);
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::v3(0, -0.6, 0));
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(object);

    }
    Player1.draw(VP);
    maze1.draw(VP);
    if(enemy1.status == 1)
        enemy1.draw(VP);
    button1.draw(VP);
    button2.draw(VP);
    if(spawn == 1)
    {
        // if (powerup1.status == 0  && powerup2.status == 0)
        // {
        //     tasks = tasks - 1;
        // }
        if(powerup1.status == 1)
            powerup1.draw(VP);
        if(powerup2.status == 1)    
            powerup2.draw(VP);
        obstacle1.draw(VP);
        obstacle2.draw(VP);
    }
    }
    if(gend==2)
        RenderText("YOU WON!!", -100.0f, 0.0f, 0.3f, glm::vec3(0.0f, 1.0f, 0.0f),VP);
    else if(gend == 1)
        RenderText("GAME OVER!!", -100.0f, 0.0f, 0.3f, glm::vec3(0.0f, 1.0f, 0.0f),VP);
    else    
        RenderText("Health: " + to_string(Player1.health) + " Time: " + to_string(time1) + " Lighting: " + light + " Tasks: " + to_string(tasks), -200.0f, 200.0f, 0.3f, glm::vec3(0.0f, 1.0f, 0.0f),VP);
}

void RenderText(std::string text, float x, float y, float scale, glm::vec3 color,glm::mat4 MVP)
{
    // activate corresponding render state	
    glUseProgram(program1ID);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
    glUniform3f(glGetUniformLocation(program1ID, "textColor"), color.x, color.y, color.z);
    glUniformMatrix4fv(glGetUniformLocation(program1ID, "projection"), 1, GL_FALSE, &MVP[0][0]);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO1);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },            
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }           
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO1);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up  = glfwGetKey(window, GLFW_KEY_UP);
    int down  = glfwGetKey(window, GLFW_KEY_DOWN);
    int toggle  = glfwGetKey(window, GLFW_KEY_C);
    int position0 = (int)(Player1.position[0]*10);
    int position1 = (int)(Player1.position[1]*10);
    int positione0 = (int)(enemy1.position[0]*10);
    int positione1 = (int)(enemy1.position[1]*10);

    if((position0 == positione0 && position1 == positione1 && enemy1.status == 1) || Player1.health == 0)
    {
        enemy1.status = 0;
        gend = 1;
    }
    if(cellx >= 9 && celly >= 9 && tasks==0)
        gend = 2;        
    // std::cout<<Player1.position[0]<<" tapori pp0 "<<Player1.position[1]<<" tapori pp1 "<<std::endl;
    // std::cout<<position0<<" tapori p0 "<<position1<<" tapori p1 "<<std::endl;
    if (right) {
        cellx = (int)((position0 + 27)/6);
        celly = (int)((position1 + 26)/6);
        // std::cout<<cellx<<" tapori cellx "<<celly<<" tapori celly "<<std::endl;
        if(cell1[cellx][celly].east == 0 )
        {        
            Player1.position[0] = (position0 +  6)/10.0;
            if((position0 == ((int)(button2.position[0] * 10)) && position1 == ((int)(button2.position[1]*10) + 1))&& enemy1.status == 1)
            {
                enemy1.status = 0;
                tasks = tasks -1;
            }
            else if ((position0 == ((int)(button1.position[0] * 10)) && position1 == ((int)(button1.position[1]*10) + 1)) && spawn==0)
            {
                spawn = 1;
                powerup1.status = 1;
                powerup2.status = 1;
            }
            else if(((position0 == ((int)(powerup1.position[0]*10)) && position1 == ((int)(powerup1.position[1]*10) + 1)) && powerup1.status == 1)&& spawn == 1 )
            {
                Player1.health += 5;
                powerup1.status = 0;
                if(powerup2.status == 0)
                    tasks = tasks -1;
            }
            else if(((position0 == (int)(powerup2.position[0]*10) && position1 == ((int)(powerup2.position[1]*10) + 1) && powerup2.status==1))&& spawn == 1)
            {
                Player1.health += 5;
                powerup2.status = 0;
                if(powerup1.status == 0)
                    tasks = tasks -1;

            }
            else if(((position0 == (int)(obstacle1.position[0]*10) && position1 == ((int)(obstacle1.position[1]*10) + 1)) or (position0 == (int)(obstacle2.position[0]*10) && position1 == (int(obstacle2.position[1]*10) + 1)))&& spawn == 1)
            {
                Player1.health -= 2;
            }
        }   // Do something
    }
    if(left) {
        cellx = (int)((position0 + 27)/6);
        celly = (int)((position1 + 26)/6);
        // std::cout<<cellx<<" tapori cellx "<<celly<<" tapori celly "<<std::endl;
        if(cell1[cellx][celly].west == 0 )
        {
            Player1.position[0] = (position0 -  6)/10.0;
            if((position0 == ((int)(button2.position[0] * 10)) && position1 == ((int)(button2.position[1]*10) + 1))&& enemy1.status == 1)
            {
                enemy1.status = 0;
                tasks = tasks -1;
            }
            else if((position0 == ((int)(button1.position[0] * 10)) && position1 == ((int)(button1.position[1]*10) + 1)) && spawn==0)
            {
                spawn = 1;
                powerup1.status = 1;
                powerup2.status = 1;
            }
            else if(((position0 == ((int)(powerup1.position[0]*10)) && position1 == ((int)(powerup1.position[1]*10) + 1)) && powerup1.status == 1)&& spawn == 1 )
            {
                // std::cout<<"shreyash lulli"<<std::endl;
                Player1.health += 5;
                powerup1.status = 0;
                if(powerup2.status == 0)
                    tasks = tasks -1;
            }
            else if(((position0 == (int)(powerup2.position[0]*10) && position1 == ((int)(powerup2.position[1]*10) + 1) && powerup2.status==1))&& spawn == 1)
            {
                Player1.health += 5;
                powerup2.status = 0;
                if(powerup1.status == 0)
                    tasks = tasks -1;

            }
            else if(((position0 == (int)(obstacle1.position[0]*10) && position1 == ((int)(obstacle1.position[1]*10) + 1)) or (position0 == (int)(obstacle2.position[0]*10) && position1 == (int(obstacle2.position[1]*10) + 1)))&& spawn == 1)
            {
                Player1.health -= 2;
            }
        }
    }
    if(up) {
       
        cellx = (int)((position0 + 27)/6);
        celly = (int)((position1 + 26)/6);
        // std::cout<<cellx<<" tapori cellx "<<celly<<" tapori celly "<<std::endl;
        if(cell1[cellx][celly].north == 0 )
        {
            Player1.position[1] = (position1 +  6)/10.0;
            if((position0 == ((int)(button2.position[0] * 10)) && position1 == ((int)(button2.position[1]*10) + 1)) && enemy1.status == 1)
            {
                enemy1.status = 0;
                tasks = tasks - 1;
            }
            else if((position0 == ((int)(button1.position[0] * 10)) && position1 == ((int)(button1.position[1]*10) + 1)) && spawn==0)
            {
                spawn = 1;
                powerup1.status = 1;
                powerup2.status = 1;
            }
            else if(((position0 == ((int)(powerup1.position[0]*10)) && position1 == ((int)(powerup1.position[1]*10) + 1)) && powerup1.status == 1)&& spawn == 1 )
            {
                Player1.health += 5;
                powerup1.status = 0;
                if(powerup2.status == 0)
                    tasks = tasks -1;
            }
            else if(((position0 == (int)(powerup2.position[0]*10) && position1 == ((int)(powerup2.position[1]*10) + 1) && powerup2.status==1))&& spawn == 1)
            {
                Player1.health += 5;
                powerup2.status = 0;
                if(powerup1.status == 0)
                    tasks = tasks -1;

            }
            else if(((position0 == (int)(obstacle1.position[0]*10) && position1 == ((int)(obstacle1.position[1]*10) + 1)) or (position0 == (int)(obstacle2.position[0]*10) && position1 == (int(obstacle2.position[1]*10) + 1)))&& spawn == 1)
            {
                Player1.health -= 2;
            }
        }
    }
    if(down) {
       
        cellx = (int)((position0 + 27)/6);
        celly = (int)((position1 + 26)/6);
        // std::cout<<cellx<<" tapori cellx "<<celly<<" tapori celly "<<std::endl;
        if(cell1[cellx][celly].south == 0 )
        {    
            Player1.position[1] = (position1 -  6)/10.0;
            if((position0 == ((int)(button2.position[0] * 10)) && position1 == ((int)(button2.position[1]*10) + 1))&& enemy1.status == 1)
            {
                enemy1.status = 0;
                tasks = tasks -1;
            }
            else if ((position0 == ((int)(button1.position[0] * 10)) && position1 == ((int)(button1.position[1]*10) + 1)) && spawn==0)
            {
                spawn = 1;
                powerup1.status = 1;
                powerup2.status = 1;
            }
            else if(((position0 == ((int)(powerup1.position[0]*10)) && position1 == ((int)(powerup1.position[1]*10) + 1)) && powerup1.status == 1)&& spawn == 1 )
            {
                Player1.health += 5;
                powerup1.status = 0;
                if(powerup2.status == 0)
                    tasks = tasks -1;
            }
            else if(((position0 == (int)(powerup2.position[0]*10) && position1 == ((int)(powerup2.position[1]*10) + 1) && powerup2.status==1))&& spawn == 1)
            {
                Player1.health += 5;
                powerup2.status = 0;
                if(powerup1.status == 0)
                    tasks = tasks -1;
            }
            else if(((position0 == (int)(obstacle1.position[0]*10) && position1 == ((int)(obstacle1.position[1]*10) + 1)) or (position0 == (int)(obstacle2.position[0]*10) && position1 == (int(obstacle2.position[1]*10) + 1)))&& spawn == 1)
            {
                Player1.health -= 2;
            }
        }
    }
   if(toggle) {
    if(!strcmp(light,"on"))
    {   
       strcpy(light,"off");
       ltime = time1;
    }
    else
    {
       strcpy(light,"on");
       ltime = 0;
    }   
   } 
}

void tick_elements() {
    Player1.tick();
    camera_rotation_angle += 1;
}

void initFTgl(GLFWwindow *window, int width, int height)
{
    FT_Library ft;
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return ;
    }

    FT_Face face;
    if (FT_New_Face(ft, "../src/arial.ttf", 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;  
        return ;
    } 
    FT_Set_Pixel_Sizes(face, 0, 48);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction  
    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
            texture, 
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        Characters.insert(std::pair<char, Character>(c, character));
    }
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
    glDisable(GL_CULL_FACE);
    glDisable(GL_BLEND);  
    program1ID = LoadShaders( "../src/shaders/text.vs","../src/shaders/text.fs");
    glGenVertexArrays(1, &VAO1);
    glGenBuffers(1, &VBO1);
    glBindVertexArray(VAO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0); 
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    Player1 = Player(-3.3, -2.6, COLOR_RED);
    std::vector<float>v;
    std::vector<float>v1;
    for(int i =0;i<10;i++)
    {
        int a = i*6;
        v.push_back((-27 + a)/10.0);
        v1.push_back((-26 + a)/10.0);
    }
    v1.erase(std::remove(v1.begin(), v1.end(), v1[0]), v1.end());
    int index = rand()%v.size();
    int index1 = rand()%v1.size();
    enemy1 = enemy(v[index],v1[index1],COLOR_BLACK);
    v.erase(std::remove(v.begin(), v.end(), v[index]), v.end());
    int index2 = rand()%v.size();
    int index3 = rand()%v1.size();
    button1 = button(v[index2],v1[index3] - 0.1,COLOR_BLACK,1);

    v1.erase(std::remove(v1.begin(), v1.end(), v1[index3]), v1.end());
    int index4 = rand()%v.size();
    int index5 = rand()%v1.size();
    powerup1 = powerup(v[index4],v1[index5] - 0.1,COLOR_BLACK);
    v.erase(std::remove(v.begin(), v.end(), v[index4]), v.end());
    int index6 = rand()%v.size();
    int index7 = rand()%v1.size();
    powerup2 = powerup(v[index6],v1[index7] - 0.1,COLOR_BLACK);

    v1.erase(std::remove(v1.begin(), v1.end(), v1[index7]), v1.end());
    int index8 = rand()%v.size();
    int index9 = rand()%v1.size();
    obstacle1 = obstacle(v[index8],v1[index9] - 0.1,COLOR_BLACK);
    v.erase(std::remove(v.begin(), v.end(), v[index8]), v.end());
    int index10 = rand()%v.size();
    int index11 = rand()%v1.size();
    obstacle2 = obstacle(v[index10],v1[index11] - 0.1,COLOR_BLACK);
    v1.erase(std::remove(v1.begin(), v1.end(), v1[index11]), v1.end());
    int index12 = rand()%v.size();
    int index13 = rand()%v1.size();
    button2 = button(v[index12],v1[index13] - 0.1,COLOR_BLACK,2);
    


    maze1 = maze(-3,-3,COLOR_RED,cell1,light,cellx,celly);
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("../src/shaders/shader.vert", "../src/shaders/shader.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);
    initFTgl (window,width,height);
    /* Draw in loop */
    int ctr=0;
    while (!glfwWindowShouldClose(window)) {
        // Process timers
        // draw();
        if (t10.processTick()) {

            time1 = 300 - glfwGetTime();
            if( tasks == 0)
            {
                cell1[9][9].east = 0;
            }
            if(ltime!=0 && ((ltime - time1)%15==0) && ltime!=time1)
            {
                Player1.health += 1;
            }
            if(time1 == 0)
            {
                gend = 1;
            }
            // 60 fps
            // OpenGL Draw commands
            //tick_input(window);
            if(!strcmp(light,"off"))
            {
                int position0 = (int)(Player1.position[0]*10.2);
                int position1 = (int)(Player1.position[1]*10.2);
                cellx = (int)((position0 + 27)/6);
                celly = (int)((position1 +26)/6); 
            }
            ctr++;
            
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            // tick_elements();
            tick_input(window);
            // if(gend == 1)
                // break;
            if(ctr == 10)
            {
                ctr = 0;
                int position0 = (int)(Player1.position[0]*10.2);
                int position1 = (int)(Player1.position[1]*10.2);
                cellx = (int)((position0 + 27)/6);
                celly = (int)((position1 +26)/6); 
                 BellmanFord();
            }

        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }
    // draw();
    // sleep(3);    
    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
