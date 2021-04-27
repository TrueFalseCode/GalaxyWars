
#include "CircleActor.h"

const float PI = 3.1415926535897932385f;

CircleActor::CircleActor(const Point& globalCenter, const float& globalRadius, const float& startRotate, const float& degreesPerSecond) : _globalCenter(globalCenter), _globalRadius(globalRadius), _degreesPerSecond(degreesPerSecond)
{
	SetRotateDegrees(startRotate);
}

void CircleActor::SetRotateDegrees(const float& new_value)
{
	_rotateDegrees = new_value;
	NormalizeDegrees(_rotateDegrees);
}

float CircleActor::GetRotateDegrees() const
{
	return _rotateDegrees;
}

Point CircleActor::GetGlobalCenter() const
{
	return _globalCenter;
}

float CircleActor::GetRadius() const
{
	return _globalRadius;
}

void CircleActor::SetDegreesPerSecond(const float & newDegrees)
{
	_degreesPerSecond = newDegrees;
}

float CircleActor::GetDegreesPerSecond() const
{
	return _degreesPerSecond;
}

inline float CircleActor::DegreesToRadians(const float& deg) const
{
	return deg * (PI / 180);
}

Point CircleActor::GetNextPosition() const
{
	return GetTargetPosition(_rotateDegrees, _globalRadius);
}

void CircleActor::NormalizeDegrees(float & value) const
{
	while (value > 360.0f)
	{
		value -= 360.0f;
	}

	while (value < -360.0f)
	{
		value += 360.0f;
	}

	if (value < 0.0f)
	{
		value += 360.0f;
	}
}

Point CircleActor::GetTargetPosition(const float& rotateDegrees, const float& radius) const
{
	float rad = DegreesToRadians(rotateDegrees);

	return Point(_globalCenter.x + (radius * cosf(rad)), _globalCenter.y + (radius * sinf(rad)));
}