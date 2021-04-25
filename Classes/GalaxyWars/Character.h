#pragma once

#include <memory>
using std::shared_ptr;

#include "Actor//Actor.h"
#include "Actor//CircleActor.h"
#include "Actor//AttackActor.h"
#include "Enemies//Enemy.h"

/* Класс Character предназначен для создания
* главного персонажа игры, его управления и отображения.
*/
class Character : public Actor, public CircleActor, public AttackActor
{
public:

	Character(const float& health, const string& filename, const Point& globalCenter, const float& radius, const float& startRotate);

	virtual	void Update(const float& dt) override;

	// Данная функция наносит урон заданным Actor'ам(в данном случае - Enemy) в зависимости от логики конкретного оружия,
	// а затем возвращает список Actor'ов, которым был нанесен урон
	vector<shared_ptr<Actor>> CheckAndProcessHits(vector<shared_ptr<Enemy>> enemies);

	// Функция перемещает персонажа на заданное 
	// количество градусов относительно его текущего положения.
	void MoveByStep(const float& stepDergees);

	// Функция перемещает персонажа на заданный угол.
	void MoveTo(const float& newDergees);
};