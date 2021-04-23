#pragma once

#include <vector>
using std::vector;

#include <memory>
using std::shared_ptr;
using std::make_shared;

#include "Actor//Actor.h"
#include "Character.h"
#include "Enemies//Enemy.h"
#include "Weapon//Weapon.h"

/* Класс GameManager сожержит методы и свойства,
* позволяющие легко и быстро создавать игровые объекты,
* управлять их изменением и отображением, а также
* управлять состояниями текущей игры, для того, чтобы
* игроку было понятно происходящее на экране.
*/
class GameManager
{
public:

	GameManager();

	// Функция предназначена для создания главного персонажа игры по заданным параметрам
	template<typename TCharacter>
	void CreateCharacter(const float& health, shared_ptr<Weapon> weapon, Render::Texture* texture, const Point& globalCenter, const float& radius, const float& startRotate);

	// Функция предназначена для создания набора врагов по заданным параметрам
	// Примечание: 
	// * Если amount > weapons.Size(), то создастся weapons.Size() врагов с оружием
	// * и (amount - weapons.Size()) врагов без оружия.
	// * Если же Если amount < weapons.Size(), то будет создано weapons.Size() врагов с оружием
	template<typename TEnemy>
	void CreateEnemies(const unsigned int& amount, const float& health, const vector<shared_ptr<Weapon>>& weapons, const float& startRotate, const float& offset, Render::Texture* texture, const Point& globalCenter, const float& radius, const float& RPS, const float& step, const float& visibleZone, const float& stormtrooperEffect);

	void Draw(Render::RenderDeviceInterface& device);
	void Update(const float& dt);

	// Функция устанавливает, в каком месте будет центр 
	// отображаемого пояснительного текста(в данном случае - Actor'а с заданной текстурой)
	void SetTextCenter(const Point& textCenter);

	// Функция инициирует атаку главного персонажа
	void CharacterAttack();

	void MoveCharacterByStep(const float& stepDegrees);
	void MoveCharacterTo(const float& newDegrees);

	bool IsGameOver();
	void RestartGame();
	void EndGame();

	~GameManager();

private:

	void FillEnemy(shared_ptr<Enemy> enemy, const shared_ptr<Weapon> weapon, const float& visibleZone, const float& stormtrooperEffect);

	bool _bGameOver;

	// Указатель на объект с пояснительным текстом
	shared_ptr<Actor> _text;

	shared_ptr<Character> _character;

	// Список, в котором хранятся "жизни" персонажа,
	// которые по очереди изчезают, когда он получает урон.
	vector<shared_ptr<Actor>> _characterHealth;

	// Список всех врагов, находящихся на сцене
	vector<shared_ptr<Enemy>> _enemies;
};

template<typename TCharacter>
void GameManager::CreateCharacter(const float& health, shared_ptr<Weapon> weapon, Render::Texture* texture, const Point& globalCenter, const float& radius, const float& startRotate)
{
	_character = make_shared<TCharacter>(health, texture, globalCenter, radius, startRotate);

	if (_character && weapon)
	{
		_character->SetWeapon(weapon);
	}

	int healthX = 100;
	int healthY = 100;
	int healthOffset = 80;

	for (int i = 0; i < health; ++i)
	{
		auto life = make_shared<Actor>(Point(healthX, healthY + (i * healthOffset)), 1.0f, texture);
		_characterHealth.push_back(life);
	}
}

template<typename TEnemy>
void GameManager::CreateEnemies(const unsigned int& amount, const float& health, const vector<shared_ptr<Weapon>>& weapons, const float& startRotate, const float& offset, Render::Texture* texture, const Point& globalCenter, const float& radius, const float& RPS, const float& step, const float& visibleZone, const float& stormtrooperEffect)
{
	unsigned int remainingAmount = amount;
	float offsetSum = startRotate;

	for (auto wpn : weapons)
	{
		shared_ptr<TEnemy> newEnemy = make_shared<TEnemy>(health, texture, globalCenter, radius, offsetSum, RPS, step);
		if (newEnemy)
		{
			FillEnemy(newEnemy, wpn, visibleZone, stormtrooperEffect);
			_enemies.push_back(newEnemy);
			offsetSum += offset;
		}
		--remainingAmount;
	}

	for (unsigned int i = 0; i < remainingAmount; ++i)
	{
		shared_ptr<TEnemy> newEnemy = make_shared<TEnemy>(health, texture, globalCenter, radius, offsetSum, RPS, step);
		if (newEnemy)
		{
			FillEnemy(newEnemy, shared_ptr<Weapon>(nullptr), visibleZone, stormtrooperEffect);
			_enemies.push_back(newEnemy);
			offsetSum += offset;
		}
	}
}