#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include "../_vs2015/Debug.h"
#include "mge/core/Mesh.hpp"
#include "mge/config.hpp"

Mesh::Mesh() : _indexBufferId(0), _vertexBufferId(0), _normalBufferId(0), _uvBufferId(0), _vertices(), _normals(), _uvs(), _indices()
{
	//ctor
}

Mesh::~Mesh()
{
	//dtor
}

/**
 * Load reads the obj data into a new mesh using C++ combined with c style coding.
 * The result is an indexed mesh for use with glDrawElements.
 * Expects a obj file with following layout v/vt/vn/f eg
 *
 * For example the obj file for a simple plane describes two triangles, based on
 * four vertices, with 4 uv's all having the same vertex normals (NOT FACE NORMALS!)
 *
 * v 10.000000 0.000000 10.000000              //vertex 1
 * v -10.000000 0.000000 10.000000             //vertex 2
 * v 10.000000 0.000000 -10.000000             //vertex 3
 * v -10.000000 0.000000 -10.000000            //vertex 4
 * vt 0.000000 0.000000                        //uv 1
 * vt 1.000000 0.000000                        //uv 2
 * vt 1.000000 1.000000                        //uv 3
 * vt 0.000000 1.000000                        //uv 4
 * vn 0.000000 1.000000 -0.000000              //normal 1 (normal for each vertex is same)
 * s off
 *
 * Using these vertices, uvs and normals we can construct faces, made up of 3 triplets (vertex, uv, normal)
 * f 2/1/1 1/2/1 3/3/1                         //face 1 (triangle 1)
 * f 4/4/1 2/1/1 3/3/1                         //face 2 (triangle 2)
 *
 * So although this is a good format for blender and other tools reading .obj files, this is
 * not an index mechanism that OpenGL supports out of the box.
 * The reason is that OpenGL supports only one indexbuffer, and the value at a certain point in the indexbuffer, eg 3
 * refers to all three other buffers (v, vt, vn) at once,
 * eg if index[0] = 5, opengl will stream vertexBuffer[5], uvBuffer[5], normalBuffer[5] into the shader.
 *
 * So what we have to do after reading the file with all vertices, is construct unique indexes for
 * all pairs that are described by the faces in the object file, eg if you have
 * f 2/1/1 1/2/1 3/3/1                         //face 1 (triangle 1)
 * f 4/4/1 2/1/1 3/3/1                         //face 2 (triangle 2)
 *
 * v/vt/vn[0] will represent 2/1/1
 * v/vt/vn[1] will represent 1/2/1
 * v/vt/vn[2] will represent 3/3/1
 * v/vt/vn[3] will represent 4/4/1
 *
 * and that are all unique pairs, after which our index buffer can contain:
 *
 * 0,1,2,3,0,2
 *
 * So the basic process is, read ALL data into separate arrays, then use the faces to
 * create unique entries in a new set of arrays and create the indexbuffer to go along with it.
 *
 * Note that loading this mesh isn't cached like we do with texturing, this is an exercise left for the students.
 */
