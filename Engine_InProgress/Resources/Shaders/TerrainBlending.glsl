#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D al_tex;
uniform sampler2D grass_tex;
uniform sampler2D mossy_cobblestone_tex;
uniform sampler2D dirt_tex;
varying vec2 uv;
uniform vec2 chunk_index;
uniform float seed;

vec2 random_p(vec2 x) {
    x = vec2(dot(x, vec2(3.92, 1.38)), dot(x, vec2(91.2, 8.53)));
    return -1.0 + 2.0*fract(sin(x) * 3.27);
}

vec2 random_v(vec2 x) {
    x = vec2(dot(x, vec2(2.92, seed)), dot(x, vec2(seed * 11.1, seed)));
    return fract(cos(x) * 3.14);
}

float smin(float a, float b, float k) {
    float h = clamp(0.5 + 0.5*(a-b)/k, 0.0, 1.0);
    return mix(a, b, h) - k*h*(1.0-h);
}

//2d
float perlin(vec2 x) {
    vec2 uv_index = floor(x);
    vec2 uv_fract = fract(x);

    vec2 blur = smoothstep(0.0, 1.0, uv_fract);

    return mix(mix(dot(random_p(uv_index + vec2(0.0, 0.0)), uv_fract - vec2(0.0, 0.0)), dot(random_p(uv_index + vec2(1.0, 0.0)), uv_fract - vec2(1.0, 0.0)), blur.x), mix(dot(random_p(uv_index + vec2(0.0, 1.0)), uv_fract - vec2(0.0, 1.0)), dot(random_p(uv_index + vec2(1.0, 1.0)), uv_fract - vec2(1.0, 1.0)), blur.x), blur.y) + 0.5;
}

const int max_octaves = 8;


//2d
float FBM(vec2 x)
{
    float result = 0.0;
    float ampl = 1.0;
    float freq = 1.0;

    for(int oct = 0; oct < max_octaves; oct++)
    {
        result += ampl * perlin(x * freq);
        ampl *= 0.35;
        freq *= 2.0;
    }

    return result;
}

//dommain_distortion_fbm
float ddFBM(vec2 x, float strength)
{
    vec2 q = vec2(FBM(x), FBM(x + vec2(5.2, 1.3)));
    return clamp(FBM(x + strength*q), 0.0, 1.0);
}

//3d
// Created by inigo quilez - iq/2013
// License Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
// http://www.iquilezles.org/www/articles/voronoilines/voronoilines.htm
vec3 voronoi(vec2 x) {
    vec2 n = floor(x);
    vec2 f = fract(x);
    vec2 ww, rr;
    float dd = 2.0;
    for (int j= -1; j <= 1; j++) {
        for (int i= -1; i <= 1; i++) {
            vec2 g = vec2(float(i),float(j));
            vec2 o = random_v( n + g );
            vec2 r = g + o - f;
            float d = dot(r,r);
            if( d<dd ) {
                dd = d;
                rr = r;
                ww = g;
            }
        }
    }
    dd = 2.0;
    for (int j= -2; j <= 2; j++) {
        for (int i= -2; i <= 2; i++) {
            vec2 g = ww + vec2(float(i),float(j));
            vec2 o = random_v( n + g );
            vec2 r = g + o - f;
            if ( dot(rr-r,rr-r)>0.00001 ) {
                dd = min(dd, dot( 0.5*(rr+r), normalize(r-rr)));
            }
        }
    }
    return vec3(dd, rr);
}

float ddVoronoi(vec2 x, float strength)
{
    vec2 q = vec2(voronoi(x).x, voronoi(x + vec2(5.2, 1.3)).x);
    return clamp(voronoi(x + strength*q).x, 0.0, 1.0);
}

float cpow(float x, float y)
{
    return clamp(pow(x, y), 0.0, 1.0);
}

void main(void) {
    // float p_1 = clamp(FBM((chunk_index + uv.xy) * 1000.0), 0.0, 1.0);
    float p_1 = ddFBM((chunk_index + uv.xy) * 1.0, 1.0);
    // float p_2 = clamp(FBM((chunk_index + uv.xy) * 50000.0), 0.0, 1.0);
    float p_2 = ddFBM((chunk_index + uv.xy) * 100.0, 4.0);

    float v_1 = voronoi((chunk_index + uv.xy) * 100.0).x;

    vec3 grass_color = texture2D(grass_tex, uv.xy).rgb;
    vec3 mossy_cobblestone_color = texture2D(mossy_cobblestone_tex, uv.xy).rgb;
    vec3 dirt_color = texture2D(dirt_tex, uv.xy).rgb;

    float s1 = step(0.1, cpow(p_1, 4.0));
    float s2 = step(0.9, cpow(p_1, 4.0));
    float rr = (s1) * (cpow(p_2, 2.0)); //edges of blending
    rr = clamp(rr * 0.9, 0.0, 1.0);

    vec3 result_color = mix(grass_color, dirt_color, cpow(p_1, 4.0));
    result_color = mix(result_color, mossy_cobblestone_color, cpow(p_1, 16.0));
    result_color = mix(result_color, grass_color, rr);
    // result_color = mix(result_color, mossy_cobblestone_color, rr2);


    // float ddfbm = ddFBM((chunk_index + uv.xy)*10.0, 1.0);
    gl_FragColor = vec4(result_color, 1.0);
}