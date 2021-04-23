#pragma once

#include "Enemy.h"

/* Наследуемый от Enemy класс, который 
* переопределяет поведение таким образом,
* чтобы атака была направлена точно на игрока.
*/
class Sniper : public Enemy
{
public:
	Sniper(const float& health, const string& filename, const Point& globalCenter, const float& radius, const int& startRotate, const float& RPS, const int& step);

	virtual	void Update(const float& dt) override;
};

