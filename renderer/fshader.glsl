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
uniform bool selected_meshes[100];

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

    vec3 r = reflect(normalize(v_position.xyz), v_normal);
    float s = pow(clamp(dot(r, LightDir), 0, 1), 32);
    vec3 spec = texture2D(speculartx, v_texcoord.st).rgb;

    float l = clamp(dot(v_normal, LightDir), 0, 1) * 0.75 + 0.25;
    color = vec4(color.rgb * l + spec * s, 1.0);

    if (selected_meshes[int(v_texcoord.w + 0.5)]) {
        color.a = timer;
    }

    gl_FragColor = color;
}

