#version 450

layout( location = 0 ) in vec3 vert_position;
layout( location = 1 ) in vec2 vert_texcoord;
layout( location = 2 ) in vec3 vert_normal;

layout( set = 0, binding = 1 ) uniform sampler2D ImageSampler;

layout( location = 0 ) out vec4 frag_color;

void main() {

  vec4 ambient = vec4(0.1, 0.0, 0.0, 1.0);
  vec4 lightColor = vec4( 1.0f, 1.0f, 1.0f, 1.0f);

  vec3 lightPosition = vec3( 1.0f, 1.0f, -100.0f );
  vec3 lightDirection = normalize(lightPosition - vert_position);

  vec4 diffuse = clamp( dot( lightDirection, vert_normal ), 0, 1) * lightColor + ambient;

  frag_color = diffuse; 
}