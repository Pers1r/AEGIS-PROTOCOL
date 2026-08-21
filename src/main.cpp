#include <vector>
#include <entt/entt.hpp>
#include <iostream>
#include <fstream>

#include "raylib.h"
#include "Player.h"
#include "Components.h"
#include "ResourceManager.h"
#include "MapLoader.h"

#include "Chunk.h"
struct Registry {
    entt::registry registry;
    std::vector<Chunk> chunks;
};


void update(float dt, Camera2D* camera, Player* player, int width, int height) {
    if (IsKeyDown(KEY_W)) {player->position.y -= player->speed * dt;}
    if (IsKeyDown(KEY_A)) {player->position.x -= player->speed * dt;}
    if (IsKeyDown(KEY_S)) {player->position.y += player->speed * dt;}
    if (IsKeyDown(KEY_D)) {player->position.x += player->speed * dt;}



    camera->zoom += ((float)GetMouseWheelMove()*0.05f);

    if (camera->zoom > 3.0f) camera->zoom = 3.0f;
    else if (camera->zoom < 0.25f) camera->zoom = 0.25f;

    camera->offset = (Vector2){ width/2.0f, height/2.0f };
    camera->target = player->position;
}

void draw(float dt,Camera2D* camera, Player* player, Registry* reg, ResourceManager* rm) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    auto view = reg->registry.view<TransformComponent, SpriteComponent>();

	Vector2 mousePos = GetScreenToWorld2D(GetMousePosition(), *camera);

    BeginMode2D(*camera);

        for (auto [ent, tr, sp] : view.each()) {
            DrawTextureEx(rm->get(sp.textureID), tr.position, tr.rotation, 1.0f, sp.tint);
        	if (mousePos.x  > tr.position.x && mousePos.x < tr.position.x + CELL_SIZE &&
        		mousePos.y > tr.position.y && mousePos.y < tr.position.y + CELL_SIZE) {
        		DrawRectangleLines(tr.position.x, tr.position.y, CELL_SIZE, CELL_SIZE, RED);
        	}
        }

        for (auto & chunk : reg->chunks) {
        	// DrawCircle(chunk.x, chunk.y, 5, RED);
        	// DrawCircle(chunk.x+ CHUNK_SIZE*CELL_SIZE, chunk.y+ CHUNK_SIZE*CELL_SIZE, 5, YELLOW);
        	if (chunk.x < player->position.x && chunk.x + CHUNK_SIZE*CELL_SIZE > player->position.x
        		&& chunk.y < player->position.y && chunk.y + CHUNK_SIZE*CELL_SIZE > player->position.y) {
        		chunk.draw(true);
        	} else {
        		chunk.draw(false);
        	}


        }
		DrawTextureEx(rm->get(1), {0, 0}, 0, 1.0f, WHITE);
        // DrawCircle(200, 200, 40, BLACK);
        DrawCircle(player->position.x, player->position.y, 10, RED);

    EndMode2D();

	DrawFPS(10, 10);

    EndDrawing();
}




void spawn_chunks(Registry* reg) {
	int cap = 32*16*2;
    float start = 0;
    for (float x = start; x < cap; x+=32.0f*16.0f) {
        for (float y = start; y < cap; y+=32.0f*16.0f) {
            reg->chunks.emplace_back(x, y);
        }
    }
}



int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "AEGIS PROTOCOL");

    Player player = { 0 };
    player.position = (Vector2){ PLAYER_SPAWN_X, PLAYER_SPAWN_Y };
    player.speed = 100;

    Camera2D camera = { 0 };
    camera.target = player.position;
    camera.offset = (Vector2){ SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f };
    camera.zoom = 1.0f;

    auto* reg = new Registry();

    auto* rm = new ResourceManager();
    rm->Load("../assets/blocks/environment/arkycite-floor.png");
	rm->Load("../assets/blocks/distribution/conveyors/conveyor-0-0.png");

    MapLoader::Load("../assets/map.txt", reg->registry);

    spawn_chunks(reg);

    SetTargetFPS(144);
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        update(deltaTime, &camera, &player, SCREEN_WIDTH, SCREEN_HEIGHT);
        draw(deltaTime,&camera,  &player, reg, rm);
    }

    delete rm;
    delete reg;
    CloseWindow();

}

