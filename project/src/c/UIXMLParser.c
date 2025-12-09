#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libxml/parser.h"
#include "UIXMLParser.h"
typedef struct NamedColor {
    const char  *name;
    unsigned int color;
} NamedColor;


#define RGB_VAL(r, g, b) (((unsigned int)r) | ((unsigned int)g << 8) | ((unsigned int)b << 16))

#define R_FROM_VAL(val) ( val & 0xff )
#define G_FROM_VAL(val) ( (val >> 8)   & 0xff )
#define B_FROM_VAL(val) ( (val >> 16 ) & 0xff )

NamedColor __colors[] = {
    
    { "red", RGB_VAL(255, 0, 0) },
    { "green", RGB_VAL( 0, 128, 0) },
    { "blue", RGB_VAL( 0, 0, 255) },
    { "yellow", RGB_VAL(255, 255, 0) },
    { "cyan", RGB_VAL( 0, 255, 255) },
    { "magenta", RGB_VAL(255, 0, 255) },
    { "black", RGB_VAL( 0, 0, 0) },
    { "grey", RGB_VAL(128, 128, 128) },
    { "gray", RGB_VAL(128, 128, 128) },
    { "white", RGB_VAL(255, 255, 255) },
    { "aliceblue", RGB_VAL(240, 248, 255) },
    { "antiquewhite", RGB_VAL(250, 235, 215) },
    { "aqua", RGB_VAL( 0, 255, 255) },
    { "aquamarine", RGB_VAL(127, 255, 212) },
    { "azure", RGB_VAL(240, 255, 255) },
    { "beige", RGB_VAL(245, 245, 220) },
    { "bisque", RGB_VAL(255, 228, 196) },
    { "blanchedalmond", RGB_VAL(255, 235, 205) },
    { "blueviolet", RGB_VAL(138, 43, 226) },
    { "brown", RGB_VAL(165, 42, 42) },
    { "burlywood", RGB_VAL(222, 184, 135) },
    { "cadetblue", RGB_VAL( 95, 158, 160) },
    { "chartreuse", RGB_VAL(127, 255, 0) },
    { "chocolate", RGB_VAL(210, 105, 30) },
    { "coral", RGB_VAL(255, 127, 80) },
    { "cornflowerblue", RGB_VAL(100, 149, 237) },
    { "cornsilk", RGB_VAL(255, 248, 220) },
    { "crimson", RGB_VAL(220, 20, 60) },
    { "darkblue", RGB_VAL( 0, 0, 139) },
    { "darkcyan", RGB_VAL( 0, 139, 139) },
    { "darkgoldenrod", RGB_VAL(184, 134, 11) },
    { "darkgray", RGB_VAL(169, 169, 169) },
    { "darkgreen", RGB_VAL( 0, 100, 0) },
    { "darkgrey", RGB_VAL(169, 169, 169) },
    { "darkkhaki", RGB_VAL(189, 183, 107) },
    { "darkmagenta", RGB_VAL(139, 0, 139) },
    { "darkolivegreen", RGB_VAL( 85, 107, 47) },
    { "darkorange", RGB_VAL(255, 140, 0) },
    { "darkorchid", RGB_VAL(153, 50, 204) },
    { "darkred", RGB_VAL(139, 0, 0) },
    { "darksalmon", RGB_VAL(233, 150, 122) },
    { "darkseagreen", RGB_VAL(143, 188, 143) },
    { "darkslateblue", RGB_VAL( 72, 61, 139) },
    { "darkslategray", RGB_VAL( 47, 79, 79) },
    { "darkslategrey", RGB_VAL( 47, 79, 79) },
    { "darkturquoise", RGB_VAL( 0, 206, 209) },
    { "darkviolet", RGB_VAL(148, 0, 211) },
    { "deeppink", RGB_VAL(255, 20, 147) },
    { "deepskyblue", RGB_VAL( 0, 191, 255) },
    { "dimgray", RGB_VAL(105, 105, 105) },
    { "dimgrey", RGB_VAL(105, 105, 105) },
    { "dodgerblue", RGB_VAL( 30, 144, 255) },
    { "firebrick", RGB_VAL(178, 34, 34) },
    { "floralwhite", RGB_VAL(255, 250, 240) },
    { "forestgreen", RGB_VAL( 34, 139, 34) },
    { "fuchsia", RGB_VAL(255, 0, 255) },
    { "gainsboro", RGB_VAL(220, 220, 220) },
    { "ghostwhite", RGB_VAL(248, 248, 255) },
    { "gold", RGB_VAL(255, 215, 0) },
    { "goldenrod", RGB_VAL(218, 165, 32) },
    { "greenyellow", RGB_VAL(173, 255, 47) },
    { "honeydew", RGB_VAL(240, 255, 240) },
    { "hotpink", RGB_VAL(255, 105, 180) },
    { "indianred", RGB_VAL(205, 92, 92) },
    { "indigo", RGB_VAL( 75, 0, 130) },
    { "ivory", RGB_VAL(255, 255, 240) },
    { "khaki", RGB_VAL(240, 230, 140) },
    { "lavender", RGB_VAL(230, 230, 250) },
    { "lavenderblush", RGB_VAL(255, 240, 245) },
    { "lawngreen", RGB_VAL(124, 252, 0) },
    { "lemonchiffon", RGB_VAL(255, 250, 205) },
    { "lightblue", RGB_VAL(173, 216, 230) },
    { "lightcoral", RGB_VAL(240, 128, 128) },
    { "lightcyan", RGB_VAL(224, 255, 255) },
    { "lightgoldenrodyellow", RGB_VAL(250, 250, 210) },
    { "lightgray", RGB_VAL(211, 211, 211) },
    { "lightgreen", RGB_VAL(144, 238, 144) },
    { "lightgrey", RGB_VAL(211, 211, 211) },
    { "lightpink", RGB_VAL(255, 182, 193) },
    { "lightsalmon", RGB_VAL(255, 160, 122) },
    { "lightseagreen", RGB_VAL( 32, 178, 170) },
    { "lightskyblue", RGB_VAL(135, 206, 250) },
    { "lightslategray", RGB_VAL(119, 136, 153) },
    { "lightslategrey", RGB_VAL(119, 136, 153) },
    { "lightsteelblue", RGB_VAL(176, 196, 222) },
    { "lightyellow", RGB_VAL(255, 255, 224) },
    { "lime", RGB_VAL( 0, 255, 0) },
    { "limegreen", RGB_VAL( 50, 205, 50) },
    { "linen", RGB_VAL(250, 240, 230) },
    { "maroon", RGB_VAL(128, 0, 0) },
    { "mediumaquamarine", RGB_VAL(102, 205, 170) },
    { "mediumblue", RGB_VAL( 0, 0, 205) },
    { "mediumorchid", RGB_VAL(186, 85, 211) },
    { "mediumpurple", RGB_VAL(147, 112, 219) },
    { "mediumseagreen", RGB_VAL( 60, 179, 113) },
    { "mediumslateblue", RGB_VAL(123, 104, 238) },
    { "mediumspringgreen", RGB_VAL( 0, 250, 154) },
    { "mediumturquoise", RGB_VAL( 72, 209, 204) },
    { "mediumvioletred", RGB_VAL(199, 21, 133) },
    { "midnightblue", RGB_VAL( 25, 25, 112) },
    { "mintcream", RGB_VAL(245, 255, 250) },
    { "mistyrose", RGB_VAL(255, 228, 225) },
    { "moccasin", RGB_VAL(255, 228, 181) },
    { "navajowhite", RGB_VAL(255, 222, 173) },
    { "navy", RGB_VAL( 0, 0, 128) },
    { "oldlace", RGB_VAL(253, 245, 230) },
    { "olive", RGB_VAL(128, 128, 0) },
    { "olivedrab", RGB_VAL(107, 142, 35) },
    { "orange", RGB_VAL(255, 165, 0) },
    { "orangered", RGB_VAL(255, 69, 0) },
    { "orchid", RGB_VAL(218, 112, 214) },
    { "palegoldenrod", RGB_VAL(238, 232, 170) },
    { "palegreen", RGB_VAL(152, 251, 152) },
    { "paleturquoise", RGB_VAL(175, 238, 238) },
    { "palevioletred", RGB_VAL(219, 112, 147) },
    { "papayawhip", RGB_VAL(255, 239, 213) },
    { "peachpuff", RGB_VAL(255, 218, 185) },
    { "peru", RGB_VAL(205, 133, 63) },
    { "pink", RGB_VAL(255, 192, 203) },
    { "plum", RGB_VAL(221, 160, 221) },
    { "powderblue", RGB_VAL(176, 224, 230) },
    { "purple", RGB_VAL(128, 0, 128) },
    { "rosybrown", RGB_VAL(188, 143, 143) },
    { "royalblue", RGB_VAL( 65, 105, 225) },
    { "saddlebrown", RGB_VAL(139, 69, 19) },
    { "salmon", RGB_VAL(250, 128, 114) },
    { "sandybrown", RGB_VAL(244, 164, 96) },
    { "seagreen", RGB_VAL( 46, 139, 87) },
    { "seashell", RGB_VAL(255, 245, 238) },
    { "sienna", RGB_VAL(160, 82, 45) },
    { "silver", RGB_VAL(192, 192, 192) },
    { "skyblue", RGB_VAL(135, 206, 235) },
    { "slateblue", RGB_VAL(106, 90, 205) },
    { "slategray", RGB_VAL(112, 128, 144) },
    { "slategrey", RGB_VAL(112, 128, 144) },
    { "snow", RGB_VAL(255, 250, 250) },
    { "springgreen", RGB_VAL( 0, 255, 127) },
    { "steelblue", RGB_VAL( 70, 130, 180) },
    { "tan", RGB_VAL(210, 180, 140) },
    { "teal", RGB_VAL( 0, 128, 128) },
    { "thistle", RGB_VAL(216, 191, 216) },
    { "tomato", RGB_VAL(255, 99, 71) },
    { "turquoise", RGB_VAL( 64, 224, 208) },
    { "violet", RGB_VAL(238, 130, 238) },
    { "wheat", RGB_VAL(245, 222, 179) },
    { "whitesmoke", RGB_VAL(245, 245, 245) },
    { "yellowgreen", RGB_VAL(154, 205, 50) }
};

