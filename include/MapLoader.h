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
						reg.emplace<SpriteComponent>(entity, "grass", WHITE);
						x++;
						break;
					}
					case '1': {
						const auto entity = reg.create();
						reg.emplace<TransformComponent>(entity, Vector2(32.0f*x, 32.0f*y), 0.0f);
						reg.emplace<SpriteComponent>(entity, "belt00", WHITE);
						AnimatorComponent anim;
						anim.frameTime = 0.15f;
						anim.frames = {"belt00", "belt01", "belt02", "belt03"};
						reg.emplace<AnimatorComponent>(entity, anim);
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