#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Windows.h>

#include "shader_c.h"
#include "stb_image.h"

const char* vertexShaderPath = "C:\\Users\\ka-564\\source\\repos\\LearningOpenGL\\LearningOpenGL\\vertexShader.txt";
const char* fragmentShaderPath = "C:\\Users\\ka-564\\source\\repos\\LearningOpenGL\\LearningOpenGL\\fragmentShader.txt";
const char* containerTexturePath = "C:\\Users\\ka-564\\source\\repos\\LearningOpenGL\\LearningOpenGL\\container.jpg";
/*// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n" //������� ��������, ���������� ���������� ����������, ��� = 0
"layout (location = 1) in vec3 aColor;\n"//������� ��������, ����������� ���������� �����, ��� = 1
"out vec3 ourColor;\n" //�������� �����, ������������ � �����������
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"ourColor = aColor;\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(ourColor,1.0);\n"
"}\0";*/

/*const char* fragmentShaderSource2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\n\0";*/
//����� �����������
/*
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

	GLfloat verticesFirstTriangle[] =
	{
		// ������ �����������
		-0.9f, -0.5f, 0.0f,  // �����
		-0.0f, -0.5f, 0.0f,  // ������
		-0.45f, 0.5f, 0.0f,  // ������
	};
	GLfloat verticesSecondTriangle[] =
	{
		// ������ �����������
		 0.0f, -0.5f, 0.0f,  // �����
		 0.9f, -0.5f, 0.0f,  // ������
		 0.45f, 0.5f, 0.0f   // ������
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
	glDeleteShader(fragmentShader);
	//������ ������ ����������� ������
	GLuint fragmentShader2 =
		glCreateShader(GL_FRAGMENT_SHADER);
	// ����������� Fragment Shader � �������
	glShaderSource(fragmentShader2, 1,
		&fragmentShaderSource2, NULL);
	// ����������� �� ��� ���� � �������� ���
	glCompileShader(fragmentShader2);

	glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS,
		&success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader2, 512,
			NULL, infoLog);
		std::cout << "Error: Shader Vertex compilation failed:\n" << infoLog << std::endl;
	}

	GLuint shaderProgram2 = glCreateProgram();
	// ����������� ��������� ������� � ���������
	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, fragmentShader2);
	// ��������� �������� ��� ������� ������ � ���������
	glLinkProgram(shaderProgram2);
	glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog);
		std::cout << "Error shader program linking failed\n" << infoLog
			<< std::endl;
	}
	glDeleteShader(fragmentShader2);
	glDeleteShader(vertexShader);
	

	// ������ ������ �� ���������� ��� 
	// Vertex Array Object � VertexBufferObject
	GLuint VBO[2], VAO[2];
	//GLuint EBO;
	

	// ���������� VAO � VBO ������ ���� � 1
	// �������� � ������
	glGenVertexArrays(1, &VAO[0]);
	glGenBuffers(1, &VBO[0]);
	//glGenBuffers(1, &EBO);

	// ������� ��������� ������ ���������� �������, ����� ��������� � ������������� ��������� �����(�), � ����� ������������� ��������� �������(�)
	glBindVertexArray(VAO[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesFirstTriangle), verticesFirstTriangle, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// �������� ��������, ��� ������ �������� ���������, ����� glVertexAttribPointer() ��������������� VBO ��� ����������� ��������� �������� ������ ��� ���������� ��������, ��� ��� ����� ����� �� ����� �������� ��������� �������
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// �������: �� ����������� EBO, ���� V�� �������, ��������� ���������� ������ ������ �������� �������� � V��; ���������� �������� EBO.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// �� ������ �������� �������� V�� ����� �����, ����� ������ ������ V�� �������� �� �������� ���� VAO (�� �������� �������� ����� ���������).
	// ����������� ������ VAO ������� ����� glBindVertexArray(), ������� �� ������ �� ������� �������� VAO (��� VBO), ����� ��� �� ��������� ��������
	glBindVertexArray(0);

	/*glGenVertexArrays(1, &VAO[1]);
	glGenBuffers(1, &VBO[1]);

	glBindVertexArray(VAO[1]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesSecondTriangle), 
	verticesSecondTriangle, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 
		3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	

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
		//glUseProgram(shaderProgram);
		// ��������� VAO � OpenGL
		//glBindVertexArray(VAO);
		// ������ �����������
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//glBindVertexArray(0);

		//glfwSwapBuffers(window);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO[0]);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		/*glUseProgram(shaderProgram2);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		glfwSwapBuffers(window);
		// ������� �� �������� ��� GLFW �������
		glfwPollEvents();
	}

	// ������� ��� ��������� �������
	glDeleteVertexArrays(1, VAO);
	glDeleteBuffers(1, VBO);
	//glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);
	//��������� �� �� ��������� ����
	glfwDestroyWindow(window);
	//����������� GLFW
	glfwTerminate();
	return 0;
}
*/

//������ � ���������
/*
int main()
{
	
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,
		GLFW_OPENGL_CORE_PROFILE);

	GLfloat verticesFirstTriangle[] =
	{
		// ����������       // �����
	 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // ������ ������ �������
	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // ������ ����� �������
	 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // ������� �������
	};
	
	GLFWwindow* window = glfwCreateWindow(800, 800,
		"Hello", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Error while creating GLFW window: " << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, 800, 800);

	Shader ourShader("C:\\Users\\ka-564\\source\\repos\\LearningOpenGL\\LearningOpenGL\\vertexShader.txt",
		"C:\\Users\\ka-564\\source\\repos\\LearningOpenGL\\LearningOpenGL\\fragmentShader.txt");
	float offset = 0.5f;
	

	GLuint VBO[2], VAO[2];

	glGenVertexArrays(1, &VAO[0]);
	glGenBuffers(1, &VBO[0]);

	glBindVertexArray(VAO[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesFirstTriangle), 
		verticesFirstTriangle, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 
		6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
		6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 0);
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader.use();
		//ourShader.setFloat("xOffset", offset);

		GLfloat timeValue = glfwGetTime();
		GLfloat greenValue = (cos(timeValue) / 2.0f + 0.5f);
		GLint vertexColorLocation = glGetUniformLocation(ourShader.ID, 
			"Color");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		Sleep(1000 / 60);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, VAO);
	glDeleteBuffers(1, VBO);
	//glDeleteProgram(shaderProgram);
	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}*/

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,
		GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800,
		"Hello", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Error while creating GLFW window: " << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, 800, 800);

	float vertices[] = {
		// ����������        // �����            // ���������� ����������
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ������� ������
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ������ ������
	   -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ������ �����
	   -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ������� ����� 
	};
	unsigned int indices[] = 
	{
		0, 1, 3, // ������ �����������
		1, 2, 3  // ������ �����������
	};
	Shader ourShader(vertexShaderPath, fragmentShaderPath);

	unsigned int VBO, VAO, EBO;
	
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), 
		vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),
		indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
		8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
		8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//������ ������ �������� � ��������� ���
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// ������������� ��������� ��������� � 
	// ���������� ������� (��� �������� ���������� ������� ��������)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// �������� � ��������� ��������
	int width, height, nrChannels;
	unsigned char* data = stbi_load(containerTexturePath,
		&width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
			GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 0);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindTexture(GL_TEXTURE_2D, texture);
		ourShader.use();

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		Sleep(1000 / 60);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}
