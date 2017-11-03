//Algoritma Bresenham

#include <GL\freeglut.h>
#include <GL\glut.h>
#include <iostream>

using namespace std;

//identifier fungsi
void init();
void display(void);
void bresenham(void);

//  posisi window di layar
int window_x;
int window_y;

//  ukuran window
int window_width = 480;
int window_height = 480;

//  judul window
char *judul_window = "Algoritma Bresenham";

void main(int argc, char **argv)
{
	//  inisialisasi GLUT (OpenGL Utility Toolkit)
	glutInit(&argc, argv);
	// set posisi window supaya berada di tengah 
	window_x = (glutGet(GLUT_SCREEN_WIDTH) - window_width) / 2;
	window_y = (glutGet(GLUT_SCREEN_HEIGHT) - window_height) / 2;
	glutInitWindowSize(window_width, window_height); //set ukuran window 
	glutInitWindowPosition(window_x, window_y); //set posisi window

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE); // set display RGB dan double buffer
	glutCreateWindow(judul_window); //set judul window

	
	init(); //jalankan fungsi init 
	glutDisplayFunc(display); //  set fungsi display
	glutMainLoop(); // set loop pemrosesan GLUT
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0); //set warna background 
	glColor3f(1.0, 1.0, 1.0); //set warna titik
	glPointSize(2.0); //set ukuran titik
	glMatrixMode(GL_PROJECTION); //set mode matriks yang digunakan 
	glLoadIdentity(); // load matriks identitas
	gluOrtho2D(0.0, 800.0, 0.0, 600.0); // set ukuran viewing window
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT); //clear color untuk membersihkan layar menjadi hitam
	bresenham(); //jalankan fungsi bresenham
	glutSwapBuffers(); //swap buffer 
}

void bresenham(void) {
	int x1, y1, x2, y2, x, y, dx, dy, xend, p, duady, duadydx;
	int x3, y3, x4, y4,s,t, ds, dt,xxend, tigady,tigadydx, pp;
	//tentukan titik awal dan akhir
	x1 = 1; //10
	y1 = 300; //10
	x2 = 1000; //500
	y2 = 300; //400

	//ini untuk garis kedua
	x3 = 1;
	y3 = 100;
	x4 = 1000;
	y4 = 100;
	x = x1 && x3; //x1
	y = y1 && y3; //y1

	//hitung dx dan dy
	dx = abs(x2 - x1);
	dy = abs(y2 - y1);

	ds = abs(x4 - x3);
	dt = abs(y4 - y3);
	
	//hitung p 
	p = 2 * dy - dx;
	duady = 2 * dy;
	duadydx = 2 * (dy - dx);

	pp = 2 * dt - ds;
	tigady = 2 * dt;
	tigadydx = 2 * (dt - ds);
	
	//tentukan titik awal dan akhir
	if (x1 > x2 && x3 > x4) { //if (x1 > x2)
		x = x2; // x = x2
		y = y2; // y = y2
		s = x4;
		t = y4;
		xend = x1;
		xxend = x3;
	}
	else
	{
		x = x1; // x1
		y = y1; // y1
		s = x3;
		t = y3;
		xend = x2;
		xxend = x4;
	}


	//gambar titik awal
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glVertex2i(s, t);

	//perulangan untuk menggambar titik-titik 
	while (x < xend && s < xxend) {
		x++;
		s++;
		if (p < 0 && pp < 0) {
			p += duady;
			pp += tigady;
		}
		else
		{
			if (y1 > y2 && y3 > y4) {
				y--;
				t--;
			}
			else 
				y++;
				t++;
		
			p += duadydx;
			pp += tigadydx;
		}
		glVertex2i(x, y);
		glVertex2i(s, t);
	}

	glEnd();
	glFlush();
}

