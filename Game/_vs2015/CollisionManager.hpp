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
	void RegisterDynamic(DynamicBoxCollider* ball);
	void UnRegisterCollider(AbstractStaticCollider* col);
	void UnRegisterDynamic(DynamicBoxCollider* ball);
private:
	std::vector<AbstractStaticCollider*> staticColliders;
	std::vector<DynamicBoxCollider*> dynamicColliders;
};


#endif // !COLLISIONMANAGER_HPP
