/*
 * model.h
 *
 *  Created on: Sep 16, 2015
 *      Author: jared
 */
#include <GL/glew.h>
#include <GL/glut.h>

#include <sstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>

using namespace std;

#define POINTS_PER_VERTEX 3
#define TOTAL_FLOATS_IN_TRIANGLE 9
#define TOTAL_FLOATS_IN_QUAD 12

//-----------------------------------------------------------------------------
typedef struct {
	int width;
	int height;
	char* title;
	float field_of_view_angle;
	float z_near;
	float z_far;
} glutWindow;

//-----------------------------------------------------------------------------
class Model {
public:

	vector<glm::vec3> temp_vertices;
	vector<glm::vec2> temp_uvs;
	vector<glm::vec3> temp_normals;
	vector<glm::vec3> vertices;
	vector<glm::vec2> uvs;
	vector<glm::vec3> normals;

	vector<int> vertex_indices, uv_indices, normal_indices;

	void parseFaceLine(string line, vector<int> &face_line);
	void parseV(string &line);
	void parseF(string &line);
	void buildTriangles();
	void loadObj();
};
