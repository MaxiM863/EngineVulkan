#version 450

layout( location = 0 ) in vec2 shadow_coords;

layout( set = 0, binding = 1 ) uniform sampler2D ShadowMap;

layout( location = 0 ) out vec4 frag_color;

void main() {
  vec4 color = texture( ShadowMap, shadow_coords );
  
  float alpha = color.w;
  
  if(alpha < 0.2)
  {
    discard;
  }

  frag_color = color;
}
