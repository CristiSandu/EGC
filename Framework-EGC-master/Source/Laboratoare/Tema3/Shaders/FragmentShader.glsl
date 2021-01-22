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
uniform sampler2D texture_1;
uniform sampler2D texture_2;
uniform bool mix_textures;

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
	vec4 colour1 = texture2D(texture_1, frag_texture);
	vec4 colour2 = texture2D(texture_2, frag_texture);
	if (mix_textures == true){
		out_color = mix(colour1,colour2,.2f);
		//out_color = mix(vec4(frag_color,1), out_color,.2f);
	}else{ 
		//out_color = vec4(frag_color,1);
		out_color = mix (colour1,vec4(frag_color,1),.5f);

	}
	out_texture = vec3(frag_texture, 1.f);
	out_normal = vec4(frag_normal, 1.f);

}