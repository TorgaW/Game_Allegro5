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

void main(void) {
    //perlin 1
    float p_1 = clamp(FBM((chunk_index + uv.xy) * 5000.0), 0.0, 1.0);
    //perlin 2
    float p_2 = clamp(FBM((chunk_index + uv.xy + 0.1) * 2500.0), 0.0, 1.0);
    //perlin 3
    float p_3 = clamp(FBM((chunk_index + uv.xy - 0.1) * 3500.0), 0.0, 1.0);
    
    float v_1 = voronoi((chunk_index + uv.xy) * 100.0).x; //voronoi 1
    float v_2 = voronoi((chunk_index + uv.xy) * 120.0).x; //voronoi 2
    float v_3 = voronoi((chunk_index + uv.xy) * 110.0).x; //voronoi 3

    float r = 1.0 - smoothstep(0.001, 0.03, v_1);

    float sr = step(0.0001, r); //first color layer (shape)
    vec3 stone_color = mix(vec3(0.1804, 0.1804, 0.1804), vec3(0.1333, 0.1333, 0.1333), sr);

    float l1 = step(0.13, v_1); //layer 2
    stone_color = mix(stone_color, vec3(0.2353, 0.251, 0.2431), l1);

    float l2 = step(0.25, v_1); //layer 3
    stone_color = mix(stone_color, vec3(0.3176, 0.3373, 0.3294), l2);

    float l4 = clamp(step(0.36, v_1) * pow(p_1, 2.0), 0.0, 1.0)*0.5; //layer 4 with perlin mix
    stone_color = mix(stone_color, vec3(0.4549, 0.5059, 0.4784), l4);
    
    float tt = FBM((chunk_index + uv.xy) * 500.0); //color gradient around all texture
    stone_color = mix(stone_color, stone_color * vec3(0.5451, 0.5137, 0.5137), tt);
    
    float srr = step(0.9, r); //additional light spots
    stone_color = mix(stone_color, stone_color + vec3(0.6353, 0.7137, 0.6941) * 0.01, srr);

    //dirt and moss spots
    stone_color = mix(stone_color, stone_color + vec3(0.5686, 0.2078, 0.0)*clamp(pow(v_2, 1.2), 0.0, 1.0)*0.2, sr);
    stone_color = mix(stone_color, stone_color + vec3(0.4353, 1.0, 0.0)*clamp(pow(v_3, 2.0), 0.0, 1.0)*0.4, sr);
    stone_color = mix(stone_color + vec3(0.5922, 0.7098, 0.0)*clamp(pow(v_2, 1.2), 0.0, 1.0)*0.2, stone_color, sr);
    stone_color = mix(stone_color + vec3(0.5176, 1.0, 0.0)*clamp(pow(v_3, 2.0), 0.0, 1.0)*0.3, stone_color, sr);
    


    gl_FragColor = vec4(stone_color * 1.2, 1.0);

}