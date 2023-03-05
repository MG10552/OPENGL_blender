#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#define WINDOW_TITLE_PREFIX "Podstawy OpenGL"

int CurrentWidth = 800,
	CurrentHeight = 600,
	WindowHandle = 0;

GLuint
	VertexShader,
	FragmentShader,
	Program,
	TriangleVao,
	TriangleVertices,
	TriangleColors,
  KonturVao,
  KonturVertices,
  KonturColors;

const GLchar* VertexShaderText =
{
	"#version 420\n"\

	"layout(location=0) in vec4 in_Position;\n"\
	"layout(location=1) in vec4 in_Color;\n"\
	"out vec4 ex_Color;\n"\

	"void main(void)\n"\
	"{\n"\
	"	gl_Position = in_Position;\n"\
	"	ex_Color = in_Color;\n"\
	"}\n"
};

const GLchar* FragmentShaderText =
{
	"#version 420\n"\

	"in vec4 ex_Color;\n"\
	"out vec4 out_Color;\n"\

	"void main(void)\n"\
	"{\n"\
	"	out_Color = ex_Color;\n"\
	"}\n"
};

void Initialize(int, char*[]);
void InitWindow(int, char*[]);
void ResizeFunction(int, int);
void RenderFunction(void);
void Cleanup(void);
void CreateTriangle(void);
void DestroyTriangle(void);
void CreateKontur(void);
void DestroyKontur(void);
void CreateShaders(void);
void DestroyShaders(void);

int main(int argc, char* argv[])
{
	Initialize(argc, argv);

	glutMainLoop();
	
	exit(EXIT_SUCCESS);
}

void Initialize(int argc, char* argv[])
{
	GLenum GlewInitResult;

	InitWindow(argc, argv);

	glewExperimental = GL_TRUE;
	GlewInitResult = glewInit();

	if (GLEW_OK != GlewInitResult) {
		fprintf(
			stderr,
			"ERROR: %s\n",
			glewGetErrorString(GlewInitResult)
		);
		exit(EXIT_FAILURE);
	}
	
	fprintf(
		stdout,
		"INFO: OpenGL Version: %s\n",
		glGetString(GL_VERSION)
	);

	CreateShaders();
	CreateTriangle();
  CreateKontur();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void InitWindow(int argc, char* argv[])
{
	glutInit(&argc, argv);
	
	glutInitContextVersion(4, 2);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutSetOption(
		GLUT_ACTION_ON_WINDOW_CLOSE,
		GLUT_ACTION_GLUTMAINLOOP_RETURNS
	);
	
	glutInitWindowSize(CurrentWidth, CurrentHeight);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	WindowHandle = glutCreateWindow(WINDOW_TITLE_PREFIX);

	if(WindowHandle < 1) {
		fprintf(
			stderr,
			"ERROR: Could not create a new rendering window.\n"
		);
		exit(EXIT_FAILURE);
	}
	
	glutReshapeFunc(ResizeFunction);
	glutDisplayFunc(RenderFunction);
	glutCloseFunc(Cleanup);
}

void ResizeFunction(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;
	glViewport(0, 0, CurrentWidth, CurrentHeight);
}

void RenderFunction(void){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glUseProgram(Program);
	glBindVertexArray(TriangleVao);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 12);
	glBindVertexArray(0);

  glBindVertexArray(KonturVao);
  glDrawArrays(GL_LINE_LOOP, 0,11);
  glBindVertexArray(0);
	glUseProgram(0);
	
	glutSwapBuffers();
	glutPostRedisplay();
}

void Cleanup(void)
{
	DestroyShaders();
	DestroyTriangle();
  DestroyKontur();
}

void CreateTriangle(void)
{
	GLfloat Vertices[] = {
		0.0f, 0.0f, 0.0f, 1.0f, 
		0.07f, 0.1f, 0.0f, 1.0f, 
		0.25f, 0.1f, 0.0f, 1.0f,//spine
		0.1f, 0.0f, 0.0f, 1.0f, 
		0.17f, -0.2f, 0.0f, 1.0f,//spine
		0.0f, -0.055f, 0.0f, 1.0f,
		-0.17f, -0.2, 0.0f, 1.0f,//spine
		-0.1f, 0.0f, 0.0f, 1.0f,
		-0.25f, 0.1f, 0.0f, 1.0f,//spine
		-0.07f, 0.1f, 0.0f, 1.0f,
		0.0f, 0.3f, 0.0f, 1.0f,//spine
		0.07f, 0.1f, 0.0f, 1.0f 
  };

	GLfloat Colors[] = {
		0.0f,0.0f, 1.0f, 1.0f,
		0.0f,0.0f, 1.0f, 1.0f,
	  	0.0f,0.0f, 1.0f, 1.0f,
    		0.0f,0.0f, 1.0f, 1.0f,
    		0.0f,0.0f, 1.0f, 1.0f,
    		0.0f,0.0f, 1.0f, 1.0f,
    		0.0f,0.0f, 1.0f, 1.0f,
    		0.0f,0.0f, 1.0f, 1.0f,
    		0.0f,0.0f, 1.0f, 1.0f,
    		0.0f,0.0f, 1.0f, 1.0f,
    		0.0f,0.0f, 1.0f, 1.0f,
    		0.0f,0.0f, 1.0f, 1.0f
	};

	GLenum ErrorCheckValue = glGetError();
	
	glGenVertexArrays(1, &TriangleVao);
	glBindVertexArray(TriangleVao);

	glGenBuffers(1, &TriangleVertices);
	glBindBuffer(GL_ARRAY_BUFFER, TriangleVertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	
  glGenBuffers(1, &TriangleColors);
	glBindBuffer(GL_ARRAY_BUFFER, TriangleColors);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	
  ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(
			stderr,
			"ERROR: Could not create a VBO: %s \n",
			gluErrorString(ErrorCheckValue)
		);

		exit(-1);
	}
}

