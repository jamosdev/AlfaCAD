//
// "$Id: editor.cxx 6518 2008-11-11 22:31:26Z spitzak $"
//
// A simple text editor program for the Fast Light Tool Kit (FLTK).
//
// This program is described in Chapter 4 of the FLTK Programmer's Guide.
//
// Copyright 1998-2006 by Bill Spitzak and others.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
//

//
// Include necessary headers...
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include <FL/Fl.H>
//#include <FL/fl_events.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Window.H>
#include <FL/fl_ask.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Menu.H>
#include <FL/Fl_Menu_.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Overlay_Window.H>
#include <FL/Fl_Multi_Label.H>
#include <FL/Enumerations.H>

#define fltk  Fl

int                changed = 0;
char               filename[256] = "";
char               title[256];
Fl_Text_Buffer     *textbuf = 0;

class EditorWindow : public Fl_Window {
public:
    EditorWindow(int w, int h, const char* t);
    ~EditorWindow();

    //Variables
    //Our text editor window will need some variables to keep track of stuff. In addition we will use some global variables for stuff that is shared between all editor windows, such as the search string:

    Fl_Window          *replace_dlg;
    Fl_Input           *replace_find;
    Fl_Input           *replace_with;
    Fl_Button          *replace_all;
    Fl_Return_Button   *replace_next;
    Fl_Button          *replace_cancel;

    Fl_Text_Editor     *editor;
    char               search[256];
};



//int                changed = 0;
//char               filename[256] = "";
//char               title[256];
//Fl_TextBuffer     *textbuf = 0;


// Syntax highlighting stuff...
Fl_Text_Buffer     *stylebuf = 0;
Fl_Text_Display::Style_Table_Entry
        styletable[] = { // Style table
        { FL_BLACK,           FL_COURIER,        12 }, // A - Plain
        { FL_DARK_GREEN,      FL_COURIER_ITALIC, 12 }, // B - Line comments
        { FL_DARK_GREEN,      FL_COURIER_ITALIC, 12 }, // C - Block comments
        { FL_BLUE,            FL_COURIER,        12 }, // D - Strings
        { FL_DARK_RED,        FL_COURIER,        12 }, // E - Directives
        { FL_DARK_RED,        FL_COURIER_BOLD,   12 }, // F - Types
        { FL_BLUE,            FL_COURIER_BOLD,   12/*, Fl_TextDisplay::ATTR_UNDERLINE*/ }  // G - Keywords
};
const char         *code_keywords[] = { // List of known C/C++ keywords...
        "and",
        "and_eq",
        "asm",
        "bitand",
        "bitor",
        "break",
        "case",
        "catch",
        "compl",
        "continue",
        "default",
        "delete",
        "do",
        "else",
        "false",
        "for",
        "goto",
        "if",
        "new",
        "not",
        "not_eq",
        "operator",
        "or",
        "or_eq",
        "return",
        "switch",
        "template",
        "this",
        "throw",
        "true",
        "try",
        "using",
        "while",
        "xor",
        "xor_eq"
};
const char         *code_types[] = {    // List of known C/C++ types...
        "auto",
        "bool",
        "char",
        "class",
        "const",
        "const_cast",
        "double",
        "dynamic_cast",
        "enum",
        "explicit",
        "extern",
        "float",
        "friend",
        "inline",
        "int",
        "long",
        "mutable",
        "namespace",
        "private",
        "protected",
        "public",
        "register",
        "short",
        "signed",
        "sizeof",
        "static",
        "static_cast",
        "struct",
        "template",
        "typedef",
        "typename",
        "union",
        "unsigned",
        "virtual",
        "void",
        "volatile"
};


//
// 'compare_keywords()' - Compare two keywords...
//

extern "C" {
int
compare_keywords(const void *a,
                 const void *b) {
    return (strcmp(*((const char **)a), *((const char **)b)));
}
}

//
// 'style_parse()' - Parse text and produce style data.
//

