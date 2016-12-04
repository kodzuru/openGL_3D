// Nehe_04.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
float WinWid = 800.0;
float WinHei = 800.0;
unsigned int textures[3]; //������ ���������� �������
int quads[2];
int xrot, yrot;
float boxcol[5][3] = { { 1.0f,0.0f,0.0f },
						{ 1.0f,0.5f,0.0f },
						{ 1.0f,1.0f,0.0f },
						{ 0.0f,1.0f,0.0f },
						{ 0.0f,1.0f,1.0f } };

float topcol[5][3] = { { .5f,0.0f,0.0f },
						{ 0.5f,0.25f,0.0f },
						{ 0.5f,0.5f,0.0f },
						{ 0.0f,0.5f,0.0f },
						{ 0.0f,0.5f,0.5f } };
#include "functions.h" // ��������� �������

int main(int argc, char** argv){
	srand(time(NULL));

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
    return 0;
}

