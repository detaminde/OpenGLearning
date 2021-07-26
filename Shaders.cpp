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
		0.5f,  0.5f, 0.0f,  // âåðõíÿÿ ïðàâàÿ
		 0.5f, -0.5f, 0.0f,  // íèæíÿÿ ïðàâàÿ
		-0.5f, -0.5f, 0.0f,  // íèæíÿÿ ëåâàÿ
		-0.5f,  0.5f, 0.0f   // âåðõíÿÿ ëåâàÿ
	};
	GLuint indices[] =
	{
		0,1,3,
		1,2,3
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

	// Ñîçäà¸ì îáúåêò Vertex(âåðøèííûé) Shader è äåëàåì ññûëêó
	GLuint vertexShader = 
		glCreateShader(GL_VERTEX_SHADER);
	// Ïðèêðåïëÿåì Vertex Shader ê îáúåêòó
	glShaderSource(vertexShader, 1, 
		&vertexShaderSource,
		NULL);
	// Êîìïèëèðóåì âñ¸ ýòî äåëî â ìàøèííûé êîä
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
	
	// Ñîçäà¸ì îáúåêò Fragment(ôðàãìåíòíûé) Shader è äåëàåì ññûëêó
	GLuint fragmentShader =
		glCreateShader(GL_FRAGMENT_SHADER);
	// Ïðèêðåïëÿåì Fragment Shader ê îáúåêòó
	glShaderSource(fragmentShader, 1,
		&fragmentShaderSource, NULL);
	// Êîìïèëèðóåì âñ¸ ýòî äåëî â ìàøèííûé êîä
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS,
		&success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512,
			NULL, infoLog);
		std::cout << "Error: Shader Vertex compilation failed:\n" << infoLog << std::endl;
	}
	// Ñîçäà¸ì ïðîãðàììó, êîòîðàÿ áóäåò ðàáîòàòü ñ 
	// øåéäàðàìè è ñîçäà¸ì å¸ ññûëêó
	GLuint shaderProgram = glCreateProgram();
	// Ïðèêðåïëÿåì ñîçäàííûå øåéäåðû ê ïðîãðàììå
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Ñâÿçûâàåì ññûëêàìè âñå øåéäåðû âìåñòå â ïðîãðàììó
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "Error shader program linking failed\n" << infoLog
			<< std::endl;
	}
	//Óäàëÿåì íåíóæíûå øåéäåðû, ò.ê. îíè åñòü â ïðîãðàììå
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Ñîçäà¸ì ññûëêè íà êîíòåéíåðû äëÿ 
	// Vertex Array Object è VertexBufferObject
	GLuint VBO, VAO;
	GLuint EBO;
	

	// Ãåíåðèðóåì VAO è VBO òîëüêî ëèøü ñ 1
	// îáúåêòîì â êàæäîì
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Ñíà÷àëà ñâÿçûâàåì îáúåêò âåðøèííîãî ìàññèâà, çàòåì ñâÿçûâàåì è óñòàíàâëèâàåì âåðøèííûé áóôåð(û), è çàòåì êîíôèãóðèðóåì âåðøèííûé àòðèáóò(û)
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Îáðàòèòå âíèìàíèå, ÷òî äàííîå äåéñòâèå ðàçðåøåíî, âûçîâ glVertexAttribPointer() çàðåãèñòðèðîâàë VBO êàê ïðèâÿçàííûé âåðøèííûé áóôåðíûé îáúåêò äëÿ âåðøèííîãî àòðèáóòà, òàê ÷òî ïîñëå ýòîãî ìû ìîæåì ñïîêîéíî âûïîëíèòü îòâÿçêó
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// ïîìíèòå: íå îòâÿçûâàéòå EBO, ïîêà VÀÎ àêòèâåí, ïîñêîëüêó ñâÿçàííîãî îáúåêò áóôåðà ýëåìåíòà õðàíèòñÿ â VÀÎ; ñîõðàíÿéòå ïðèâÿçêó EBO.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Âû ìîæåòå îòìåíèòü ïðèâÿçêó VÀÎ ïîñëå ýòîãî, ÷òîáû äðóãèå âûçîâû VÀÎ ñëó÷àéíî íå èçìåíèëè ýòîò VAO (íî ïîäîáíîå äîâîëüíî ðåäêî ñëó÷àåòñÿ).
	// Ìîäèôèêàöèÿ äðóãèõ VAO òðåáóåò âûçîâ glBindVertexArray(), ïîýòîìó ìû îáû÷íî íå ñíèìàåì ïðèâÿçêó VAO (èëè VBO), êîãäà ýòî íå òðåáóåòñÿ íàïðÿìóþ
	glBindVertexArray(0);

	
	

	// çàäà¸ì öâåò çàäíåãî ôîíà
	//glClearColor(0.07f, 0.13f, 0.17f, 0);
	// î÷èùàåì back-áóôôåð è çàäà¸ì åìó íîâûé öâåò
	//glClear(GL_COLOR_BUFFER_BIT);
	// ìåíÿåì áóôôåðû ìåñòàìè â îêíå
	//glfwSwapBuffers(window);

	// ãëàâíûé öèêë
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 0);
		glClear(GL_COLOR_BUFFER_BIT);
		//Ãîâîðèì OpenGl ïðî èñïîëüçîâàíèå ïðîãðàììû äëÿ øåéäåðîâ
		/*glUseProgram(shaderProgram);
		// Ñâÿçûâàåì VAO ñ OpenGL
		glBindVertexArray(VAO);
		// Ðèñóåì òðåóãîëüíèê
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);*/

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		// Áåðóòñÿ âî âíèìàíèå âñå GLFW ñîáûòèÿ
		glfwPollEvents();
	}

	// Óäàëÿåì âñå ñîçäàííûå îáúåêòû
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);
	//Óäàëÿåòñÿ èç ÎÏ ñîçäàííîå îêíî
	glfwDestroyWindow(window);
	//Çàêðûâàåòñÿ GLFW
	glfwTerminate();
	return 0;
}
