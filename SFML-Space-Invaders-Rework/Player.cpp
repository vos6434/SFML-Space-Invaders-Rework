#include "Player.h"

void Player::Update(const float deltaTime_)
{
	Move(deltaTime_);
}

void Player::Move(const float deltaTime_)
{
	Vector2f direction = Vector2f(m_input, 0);
	Vector2f newposition = getPosition() + direction * m_speed * deltaTime_;
	setPosition(newposition);
}

void Player::SetInput(const int input_)
{
	m_input = input_;
}
