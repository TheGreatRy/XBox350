#include "VertexShader.h"

VertexShader::uniforms_t VertexShader::uniforms =
{
	glm::mat4{ 1 },
	glm::mat4{ 1 },
	glm::mat4{ 1 }, 
	color3_t{ 1 }
};

//Point Light : Uses the light’s position for calculations.
//Calculate the direction vector from the vertex position to the light's position.
//Put the light position into view space by multiplying the position by the view vector.
//Normalize the direction vector to ensure it has a length of 1.

//Directional Light : Ignores position and uses a fixed direction.
//Use the light's direction vector as the direction of the light.
//Put the light direction into view space by multiplying the direction by the view vector.
//Normalize the light direction vector to ensure consistent calculations.You will need to flip the light direction.

void VertexShader::Process(const vertex_t& ivertex, vertex_output_t& overtex)
{
	glm::mat4 mvp = uniforms.projection * uniforms.view * uniforms.model;
	overtex.position = mvp * glm::vec4{ ivertex.position, 1 };
	glm::mat4 mv = uniforms.view * uniforms.model;
	overtex.normal = glm::normalize(glm::mat3{ mv } * ivertex.normal);

	glm::vec3 light_position = uniforms.light.position;
	glm::vec3 light_dir = uniforms.light.direction;
	
	//Point Light
	light_position = uniforms.view * glm::vec4{ light_position, 1 };

	//Directional Light
	light_dir = uniforms.view * glm::vec4{ light_dir, 0 };
	light_dir = glm::normalize(-uniforms.light.direction);

	glm::vec3 vposition = mv * glm::vec4{ ivertex.position, 1 };
	light_dir = glm::normalize(light_position - vposition);
	
	

	//Light intensity = dot(normalized light dir, vertex normal)
	//Clamp to prevent negatives
	float intensity = std::max(0.0f, glm::dot(light_dir, overtex.normal));

	color3_t diffuse = uniforms.light.color * intensity;
	overtex.color = uniforms.ambient + diffuse;
}
