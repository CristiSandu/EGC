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

uniform vec3 object_color;
out vec4 color;


void main() {
    color = vec4(1);
	color = vec4(object_color,1.0);
	vec4 pos4 = Projection * View * Model * vec4(pos, 1.0);
	gl_Position = pos4;
}