void
style_parse(const char *text,
            char       *style,
            int        length) {
    char       current;
    int        col;
    int        last;
    char       buf[255],
            *bufptr;
    const char *temp;

    // Style letters:
    //
    // A - Plain
    // B - Line comments
    // C - Block comments
    // D - Strings
    // E - Directives
    // F - Types
    // G - Keywords

    for (current = *style, col = 0, last = 0; length > 0; length --, text ++) {
        if (current == 'B' || current == 'F' || current == 'G') current = 'A';
        if (current == 'A') {
            // Check for directives, comments, strings, and keywords...
            if (col == 0 && *text == '#') {
                // Set style to directive
                current = 'E';
            } else if (strncmp(text, "//", 2) == 0) {
                current = 'B';
                for (; length > 0 && *text != '\n'; length --, text ++) *style++ = 'B';

                if (length == 0) break;
            } else if (strncmp(text, "/*", 2) == 0) {
                current = 'C';
            } else if (strncmp(text, "\\\"", 2) == 0) {
                // Quoted quote...
                *style++ = current;
                *style++ = current;
                text ++;
                length --;
                col += 2;
                continue;
            } else if (*text == '\"') {
                current = 'D';
            } else if (!last && (islower(*text) || *text == '_')) {
                // Might be a keyword...
                for (temp = text, bufptr = buf;
                     (islower(*temp) || *temp == '_') && bufptr < (buf + sizeof(buf) - 1);
                     *bufptr++ = *temp++);

                if (!islower(*temp) && *temp != '_') {
                    *bufptr = '\0';

                    bufptr = buf;

                    if (bsearch(&bufptr, code_types,
                                sizeof(code_types) / sizeof(code_types[0]),
                                sizeof(code_types[0]), compare_keywords)) {
                        while (text < temp) {
                            *style++ = 'F';
                            text ++;
                            length --;
                            col ++;
                        }

                        text --;
                        length ++;
                        last = 1;
                        continue;
                    } else if (bsearch(&bufptr, code_keywords,
                                       sizeof(code_keywords) / sizeof(code_keywords[0]),
                                       sizeof(code_keywords[0]), compare_keywords)) {
                        while (text < temp) {
                            *style++ = 'G';
                            text ++;
                            length --;
                            col ++;
                        }

                        text --;
                        length ++;
                        last = 1;
                        continue;
                    }
                }
            }
        } else if (current == 'C' && strncmp(text, "*/", 2) == 0) {
            // Close a C comment...
            *style++ = current;
            *style++ = current;
            text ++;
            length --;
            current = 'A';
            col += 2;
            continue;
        } else if (current == 'D') {
            // Continuing in string...
            if (strncmp(text, "\\\"", 2) == 0) {
                // Quoted end quote...
                *style++ = current;
                *style++ = current;
                text ++;
                length --;
                col += 2;
                continue;
            } else if (*text == '\"') {
                // End quote...
                *style++ = current;
                col ++;
                current = 'A';
                continue;
            }
        }

        // Copy style info...
        if (current == 'A' && (*text == '{' || *text == '}')) *style++ = 'G';
        else *style++ = current;
        col ++;

        last = isalnum(*text) || *text == '_' || *text == '.';

        if (*text == '\n') {
            // Reset column and possibly reset the style
            col = 0;
            if (current == 'B' || current == 'E') current = 'A';
        }
    }
}


//
// 'style_init()' - Initialize the style buffer...
//

void
style_init(void) {
    char *style = new char[textbuf->length() + 1];
    const char *text = textbuf->text();

    memset(style, 'A', textbuf->length());
    style[textbuf->length()] = '\0';

    if (!stylebuf) stylebuf = new Fl_Text_Buffer(textbuf->length());

    style_parse(text, style, textbuf->length());

    stylebuf->text(style);
    delete[] style;
}


//
// 'style_unfinished_cb()' - Update unfinished styles.
//

void
style_unfinished_cb(int, void*) {
}


//
// 'style_update()' - Update the style buffer...
//

