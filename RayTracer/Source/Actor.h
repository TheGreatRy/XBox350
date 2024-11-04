#pragma once
#include "Color.h"
#include "SceneObject.h"
#include "Transform.h"
#include <memory>

class Actor
{
public:
	class Actor(const Transform& transform, std::unique_ptr<SceneObject> model) :
		m_transform {transform},
		m_model{std::move(model)}
	{}

	const Transform& GetTransform() const { return m_transform; }
	std::unique_ptr<SceneObject> GetModel() { return std::move(m_model); }
	void Draw(class Framebuffer& framebuffer, const class Camera& camera);
	void SetColor(const color_t& color) { m_color = color; }

private:
	Transform m_transform;
	std::unique_ptr<SceneObject> m_model;
	color_t m_color{ 255,255,255,255 };

};
