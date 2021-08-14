#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetWindowTitle("openFrameworks");
	ofSetFrameRate(60);

	ofBackground(0);
	ofSetColor(10, 10, 255);
	ofNoFill();
	ofSetLineWidth(2);

	this->font_size = 55;
	this->font.loadFont("fonts/msgothic.ttc", this->font_size, true, true, true);

	this->charactor_list = { 'A', 'B', 'C', 'D', 'E', 'F',
								'G', 'H', 'I', 'J', 'K', 'L',
								'M', 'N', 'O', 'P', 'Q', 'R',
								'S', 'T', 'U', 'V', 'W', 'X',
								'Y', 'Z', '!' };
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);
	ofRotateY(sin(ofGetFrameNum() * 0.01) * 30);
	ofRotateX(sin(ofGetFrameNum() * 0.02) * 15);

	int sample_count = 180;
	for (int x = this->font_size * -3; x <= this->font_size * 3; x += this->font_size * 1.25)
	{
		for (int y = this->font_size * -3; y <= this->font_size * 3; y += this->font_size * 1.25) {

			for (int z = this->font_size * -3; z <= this->font_size * 3; z += this->font_size * 1.25) {

				ofPath path = this->font.getCharacterAsPoints(this->charactor_list[(int)ofRandom(this->charactor_list.size())], true, false);
				vector<ofPolyline> outline = path.getOutline();
				auto frame_param = (int)ofRandom(sample_count * 2) + ofGetFrameNum() * (int)ofRandom(2, 4);

				for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

					outline[outline_index] = outline[outline_index].getResampledByCount(sample_count);
					vector<glm::vec3> vertices = outline[outline_index].getVertices();

					ofBeginShape();
					for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {

						glm::vec3 vertex = glm::vec3(x + this->font_size * 0.25, y + this->font_size, 0) + glm::vec3(vertices[vertices_index].x, vertices[vertices_index].y, z + vertices[vertices_index].z);

						if (frame_param % (sample_count * 2) < sample_count) {

							if (vertices_index < frame_param % sample_count) {

								ofVertex(vertex);
							}
						}
						else {

							if (vertices_index > frame_param % sample_count) {

								ofVertex(vertex);
							}
						}

						if (vertices_index == frame_param % sample_count) {

							ofFill();
							ofDrawSphere(vertex, 2);
							ofNoFill();
						}

					}
					ofEndShape();
				}
			}
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}