void
style_update(int        pos,        // I - Position of update
             int        nInserted,  // I - Number of inserted chars
             int        nDeleted,   // I - Number of deleted chars
             int        /*nRestyled*/,  // I - Number of restyled chars
             const char * /*deletedText*/,// I - Text that was deleted
             void       *cbArg) {   // I - Callback data
    int   start,              // Start of text
    end;                // End of text
    char  last,               // Last style on line
    *style,             // Style data
    *text;              // Text data


    // If this is just a selection change, just unselect the style buffer...
    if (nInserted == 0 && nDeleted == 0) {
        stylebuf->unselect();
        return;
    }

    // Track changes in the text buffer...
    if (nInserted > 0) {
        // Insert characters into the style buffer...
        style = new char[nInserted + 1];
        memset(style, 'A', nInserted);
        style[nInserted] = '\0';

        stylebuf->replace(pos, pos + nDeleted, style);
        delete[] style;
    } else {
        // Just delete characters in the style buffer...
        stylebuf->remove(pos, pos + nDeleted);
    }

    // Select the area that was just updated to avoid unnecessary
    // callbacks...
    stylebuf->select(pos, pos + nInserted - nDeleted);

    // Re-parse the changed region; we do this by parsing from the
    // beginning of the previous line of the changed region to the end of
    // the line of the changed region...  Then we check the last
    // style character and keep updating if we have a multi-line
    // comment character...
    start = textbuf->line_start(pos);
//  if (start > 0) start = textbuf->line_start(start - 1);
    end   = textbuf->line_end(pos + nInserted);
    text  = textbuf->text_range(start, end);
    style = stylebuf->text_range(start, end);
    if (start==end)
        last = 0;
    else
        last  = style[end - start - 1];

//  printf("start = %d, end = %d, text = \"%s\", style = \"%s\", last='%c'...\n",
//         start, end, text, style, last);

    style_parse(text, style, end - start);

//  printf("new style = \"%s\", new last='%c'...\n",
//         style, style[end - start - 1]);

    stylebuf->replace(start, end, style);
    ((Fl_Text_Editor *)cbArg)->redisplay_range(start, end);

    if (start==end || last != style[end - start - 1]) {
//    printf("Recalculate the rest of the buffer style\n");
        // Either the user deleted some text, or the last character
        // on the line changed styles, so reparse the
        // remainder of the buffer...
        free(text);
        free(style);

        end   = textbuf->length();
        text  = textbuf->text_range(start, end);
        style = stylebuf->text_range(start, end);

        style_parse(text, style, end - start);

        stylebuf->replace(start, end, style);
        ((Fl_Text_Editor *)cbArg)->redisplay_range(start, end);
    }

    free(text);
    free(style);
}


// Editor window functions and class...
void save_cb();
void saveas_cb();
void find2_cb(Fl_Widget*, void*);
void replall_cb(Fl_Widget*, void*);
void replace2_cb(Fl_Widget*, void*);
void replcan_cb(Fl_Widget*, void*);

class Editor_Window : public Fl_Window {
public:
    Editor_Window(int w, int h, const char* t);
    ~Editor_Window();

    Fl_Window          *replace_dlg;
    Fl_Input           *replace_find;
    Fl_Input           *replace_with;
    Fl_Button          *replace_all;
    Fl_Return_Button   *replace_next;
    Fl_Button          *replace_cancel;

    Fl_Text_Editor     *editor;
    char               search[256];
};

EditorWindow::EditorWindow(int w, int h, const char* t) : Fl_Window(w, h, t) {
    replace_dlg = new Fl_Window(300, 105, "Replace");
    replace_dlg->begin();
    replace_find = new Fl_Input(80, 10, 210, 25, "Find:");
    replace_find->align(FL_ALIGN_LEFT);

    replace_with = new Fl_Input(80, 40, 210, 25, "Replace:");
    replace_with->align(FL_ALIGN_LEFT);

    replace_all = new Fl_Button(10, 70, 90, 25, "Replace All");
    replace_all->callback((Fl_Callback *)replall_cb, this);

    replace_next = new Fl_Return_Button(105, 70, 120, 25, "Replace Next");
    replace_next->callback((Fl_Callback *)replace2_cb, this);

    replace_cancel = new Fl_Button(230, 70, 60, 25, "Cancel");
    replace_cancel->callback((Fl_Callback *)replcan_cb, this);
    replace_dlg->end();
    replace_dlg->set_non_modal();
    editor = 0;
    *search = (char)0;
}

