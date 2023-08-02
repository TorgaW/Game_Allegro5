#ifdef GL_ES
precision mediump float;
#endif

vec2 random(vec2 uv) {
    uv = vec2(dot(uv, vec2(121.1, 311.7)), dot(uv, vec2(262.5, 183.3)));
    return -1.0 + 2.0 * fract(sin(uv) * 3.0);
}

float noise(vec2 uv) {
    vec2 uv_index = floor(uv);
    vec2 uv_fract = fract(uv);

    vec2 blur = smoothstep(0.0, 1.0, uv_fract);

    return mix(mix(dot(random(uv_index + vec2(0.0, 0.0)), uv_fract - vec2(0.0, 0.0)), dot(random(uv_index + vec2(1.0, 0.0)), uv_fract - vec2(1.0, 0.0)), blur.x), mix(dot(random(uv_index + vec2(0.0, 1.0)), uv_fract - vec2(0.0, 1.0)), dot(random(uv_index + vec2(1.0, 1.0)), uv_fract - vec2(1.0, 1.0)), blur.x), blur.y) + 0.5;
}

void main(void) {
    float t = 0.0;
    // for(int i = 5; i >= 0; i--) {
    //     float p = float(i);
    //     t += noise(gl_FragCoord.xy / pow(2.0, p+1.0)) * (1.0/(6.0 - p));
    // }
    t = noise(gl_FragCoord.xy/64.0) * 0.5 + noise(gl_FragCoord.xy/32.0) * 0.25 + noise(gl_FragCoord.xy/16.0) * 0.125;
    gl_FragColor = vec4(vec3(t, t, t), 1.0);
}