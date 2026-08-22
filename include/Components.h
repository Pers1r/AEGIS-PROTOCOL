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
	std::string textureID;
    Color tint;
};

struct AnimatorComponent {
	std::vector<std::string> frames;
	int currentFrame = 0;
	float frameTime = 0.15f;
	float timeAccumulator = 0.0f;
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


