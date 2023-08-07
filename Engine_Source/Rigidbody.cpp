#include "Rigidbody.h"
#include "RokaTime.h"
#include "Application.h"
#include "Transform.h"
extern roka::Application application;
namespace roka
{
	Rigidbody::Rigidbody() :Component(EComponentType::Rigidbody)
		, mTime(0.0f)
		, mMass(1.0f)
		, mAccelation(Vector2::Zero)
		, mVelocity(Vector2::Zero)
		, mForce(Vector2::Zero)
		, mbGround(true)
		, mbGravity(false)
		, mDecreaseGravity(1.0f)
		, mIncreaseGravity(2.0f)
		, mbFall(false)
	{
		mLimitedVelocity.x = 200.0f;
		mLimitedVelocity.y = 10000.0f;
		mGravity = Vector2(0.0f, 980.0f);
		mFriction = 100.0f;
		Time::RegisterEvent(L"RgidFallCompEvent", 1.5, &Rigidbody::CompleteFallEvent, this);
	}
	Rigidbody::Rigidbody(const Rigidbody& ref) :Component(ref)
	{
		mTime = ref.mTime;
		mMass = ref.mMass;
		mAccelation = ref.mAccelation;
		mVelocity = ref.mVelocity;
		mForce = ref.mForce;
		mbGravity = ref.mbGravity;
		mbGround = ref.mbGround;
		mLimitedVelocity = ref.mLimitedVelocity;
		mGravity = ref.mGravity;
		mFriction = ref.mFriction;
		mDecreaseGravity = ref.mDecreaseGravity;
		mIncreaseGravity = ref.mIncreaseGravity;
		mbFall = ref.mbFall;
		Time::RegisterEvent(L"RgidFallCompEvent", 1.5, &Rigidbody::CompleteFallEvent, this);
	}
	Rigidbody::~Rigidbody()
	{

	}
	void Rigidbody::Copy(Component* src)
	{
		Rigidbody* source = dynamic_cast<Rigidbody*>(src);
		mTime = source->mTime;
		mMass = source->mMass;
		mAccelation = source->mAccelation;
		mVelocity = source->mVelocity;
		mForce = source->mForce;
		mbGravity = source->mbGravity;
		mbGround = source->mbGround;
		mLimitedVelocity = source->mLimitedVelocity;
		mGravity = source->mGravity;
		mFriction = source->mFriction;
		mDecreaseGravity = source->mDecreaseGravity;
		mIncreaseGravity = source->mIncreaseGravity;
		mbFall = source->mbFall;
		Time::RegisterEvent(L"RgidFallCompEvent", 1.5, &Rigidbody::CompleteFallEvent, this);
	}
	void Rigidbody::Initialize()
	{
		
	}
	void Rigidbody::Update()
	{
		Vector2 resolution = { (float)application.GetWidth(),(float)application.GetHeight() };

		Vector2 mass = { mMass ,mMass };
		Vector2 friction = { mFriction / resolution.x, mFriction / resolution.y };

		Vector2 force = { mForce.x / resolution.x ,mForce.y /= resolution.y };
		Vector2 accelation = mForce / mass;

		Vector2 gravity = mGravity / resolution;

		Vector2 limit_velocity = mLimitedVelocity / resolution;


		mVelocity -= accelation * Time::DeltaTime();
		if (mbGravity)
		{
			if (mbGround)
			{
				Vector2 gravity2= mGravity;
				gravity2.Normalize();

				float dot = mVelocity.Dot(gravity);
				mVelocity += gravity2 * dot;
			}
			else
			{
				if (mbFall)
				{
					mVelocity.y = -0.1f;
				}
				else
				{
 					DecreaseGravity(false);
				}
				mVelocity -= gravity * mIncreaseGravity * mDecreaseGravity * Time::DeltaTime();
			}
		}
		else
		{

		} 

		// 중력가속도 최대 속도 제한
		gravity.Normalize();
		float dot = mVelocity.Dot(gravity);
		gravity = gravity * dot;

		Vector2 sideVelocity = mVelocity - gravity;
		if (limit_velocity.y < gravity.Length())
		{
			gravity *= limit_velocity.y;
		}

		if (limit_velocity.x < sideVelocity.Length())
		{
			sideVelocity.Normalize();
			sideVelocity *= limit_velocity.x;
		}

		// 마찰력 조건 ( 적용된 힘이 없고, 속도가 0이 아님)
		if (!(mVelocity == Vector2::Zero))
		{
			//속도에 반대방향으로 마찰력이 적용된다.
			Vector2 friction2 = -mVelocity;
			friction2.Normalize();
			friction2 = friction2 * friction * mass * Time::DeltaTime();

			//마찰력으로 인한 속도 감소는 현재 속도보다 큰 경우
			if (mbGround)
			{
				if (mVelocity.Length() < friction.Length())
				{
					mVelocity = Vector2::Zero;
				}
				else
				{
					mVelocity -= friction2;
				}
			}
		}

		std::shared_ptr<Transform> tf = owner->GetComponent<Transform>();
		Vector3 pos = tf->position;
		pos = pos + mVelocity * Time::DeltaTime();
		if (mbGround)
		{
			mVelocity = Vector2::Zero;
		}
	
		tf->position = pos;
		
		mForce = Vector2::Zero;
	}
	void Rigidbody::LateUpdate()
	{

	}
	void Rigidbody::Render()
	{

	}

	void Rigidbody::SetVelocity(Vector2 velocity)
	{
		Vector2 resolution = Vector2{ (float)application.GetWidth(),(float)application.GetHeight() };
		mVelocity = velocity / resolution;
	}

	void Rigidbody::DecreaseGravity(bool flag)
	{
		if (flag)
		{
			mbFall = true;
			mDecreaseGravity = 0.1f;
			Time::ActiveEvent(L"RgidFallCompEvent",this);
		}
		else
		{
			mDecreaseGravity = 1.0f;
		}
	}



	void Rigidbody::CompleteFallEvent(void* ptr)
	{
		Rigidbody* rigid = reinterpret_cast<Rigidbody*>(ptr);
		rigid->mbFall = false;
		rigid->mVelocity.y = -1.0f;
	}

}