#ifndef PLAYER_H
#define PLAYER_H
#include <stdio.h>
#include <vector>
#include "envItem.h"
#include "raylib.h"
#include "raymath.h"

#define G 400
#define PLAYER_HOR_SPD 200.0f
#define PLAYER_JMP_SPD 350.0f

class Player
{
    public:
        Vector2 position;
        float speed;
        bool canJump;

        // player constructor
        Player(Vector2 position, float speed, bool canJump);


    // update player methods
    private:
        void MoveLeft(std::vector<EnvItem> envItems, float delta);
        void MoveRight(std::vector<EnvItem> envItems, float delta);
        void MoveUp(std::vector<EnvItem> envItems, float delta);
        void MoveDown(std::vector<EnvItem> envItems, float delta);
    public:
        void UpdatePlayer(std::vector<EnvItem> envItems, float delta); 
        void FollowPlayer(Camera2D *camera, std::vector<EnvItem> envItems, float delta, int screenWidth, int screenHeight);
        char* CoordPlayer();
};




#endif