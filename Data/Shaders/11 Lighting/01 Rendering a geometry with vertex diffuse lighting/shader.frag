#version 450

layout( location = 0 ) in vec3 vert_position;
layout( location = 1 ) in vec2 vert_texcoord;
layout( location = 2 ) in vec3 vert_normal;
layout( location = 3 ) in vec3 vert_tangent;
layout( location = 4 ) in vec3 vert_bitangent;

layout( set = 0, binding = 1 ) uniform sampler2D ImageSampler;

layout( push_constant ) uniform LightParameters {
  vec4 Position;
} Light;

layout( location = 0 ) out vec4 frag_color;

void main() {

  vec3 color = texture( ImageSampler, fract(vert_texcoord + vec2(Light.Position.x, Light.Position.x)) ).rgb;
  frag_color = vec4( color, 1.0f );
}
