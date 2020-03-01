#ifndef UISTRUCTURE_H_INCLUDED
#define UISTRUCTURE_H_INCLUDED

#include <stdint.h>


typedef struct UIRenderPosition {
    double x;
    double y;
    double scale;
} UIRenderPosition;

typedef struct UICalculated {
    double x;
    double y;
    double render_width;
    double render_height;
    double width;
    double height;
    double scale;
    
    // fix: take into account custom width if specified
    int size_override;
    double width_override;
    
    int lineBreak;
    int absolute;
} UICalculated;

typedef struct UIFloatType {
    int is_set;
    double f_value;
    int unit;
    double pixels;
} UIFloatType;

typedef struct UIColorType {
    int is_set;
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
    char* s_value;
} UIColorType;

typedef struct UIColorStop {
    int is_set;
    int is_linear;
    double x;
    double y;
    double degree;
    double percentage;
    UIColorType* color;
    struct UIColorStop* next;
} UIColorStop;

typedef struct UIBooleanType {
    int is_set;
    int b_value;
} UIBooleanType;

typedef struct UIStringType {
    int is_set;
    char* s_value;
} UIStringType;
typedef struct UIStructure {
    UIFloatType *x;
    UIFloatType *y;
    UIFloatType *left;
    UIFloatType *top;
    UIStringType *id;
    UIFloatType *width;
    UIFloatType *height;
    UIStringType *direction;
    UIStringType *align;
    UIStringType *verticalAlign;
    UIFloatType *innerWidth;
    UIFloatType *innerHeight;
    UIBooleanType *lineBreak;
    UIStringType *overflow;
    UIFloatType *fontSize;
    UIStringType *fontFamily;
    UIColorType *color;
    UIColorType *backgroundColor;
    UIFloatType *opacity;
    UIFloatType *rotate;
    UIFloatType *borderWidth;
    UIColorType *borderColor;
    UIFloatType *borderRadius;
    UIStringType *svgPath;
    UIStringType *imageUrl;
    UIStringType *text;
    UIColorStop *linearGradient;
    UIColorStop *radialGradient;
    UIFloatType *scale;
    UIFloatType *margin;
    UIFloatType *marginLeft;
    UIFloatType *marginRight;
    UIFloatType *marginBottom;
    UIFloatType *marginTop;
    UIFloatType *padding;
    UIFloatType *paddingLeft;
    UIFloatType *paddingRight;
    UIFloatType *paddingBottom;
    UIFloatType *paddingTop;
    UIColorType *shadowColor;
    UIFloatType *shadowOffsetX;
    UIFloatType *shadowOffsetY;
    UIFloatType *shadowOpacity;
    UIFloatType *shadowRadius;
    UICalculated calculated;
    
    char *tagName;
    // hierarchy of the nodes
    struct UIStructure *parent;
    struct UIStructure *nextSibling;
    struct UIStructure *prevSibling;
    struct UIStructure *firstChild;
    struct UIStructure *lastChild;
} UIStructure;

// function declarations
UIRenderPosition* UIRenderPosition_New();
UIRenderPosition* UIRenderPosition_With(double x, double y, double scale);
void UIRenderPosition_Free(UIRenderPosition* item);
UICalculated* UICalculated_New();
UICalculated* UICalculated_With(double x, double y, double render_width, double render_height, double width, double height, int lineBreak, int absolute);
void UICalculated_Free(UICalculated* item);
UIFloatType* UIFloatType_New();
UIFloatType* UIFloatType_With(int is_set, double f_value, int unit, double pixels);
void UIFloatType_Free(UIFloatType* item);
UIColorType* UIColorType_New();
UIColorType* UIColorType_With(int is_set, uint8_t r, uint8_t g, uint8_t b, uint8_t a, char* s_value);
void UIColorType_Free(UIColorType* item);
UIColorStop* UIColorStop_New();
UIColorStop* UIColorStop_With(int is_set, int is_linear, double x, double y, double degree, double percentage, UIColorType* color, struct UIColorStop* next);
void UIColorStop_Free(UIColorStop* item);
UIBooleanType* UIBooleanType_New();
UIBooleanType* UIBooleanType_With(int is_set, int b_value);
void UIBooleanType_Free(UIBooleanType* item);
UIStringType* UIStringType_New();
UIStringType* UIStringType_With(int is_set, char* s_value);
void UIStringType_Free(UIStringType* item);
UIStructure *UIStructure_New();
void UIStructure_Free(UIStructure *node);
int UIStructure_AddChild(UIStructure* this, UIStructure* node);
int UIStructure_RemoveChild(UIStructure* this, UIStructure* node);

#endif
