#pragma once
void LoadTextures();
void QUAD_LIST_INIT();
void Initialize() {
	LoadTextures();	

	glClearColor(0.0, 0.0, 0.0, 0.0);//����� ������ �� ������� | ���� �������
	glMatrixMode(GL_PROJECTION);//��� ������� ������� ����� �������� � ����������� GL_PROJECTION - ������� ��������
	glLoadIdentity(); //��������� ��������� �������
	//glOrtho(-WinWid / 2, WinWid / 2, -WinHei / 2, WinHei / 2, -WinHei / 2, WinHei / 2); //������� ����� ���������(������� ��������) ������������ ������ ������
	//glOrtho(0, WinWid, WinHei, 0, 1, 0); //������� ����� ���������(������� ��������) ������������ ������ �������� ����
	// ������������ �������� ������������� ���������
	gluPerspective(45.0f, WinWid / WinHei, 0.1f, 100.0f);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE); // ������� ���������� ��� ��������������,

	glMatrixMode(GL_MODELVIEW);
	glShadeModel(GL_SMOOTH);


	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL); // Enable Material Coloring
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	QUAD_LIST_INIT();
}

void Draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //������ ��� GL_COLOR_BUFFER_BIT - ����� �����, GL_DEPTH_BUFFER_BIT - ����� �������
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHT0); // ��� ���������� Quick And Dirty Lighting (Assumes Light0 Is Set Up)

	glPushMatrix(); {
		for (int i = 1; i<6; i++)
		{
			for (int j = 0; j<i; j++)
			{
				glLoadIdentity();							// Reset The View
				glTranslatef(1.4f + (float(j)*2.8f) - (float(i)*1.4f), ((6.0f - float(i))*2.4f) - 7.0f, -20.0f);
				glRotatef(45.0f - (2.0f*i) + xrot, 1.0f, 0.0f, 0.0f);
				glRotatef(45.0f + yrot, 0.0f, 1.0f, 0.0f);
				glColor3fv(boxcol[i - 1]);
				glCallList(quads[0]);
				glColor3fv(topcol[i - 1]);
				glCallList(quads[1]);
			}
		}
	}glPopMatrix();
	
		

	glDisable(GL_LIGHT0);


	glutSwapBuffers(); //��� ������������� �������� ������ GLUT_DOUBLE
}

void QUAD_LIST_INIT()
{
	quads[0] = glGenLists(2); // ���������� ��� ����� ������
	if (quads[0] == 0) {
		std::cout << "Error : AXIS_LIST_INIT" << std::endl;
		return;// ��������� ����������� �������
	}
	quads[1] = quads[0] + 1;

	glNewList(quads[0], GL_COMPILE); {
		glEnable(GL_TEXTURE_2D); {

			glBindTexture(GL_TEXTURE_2D, textures[2]); // ������������� �� ������ ��������
			glPushMatrix();{
				//glRotatef(90, 0.0, 0.0, 1.0);
				//glTranslatef(0.0, 0.0, 1.0);
				glBegin(GL_QUADS); {
					// Bottom Face
					glNormal3f(0.0f, 0.0f, 0.0f);
					glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
					glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
					glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
					// Front Face
					glNormal3f(0.0f, 0.0f, 1.0f);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
					glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
					glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
					glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
					// Back Face
					glNormal3f(0.0f, 0.0f, -1.0f);
					glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
					glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
					glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
					// Right face
					glNormal3f(1.0f, 0.0f, 0.0f);
					glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
					glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
					glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
					// Left Face
					glNormal3f(-1.0f, 0.0f, 0.0f);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
					glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
					glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
					glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
				}glEnd();
			}glPopMatrix();
		}glDisable(GL_TEXTURE_2D);
	}glEndList(); // ��������� �������� ������

	glNewList(quads[1], GL_COMPILE); {
		glEnable(GL_TEXTURE_2D); {
			glBindTexture(GL_TEXTURE_2D, textures[2]); // ������������� �� ������ ��������
			glPushMatrix(); {
				glBegin(GL_QUADS); {
					// Top Face
					glNormal3f(0.0f, 1.0f, 0.0f);
					glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
					glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
					glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
				}glEnd();
			}glPopMatrix();
		}glDisable(GL_TEXTURE_2D);
	}glEndList(); // ��������� �������� ������
	

}


void LoadTextures() {


	AUX_RGBImageRec *texture1 = auxDIBImageLoadA("Cube.bmp"); //��������� �������� � RGB

	glGenTextures(3, &textures[0]); //��������� �������� n - ������ ������� �������, ��������� �� ������ �������


									// �������� �������� � �������� �� �������� ��������
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // ( ����� )
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // ( ����� )
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY,
		0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);

	// �������� �������� � �������� �����������
	glBindTexture(GL_TEXTURE_2D, textures[1]); //�������� �������� � ������� ����� �������� � �������� � � ������ �������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);// ����� ��������� �������� (��������� �������������� ������-������)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);// ����� ��������� �������� (��������� �������������� ������-������)
																	 //1- ��� ��������, 2- , 3- ���������� ������, 4- ������ �� �, 5 - ������ �� �, 6 - ����������� �������, 7 - ������ ������,
																	 // 8 - ��� ������� �������������� ��������, 9 - ���� ��������
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, texture1->data);


	// �������� �������� � ���-����������
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, texture1->sizeX, texture1->sizeY,
		GL_RGB, GL_UNSIGNED_BYTE, texture1->data);


	if (texture1) { // ���� �������� ����������
		if (texture1->data) {    // ���� ����������� �������� ����������
			delete[] texture1->data; // ������������ ������ ����������� ��������
		}
		delete[] texture1;        // ������������ ������ ��� ���������
	}
}

void Timer(int value)
{

	Draw();
	glutPostRedisplay(); //���������� ����� ������. ���� ��� ����������
	glutTimerFunc(33, Timer, 0); //���������� ������� �������������(������� �������):���� ��������
}

void SKeyboard(int key, int x, int y)  //������� �������������� � ����������� 2 �� ASCII
{
	switch (key)
	{
	case GLUT_KEY_UP:
		xrot -= 5;
		break;
	case GLUT_KEY_DOWN:
		xrot += 5;
		break;
	case GLUT_KEY_LEFT:
		yrot -= 5;
		break;
	case GLUT_KEY_RIGHT:
		yrot += 5;
		break;
	}
}