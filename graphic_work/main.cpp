#include <GL/freeglut.h>
#include <iostream>
#include <ctime>
#include <list>
//#include <Windows.h>

using namespace std;

GLint width = 800, height = 400;
long time0 = 0;
long time_fps = 0;
unsigned long long iter = 0;
short count_of_dec = 0;
short delay = 0;
enum colors
{
	BLACK, BLUE, GREEN, NAVY, PURPLE, RED, YELLOW, LIME
};
int col;
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
	int color;

};
list<decagon> lt;


struct decagon_list
{
	decagon *this_dec;
	decagon_list *next_dec = NULL;
};
decagon_list *arr;
void add(decagon_list *&list, decagon *element)
{
	decagon_list *next = list;
	while (next->next_dec != NULL)
	{
		next = list->next_dec;
	}
	decagon_list *adding = new decagon_list;
	decagon *a = element;
	adding->this_dec = a;
	/*adding->this_dec->acceleration_x = element->acceleration_x;
	adding->this_dec->acceleration_y = element->acceleration_y;
	adding->this_dec->x = element->x;
	adding->this_dec->y = element->y;
	adding->this_dec->r = element->r;
	adding->this_dec->increasing = element->increasing;
	adding->this_dec->velocity_x = element->velocity_x;
	adding->this_dec->velocity_y = element->velocity_y;*/
	
	next->next_dec = adding;
	count_of_dec++;
}
void drawCircle(float x, float y, float r, int amountSegments, int color);
void Display() {
	glClear(GL_COLOR_BUFFER_BIT);
	/*decagon_list *l = arr;
	drawCircle(l->this_dec->x, l->this_dec->y, l->this_dec->r, 10);
	while (l->next_dec != NULL)
	{
		l = l->next_dec;
		drawCircle(l->this_dec->x, l->this_dec->y, l->this_dec->r, 10);
	}*/
	for (list<decagon>::iterator i = lt.begin(); i != lt.end(); i++)
	{
		drawCircle(i->x, i->y, i->r, 10, i->color);
	}
	glFlush();
}

void Initialize(int w, int h) {
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-200.0, 200.0, -200.0, 200.0, -5.0, 5.0);
	//glOrtho2D(0, w, 0, h);
	gluOrtho2D(0, w, 0, h);
}
void drawCircle(float x, float y, float r, int amountSegments, int color)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glColor3f(1,0,0);
	
	/*switch (col)
	{
	case BLACK:
		glColor3f(1, 0, 0);
		break;
	case BLUE:
		glColor3f(0, 0, 1);
		break;
	case GREEN:
		glColor3f(0, 128/255, 0);
		break;
	case NAVY:
		glColor3f(0, 0, 128/255);
		break;
	case PURPLE:
		glColor3f(128/255, 0, 128/255);
		break;
	case RED:
		glColor3f(1, 0, 0);
		break;
	case YELLOW:
		glColor3f(1, 1, 0);
		break;
	case LIME:
		glColor3f(0, 1, 0);
		break;
	
	}*/
	
		for (int i = 0; i < amountSegments; i++)
		{
			float angle = 2.0 * 3.1415926 * float(i) / float(amountSegments);

			float dx = r * cosf(angle);
			float dy = r * sinf(angle);

			glVertex2f(x + dx, y + dy);
		}
	
	glEnd();
}