static NamedColor *parseColorName(const char* str)
{
    int i, ncolors = sizeof(__colors) / sizeof(NamedColor);
    
    for (i = 0; i < ncolors; i++) {
        if (strstr(str, __colors[i].name) == str) {
            return &(__colors[i]);
        }
    }
    return NULL;
}


// create XML attribute parsers
static unsigned int parseColorHex(UIColorType *res, const char* str)
{
    unsigned int c = 0, r = 0, g = 0, b = 0;
    int n = 0;
    str++; // skip #
    // Calculate number of characters.
    while(str[n] && !( (str[n] == ' ') || (str[n] == ','))) n++;
    
    if (n == 6) {
        if(sscanf(str, "%x", &c) != 1) return 0;
    } else if (n == 3) {
        if(sscanf(str, "%x", &c) != 1) return 0;
        c = (c&0xf) | ((c&0xf0) << 4) | ((c&0xf00) << 8);
        c |= c<<4;
    } else {
        return 0;
    }
    r = (c >> 16) & 0xff;
    g = (c >> 8) & 0xff;
    b = c & 0xff;
    
    res->r = r;
    res->g = g;
    res->b = b;
    res->a = 255;
    res->is_set = 1;
    // printf("HEX and %i\n", n);
    return n+1;
}

typedef struct HSLAColorHolder {
    int h;
    int s;
    int l;
    int a;
    int is_set;
} HSLAColorHolder;

