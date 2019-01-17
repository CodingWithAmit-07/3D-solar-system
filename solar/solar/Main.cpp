#include"import.h"

#define PI 3.141
int mercuryRadius = 200;
int venusRadius = mercuryRadius + 150;
int earthRadius = venusRadius + 150;
int marsRadius = earthRadius + 150;
int jupiterRadius = marsRadius + 200;
int saturnRadius = jupiterRadius + 200;
int uranusRadius = saturnRadius + 150;
int neptuneRadius = uranusRadius + 150;

float mercuryAngle = 0.0f;
float venusAngle = 0.0f;
float earthAngle = 0.0f;
float marsAngle = 0.0f;
float jupiterAngle = 0.0f;
float saturnAngle = 0.0f;
float uranusAngle = 0.0f;
float neptuneAngle = 0.0f;

float mainangle = 0;

float st = 0;
float st2 = 0;
float st3 = 0;
float st4 = 0;
float st5 = 0;
float st6 = 0;
float Angle = 0;
float angle = 0.0f;
float j = 0.0f;
RGBApixmap pic[11];
Mesh t;
Camera cam;


GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat mat_specular[] = { 0.0, 0.0, 0.0, 0.0 };
GLfloat mat_shininess[] = { 50.0 };
GLfloat light_position[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat model_ambient[] = { 1.0, 1.0, 1.0, 1.0 };

void setupMaterials()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);
}

void changeColour(GLfloat r, GLfloat g, GLfloat b, GLfloat A) {
	model_ambient[0] = r;
	model_ambient[1] = g;
	model_ambient[2] = b;
	model_ambient[3] = A;
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);
}

void Lighting()
{
	float LightAmbient[] = { 0.4, 0.4, 0.8, 1.0 };
	float LightDiffuse[] = { 0.6, 0.6, 0.3, 1.0 };
	float Light_Specular[] = { 0.5, 0.5, 0.5, 1.0 };
	float Light_Position[] = { 0.0, 0.0, 0.3, 0.0 };

	float Model_Ambient[] = { 0.4, 0.4, 0.4, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Light_Specular);
	glLightfv(GL_LIGHT0, GL_POSITION, Light_Position);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Model_Ambient);

	glDepthFunc(GL_LEQUAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
}

void Paths(void){
	glBegin(GL_LINE_STRIP);
	for (double i = 0; i < 360; i += 0.1)
		glVertex3f(cos(i) * mercuryRadius, 1.0, sin(i) * mercuryRadius);
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (double i = 0; i < 360; i += 0.1)
		glVertex3f(cos(i) * venusRadius, 1.0, sin(i) * venusRadius);
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (double i = 0; i < 360; i += 0.1)
		glVertex3f(cos(i) * earthRadius, 1.0, sin(i) * earthRadius);
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (double i = 0; i < 360; i += 0.1)
		glVertex3f(cos(i) * marsRadius, 1.0, sin(i) * marsRadius);
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (double i = 0; i < 360; i += 0.1)
		glVertex3f(cos(i) * jupiterRadius, 1.0, sin(i) * jupiterRadius);
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (double i = 0; i < 360; i += 0.1)
		glVertex3f(cos(i) * saturnRadius, 1.0, sin(i) * saturnRadius);
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (double i = 0; i < 360; i += 0.1)
		glVertex3f(cos(i) * uranusRadius, 1.0, sin(i) * uranusRadius);
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (double i = 0; i < 360; i += 0.1)
		glVertex3f(cos(i) * neptuneRadius, 1.0, sin(i) * neptuneRadius);
	glEnd();
}