EditorWindow::~EditorWindow() {
    delete replace_dlg;
}

int check_save(void) {
    if (!changed) return 1;

    int r = fl_choice("The current file has not been saved.\n"
                         "Would you like to save it now?",
                         "Cancel", "Save", "Don't Save");

    if (r == 1) {
        save_cb(); // Save the file...
        return !changed;
    }

    return (r == 2) ? 1 : 0;
}

int loading = 0;
void load_file(const char *newfile, int ipos) {
    loading = 1;
    int insert = (ipos != -1);
    changed = insert;
    if (!insert) strcpy(filename, "");
    int r;
    if (!insert) r = textbuf->loadfile(newfile);
    else r = textbuf->insertfile(newfile, ipos);
    if (r) {
        if (fl_ask("File '%s' does not exit. Do you want to create one?", newfile))
            strcpy(filename, newfile);
        else
            strcpy(filename, "");
    } // if
    else
    if (!insert) strcpy(filename, newfile);
    loading = 0;
    textbuf->call_modify_callbacks();
}

void save_file(const char *newfile) {
    if (textbuf->savefile(newfile))
        fl_alert("Error writing to file \'%s\':\n%s.", newfile, strerror(errno));
    else
        strcpy(filename, newfile);
    changed = 0;
    textbuf->call_modify_callbacks();
}

void copy_cb(Fl_Widget*, void* v) {
    EditorWindow* e = (EditorWindow*)v;
    Fl_Text_Editor::kf_copy(0, e->editor);
}

void cut_cb(Fl_Widget*, void* v) {
    EditorWindow* e = (EditorWindow*)v;
    Fl_Text_Editor::kf_cut(0, e->editor);
}

void delete_cb(Fl_Widget*, void*) {
    textbuf->remove_selection();
}

void find_cb(Fl_Widget* w, void* v) {
    EditorWindow* e = (EditorWindow*)v;
    const char *val;

    val = fl_input("Search String:", e->search);
    if (val != NULL) {
        // User entered a string - go find it!
        strcpy(e->search, val);
        find2_cb(w, v);
    }
}

void find2_cb(Fl_Widget* w, void* v) {
    EditorWindow* e = (EditorWindow*)v;
    if (e->search[0] == '\0') {
        // Search string is blank; get a new one...
        find_cb(w, v);
        return;
    }

    int pos = e->editor->insert_position();
    int found = textbuf->search_forward(pos, e->search, &pos);
    if (found) {
        // Found a match; select and update the position...
        textbuf->select(pos, pos+strlen(e->search));
        e->editor->insert_position(pos+strlen(e->search));
        e->editor->show_insert_position();
    }
    else fl_alert("No occurrences of \'%s\' found!", e->search);
}

void set_title(Fl_Window* w) {
    if (filename[0] == '\0') strcpy(title, "Untitled.txt");
    else {
        char *slash;
        slash = strrchr(filename, '/');
#ifdef WIN32
        if (slash == NULL) slash = strrchr(filename, '\\');
#endif
        if (slash != NULL) strcpy(title, slash + 1);
        else strcpy(title, filename);
    }

    if (changed) strcat(title, " (modified)");

    w->label(title);
}

void changed_cb(int, int nInserted, int nDeleted,int, const char*, void* v) {
    if ((nInserted || nDeleted) && !loading) changed = 1;
    EditorWindow *w = (EditorWindow *)v;
    set_title(w);
    if (loading) w->editor->show_insert_position();
}

void new_cb(Fl_Widget*, void*) {
    if (!check_save()) return;

    filename[0] = '\0';
    textbuf->select(0, textbuf->length());
    textbuf->remove_selection();
    changed = 0;
    textbuf->call_modify_callbacks();
}

void open_cb(Fl_Widget*, void*) {
    if (!check_save()) return;

    const char *newfile = fl_file_chooser("Open File?", "*", filename);
    if (newfile != NULL) load_file(newfile, -1);
}

