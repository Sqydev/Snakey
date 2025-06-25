#include <raylib.h>

int main() {
	InitWindow(640, 640, "Snakey");
	SetTargetFPS(60);

	while(!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(WHITE);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
