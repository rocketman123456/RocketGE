// Basic Texture Shader

#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in float a_TexIndex;
layout(location = 4) in float a_TilingFactor;

uniform mat4 u_ViewProjection;

out vec4 v_Color;
out vec2 v_TexCoord;
out vec2 v_ScreenPos;
out float v_TexIndex;
out float v_TilingFactor;

void main()
{
	v_Color = a_Color;
	v_TexCoord = a_TexCoord;
	v_TexIndex = a_TexIndex;
	v_TilingFactor = a_TilingFactor;
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
	v_ScreenPos = gl_Position.xy;
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_Color;
in vec2 v_TexCoord;
in vec2 v_ScreenPos;
in float v_TexIndex;
in float v_TilingFactor;

uniform sampler2D u_Textures[16];

void main()
{
	// Dark Effect
	float dist = 1.0f - distance(v_ScreenPos * 0.8f, vec2(0.0f));
	dist = clamp(dist, 0.0f, 1.0f);
	dist = sqrt(dist);

	vec4 texColor = v_Color;
	switch(int(v_TexIndex))
	{
		case 0: texColor *= texture(u_Textures[0], v_TexCoord * v_TilingFactor); break;
		case 1: texColor *= texture(u_Textures[1], v_TexCoord * v_TilingFactor); break;
		case 2: texColor *= texture(u_Textures[2], v_TexCoord * v_TilingFactor); break;
		case 3: texColor *= texture(u_Textures[3], v_TexCoord * v_TilingFactor); break;
		case 4: texColor *= texture(u_Textures[4], v_TexCoord * v_TilingFactor); break;
		case 5: texColor *= texture(u_Textures[5], v_TexCoord * v_TilingFactor); break;
		case 6: texColor *= texture(u_Textures[6], v_TexCoord * v_TilingFactor); break;
		case 7: texColor *= texture(u_Textures[7], v_TexCoord * v_TilingFactor); break;
		case 8: texColor *= texture(u_Textures[8], v_TexCoord * v_TilingFactor); break;
		case 9: texColor *= texture(u_Textures[9], v_TexCoord * v_TilingFactor); break;
		case 10: texColor *= texture(u_Textures[10], v_TexCoord * v_TilingFactor); break;
		case 11: texColor *= texture(u_Textures[11], v_TexCoord * v_TilingFactor); break;
		case 12: texColor *= texture(u_Textures[12], v_TexCoord * v_TilingFactor); break;
		case 13: texColor *= texture(u_Textures[13], v_TexCoord * v_TilingFactor); break;
		case 14: texColor *= texture(u_Textures[14], v_TexCoord * v_TilingFactor); break;
		case 15: texColor *= texture(u_Textures[15], v_TexCoord * v_TilingFactor); break;
	}
	//color = texColor * dist;
	color = texColor;
}
