#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include"level.h"
#include"menu.h"

class GameManager {

    private:

        Graphics& graphics;
    
        EventHandler& events;
    
        vector<GameComponent*> components;
    
        GameComponent* root;
   
    protected:

    public:
    
        GameManager(EventHandler&);
    
        ~GameManager();
    
        void addAsRoot(GameComponent* c) { components.push_back(c); root = c; }
    
        void add(GameComponent* c) { components.push_back(c); }
    
        void launchGame();
};

#endif