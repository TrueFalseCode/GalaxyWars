
#include "AttackActor.h"

void AttackActor::UpdateWeapon(const float & dt)
{
	if (_weapon)
		_weapon->Update(dt);
}

shared_ptr<Weapon> AttackActor::GetWeapon()
{
	return _weapon;
}

void AttackActor::SetWeapon(shared_ptr<Weapon> newWeapon)
{
	_weapon = newWeapon;
}

float AttackActor::GetDamage() const
{
	if (_weapon)
		return _weapon->GetDamage();
	else
		return 0.0f;
}

void AttackActor::DoAttack(const Actor* attackingActor, const Point& target)
{
	if(_weapon)
		_weapon->DoAttack(attackingActor, target);
}

void AttackActor::DoAttack(const Actor* attackingActor, const Actor* target)
{
	if (_weapon)
		_weapon->DoAttack(attackingActor, target);
}

bool AttackActor::CheckAndProcessHits(shared_ptr<Actor> actor)
{
	if (_weapon && _weapon->CheckHits(actor))
	{
		actor->DoDamage(_weapon->GetDamage());

		return true;
	}

	return false;
}

vector<shared_ptr<Actor>> AttackActor::CheckAndProcessHits(vector<shared_ptr<Actor>> actors)
{
	vector<shared_ptr<Actor>> hitsActors;

	if (_weapon)
	{
		hitsActors = _weapon->CheckHits(actors);
		{
			for (auto actr : hitsActors)
			{
				actr->DoDamage(_weapon->GetDamage());
			}
		}
	}

	return hitsActors;
}
