#pragma once

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