Mesh* Mesh::load(std::string pFilename)
{
	if (pFilename == " ")return NULL;
	Debug::Log("Loading " + pFilename + "...", WARNINGS_ERRORS_LOG2);

	Mesh* mesh = new Mesh();

	std::ifstream file(pFilename, std::ios::in);

	if (file.is_open()) {
		//these three vectors will contains data as taken from the obj file
		//in the order it is encountered in the object file
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> uvs;

		//in addition we create a map to store the triplets found under the f(aces) section in the
		//object file and map them to an index for our index buffer (just number them sequentially
		//as we encounter them and store references to the pack
		std::map <FaceIndexTriplet, unsigned int> mappedTriplets;

		std::string line; // to store each line in
		while (getline(file, line)) {

			// c-type string to store cmd read from obj file (cmd is v, vt, vn, f)
			char cmd[10];
			cmd[0] = 0;

			//get the first string in the line of max 10 chars (c-style)
			sscanf(line.c_str(), "%10s", cmd);

			//note that although the if statements below seem to imply that we can
			//read these different line types (eg vertex, normal, uv) in any order,
			//this is just convenience coding for us (instead of multiple while loops)
			//we assume the obj file to list ALL v lines first, then ALL vt lines,
			//then ALL vn lines and last but not least ALL f lines last

			//so... start processing lines
			//are we reading a vertex line? straightforward copy into local vertices vector
			if (strcmp(cmd, "v") == 0) {
				glm::vec3 vertex;
				sscanf(line.c_str(), "%10s %f %f %f ", cmd, &vertex.x, &vertex.y, &vertex.z);
				vertices.push_back(vertex);

				//or are we reading a normal line? straightforward copy into local normal vector
			}
			else if (strcmp(cmd, "vn") == 0) {
				glm::vec3 normal;
				sscanf(line.c_str(), "%10s %f %f %f ", cmd, &normal.x, &normal.y, &normal.z);
				normals.push_back(normal);

				//or are we reading a uv line? straightforward copy into local uv vector
			}
			else if (strcmp(cmd, "vt") == 0) {
				glm::vec2 uv;
				sscanf(line.c_str(), "%10s %f %f ", cmd, &uv.x, &uv.y);
				uvs.push_back(uv);

				//this is where it gets nasty. After having read all vertices, normals and uvs into
				//their own buffer
			}
			else if (strcmp(cmd, "f") == 0) {

				//an f lines looks like
				//f 2/1/1 1/2/1 3/3/1
				//in other words
				//f v1/u1/n1 v2/u2/n2 v3/u3/n3
				//for each triplet like that we need to check whether we already encountered it
				//and update our administration based on that
				glm::ivec3 vertexIndex;
				glm::ivec3 normalIndex;
				glm::ivec3 uvIndex;
				int count = sscanf(line.c_str(), "%10s %d/%d/%d %d/%d/%d %d/%d/%d", cmd, &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);

				//Have we read exactly 10 elements?
				if (count == 10) {

					//process 3 triplets, one for each vertex (which is first element of the triplet)
					for (int i = 0; i < 3; ++i) {
						//create key out of the triplet and check if we already encountered this before
						FaceIndexTriplet triplet(vertexIndex[i], uvIndex[i], normalIndex[i]);
						std::map<FaceIndexTriplet, unsigned int>::iterator found = mappedTriplets.find(triplet);

						//if iterator points at the end, we haven't found it
						if (found == mappedTriplets.end())
						{
							//so create a new index value, and map our triplet to it
							unsigned int index = mappedTriplets.size();
							mappedTriplets[triplet] = index;

							//now record this index
							mesh->_indices.push_back(index);
							//and store the corresponding vertex/normal/uv values into our own buffers
							//note the -1 is required since all values in the f triplets in the .obj file
							//are 1 based, but our vectors are 0 based
							mesh->_vertices.push_back(vertices[vertexIndex[i] - 1]);
							mesh->_normals.push_back(normals[normalIndex[i] - 1]);
							mesh->_uvs.push_back(uvs[uvIndex[i] - 1]);
						}
						else
						{
							//if the key was already present, get the index value for it
							unsigned int index = found->second;
							//and update our index buffer with it
							mesh->_indices.push_back(index);
						}
					}
				}
				else {
					//If we read a different amount, something is wrong
					Debug::LogError("Error reading obj, needing v, vn, vt");
					delete mesh;
					return NULL;
				}
			}

		}

		file.close();

	//	mesh->ComputeTangents();

		mesh->_buffer();

		Debug::Log("Mesh loaded and buffered:" + std::to_string(mesh->_indices.size() / 3.0f) + " triangles.", WARNINGS_ERRORS_LOG2);
		return mesh;
	}
	else {
		Debug::LogError("Could not read " + pFilename );
		delete mesh;
		return NULL;
	}
}

