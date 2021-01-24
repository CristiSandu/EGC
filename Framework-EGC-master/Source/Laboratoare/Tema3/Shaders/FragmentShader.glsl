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


*/
uniform sampler2D texture_1;
uniform sampler2D texture_2;
uniform bool mix_textures;
uniform bool only_spot;

uniform bool only_punct;


uniform vec3 light_direction;
uniform vec3 light_position;

uniform vec3 light_direction_spot;
uniform vec3 light_position_spot;

uniform vec3 light_direction_spot_1;
uniform vec3 light_position_spot_1;

uniform vec3 light_direction_spot_2;
uniform vec3 light_position_spot_2;

uniform vec3 light_direction_spot_3;
uniform vec3 light_position_spot_3;

uniform vec3 light_direction_spot_4;
uniform vec3 light_position_spot_4;

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

flat in float frag_ball;

/*uniform sampler2D texture_1;
uniform sampler2D texture_2;
uniform bool mix_textures;*/

layout(location = 0) out vec4 out_color;
layout(location = 1) out vec4 out_normal;
layout(location = 2) out vec3 out_texture;

float computSpotLight(vec3 light_direction_spot, vec3 light_position_spot, vec3 world_position,vec3 V, vec3 N, float angel)
{
	float light = 0.f;
	vec3 L_spot = normalize(light_position_spot - world_position);
	vec3 H_spot = normalize(L_spot + V);

	float diffuse_light_spot = 0;
	diffuse_light_spot = material_kd * max(dot(normalize(N), L_spot), 1.f);

	float specular_light_spot = 0;
	if (diffuse_light_spot > 0)
	{
		specular_light_spot = material_ks * pow(max(dot(N, H_spot), 0), material_shininess);
	}

	float light_spot = 0.f;
	float ambient_light = 0.25;

	float cut_off_rad		= radians(angel);
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
	

	return light_spot;
}


float computPunctLight(vec3 world_normal,vec3 light_position,vec3 world_position,vec3 eye_position, float inten){

	vec3 N = normalize(world_normal);
	vec3 L = normalize(light_position - world_position);
	vec3 V = normalize(eye_position - world_position);
	vec3 H = normalize(L + V);
	vec3 R = normalize(reflect(L, world_normal));
	
	float light = .0f;
	float ambient_light = 0.25;
	float diffuse_light = 0;

	diffuse_light = material_kd * max(dot(normalize(N), L), inten);

	float specular_light = 0;

	if (diffuse_light > 0)
	{
		float dl = dot(N, H);
		float de = dot(normalize(N), L);

		//specular_light = material_ks * pow(dl*de + sqrt(1.- dl*dl) * sqrt(1.-de*de),material_shininess);

		specular_light = material_ks * pow(max(dot(N, H), 0), material_shininess);
	}

	float d						= distance(light_position, world_position);
	float attenuation_factor	= clamp(1 / (1 + 0.14 * d + 0.07 * d * d), 0,1);
	light						= ambient_light + attenuation_factor * (diffuse_light + specular_light);
	//1.f / max(d * d, 1.f);
	return light;
}

void main() {
	float light = 0.f;
	float light_0 = 0.f;
	float light_1 = 0.f;
	float light_2 = 0.f;
	float light_3 = 0.f;
	float light_4 = 0.f;

	vec3 N = normalize(world_normal);
	vec3 L = normalize(light_position - world_position);
	vec3 V = normalize(eye_position - world_position);
	vec3 H = normalize(L + V);
	vec3 R = normalize(reflect(L, world_normal));
	
	


	if (only_punct == true){
		light = computPunctLight(world_normal, light_position, world_position, eye_position, 4.);
 		light_1 = computPunctLight(world_normal, light_position_spot_1, world_position, eye_position,4.);
		light_4 =  computPunctLight(world_normal, light_position_spot_4, world_position, eye_position,10.);
	} else if (only_spot == true){
		light_2 =  computSpotLight(light_direction_spot_2, light_position_spot_2, world_position, V,  N,cut_off_angle);
		light_3 =  computSpotLight(light_direction_spot_3, light_position_spot_3, world_position, V,  N,cut_off_angle);
	} else {
		light = computPunctLight(world_normal, light_position, world_position, eye_position,4.);
 		light_1 = computPunctLight(world_normal, light_position_spot_1, world_position, eye_position,4.);
		light_2 =  computSpotLight(light_direction_spot_2, light_position_spot_2, world_position, V,  N,cut_off_angle);
		light_3 =  computSpotLight(light_direction_spot_3, light_position_spot_3, world_position, V,  N,cut_off_angle);
		light_4 =  computPunctLight(world_normal, light_position_spot_4, world_position, eye_position,10.);
	}
	
	

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

	if (frag_ball == .0){
		
	}else {
		out_color = vec4( mix(vec3(.23,.72,.21), vec3(.53,.12,.01), frag_ball ) * 162.1,1);
	}

	out_color = out_color * ( light * vec4(1,1,1,1)
	+ light_0 * vec4(1,0,0,1) 
	+ light_1 * vec4(1,1,1,1)
	+ light_2 * vec4(1,0,1,1)
	+ light_3 * vec4(1,0,1,1)
	+ light_4 * vec4(0,1.4,0,1)
	); 
	//out_texture = vec3(frag_texture, 1.f);
	//out_normal = vec4(frag_normal, 1.f);

}