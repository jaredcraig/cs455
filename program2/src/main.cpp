#include "model.h"

#define POINTS_PER_VERTEX 3
#define TOTAL_FLOATS_IN_TRIANGLE 9

Model model;
glutWindow win;
GLuint texture[1];

float g_rotation;
float* Faces_Triangles;
float* UVcoords;
float* vertexBuffer;
long TotalConnectedPoints;
long TotalConnectedTriangles;

bool gIsDevILInitialized = false;

//-----------------------------------------------------------------------------
int LoadGLTextures() {
	texture[0] = SOIL_load_OGL_texture("bowser.bmp", SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	if (texture[0] == 0)
		return false;

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return true;
}

//-----------------------------------------------------------------------------
void Model::draw() {
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, Faces_Triangles);
	glDrawArrays(GL_TRIANGLES, 0, TotalConnectedTriangles);
	glDisableClientState(GL_VERTEX_ARRAY);
}

//-----------------------------------------------------------------------------
void init() {
	LoadGLTextures();

	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	try {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 939, 800, 0, GL_RGB, GL_FLOAT,
				&texture[0]);
	} catch (exception &e) {
		cout << e.what() << endl;
	}

	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, win.width, win.height);
	GLfloat aspect = (GLfloat) win.width / win.height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(win.field_of_view_angle, aspect, win.z_near, win.z_far);
	glMatrixMode(GL_MODELVIEW);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	GLfloat amb_light[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat diffuse[] = { 0.6, 0.6, 0.6, 1 };
	GLfloat specular[] = { 0.7, 0.7, 0.3, 1 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb_light);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

//-----------------------------------------------------------------------------
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0, 1, 4, 0, 0, 0, 0, 1, 0);
	glPushMatrix();
	glRotatef(g_rotation, 0, 1, 0);
	glRotatef(90, 0, 1, 0);
	g_rotation++;
	model.draw();
	glPopMatrix();
	glutSwapBuffers();
	glFlush();
}

//-----------------------------------------------------------------------------
void load() {
	string line;
	ifstream objFile("rock.obj");

	if (objFile.is_open()) {
		objFile.seekg(0, ios::end);
		long fileSize = objFile.tellg();
		objFile.seekg(0, ios::beg);

		vertexBuffer = (float*) malloc(fileSize);
		Faces_Triangles = (float*) malloc(fileSize * sizeof(float));
		UVcoords = (float*) malloc(fileSize * sizeof(float));

		int triangle_index = 0;
		int normal_index = 0;
		int x, y, z, u, v, w;

		while (!objFile.eof()) {
			getline(objFile, line);

			if (line.c_str()[0] == 'v') {
				line[0] = ' ';
				sscanf(line.c_str(), "%f %f %f ",
						&vertexBuffer[TotalConnectedPoints],
						&vertexBuffer[TotalConnectedPoints + 1],
						&vertexBuffer[TotalConnectedPoints + 2]);

				TotalConnectedPoints += POINTS_PER_VERTEX;
			}
			if (line.c_str()[0] == 'f') {
				line[0] = ' ';

				string s;
				istringstream iss(line);
				ostringstream oss;
				while (getline(iss, s, '/')) {
					oss << s << " ";
				}
				iss.clear();
				iss.str(oss.str());
				for (int i = 0; i < 6; i++) {
					iss >> x >> u >> y >> v >> z >> w;
				}

				//printf("xyz:[%i, %i, %i], ", x, y, z);
				//printf("uvw:[%i, %i, %i]\n", u, v, w);

				x--;
				y--;
				z--;
				u--;
				v--;
				w--;

				int vertexNumber[4] = { x, y, z };
				int uvNum[4] = { u, v, w };

				int tCounter = 0;
				for (int i = 0; i < POINTS_PER_VERTEX; i++) {
					Faces_Triangles[triangle_index + tCounter] = vertexBuffer[3
							* vertexNumber[i]];
					Faces_Triangles[triangle_index + tCounter + 1] =
							vertexBuffer[3 * vertexNumber[i] + 1];
					Faces_Triangles[triangle_index + tCounter + 2] =
							vertexBuffer[3 * vertexNumber[i] + 2];

					UVcoords[triangle_index + tCounter] = uvNum[3
							* vertexNumber[i]];
					UVcoords[triangle_index + tCounter + 1] = uvNum[3
							* vertexNumber[i] + 1];
					UVcoords[triangle_index + tCounter + 2] = uvNum[3
							* vertexNumber[i] + 2];

					tCounter += POINTS_PER_VERTEX;
				}

				triangle_index += TOTAL_FLOATS_IN_TRIANGLE;
				normal_index += TOTAL_FLOATS_IN_TRIANGLE;
				TotalConnectedTriangles += TOTAL_FLOATS_IN_TRIANGLE;

			}
		}
		objFile.close();
	} else {
		cout << "Unable to open file";
	}
}

//-----------------------------------------------------------------------------
int main(int argc, char** argv) {
	win.width = 640;
	win.height = 480;
	win.title = "GLUT OBJ Loader.";
	win.field_of_view_angle = 45;
	win.z_near = 1.0f;
	win.z_far = 500.0f;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(win.width, win.height);
	glutCreateWindow(win.title);
	glutDisplayFunc(display);

	init();
	load();
	glutMainLoop();
	return 0;
}

//-----------------------------------------------------------------------------