void MoonPath(void){
	glPushMatrix();
	glRotatef(earthAngle, 0.0f, 1.0f, 0.0f);
	glTranslatef(earthRadius, 0.0, 0.0);
	changeColour(1.0, 1.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	for (double i = 0; i < 2 * PI; i += PI / 1000) glVertex3f(cos(i) * 50, 0.0, sin(i) * 50);
	glEnd();
	glPopMatrix();
}

void Saturndish(void){
	glPushMatrix();
	glRotatef(saturnAngle, 0.0f, 1.0f, 0.0f);
	glTranslatef(saturnRadius, 0.0, 0.0);
	glRotatef(80.0f, 1.0f, 0.0f, 0.0f); /// Rotate the circles
	changeColour(163 / 255.0, 149 / 255.0, 79 / 255.0, 0.0);
	glBegin(GL_LINE_STRIP);
	for (double i = 0; i < 360; i += 0.1) glVertex3f(cos(i) * 70, sin(i) * 70, 0.0);
	for (double i = 0; i < 360; i += 0.1) glVertex3f(cos(i) * 75, sin(i) * 75, 0.0);
	for (double i = 0; i < 360; i += 0.1) glVertex3f(cos(i) * 80, sin(i) * 80, 0.0);
	for (double i = 0; i < 360; i += 0.1) glVertex3f(cos(i) * 85, sin(i) * 85, 0.0);
	for (double i = 0; i < 360; i += 0.1) glVertex3f(cos(i) * 90, sin(i) * 90, 0.0);
	for (double i = 0; i < 360; i += 0.1) glVertex3f(cos(i) * 95, sin(i) * 95, 0.0);
	for (double i = 0; i < 360; i += 0.1) glVertex3f(cos(i) * 100, sin(i) * 100, 0.0);
	glEnd();
	glPopMatrix();
}

void pushCT(){
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
}

void popCT(){
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void draw(int row, int col, int x, int y, int z){
	pushCT();
	glTranslatef(0, 0, 0);
	for (int i = 0; i < row; i++)
	{
		pushCT();
		for (int j = 0; j < col; j++)
		{
			glColor3f(1, 0, 0);
			t.drawMesh();
			glTranslatef(x, 0, 0);
		}
		popCT();
		glTranslatef(0, 0, z);
	}
	popCT();
}

void drawsphere() {
	int nslices = 20;
	int nstacks = 20;
	int radius = 30.6;
	double deltheta = 2 * PI / nslices;
	double delalpha = PI / nstacks;
	Point2 p;
	double alpha, theta;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	int d = 30;
	for (int i = 0; i < nstacks; i++)
	{
		for (int j = 0; j < nslices; j++)
		{
			alpha = (i*PI) / nstacks;
			theta = (j*PI * 2) / nslices;

			glEnable(GL_DEPTH_TEST);
			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
			glBindTexture(GL_TEXTURE_2D, 2003);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); 	glVertex3f(radius*sin(alpha)*sin(theta), radius*sin(alpha)*cos(theta), radius*cos(alpha));
			glTexCoord2f(0.0, 1.0); glVertex3f(radius*sin(alpha)*sin(theta + deltheta), radius*sin(alpha)*cos(theta + deltheta), radius*cos(alpha));
			glTexCoord2f(1.0, 1.0); glVertex3f(radius*sin(alpha + delalpha)*sin(theta + deltheta), radius*sin(alpha + delalpha)*cos(theta + deltheta), radius*cos(alpha + delalpha));
			glTexCoord2f(1.0, 0.0); 	glVertex3f(radius*sin(alpha + delalpha)*sin(theta), radius*sin(alpha + delalpha)*cos(theta), radius*cos(alpha + delalpha));
			glEnd();

			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
		}
	}
}

void drawMountain(float bradius, float height)
{

	GLUquadricObj *mount;

	mount = gluNewQuadric();
	gluQuadricDrawStyle(mount, GL_POLYGON);

	glPushMatrix();


	glRotatef(-90.0, 1.0, 0.0, 0.0);
	//glColor3f(0.0, 0.1, 0.3);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glEnable(GL_COLOR_MATERIAL);

	//glColor3f(0.447, 0.062, 0.062);
	glColor3f(1, 1, 1);
	gluCylinder(mount, bradius, 0.0, height, 40, 5);
	glPopMatrix();

	glDisable(GL_COLOR_MATERIAL);
}

void setMountainsPosition() {

	int br = 3;                   // br = base radius of Cylinder to make mountains
	int displacement = 0;          // to draw mountains without GAP/SPACE between them...

	for (int i = 0; i < 2; i++)
	{
		glPushMatrix();
		glTranslatef(-6 + displacement, 0, -15);
		drawMountain(2.5, 8);
		displacement += (br);
		glPopMatrix();
	}

	for (int i = 0; i < 5; i++)
	{
		glPushMatrix();
		glTranslatef(-2 + displacement, 0, -15);
		drawMountain(3, 8);
		displacement += (br);
		glPopMatrix();
	}
}

void drawgrass_barn(void){

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glPushMatrix();               
	glBindTexture(GL_TEXTURE_2D, 2004);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-10, 0, -20);

	glTexCoord2f(0, 1);
	glVertex3f(-10, 0, 15);

	glTexCoord2f(1, 1);
	glVertex3f(20, 0, 15);

	glTexCoord2f(1, 0);
	glVertex3f(20, 0, -20);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, 2005);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-20, 0, -20);

	glTexCoord2f(0, 1);
	glVertex3f(-20, 0, 20);

	glTexCoord2f(1, 1);
	glVertex3f(-13, 0, 20);

	glTexCoord2f(1, 0);
	glVertex3f(-13, 0, -20);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, 2007);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0);
	glVertex3f(-13, 0, -20);

	glTexCoord2f(0, 0);
	glVertex3f(-13, 0, 20);

	glTexCoord2f(0, 1);
	glVertex3f(-10, 0, 20);

	glTexCoord2f(1, 1);
	glVertex3f(-10, 0, -20);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, 2006);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-10, 0, 15);

	glTexCoord2f(0, 1);
	glVertex3f(-10, 0, 20);

	glTexCoord2f(1, 1);
	glVertex3f(20, 0, 20);

	glTexCoord2f(1, 0);
	glVertex3f(20, 0, 15);
	glEnd();
	glPopMatrix();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	glPushAttrib(GL_LIGHTING);     // save context
	Lighting();

	draw(3, 3, 3, 0, 3);
	draw(3, 3, -3, 0, 3);
	draw(3, 3, -3, 0, -3);
	draw(3, 3, 3, 0, -3);

	glPopAttrib();

	setMountainsPosition();
}

