#version 330 core

in vec3 vertexPosition;
in vec3 vertexNormal;
in vec4 vertexColor;

uniform vec3 cameraPos;

out vec4 color;

uniform mat4 mvp;
uniform mat4 modelMatrix;
uniform mat4 inverseModelMatrix;

void main()
{
    gl_Position = mvp * vec4(vertexPosition, 1.0);

    vec3 normalDirection = normalize(vec3(vec4(vertexNormal, 0.0) * inverseModelMatrix));

    vec4 position = modelMatrix * vec4(vertexPosition, 1.0);
    vec3 viewDirection = normalize(cameraPos - position.xyz);

    float p = exp(dot(viewDirection, normalDirection));

    color = vec4(vertexColor.rgb, p);
}
