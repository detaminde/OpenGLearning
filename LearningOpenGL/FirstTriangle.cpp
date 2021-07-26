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
	//èíèöèàëèçàöèÿ GLFW
	glfwInit();

	// Ãîâîðèì GLFW êàêóþ âåðñèþ OpenGL ìû èñïîëüçóåì
	// Ìû èñïîëüçóåì âåðñèþ 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Ãîâîðèì GLFW, ÷òî ìû èñïîëüçóåì CORE ïðîôèëü
	// (èñïîëüçóåì òîëüêî ñîâðåìåííûå ôóíêöèè
	// â îòëè÷èå îò COMPAT, êîòîðûé èñïîëüçóåò âñå
	// ôóíêöèè)
	glfwWindowHint(GLFW_OPENGL_PROFILE,
		GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] =
	{
		-0.5f, -0.5 * float(sqrt(3)) / 3, 0.0f, //íèæíèé ëåâûé óãîë
		0.5f, -0.5 * float(sqrt(3)) / 3, 0.0f, //íèæíèé ïðàâûé óãîë
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f //âåðõíèé óãîë
	};
	
	// Ñîçäà¸ì îêíî GLFWwindow îáúåêò 800õ800 ïèêñåëåé
	GLFWwindow* window = glfwCreateWindow(800, 800,
		"Hello", NULL, NULL);
	// Ïðîâåðêà íà âîçíèêíîâåíèå îøèáêè
	if (window == NULL)
	{
		std::cout << "Error while creating GLFW window: " << std::endl;
		glfwTerminate();
		return -1;
	}
	// Ïðåäñòàâëÿåì îêíî â òåêóùèé êîíòåêñò
	glfwMakeContextCurrent(window);

	// Çàãðóæàåì GLAD, êîòîðûé íàñòðàèâàåò OpenGL
	gladLoadGL();

	// Óòî÷íÿåì ãðàíèöû âèäà OpenGL â îêíå
	// â äàííîì ñëó÷àå ãðàíèöû âèäà èäóò îò x = 0, 
	// y = 0 äî x = 800, y = 800
	glViewport(0,0,800,800);

	// Ñîçäà¸ì îáúåêò Vertex Shader è äåëàåì ññûëêó
	GLuint vertexShader = 
		glCreateShader(GL_VERTEX_SHADER);
	// Ïðèêðåïëÿåì Vertex Shader ê îáúåêòó
	glShaderSource(vertexShader, 1, 
		&vertexShaderSource,
		NULL);
	// Êîìïèëèðóåì âñ¸ ýòî äåëî â ìàøèííûé êîä
	glCompileShader(vertexShader);

	// Ñîçäà¸ì îáúåêò Fragment Shader è äåëàåì ññûëêó
	GLuint fragmentShader =
		glCreateShader(GL_FRAGMENT_SHADER);
	// Ïðèêðåïëÿåì Fragment Shader ê îáúåêòó
	glShaderSource(fragmentShader, 1,
		&fragmentShaderSource, NULL);
	// Êîìïèëèðóåì âñ¸ ýòî äåëî â ìàøèííûé êîä
	glCompileShader(fragmentShader);

	// Ñîçäà¸ì ïðîãðàììó, êîòîðàÿ áóäåò ðàáîòàòü ñ 
	// øåéäàðàìè è ñîçäà¸ì å¸ ññûëêó
	GLuint shaderProgram = glCreateProgram();
	// Ïðèêðåïëÿåì ñîçäàííûå øåéäåðû ê ïðîãðàììå
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Ñâÿçûâàåì ññûëêàìè âñå øåéäåðû âìåñòå â ïðîãðàììó
	glLinkProgram(shaderProgram);
	//Óäàëÿåì íåíóæíûå øåéäåðû, ò.ê. îíè åñòü â ïðîãðàììå
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Ñîçäà¸ì ññûëêè íà êîíòåéíåðû äëÿ 
	// Vertex Array Object è VertexBufferObject
	GLuint VBO, VAO;

	// Ãåíåðèðóåì VAO è VBO òîëüêî ëèøü ñ 1
	// îáúåêòîì â êàæäîì
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Äåëàåì VAO òåêóùèì Vertex Array Object
	// ñâÿçûâàíèåì
	glBindVertexArray(VAO);
	// Ñâÿçûâàåì VBO óòî÷íÿÿ ïðî GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Ïðåäñòàâëÿåì âåðøèíû â VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
		vertices, GL_STATIC_DRAW);

	// Íàñòðàèâàåì Vertex Attribute òàê, ÷òîáû OpenGL
	// çíàë êàê ÷èòàòü VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		3 * sizeof(float), (void*)0);
	// Ðàçðåøàåì Vertex Attribute òàê, ÷òîáû 
	// OpenGL çíàë êàê åãî èñïîëüçîâàòü
	glEnableVertexAttribArray(0);

	// Ñâÿçûâàåì îáà VBO & VAO ê íóëþ, ÷òîáû ìû íå ìîãëè 
	// åæåìîìåíòíî èõ ìîäèôèöèðîâàòü
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// çàäà¸ì öâåò çàäíåãî ôîíà
	glClearColor(0.07f, 0.13f, 0.17f, 0);
	// î÷èùàåì back-áóôôåð è çàäà¸ì åìó íîâûé öâåò
	glClear(GL_COLOR_BUFFER_BIT);
	// ìåíÿåì áóôôåðû ìåñòàìè â îêíå
	glfwSwapBuffers(window);

	// ãëàâíûé öèêë
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 0);
		glClear(GL_COLOR_BUFFER_BIT);
		//Ãîâîðèì OpenGl ïðî èñïîëüçîâàíèå ïðîãðàììû äëÿ øåéäåðîâ
		glUseProgram(shaderProgram);
		// Ñâÿçûâàåì VAO ñ OpenGL
		glBindVertexArray(VAO);
		// Ðèñóåì òðåóãîëüíèê
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);

		// Áåðóòñÿ âî âíèìàíèå âñå GLFW ñîáûòèÿ
		glfwPollEvents();
	}

	// Óäàëÿåì âñå ñîçäàííûå îáúåêòû
	glDeleteVertexArrays(1, &VAO);
	glDeleteProgram(shaderProgram);
	//Óäàëÿåòñÿ èç ÎÏ ñîçäàííîå îêíî
	glfwDestroyWindow(window);
	//Çàêðûâàåòñÿ GLFW
	glfwTerminate();
	return 0;
}
