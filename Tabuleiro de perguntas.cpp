#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <gl/glut.h>
#include <math.h>

#define MAX 20


void telaJogo(int t);
void telaTabuleiro();
void corAleatoria(int cont);
void jogarDado();
void position();
void pergunta();

GLfloat win = 20;
GLint view_w, view_h;
int tela = 0, vidas = 3, jogadores, j = 0, dado, botoes, bot, resp, perg = 0;
float r = 1.0, g = 1.0, b = 1.0, botr = 0.26, botg = 0.9, botb = 0.64, botr2 = 0.26, botg2 = 0.9, botb2 = 0.64, botr3 = 0.26, botg3 = 0.9, botb3 = 0.64, botr4 = 0.26, botg4 = 0.9, botb4 = 0.64;
float botrresp[5], botgresp[5], botbresp[5];

typedef struct player{
	int posant, pos;
}player;

player p[4];


typedef struct posicoes{
	float x, y;
}posicoes;

posicoes pos[16];

void Inicializa (void)
{
	srand(time(NULL));

	
	glShadeModel(GL_SMOOTH);
	
	glClearColor(r, g, b, 1.0f);
	glMatrixMode(GL_PROJECTION);
    win=20.0f;
    position();
  //  glEnable(GL_DEPTH_TEST);
  	for(int cont; cont < botoes; cont++){
		botrresp[cont] = 0.26; 
		botgresp[cont] = 0.9; 
		botbresp[cont] = 0.64;
	}
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void AlteraTamanhoJanela(GLsizei w, GLsizei h){ 
    glViewport(0, 0, w, h);
    view_w = w;
    view_h = h;                   

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D (0, win, 0, win);
}

void Teclado(unsigned char key, int x, int y)
{
	if (key == 27)
	exit(0);

	if (key == 32 && tela == 1){
		jogarDado();
		if(p[j].pos >= 15){
			p[j].pos = 15;
			telaJogo(2);
		}else
			telaJogo(5);
	}
	
	if ((key == 112 || key == 80) && tela == 5){
		bot = 0;
		pergunta();
		telaJogo(6);
	}

	if ((key == 13) && tela == 6){
		if(bot == 0){
			if(perg == 0){
				p[j].pos = p[j].posant;
			}if(perg == 1){
				p[j].pos = p[j].posant;
			}
		}
		if(bot == 1){
			if(perg == 0){
				p[j].pos = p[j].posant;
			}if(perg == 1){
				p[j].pos = p[j].posant;	
			}
		}
		if(bot == 2){
			if(perg == 0){
				p[j].pos = p[j].posant;	
			}if(perg == 1){
			}
		}
		if(bot == 3){
			if(perg == 0){
				p[j].pos = p[j].posant;
			}if(perg == 1){
				p[j].pos = p[j].posant;
			}
		}
		if(bot == 4){
			if(perg == 0){
				j++;
			}if(perg == 1){
				p[j].pos = p[j].posant;
			}
		}
		j++;
		if(j >= jogadores)
			j = 0;
		
		telaJogo(1);
			
	}	
	
	glutPostRedisplay();
}


void TeclasEspeciais(int key, int x, int y){
	if(tela == 6){
		if (key == GLUT_KEY_UP){
			if(bot >= 0)
				bot--;
			else
				bot = 0;
		}
		if (key == GLUT_KEY_DOWN){
			if(bot < botoes)
				bot++;
			else
				bot = botoes - 1;
		}
		for(int cont; cont < botoes; cont++){
			botrresp[cont] = 0.26; 
			botgresp[cont] = 0.9; 
			botbresp[cont] = 0.64;
		}
		botrresp[bot] = 0.10;
		botgresp[bot] = 0.76;
		botbresp[bot] = 0.49;
	}
	
	
	glutPostRedisplay();
}


void reiniciarJogo(){
	for(int cont; cont < 4; cont++){
		p[cont].pos = 0;
	}
	j = 0;
}
	
void botoesMouse(int button, int state, int x, int y){
	if(tela == 1){
		if(x >= 18.0 * view_w / win && x <= 19.3 * view_w / win && y >= 0.2 * view_h / win && y < 1.5 * view_h / win)
			telaJogo(3);
	}
	if(tela == 2){
		if(x >= 5.5 * view_w / win && x <= 14.5 * view_w / win && y >= 12.0 * view_h / win && y < 14.0 * view_h / win){
			reiniciarJogo();
			telaJogo(1);
		}
		if(x >= 6.0 * view_w / win && x <= 13.0 * view_w / win && y >= 15.0 * view_h / win && y < 17.0 * view_h / win)
			telaJogo(0);
	}
	if(tela == 0){
		if(x >= 6.0 * view_w / win && x <= 14.0 * view_w / win && y >= 8.0 * view_h / win && y < 10.0 * view_h / win && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && tela == 0){
			telaJogo(4);
		}if(x >= 7.0 * view_w / win && x <= 13.0 * view_w / win && y >= 11.0 * view_h / win && y < 13.0 * view_h / win)
			exit(2);					
	}
	if(tela == 4){
		if(x >= 8.2 * view_w / win && x <= 11.8 * view_w / win && y >= 6.0 * view_h / win && y < 8.0 * view_h / win){
			j = 0;
			jogadores = 0;
			p[0].pos = 0;
			j = 0;
			telaJogo(1); 			
		}
		if(x >= 8.0 * view_w / win && x <= 12.0 * view_w / win && y >= 9.0 * view_h / win && y < 11.0 * view_h / win){
			j = 0;
			jogadores = 1;
			p[0].pos = 0;
			p[1].pos = 0;
			j = 0;						
			telaJogo(1);			
		}
		if(x >= 5.5 * view_w / win && x <= 14.5 * view_w / win && y >= 12.0 * view_h / win && y < 14.0 * view_h / win){
			j = 0;
			jogadores = 2;
			p[0].pos = 0;
			p[1].pos = 0;
			p[3].pos = 0;
			j = 0;			
			telaJogo(1);			
		}
		if(x >= 5.5 * view_w / win && x <= 14.5 * view_w / win && y >= 15.0 * view_h / win && y < 17.0 * view_h / win){
			j = 0;
			jogadores = 3;
			p[0].pos = 0;
			p[1].pos = 0;
			p[3].pos = 0;
			p[4].pos = 0;
			j = 0;			
			telaJogo(1);			
		}	
	}
	if(tela == 3){
		if(x >= 8.2 * view_w / win && x <= 11.8 * view_w / win && y >= 6.0 * view_h / win && y < 8.0 * view_h / win){
			telaJogo(1);			
		}
		if(x >= 8.0 * view_w / win && x <= 12.0 * view_w / win && y >= 9.0 * view_h / win && y < 11.0 * view_h / win){
			telaJogo(0);			
		}		
	}		
	
}

void MoveMouse(int x, int y){
	
    if(tela == 2){
		if(x >= 5.5 * view_w / win && x <= 14.5 * view_w / win && y >= 12.0 * view_h / win && y < 14.0 * view_h / win){
			botr = 0.10;
			botg = 0.76;
			botb = 0.49;
		}else{
			botr = 0.26;
			botg = 0.9;
			botb = 0.64;
		}		
		if(x >= 6.0 * view_w / win && x <= 13.0 * view_w / win && y >= 15.0 * view_h / win && y < 17.0 * view_h / win){
			botr2 = 0.10;
			botg2 = 0.76;
			botb2 = 0.49;
		}else{
			botr2 = 0.26;
			botg2 = 0.9;
			botb2 = 0.64;
		}
	}
    if(tela == 0){
		if(x >= 6.0 * view_w / win && x <= 14.0 * view_w / win && y >= 8.0 * view_h / win && y < 10.0 * view_h / win){
			botr2 = 0.10;
			botg2 = 0.76;
			botb2 = 0.49;
		}else{
			botr2 = 0.26;
			botg2 = 0.9;
			botb2 = 0.64;			
		} 
		if(x >= 7.0 * view_w / win && x <= 13.0 * view_w / win && y >= 11.0 * view_h / win && y < 13.0 * view_h / win){
			botr = 0.10;
			botg = 0.76;
			botb = 0.49;
		}else{
			botr = 0.26;
			botg = 0.9;
			botb = 0.64;
		}
	}
    if(tela == 4){
		if(x >= 8.2 * view_w / win && x <= 11.8 * view_w / win && y >= 6.0 * view_h / win && y < 8.0 * view_h / win){
			botr = 0.10;
			botg = 0.76;
			botb = 0.49;
		}else{
			botr = 0.26;
			botg = 0.9;
			botb = 0.64;			
		} 
		if(x >= 8.0 * view_w / win && x <= 12.0 * view_w / win && y >= 9.0 * view_h / win && y < 11.0 * view_h / win){
			botr2 = 0.10;
			botg2 = 0.76;
			botb2 = 0.49;
		}else{
			botr2 = 0.26;
			botg2 = 0.9;
			botb2 = 0.64;
		}
		if(x >= 5.5 * view_w / win && x <= 14.5 * view_w / win && y >= 12.0 * view_h / win && y < 14.0 * view_h / win){
			botr3 = 0.10;
			botg3 = 0.76;
			botb3 = 0.49;
		}else{
			botr3 = 0.26;
			botg3 = 0.9;
			botb3 = 0.64;
		}
		if(x >= 5.5 * view_w / win && x <= 14.5 * view_w / win && y >= 15.0 * view_h / win && y < 17.0 * view_h / win){
			botr4 = 0.10;
			botg4 = 0.76;
			botb4 = 0.49;
		}else{
			botr4 = 0.26;
			botg4 = 0.9;
			botb4 = 0.64;
		}				
	}
    if(tela == 3){
		if(x >= 8.2 * view_w / win && x <= 11.8 * view_w / win && y >= 6.0 * view_h / win && y < 8.0 * view_h / win){
			botr = 0.10;
			botg = 0.76;
			botb = 0.49;
		}else{
			botr = 0.26;
			botg = 0.9;
			botb = 0.64;			
		} 
		if(x >= 8.0 * view_w / win && x <= 12.0 * view_w / win && y >= 9.0 * view_h / win && y < 11.0 * view_h / win){
			botr2 = 0.10;
			botg2 = 0.76;
			botb2 = 0.49;
		}else{
			botr2 = 0.26;
			botg2 = 0.9;
			botb2 = 0.64;
		}				
	}
	glutPostRedisplay();			
}

void desenharTexto(void *font, char *string){
	while(*string)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,*string++); 
}

