#include <iostream>
//#include <Windows.h>
//#include <time.h>
#include <vector>
//#include <memory>
//#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "SOIL.h"

#include <set>
#include <map>


using namespace std;

#pragma comment(lib, "glew32.lib")

void key_callback(GLFWwindow* w, int key, int scancode, int action, int node) {
	cout << "Key: " << key << endl;
}

const GLuint W = 800, H = 600;

const GLchar* vertexShaderSource =
"#version 330\n"
"uniform vec4 coord;\n"
"uniform vec2 N;\n"
"layout(location = 0) in vec3 a_position;\n"
"layout(location = 1) in vec2 a_uv;\n"

"out vec2 TexCoord;\n"

"void main()\n"
"{\n"
"gl_Position = vec4(a_position,1.0)*coord;\n"
"TexCoord = a_uv;\n"
"}\0";

const GLchar* fragmentShaderSource =
"#version 330\n"
"out vec4 color;\n"
"uniform vec2 N;\n"

"uniform sampler2D tex_AAA;\n"

"in vec2 TexCoord;\n"

"void main()\n"
"{\n"
"color = texture(tex_AAA, TexCoord)*N.yyyy;\n"
"}\n\0";

//const GLchar* vertexShaderSource2 =
//"uniform vec4 coord;\n"
//"uniform vec2 N;\n"
//"in vec3 a_position;\n"
//
//
//"void main()\n"
//"{\n"
//"gl_Position = vec4(a_position,1.0)*coord;\n"
//"}\0";

void mouse_callback(GLFWwindow* w, int key, int scancode, int action) {
	cout << "Mouse: " << key << endl;

	
}


GLuint createProgram(const char** vsrc, const char** fsrc) {
	GLint success;
	GLchar infoLog[512];

	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, vsrc, nullptr);
	glCompileShader(vShader);

	glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vShader, 512, nullptr, infoLog);
		cout << "Error::shader::v\n" << infoLog << endl;
	}

	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, fsrc, nullptr);
	glCompileShader(fShader);

	glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fShader, 512, nullptr, infoLog);
		cout << "Error::shader::f\n" << infoLog << endl;
	}

	GLuint program_A = glCreateProgram();
	glAttachShader(program_A, vShader);
	glAttachShader(program_A, fShader);
	glLinkProgram(program_A);

	glGetProgramiv(program_A, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program_A, 512, nullptr, infoLog);
		cout << "program::infoLog: " << infoLog << endl;
	}
	glDeleteShader(vShader);
	glDeleteShader(fShader);

	return program_A;
}

