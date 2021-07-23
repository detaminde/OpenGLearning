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

	GLfloat vertices[] =
	{
		-0.5f, -0.5 * float(sqrt(3)) / 3, 0.0f, //нижний левый угол
		0.5f, -0.5 * float(sqrt(3)) / 3, 0.0f, //нижний правый угол
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f //верхний угол
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

	// Создаём объект Vertex Shader и делаем ссылку
	GLuint vertexShader = 
		glCreateShader(GL_VERTEX_SHADER);
	// Прикрепляем Vertex Shader к объекту
	glShaderSource(vertexShader, 1, 
		&vertexShaderSource,
		NULL);
	// Компилируем всё это дело в машинный код
	glCompileShader(vertexShader);

	// Создаём объект Fragment Shader и делаем ссылку
	GLuint fragmentShader =
		glCreateShader(GL_FRAGMENT_SHADER);
	// Прикрепляем Fragment Shader к объекту
	glShaderSource(fragmentShader, 1,
		&fragmentShaderSource, NULL);
	// Компилируем всё это дело в машинный код
	glCompileShader(fragmentShader);

	// Создаём программу, которая будет работать с 
	// шейдарами и создаём её ссылку
	GLuint shaderProgram = glCreateProgram();
	// Прикрепляем созданные шейдеры к программе
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Связываем ссылками все шейдеры вместе в программу
	glLinkProgram(shaderProgram);
	//Удаляем ненужные шейдеры, т.к. они есть в программе
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Создаём ссылки на контейнеры для 
	// Vertex Array Object и VertexBufferObject
	GLuint VBO, VAO;

	// Генерируем VAO и VBO только лишь с 1
	// объектом в каждом
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Делаем VAO текущим Vertex Array Object
	// связыванием
	glBindVertexArray(VAO);
	// Связываем VBO уточняя про GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Представляем вершины в VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
		vertices, GL_STATIC_DRAW);

	// Настраиваем Vertex Attribute так, чтобы OpenGL
	// знал как читать VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		3 * sizeof(float), (void*)0);
	// Разрешаем Vertex Attribute так, чтобы 
	// OpenGL знал как его использовать
	glEnableVertexAttribArray(0);

	// Связываем оба VBO & VAO к нулю, чтобы мы не могли 
	// ежемоментно их модифицировать
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// задаём цвет заднего фона
	glClearColor(0.07f, 0.13f, 0.17f, 0);
	// очищаем back-буффер и задаём ему новый цвет
	glClear(GL_COLOR_BUFFER_BIT);
	// меняем буфферы местами в окне
	glfwSwapBuffers(window);

	// главный цикл
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 0);
		glClear(GL_COLOR_BUFFER_BIT);
		//Говорим OpenGl про использование программы для шейдеров
		glUseProgram(shaderProgram);
		// Связываем VAO с OpenGL
		glBindVertexArray(VAO);
		// Рисуем треугольник
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);

		// Берутся во внимание все GLFW события
		glfwPollEvents();
	}

	// Удаляем все созданные объекты
	glDeleteVertexArrays(1, &VAO);
	glDeleteProgram(shaderProgram);
	//Удаляется из ОП созданное окно
	glfwDestroyWindow(window);
	//Закрывается GLFW
	glfwTerminate();
	return 0;
}