void DesenhaTextoStroke(void *font, char *string){  
	while(*string)
		glutStrokeCharacter(GLUT_STROKE_ROMAN,*string++); 
}


void jogarDado(){
	dado = rand() % 6 + 1;
	
	p[j].posant = p[j].pos;
	p[j].pos += dado;
	
	if(	p[j].pos >= 15){
		telaJogo(2);
	}else
		telaTabuleiro();
	
}

void pergunta(){
	perg++;
	if(perg > 1)
		perg = 0;
}


void position(){
	pos[0].x = 4.0;
	pos[0].y = 17.5;
	pos[1].x = 7.5;
	pos[1].y = 17.4;
	pos[2].x = 11.1;
	pos[2].y = 17.4;
	pos[3].x = 14.5;
	pos[3].y = 17.4;
	pos[4].x = 16.5;
	pos[4].y = 15.4;
	pos[5].x = 14.5;
	pos[5].y = 13.2;
	pos[6].x = 11.0;
	pos[6].y = 13.2;
	pos[7].x = 7.5;
	pos[7].y = 13.2;
	pos[8].x = 4.0;
	pos[8].y = 13.2;
	pos[9].x = 2.5;
	pos[9].y = 11.2;
	pos[10].x = 2.5;
	pos[10].y = 8.8;
	pos[11].x = 2.5;
	pos[11].y = 6.4;
	pos[12].x = 2.5;
	pos[12].y = 4.0;
	pos[13].x = 6.0;
	pos[13].y = 4.0;
	pos[14].x = 9.5;
	pos[14].y = 4.0;
	pos[15].x = 14.0;
	pos[15].y = 4.1;			
			
}

