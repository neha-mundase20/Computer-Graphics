#include<iostream>
using namespace std;
#include<GL/glut.h>
#include<math.h>

struct point{
	float x;
	float y;
	int reg[4];
};

struct point*p1;
struct point*p2;

int xmin=200,ymin=200,xmax=600,ymax=600;

void init(){
	glClearColor(1,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(0,800,0,800);
	
	glFlush();
}

int Round(float a){
	return(int)(a+0.5);
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
	
	float delx=((float)dx/step);
	
	float dely=((float)dy/step);
	
	float xplot=x1,yplot=y1;
	
	glPointSize(2);
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

void regCode(point*p){
	for(int i=0;i<4;i++){
		p->reg[i]=0;
	}
	if(p->x < xmin){
		p->reg[3]=1;
	}
	if(p->x >xmax){
		p->reg[2]=1;
	}
	if(p->y < ymin){
		p->reg[1]=1;
	}
	if(p->y > ymax){
		p->reg[0]=1;
	}
	cout<<"\n";
	for(int i=0;i<4;i++){
		cout<<"\t"<<p->reg[i];
	}
}

void find(point*p){
	int x,y;
	
	float m=((p2->y)-(p1->y))/((p2->x)-(p1->x));
	
	if(p->reg[0]==0 && p->reg[1]==0 && p->reg[2]==0 && p->reg[3]==0){
		return;
	}
	
	if(p->reg[3]==1){
		x=xmin;
	}
	if(p->reg[2]==1){
		x=xmax;
	}
	if(p->reg[1]==1){
		y=ymin;
	}
	if(p->reg[0]==1){
		y=ymax;
	}
	
	if(p->reg[3]==1 || p->reg[2]==1){
		y=(p1->y)+m*(x-(p1->x));
	}
	else{
		x=(p1->x)+((y-(p1->y))/m);
	}
	p->x=x;
	p->y=y;
}

void lineClipping(point*p1,point*p2){
	int And[4];
	regCode(p1);
	regCode(p2);
	
	cout<<"\n";
	for(int i=0;i<4;i++){
		And[i]=p1->reg[i] && p2->reg[i];
		cout<<"\t"<<And[i];
	}
	
	if(And[0]==0 && And[1]==0 && And[2]==0 && And[3]==0){
	
		if((p1->reg[0]==0 && p1->reg[1]==0 && p1->reg[2]==0 && p1->reg[3]==0) && (p2->reg[0]==0 && p2->reg[1]==0 && p2->reg[2]==0 && p2->reg[3]==0)){
			
			glColor3f(0.0,1.0,0.0);
			dda(p1->x,p1->y,p2->x,p2->y);
			
		}
		else{
			find(p1);
			find(p2);
			glColor3f(0.0,1.0,0.0);
			dda(p1->x,p1->y,p2->x,p2->y);
		}
	}
	else{
		return;
	}
}

void drawClippingWindow(){
	glColor3f(0.0,0.0,0.0);
	dda(xmin,ymin,xmax,ymin);
	dda(xmax,ymin,xmax,ymax);
	dda(xmax,ymax,xmin,ymax);
	dda(xmin,ymax,xmin,ymin);
}

void mouseInterface(int button,int state,int x,int y){
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
		p1->x=x;
		p1->y=800-y;
	}
	if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN){
		p2->x=x;
		p2->y=800-y;
		
		glColor3f(0.0,0.0,1.0);
		dda(p1->x,p1->y,p2->x,p2->y);
		lineClipping(p1,p2);
	}
}

int main(int argc,char**argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800,800);
	glutInitWindowPosition(0,0);
	
	p1=new point();
	p2=new point();
	
	/*cout<<"\n"<<"Enter the x-co-ordinate of first point:"<<"\n";
	cin>>p1->x;
	cout<<"\n"<<"Enter the y-co-ordinate of first point:"<<"\n";
	cin>>p1->y;
	cout<<"\n"<<"Enter the x-co-ordinate of second point:"<<"\n";
	cin>>p2->x;
	cout<<"\n"<<"Enter the y-co-ordinate of second point:"<<"\n";
	cin>>p2->y; */
	
	glutCreateWindow("Line Clipping");
	
	init();
	
	drawClippingWindow();
	
	glutMouseFunc(mouseInterface);
	
	/*glColor3f(0.0,0.0,1.0);
	dda(p1->x,p1->y,p2->x,p2->y);
	
	lineClipping(p1,p2);*/
	
	glutMainLoop();
	
	return 0;

}
