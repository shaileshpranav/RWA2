#include "../include/mouse/mouse.h"  
#include "../include/api/api.h"  
#include "../include/util/util.h"
#include "../include/node/node.h"
#include <string>
#include <algorithm>
#include <vector>
#include <stack>
#include <iostream>

namespace rwa2
{
void Mouse::display_walls() {
    for (int x = 0; x < m_maze_width; x += 1) {
        for (int y = 0; y < m_maze_height; y += 1) {
            if (m_maze.at(x).at(y).is_wall(direction::NORTH)) {
                //display this wall in the simulator
                API::setWall(x, y, 'n');
            }
                
            if (m_maze.at(x).at(y).is_wall(direction::EAST)) {
                //display this wall in the simulator
                API::setWall(x, y, 'e');
            }
                
            if (m_maze.at(x).at(y).is_wall(direction::SOUTH)) {
                //display this wall in the simulator
                API::setWall(x, y, 's');
            }
                
            if (m_maze.at(x).at(y).is_wall(direction::WEST)) {
                //display this wall in the simulator
                API::setWall(x, y, 'w');
            }
            //display the number of walls surrounding the current node
            API::setText(x, y, std::to_string(m_maze.at(x).at(y).compute_number_of_walls()));
        }
    }
}
void Mouse::move_forward()
{
    API::moveForward();
}
void Mouse::turn_left()
{
    API::turnLeft();
}
void Mouse::turn_right()
{
    API::turnRight();
}

std::vector <std::array<int,2>>v;
std::stack <std::array<int,2>>s;

bool Mouse::search_maze(std::array<int,2> n, std::array<int,2> g)
{
    int n_x = n[0];
    int n_y = n[1]; 
    if(n!=g)
    {
        if(s.empty())
        {
            s.push(n);
            std::cout<<"s.empty";
        }
    }
    else
    {
        return true;
    }

    if(std::find(v.begin(),v.end(),n)==v.end())
    {
        v.push_back(n);
        std::cout<<"findv";
    }
    
    if(!m_maze.at(n_x).at(n_y).is_wall(direction::NORTH))
    {
        s.push(n);
        n_y++;
        n[1]=n_y;
    }
    else if(!m_maze.at(n_x).at(n_y).is_wall(direction::EAST))
    {
        s.push(n);
        n_x++;
        n[0]=n_x;
    }
    else if(!m_maze.at(n_x).at(n_y).is_wall(direction::SOUTH))
    {
        s.push(n);
        n_y--;
        n[1]=n_y;
    }
    else if(!m_maze.at(n_x).at(n_y).is_wall(direction::WEST))
    {
        s.push(n);
        n_x--;
        n[0]=n_x;
    }
    else
    {
        if(!s.empty())
        {
            s.pop();
            std::cout<<"s.pop";
        }
        else
        {
            return false;
            std::cout<<"s. no pop";
        }
    }
    if(!s.empty())
    {
        search_maze(n,s.top());
        std::cout<<"Going in loop";
    }
    else
    {
        return false;
    }
}

int Mouse::ret_m_x(){
    return m_x;
}
int Mouse::ret_m_y(){
    return m_y;
}
int Mouse::ret_m_dir(){
    return m_direction;
}

} // namespace rwa2;

