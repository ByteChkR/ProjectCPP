#include "CollisionManager.hpp"
#include "AbstractStaticCollider.hpp"
#include "DynamicBoxCollider.hpp"

void CollisionManager::Update(float time)
{
	for each (AbstractStaticCollider* col in staticColliders)
	{ 
		if (!col->IsEnabled())continue;
		for each (DynamicBoxCollider* box in dynamicColliders)
		{
			bool isCollision = col->IsCollision(box);
			if (isCollision) 
			{
				box->FireCollision(col->GetOwner());
				//col->GetOwner()->FireCollision(box->getOwner()); //Maybe later. Enables that obstacles can receive the collision event as well.
			}
		}
	}
}

void CollisionManager::RegisterCollider(AbstractStaticCollider* col)
{
	staticColliders.push_back(col);
}

void CollisionManager::RegisterDynamic(DynamicBoxCollider* box)
{
	dynamicColliders.push_back(box);
}

void CollisionManager::UnRegisterCollider(AbstractStaticCollider* col)
{
	for (int i = staticColliders.size()-1; i >= 0; i--)
	{
		if (col == staticColliders[i])
		{
			staticColliders.erase(staticColliders.begin() + i);
		}
	}
}

void CollisionManager::UnRegisterDynamic(DynamicBoxCollider* box)
{
	for (int i = dynamicColliders.size()-1; i >= 0; i--)
	{
		if (box == dynamicColliders[i])
		{
			dynamicColliders.erase(dynamicColliders.begin() + i);
		}
	}
}
