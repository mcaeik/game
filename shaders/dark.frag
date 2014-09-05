uniform sampler2D texture;
uniform vec4 ambient;

void main(void) {
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	if (pixel != vec4(1.0)) gl_FragColor = ambient;
	else gl_FragColor = vec4 (1.0);
}
