#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Alien : public Sprite
{
	private:
		bool m_isGoingRight = true;
		float speed = 200.0f;

	public:
		void Update(const float _deltaTime);

		void Move(const float _deltaTime);

		void CheckDirection();
};

