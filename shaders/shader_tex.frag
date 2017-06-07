#version 430 core

uniform vec3 objectColor;
uniform vec3 lightDir;
uniform sampler2D sampler2dtype;

in vec3 interpNormal;
in vec2 vertexTexCoord1;
in vec3 Position;

void main()
{

	vec3 lightDir2 = normalize(Position - vec3(0,0,0));


	vec3 normal = normalize(interpNormal);
	float diffuse = max(dot(normal, -lightDir2), 0.0);
	vec4 textureColor = texture2D(sampler2dtype, vertexTexCoord1);
	gl_FragColor = vec4(textureColor.xyz * diffuse, 1.0);
}
