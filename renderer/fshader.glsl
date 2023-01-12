#version 120
#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform sampler2D diffusetx;
uniform sampler2D speculartx;
uniform sampler2D normaltx;
uniform sampler2D lighttx;

uniform float timer;
uniform int selsize;
uniform int selected_mesh_part[100];

uniform mat4 mv_matrix;
uniform vec3 LightDir;

varying vec4 v_position;
varying vec3 v_normal;
varying vec4 v_texcoord;

void main()
{
    vec4 color = texture2D(diffusetx, v_texcoord.st);

    if (color.a < 0.5) {
        discard;
    }

    vec3 n = texture2D(diffusetx, v_texcoord.st).xyz;
    n = mat3(mv_matrix) * n;
    n = normalize(v_normal + n);

    vec3 r = reflect(normalize(v_position.xyz), n);
    float s = pow(clamp(dot(r, LightDir), 0, 1), 32);
    vec3 spec = texture2D(speculartx, v_texcoord.st).xyz;

    float l = clamp(dot(n, LightDir), 0, 1) * 0.75 + 0.25;
    color = vec4(color.rgb * l + spec * s, 1.0);

    for(int i=0;i<selsize;i++) {
        if(v_texcoord.w == selected_mesh_part[i]) {
            color.a = timer;
            break;
        }
    }

    gl_FragColor = color;
}

