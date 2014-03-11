#version 410 core

in vec3 vNormal;
in vec3 triDistance;

out vec4 out_color;

void main(void)
{
  vec3 normal = normalize(vNormal);
//  float diffuse = clamp(dot(normal,light_dir),0,1);

  out_color = vec4(1,0,0,1);

  float d1 = min(min(triDistance.x, triDistance.y), triDistance.z);
  if(d1 < 0.02)
    out_color = vec4(0,0,1,1);
  else
  {
    out_color = vec4(0,1,0,1);
  }

}
