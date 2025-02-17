#pragma once
#include "hjComponent.h"
#include "hjAnimation.h"

namespace hj
{
	class Animator :
		public Component
	{
	public:
		struct Events
		{
			struct Event
			{
				void operator=(std::function<void()> func)
				{
					mEvent = std::move(func);
				}
				void operator()()
				{
					if (mEvent)
						mEvent();
				}

				std::function<void()> mEvent;
			};

			Event mStartEvent;
			Event mCompleteEvent;
			Event mEndEvent;

			std::vector<Event> mEvents;

			Events()
				: mStartEvent()
				, mCompleteEvent()
				, mEndEvent()
			{
			}
			Events(const Events& other)
				: mStartEvent(other.mStartEvent),
				mCompleteEvent(other.mCompleteEvent),
				mEndEvent(other.mEndEvent),
				mEvents(other.mEvents)
			{
			}

			Events* Clone() { return new Events(*this); }
		};

		Animator();
		Animator(const Animator& animator);
		virtual ~Animator();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual Component* Clone() const override;

	public:
		void SetPause(bool pause)
		{
			if (!mActiveAnimation)
			{
				return;
			}

			mActiveAnimation->SetPause(pause);
		}

		bool IsPause() 
		{
			bool result = false;
			if (mActiveAnimation)
			{
				result = mActiveAnimation->IsPause();
			}

			return result; 
		}

	public:
		bool IsInverse()
		{
			if (!mActiveAnimation)
				return false;

			return mActiveAnimation->IsInverse();
		}
		bool Create(const std::wstring& name, std::shared_ptr<Texture> atlas
			, Vector2 leftTop, Vector2 size, Vector2 offset
			, UINT spriteLength, float duration, bool reversePlay = false);

		bool Create(const std::wstring& name, std::shared_ptr<Texture> atlas
			, const std::vector<Animation::Sprite>& sprite, Vector2 canvasSize, bool reversePlay);

		bool Create(const std::string& name, std::shared_ptr<Texture> atlas
			, Vector2 leftTop, Vector2 size, Vector2 offset
			, UINT spriteLength, float duration, bool reversePlay = false);

		bool Create(const std::string& name, std::shared_ptr<Texture> atlas
			, const std::vector<Animation::Sprite>& sprite, Vector2 canvasSize, bool reversePlay);

		bool AddAnimation(Animation* const anim);

		Animation* GetCurrentAnimation() const
		{
			if (mActiveAnimation)
				return mActiveAnimation;

			return nullptr;
		}

		Animation* FindAnimation(const std::wstring& name);
		Events* FindEvents(const std::wstring& name);
		void Play(const std::wstring& name, bool loop = true);
		void Play(const std::string& name, bool loop = true);
		void Inverse(bool inverse);
		void Binds();
		void Clear();

		void ChangePlayDuration(float duration) { mActiveAnimation->ChangePlayDuration(duration); }

		std::function<void()>& GetStartEvent(const std::wstring& name);
		std::function<void()>& GetCompleteEvent(const std::wstring& name);
		std::function<void()>& GetEndEvent(const std::wstring& name);
		std::function<void()>& GetEvent(const std::wstring& name, UINT index);

	private:
		std::map<std::wstring, Animation*> mAnimations;
		std::map<std::wstring, Events*> mEvents;
		Animation* mActiveAnimation;
		bool mbLoop;
	};
}