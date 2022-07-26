class Cartridge
{
    private:
        int start_x;
        int start_y;
        int end_x;
        int end_y;
    public:
    Cartridge(int x_s, int y_s,int x_e, int y_e) 
    {
        start_x = x_s;
        start_y = y_s;
        end_x = x_e;
        end_y = y_e;
    }
    void move()
    {
        start_y -= 7;
        end_y -= 7;
    }
    void move_enemy()
    {
        start_y += 10;
        end_y += 10;
    }
    void change_start()
    {
        start_y += 20;
    }
    void change_end()
    {
        end_y += 20;
    }
    int getstart_x(){return start_x;}
    int getstart_y(){return start_y;}
    int getend_x(){return end_x;}
    int getend_y(){return end_y;}
};