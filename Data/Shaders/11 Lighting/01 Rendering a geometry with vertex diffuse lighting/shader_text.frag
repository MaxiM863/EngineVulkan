#version 450

layout( location = 0 ) in vec3 vert_position;
layout( location = 1 ) in vec2 vert_texcoord;

layout( set = 0, binding = 1 ) uniform sampler2D ImageSampler;

layout( location = 0 ) out vec4 frag_color;

void main() {

  vec3 color = texture( ImageSampler, vert_texcoord ).rgb; 
  
  frag_color = vec4( 1.0f,1.0f,1.0f,1.0f ); 
}