void insert_cb(Fl_Widget*, void *v) {
    const char *newfile = fl_file_chooser("Insert File?", "*", filename);
    EditorWindow *w = (EditorWindow *)v;
    if (newfile != NULL) load_file(newfile, w->editor->insert_position());
}

void paste_cb(Fl_Widget*, void* v) {
    EditorWindow* e = (EditorWindow*)v;
    Fl_Text_Editor::kf_paste(0, e->editor);
}

int num_windows = 0;

void close_cb(Fl_Widget*, void* v) {
    Fl_Window* w = (Fl_Window*)v;
    if (num_windows == 1 && !check_save()) {
        return;
    }

    w->hide();
    w->resize(0,0,0,0);
    w->redraw();
    textbuf->remove_modify_callback(changed_cb, w);
    delete w;
    num_windows--;
    //if (!num_windows) exit(0);
}

void quit_cb(Fl_Widget*, void*) {
    if (changed && !check_save())
        return;

    exit(0);
}

void replace_cb(Fl_Widget*, void* v) {
    EditorWindow* e = (EditorWindow*)v;
    e->replace_dlg->show();
}

void replace2_cb(Fl_Widget*, void* v) {
    EditorWindow* e = (EditorWindow*)v;
    const char *find = e->replace_find->label();
    const char *replace = e->replace_with->label();

    if (find[0] == '\0') {
        // Search string is blank; get a new one...
        e->replace_dlg->show();
        return;
    }

    e->replace_dlg->hide();

    int pos = e->editor->insert_position();
    int found = textbuf->search_forward(pos, find, &pos);

    if (found) {
        // Found a match; update the position and replace text...
        textbuf->select(pos, pos+strlen(find));
        textbuf->remove_selection();
        textbuf->insert(pos, replace);
        textbuf->select(pos, pos+strlen(replace));
        e->editor->insert_position(pos+strlen(replace));
        e->editor->show_insert_position();
    }
    else fl_alert("No occurrences of \'%s\' found!", find);
}

void replall_cb(Fl_Widget*, void* v) {
    EditorWindow* e = (EditorWindow*)v;
    const char *find = e->replace_find->label();
    const char *replace = e->replace_with->label();

    find = e->replace_find->label();
    if (find[0] == '\0') {
        // Search string is blank; get a new one...
        e->replace_dlg->show();
        return;
    }

    e->replace_dlg->hide();

    e->editor->insert_position(0);
    int times = 0;

    // Loop through the whole string
    for (int found = 1; found;) {
        int pos = e->editor->insert_position();
        found = textbuf->search_forward(pos, find, &pos);

        if (found) {
            // Found a match; update the position and replace text...
            textbuf->select(pos, pos+strlen(find));
            textbuf->remove_selection();
            textbuf->insert(pos, replace);
            e->editor->insert_position(pos+strlen(replace));
            e->editor->show_insert_position();
            times++;
        }
    }

    if (times) fl_message("Replaced %d occurrences.", times);
    else fl_alert("No occurrences of \'%s\' found!", find);
}

void replcan_cb(Fl_Widget*, void* v) {
    EditorWindow* e = (EditorWindow*)v;
    e->replace_dlg->hide();
}

void save_cb() {
    if (filename[0] == '\0') {
        // No filename - get one!
        saveas_cb();
        return;
    }
    else save_file(filename);
}

void saveas_cb() {
    const char *newfile = fl_file_chooser("Save File As?", "*", filename);
    if (newfile != NULL) save_file(newfile);
}

Fl_Window* new_view();

void view_cb(Fl_Widget*, void*) {
    Fl_Window* w = new_view();
    w->show();
}

