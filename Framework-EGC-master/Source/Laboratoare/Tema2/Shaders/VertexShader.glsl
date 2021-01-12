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



layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_color;
layout(location = 2) in vec2 v_texture;
layout(location = 3) in vec3 v_normal;

out vec3 frag_position;
out vec3 frag_normal;
out vec2 frag_texture;
out vec3 frag_color;
flat out int frag_ball;
 
float noise(float delta){
	return cos(delta + cos(delta*90) * 100) * 0.5 + 0.5;
}


void main() {
	vec3 posistion = v_position ;
	frag_color = object_color;
   if (deformation == 1){
	 //frag_color.r += noise(Time * v_normal.y + v_normal.x);
	 

	 frag_ball = 1;
	 //float val = abs(tan(Time*100))/100+0.1+ 24.5;
	 float sum = 0.0;
	 float size = 1.0;
	 vec3 stp = v_position;
	 for( int i = 0; i < 100; i++ )
	 {  
		sum += noise( size*stp.x ) / size;  
		size *= 2.3; 
	 }
	//sum = clamp( 23.3 * sum, 0.0, 1.0 );
	 posistion = v_position * sum;
	 frag_color =  mix(vec3(.23,.72,.21), vec3(.53,.12,.01), sum ) * 162.1;
   } else {
	 frag_color = object_color;
	 frag_position = v_position;
	 frag_ball = 0;
   }
   
   frag_normal = v_normal;
   frag_texture = v_texture;
  
   if (combustibilBool == 0)
		gl_Position = Projection * View * Model * vec4(posistion , 1.0);
	else if (combustibilBool == 1)
		gl_Position =  vec4(v_position, 1.0);
}