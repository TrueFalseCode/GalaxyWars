#pragma once

#include <memory>
using std::shared_ptr;

#include "cocos2d.h"
using cocos2d::Point;

// <<<<< Sphere =====
/* Класс Sphere предназначен для определения границ игрового объекта,
* представленного в виде сферы.
* В данном классе присутствуют методы, позволяющие устанавливать наличие
* столкновений с другими объектами.
*/
class Sphere
{
public:

	Sphere();
	Sphere(const Point& centerPosition, const float& radius);

	Point GetPosition() const;
	void SetPosition(const Point& new_position);

	float GetRadius() const;
	void SetRadius(const float& new_radius);

	// Функция возвращает true, если возникло столкновение(соприкосновение) с другим объектом
	bool CheckCollision(const Sphere& another_sphere);

	// Функция возвращает true, если возникло столкновение(соприкосновение) с заданной точкой
	bool CheckCollision(const Point& point);

private:

	// Функция возвращает расстояние между двумя заданными точками
	float GetDistance(const Point& A, const Point& B);

	Point _centerPosition;
	float _radius;
};
// ===== Sphere >>>>>

// <<<<< Actor =====
/* Класс Actor является базовым классом для всех игровых объектов,
* отображающихся на игровом экране. Он позволяет использовать единый
* интерфейс для манипуляции игровымы объектами, их отображения и
* взаимодействия с другими объектами.
*/
class Actor
{
public:

	Actor(const Point& positionByCenter, const float& health, Render::Texture* texture);

	virtual void Draw(Render::RenderDeviceInterface& device);
	virtual void Update(const float& dt);

	Point GetActorPosition() const;
	Point GetTexturePosition() const;
	Render::Texture* GetTexture() const;

	// При задании позиции для объекта Actor, 
	// указанная точка будет находиться в центре объекта,
	// а также в центре текстуры и объекта Sphere,
	// который отвечает за представление границ Actor'а
	void SetActorPosition(const Point & new_position);

	// Функция позволяет смещать текстуру относительно Actor'а
	void SetTexturePosition(const Point & new_position);

	void SetTexture(Render::Texture* new_texture);

	bool CheckCollision(shared_ptr<const Actor> another_actor);

	float GetCurrentHealth() const;
	void DoHeal(const float & heal);
	void DoDamage(const float & damage);
	bool IsDied();

protected:

	// Функция позволяет смещать "тело"(объект класса Sphere) Actor'а
	void SetBodyPosition(const Point & new_position);

	void DrawTexture();

	float _timer;

private:

	// _maxHealth необходима для того, 
	// чтобы после "лечения"(DoHeal()) 
	// у объекта не оказалось больше хп, чем было
	float _maxHealth;

	float _currentHealth;
	Sphere _body;
	Point _texturePosition;
	Render::Texture* _texture;
};
// ===== Actor >>>>>