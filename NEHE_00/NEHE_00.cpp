// NEHE_00.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <glut.h>
#include <GLAux.h>
#include <iostream>
#include <conio.h>
#include <math.h>
#include <cstdlib>



float WinWid = 800.0;
float WinHei = 800.0;
int rot = 0;
int axis[2];
#include "functions.h" // ��������� �������


using namespace std;
int main(int argc, char** argv) {

	//�������������
	glutInit(&argc, argv); // ���������� �������������
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);// ������������� ���� �������(��� ������)
	glutInitWindowSize(WinWid, WinHei); // ������������� �������� �������/����
	glutInitWindowPosition(500, 100); // ������������� ������� ����
	glutCreateWindow("Super <openGL> balalaika"); //�������� ����


	glutTimerFunc(33, Timer, 0); // ����������� ������� ��������(������� �������)
	glutSpecialFunc(SKeyboard);// ����������� ������� ���������� 2 ��� ������ ������

	//�����������
	glutDisplayFunc(Draw); //����������� ������� ���������
	Initialize(); //����������� ������� �������������

	glutMainLoop(); //������ �������� �����(����������� ������� GLUT)
	_getch();
	return 1;
}