void CreateKontur(void)
{
	GLfloat Vertices[] = {
		0.1f, 0.1f, 0.0f, 0.5f, 
		0.25f, 0.1f, 0.0f, 0.5f,
		0.1f, 0.0f, 0.0f, 0.5f, 
		0.17f,-0.2f, 0.0f, 0.5f,
		0.0f,-0.07f, 0.0f, 0.5f,
	       -0.17f,-0.2f, 0.0f, 0.5f,
	       -0.1f, 0.0f, 0.0f, 0.5f,
	       -0.25f, 0.1f, 0.0f, 0.5f,
	       -0.07f, 0.1f, 0.0f, 0.5f,
		0.0f, 0.3f, 0.0f, 0.5f,
		0.07f, 0.1f, 0.0f, 0.5f 
  };

	GLfloat Colors[] = {
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
	  	0.0f, 0.0f, 1.0f, 1.0f,
    		0.0f, 0.0f, 1.0f, 1.0f,
    		0.0f, 0.0f, 1.0f, 1.0f,
    		0.0f, 0.0f, 1.0f, 1.0f,
    		0.0f, 0.0f, 1.0f, 1.0f,
    		0.0f, 0.0f, 1.0f, 1.0f,
    		0.0f, 0.0f, 1.0f, 1.0f,
    		0.0f, 0.0f, 1.0f, 1.0f,
    		0.0f, 0.0f, 1.0f, 1.0f,
    		0.0f, 0.0f, 1.0f, 1.0f
	};

	GLenum ErrorCheckValue = glGetError();
	
	glGenVertexArrays(1, &KonturVao);
	glBindVertexArray(KonturVao);

	glGenBuffers(1, &KonturVertices);
	glBindBuffer(GL_ARRAY_BUFFER, KonturVertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	
  glGenBuffers(1, &KonturColors);
	glBindBuffer(GL_ARRAY_BUFFER, KonturColors);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	
  ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(
			stderr,
			"ERROR: Could not create a VBO: %s \n",
			gluErrorString(ErrorCheckValue)
		);

		exit(-1);
	}
}

void DestroyKontur(void)
{
	GLenum ErrorCheckValue = glGetError();

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &KonturColors);
	glDeleteBuffers(1, &KonturVertices);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &KonturVao);

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(
			stderr,
			"ERROR: Could not destroy the VBO: %s \n",
			gluErrorString(ErrorCheckValue)
		);

		exit(-1);
	}
}

void DestroyTriangle(void)
{
	GLenum ErrorCheckValue = glGetError();

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &TriangleColors);
	glDeleteBuffers(1, &TriangleVertices);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &TriangleVao);

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(
			stderr,
			"ERROR: Could not destroy the VBO: %s \n",
			gluErrorString(ErrorCheckValue)
		);

		exit(-1);
	}
}

void CreateShaders(void)
{
	GLenum ErrorCheckValue = glGetError();
	
	VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShader, 1, &VertexShaderText, NULL);
	glCompileShader(VertexShader);

	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShader, 1, &FragmentShaderText, NULL);
	glCompileShader(FragmentShader);

	Program = glCreateProgram();
	glAttachShader(Program, VertexShader);
	glAttachShader(Program, FragmentShader);
	glLinkProgram(Program);
	glUseProgram(Program);

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(
			stderr,
			"ERROR: Could not create the shaders: %s \n",
			gluErrorString(ErrorCheckValue)
		);

		exit(-1);
	}
}

void DestroyShaders(void)
{
	GLenum ErrorCheckValue = glGetError();

	glUseProgram(0);

	glDetachShader(Program, VertexShader);
	glDetachShader(Program, FragmentShader);

	glDeleteShader(FragmentShader);
	glDeleteShader(VertexShader);

	glDeleteProgram(Program);

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(
			stderr,
			"ERROR: Could not destroy the shaders: %s \n",
			gluErrorString(ErrorCheckValue)
		);

		exit(-1);
	}
}
