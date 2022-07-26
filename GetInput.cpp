//in the name of god
#include<iostream>
#include<string>
#include<vector>
#include<math.h>
#include "rsdl.hpp"
#include "game.hpp"
//#include "ship.hpp"
#include "Cartridge.hpp"
using namespace std;

class ship
{
    private:
        int x,y;
        string type;
        bool is_end_of_path;
        bool is_alive;
        vector<Cartridge>cartridges;
    public:
    ship(int _x,int _y,string _type)
    {
        type = _type;
        x=_x;
        y=_y;
        is_end_of_path = false;
        is_alive = true;
    }
    void change_alive()
    {
        is_alive = false;
    }
    int getx(){return x;}
    int gety(){return y;}
    bool getalive(){return is_alive;}
    string gettype(){return type;}
    void move_my_cartridges()
    {
        for(int i=0;i<cartridges.size();i++)
        {
            cartridges[i].move();
            if(cartridges[i].getend_y()<=-45)
            {
                cartridges.erase(cartridges.begin()+ i);
            }
        }
    }
    void move_that_cartridge()
    {
        for(int i=0;i<cartridges.size();i++)
        {
            cartridges[i].move_enemy();
        }
    }
    void move_my_ship(char key)
    {
        switch(key)
        {
            case 'd':
            x+=10;
            if(x>=500)
            {
                x=500;
            }
            break;

            case 'w':
            y-=10;
            if(y<=0)
            {
                y=0;
            }
            break;
            
            case 'a':
            x-=10;
            if(x<=0)
            {
                x=0;
            }
            break;

            case 's':
            y+=10;
            if(y>=499)
            {
                y=499;
            }
            break;
        }
        
    }
    void enemyes_move()
    {
        if(is_end_of_path == false)
        {
            x+=10;
            if(x>=690)
            {
                is_end_of_path = true;
            }
        }
        else if(is_end_of_path==true)
        {
            x-=10;
            if(x<=0)
            {
                is_end_of_path = false;
            }
        }

    }
    void add_cartridge(int x_s, int y_s, int x_e, int y_e)
    {
        cartridges.push_back(Cartridge(x_s,y_s,x_e,y_e));
    }
    vector<Cartridge> get_cartridges(){return cartridges;}
};