void telaInicio(){
	reiniciarJogo();
	
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);	
	
	glColor3f(0.4,0.34,0.41);
	glPushMatrix();	
	glTranslatef(5.7,18,0);
	glScalef(0.015, 0.015, 0.015);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"Tabuleiro");
	glPopMatrix();
	
	glColor3f(0.4,0.34,0.41);
	glPushMatrix();	
	glTranslatef(8.7,16,0);
	glScalef(0.015, 0.015, 0.015);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"de");
	glPopMatrix();
	
	glColor3f(0.4,0.34,0.41);
	glPushMatrix();	
	glTranslatef(5.2,14,0);
	glScalef(0.015, 0.015, 0.015);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"Perguntas");	
	glPopMatrix();		

	glBegin(GL_QUADS);
		glColor3f(botr2,botg2,botb2);
		glVertex3f(6.0, 10.0, 0);
		glVertex3f(14.0, 10.0, 0);
		glVertex3f(14.0, 12.0, 0);
		glVertex3f(6.0, 12.0, 0);
	glEnd();	
	
	glColor3f(1,1,1);
	glPushMatrix();	
	glTranslatef(8.3,10.5,0);
	glScalef(0.01, 0.01, 0.01);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"Iniciar");
	glPopMatrix();
		
	glBegin(GL_QUADS);
		glColor3f(botr,botg,botb);
		glVertex3f(7.0, 7.0, 0);
		glVertex3f(13.0, 7.0, 0);
		glVertex3f(13.0, 9.0, 0);
		glVertex3f(7.0, 9.0, 0);
	glEnd();
	
	glFlush();
		
	glColor3f(1,1,1);
	glPushMatrix();	
	glTranslatef(8.7,7.5,0);
	glScalef(0.01, 0.01, 0.01);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"Sair");
	glPopMatrix();

	glutSwapBuffers();
}

void telaJogadores(){

	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f(0.4,0,0.22);
	glPushMatrix();	
	glTranslatef(7,17,0);
	glScalef(0.01, 0.01, 0.01);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"Jogadores");
	glPopMatrix();

	
	glBegin(GL_QUADS);
		glColor3f(botr,botg,botb);
		glVertex3f(8.2, 12, 0);
		glVertex3f(11.8, 12, 0);
		glVertex3f(11.8, 14, 0);
		glVertex3f(8.2, 14, 0);		
	glEnd();
	
	glColor3f(1.0,1.0,1.0);
	glPushMatrix();	
	glTranslatef(9.3,12.5,0);
	glScalef(0.008, 0.008, 0.008);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"UM");
	glPopMatrix();	
	
	glBegin(GL_QUADS);
		glColor3f(botr2,botg2,botb2);
		glVertex3f(8, 11, 0);
		glVertex3f(12, 11, 0);
		glVertex3f(12, 9, 0);
		glVertex3f(8, 9, 0);		
	glEnd();
	
	glColor3f(1.0,1.0,1.0);
	glPushMatrix();	
	glTranslatef(8.8,9.5,0);
	glScalef(0.008, 0.008, 0.008);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"DOIS");
	glPopMatrix();
	
	glBegin(GL_QUADS);
		glColor3f(botr3,botg3,botb3);
		glVertex3f(8, 8, 0);
		glVertex3f(12, 8, 0);
		glVertex3f(12, 6, 0);
		glVertex3f(8, 6, 0);		
	glEnd();
	
	glColor3f(1.0,1.0,1.0);
	glPushMatrix();	
	glTranslatef(8.8,6.5,0);
	glScalef(0.008, 0.008, 0.008);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"TRES");
	glPopMatrix();
	
	glBegin(GL_QUADS);
		glColor3f(botr4,botg4,botb4);
		glVertex3f(7.5, 5, 0);
		glVertex3f(12.5, 5, 0);
		glVertex3f(12.5, 3, 0);
		glVertex3f(7.5, 3, 0);		
	glEnd();
	
	glColor3f(1.0,1.0,1.0);
	glPushMatrix();	
	glTranslatef(8.0,3.5,0);
	glScalef(0.008, 0.008, 0.008);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"QUATRO");
	glPopMatrix();			
				
									
	
	glFlush();
}


void telaVitoria(){
	
	glClear(GL_COLOR_BUFFER_BIT);
	
	telaTabuleiro();
	glBegin(GL_QUADS);
		glColor4f(1.0, 1.0, 1.0, 0.6);
		glVertex3f(0.0, 0.0, 0);
		glVertex3f(20.0, 0.0, 0);
		glVertex3f(20.0, 20.0, 0);
		glVertex3f(0.0, 20.0, 0);		
	glEnd();
	
	glColor3f(0.05,0.05,0.5);
	glPushMatrix();	
	glTranslatef(4.5,15.0,0);
	glScalef(0.01, 0.01, 0.01);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"Jogador");
	glPopMatrix();
	
	if(j == 0){
		glColor3f(0.05,0.05,0.5);
		glPushMatrix();	
		glTranslatef(10.0,15.0,0);
		glScalef(0.01, 0.01, 0.01);
		glLineWidth(5); 
		DesenhaTextoStroke(GLUT_STROKE_ROMAN,"1");
		glPopMatrix();
	}else if(j == 1){
		glColor3f(0.05,0.05,0.5);
		glPushMatrix();	
		glTranslatef(10.0,15.0,0);
		glScalef(0.01, 0.01, 0.01);
		glLineWidth(5); 
		DesenhaTextoStroke(GLUT_STROKE_ROMAN,"2");
		glPopMatrix();		
	}else if(j == 2){
		glColor3f(0.05,0.05,0.5);
		glPushMatrix();	
		glTranslatef(10.0,15.0,0);
		glScalef(0.01, 0.01, 0.01);
		glLineWidth(5); 
		DesenhaTextoStroke(GLUT_STROKE_ROMAN,"3");
		glPopMatrix();		
	}else if(j == 3){
		glColor3f(0.05,0.05,0.5);
		glPushMatrix();	
		glTranslatef(10.0,15.0,0);
		glScalef(0.01, 0.01, 0.01);
		glLineWidth(5); 
		DesenhaTextoStroke(GLUT_STROKE_ROMAN,"4");
		glPopMatrix();	
	}
	
	glColor3f(0.05,0.05,0.5);
	glPushMatrix();	
	glTranslatef(11.5,15.0,0);
	glScalef(0.01, 0.01, 0.01);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"venceu!");
	glPopMatrix();
		
	glBegin(GL_QUADS);
		glColor3f(botr,botg,botb);
		glVertex3f(5.5, 6.0, 0);
		glVertex3f(14.5, 6.0, 0);
		glVertex3f(14.5, 8.0, 0);
		glVertex3f(5.5, 8.0, 0);
	glEnd();
		
	glColor3f(1,1,1);
	glPushMatrix();	
	glTranslatef(6,6.8,0);
	glScalef(0.0075, 0.0075, 0.0075);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"Jogar novamente");
	glPopMatrix();
	
	
	glBegin(GL_QUADS);
		glColor3f(botr2,botg2,botb2);
		glVertex3f(6.0, 3.0, 0);
		glVertex3f(13.5, 3.0, 0);
		glVertex3f(13.5, 5.0, 0);
		glVertex3f(6.0, 5.0, 0);
	glEnd();
	
	glFlush();
		
	glColor3f(1,1,1);
	glPushMatrix();	
	glTranslatef(6.5,3.8,0);
	glScalef(0.0075, 0.0075, 0.0075);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"Menu principal");
	glPopMatrix();	

	glutSwapBuffers();	
	
}


