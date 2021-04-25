
#include "Firearms.h"

Firearms::Firearms(const float & damage, const float& coolDown, const float& projectileSpeed, const string& filename) : Weapon(damage, coolDown),
																												_projectileSpeed(projectileSpeed), 
																												_spriteName(filename)
{
	int a = 1;
}

void Firearms::Update(const float & dt)
{
	Weapon::Update(dt);

	for (auto beg = _projectiles.begin(); beg != _projectiles.cend(); )
	{
		if (*beg)
		{
			// Когда снаряд достигает цели, 
			// после которой он должен быть уничтожен,
			// IsDied() возвращает true и оружие удаляет
			// созданный ранее снаряд из своего списка
			if ((*beg)->IsDied())
			{
				beg = _projectiles.erase(beg);
			}
			else
			{
				(*beg)->Update(dt);
				++beg;
			}
		}
	}
}

void Firearms::DoAttack(const Actor* attackingActor, const Point& target)
{
	if (CoolDownEnded())
	{
		if (attackingActor)
		{
			_projectiles.push_back(make_shared<Projectile>(attackingActor->GetActorPosition(), target, 1.0f, GetDamage(), _spriteName, _projectileSpeed));
			StartCoolDown();
		}
	}
}

void Firearms::DoAttack(const Actor * attackingActor, const Actor * target)
{
	if (CoolDownEnded())
	{
		if (attackingActor && target)
		{
			DoAttack(attackingActor, target->GetActorPosition());
		}
	}
}

bool Firearms::CheckHits(shared_ptr<Actor> actor)
{
	for (auto prjctl : _projectiles)
	{
		if (actor->CheckCollision(prjctl))
		{
			// Когда снаряд достигает цели, он должен быть уничтожен,
			// поэтому мы наносим ему урон, равный его текущему здоровью.
			prjctl->DoDamage(prjctl->GetCurrentHealth());

			return true;
		}
	}

	return false;
}

vector<shared_ptr<Actor>> Firearms::CheckHits(vector<shared_ptr<Actor>> actors)
{
	vector<shared_ptr<Actor>> hitsActors;

	for (auto actr : actors)
	{
		if (CheckHits(actr))
		{
			hitsActors.push_back(actr);
		}
	}

	return hitsActors;
}
