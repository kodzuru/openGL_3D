// NEHE_02.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

float WinWid = 800.0;
float WinHei = 800.0;
float z_index = 0;
const float piover180 = 0.0174532925;
int dz = 0;
float heading;
float xpos;
float zpos;
float	yrot;				// Y Rotation
float walkbias = 0;
float walkbiasangle = 0;
float lookupdown = 0.0f;
float	z = 0.0f;				// Depth Into The Screen
unsigned int textures[3]; //������ ���������� �������


struct VERTEX
{
	float x, y, z;    // 3D ����������
	float u, v;      // ���������� �� ��������
};
struct TRIANGLE
{
	VERTEX vertex[3];          // ������ ��� ������
};
struct SECTOR
{
	int numtriangles;          // ���-�� ������������� � �������
	TRIANGLE* triangle;         // ������ �� ������ �������������

};
SECTOR sector1;
#include "functions.h" // ��������� �������


void main(int argc, char** argv){
	
	//�������������
	glutInit(&argc, argv); // ���������� �������������
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);// ������������� ���� �������(��� ������)
	glutInitWindowSize(WinWid, WinHei); // ������������� �������� �������/����
	glutInitWindowPosition(500, 100); // ������������� ������� ����
	glutCreateWindow("Super <openGL> balalaika"); //�������� ����



	glutTimerFunc(33, Timer, 0); // ����������� ������� ��������(������� �������)
	glutSpecialFunc(SKeyboard);// ����������� ������� ���������� 2 ��� ������ ������
	//glutKeyboardFunc(Keyboard); // ����������� ������� ���������� 1

								//�����������
	glutDisplayFunc(Draw); //����������� ������� ���������
	Initialize(); //����������� ������� �������������
	glutMainLoop(); //������ �������� �����(����������� ������� GLUT)


	_getch();
    //return 1;
}

