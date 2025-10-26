#include "player.h"

Player::Player(Vector2 position, float speed, bool canJump)
: position{position}, speed{speed}, canJump{canJump}
{
}


void Player::MoveLeft(std::vector<EnvItem> envItems, float delta)
{
    if (IsKeyDown(KEY_D)) this->position.x += PLAYER_HOR_SPD*delta;
}

void Player::MoveRight(std::vector<EnvItem> envItems, float delta)
{
    if (IsKeyDown(KEY_A)) this->position.x -= PLAYER_HOR_SPD*delta;
}

void Player::MoveUp(std::vector<EnvItem> envItems, float delta)
{
    if (IsKeyDown(KEY_W) && this->canJump)
    {
        this->speed = -PLAYER_JMP_SPD;
        this->canJump = false;
    }

    bool hitObsitcle = false;
    for (EnvItem ei: envItems)
    {
        if (ei.blocking && 
            ei.rect.x <= this->position.x &&
            ei.rect.x + ei.rect.width >= this->position.x &&
            ei.rect.y >= this->position.y &&
            ei.rect.y <= this->position.y + this->speed*delta)
            {
                hitObsitcle = true;
                this->speed = 0.0f;
                this->position.y = ei.rect.y;
                break;
            }
        else if (ei.blocking &&   // this isnt a very clean method but it works
            ei.rect.x <= this->position.x &&
            ei.rect.x + ei.rect.width >= this->position.x &&
            ei.rect.y + ei.rect.height <= this->position.y - 40 &&
            ei.rect.y + ei.rect.height >= this->position.y + this->speed*delta - 40)
            {
                hitObsitcle = false;
                this->speed = 0.0f;
                this->position.y = ei.rect.y + ei.rect.height + 41;
                break;
            }
            
    }
    
    if (!hitObsitcle)
    {
        this->position.y += this->speed*delta;
        this->speed += G*delta;
        this->canJump = false;
    }
    else this->canJump = true;

}

void Player::MoveDown(std::vector<EnvItem> envItems, float delta)
{

    bool hitObsitcle = false;
    for (EnvItem ei: envItems)
    {
        if (ei.blocking && 
            ei.rect.x <= this->position.x &&
            ei.rect.x + ei.rect.width >= this->position.x &&
            ei.rect.y >= this->position.y &&
            ei.rect.y <= this->position.y + this->speed*delta)
            {
                hitObsitcle = true;
                this->speed = 0.0f;
                this->position.y = ei.rect.y;
                break;
            }
    }
    
    if (!hitObsitcle)
    {
        this->position.y += this->speed*delta;
        this->speed += G*delta;
        this->canJump = false;
    }
    else this->canJump = true;


}

void Player::UpdatePlayer(std::vector<EnvItem> envItems, float delta)
{
    this->MoveLeft(envItems, delta);
    this->MoveRight(envItems, delta);
    this->MoveUp(envItems, delta);
}

void Player::FollowPlayer(Camera2D *camera, std::vector<EnvItem> envItems, float delta, int screenWidth, int screenHeight)
{
	static float minSpeed = 30;
	static float minEffectLength = 10;
	static float fractionSpeed = 0.8f;
	Vector2 diff = Vector2Subtract(this->position, camera->target);
	float length = Vector2Length(diff);
	if (length > minEffectLength)
	{
		float spd = fmaxf(fractionSpeed*length, minSpeed);
		camera->target = Vector2Add(camera->target, Vector2Scale(diff, spd*delta/length));
	}
}

char *Player::CoordPlayer()
{
    char str[20];
    sprintf(str,"(%d, %d)", (int) this->position.x, (int) this->position.y);
    DrawText(str, 20, 20, 10, BLACK);
    return str;
}
