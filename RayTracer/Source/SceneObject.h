#pragma once
#include "Ray.h"
#include <memory>

class SceneObject 
{
public:
	//SceneObject() = default;
	SceneObject(std::shared_ptr<class Material> material) :
		m_material{ material }
	{}
	virtual bool Hit(const ray_t& ray, raycastHit_t& raycastHit, float minDistance, float maxDistance) = 0;
	std::weak_ptr<class Material> GetMaterial() { return m_material; }

private:
	std::shared_ptr<class Material> m_material;
};