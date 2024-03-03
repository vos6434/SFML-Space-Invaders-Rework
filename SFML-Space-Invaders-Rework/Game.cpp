#include "Game.h"
#include "Player.h"
#include "Alien.h"
#include "Bullet.h"

Game::Game()
{
	m_Window.create(VideoMode(1000, 1000), "Space Invaders");

	m_GameWon = false;

	m_Player = new Player();
	m_Player->setPosition(Vector2f(500, 800));

	m_PlayerTexture = new Texture();
	m_PlayerTexture->loadFromFile("mbase.png");
	m_Player->setTexture(*m_PlayerTexture);


	//m_Alien = new Alien();
	//m_Alien->setPosition(Vector2f(500, 100));

	m_AlienTexture = new Texture();
	m_AlienTexture->loadFromFile("alien1.png");
	//m_Alien->setTexture(*m_AlienTexture);

	//m_Bullet = new Bullet();
	m_BulletTexture = new Texture();
		m_BulletTexture->loadFromFile("Bullet.png");
	//m_BulletTexture->setTexture(*m_BulletTexture);

	//SpawnBullet(Vector2f(500, 500)); Spawns a bullet at the start of the game
	SpawnAlienGrid(5, 7, 100, 100, 80); // Adjust parameters as needed

	m_Score = 0;

	if (!m_Font.loadFromFile("arial.ttf")) // Replace "arial.ttf" with the path to your font file
	{
		m_Window.close(); // close window if found is not found
	}

	m_ScoreText.setFont(m_Font);
	m_ScoreText.setCharacterSize(24);
	m_ScoreText.setFillColor(sf::Color::White);
	m_ScoreText.setPosition(10.f, 10.f); // Adjust position as needed
	UpdateScoreText();

}

void Game::Start()
{
	Clock clock;
	while (m_Window.isOpen())
	{
		// check all the triggered window events since the last iteration of the loop
		Event event;
		while (m_Window.pollEvent(event))
		{
			// close the window with close request event
			if (event.type == Event::Closed)
				m_Window.close();
		}

		// Restart clock and save elapsed time to dt
		Time dt = clock.restart();

		// Make a fraction from the delta time
		float dtAsSeconds = dt.asSeconds();

		// call methods in the game loops start
		Update(dtAsSeconds);
		Draw();
		Input();
		CheckCollisions();

	}
}

void Game::Input()
{
	int _input = 0;

	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		_input = -1;
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		_input = 1;
	}
	
	m_Player->SetInput(_input);

	
	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		if (!m_HasShot)
		{
			float xPosition = m_Player->getPosition().x + m_Player->getGlobalBounds().width / 2;
			float yPosition = m_Player->getGlobalBounds().top - m_BulletTexture->getSize().y;
			Vector2f shootPosition = Vector2f(xPosition, yPosition);
			SpawnBullet(shootPosition);

			m_HasShot = true;
		}
	}
		else
		{
			m_HasShot = false;
		}
}

void Game::Update(float dt_)
{
	m_Player->Update(dt_);
	/*
	if (m_Alien != nullptr)
	{
		m_Alien->Update(dt_);
	}
	*/
	for (auto& alien : m_AlienList)
	{
		if (alien)
		{
			alien->Update(dt_);

			if (alien->getPosition().y >= m_LoseHeight)
			{
				GameOver();
			}
		}
	}

	for (auto& bullet : m_BulletList)
		{
		if (bullet)
			{
			bullet->Update(dt_);
			}
		}
}


void Game::Draw()
{
	m_Window.clear();

	if (m_GameWon)
	{
		// Display "Game Win" message
		sf::Text gameWinText("Game Win!", m_Font, 36);
		gameWinText.setFillColor(sf::Color::Green);
		gameWinText.setPosition(400.f, 400.f); // Adjust position as needed
		m_Window.draw(gameWinText);
	}
	else
	{
		m_Window.draw(m_ScoreText);
		m_Window.draw(*m_Player);

		for (auto& alien : m_AlienList)
		{
			if (alien)
			{
				m_Window.draw(*alien);
			}
		}

		for (auto& bullet : m_BulletList)
		{
			if (bullet)
			{
				m_Window.draw(*bullet);
			}
		}
	}

	m_Window.display();
}

void Game::SpawnAlienGrid(int rows, int columns, float startX, float startY, float spacing)
{
	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < columns; ++col)
		{
			Alien* newAlien = new Alien();
			newAlien->setTexture(*m_AlienTexture);

			float x = startX + col * spacing;
			float y = startY + row * spacing;

			newAlien->setPosition(Vector2f(x, y));

			// Add the new alien to a vector or array to keep track of them
			// For example: vector<Alien*> m_AlienList;
			m_AlienList.push_back(newAlien);
		}
	}
}

void Game::SpawnBullet(const Vector2f _position)
{
	Bullet* newBullet = new Bullet();
	newBullet->setTexture(*m_BulletTexture);
	newBullet->setPosition(_position);
	m_BulletList.push_back(newBullet);
}

void Game::CheckCollisions()
{
	// Check to see if any bullets are colliding with aliens
	for (auto&bullet : m_BulletList)
	{
		for (auto&alien : m_AlienList)
		{
			if (alien && bullet)
			{
				if (bullet->getGlobalBounds().intersects(alien->getGlobalBounds()))
				{
					delete alien;
					alien = nullptr;
					delete bullet;
					bullet = nullptr;

					m_Score++; // Increase the score when an alien is hit
					UpdateScoreText(); //Update score text
				}
			}
		}
	}

	auto eraseStart = remove(begin(m_BulletList), end(m_BulletList), nullptr);
	m_BulletList.erase(eraseStart, end(m_BulletList));

	if (m_Score >= 35)
	{
		m_GameWon = true;
	}

}

void Game::GameOver()
{
	m_Window.close(); // Close the game window (or perform other game over actions)
}

void Game::UpdateScoreText()
{
	m_ScoreText.setString("Score: " + std::to_string(m_Score));
}

