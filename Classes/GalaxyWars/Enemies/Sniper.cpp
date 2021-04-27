
#include "Sniper.h"

Sniper::Sniper(const float & health, const string& filename, const Point & globalCenter, const float & radius, const float & startRotate, const float & degreesPerSecond) :
	Enemy(health, filename, globalCenter, radius, startRotate, degreesPerSecond)
{
}

void Sniper::Update(const float & dt)
{
	UpdateReactionTimer(dt);
	UpdateWeapon(dt);
	MoveBy(GetDegreesPerSecond() * dt);

	if (IsReactionAllows() && _character && CheckVisibleZoneCollision(_character))
	{
		// Снаряд полетит нацеленно в персонажа, но в зависимости от указанной меткости
		// Снаряд полетит на 350 единиц дальше, чем радиус окружности, на которой находится персонаж
		DoAttack(this, GetTargetPositionWithStormtrooperEffect(_character->GetRotateDegrees(), _character->GetRadius() + 350.0f));
	}
}
