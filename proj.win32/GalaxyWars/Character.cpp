#pragma once

#include "Character.h"

Character::Character(const float& health,
			   const string& filename,
			   const Point& globalCenter,
			   const float& radius,
			   const float& startRotate) : Actor(globalCenter, health, filename),
										   CircleActor(globalCenter, radius, startRotate)
{
	SetActorPosition(GetNextPosition());
}

void Character::Update(const float & dt)
{
	UpdateWeapon(dt);
}

vector<shared_ptr<Actor>> Character::CheckNProcessHits(vector<shared_ptr<Enemy>> enemies)
{
	vector<shared_ptr<Actor>> hitsEnemies;

	for (auto enm : enemies)
	{
		if (AttackActor::CheckNProcessHits(enm))
		{
			hitsEnemies.push_back(enm);
		}
	}

	return hitsEnemies;
}

void Character::MoveByStep(const float & stepDergees)
{
	SetRotateDegrees(GetRotateDegrees() + stepDergees);
	SetActorPosition(GetNextPosition());
}

void Character::MoveTo(const float & newDergees)
{
	SetRotateDegrees(newDergees);
	SetActorPosition(GetNextPosition());
}
