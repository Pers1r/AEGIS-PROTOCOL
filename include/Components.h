#pragma once
#include "raylib.h"


struct TransformComponent {
    Vector2 position;
    float rotation;
};


struct SpriteComponent {
    int textureID;
    Color tint;
};


struct ResourceNodeComponent {
    enum {
        Iron,
        Copper,
        Coal,
    } type;
    float baseMineTime;
};
