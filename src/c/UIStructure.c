#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "UIStructure.h"
static void UIRenderPosition_Init(UIRenderPosition *node) {
    node->x=0;
    node->y=0;
}
UIRenderPosition* UIRenderPosition_New() {
    UIRenderPosition *node = calloc(1, sizeof(UIRenderPosition));
    UIRenderPosition_Init(node);
    return node;
}
UIRenderPosition* UIRenderPosition_With(double x, double y) {
    UIRenderPosition *node = calloc(1, sizeof(UIRenderPosition));
    node->x=x;
    node->y=y;
    return node;
}
void UIRenderPosition_Free(UIRenderPosition* item) {
    free(item);
}
static void UICalculated_Init(UICalculated *node) {
    node->x=0;
    node->y=0;
    node->render_width=0;
    node->render_height=0;
    node->width=0;
    node->height=0;
    node->lineBreak=0;
    node->absolute=0;
    // fix default for size override is zero
    node->size_override = 0;
}
UICalculated* UICalculated_New() {
    UICalculated *node = calloc(1, sizeof(UICalculated));
    UICalculated_Init(node);
    return node;
}
UICalculated* UICalculated_With(double x, double y, double render_width, double render_height, double width, double height, int lineBreak, int absolute) {
    UICalculated *node = calloc(1, sizeof(UICalculated));
    node->x=x;
    node->y=y;
    node->render_width=render_width;
    node->render_height=render_height;
    node->width=width;
    node->height=height;
    node->lineBreak=lineBreak;
    node->absolute=absolute;
    return node;
}
void UICalculated_Free(UICalculated* item) {
    free(item);
}
static void UIFloatType_Init(UIFloatType *node) {
    node->is_set=0;
    node->f_value=0;
    node->unit=3;
    node->pixels=0;
}
UIFloatType* UIFloatType_New() {
    UIFloatType *node = calloc(1, sizeof(UIFloatType));
    UIFloatType_Init(node);
    return node;
}
UIFloatType* UIFloatType_With(int is_set, double f_value, int unit, double pixels) {
    UIFloatType *node = calloc(1, sizeof(UIFloatType));
    node->is_set=is_set;
    node->f_value=f_value;
    node->unit=unit;
    node->pixels=pixels;
    return node;
}
void UIFloatType_Free(UIFloatType* item) {
    free(item);
}
static void UIColorType_Init(UIColorType *node) {
    node->is_set=0;
    node->r=0;
    node->g=0;
    node->b=0;
    node->a=0;
    node->s_value=NULL;
}
UIColorType* UIColorType_New() {
    UIColorType *node = calloc(1, sizeof(UIColorType));
    UIColorType_Init(node);
    return node;
}
UIColorType* UIColorType_With(int is_set, uint8_t r, uint8_t g, uint8_t b, uint8_t a, char* s_value) {
    UIColorType *node = calloc(1, sizeof(UIColorType));
    node->is_set=is_set;
    node->r=r;
    node->g=g;
    node->b=b;
    node->a=a;
    node->s_value=s_value;
    return node;
}
void UIColorType_Free(UIColorType* item) {
    if(item->s_value != NULL) free(item->s_value);
    free(item);
}
static void UIColorStop_Init(UIColorStop *node) {
    node->is_set=0;
    node->is_linear=1;
    node->x=0;
    node->y=0;
    node->degree=180;
    node->percentage=0;
    node->color=UIColorType_New();
    node->next=NULL;
}
UIColorStop* UIColorStop_New() {
    UIColorStop *node = calloc(1, sizeof(UIColorStop));
    UIColorStop_Init(node);
    return node;
}
UIColorStop* UIColorStop_With(int is_set, int is_linear, double x, double y, double degree, double percentage, UIColorType* color, struct UIColorStop* next) {
    UIColorStop *node = calloc(1, sizeof(UIColorStop));
    node->is_set=is_set;
    node->is_linear=is_linear;
    node->x=x;
    node->y=y;
    node->degree=degree;
    node->percentage=percentage;
    node->color=color;
    node->next=next;
    return node;
}
void UIColorStop_Free(UIColorStop* item) {
    if(item->color != NULL) UIColorType_Free(item->color);
    if(item->next != NULL) UIColorStop_Free(item->next);
    free(item);
}
static void UIBooleanType_Init(UIBooleanType *node) {
    node->is_set=0;
    node->b_value=0;
}
UIBooleanType* UIBooleanType_New() {
    UIBooleanType *node = calloc(1, sizeof(UIBooleanType));
    UIBooleanType_Init(node);
    return node;
}
UIBooleanType* UIBooleanType_With(int is_set, int b_value) {
    UIBooleanType *node = calloc(1, sizeof(UIBooleanType));
    node->is_set=is_set;
    node->b_value=b_value;
    return node;
}
void UIBooleanType_Free(UIBooleanType* item) {
    free(item);
}
static void UIStringType_Init(UIStringType *node) {
    node->is_set=0;
    node->s_value=NULL;
}
UIStringType* UIStringType_New() {
    UIStringType *node = calloc(1, sizeof(UIStringType));
    UIStringType_Init(node);
    return node;
}
UIStringType* UIStringType_With(int is_set, char* s_value) {
    UIStringType *node = calloc(1, sizeof(UIStringType));
    node->is_set=is_set;
    node->s_value=s_value;
    return node;
}
void UIStringType_Free(UIStringType* item) {
    if(item->s_value != NULL) free(item->s_value);
    free(item);
}
static void UIStructure_Init(UIStructure *node) {
    node->x = UIFloatType_New();
    node->y = UIFloatType_New();
    node->left = UIFloatType_New();
    node->top = UIFloatType_New();
    node->id = UIStringType_New();
    node->width = UIFloatType_New();
    node->height = UIFloatType_New();
    node->direction = UIStringType_New();
    node->align = UIStringType_New();
    node->verticalAlign = UIStringType_New();
    node->innerWidth = UIFloatType_New();
    node->innerHeight = UIFloatType_New();
    node->lineBreak = UIBooleanType_New();
    node->overflow = UIStringType_New();
    node->fontSize = UIFloatType_New();
    node->fontFamily = UIStringType_New();
    node->color = UIColorType_New();
    node->backgroundColor = UIColorType_New();
    node->opacity = UIFloatType_New();
    node->rotate = UIFloatType_New();
    node->borderWidth = UIFloatType_New();
    node->borderColor = UIColorType_New();
    node->borderRadius = UIFloatType_New();
    node->svgPath = UIStringType_New();
    node->imageUrl = UIStringType_New();
    node->text = UIStringType_New();
    node->linearGradient = UIColorStop_New();
    node->radialGradient = UIColorStop_New();
    node->margin = UIFloatType_New();
    node->marginLeft = UIFloatType_New();
    node->marginRight = UIFloatType_New();
    node->marginBottom = UIFloatType_New();
    node->marginTop = UIFloatType_New();
    node->padding = UIFloatType_New();
    node->paddingLeft = UIFloatType_New();
    node->paddingRight = UIFloatType_New();
    node->paddingBottom = UIFloatType_New();
    node->paddingTop = UIFloatType_New();
    node->shadowColor = UIColorType_New();
    node->shadowOffsetX = UIFloatType_New();
    node->shadowOffsetY = UIFloatType_New();
    node->shadowOpacity = UIFloatType_New();
    node->shadowRadius = UIFloatType_New();
    node->parent = NULL;
    node->nextSibling   = NULL;
    node->prevSibling   = NULL;
    node->firstChild   = NULL;
    node->lastChild   = NULL;
    node->tagName = NULL;
    UICalculated_Init(&(node->calculated));
}
UIStructure *UIStructure_New() {
    UIStructure *node = calloc(1, sizeof(UIStructure));
    UIStructure_Init(node);
    return node;
}

