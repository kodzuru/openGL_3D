// NEHE_00.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <glut.h>
#include <GLAux.h>
#include <iostream>
#include <conio.h>
#include <math.h>
#include <cstdlib>

bool  blend = false; // Смешивание НЕТ/ДА?
bool light = false;      // Свет ВКЛ / ВЫКЛ
float dx = 0.0;       // X скорость вращения
float dy = 0.0;       // Y скорость вращения
float dz = 0.0; // Сдвиг вглубь экрана

float LightAmbient[4] = { 0.5, 0.5, 0.5, 1.0 };
float LightDiffuse[4] = { 1.0, 1.0, 1.0, 1.0 };
float LightPosition[4] = { 0.0, 0.0, 1.0, 1.0 };


float WinWid = 800.0;
float WinHei = 800.0;
int rot_x = 0;
int rot_y = 0;
int axis[2];
unsigned int textures[3]; //массив количества текстур
#include "functions.h" // различные функции


using namespace std;
int main(int argc, char** argv) {

	//инициализация
	glutInit(&argc, argv); // глобальная инициализация
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);// инициализация мода дисплея(как рисуем)
	glutInitWindowSize(WinWid, WinHei); // инициализация размеров дисплея/окна
	glutInitWindowPosition(500, 100); // инициализация позиции окна
	glutCreateWindow("Super <openGL> balalaika"); //создание окна


	glutTimerFunc(33, Timer, 0); // регистрация функции анимации(функция таймера)
	glutSpecialFunc(SKeyboard);// регистрация функций клавиатуры 2 для особых клавиш
	glutKeyboardFunc(Keyboard); // регистрация функций клавиатуры 1

	//регистрация
	glutDisplayFunc(Draw); //регистрация функции рисования
	Initialize(); //регистрация функции инициализация
	glutMainLoop(); //запуск главного цикла(стандартная функция GLUT)
	_getch();
	return 1;
}

