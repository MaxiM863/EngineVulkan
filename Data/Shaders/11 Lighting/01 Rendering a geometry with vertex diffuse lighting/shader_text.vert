#version 450

layout( location = 0 ) in vec3 app_position;
layout( location = 1 ) in vec2 app_texcoord;

layout( set = 0, binding = 0 ) uniform UniformBuffer {
  mat4 ModelViewMatrix;
  mat4 ProjectionMatrix;
};

layout( location = 0 ) out vec3 vert_position;
layout( location = 1 ) out vec2 vert_texcoord;

void main() {
  vec4 position = ModelViewMatrix * vec4(app_position, 1.0f);
  gl_Position = ProjectionMatrix * position;
  
  vert_position = position.xyz;
  vert_texcoord = app_texcoord;
}
