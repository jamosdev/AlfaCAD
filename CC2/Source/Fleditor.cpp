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

#include <FL/Fl.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Overlay_Window.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_File_Chooser.H>

Fl_Text_Buffer *buf;

void cb(Fl_Widget *w, void *data) {
    Fl_File_Chooser *chooser = new Fl_File_Chooser(
            ".", "*.{txt,cpp,c}", Fl_File_Chooser::SINGLE, "MyDialog");
    chooser->show();
    while (chooser->shown())
        Fl::wait();
    buf->loadfile(chooser->value());

}

char * tinyfd_editBox____(char const * aTitle,
                         char const * aText,
                         char const * aParams) /* "" , if NULL it's default */
{
    buf = new Fl_Text_Buffer;
    Fl_Menu_Item menu_File[] = { {"New", 0, cb, nullptr}, nullptr };

    Fl_Double_Window *window_main = new Fl_Double_Window(100, 100, 624, 644, "Text editor");
    window_main->labelfont(1);
    window_main->align(Fl_Align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE));

    Fl_Menu_Button *File = new Fl_Menu_Button(0, 0, 69, 20, "File");
    File->labelfont(13);
    File->menu(menu_File);

    Fl_Text_Editor *File_text = new Fl_Text_Editor(5, 25, window_main->w() - 10, 615);
    File_text->buffer(buf);

    window_main->size_range(0, 0, 1280, 660);
    window_main->resizable(File_text); // <-- here
    window_main->end();

    window_main->show(0, NULL);

    Fl::run();


    File_text->hide();

    window_main->hide();

    delete File_text;
    delete File;
    delete window_main;
    while(Fl::first_window())
    {
        delete Fl::first_window();
    }
    delete buf;

    return "";
}