#include<iostream>
using namespace std;
#include<GL/glut.h>

int n;
float t;

struct point{
	float x;
	float y;
};

point c_pt[16];


void init(){
	glClearColor(1,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(0,800,0,800);
	
	glFlush();
}

void de_casteljau(float t){
	
	int num=n;
	while (num > 1) {
        for (int i = 0; i < num-1; i++) {
            c_pt[i].x = (1 - t) * c_pt[i].x + t * c_pt[i + 1].x;
            c_pt[i].y = (1 - t) * c_pt[i].y + t * c_pt[i + 1].y;
        }
        --num;
    }  
}

void plotControlPoints(){

	glPointSize(4);
	glColor3f(0.0,0.0,1.0);
	for(int i=0;i<n;i++){
		glBegin(GL_POINTS);
		glVertex2d(c_pt[i].x,c_pt[i].y);
		glEnd();
	}
	glFlush();
}

void draw(){

	plotControlPoints();	
	
	float t_step = 0.01; // Step size for parameter t
	glPointSize(2);
    	glColor3f(0.0, 0.0, 1.0); // Set color for the curve

    	glBegin(GL_LINE_STRIP); // Start drawing the curve as a series of connected line segments
    	for (float t = 0.0; t <= 1.0; t += t_step) {
        	de_casteljau(t);
        	glVertex2d(c_pt[0].x, c_pt[0].y);
    	} 
    	glEnd();
    	glFlush();
}

int main(int argc,char**argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800,800);
	glutInitWindowPosition(0,0);
	
	cout<<"\n"<<"Enter the number of control points:"<<"\n";
	cin>>n;
	
	for(int i =0;i<n;i++){
		cout<<"\n"<<"Enter the x-co-ordinate of control point:"<<"\n";
		cin>>c_pt[i].x;
		
		cout<<"\n"<<"Enter the y-co-ordinate of control point:"<<"\n";
		cin>>c_pt[i].y;
	}
	
	
	for(int i=0;i<n;i++){
		cout<<"\n"<<c_pt[i].x<<"\t"<<c_pt[i].y;
	}
	
	glutCreateWindow("Bezier Curve");
	
	init();
	
	glutDisplayFunc(draw);
	
	glutMainLoop();
	
	return 0;
}
