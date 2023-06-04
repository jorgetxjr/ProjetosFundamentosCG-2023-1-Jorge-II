// C�digo fonte do Vertex Shader (em GLSL)
#version 450

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec4 finalColor;

void main()
{
	//...pode ter mais linhas de c�digo aqui!
	gl_Position = projection * view * model * vec4(position, 1.0);
	//gl_Position = projection  * model * vec4(position, 1.0);
	finalColor = vec4(color, 1.0);
}
