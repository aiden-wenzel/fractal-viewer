#version 330 core

out vec4 FragColor;
uniform vec2 u_center;
uniform vec2 u_screen_dim;
uniform float zoom;

float divergence_lim = 10000.0;

void main()
{
	vec2 normChoord = (gl_FragCoord.xy / u_screen_dim.xy) * 2.0 - 1.0;
	vec2 c = u_center + zoom*normChoord;
	
	vec2 z_curr = vec2(0.0, 0.0);
	for (int i = 0; i < 10000; i++) {
		z_curr = vec2(z_curr.x * z_curr.x - z_curr.y * z_curr.y, 2 * z_curr.x * z_curr.y);
		z_curr += c;

		if (dot(z_curr, z_curr) > 4.0) {
			FragColor = vec4(i/300.0, i/500.0, i/500.0, 1.0);
			return;
		}
	}
} 
