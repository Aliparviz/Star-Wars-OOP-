class Game
{
    private:
        bool game_running;

    public:
    void start_game(){game_running = true;}
    void end_game(){game_running = false;}
    bool getgamestate(){return game_running;}

};