void UIStructure_Free(UIStructure *node) {
    UIFloatType_Free(node->x);
    UIFloatType_Free(node->y);
    UIFloatType_Free(node->left);
    UIFloatType_Free(node->top);
    UIStringType_Free(node->id);
    UIFloatType_Free(node->width);
    UIFloatType_Free(node->height);
    UIStringType_Free(node->direction);
    UIStringType_Free(node->align);
    UIStringType_Free(node->verticalAlign);
    UIFloatType_Free(node->innerWidth);
    UIFloatType_Free(node->innerHeight);
    UIBooleanType_Free(node->lineBreak);
    UIStringType_Free(node->overflow);
    UIFloatType_Free(node->fontSize);
    UIStringType_Free(node->fontFamily);
    UIColorType_Free(node->color);
    UIColorType_Free(node->backgroundColor);
    UIFloatType_Free(node->opacity);
    UIFloatType_Free(node->rotate);
    UIFloatType_Free(node->borderWidth);
    UIColorType_Free(node->borderColor);
    UIFloatType_Free(node->borderRadius);
    UIStringType_Free(node->svgPath);
    UIStringType_Free(node->imageUrl);
    UIStringType_Free(node->text);
    UIColorStop_Free(node->linearGradient);
    UIColorStop_Free(node->radialGradient);
    UIFloatType_Free(node->margin);
    UIFloatType_Free(node->marginLeft);
    UIFloatType_Free(node->marginRight);
    UIFloatType_Free(node->marginBottom);
    UIFloatType_Free(node->marginTop);
    UIFloatType_Free(node->padding);
    UIFloatType_Free(node->paddingLeft);
    UIFloatType_Free(node->paddingRight);
    UIFloatType_Free(node->paddingBottom);
    UIFloatType_Free(node->paddingTop);
    UIColorType_Free(node->shadowColor);
    UIFloatType_Free(node->shadowOffsetX);
    UIFloatType_Free(node->shadowOffsetY);
    UIFloatType_Free(node->shadowOpacity);
    UIFloatType_Free(node->shadowRadius);
    if(node->tagName != NULL) free(node->tagName);
    free(node);
}
int UIStructure_AddChild(UIStructure* this, UIStructure* node) {
    if(node->parent != NULL) {
        UIStructure_RemoveChild(node->parent, node);
    }
    
    node->prevSibling = this->lastChild;
    if(this->lastChild != NULL) {
        this->lastChild->nextSibling = node;
        this->lastChild = node;
    } else {
        this->firstChild = node;
        this->lastChild = node;
    }
    node->nextSibling = NULL;
    node->parent = this;
    return 1;
}
int UIStructure_RemoveChild(UIStructure* this, UIStructure* node) {
    if(node->parent == NULL) return 0;
    if(node->parent != this) return 0;
    
    if(this->firstChild == node) this->firstChild = node->nextSibling;
    if(this->lastChild == node) this->lastChild = node->prevSibling;
    
    UIStructure *prev = node->prevSibling;
    UIStructure *next = node->nextSibling;
    
    if(prev != NULL) {
        prev->nextSibling = node->nextSibling;
    }
    if(next != NULL) {
        next->prevSibling = node->prevSibling;
    }
    node->parent = NULL;
    return 1;
}
