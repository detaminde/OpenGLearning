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
		0.5f,  0.5f, 0.0f,  // ������� ������
		 0.5f, -0.5f, 0.0f,  // ������ ������
		-0.5f, -0.5f, 0.0f,  // ������ �����
		-0.5f,  0.5f, 0.0f   // ������� �����
	};
	GLuint indices[] =
	{
		0,1,3,
		1,2,3
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

	// ������ ������ Vertex(���������) Shader � ������ ������
	GLuint vertexShader = 
		glCreateShader(GL_VERTEX_SHADER);
	// ����������� Vertex Shader � �������
	glShaderSource(vertexShader, 1, 
		&vertexShaderSource,
		NULL);
	// ����������� �� ��� ���� � �������� ���
	glCompileShader(vertexShader);

	int success; 
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS,
		&success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512,
			NULL, infoLog);
		std::cout << "Error: Shader Vertex compilation failed:\n" << infoLog << std::endl;
	}
	
	// ������ ������ Fragment(�����������) Shader � ������ ������
	GLuint fragmentShader =
		glCreateShader(GL_FRAGMENT_SHADER);
	// ����������� Fragment Shader � �������
	glShaderSource(fragmentShader, 1,
		&fragmentShaderSource, NULL);
	// ����������� �� ��� ���� � �������� ���
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS,
		&success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512,
			NULL, infoLog);
		std::cout << "Error: Shader Vertex compilation failed:\n" << infoLog << std::endl;
	}
	// ������ ���������, ������� ����� �������� � 
	// ��������� � ������ � ������
	GLuint shaderProgram = glCreateProgram();
	// ����������� ��������� ������� � ���������
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// ��������� �������� ��� ������� ������ � ���������
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "Error shader program linking failed\n" << infoLog
			<< std::endl;
	}
	//������� �������� �������, �.�. ��� ���� � ���������
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// ������ ������ �� ���������� ��� 
	// Vertex Array Object � VertexBufferObject
	GLuint VBO, VAO;
	GLuint EBO;
	

	// ���������� VAO � VBO ������ ���� � 1
	// �������� � ������
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// ������� ��������� ������ ���������� �������, ����� ��������� � ������������� ��������� �����(�), � ����� ������������� ��������� �������(�)
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// �������� ��������, ��� ������ �������� ���������, ����� glVertexAttribPointer() ��������������� VBO ��� ����������� ��������� �������� ������ ��� ���������� ��������, ��� ��� ����� ����� �� ����� �������� ��������� �������
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// �������: �� ����������� EBO, ���� V�� �������, ��������� ���������� ������ ������ �������� �������� � V��; ���������� �������� EBO.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// �� ������ �������� �������� V�� ����� �����, ����� ������ ������ V�� �������� �� �������� ���� VAO (�� �������� �������� ����� ���������).
	// ����������� ������ VAO ������� ����� glBindVertexArray(), ������� �� ������ �� ������� �������� VAO (��� VBO), ����� ��� �� ��������� ��������
	glBindVertexArray(0);

	
	

	// ����� ���� ������� ����
	//glClearColor(0.07f, 0.13f, 0.17f, 0);
	// ������� back-������ � ����� ��� ����� ����
	//glClear(GL_COLOR_BUFFER_BIT);
	// ������ ������� ������� � ����
	//glfwSwapBuffers(window);

	// ������� ����
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 0);
		glClear(GL_COLOR_BUFFER_BIT);
		//������� OpenGl ��� ������������� ��������� ��� ��������
		/*glUseProgram(shaderProgram);
		// ��������� VAO � OpenGL
		glBindVertexArray(VAO);
		// ������ �����������
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);*/

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		// ������� �� �������� ��� GLFW �������
		glfwPollEvents();
	}

	// ������� ��� ��������� �������
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);
	//��������� �� �� ��������� ����
	glfwDestroyWindow(window);
	//����������� GLFW
	glfwTerminate();
	return 0;
}