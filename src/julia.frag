#version 330 core

out vec4 FragColor;
uniform vec2 u_screen_dim;
uniform vec2 u_offset;
uniform float u_scale;
uniform float u_a;

float divergence_lim = 10000.0;


void main()
{
	vec2 normChoord = (gl_FragCoord.xy + u_offset) / u_screen_dim.xy;
	normChoord *= u_scale;
	
	vec2 c = vec2(0.7885*cos(u_a), 0.7885*sin(u_a));
	vec2 z_curr = normChoord;
	for (int i = 0; i < 1000; i++) {
		z_curr = vec2((z_curr.x * z_curr.x - z_curr.y * z_curr.y) + c.x, 2 * z_curr.x * z_curr.y + c.y);

		if (distance(z_curr, vec2(0.0, 0.0)) > divergence_lim) {
			FragColor = vec4(i/100.0, 0.0, 0.0, 1.0);
			return;
		}
	}
	FragColor = vec4(0.0, 0.0, 0.0, 1.0);
} 
