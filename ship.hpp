#include "Cartridge.hpp"

class ship
{
    private:
        int x,y;
        string type;
        bool is_moving;
        vector<Cartridge>cartridges;
    public:
    ship(int _x,int _y,string _type)
    {
        type = _type;
        x=_x;
        y=_y;
    }
    int getx(){return x;}
    int gety(){return y;}
    bool getmoving(){return is_moving;}
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
    void move_others_cartridges()
    {
        for(int i=0;i<cartridges.size();i++)
        {
            cartridges[i].move_enemy();
          /*  if(cartridges[i].getend_y()>=1000)
            {
                cartridges.erase(cartridges.begin()+ i);           
            }*/
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
    void add_cartridge(int x_s, int y_s, int x_e, int y_e)
    {
        cartridges.push_back(Cartridge(x_s,y_s,x_e,y_e));
    }
    vector<Cartridge> get_cartridges(){return cartridges;}
};