#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D al_tex;
uniform sampler2D ground_mask;
varying vec2 uv;
uniform int seed;
uniform vec2 chunk_index;
uniform int tile_size;

const int max_octaves = 8;

vec2 random_p(vec2 x) {
    x = vec2(dot(x, vec2(91.2, float(seed) + 3.92)), dot(x, vec2(float(seed) - 1.38, float(seed) + 2.45)));
    return -1.0 + 2.0*fract(sin(x) * 4.72);
}

//2d
float perlin(vec2 x) {
    vec2 uv_index = floor(x);
    vec2 uv_fract = fract(x);

    vec2 blur = smoothstep(0.0, 1.0, uv_fract);

    return mix(mix(dot(random_p(uv_index + vec2(0.0, 0.0)), uv_fract - vec2(0.0, 0.0)), 
    dot(random_p(uv_index + vec2(1.0, 0.0)), uv_fract - vec2(1.0, 0.0)), blur.x), 
    mix(dot(random_p(uv_index + vec2(0.0, 1.0)), uv_fract - vec2(0.0, 1.0)), 
    dot(random_p(uv_index + vec2(1.0, 1.0)), uv_fract - vec2(1.0, 1.0)), blur.x), blur.y) + 0.5;
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
    return FBM(x + strength*q);
}

float istep(float edge, float x)
{
    return 1.0 - step(edge, x);
}


//steps for ground
// 0.0 - 0.7 - water
// 0.7 - 0.75 - sand
// 0.75 - 0.85 - grass
// 0.85 - 1.0 - rock


void main(void) {

    float distortion_mask = ddFBM((uv + chunk_index)*10.0, 1.0);
    float mask = texture2D(ground_mask, uv).r;
    float water_step = step(0.6, mask);
    float grass_step = step(0.67, mask);
    float rock_step = step(0.999, mask);
    vec3 color = mix(vec3(0.0, 0.7098, 0.9882), vec3(1.0, 0.7333, 0.0), water_step);
    color = mix(color, vec3(0.2471, 0.7255, 0.0118), grass_step);
    color = mix(color, vec3(0.6706, 0.6902, 0.6588), rock_step);
    gl_FragColor = vec4(color, 1.0);
}
