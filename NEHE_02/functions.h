#pragma once
#pragma warning(disable : 4996)
void WORLD_COUT();
void SetupWorld();
void LoadTextures();
using namespace std;
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


	SetupWorld();
	WORLD_COUT();
	
}

void Draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //������ ��� GL_COLOR_BUFFER_BIT - ����� �����, GL_DEPTH_BUFFER_BIT - ����� �������
	glEnable(GL_DEPTH_TEST);

	float x_m, y_m, z_m, u_m, v_m;
	float xtrans = -xpos;
	float ztrans = -zpos;
	float ytrans = -walkbias - 0.25f;
	
	
	int numtriangles;

	glEnable(GL_TEXTURE_2D); {

		glBindTexture(GL_TEXTURE_2D, textures[2]); // ������������� �� ������ ��������
		glPushMatrix(); {
			glTranslatef(xtrans, ytrans, ztrans);
			glRotatef(lookupdown, 1.0, 0.0, 0.0);
			glRotatef(yrot, 0.0, 1.0, 0.0);
			glColor3f(1.0, 1.0, 1.0);
			numtriangles = sector1.numtriangles;
			// Process Each Triangle
			for (int loop_m = 0; loop_m < numtriangles; loop_m++)
			{
				glBegin(GL_TRIANGLES); {
					glNormal3f(0.0f, 0.0f, 1.0f);
					x_m = sector1.triangle[loop_m].vertex[0].x;
					y_m = sector1.triangle[loop_m].vertex[0].y;
					z_m = sector1.triangle[loop_m].vertex[0].z;
					u_m = sector1.triangle[loop_m].vertex[0].u;
					v_m = sector1.triangle[loop_m].vertex[0].v;
					glTexCoord2f(u_m, v_m); glVertex3f(x_m, y_m, z_m);

					x_m = sector1.triangle[loop_m].vertex[1].x;
					y_m = sector1.triangle[loop_m].vertex[1].y;
					z_m = sector1.triangle[loop_m].vertex[1].z;
					u_m = sector1.triangle[loop_m].vertex[1].u;
					v_m = sector1.triangle[loop_m].vertex[1].v;
					glTexCoord2f(u_m, v_m); glVertex3f(x_m, y_m, z_m);

					x_m = sector1.triangle[loop_m].vertex[2].x;
					y_m = sector1.triangle[loop_m].vertex[2].y;
					z_m = sector1.triangle[loop_m].vertex[2].z;
					u_m = sector1.triangle[loop_m].vertex[2].u;
					v_m = sector1.triangle[loop_m].vertex[2].v;
					glTexCoord2f(u_m, v_m); glVertex3f(x_m, y_m, z_m);
				}glEnd();
			}
		}glPopMatrix();
	}glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);

	glutSwapBuffers(); //��� ������������� �������� ������ GLUT_DOUBLE
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
		// ������������� �� X-���������, ���������� �� ����������� ������
		xpos -= (float)sin(heading*piover180) * 0.05f;
		// ������������� �� Z-���������, ���������� �� ����������� ������
		zpos -= (float)cos(heading*piover180) * 0.05f;
		if (walkbiasangle >= 359.0f)// walkbiasangle>=359?
		{
			walkbiasangle = 0.0f; // ��������� walkbiasangle  0
		}else {                     // � ��������� ������
			// ���� walkbiasangle < 359 ��������� ��� �� 10
			walkbiasangle += 10;
		}
		// ��������� ������� ��������
		walkbias = (float)sin(walkbiasangle * piover180) / 20.0f;
		break;
	case GLUT_KEY_DOWN:
		xpos += sin(heading*piover180) * 0.05;
		zpos += cos(heading*piover180) * 0.05;
		if (walkbiasangle <= 1.0f)
		{
			walkbiasangle = 359.0f;
		}
		else
		{
			walkbiasangle -= 10;
		}
		walkbias = (float)sin(walkbiasangle * piover180) / 20.0f;
		break;
	case GLUT_KEY_RIGHT:
		yrot += 1.5f;              // ������� ����� �����
		break;
	case GLUT_KEY_LEFT:
		yrot -= 1.5f;              // ������� ����� ������
		break;
	case GLUT_KEY_PAGE_UP:
		lookupdown -= 1.0f;
		break;
	case GLUT_KEY_PAGE_DOWN:
		lookupdown += 1.0f;
		break;
	}
}

void readstr(FILE *f, char *string)
{
	do
	{
		fgets(string, 255, f);
	} while ((string[0] == '/') || (string[0] == '\n'));
	return;
}

void SetupWorld() {

	float x, y, z, u, v; // ���������� ������������
	int numtriangles;	// ���-�� ������������� � �������
	FILE *filein;
	char oneline[255]; // ������ ��� ���������� ������
	filein = fopen("World.txt", "rt");				// File To Load World Data From

	readstr(filein, oneline); // ������� ���� ����� ������
	sscanf(oneline, "NUMPOLLIES %d\n", &numtriangles); //���������

	// �������� ������ ���  numtriangles � ������������� ������
	sector1.triangle = new TRIANGLE[numtriangles];
	// ���������� ���-�� ������������� � ������� 1
	sector1.numtriangles = numtriangles;

	// ���� ��� ���� �������������
	// �� ������ ��� ����� � ���� ����������� � �������
	for (int loop = 0; loop < numtriangles; loop++)
	{
		// ���� ��� ���� ������
		// �� ������ ��� ����� � ���� ������� � ������������
		for (int vert = 0; vert < 3; vert++)
		{
			readstr(filein, oneline); // ������� ������ ��� ������

			// ������� ������ � ��������������� ���������� ������
			sscanf(oneline, "%f %f %f %f %f", &x, &y, &z, &u, &v);
			// ��������� ��� ������ � ���������� ����� ��������
			sector1.triangle[loop].vertex[vert].x = x;
			sector1.triangle[loop].vertex[vert].y = y;
			sector1.triangle[loop].vertex[vert].z = z;
			sector1.triangle[loop].vertex[vert].u = u;
			sector1.triangle[loop].vertex[vert].v = v;
		}
	}
	fclose(filein);
}


void WORLD_COUT() {
	for (int loop = 0; loop < 36; loop++)
	{
		for (int vert = 0; vert < 3; vert++)
		{			
			cout << sector1.triangle[loop].vertex[vert].x << "  " ;
			cout << sector1.triangle[loop].vertex[vert].y << "  ";
			cout << sector1.triangle[loop].vertex[vert].z << "  ";
			cout << sector1.triangle[loop].vertex[vert].u << "  ";
			cout << sector1.triangle[loop].vertex[vert].v << "  ";
		}		
		cout << endl;
		cout << endl;
	}

}

void LoadTextures() {


	AUX_RGBImageRec *texture1 = auxDIBImageLoadA("Mud.bmp"); //��������� �������� � RGB

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