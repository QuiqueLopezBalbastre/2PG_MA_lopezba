#version 330
//The shader itself.
uniform sampler2D u_albedo_1;
uniform sampler2D u_albedo_2;
uniform vec4 u_color;
uniform int u_use_texture;
in vec2 uv;
out vec4 FragColor;
void main()
{
    //srand(time_t);
    if (0 == u_use_texture)
    {
        FragColor = u_color;
    }
    else {
        
        FragColor = u_color * texture(u_albedo_1, uv);
    }
    //FragColor = vec4(0.0, 0.0, 1.0, 1.0);
}
