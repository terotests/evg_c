
#include <math.h>

#include <cairo.h>
#include <cairo-ft.h>
#include <cairo-pdf.h>

#include <pango/pangocairo.h>

#include "UINativeText.h"
#include "UIStructure.h"


double __globalAlpha = 1.0;

double setTextAlpha( double usingValue  ) {
    __globalAlpha = usingValue;
}



// https://jannewmarch.gitbooks.io/programming-and-using-linux-sound-systems/content/Diversions/Gtk/DrawingtextusingPango.html


static FT_Face ftFace;
static FT_Error ftError;
static FT_Library library;
static cairo_scaled_font_t *sfPtr;
static cairo_font_face_t *crFace = NULL;

static cairo_surface_t *surface = NULL;
static cairo_t *cr = NULL;

static int library_inited = 0;

// might be useful to combine the tools into common files
static char* stradd(const char* a, const char* b){
    size_t len = strlen(a) + strlen(b);
    char *ret = (char*)malloc(len * sizeof(char) + 1);
    *ret = '\0';
    return strcat(strcat(ret, a) ,b);
}


// might be useful in some other libs too...
static int file_exist (char *filename)
{
    struct stat   buffer;
    return (stat (filename, &buffer) == 0);
}


LinkedList *__activeFontList = NULL;

cairo_font_face_t *findFontFace( char *fontName, char *fontStyle) {
    
    if(__activeFontList == NULL) {
        __activeFontList = createList();
    }
    
    LinkedListNode *cached_font = List_find(__activeFontList, fontName);
    
    if( cached_font == NULL ) {
        
        if(!library_inited) {
            ftError = FT_Init_FreeType(&library);
            if(ftError) {
                printf("Error initializing the Freetype");
                return NULL;
            }
            library_inited = 1;
        }
        
        int faceIdx = 0;
        
        const char *base_dir = "./fonts/";
        
        static FT_Face ftFace;
        cairo_font_face_t *new_crFace = NULL;
        
        char *font_name            = strdup(fontName);
        char *font_dir             = stradd(base_dir, fontName);
        char *font_dir_with_slash  = stradd(font_dir, "/");
        
        char *fbase_name = stradd( font_dir_with_slash, fontName);
        
        char *plain_dir = stradd( fbase_name, ".ttf");
        char *regular_dir = stradd( fbase_name, "-Regular.ttf");
        
        if(file_exist(plain_dir)) {
            
            ftError = FT_New_Face(library, plain_dir, faceIdx, &ftFace);
            if(ftError)  {
                printf("Error creating FT_New_Face");
                return NULL;
            }
            new_crFace = cairo_ft_font_face_create_for_ft_face(ftFace, 0);
            LinkedListNode *saveItem = ListNode_Create(fontName, new_crFace);
            List_push( __activeFontList, saveItem );
            
            // printf("Found font %s \n", plain_dir);
            
            return new_crFace;
        }
        
        if(file_exist(regular_dir)) {
            
            ftError = FT_New_Face(library, regular_dir, faceIdx, &ftFace);
            if(ftError)  {
                printf("Error creating FT_New_Face");
                return NULL;
            }
            new_crFace = cairo_ft_font_face_create_for_ft_face(ftFace, 0);
            LinkedListNode *saveItem = ListNode_Create(fontName, new_crFace);
            List_push( __activeFontList, saveItem );
            
            // printf("Found font %s \n", regular_dir);
            
            return new_crFace;
        }
        
        cached_font = List_find(__activeFontList, "Forum");
        
        if(cached_font == NULL ) {
            
            // Load the default font from the directory, for now

            const char *filePath2 = "/var/www/static/cpp/fonts/Forum/Forum-Regular.ttf";
            ftError = FT_New_Face(library, filePath2, faceIdx, &ftFace);
            
            if(ftError)  {
                printf("Error FT_New_Face");
                return NULL;
            }
            new_crFace = cairo_ft_font_face_create_for_ft_face(ftFace, 0);
            
            LinkedListNode *saveItem = ListNode_Create("Forum", new_crFace);
            List_push( __activeFontList, saveItem );
            
            return new_crFace;
            
        }
        
        return (cairo_font_face_t*)cached_font->data;
        
    } else {
        // printf("Was cached %s \n", cached_font->name);
        return (cairo_font_face_t*)cached_font->data;
        
    }
    
}