void drawcube(Point3 p0, Point3 p1, Point3 p2, Point3 p3, Point3 p4, Point3 p5, Point3 p6, Point3 p7, double id){
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glPushMatrix();                  //left
	glBindTexture(GL_TEXTURE_2D, id);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(p1.x, p1.y, p1.z);

	glTexCoord2f(1, 0);
	glVertex3f(p0.x, p0.y, p0.z);

	glTexCoord2f(1, 1);
	glVertex3f(p3.x, p3.y, p3.z);

	glTexCoord2f(0, 1);
	glVertex3f(p2.x, p2.y, p2.z);
	glEnd();
	glPopMatrix();

	glPushMatrix();                  //back
	glBindTexture(GL_TEXTURE_2D, id);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(p5.x, p5.y, p5.z);

	glTexCoord2f(1, 0);
	glVertex3f(p1.x, p1.y, p1.z);

	glTexCoord2f(1, 1);
	glVertex3f(p2.x, p2.y, p2.z);

	glTexCoord2f(0, 1);
	glVertex3f(p6.x, p6.y, p6.z);
	glEnd();
	glPopMatrix();

	glPushMatrix();                  //right
	glBindTexture(GL_TEXTURE_2D, id);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(p4.x, p4.y, p4.z);

	glTexCoord2f(1, 0);
	glVertex3f(p5.x, p5.y, p5.z);

	glTexCoord2f(1, 1);
	glVertex3f(p6.x, p6.y, p6.z);

	glTexCoord2f(0, 1);
	glVertex3f(p7.x, p7.y, p7.z);
	glEnd();
	glPopMatrix();

	glPushMatrix();                  //front
	glBindTexture(GL_TEXTURE_2D, id);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(p0.x, p0.y, p0.z);

	glTexCoord2f(1, 0);
	glVertex3f(p4.x, p4.y, p4.z);

	glTexCoord2f(1, 1);
	glVertex3f(p7.x, p7.y, p7.z);

	glTexCoord2f(0, 1);
	glVertex3f(p3.x, p3.y, p3.z);
	glEnd();
	glPopMatrix();


	glPushMatrix();                  //bottom
	glBindTexture(GL_TEXTURE_2D, id);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(p4.x, p4.y, p4.z);

	glTexCoord2f(1, 0);
	glVertex3f(p5.x, p5.y, p5.z);

	glTexCoord2f(1, 1);
	glVertex3f(p1.x, p1.y, p1.z);

	glTexCoord2f(0, 1);
	glVertex3f(p0.x, p0.y, p0.z);
	glEnd();
	glPopMatrix();

	glPushMatrix();                  //top
	glBindTexture(GL_TEXTURE_2D, id);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(p7.x, p7.y, p7.z);

	glTexCoord2f(1, 0);
	glVertex3f(p6.x, p6.y, p6.z);

	glTexCoord2f(1, 1);
	glVertex3f(p2.x, p2.y, p2.z);

	glTexCoord2f(0, 1);
	glVertex3f(p3.x, p3.y, p3.z);
	glEnd();
	glPopMatrix();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);
	cam.setShape(50, 1.3285714285714285714285714285714, 1, 30000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	cam.setModelViewMatrix();

	glRotatef(Angle, 0, 1, 0);

	// Earth
	glPushMatrix();
	glRotatef(earthAngle, 0.0f, 1.0f, 0.0f);
	glTranslatef(earthRadius, 0.0, 0.0);
	changeColour(0.0, 0.007, 0.686, 0.0);
	//glutSolidSphere(20.6, 100, 100);
	drawsphere();
	drawgrass_barn();
	//glPopMatrix();

	//Moon
	glRotatef(5 * earthAngle, 0.0f, 1.0f, 0.0f);
	glTranslatef(50, 0.0, 0.0);
	changeColour(0.7, 0.7, 0.7, 0.0);
	glutSolidSphere(7, 100, 100);
	glPopMatrix();

	MoonPath();
	
	changeColour(0.4, 0.4, 0.4, 1.0);

	Paths();


	// The Sun
	glPushMatrix();
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	changeColour(1.0, 1.0, 0.0, 0.0);
	glutSolidSphere(100, 100, 100);
	//glutWireSphere(200, 30, 30);
	glPopMatrix();

	// Mercury
	glPushMatrix();
	glRotatef(mercuryAngle, 0.0f, 1.0f, 0.0f);
	glTranslatef(mercuryRadius, 0.0, 0.0);
	changeColour(66 / 255.0, 61 / 255.0, 57 / 255.0, 0.0);
	glutSolidSphere(10, 100, 100);
	glPopMatrix();

	// Venus
	glPushMatrix();
	glRotatef(venusAngle, 0.0f, 1.0f, 0.0f);
	glTranslatef(venusRadius, 0.0, 0.0);
	changeColour(140.0 / 255.0, 70.0 / 255.0, 0.0, 0.0);
	glutSolidSphere(25.8, 100, 100);
	glPopMatrix();

	// Mars
	glPushMatrix();
	glRotatef(marsAngle, 0.0f, 1.0f, 0.0f);
	glTranslatef(marsRadius, 0.0, 0.0);
	changeColour(170 / 255.0, 60 / 255.0, 5 / 255.0, 0.0);
	glutSolidSphere(18.4, 100, 100);
	glPopMatrix();

	// Jupitar
	glPushMatrix();
	glRotatef(jupiterAngle, 0.0f, 1.0f, 0.0f);
	glTranslatef(jupiterRadius, 0.0, 0.0);
	glRotatef(angle + angle * 4, 0.0f, 1.0f, 0.0f); /// Rotate in Own axis
	changeColour(53 / 255.0, 107 / 255.0, 112 / 255.0, 0.0);
	glutSolidSphere(64.5, 100, 100);
	//glutWireSphere(64.5, 30, 30);
	glPopMatrix();


	// Saturn
	glPushMatrix();
	glRotatef(saturnAngle, 0.0f, 1.0f, 0.0f);
	glTranslatef(saturnRadius, 0.0, 0.0);
	glRotatef(angle + angle * 4, 0.0f, 1.0f, 0.0f); /// Rotate in Own axis
	changeColour(165 / 255.0, 138 / 255.0, 38 / 255.0, 0.0);
	glutSolidSphere(54, 100, 100);
	glPopMatrix();

	Saturndish();

	// Uranus
	glPushMatrix();
	glRotatef(uranusAngle, 0.0f, 1.0f, 0.0f);
	glTranslatef(uranusRadius, 0.0, 0.0);
	changeColour(53 / 255.0, 198 / 255.0, 198 / 255.0, 0.0);
	glutSolidSphere(22.5, 100, 100);
	glPopMatrix();

	// Neptune
	glPushMatrix();
	glRotatef(neptuneAngle, 0.0f, 1.0f, 0.0f);
	glTranslatef(neptuneRadius, 0.0, 0.0);
	changeColour(5 / 255.0, 5 / 255.0, 186 / 255.0, 0.0);
	glutSolidSphere(24, 100, 100);
	glPopMatrix();


	angle += 0.2f;
	mercuryAngle += 0.409 ;
	venusAngle += 0.534;
	earthAngle += 0.164;
	Angle -= 0.164;
	marsAngle += 0.262;
	jupiterAngle += 0.415;
	saturnAngle += 0.267;
	uranusAngle += 0.093;
	neptuneAngle += 0.126;

	glPushMatrix();										//Asteroid 1
	glTranslatef(st, 0, st2);
	//glTranslatef(-2500, -300, 800);
	drawcube(Point3(-1500, 600, -500), Point3(-1500, 550, -300), Point3(-1550, 700, -350), Point3(-1530, 650, -450), Point3(-1600, 550, -550), Point3(-1650, 500, -350), Point3(-1620, 700, -400), Point3(-1600, 680, -500), 2008);
	glPopMatrix();
	st += 10;
	st2 += 10;

	glPushMatrix();										//Asteroid 2
	glTranslatef(st3, 0, st4);
	glTranslatef(-400, -300, 800);
	drawcube(Point3(-1500, 600, 500), Point3(-1500, 550, 300), Point3(-1550, 700, 350), Point3(-1530, 650, 450), Point3(-1600, 550, 550), Point3(-1650, 500, 350), Point3(-1620, 700, 400), Point3(-1600, 680, 500), 2008);
	glPopMatrix();
	st3 -= 10;
	st4 += 10;

	glPushMatrix();										//Asteroid 3
	glTranslatef(st5, 0, st6);
	//glTranslatef(-2500, -300, 800);
	drawcube(Point3(500, 600, -500), Point3(500, 550, -300), Point3(550, 700, -350), Point3(530, 650, -450), Point3(600, 550, -550), Point3(650, 500, -350), Point3(620, 700, -400), Point3(600, 680, -500), 2008);
	glPopMatrix();
	st5 -= 10;
	st6 -= 10;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);


	glPushMatrix();                  //bottom
	glBindTexture(GL_TEXTURE_2D, 2001);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-9000, -6000, -9000);

	glTexCoord2f(0, 1);
	glVertex3f(-9000, -6000, 9000);

	glTexCoord2f(1, 1);
	glVertex3f(9000, -6000, 9000);

	glTexCoord2f(1, 0);
	glVertex3f(9000, -6000, -9000);
	glEnd();
	glPopMatrix();

	glPushMatrix();              //   top
	glBindTexture(GL_TEXTURE_2D, 2001);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-9000, 6000, 9000);

	glTexCoord2f(0, 1);
	glVertex3f(-9000, 6000, -9000);

	glTexCoord2f(1, 1);
	glVertex3f(9000, 6000, -9000);

	glTexCoord2f(1, 0);
	glVertex3f(9000, 6000, 9000);
	glEnd();
	glPopMatrix();



	glPushMatrix();                 //back
	glBindTexture(GL_TEXTURE_2D, 2001);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-9000, 6000, -9000);

	glTexCoord2f(0, 1);
	glVertex3f(-9000, -6000, -9000);

	glTexCoord2f(1, 1);
	glVertex3f(9000, -6000, -9000);

	glTexCoord2f(1, 0);
	glVertex3f(9000, 6000, -9000);
	glEnd();
	glPopMatrix();

	glPushMatrix();                // front
	glBindTexture(GL_TEXTURE_2D, 2001);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-9000, -6000, 9000);

	glTexCoord2f(0, 1);
	glVertex3f(-9000, 6000, 9000);

	glTexCoord2f(1, 1);
	glVertex3f(9000, 6000, 9000);

	glTexCoord2f(1, 0);
	glVertex3f(9000, -6000, 9000);
	glEnd();
	glPopMatrix();


	glPushMatrix();                //left
	glBindTexture(GL_TEXTURE_2D, 2001);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-9000, 6000, -9000);

	glTexCoord2f(0, 1);
	glVertex3f(-9000, 6000, 9000);

	glTexCoord2f(1, 1);
	glVertex3f(-9000, -6000, 9000);

	glTexCoord2f(1, 0);
	glVertex3f(-9000, -6000, -9000);
	glEnd();
	glPopMatrix();



	glPushMatrix();                //sky right
	glBindTexture(GL_TEXTURE_2D, 2001);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(9000, 6000, 9000);

	glTexCoord2f(0, 1);
	glVertex3f(9000, 6000, -9000);

	glTexCoord2f(1, 1);
	glVertex3f(9000, -6000, -9000);

	glTexCoord2f(1, 0);
	glVertex3f(9000, -6000, 9000);
	glEnd();
	glPopMatrix();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	//if(angle == 360) angle = 0;
	glutSwapBuffers();
}

