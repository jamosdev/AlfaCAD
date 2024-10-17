/*   ______   ___       ___         ____     ______  ____
*   /\  _  \ /\_ \    /'___\       /\  _`\  /\  _  \/\  _`\
*   \ \ \L\ \\//\ \  /\ \__/   __  \ \ \/\_\\ \ \L\ \ \ \/\ \
*    \ \  __ \ \ \ \ \ \ ,__\/'__`\ \ \ \/_/_\ \  __ \ \ \ \ \
*     \ \ \/\ \ \_\ \_\ \ \_/\ \L\.\_\ \ \L\ \\ \ \/\ \ \ \_\ \
*      \ \_\ \_\/\____\\ \_\\ \__/.\_\\ \____/ \ \_\ \_\ \____/
*       \/_/\/_/\/____/ \/_/ \/__/\/_/ \/___/   \/_/\/_/\/___/
*
*   A CAD
*
*   By Marek Ratajczak 2024
*
*   See readme_alfacad.txt for copyright information.
*
*/

#include<forwin.h>
#define ALLEGWIN
#include <allegext.h>
#include<math.h>
#include<stddef.h>
#include "bib_e.h"
#include "rysuj_e.h"
#include "o_libfun.h"
#include "o_object.h"
#include "bib_arc.h"


extern int getupattern(void);

static int lL,OL ;
void mvcurbplL(unsigned i)      /* ini */
{ lL=OL=i;}

void linen(long X1, long Y1, long X2, long Y2, int mode)
{
  long X,Y,DX,DY,XS,YS;

  if (X1 == X2 && Y1 == Y2) return ;
  if (COPY_PUT == mode)
  {
   lineC(X1, Y1, X2, Y2) ;
   return ;
  }
  X=X1;
  Y=Y1;
  XS=YS=1;
  if (X1>X2) XS=-1;
  if (Y1>Y2) YS=-1;
  DX=labs(X2-X1);
  DY=labs(Y2-Y1);
  if(DX>=2*DY) X+=XS;
  else if(DY>=2*DX) Y+=YS;
  else { X+=XS; Y+=YS; }
  lineC(X,Y,X2,Y2);
}

static void near sinX(int *X,int N)
{ double dk,kat=0;
  int i;
  dk=Pi/(2*(N-1));
  for(i=0,kat=0;i<N;i++,X++,kat+=dk) *X=sin(kat)*1000+0.5;
}

#define NPC0 14
#define NPC 31
void DrawCircle(long Xr,long Yr,long R, int mode)
{
  static int Y0[NPC0] = {0,121,239,355,465,568,663,749,823,885,935,971,993,1000};
  static int Y[NPC] = {0,52,105,156,208,259,309,358,407,454,500,545,588,629,669,
                       707,743,777,809,839,866,891,914,934,951,966,978,988,995,999,1000};
  static int Z[NPC], *X, wsk=0;
  static long R0;
  long  Xk1, Xk2, Yk1, Yk2, Xp1, Yp1, Xp2, Yp2;
  double  Xfact, Yfact;
  int I=0;  //16.08.2007
  long N;
  int linestyle;

  linestyle = getupattern();

  if (linestyle > 0)
  {
	  DrawArc(Xr, Yr, 0, PI2*3.99, R, mode);
	  return;
  }

  Xfact = fabs(R * 0.001);
  Yfact = Xfact / sk_x;
  if (Xfact > 0.0)
   { if(Pi*R<NPC*10/*7.5*/)
      { N=3+R/20;
	X=Z;
	if(wsk==0 || R0!=R)
	 { sinX(Z,(int)N);
	   wsk=1;
	   R0=R;
	 }
      }
     else { N=NPC; X=Y;}
     Xk1  = X[0] * Xfact + 0.5;
     Yk1  = X[(int)N-1] * Yfact + 0.5;
     for(I=1;I<N;I++)
      { if( mvcurb.akton && mvcurb.mvc ) 
	 { OL=I; return; }
	    if( mvcurb.aktoff && mvcurb.O==1 && OL==I ) return;
		Xk2 = X[I] * Xfact + 0.5;
		Yk2 = X[(int)N -I-1] * Yfact + 0.5;
		Xp1 = Xr - Xk1;
		Yp1 = Yr + Yk1;
		Xp2 = Xr - Xk2;
		Yp2 = Yr + Yk2;
		linen(Xp2, Yp2, Xp1, Yp1, mode);
		Xp1 = Xr + Xk1;
		Xp2 = Xr + Xk2;
		linen(Xp1, Yp1, Xp2, Yp2, mode);
		Yp1 = Yr - Yk1;
		Yp2 = Yr - Yk2;
		linen(Xp2, Yp2, Xp1, Yp1, mode);
		Xp1 = Xr - Xk1;
		Xp2 = Xr - Xk2;
		linen(Xp1, Yp1, Xp2, Yp2, mode);
		Xk1 = Xk2;
		Yk1 = Yk2;
      }
   }
  else 
    {
      lineC(Xr,Yr,Xr,Yr);
    }  
  if( mvcurb.akton ) { OL=I+1; return; }
}