void pango_draw_test(cairo_t *cr) {
    
    gchar *markup_text = "<span foreground=\"red\">hello there and... </span><i>OK?</i><span foreground=\"black\">world</span>... <span foreground=\"red\">hello </span><i>OK?</i><span foreground=\"black\">world</span> <span foreground=\"red\">hello </span><i>OK?</i><span foreground=\"black\">world</span> <span foreground=\"red\">hello </span><i>OK?</i><span foreground=\"black\">world</span>";
    PangoAttrList *attrs;
    gchar *text;
    
    pango_parse_markup (markup_text, -1,0, &attrs, &text, NULL, NULL);
    
    PangoLayout *layout;
    PangoFontDescription *desc;
    
    cairo_move_to(cr, 100.0, 50.0);
    layout = pango_cairo_create_layout (cr);
    pango_layout_set_text (layout, text, -1);
    pango_layout_set_attributes(layout, attrs);
    
    pango_layout_set_width (layout, 200*PANGO_SCALE);
    pango_layout_set_wrap (layout, PANGO_WRAP_WORD);
    
    pango_cairo_update_layout (cr, layout);
    pango_cairo_show_layout (cr, layout);
    
}

#ifdef __UN__
void pango_draw_test(cairo_t *cr)
{
    printf("Pango draw text called!!!\n");
    
#define RADIUS 150
#define N_WORDS 10
#define FONT "Sans Bold 27"
    
    PangoLayout *layout;
    PangoFontDescription *desc;
    int i;
    
    /* Center coordinates on the middle of the region we are drawing
     */
    cairo_translate (cr, RADIUS, RADIUS);
    
    /* Create a PangoLayout, set the font and text */
    layout = pango_cairo_create_layout (cr);
    
    pango_layout_set_text (layout, "Text", -1);
    desc = pango_font_description_from_string (FONT);
    pango_layout_set_font_description (layout, desc);
    pango_font_description_free (desc);
    
    /* Draw the layout N_WORDS times in a circle */
    for (i = 0; i < N_WORDS; i++)
    {
        int width, height;
        double angle = (360. * i) / N_WORDS;
        double red;
        
        cairo_save (cr);
        
        /* Gradient from red at angle == 60 to blue at angle == 240 */
        red   = (1 + cos ((angle - 60) * G_PI / 180.)) / 2;
        cairo_set_source_rgb (cr, red, 0, 1.0 - red);
        
        cairo_rotate (cr, angle * G_PI / 180.);
        
        /* Inform Pango to re-layout the text with the new transformation */
        pango_cairo_update_layout (cr, layout);
        
        pango_layout_get_size (layout, &width, &height);
        cairo_move_to (cr, - ((double)width / PANGO_SCALE) / 2, - RADIUS);
        pango_cairo_show_layout (cr, layout);
        
        cairo_restore (cr);
    }
    
    /* free the layout object */
    g_object_unref (layout);
}
#endif



static cairo_t *get_tmp_cairo_context() {
    if(cr) return cr;
    surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 1, 1);
    cr = cairo_create(surface);
}



