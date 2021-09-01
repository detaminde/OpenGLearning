#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <Windows.h>

#include "shader_c.h"
#include "stb_image.h"
#include "camera.h"

const char* vertexShaderPath = "C:\\Users\\ka-564\\source\\repos\\LearningOpenGL\\LearningOpenGL\\shaders\\chapter 0\\vertexShader.txt";
const char* fragmentShaderPath = "C:\\Users\\ka-564\\source\\repos\\LearningOpenGL\\LearningOpenGL\\shaders\\chapter 0\\fragmentShader.txt";
const char* vertexShaderPath_1_colors = "C:\\Users\\ka-564\\source\\repos\\LearningOpenGL\\LearningOpenGL\\shaders\\chapter 1\\VertexShaders\\vertexShader_colors.txt";
const char* fragmentShaderPath_1_colors = "C:\\Users\\ka-564\\source\\repos\\LearningOpenGL\\LearningOpenGL\\shaders\\chapter 1\\FragmentShaders\\fragmentShader_colors.txt";
const char* vertexShaderPath_1_lamp = "C:\\Users\\ka-564\\source\\repos\\LearningOpenGL\\LearningOpenGL\\shaders\\chapter 1\\VertexShaders\\vertexShader_lamp.txt";
const char* fragmentShaderPath_1_lamp = "C:\\Users\\ka-564\\source\\repos\\LearningOpenGL\\LearningOpenGL\\shaders\\chapter 1\\FragmentShaders\\fragmentShader_lamp.txt";

const char* containerTexturePath = "C:\\Users\\ka-564\\source\\repos\\LearningOpenGL\\LearningOpenGL\\textures\\container.jpg";
const char* awesomefaceTexturePath = "C:\\Users\\ka-564\\source\\repos\\LearningOpenGL\\LearningOpenGL\\textures\\awesomeface.png";
const char* container2TexturePath = "C:\\Users\\ka-564\\source\\repos\\LearningOpenGL\\LearningOpenGL\\textures\\container.png";
const char* containerRamiTexturePath = "C:\\Users\\ka-564\\source\\repos\\LearningOpenGL\\LearningOpenGL\\textures\\container_rami.png";
const char* linesTexturePath = "C:\\Users\\ka-564\\source\\repos\\LearningOpenGL\\LearningOpenGL\\textures\\lines.jpg";

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
unsigned int load_texture(const char* texturePath);

// ���������
const unsigned int SCR_WIDTH = 600;
const unsigned int SCR_HEIGHT = 400;

// ������
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// ��������
float deltaTime = 0.0f;
float lastFrame = 0.0f;


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

//������ � ���������� � �� ��������������
/*
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
	glfwSetFramebufferSizeCallback(window, 
		framebuffer_size_callback);
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

	GLuint texture_container, texture_awesomeface;
	glGenTextures(1, &texture_container);

	glBindTexture(GL_TEXTURE_2D, texture_container);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
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

	glGenTextures(1, &texture_awesomeface);
	glBindTexture(GL_TEXTURE_2D, texture_awesomeface);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load(awesomefaceTexturePath, &width, &height,
		&nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
			0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	ourShader.use();
	glUniform1i(glGetUniformLocation(ourShader.ID, "texture_container"), 0);
	ourShader.setInt("texture_awesomeface", 1);

	
	

	bool flag = true;
	while (!glfwWindowShouldClose(window))
	{
		//processInput(window);
		

		glClearColor(0.07f, 0.13f, 0.17f, 0);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_container);
		glActiveTexture(GL_TEXTURE0 + 1);
		glBindTexture(GL_TEXTURE_2D, texture_awesomeface);

		glm::mat4 trans = glm::mat4(1.0f);
		
		trans = glm::translate(trans, 
			glm::vec3(0.5f, -0.5f, 0.0f));
		trans = glm::rotate(trans, (float)glfwGetTime(),
			glm::vec3(0.0f, 0.0f, 1.0f));

		
		
		ourShader.use();
		unsigned int transfromLoc =
			glGetUniformLocation(ourShader.ID, "transform");
		glUniformMatrix4fv(transfromLoc, 1,
			GL_FALSE, glm::value_ptr(trans));

		// � ������������� ����������� 
		// �������� ������ ������ ���������
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		trans = glm::mat4(1.0f); // ��������� ����� � ��������� �������
		trans = glm::translate(trans,
			glm::vec3(-0.5f, 0.5f, 0.0f));
		float scaleAmount = sin(glfwGetTime());
		trans = glm::scale(trans, 
			glm::vec3(scaleAmount, scaleAmount, scaleAmount));
		glUniformMatrix4fv(transfromLoc, 1, GL_FALSE, &trans[0][0]);
		// �� ���� ��� ������� ������ ������� ������� 
		// �������� ������� � �������� �������� ��������� 
		// ������

		// ������ � ������� ����������� ������� 
		// �� ����� �������������� ������ � �����
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
*/

