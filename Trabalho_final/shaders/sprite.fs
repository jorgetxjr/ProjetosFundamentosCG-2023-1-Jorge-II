#version 450

in vec4 vertexColor;
in vec2 texCoord;

out vec4 color;

//Propriedades da superficie
uniform float ka;
uniform float kd;
uniform float ks;
uniform float q;

//Propriedades da fonte de luz
uniform vec3 lightPos;
uniform vec3 lightColor;

// pixels da textura
uniform sampler2D tex_buffer;

void main()
{
    //Cálculo da parcela de iluminação ambiente
	vec3 ambient = ka * lightColor;

	//Cálculo da parcela de iluminação difusa
	vec3 N = normalize(scaledNormal);
	vec3 L = normalize(lightPos - fragPos);
	float diff = max(dot(N,L),0.0);
	vec3 diffuse = kd * diff * lightColor;

	//Cálculo da parcela de iluminação especular
	vec3 V = normalize(cameraPos - fragPos);
	vec3 R = normalize(reflect(-L,N));
	float spec = max(dot(R,V),0.0);
	spec = pow(spec,q);
	vec3 specular = ks * spec * lightColor;

	vec3 result = (ambient + diffuse) * finalColor + specular;

    //color = texture(tex_buffer, texCoord);
	color=vec4(result,1.0);
}