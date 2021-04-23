
#include <cmath>
#include "Actor.h"

// <<<<< Sphere =====

Sphere::Sphere() : _centerPosition(Point()), _radius(0) { }

Sphere::Sphere(const Point & positionByCenter, const float & radius) : _centerPosition(positionByCenter), _radius(radius) { }

Point Sphere::GetPosition() const
{
	return _centerPosition;
}

void Sphere::SetPosition(const Point & new_position)
{
	_centerPosition = new_position;
}

float Sphere::GetRadius() const
{
	return _radius;
}

void Sphere::SetRadius(const float & new_radius)
{
	_radius = new_radius;
}

bool Sphere::CheckCollision(const Sphere & another_sphere)
{
	if (GetDistance(_centerPosition, another_sphere._centerPosition) <= (_radius + another_sphere._radius))
		return true;
	else
		return false;
}

bool Sphere::CheckCollision(const Point & point)
{
	if (GetDistance(_centerPosition, point) <= _radius)
		return true;
	else
		return false;
}

float Sphere::GetDistance(const Point & A, const Point & B)
{
	float tmp_one = A.x - B.x;
	float tmp_two = A.y - B.y;

	return std::sqrt((tmp_one * tmp_one) + (tmp_two * tmp_two));
}

// ===== Sphere >>>>>

// <<<<< Actor =====

Actor::Actor(const Point& centerPosition, const float& health, const string& filename) : _maxHealth(health), _currentHealth(health), _timer(0.0f)
{
	_sprite = Sprite::create(filename);

	SetActorPosition(centerPosition);

	// Если задана текстура, то диаметр сферы, 
	// которая определяет границы Actor'а
	// будет равен размеру большей стороны текстуры
	if (_sprite)
	{
		float radius_tmp;
		float textureW = _sprite->getContentSize().width;
		float textureH = _sprite->getContentSize().height;

		if (textureW >= textureH)
		{
			radius_tmp = textureW;
		}
		else
		{
			radius_tmp = textureH;
		}

		_body.SetRadius(radius_tmp / 2);
	}
}

void Actor::Update(const float& dt) {}

Point Actor::GetActorPosition() const
{
	return _body.GetPosition();
}

Point Actor::GetTexturePosition() const
{
	return _spritePosition;
}

Sprite * Actor::GetTexture() const
{
	return _sprite;
}

void Actor::SetActorPosition(const Point & new_position)
{
	SetBodyPosition(new_position);

	if (_sprite)
	{
		float X = new_position.x - (_sprite->getContentSize().width / 2);
		float Y = new_position.y - (_sprite->getContentSize().height / 2);

		SetTexturePosition(Point(X, Y));
	}
	else
	{
		SetTexturePosition(new_position);
	}
}

void Actor::SetTexturePosition(const Point & new_position)
{
	_spritePosition = new_position;
}

void Actor::SetBodyPosition(const Point & new_position)
{
	_body.SetPosition(new_position);
}

void Actor::SetTexture(Sprite * new_sprite)
{
		_sprite = new_sprite;
}

bool Actor::CheckCollision(shared_ptr<const Actor> another_actor)
{
	if (another_actor)
		return _body.CheckCollision(another_actor->_body);
	else
		return false;
}

float Actor::GetCurrentHealth() const
{
	return _currentHealth;
}

void Actor::DoHeal(const float & heal)
{
	if ((_currentHealth + heal) < _maxHealth)
		_currentHealth += heal;
	else
		_currentHealth = _maxHealth;
}

void Actor::DoDamage(const float & damage)
{
	if ((_currentHealth - damage) > 0.0f)
		_currentHealth -= damage;
	else
		_currentHealth = 0.0f;
}

bool Actor::IsDied()
{
	return _currentHealth <= 0.0f;
}

// ===== Actor >>>>>