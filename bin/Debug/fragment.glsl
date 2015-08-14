#version 110

varying vec3 outColor;

uniform float time;

void main()
{
	gl_FragColor = vec4(outColor * clamp(sin(time) + cos(time), 0.2, 0.8), 1.0f);
}
