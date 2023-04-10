#ifndef STYLESHEETS_H
#define STYLESHEETS_H

#define CELL_STYLE \
    "QFrame {\
        background-color: #FFFFFF;\
        color: #000000;\
        border: 1px\
        outset #CCCCCC;\
    }\
    QLabel {\
        border: none;\
        font-size: 16px;\
        padding: 5px;\
        background-color: rgba(0,0,0,0);\
    }\
    QFrame#header {\
        background-color: #23b5d3;\
    }\
    QLabel#header {\
        font-weight: bold;\
    }\
    QFrame#header {\
        background-color: #FFFFFF;\
    }\
    QFrame#today {\
        background-color: #DDDDFF;\
    }\
    QLabel#today {\
        background-color: #FFFF88;\
        color: #FF0000;\
        border: 1px\
        solid #FF0000;\
    }\
    QFrame#future {\
        background-color: #279af1;\
    }\
    QLabel#future {\
        font-weight: bold;\
    }\
    QFrame#past {\
        background-color: #D1D1D1;\
    }\
    QLabel#past {\
        font-weight: bold;\
    }\
    \
    QFrame#selected {\
            background-color: #EEEEFF;\
    }\
    QFrame#disabled {\
        background-color: #EFEFEF;\
    }"


#define LABELDATE_STYLE \
    "QLabel {\
        color: #000000;\
        qproperty-alignment: AlignCenter;\
        padding-left: 100px;\
        padding-right: 100px;\
        font-size: 20px;\
    }"


#define BUTTON_STYLE \
    "QPushButton {\
        border: 1px\
        solid #000000;\
        color: #000000;\
        padding: 5px;\
        font-weight: bold;\
        border-radius: 5px;\
    }\
    QPushButton:hover {\
        color: #2222BB;\
    }"

#endif // STYLESHEETS_H
