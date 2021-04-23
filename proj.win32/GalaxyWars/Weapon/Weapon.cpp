
#include "Weapon.h"

Weapon::Weapon(const float& damage, const float& coolDown) : _damage(damage), _coolDown(coolDown), _coolDownTimer(0.0f), _bEnableCoolDown(false) { }

void Weapon::Update(const float & dt)
{
	if (_bEnableCoolDown)
	{
		if (_coolDownTimer >= _coolDown)
		{
			_bEnableCoolDown = false;
			_coolDownTimer = 0.0f;
		}
		else
		{
			_coolDownTimer += dt;
		}
	}
}

void Weapon::StartCoolDown()
{
	_bEnableCoolDown = true;
}

bool Weapon::CoolDownEnded()
{
	return !_bEnableCoolDown;
}

float Weapon::GetDamage()
{
	return _damage;
}