void telaTabuleiro(){
	
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.208f, 0.286f, 0.369f, 1.0f);
	
	glEnable(GL_LINE_SMOOTH);
	glLineWidth (0.0001);
	float aux = 0;
	for(int cont = 0; cont < 40; cont++){
		glBegin(GL_LINE_STRIP);
			glColor3f(0.973, 0.973, 0.973);
			glVertex3f(0.0, aux, 0);
			glVertex3f(20.0, aux, 0);
		glEnd();
		glBegin(GL_LINE_STRIP);
			glColor3f(0.973, 0.973, 0.973);
			glVertex3f(aux, 0, 0);
			glVertex3f(aux, 20.0, 0);
		glEnd();
		aux += 1;				
	}
	glClearColor(0.208f, 0.286f, 0.369f, 1.0f);
	
	//linhas
	glLineWidth (10.0);
	glBegin(GL_LINE_STRIP);
		glColor3f(0.973, 0.973, 0.973);
		glLineWidth (1.0);
		glVertex3f(4.5, 17.0, 0);
		glVertex3f(16.0, 17.0, 0);
		glVertex3f(16.0, 12.8, 0);	
		glVertex3f(2.0, 12.8, 0);	
		glVertex3f(2.0, 3.5, 0);	
		glVertex3f(14.0, 3.5, 0);								
	glEnd();
	
	//Inicio
	glBegin(GL_QUADS);
		glColor3f(0.08, 0.659, 0.659);
		glVertex3f(1.0, 16.0, 0);
		glVertex3f(4.5, 16.0, 0);
		glVertex3f(4.5, 18.0, 0);
		glVertex3f(1.0, 18.0, 0);		
	glEnd();

	glColor3f(0.961,0.961,0.97);
	glPushMatrix();	
	glTranslatef(1.6,16.5,0);
	glScalef(0.0075, 0.0075, 0.0075);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"Inicio");
	glPopMatrix();
	
	//Percurso
	glBegin(GL_QUADS);
		glColor3f(0.941, 0.075, 0.302);
		glVertex3f(6.0, 16.2, 0);
		glVertex3f(8.0, 16.2, 0);
		glVertex3f(8.0, 17.8, 0);
		glVertex3f(6.0, 17.8, 0);		
	glEnd();	
	
	glBegin(GL_QUADS);
		glColor3f(0.322, 0.871, 0.592);
		glVertex3f(9.5, 16.2, 0);
		glVertex3f(11.5, 16.2, 0);
		glVertex3f(11.5, 17.8, 0);
		glVertex3f(9.5, 17.8, 0);		
	glEnd();
	
	glBegin(GL_QUADS);
		glColor3f(1.0, 0.827, 0.412);
		glVertex3f(13.0, 16.2, 0);
		glVertex3f(15.0, 16.2, 0);
		glVertex3f(15.0, 17.8, 0);
		glVertex3f(13.0, 17.8, 0);		
	glEnd();
		
	glBegin(GL_QUADS);
		glColor3f(0.322, 0.871, 0.592);
		glVertex3f(15.0, 14.2, 0);
		glVertex3f(17.0, 14.2, 0);
		glVertex3f(17.0, 15.8, 0);
		glVertex3f(15.0, 15.8, 0);		
	glEnd();
	
	glBegin(GL_QUADS);
		glColor3f(0.941, 0.075, 0.302);
		glVertex3f(13.0, 12.0, 0);
		glVertex3f(15.0, 12.0, 0);
		glVertex3f(15.0, 13.6, 0);
		glVertex3f(13.0, 13.6, 0);		
	glEnd();
	
	glBegin(GL_QUADS);
		glColor3f(1.0, 0.827, 0.412);
		glVertex3f(9.5, 12.0, 0);
		glVertex3f(11.5, 12.0, 0);
		glVertex3f(11.5, 13.6, 0);
		glVertex3f(9.5, 13.6, 0);		
	glEnd();
	
	glBegin(GL_QUADS);
		glColor3f(0.941, 0.075, 0.302);
		glVertex3f(6.0, 12.0, 0);
		glVertex3f(8.0, 12.0, 0);
		glVertex3f(8.0, 13.6, 0);
		glVertex3f(6.0, 13.6, 0);		
	glEnd();

	glBegin(GL_QUADS);
		glColor3f(1.0, 0.827, 0.412);
		glVertex3f(2.5, 12.0, 0);
		glVertex3f(4.5, 12.0, 0);
		glVertex3f(4.5, 13.6, 0);
		glVertex3f(2.5, 13.6, 0);		
	glEnd();
	
	glBegin(GL_QUADS);
		glColor3f(0.322, 0.871, 0.592);
		glVertex3f(1.0, 10.0, 0);
		glVertex3f(3.0, 10.0, 0);
		glVertex3f(3.0, 11.6, 0);
		glVertex3f(1.0, 11.6, 0);		
	glEnd();	
	
	glBegin(GL_QUADS);
		glColor3f(0.941, 0.075, 0.302);
		glVertex3f(1.0, 7.6, 0);
		glVertex3f(3.0, 7.6, 0);
		glVertex3f(3.0, 9.2, 0);
		glVertex3f(1.0, 9.2, 0);		
	glEnd();		
				
	glBegin(GL_QUADS);
		glColor3f(0.322, 0.871, 0.592);
		glVertex3f(1.0, 6.8, 0);
		glVertex3f(3.0, 6.8, 0);
		glVertex3f(3.0, 5.2, 0);
		glVertex3f(1.0, 5.2, 0);		
	glEnd();
	
	glBegin(GL_QUADS);
		glColor3f(1.0, 0.827, 0.412);
		glVertex3f(1.0, 2.8, 0);
		glVertex3f(3.0, 2.8, 0);
		glVertex3f(3.0, 4.4, 0);
		glVertex3f(1.0, 4.4, 0);		
	glEnd();
	
	glBegin(GL_QUADS);
		glColor3f(0.941, 0.075, 0.302);
		glVertex3f(4.5, 2.8, 0);
		glVertex3f(6.5, 2.8, 0);
		glVertex3f(6.5, 4.4, 0);
		glVertex3f(4.5, 4.4, 0);		
	glEnd();	
	
	glBegin(GL_QUADS);
		glColor3f(0.322, 0.871, 0.592);
		glVertex3f(8.0, 2.8, 0);
		glVertex3f(10.0, 2.8, 0);
		glVertex3f(10.0, 4.4, 0);
		glVertex3f(8.0, 4.4, 0);		
	glEnd();				
											
	
	//Chegada
	glBegin(GL_QUADS);
		glColor3f(0.08, 0.659, 0.659);
		glVertex3f(17.0, 2.5, 0);
		glVertex3f(11.5, 2.5, 0);
		glVertex3f(11.5, 4.5, 0);
		glVertex3f(17.0, 4.5, 0);		
	glEnd();

	glColor3f(0.961,0.961,0.97);
	glPushMatrix();	
	glTranslatef(12.3,3,0);
	glScalef(0.0075, 0.0075, 0.0075);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"Chegada");
	glPopMatrix();	
	
	glColor3f(0.961,0.961,0.97);
	glPushMatrix();	
	glTranslatef(6.5,8.5,0);
	glScalef(0.0075, 0.0075, 0.0075);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"Espaco para jogar dado");
	glPopMatrix();	
		
	
	//Pause
	glBegin(GL_QUADS);
		glColor3f(0.97f, 0.99f, 0.98f);
		glVertex3f(18.0, 18.5, 0);
		glVertex3f(18.5, 18.5, 0);
		glVertex3f(18.5, 19.8, 0);
		glVertex3f(18.0, 19.8, 0);
	glEnd();
	
	glBegin(GL_QUADS);
		glColor3f(0.97f, 0.99f, 0.98f);
		glVertex3f(18.8, 18.5, 0);
		glVertex3f(19.3, 18.5, 0);
		glVertex3f(19.3, 19.8, 0);
		glVertex3f(18.8, 19.8, 0);
	glEnd();
	
	//Borda esquerda
	glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0, 0.0, 0);
		glVertex3f(0.2, 0.0, 0);
		glVertex3f(0.2, 20.0, 0);
		glVertex3f(0.0, 20.0, 0);
	glEnd();

	//Borda direita	
	glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(20.0, 0.0, 0);
		glVertex3f(19.8, 0.0, 0);
		glVertex3f(19.8, 20.0, 0);
		glVertex3f(20.0, 20.0, 0);
	glEnd();
	
	if(p[j].pos > 15){
		p[j].pos = 15;
	}
	
	if(jogadores >= 0){
		glBegin(GL_QUADS);
			glColor3f(0.137f, 0.016f, 0.267f);
			glVertex3f(pos[p[0].pos].x - 0.3, pos[p[0].pos].y - 0.3, 0);
			glVertex3f(pos[p[0].pos].x + 0.3, pos[p[0].pos].y - 0.3, 0);
			glVertex3f(pos[p[0].pos].x + 0.3, pos[p[0].pos].y + 0.3, 0);
			glVertex3f(pos[p[0].pos].x - 0.3, pos[p[0].pos].y + 0.3, 0);
		glEnd();
		
		glColor3f(0.961,0.961,0.97);
		glPushMatrix();	
		glTranslatef(pos[p[0].pos].x - 0.08, pos[p[0].pos].y - 0.08, 0.f);
		glScalef(0.003, 0.003, 0.003);
		glLineWidth(3); 
		DesenhaTextoStroke(GLUT_STROKE_ROMAN,"1");
		glPopMatrix();
	}
	if(jogadores >= 1){
		glBegin(GL_QUADS);
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(pos[p[1].pos].x - 0.3, pos[p[1].pos].y - 0.3 - 0.8, 0);
			glVertex3f(pos[p[1].pos].x + 0.3, pos[p[1].pos].y - 0.3 - 0.8, 0);
			glVertex3f(pos[p[1].pos].x + 0.3, pos[p[1].pos].y + 0.3 - 0.8, 0);
			glVertex3f(pos[p[1].pos].x - 0.3, pos[p[1].pos].y + 0.3 - 0.8, 0);
		glEnd();
		
		glColor3f(0.961,0.961,0.97);
		glPushMatrix();	
		glTranslatef(pos[p[1].pos].x - 0.08, pos[p[1].pos].y - 0.08 - 0.8, 0.f);
		glScalef(0.003, 0.003, 0.003);
		glLineWidth(3); 
		DesenhaTextoStroke(GLUT_STROKE_ROMAN,"2");
		glPopMatrix();					
	}
	if(jogadores >= 2){
		glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(pos[p[2].pos].x - 0.3 - 1.0, pos[p[2].pos].y - 0.3, 0);
			glVertex3f(pos[p[2].pos].x + 0.3 - 1.0, pos[p[2].pos].y - 0.3, 0);
			glVertex3f(pos[p[2].pos].x + 0.3 - 1.0, pos[p[2].pos].y + 0.3, 0);
			glVertex3f(pos[p[2].pos].x - 0.3 - 1.0, pos[p[2].pos].y + 0.3, 0);
		glEnd();
		
		glColor3f(0.961,0.961,0.97);
		glPushMatrix();	
		glTranslatef(pos[p[2].pos].x - 0.08 - 1, pos[p[2].pos].y - 0.08, 0.f);
		glScalef(0.003, 0.003, 0.003);
		glLineWidth(3); 
		DesenhaTextoStroke(GLUT_STROKE_ROMAN,"3");
		glPopMatrix();						
	}
	if(jogadores >= 3){
		glBegin(GL_QUADS);
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(pos[p[3].pos].x - 0.3 - 1.0, pos[p[3].pos].y - 0.3 - 0.8, 0);
			glVertex3f(pos[p[3].pos].x + 0.3 - 1.0, pos[p[3].pos].y - 0.3 - 0.8, 0);
			glVertex3f(pos[p[3].pos].x + 0.3 - 1.0, pos[p[3].pos].y + 0.3 - 0.8, 0);
			glVertex3f(pos[p[3].pos].x - 0.3 - 1.0, pos[p[3].pos].y + 0.3 - 0.8, 0);
		glEnd();	
		
		glColor3f(0.961,0.961,0.97);
		glPushMatrix();	
		glTranslatef(pos[p[3].pos].x - 0.08 -1.0, pos[p[3].pos].y - 0.08 - 0.8, 0.f);
		glScalef(0.003, 0.003, 0.003);
		glLineWidth(3); 
		DesenhaTextoStroke(GLUT_STROKE_ROMAN,"4");
		glPopMatrix();			
	}
	
	glColor3f(0.961,0.961,0.97);
	glPushMatrix();	
	glTranslatef(7.0,19.0,0);
	glScalef(0.0075, 0.0075, 0.0075);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"Jogador");
	glPopMatrix();
	
	if(j == 0){
		glColor3f(0.961,0.961,0.97);
		glPushMatrix();	
		glTranslatef(11.0,19.0,0);
		glScalef(0.0075, 0.0075, 0.0075);
		glLineWidth(5); 
		DesenhaTextoStroke(GLUT_STROKE_ROMAN,"1");
		glPopMatrix();
	}else if(j == 1){
		glColor3f(0.961,0.961,0.97);
		glPushMatrix();	
		glTranslatef(11.0,19.0,0);
		glScalef(0.0075, 0.0075, 0.0075);
		glLineWidth(5); 
		DesenhaTextoStroke(GLUT_STROKE_ROMAN,"2");
		glPopMatrix();		
	}else if(j == 2){
		glColor3f(0.961,0.961,0.97);
		glPushMatrix();	
		glTranslatef(11.0,19.0,0);
		glScalef(0.0075, 0.0075, 0.0075);
		glLineWidth(5); 
		DesenhaTextoStroke(GLUT_STROKE_ROMAN,"3");
		glPopMatrix();		
	}else if(j == 3){
		glColor3f(0.961,0.961,0.97);
		glPushMatrix();	
		glTranslatef(11.0,19.0,0);
		glScalef(0.0075, 0.0075, 0.0075);
		glLineWidth(5); 
		DesenhaTextoStroke(GLUT_STROKE_ROMAN,"4");
		glPopMatrix();	
	}
	
	glFlush();
	glutSwapBuffers();
}


