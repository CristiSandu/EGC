/*precision highp float;
precision highp int;

uniform float distortion;
uniform float time;
uniform float speed;
uniform float swirl;
uniform vec3 baseColor;
uniform float red;
uniform float green;
uniform float blue;

const int iterations = 50;
const int swirlIterations = 6;

varying vec2 vUv;
*/
/*in vec3 color;
layout(location = 0) out vec4 out_color;*/
in vec3 frag_position;
in vec3 frag_normal;
in vec2 frag_texture;
in vec3 frag_color;
flat in int frag_ball;

/*uniform sampler2D texture_1;
uniform sampler2D texture_2;
uniform bool mix_textures;*/

layout(location = 0) out vec4 out_color;
layout(location = 1) out vec4 out_normal;
layout(location = 2) out vec3 out_texture;

void main() {

	
	out_color = vec4(1);
	
	out_color = vec4(frag_color, 1);
	out_texture = vec3(frag_texture, 1.f);
	out_normal = vec4(frag_normal, 1.f);

}