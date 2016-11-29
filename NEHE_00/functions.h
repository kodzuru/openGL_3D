#pragma once
void AXIS_LIST_INIT();

void Initialize() {

	glClearColor(0.0, 0.0, 0.0, 0.0);//����� ������ �� ������� | ���� �������
	glMatrixMode(GL_PROJECTION);//��� ������� ������� ����� �������� � ����������� GL_PROJECTION - ������� ��������
	glLoadIdentity(); //��������� ��������� �������
	glOrtho(-WinWid/2, WinWid/2, -WinHei /2, WinHei/2, -WinHei/2, WinHei/2); //������� ����� ���������(������� ��������) ������������ ������ ������
	//glOrtho(0, WinWid, WinHei, 0, 1, 0); //������� ����� ���������(������� ��������) ������������ ������ �������� ����
	AXIS_LIST_INIT();

}

void Draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //������ ��� GL_COLOR_BUFFER_BIT - ����� �����, GL_DEPTH_BUFFER_BIT - ����� �������
	glEnable(GL_DEPTH_TEST); //�������� �������
	
	// ������ ���������
	glPushMatrix();
	glTranslatef(-100.0, 0.0, 0.0);
	glRotatef(rot, 1.0, 1.0, 0.0);
	for (int i(0); i < 4; i++) {
		glPushMatrix(); {
			glRotatef(i*90, 0.0, 1.0, 0.0);
			glCallList(axis[0]); // �������� ������ ��� ������ �� ID	
		}glPopMatrix();
	}
	glPushMatrix(); {
		glBegin(GL_QUADS); {
			glColor3f(1.0, 1.0, 1.0);
			glVertex3f(-50.0, -50.0, 50.0);
			glColor3f(0.0, 0.0, 1.0);
			glVertex3f(-50.0, -50.0, -50.0);
			glColor3f(1.0, 0.0, 1.0);
			glVertex3f(50.0, -50.0, -50.0);
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f(50.0, -50.0, 50.0);
		}glEnd();
	}glPopMatrix();
	glPopMatrix();

	// ������ �����
	glPushMatrix(); {
		glTranslatef(100.0, 0.0, 0.0);
		glRotatef(rot, 1.0, 1.0, 0.0);
		for (int i(0); i < 4; i++) {
			glPushMatrix(); {
				glRotatef(i * 90, 0.0, 1.0, 0.0);
				glCallList(axis[1]); // �������� ������ ��� ������ �� ID	
			}glPopMatrix();
		}
		for (int i(90); i < 360; i+=180) {
			glPushMatrix(); {
				glRotatef(i, 1.0, 0.0, 0.0);
				glCallList(axis[1]); // �������� ������ ��� ������ �� ID	
			}glPopMatrix();
		}
	}glPopMatrix();

	glDisable(GL_DEPTH_TEST); // ��������� �������
	glutSwapBuffers(); //��� ������������� �������� ������ GLUT_DOUBLE
}


void Timer(int value)
{

	rot += 0;
	glutPostRedisplay(); //���������� ����� ������. ���� ��� ����������
	glutTimerFunc(33, Timer, 0); //���������� ������� �������������(������� �������):���� ��������
}

void SKeyboard(int key, int x, int y)  //������� �������������� � ����������� 2 �� ASCII
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		rot += 10;
		break;
	case GLUT_KEY_RIGHT:
		rot -= 10;
		break;
	}
}

void AXIS_LIST_INIT()
{
	axis[0] = glGenLists(1); // ���������� ����� ������
	if (axis[0] == 1)  // ���� ������ ������
	{
		glNewList(axis[0], GL_COMPILE); //�������� ����������� ������ GL_COMPILE - ����� �� ������ ������ �����������
		 // ��� ����� �������� - GL_COMPILE_AND_EXECUTE

		glBegin(GL_TRIANGLES); {
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f(0.0, 50.0, 0.0);
			glColor3f(0.0, 1.0, 0.0);
			glVertex3f(-50.0, -50.0, 50.0);
			glColor3f(0.0, 0.0, 1.0);
			glVertex3f(50.0, -50.0, 50.0);
		}glEnd();

	}
	glEndList(); // ��������� �������� ������

	axis[1] = glGenLists(1); // ���������� ����� ������
	if (axis[1] == 2)  // ���� ������ ������
	{
		glNewList(axis[1], GL_COMPILE); //�������� ����������� ������ GL_COMPILE - ����� �� ������ ������ �����������
		// ��� ����� �������� - GL_COMPILE_AND_EXECUTE

		glBegin(GL_QUADS); {
			glColor3f(1.0, 1.0, 1.0);
			glVertex3f(-50.0, -50.0, 50.0);
			glColor3f(0.0, 0.0, 1.0);
			glVertex3f(-50.0, 50.0, 50.0);
			glColor3f(1.0, 0.0, 1.0);
			glVertex3f(50.0, 50.0, 50.0);
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f(50.0, -50.0, 50.0);
		}glEnd();

	}
	glEndList(); // ��������� �������� ������
	std::cout << axis[1] << std::endl;

}

