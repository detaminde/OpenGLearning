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
"layout (location = 0) in vec3 aPos;\n" //позиция атрибута, содержащая переменные координаты, уст = 0
"layout (location = 1) in vec3 aColor;\n"//позиция атрибута, содержащего переменные цвета, уст = 1
"out vec3 ourColor;\n" //значения цвета, передаваемое в фрагментный
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
//рисую треугольник
/*
int main()
{
	//инициализация GLFW
	glfwInit();

	// Говорим GLFW какую версию OpenGL мы используем
	// Мы используем версию 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Говорим GLFW, что мы используем CORE профиль
	// (используем только современные функции
	// в отличие от COMPAT, который использует все
	// функции)
	glfwWindowHint(GLFW_OPENGL_PROFILE,
		GLFW_OPENGL_CORE_PROFILE);

	GLfloat verticesFirstTriangle[] =
	{
		// Первый треугольник
		-0.9f, -0.5f, 0.0f,  // слева
		-0.0f, -0.5f, 0.0f,  // справа
		-0.45f, 0.5f, 0.0f,  // вверху
	};
	GLfloat verticesSecondTriangle[] =
	{
		// Второй треугольник
		 0.0f, -0.5f, 0.0f,  // слева
		 0.9f, -0.5f, 0.0f,  // справа
		 0.45f, 0.5f, 0.0f   // вверху
	};
	GLuint indices[] =
	{
		0,1,3,
		1,2,3
	};
	
	// Создаём окно GLFWwindow объект 800х800 пикселей
	GLFWwindow* window = glfwCreateWindow(800, 800,
		"Hello", NULL, NULL);
	// Проверка на возникновение ошибки
	if (window == NULL)
	{
		std::cout << "Error while creating GLFW window: " << std::endl;
		glfwTerminate();
		return -1;
	}
	// Представляем окно в текущий контекст
	glfwMakeContextCurrent(window);

	// Загружаем GLAD, который настраивает OpenGL
	gladLoadGL();

	// Уточняем границы вида OpenGL в окне
	// в данном случае границы вида идут от x = 0, 
	// y = 0 до x = 800, y = 800
	glViewport(0,0,800,800);

	// Создаём объект Vertex(вершинный) Shader и делаем ссылку
	GLuint vertexShader = 
		glCreateShader(GL_VERTEX_SHADER);
	// Прикрепляем Vertex Shader к объекту
	glShaderSource(vertexShader, 1, 
		&vertexShaderSource,
		NULL);
	// Компилируем всё это дело в машинный код
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
	
	// Создаём объект Fragment(фрагментный) Shader и делаем ссылку
	GLuint fragmentShader =
		glCreateShader(GL_FRAGMENT_SHADER);
	// Прикрепляем Fragment Shader к объекту
	glShaderSource(fragmentShader, 1,
		&fragmentShaderSource, NULL);
	// Компилируем всё это дело в машинный код
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS,
		&success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512,
			NULL, infoLog);
		std::cout << "Error: Shader Vertex compilation failed:\n" << infoLog << std::endl;
	}
	// Создаём программу, которая будет работать с 
	// шейдарами и создаём её ссылку
	GLuint shaderProgram = glCreateProgram();
	// Прикрепляем созданные шейдеры к программе
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Связываем ссылками все шейдеры вместе в программу
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "Error shader program linking failed\n" << infoLog
			<< std::endl;
	}
	//Удаляем ненужные шейдеры, т.к. они есть в программе
	glDeleteShader(fragmentShader);
	//создаём второй фрагментный шейдер
	GLuint fragmentShader2 =
		glCreateShader(GL_FRAGMENT_SHADER);
	// Прикрепляем Fragment Shader к объекту
	glShaderSource(fragmentShader2, 1,
		&fragmentShaderSource2, NULL);
	// Компилируем всё это дело в машинный код
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
	// Прикрепляем созданные шейдеры к программе
	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, fragmentShader2);
	// Связываем ссылками все шейдеры вместе в программу
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
	

	// Создаём ссылки на контейнеры для 
	// Vertex Array Object и VertexBufferObject
	GLuint VBO[2], VAO[2];
	//GLuint EBO;
	

	// Генерируем VAO и VBO только лишь с 1
	// объектом в каждом
	glGenVertexArrays(1, &VAO[0]);
	glGenBuffers(1, &VBO[0]);
	//glGenBuffers(1, &EBO);

	// Сначала связываем объект вершинного массива, затем связываем и устанавливаем вершинный буфер(ы), и затем конфигурируем вершинный атрибут(ы)
	glBindVertexArray(VAO[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesFirstTriangle), verticesFirstTriangle, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Обратите внимание, что данное действие разрешено, вызов glVertexAttribPointer() зарегистрировал VBO как привязанный вершинный буферный объект для вершинного атрибута, так что после этого мы можем спокойно выполнить отвязку
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// помните: не отвязывайте EBO, пока VАО активен, поскольку связанного объект буфера элемента хранится в VАО; сохраняйте привязку EBO.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Вы можете отменить привязку VАО после этого, чтобы другие вызовы VАО случайно не изменили этот VAO (но подобное довольно редко случается).
	// Модификация других VAO требует вызов glBindVertexArray(), поэтому мы обычно не снимаем привязку VAO (или VBO), когда это не требуется напрямую
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
	

	// задаём цвет заднего фона
	//glClearColor(0.07f, 0.13f, 0.17f, 0);
	// очищаем back-буффер и задаём ему новый цвет
	//glClear(GL_COLOR_BUFFER_BIT);
	// меняем буфферы местами в окне
	//glfwSwapBuffers(window);

	// главный цикл
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 0);
		glClear(GL_COLOR_BUFFER_BIT);
		//Говорим OpenGl про использование программы для шейдеров
		//glUseProgram(shaderProgram);
		// Связываем VAO с OpenGL
		//glBindVertexArray(VAO);
		// Рисуем треугольник
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
		// Берутся во внимание все GLFW события
		glfwPollEvents();
	}

	// Удаляем все созданные объекты
	glDeleteVertexArrays(1, VAO);
	glDeleteBuffers(1, VBO);
	//glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);
	//Удаляется из ОП созданное окно
	glfwDestroyWindow(window);
	//Закрывается GLFW
	glfwTerminate();
	return 0;
}
*/

//Работа с шейдерами
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
		// координаты       // цвета
	 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // нижняя правая вершина
	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // нижняя левая вершина
	 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // верхняя вершина
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
		// координаты        // цвета            // текстурные координаты
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // верхняя правая
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // нижняя правая
	   -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // нижняя левая
	   -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // верхняя левая 
	};
	unsigned int indices[] = 
	{
		0, 1, 3, // первый треугольник
		1, 2, 3  // второй треугольник
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

	//Создаём объект текстуры и связываем его
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Устанавливаем параметры наложения и 
	// фильтрации текстур (для текущего связанного объекта текстуры)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Загрузка и генерация текстуры
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
