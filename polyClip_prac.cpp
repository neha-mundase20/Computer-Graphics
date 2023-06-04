#include<iostream>
using namespace std;
#include<GL/glut.h>
#include<math.h>

struct point{
	float x;
	float y;
};

point ip[16];
point op[16];
int v;
float xmin=200,ymin=200,xmax=600,ymax=600;
int cvc,n=0;

void init(){
	glClearColor(1,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(0,800,0,800);
	
	glFlush();
}

int Round(float x){
	return (x+0.5);
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
	
	float delx=(float)(dx/step);
	float dely=(float)(dy/step);
	
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

void drawClippingWindow(){
	
	glPointSize(3);
	glColor3f(0.0,0.0,0.0);
	dda(xmin,ymin,xmax,ymin);
	dda(xmax,ymin,xmax,ymax);
	dda(xmax,ymax,xmin,ymax);
	dda(xmin,ymax,xmin,ymin);
}

void drawIPPoly(){
	int i;
	glPointSize(3);
	glColor3f(0.0,0.0,1.0);
	for(i=0;i<v-1;i++){
		dda(ip[i].x,ip[i].y,ip[i+1].x,ip[i+1].y);
	}
	dda(ip[i].x,ip[i].y,ip[0].x,ip[0].y);
}

void showClippedVertices(int cvc){
	cout<<"\n";
	for(int i=0;i<cvc;i++){
		cout<<"\n"<<op[i].x<<"\t"<<op[i].y;
		ip[i].x=op[i].x;
		ip[i].y=op[i].y;
	}
}

void drawOPPoly(int cvc){
	int i;
	glPointSize(3);
	glColor3f(0.0,1.0,0.0);
	for(i=0;i<cvc-1;i++){
		dda(op[i].x,op[i].y,op[i+1].x,op[i+1].y);
	}
	dda(op[i].x,op[i].y,op[0].x,op[0].y);
	
	glFlush();
}

void leftClip(float x1,float y1,float x2,float y2){

	float m=((y2-y1)/(x2-x1));	
	
	//out-in
	if(x1<xmin && x2>=xmin){
		
		op[n].x=xmin;
		op[n++].y=y1+m*(xmin-x1);
		cvc++;
	
		op[n].x=x2;
		op[n++].y=y2;
		cvc++;
	}
	
	//in-out
	else if(x1>=xmin && x2<xmin){
		op[n].x=xmin;
		op[n++].y=y1+m*(xmin-x1);
		cvc++;
	}
	
	//in-in
	else if(x1>=xmin && x2>=xmin){
		op[n].x=x2;
		op[n++].y=y2;
		cvc++;
	}
}

void rightClip(float x1,float y1,float x2,float y2){

	float m=((y2-y1)/(x2-x1));	
	
	//out-in
	if(x1>xmax && x2<=xmax){
		
		op[n].x=xmax;
		op[n++].y=y1+m*(xmax-x1);
		cvc++;
	
		op[n].x=x2;
		op[n++].y=y2;
		cvc++;
	}
	
	//in-out
	else if(x1<=xmax && x2>xmax){
		op[n].x=xmax;
		op[n++].y=y1+m*(xmax-x1);
		cvc++;
	}
	
	//in-in
	else if(x1<=xmax && x2<=xmax){
		op[n].x=x2;
		op[n++].y=y2;
		cvc++;
	}
}

void bottomClip(float x1,float y1,float x2,float y2){

	float m=((y2-y1)/(x2-x1));	
	
	//out-in
	if(y1<ymin && y2>=ymin){
		
		op[n].y=ymin;
		op[n++].x=x1+((ymin-y1)/m);
		cvc++;
	
		op[n].x=x2;
		op[n++].y=y2;
		cvc++;
	}
	
	//in-out
	else if(y1>=ymin && y2<ymin){
		op[n].y=ymin;
		op[n++].x=x1+((ymin-y1)/m);
		cvc++;
	}
	
	//in-in
	else if(y1>=ymin && y2>=ymin){
		op[n].x=x2;
		op[n++].y=y2;
		cvc++;
	}
}

void topClip(float x1,float y1,float x2,float y2){

	float m=((y2-y1)/(x2-x1));	
	
	//out-in
	if(y1>ymax && y2<=ymax){
		
		op[n].y=ymax;
		op[n++].x=x1+((ymax-y1)/m);
		cvc++;
	
		op[n].x=x2;
		op[n++].y=y2;
		cvc++;
	}
	
	//in-out
	else if(y1<=ymax && y2>ymax){
		op[n].y=ymax;
		op[n++].x=x1+((ymax-y1)/m);
		cvc++;
	}
	
	//in-in
	else if(y1<=ymax && y2<=ymax){
		op[n].x=x2;
		op[n++].y=y2;
		cvc++;
	}
}

void clippings(){
	int count=0;
	int j;
	for(j=0;j<v-1;j++){
		leftClip(ip[j].x,ip[j].y,ip[j+1].x,ip[j+1].y);
	}
	leftClip(ip[j].x,ip[j].y,ip[0].x,ip[0].y);
	cout<<"\n"<<cvc<<"\n";
	showClippedVertices(cvc);
	//drawOPPoly(cvc);
	count=cvc;
	cvc=0,n=0;
	
	for(j=0;j<count-1;j++){
		rightClip(ip[j].x,ip[j].y,ip[j+1].x,ip[j+1].y);
	}
	rightClip(ip[j].x,ip[j].y,ip[0].x,ip[0].y);
	cout<<"\n"<<cvc<<"\n";
	showClippedVertices(cvc);
	//drawOPPoly(cvc);
	count=cvc;
	cvc=0,n=0;
	
	for(j=0;j<count-1;j++){
		bottomClip(ip[j].x,ip[j].y,ip[j+1].x,ip[j+1].y);
	}
	bottomClip(ip[j].x,ip[j].y,ip[0].x,ip[0].y);
	cout<<"\n"<<cvc<<"\n";
	showClippedVertices(cvc);
	//drawOPPoly(cvc);
	count=cvc;
	cvc=0,n=0;
	
	for(j=0;j<count-1;j++){
		topClip(ip[j].x,ip[j].y,ip[j+1].x,ip[j+1].y);
	}
	topClip(ip[j].x,ip[j].y,ip[0].x,ip[0].y);
	cout<<"\n"<<cvc<<"\n";
	showClippedVertices(cvc);
	drawOPPoly(cvc);
	count=cvc;
}

void mouseInterface(int button,int state,int x,int y){
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
		ip[v].x=x;
		ip[v].y=800-y;
		cout<<"\n"<<ip[v].x<<"\t"<<ip[v].y;
		v++;
	}
	if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN){
		drawIPPoly();
	}
	if(button==GLUT_RIGHT_BUTTON && state==GLUT_UP){
		clippings();
	}
}

int main(int argc,char**argv){
	//int count=0;
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800,800);
	glutInitWindowPosition(0,0);
	
	/*cout<<"\n"<<"Enter the number of vertices of the polygon:";
	cin>>v;
	
	for(int i=0;i<v;i++){
		cout<<"\n"<<"Enter the x-co-ordinate of the point:"<<"\n";
		cin>>ip[i].x;
		cout<<"\n"<<"Enter the y-co-ordinate of the point:"<<"\n";
		cin>>ip[i].y;
	}
	for(int i=0;i<v;i++){
		cout<<"\n"<<ip[i].x<<"\t"<<ip[i].y;
	}*/
	
	glutCreateWindow("Polygon Clipping");
	
	init();
	drawClippingWindow();
	//drawIPPoly();
	
	glutMouseFunc(mouseInterface);
	
	glutMainLoop();
	
	return 0;   
}
