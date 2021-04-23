
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

Actor::Actor(const Point& centerPosition, const float& health, Render::Texture * texture) : _maxHealth(health), _currentHealth(health), _texture(texture), _timer(0.0f)
{
	SetActorPosition(centerPosition);

	// Если задана текстура, то диаметр сферы, 
	// которая определяет границы Actor'а
	// будет равен размеру большей стороны текстуры
	if (_texture)
	{
		float radius_tmp;
		int textureW = _texture->Width();
		int textureH = _texture->Height();

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

void Actor::Draw(Render::RenderDeviceInterface& device)
{
	device.PushMatrix();
	device.MatrixTranslate(GetTexturePosition());
	DrawTexture();
	device.PopMatrix();
}

void Actor::Update(const float& dt) {}

Point Actor::GetActorPosition() const
{
	return _body.GetPosition();
}

Point Actor::GetTexturePosition() const
{
	return _texturePosition;
}

Render::Texture * Actor::GetTexture() const
{
	return _texture;
}

void Actor::SetActorPosition(const Point & new_position)
{
	SetBodyPosition(new_position);

	if (_texture)
	{
		float X = new_position.x - (_texture->Width() / 2);
		float Y = new_position.y - (_texture->Height() / 2);

		SetTexturePosition(Point(X, Y));
	}
	else
	{
		SetTexturePosition(new_position);
	}
}

void Actor::SetTexturePosition(const Point & new_position)
{
	_texturePosition = new_position;
}

void Actor::SetBodyPosition(const Point & new_position)
{
	_body.SetPosition(new_position);
}

void Actor::SetTexture(Render::Texture * new_texture)
{
		_texture = new_texture;
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

void Actor::DrawTexture()
{
	if (_texture)
	{
		_texture->Draw();
	}
}

// ===== Actor >>>>>