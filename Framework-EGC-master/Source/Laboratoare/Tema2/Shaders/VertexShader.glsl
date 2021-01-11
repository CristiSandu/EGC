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
   if (deformation == 1){
	 frag_color = vec3(.1,noise(Time * v_normal.x),.91);
	 frag_ball = 1;
	 float val = abs(sin(Time*10))/4.0+0.1;
	 posistion += vec3(val,val,val) * posistion;
	 posistion += posistion * clamp(noise(Time * v_normal.y + v_normal.x),0.1,0.25) * noise(Time * v_normal.y + v_normal.x);
	
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
		gl_Position = vec4(posistion, 1.0);
}