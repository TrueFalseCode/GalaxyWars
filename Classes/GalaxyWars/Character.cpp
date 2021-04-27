#pragma once

#include "Character.h"

Character::Character(const float& health,
					const string& filename,
					const Point& globalCenter,
					const float& radius,
					const float& startRotate,
					const float& degreesPerSecond) : Actor(globalCenter, health, filename),
													CircleActor(globalCenter, radius, startRotate, degreesPerSecond)
{
	SetActorPosition(GetNextPosition());
}

void Character::Update(const float & dt)
{
	UpdateWeapon(dt);
	MoveBy(GetDegreesPerSecond() * dt);
}

vector<shared_ptr<Actor>> Character::CheckAndProcessHits(vector<shared_ptr<Enemy>> enemies)
{
	vector<shared_ptr<Actor>> hitsEnemies;

	for (auto enm : enemies)
	{
		if (AttackActor::CheckAndProcessHits(enm))
		{
			hitsEnemies.push_back(enm);
		}
	}

	return hitsEnemies;
}

void Character::MoveBy(const float & stepDegrees)
{
	SetRotateDegrees(GetRotateDegrees() + stepDegrees);
	SetActorPosition(GetNextPosition());
}

void Character::MoveTo(const float & stepDegrees)
{
	SetRotateDegrees(stepDegrees);
	SetActorPosition(GetNextPosition());
}
