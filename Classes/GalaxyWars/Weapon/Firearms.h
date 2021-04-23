#pragma once

#include <vector>
using std::vector;

#include <string>
using std::string;

#include "Weapon.h"
#include "Projectile.h"

/* Класс Firearms является наследником класса Weapon и
* описывает поведение, похожее на огнестрельное оружие,
* то есть имеется снаряд, который с определенной скоростью
* летит в указанном направлении.
*/
class Firearms : public Weapon
{
public:

	Firearms(const float& damage, const float& coolDown, const float& projectileSpeed, const string& filename);

	virtual void Update(const float& dt) override;

	virtual void DoAttack(const Actor* attackingActor, const Point& target) override;
	virtual void DoAttack(const Actor* attackingActor, const Actor* target) override;

	virtual bool CheckHits(shared_ptr<Actor> actor) override;
	virtual vector<shared_ptr<Actor>> CheckHits(vector<shared_ptr<Actor>> actors) override;

protected:

	float _projectileSpeed;

	const string& _spriteName;

	// Список летящих снарядов, выпущенных оружием
	vector<shared_ptr<Projectile>> _projectiles;
};

