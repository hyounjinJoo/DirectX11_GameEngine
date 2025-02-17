#pragma once

#include "hjMath.h"
#include "hjEntity.h"

using namespace hj::enums;
namespace hj
{
	class GameObject;
	class Component : public Entity
	{
	public:
		Component(eComponentType type);
		virtual ~Component();


		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void Render() = 0;

		virtual Component* Clone() const = 0;

	public:
		eComponentType GetOrder() const { return mType; }

		GameObject* GetOwner() { return mOwner; }
		void SetOwner(GameObject* owner) { mOwner = owner; }

	private:
		const eComponentType mType;
		GameObject* mOwner;

	public:
		void DeActivate() { mbActive = false; }
		void Activate() { mbActive = true; }
		bool IsActive() { return mbActive; }

	protected:
		bool mbActive = true;
	};
}