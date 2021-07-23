#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main()
{
	//������������� GLFW
	glfwInit();

	// ������� GLFW ����� ������ OpenGL �� ����������
	// �� ���������� ������ 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// ������� GLFW, ��� �� ���������� CORE �������
	// (���������� ������ ����������� �������
	// � ������� �� COMPAT, ������� ���������� ���
	// �������)
	glfwWindowHint(GLFW_OPENGL_PROFILE,
		GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] =
	{
		-0.5f, -0.5 * float(sqrt(3)) / 3, 0.0f, //������ ����� ����
		0.5f, -0.5 * float(sqrt(3)) / 3, 0.0f, //������ ������ ����
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f //������� ����
	};
	
	// ������ ���� GLFWwindow ������ 800�800 ��������
	GLFWwindow* window = glfwCreateWindow(800, 800,
		"Hello", NULL, NULL);
	// �������� �� ������������� ������
	if (window == NULL)
	{
		std::cout << "Error while creating GLFW window: " << std::endl;
		glfwTerminate();
		return -1;
	}
	// ������������ ���� � ������� ��������
	glfwMakeContextCurrent(window);

	// ��������� GLAD, ������� ����������� OpenGL
	gladLoadGL();

	// �������� ������� ���� OpenGL � ����
	// � ������ ������ ������� ���� ���� �� x = 0, 
	// y = 0 �� x = 800, y = 800
	glViewport(0,0,800,800);

	// ������ ������ Vertex Shader � ������ ������
	GLuint vertexShader = 
		glCreateShader(GL_VERTEX_SHADER);
	// ����������� Vertex Shader � �������
	glShaderSource(vertexShader, 1, 
		&vertexShaderSource,
		NULL);
	// ����������� �� ��� ���� � �������� ���
	glCompileShader(vertexShader);

	// ������ ������ Fragment Shader � ������ ������
	GLuint fragmentShader =
		glCreateShader(GL_FRAGMENT_SHADER);
	// ����������� Fragment Shader � �������
	glShaderSource(fragmentShader, 1,
		&fragmentShaderSource, NULL);
	// ����������� �� ��� ���� � �������� ���
	glCompileShader(fragmentShader);

	// ������ ���������, ������� ����� �������� � 
	// ��������� � ������ � ������
	GLuint shaderProgram = glCreateProgram();
	// ����������� ��������� ������� � ���������
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// ��������� �������� ��� ������� ������ � ���������
	glLinkProgram(shaderProgram);
	//������� �������� �������, �.�. ��� ���� � ���������
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// ������ ������ �� ���������� ��� 
	// Vertex Array Object � VertexBufferObject
	GLuint VBO, VAO;

	// ���������� VAO � VBO ������ ���� � 1
	// �������� � ������
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// ������ VAO ������� Vertex Array Object
	// �����������
	glBindVertexArray(VAO);
	// ��������� VBO ������� ��� GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// ������������ ������� � VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
		vertices, GL_STATIC_DRAW);

	// ����������� Vertex Attribute ���, ����� OpenGL
	// ���� ��� ������ VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		3 * sizeof(float), (void*)0);
	// ��������� Vertex Attribute ���, ����� 
	// OpenGL ���� ��� ��� ������������
	glEnableVertexAttribArray(0);

	// ��������� ��� VBO & VAO � ����, ����� �� �� ����� 
	// ����������� �� ��������������
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// ����� ���� ������� ����
	glClearColor(0.07f, 0.13f, 0.17f, 0);
	// ������� back-������ � ����� ��� ����� ����
	glClear(GL_COLOR_BUFFER_BIT);
	// ������ ������� ������� � ����
	glfwSwapBuffers(window);

	// ������� ����
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 0);
		glClear(GL_COLOR_BUFFER_BIT);
		//������� OpenGl ��� ������������� ��������� ��� ��������
		glUseProgram(shaderProgram);
		// ��������� VAO � OpenGL
		glBindVertexArray(VAO);
		// ������ �����������
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);

		// ������� �� �������� ��� GLFW �������
		glfwPollEvents();
	}

	// ������� ��� ��������� �������
	glDeleteVertexArrays(1, &VAO);
	glDeleteProgram(shaderProgram);
	//��������� �� �� ��������� ����
	glfwDestroyWindow(window);
	//����������� GLFW
	glfwTerminate();
	return 0;
}