//
// Created by Marek on 1/18/24.
//

#ifndef LIBFUN_PL_H_XDNDFILE_H
#define LIBFUN_PL_H_XDNDFILE_H
//-----------------------------------------------------------------------------
// xdndfile.h
//
//  X11 drag/drop processor definition.
//
// Copyright (c) 2013 - No Fun Farms A.K.A. www.smegware.com
//
//  All Smegware software is free; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This software is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  GNU General Public License for more details.
//
//-----------------------------------------------------------------------------
//
// History...
//
//   $Source$
//   $Author$
// $Revision$
//
// $Log$
//
//-----------------------------------------------------------------------------
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/keysym.h>

#define XDND_VERSION 3

//-----------------------------------------------------------------------------

typedef struct {
    Display *display;
    Window window;
    Window src_window;
    int src_version;
    time_t time;
    Atom version;               //= XDND_VERSION;
    Atom XdndAware;             //= XInternAtom(dnd->display, "XdndAware", False);
    Atom XdndSelection;         //= XInternAtom(dnd->display, "XdndSelection", False);
    Atom XdndEnter;             //= XInternAtom(dnd->display, "XdndEnter", False);
    Atom XdndLeave;             //= XInternAtom(dnd->display, "XdndLeave", False);
    Atom XdndPosition;          //= XInternAtom(dnd->display, "XdndPosition", False);
    Atom XdndDrop;              //= XInternAtom(dnd->display, "XdndDrop", False);
    Atom XdndFinished;          //= XInternAtom(dnd->display, "XdndFinished", False);
    Atom XdndStatus;            //= XInternAtom(dnd->display, "XdndStatus", False);
    Atom XdndActionCopy;        //= XInternAtom(dnd->display, "XdndActionCopy", False);
    Atom XdndActionMove;        //= XInternAtom(dnd->display, "XdndActionMove", False);
    Atom XdndActionLink;        //= XInternAtom(dnd->display, "XdndActionLink", False);
    Atom XdndActionAsk;         //= XInternAtom(dnd->display, "XdndActionAsk", False);
    Atom XdndActionPrivate;     //= XInternAtom(dnd->display, "XdndActionPrivate",False);
    Atom XdndTypeList;          //= XInternAtom(dnd->display, "XdndTypeList", False);
    Atom XdndActionList;        //= XInternAtom(dnd->display, "XdndActionList", False);
    Atom XdndActionDescription; //= XInternAtom(dnd->display, "XdndActionDescription", False);
    Atom text_uri_list;         //= XInternAtom(dnd->display, "text/uri-list", False);
    Atom utf8_string;           //= XInternAtom(dnd->display, "UTF8-STRING", False);
    Atom compound_text;         //= XInternAtom(dnd->display, "COMPOUND_TEXT", False);
    Atom text;                  //= XInternAtom(dnd->display, "TEXT", False);
    Atom string;                //= XInternAtom(dnd->display, "STRING", False);
    Atom text_plain_utf_8;      //= XInternAtom(dnd->display, "text/plain;charset=utf-8", False);
    Atom text_plain;            //= XInternAtom(dnd->display, "text/plain", False);
    Atom TypeList[64];
} AWIdnd, *pAWIdnd;

//-----------------------------------------------------------------------------

extern void xdnd_init_file(Display*, Window, pAWIdnd);
extern void xdnd_set_dnd_aware(pAWIdnd);
extern void xdnd_set_dnd_unaware(pAWIdnd);
extern void xdnd_get_type_list(pAWIdnd);
extern void xdnd_convert_selection(pAWIdnd, XEvent*, Atom);
extern void xdnd_get_selection(pAWIdnd, XEvent*, Atom, char**);
extern void xdnd_recv_enter(pAWIdnd, XEvent*);
extern void xdnd_recv_position(pAWIdnd, XEvent*);
extern void xdnd_recv_leave(pAWIdnd, XEvent*);
extern void xdnd_recv_drop(pAWIdnd, XEvent*);
extern void xdnd_recv_status(pAWIdnd, XEvent*);
extern void xdnd_send_status(pAWIdnd, int, int, unsigned, unsigned, unsigned, unsigned, Atom);
extern void xdnd_send_finished(pAWIdnd, Atom);

//-----------------------------------------------------------------------------
// end: xdndfile.h
//
#endif //LIBFUN_PL_H_XDNDFILE_H
