#pragma once
void AXIS_LIST_INIT();
void LoadTextures();
void Initialize() {

	LoadTextures();

	glClearColor(0.0, 0.0, 0.0, 0.0);//каким цветом всё стереть | цвет очистки
	glMatrixMode(GL_PROJECTION);//тип матрицы который будет изменять в последующем GL_PROJECTION - матрица проекций
	glLoadIdentity(); //загружаем единичную матрицу
	glOrtho(-WinWid/2, WinWid/2, -WinHei /2, WinHei/2, -WinHei/2, WinHei/2); //задаётся сетка координат(матрица проекции) относительно центра экрана
	//glOrtho(0, WinWid, WinHei, 0, 1, 0); //задаётся сетка координат(матрица проекции) относительно левого верхнего угла
	glMatrixMode(GL_MODELVIEW);

	AXIS_LIST_INIT();
	

}

void Draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //рисуем фон GL_COLOR_BUFFER_BIT - буфер цвета, GL_DEPTH_BUFFER_BIT - буфер глубины
	glEnable(GL_DEPTH_TEST); //включаем глубину
	
	// рисуем пирамидку
	
	glPushMatrix();
	glTranslatef(-100.0, 0.0, 0.0);
	glRotatef(rot, 1.0, 1.0, 0.0);
	for (int i(0); i < 4; i++) {
		glPushMatrix(); {
			glRotatef(i*90, 0.0, 1.0, 0.0);
			glCallList(axis[0]); // вызываем нужный нам список по ID	
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
	

	// рисуем кубик
	glEnable(GL_TEXTURE_2D); //разрешение накладывать текстуру
	glPushMatrix(); {
		//glScalef(5, 5, 5);
		glTranslatef(100.0, 0.0, 0.0);
		glRotatef(rot, 1.0, 1.0, 0.0);
		for (int i(0); i < 4; i++) {
			glPushMatrix(); {
				glRotatef(i * 90, 0.0, 1.0, 0.0);
				glCallList(axis[1]); // вызываем нужный нам список по ID	
			}glPopMatrix();
		}
		for (int i(90); i < 360; i+=180) {
			glPushMatrix(); {
				glRotatef(i, 1.0, 0.0, 0.0);
				glCallList(axis[1]); // вызываем нужный нам список по ID	
			}glPopMatrix();
		}
	}glPopMatrix();
	glDisable(GL_TEXTURE_2D);


	glDisable(GL_DEPTH_TEST); // выключаем глубину
	glutSwapBuffers(); //при использовании двойного буфера GLUT_DOUBLE
}


void Timer(int value)
{

	rot += 0;
	glutPostRedisplay(); //обновление всего экрана. того что нарисовали
	glutTimerFunc(33, Timer, 0); //обновления функции инициализации(функции таймера):типа рекурсия
}

void SKeyboard(int key, int x, int y)  //функция взаимодействия с клавиатурой 2 НЕ ASCII
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
	axis[0] = glGenLists(1); // ренерируем новый список
	if (axis[0] == 1)  // если список создан
	{
		glNewList(axis[0], GL_COMPILE); //начинаем формировать список GL_COMPILE - будет ли список только сформирован
		 // или сразу отображён - GL_COMPILE_AND_EXECUTE

		glBegin(GL_TRIANGLES); {
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f(0.0, 50.0, 0.0);
			glColor3f(0.0, 1.0, 0.0);
			glVertex3f(-50.0, -50.0, 50.0);
			glColor3f(0.0, 0.0, 1.0);
			glVertex3f(50.0, -50.0, 50.0);
		}glEnd();

	}
	glEndList(); // завершаем создание списка
	std::cout << axis[0] << std::endl;
	axis[1] = glGenLists(2); // ренерируем новый список
	if (axis[1] == 2)  // если список создан
	{
		glNewList(axis[1], GL_COMPILE); //начинаем формировать список GL_COMPILE - будет ли список только сформирован
		// или сразу отображён - GL_COMPILE_AND_EXECUTE	

		glBegin(GL_QUADS); {
			glBindTexture(GL_TEXTURE_2D, textures[0]); // переключаемся на первую текстуру
			//glColor3f(1.0, 1.0, 1.0);
			glTexCoord2f(0.0, 0.0);		glVertex3f(-50.0, -50.0, 50.0);
			//glColor3f(0.0, 0.0, 1.0);
			glTexCoord2f(0.0, 1.0);		glVertex3f(-50.0, 50.0, 50.0);
			//glColor3f(1.0, 0.0, 1.0);
			glTexCoord2f(1.0, 1.0);		glVertex3f(50.0, 50.0, 50.0);
			//glColor3f(1.0, 0.0, 0.0);
			glTexCoord2f(1.0, 0.0);		glVertex3f(50.0, -50.0, 50.0);
		}glEnd();

	}
	glEndList(); // завершаем создание списка
	std::cout << axis[1] << std::endl;

}

void LoadTextures() {
	AUX_RGBImageRec *texture1 = auxDIBImageLoadA("example.bmp"); //загружаем текстуру в RGB

	glGenTextures(1, &textures[0]); //загружаем текстуру n - размер массива текстур, указатель на массив текстур
	// загрузка первой текстуры
	glBindTexture(GL_TEXTURE_2D, textures[0]); //выбираем текстуру с которой будем работать и помещаем её в массив текстур
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);// задаём параметры текстуре (параметры приобразования больше-меньше)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);// задаём параметры текстуре (параметры приобразования больше-меньше)
	//1- тип текстуры, 2- , 3- количество цветов, 4- размер по Х, 5 - размер по У, 6 - нарисованая граница, 7 - формат цветов,
	// 8 - тип которым представляется текстура, 9 - сама текстура
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, texture1->data);

}