static unsigned int parseColorStringHSL(HSLAColorHolder *res, char* str)
{
    int r = 0, g = 0, b = 0;
    double a=1;
    
    int n = 0;
    
    res->is_set = 0;
    
    if(!str) return 0;
    
    char *s = strchr(str, '(');
    double color;
    if(!s) return 0;
    
    s++;
    char *comma  = strchr(s, ',');
    if(comma) {
        if( sscanf(s, "%lf", &color) != 1 ) {
            return 0;
        }
        r = color;
        s = comma+1;
    } else {
        return 0;
    }
    
    comma  = strchr(s, ',');
    if(comma) {
        if( sscanf(s, "%lf", &color) != 1 ) {
            return 0;
        }
        g = color;
        s = comma+1;
    } else {
        return 0;
    }
    
    if( sscanf(s, "%lf", &color) != 1 ) {
        return 0;
    }
    b = color;
    comma  = strchr(s, ',');
    
    if(comma) {
        s = comma+1;
        if( sscanf(s, "%lf", &color) != 1 ) {
            return 0;
        }
        a = color;
    }
    
    // n
    char *endPos = strchr(str, ')');
    
    if(endPos != NULL) {
        
        res->h = r;
        res->s = g;
        res->l = b;
        res->a = a*255;
        res->is_set = 1;
        
        return  (int)(endPos - str);
    }
    return 0;
}


static unsigned int parseColorRGB(UIColorType *res, char* str)
{
    int r = 0, g = 0, b = 0;
    double a=1;
    
    int n = 0;
    
    res->is_set = 0;
    
    if(!str) return 0;
    
    char *s = strchr(str, '(');
    double color;
    if(!s) return 0;
    
    s++;
    char *comma  = strchr(s, ',');
    if(comma) {
        if( sscanf(s, "%lf", &color) != 1 ) {
            return 0;
        }
        r = color;
        s = comma+1;
    } else {
        return 0;
    }
    
    comma  = strchr(s, ',');
    if(comma) {
        if( sscanf(s, "%lf", &color) != 1 ) {
            return 0;
        }
        g = color;
        s = comma+1;
    } else {
        return 0;
    }
    
    if( sscanf(s, "%lf", &color) != 1 ) {
        return 0;
    }
    b = color;
    comma  = strchr(s, ',');
    
    if(comma) {
        s = comma+1;
        if( sscanf(s, "%lf", &color) != 1 ) {
            return 0;
        }
        a = color;
    }
    
    // n
    char *endPos = strchr(str, ')');
    
    if(endPos != NULL) {
    
        res->r = r;
        res->g = g;
        res->b = b;
        res->a = a*255;
        res->is_set = 1;
    
        return  (int)(endPos - str);
    }
    return 0;
}

