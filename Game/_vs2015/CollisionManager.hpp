#ifndef COLLISIONMANAGER_HPP
#define COLLISIONMANAGER_HPP

#include <vector>
#include "AbstractStaticCollider.hpp";
#include "DynamicSphereCollider.hpp"
class CollisionManager
{

public:
	void Update(float pTime);
	void RegisterCollider(AbstractStaticCollider* col);
	void RegisterDynamic(DynamicSphereCollider* ball);
	void UnRegisterCollider(AbstractStaticCollider* col);
	void UnRegisterDynamic(DynamicSphereCollider* ball);
private:
	std::vector<AbstractStaticCollider* > staticColliders;
	std::vector<DynamicSphereCollider*> dynamicColliders;
};


#endif // !COLLISIONMANAGER_HPP