int main() {
	GLFWwindow* window;

	if (!glfwInit()) {
		return -1;
	}
	window = glfwCreateWindow(1136, 640, "hello AA", nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		cout << "window failed." << endl;
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_callback);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		cout << "glew failed." << endl;
		return -1;
	}

	//glProgramUniform1f()

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	GLint size_A;

	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &size_A);
	cout << "GL_FRAMEBUFFER_BINDING: " << size_A << endl;
	glGetIntegerv(GL_MAX_VARYING_VECTORS, &size_A);
	cout << "GL_MAX_VARYING_VECTORS: " << size_A << endl;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &size_A);
	cout << "GL_MAX_VERTEX_ATTRIBS: " << size_A << endl;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &size_A);
	cout << "GL_MAX_TEXTURE_SIZE: " << size_A << endl;
	glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &size_A);
	cout << "GL_MAX_VERTEX_UNIFORM_COMPONENTS: " << size_A << endl;
	glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, &size_A);
	cout << "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS: " << size_A << endl;


	// culling
	glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
	glFrontFace(GL_CW);

	// viewport
	glViewport(0, 80, width - 100, height - 100);

	/* GLuint fb;
	glGenFramebuffers(1, &fb);
	glBindFramebuffer(GL_FRAMEBUFFER, fb);

	GLenum fbStatus;

	//fbStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	//if (fbStatus == GL_FRAMEBUFFER_COMPLETE) {
	//	cout << "fbstatus" << endl;
	//};

	GLuint tex_R;
	glGenTextures(1, &tex_R);
	glBindTexture(GL_TEXTURE_2D, tex_R);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex_R, 0);

	fbStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (fbStatus == GL_FRAMEBUFFER_COMPLETE) {
		cout << "fbstatus" << endl;
	};

	glBindFramebuffer(GL_FRAMEBUFFER, 0);*/

	// shader
	GLuint program_A;
	//GLuint program_B;

	program_A = createProgram(&vertexShaderSource, &fragmentShaderSource);
	//program_B = createProgram(&vertexShaderSource2, &fragmentShaderSource);

	// texture
	int texW;
	int texH;
	unsigned char* image = SOIL_load_image("img_test.jpg", &texW, &texH, 0, SOIL_LOAD_RGB);

	GLuint tex_A;
	glGenTextures(1, &tex_A);
	glBindTexture(GL_TEXTURE_2D, tex_A);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texW, texH, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	//glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	



	//GL_MIRRORED_REPEAT

	//glActiveTexture()

	//glActiveTexture(GL_TEXTURE0);

	// vertex
	GLfloat vertices[] =
	{
		-1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f
	};
	GLfloat UV[] =
	{
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f
	};
	// indice
	GLuint indices[] =
	{
		0,1,2, 1,3,2
		//0,2,1,1,2,3
	};

	GLuint vbo, vbo2, ebo, vao;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo); 
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &vbo2);
	glBindBuffer(GL_ARRAY_BUFFER, vbo2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(UV), UV, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);

	GLsizei r1;
	GLint r2;
	GLenum r3;
	GLchar r4[30];

	glGetActiveAttrib(program_A, 0, 30, &r1, &r2, &r3, r4);
	cout << r1 << " | " << r2 << " | " << " | " << r3 << " | " << r4 << endl;

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), nullptr, GL_DYNAMIC_DRAW);

	void* pb = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
	memcpy(pb, indices, sizeof(indices));
	cout << pb << endl;
	GLuint* fb = (GLuint*)pb;
	cout << *fb << *(fb + 1) << *(fb + 2) << *(fb + 3) << *(fb + 4) << *(fb + 5) << endl;
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	




	GLint pv;

	//glGetIntegerv(GL_VERTEX_ATTRIB_ARRAY_ENABLED, &pv);
	//cout << "enabled: " << pv << endl;

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glGetVertexAttribiv()

	//glGetBufferPointerv(GL_ARRAY_BUFFER, )

	glGetProgramiv(program_A, GL_ACTIVE_UNIFORM_MAX_LENGTH, &pv);
	cout << "u: " << pv << endl;

	glGetProgramiv(program_A, GL_ACTIVE_UNIFORMS, &pv);
	cout << "u: " << pv << endl;

	glGetProgramiv(program_A, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &pv);
	cout << "v: " << pv << endl;

	//glGetProgramiv(program_A, GL_ACTIVE_TEXTURE ,&pv);
	//cout << "v: " << pv << endl;

	//glUseProgram(program_A);
	//GLint loca = glGetUniformLocation(program_A, "coord");
	//glUniform4f(loca, 0.5, 0.5, 0.5, 1);
	//loca = glGetUniformLocation(program_A, "N");
	//glUniform2f(loca, 0.3, 1.0);
	
	GLint location_A = glGetUniformLocation(program_A, "coord");
	glProgramUniform4f(program_A, location_A, 0.5, 0.5, 0.5, 1);

	location_A = glGetUniformLocation(program_A, "N");
	glProgramUniform2f(program_A, location_A, 0.3, 1.0);

	//set<int> c;
	//c.insert(1);
	//c.insert(2);
	//c.insert(6);
	//c.insert(8);
	//c.insert(2);
	//c.insert(9);

	map<string, float> coll;

	auto item = coll.begin();
	
	for (auto& elem : coll) {
		//elem.
	}


	int count;

	while (!glfwWindowShouldClose(window)) {

		glfwPollEvents();

		glClearColor(0.6f, 0.0f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program_A);
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);


	 	glfwSwapBuffers(window);


	}

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);

	glfwTerminate();

	return 0;

	//system("PAUSE");

}