void maindisplay(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);
	cam.setShape(50, 1.3285714285714285714285714285714, 1, 30000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	cam.setModelViewMatrix();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glPushMatrix();                  //front
	glBindTexture(GL_TEXTURE_2D, 2010);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1500, -14000, -14000);

	glTexCoord2f(1, 0);
	glVertex3f(-1500, 14000, -14000);

	glTexCoord2f(1, 1);
	glVertex3f(-1500, 14000, 14000);

	glTexCoord2f(0, 1);
	glVertex3f(-1500, -14000, 14000);
	glEnd();
	glPopMatrix();

	glPushMatrix();                  //front
	glBindTexture(GL_TEXTURE_2D, 2011);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-900, -10000, 5000);

	glTexCoord2f(0, 1);
	glVertex3f(-900, -9000, 5000);

	glTexCoord2f(1, 1);
	glVertex3f(-900, -9000, -5000);

	glTexCoord2f(1, 0);
	glVertex3f(-900, -10000, -5000);
	glEnd();
	glPopMatrix();


	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	glTranslatef(0, -5000, 0);

	glRotatef(mainangle, 0.5, 2, 0.5);

	drawcube(Point3(1500, -1500, 1500), Point3(-1500, -1500, 1500), Point3(-1500, 1500, 1500), Point3(1500, 1500, 1500), Point3(1500, -1500, -1500), Point3(-1500, -1500, -1500), Point3(-1500, 1500, -1500), Point3(1500, 1500, -1500), 2009);

	mainangle+=5;
	glutSwapBuffers();
}

