#pragma once
#include <iostream>
#include <map>
#include <ostream>
#include <string>

#include "raylib.h"

enum class TextureID {
    TEX_GROUND,
    TEX_COAL_MINE,
    TEX_COAL_ORE,
};

class ResourceManager {
public:
    ResourceManager() {
        index = 0;
    }
    ~ResourceManager() {
        UnloadAll();
    }

    void Load(const std::string& filepath) {
        Texture2D texture = LoadTexture(filepath.c_str());
        textures.emplace(index++, texture);
        std::cout << "Load texture: " << filepath << std::endl;
    }

    Texture2D get(const int i) const{
        return textures.at(i);
    }

    void UnloadAll() {
        for (auto & texture : textures) {
            UnloadTexture(texture.second);
        }
    }
    int index;
private:
    std::map<int, Texture2D> textures;

};