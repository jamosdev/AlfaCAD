//
// Created by marek on 9/2/24.
//

#ifndef LIBFUN_PL_H_O_ANIMATE_DYNAMICS_H
#define LIBFUN_PL_H_O_ANIMATE_DYNAMICS_H

extern void Animate_dynamics(void);

#define MAX_ANIM_BLOCKS 1000

typedef struct{
    char *adp;
    char *adk;
    unsigned char flag;
    unsigned char mode;
    float x;
    float y;
    char *type;
} ANIM_BLOCKS;


#endif //LIBFUN_PL_H_O_ANIMATE_DYNAMICS_H