void telaDado(){
	
	glBegin(GL_QUADS);
		glColor3f(0.08, 0.659, 0.659);
		glVertex3f(11.3, 5.4, 0);
		glVertex3f(13.3, 5.4, 0);
		glVertex3f(13.3, 7.4, 0);
		glVertex3f(11.3, 7.4, 0);		
	glEnd();
	
	if(dado == 1){
		glColor3f(0.961,0.961,0.97);
		glPushMatrix();	
		glTranslatef(12,6,0);
		glScalef(0.0075, 0.0075, 0.0075);
		glLineWidth(5); 
		DesenhaTextoStroke(GLUT_STROKE_ROMAN,"1");
		glPopMatrix();
	}else if(dado == 2){
		glColor3f(0.961,0.961,0.97);
		glPushMatrix();	
		glTranslatef(12,6,0);
		glScalef(0.0075, 0.0075, 0.0075);
		glLineWidth(5); 
		DesenhaTextoStroke(GLUT_STROKE_ROMAN,"2");
		glPopMatrix();		
	}else if(dado == 3){
		glColor3f(0.961,0.961,0.97);
		glPushMatrix();	
		glTranslatef(12,6,0);
		glScalef(0.0075, 0.0075, 0.0075);
		glLineWidth(5); 
		DesenhaTextoStroke(GLUT_STROKE_ROMAN,"3");
		glPopMatrix();		
	}else if(dado == 4){
		glColor3f(0.961,0.961,0.97);
		glPushMatrix();	
		glTranslatef(12,6,0);
		glScalef(0.0075, 0.0075, 0.0075);
		glLineWidth(5); 
		DesenhaTextoStroke(GLUT_STROKE_ROMAN,"4");
		glPopMatrix();		
	}else if(dado == 5){
		glColor3f(0.961,0.961,0.97);
		glPushMatrix();	
		glTranslatef(12,6,0);
		glScalef(0.0075, 0.0075, 0.0075);
		glLineWidth(5); 
		DesenhaTextoStroke(GLUT_STROKE_ROMAN,"5");
		glPopMatrix();	
	}else if(dado == 6){
		glColor3f(0.961,0.961,0.97);
		glPushMatrix();	
		glTranslatef(12,6,0);
		glScalef(0.0075, 0.0075, 0.0075);
		glLineWidth(5); 
		DesenhaTextoStroke(GLUT_STROKE_ROMAN,"6");
		glPopMatrix();		
	}
	
	glColor3f(0.922,0.302,0.333);
	glPushMatrix();	
	glTranslatef(4.5,10.5,0);
	glScalef(0.0075, 0.0075, 0.0075);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"[P] Responder Pergunta");
	glPopMatrix();	
	
	glFlush();
}

