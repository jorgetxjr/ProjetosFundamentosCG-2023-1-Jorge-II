/* Hello Triangle - c�digo adaptado de https://learnopengl.com/#!Getting-started/Hello-Triangle
 *
 * Adaptado por Rossana Baptista Queiroz
 * para a disciplina de Processamento Gr�fico - Jogos Digitais - Unisinos
 * Vers�o inicial: 7/4/2017
 * �ltima atualiza��o em 11/04/2022
 *
 */

#include <iostream>
#include <string>
#include <assert.h>
#include <cmath>
#include <vector>

using namespace std;

// GLAD
#include <glad/glad.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//stb_image
#include "stb_image.h"

// Nossa classe que armazena as infos dos shaders
#include "Shader.h"
#include "Mesh.h"

//const float Pi = 3.1419;

// Prot�tipo da fun��o de callback de teclado
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);


int loadTexture(string path);
int loadSimpleOBJ(string filepath, int& nVerts, glm::vec3 color);
void loadSimpleMTL(string filepath);

// Dimens�es da janela (pode ser alterado em tempo de execu��o)
const GLuint WIDTH = 800, HEIGHT = 600;

//vari�veis de textura
float q = 0.0;
float ka = 0.0;
float ks = 0.0;
float kd = 0.0;

int main()
{
	// Inicializa��o da GLFW
	glfwInit();

	// Cria��o da janela GLFW
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Ola Trabalho final - Jorge JR!", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Fazendo o registro da fun��o de callback para a janela GLFW
	glfwSetKeyCallback(window, key_callback);

	// GLAD: carrega todos os ponteiros d fun��es da OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	// Obtendo as informa��es de vers�o
	const GLubyte* renderer = glGetString(GL_RENDERER); /* get renderer string */
	const GLubyte* version = glGetString(GL_VERSION); /* version as a string */
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;

	// Compilando e buildando o programa de shader
	Shader shader("../shaders/Hello3D.vs", "../shaders/Hello3D.fs");

	//Carregando uma textura e armazenando o identificador na mem�ria
	string nomeTexturaSuzanne = "Suzanne.png";
	string nomeTexturaCubo = "cube.png";
	GLuint texIDCubo = loadTexture(nomeTexturaCubo);
	GLuint textIDSuzanne = loadTexture(nomeTexturaSuzanne);
	
	// Gerando uma geometria de quadril�tero com coordenadas de textura
	int nVerts;
	string caminhoObjSuzanne = "SuzanneTriTextured.obj";
	string caminhoObjCubo = "cube.obj";
	GLuint VAOCubo = loadSimpleOBJ(caminhoObjCubo, nVerts,glm::vec3(0,0,0));
	GLint VAOSuzanne = loadSimpleOBJ(caminhoObjSuzanne, nVerts, glm::vec3(0, 0, 0));
	
	Mesh cubo, suzanne;
	cubo.initialize(VAOCubo,nVerts,&shader);
	cubo.setTexture(texIDCubo);

	suzanne.initialize(VAOSuzanne, nVerts, &shader, glm::vec3(-1.75, 0.0, 0.0));
	suzanne.setTexture(textIDSuzanne);

	// Ativando o shader
	glUseProgram(shader.ID);

	// Associando com o shader o buffer de textura que conectaremos
	// antes de desenhar com o bindTexture
	glUniform1i(glGetUniformLocation(shader.ID, "tex_buffer"), 0);

	string caminhoMTL="SuzanneTriTextured.mtl";
	loadSimpleMTL(caminhoMTL);
	shader.setFloat("ka", ka);
	shader.setFloat("kd", kd);
	shader.setFloat("ks", ks);
	shader.setFloat("q", q);

	//Definindo a fonte de luz pontual
	//isso tamb�m � definido no MTL? acho que n�o
	shader.setVec3("lightPos", -2.0, 10.0, 2.0);
	shader.setVec3("lightColor", 1.0, 1.0, 0.0);

	//Criando a matriz de proje��o usando a GLM
	glm::mat4 projection = glm::mat4(1); //matriz identidade
	projection = glm::ortho(-2.0, 2.0, -2.0, 2.0, -1.0, 1.0);

	GLint projLoc = glGetUniformLocation(shader.ID, "projection");
	glUniformMatrix4fv(projLoc, 1, FALSE, glm::value_ptr(projection));


	glEnable(GL_DEPTH_TEST);
	glActiveTexture(GL_TEXTURE0);

	// Loop da aplica��o - "game loop"
	while (!glfwWindowShouldClose(window))
	{
		// Checa se houveram eventos de input (key pressed, mouse moved etc.) e chama as fun��es de callback correspondentes
		glfwPollEvents();

		// Definindo as dimens�es da viewport com as mesmas dimens�es da janela da aplica��o
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		// Limpa o buffer de cor
		glClearColor(0.1f, 0.2f, 0.3f, 0.8f); //cor de fundo
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glLineWidth(10);
		glPointSize(20);


		shader.setFloat("q", 250.0);
		cubo.update();
		cubo.draw();
		suzanne.update();
		suzanne.draw();
		
		glBindVertexArray(0); //unbind - desconecta
		glBindTexture(GL_TEXTURE_2D, 0); //unbind da textura

		// Troca os buffers da tela
		glfwSwapBuffers(window);
	}
	// Pede pra OpenGL desalocar os buffers
	glDeleteVertexArrays(1, &VAOCubo);
	// Finaliza a execu��o da GLFW, limpando os recursos alocados por ela
	glfwTerminate();
	return 0;
}

