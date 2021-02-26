#pragma once
#include "Forms.h"
#include "TimeDuration.h"

class TextBox:public Forms
{
public:
	bool escribiendo;
	char*escritura;
	unsigned max,cont;
	float Tope;
	TimeDuration tim;
	bool dosClicks;
	TextBox(){};
	TextBox(char*name,CRD crd,float wigth,float TotalWigth,float TotalHeight,char*Escritura="",unsigned max=0):Forms(name,crd,0,20,TotalWigth,TotalHeight){
		if(wigth<15)
		{
			this->Wigth=15;
			this->max=1;
		}
		else
		{
			this->Wigth=wigth;
			if(!max)
			   this->max=(unsigned)(wigth/15);
			else
				this->max=max;
		}
		cont=0;
		AddNewText(Escritura);
		Tope=0;
		dosClicks=escribiendo=false;
		t=Type::TEXTBOX;
	
	};
	~TextBox(){delete escritura;};
	bool Escribiendo(){
		if(active)
		   return escribiendo;
	    return false;     
	};
	char*GetEscritura(){
		return escritura;
	};
	void AddNewText(char*newText){
		 escritura=new char[max+1];
		if(strlen(newText)>max)
		{
		  
		   escritura[max]=0;
		   cont=max;
		   for(unsigned i=0;i<max;i++)
			  escritura[i]=newText[i];
		}
		else
		{
		   escritura[strlen(newText)]=0;
		   for(unsigned i=0;i<strlen(newText);i++)
			  escritura[i]=newText[i];
	 	   cont=strlen(newText);
		
		}	
	};
	void AddText(char letra){
		if(cont<max)
		{
			escritura[cont++]=letra;
			escritura[cont]=0;
		}
	}
	void SubText()
	{
		if(cont>0)
		{	
               escritura[--cont]=0;
		}
		
	}
	void CambiarEscritura(char*Newescritura){AddNewText(Newescritura);};

	//PURAS///
	void Draw(){
		if(!this->NoDraw)
		{
	         glPushMatrix();
				  glLoadIdentity();
				  glTranslatef((GLfloat)(-TotalWigth/2+coord->x),(GLfloat)(TotalHeight/2-coord->y),(GLfloat)2*this->TotalWigth-1); 
				  glColor3f(1,1,1);
				  glBegin(GL_POLYGON);
				  glVertex3f(0,0,-1);
				  glVertex3f((GLfloat)Wigth,0,-1);
				  glVertex3f((GLfloat)Wigth,(GLfloat)-Height,-1);
				  glVertex3f(0,(GLfloat)-Height,-1);
				  glEnd();
				  if(!active)
				  {
					  glColor3f((GLfloat)0.3,(GLfloat)0.3,(GLfloat)0.3);
					  glBegin(GL_LINES);
				     glVertex3f(0,0,(GLfloat)-0.9);
					 glVertex3f((GLfloat)Wigth/4,-Height,(GLfloat)-0.9);

				     glVertex3f((GLfloat)Wigth/4,(GLfloat)0,(GLfloat)-0.9);
				     glVertex3f((GLfloat)2*Wigth/4,(GLfloat)-Height,(GLfloat)-0.9);

					 glVertex3f((GLfloat)Wigth/2,(GLfloat)0,(GLfloat)-0.9);
				     glVertex3f((GLfloat)3*Wigth/4,(GLfloat)-Height,(GLfloat)-0.9);

					  glVertex3f((GLfloat)3*Wigth/4,(GLfloat)0,(GLfloat)-0.9);
				     glVertex3f((GLfloat)Wigth,(GLfloat)-Height,(GLfloat)-0.9);
				     glEnd();
				  
				  }
				  glLoadIdentity();
				  TextAlignCenter(escritura,(GLfloat)coord->x,(GLfloat)coord->y,active?(GLfloat)0:(GLfloat)0.2,active?(GLfloat)0:(GLfloat)0.2,active?(GLfloat)0:(GLfloat)0.2,1,this);
		     
		
	      }
			 glPopMatrix();
	};
	unsigned Click(){
		if(!escribiendo)
			escribiendo=true;

		if(!dosClicks)
		{
			dosClicks=true;
			tim.ResettIncrementa(&tim);
			tim.Incrementa(&tim);
		}
		else if(dosClicks)
		{
		dosClicks=false;
		tim.Incrementa(&tim);
		if(tim.TimE<=1.5)
			AddNewText("");

		}

		return t;
	}
	void NoClick(){
		if(escribiendo)
			escribiendo=false;
	}
	void TextAlignCenter(char*c,GLfloat x,GLfloat y,GLfloat R,GLfloat G,GLfloat B,unsigned LetterSize,Forms*f)
	{
	   glColor3f(R,G,B);
	   glRasterPos3f((GLfloat)-f->TotalWigth/2+x,(GLfloat)((f->TotalHeight/2)-y-f->Height*4/5),(GLfloat)2*f->TotalWigth-1);
	   for(unsigned int i=0;i<strlen(c);i++)
	   {
		if(LetterSize==2)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);
		 else if(LetterSize==1)
			  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c[i]);
		 else if(LetterSize==0)
	 	      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c[i]);
	   }

   }
};