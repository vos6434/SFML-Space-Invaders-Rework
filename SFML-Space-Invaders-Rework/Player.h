#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Player : public Sprite
{
	float m_speed = 200.f;
	int m_input = 0;

public:

	void Update(const float deltaTime_);

	void Move(const float deltaTime_);

	void SetInput(const int input_);

};

