#include "Tracer.h"
#include "Scene.h"
#include "Material.h"
#include "MathUtils.h"

color3_t Tracer::Trace(Scene& scene, const ray_t& ray)
{
	for (auto& object : scene.m_objects)
	{
		if (object->Hit(ray))
		{
			return object->GetMaterial().lock()->GetColor();
		}
	}

	color3_t color{ 0 };
	glm::vec3 direction = glm::normalize(ray.direction);
	float t = direction.y;
	color = Lerp(color3_t{ 1,1,1 }, color3_t{ 0.5f, 0.7f, 0.1f }, t);
	
	return color;
}