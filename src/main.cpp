#include <vector>
#include "envItem.h"
#include "player.h"
#include "raylib.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

int main ()
{
	const int screenWidth = 800;
	const int screenHeight = 450;
	InitWindow(screenWidth, screenHeight, "wiz und liz");

	Player player((Vector2){400, 200}, 0, false);
	std::vector<EnvItem> envItems = 
	{
		{{ 0, 0, 3000, 400 }, 0, LIGHTGRAY},
        {{ 0, 400, 3000, 200 }, 1, BLUE },
        {{ 300, 200, 400, 10 }, 1, ORANGE },
        {{ 250, 300, 100, 10 }, 1, GREEN },
        {{ 650, 300, 100, 10 }, 1, YELLOW },
		{{ 650, 200, 100, 10 }, 1, YELLOW },
		{{ 650, 100, 100, 10 }, 1, YELLOW },
		{{ 650, 0, 100, 10 }, 1, YELLOW }
	};

	Camera2D camera = 
	{
		(Vector2){screenWidth/2.0f, screenHeight/2.0f}, // offset
		player.position,                                // target
		0.0f,                                           // rotation
		1.0f                                            // zoom
	};

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		float deltaTime = GetFrameTime();

		player.UpdatePlayer(envItems, deltaTime);

		player.FollowPlayer(&camera, envItems, deltaTime, screenWidth, screenHeight);

		BeginDrawing();
		ClearBackground(LIGHTGRAY);

		BeginMode2D(camera);
			for (EnvItem ei: envItems) DrawRectangleRec(ei.rect, ei.color);
			Rectangle playerRect = {player.position.x - 20, player.position.y - 40, 40.0f, 40.0f};
			DrawRectangleRec(playerRect, RED);
		EndMode2D();

		EndDrawing();
	}

	CloseWindow();
	
	return 0;

}