bool alteration(decagon_list *&arr, int n)
{
	bool result = false;
	long time = clock();
	int temp;
	/*decagon_list *next = arr->next_dec;
	decagon_list *prev = arr;*/
	bool flag = false;
	for (list<decagon>::iterator i = lt.begin(); i != lt.end(); i++)
	{
		if (flag)
		{
			i--;
			flag = false;
		}
		
		if ((i->x >= width + i->r) || (i->y >= height + i->r))
		{
			//if (lt.size() != 1)
			//{
				//lt.erase(i++);
				//flag = true;
			//}
			//else lt.pop_back();
			//if (lt.size() == 0)
			//	break;
			/*arr = arr->next_dec;
			delete prev;
			prev = NULL;
			count_of_dec--;*/
			continue;
		}
		if ((i->x <= 0 - i->r) || (i->y <= 0 - i->r))
		{
			/*if (lt.size() != 1)
			{
				lt.erase(i++);
				flag = true;
			}*/
			//else lt.pop_back();
			//if (lt.size() == 0)
			//	break;
			/*arr = arr->next_dec;
			delete prev;
			prev = NULL;
			count_of_dec--;*/
			continue;
		}

		if (i->increasing == 1 && i->r < 15)
		{
			i->r += i->r*0.00303;
		}
		else if (i->increasing == -1)
		{
			i->r -= i->r*0.0017;
		}
		if (i->acceleration_x != 0)
		{
			i->velocity_x += i->acceleration_x*(time - time0) / 1000;
		}
		if (i->acceleration_y != 0)
		{
			i->velocity_y += i->acceleration_y*(time - time0) / 1000;
		}
		if (i->velocity_x != 0)
		{
			temp = i->x;
			i->x += i->velocity_x*(time - time0) / 1000;
			//cout << temp << " " << arr[i].x << " ";
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

		if (i->velocity_y <= 70 && i->increasing != -1)
		{

			//delete prev;
			short x = 20;
			for (int j = 0; j < 10; j++)
			{
				decagon *a = new decagon;
				a->x = i->x + x;
				a->y = i->y;
				a->velocity_x = x + rand() % 10;
				a->velocity_y = 40 + rand() % 50;
				a->increasing = -1;
				a->r = 1;
				a->color = rand();
				lt.push_back(*a);
				count_of_dec++;
				x -= 5;
			}
			lt.erase(i++);
			flag = true;
			/*decagon_list *abc = arr->next_dec;
			arr = abc;
			delete prev;
			prev = NULL;*/
			count_of_dec--;
		}
	}
	/*while (true)
	{
		next = arr->next_dec;
		prev = arr;

		if ((prev->this_dec->x >= width + prev->this_dec->r) || (prev->this_dec->y >= height + prev->this_dec->r))
		{
			arr = arr->next_dec;
			delete prev;
			prev = NULL;
			count_of_dec--;
			continue;
		}
		if ((prev->this_dec->x <= 0 - prev->this_dec->r) || (prev->this_dec->y <= 0 - prev->this_dec->r))
		{
			arr = arr->next_dec;
			delete prev;
			prev = NULL;
			count_of_dec--;
			continue;
		}
		//	continue; /* TODO: ÓÄÀËÈÒÜ ÏÅÐÂÛÉ ÝËÅÌÅÍÒ*/
		/*if (prev->this_dec->increasing == 1)
		{
			prev->this_dec->r += prev->this_dec->r*0.0000001;
		}
		else if (prev->this_dec->increasing == -1)
		{
			prev->this_dec->r -= prev->this_dec->r*0.0000003;
		}
		if (prev->this_dec->acceleration_x != 0)
		{
			prev->this_dec->velocity_x += prev->this_dec->acceleration_x*(time - time0) / 1000;
		}
		if (prev->this_dec->acceleration_y != 0)
		{
			prev->this_dec->velocity_y += prev->this_dec->acceleration_y*(time - time0) / 1000;
		}
		if (prev->this_dec->velocity_x != 0)
		{
			temp = prev->this_dec->x;
			prev->this_dec->x += prev->this_dec->velocity_x*(time - time0) / 1000;
			//cout << temp << " " << arr[i].x << " ";
			if ((int)prev->this_dec->x - temp)
			{
				result = true;
			}
		}
		if (prev->this_dec->velocity_y != 0)
		{
			temp = prev->this_dec->y;
			prev->this_dec->y += prev->this_dec->velocity_y*(time - time0) / 1000;
			if ((int)prev->this_dec->y - temp)
			{
				result = true;
			}
		}

		if (prev->this_dec->velocity_y <= 70 && prev->this_dec->increasing != -1)
		{
			
			//delete prev;
			short x = 10;
			for (int j = 0; j < 1; j++)
			{
				decagon *a = new decagon;
				a->x = prev->this_dec->x + x;
				a->y = prev->this_dec->y;
				a->velocity_x = x;
				a->velocity_y = 80;
				a->increasing = -1;
				a->r = 1;
				add(prev, a);
				x -= 10;
			}
			decagon_list *abc = arr->next_dec;
			arr = abc;
			delete prev;
			prev = NULL;
			count_of_dec--;
		}

		if (prev == NULL)
			continue;
		else
			break;
	}
	while (next != NULL)
	{
		if ((next->this_dec->x >= width + next->this_dec->r) || (next->this_dec->y >= height + next->this_dec->r))
		{
			prev->next_dec = next->next_dec;
			delete next;
			next = prev->next_dec;
			count_of_dec--;
			continue;
		}
		//continue;
		if ((next->this_dec->x <= 0 - next->this_dec->r) || (next->this_dec->y <= 0 - next->this_dec->r))
		{
			prev->next_dec = next->next_dec;
			delete next;
			next = prev->next_dec;
			count_of_dec--;
			continue;
		}
		//continue; /*TODO: ÓÄÀËÈÒÜ ÝËÅÌÅÍÒ NEXT*/
		/*if (next->this_dec->increasing == 1)
		{
			next->this_dec->r += next->this_dec->r*0.0000001;
		}
		else if (next->this_dec->increasing == -1)
		{
			next->this_dec->r -= next->this_dec->r*0.0000003;
		}
		if (next->this_dec->acceleration_x != 0)
		{
			next->this_dec->velocity_x += next->this_dec->acceleration_x*(time - time0) / 1000;
		}
		if (next->this_dec->acceleration_y != 0)
		{
			next->this_dec->velocity_y += next->this_dec->acceleration_y*(time - time0) / 1000;
		}
		if (next->this_dec->velocity_x != 0)
		{
			temp = next->this_dec->x;
			next->this_dec->x += next->this_dec->velocity_x*(time - time0) / 1000;
			//cout << temp << " " << arr[i].x << " ";
			if ((int)next->this_dec->x - temp)
			{
				result = true;
			}
		}
		if (next->this_dec->velocity_y != 0)
		{
			temp = next->this_dec->y;
			next->this_dec->y += next->this_dec->velocity_y*(time - time0) / 1000;
			if ((int)next->this_dec->y - temp)
			{
				result = true;
			}
		}

		if (next->this_dec->velocity_y <= 70 && next->this_dec->increasing != -1) 
		{
			cout << "ZPLTCM";
			//delete prev;
			short x = 10;
			for (int j = 0; j < 3; j++)
			{
				decagon *a = new decagon;
				a->x = prev->this_dec->x + x;
				a->y = prev->this_dec->y;
				a->velocity_x = x;
				a->velocity_y = 80;
				a->increasing = -1;
				a->r = 1;
				add(arr, a);
				x -= 10;
			}
			prev->next_dec = next->next_dec;
			delete next;
			next = NULL;
			count_of_dec--;
			//prev = NULL;
		}

		if (next != NULL)
		{
			prev = prev->next_dec;
			next = next->next_dec;
		}
		else
		{
			next = next->next_dec;
		}
	}

	/*for (int i = 0; i < n; i++)
	{
		
		/*if (arr[i].x + arr[i].r - 3 >= width) 
		{
			arr[i].acceleration_x = -arr[i].acceleration_x;
			//int temp = arr[i].velocity_x/100;
			arr[i].velocity_x = (double)(arr[i].velocity_x) * (-1);// +temp;
		}
		if (arr[i].x - arr[i].r <= 0 + 3 )
		{
			arr[i].acceleration_x = -arr[i].acceleration_x;
			arr[i].velocity_x = -arr[i].velocity_x;
		}
		if (arr[i].y + arr[i].r - 3 >= height)
		{
			arr[i].acceleration_y = -arr[i].acceleration_y;
			arr[i].velocity_y = -arr[i].velocity_y;
		}
		if (arr[i].y - arr[i].r <= 0 + 3)
		{
			arr[i].acceleration_y = -arr[i].acceleration_y;
			arr[i].velocity_y = -arr[i].velocity_y;
		}*/
		/*if ((arr[i].x >= width + arr[i].r) || (arr[i].y >= height + arr[i].r))
			continue;
		if ((arr[i].x <= 0 - arr[i].r) || (arr[i].y <= 0 - arr[i].r))
			continue;
		if (arr[i].increasing == 1)
		{
			arr[i].r += arr[i].r*0.0000001;
		}
		else if (arr[i].increasing == -1)
		{
			arr[i].r -= arr[i].r*0.0000003;
		}
		if (arr[i].acceleration_x != 0)
		{			
			arr[i].velocity_x += arr[i].acceleration_x*(time - time0) / 1000;
		}
		if (arr[i].acceleration_y != 0)
		{
			arr[i].velocity_y += arr[i].acceleration_y*(time - time0) / 1000;
		}
		if (arr[i].velocity_x != 0)
		{
			temp = arr[i].x;
			arr[i].x += arr[i].velocity_x*(time - time0) / 1000;
			//cout << temp << " " << arr[i].x << " ";
			if ((int) arr[i].x - temp)
			{
				result = true;
			}
		}
		if (arr[i].velocity_y != 0)
		{
			temp = arr[i].y;
			arr[i].y += arr[i].velocity_y*(time - time0) / 1000;			
			if ((int) arr[i].y - temp)
			{
				result = true;
			}
		}

		if (arr[i].velocity_y <= 70 && arr[i].increasing != -1)
		{
			decagon *a = new decagon;
			a->x = arr[i].x;
			a->y = arr[i].y;
			a->velocity_y = 80;
			a->increasing = -1;
			a->r = 1;
			arr[i] = *a;
			a->x += 10;
			a->velocity_x += 10;
			a->velocity_y -= 10;
			arr[i + 1] = *a;
			a->x -= 20;
			a->velocity_x -= 20;
			//a->velocity_y -= 10;
			arr[i + 2] = *a;
			delete a;
			count_of_dec += 2;
			n += 2;
			/*count_of_dec++;
			n++;*/
			/*//arr[i] = arr[n];

		}
		
	}*/
	time0 = time;
	return result;
}

void Idle()
{		
	if (clock() - time0 < delay)
		return;

	if (clock() - time_fps >= 1000)
	{
		int n = 1 + rand() % 4;
		col = 1 + rand() % 7;
		for (int i = 0; i < n; i++)
		{
			
			decagon *a = new decagon;
			a->y = 20;
			a->r = 10;
			a->x = 20 + rand() % 740;
			a->velocity_y = 215 + (-100 + rand() % 120);
			a->increasing = 1;
			a->color = rand();
			
			lt.push_back(*a);
			
			count_of_dec++;
			delete a;
		}
		system("cls");
		cout << iter;
		time_fps = clock();
		iter = 0;
	}
	
	
	bool reshape = alteration(arr, count_of_dec);
	if (reshape)
	{
		//system("cls");
		iter++;
		glutPostRedisplay();	// Èíèèöèèðîâàòü ñîáûòèå Display
	}
}

int main(int argc, char ** argv) {
	srand(time(NULL));
	//arr = new decagon[100];
	arr = new decagon_list;
	short x = 150;
	for (int i = 0; i < 7; i++)
	{
		decagon *a = new decagon;
		a->y = 20;
		a->r = 10;
		a->x = x;
		a->velocity_y = 215 + (-100 + rand() % 120);
		a->color = rand();
		//a->increasing = -1;
		x += 80;
		//arr->this_dec = a;
		lt.push_back(*a);
		/*a->velocity_y = 150;
		lt.push_back(*a);
		list<decagon>::iterator it = lt.begin();
		lt.erase(it++);
		cout << it->velocity_y;*/
		count_of_dec++;
		delete a;
	}
	/*decagon a;
	a.x = 400;
	a.y = 200;
	a.r = 2;
	a.velocity_y = 100;
	//a.acceleration_x = 25;
	//a.acceleration_y = 25;
	arr[0] = a;
	count_of_dec++;
	decagon b;
	b.x = 200;
	b.y = 40;
	b.r = 20;
	b.velocity_y = 60;
	//b.acceleration_x = 25;
	//b.acceleration_y = 25;
	arr[1] = b;
	count_of_dec++;
	decagon c;
	c.x = 40;
	c.y = 12;
	c.r = 20;
	c.velocity_y = 220;
	//c.acceleration_x = 25;
	//c.acceleration_y = 25;
	arr[2] = c;
	
	//count_of_dec = 3;*/
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 200);
	glutCreateWindow("ßêîâåíêî Â.Â. ÀÂÒ-615");
	glutDisplayFunc(Display);
	Initialize(width, height);
	//system("pause");
	glutIdleFunc(Idle);

	time0 = clock();
	time_fps = time0;
	glutMainLoop();
	//glClearColor(0, 0, 0, 1.0);
	delete[] arr;
	return 0;
}