//������ ��� �������� � 3D
//������ � �������
/*
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
	glfwSetFramebufferSizeCallback(window,
		framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	gladLoadGL();
	glViewport(0, 0, 800, 800);

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	unsigned int indices[] =
	{
		0, 1, 3, // ������ �����������
		1, 2, 3  // ������ �����������
	};
	
	Shader ourShader(vertexShaderPath, fragmentShaderPath);

	unsigned int VBO, VAO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);


	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
		vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
		5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	GLuint texture_container, texture_awesomeface;
	glGenTextures(1, &texture_container);

	glBindTexture(GL_TEXTURE_2D, texture_container);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
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

	glGenTextures(1, &texture_awesomeface);
	glBindTexture(GL_TEXTURE_2D, texture_awesomeface);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load(awesomefaceTexturePath, &width, &height,
		&nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
			0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	

	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	ourShader.use();
	glUniform1i(glGetUniformLocation(ourShader.ID, "texture_container"), 0);
	ourShader.setInt("texture_awesomeface", 1);


	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);


		glClearColor(0.07f, 0.13f, 0.17f, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_container);
		glActiveTexture(GL_TEXTURE0 + 1);
		glBindTexture(GL_TEXTURE_2D, texture_awesomeface);

		ourShader.use();

		//����� ����� ��������� ����� �����,
		// ��� � �������� ���������� ����� � ������� ������������
		
		glm::mat4 projection = 
			glm::perspective(glm::radians(camera.Zoom), 
			(float)800.0f/ (float)800.0f, 0.1f, 100.0f);
		ourShader.setMat4("projection", projection);

		
		glm::mat4 view = camera.GetViewMatrix();
		ourShader.setMat4("view", view);

		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 25.0f * i;
			model = glm::rotate(model, (float)glfwGetTime()*glm::radians(angle),
				glm::vec3(1.0f, 0.3f, 0.5f));
			ourShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}
*/


