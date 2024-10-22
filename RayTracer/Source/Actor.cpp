#include "Actor.h"

void Actor::Draw(Framebuffer& frameBuffer, const Camera& camera)
{
	m_model->SetColor(m_color);
	m_model->Draw(frameBuffer, m_transform.GetMatrix(), camera);
}