#define NPA 90 //56
void DrawArc(long Xr,long Yr,double sta,double ea,long R, int mode)
/*---------------------------------------------------------------*/
{
  double Xp1,Yp1,Xp2,Yp2;
  double da, dda;	/*kat rozwarcia luku, kat podzialu luku*/
  double si, co; 	/*sinus i cosinus kata podzialu luku*/
  int N;		/*liczba 'bokow' luku*/
  int k;
  long Num; 		/*liczba 'bokow' podzialu okregu (zalezy od promienia)*/
  double xdiff, ydiff;	/*pomocnicze*/


  if (R == 0.0)  { return; }
  sta = Angle_Normal (sta);
  ea = Angle_Normal (ea);
  da = ea - sta;
  if (FALSE == Check_if_Equal (da, 0)  &&  sta > ea)
  {
    da += Pi2;
  }
			/*  dla da =  Pi2 okrag */
  Num = 8 + R / 5;
  if( Num > NPA )
  {
    Num = NPA;
  }
  dda = Pi2 / Num ;
  si = sin (dda) ;
  co = cos (dda) ;
  N =  (int)(da / dda);
  Xp1 = Xr + R * cos (sta);
  Yp1 = Yr - R * sin (sta) / sk_x;
  
  for(k = 0; k < N; k++)
   {
     if( mvcurb.akton && mvcurb.mvc ) { lL=k; return; }
     if( mvcurb.aktoff && mvcurb.l==1 && lL==k ) return;

     xdiff = Xp1 - Xr ;
     ydiff = Yp1 - Yr ;
     Xp2 = Xr + xdiff * co + ydiff * si * sk_x;
     Yp2 = Yr - xdiff * si / sk_x + ydiff * co;
     linen (Xp1 + .5, Yp1 + .5, Xp2 + .5, Yp2 + .5, mode) ;
	 
     Xp1 = Xp2;
     Yp1 = Yp2;
   }
  Xp2 = Xr + R * cos (ea) ;
  Yp2 = Yr - R * sin (ea) / sk_x;
  linen (Xp1 + .5, Yp1 + .5, Xp2 + .5, Yp2 + .5, mode) ;

  if (mvcurb.akton) { lL = k + 1 ; return ; }
}

void DrawArcNocut(long Xr, long Yr, double sta, double ea, long R)
/*---------------------------------------------------------------*/
{
	double Xp1, Yp1, Xp2, Yp2;
	double da, dda;	/*kat rozwarcia luku, kat podzialu luku*/
	double si, co; 	/*sinus i cosinus kata podzialu luku*/
	int N;		/*liczba 'bokow' luku*/
	int k;
	long Num; 		/*liczba 'bokow' podzialu okregu (zalezy od promienia)*/
	double xdiff, ydiff;	/*pomocnicze*/

	if (R == 0.0) { return; }
	sta = Angle_Normal(sta);
	ea = Angle_Normal(ea);
	da = ea - sta;
	if (FALSE == Check_if_Equal(da, 0) && sta > ea)
	{
		da += Pi2;
	}
	/*  dla da =  Pi2 okrag */
	Num = 8 + R / 5;
	if (Num > NPA)
	{
		Num = NPA;
	}
	dda = Pi2 / Num;
	si = sin(dda);
	co = cos(dda);
	N = (int)(da / dda);
	Xp1 = Xr + R * cos(sta);
	Yp1 = Yr - R * sin(sta) / sk_x;

	for (k = 0; k < N; k++)
	{
		if (mvcurb.akton && mvcurb.mvc) { lL = k; return; }
		if (mvcurb.aktoff && mvcurb.l == 1 && lL == k) return;

		xdiff = Xp1 - Xr;
		ydiff = Yp1 - Yr;
		Xp2 = Xr + xdiff * co + ydiff * si * sk_x;
		Yp2 = Yr - xdiff * si / sk_x + ydiff * co;
		lineC(Xp1 + .5, Yp1 + .5, Xp2 + .5, Yp2 + .5);

		Xp1 = Xp2;
		Yp1 = Yp2;
	}
	Xp2 = Xr + R * cos(ea);
	Yp2 = Yr - R * sin(ea) / sk_x;
	lineC(Xp1 + .5, Yp1 + .5, Xp2 + .5, Yp2 + .5);

	if (mvcurb.akton) { lL = k + 1; return; }
}


