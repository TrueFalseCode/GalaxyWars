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
	void CreateCharacter(const float& health, shared_ptr<Weapon> weapon, const string& filename, const Point& globalCenter, const float& radius, const float& startRotate, const float& degreesPerSecond);

	// Функция предназначена для создания набора врагов по заданным параметрам
	// Примечание: 
	// * Если amount > weapons.Size(), то создастся weapons.Size() врагов с оружием
	// * и (amount - weapons.Size()) врагов без оружия.
	// * Если же Если amount < weapons.Size(), то будет создано weapons.Size() врагов с оружием
	template<typename TEnemy>
	void CreateEnemies(const unsigned int& amount, const float& health, const vector<shared_ptr<Weapon>>& weapons, const float& startRotate, const float& offset, const string& filename, const Point& globalCenter, const float& radius, const float& degreesPerSecond, const float& visibleZone, const float& stormtrooperEffect);

	void Update(const float& dt);

	// Функция инициирует атаку главного персонажа
	void CharacterAttack();

	void MoveCharacterLeft();
	void MoveCharacterRight();
	void MoveCharacterBy(const float& stepDegrees);
	void MoveCharacterTo(const float& newDegrees);
	void StopCharacter();

	bool IsLevelUp();
	bool IsGameOver();
	void StartGame();
	void RestartGame();
	void EndGame();

	~GameManager();

private:

	void FillEnemy(shared_ptr<Enemy> enemy, const shared_ptr<Weapon> weapon, const float& visibleZone, const float& stormtrooperEffect);

	bool _bGameOver;
	bool _bLevelUp;

	shared_ptr<Character> _character;
	float _characterDegreesPerSecond;

	// Список, в котором хранятся "жизни" персонажа,
	// которые по очереди изчезают, когда он получает урон.
	vector<shared_ptr<Actor>> _characterHealth;

	// Контейнер с флагами, которые показывают текущий уровень
	vector<shared_ptr<Actor>> _flags;

	// Список всех врагов, находящихся на сцене
	vector<shared_ptr<Enemy>> _enemies;
};

template<typename TCharacter>
void GameManager::CreateCharacter(const float& health, shared_ptr<Weapon> weapon, const string& filename, const Point& globalCenter, const float& radius, const float& startRotate, const float& degreesPerSecond)
{
	_character = make_shared<TCharacter>(health, filename, globalCenter, radius, startRotate, 0.0f);

	_characterDegreesPerSecond = degreesPerSecond;

	if (_character && weapon)
	{
		_character->SetWeapon(weapon);
	}

	float healthX = 100.0f;
	float healthY = 100.0f;
	float healthOffset = 80.0f;

	for (int i = 0; i < health; ++i)
	{
		auto life = make_shared<Actor>(Point(healthX, healthY + (i * healthOffset)), 1.0f, filename);
		_characterHealth.push_back(life);
	}
}

template<typename TEnemy>
void GameManager::CreateEnemies(const unsigned int& amount, const float& health, const vector<shared_ptr<Weapon>>& weapons, const float& startRotate, const float& offset, const string& filename, const Point& globalCenter, const float& radius, const float& degreesPerSecond, const float& visibleZone, const float& stormtrooperEffect)
{
	unsigned int remainingAmount = amount;
	float offsetSum = startRotate;

	// Создание врагов с оружием
	for (auto wpn : weapons)
	{
		shared_ptr<TEnemy> newEnemy = make_shared<TEnemy>(health, filename, globalCenter, radius, offsetSum, degreesPerSecond);
		if (newEnemy)
		{
			FillEnemy(newEnemy, wpn, visibleZone, stormtrooperEffect);
			_enemies.push_back(newEnemy);
			offsetSum += offset;
		}
		--remainingAmount;
	}

	// Если оружия было меньше, чем врагов, создаются враги без оружия
	for (unsigned int i = 0; i < remainingAmount; ++i)
	{
		shared_ptr<TEnemy> newEnemy = make_shared<TEnemy>(health, filename, globalCenter, radius, offsetSum, degreesPerSecond);
		if (newEnemy)
		{
			FillEnemy(newEnemy, shared_ptr<Weapon>(nullptr), visibleZone, stormtrooperEffect);
			_enemies.push_back(newEnemy);
			offsetSum += offset;
		}
	}
}