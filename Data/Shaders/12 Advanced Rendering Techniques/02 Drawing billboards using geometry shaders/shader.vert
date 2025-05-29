#version 450

layout( location = 0 ) in vec3 app_position;
layout( location = 1) in float pos;

layout( set = 0, binding = 0 ) uniform UniformBuffer {
  mat4 ModelViewMatrix;
  mat4 ProjectionMatrix;
};

layout( location = 1) out int ppos;

void main() {
  gl_Position = vec4(app_position, 1.0f);
  ppos = int(pos);
}
