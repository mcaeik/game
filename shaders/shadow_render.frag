#define PI 3.141592

uniform sampler2D texture;
uniform sampler2D stexture;
uniform float resolution;
uniform vec4 color;

void main(void) {
	vec2 pos = gl_FragCoord.xy;
	pos.y = resolution - pos.y;

	float dis = distance (pos, vec2 (resolution/2.0, resolution/2.0));
	float angel = atan (pos.y - resolution/2.0, pos.x - resolution/2.0);

	if (angel < 0.0) angel = angel+2.0*PI;
	vec2 shadow = vec2 (angel/(2.0*PI), 0.0);

	if (dis/resolution*2.0 > texture2D (stexture, shadow).r) {
		gl_FragColor = vec4 (0.0, 0.0, 0.0, 1.0);
		return;
	}

	float att = 1.0 - pow(dis/resolution*2.0, 0.5);

	gl_FragColor = vec4 (att, att, att, 1.0)*color;
}
