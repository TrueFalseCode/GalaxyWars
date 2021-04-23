#pragma once

#include <memory>
using std::shared_ptr;
using std::make_shared;

#include "cocos2d.h"
using cocos2d::Point;

#include "..//Weapon/Weapon.h"

/* Класс AttackActor позволяет объекту 
* иметь возможность использовать оружие
*/
class AttackActor
{
public:

	void DrawWeapon(Render::RenderDeviceInterface& device);
	void UpdateWeapon(const float& dt);

	shared_ptr<Weapon> GetWeapon();
	void SetWeapon(shared_ptr<Weapon> newWeapon);

	float GetDamage() const;

	void DoAttack(const Actor* attackingActor, const Point& target);
	void DoAttack(const Actor* attackingActor, const Actor* target);

	// Данная функция наносит урон заданному Actor'у в зависимости от логики конкретного оружия,
	// а затем возвращает true, если урон был нанесен Actor'у 
	virtual bool CheckNProcessHits(shared_ptr<Actor> actor);

	// Данная функция наносит урон заданным Actor'ам в зависимости от логики конкретного оружия,
	// а затем возвращает список Actor'ов, которым был нанесен урон
	virtual vector<shared_ptr<Actor>> CheckNProcessHits(vector<shared_ptr<Actor>> actors);

private:

	shared_ptr<Weapon> _weapon;
};

