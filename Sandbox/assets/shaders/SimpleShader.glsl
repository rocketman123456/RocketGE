#type vertex
#version 410 core
layout (location = 0) in vec3 a_Position;
uniform mat4 u_ViewProjection;
void main()
{
    gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}

#type fragment
#version 410 core
out vec4 FragColor;
void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