void Mesh::ComputeTangents() {

	Debug::Log("Computing Tangents and Bitangents..", WARNINGS_ERRORS_LOG3);
	_tangents.clear();
	_biTangents.clear();
	_tangents = std::vector<glm::vec3>(_indices.size());
	_biTangents = std::vector<glm::vec3>(_indices.size());

	//GLMHelper glmHelper;
	for (unsigned int i = 0; i < _indices.size(); i += 3) {


		// Shortcuts for vertices
		int index0 = _indices[i];
		int index1 = _indices[i + 1];
		int index2 = _indices[i + 2];

		glm::vec3 & v0 = _vertices[index0];
		glm::vec3 & v1 = _vertices[index1];
		glm::vec3 & v2 = _vertices[index2];



		// Shortcuts for UVs
		glm::vec2 & uv0 = _uvs[index0];
		glm::vec2 & uv1 = _uvs[index1];
		glm::vec2 & uv2 = _uvs[index2];


		// Edges of the triangle : postion delta
		glm::vec3 deltaPos1 = v1 - v0;
		glm::vec3 deltaPos2 = v2 - v0;


		// UV delta
		glm::vec2 deltaUV1 = uv1 - uv0;
		glm::vec2 deltaUV2 = uv2 - uv0;


		float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
		glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y)*r;
		glm::vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x)*r;

		// Set the same tangent for all three vertices of the triangle.
		// They will be merged later, in vboindexer.cpp
		_tangents[index0] = (tangent);
		_tangents[index1] = (tangent);
		_tangents[index2] = (tangent);

		// Same thing for bitangents
		_biTangents[index0] = (bitangent);
		_biTangents[index1] = (bitangent);
		_biTangents[index2] = (bitangent);



	}


	Debug::Log("Done", WARNINGS_ERRORS_LOG3);


}

