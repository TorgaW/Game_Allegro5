#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D al_tex;
varying vec2 uv;
uniform vec2 chunk_index;
uniform float seed;

vec2 random_p(vec2 x) {
    x = vec2(dot(x, vec2(3.92, seed * 1.38)), dot(x, vec2(seed * 91.2, seed / 8.53)));
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

const int max_octaves = 6;


//2d
float FBM(vec2 x)
{
    float result = 0.0;
    float ampl = 1.0;
    float freq = 0.005;

    for(int oct = 0; oct < max_octaves; oct++)
    {
        result += ampl * perlin(x * freq);
        ampl *= 0.1;
        freq *= 1.2;
    }

    return result;
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
                dd = smin(dd, dot( 0.5*(rr+r), normalize(r-rr)), 0.35);
            }
        }
    }
    return vec3(dd, rr);
}

float cpow(float x, float y)
{
    return clamp(pow(x, y), 0.0, 1.0);
}

void main(void) {

    float p_1 = clamp(FBM((chunk_index + uv.xy + 0.13) * 500.0), 0.0, 1.0);
    float v_1 = voronoi((chunk_index + uv.xy) * 257.0).x;

    vec3 dirt_color = mix(vec3(0.396, 0.267, 0.196), vec3(0.2431, 0.1608, 0.1176), v_1);

    float s1 = step(0.1, v_1);
    float s2 = step(0.15, v_1);
    float s3 = step(0.25, v_1);
    float s4 = step(0.35, v_1);
    dirt_color = mix(dirt_color, vec3(0.3216, 0.2196, 0.1059), s1);
    dirt_color = mix(dirt_color, vec3(0.5294, 0.4588, 0.302), s2);
    dirt_color = mix(dirt_color, vec3(0.3608, 0.2431, 0.1098), s3);
    dirt_color = mix(dirt_color, vec3(0.2431, 0.1529, 0.098), s4);

    dirt_color = mix(dirt_color, dirt_color * 0.7, cpow(p_1, 0.9));
    dirt_color = mix(dirt_color, dirt_color * vec3(1.0, 0.4667, 0.0), cpow(p_1, 1.1));

    gl_FragColor = vec4(dirt_color, 1.0);

    // gl_FragColor = vec4(vec3(s3), 1.0);

}