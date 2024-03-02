#include "Bullet.h"

void Bullet::Update(const float _deltaTime)
{
	Move(_deltaTime);
}

void Bullet::Move(const float _deltaTime)
{
	Vector2f direction = Vector2f(0.0, -1.0);
	Vector2f newposition = getPosition() + direction * m_Speed * _deltaTime;
	setPosition(newposition);
}