void telaPause(){

	telaTabuleiro();
	glBegin(GL_QUADS);
		glColor4f(1.0, 1.0, 1.0, 0.2);
		glVertex3f(0.0, 0.0, 0);
		glVertex3f(20.0, 0.0, 0);
		glVertex3f(20.0, 20.0, 0);
		glVertex3f(0.0, 20.0, 0);		
	glEnd();	
	
	glBegin(GL_QUADS);
		glColor3f(botr,botg,botb);
		glVertex3f(8.2, 12, 0);
		glVertex3f(11.8, 12, 0);
		glVertex3f(11.8, 14, 0);
		glVertex3f(8.2, 14, 0);		
	glEnd();
	
	glColor3f(1.0,1.0,1.0);
	glPushMatrix();	
	glTranslatef(8.7,12.5,0);
	glScalef(0.008, 0.008, 0.008);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"Voltar");
	glPopMatrix();	
	
	glBegin(GL_QUADS);
		glColor3f(botr2,botg2,botb2);
		glVertex3f(8, 11, 0);
		glVertex3f(12, 11, 0);
		glVertex3f(12, 9, 0);
		glVertex3f(8, 9, 0);		
	glEnd();
	
	glColor3f(1.0,1.0,1.0);
	glPushMatrix();	
	glTranslatef(8.8,9.5,0);
	glScalef(0.008, 0.008, 0.008);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"Menu");
	glPopMatrix();
	
	glFlush();
	//glutPostRedisplay();
	//glutSwapBuffers();
}

