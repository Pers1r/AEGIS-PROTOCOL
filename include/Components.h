#pragma once
#include "raylib.h"

// ENUMS

enum BeltType {
	Basic,
};

enum ResourceType {
	Iron,
	Copper,
	Coal,
};

enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

struct TransformComponent {
    Vector2 position;
    float rotation;
};


struct SpriteComponent {
    int textureID;
    Color tint;
};

struct DirectionComponent {
	Direction direction;
};

struct BeltComponent {
	Direction direction;
	BeltType type;

};

struct MinerComponent {
	ResourceType resourceType;
	int storage;
};


struct ResourceNodeComponent {
	ResourceType type;
    float baseMineTime;
};


