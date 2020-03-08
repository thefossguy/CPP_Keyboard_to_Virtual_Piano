#include<iostream.h>
#include<dos.h>
#include<conio.h>
#include<stdlib.h>
#define SHOW 1
#define HIDE 2
union REGS input,output;

class piano
{
    public:int BIGKEY,MIDKEY,back,border;
            piano()  //CONSTRUCTOR INITIALIZATION
            {
                BIGKEY=15;
                MIDKEY=1;
                back=7;
                border=15
            }
}color;

void drawpiano(int x,int y);
int check_xy(int x, int y);
void BOX(int c,int r,int c1,int r1,int col);
int initmouse();
void setupscreen();
void pointer(int on);
void restrictmouse(int x1,int y1,int x2,int y2);
void check_keys(int x,int y);
void getmouse(int *button,int *x,int *y);
float freq[7] = {130.81, 146.83, 164.81, 174.61,196, 220, 246.94 } ;
int n=0,a=4,backcolor=2,exitcode=1;
void showbar(int t)
{
 if(t>65) t=65;
 if(t<1) t=1;
 textcolor(15);
 for(int q=0;q<=t;t++)
 {
	gotoxy(3+q,4);
	cprintf("Û");
 }
}


//MAIN FUNCTION

int main(){
    int b,x,y,key;
    char ch;
    if(initmouse()==-1){
        //TERMINATES THE PROGRAM IF MOUSE IS NOT CONNECTED
        clrscr();
        cout<<"\n\n -----NO MOUSE CONNECTED----- \n\n"

    }

    pointer(SHOW);
    setupscreen();
    exitcode=1;
    while(exitcode)
    {
            if(kbhit())
	        {
	            ch=getch();
	            if(ch==27) break;
	            if(ch==75) a--;
	            if(ch==77) a++;
	            check_keys(x,y);
	            switch(ch)
	            {
		            case 'a':case'A':key=0;break;
		            case 's':case'S':key=1;break;
		            case 'd':case'D':key=2;break;
		            case 'f':case'F':key=3;break;
		            case 'j':case'J':key=4;break;
		            case 'k':case'K':key=5;break;
		            case 'l':case'L':key=6;break;
	            }
	            sound(freq[key]*a);
	            delay(80);
	            nosound();
	        }
	        getmouse(&b,&x,&y);
	        if(b==1)
	        {
		        while(b==1)
		        {
			        getmouse(&b,&x,&y);
			        key=check_xy(x,y);
			        if(key!=-1 && key<7)
		        	{
		        		sound(freq[key]*a);
		        	}
		        	else if(key>6)
			        {
				         sound(freq[12-key]*(a/2));
			        }
		    }
		    nosound();
		    check_keys(x,y);
	        }
        }
        
    }
    textbackground(0);
    clrscr();
    _setcursortype(_NORMALCURSOR);
    return 0;

}  //EOF

void setupscreen() /* Display screen settings */
{
 _setcursortype(_NOCURSOR);
 textbackground(backcolor);
 clrscr();
 drawpiano(9,17);
 BOX(4,5,8,5,0);
 BOX(5,5,7,5,1);
 textcolor(15);
 gotoxy(70,5);
 cprintf(">Quit<");
 gotoxy(4,4);
 cprintf("Range");
 textbackground(0);
 gotoxy(8,5);
 cprintf("");
 gotoxy(4,5);
 cprintf("");
 gotoxy(6,5);
 cprintf("%d",a);
 textcolor(14);
 textbackground(backcolor+7);
 gotoxy(30,4);
 cprintf(" VIRTUAL PIANO ");

}

void pianokey(int x,int y) /* Piano key display settings */
{
 textbackground(color.MIDKEY);
 textcolor(color.BIGKEY);
 gotoxy(x,y);
 cprintf("ÛÛÛ  ÛÛÛ");
 gotoxy(x,y+1);
 cprintf("ÛÛÛ  ÛÛÛ");
 gotoxy(x,y+2);
 cprintf("ÛÛÛ  ÛÛÛ");
 gotoxy(x,y+3);
 cprintf("ÛÛÛÛÞÛÛÛ");
 gotoxy(x,y+4);
 cprintf("ÛÛÛÛÞÛÛÛ");
 gotoxy(x,y+5);
 cprintf("ÛÛÛÛÞÛÛÛ");
 gotoxy(x,y+6);
 cprintf("ÛÛÛÛÞÛÛÛ");
 gotoxy(x,y);
}

void drawpiano(int x,int y) /* Drawing of piano */
{
 int t=9;
 BOX(x-5,y-3,75,y+8,color.border); /*invoking function box */
 BOX(x-4,y-2,74,y+7,color.back);
 pianokey(x,y);
 pianokey(x+t,y);
 pianokey(x+t*2,y);
 pianokey(x+t*3,y);
 pianokey(x+t*4,y);
 pianokey(x+t*5,y);
 pianokey(x+t*6,y);
}

void BOX(int c,int r,int c1,int r1,int col)
{
 int i,j;
 textcolor(col);
 for(i=r;i<=r1;i++)
 {
	for(j=c;j<=c1;j++)
	{
		gotoxy(j,i);
		cprintf("Û");
	}
 }
}

int initmouse()
{
 input.x.ax=0;
 int86(0x33,&input,&output);
 return(output.x.ax==0 ? -1 : 0);
}

void pointer(int on)
{
   input.x.ax=on;
   int86(0x33,&input,&output);
}

void restrictmouse(int x1,int y1,int x2,int y2)
{
   input.x.ax=7;
   input.x.cx=x1/8;
   input.x.dx=x2/8;
   int86(0x33,&input,&output);
   input.x.ax=8;
   input.x.cx=y1/8;
   input.x.dx=y2/8;
   int86(0x33,&input,&output);
}


