#include <GL/freeglut.h>
#include <iostream>
#include <ctime>
#include <list>
//#include <Windows.h>

using namespace std;

GLint width = 800, height = 400;
long time0 = 0;
long time_fps = 0;
unsigned long long iter = 0; // количество пересчетов
short count_of_dec = 0; // совершенно ненужная переменная
short delay = 5; // минимальная задержка по времени между пересчетами

struct decagon
{
	double velocity_x = 0;
	double velocity_y = 0;
	double acceleration_x = 0;
	double acceleration_y = -72;
	float x;
	float y;
	float r;
	char increasing = 1;
};
list<decagon> lt;


void drawCircle(float x, float y, float r, int amountSegments);
void Display() {
	glClear(GL_COLOR_BUFFER_BIT);
	for (list<decagon>::iterator i = lt.begin(); i != lt.end(); i++)
	{
		drawCircle(i->x, i->y, i->r, 10);
	}
	glFlush();
}

void Initialize(int w, int h) {
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
}
void drawCircle(float x, float y, float r, int amountSegments) // функция рисования многоугольников
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glColor3f(1,0,0);
	//amountSegments = 15;

	
		for (int i = 0; i < amountSegments; i++)
		{
			/*if (i % 3 == 0 )
				glColor3f(1, 0, 0);
			else if (i % 3 == 1)
				glColor3f(0, 0, 1);
			else if (i % 3 == 2)
				glColor3f(0, 1, 0);*/
			float angle = 2.0 * 3.1415926 * float(i) / float(amountSegments);

			float dx = r * cosf(angle);
			float dy = r * sinf(angle);

			glVertex2f(x + dx, y + dy);
			//glColor3f(0, 0, 1);
		}
	
	glEnd();
}

bool alteration()
{
	bool result = false;
	long time = clock();
	int temp;
	bool flag = false;
	for (list<decagon>::iterator i = lt.begin(); i != lt.end(); i++)
	{
		if (flag) /*TODO: исправить баг с удалением объектов, добавить удаление объектов.*/
		{
			i--;
			flag = false;
		}
		
		if ((i->x >= width + i->r) || (i->y >= height + i->r)) // пропуск элементов, ушедших за экран
		{
			continue;
		}
		if ((i->x <= 0 - i->r) || (i->y <= 0 - i->r))
		{
			continue;
		}

		if (i->increasing == 1 && i->r < 25) // увеличение радиуса шаров
		{
			i->r = 70 / i->velocity_y * 25;
			//i->r += i->r*0.000833;
		}
		else if (i->increasing == -1) // уменьшение радиуса шаров для эффекта исчезновения
		{
			if (i->velocity_y < -200)
				;

			else if (i->velocity_y > 0)
				i->r = 3 + i->velocity_y / 90;
			else if (i->velocity_y < 0)
				i->r = 3 + i->velocity_y / 30;
			//i->r -= i->r*0.0017;
		}
		if (i->acceleration_x != 0) // вычисление изменившейся скорости
		{
			i->velocity_x += i->acceleration_x*(time - time0) / 1000;
		}
		if (i->acceleration_y != 0)
		{
			i->velocity_y += i->acceleration_y*(time - time0) / 1000;
		}
		if (i->velocity_x != 0) // вычисление координаты
		{
			temp = i->x;
			i->x += i->velocity_x*(time - time0) / 1000;
			if ((int)i->x - temp)
			{
				result = true;
			}
		}
		if (i->velocity_y != 0)
		{
			temp = i->y;
			i->y += i->velocity_y*(time - time0) / 1000;
			if ((int)i->y - temp)
			{
				result = true;
			}
		}

		if (i->velocity_y <= 70 && i->increasing != -1) // условие взрыва для увеличивающихся шаров
		{
			short x = 20;
			for (int j = 0; j < 10; j++)// создание маленьких шаров
			{
				decagon *a = new decagon;
				a->x = i->x + x;
				a->y = i->y;
				a->velocity_x = x + rand() % 10;
				a->velocity_y = 40 + rand() % 50;
				a->increasing = -1;
				a->r = 5;
				lt.push_back(*a);
				count_of_dec++;
				x -= 5;
			}
			lt.erase(i++);
			flag = true;
			count_of_dec--;
		}
	}
	time0 = time;
	return result;
}

void Idle()
{		
	if (clock() - time0 < delay)
		return;

	if (clock() - time_fps >= 1000) // выполняется каждую секунду
	{
		for (list<decagon>::iterator i = lt.begin(); i != lt.end();)
		{
			if ((i->x >= width + i->r) || (i->y >= height + i->r) || (i->x <= 0 - i->r) || (i->y <= 0 - i->r)) // пропуск элементов, ушедших за экран
			{
				lt.erase(i++);
			}
			else i++;			
		}
		int n = 1 + rand() % 20; // создание нескольких шаров
		for (int i = 0; i < n; i++)
		{
			
			decagon *a = new decagon;
			a->y = 20;
			a->r = 10;
			a->x = 20 + rand() % 740;
			a->velocity_y = 215 + (-100 + rand() % 120);
			a->increasing = 1;
			
			lt.push_back(*a);
			
			count_of_dec++;
			delete a;
		}
		system("cls");
		cout << "Количество перерисовок за прошлую секунду: " << iter; // вывод количества перерисовок за прошлую секунду
		time_fps = clock();
		iter = 0;
	}
	
	
	bool reshape = alteration(); // перерасчет координат
	if (reshape) // вызов перерисовки
	{
		iter++;
		glutPostRedisplay();
	}
}

int main(int argc, char ** argv) {
	setlocale(LC_ALL, "");
	srand(time(NULL));
	short x = 150;
	for (int i = 0; i < 7; i++)
	{
		decagon *a = new decagon;
		a->y = 20;
		a->r = 10;
		a->x = x;
		a->velocity_y = 215 + (-100 + rand() % 120);
		
		x += 80;
		
		lt.push_back(*a);
		count_of_dec++;
		delete a;
	}
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 200);
	glutCreateWindow("Яковенко В.В. АВТ-615");
	glutDisplayFunc(Display);
	Initialize(width, height);
	glutIdleFunc(Idle);

	time0 = clock();
	time_fps = time0;
	glutMainLoop();
	return 0;
}