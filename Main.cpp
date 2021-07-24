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
		0.5f,  0.5f, 0.0f,  // верхняя правая
		 0.5f, -0.5f, 0.0f,  // нижняя правая
		-0.5f, -0.5f, 0.0f,  // нижняя левая
		-0.5f,  0.5f, 0.0f   // верхняя левая
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
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Создаём ссылки на контейнеры для 
	// Vertex Array Object и VertexBufferObject
	GLuint VBO, VAO;
	GLuint EBO;
	

	// Генерируем VAO и VBO только лишь с 1
	// объектом в каждом
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Сначала связываем объект вершинного массива, затем связываем и устанавливаем вершинный буфер(ы), и затем конфигурируем вершинный атрибут(ы)
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Обратите внимание, что данное действие разрешено, вызов glVertexAttribPointer() зарегистрировал VBO как привязанный вершинный буферный объект для вершинного атрибута, так что после этого мы можем спокойно выполнить отвязку
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// помните: не отвязывайте EBO, пока VАО активен, поскольку связанного объект буфера элемента хранится в VАО; сохраняйте привязку EBO.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Вы можете отменить привязку VАО после этого, чтобы другие вызовы VАО случайно не изменили этот VAO (но подобное довольно редко случается).
	// Модификация других VAO требует вызов glBindVertexArray(), поэтому мы обычно не снимаем привязку VAO (или VBO), когда это не требуется напрямую
	glBindVertexArray(0);

	
	

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
		/*glUseProgram(shaderProgram);
		// Связываем VAO с OpenGL
		glBindVertexArray(VAO);
		// Рисуем треугольник
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);*/

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		// Берутся во внимание все GLFW события
		glfwPollEvents();
	}

	// Удаляем все созданные объекты
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);
	//Удаляется из ОП созданное окно
	glfwDestroyWindow(window);
	//Закрывается GLFW
	glfwTerminate();
	return 0;
}