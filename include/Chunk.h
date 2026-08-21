#pragma once

#include "raylib.h"
#include "constants.h"

enum class CeilType {
    GRASS
};


struct Ceil {
    float x, y;
    Image image;
    CeilType type;
};

struct Chunk {
    Chunk(float x, float y): x(x), y(y) {
    	ceils.reserve(CHUNK_SIZE*CHUNK_SIZE);
	    for (int i = 0; i < CHUNK_SIZE*CHUNK_SIZE; i++) {
		    ceils.emplace_back();
	    }
    }
    float x, y;
    std::vector<Ceil> ceils;

    void draw(bool isPlayerIn) const {

    	Color color;
    	if (isPlayerIn) {
    		color = LIME;
    	} else {
    		color = BLACK;
    	}
        DrawRectangleLines(x, y, CHUNK_SIZE*32, CHUNK_SIZE*32, color);
    }
};