
#include "Projectile.h"

Projectile::Projectile(const Point & start,
					   const Point & finish,
					   const float& health,
					   const float & damage,
					   Render::Texture* texture,
					   const float & speedCoefficient) : Actor(start, health, texture),
													      _speedCoefficient(speedCoefficient)
{
	_spline.addKey(0.0f, start);
	_spline.addKey(1.0f, finish);
	_spline.CalculateGradient();
}

void Projectile::Update(const float & dt)
{
	_timer += dt * _speedCoefficient;

	Point nextPosition;// = _spline.getGlobalFrame(std::clamp(0.0f, 1.0f, _timer / 6.0f));

	// Как только снаряд достиг конечной точки, 
	// ему наносится урон, равный его здоровью,
	// чтобы обозначить, что он должен быть уничтожен.
	if (nextPosition == _spline.GetKey(_spline.GetKeysCount() - 1))
	{
		DoDamage(GetCurrentHealth());
	}
	else
	{
		SetActorPosition(nextPosition);
	}
}
