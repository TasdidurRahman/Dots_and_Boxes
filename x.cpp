#include<bits/stdc++.h>
#include<GL/glut.h>

GLfloat ver[60][2] = {
        {-0.90f, 0.75},{-0.70f, 0.75},{-0.50f, 0.75},{-0.30f, 0.75},{-0.10f, 0.75},
        {0.10f, 0.75},{0.30f, 0.75},{0.50f, 0.75},{0.70f, 0.75}, {0.90f, 0.75},

        {-0.90f, 0.45f},{-0.70f, 0.45f},{-0.50f, 0.45f},{-0.30f, 0.45f},{-0.10f, 0.45f},
        {0.10f, 0.45f},{0.30f, 0.45f},{0.50f, 0.45f},{0.70f, 0.45f},{0.90f, 0.45f},

        {-0.90f, 0.15f},{-0.70f, 0.15f}, {-0.50f, 0.15f},{-0.30f, 0.15f},{-0.10f, 0.15f},
        {0.10f, 0.15f},{0.30f, 0.15f},{0.50f, 0.15f}, {0.70f, 0.15f},{0.90f, 0.15f},

        {-0.90f, -0.15f},{-0.70f, -0.15f},{-0.50f, -0.15f}, {-0.30f, -0.15f}, {-0.10f, -0.15f},
        {0.10f, -0.15f},{0.30f, -0.15f},{0.50f, -0.15f},{0.70f, -0.15f},{0.90f, -0.15f},

        {-0.90f, -0.45f},{-0.70f, -0.45f},{-0.50f, -0.45f},{-0.30f, -0.45f},{-0.10f, -0.45f},
        {0.10f, -0.45f},{0.30f, -0.45f},{0.50f, -0.45f}, {0.70f, -0.45f}, {0.90f, -0.45f},

        {-0.90f, -0.75f},{-0.70f, -0.75f}, {-0.50f, -0.75f},{-0.30f, -0.75f}, {-0.10f, -0.75f},
        {0.10f, -0.75f}, {0.30f, -0.75f},{0.50f, -0.75f}, {0.70f, -0.75f}, {0.90f, -0.75f}};

GLfloat colors[8][3] = {{1.0,1.0,1.0},
                        {1.0,0.0,0.0},
                        {0.0,1.0,0.0},
                        {0.0,0.0,1.0},
                        {1.0,0.0,1.0},
                        {1.0,1.0,0.0},
                        {0.0,1.0,1.0},
                        {0.0,0.0,0.0}};

GLfloat Tpos[2][2] = {{-0.50f, 0.90f},
                    {0.5f, 0.90f}};

bool vis[62][62],selected=false;
int cursor=0,turn=0,points[3]={0,0,0};

void drawT(void)
{
    int cl,on,off;
    if(points[1]+points[2]>=5)
        cl = 7, on = 0, off = 1;
    else if(turn==0)
        cl = 4,on = 0,off = 1;
    else
        cl = 5,on = 1,off = 0;
    glPointSize(30.0);
    glBegin(GL_POINTS);
        glColor3fv(colors[cl]);
        glVertex2fv(Tpos[on]);
        glColor3f(0.0,0.0,0.0);
        glVertex2fv(Tpos[off]);
    glEnd();
    glutSwapBuffers();
}

void drawP(int pos,int col)
{
    glPointSize(20.0);
        glBegin(GL_POINTS);
            glColor3fv(colors[col]);
            glVertex2fv(ver[pos]);
        glEnd();
    glutSwapBuffers();
}

void drawL(int p1,int p2,int col)
{
    glLineWidth(8.0);
    glBegin(GL_LINES);
        glColor3fv(colors[col]);
        glVertex2fv(ver[p1]);
        glVertex2fv(ver[p2]);
    glEnd();
    drawP(p1,3);
    drawP(p2,3);
    glutSwapBuffers();
}

void output()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    cursor = 0;
    glPointSize(30.0);
    glBegin(GL_POINTS);
        glColor3f(0.0,0.0,0.0);
        glVertex2fv(Tpos[0]);
        glVertex2fv(Tpos[1]);
        glVertex2fv(ver[cursor]);
    glEnd();
    glutSwapBuffers();


    char p1[] = "Player_1";
    char p2[] = "Player_2";
    char s1[] = "00";
    s1[1]+=points[1]%10,s1[0]+=points[1]/10;
    char s2[] = "00";
    s2[1]+=points[2]%10,s2[0]+=points[2]/10;
    char pw[] = "Congrats_Player_x";
    if(points[1]>points[2])
        pw[16] = '1';
    else if(points[1]<points[2])
        pw[16] = '2';
    int i;
    glColor3fv(colors[4]);
    glRasterPos2f(-0.50, 0.45);
    for (i = 0; i < 8; i++) {
      glutBitmapCharacter(GLUT_BITMAP_9_BY_15, p1[i]);
    }
    glRasterPos2f(-0.50, 0.15);
    for (i = 0; i < 2; i++) {
      glutBitmapCharacter(GLUT_BITMAP_9_BY_15, s1[i]);
    }
    glColor3fv(colors[5]);
    glRasterPos2f(0.30, 0.45);
    for (i = 0; i < 8; i++) {
      glutBitmapCharacter(GLUT_BITMAP_9_BY_15, p2[i]);
    }
    glRasterPos2f(0.30, 0.15);
    for (i = 0; i < 2; i++) {
      glutBitmapCharacter(GLUT_BITMAP_9_BY_15, s2[i]);
    }
    if(pw[16]=='1')
        glColor3fv(colors[4]);
    glRasterPos2f(-0.15, -0.15);
    for (i = 0; i < 17; i++) {
      glutBitmapCharacter(GLUT_BITMAP_9_BY_15, pw[i]);
    }
}

