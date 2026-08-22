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
    ~ResourceManager() {
        UnloadAll();
    }

    void Load(const std::string& id, const std::string& filepath) {
    	if (!textures.contains(id)) {
    		Texture2D tex = LoadTexture(filepath.c_str());
    		textures[id] = tex;
    	}
        std::cout << "Load texture: " << filepath << std::endl;
    }

    Texture2D Get(const std::string& id) {
    	if (textures.find(id) != textures.end()) {
    		return textures[id];
    	}
    	std::cerr << "Warning: Texture '" << id << "' not found!\n";
    	return Texture2D{ 0 };
    }

    void UnloadAll() {
    	for (auto& pair : textures) {
    		UnloadTexture(pair.second);
    	}
    	textures.clear();
    }
private:
	std::unordered_map<std::string, Texture2D> textures;
};