static double hue2rgb( double p, double q, double t){
    
    // printf(" hue2rgb  %f %f %f  \n", p,q,t);
    
    if(t < 0.0) t += 1.0;
    if(t > 1.0) t -= 1.0;
    if(t < 1.0/6.0) return p + (q - p) * 6.0 * t;
    if(t < 1.0/2.0) return q;
    if(t < 2.0/3.0) return p + (q - p) * (2.0/3.0 - t) * 6.0;
    return p;
}
static unsigned int parseColorHSL(UIColorType *res, char* str) {
    
    HSLAColorHolder hslColor;
    
    hslColor.is_set = 0;
    
    // printf("HSL parsing for %s \n", str);
    // syntax same as with RGB
    int n = parseColorStringHSL(&hslColor, str);
    if(hslColor.is_set) {
        // printf(" HSL:  %i %i %i %i \n", hslColor.h, hslColor.s, hslColor.l, hslColor.s);
        double h = ((double)hslColor.h) / 360.0;
        double s = ((double)hslColor.s) / 100.0;
        double l = ((double)hslColor.l) / 100.0;
        
        double r = l;
        double g = l;
        double b = l;
        
        if( s != 0) {
            
            // printf(" before conversion:  %f %f %f  \n", h,s,l);
            double q = (l < 0.5) ? (l * (1.0 + s)) : (l + s - l * s);
            double p = 2.0 * l - q;
            r = hue2rgb(p, q, h + 0.333333);
            g = hue2rgb(p, q, h);
            b = hue2rgb(p, q, h - 0.333333);
            
        } else {
            // printf(" s was zer0 :/ \n", r,g,b);
        }
        
        // printf(" after conversion:  %f %f %f \n", r,g,b);
        
        res->r = r*255.0;
        res->g = g*255.0;
        res->b = b*255.0;
        res->a = hslColor.a;
        
        res->is_set = 1;
        
        return n;
    }
}

// hsla(120, 100%, 50%, 0.3)

/*
 function hslToRgb(h, s, l){
 var r, g, b;
 
 if(s == 0){
 r = g = b = l; // achromatic
 }else{
 var hue2rgb = function hue2rgb(p, q, t){
 if(t < 0) t += 1;
 if(t > 1) t -= 1;
 if(t < 1/6) return p + (q - p) * 6 * t;
 if(t < 1/2) return q;
 if(t < 2/3) return p + (q - p) * (2/3 - t) * 6;
 return p;
 }
 
 var q = l < 0.5 ? l * (1 + s) : l + s - l * s;
 var p = 2 * l - q;
 r = hue2rgb(p, q, h + 1/3);
 g = hue2rgb(p, q, h);
 b = hue2rgb(p, q, h - 1/3);
 }
 
 return [Math.round(r * 255), Math.round(g * 255), Math.round(b * 255)];
 }
 */

static unsigned int parseColorType(UIColorType *into, char* str)
{
    size_t len = 0;
    int pre_trim = 0;
    while(*str == ' ') {
        pre_trim++;
        ++str;
    }
    len = strlen(str);
    
    if (len >= 4 && str[0] == 'r' && str[1] == 'g' && str[2] == 'b' ) {
        return parseColorRGB(into, str) + pre_trim;
    }
    if (len >= 4 && str[0] == 'h' && str[1] == 's' && str[2] == 'l' ) {
        return parseColorHSL(into, str) + pre_trim;
    }
    int n = parseColorHex(into, str);
    
    // printf("from %s parseColorHex returns %i\n", str, n);
    
    if(!n) {
        
        // printf("Looking named color from %s ---\n", str);
        n = 0;
        while(str[n] && ( (str[n] == ' '))) {
            n++;
        }
        str = str+n;
        
        // printf("after trim of %i we have %s ---\n", n, str);
        
        NamedColor *named = parseColorName(str);
        
        if(named != NULL) {
            // printf("Found named color %s\n", named->name);
            unsigned int val = named->color;
            into->r = R_FROM_VAL( val );
            into->g = G_FROM_VAL( val );
            into->b = B_FROM_VAL( val );
            into->a = 255;
            into->is_set = 1;
            return strlen(named->name) +n + pre_trim;
        } else {
            // printf("did not find named color from  %s ---\n", str);
        }
    } else {
        return n + pre_trim;
    }
    return 0;
}

static int parseBooleanType( UIBooleanType *into, char *str) {
    
    char *px = strstr(str, "true");
    if(px) {
        into->is_set = 1;
        into->b_value = 1;
        return 1;
    }
    px = strstr(str, "1");
    if(px) {
        into->is_set = 1;
        into->b_value = 1;
        return 1;
    }
    into->is_set = 1;
    into->b_value = 0;
    return 1;
}

static int parseStringType( UIStringType *into, char *str) {
    
    if(str  && (strlen(str)>0)) {
        into->is_set = 1;
        into->s_value = strdup(str);
        return 1;
    }
    into->is_set = 0;
    return 1;
}



