#include "Actor.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Scene.h"
#include "Tracer.h"

void Actor::Draw(Framebuffer& framebuffer, const Camera& camera)
{
	//for (int y = 0; y < framebuffer.m_height; y++)
	//{
	//	for (int x = 0; x < framebuffer.m_width; x++)
	//	{
	//		
	//		color3_t color{ 0 };
	//			glm::vec2 pixel{ x, y };
	//			// add a random value to the pixel (0-1)
	//			pixel += glm::vec2{ 0.0f, 1.0f };
	//			// normalize the pixel value
	//			glm::vec2 point = pixel / glm::vec2{ framebuffer.m_width, framebuffer.m_height };
	//			// flip the y value (bottom = 0, top = 1)
	//			point.y = 1 - point.y;

	//			ray_t ray = camera.GetRay(point);
	//			color += Tracer::Trace(scene, ray, 0.001f, 100.0f, depth);
	//			framebuffer.DrawPoint(x, y, ColorConvert(color));
	//	}
	//}
}