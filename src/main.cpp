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
		{{ 0, 0, 3000, 400 }, LIGHTGRAY, 0},
        {{ 0, 400, 3000, 200 }, BLUE, 1, 1},  // base level
        {{ 300, 200, 400, 10 }, ORANGE, 1},
		{{ 150, 100, 50, 10 }, PURPLE, 1},
		{{ 0, 0, 50, 10 }, PURPLE, 1},
        {{ 250, 300, 100, 10 }, GREEN, 1},
        {{ 650, 300, 100, 10 }, YELLOW, 1}
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

		char* test = player.CoordPlayer();
		DrawText(test, 20, 20, 10, BLACK);
		// printf("%s\n", test); // seg fault
		EndDrawing();
	}

	CloseWindow();
	
	return 0;

}
