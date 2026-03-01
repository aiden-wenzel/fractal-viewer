#version 330 core

out vec4 FragColor;
uniform vec2 u_screen_dim;

float divergence_lim = 10000.0;

void main()
{
	vec2 normChoord = gl_FragCoord.xy / u_screen_dim.xy;
	
	vec2 z_curr = vec2(0.0, 0.0);
	for (int i = 0; i < 10000; i++) {
		z_curr = vec2(z_curr.x * z_curr.x - z_curr.y * z_curr.y, 2 * z_curr.x * z_curr.y);

		z_curr.x += normChoord.x;
		z_curr.y += normChoord.y;

		if (distance(z_curr, vec2(0.0, 0.0)) > divergence_lim) {
			FragColor = vec4(i/100.0, i/100.0, i/100.0, 1.0);
			return;
		}
	}
} 
