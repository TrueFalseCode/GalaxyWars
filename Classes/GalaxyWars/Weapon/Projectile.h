#pragma once

#include "..//Actor/Actor.h"

#include "cocos2d.h"
using cocos2d::Node;
using cocos2d::MoveTo;

/* Класс Projectile предоставляет функции
* для удобного создания объектов-снарядов,
* которые перемещаются из одной точки в другую
* с заданной скоростью.
*/
class Projectile : public Actor
{
public:

	Projectile(const Point& start, const Point& finish, const float& health, const float & damage, const string& filename, const float& speedCoefficient);
	~Projectile();

	virtual	void Update(const float& dt) override;

protected:

	// За какую долю секунды снаряд должен долететь до конечной точки
	// Расчитывается по формуле: 1 секунда / _speedCoefficient
	float _speedCoefficient;

	Point _finishPoint;

	// Данный нод используется для расчета координат полета снаряда с помощью MoveTo Action.
	// Эти координаты задаются Actor'у снаряда на каждой итерации update, то есть в каждом кадре.
	// Более простого и быстрого варианта рассчета координат для данного случая не придумал.
	Node* _positionNode;
};