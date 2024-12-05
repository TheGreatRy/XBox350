#include "FragmentShader.h"
#include "Shader.h"

color4_t FragmentShader::Process(const fragment_input_t& fragment)
{
	glm::vec3 light_position = Shader::uniforms.light.position;
	glm::vec3 light_dir = Shader::uniforms.light.direction;

	light_position = Shader::uniforms.view * glm::vec4{ light_position, 1 };
	light_dir = Shader::uniforms.view * glm::vec4{ light_dir, 0 };
	light_dir = glm::normalize(-Shader::uniforms.light.direction);
	light_dir = glm::normalize(light_position - fragment.position);

	//Light intensity = dot(normalized light dir, vertex normal)
	//Clamp to prevent negatives
	float intensity = std::max(0.0f, glm::dot(light_dir, fragment.normal));

	color3_t diffuse = Shader::uniforms.light.color * intensity;
	color3_t specular{ 0 };

	if (intensity > 0)
	{
		glm::vec3 reflection = glm::reflect(-light_dir, fragment.normal); // Compute reflection vector
		glm::vec3 view_direction = glm::normalize(-fragment.position); // Calculate view direction
		intensity = std::max(glm::dot(reflection, view_direction), 0.0f); // Compute intensity of reflection
		intensity = std::pow(intensity, Shader::uniforms.material.shininess); // Apply shininess factor
		specular = color3_t(Shader::uniforms.material.specular * intensity); // Scale specular by intensity and material property
	}
	color3_t color = ((Shader::uniforms.ambient + diffuse) * Shader::uniforms.material.albedo) + specular;

	return { color.r, color.g, color.b, 1 };
}


