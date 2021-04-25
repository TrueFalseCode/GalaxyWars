
#include "Projectile.h"

Projectile::Projectile(const Point & start,
					   const Point & finish,
					   const float& health,
					   const float & damage,
					   const string& filename,
					   const float & speedCoefficient) : Actor(start, health, filename),
													    _speedCoefficient(speedCoefficient),
														_finishPoint(finish),
														_positionNode(nullptr)
{
	auto currentScene = Actor::GetCurrentScene();
	if (currentScene)
	{
		_positionNode = Node::create();

		if (_positionNode)
		{
			_positionNode->setPosition(this->GetActorPosition());
			_positionNode->runAction(MoveTo::create(1 / _speedCoefficient, finish));

			currentScene->addChild(_positionNode);
		}
	}
}

Projectile::~Projectile()
{
	auto currentScene = Actor::GetCurrentScene();
	if (currentScene && _positionNode)
	{
		currentScene->removeChild(_positionNode);
	}
}

void Projectile::Update(const float & dt)
{
	if (_positionNode)
	{
		Point nextPosition = _positionNode->getPosition();// = _spline.getGlobalFrame(std::clamp(0.0f, 1.0f, _timer / 6.0f));

		// Как только снаряд достиг конечной точки, 
		// ему наносится урон, равный его здоровью,
		// чтобы обозначить, что он должен быть уничтожен.
		//if (nextPosition == _spline.GetKey(_spline.GetKeysCount() - 1))
		if (nextPosition == _finishPoint)
		{
			DoDamage(GetCurrentHealth());
		}
		else
		{
			SetActorPosition(nextPosition);
		}
	}
}
