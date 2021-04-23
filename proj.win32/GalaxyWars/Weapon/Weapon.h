#pragma once

#include <memory>
using std::shared_ptr;
using std::make_shared;

#include <vector>
using std::vector;

#include "..//Actor/Actor.h"

/* Абстрактный класс Weapon сожержит функции и свойства, 
* которые имеются у любого оружия. На его основе можно 
* создавать оружие с разными особенностями в поведении.
*/
class Weapon
{
public:
	
	Weapon(const float & damage, const float& coolDown);

	virtual void Draw(Render::RenderDeviceInterface& device) = 0;
	virtual void Update(const float& dt);

	virtual void DoAttack(const Actor* attackingActor, const Point& target) = 0;
	virtual void DoAttack(const Actor* attackingActor, const Actor* target) = 0;

	// Данная функция определяет, нанесло ли оружие урон переданному Actor'у 
	virtual bool CheckHits(shared_ptr<Actor> actor) = 0;

	// Данная функция возвращает список Actor'ов, которым был нанесен урон данным оружием
	virtual vector<shared_ptr<Actor>> CheckHits(vector<shared_ptr<Actor>> actors) = 0;

	float GetDamage();

protected:

	void StartCoolDown();
	bool CoolDownEnded();

private:

	float _damage;
	float _coolDown;
	float _coolDownTimer;
	bool _bEnableCoolDown;
};