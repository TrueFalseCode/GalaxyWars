#pragma once

#include "cocos2d.h"
using cocos2d::Point;

/* Класс CircleActor реализует методы,
* которые позволяют объекту легко вычислять
* позицию в заданной окружности.
*/
class CircleActor
{
public:

	CircleActor(const Point& globalCenter, const float& radius, const float& startRotate);

	void SetRotateDegrees(const float& new_value);
	float GetRotateDegrees() const;

	Point GetGlobalCenter() const;
	float GetRadius() const;

	// Функция возвращает точку на оси XY, которая повернута на угол rotateDegrees 
	// в окружности с заданным радиусом (центр окружности при этом хранится в текущем объекте)
	Point GetTargetPosition(const float& rotateDegrees, const float& radius) const;

protected:

	float DegreesToRadians(const float& deg) const;

	// Функция возвращает точку на оси XY, в которую, в соответствии
	// с установленным углом должен быть перемещен объект на следующей итерации
	Point GetNextPosition() const;

	// Нормализует полученное значение так, чтобы оно входило в диапазон 0 - 360
	void NormalizeDegrees(float& value) const;

private:

	Point _globalCenter;
	float _globalRadius;
	float _rotateDegrees;
};