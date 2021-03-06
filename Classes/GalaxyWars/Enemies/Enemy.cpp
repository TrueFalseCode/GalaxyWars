
#include <random>
#include <ctime>

#include "Enemy.h"

Enemy::Enemy(const float& health,
			 const string& filename,
			 const Point& globalCenter, 
			 const float& radius, 
			 const float& startRotate,
			 const float& degreesPerSecond) : Actor(globalCenter, health, filename),
											  CircleActor(globalCenter, radius, startRotate, degreesPerSecond),
											  _visibleZone(0.0f),
											  _bReactionAllow(false),
											  _reactionDelay(-1.0f),
											  _reactionDelayTimer(0.0f),
											  _generator(std::random_device().operator()()),
											  _stormtrooperEffect(0.0f)
{
}

void Enemy::Update(const float& dt)
{
	UpdateReactionTimer(dt);
	UpdateWeapon(dt);
	MoveBy(GetDegreesPerSecond() * dt);

	if (IsReactionAllows() && _character)
	{
		// В данном случае, целью указано текущее положение этого врага, чтобы он стрелял просто вперед.
		// Снаряд полетит на 350 единиц дальше, чем радиус окружности, на которой находится персонаж
		DoAttack(this, GetTargetPositionWithStormtrooperEffect(GetRotateDegrees(), _character->GetRadius() + 350.0f));
	}	
}

shared_ptr<const CircleActor> Enemy::GetCharacter() const
{
	return _character;
}

void Enemy::SetCharacter(shared_ptr<const CircleActor> Character)
{
	_character = Character;
}

void Enemy::SetVisibleZone(const float & visibleZone)
{
	_visibleZone = visibleZone;
}

float Enemy::GetVisibleZone() const
{
	return _visibleZone;
}

void Enemy::SetStormtrooperEffect(const float & val)
{
	_stormtrooperEffect = val;

	if (val < 0.0f)
	{
		_stormtrooperEffect = 0.0f;
	}
	else if(val > 1.0f)
	{
		_stormtrooperEffect = 1.0f;
	}
}

void Enemy::MoveBy(const float & stepDegrees)
{
	SetRotateDegrees(GetRotateDegrees() + stepDegrees);
	SetActorPosition(GetNextPosition(), -(GetRotateDegrees() - 90.0f));
}

void Enemy::MoveTo(const float & stepDegrees)
{
	SetRotateDegrees(stepDegrees);
	SetActorPosition(GetNextPosition(), -(GetRotateDegrees() - 90.0f));
}

bool Enemy::CheckVisibleZoneCollision(shared_ptr<const CircleActor> circleActor)
{
	if (circleActor)
	{
		float minZoneDegrees = GetRotateDegrees() - (_visibleZone / 2);
		float maxZoneDegrees = minZoneDegrees + _visibleZone;
		float actorDegrees = circleActor->GetRotateDegrees();

		if ((actorDegrees >= minZoneDegrees) && (actorDegrees <= maxZoneDegrees))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

void Enemy::UpdateReactionTimer(const float & dt)
{
	if (_reactionDelay < 0.0f)
	{
		// После каждой атаки задержка реакции врага 
		// принимает случайное значение из заданного диапазона.
		// Это сделано для того, чтобы добавить хаотичности в атаку врагов
		_reactionDelay = GetRandomValueFromRange(0.5f, 2.5f);

		_bReactionAllow = false;
	}

	if (_reactionDelayTimer >= _reactionDelay)
	{
		_reactionDelay = -1.0f;
		_reactionDelayTimer = 0.0f;

		_bReactionAllow = true;
	}

	_reactionDelayTimer += dt;
}

bool Enemy::IsReactionAllows()
{
	return _bReactionAllow;
}

float Enemy::GetRandomValueFromRange(const float & min, const float & max)
{
	return std::uniform_real_distribution<float>{min, max}(_generator);
}

Point Enemy::GetTargetPositionWithStormtrooperEffect(const float & rotateDegrees, const float & radius)
{
	float visibleZoneHalf = (_visibleZone / 2) * _stormtrooperEffect;

	return GetTargetPosition(GetRandomValueFromRange(rotateDegrees - visibleZoneHalf, rotateDegrees + visibleZoneHalf), radius);
}
