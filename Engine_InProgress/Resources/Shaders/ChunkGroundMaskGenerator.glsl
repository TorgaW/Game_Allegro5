#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D al_tex;
varying vec2 uv;
uniform vec2 chunk_index;
uniform int seed;


const int max_octaves = 8;

vec2 random_p(vec2 x) {
    x = vec2(dot(x, vec2(3.92, float(seed) + 1.38)), dot(x, vec2(float(seed) - 91.2, float(seed) + 8.53)));
    return -1.0 + 2.0*fract(sin(x) * 3.27);
}

//2d
float perlin(vec2 x) {
    vec2 uv_index = floor(x);
    vec2 uv_fract = fract(x);

    vec2 blur = smoothstep(0.0, 1.0, uv_fract);

    return mix(mix(dot(random_p(uv_index + vec2(0.0, 0.0)), uv_fract - vec2(0.0, 0.0)), dot(random_p(uv_index + vec2(1.0, 0.0)), uv_fract - vec2(1.0, 0.0)), blur.x), mix(dot(random_p(uv_index + vec2(0.0, 1.0)), uv_fract - vec2(0.0, 1.0)), dot(random_p(uv_index + vec2(1.0, 1.0)), uv_fract - vec2(1.0, 1.0)), blur.x), blur.y) + 0.5;
}

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

    return clamp(result, 0.0, 1.0);
}

//dommain_distortion_fbm
float ddFBM(vec2 x, float strength)
{
    vec2 q = vec2(FBM(x), FBM(x + vec2(5.2, 1.3)));
    return clamp(FBM(x + strength*q), 0.0, 1.0);
}

void main(void)
{   
    float t = ddFBM((uv + chunk_index)*0.5, 1.5);
    gl_FragColor = vec4(t, 0, 0, 1.0);
}