#ifdef aaaaa
//alternative like
#define NPA 53
void DrawArc(long Xr,long Yr,double sta,double ea,long R)
{ int Sy[NPA] ={
0, 121, 239, 355, 465, 568, 663, 749, 823, 885, 935, 971, 993, 1000,
   993, 971, 935, 885, 823, 749, 663, 568, 465, 355, 239, 121, 0,
  -121,-239,-355,-465,-568,-663,-749,-823,-885,-935,-971,-993,-1000,
  -993,-971,-935,-885,-823,-749,-663,-568,-465,-355,-239,-121, 0 };

  int Cy[NPA] ={
1000, 993, 971, 935, 885, 823, 749, 663, 568, 465, 355, 239, 121, 0,
     -121,-239,-355,-465,-568,-663,-749,-823,-885,-935,-971,-993,-1000,
     -993,-971,-935,-885,-823,-749,-663,-568,-465,-355,-239,-121, 0,
      121, 239, 355, 465, 568, 663, 749, 823, 885, 935, 971, 993, 1000};

  static double sta0,ea0;
  static int Sz[NPA],Cz[NPA],*S,*C,R0,wsk=0;
  long Xp1,Yp1,Xp2,Yp2;
  double Xfact,Yfact,xx,yy;
  double da;
  int i,N,n1,n2,k;
/*  da=fabs(ea-sta);
  if(da>=Pi2) { DrawCircle(Xr,Yr,R); return; }
*/
  if(fabs(sta)>=Pi2) sta-=floor(0.5+sta/Pi2)*Pi2;
  if(sta<0) sta+=Pi2;
  if(fabs(ea)>=Pi2) ea-=floor(0.5+ea/Pi2)*Pi2;
  if(ea<0) ea+=Pi2;

  da=fabs(ea-sta);
  if(da>=Pi2) { DrawCircle(Xr,Yr,R); return; }

  Xfact = fabs(R*0.001);
  Yfact = Xfact / sk_x;
  if (Xfact == 0.0)  { line(Xr, Yr,Xr,Yr); return; }
  if(Pi*R<NPA*7.5)
   { N=8+R/5;
     S=Sz;C=Cz;
     if(wsk==0 || R0!=R || sta0!=sta || ea0!=ea)
      { SC(Sz,Cz,N);
	S=Sz;
	C=Cz;
	wsk=1;
	R0=R;
	sta0=sta;
	ea0=ea;
      }
   }
  else { N=NPA; S=Sy; C=Cy;}
  da=Pi2/(N-1);
  n1=1+sta/da;
  n2=1+ea/da;
  Xp1=Xr+R*cos(sta)+0.5;
  Yp1=Yr-R*sin(sta)/sk_x+0.5;
  if(sta>ea && n1==n2)
   { Xp2=Xr+Xfact*C[n1]+0.5;
     Yp2=Yr-Yfact*S[n1]+0.5;
     linen(Xp1,Yp1,Xp2,Yp2);
     Xp1=Xp2;
     Yp1=Yp2;
     n1++;
   }
  for(k=0,i=n1;i!=n2;k++,i++) 		/*k - zmienna testowa*/
   { if( mvcurb.akton && mvcurb.mvc ) { lL=k; return; }
     if( mvcurb.aktoff && mvcurb.l==1 && lL==k ) return;
     Xp2=Xr+Xfact*C[i]+0.5;
     Yp2=Yr-Yfact*S[i]+0.5;
     if(k>60)
     {
       k=k+1;
       break;
     }
     linen(Xp1,Yp1,Xp2,Yp2);
     Xp1=Xp2;
     Yp1=Yp2;
     if( (i == N-1)  && (N != n2) )
      {
	i=0;
      }
   }
  Xp2=Xr+R*cos(ea)+0.5;
  Yp2=Yr-R*sin(ea)/sk_x+0.5;
  linen(Xp1,Yp1,Xp2,Yp2);
  if( mvcurb.akton ) { lL=k+1; return; }
}
#endif
