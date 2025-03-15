#include "raylib.h"

const char *GameName = "Axe Game";
static int WindowWidth = 800;
static int WindowHeight = 450;
static int FPS = 60;

//circle
int circleSpeed = 4;
int circleX = WindowWidth / 4;
int circleY = WindowHeight / 2;
int circleRadius = 25;
//circle edges
int lCircleX = circleX - circleRadius;
int rCircleX = circleX + circleRadius;
int uCircleY = circleY - circleRadius;
int bCircleY = circleY + circleRadius;

//axe
int axeX = WindowWidth / 2;
int axeY = 0;
int axeWidth = 50;
int axeHeight = 50;
int axeDirection = 10;
//axe edges
int lAxeX = axeX;
int rAxeX = axeX + axeWidth;
int uAxeY = axeY;
int bAxeY = axeX + axeHeight;

void MoveCircle()
{
	if (IsKeyDown(KEY_D) && circleX < (WindowWidth - circleRadius))
	{
		circleX += 1 * circleSpeed;
	}
	if (IsKeyDown(KEY_A) && circleX > circleRadius)
	{
		circleX -= 1 * circleSpeed;
	}
	if (IsKeyDown(KEY_S) && circleY < (WindowHeight - circleRadius))
	{
		circleY += 1 * circleSpeed;
	}
	if (IsKeyDown(KEY_W) && circleY > circleRadius)
	{
		circleY -= 1 * circleSpeed;
	}

	lCircleX = circleX - circleRadius;
	rCircleX = circleX + circleRadius;
	uCircleY = circleY - circleRadius;
	bCircleY = circleY + circleRadius;
}

void MoveAxe()
{
	bool falsee = false;
	bool truee = true;

	if (truee)
	{
		
	}















	axeY += axeDirection;
	if (axeY > (WindowHeight - axeHeight) || axeY < 0)
	{
		axeDirection = -axeDirection;
	}

	lAxeX = axeX;
	rAxeX = axeX + axeWidth;
	uAxeY = axeY;
	bAxeY = axeX + axeHeight;
}

bool CollideWithAxe()
{
	if (bAxeY >= uCircleY && 
		uAxeY <= bCircleY && 
		lAxeX <= rCircleX && 
		rAxeX >= lCircleX)
	{
		return true;
	}

	return false;
}

void RunGameLogic()
{
	MoveAxe();
	MoveCircle();

	DrawCircle(circleX, circleY, circleRadius, GREEN);
	DrawRectangle(axeX, axeY, axeWidth, axeHeight, RED);

	if (CollideWithAxe())
	{
		DrawText("Game Over!", 200, 190, 75, RED);
		return;
	}
}

int main()
{
	InitWindow(WindowWidth, WindowHeight, GameName);
	SetTargetFPS(FPS);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);

		RunGameLogic();

		EndDrawing();
	}
}