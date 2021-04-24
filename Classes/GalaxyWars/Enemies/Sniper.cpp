
#include "Sniper.h"

Sniper::Sniper(const float & health, const string& filename, const Point & globalCenter, const float & radius, const float & startRotate, const float & RPS, const float & step) : 
	Enemy(health, filename, globalCenter, radius, startRotate, RPS, step)
{
}

void Sniper::Update(const float & dt)
{
	UpdateReactionTimer(dt);
	UpdateWeapon(dt);

	if (_timer >= _timeByStep)
	{
		SetRotateDegrees(GetRotateDegrees() + _step);
		_timer = 0;
	}
	else
	{
		_timer += dt;
	}
	SetActorPosition(GetNextPosition());

	if (IsReactionAllows() && _character && CheckVisibleZoneCollision(_character))
	{
		DoAttack(this, GetTargetPositionWithStormtrooperEffect(_character->GetRotateDegrees(), _character->GetRadius() + 250.0f));
	}
}
