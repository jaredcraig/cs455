/*
 * model.cpp
 *
 *  Created on: Sep 16, 2015
 *      Author: jared
 */
#include "model.h"

//-----------------------------------------------------------------------------
void Model::parseFaceLine(string line, vector<int> &face_line) {
	line[0] = ' ';
	string parsed_line;
	string el;
	istringstream ss(line);

	while (!ss.eof()) {
		ss >> el;
		parsed_line += el;
		parsed_line += '/';
	}

	ss.clear();
	ss.str(parsed_line);

	while (getline(ss, el, '/')) {
		face_line.push_back(atoi(el.c_str()));
	}
}

//-----------------------------------------------------------------------------
void Model::parseV(string &line) {
	line[0] = ' ';
	char c = line.c_str()[1];

	if (c == 't') {
		line[1] = ' ';
		glm::vec2 uv;
		sscanf(line.c_str(), "%f %f", &uv.x, &uv.y);
		temp_uvs.push_back(uv);
	} else if (c == 'n') {
		glm::vec3 normal;
		line[1] = ' ';
		sscanf(line.c_str(), "%f %f %f", &normal.x, &normal.y, &normal.z);
		temp_normals.push_back(normal);
	} else {
		glm::vec3 vertex;
		sscanf(line.c_str(), "%f %f %f ", &vertex.x, &vertex.y, &vertex.z);
		temp_vertices.push_back(vertex);
	}
}

//-----------------------------------------------------------------------------
void Model::parseF(string &line) {

	vector<int> faces;
	parseFaceLine(line, faces);

	vertex_indices.push_back(faces[0]);
	vertex_indices.push_back(faces[3]);
	vertex_indices.push_back(faces[6]);

	uv_indices.push_back(faces[1]);
	uv_indices.push_back(faces[4]);
	uv_indices.push_back(faces[7]);

	normal_indices.push_back(faces[2]);
	normal_indices.push_back(faces[5]);
	normal_indices.push_back(faces[8]);
}

void Model::buildTriangles() {
	for (unsigned int i = 0; i < vertex_indices.size(); i++) {

		// Get the indices of its attributes
		unsigned int vertexIndex = vertex_indices[i];
		unsigned int uvIndex = uv_indices[i];
		unsigned int normalIndex = normal_indices[i];

		// Get the attributes thanks to the index
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		glm::vec2 uv = temp_uvs[uvIndex - 1];
		glm::vec3 normal = temp_normals[normalIndex - 1];

		// Put the attributes in buffers
		vertices.push_back(vertex);
		uvs.push_back(uv);
		normals.push_back(normal);

	}
}
//-----------------------------------------------------------------------------
void Model::loadObj() {
	string line;
	ifstream file("box.obj");

	if (file.is_open()) {
		while (!file.eof()) {
			getline(file, line);
			switch (line.c_str()[0]) {
			case 'v':
				parseV(line);
				break;
			case 'f':
				parseF(line);
				break;
			}
		}
		buildTriangles();
		file.close();
	} else {
		cout << "Unable to open file";
	}
}
