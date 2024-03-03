#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Alien : public Sprite
{
	private:
		float speed = 200.0f;

	public:
		void Update(const float _deltaTime);

		void MoveDown();

		void Move(const float _deltaTime);

		void CheckDirection();
};

