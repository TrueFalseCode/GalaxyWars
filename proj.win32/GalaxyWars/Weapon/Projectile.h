#pragma once

#include "..//Actor/Actor.h"

/* Класс Projectile предоставляет функции
* для удобного создания объектов-снарядов,
* которые перемещаются из одной точки в другую
* с заданной скоростью.
*/
class Projectile : public Actor
{
public:

	Projectile(const Point& start, const Point& finish, const float& health, const float & damage, Render::Texture* texture, const float& speedCoefficient);

	virtual	void Update(const float& dt) override;

protected:

	float _speedCoefficient;
	TimedSpline<Point> _spline;
};