#include<iostream>
using namespace std;
#include<GL/glut.h>
#include<math.h>

int xc,yc,r;
int arr[4];

void init(){
	glClearColor(1,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(-400,400,-400,400);
	
	glFlush();
}

int Round(float a){
	return (int)(a+0.5);
}

void dda(float x1,float y1,float x2,float y2){
	float dx=x2-x1;
	float dy=y2-y1;
	
	int step;
	
	if(abs(dx)>abs(dy)){
		step=abs(dx);
	}
	else{
		step=abs(dy);
	}
	
	float delx=dx/step;
	float dely=dy/step;
	cout<<"\n"<<delx<<"\t"<<dely;
	
	float xplot=x1,yplot=y1;
	
	glPointSize(3);
	glColor3f(0.0,0.0,0.0);
	
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
	dda(-400,0,400,0);
	dda(0,-400,0,400);
	//dda(0,0,-350,-350);
}

void bres_circle(int xc,int yc,int r){
	int x=0,y=r;
	
	int pk=3-(2*r);
	
	while(x<=y){
		
		glPointSize(3);
		glColor3f(0.0,0.0,1.0);
		glBegin(GL_POINTS);
		
		glVertex2d(xc+x,yc+y);
		glVertex2d(xc+y,yc+x);
		
		glVertex2d(xc-x,yc+y);
		glVertex2d(xc-y,yc+x);
		
		glVertex2d(xc-x,yc-y);
		glVertex2d(xc-y,yc-x);
		
		glVertex2d(xc+x,yc-y);
		glVertex2d(xc+y,yc-x);
		
		glEnd();
		
		if(pk>=0){
			x=x+1;
			y=y-1;
			pk=pk+4*(x-y)+10;
		}
		else{
			x=x+1;
			y=y;
			pk=pk+4*(x)+6;
		}	
	}
	glFlush();
}

void mouse(int button, int state, int x, int y){
	x = x - 400;
	y = 400 - y;
	
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		xc=x;
		yc=y; 
		arr[0]=x;
		arr[1]=y;
	} 
	
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		arr[2]=x;
		arr[3]=y; 
		
		r=pow(pow((arr[2]-arr[0]),2)+pow((arr[3]-arr[1]),2),0.5);
		
		bres_circle(xc,yc,r);
	}  
}

int main(int argc,char**argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800,800);
	glutInitWindowPosition(0,0);
	
	/*cout<<"\n"<<"Enter the x-co-ordinate of centre of the circle:"<<"\n";
	cin>>xc;
	cout<<"\n"<<"Enter the y-co-ordinate of centre of the circle:"<<"\n";
	cin>>yc;
	cout<<"\n"<<"Enter the radius of the circle:"<<"\n";
	cin>>r;*/
	
	glutCreateWindow("Bresenham circle");
	
	init();
	axes();
	
	glutMouseFunc(mouse);
	
	glutMainLoop();
	
	return 0;
}