static void parseFloatType( UIFloatType *into, char *str) {
    
    char *px = strstr(str, "fill");
    if(px) {
        into->is_set = 1;
        into->unit = 5;
        return;
    }
    
    px = strstr(str, "px");
    if(px) {
        into->is_set = 1;
        into->unit = 3;
        double d;
        if( sscanf(str, "%lf", &(d)) != 1 ) {
            into->is_set = 0;
            return;
        } else {
            into->is_set = 1;
        }
        into->f_value = d;
        return;
    }
    px = strstr(str, "em");
    if(px) {
        into->is_set = 1;
        into->unit = 2;
        double d;
        if( sscanf(str, "%lf", &(d)) != 1 ) {
            into->is_set = 0;
            return;
        } else {
            into->is_set = 1;
        }
        into->f_value = d;
        return;
    }
    px = strstr(str, "hp");
    if(px) {
        into->is_set = 1;
        into->unit = 4;
        double d;
        if( sscanf(str, "%lf", &(d)) != 1 ) {
            into->is_set = 0;
            return;
        } else {
            into->is_set = 1;
        }
        into->f_value = d;
        return;
    }
    px = strrchr(str, '%');
    if(px) {
        into->unit = 1;
        double d;
        if( sscanf(str, "%lf", &(d)) != 1 ) {
            into->is_set = 0;
            return;
        } else {
            into->is_set = 1;
        }
        into->f_value = d;
        return;
    }
    into->unit = 3;
    double d;
    if( sscanf(str, "%lf", &(d)) != 1 ) {
        into->is_set = 0;
        return;
    } else {
        into->is_set = 1;
    }
    into->f_value = d;
}

static void distribute_pros( UIColorStop *from, UIColorStop *to, double startValue, double endValue, double cnt) {
    
    if(cnt < 2) return;
    if(from == NULL ) return;
    double i = 0;
    while(from != to) {
        if(from->percentage < 0 ) {
           from->percentage = startValue + ( (endValue - startValue) * ( i / (cnt-1)) );
        }
        from = from->next;
        i++;
    }
    
}

static void parseLinearGradient( UIColorStop *into, char *str) {
    
    if( str == NULL ) return;
    
    int cnt = 0;
    
    UIColorStop *activeStop = into;
    UIColorStop *newStop = NULL;
    UIColorType  testColor;
    
    //while ((token = strsep(&string, ",")) != NULL) {

        char *deg = strstr(str, "deg");
        if(deg) {
            // printf("Degrees found \n");
            double d;
            if( sscanf(str, "%lf", &(d)) == 1 ) {

                // setting the stop angle
                activeStop->degree = d;
                str = strstr(str, ","); // find the separator comma
                if(str != NULL) str++;  // step over the comma
            }
        }
        if(str == NULL) return;
    
        char *first_comma = strstr(str, ",");
        char *has_to = strstr(str, "to");
    
        // to left to right, to left top etc.
        /*
            The values to top, to bottom, to left and to right are translated into the angles 0deg, 180deg, 270deg, 90deg respectively
        */
        if(has_to && (has_to < first_comma)) {
           
            char *has_left = strstr(str, "left");
            char *has_right = strstr(str, "right");
            char *has_bottom = strstr(str, "bottom");
            char *has_top = strstr(str, "top");
            
            if(has_top  &&  !(has_left || has_right))   activeStop->degree = 0;
            if(has_bottom &&  !(has_left  || has_right))  activeStop->degree = 180;
            
            if(has_left &&  !(has_top  || has_bottom))  activeStop->degree = 270;
            if(has_right &&  !(has_top  || has_bottom))  activeStop->degree = 90;
            
            // --> can not calculate angle for left-top etc.
            
            str = strstr(str, ","); // find the separator comma
            if(str != NULL) str++; // step over the comma
        }
    
        if(str == NULL) return;
    
        int step_cnt = 0, stop_cnt = 0;
    
        while(str) {
         // printf("parsing: %s\n", str);
         // try to find a color value
         step_cnt = parseColorType( &testColor, str );
            
         if(step_cnt > 0) {

            if(cnt>0) {
                newStop = UIColorStop_New();
                activeStop->next = newStop;
                activeStop = newStop;
                activeStop->percentage = -1;
            } else {
                activeStop->percentage = -1;
            }
            activeStop->is_set = 1;
            activeStop->color->r = testColor.r;
            activeStop->color->g = testColor.g;
            activeStop->color->b = testColor.b;
            activeStop->color->a = testColor.a;
            
            // printf("Found stop %i %i %i %i \n ", activeStop->color->r, activeStop->color->g, activeStop->color->b, activeStop->color->a);

            cnt++;
            str += (step_cnt);
             
            // printf("--> after color processing left %s \n", str);
             
            char *next_comma = strstr(str, ",");
            char *next_pros  = strstr(str, "%");
            
            if( (next_pros && !next_comma) || (next_pros && (next_pros < next_comma))) {
             double d;
             if( sscanf(str, "%lf", &(d)) == 1 ) {
                // printf("found percentage %f \n", d);
                activeStop->percentage = d;
             }
            }
            str = strstr(str, ",");
             if(str !=NULL) str++;
         } else {
             // printf("step_cnt==0\n", str);
             break; // nothing to be found...
         }
        }
        // parseColorRGB
        
    // }
        // printf("%s\n", token);
    
    if(cnt>=2) {
        // printf("Had more than 2 stops, setting the stops active\n");
        into->is_set = 1;
        
        UIColorStop *editStop = into;
        
        UIColorStop *distribute_from = into;
        UIColorStop *distribute_to = into;
        
        double i = 0;
        double remains = 100;
        double last_start = 0;
        double dist_cnt = 0;
        
        int has_intermediate = 0;
        
        // editStop->percentage = 0;
        
        while( editStop ) {
           if(editStop->percentage < 0 ) {
               distribute_to = editStop;
               dist_cnt++;
           } else {
               
               distribute_pros( distribute_from, editStop, last_start, editStop->percentage, dist_cnt+1 );
               
               last_start = editStop->percentage; // red, green 50%, blue
               
               distribute_from = editStop;
               distribute_to = editStop;
               dist_cnt = 0;
               
               has_intermediate = 1;
           }
           if(editStop->next == NULL) {
               editStop->percentage = 100;
           }
           editStop = editStop->next;
        }
        if(distribute_from && distribute_to && (dist_cnt>1)) {
            if(has_intermediate) {
                distribute_pros( distribute_from, NULL, last_start, 100.00, dist_cnt +1 );
            } else {
                distribute_pros( distribute_from, NULL, last_start, 100.00, dist_cnt );
            }
            
        }
        
    }

}

