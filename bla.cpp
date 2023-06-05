#include<iostream>
using namespace std;
#include<GL/glut.h>
#include<math.h>

int xa,ya,xb,yb;

void init(){
	glClearColor(1,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(-400,400,-400,400);
	
	glFlush();
}

int Round(float a){
	return (int)(a+0.5);
}

void dda(int x1,int y1,int x2,int y2){
	int dx=x2-x1;
	int dy=y2-y1;
	
	int step;
	
	if(abs(dx)>abs(dy)){
		step=abs(dx);
	}
	else{
		step=abs(dy);
	}
	
	float delx=(float)dx/step;
	float dely=(float)dy/step;
	
	float xplot=x1,yplot=y1;
	
	glBegin(GL_POINTS);
	glVertex2d(Round(xplot),Round(yplot));
	glEnd();
	
	for(int i=0;i<step;i++){
		xplot=xplot+delx;
		yplot=yplot+dely;
		
		glBegin(GL_POINTS);
		glVertex2d(Round(xplot),Round(yplot));
		glEnd();
	}
	glFlush();
}

void axes(){
	glColor3f(0.0,0.0,0.0);
	dda(-400,0,400,0);
	dda(0,-400,0,400);
}

void bla(int x1,int y1,int x2,int y2){
	int delx=abs(x2-x1);
	
	int dely=abs(y2-y1);
	
	int xinc,yinc;
	
	if(x2>x1){
		xinc=1;
	}
	else{
		xinc=-1;
	}
	if(y2>y1){
		yinc=1;
	}
	else{
		yinc=-1;
	}
	
	if(delx>dely){
	//gentle slope
	
	int pk=(2*dely)-delx;
	
	int xplot=x1,yplot=y1;
	
	glPointSize(2);
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_POINTS);
	glVertex2d(xplot,yplot);
	glEnd();
	
	for(int i=0;i<delx;i++){
		if(pk>=0){
			pk=pk+(2*dely-2*delx);
			xplot=xplot+xinc;
			yplot=yplot+yinc;
		}
		else{
			pk=pk+(2*dely);
			xplot=xplot+xinc;
			yplot=yplot;
		}
		glBegin(GL_POINTS);
		glVertex2d(xplot,yplot);
		glEnd();
	}
	glFlush();
	}
	
	else{
		int pk=(2*delx)-dely;	
		
		int xplot=x1,yplot=y1;
	
		glPointSize(2);
		glColor3f(0.0,0.0,1.0);
		glBegin(GL_POINTS);
		glVertex2d(xplot,yplot);
		glEnd();
	
		for(int i=0;i<dely;i++){
		if(pk>=0){
			pk=pk+(2*delx-2*dely);
			xplot=xplot+xinc;
			yplot=yplot+yinc;
		}
		else{
			pk=pk+(2*delx);
			xplot=xplot;
			yplot=yplot+yinc;
		}
		glBegin(GL_POINTS);
		glVertex2d(xplot,yplot);
		glEnd();
	}
	glFlush();
	}
}

void mouseInterface(int button,int state,int x,int y){
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
		xa=x-400;
		ya=400-y;
	}
	
	if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN){
		xb=x-400;
		yb=400-y;
		
		bla(xa,ya,xb,yb);
	}
}

int main(int argc,char**argv){
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800,800);
	glutInitWindowPosition(0,0);
	
	/*cout<<"\n"<<"Enter the x-co-ordinate of initial point:"<<"\n";
	cin>>xa;
	
	cout<<"\n"<<"Enter the y-co-ordinate of initial point:"<<"\n";
	cin>>ya;
	
	cout<<"\n"<<"Enter the x-co-ordinate of final point:"<<"\n";
	cin>>xb;
	
	cout<<"\n"<<"Enter the y-co-ordinate of final point:"<<"\n";
	cin>>yb;*/
	
	glutCreateWindow("Bresenham Line Drawing Algorithm");
	
	init();
	axes();
	//bla(xa,ya,xb,yb);
	
	glutMouseFunc(mouseInterface);
	glutMainLoop();
	
	return 0;
}