void Mesh::_buffer()
{
	glGenBuffers(1, &_indexBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &_vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(glm::vec3), &_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &_normalBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, _normalBufferId);
	glBufferData(GL_ARRAY_BUFFER, _normals.size() * sizeof(glm::vec3), &_normals[0], GL_STATIC_DRAW);

	if ((int)_tangents.size() > 0)
	{
		glGenBuffers(1, &_tanBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, _tanBufferID);
		glBufferData(GL_ARRAY_BUFFER, _tangents.size() * sizeof(glm::vec3), &_tangents[0], GL_STATIC_DRAW);
	}

	if ((int)_biTangents.size() > 0)
	{
		glGenBuffers(1, &_bitanBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, _bitanBufferID);
		glBufferData(GL_ARRAY_BUFFER, _biTangents.size() * sizeof(glm::vec3), &_biTangents[0], GL_STATIC_DRAW);
	}

	glGenBuffers(1, &_uvBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, _uvBufferId);
	glBufferData(GL_ARRAY_BUFFER, _uvs.size() * sizeof(glm::vec2), &_uvs[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::streamToOpenGL(GLint pVerticesAttrib, GLint pNormalsAttrib, GLint pUVsAttrib, GLint pTanAttrib, GLint biTanAttrib) {
	if (pVerticesAttrib != -1) {
		glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferId);
		glEnableVertexAttribArray(pVerticesAttrib);
		glVertexAttribPointer(pVerticesAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	if (pNormalsAttrib != -1) {
		glBindBuffer(GL_ARRAY_BUFFER, _normalBufferId);
		glEnableVertexAttribArray(pNormalsAttrib);
		glVertexAttribPointer(pNormalsAttrib, 3, GL_FLOAT, GL_TRUE, 0, 0);
	}

	if (pUVsAttrib != -1) {
		glBindBuffer(GL_ARRAY_BUFFER, _uvBufferId);
		glEnableVertexAttribArray(pUVsAttrib);
		glVertexAttribPointer(pUVsAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
	}

	if (pTanAttrib != -1) {
		glBindBuffer(GL_ARRAY_BUFFER, _tanBufferID);
		glEnableVertexAttribArray(pTanAttrib);
		glVertexAttribPointer(pTanAttrib, 3, GL_FLOAT, GL_TRUE, 0, 0);
	}

	if (biTanAttrib != -1) {
		glBindBuffer(GL_ARRAY_BUFFER, _bitanBufferID);
		glEnableVertexAttribArray(biTanAttrib);
		glVertexAttribPointer(biTanAttrib, 3, GL_FLOAT, GL_TRUE, 0, 0);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferId);

	glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, (GLvoid*)0);

	// no current buffer, to avoid mishaps, very important for performance

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//fix for serious performance issue
	if (pUVsAttrib != -1) glDisableVertexAttribArray(pUVsAttrib);
	if (pNormalsAttrib != -1) glDisableVertexAttribArray(pNormalsAttrib);
	if (pVerticesAttrib != -1) glDisableVertexAttribArray(pVerticesAttrib);
	if (pTanAttrib != -1) glDisableVertexAttribArray(pTanAttrib);
	if (biTanAttrib != -1) glDisableVertexAttribArray(biTanAttrib);
}

glm::vec3 Mesh::GetMaxLocalBounds()
{
	glm::vec3 ret = glm::vec3(-1000000);
	if(_indices.size() == 0)return glm::vec3(0);
	for (size_t i = 0; i < _indices.size();i++)
	{
		if (_vertices[_indices[i]].x > ret.x)
			ret.x = _vertices[_indices[i]].x;
		if (_vertices[_indices[i]].y > ret.y)
			ret.y = _vertices[_indices[i]].y;
		if (_vertices[_indices[i]].z > ret.z)
			ret.z = _vertices[_indices[i]].z;
	}
	return ret;
}

glm::vec3 Mesh::GetMinLocalBounds()
{
	glm::vec3 ret = glm::vec3(100000000);
	if (_indices.size() == 0)return glm::vec3(0);
	for (size_t i = 0; i < _indices.size(); i++)
	{
		if (_vertices[_indices[i]].x < ret.x)
			ret.x = _vertices[_indices[i]].x;
		if (_vertices[_indices[i]].y < ret.y)
			ret.y = _vertices[_indices[i]].y;
		if (_vertices[_indices[i]].z < ret.z)
			ret.z = _vertices[_indices[i]].z;
	}
	return ret;
}

void Mesh::drawDebugInfo(const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix, std::vector<glm::vec3> collider) {
	//demo of how to render some debug info using the good ol' direct rendering mode...
	glUseProgram(0);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(pProjectionMatrix));
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(glm::value_ptr(pViewMatrix * pModelMatrix));

	glBegin(GL_LINES);

	for (size_t i = 0; i < collider.size(); i++)
	{
		glm::vec3 start, end;
		start = glm::vec3(collider[i]);
		end = glm::vec3(collider[(i + 1) % collider.size()]);
		glColor3fv(glm::value_ptr(glm::vec3(0, 1, 0)));
		glVertex3fv(glm::value_ptr(start));
		glVertex3fv(glm::value_ptr(end));
	}

	//for each index draw the normal starting at the corresponding vertex
	//for (size_t i = 0; i < _indices.size(); i++) {
	//	//draw normal for vertex
	//	if (true) {

	//		//now get normal end
	//		glm::vec3 normal = _normals[_indices[i]];
	//		glColor3fv(glm::value_ptr(normal));

	//		glm::vec3 normalStart = _vertices[_indices[i]];
	//		glVertex3fv(glm::value_ptr(normalStart));
	//		glm::vec3 normalEnd = normalStart + normal * 0.2f;
	//		glVertex3fv(glm::value_ptr(normalEnd));
	//	}

	//}
	glEnd();
}



