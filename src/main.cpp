#include <vector>
#include <entt/entt.hpp>
#include <iostream>
#include <fstream>

#include "raylib.h"
#include "Player.h"
#include "Components.h"
#include "ResourceManager.h"

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

    BeginMode2D(*camera);
        for (auto [ent, tr, sp] : view.each()) {
            DrawTextureEx(rm->get(sp.textureID), tr.position, tr.rotation, 1.0f, sp.tint);
        }
        // for (auto & chunk : reg->chunks) {
        //     chunk.draw();
        // }
        // DrawCircle(200, 200, 40, BLACK);
        DrawCircle(player->position.x, player->position.y, 10, RED);
    EndMode2D();
    EndDrawing();
}




void spawn_chunks(Registry* reg) {
    float start = -3200.0;
    for (float x = start; x < start*-1; x+=32.0f*16.0f) {
        for (float y = start; y < start*-1; y+=32.0f*16.0f) {
            reg->chunks.emplace_back(x, y);
        }
    }
}

namespace MapLoader {
    void Load(const std::string& filepath, entt::registry& reg) {
        std::fstream file(filepath);

        if (!file.is_open()) {
            std::cerr << "Error: Could not open the file!" << '\n';
        }

        std::string line;
        float y = 0.0f;
        while (std::getline(file, line)) {
            float x = 0.0f;
            for (auto c: line) {
                switch (c) {
                    case '0': {
                        const auto entity = reg.create();
                        reg.emplace<TransformComponent>(entity, Vector2(32.0f*x, 32.0f*y), 0.0f);
                        reg.emplace<SpriteComponent>(entity, 0, WHITE);
                        x++;
                        break;
                    }
                    case '1': {
                        const auto entity = reg.create();
                        reg.emplace<TransformComponent>(entity, Vector2(32.0f*x, 32.0f*y), 0.0f);
                        reg.emplace<SpriteComponent>(entity, 0, WHITE);
                        x++;
                        break;
                    }
                    default:
                        break;
                }

            }
            y++;
        }
    }
}

int main() {
    constexpr int screenWidth = 1280;
    constexpr int screenHeight = 820;

    InitWindow(screenWidth, screenHeight, "AEGIS PROTOCOL");

    Player player = { 0 };
    player.position = (Vector2){ 400, 280 };
    player.speed = 100;

    Camera2D camera = { 0 };
    camera.target = player.position;
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.zoom = 1.0f;

    auto* reg = new Registry();

    auto* rm = new ResourceManager();
    rm->Load("../assets/blocks/environment/arkycite-floor.png");

    MapLoader::Load("../assets/map.txt", reg->registry);

    spawn_chunks(reg);

    SetTargetFPS(144);
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        update(deltaTime, &camera, &player, screenWidth, screenHeight);
        draw(deltaTime,&camera,  &player, reg, rm);
    }

    delete rm;
    delete reg;
    CloseWindow();

}

