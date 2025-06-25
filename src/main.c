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

	int TailSize = 0;

	Vector2 PlayerDir = {1, 0};
	Vector2 PlayerPos[256];
	PlayerPos[0].x = 4;
	PlayerPos[0].y = 10;

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
			//Apple Collision
			if(IsVector2Equal(PlayerPos[0], ApplePos)) {
				ApplePos.x = GetRandomValue(0, 15);
				ApplePos.y = GetRandomValue(0, 15);
			
				if(TailSize < 256) TailSize++;
			}
			else {
				for(int i = 0; i < 256; i++) {
					if(IsVector2Equal(PlayerPos[i], ApplePos)) {
						ApplePos.x = GetRandomValue(0, 15);
						ApplePos.y = GetRandomValue(0, 15);
					}
				}
			}

			for(int i = TailSize; i != 0; i--) {
				PlayerPos[i].x = PlayerPos[i - 1].x;
				PlayerPos[i].y = PlayerPos[i - 1].y;
			}
			PlayerPos[0] = SumVector2(PlayerPos[0], PlayerDir);
		
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
		if(PlayerPos[0].x == 16) PlayerPos[0].x = 0;
		if(PlayerPos[0].x == -1) PlayerPos[0].x = 15;
		if(PlayerPos[0].y == 16) PlayerPos[0].y = 0;
		if(PlayerPos[0].y == -1) PlayerPos[0].y = 15;

		//Difficulty Thingie
		if(MouseWheelDelta >= 0.0f) Difficulty += 0.5;
		if(MouseWheelDelta <= 0.0f && Difficulty > 1.0f) Difficulty -= 0.5;

		//GameScreen Drawing
		BeginTextureMode(GameScreen);
		ClearBackground(BROWN);
		
		DrawPixelV(ApplePos, RED);
		
		for(int i = 1; i <= TailSize; i++) {
			DrawPixelV(PlayerPos[i], GREEN);
		}

		DrawPixelV(PlayerPos[0], BLUE);

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