static void parseRadialGradient( UIColorStop *into, char *str) {
    
    if( str == NULL ) return;
    
    int cnt = 0;
    
    UIColorStop *activeStop = into;
    UIColorStop *newStop = NULL;
    UIColorType  testColor;
    
    
    int step_cnt = 0, stop_cnt = 0;
    
    while(str) {
        // printf("parsing radial: %s\n", str);
        // try to find a color value
        step_cnt = parseColorType( &testColor, str );
        
        if(step_cnt > 0) {
            
            if(cnt>0) {
                newStop = UIColorStop_New();
                activeStop->next = newStop;
                activeStop = newStop;
                activeStop->percentage = -1;
            } else {
                activeStop->percentage = -1;
            }
            activeStop->is_set = 1;
            activeStop->color->r = testColor.r;
            activeStop->color->g = testColor.g;
            activeStop->color->b = testColor.b;
            activeStop->color->a = testColor.a;
            
            // printf("Found radial stop %i %i %i %i \n ", activeStop->color->r, activeStop->color->g, activeStop->color->b, activeStop->color->a);
            
            cnt++;
            str += (step_cnt);

            char *next_comma = strstr(str, ",");
            char *next_pros  = strstr(str, "%");
            
            if( (next_pros && !next_comma) || (next_pros && (next_pros < next_comma))) {
                double d;
                if( sscanf(str, "%lf", &(d)) == 1 ) {
                    // printf("found radial percentage %f \n", d);
                    activeStop->percentage = d;
                }
            }
            str = strstr(str, ",");
            if(str !=NULL) str++;
        } else {
            printf("step_cnt==0\n");
            break; // nothing to be found...
        }
    }

    
    if(cnt>=2) {
        // printf("Had more than 2 stops, setting the radial stops active\n");
        into->is_set = 1;
        
        UIColorStop *editStop = into;
        
        UIColorStop *distribute_from = into;
        UIColorStop *distribute_to = into;
        
        double i = 0;
        double remains = 100;
        double last_start = 0;
        double dist_cnt = 0;
        
        int has_intermediate = 0;
        
        
        while( editStop ) {
            if(editStop->percentage < 0 ) {
                distribute_to = editStop;
                dist_cnt++;
            } else {
                
                distribute_pros( distribute_from, editStop, last_start, editStop->percentage, dist_cnt+1 );
                
                last_start = editStop->percentage; // red, green 50%, blue
                
                distribute_from = editStop;
                distribute_to = editStop;
                dist_cnt = 0;
                
                has_intermediate = 1;
            }
            if(editStop->next == NULL) {
                editStop->percentage = 100;
            }
            editStop = editStop->next;
        }
        if(distribute_from && distribute_to && (dist_cnt>1)) {
            if(has_intermediate) {
                distribute_pros( distribute_from, NULL, last_start, 100.00, dist_cnt +1 );
            } else {
                distribute_pros( distribute_from, NULL, last_start, 100.00, dist_cnt );
            }
            
        }
        
    }
    
}


static char* stradd(const char* a, const char* b){
    size_t len = strlen(a) + strlen(b);
    char *ret = (char*)malloc(len * sizeof(char) + 1);
    *ret = '\0';
    return strcat(strcat(ret, a) ,b);
}


// always re-reads the custom tag for now... :/

