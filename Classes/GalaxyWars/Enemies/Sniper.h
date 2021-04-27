#pragma once

#include "Enemy.h"

/* Наследуемый от Enemy класс, который 
* переопределяет поведение таким образом,
* чтобы атака была направлена точно на игрока.
*/
class Sniper : public Enemy
{
public:
	Sniper(const float& health, const string& filename, const Point& globalCenter, const float& radius, const float& startRotate, const float& degreesPerSecond);

	virtual	void Update(const float& dt) override;
};

