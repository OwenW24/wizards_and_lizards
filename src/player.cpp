#include "player.h"

Player::Player(Vector2 position, float speed, bool canJump)
{
    this->position = position;
    this->speed = speed;
    this->canJump = canJump;
}

void Player::XMove(std::vector<EnvItem> envItems, float delta)
{
    if (IsKeyDown(KEY_A)) this->position.x -= PLAYER_HOR_SPD*delta;
    if (IsKeyDown(KEY_D)) this->position.x += PLAYER_HOR_SPD*delta;
}

void Player::YMove(std::vector<EnvItem> envItems, float delta)
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
    this->XMove(envItems, delta);
    this->YMove(envItems, delta);
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
