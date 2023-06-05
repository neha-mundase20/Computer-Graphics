#include<iostream>
using namespace std;
#include<GL/glut.h>
#include<math.h>

#define r 0.01745

int n;

void init(){
	glClearColor(1,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(0,1000,0,1000);
	
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

/*int Round(float a){
	return(a+0.5);
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
	
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_POINTS);
	glVertex2d(Round(xplot),Round(yplot));
	glEnd();
	
	for(int i=0;i<step;i++){
		xplot=xplot+delx;
		yplot=yplot+dely;
		
		glColor3f(0.0,0.0,1.0);
		glBegin(GL_POINTS);
		glVertex2d(Round(xplot),Round(yplot));
		glEnd();
	}
	glFlush();
}*/

void koch_generator(float xa,float ya,float xb,float yb,int n){
	
	float xc,yc,xd,yd,midx,midy;

	xc=((2*xa)+xb)/3.0;	
	yc=((2*ya)+yb)/3.0;
	
	xd=((2*xb)+xa)/3.0;	
	yd=((2*yb)+ya)/3.0;
	
	midx=xc + ((xd-xc)*cos(60*r)) + ((yd-yc)*sin(60*r));
	
	midy=yc - ((xd-xc)*sin(60*r)) + ((yd-yc)*cos(60*r));
	
	glFlush();
	
	if(n>0){
		koch_generator(xa, ya, xc, yc, n - 1);
		koch_generator(xc, yc, midx, midy, n - 1);
		koch_generator(midx, midy, xd, yd, n - 1);
		koch_generator(xd, yd, xb, yb, n - 1);	
	}
	
	else{
		/*dda(xa,ya,xc,yc);
		dda(xc,yc,midx,midy);
		dda(midx,midy,xd,yd);
		dda(xd,yd,xb,yb);*/
		
		glPointSize(2);
		glColor3f(0.0,0.0,1.0);
		glBegin(GL_LINES);
		glVertex2d(xa,ya);
		glVertex2d(xc,yc);
		
		glVertex2d(xc,yc);
		glVertex2d(midx,midy);
		
		glVertex2d(midx,midy);
		glVertex2d(xd,yd);
		
		glVertex2d(xd,yd);
		glVertex2d(xb,yb);
		glEnd();
		
		glFlush();
	}
}

void initiator(){
	
	koch_generator(600,100,800,400,n);
	koch_generator(800,400,400,400,n);
	koch_generator(400,400,600,100,n);
}

int main(int argc,char**argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000,1000);
	glutInitWindowPosition(0,0);
	
	cout<<"\n"<<"Enter the number of iterations:"<<"\n";
	cin>>n;
	
	glutCreateWindow("Koch Curve");
	
	init();
	glutDisplayFunc(initiator);
	
	glutMainLoop();
	
	return 0;
}
