#version 450

layout( points ) in;
layout( location = 1) in int pos[1];

layout( set = 0, binding = 0 ) uniform UniformBuffer {
  mat4 ModelViewMatrix[20];
  mat4 ProjectionMatrix;
};

layout( triangle_strip, max_vertices = 4 ) out;
layout( location = 0 ) out vec2 geom_texcoord;

const float SIZE = 1.0;

void main() {

  vec4 position = gl_in[0].gl_Position;
  
  gl_Position = ProjectionMatrix *  (ModelViewMatrix[pos[0]] * gl_in[0].gl_Position + vec4( -SIZE, SIZE, 0.0, 0.0 ));
  geom_texcoord = vec2( 0.0, 1.0 );
  EmitVertex();
  
  gl_Position = ProjectionMatrix *  (ModelViewMatrix[pos[0]] * gl_in[0].gl_Position + vec4( -SIZE, -SIZE, 0.0, 0.0 ));
  geom_texcoord = vec2( 0.0, 0.0 );
  EmitVertex();
  
  gl_Position = ProjectionMatrix *  (ModelViewMatrix[pos[0]] * gl_in[0].gl_Position + vec4( SIZE, SIZE, 0.0, 0.0 ));
  geom_texcoord = vec2( 1.0, 1.0 );
  EmitVertex();
  
  gl_Position = ProjectionMatrix *  (ModelViewMatrix[pos[0]] * gl_in[0].gl_Position + vec4( SIZE, -SIZE, 0.0, 0.0 ));
  geom_texcoord = vec2( 1.0, 0.0 );
  EmitVertex();

  EndPrimitive();
}