// Fun��o de callback de teclado - s� pode ter uma inst�ncia (deve ser est�tica se
// estiver dentro de uma classe) - � chamada sempre que uma tecla for pressionada
// ou solta via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int loadTexture(string path)
{
	GLuint texID;

	// Gera o identificador da textura na mem�ria 
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	//Ajusta os par�metros de wrapping e filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Carregamento da imagem
	int width, height, nrChannels;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

	if (data)
	{
		if (nrChannels == 3) //jpg, bmp
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else //png
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, 0);

	return texID;
}

int loadSimpleOBJ(string filepath, int &nVerts, glm::vec3 color)
{
	vector <glm::vec3> vertices;
	vector <GLuint> indices;
	vector <glm::vec2> texCoords;
	vector <glm::vec3> normals;
	vector <GLfloat> vbuffer;

	ifstream inputFile;
	inputFile.open(filepath.c_str());
	if (inputFile.is_open())
	{
		char line[100];
		string sline;
		
		
		
		while (!inputFile.eof())
		{
			inputFile.getline(line, 100);
			sline = line;
			
			string word;
			
			istringstream ssline(line);
			ssline >> word;

			//cout << word << " ";
			if (word == "v")
			{
				glm::vec3 v;

				ssline >> v.x >> v.y >> v.z;
				
				vertices.push_back(v);
			}
			if (word == "vt")
			{
				glm::vec2 vt;

				ssline >> vt.s >> vt.t;
				
				texCoords.push_back(vt);
			}
			if (word == "vn")
			{
				glm::vec3 vn;

				ssline >> vn.x >> vn.y >> vn.z;

				normals.push_back(vn);
			}
			if (word == "f")
			{
				string tokens[3];
				
				ssline >> tokens[0] >> tokens[1] >> tokens[2];
				
				for (int i = 0; i < 3; i++)
				{
					//Recuperando os indices de v
					int pos = tokens[i].find("/");
					string token = tokens[i].substr(0, pos);
					int index = atoi(token.c_str()) - 1;
					indices.push_back(index);
					
					vbuffer.push_back(vertices[index].x);
					vbuffer.push_back(vertices[index].y);
					vbuffer.push_back(vertices[index].z);
					vbuffer.push_back(color.r);
					vbuffer.push_back(color.g);
					vbuffer.push_back(color.b);
				
					//Recuperando os indices de vts
					tokens[i] = tokens[i].substr(pos + 1);
					pos = tokens[i].find("/");
					token = tokens[i].substr(0, pos);
					index = atoi(token.c_str()) - 1;

					vbuffer.push_back(texCoords[index].s);
					vbuffer.push_back(texCoords[index].t);

					//Recuperando os indices de vns
					tokens[i] = tokens[i].substr(pos + 1);
					index = atoi(tokens[i].c_str()) - 1;

					vbuffer.push_back(normals[index].x);
					vbuffer.push_back(normals[index].y);
					vbuffer.push_back(normals[index].z);
				}
			}

		}

	}
	else
	{
		cout << "Problema ao encontrar o arquivo " << filepath << endl;
	}
	inputFile.close();

	GLuint VBO, VAO;

	nVerts = vbuffer.size() / 11; //Provis�rio

	//Gera��o do identificador do VBO
	glGenBuffers(1, &VBO);

	//Faz a conex�o (vincula) do buffer como um buffer de array
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//Envia os dados do array de floats para o buffer da OpenGl
	glBufferData(GL_ARRAY_BUFFER, vbuffer.size() * sizeof(GLfloat), vbuffer.data(), GL_STATIC_DRAW);

	//Gera��o do identificador do VAO (Vertex Array Object)
	glGenVertexArrays(1, &VAO);

	// Vincula (bind) o VAO primeiro, e em seguida  conecta e seta o(s) buffer(s) de v�rtices
	// e os ponteiros para os atributos 
	glBindVertexArray(VAO);

	//Para cada atributo do vertice, criamos um "AttribPointer" (ponteiro para o atributo), indicando: 
	// Localiza��o no shader * (a localiza��o dos atributos devem ser correspondentes no layout especificado no vertex shader)
	// Numero de valores que o atributo tem (por ex, 3 coordenadas xyz) 
	// Tipo do dado
	// Se est� normalizado (entre zero e um)
	// Tamanho em bytes 
	// Deslocamento a partir do byte zero 

	//Atributo posi��o (x, y, z)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Atributo cor (r, g, b)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//Atributo coordenada de textura (s, t)
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	//Atributo normal do v�rtice (x, y, z)
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(8 * sizeof(GLfloat)));
	glEnableVertexAttribArray(3);


	// Observe que isso � permitido, a chamada para glVertexAttribPointer registrou o VBO como o objeto de buffer de v�rtice 
	// atualmente vinculado - para que depois possamos desvincular com seguran�a
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Desvincula o VAO (� uma boa pr�tica desvincular qualquer buffer ou array para evitar bugs medonhos)
	glBindVertexArray(0);

	return VAO;

}

void loadSimpleMTL(string filepath)
{
	ifstream inputFile;
	inputFile.open(filepath.c_str());
	if (inputFile.is_open())
	{
		char line[100];
		string sline;

		while (!inputFile.eof())
		{
			inputFile.getline(line, 100);
			sline = line;

			string word;

			istringstream ssline(line);
			ssline >> word;

			//cout << word << " ";
			if (word == "Ns")
			{
				ssline >> q;//not sure

			}

			if (word == "Ka")
			{
				glm::vec3 kav;

				ssline >> kav.x >> kav.y >> kav.z;

				ka = (float)kav.x;
			}
			if (word == "Ks")
			{
				glm::vec3 ksv;

				ssline >> ksv.x >> ksv.y >> ksv.z;

				ks = ksv.x;
			}
			if (word == "Ke")
			{
				glm::vec3 ke;

				ssline >> ke.x >> ke.y >> ke.z;

				kd = ke.x;
			}
		}
	}
	else
	{
		cout << "Problema ao encontrar o arquivo " << filepath << endl;
	}
	inputFile.close();
}