static UIStructure *read_custom_tag_def(char *filename) {
    
    
    if(filename == NULL) return NULL;
    
    char *baseDir = "./";
    
    char *path_name = strdup(filename);
    char *s = path_name;
    
    while(*s) {
        if( (*s) == '.') (*s) = '/';
        s++;
    }
    
    char *with_xml = stradd( path_name, ".xml");
    free(path_name);
    
    char *with_path_part = stradd( baseDir, with_xml );
    free( with_xml );
    
    xmlDoc         *document;
    xmlNode        *root, *first_child, *node;
    xmlChar        *value;
    
    document = xmlReadFile(with_path_part, NULL, 0);
    root = xmlDocGetRootElement(document);
    if(!root) {
        return NULL;
    }
    return parseXMLNodes(root, NULL);
}


static UIStructure *find_content_node( UIStructure *node ) {
    
    
    if(node->id->is_set && (strcmp(node->id->s_value, "content")==0)) {
        return node;
    }
    if((node->tagName != NULL) && strcmp(node->tagName, "content")==0) {
        return node;
    }
    
    UIStructure* childNode = node->firstChild;
    UIStructure* did_find = NULL;
    while(childNode) {
        did_find = find_content_node( childNode );
        if(did_find) return did_find;
        childNode = childNode->nextSibling;
    }
    return NULL;
}



