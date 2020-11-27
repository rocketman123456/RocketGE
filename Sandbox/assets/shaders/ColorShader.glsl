#type vertex
#version 330 core
layout (location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;

out vec2 v_TexCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

void main()
{
    v_TexCoord = a_TexCoord;
    gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
}

#type fragment
#version 330 core
layout(location = 0) out vec4 FragColor;

in vec2 v_TexCoord;

uniform vec3 u_Color;
uniform sampler2D u_Texture;

void main()
{
    vec4 color = texture(u_Texture, v_TexCoord);
    FragColor = color;
    //FragColor = vec4(u_Color, 1.0f);// * color;
    //FragColor = vec4(v_TexCoord, 1.0f, 1.0f) * vec4(u_Color, 1.0f);
}
