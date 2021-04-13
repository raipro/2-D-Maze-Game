#include "maze.h"
#include "main.h"
#include "cell.h"

// cell cell1[10][10];
maze::maze(float x, float y, color_t color, cell cell1[10][10],char light[4],int cellx,int celly) {
    srand(time(0));
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    GLfloat vertex_buffer_data[4810] = {
    };
    int x1 = rand()%10;
    int y1 = rand()%10;
    cell1[x1][y1].visited = 1;
    int flag = 0;
    while(flag == 0)
    {   flag = 1;
        cell1[x1][y1].visited = 1;
        for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
        {
            if(!cell1[i][j].visited)
                flag = 0;
        }
        if(flag==1)
            break;
            std::vector<int>v;
            v.insert(v.end(), { 0,1,2,3 });
            if(x1 == 9)
            {
                v.erase(std::remove(v.begin(), v.end(), 3), v.end());
            }
            if(y1==9)
            {
                v.erase(std::remove(v.begin(), v.end(), 0), v.end());
            }
            if(x1==0)
            {
                 v.erase(std::remove(v.begin(), v.end(), 2), v.end());
            }
            if(y1==0)
            {
               v.erase(std::remove(v.begin(), v.end(), 1), v.end());
            }
            int a = v[rand()%(v.size())];
            if(a==3)
                {
                    if( !cell1[x1+1][y1].visited )
                        {
                            cell1[x1][y1].east = 0;
                            x1 = x1 + 1;
                            cell1[x1][y1].west = 0;
                        }
                        else
                        {
                            x1 = x1 + 1;
                        }
                }
            else if(a==2)
                {
                    if(!cell1[x1-1][y1].visited)
                    {
                        cell1[x1][y1].west = 0;
                        x1 = x1 - 1;
                        cell1[x1][y1].east = 0;
                    }
                    else
                    {
                        x1 = x1 -1;
                    }
                }
            else if(a==1)
                {
                    if(!cell1[x1][y1 - 1].visited)
                    {
                        cell1[x1][y1].south = 0;
                        y1 = y1 -1;
                        cell1[x1][y1].north = 0;
                    }
                    else
                    {
                        y1 = y1 - 1;
                    }
                }
            else
                {
                  if(!cell1[x1][y1 + 1].visited)
                    {
                        cell1[x1][y1].north = 0;
                        y1 = y1 + 1;
                        cell1[x1][y1].south = 0;
                    }
                    else
                    {
                        y1 = y1 + 1;
                    }   
                }            
    }
    int j1 = 0;
    cell1[0][0].west = 0;
    // cell1[9][9].east = 0;
    for(int i=0;i<10;i++)
    for(int j=0;j<10;j++)
    {
        if (cell1[i][j].north == 1)
            {
                vertex_buffer_data[j1] = 0.6*i ;
                vertex_buffer_data[j1 + 1] = 0.6*j +  0.6;
                vertex_buffer_data[j1 + 2] = 0.6f;

                vertex_buffer_data[j1 + 3] = 0.6*i +  0.6;
                vertex_buffer_data[j1 + 4] = 0.6*j +  0.6;
                vertex_buffer_data[j1 + 5] = 0.0f;
                j1 +=6;
            }
        if (cell1[i][j].west == 1)
            {
                vertex_buffer_data[j1] = 0.6*i ;
                vertex_buffer_data[j1 + 1] = 0.6*j ;
                vertex_buffer_data[j1 + 2] = 0.0f;

                vertex_buffer_data[j1+3] = 0.6*i ;
                vertex_buffer_data[j1 + 4] = 0.6*j +  0.6;
                vertex_buffer_data[j1 + 5] = 0.0f;
                j1 += 6;
            }
        if (cell1[i][j].south == 1)
            {
                vertex_buffer_data[j1] = 0.6*i ;
                vertex_buffer_data[j1 + 1] = 0.6*j ;
                vertex_buffer_data[j1 + 2] = 0.0f;

                vertex_buffer_data[j1 + 3] = 0.6*i +  0.6;
                vertex_buffer_data[j1 + 4] = 0.6*j;
                vertex_buffer_data[j1 + 5] = 0.0f;

                j1+=6;
            }
        if (cell1[i][j].east == 1 && (i*j)!=81) 
            {
                vertex_buffer_data[j1] = 0.6*i + 0.6;
                vertex_buffer_data[j1 + 1] = 0.6*j ;
                vertex_buffer_data[j1 + 2] = 0.0f;

                vertex_buffer_data[j1 + 3] = 0.6*i +  0.6;
                vertex_buffer_data[j1 + 4] = 0.6*j +  0.6;
                vertex_buffer_data[j1 + 5] = 0.0f;

                j1+=6;
            }

    }
    


    //GLfloat radius = 0.2f
    
    this->object = create3DObject(GL_LINES, 400*2, vertex_buffer_data, color, GL_FILL);
  
    
}

void maze::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::v3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void maze::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void maze::tick() {
    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

