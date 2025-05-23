#version 450

layout( location = 0 ) in vec4 app_position;
layout( location = 1 ) in vec4 app_norm;
layout( location = 2 ) in vec2 app_texcoord;

layout( set = 0, binding = 0 ) uniform UniformBuffer {
  mat4 ModelViewMatrix;
  mat4 ProjectionMatrix;
};

layout( location = 0 ) out vec3 vert_position;
layout( location = 1 ) out vec2 vert_texcoord;
layout( location = 2 ) out vec3 vert_normal;

void main() {
  vec4 position = ModelViewMatrix * app_position;
  gl_Position = ProjectionMatrix * position;

  vec4 norm = app_norm * ModelViewMatrix;
  
  vert_position = (app_position * ModelViewMatrix).xyz;
  vert_normal = norm.xyz;
  vert_texcoord = app_texcoord;
}
