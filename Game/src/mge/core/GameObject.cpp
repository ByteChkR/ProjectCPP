#include <iostream>
#include "GameObject.hpp"
#include "mge/behaviours/AbstractBehaviour.hpp"

GameObject::GameObject(const std::string& pName, const glm::vec3& pPosition)
	: _name(pName), _transform(glm::translate(pPosition)), _parent(nullptr), _children(),
	_mesh(nullptr), _behaviours(), _material(nullptr), _world(nullptr)

{
}

GameObject::~GameObject()
{
	//detach all children
	std::cout << "GC running on:" << _name << std::endl;

	for (size_t i = 0; i < _behaviours.size(); i++)
	{
		delete _behaviours[i];
	}
	_behaviours.empty();
	while (_children.size() > 0) {
		GameObject* child = _children[0];
		remove(child);
		delete child;
	}

	//do not forget to delete behaviour, material, mesh, collider manually if required!
}

void GameObject::setName(const std::string& pName)
{
	_name = pName;
}

std::string GameObject::getName() const
{
	return _name;
}

void GameObject::setTransform(const glm::mat4& pTransform)
{
	_transform = pTransform;
}

const glm::mat4& GameObject::getTransform() const
{
	return _transform;
}

void GameObject::setLocalPosition(glm::vec3 pPosition)
{
	_transform[3] = glm::vec4(pPosition, 1);
}

glm::vec3 GameObject::getLocalPosition() const
{
	return glm::vec3(_transform[3]);
}

void GameObject::setMaterial(AbstractMaterial* pMaterial)
{
	_material = pMaterial;
}

AbstractMaterial * GameObject::getMaterial() const
{
	return _material;
}

void GameObject::setMesh(Mesh* pMesh)
{
	_mesh = pMesh;
}

Mesh * GameObject::getMesh() const
{
	return _mesh;
}

void GameObject::addBehaviour(AbstractBehaviour* pBehaviour)
{
	if (!ContainsBehaviour(pBehaviour->GetName()))
	{
		pBehaviour->setOwner(this);
		_behaviours.push_back(pBehaviour);
	}
}

void GameObject::RemoveBehaviour(std::string name)
{
	for (size_t i = _behaviours.size() - 1; i >= 0; i++)
	{
		if (_behaviours[i]->GetName() == name)
		{
			_behaviours.erase(_behaviours.begin() + i);
		}
	}
}

bool GameObject::ContainsBehaviour(std::string name)
{
	for each (AbstractBehaviour* b in _behaviours)
	{
		if (b->GetName() == name) return true;
	}
	return false;
}

AbstractBehaviour* GameObject::getBehaviour(std::string name) const
{
	for each (AbstractBehaviour* b in _behaviours)
	{
		if (b->GetName() == name)return b;
	}
	return nullptr;
}

void GameObject::setParent(GameObject* pParent) {
	//remove from previous parent
	if (_parent != nullptr) {
		_parent->_innerRemove(this);
	}

	//set new parent
	if (pParent != nullptr) {
		pParent->_innerAdd(this);
	}

	//if we have been detached from our parent, make sure
	//the world reference for us and all our children is set to null
	//if we have been attached to a parent, make sure
	//the world reference for us and all our children is set to our parent world reference
	//(this could still be null if the parent or parent's parent is not attached to the world)
	if (_parent == nullptr) {
		_setWorldRecursively(nullptr);
	}
	else {
		//might still not be available if our parent is not part of the world
		_setWorldRecursively(_parent->_world);
	}
}

void GameObject::FireCollision(GameObject* other)
{
	for (size_t i = 0; i < _behaviours.size(); i++)
	{
		_behaviours[i]->OnCollision(other);
	}
}

GameObject* GameObject::Clone()
{
	GameObject* gobj = new GameObject(_name+ "(CLONE)");
	gobj->setTransform(glm::mat4(_transform));
	gobj->setParent(_parent);
	gobj->setMesh(_mesh);
	gobj->setMaterial(_material);
	
	for each (GameObject* child in _children)
	{
		gobj->add(child->Clone());
	}
	for each (AbstractBehaviour* beh in _behaviours)
	{
		gobj->addBehaviour(beh->Clone());
	}



}

void GameObject::_innerRemove(GameObject* pChild) {
	for (auto i = _children.begin(); i != _children.end(); ++i) {
		if (*i == pChild) {
			_children.erase(i);
			pChild->_parent = nullptr;
			return;
		}
	}
}

void GameObject::_innerAdd(GameObject* pChild)
{
	_children.push_back(pChild);
	pChild->_parent = this;
}

void GameObject::add(GameObject* pChild) {
	pChild->setParent(this);
}

void GameObject::remove(GameObject* pChild) {
	pChild->setParent(nullptr);
}

GameObject* GameObject::getParent() const {
	return _parent;
}

////////////

//costly operation, use with care
glm::vec3 GameObject::getWorldPosition() const
{
	return glm::vec3(getWorldTransform()[3]);
}

//costly operation, use with care
glm::mat4 GameObject::getWorldTransform() const
{
	if (_parent == nullptr) return _transform;
	else return _parent->getWorldTransform() * _transform;
}

////////////

void GameObject::translate(glm::vec3 pTranslation)
{
	setTransform(glm::translate(_transform, pTranslation));
}

void GameObject::scale(glm::vec3 pScale)
{
	setTransform(glm::scale(_transform, pScale));
}

void GameObject::rotate(float pAngle, glm::vec3 pAxis)
{
	setTransform(glm::rotate(_transform, pAngle, pAxis));
}

void GameObject::update(float pStep)
{
	//make sure behaviour is updated after worldtransform is set
	if (_behaviours.size() > 0) {
		for each (AbstractBehaviour* b in _behaviours)
		{
			b->update(pStep);
		}
	}

	for (int i = _children.size() - 1; i >= 0; --i) {
		_children[i]->update(pStep);
	}
}

void GameObject::_setWorldRecursively(World* pWorld) {
	_world = pWorld;

	for (int i = _children.size() - 1; i >= 0; --i) {
		_children[i]->_setWorldRecursively(pWorld);
	}
}

int GameObject::getChildCount() const {
	return _children.size();
}

GameObject* GameObject::getChildAt(int pIndex) const {
	return _children[pIndex];
}

