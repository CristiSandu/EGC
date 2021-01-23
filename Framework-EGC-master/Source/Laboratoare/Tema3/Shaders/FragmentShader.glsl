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

uniform vec3 light_direction;
uniform vec3 light_position;

uniform vec3 light_direction_spot;
uniform vec3 light_position_spot;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;
uniform float cut_off_angle;

in vec3 frag_position;
in vec3 frag_normal;
in vec2 frag_texture;
in vec3 frag_color;

in vec3 world_position;
in vec3 world_normal;

flat in int frag_ball;

/*uniform sampler2D texture_1;
uniform sampler2D texture_2;
uniform bool mix_textures;*/

layout(location = 0) out vec4 out_color;
layout(location = 1) out vec4 out_normal;
layout(location = 2) out vec3 out_texture;

void main() {

	vec3 N = normalize(world_normal);
	vec3 L = normalize(light_position - world_position);
	vec3 L_spot = normalize(light_position_spot - world_position);
	vec3 V = normalize(eye_position - world_position);

	vec3 H = normalize(L + V);
	vec3 H_spot = normalize(L_spot + V);

	vec3 R = normalize(reflect(L, world_normal));
	
	float ambient_light = 0.25;
	
	// TODO: compute diffuse light component
	float diffuse_light = 0;
	float diffuse_light_spot = 0;

	diffuse_light = material_kd * max(dot(normalize(N), L), 10.f);
	diffuse_light_spot = material_kd * max(dot(normalize(N), L_spot), 1.f);

	// TODO: compute specular light component
	float specular_light = 0;
	float specular_light_spot = 0;

	if (diffuse_light > 0)
	{
		specular_light = material_ks * pow(max(dot(N, H), 0), material_shininess);
	}

	if (diffuse_light_spot > 0)
	{
		specular_light_spot = material_ks * pow(max(dot(N, H_spot), 0), material_shininess);
	}
	float light = 0.f;
	// TODO: compute light
	float light_spot = 0.f;


	float cut_off_rad		= radians(cut_off_angle);
	float spot_light		= dot(-L_spot, light_direction_spot);
	float spot_light_limit	= cos(cut_off_rad);
		
	if (spot_light > spot_light_limit)
	{	 
		// Quadratic attenuation
		float linear_att		= (spot_light - spot_light_limit) / (1.f - spot_light_limit);
		float light_att_factor	= linear_att * linear_att;
		light_spot				= ambient_light + light_att_factor * (diffuse_light_spot + specular_light_spot);
	} else
	{
		light_spot = ambient_light;  // There is no spot light, but there is light from other objects
	}



	float d						= distance(light_position, world_position);
	float attenuation_factor	= 30.f / max(d * d, 32.f);
	light						= ambient_light + attenuation_factor * (diffuse_light + specular_light);
	
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

	out_color =( out_color  ) * (light * vec4(0,1,0,1) + light_spot *( vec4(1,0,0,1) *vec4(1,1,1,1))); 
	//out_texture = vec3(frag_texture, 1.f);
	//out_normal = vec4(frag_normal, 1.f);

}