UITextDimensions *calculateTextDimensions( UIStructure *ui, double availableWidth ) {
    
    UITextDimensions *dimensions = calloc(1, sizeof(UITextDimensions));
    
    dimensions->width = 0.0;
    dimensions->height = 0.0;
    
    if( ui == NULL ) return dimensions;
    if( !ui->text->is_set ) return dimensions;
    if( ui->text->s_value == NULL ) return dimensions;
    if( strlen( ui->text->s_value) == 0 ) return dimensions;
    
    cr = get_tmp_cairo_context();

    cairo_set_font_face( cr, findFontFace( ui->fontFamily->is_set ? ui->fontFamily->s_value : "Forum", NULL) );
    
    double fontSize = 14.0;
    
    if(ui->fontSize->is_set) fontSize = ui->fontSize->f_value * ui->calculated.scale;
    
    // printf("TESTING FONT %s\n", ui->fontFamily->s_value);
    
    cairo_set_font_size(cr, fontSize);
    
    cairo_text_extents_t extents;
    cairo_text_extents (cr, ui->text->s_value, &extents);
    
    // TODO: add line flow for multiple lines when required...
    
    
    
    // printf("Measured Text box size : %f %f \n", extents.width, extents.height);
    
    // availableWidth
    
    if(availableWidth > extents.x_advance) {
        dimensions->width = extents.x_advance;
        dimensions->height = fontSize;
    } else {
        // must increase the height
        
        char *str = strdup( ui->text->s_value  );
        char *token = NULL;
        
        // Testing
        // u8_strtok
        
        cairo_text_extents_t extents;
        
        double x_pos = 0;
        double y_pos = fontSize;
        
        token = strtok(str, " ");
        while(token) {
            // printf("str : %s \n", token);
            char *toPrint = stradd(token, " ");
            cairo_text_extents (cr, toPrint, &extents);
            
            if( (x_pos + extents.x_advance) < availableWidth) {
                x_pos += extents.x_advance;
            } else {
                x_pos = 0;
                y_pos += fontSize;
            }
            token = strtok(NULL, " ");
        }
        
        // printf("re-measure results : %f %f \n", extents.x_advance, y_pos + fontSize);
        
        /*
        double max_w = availableWidth;
        double needs_height = fontSize;
        
        char *str = strdup( ui->text->s_value );
        char *current_position = ui->text->s_value;
        char *current_position_end = ui->text->s_value;
        
        int str_len = strlen(str);
        
        // 600 / fontSize
        int initial_step = floor( availableWidth / fontSize );
        if(initial_step >=str_len) initial_step = 0;
        
        while(str) {
            
        }
        */
        
        // <unistr.h>
        
        dimensions->width = extents.x_advance;
        dimensions->height = y_pos + fontSize;
    }
    

    
    return dimensions;
}


void evg_apply_shadow(cairo_t *_context, UIStructure *ui, void (fn)(cairo_t *cr)) {
    
    /*
    if(__globalAlpha < 1 ) {
        printf("skipping blur because alpha is %f \n", __globalAlpha);
        return;
    }
     */
    
    
    cairo_path_t *path = cairo_copy_path_flat(_context);
    cairo_save(_context);
    
    // shadowOffset is unaffected by current transform
    cairo_matrix_t path_matrix;
    cairo_get_matrix(_context, &path_matrix);
    cairo_identity_matrix(_context);
    
    // Apply shadow
    cairo_push_group(_context);
    
    double offsetX = 0.0;
    double offsetY = 0.0;
    
    // No need to invoke blur if shadowBlur is 0
    if (ui->shadowRadius->is_set) {
        // find out extent of path
        double x1, y1, x2, y2;
        if (fn == cairo_fill || fn == cairo_fill_preserve) {
            cairo_fill_extents(_context, &x1, &y1, &x2, &y2);
        } else {
            cairo_stroke_extents(_context, &x1, &y1, &x2, &y2);
        }
        
        // create new image surface that size + padding for blurring
        double dx = x2-x1, dy = y2-y1;
        cairo_user_to_device_distance(_context, &dx, &dy);
        
        
        int pad = 1+ui->shadowRadius->f_value * 2;
        
        // printf("Creating image surface %f %f\n", dx + 2 * pad, dy + 2 * pad);
        cairo_surface_t *shadow_surface = cairo_image_surface_create(
                                                                     CAIRO_FORMAT_ARGB32,
                                                                     dx + 2 * pad,
                                                                     dy + 2 * pad);
        cairo_t *shadow_context = cairo_create(shadow_surface);
        
        // transform path to the right place
        cairo_translate(shadow_context, pad-x1, pad-y1);
        cairo_transform(shadow_context, &path_matrix);
        
        // draw the path and blur
        cairo_set_line_width(shadow_context, cairo_get_line_width(_context));
        cairo_new_path(shadow_context);
        cairo_append_path(shadow_context, path);
        
        if( ui->shadowColor->is_set ) {
            UIColorType *c = ui->shadowColor;
            // the alpha should be the global alpha of the rendering state
            cairo_set_source_rgba( shadow_context, c->r/255.0, c->g/255.0, c->b/255.0, __globalAlpha* c->a/255.0  );
        } else {
            cairo_set_source_rgba( shadow_context, 0.0, 0.0, 0.0, __globalAlpha);
        }
        
        fn(shadow_context);
        evg_blur(shadow_surface, ui->shadowRadius->f_value);
        

        
        // paint to original context
        cairo_set_source_surface(_context, shadow_surface,
                                 x1 - pad + offsetX + 1,
                                 y1 - pad + offsetY + 1);
        cairo_paint(_context);
        cairo_destroy(shadow_context);
        cairo_surface_destroy(shadow_surface);
    } else {
        // Offset first, then apply path's transform
        cairo_translate(
                        _context
                        , offsetX
                        , offsetY);
        cairo_transform(_context, &path_matrix);
        
        // Apply shadow
        cairo_new_path(_context);
        cairo_append_path(_context, path);
        
        if( ui->shadowColor->is_set ) {
            UIColorType *c = ui->shadowColor;
            // the alpha should be the global alpha of the rendering state
            cairo_set_source_rgba( _context, c->r/255.0, c->g/255.0, c->b/255.0, __globalAlpha * c->a/255.0  );
        } else {
            cairo_set_source_rgba( _context, 0.0, 0.0, 0.0, __globalAlpha );
        }
        
        fn(_context);
    }
    
    // Paint the shadow
    cairo_pop_group_to_source(_context);
    cairo_paint(_context);
    
    // Restore state
    cairo_restore(_context);
    cairo_new_path(_context);
    cairo_append_path(_context, path);
    
    // temporarily remove...
    // fn(_context);
    
    cairo_path_destroy(path);
}

