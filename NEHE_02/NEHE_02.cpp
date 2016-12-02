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
unsigned int textures[3]; //массив количества текстур


struct VERTEX
{
	float x, y, z;    // 3D координаты
	float u, v;      // Координаты на текстуре
};
struct TRIANGLE
{
	VERTEX vertex[3];          // Массив трёх вершин
};
struct SECTOR
{
	int numtriangles;          // Кол-во треугольников в секторе
	TRIANGLE* triangle;         // Ссылка на массив треугольников

};
SECTOR sector1;
#include "functions.h" // различные функции


void main(int argc, char** argv){
	
	//инициализация
	glutInit(&argc, argv); // глобальная инициализация
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);// инициализация мода дисплея(как рисуем)
	glutInitWindowSize(WinWid, WinHei); // инициализация размеров дисплея/окна
	glutInitWindowPosition(500, 100); // инициализация позиции окна
	glutCreateWindow("Super <openGL> balalaika"); //создание окна



	glutTimerFunc(33, Timer, 0); // регистрация функции анимации(функция таймера)
	glutSpecialFunc(SKeyboard);// регистрация функций клавиатуры 2 для особых клавиш
	//glutKeyboardFunc(Keyboard); // регистрация функций клавиатуры 1

								//регистрация
	glutDisplayFunc(Draw); //регистрация функции рисования
	Initialize(); //регистрация функции инициализация
	glutMainLoop(); //запуск главного цикла(стандартная функция GLUT)


	_getch();
    //return 1;
}

