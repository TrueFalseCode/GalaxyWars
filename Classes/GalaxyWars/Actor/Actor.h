#pragma once

#include <memory>
using std::shared_ptr;

#include <string>
using std::string;

#include "cocos2d.h"
using cocos2d::Scene;
using cocos2d::Sprite;
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

	Actor(const Point& positionByCenter, const float& health, const string& filename);
	~Actor();

	virtual void Update(const float& dt);

	Point GetActorPosition() const;
	Sprite* GetSprite() const;

	// При задании позиции для объекта Actor, 
	// указанная точка будет находиться в центре объекта,
	// а также в центре текстуры и объекта Sphere,
	// который отвечает за представление границ Actor'а
	void SetActorPosition(const Point & new_position);

	// Позволяет помимо позиции Actor'а задать ещё и поворот для спрайта
	void SetActorPosition(const Point & new_position, const float& spriteRotation);

	void SetSpriteTexture(const string& filename);

	bool CheckCollision(shared_ptr<const Actor> another_actor);

	float GetCurrentHealth() const;
	void DoHeal(const float & heal);
	void DoDamage(const float & damage);
	bool IsDied();

	static void SetCurrentScene(Scene* currentScene);
	static Scene* GetCurrentScene();

protected:

	// Функция позволяет смещать "тело"(объект класса Sphere) Actor'а
	void SetBodyPosition(const Point & new_position);

private:

	Point GetSpritePosition() const;

	// Функция позволяет смещать текстуру относительно Actor'а
	void SetSpritePosition(const Point & new_position);

	static Scene* _currentScene;

	// _maxHealth необходима для того, 
	// чтобы после "лечения"(DoHeal()) 
	// у объекта не оказалось больше хп, чем было
	float _maxHealth;

	float _currentHealth;
	Sphere _body;
	Sprite* _sprite;
};
// ===== Actor >>>>>