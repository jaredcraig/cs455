/*
 * model.cpp
 *
 *  Created on: Sep 16, 2015
 *      Author: jared
 */
#include "model.h"

#define POINTS_PER_VERTEX 3

//-----------------------------------------------------------------------------
bool Model::openFile(string filename, ifstream& file) {
	file.open(filename.c_str());
	if (file.is_open()) {
		file.seekg(0, ios::end);
		file.seekg(0, ios::beg);
		return true;
	} else {
		cout << "Unable to open file";
	}
	return false;
}

//-----------------------------------------------------------------------------
bool Model::parseV(istringstream &iss) {
	iss.clear();
	float x, y, z;
	iss >> x >> y >> z;
	if (iss.fail()) {
		cout << "ERROR: could not read in vertex" << endl;
		return false;
	}

	points.push_back(x);
	points.push_back(y);
	points.push_back(z);

	return true;
}

//-----------------------------------------------------------------------------
bool Model::parseF(istringstream &iss) {
	iss.clear();

	int x, y, z;
	iss >> x >> y >> z;
	if (iss.fail()) {
		cout << "ERROR: could not read in point" << endl;
		return false;
	}

	x -= 1;
	y -= 1;
	z -= 1;

	triangles.push_back(points.at(3 * x));
	triangles.push_back(points.at(3 * y));
	triangles.push_back(points.at(3 * z));

	return true;
}

//-----------------------------------------------------------------------------
bool Model::load() {
	string line;
	string word;
	istringstream iss;
	ifstream file;

	if (!openFile("rock.obj", file))
		return false;

	while (!file.eof()) {
		getline(file, line);
		iss.clear();
		iss.str(line);
		iss >> word;

		// vertices
		if (word.c_str()[0] == 'v') {
			if (!parseV(iss)) {
				return false;
			}
		}

		// faces
		if (line.c_str()[0] == 'f') {
			if (!parseF(iss)) {
				cout << "ERROR: Parse 'f'" << endl;
				return false;
			}
		}
	}
	file.close();
	cout << "VERTICES: " << triangles.size() << endl;

	return true;
}

//-----------------------------------------------------------------------------