void telaPerguntas(){

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);	
	
	if(perg == 0){
//PERGUNTA	
//PERGUNTA FÍSICA 1
	glColor3f(0,0,0);
	glPushMatrix();	
	glTranslatef(1.0,19.4,0);
	glScalef(0.004, 0.004, 0.004);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"15 (FUVEST 2014 - Primeira Fase) Para passar de");
	glPopMatrix();
	
	glColor3f(0,0,0);
	glPushMatrix();	
	glTranslatef(1.0,18.5,0);
	glScalef(0.004, 0.004, 0.004);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"uma margem a outra de um rio, uma pessoa se");
	glPopMatrix();
	
	glColor3f(0,0,0);
	glPushMatrix();	
	glTranslatef(1.0,17.5,0);
	glScalef(0.004, 0.004, 0.004);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"uma margem a outra de um rio, uma pessoa se");
	glPopMatrix();
	
	glColor3f(0,0,0);
	glPushMatrix();	
	glTranslatef(1.0,16.5,0);
	glScalef(0.004, 0.004, 0.004);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"Pendura na extremidade de um cipó esticado,");
	glPopMatrix();
	
	glColor3f(0,0,0);
	glPushMatrix();	
	glTranslatef(1.0,15.5,0);
	glScalef(0.004, 0.004, 0.004);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"formando um ângulo de 30° com a vertical, e inicia,");
	glPopMatrix();
	
	glColor3f(0,0,0);
	glPushMatrix();	
	glTranslatef(1.0,14.5,0);
	glScalef(0.005, 0.005, 0.005);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"com velocidade nula, um movimento pendular.");
	glPopMatrix();
	
	glColor3f(0,0,0);
	glPushMatrix();	
	glTranslatef(1.0,13.5,0);
	glScalef(0.004, 0.004, 0.004);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"Do outro lado do rio, a pessoa se solta do");
	glPopMatrix();
	
	glColor3f(0,0,0);
	glPushMatrix();	
	glTranslatef(1.0,12.5,0);
	glScalef(0.004, 0.004, 0.004);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"no instante em que sua velocidade fica novamente igual");
	glPopMatrix();
	
	glColor3f(0,0,0);
	glPushMatrix();	
	glTranslatef(1.0,11.5,0);
	glScalef(0.004, 0.004, 0.004);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"a zero. Imediatamente antes de se soltar, sua aceleração tem");
	glPopMatrix();
	
//LETRA A	
	glBegin(GL_QUADS);
		glColor3f(botrresp[0],botgresp[0],botbresp[0]);
		glVertex3f(1.0, 11.0, 0);
		glVertex3f(19.0, 11.0, 0);
		glVertex3f(19.0, 9.5, 0);
		glVertex3f(1.0, 9.5, 0);
	glEnd();
	
	glFlush();
		
	glColor3f(1,1,1);
	glPushMatrix();	
	glTranslatef(1.2,10.0,0);
	glScalef(0.0035, 0.0035, 0.0035);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"valor nulo.");
	glPopMatrix();

//LETRA B
	glBegin(GL_QUADS);
		glColor3f(botrresp[1],botgresp[1],botbresp[1]);
		glVertex3f(1.0, 9.0, 0);
		glVertex3f(19.0, 9.0, 0);
		glVertex3f(19.0, 7.5, 0);
		glVertex3f(1.0, 7.5, 0);
	glEnd();
	
	glFlush();
		
	glColor3f(1,1,1);
	glPushMatrix();	
	glTranslatef(1.2,8.0,0);
	glScalef(0.0035, 0.0035, 0.0035);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"direção que forma um ângulo de 30° com a vertical e módulo 9m/s2.");
	glPopMatrix();

//LETRA C
glBegin(GL_QUADS);
		glColor3f(botrresp[2],botgresp[2],botbresp[2]);
		glVertex3f(1.0, 7.0, 0);
		glVertex3f(19.0, 7.0, 0);
		glVertex3f(19.0, 5.5, 0);
		glVertex3f(1.0, 5.5, 0);
	glEnd();
	
	glFlush();
		
	glColor3f(1,1,1);
	glPushMatrix();	
	glTranslatef(1.2,6.0,0);
	glScalef(0.0035, 0.0035, 0.0035);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"direcao que forma um ângulo de 30° com a vertical e módulo 5m/s2.");
	glPopMatrix();
//LETRA D
glBegin(GL_QUADS);
		glColor3f(botrresp[3],botgresp[3],botbresp[3]);
		glVertex3f(1.0, 5.0, 0);
		glVertex3f(19.0, 5.0, 0);
		glVertex3f(19.0, 3.5, 0);
		glVertex3f(1.0, 3.5, 0);
	glEnd();
	
	glFlush();
		
	glColor3f(1,1,1);
	glPushMatrix();	
	glTranslatef(1.2,4.0,0);
	glScalef(0.0035, 0.0035, 0.0035);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"direcao que forma um ângulo de 60° com a vertical e módulo 9m/s2.");
	glPopMatrix();