void done_state(int p1,int p2)
{
    drawL(p1,p2,0);
    vis[p1][p2] = true;
    vis[p2][p1] = true;
    int cc = turn+4;
    int r1 = (p1/10);
    int c1 = p1%10;
    int r2 = (p2/10);
    int c2 = p2%10;
    bool cng = 1;
    if(r1==r2)
    {
        if(r1!=0)
        {
            int p3 = p1-10;
            int p4 = p2-10;
            if(vis[p1][p3] && vis[p3][p4] && vis[p4][p2])
                drawL(p1,p4,cc),drawL(p2,p3,cc),cng=0,points[turn+1]++;
        }
        if(r1!=5)
        {
            int p3 = p1+10;
            int p4 = p2+10;
            if(vis[p1][p3] && vis[p3][p4] && vis[p4][p2])
                drawL(p1,p4,cc),drawL(p2,p3,cc),cng=0,points[turn+1]++;
        }
    }
    else
    {
        if(c1!=0)
        {
            int p3 = p1-1;
            int p4 = p2-1;
            if(vis[p1][p3] && vis[p3][p4] && vis[p4][p2])
                drawL(p1,p4,cc),drawL(p2,p3,cc),cng=0,points[turn+1]++;
        }
        if(c1!=9)
        {
            int p3 = p1+1;
            int p4 = p2+1;
            if(vis[p1][p3] && vis[p3][p4] && vis[p4][p2])
                drawL(p1,p4,cc),drawL(p2,p3,cc),cng=0,points[turn+1]++;
        }
    }
    turn^=cng;
    return;
}

void move_state(int val)
{
    cursor = (val+60)%60;
    drawP(cursor,2);
    return;
}

void input_proc(unsigned char key,int x,int y)
{
    if(points[1]+points[2]==45)
        output();

    int prev_cursor = cursor;

    if(!selected)
    {
        if(key=='8')
            move_state(cursor-10);
        else if(key=='2')
            move_state(cursor+10);
        else if(key=='4')
            move_state(cursor-1);
        else if(key=='6')
            move_state(cursor+1);
        else if(key=='s')
        {
            selected = true;
            drawP(cursor,1);
        }
        if(key!='s' && cursor!=prev_cursor)
        drawP(prev_cursor,3);
    }
    else
    {
        int r1 = (cursor/10);
        int c1 = cursor%10;
        if(key=='c')
        {
            selected = false;
            drawP(cursor,2);
        }
        else if(key!='8' && key!='2' && key!='4' && key!='6')
            drawP(cursor,1);
        else
        {
            int new_cursor;
            if(key=='8' && r1!=0)
                new_cursor = cursor-10;
            else if(key=='2' && r1!=5)
                new_cursor = cursor+10;
            else if(key=='4' && c1!=0)
                new_cursor = cursor-1;
            else if(key=='6' && c1!=9)
                new_cursor = cursor+1;

            new_cursor += 60;
            new_cursor %= 60;
            if(!vis[cursor][new_cursor])
            {
                selected = false;
                done_state(cursor,new_cursor);
                drawP(new_cursor,2);
                drawP(cursor,3);
                cursor = new_cursor;
            }
        }
        //if(points[1]+points[2]>=5)drawP(cursor,7),drawP(prev_cursor,7);
    }
    drawT();
    //glutPostRedisplay();s
    return;
}

void parsing_state()
{
    drawT();
    glutKeyboardFunc(input_proc);
}

void drawbase(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    cursor = 0;
    for(int i=0;i<60;i++)
        drawP(i,3);
    drawP(0,2);
    parsing_state();
}

int main(int argc,char** argv)
{

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(400,300);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Dots_and_Boxes");
    glutDisplayFunc(drawbase);
    glutMainLoop();
    return 0;
}

/*
install Glut in ubuntu : sudo apt-get install freeglut3-dev
compile :  g++ x.cpp -o fx -lglut -lGLU -lGL
run : ./fx
*/
