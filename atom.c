#include<stdio.h>
        #include<GL/glut.h>
        #include<stdlib.h>
        #include<time.h>
        #include<string.h>
        #include<math.h>
        #define MAX_LIGHT_POSITION 30.00
        #define LIGHT_ON 1
        #define LIGHT_OFF 0
        #define EXIT_YES 1
        #define EXIT_NO 0
        #define BLACK 0
        #define WHITE 1
        #define RED 2
        #define GREEN 3
        #define BLUE 4
        #define RANDOM 5
        #define NORMAL_SCALE 0
        #define ELECTRONS_SCALE 1
        #define ATOM_SCALE 2
        #define X_ROTATE 0
        #define Y_ROTATE 1
        #define Z_ROTATE 2
        #define ROTATE_STOP 3
        #define Y_AXIS 0
        #define Z_AXIS 1
        #define X_AXIS 2
        #define PARALLEL_VIEW 0
        #define PERSPECTIVE_VIEW 1
        #define ADD_ELECTRON 0
        #define REMOVE_ELECTRON 1
        #define AXES_ON 0
        #define AXES_OFF 1
        #define RINGS_ON 0
        #define RINGS_OFF 1

        float SCALE_FACTOR = 2;

        int n = 5,x,y,z,rot2,tflag = 0,scaleflag = 0,xlight = 2,ylight =
2,zlight = 2,frustum = 0,rotate = 0;
        int lightflag = 1,randomColorFlag = 0,count,axesflag =
