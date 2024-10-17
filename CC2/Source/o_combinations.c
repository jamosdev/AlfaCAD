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

/*

 1. Each layer can contain any members of the structure, descriptions (properties) and any load
 2. Only visible elements, descriptions and loads are taken into account, so all put on visible layers
 3. Load case is declared as all loads taken into analized block, no matter on what layer, as long the layer is on when block is selected
 4. Number of combination is determined by number choosen in ststic analysis dialog
 5. In AlfaCAD meaning the case is alternative load, as a combination of all g, DL, LL, Lr, WL, SL, EL, RL, HL, FL, TL and displacement of node
 6. Default combination is 1, and can be any number from 1 to 255
 7. Resulting layers are marked with number of case

 EUROCODE
========

g=DL+FL
q=LL+EL+HL+TL
s=SL|RL
r=RL
w=WL

γ       Partial factor for permanent / variable loads from EN 1990 Table A1.2(B)
γ.inf   Partial factor for permanent loads (lower value) from EN 1990 Table A1.2(B)
Ψ0      Factor for combination value of live / snow / wind load from EN 1990 Table A1.1
Ψ1      Factor for "frequent" combination value of live / snow / wind load from EN 1990 Table A1.1
Ψ2      Factor for "quasi permanent" combination value of live / snow / wind load from EN 1990 Table A1.1

ULS

ULSLC1=g*γ
ULSLC2=g*γ + q*γ
ULSLC3=g*γ + q*γ + s*γ*Ψ0
ULSLC4=g*γ + q*γ*Ψ0 + s*γ               //s=max(SL,RL)
ULSLC5=g*γ + q*γ + s*γ*Ψ0 + w*γ*Ψ0      //s=min(SL,RL)
ULSLC6=g*γ + q*γ*Ψ0 + s*γ + w*γ*Ψ0      //s=max(SL,RL)
ULSLC7=g*γ + q*γ*Ψ0 + s*γ*Ψ0 + w*γ      //s=min(SL,RL)
ULSLC8=g*γ + s*γ                        //s=max(SL,RL)
ULSLC9=g*γ + w*γ
ULSLC10=g*γ + s*γ + w*γ*Ψ0              //s=max(SL,RL)
ULSLC11=g*γ + w*γ + s*γ*Ψ0              //s=min(SL,RL)
ULSLC12=g*γ + q*γ + w*γ*Ψ0
ULSLC13=g*γ + q*γ*Ψ0 + w*γ
ULSLC14=g*γ.inf + w*γ                   //γ.inf=1.0 for DL
                      //ξ=0.85 for DL

g=DL+FL
q=LL+EL+HL+TL
s=SL
r=RL
w=WL
l=Lr

DL=1
LL=2
Lr=4
WL=8
SL=16
EL=32  //2
RL=64
HL=128 //2
FL=256 //1
TL=512 //2

 1->  1+256
 2->  2+32+128+512
                                    //mask
ULSLC1=g*γ               //1           //1

ULSLC2=g*γ + q*γ         //2           //1+2

ULSLC3=g*γ + q*γ + s*γ*Ψ0    //3       //1+2+16

ULSLC4=g*γ + q*γ*Ψ0 + s*γ   //4        //1+2+16
ULSLC5=g*γ + q*γ*Ψ0 + r*γ   //5        //1+2+64
ULSLC6=g*γ + q*γ*Ψ0 + l*γ   //6       //1+2+4

ULSLC7=g*γ + q*γ + s*γ*Ψ0 + w*γ*Ψ0 //7 //1+2+16+8
ULSLC8=g*γ + q*γ + r*γ*Ψ0 + w*γ*Ψ0 //8 //1+2+64+8
ULSLC9=g*γ + q*γ + l*γ*Ψ0 + w*γ*Ψ0 //9 //1+2+4+8

ULSLC10=g*γ + q*γ*Ψ0 + s*γ + w*γ*Ψ0 //10 //1+2+16+8
ULSLC11=g*γ + q*γ*Ψ0 + r*γ + w*γ*Ψ0 //11 //1+2+64+8
ULSLC12=g*γ + q*γ*Ψ0 + l*γ + w*γ*Ψ0 //12 //1+2+4+8

ULSLC13=g*γ + q*γ*Ψ0 + s*γ*Ψ0 + w*γ //13 //1+2+16+8
ULSLC14=g*γ + q*γ*Ψ0 + r*γ*Ψ0 + w*γ //14 //1+2+64+8
ULSLC15=g*γ + q*γ*Ψ0 + l*γ*Ψ0 + w*γ //15 //1+2+4+8

ULSLC16=g*γ + s*γ        //16           //1+16

ULSLC17=g*γ + r*γ        //17           //1+64

ULSLC18=g*γ + l*γ        //18           //1+4

ULSLC19=g*γ + w*γ        //19           //1+8

ULSLC20=g*γ + s*γ + w*γ*Ψ0  //20        //1+16+8

ULSLC21=g*γ + r*γ + w*γ*Ψ0   //21       //1+64+8
ULSLC22=g*γ + l*γ + w*γ*Ψ0   //22       //1+4+8
ULSLC23=g*γ + w*γ + s*γ*Ψ0   //23       //1+8+16
ULSLC24=g*γ + w*γ + r*γ*Ψ0   //24       //1+8+64
ULSLC25=g*γ + w*γ + l*γ*Ψ0   //25       //1+8+4
ULSLC26=g*γ + q*γ + w*γ*Ψ0   //26       //1+2+8
ULSLC27=g*γ + q*γ*Ψ0 + w*γ   //27       //1+2+8
ULSLC28=g*γ.inf + w*γ        //28       //1+8

///////                                    //mask
ULSLC1=g*γ                          //1
ULSLC2=g*γ + q*γ                    //1+2
ULSLC3=g*γ + q*γ + s*γ*Ψ0           //1+2+16
ULSLC4=g*γ + q*γ*Ψ0 + s*γ           //1+2+16
ULSLC5=g*γ + q*γ*Ψ0 + r*γ           //1+2+64
ULSLC6=g*γ + q*γ*Ψ0 + l*γ           //1+2+4
ULSLC7=g*γ + q*γ + s*γ*Ψ0 + w*γ*Ψ0  //1+2+16+8
ULSLC8=g*γ + q*γ + r*γ*Ψ0 + w*γ*Ψ0  //1+2+64+8
ULSLC9=g*γ + q*γ + l*γ*Ψ0 + w*γ*Ψ0  //1+2+4+8
ULSLC10=g*γ + q*γ*Ψ0 + s*γ + w*γ*Ψ0 //1+2+16+8

ULSLC11=g*γ + q*γ*Ψ0 + r*γ + w*γ*Ψ0 //1+2+64+8
ULSLC12=g*γ + q*γ*Ψ0 + l*γ + w*γ*Ψ0 //1+2+4+8
ULSLC13=g*γ + q*γ*Ψ0 + s*γ*Ψ0 + w*γ //1+2+16+8
ULSLC14=g*γ + q*γ*Ψ0 + r*γ*Ψ0 + w*γ //1+2+64+8
ULSLC15=g*γ + q*γ*Ψ0 + l*γ*Ψ0 + w*γ //1+2+4+8
ULSLC16=g*γ + s*γ                   //1+16
ULSLC17=g*γ + r*γ                   //1+64
ULSLC18=g*γ + l*γ                   //1+4
ULSLC19=g*γ + w*γ                   //1+8
ULSLC20=g*γ + s*γ + w*γ*Ψ0          //1+16+8

ULSLC21=g*γ + r*γ + w*γ*Ψ0          //1+64+8
ULSLC22=g*γ + l*γ + w*γ*Ψ0          //1+4+8
ULSLC23=g*γ + w*γ + s*γ*Ψ0          //1+8+16
ULSLC24=g*γ + w*γ + r*γ*Ψ0          //1+8+64
ULSLC25=g*γ + w*γ + l*γ*Ψ0          //1+8+4
ULSLC26=g*γ + q*γ + w*γ*Ψ0          //1+2+8
ULSLC27=g*γ + q*γ*Ψ0 + w*γ          //1+2+8
ULSLC28=g*γ.inf + w*γ               //1+8


    DL,     LL,         Lr,         WL,         SL,         EL,         RL,         HL,         FL,         TL
1, gamma,   NULL,       NULL,       NULL,       NULL,       NULL,       NULL,       NULL,       gamma,      NULL
2, gamma,   gamma,      NULL,       NULL,       NULL,       gamma,      NULL,       gamma,      gamma,      gamma
3, gamma,   gamma,      NULL,       NULL,       gamma*psi0, gamma,      NULL,       gamma,      gamma,      gamma
4, gamma,   gamma*psi0, NULL,       NULL,       gamma,      gamma*psi0, NULL,       gamma*psi0, gamma,      gamma*psi0
5, gamma,   gamma*psi0, NULL,       NULL,       NULL,       gamma*psi0, gamma,      gamma*psi0, gamma,      gamma*psi0
6, gamma,   gamma*psi0, gamma,      NULL,       NULL,       gamma*psi0, NULL,       gamma*psi0, gamma,      gamma*psi0
7, gamma,   gamma,      gamma,      gamma*psi0, gamma*psi0, gamma,      NULL,       gamma,      gamma,      gamma
8, gamma,   gamma,      gamma,      gamma*psi0, NULL,       gamma,      gamma*psi0, gamma,      gamma,      gamma
9, gamma,   gamma,      gamma*psi0, gamma*psi0, NULL,       gamma,      NULL,       gamma,      gamma,      gamma
10,gamma,   gamma*psi0, NULL,       gamma*psi0, gamma,      gamma*psi0, NULL,       gamma*psi0, gamma,      gamma*psi0

11,gamma,   gamma*psi0, NULL,       gamma*psi0, NULL,       gamma*psi0, gamma,      gamma*psi0, gamma,      gamma*psi0
12,gamma,   gamma*psi0, gamma,      gamma*psi0, NULL,       gamma*psi0, NULL,       gamma*psi0, gamma,      gamma*psi0
13,gamma,   gamma*psi0, NULL,       gamma,      gamma*psi0, gamma*psi0, NULL,       gamma*psi0, gamma,      gamma*psi0
14,gamma,   gamma*psi0, NULL,       gamma,      NULL,       gamma*psi0, gamma*psi0, gamma*psi0, gamma,      gamma*psi0
15,gamma,   gamma*psi0, gamma*psi0, gamma,      NULL,       gamma*psi0, NULL,       gamma*psi0, gamma,      gamma*psi0
16, gamma,  NULL,       NULL,       NULL,       gamma,      NULL,       NULL,       NULL,       gamma,      NULL
17, gamma,  NULL,       NULL,       NULL,       NULL,       NULL,       gamma,      NULL,       gamma,      NULL
18, gamma,  NULL,       gamma,      NULL,       NULL,       NULL,       NULL,       NULL,       gamma,      NULL
19, gamma,  NULL,       NULL,       gamma,      NULL,       NULL,       NULL,       NULL,       gamma,      NULL
20, gamma,  NULL,       NULL,       gamma*psi0, gamma,      NULL,       NULL,       NULL,       gamma,      NULL

21, gamma,  NULL,       NULL,       gamma*psi0, NULL,       NULL,      gamma,      NULL,       gamma,      NULL
22, gamma,  NULL,       gamma,      gamma*psi0, NULL,       NULL,      NULL,       NULL,       gamma,      NULL
23, gamma,  NULL,       NULL,       gamma,      gamma*psi0, NULL,      NULL,       NULL,       gamma,      NULL
24, gamma,  NULL,       gamma,      gamma,      NULL,       NULL,      gamma*psi0, NULL,       gamma,      NULL
25, gamma,  NULL,       gamma*psi0, gamma,      NULL,       NULL,      NULL,       NULL,       gamma,      NULL
26, gamma,  gamma,      NULL,       gamma*psi0, NULL,       gamma,     NULL,       gamma,      gamma,      gamma
27, gamma,  gamma*psi0, NULL,       gamma,      NULL,       gamma*psi0,NULL,       gamma*psi0, gamma,      gamma*psi0
28, gamma.inf, NULL,    NULL,       gamma,      NULL,       NULL,      NULL,       NULL,       gamma.inf,  NULL


for the flat roof:
γg      1.35 (unfavourable)
γq      1.5
Ψ0.q    0
Ψ0.s    0.7 (Sweden)
Ψ0.w    0.6

flags
DL=1
LL=2
Lr=4
WL=8
SL=16
EL=2
RL=64
HL=2
FL=1
TL=2

SLS

SLSLC1=g                    //1
SLSLC2=g + q                //1+2
SLSLC3=g + q + s*Ψ0         //1+2+16
SLSLC4=g + q + w*Ψ0         //1+2+8
SLSLC5=g + q + s*Ψ0 + w*Ψ0  //1+2+16+8
SLSLC6=g + q*Ψ0 + s + w*Ψ0  //1+2+16+8
SLSLC7=g + q*Ψ0 + s*Ψ0 + w  //1+2+16+8
SLSLC8=g + s                //1+16
SLSLC9=g + w                //1+8
SLSLC10=g + s + w*Ψ0        //1+16+8
SLSLC11=g + w + s*Ψ0        //1+8+16
SLSLC12=g + q*Ψ0 + s        //1+2+16
SLSLC13=g + q*Ψ0 + w        //1+2+8

    DL,     LL,         Lr,         WL,         SL,         EL,         RL,         HL,         FL,         TL
1, 0,      0,          0,          0,          0,          0,          0,          0,          0,          0
2, 0,      0,          0,          0,          0,          0,          0,          0,          0,          0
3, 0,      0,          0,          0,          psi0,          0,          0,          0,          0,          0
4, 0,      0,          0,          psi0,       0,          0,          0,          0,          0,          0
5, 0,      0,          0,          psi0,       psi0,          0,          0,          0,          0,          0
6, 0,      psi0,          0,       psi0,          0,          0,          0,          0,          0,          0
7, 0,      psi0,          0,          0,       psi0,          0,          0,          0,          0,          0
8, 0,      0,          0,          0,          0,          0,          0,          0,          0,          0
9, 0,      0,          0,          0,          0,          0,          0,          0,          0,          0
10, 0,      0,          0,          psi0,          0,          0,          0,          0,          0,          0
11, 0,      0,          0,          0,          psi0,          0,          0,          0,          0,          0
12, 0,      psi0,          0,          0,          0,          0,          0,          0,          0,          0
13, 0,      psi0,          0,          0,          0,          0,          0,          0,          0,          0

Quasi permanent SLS

QPSLSLC1=g                          //1
QPSLSLC2=g + q*Ψ2                   //1+2
QPSLSLC3=g + q*Ψ2  + s*Ψ2           //1+2+16
QPSLSLC4=g + q*Ψ2  + w*Ψ2           //1+2+8
QPSLSLC5=g + q*Ψ2  + s*Ψ2  + w*Ψ2   //1+2+16+8
QPSLSLC6=g + s*Ψ2                   //1+16
QPSLSLC7=g + w*Ψ2                   //1+8
QPSLSLC8=g + s*Ψ2  + w*Ψ2           //1+16+8

Ψ2.q    0
Ψ2.s    0.2 (Sweden)
Ψ2.w    0

===========================================
ASCE7-10

D=DL
L=LL
l=Lr
S=SL
R=RL
W=WL
E=EL

l=Lr
========
FLC  (factored loads combination)


ASCEFLC1=1.4*D //1
ASCEFLC2=1.2*D + 1.6*L + 0.5*l //1+2+4
ASCEFLC3=1.2*D + 1.6*L + 0.5*S //1+2+16
ASCEFLC4=1.2*D + 1.6*L + 0.5*R //1+2+64
ASCEFLC5=1.2*D + 1.6*l + L  //1+2+4
ASCEFLC6=1.2*D + 1.6*S + L  //1+2+16
ASCEFLC7=1.2*D + 1.6*R + L  //1+2+64
ASCEFLC8=1.2*D + 1.6*l + 0.5*W  //1+4+8
ASCEFLC9=1.2*D + 1.6*S + 0.5*W  //1+8+16
ASCEFLC10=1.2*D + 1.6*R + 0.5*W //1+8+64
ASCEFLC11=1.2*D + 1.0*W + L + 0.5*l //1+2+4+8
ASCEFLC12=1.2*D + 1.0*W + L + 0.5*S  //1+2+8+16
ASCEFLC13=1.2*D + 1.0*W + L + 0.5*R  //1+2+8+64
ASCEFLC14=1.2*D + 1.0*E + L + 0.2*S  //1+2+16+32
ASCEFLC15=0.9*D + 1.0*W // 1+8
ASCEFLC16=0.9*D + 1.0*E //1+32


D=DL+FL
L=LL+HL+TL

for analogy to Eurocode:
ASCEFLC1=D*γg   //(1)         //γg=1.4 for DL, FL

ASCEFLC2=D*ξ + L*γq + Ψ0*l  //(2)    //ξ=1.2 for DL, FL  γq=1.6 for LL, Lr, SL, RL, HL Ψ0=0.5 for Lr, SL, RL, WL
ASCEFLC3=D*ξ + L*γq + Ψ0*S
ASCEFLC4=D*ξ + L*γq + Ψ0*R

ASCEFLC5=D*ξ + l*γq + L  //(3)
ASCEFLC6=D*ξ + S*γq + L
ASCEFLC7=D*ξ + R*γq + L

ASCEFLC8=D*ξ + l*γq + Ψ0*W
ASCEFLC9=D*ξ + S*γq + Ψ0*W
ASCEFLC10=D*ξ + R*γq + Ψ0*W

ASCEFLC11=D*ξ + W + L + Ψ0*l  //(4)
ASCEFLC12=D*ξ + W + L + Ψ0*S
ASCEFLC13=D*ξ + W + L + Ψ0*R

ASCEFLC14=D*ξ + E + L + Ψ1*S  //(5)  //Ψ1=0.2 for SL

ASCEFLC15=D*Ψ0 + W   //(6)          //Ψ0=0.9 for DL
ASCEFLC16=D*Ψ0 + E   //(7)

NL  (nominal loads combination)

ASCENLC1=D  //1
ASCENLC2=D + L //1+2
ASCENLC3=D + l  //1+4
ASCENLC4=D + S  //1+16
ASCENLC5=D + R  //1+64
ASCENLC6=D + L*Ψ2 + l*Ψ2   //1+2+4  //Ψ2=0.75 for LL, Lr, SL, RL  also HL
ASCENLC7=D + L*Ψ2 + S*Ψ2  //1+2+16
ASCENLC8=D + L*Ψ2 + R*Ψ2  //1+2+64
ASCENLC9=D + W*Ψ2    //1+8      //Ψ2=0.6 for WL
ASCENLC10=D + E*Ψ2   //1+32      //Ψ2=0.7 for EL
ASCENLC11=D + L*Ψ2 + W*Ψ1*Ψ2 + l*Ψ2   //1+2+4+8  //Ψ1=0.75 for WL
ASCENLC12=D + L*Ψ2 + W*Ψ1*Ψ2 + S*Ψ2  //1+2+8+16
ASCENLC13=D + L*Ψ2 + W*Ψ1*Ψ2 + R*Ψ2  //1+2+8+64
ASCENLC14=D + L*Ψ2 + E*Ψ1*Ψ2 + S*Ψ2  //1+2+16+32  //Ψ1=0.75 for EL
ASCENLC15=D*Ψ1 + W*Ψ2  //1+8       // Ψ1=0.6 for DL  also FL
ASCENLC16=D*Ψ1 + E*Ψ2  //1+32


WDLC   (Wind Drift Load Combinations)  //IGNORED NOW

Wind drift can be check as per load combinations specified in the ASCE7-10 commentary (CC-3) as:

ASCEWDLC1=D + L*Ψ1 + W*Ψ1  //1+2+8  // Ψ1=0.5 for L  //Ψ1=0.75 for W but should be 0.7

==================================================
IBC

D=DL
L=LL
l=Lr
S=SL
R=RL
W=WL
E=EL
H=HL
F=FL

l=Lr
===
FLC  (factored loads combination)


IBCFLC1=D*γg + F*γq  //(1)       //1+256                 //γg=1.4  for DL, FL

IBCFLC2=D*ξ + F*ξ + L*yq + H*yq + l*Ψ0  //(2) //1+2+4+128+256  //ξ=1.2 for DL, FL, γq=1.6 for LL, HL, SL, RL
IBCFLC3=D*ξ + F*ξ + L*yq + H*yq + S*Ψ0        //1+2+16+128+256  //γq=1.6 for L, l, H, R, S, γq=1.0 for W  Ψ0=0.5 for l, S, R, W
IBCFLC4=D*ξ + F*ξ + L*yq + H*yq + R*Ψ0        //1+2+64+128+256

IBCFLC5=D*ξ + F*ξ + l*yq + H*yq + L*Ψ0  //(3)      //1+2+4+128+256    //Ψ0=0.5 or 1.0 for LL, assumed 0.5 so "other live loads
IBCFLC6=D*ξ + F*ξ + S*yq + H*yq + L*Ψ0        //1+2+16+128+256
IBCFLC7=D*ξ + F*ξ + R*yq + H*yq + L*Ψ0        //1+2+64+128+256

IBCFLC8=D*ξ + F*ξ + l*yq + H*yq + W*Ψ0          //1+4+8+128+256
IBCFLC9=D*ξ + F*ξ + S*yq + H*yq + W*Ψ0          //1+8+16+128+256
IBCFLC10=D*ξ + F*ξ + R*yq + H*yq + W*Ψ0         //1+8+64+128+256

IBCFLC11=D*ξ + F*ξ + W + L*Ψ0 + H*yq + l*Ψ0  //(4)   //1+2+4+8+128+256
IBCFLC12=D*ξ + F*ξ + W + L*Ψ0 + H*yq + S*Ψ0     //1+2+8+16+128+256
IBCFLC13=D*ξ + F*ξ + W + L*Ψ0 + H*yq + R*Ψ0     //1+2+8+64+128+256

IBCFLC14=D*ξ + F*ξ + E + L*Ψ0 + H*yq + S*Ψ1  //(5)   //1+2+16+32+128+256  //Ψ1=0.7 or 0.2 for S  assumed 0.2 so "other roof configurations"

IBCFLC15=D*Ψ0 + W + H*yq //(6)  //1+8+128          //Ψ0=0.9 for D and F
IBCFLC16=D*Ψ0 + F*Ψ0 + E + H*yq  //(7) //  1+32+128+256  //Ψ0=0.6 for F

where:
Ψ0 for L= 1 for places of public assembly live load in excess of 100 pounds per square foot (4.79 kN/m2), and parking garages
Ψ0 for L= 0.5 for other live loads
Ψ1 for S= 0.7 for roof configurations (such as saw tooth) that do not shed snow off the structure
Ψ1 for S= 0.2 for other roof combinations

BLC   (Basic load combinations)

IBCBLC1=D + F  //1+256
IBCBLC2=D + H + F + L //1+2+128+256
IBCBLC3=D + H + F + l //1+4+128+256
IBCBLC4=D + H + F + S  //1+16+128+256
IBCBLC5=D + H + F + R  //1+64+128+256
IBCBLC6=D + H + F + L*Ψ2 + l*Ψ2    //1+2+4+128+256             //Ψ2=0.75 for L,l,S,R
IBCBLC7=D + H + F + L*Ψ2 + S*Ψ2    //1+2+16+128+256
IBCBLC8=D + H + F + L*Ψ2 + R*Ψ2    //1+2+64+128+256
IBCBLC9=D + H + F + W*Ψ2  //1+8+128+256
IBCBLC10=D + H + F + E*Ψ2  //1+32+128+256
IBCBLC11=D + H + F + W*Ψ1*Ψ2 + L*Ψ2 + l*Ψ2  //1+2+4+8+128+256    //Ψ1=0.75 for W, E
IBCBLC12=D + H + F + W*Ψ1*Ψ2 + L*Ψ2 + S*Ψ2  //1+2+8+16+128+256
IBCBLC13=D + H + F + W*Ψ1*Ψ2 + L*Ψ2 + R*Ψ2  //1+2+8+64+128+256
IBCBLC14=D + H + F + E*Ψ1*Ψ2 + L*Ψ2 + S*Ψ2   //1+2+16+32+128+256   //Ψ2=0.7 for E
IBCBLC15=D*Ψ2 + W*Ψ2 + H   //1+8+128                     // Ψ2=0.6 for D  Ψ2=0.6 for W, F
IBCBLC16=D*Ψ2 + F*Ψ2 + E*Ψ2 + H  //1+32+128+256

ABLC  (Alternative basic load combination)   //IGNORED NOW

IBCABLC1=D + L + l //1+2+4
IBCABLC2=D + L + S //1+2+16
IBCABLC3=D + L + R //1+2+64
IBCABLC4=D + L + 0.6*ω*W  //1+2+8   //  Ψ2=0.6 for W
IBCABLC5=D + L + 0.6*ω*W + 0.5*S  //1+2+8+16     Ψ2=0.6 for W   Ψ0=0.5 for l, S, R, W
IBCABLC6=D + L + S + 0.5*0.6*ω*W  //1+2+8+16
IBCABLC7=D + L + S + 0.7143*E     //1+2+16+32    //Ψ2=0.7 for E  and  //Ψ1=0.75 for W, E
IBCABLC8=0.9*D + + 0.7143*E   //1+32    //Ψ0=0.9 for D and F

 */

