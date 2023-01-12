#version 120

#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform mat4 mvp_matrix;
uniform mat4 mv_matrix;

attribute vec4 a_position;
attribute vec4 a_normals;
attribute vec4 a_texcoord;

varying vec4 v_position;
varying vec3 v_normal;
varying vec4 v_texcoord;

void main()
{
   gl_Position = mvp_matrix * vec4(a_position.xyz, 1.0);
   v_position = mv_matrix * vec4(a_position.xyz, 1.0);
   v_normal = normalize(mat3(mv_matrix) * a_normals.xyz);
   v_texcoord = a_texcoord;
}
