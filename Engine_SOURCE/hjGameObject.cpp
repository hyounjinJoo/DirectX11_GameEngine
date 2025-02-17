#include "pch.h"
#include "hjGameObject.h"

namespace hj
{
	GameObject::GameObject()
		: mState(eState::Active)
		, mLayerType(eLayerType::None)
		, mbDontDestroy(false)
	{
		mComponents.resize((UINT)eComponentType::End);
		AddComponent(new Transform());
	}

	GameObject::GameObject(const GameObject& obj)
	{
		mComponents.resize((UINT)eComponentType::End);
		mLayerType = obj.mLayerType;
		mbDontDestroy = obj.mbDontDestroy;
		mState = obj.mState;

		for (Component* comp : obj.mComponents)
		{
			if (comp == nullptr)
				continue;

			AddComponent(comp->Clone());
		}

		for (Component* scrComp : obj.mScripts)
		{
			if (scrComp == nullptr)
				continue;

			AddComponent(scrComp->Clone());
		}
	}

	GameObject::~GameObject()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			delete comp;
			comp = nullptr;
		}

		for (Component* scrComp : mScripts)
		{
			if (scrComp == nullptr)
				continue;

			delete scrComp;
			scrComp = nullptr;
		}
	}

	void GameObject::Initialize()
	{
	}

	void GameObject::Update()
	{
		if (eState::Active != mState)
			return;

		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->Update();
		}

		for (Component* script : mScripts)
		{
			if (script == nullptr)
				continue;

			script->Update();
		}
	}
	void GameObject::FixedUpdate()
	{
		if (eState::Active != mState)
			return;

		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->FixedUpdate();
		}

		for (Component* script : mScripts)
		{
			if (script == nullptr)
				continue;

			script->FixedUpdate();
		}
	}
	void GameObject::Render()
	{
		if (eState::Active != mState)
			return;

		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->Render();
		}

		for (Component* script : mScripts)
		{
			if (script == nullptr)
				continue;

			script->Render();
		}
	}

	GameObject* GameObject::Clone() const
	{
		return new GameObject(*this);
	}

	void GameObject::AddComponent(Component* comp)
	{
		eComponentType order = comp->GetOrder();

		if (order != eComponentType::Script)
		{
			mComponents[(UINT)order] = comp;
			mComponents[(UINT)order]->SetOwner(this);
		}
		else
		{
			mScripts.push_back(dynamic_cast<Script*>(comp));
			comp->SetOwner(this);
		}

		comp->Initialize();
	}
}