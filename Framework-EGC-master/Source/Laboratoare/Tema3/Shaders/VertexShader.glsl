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
uniform int deformation;
uniform bool isSkull;


layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_color;
layout(location = 2) in vec2 v_texture;
layout(location = 3) in vec3 v_normal;

out vec3 frag_position;
out vec3 frag_normal;
out vec2 frag_texture;
out vec3 frag_color;

out vec3 world_position;
out vec3 world_normal;

flat out float frag_ball;
 
float noise(float delta){
	return cos(delta + cos(delta*90) * 100) * 0.5 + 0.5;
}


void main() {
	vec3 posistion = v_position ;
	frag_color = object_color;
	
	world_position = (Model * vec4(v_position, 1)).xyz;
	world_normal = normalize( mat3(Model) * normalize(v_normal) );

	/*if (Time >= 0)
	{
		frag_texture= vec2(v_texture.x - Time / 10.f, v_texture.y);
	}*/
   if (deformation == 1){
	 //frag_ball = 1;
	 float sum = 0.0;
	 float size = 1.0;
	 vec3 stp = v_position;

	 
	 /*sum = pow((2*pow(stp.x,2) + 2* pow(stp.y,2) + pow(stp.z,2) - 1),3) - 1/10 *pow(stp.x,2) *pow(stp.z,3) -pow(stp.y,2) *pow(stp.z,3);
	 posistion = 5* vec3(stp.x,stp.z,stp.y)*sum ;
	 frag_color =  mix(vec3(.23,.72,.21), vec3(.53,.12,.01), sum ) * 162.1;*/
	 for( int i = 0; i < 100; i++ )
	 {
		sum += noise( size*length(stp.xx)  ) / size;
		size *= 2.3;
	 }
	
	 posistion = v_position * sum;
	 frag_ball = sum;
	 //frag_color =  mix(vec3(.23,.72,.21), vec3(.53,.12,.01), sum ) * 162.1;
	frag_color = object_color;  
   } else {
     if (isSkull == true ){
		frag_color = mix(object_color, v_position, 0.2 );
		frag_color = mix (frag_color , v_normal,0.3);
	 }else {
		frag_color = object_color;
	 }
	 
	 frag_position = v_position;
	 frag_ball = 0;
   }
   
   frag_normal = v_normal;
   frag_texture = v_texture;
 
 gl_Position = Projection * View * Model* vec4(posistion , 1.0);

  /* if (combustibilBool == 0)
		 gl_Position = Projection * View * Model* vec4(posistion , 1.0);
	else if (combustibilBool == 1){
		gl_Position = Model* vec4(v_position, 1.0);
	}	
	*/
}