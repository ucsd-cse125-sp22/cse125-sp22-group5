#include "skin.hpp"
skin::skin(Skeleton* s, bool hasSkel) {

	this->hasSkel = hasSkel;

	skeleton = s;

	model = glm::mat4(1);
	// The color of the cube. Try setting it to something else!
	color = glm::vec3(1.0f, 1.0f, 1.0f);
}

skin::~skin() {
	for (int i = 0; i < vertexs.size(); i++) {
		delete vertexs[i];
	}
	for (int i = 0; i < triangles.size(); i++) {
		delete triangles[i];
	}

	// Delete the VBOs and the VAO.
	glDeleteBuffers(1, &VBO_positions);
	glDeleteBuffers(1, &VBO_normals);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
}

bool skin::load(const char* file) {
	Tokenizer token;
	token.Open(file);

	token.FindToken("positions");
	int times = token.GetInt();
	token.FindToken("{");

	float a, b, c;
	for (int i = 0; i < times; i++) {
		a = token.GetFloat();
		b = token.GetFloat();
		c = token.GetFloat();
		vertex* newVertex = new vertex(a,b,c);
		vertexs.push_back(newVertex);
		positions.push_back(glm::vec3(a, b, c));
	}

	token.FindToken("}");

	token.FindToken("normals");
	times = token.GetInt();
	token.FindToken("{");

	for (int i = 0; i < times; i++) {
		a = token.GetFloat();
		b = token.GetFloat();
		c = token.GetFloat();
		vertexs[i]->setNormal(a, b, c);
		normals.push_back(glm::vec3(a, b, c));
	}

	token.FindToken("}");

	token.FindToken("skinweights");
	times = token.GetInt();
	token.FindToken("{");

	int number, joint;
	for (int i = 0; i < times; i++) {
		number = token.GetInt();
		for (int j = 0; j < number; j++) {
			joint = token.GetInt();
			c = token.GetFloat();
			vertexs[i]->addBind(joint, c);
		}
	}

	token.FindToken("}");

	token.FindToken("triangles");
	times = token.GetInt();
	token.FindToken("{");

	int ia, ib, ic;
	for (int i = 0; i < times; i++) {
		ia = token.GetInt();
		ib = token.GetInt();
		ic = token.GetInt();
		triangle* tri = new triangle(ia, ib, ic);
		triangles.push_back(tri);
		indices.push_back(ia);
		indices.push_back(ib);
		indices.push_back(ic);
	}

	token.FindToken("}");

	token.FindToken("bindings");
	times = token.GetInt();
	token.FindToken("{");

	for (int i = 0; i < times; i++) {
		token.FindToken("matrix");
		token.FindToken("{");
		glm::mat4* matrix = new glm::mat4();
		glm::mat4* smatrix = new glm::mat4();
		for (int j = 0; j < 4; j++) {
			a = token.GetFloat();
			b = token.GetFloat();
			c = token.GetFloat();
			if (j == 3) {
				(*matrix)[j] = glm::vec4(a, b, c, 1);
			}
			else {
				(*matrix)[j] = glm::vec4(a, b, c, 0);
			}

			if (j == 3) {
				(*smatrix)[j] = glm::vec4(a, b, c, 1);
			}
			else {
				(*smatrix)[j] = glm::vec4(a, b, c, 0);
			}
		}
		bindings.push_back(matrix);
		skinMatrix.push_back(smatrix);
	}

	token.FindToken("}");

	// Finish
	token.Close();

	// Generate a vertex array (VAO) and two vertex buffer objects (VBO).
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO_positions);
	glGenBuffers(1, &VBO_normals);

	// Bind to the VAO.
	glBindVertexArray(VAO);

	// Bind to the first VBO - We will use it to store the vertices
	glBindBuffer(GL_ARRAY_BUFFER, VBO_positions);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * positions.size(), positions.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

	// Bind to the second VBO - We will use it to store the normals
	glBindBuffer(GL_ARRAY_BUFFER, VBO_normals);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals.size(), normals.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

	// Generate EBO, bind the EBO to the bound VAO and send the data
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

	// Unbind the VBOs.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return true;
}
void skin::setModel(glm::mat4 m)
{
	this->model = m;
}
void skin::update() {

	for (int i = 0; i < skinMatrix.size(); i++) {
		*(skinMatrix[i]) = skeleton->getWorldMatrix(i) * (glm::inverse(*(bindings[i])));
	}
	
	for (int i = 0; i < vertexs.size(); i++) {
		if (vertexs[i]->getWeights()->size() == 0) {
			continue;
		}
		else {
			positions[i] = glm::vec3(0, 0, 0);
			normals[i] = glm::vec3(0, 0, 0);
			for (int j = 0; j < vertexs[i]->getWeights()->size(); j++) {
				glm::vec4 original = glm::vec4((*(vertexs[i]->getVertex()))[0], (*(vertexs[i]->getVertex()))[1], (*(vertexs[i]->getVertex()))[2], 1);

				positions[i] = positions[i] + glm::vec3((*(vertexs[i]->getWeights()))[j] * (*(skinMatrix[(*(vertexs[i]->getJoints()))[j]])) * original);

				original = glm::vec4((*(vertexs[i]->getNormal()))[0], (*(vertexs[i]->getNormal()))[1], (*(vertexs[i]->getNormal()))[2], 0);
				normals[i] = normals[i] + glm::vec3((*(vertexs[i]->getWeights()))[j] * glm::transpose(glm::inverse((*(skinMatrix[(*(vertexs[i]->getJoints()))[j]])))) * original);

			}

			normals[i] = glm::normalize(normals[i]);

		}
	}

}
void skin::draw(const glm::mat4& viewProjMtx, GLuint shader) {

	// actiavte the shader program 
	glUseProgram(shader);

	// get the locations and send the uniforms to the shader 
	glUniformMatrix4fv(glGetUniformLocation(shader, "viewProj"), 1, false, (float*)&viewProjMtx);
	glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, (float*)&model);
	glUniform3fv(glGetUniformLocation(shader, "DiffuseColor"), 1, &color[0]);

	// Bind the VAO
	glBindVertexArray(VAO);

	// Bind to the first VBO - We will use it to store the vertices
	glBindBuffer(GL_ARRAY_BUFFER, VBO_positions);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * positions.size(), positions.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

	// Bind to the second VBO - We will use it to store the normals
	glBindBuffer(GL_ARRAY_BUFFER, VBO_normals);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals.size(), normals.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

	// Generate EBO, bind the EBO to the bound VAO and send the data
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

	// draw the points using triangles, indexed with the EBO
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, NULL, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_positions);
	glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_normals);
	glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_STATIC_DRAW);


	// Unbind the VAO and shader program
	glBindVertexArray(0);
	glUseProgram(0);
}