// http://www.html5rocks.com/en/tutorials/canvas/texteffects/

void  evg_blur( cairo_surface_t *surface, int radius ) {
    
    // Steve Hanov, 2009
    // Released into the public domain.
    // The modifications from node-canvas
    
    /*
    if(__globalAlpha < 1 ) {
        printf("skipping blur because alpha is %f \n", __globalAlpha);
        return;
    }
    */
    
    // printf("BLUR alpha %f \n", __globalAlpha);
    
    radius = radius * 0.57735f + 0.5f;
    // get width, height
    
    int width = cairo_image_surface_get_width( surface );
    int height = cairo_image_surface_get_height( surface );
    
    unsigned* precalc = (unsigned *)malloc(width*height*sizeof(unsigned));
    
    // making sure all writes so far have been applied to the surface
    cairo_surface_flush( surface );
    
    unsigned char* src = cairo_image_surface_get_data( surface );
    double mul=1.f/((radius*2)*(radius*2));
    int channel;
    
    // printf("evg_blur called with radius %i\n", radius);
    
    // The number of times to perform the averaging. According to wikipedia,
    // three iterations is good enough to pass for a gaussian.
    const int MAX_ITERATIONS = 3;
    int iteration;
    
    for ( iteration = 0; iteration < MAX_ITERATIONS; iteration++ ) {
        for( channel = 0; channel < 4; channel++ ) {
            int x,y;
            
            // precomputation step.
            unsigned char* pix = src;
            unsigned* pre = precalc;
            
            pix += channel;
            for (y=0;y<height;y++) {
                for (x=0;x<width;x++) {
                    int tot=pix[0];
                    if (x>0) tot+=pre[-1];
                    if (y>0) tot+=pre[-width];
                    if (x>0 && y>0) tot-=pre[-width-1];
                    *pre++=tot;
                    pix += 4;
                }
            }
            
            // blur step.
            pix = src + (int)radius * width * 4 + (int)radius * 4 + channel;
            for (y=radius;y<height-radius;y++) {
                for (x=radius;x<width-radius;x++) {
                    int l = x < radius ? 0 : x - radius;
                    int t = y < radius ? 0 : y - radius;
                    int r = x + radius >= width ? width - 1 : x + radius;
                    int b = y + radius >= height ? height - 1 : y + radius;
                    int tot = precalc[r+b*width] + precalc[l+t*width] -
                    precalc[l+b*width] - precalc[r+t*width];
                    *pix=(unsigned char)(tot*mul);
                    pix += 4;
                }
                pix += (int)radius * 2 * 4;
            }
        }
    }
    
    cairo_surface_mark_dirty(surface);
    free(precalc);
    
}


