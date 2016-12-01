// NEHE_00.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <glut.h>
#include <GLAux.h>
#include <iostream>
#include <conio.h>
#include <math.h>
#include <cstdlib>
#include <time.h>

bool  blend = false; // Смешивание НЕТ/ДА?
bool light = false;      // Свет ВКЛ / ВЫКЛ
float dx = 0.0;       // X скорость вращения
float dy = 0.0;       // Y скорость вращения
float dz = 0.0; // Сдвиг вглубь экрана

float LightAmbient[4] = { 0.5, 0.5, 0.5, 1.0 };
float LightDiffuse[4] = { 1.0, 1.0, 1.0, 1.0 };
float LightPosition[4] = { 0.0, 0.0, 1.0, 1.0 };

bool twinkle = true;  // Twinkling Stars (Вращающиеся звезды)
bool tp;    // 'T' клавиша нажата?
const int num = 50;// Количество рисуемых звезд
struct stars  // Создаём структуру для звезд
{
	int r, g, b;                    // Цвет звезды
	GLfloat dist;                   // Расстояние от центра
	GLfloat angle;                // Текущий угол звезды
};
stars star[num];  // Делаем массив 'star' длинной 'num',где элементом является структура 'stars'

float zoom = -15.0f;                    // Расстояние от наблюдателя до звезд
float tilt = 90.0f;                     // Начальный угол
float spin = 0.0;                           // Для вращения звезд
int  loop;                           // Используется для циклов



float WinWid = 800.0;
float WinHei = 800.0;
int rot_x = 0;
int rot_y = 0;
int axis[2];
unsigned int textures[3]; //массив количества текстур
#include "functions.h" // различные функции


using namespace std;
int main(int argc, char** argv) {
	srand(time(NULL));

	for (loop = 0; loop<num; loop++)
	{
		star[loop].angle = 0.0f;
		star[loop].dist = (float(loop) / num)*5.0f;
		star[loop].r = rand() % 256;
		star[loop].g = rand() % 256;
		star[loop].b = rand() % 256;
	}

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

