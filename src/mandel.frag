#version 330 core

out vec4 FragColor;
uniform vec2 screen_dim;

void main()
{
	vec2 origin = vec2(0.5, 0.5);
	vec2 normChoord = gl_FragCoord.xy / screen_dim.xy;
	float dis = distance(origin, normChoord);
    FragColor = vec4(dis, dis, dis, 1.0);
} 
