#version 330 core

in vec3 vertexPosition;
in vec3 vertexNormal;

uniform vec3 cameraPos;

out float dotprod;

uniform mat4 mvp;
uniform mat4 inverseModelMatrix;
uniform mat4 modelMatrix;

void main()
{
    vec3 normalDirection = normalize(vec3(vec4(vertexNormal, 0.0) * inverseModelMatrix));

    vec4 position = modelMatrix * vec4(vertexPosition, 1.0);
    vec3 viewDirection = normalize(cameraPos - position.xyz);

    dotprod = pow(abs(dot(viewDirection, normalDirection)), 0.5);
    gl_Position = mvp * vec4(vertexPosition, 1.0);

}