void Mouse(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		//cam.set(503, 1, 2, 0, 0, 0, 0, 1, 0);
		cam.set(2600, 400, 0, 0, 0, 0, 0, 1, 0);
		glutDisplayFunc(renderScene);
		//glutMouseFunc(mymouse1);
		//glutDisplayFunc(myDisplay3);
		glutPostRedisplay();
	}
}

int old_x = 0, old_y = 0;
void Mouse1(int xx, int yy) {
	if (xx <= 930) {
		if (old_x < xx)
		{
			cam.yaw(-5.0);
		}
		else if (old_x > xx) {
			cam.yaw(5.0);
		}
		old_x = xx;
	}
	//glutPostRedisplay();
}

void keyboard(unsigned char key, int xx, int yy) {
	switch (key)
	{
	//case 'w': cam.slide(0, 0, -1); break; // slide camera forward
	//case 's': cam.slide(0, 0, 1);  break; // slide camera back
	//case 'l': cam.slide(-1, 0, 0); break;
	//case 'r': cam.slide(1, 0, 0);  break;
	//case 'u': cam.slide(0, 1, 0);  break;
	//case 'U': cam.slide(0, -1, 0); break;
	//case 'a': Angle += 1; break;
	//case 'd': Angle -= 1; break;

	case 'w': cam.slide(0, 0, -3); break; // slide camera forward
	case 's': cam.slide(0, 0, 3);  break; // slide camera back
	case 'l': cam.slide(-3, 0, 0); break;
	case 'r': cam.slide(3, 0, 0);  break;
	case 'u': cam.slide(0, 3, 0);  break;
	case 'U': cam.slide(0, -3, 0); break;
	case 'a': Angle += 1; break;
	case 'd': Angle -= 1; break;

	case 'm': cam.roll(-10); break; // roll counter-clockwise
	case 'M': cam.roll(10); break; // roll clockwise
	case 'p': cam.pitch(-10); break;
	case 'P': cam.pitch(10); break; 
	case 'y': cam.yaw(-10); break; // roll counter-clockwise
	case 'Y': cam.yaw(10); break; // roll clockwise
	case 'Q': exit(0);
	default: break;
	}
	glutPostRedisplay();
}

