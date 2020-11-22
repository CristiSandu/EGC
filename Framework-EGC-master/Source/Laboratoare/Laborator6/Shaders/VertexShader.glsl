#version 330

// TODO: get vertex attributes from each location


// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float Time;

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_color;
layout(location = 2) in vec2 v_texture;
layout(location = 3) in vec3 v_normal;

// TODO: output values to fragment shader
out vec3 frag_position;
out vec3 frag_normal;
out vec2 frag_texture;
out vec3 frag_color;

void main()
{
	
	frag_position = v_position;
	frag_normal = v_normal + vec3(cos(Time), tan(Time), sin(Time) + tan(Time));
	frag_texture = v_texture;
	frag_color = v_color;
	vec4 vec_final = vec4(v_position, 1.f) + vec4(0.f, cos(Time), tan(Time), 0.f) * 5.f;
	gl_Position = Projection * View * Model * vec_final;
}
