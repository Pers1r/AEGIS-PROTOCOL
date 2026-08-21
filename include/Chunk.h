#pragma once

#define CHUNK_SIZE 32
#define CELL_SIZE 32;

enum class CeilType {
    GRASS
};


struct Ceil {
    float x, y;
    Image image;
    CeilType type;
};

struct Chunk {
    Chunk(float x, float y): x(x), y(y) {}
    float x, y;

    void draw() const {
        DrawRectangleLines(x, y, 32*32, 32*32, BLACK);
    }
};