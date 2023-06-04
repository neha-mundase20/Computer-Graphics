#include<iostream>
using namespace std;
#include<GL/glut.h>

float bckcol[3]={1.0,1.0,1.0};
float fcol[3];
float sidecol[3][16];
int v;
int sx,sy;
struct point{
	int x;
	int y;
};

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
		return x;
	}
}

int Round(float a){
	return (a+0.5);
}

void dda(int x1,int y1,int x2,int y2){
	int dx=x2-x1;
	int dy=y2-y1;
	
	float xplot,yplot;
	
	float delx,dely;
	
	int step;
	
	if(abs(dx)>abs(dy)){
		step=abs(dx);
	}	
	
	else{
		step=abs(dy);
	}
	
	delx=(float)dx/step;
	
	dely=(float)dy/step;
	
	xplot=x1;
	yplot=y1;
	
	for(int i=0;i<=step;i++){
		glBegin(GL_POINTS);
		glVertex2d(Round(xplot),Round(yplot));
		glEnd();
		
		xplot=xplot+delx;
		yplot=yplot+dely;
	}
	glFlush();
}

void floodFill(int x,int y,float fcol[3],float bckcol[3]){
	float col[3];
	
	glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,col);
	
	if(col[0]==bckcol[0] && col[1]==bckcol[1] && col[2]==bckcol[2]){   //pixel isn't filled with fill color
		glColor3f(fcol[0],fcol[1],fcol[2]);
		glBegin(GL_POINTS);
		glVertex2d(x,y);
		glEnd();
		glFlush();
		
		floodFill(x+1,y,fcol,bckcol);
		floodFill(x-1,y,fcol,bckcol);
		floodFill(x,y+1,fcol,bckcol);
		floodFill(x,y-1,fcol,bckcol);	
	}
	else{
		return;
	}
	
	/*if(col[0]!=bckcol[0] || col[1]!=bckcol[1] || col[2]!=bckcol[2]){
		return;
	}
	else{
		glColor3f(fcol[0],fcol[1],fcol[2]);
		glBegin(GL_POINTS);
		glVertex2d(x,y);
		glEnd();
		glFlush();
		
		floodFill(x+1,y,fcol,bckcol);
		floodFill(x-1,y,fcol,bckcol);
		floodFill(x,y+1,fcol,bckcol);
		floodFill(x,y-1,fcol,bckcol);	
	}*/
	
}

void drawPoly(){
	int i;
	for(i=0;i<v-1;i++){
		//glPointSize(3);
		glColor3f(sidecol[0][i],sidecol[1][i],sidecol[2][i]);
		dda(p[i].x,p[i].y,p[i+1].x,p[i+1].y);
	}
	//glPointSize(3);
	glColor3f(sidecol[0][i],sidecol[1][i],sidecol[2][i]);
	dda(p[i].x,p[i].y,p[0].x,p[0].y);
}

void mouseInterface(int button,int state,int x,int y){
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
		sx=x;
		sy=800-y;
		
		floodFill(sx,sy,fcol,bckcol);
	}
}

int main(int argc,char**argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800,800);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Flood Fill");
	
	cout<<"\n"<<"Enter the number of vertices of the polygon:"<<"\n";
	cin>>v;
	
	for(int i=0;i<v;i++){
		cout<<"\n"<<"Enter the x-coordinate of the point:"<<"\n";
		cin>>p[i].x;
		
		cout<<"\n"<<"Enter the y-coordinate of the point:"<<"\n";
		cin>>p[i].y;	
	}
	
	cout<<"\n"<<"Enter the Fill Color"<<"\n";
	for(int i=0;i<3;i++){
		cin>>fcol[i];
	}
	
	cout<<"\n"<<"Enter the color of the sides of the polygon"<<"\n";
	for(int i=0;i<v;i++){
		cout<<"\n"<<"Enter the color of the "<<(i+1)<<"side"<<"\n";
		cin>>sidecol[0][i];
		cin>>sidecol[1][i];
		cin>>sidecol[2][i];
		
	}
	
	/*cout<<"\n"<<"Enter the  x-coordinate of seed pixel:"<<"\n";
	cin>>sx;
	
	cout<<"\n"<<"Enter the  y-coordinate of seed pixel:"<<"\n";
	cin>>sy;*/
	
	init();
	glutDisplayFunc(drawPoly);
	glutMouseFunc(mouseInterface);
	glutMainLoop();
	
	return 0;
}