vector<vector<char>> get_map_inputs()
{
    int row,col;

    cin>>row>>col;

    vector<vector<char>>map(row);
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            char temp;
            cin>>temp;
            map[i].push_back(temp);
        }
    }

    return map;
}
vector<ship> find_ships(vector<vector<char>>map)
{
    vector<ship>ships;
    for(int i=0;i<map.size();i++)
    {
        for(int j=0; j<map[i].size();j++)
        {
            if(map[i][j]=='E')
            {
                ships.push_back(ship((i+1)*20,(j+1)*20,"enemy"));
            }
            else if(map[i][j]=='M')
            {
                ships.push_back(ship((i+1)*20,(j+1)*20,"movement_enemy"));
            }
            else if(map[i][j] == 'S')
            {
                ships.push_back(ship((i+1)*20,(j+1)*20,"hostage"));
            }
        }
    }
    ships.push_back(ship((rand()%690)+10,489,"my_ship"));
    return ships;
}
void check_how_am_i(vector<ship>ships,Game& game)
{
    for(int i=0;i<ships.size();i++)
    {
        if(ships[i].gettype()=="my_ship")
        {
            if(ships[i].getalive()==false)
            {
                game.end_game();
            }
        }
    }
}
void draw_ships(vector<ship>ships,Window& window)
{
    for(int i=0;i<ships.size();i++)
    {
        if(ships[i].gettype() == "enemy" || ships[i].gettype()=="movement_enemy")
        {
            window.fill_circle(Point(ships[i].getx(),ships[i].gety()),10,GREEN);
        }
        else if(ships[i].gettype() == "hostage")
        {
            window.fill_circle(Point(ships[i].getx(),ships[i].gety()),10,RED);           
        }
        else if(ships[i].gettype() == "my_ship")
        {
            window.fill_circle(Point(ships[i].getx(),ships[i].gety()),10,WHITE);
        }
    }
    
}
void shoot(ship& attacker,vector<ship>&ships,Window& window)
{
    attacker.add_cartridge(attacker.getx(),attacker.gety(),attacker.getx(),attacker.gety()-25);
}
void get_command(char key,vector<ship>&ships,Window& window)
{
    for(int i=0;i<ships.size();i++)
    {
        if(ships[i].gettype()=="my_ship")
        {
            if(key == 'w' ||key == 'a'||
            key == 's'||key == 'd')
            {
                ships[i].move_my_ship(key);
            }
            else if(key == ' ')
            {
               shoot(ships[i],ships,window);
            }
        }
    }
}
void update(Game& game,vector<ship>&ships,Window& window)
{
    if(window.has_pending_event())
    {
        Event e = window.poll_for_event();
        switch(e.get_type())
        {
            case Event::EventType::QUIT:
            game.end_game();
            break;

            case Event ::EventType::KEY_PRESS:
            get_command(e.get_pressed_key(),ships,window);
            break;

           
        }   
    }
}
ship find_my_self(vector<ship> ships)
{
    for(int i=0;i<ships.size();i++)
    {
        if(ships[i].gettype() == "my_ship")
        {
            return ships[i];
        }
    }
    return ships[0];
}
void add_cartridges(vector<ship>& ships)
{
    for(int i=0;i<ships.size();i++)
    {
        if(ships[i].gettype() != "my_ship")
        {
            ships[i].add_cartridge(ships[i].getx(),ships[i].gety(),ships[i].getx(),ships[i].gety()+25);

        }
    }
}
void draw_cartridges(vector<ship>& ships,Window& window)
{
   for(int j=0;j<ships.size();j++)
   {
       if(ships[j].gettype() =="my_ship")
       {
           for(int i=0;i<ships[j].get_cartridges().size();i++)
           {
               window.draw_line(Point(ships[j].get_cartridges()[i].getstart_x(),ships[j].get_cartridges()[i].getstart_y()),
               Point(ships[j].get_cartridges()[i].getend_x(),ships[j].get_cartridges()[i].getend_y()),GREEN);
               
           }
       }
       else
       {
           for(int i=0;i<ships[j].get_cartridges().size();i++)
           {
                window.draw_line(Point(ships[j].get_cartridges()[i].getstart_x(),ships[j].get_cartridges()[i].getstart_y()),
                Point(ships[j].get_cartridges()[i].getend_x(),ships[j].get_cartridges()[i].getend_y()),WHITE);
           }
       }
   }
}
void move_cartridges(vector<ship>& ships)
{
    for(int i=0;i<ships.size();i++)
    {
        if(ships[i].gettype() == "my_ship")
        {
            ships[i].move_my_cartridges();
        }
        else
        {
            ships[i].move_that_cartridge();
        }
    }
}
void check_being_shot(vector<ship>& ships,Game& game)
{
    ship me = find_my_self(ships);
    for(int i=0;i<ships.size();i++)
    {
        if(ships[i].gettype() != "my_ship")
        {
            for(int j=0;j<ships[i].get_cartridges().size();j++)
            {
                if(sqrt(pow((ships[i].get_cartridges()[j].getstart_x() - me.getx()) , 2 ) + pow((ships[i].get_cartridges()[j].getstart_y() - me.gety()), 2 )) < 10)
                {
                    game.end_game();
                }
            }
        }
    }    
}
void check_end_of_game(vector<ship>& ships,Game& game)
{
    int enemy_counter=0;
    for(int i=0;i<ships.size();i++)
    {
        if(ships[i].gettype() == "movement_enemy" ||  ships[i].gettype() == "enemy")
        {
            enemy_counter++;
        }
    }
    if(enemy_counter == 0)
    {
        game.end_game();
    }
}
void check_shooting(vector<ship>& ships,Game& game)
{
    ship attacker = find_my_self(ships);
    for(int i=0;i<ships.size();i++)
    {
        if(ships[i].gettype() == "my_ship")
        {
            continue;
        }
        else
        {
            for(int j=0;j<attacker.get_cartridges().size();j++)
            {
                if(sqrt(pow((attacker.get_cartridges()[j].getstart_y())-(ships[i].gety()),2) + pow((attacker.get_cartridges()[j].getstart_x())-(ships[i].getx()),2) )<10)
                {
                    if(ships[i].gettype() == "hostage")
                    {
                        game.end_game();
                    }
                    ships.erase(ships.begin() + i);
                    check_end_of_game(ships,game);
                    
                }
            }
        }
    }
}
void check_accident(vector<ship>& ships,Game& game)
{
    ship attacker = find_my_self(ships);
    for(int i=0;i<ships.size();i++)
    {
        if(sqrt(pow(attacker.getx()-ships[i].getx(),2) + pow(attacker.gety()-ships[i].gety(),2))<20)
        {
            if(ships[i].gettype() == "my_ship")
            {
                continue;
            }
            for(int j=0;j<ships.size();j++)
            {
                if(ships[j].gettype() == "my_ship")
                {
                    ships[j].change_alive();
                    game.end_game();
                }
            }
            return;
        }
    }
    return;
}
void move_enemies(vector<ship>& ships)
{
    for(int i=0;i<ships.size();i++)
    {
        if(ships[i].gettype()=="movement_enemy")
        {
            ships[i].enemyes_move();
        }
    }
}
void manage_game( Game& game,vector<ship>& ships,Window& window)
{
    int counter_c = 0; 
    int counter_m = 0;
    while(game.getgamestate())
    {
        window.clear();
        check_how_am_i(ships,game);
        if(game.getgamestate())
        {
            update(game,ships,window);
            draw_ships(ships,window);
            if(counter_c % 350 == 0)
            {
                add_cartridges(ships);
            }
            if(counter_m % 20 == 0)
            {
                move_cartridges(ships);
            }
            move_enemies(ships);
            check_accident(ships,game);
            check_being_shot(ships,game);
            check_shooting(ships,game);
            draw_cartridges(ships,window);
            window.update_screen();



            delay(15);
            counter_c++;
            counter_m++;
        }
    }
}
int main()
{   
    int rounds_num;
    cin>>rounds_num;
    Game game;
    vector<vector<ship>>ships(rounds_num);
    for(int i=0;i<rounds_num;i++)
    { 
        game.start_game();
        ships[i]=find_ships(get_map_inputs());
        Window window(700,500,"Ali's game");
        manage_game(game,ships[i],window);
    }

    return 0;
}
