#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Bullet : public Sprite
{
	private:
		float m_Speed = 600.0f;

	public:
		void Update(const float _deltaTime);

		void Move(const float _deltaTime);
};

