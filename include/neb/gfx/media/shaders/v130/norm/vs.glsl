#version 130

struct Light
{
	vec4 position;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec3 spot_direction;
	float spot_cutoff;
	float atten_const;
	float atten_linear;
	float atten_quad;
	float spot_exponent;
	float spot_light_cos_cutoff;
};

struct Material
{
	vec4 diffuse;
	vec4 specular;
	vec4 ambient;
	vec4 emission;
	float shininess;
};

out vec4 vs_P;
out vec3 vs_N;
out vec2 vs_texcoor;
out mat3 vs_norm_trans;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

in vec4 position; // 0
in vec3 normal; // 1
in vec2 texcoor; // 2
in mat3 tangent; // 3
in mat3 binormal; // 4

void main(void)
{
	mat4 modelview = view * model;
	
	// Calculate view-space coordinate
	vs_P = modelview * position;
	
	// Calculate normal in view-space
	vs_N = normalize(mat3(modelview) * normal);
	vs_norm_trans = mat3(modelview) * norm_trans;
	
	// texture coordinate
	vs_texcoor = texcoor;

	
	// Calculate the clip-space position of each vertex
	gl_Position = proj * vs_P;
}


