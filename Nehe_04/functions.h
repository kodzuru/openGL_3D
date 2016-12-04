#pragma once
void LoadTextures();
void QUAD_LIST_INIT();
void Initialize() {
	LoadTextures();	

	glClearColor(0.0, 0.0, 0.0, 0.0);//каким цветом всё стереть | цвет очистки
	glMatrixMode(GL_PROJECTION);//тип матрицы который будет изменять в последующем GL_PROJECTION - матрица проекций
	glLoadIdentity(); //загружаем единичную матрицу
	//glOrtho(-WinWid / 2, WinWid / 2, -WinHei / 2, WinHei / 2, -WinHei / 2, WinHei / 2); //задаётся сетка координат(матрица проекции) относительно центра экрана
	//glOrtho(0, WinWid, WinHei, 0, 1, 0); //задаётся сетка координат(матрица проекции) относительно левого верхнего угла
	// Максимальное качество перспективной коррекции
	gluPerspective(45.0f, WinWid / WinHei, 0.1f, 100.0f);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE); // Функция смешивания для непрозрачности,

	glMatrixMode(GL_MODELVIEW);
	glShadeModel(GL_SMOOTH);


	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL); // Enable Material Coloring
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	QUAD_LIST_INIT();
}

void Draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //рисуем фон GL_COLOR_BUFFER_BIT - буфер цвета, GL_DEPTH_BUFFER_BIT - буфер глубины
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHT0); // без параметров Quick And Dirty Lighting (Assumes Light0 Is Set Up)

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


	glutSwapBuffers(); //при использовании двойного буфера GLUT_DOUBLE
}

void QUAD_LIST_INIT()
{
	quads[0] = glGenLists(2); // ренерируем два новых список
	if (quads[0] == 0) {
		std::cout << "Error : AXIS_LIST_INIT" << std::endl;
		return;// генерация провалилась выходим
	}
	quads[1] = quads[0] + 1;

	glNewList(quads[0], GL_COMPILE); {
		glEnable(GL_TEXTURE_2D); {

			glBindTexture(GL_TEXTURE_2D, textures[2]); // переключаемся на первую текстуру
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
	}glEndList(); // завершаем создание списка

	glNewList(quads[1], GL_COMPILE); {
		glEnable(GL_TEXTURE_2D); {
			glBindTexture(GL_TEXTURE_2D, textures[2]); // переключаемся на первую текстуру
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
	}glEndList(); // завершаем создание списка
	

}


void LoadTextures() {


	AUX_RGBImageRec *texture1 = auxDIBImageLoadA("Cube.bmp"); //загружаем текстуру в RGB

	glGenTextures(3, &textures[0]); //загружаем текстуру n - размер массива текстур, указатель на массив текстур


									// Создание текстуры с фильтром по соседним пикселям
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // ( НОВОЕ )
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // ( НОВОЕ )
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY,
		0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);

	// Создание текстуры с линейной фильтрацией
	glBindTexture(GL_TEXTURE_2D, textures[1]); //выбираем текстуру с которой будем работать и помещаем её в массив текстур
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);// задаём параметры текстуре (параметры приобразования больше-меньше)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);// задаём параметры текстуре (параметры приобразования больше-меньше)
																	 //1- тип текстуры, 2- , 3- количество цветов, 4- размер по Х, 5 - размер по У, 6 - нарисованая граница, 7 - формат цветов,
																	 // 8 - тип которым представляется текстура, 9 - сама текстура
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, texture1->data);


	// Создание Текстуры с Мип-Наложением
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, texture1->sizeX, texture1->sizeY,
		GL_RGB, GL_UNSIGNED_BYTE, texture1->data);


	if (texture1) { // Если текстура существует
		if (texture1->data) {    // Если изображение текстуры существует
			delete[] texture1->data; // Освобождение памяти изображения текстуры
		}
		delete[] texture1;        // Освобождение памяти под структуру
	}
}

void Timer(int value)
{

	Draw();
	glutPostRedisplay(); //обновление всего экрана. того что нарисовали
	glutTimerFunc(33, Timer, 0); //обновления функции инициализации(функции таймера):типа рекурсия
}

void SKeyboard(int key, int x, int y)  //функция взаимодействия с клавиатурой 2 НЕ ASCII
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