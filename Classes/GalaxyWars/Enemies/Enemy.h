#pragma once

#include <memory>
using std::shared_ptr;
using std::make_shared;

#include <random> 
#include <ctime>

#include "..//Actor/Actor.h"
#include "..//Actor/CircleActor.h"
#include "..//Actor/AttackActor.h"

/* Класс Enemy содержит все необходимые 
* функции и свойства базового врага, 
* на основе которого можно создавать врагов с уникальным поведением.
*/
class Enemy : public Actor, public CircleActor, public AttackActor
{
public:

	Enemy(const float& health, const string& filename, const Point& globalCenter, const float& radius, const float& startRotate, const float& degreesPerSecond);

	virtual	void Update(const float& dt) override;

	shared_ptr<const CircleActor> GetCharacter() const;
	void SetCharacter(shared_ptr<const CircleActor> Character);

	// Зона видимости задается в градусах и отражает сумму 
	// количества градусов слева и справа от текущей позиции врага
	void SetVisibleZone(const float& visibleZone);

	float GetVisibleZone() const;

	// Функция устанавливает значение "Эффекта штурмовика",
	// который позволяет регулировать точность попадания врага
	void SetStormtrooperEffect(const float& val);

	// Функция перемещает персонажа на заданное 
	// количество градусов относительно его текущего положения.
	void MoveBy(const float& stepDegrees);

	// Функция перемещает персонажа на заданный угол.
	void MoveTo(const float& newDegrees);

protected:

	// Функция возвращает true, если игрок находится в зоне видимости врага
	bool CheckVisibleZoneCollision(shared_ptr<const CircleActor> circleActor);

	void UpdateReactionTimer(const float& dt);

	// Функция предназначена для того, чтобы определить, позволяет ли установленная реакция врага провести атаку
	bool IsReactionAllows();

	float GetRandomValueFromRange(const float& min, const float& max);

	// Данная функция возвращает точку по заданным углу и радиусу применяя при этом "Эффект штурмовика",
	// который позволяет регулировать точность попадания врага
	Point GetTargetPositionWithStormtrooperEffect(const float& rotateDegrees, const float& radius);

	shared_ptr<const CircleActor> _character;

	// Зона видимости отражает сумму количества градусов справа и слева от текущей позиции врага
	float _visibleZone;

private:

	bool _bReactionAllow;
	float _reactionDelay;
	float _reactionDelayTimer;

	std::mt19937 _generator;

	// Переменная содержит величину "эффекта штурмовика",
	// с помощью которой регулируется точность попадания врага в цель.
	// Величина устанавливается с помощью функции SetStormtrooperEffect(), 
	// которая не позволяет переменной выходить за пределы диапазона 0.0 - 1.0
	// *
	// NOTE: Имеется в виду точность попадания в зоне видимости врага.
	float _stormtrooperEffect;
};