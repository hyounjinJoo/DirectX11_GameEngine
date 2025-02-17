#pragma once
#include "hjComponent.h"

using namespace hj::math;
namespace hj
{
	class RigidBody : public Component
	{
	public:
		RigidBody();
		RigidBody(const RigidBody& rigidBody);
		virtual ~RigidBody();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual Component* Clone() const override;
	public:
		void AddForce(Vector2 force);
		void SetMass(float mass) { mMass = mass; }
		void SetGround(bool isGround) { mbGround = isGround; }
		bool IsGround() { return mbGround; }
		void SetPathThroughFloor(bool isOnFloor) { mbOnPathThroughFloor = isOnFloor; }
		bool IsOnPathThroughFloor() { return mbOnPathThroughFloor; }

		Vector2 GetVelocity() { return mVelocity; }
		Vector2 GetForce() { return mForce; }
		void SetVelocity(Vector2 velocity) { mVelocity = velocity; }
		void ClearVelocityY() { mVelocity.y = 0.f; }
		void ClearVelocityX() { mVelocity.x = 0.f; }

		void OnFriction(bool isOn) { mbOnFriction = isOn; }
		void OnHorizonAccelMove(bool isOn) { mbHorizonAccelMove = isOn; }

		eMoveDir GetMoveDir() { return mMoveDir; }

	private:
		// 힘과 마찰력을 이용한 이동
		float mMass;
		bool mbOnFriction;
		float mFriction;

		Vector2 mForce;
		Vector2 mVelocity;
		Vector2 mAccelation;
		float mbHorizonAccelMove;

		// 중력 이용한 점프
		Vector2 mGravity;
		bool mbGround;
		bool mbOnPathThroughFloor;

		Vector2 mLimitVelocity;

		eMoveDir mMoveDir;
	};
}