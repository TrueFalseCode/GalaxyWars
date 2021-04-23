
#include "Sniper.h"

Sniper::Sniper(const float & health, Render::Texture * texture, const Point & globalCenter, const float & radius, const int & startRotate, const float & RPS, const int & step) : 
	Enemy(health, texture, globalCenter, radius, startRotate, RPS, step)
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