// Add an image in front of item's text
int AddItemToMenu(Fl_Menu_   *menu,                   // menu to add item to
                  const char  *labeltext,              // label text
                  int         shortcut,                // shortcut (e.g. FL_COMMAND+'a')
                  Fl_Callback *cb,                     // callback to invoke
                  void        *userdata,               // userdata for callback
                  Fl_Pixmap*  pixmap,                  // image (if any) to add to item
                  int         flags=0) {               // menu flags (e.g. FL_MENU_DIVIDER..)
    // Add a new menu item
    int i = menu->add(labeltext, shortcut, cb, userdata, flags);

    if ( !pixmap ) return i;
    Fl_Menu_Item *item = (Fl_Menu_Item*)&(menu->menu()[i]);

    // Create a multi label, assign it an image + text
    Fl_Multi_Label *ml = new Fl_Multi_Label;

    // Left side of label is image
    ml->typea  = _FL_IMAGE_LABEL;
    ml->labela = (const char*)pixmap;

    // Right side of label is text
    ml->typeb  = FL_NORMAL_LABEL;
    ml->labelb = item->label();

    // Assign multilabel to item.
    // Note: There are two documented ways to achieve this. Both of them
    // are supported, but one of them is commented out intentionally.

    // item->label(FL_MULTI_LABEL, (const char *)ml);
    ml->label(item);

    return i;
}

// Handle the different menu items..
void Menu_CB(Fl_Widget *w, void* data) {
    const char *itemname = (const char*)data;   // "New", "Open", etc
    if ( strcmp(itemname, "Quit") == 0 ) {      // handle Quit
        w->window()->hide();
    } else {                                    // just show a message for other items
        fl_message("'%s' would happen here", itemname);
    }
}

static void build_menus(Fl_Menu_ * menu, Fl_Widget *w) {
    //Fl_Group * g;
    //menu->user_data(w);
    //menu->begin();
    //g = new Fl_Item_Group( "&File" );
    //g->begin();
    //new Fl_Menu_Item( "&New File",        0, (Fl_Callback *)new_cb );
    // Add items with LABELS AND IMAGES using Fl_Multi_Label..
    AddItemToMenu(menu, "File/New",  FL_COMMAND+'n', Menu_CB, (void*)"&New",  NULL); //&L_document_pixmap);
    //new Fl_Item( "&Open File...",    Fl_COMMAND + 'O', (Fl_Callback *)open_cb );
    AddItemToMenu(menu, "File/Open", FL_COMMAND+'o', Menu_CB, (void*)"&Open", NULL, FL_MENU_DIVIDER); //&L_folder_pixmap, FL_MENU_DIVIDER);
    //new Fl_Item( "&Insert File...",  Fl_COMMAND + 'I', (Fl_Callback *)insert_cb);
    //new Fl_Divider();
    //new Fl_Item( "&Save File",       Fl_COMMAND + 'S', (Fl_Callback *)save_cb );
    AddItemToMenu(menu, "File/Save", FL_COMMAND+'o', Menu_CB, (void*)"&Save", NULL); //&L_folder_pixmap,
    //new Fl_Item( "Save File &As...", Fl_COMMAND + Fl_SHIFT + 'S', (Fl_Callback *)saveas_cb);
    //new Fl_Divider();
    AddItemToMenu(menu, "File/Save As", FL_COMMAND+'o', Menu_CB, (void*)"Save &As", NULL); //&L_folder_pixmap,
    //new Fl_Item( "New &View", Fl_ACCELERATOR + 'V', (Fl_Callback *)view_cb, 0 );
    AddItemToMenu(menu, "File/New View", FL_COMMAND+'o', Menu_CB, (void*)"Mew &View", NULL); //&L_folder_pixmap,
    //new Fl_Item( "&Close View", Fl_COMMAND + 'W', (Fl_Callback *)close_cb);
    //new Fl_Divider();
    AddItemToMenu(menu, "File/Close View", FL_COMMAND+'o', Menu_CB, (void*)"Close View", NULL); //&L_folder_pixmap,
    //new Fl_Item( "E&xit", Fl_COMMAND + 'Q', (Fl_Callback *)quit_cb, 0 );
    //g->end();
    AddItemToMenu(menu, "File/Exit", FL_COMMAND+'o', Menu_CB, (void*)"Quit", NULL, FL_MENU_DIVIDER); //&L_folder_pixmap,
    //g = new Fl_ItemGroup( "&Edit" );
    //g->begin();
    AddItemToMenu(menu, "Edit/Cut", FL_COMMAND+'o', Menu_CB, (void*)"Cu&t", NULL); //&L_folder_pixmap,
    //new Fl_Item( "Cu&t",        Fl_COMMAND + 'X', (Fl_Callback *)cut_cb );
    AddItemToMenu(menu, "Edit/Copy", FL_COMMAND+'o', Menu_CB, (void*)"&Copy", NULL); //&L_folder_pixmap,
    //new Fl_Item( "&Copy",       Fl_COMMAND + 'C', (Fl_Callback *)copy_cb );
    AddItemToMenu(menu, "Edit/Paste", FL_COMMAND+'o', Menu_CB, (void*)"&Paste", NULL); //&L_folder_pixmap,
    //new Fl_Item( "&Paste",      Fl_COMMAND + 'V', (Fl_Callback *)paste_cb );
    AddItemToMenu(menu, "Edit/Delete", FL_COMMAND+'o', Menu_CB, (void*)"&Delete", NULL); //&L_folder_pixmap,
    //new Fl_Item( "&Delete",     0, (Fl_Callback *)delete_cb );
    //g->end();
    //g = new Fl_ItemGroup( "&Search" );
    //g->begin();
    AddItemToMenu(menu, "Search/Find", FL_COMMAND+'o', Menu_CB, (void*)"&Find", NULL); //&L_folder_pixmap,
    //new Fl_Item( "&Find...",       Fl_COMMAND + 'F', (Fl_Callback *)find_cb );
    AddItemToMenu(menu, "Search/Find Again", FL_COMMAND+'o', Menu_CB, (void*)"F&ind Again", NULL); //&L_folder_pixmap,
    //new Fl_Item( "F&ind Again",    Fl_COMMAND + 'G', find2_cb );
    AddItemToMenu(menu, "Search/Replace", FL_COMMAND+'o', Menu_CB, (void*)"&Replace", NULL); //&L_folder_pixmap,
    //new Fl_Item( "&Replace...",    Fl_COMMAND + 'R', replace_cb );
    AddItemToMenu(menu, "Search/Replace Again", FL_COMMAND+'o', Menu_CB, (void*)"Re&place Again", NULL); //&L_folder_pixmap,
    //new Fl_Item( "Re&place Again", Fl_COMMAND + 'T', replace2_cb );
    //g->end();
    //menu->end();
}

