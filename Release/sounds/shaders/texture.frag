#version 330

uniform vec4 color;
uniform sampler2D tex;

uniform float invertir = 0.0f;

in vec2 texCoordFrag;
out vec4 outColor;

void main()
{
	// Discard fragment if texture sample has alpha < 0.5
	// otherwise compose the texture sample with the fragment's interpolated color

	vec2 st = texCoordFrag;
	if (invertir > 0.0f) {
		st = vec2( (invertir*(1.0f/16.0f)) - st.x, st.y);
	}
	vec4 texColor = texture(tex, st);
	if(texColor.a < 0.5f)
		discard;
	outColor = color * texColor;
}