void mySpecialKeys(int key, int x, int y)
{
	switch (key)
	{
		// controls for camera
	case GLUT_KEY_UP:  cam.pitch(-10.0); break; // pitch camera down
	case GLUT_KEY_DOWN: cam.pitch(10.0); break; // pitch camera up	
	case GLUT_KEY_RIGHT: cam.yaw(-10.0); break; // yaw camera left
	case GLUT_KEY_LEFT: cam.yaw(10.0); break;  // yaw camera right
	case GLUT_KEY_F1: exit(0);
	}
	glutPostRedisplay(); // draw it again
}

void timer(int visible){
	glutPostRedisplay();
	glutTimerFunc(60, timer, 1);
}

void init(void) {
	setupMaterials();
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

int main(int argc, char * argv[]) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(930, 700);
	glutCreateWindow("Solar System");
	init();

	glutDisplayFunc(maindisplay);
	glutTimerFunc(100, timer, 1);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(mySpecialKeys);
	glutMouseFunc(Mouse);
	glutPassiveMotionFunc(Mouse1);

	pic[0].readBMPFile("g1.bmp");
	pic[0].setTexture(2001);

	pic[1].readBMPFile("g2.bmp");
	pic[1].setTexture(2002);

	pic[2].readBMPFile("sky1.bmp");
	pic[2].setTexture(2003);

	pic[3].readBMPFile("grass2.bmp");
	pic[3].setTexture(2004);

	pic[4].readBMPFile("water.bmp");
	pic[4].setTexture(2005);

	pic[5].readBMPFile("road.bmp");
	pic[5].setTexture(2006);

	pic[6].readBMPFile("road1.bmp");
	pic[6].setTexture(2007);

	pic[7].readBMPFile("asteroid.bmp");
	pic[7].setTexture(2008);

	pic[8].readBMPFile("RFS.bmp");
	pic[8].setTexture(2009);

	pic[9].readBMPFile("planets.bmp");
	pic[9].setTexture(2010);

	pic[10].readBMPFile("logo1.bmp");
	pic[10].setTexture(2011);

	t = Mesh(10, 7, 7);
	t.InitializeTetrahedron();

	cam.set(22000, 0, 0, 0, 0, 0, 0, 1, 0);

	// enter GLUT event processing cycle
	glutMainLoop();
	return 0;
}