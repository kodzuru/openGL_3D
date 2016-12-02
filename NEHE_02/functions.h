#pragma once
#pragma warning(disable : 4996)
void WORLD_COUT();
void SetupWorld();
void LoadTextures();
using namespace std;
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


	SetupWorld();
	WORLD_COUT();
	
}

void Draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //рисуем фон GL_COLOR_BUFFER_BIT - буфер цвета, GL_DEPTH_BUFFER_BIT - буфер глубины
	glEnable(GL_DEPTH_TEST);

	float x_m, y_m, z_m, u_m, v_m;
	float xtrans = -xpos;
	float ztrans = -zpos;
	float ytrans = -walkbias - 0.25f;
	
	
	int numtriangles;

	glEnable(GL_TEXTURE_2D); {

		glBindTexture(GL_TEXTURE_2D, textures[2]); // переключаемся на первую текстуру
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

	glutSwapBuffers(); //при использовании двойного буфера GLUT_DOUBLE
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
		// Переместиться на X-плоскости, базируемой на направлении игрока
		xpos -= (float)sin(heading*piover180) * 0.05f;
		// Переместиться на Z-плоскости, базируемой на направлении игрока
		zpos -= (float)cos(heading*piover180) * 0.05f;
		if (walkbiasangle >= 359.0f)// walkbiasangle>=359?
		{
			walkbiasangle = 0.0f; // Присвоить walkbiasangle  0
		}else {                     // В противном случае
			// Если walkbiasangle < 359 увеличить его на 10
			walkbiasangle += 10;
		}
		// Иммитация походки человека
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
		yrot += 1.5f;              // Вращать сцену влево
		break;
	case GLUT_KEY_LEFT:
		yrot -= 1.5f;              // Вращать сцену вправо
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

	float x, y, z, u, v; // координаты треугольника
	int numtriangles;	// Кол-во треугольников в секторе
	FILE *filein;
	char oneline[255]; // Строка для сохранения данных
	filein = fopen("World.txt", "rt");				// File To Load World Data From

	readstr(filein, oneline); // Считать одну линию данных
	sscanf(oneline, "NUMPOLLIES %d\n", &numtriangles); //считываем

	// Выделяем память для  numtriangles и устанавливаем ссылку
	sector1.triangle = new TRIANGLE[numtriangles];
	// Определяем кол-во треугольников в Секторе 1
	sector1.numtriangles = numtriangles;

	// Цикл для всех треугольников
	// За каждый шаг цикла – один треугольник в секторе
	for (int loop = 0; loop < numtriangles; loop++)
	{
		// Цикл для всех вершин
		// За каждый шаг цикла – одна вершина в треугольнике
		for (int vert = 0; vert < 3; vert++)
		{
			readstr(filein, oneline); // Считать строку для работы

			// Считать данные в соответствующие переменные вершин
			sscanf(oneline, "%f %f %f %f %f", &x, &y, &z, &u, &v);
			// Сохраняем эти данные в переменные наших структур
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


	AUX_RGBImageRec *texture1 = auxDIBImageLoadA("Mud.bmp"); //загружаем текстуру в RGB

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