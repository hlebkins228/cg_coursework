#version 330 core
    
in vec3 fragCoord;
out vec4 fragColor;
uniform float iTime;

vec3 palette(float t)
{
    vec3 a = vec3(0.5, 0.5, 0.5);
    vec3 b = vec3(0.5, 0.5, 0.5);
    vec3 c = vec3(1.0, 1.0, 1.0);
    vec3 d = vec3(0.263, 0.416, 0.557);
    
    vec3 result = a + b * cos( 6.28318 * (c * t + d) );
    
    return result;
}

void main()
{
    vec3 uv = fragCoord;
    vec3 uv0 = uv;
    vec3 finalColor = vec3(0.0);
    vec3 col = vec3(0.0);
    float l = 0.0;
    float d = 0.0;

    float gray = 0.0;
    vec3 grayVec = vec3(0.0);
    
    for (float i = 0.0; i < 2.0; i++)
    {
        uv = fract(uv * 1.5) - 0.5;
        l = length(uv) * exp(-length(uv0));
        col = palette(length(uv0) + iTime * 0.3);

        d = sin(l*8.0 + iTime * cos(uv.y))/8.0;
        d = abs(d);
        d = 0.02 / d;
        
        finalColor += col * d;
    }

    gray = (finalColor.x + finalColor.y + finalColor.z) / 3.0;
    grayVec = vec3(gray);
    fragColor = vec4(finalColor, 1.0);
}
