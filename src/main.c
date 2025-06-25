#include <raylib.h>

Vector2 SumVector2(Vector2 v1, Vector2 v2) {
	Vector2 RETURNER = {v1.x + v2.x, v1.y + v2.y};
	return RETURNER;
}

int main() {
	InitWindow(640, 640, "Snakey");
	SetTargetFPS(60);

	//Make game screen
	RenderTexture2D GameScreen = LoadRenderTexture(16, 16);
	//Make is so It's not blured
	SetTextureFilter(GameScreen.texture, TEXTURE_FILTER_POINT);

	float Difficulty = 1.0f;

	Vector2 PlayerDir = {1, 0};
	Vector2 PlayerPos = {4, 10};

	float elapsedTime = 0.0f;

	while(!WindowShouldClose()) {
		//Calculations
		float dt = GetFrameTime();
		elapsedTime += dt;

		//Calcs to make only one time a sec
		if(elapsedTime >= 1.0f / Difficulty) {
			PlayerPos = SumVector2(PlayerPos, PlayerDir);
			
			elapsedTime -= 1.0f / Difficulty;
		}

		if(IsKeyDown(KEY_W)) {
			PlayerDir.x = 0;
			PlayerDir.y = -1;
		}
		if(IsKeyDown(KEY_S)) {
			PlayerDir.x = 0;
			PlayerDir.y = 1;
		}
		if(IsKeyDown(KEY_A)) {
			PlayerDir.x = -1;
			PlayerDir.y = 0;
		}
		if(IsKeyDown(KEY_D)) {
			PlayerDir.x = 1;
			PlayerDir.y = 0;
		}

		//GameScreen Drawing
		BeginTextureMode(GameScreen);
		ClearBackground(BROWN);
		
		DrawPixelV(PlayerPos, RED);

		EndTextureMode();


		//GameScreen to Window Drawing
		BeginDrawing();
		ClearBackground(WHITE);

		DrawTexturePro(
    		GameScreen.texture,
    		(Rectangle){ 0, 0, 16, -16 },
			(Rectangle){ 0, 0, 640, 640 },
			(Vector2){ 0, 0 },
    		0.0f,
    		WHITE
		);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
