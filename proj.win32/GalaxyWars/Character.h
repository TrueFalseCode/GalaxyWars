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

	Character(const float& health, Render::Texture* texture, const Point& globalCenter, const float& radius, const float& startRotate);

	virtual void Draw(Render::RenderDeviceInterface& device) override;
	virtual	void Update(const float& dt) override;

	// Данная функция наносит урон заданным Actor'ам(в данном случае - Enemy) в зависимости от логики конкретного оружия,
	// а затем возвращает список Actor'ов, которым был нанесен урон
	vector<shared_ptr<Actor>> CheckNProcessHits(vector<shared_ptr<Enemy>> enemies);

	// Функция перемещает персонажа на заданное 
	// количество градусов относительно его текущего положения.
	void MoveByStep(const float& stepDergees);

	// Функция перемещает персонажа на заданный угол.
	void MoveTo(const float& newDergees);
};