//����� 1, ���������
int main()
{
	// glfw: ������������� � ����������������
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // ���������������� ��� ������, ���� ����������� macOS
#endif

	// glfw: �������� ����
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL for Ravesli.com", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// �������� GLFW, ����� �� �������� ��� ������
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: �������� ���� ���������� �� OpenGL-�������
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// ���������������� ����������� ��������� OpenGL
	glEnable(GL_DEPTH_TEST);

	// �������������� ����� ��������� ���������
	Shader lightingShader(vertexShaderPath_1_colors, fragmentShaderPath_1_colors);
	Shader lightCubeShader(vertexShaderPath_1_lamp, fragmentShaderPath_1_lamp);

	// �������� ������ (� ������(��)) � ��������� ��������� ���������
	float vertices[] = 
	{
		// ����������        // �������           // ���������� ����������
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};

	// ���������� ���� �����������
	glm::vec3 cubePositions[] = 
	{
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	glm::vec3 pointLightPositions[] = 
	{
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};

	// 1. ����������� VAO (� VBO) ����
	unsigned int VBO, cubeVAO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(cubeVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// 2. ����������� VAO ����� (VBO �������� ����������; ������� �� �� � ��� ��������� �������, ������� ����� �������� 3D-�����)
	unsigned int lightCubeVAO;;
	glGenVertexArrays(1, &lightCubeVAO);
	glBindVertexArray(lightCubeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// �������� ��������, ��� �� ��������� ��� �������� ��������� �����, ����� �������� ����������� ������ ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// �������� �������
	unsigned int diffuseMap = load_texture(container2TexturePath);
	unsigned int specularMap = load_texture(containerRamiTexturePath);

	// ������������ ��������
	lightingShader.use();
	lightingShader.setInt("material.diffuse", 0);
	lightingShader.setInt("material.specular", 1);

	// ���� ����������
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// ��������� �����
		processInput(window);

		// ���������
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// ����������, ��� ������������ ������ ������, ��� ����������� uniform-����������/�������_���������
		lightingShader.use();
		lightingShader.setVec3("viewPos", camera.Position);
		lightingShader.setFloat("material.shininess", 32.0f);


		// ������������ ����
		lightingShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
		lightingShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
		lightingShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
		lightingShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

		// �������� �������� ����� �1
		lightingShader.setVec3("pointLights[0].position", pointLightPositions[0]);
		lightingShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
		lightingShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
		lightingShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
		lightingShader.setFloat("pointLights[0].constant", 1.0f);
		lightingShader.setFloat("pointLights[0].linear", 0.09);
		lightingShader.setFloat("pointLights[0].quadratic", 0.032);

		// �������� �������� ����� �2
		lightingShader.setVec3("pointLights[1].position", pointLightPositions[1]);
		lightingShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
		lightingShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
		lightingShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
		lightingShader.setFloat("pointLights[1].constant", 1.0f);
		lightingShader.setFloat("pointLights[1].linear", 0.09);
		lightingShader.setFloat("pointLights[1].quadratic", 0.032);

		// �������� �������� ����� �3
		lightingShader.setVec3("pointLights[2].position", pointLightPositions[2]);
		lightingShader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
		lightingShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
		lightingShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
		lightingShader.setFloat("pointLights[2].constant", 1.0f);
		lightingShader.setFloat("pointLights[2].linear", 0.09);
		lightingShader.setFloat("pointLights[2].quadratic", 0.032);

		// �������� �������� ����� �4
		lightingShader.setVec3("pointLights[3].position", pointLightPositions[3]);
		lightingShader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
		lightingShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
		lightingShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
		lightingShader.setFloat("pointLights[3].constant", 1.0f);
		lightingShader.setFloat("pointLights[3].linear", 0.09);
		lightingShader.setFloat("pointLights[3].quadratic", 0.032);

		// �������������� ����/��������
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		lightingShader.setMat4("projection", projection);
		lightingShader.setMat4("view", view);

		// ������� ��������������
		glm::mat4 model = glm::mat4(1.0f);
		lightingShader.setMat4("model", model);

		// ���������� ��������� �����
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);

		// ���������� ����� ����������� �����
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap);

		// ��������� �����������
		
		for (unsigned int i = 0; i < 10; i++)
		{
			glBindVertexArray(cubeVAO);
			// ��������� ������� ������ ��� ������� ������� � �������� � � ������
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			lightingShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// ����� ������������ ������ �����
		lightCubeShader.use();
		lightCubeShader.setMat4("projection", projection);
		lightCubeShader.setMat4("view", view);

		// � ������ �� ������������ ������� ����, ������� � ��� ���� �������� ���������� �����
		glBindVertexArray(lightCubeVAO);
		for (unsigned int i = 0; i < 4; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f)); // ������� ���
			lightCubeShader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// glfw: ����� ���������� front- � back- �������. ������������ ������� �����/������ (���� �� ������/�������� ������, ��������� ������ ���� � �.�.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// �����������: ����������� ��� �������, ��� ������ ��� ��������� ���� ��������������
	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &lightCubeVAO);
	glDeleteBuffers(1, &VBO);

	// glfw: ����������, ������������ ���� ���������� ����� GLFW-��c�����
	glfwTerminate();
	return 0;
}

// ��������� ���� ������� �����: ������ GLFW � �������/���������� ������ ���� � ������ ����� � ��������������� ��������� ������ �������
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: ������ ���, ����� ���������� ������� ���� (������������� ��� ������������ ��������), ���������� ������ callback-�������
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// ����������, ��� ���� ��������� ������������� ����� �������� ����.
	// �������� ��������, ������ � ������ ����� ����������� ������, ��� �������, �� Retina-��������
	glViewport(0, 0, width, height);
}


// glfw: ������ ���, ����� ������������ ����, ���������� ������ callback-�������
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // �����������, ��� ��� y-���������� ���� ����� �����

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: ������ ���, ����� �������������� �������� ����, ���������� ������ callback-�������
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

// ������� ��� �������� 2D-�������� �� �����
unsigned int load_texture(char const* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}