// XML parser main function
UIStructure *parseXMLNodes( xmlNode *node,  xmlNode *parentNode) {
    
    if(node->type==3) return NULL;
    
    UIStructure *ui = UIStructure_New();
    xmlNode *first_child;
    xmlNode *childNode;
    UIStructure *contentNode = ui;
    
    ui->tagName = strdup(node->name);
    
    if(strstr(ui->tagName, ".")) {
        // Then, we will change the UI suddenly to something else...
        
        UIStructure *now_it_actually_is = read_custom_tag_def(ui->tagName);
        
        if(now_it_actually_is) {
            
            UIStructure_Free(ui);
            
            ui = now_it_actually_is;
            contentNode = ui;
            
            UIStructure *did_have_content = find_content_node( now_it_actually_is );
            if(did_have_content) contentNode = did_have_content;

        }
        
    }
    
    // now, just test
    
    
    xmlAttr* attribute = node->properties;
    while(attribute)
    {
        
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"x")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseFloatType( ui->x, value );
            xmlFree(value);
        }
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"y")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseFloatType( ui->y, value );
            xmlFree(value);
        }
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"left")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseFloatType( ui->left, value );
            xmlFree(value);
        }
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"top")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseFloatType( ui->top, value );
            xmlFree(value);
        }
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"id")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseStringType( ui->id, value );
            xmlFree(value);
        }
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"width")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseFloatType( ui->width, value );
            xmlFree(value);
        }
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"height")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseFloatType( ui->height, value );
            xmlFree(value);
        }
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"direction")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseStringType( ui->direction, value );
            xmlFree(value);
        }
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"align")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseStringType( ui->align, value );
            xmlFree(value);
        }
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"verticalAlign") || !xmlStrcmp(attribute->name, (const xmlChar *)"vertical-align")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseStringType( ui->verticalAlign, value );
            xmlFree(value);
        }
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"innerWidth")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseFloatType( ui->innerWidth, value );
            xmlFree(value);
        }
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"innerHeight")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseFloatType( ui->innerHeight, value );
            xmlFree(value);
        }
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"lineBreak") || !xmlStrcmp(attribute->name, (const xmlChar *)"line-break")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseBooleanType( ui->lineBreak, value );
            xmlFree(value);
        }
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"overflow")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseStringType( ui->overflow, value );
            xmlFree(value);
        }
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"fontSize") || !xmlStrcmp(attribute->name, (const xmlChar *)"font-size")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseFloatType( ui->fontSize, value );
            xmlFree(value);
        }
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"fontFamily") || !xmlStrcmp(attribute->name, (const xmlChar *)"font-family")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseStringType( ui->fontFamily, value );
            xmlFree(value);
        }
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"color")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseColorType( ui->color, value );
            xmlFree(value);
        }
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"backgroundColor") || !xmlStrcmp(attribute->name, (const xmlChar *)"background-color")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseColorType( ui->backgroundColor, value );
            xmlFree(value);
        }
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"opacity")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseFloatType( ui->opacity, value );
            xmlFree(value);
        }
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"rotate")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseFloatType( ui->rotate, value );
            xmlFree(value);
        }
        
        // FIX: trying to find the radial gradient
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"radialGradient") || !xmlStrcmp(attribute->name, (const xmlChar *)"radial-gradient")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            // printf("radial gradient found %s \n", value);
            parseRadialGradient( ui->radialGradient, value);
            // parseFloatType( ui->borderWidth, value );
            xmlFree(value);
        }
        
        // FIX: trying to find the linear gradient
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"linearGradient") || !xmlStrcmp(attribute->name, (const xmlChar *)"linear-gradient")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            // printf("Linear gradient found %s \n", value);
            parseLinearGradient( ui->linearGradient, value);
            // parseFloatType( ui->borderWidth, value );
            xmlFree(value);
        }
        
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"borderWidth") || !xmlStrcmp(attribute->name, (const xmlChar *)"border-width")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseFloatType( ui->borderWidth, value );
            xmlFree(value);
        }
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"borderColor") || !xmlStrcmp(attribute->name, (const xmlChar *)"border-color")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseColorType( ui->borderColor, value );
            xmlFree(value);
        }
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"borderRadius") || !xmlStrcmp(attribute->name, (const xmlChar *)"border-radius")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseFloatType( ui->borderRadius, value );
            xmlFree(value);
        }
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"svgPath") || !xmlStrcmp(attribute->name, (const xmlChar *)"path")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseStringType( ui->svgPath, value );
            xmlFree(value);
        }
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"imageUrl") || !xmlStrcmp(attribute->name, (const xmlChar *)"src")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseStringType( ui->imageUrl, value );
            xmlFree(value);
        }
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"text")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseStringType( ui->text, value );
            xmlFree(value);
        }
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"scale")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseFloatType( ui->scale, value );
            xmlFree(value);
        }
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"margin")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseFloatType( ui->margin, value );
            xmlFree(value);
        }
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"marginLeft") || !xmlStrcmp(attribute->name, (const xmlChar *)"margin-left")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseFloatType( ui->marginLeft, value );
            xmlFree(value);
        }
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"marginRight") || !xmlStrcmp(attribute->name, (const xmlChar *)"margin-right")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseFloatType( ui->marginRight, value );
            xmlFree(value);
        }
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"marginBottom") || !xmlStrcmp(attribute->name, (const xmlChar *)"margin-bottom")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseFloatType( ui->marginBottom, value );
            xmlFree(value);
        }
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"marginTop") || !xmlStrcmp(attribute->name, (const xmlChar *)"margin-top")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseFloatType( ui->marginTop, value );
            xmlFree(value);
        }
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"padding")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseFloatType( ui->padding, value );
            xmlFree(value);
        }
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"paddingLeft") || !xmlStrcmp(attribute->name, (const xmlChar *)"padding-left")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseFloatType( ui->paddingLeft, value );
            xmlFree(value);
        }
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"paddingRight") || !xmlStrcmp(attribute->name, (const xmlChar *)"padding-right")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseFloatType( ui->paddingRight, value );
            xmlFree(value);
        }
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"paddingBottom") || !xmlStrcmp(attribute->name, (const xmlChar *)"padding-bottom")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseFloatType( ui->paddingBottom, value );
            xmlFree(value);
        }
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"paddingTop") || !xmlStrcmp(attribute->name, (const xmlChar *)"padding-top")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseFloatType( ui->paddingTop, value );
            xmlFree(value);
        }
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"shadowColor") || !xmlStrcmp(attribute->name, (const xmlChar *)"shadow-color")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseColorType( ui->shadowColor, value );
            xmlFree(value);
        }
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"shadowOffsetX") || !xmlStrcmp(attribute->name, (const xmlChar *)"shadow-offset-x")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseFloatType( ui->shadowOffsetX, value );
            xmlFree(value);
        }
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"shadowOffsetY") || !xmlStrcmp(attribute->name, (const xmlChar *)"shadow-offset-y")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseFloatType( ui->shadowOffsetY, value );
            xmlFree(value);
        }
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"shadowOpacity") || !xmlStrcmp(attribute->name, (const xmlChar *)"shadow-opacity")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseFloatType( ui->shadowOpacity, value );
            xmlFree(value);
        }
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"shadowRadius") || !xmlStrcmp(attribute->name, (const xmlChar *)"shadow-radius")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseFloatType( ui->shadowRadius, value );
            xmlFree(value);
        }
        attribute = attribute->next;
    }
    
    first_child = node->children;
    for (childNode = first_child; childNode; childNode = childNode->next) {

        // check if the child type is text
        /*
        if(!xmlStrcmp(attribute->name, (const xmlChar *)"text")) {
            char *value = xmlNodeListGetString(node->doc, attribute->children, 1);
            parseStringType( ui->text, value );
            xmlFree(value);
        }        
        */

        UIStructure *child_ui = parseXMLNodes(childNode, node);
        if(child_ui != NULL) {
            if ( !child_ui->text->is_set && (!xmlStrcmp(childNode->name, (const xmlChar *)"Label")) ) {
               char* strVal = xmlNodeListGetString(node->doc, childNode->xmlChildrenNode, 1);
               parseStringType( child_ui->text, strVal );
            }
            UIStructure_AddChild(contentNode, child_ui );
        }
    }
    
    
    return ui;
}

// small test function...
void test_walk_tree( UIStructure *node ) {
    
    printf("<%s>\n", node->tagName);
    
    UIStructure* childNode = node->firstChild;
    
    while(childNode) {
        test_walk_tree( childNode );
        childNode = childNode->nextSibling;
    }
    printf("</%s>\n", node->tagName);
}
