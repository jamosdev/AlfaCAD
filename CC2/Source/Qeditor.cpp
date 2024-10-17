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

#include <QtWidgets/qinputdialog.h>
#include <string.h>

char * tinyfd_editBox___(char const * aText,
                           char const * aParams) /* "" , if NULL it's default */
{
    bool ok;

    QString text = QInputDialog::getMultiLineText(NULL, "AlfaCAD",
                                                  "Edit text", "", &ok);

    if (ok && !text.isEmpty()) {

        char* cstr;
        std::string fname = text.toUtf8().data();
        cstr = new char [fname.size()+1];
        strcpy( cstr, fname.c_str() );

        return cstr;
    }


    return NULL;
}