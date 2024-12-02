#pragma once
#include "Model.h"
#include "Transform.h"
#include <memory>
class Actor
{
public:
	class Actor(const Transform& transform, std::shared_ptr<Model> model) :
		m_transform {transform},
		m_model{model}
	{}

	Transform& GetTransform() { return m_transform; }
	void Draw();

private:
	Transform m_transform;
	std::shared_ptr<Model> m_model;
};
