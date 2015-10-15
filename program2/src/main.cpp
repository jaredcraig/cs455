#include "model.h"

Model model;
glutWindow win;
GLuint texture[1];
GLuint vertexbuffer;
GLuint uvbuffer;

//-----------------------------------------------------------------------------
int LoadGLTextures() {
	texture[0] = SOIL_load_OGL_texture("CrayonBox2.png", SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	if (texture[0] == 0)
		return false;

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	return true;
}

//-----------------------------------------------------------------------------
void draw() {
	glDrawArrays(GL_TRIANGLES, 0, model.vertices.size());
}

//-----------------------------------------------------------------------------
int init() {
	glEnable(GL_TEXTURE_2D);

	if (!LoadGLTextures()) {
		cerr << "BAD TEXTURE";
		return false;
	}
	//glGenTextures(GL_TEXTURE_2D, &texture[0]);

	glEnable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, win.width, win.height);
	GLfloat aspect = (GLfloat) win.width / win.height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(win.field_of_view_angle, aspect, win.z_near, win.z_far);
	glMatrixMode(GL_MODELVIEW);

	return true;
}

//-----------------------------------------------------------------------------
void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//		 ex ey ez  cx cy cz  ux uy uz
	gluLookAt(0, 6, 10, 0, 2, 0, 0, 1, 0);
	glPushMatrix();
	glRotatef(135, 0, 1, 0);

	draw();
	glPopMatrix();

	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		cerr << "OpenGL error: " << err << endl;
	}

	glutSwapBuffers();
	glFlush();
}

//-----------------------------------------------------------------------------
int main(int argc, char** argv) {
	win.width = 1024;
	win.height = 768;
	win.title = "GLUT OBJ Loader.";
	win.field_of_view_angle = 45;
	win.z_near = 1.0f;
	win.z_far = 500.0f;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(win.width, win.height);
	glutCreateWindow(win.title);

	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return 0;
	}

	glutDisplayFunc(display);
	init();
	model.loadObj();

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, model.vertices.size() * sizeof(glm::vec3),
			&model.vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, model.uvs.size() * sizeof(glm::vec2),
			&model.uvs[0], GL_STATIC_DRAW);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0,                  // attribute
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*) 0            // array buffer offset
			);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(1,                                // attribute
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*) 0                          // array buffer offset
			);

	glutMainLoop();
	return 0;
}

//-----------------------------------------------------------------------------
