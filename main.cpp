#include <iostream>
#include <raylib.h>

using namespace std;

const int screen_width = 1280;
const int screen_height = 800;

class Ball
{
public:
    float x, y;
    int dx, dy;
    int radius;

    Ball(float x, float y, int dx, int dy, int radius)
    {
        this->x = x;
        this->y = y;
        this->dx = dx;
        this->dy = dy;
        this->radius = radius;
    }

    void Draw()
    {
        DrawCircle(x, y, radius, WHITE);
    }

    void Update()
    {
        x += dx;
        y += dy;
        if (x + this->radius >= screen_width || x + this->radius <= 0)
        {
            dx *= -1;
        }
        if (y + this->radius >= screen_height || y + this->radius <= 0)
        {
            dy *= -1;
        }
    }
};

class Paddle
{
public:
    float x, y;
    float width, height;
    int speed;

    Paddle(float x, float y, float width, float height, int speed)
    {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        this->speed = speed;
    }

    void Draw()
    {
        DrawRectangle(x, y, width, height, WHITE);
    }

    void CheckBounds()
    {
        if (y <= 0)
        {
            y = 0;
        }
        if (y + this->height >= screen_height)
        {
            y = screen_height - this->height;
        }
    }

    void Update()
    {
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W) || IsKeyDown(KEY_K))
        {
            y -= speed;
        }
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S) || IsKeyDown(KEY_J))
        {
            y += speed;
        }

        CheckBounds();
    }
};

class CpuPaddle : public Paddle
{
public:
    CpuPaddle(float x, float y, float width, float height, int speed) : Paddle(x, y, width, height, speed){};
    void Update(int bally)
    {
        if (y + height / 2 < bally)
        {
            y += speed;
        }
        if (y + height / 2 > bally)
        {
            y -= speed;
        }

        CheckBounds();
    }
};

int main()
{
    Ball ball(screen_width / 2, screen_height / 2, 10, 10, 25);
    Paddle player(screen_width - 30, screen_height / 2 - 60, 25, 120, 10);
    CpuPaddle computer(10, screen_height / 2 - 60, 25, 120, 10);
    InitWindow(screen_width, screen_height, "Pong!");
    SetTargetFPS(60);
    int player_score = 0;
    int cpu_score = 0;
    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ball.Update();
        player.Update();
        computer.Update(ball.y);
        // Drawing
        ClearBackground(BLACK);
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
        ball.Draw();
        player.Draw();
        computer.Draw();
        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height}))
        {
            ball.dx *= -1;
        }
        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{computer.x, computer.y, computer.width, computer.height}))
        {
            ball.dx *= -1;
        }
        if (ball.x + ball.radius <= 0)
        {
            player_score++;
            ball.x = screen_width / 2;
            ball.y = screen_height / 2;
        }
        if (ball.x + ball.radius >= screen_width)
        {
            cpu_score++;
            ball.x = screen_width / 2;
            ball.y = screen_height / 2;
        }
        DrawText(TextFormat("%i", cpu_score), 20, 60, 80, WHITE);
        DrawText(TextFormat("%i", player_score), screen_width - 40, 60, 80, WHITE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}