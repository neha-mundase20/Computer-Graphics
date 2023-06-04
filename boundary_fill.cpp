#include<iostream>
using namespace std;
#include<GL/glut.h>

struct point{
	int x;
	int y;
};

float bcol[3],fcol[3],col[3];
int v,sx,sy;
point p[16];

void init(){
	glClearColor(1,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(0,800,0,800);
	
	glFlush();
}

int abs(int x){
	if(x<0){
		return -x;
	}
	else{
	
	}	return x;
}

int Round(float a){
	return (a+0.5);
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
	
	glColor3f(bcol[0],bcol[1],bcol[2]);
	glBegin(GL_POINTS);
	glVertex2d(Round(xplot),Round(yplot));
	glEnd();
	
	for(int i=0;i<step;i++){
		xplot=xplot+delx;
		yplot=yplot+dely;
		
		glColor3f(bcol[0],bcol[1],bcol[2]);
		glBegin(GL_POINTS);
		glVertex2d(Round(xplot),Round(yplot));
		glEnd();
	}
	glFlush();
}

void boundaryFill(int x,int y,float fcol[3]){
	glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,col);
	
	if((col[0]!=bcol[0] || col[1]!=bcol[1] || col[2] != bcol[2]) && (col[0]!=fcol[0] || col[1]!=fcol[1] || col[1] != fcol[3])){
		glColor3f(fcol[0],fcol[1],fcol[2]);
		glBegin(GL_POINTS);
		glVertex2d(x,y);
		glEnd();
		
		glFlush();
		
		boundaryFill(x+1,y,fcol);
		boundaryFill(x-1,y,fcol);
		boundaryFill(x,y+1,fcol);
		boundaryFill(x,y-1,fcol);
		
		//glFlush();	
	}
	else{
		return;
	}
}

void drawPoly(){
	int i;
	
	for(i=0;i<v-1;i++){
		dda(p[i].x,p[i].y,p[i+1].x,p[i+1].y);
	}
	dda(p[i].x,p[i].y,p[0].x,p[0].y);
	
	boundaryFill(sx,sy,fcol);
}

int main(int argc,char**argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800,800);
	glutInitWindowPosition(0,0);
	
	cout<<"\n"<<"Enter the number of vertices of the polygon:"<<"\n";
	cin>>v;
	
	for(int i=0;i<v;i++){
		cout<<"\n"<<"Enter the x-co-ordinate of the point:"<<"\n";
		cin>>p[i].x;
		
		cout<<"\n"<<"Enter the y-co-ordinate of the point:"<<"\n";
		cin>>p[i].y;
	}
	
	cout<<"\n"<<"Enter the boundary color(RGB Format):"<<"\n";
	for(int i=0;i<3;i++){
		cin>>bcol[i];
	}
	
	cout<<"\n"<<"Enter the fill color(RGB Format):"<<"\n";
	for(int i=0;i<3;i++){
		cin>>fcol[i];
	}
	
	cout<<"\n"<<"Enter the seed pixel(inside pixel):"<<"\n";
	cin>>sx;
	cin>>sy;
	
	glutCreateWindow("Bounday Fill");
	init();
	
	glutDisplayFunc(drawPoly);
	
	glutMainLoop();
	return 0;
}
