#ifndef UINATIVETEXT_H_INCLUDED
#define UINATIVETEXT_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <cairo.h>
#include <cairo-ft.h>
#include <cairo-pdf.h>

#include "EVGLinkedList.h"
#include "UIStructure.h"



typedef struct UITextDimensions {
    double width;
    double height;
} UITextDimensions;

/*
// Global alpha handlers
double getGlobalAlpha( double usingValue  );
double pushGlobalAlpha( double value );
void popGlobalAlpha();
*/

double setTextAlpha( double usingValue  );

// test
void pango_draw_test(cairo_t *cr);

cairo_font_face_t *findFontFace( char *fontName, char *fontStyle);


// creating blur for the surface
void  evg_blur(cairo_surface_t *surface, int radius);

UITextDimensions *calculateTextDimensions( UIStructure *ui, double availableWidth );

#endif