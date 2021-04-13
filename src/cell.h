#ifndef CELL_H
#define CELL_H
class cell{
public:    
    int north = 1;
    int south = 1;
    int west = 1;
    int east = 1;
    int visited = 0;
    cell() {};
private:
    VAO *object;        
};

#endif