/*
 * Author: Kiran Kumar Lekkala
 * Created: 3 April 2017
 */

#include "beaglecv.h"
#include "internal.h"

static GLuint g_program;
static GLuint g_programCameraPositionLocation;
static GLuint g_programLightPositionLocation;
static GLuint g_programLightColorLocation;

static GLuint g_cylinderBufferId;
static unsigned int g_cylinderNumVertices;

static float g_cameraPosition[3];

#define NUM_LIGHTS 3
static float g_lightRotation;


void modify_saturation(ccv_dense_matrix_t* a, ccv_dense_matrix_t** b, int type, double ds)
{

}


void modify_contrast(ccv_dense_matrix_t* a, ccv_dense_matrix_t** b, int type, double ds)
{

}

void modify_contrast(ccv_dense_matrix_t* a, ccv_dense_matrix_t** b, int type, double ds)
{
	GLint result;

	/* create program object and attach shaders */
	g_program = glCreateProgram();
	shaderAttachFromFile(g_program, GL_VERTEX_SHADER, "shaders/bright_sample.vp");
	shaderAttachFromFile(g_program, GL_FRAGMENT_SHADER, "shaders/bright_sample.fp");

	/* link the program and make sure that there were no errors */
	glLinkProgram(g_program);
	glGetProgramiv(g_program, GL_LINK_STATUS, &result);

	if(result == GL_FALSE) {
		GLint length;
		char *log;

		/* get the program info log */
		glGetProgramiv(g_program, GL_INFO_LOG_LENGTH, &length);
		log = malloc(length);
		glGetProgramInfoLog(g_program, length, &result, log);

		/* print an error message and the info log */
		fprintf(stderr, "sceneInit(): Program linking failed: %s\n", log);
		free(log);

		/* delete the program */
		glDeleteProgram(g_program);
		g_program = 0;
	}

	/* get uniform locations */
	g_programImageLocation = glGetUniformLocation(g_program, "image");
	g_programBrightnessLocation = glGetUniformLocation(g_program, "brightness");

	/* load an image as texture */
	g_ImageLocation[0] = 1.0f; g_ImageLocation[1] = 0.0f; g_ImageLocation[2] = 0.0f;

	/* do the first cycle to initialize positions */
	sceneCycle();

	/* setup brightness constant*/
	g_Brightness = 0.1f;
	glLoadIdentity();
}