0,rotx,roty,menuredrawflag = 0; //Scaleflag 2 for only electrons and 1
for the entire atom
        int w1 = 500,h1 = 500,ringflag = 0;
        time_t t1;

        float rottor[][3] = {{1,0,0}, {0,1,0}, {-1,1,0}, {1,1,0}, {1,0,0},
{0,1,0}, {-1,1,0}, {1,1,0}};
        float torsize[] = {4, 4.5, 5, 5.5, 6, 6.5, 7, 7.5};
        float colors[][3] = {{1,0,0}, {0,1,0}, {0,0,1}, {1,1,0} , {0,1,1},
{0.5,1,0.25}, {1,1,1}, {1,0,0},{0.2,0.2,0.9}, {0.75,0,0}};
        float rot[][3] =
{{0,1,0},{1,0,0},{1,1,0},{-1,1,0},{0,1,0},{1,0,0},{1,1,0},{-1,1,0}};
        //float ele[][3] = {{4,0,0}, {0,4.5,0}, {-5,5,5}, {5.5,5.5,5.5},
{6,0,0}, {0,6.5,0}, {-7,7,7}, {7.5,7.5,7.5}};
        float ele[][3] = {{4,0,0}, {0,4.5,0}, {-2.8868,2.8868,2.8868},
{3.1755,3.1755,3.1755}, {6,0,0}, {0,6.5,0}, {-4.0415,4.0415,4.0415},
{4.3301,4.3301,4.3301}};
        float axisa[] = {0.5,1.0,1.5,2,2.5,3,3.5,4};
        float axis[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
        float col[]= {0.5,0.5,1};
        float viewer[] = {0.0,0.0,5};
        float port[] = {0.0,0.0,0};
        char num[][11] = {{"Electron 1"},{"Electron 2"},{"Electron
3"},{"Electron 4"},{"Electron 5"},{"Electron 6"},{"Electron
7"},{"Electron 8"}};
        GLfloat mat_shininess[] = { 50.0 };
        GLfloat light_position[] = { 30.0, 0.0, 0.0, 0.0 };
        GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat mat_specular2[] = { 0.1, 0.1, 0.1, 0.0 };
        GLfloat lightintensity[]={0.7,0.7,0.7,1.0};

        void myinit();
        void createGLUTMenus2();

        void processRings(int option)
        {
                if(option == RINGS_ON)  ringflag = 1;
                else ringflag = 0;
        }

        void processIncreaseSpeed(int option)
        {
                axisa[option] += 0.5;
        }

        void processDecreaseSpeed(int option)
        {
                if(axisa[option] > 0.5) axisa[option] -= 0.5;
        }

        void processToggleAxes(int option)
        {
                if(option == AXES_ON) axesflag = 1;
                else axesflag = 0;
        }

        void processElectronScale(int option)
        {
                switch(option)
                {
                case 1: SCALE_FACTOR = 0.75;scaleflag = 2;break;
                case 2: SCALE_FACTOR = 2;scaleflag = 2;break;
                case 3: SCALE_FACTOR = 3;scaleflag = 2;break;
                }
                glutPostRedisplay();
        }

        void processAtomScale(int option)
        {
                switch(option)
                {
                case 1: SCALE_FACTOR = 0.75;scaleflag = 1;break;
                case 2: SCALE_FACTOR = 2;scaleflag = 1;break;
                case 3: SCALE_FACTOR = 3;scaleflag = 1;break;
                }
                glutPostRedisplay();
        }

        void processAnimation(int option)
        {
        }

        void redrawmenu()
        {
                createGLUTMenus2();
        }

        void processElectron(int option)
        {
                if(option == ADD_ELECTRON && n<8)       n++;
                else if(option == REMOVE_ELECTRON && n>1) n--;
                menuredrawflag = 1;
        }

        void processView(int option)
        {
                if(option == PARALLEL_VIEW)     
                frustum = 0;
                else
                frustum = 1;
                myinit();
        }

        void processPositionLight(int option)
        {
                switch(option)
                {
                case Y_AXIS:    light_position[0] = 0;light_position[1] =
30.0;light_position[2] = 0;break;
                case Z_AXIS:    light_position[0] = 0;light_position[1] =
0.0;light_position[2] = 30.0;break;
                case X_AXIS:    light_position[0] = 30.0;light_position[1] =
0.0;light_position[2] = 0;break;
                }
        }

        void processRotateLight(int option)
        {
                switch(option)
                {
                case X_ROTATE:  xlight = 2;ylight = 0;zlight = 0;break;
                case Y_ROTATE:  xlight = 0;ylight = 2;zlight = 0;break;
                case Z_ROTATE:  xlight = 0;ylight = 0;zlight = 2;break;
                case ROTATE_STOP:       xlight = 2;ylight = 2;zlight = 2;break;
                }
        }

        void processScaling(int option)
        {
                if(option == NORMAL_SCALE)      scaleflag = 0; SCALE_FACTOR = 2;
        }

        void processMenuLighting(int option)
        {
                if(option == LIGHT_OFF) lightflag = 0;
                else lightflag = 1;
        }

        void processMenuExit(int option)
        {
                if(option == EXIT_YES) exit(0);
        }

        void processBgColor(int option)
        {
                switch(option)
                {
                case BLACK:     glClearColor(0,0,0,0);randomColorFlag=0;break;
                case WHITE:     glClearColor(1,1,1,0);randomColorFlag=0;break;
                case RED:       glClearColor(1,0,0,0);randomColorFlag=0;break;
                case GREEN:     glClearColor(0,1,0,0);randomColorFlag=0;break;
                case BLUE:      glClearColor(0,0,1,0);randomColorFlag=0;break;
                case RANDOM:    randomColorFlag = 1;break;
                }
                glutPostRedisplay();
        }

        void processMainMenu2(int option)
        {

        }

        void createGLUTMenus2()
        {
                int i;
                int menuRotateLight = glutCreateMenu(processRotateLight);
                glutAddMenuEntry("About X axis",X_ROTATE);
                glutAddMenuEntry("About Y axis",Y_ROTATE);
                glutAddMenuEntry("About Z axis",Z_ROTATE);
                glutAddMenuEntry("Stop",ROTATE_STOP);

                int menuPositionLight = glutCreateMenu(processPositionLight);
                glutAddMenuEntry("+Y Axis",Y_AXIS);
                glutAddMenuEntry("+Z Axis",Z_AXIS);
                glutAddMenuEntry("+X Axis",X_AXIS);

                int menuLight = glutCreateMenu(processMenuLighting);
                glutAddMenuEntry("On",LIGHT_ON);
                glutAddMenuEntry("Off",LIGHT_OFF);
                glutAddSubMenu("Rotate",menuRotateLight);
                glutAddSubMenu("Position",menuPositionLight);

                int menuExit = glutCreateMenu(processMenuExit);
                glutAddMenuEntry("Yes",EXIT_YES);
                glutAddMenuEntry("No",EXIT_NO);

                int menuBgColor = glutCreateMenu(processBgColor);
                glutAddMenuEntry("Black",BLACK);
                glutAddMenuEntry("White",WHITE);
                glutAddMenuEntry("Red",RED);
                glutAddMenuEntry("Green",GREEN);
                glutAddMenuEntry("Blue",BLUE);
                glutAddMenuEntry("Random",RANDOM);

                int menuElectronScale = glutCreateMenu(processElectronScale);
                glutAddMenuEntry("X0.75",1);
                glutAddMenuEntry("X2",2);
                glutAddMenuEntry("X3",3);

                int menuAtomScale = glutCreateMenu(processAtomScale);
                glutAddMenuEntry("X0.75",1);
                glutAddMenuEntry("X2",2);
                glutAddMenuEntry("X3",3);

                int menuScale = glutCreateMenu(processScaling);
                glutAddMenuEntry("Normal",NORMAL_SCALE);
                glutAddSubMenu("Electrons",menuElectronScale);
                glutAddSubMenu("Atom",menuAtomScale);

                int menuView = glutCreateMenu(processView);
                glutAddMenuEntry("Parallel",PARALLEL_VIEW);
                glutAddMenuEntry("Perspective",PERSPECTIVE_VIEW);

                int menuElectron = glutCreateMenu(processElectron);
                if(n < 8)
                glutAddMenuEntry("Add",ADD_ELECTRON);
                if(n > 1)
                glutAddMenuEntry("Remove",REMOVE_ELECTRON);

                int menuAnimationIncrease = glutCreateMenu(processIncreaseSpeed);
                for(i = 0;i<n;i++)
                glutAddMenuEntry(num[i],i);

                int menuAnimationDecrease = glutCreateMenu(processDecreaseSpeed);
                for(i = 0;i<n;i++)
                glutAddMenuEntry(num[i],i);

                int menuAnimation = glutCreateMenu(processAnimation);
                glutAddSubMenu("Increase Speed",menuAnimationIncrease);
                glutAddSubMenu("Decrease Speed",menuAnimationDecrease);

                int menuToggleAxes = glutCreateMenu(processToggleAxes);
                glutAddMenuEntry("On",AXES_ON);
                glutAddMenuEntry("Off",AXES_OFF);

                int menuRings = glutCreateMenu(processRings);
                glutAddMenuEntry("On",RINGS_ON);
                glutAddMenuEntry("Off",RINGS_OFF);

                glutCreateMenu(processMainMenu2);
                glutAddSubMenu("Lighting",menuLight);
                glutAddSubMenu("Exit",menuExit);
                glutAddSubMenu("Background Color",menuBgColor);
                glutAddSubMenu("Scaling",menuScale);
                glutAddSubMenu("View",menuView);
                glutAddSubMenu("Electron",menuElectron);
                glutAddSubMenu("Animation",menuAnimation);
                glutAddSubMenu("Axes",menuToggleAxes);
                glutAddSubMenu("Rings",menuRings);
                glutAttachMenu(GLUT_RIGHT_BUTTON);
        }       

        void rotatelight()
        {
                if(xlight % 3 == 0)
                {
                if(light_position[0] > -MAX_LIGHT_POSITION)
                light_position[0] -= 0.2;
                else
                xlight++;
                }
                else if(xlight % 3 == 1)
                {
                if(light_position[0] < 30.00)
                light_position[0] += 0.2;
                else
                xlight--;
                }

                if(ylight % 3 == 0)
                {
                if(light_position[1] > -MAX_LIGHT_POSITION)
                light_position[1] -= 0.2;
                else
                ylight++;
                }
                else if(ylight % 3 == 1)
                {
                if(light_position[1] < MAX_LIGHT_POSITION)
                light_position[1] += 0.2;
                else
                ylight--;
                }

                if(zlight % 3 == 0)
                {
                if(light_position[2] > -MAX_LIGHT_POSITION)
                light_position[2] -= 0.2;
                else
                zlight++;
                }
                else if(zlight % 3 == 1)
                {
                if(light_position[2] < MAX_LIGHT_POSITION)
                light_position[2] += 0.2;
                else
                zlight--;
                }

                glLightfv(GL_LIGHT0, GL_POSITION, light_position);
                glLightfv(GL_LIGHT1, GL_POSITION, light_position);
        }       

        void keyboard(unsigned char key,int x,int y)
        {
                switch(key)
                {
                case 'w':
                case 'W': rotx--;
                break;
                case 's':
                case 'S':       rotx++;
                break;
                case 'a':
                case 'A':       roty--;
                break;
                case 'd':
                case 'D':       roty++;
                break;
                case 'q':
                case 'Q':       if(frustum == 1)
                viewer[2] += 0.5;
                break;
                case 'e':
                case 'E':       if(frustum == 1)
                viewer[2] -= 0.5;
                break; 
                }
        }       

        void BitmapCharacter(char text[])
        {
                int i;
                for(i = 0;i<strlen(text);i++)
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,text[i]);
        }

        void setcol(float colors1[])
        {
                col[0] = colors1[0];
                col[1] = colors1[1];
                col[2] = colors1[2];
        }
        void sphere(float x,float y,float z)
        {
                glPushMatrix();
                glTranslatef(x,y,z);
                glutSolidSphere(1.0,50,50);
                glPopMatrix();
        }

        void electrons(float ele[],int i)
        {
                glColor3f(0.5,0.5,0.5);
                if(ringflag)
                {
                glPushMatrix();
                glRotatef(90,rottor[i][0],rottor[i][1],rottor[i][2]);
                glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular2);
                glutSolidTorus(0.03,torsize[i] + 0.03,10,100);
                glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
                glPopMatrix();
                }
                glColor3f(0,0,1);
                glTranslatef(ele[0],ele[1],ele[2]);
                glutSolidSphere(0.3,50,50);
        }

        void nucleus()
        {
                glColor3f(0,0.5,1);     //((float)(rand()%10000)/10000.0)
                glutSolidSphere(0.75,50,50);
                glColor3fv(colors[8]);
                sphere(-1.5,0,0);
                glColor3fv(colors[9]);
                sphere(1.5,0,0);
                glColor3fv(colors[9]);
                sphere(0,1.5,0);
                glColor3fv(colors[8]);
                sphere(0,-1.5,0);
                glColor3fv(colors[8]);
                sphere(0,0,-1.5);
                glColor3fv(colors[9]);
                sphere(0,0,1.5);

                glColor3fv(colors[9]);
                sphere(2.25,0,0);
                glColor3fv(colors[9]);
                sphere(0,0,2.25);
                glColor3fv(colors[8]);
                sphere(0,0,-2.25);
                glColor3fv(colors[8]);
                sphere(-2.25,0,0);
                glColor3fv(colors[9]);
                sphere(0,2,0);
                glColor3fv(colors[8]);
                sphere(0,-2,0);

                glColor3fv(colors[9]);
                sphere(-1.5,-1.5,0);
                glColor3fv(colors[8]);
                sphere(1.5,1.5,0);
                glColor3fv(colors[8]);
                sphere(-1.5,1.5,0);
                glColor3fv(colors[9]);
                sphere(1.5,-1.5,0);

                glColor3fv(colors[8]);
                sphere(-1.5,0,1.5);
                glColor3fv(colors[9]);
                sphere(1.5,0,1.5);
                glColor3fv(colors[9]);
                sphere(0,1.5,1.5);
                glColor3fv(colors[8]);
                sphere(0,-1.5,1.5);

                glColor3fv(colors[9]);
                sphere(-1.5,0,-1.5);
                glColor3fv(colors[9]);
                sphere(1.5,0,-1.5);
                glColor3fv(colors[8]);
                sphere(0,1.5,-1.5);
                glColor3fv(colors[9]);
                sphere(0,-1.5,-1.5);
        }

        void atom()
        {
                int i;

                if(axesflag)
                {
                glBegin(GL_LINES);
                glColor3f(0,0,1);
                glVertex3f(0,0,-100);
                glVertex3f(0,0,100);
                glColor3f(0,1,0);
                glVertex3f(0,-100,0);
                glVertex3f(0,100,0);
                glColor3f(1,0,0);
                glVertex3f(-100,0,0);
                glVertex3f(100,0,0);
                glEnd();

                glLineWidth(5.0);
                glColor3f(1,0,0);
                glRasterPos3f(3.5,0,0);
                BitmapCharacter("X axis");
                glColor3f(0,1,0);
                glRasterPos3f(0,3.5,0);
                BitmapCharacter("Y axis");
                glColor3f(0,0,1);
                glRasterPos3f(0,0,3.5);
                BitmapCharacter("Z axis");
                }
                glLineWidth(1.0);

                nucleus();

                for(i = 0;i < n;i++)
                {
                glPushMatrix();
                glRotatef((axis[i] += axisa[i]),rot[i][0], rot[i][1], rot[i][2]);
                if(scaleflag == 2)
                glScalef(SCALE_FACTOR,SCALE_FACTOR,SCALE_FACTOR);       
                electrons(ele[i],i);
                glPopMatrix();
                if(axis[i] >= 360) axis[i] -= 360.0;   
                }
        }

        void display()
        {
                if(menuredrawflag)
                {
                menuredrawflag = 0;
                redrawmenu();
                }
                glPushMatrix();
                gluLookAt(viewer[0],viewer[1],viewer[2],port[0],port[1],port[2],0,1,0);
                rotatelight();

                if(((count = count % 100) == 0) && randomColorFlag)
                glClearColor((rand()%100)/100.0,(rand()%100)/100.0,(rand()%100)/100.0,0);

                if(lightflag) glEnable(GL_LIGHTING);
                else glDisable(GL_LIGHTING);

                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                count++;

                glRotatef(roty, 0.0, 1.0, 0.0);
                glRotatef(rotx, 1.0, 0.0, 0.0);
                if(scaleflag == 1)
                glScalef(SCALE_FACTOR, SCALE_FACTOR, SCALE_FACTOR);     
                atom();
                glutSwapBuffers();
                glPopMatrix();
        }

        void reshape(int w,int h)
        {
                w1 = w;
                h1 = h;
                glViewport(0,0,w,h);
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                if(frustum == 0)
                {
                if(w <= h)
                glOrtho(-10,10,-10.0 * (float)h/(float)w,10.0 * (float) h/ (float) w,-30,30);
                else
                glOrtho(-10.0 * (float) w / (float) h, 10.0 * (float) w / (float)
h,-10,10,-30,30);
                }
                else
                {
                if(w <= h)
                glFrustum(-5,5,-5.0 * (float) h / (float) w,5.0 * (float) h /
(float) w,1.0,200.0 * (float) h/ (float) w);
                else
                glFrustum(-5.0 * (float)w / (float) h,5.0 * (float) w / (float)
h,-5.0, 5.0,1.0,200.0 * (float) w/ (float) h);
                }
                glMatrixMode(GL_MODELVIEW);
        }

        void myinit()
        {
                glClearColor(0,0,0,0);
                glEnable(GL_DEPTH_TEST);
                glEnable(GL_NORMALIZE);

                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                if(w1 == 0 && h1 == 0)
                {
                if(frustum == 0)
                glOrtho(-10,10,-10,10,-30,30);
                else
                glFrustum(-5,5,-5,5,1,200);
                }
                else
                {
                if(frustum == 0)
                {
                if(w1 <= h1)
                glOrtho(-10,10,-10.0 * (float)h1/(float)w1,10.0 * (float) h1/
(float) w1,-30,30);
                else
                glOrtho(-10.0 * (float) w1 / (float) h1, 10.0 * (float) w1 / (float)
h1,-10,10,-30,30);
                }
                else
                {
                if(w1 <= h1)
                glFrustum(-5,5,-5.0 * (float) h1 / (float) w1,5.0 * (float) h1 /
(float) w1,1.0,200.0);
                else
                glFrustum(-5.0 * (float)w1 / (float) h1,5.0 * (float) w1 / (float)
h1,-5.0, 5.0,1.0,200.0);
                }
                }
                glMatrixMode(GL_MODELVIEW);     

                glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
         glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
         glShadeModel (GL_SMOOTH);
                glEnable(GL_LIGHT0);
                //glEnable(GL_LIGHT1);
                //glLightfv(GL_LIGHT1,GL_SPECULAR,mat_specular);
                //glLightfv(GL_LIGHT0,GL_SPECULAR,mat_specular);

                glEnable(GL_COLOR_MATERIAL);
        }

        void keyboard2(unsigned char c, int x, int y)
        {
                switch(c)
                {
                case 13:
                myinit();
                glutDisplayFunc(display);
                createGLUTMenus2();
                glutKeyboardFunc(keyboard);
                glutReshapeFunc(reshape);
                glutIdleFunc(display);

                break;
                }
                glutPostRedisplay();
        }

        void processMenuMain1(int option)
        {

        }

        void processMenuNumElectrons(int num)
        {
                n = num;
                glutPostRedisplay();
        }

        void createGLUTMenus1()
        {
                int menu = glutCreateMenu(processMenuNumElectrons);
                glutAddMenuEntry("1",1);
                glutAddMenuEntry("2",2);
                glutAddMenuEntry("3",3);
                glutAddMenuEntry("4",4);
                glutAddMenuEntry("5",5);
                glutAddMenuEntry("6",6);
                glutAddMenuEntry("7",7);
                glutAddMenuEntry("8",8);
                int menuExit = glutCreateMenu(processMenuExit);
                glutAddMenuEntry("Yes",0);
                glutAddMenuEntry("No",1);
                glutCreateMenu(processMenuMain1);
                glutAddSubMenu("Number of Electrons",menu);
                glutAddSubMenu("Exit",menuExit);
                glutAttachMenu(GLUT_RIGHT_BUTTON);
        }

        void strokeString(float x,float y,float sx,float sy,char *string,int width)
        {
                char *c;
                glLineWidth(width);
                glPushMatrix();
                glTranslatef(x,y,0);
                glScalef(sx,sy,0);
                for (c=string; *c != '\0'; c++)
                {
                glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
                }
                glPopMatrix();
        }

        void first()
        {
                glClear(GL_COLOR_BUFFER_BIT);
                glColor3f(255,255,255);
                strokeString(90,850,0.30,0.30,"BANGALORE INSTITUTE OF TECHNOLOGY",4);
                strokeString(100,750,0.3,0.3,"DEPARTMENT OF COMPUTER SCIENCE",2);
                strokeString(300,670,0.3,0.3,"AND ENGINEERING",2);

                glColor3f(255,255,255);
                strokeString(200,500,0.3,0.3,"AN OPENGL MINI PROJECT ON",2);
                strokeString(170,420,0.4,0.4,"SIMULATION OF AN ATOM",6);
                //strokeString(110,220,0.2,0.2,"NUMBER OF ELECTRONS:",3);
                //glColor3f(0,0.5,1);
                //char str[5];
                //sprintf(str, "%d", n);
                //strokeString(450,220,0.2,0.2,str,3);
                //glColor3f(0,0,1);
                strokeString(180,300,0.17,0.17,"SET THE NUMBER OF ELECTRONS USING
THE MENUE",2);
                strokeString(300,350,0.2,0.2,"(PRESS ENTER TO START)",2);
                glColor3f(255,255,255);
                strokeString(650,200,0.15,0.15,"BY:",2);
                glColor3f(255,255,255);
                strokeString(650,165,0.15,0.15,"LIKITHA.K.",2);
                strokeString(650,120,0.15,0.15,"NIHARIKA.",2);
                strokeString(650,30,0.2,0.2,"BHANUSHREE.K.J.",2);
                strokeString(750,165,0.15,0.15,"1BI18CS074",2);
                strokeString(750,120,0.15,0.15,"1BI18CS094",2);
                glColor3f(255,255,255);

                strokeString(650,80,0.15,0.15,"UNDER THE GUIDANCE OF ",2);     
                glutSwapBuffers();
        }

        void initfirst()
        {
                glClearColor(0,0,0,0);
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                glOrtho(0,1000,0,1000,-1,1);
                glMatrixMode(GL_MODELVIEW);
        }

        int main(int argc,char **argv)
        {
                srand((unsigned)time(&t1));
                glutInit(&argc,argv);
                glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
                glutInitWindowSize(500,500);
                glutInitWindowPosition(200,200);
                glutCreateWindow("Atom");
                initfirst();
                glutDisplayFunc(first);
                createGLUTMenus1();
                glutKeyboardFunc(keyboard2);
                glutMainLoop();

                return EXIT_SUCCESS;
        }
