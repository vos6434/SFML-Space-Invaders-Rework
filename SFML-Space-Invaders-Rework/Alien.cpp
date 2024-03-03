#include "Alien.h"

bool m_isGoingRight = true;

void Alien::Update(const float _deltaTime)
{
	CheckDirection();
	Move(_deltaTime);
}

void Alien::Move(const float _deltaTime)
{
	Vector2f direction = Vector2f(1.0, 0.0);
	if (!m_isGoingRight) // If is not going right
	{
		direction *= -1.f; // reverse the direction
	}
	Vector2f newposition = getPosition() + direction * speed * _deltaTime;
	setPosition(newposition);
}

void Alien::CheckDirection()
{
	if (getGlobalBounds().left <= 0) //if our left side is at the left side of the screen
	{
		m_isGoingRight = true; //go right
		MoveDown(); // Move down when reaching the edge
		return;
	}

	float rightSide = getGlobalBounds().left + getGlobalBounds().width;

	if (rightSide >= 1000) //if our right side is at the right side of the screen
	{
		m_isGoingRight = false; //go left
		MoveDown(); // Move down when reaching the edge
	}
}

void Alien::MoveDown()
{
	setPosition(getPosition() + sf::Vector2f(0.0f, 100.0f));
}
