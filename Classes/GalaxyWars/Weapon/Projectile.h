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

	float _speedCoefficient;
	Point _finishPoint;
	Node* _positionNode;
};