Fl_Window* new_view() {
    EditorWindow* w = new EditorWindow(660, 400, title);
    w->begin();
    Fl_Menu_Bar* m = new Fl_Menu_Bar(0, 0, 660, 21);
    build_menus(m,w);
    w->editor = new Fl_Text_Editor(0, 21, 660, 379);
    w->editor->buffer(textbuf);
    w->editor->highlight_data(stylebuf, styletable,
                              sizeof(styletable) / sizeof(styletable[0]),
                              'A', style_unfinished_cb, 0);
    w->editor->textfont(FL_COURIER);
    w->end();
    w->resizable(w->editor);
    w->callback((Fl_Callback *)close_cb, w);

    w->editor->linenumber_width(60);
    w->editor->wrap_mode(true, 0);
    w->editor->cursor_style(Fl_Text_Display::BLOCK_CURSOR);
    // w->editor->insert_mode(false);

    textbuf->add_modify_callback(style_update, w->editor);
    textbuf->add_modify_callback(changed_cb, w);
    textbuf->call_modify_callbacks();
    num_windows++;
    w->end();
    return w;
}

//int main(int argc, char **argv)
char * tinyfd_editBox_(char const * aTitle,
                      char const * aText,
                      char const * aParams) /* "" , if NULL it's default */
{

    textbuf = new Fl_Text_Buffer(0);
    style_init();

    Fl_Window* window = new_view();

    //window->show(1, argv);

    window->show();

   // if (argc > 1) {
       window->label("AlfaCAD Edit text");
     //   load_file(argv[1], -1);
    //}

    Fl::run();

    return "";
}

//
// End of "$Id: editor.cxx 6518 2008-11-11 22:31:26Z spitzak $".
//