#include <SFML/Graphics.hpp>
#pragma once

using namespace sf;
using namespace std;

class Game
{
private: //Member variables, all forward delcared
		RenderWindow m_Window;
		class Player* m_Player;
		class Texture* m_PlayerTexture;

		//class Alien* m_Alien;
		vector<class Alien*> m_AlienList;
		class Texture* m_AlienTexture;

		//class Bullet* m_Bullet;
		//class Texture* m_BulletTexture;

		vector<class Bullet*> m_BulletList;
		class Texture* m_BulletTexture;

		bool m_HasShot = false;

		float m_LoseHeight = 800.0f;
		void GameOver();

		int m_Score;
		Font m_Font;
		Text m_ScoreText;

		void UpdateScoreText();

public:
	Game();
	void Start();

private:
	void Input();
	void Update(float dt_);
	void Draw();
	void SpawnAlienGrid(int rows, int columns, float startX, float startY, float spacing);
	void SpawnBullet(const Vector2f _position);
	void CheckCollisions();
};

