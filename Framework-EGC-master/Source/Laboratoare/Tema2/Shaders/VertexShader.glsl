/*precision highp float;
precision highp int;
uniform mat4 modelMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

attribute vec3 position;
attribute vec2 uv;

varying vec2 vUv;*/
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float Time;
uniform vec3 object_color;
uniform int combustibilBool;



layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_color;
layout(location = 2) in vec2 v_texture;
layout(location = 3) in vec3 v_normal;

out vec3 frag_position;
out vec3 frag_normal;
out vec2 frag_texture;
out vec3 frag_color;


void main() {
   
   frag_position = v_position;
   frag_normal = v_normal;
   frag_texture = v_texture;
   frag_color = object_color;
   if (combustibilBool == 0)
		gl_Position = Projection * View * Model * vec4(v_position, 1.0);
	else 
		gl_Position = vec4(v_position, 1.0);
}