//LETRA E
    glBegin(GL_QUADS);
		glColor3f(botrresp[4],botgresp[4],botbresp[4]);
		glVertex3f(1.0, 3.0, 0);
		glVertex3f(19.0, 3.0, 0);
		glVertex3f(19.0, 1.5, 0);
		glVertex3f(1.0, 1.5, 0);
	glEnd();
	
	glFlush();
		
	glColor3f(1,1,1);
	glPushMatrix();	
	glTranslatef(1.2,2.0,0);
	glScalef(0.0035, 0.0035, 0.0035);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"direcao que forma um ângulo de 60° com a vertical e módulo 5m/s2.");
	glPopMatrix();
}
	glFlush();
	
	if(perg == 1){
	glColor3f(1,1,1);
	glPushMatrix();	
	glTranslatef(1.2,3.0,0);
	glScalef(0.005, 0.005, 0.005);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"4/5");
	glPopMatrix();
	
	//PERGUNTA FÍSICA 2
	glColor3f(0,0,0);
	glPushMatrix();	
	glTranslatef(1.0,19.4,0);
	glScalef(0.004, 0.004, 0.004);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"22 (FUVEST 2014 - Primeira Fase) No sistema cardiovascular");
	glPopMatrix();
	
	glColor3f(0,0,0);
	glPushMatrix();	
	glTranslatef(1.0,18.5,0);
	glScalef(0.004, 0.004, 0.004);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"de um ser humano, o coracao funciona como uma bomba,");
	glPopMatrix();
	
	glColor3f(0,0,0);
	glPushMatrix();	
	glTranslatef(1.0,17.5,0);
	glScalef(0.004, 0.004, 0.004);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"com potencia media de 10W, responsavel pela circulacao");
	glPopMatrix();
	
	glColor3f(0,0,0);
	glPushMatrix();	
	glTranslatef(1.0,16.5,0);
	glScalef(0.004, 0.004, 0.004);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"sanguinea. Se uma pessoa fizer uma dieta alimentar de 2500");
	glPopMatrix();
	
	glColor3f(0,0,0);
	glPushMatrix();	
	glTranslatef(1.0,15.5,0);
	glScalef(0.004, 0.004, 0.004);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"kcal diarias, a porcentagem dessa energia utilizada para manter");
	glPopMatrix();
	
	glColor3f(0,0,0);
	glPushMatrix();	
	glTranslatef(1.0,14.5,0);
	glScalef(0.005, 0.005, 0.005);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"sua circulacao sanguinea sera, aproximadamente, igual a?");
	glPopMatrix();
	
	glColor3f(0,0,0);
	glPushMatrix();	
	glTranslatef(1.0,13.5,0);
	glScalef(0.004, 0.004, 0.004);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"Note e adote -> 1 cal = 4J");
	glPopMatrix();
	
	glColor3f(0,0,0);
	glPushMatrix();	
	glTranslatef(1.0,12.5,0);
	glScalef(0.004, 0.004, 0.004);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN," ");
	glPopMatrix();
	
	glColor3f(0,0,0);
	glPushMatrix();	
	glTranslatef(1.0,11.5,0);
	glScalef(0.004, 0.004, 0.004);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN," ");
	glPopMatrix();
	
//LETRA A	
	glBegin(GL_QUADS);
		glColor3f(botrresp[0],botgresp[0],botbresp[0]);
		glVertex3f(1.0, 11.0, 0);
		glVertex3f(19.0, 11.0, 0);
		glVertex3f(19.0, 9.5, 0);
		glVertex3f(1.0, 9.5, 0);
	glEnd();
	
	glFlush();
		
	glColor3f(1,1,1);
	glPushMatrix();	
	glTranslatef(1.2,10.0,0);
	glScalef(0.0035, 0.0035, 0.0035);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"1%");
	glPopMatrix();

//LETRA B
	glBegin(GL_QUADS);
		glColor3f(botrresp[1],botgresp[1],botbresp[1]);
		glVertex3f(1.0, 9.0, 0);
		glVertex3f(19.0, 9.0, 0);
		glVertex3f(19.0, 7.5, 0);
		glVertex3f(1.0, 7.5, 0);
	glEnd();
	
	glFlush();
		
	glColor3f(1,1,1);
	glPushMatrix();	
	glTranslatef(1.2,8.0,0);
	glScalef(0.0035, 0.0035, 0.0035);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"4%");
	glPopMatrix();

//LETRA C
glBegin(GL_QUADS);
		glColor3f(botrresp[2],botgresp[2],botbresp[2]);
		glVertex3f(1.0, 7.0, 0);
		glVertex3f(19.0, 7.0, 0);
		glVertex3f(19.0, 5.5, 0);
		glVertex3f(1.0, 5.5, 0);
	glEnd();
	
	glFlush();
		
	glColor3f(1,1,1);
	glPushMatrix();	
	glTranslatef(1.2,6.0,0);
	glScalef(0.0035, 0.0035, 0.0035);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"9%");
	glPopMatrix();
//LETRA D
glBegin(GL_QUADS);
		glColor3f(botrresp[3],botgresp[3],botbresp[3]);
		glVertex3f(1.0, 5.0, 0);
		glVertex3f(19.0, 5.0, 0);
		glVertex3f(19.0, 3.5, 0);
		glVertex3f(1.0, 3.5, 0);
	glEnd();
	
	glFlush();
		
	glColor3f(1,1,1);
	glPushMatrix();	
	glTranslatef(1.2,4.0,0);
	glScalef(0.0035, 0.0035, 0.0035);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"20%");
	glPopMatrix();
//LETRA E
    glBegin(GL_QUADS);
		glColor3f(botrresp[4],botgresp[4],botbresp[4]);
		glVertex3f(1.0, 3.0, 0);
		glVertex3f(19.0, 3.0, 0);
		glVertex3f(19.0, 1.5, 0);
		glVertex3f(1.0, 1.5, 0);
	glEnd();
	
	glFlush();
		
	glColor3f(1,1,1);
	glPushMatrix();	
	glTranslatef(1.2,2.0,0);
	glScalef(0.0035, 0.0035, 0.0035);
	glLineWidth(5); 
	DesenhaTextoStroke(GLUT_STROKE_ROMAN,"25%");
	glPopMatrix();
	}
	
	glutSwapBuffers();
	
	
	glFlush();
	//glutPostRedisplay();
	//glutSwapBuffers();
}


void telaJogo(int t){
	switch(t){
		//Menu principal
		case 0:
			tela = 0;
			glutDisplayFunc(telaInicio);
			break;		
		//labirinto
		case 1:
			tela = 1;
			glutDisplayFunc(telaTabuleiro);
			break;
		//vitoria
		case 2:
			tela = 2;
			glutDisplayFunc(telaVitoria);			
			break;
		//derrota
		case 3:
			tela = 3;
			glutDisplayFunc(telaPause);			
			break;
		case 4:
			tela = 4;
			glutDisplayFunc(telaJogadores);			
			break;
		case 5:
			tela = 5;			
			glutDisplayFunc(telaDado);			
			break;	
		case 6:
			bot = 0;
			botoes = 5;
			tela = 6;			
			glutDisplayFunc(telaPerguntas);			
			break;					
	}
}



int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitWindowSize(800,800);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowPosition(150,50);
	glutCreateWindow("Tabuleiro de Perguntas");
	telaJogo(tela);
    glutReshapeFunc(AlteraTamanhoJanela);	
    glutPassiveMotionFunc(MoveMouse);    
	glutSpecialFunc(TeclasEspeciais); 
	glutKeyboardFunc(Teclado);
	glutMouseFunc(botoesMouse);
	Inicializa();
	glutMainLoop();
	
	return 0;
}
