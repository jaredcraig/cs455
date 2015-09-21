/*
 * model.h
 *
 *  Created on: Sep 16, 2015
 *      Author: jared
 */
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <GL/glut.h>
#include <cstdio>
#include <cmath>
#include <SOIL/SOIL.h>

using namespace std;

//-----------------------------------------------------------------------------
class Model {
public:

	bool load();
	void draw();
	bool parseV(istringstream &iss);
	bool parseF(istringstream &iss);
	bool openFile(string filename, ifstream&);

	vector<float> points;
	vector<float> triangles;
	float g_rotation;
};

//-----------------------------------------------------------------------------
typedef struct {
	int width;
	int height;
	char* title;
	float field_of_view_angle;
	float z_near;
	float z_far;
} glutWindow;

