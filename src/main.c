#include <raylib.h>

bool IsVector2Equal(Vector2 v1, Vector2 v2) {
	return v1.x == v2.x && v1.y == v2.y;
}

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

	int Points;

	Vector2 ApplePos;
	ApplePos.x = GetRandomValue(0, 15);
	ApplePos.y = GetRandomValue(0, 15);

	float elapsedTime = 0.0f;

	while(!WindowShouldClose()) {
		//Calculations
		float dt = GetFrameTime();
		float MouseWheelDelta = GetMouseWheelMoveV().y;
		elapsedTime += dt;

		//Calcs to make only one time a sec
		if(elapsedTime >= 1.0f / Difficulty) {
			PlayerPos = SumVector2(PlayerPos, PlayerDir);
			
			elapsedTime -= 1.0f / Difficulty;
		}

		//Movement
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

		//Out of bounce coll check and action
		if(PlayerPos.x == 16) PlayerPos.x = 0;
		if(PlayerPos.x == -1) PlayerPos.x = 15;
		if(PlayerPos.y == 16) PlayerPos.y = 0;
		if(PlayerPos.y == -1) PlayerPos.y = 15;

		//Apple Collision
		if(IsVector2Equal(PlayerPos, ApplePos)) {
			ApplePos.x = GetRandomValue(0, 15);
			ApplePos.y = GetRandomValue(0, 15);

			Points++;
		}

		//Difficulty Thingie
		if(MouseWheelDelta >= 0.0f) Difficulty += 0.5;
		if(MouseWheelDelta <= 0.0f && Difficulty > 1.0f) Difficulty -= 0.5;

		//GameScreen Drawing
		BeginTextureMode(GameScreen);
		ClearBackground(BROWN);
		
		DrawPixelV(PlayerPos, GREEN);
		
		DrawPixelV(ApplePos, RED);

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
