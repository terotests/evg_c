#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "UICalculateLayout.h"
#include "UINativeText.h"


static void adjustLayoutParams( UIStructure *this, UIStructure *node ) {
    if( node == NULL || this == NULL ) return;
    if(this->width->is_set) {
        switch(this->width->unit) {
            case 1 : this->width->pixels = node->innerWidth->pixels * this->width->f_value / 100; break;
            case 2 : this->width->pixels = node->fontSize->pixels * this->width->f_value; break;
            case 3 : this->width->pixels = this->width->f_value;break;
            case 4 : this->width->pixels = node->innerHeight->pixels * this->width->f_value / 100; break;
            default : break;
        }
    } else {
        this->width->pixels = node->innerWidth->pixels;
    }
    if(this->height->is_set) {
        switch(this->height->unit) {
            case 1 : this->height->pixels = node->innerWidth->pixels * this->height->f_value / 100; break;
            case 2 : this->height->pixels = node->fontSize->pixels * this->height->f_value; break;
            case 3 : this->height->pixels = this->height->f_value;break;
            case 4 : this->height->pixels = node->innerHeight->pixels * this->height->f_value / 100; break;
            default : break;
        }
    } else {
        this->height->pixels = node->innerHeight->pixels;
    }
    if(this->left->is_set) {
        switch(this->left->unit) {
            case 1 : this->left->pixels = node->innerWidth->pixels * this->left->f_value / 100; break;
            case 2 : this->left->pixels = node->fontSize->pixels * this->left->f_value; break;
            case 3 : this->left->pixels = this->left->f_value;break;
            case 4 : this->left->pixels = node->innerHeight->pixels * this->left->f_value / 100; break;
            default : break;
        }
    }
    if(this->top->is_set) {
        switch(this->top->unit) {
            case 1 : this->top->pixels = node->innerWidth->pixels * this->top->f_value / 100; break;
            case 2 : this->top->pixels = node->fontSize->pixels * this->top->f_value; break;
            case 3 : this->top->pixels = this->top->f_value;break;
            case 4 : this->top->pixels = node->innerHeight->pixels * this->top->f_value / 100; break;
            default : break;
        }
    }
    if(this->borderWidth->is_set) {
        switch(this->borderWidth->unit) {
            case 1 : this->borderWidth->pixels = node->innerWidth->pixels * this->borderWidth->f_value / 100; break;
            case 2 : this->borderWidth->pixels = node->fontSize->pixels * this->borderWidth->f_value; break;
            case 3 : this->borderWidth->pixels = this->borderWidth->f_value;break;
            case 4 : this->borderWidth->pixels = node->innerHeight->pixels * this->borderWidth->f_value / 100; break;
            default : break;
        }
    }
    if(this->margin->is_set) {
        switch(this->margin->unit) {
            case 1 : this->margin->pixels = node->innerWidth->pixels * this->margin->f_value / 100; break;
            case 2 : this->margin->pixels = node->fontSize->pixels * this->margin->f_value; break;
            case 3 : this->margin->pixels = this->margin->f_value;break;
            case 4 : this->margin->pixels = node->innerHeight->pixels * this->margin->f_value / 100; break;
            default : break;
        }
    }
    if(!this->marginLeft->is_set) {
        this->marginLeft->pixels = this->margin->pixels;
    } else {
        switch(this->marginLeft->unit) {
            case 1 : this->marginLeft->pixels = node->innerWidth->pixels * this->marginLeft->f_value / 100; break;
            case 2 : this->marginLeft->pixels = node->fontSize->pixels * this->marginLeft->f_value; break;
            case 3 : this->marginLeft->pixels = this->marginLeft->f_value;break;
            case 4 : this->marginLeft->pixels = node->innerHeight->pixels * this->marginLeft->f_value / 100; break;
            default : break;
        }
    }
    if(!this->marginRight->is_set) {
        this->marginRight->pixels = this->margin->pixels;
    } else {
        switch(this->marginRight->unit) {
            case 1 : this->marginRight->pixels = node->innerWidth->pixels * this->marginRight->f_value / 100; break;
            case 2 : this->marginRight->pixels = node->fontSize->pixels * this->marginRight->f_value; break;
            case 3 : this->marginRight->pixels = this->marginRight->f_value;break;
            case 4 : this->marginRight->pixels = node->innerHeight->pixels * this->marginRight->f_value / 100; break;
            default : break;
        }
    }
    if(!this->marginTop->is_set) {
        this->marginTop->pixels = this->margin->pixels;
    } else {
        switch(this->marginTop->unit) {
            case 1 : this->marginTop->pixels = node->innerWidth->pixels * this->marginTop->f_value / 100; break;
            case 2 : this->marginTop->pixels = node->fontSize->pixels * this->marginTop->f_value; break;
            case 3 : this->marginTop->pixels = this->marginTop->f_value;break;
            case 4 : this->marginTop->pixels = node->innerHeight->pixels * this->marginTop->f_value / 100; break;
            default : break;
        }
    }
    if(!this->marginBottom->is_set) {
        this->marginBottom->pixels = this->margin->pixels;
    } else {
        switch(this->marginBottom->unit) {
            case 1 : this->marginBottom->pixels = node->innerWidth->pixels * this->marginBottom->f_value / 100; break;
            case 2 : this->marginBottom->pixels = node->fontSize->pixels * this->marginBottom->f_value; break;
            case 3 : this->marginBottom->pixels = this->marginBottom->f_value;break;
            case 4 : this->marginBottom->pixels = node->innerHeight->pixels * this->marginBottom->f_value / 100; break;
            default : break;
        }
    }
    
    if(this->padding->is_set) {
        switch(this->padding->unit) {
            case 1 : this->padding->pixels = node->innerWidth->pixels * this->padding->f_value / 100; break;
            case 2 : this->padding->pixels = node->fontSize->pixels * this->padding->f_value; break;
            case 3 : this->padding->pixels = this->padding->f_value;break;
            case 4 : this->padding->pixels = node->innerHeight->pixels * this->padding->f_value / 100; break;
            default : break;
        }
    }
    if(!this->paddingLeft->is_set) {
        this->paddingLeft->pixels = this->padding->pixels;
    } else {
        switch(this->paddingLeft->unit) {
            case 1 : this->paddingLeft->pixels = node->innerWidth->pixels * this->paddingLeft->f_value / 100; break;
            case 2 : this->paddingLeft->pixels = node->fontSize->pixels * this->paddingLeft->f_value; break;
            case 3 : this->paddingLeft->pixels = this->paddingLeft->f_value;break;
            case 4 : this->paddingLeft->pixels = node->innerHeight->pixels * this->paddingLeft->f_value / 100; break;
            default : break;
        }
    }
    if(!this->paddingRight->is_set) {
        this->paddingRight->pixels = this->padding->pixels;
    } else {
        switch(this->paddingRight->unit) {
            case 1 : this->paddingRight->pixels = node->innerWidth->pixels * this->paddingRight->f_value / 100; break;
            case 2 : this->paddingRight->pixels = node->fontSize->pixels * this->paddingRight->f_value; break;
            case 3 : this->paddingRight->pixels = this->paddingRight->f_value;break;
            case 4 : this->paddingRight->pixels = node->innerHeight->pixels * this->paddingRight->f_value / 100; break;
            default : break;
        }
    }
    if(!this->paddingTop->is_set) {
        this->paddingTop->pixels = this->padding->pixels;
    } else {
        switch(this->paddingTop->unit) {
            case 1 : this->paddingTop->pixels = node->innerWidth->pixels * this->paddingTop->f_value / 100; break;
            case 2 : this->paddingTop->pixels = node->fontSize->pixels * this->paddingTop->f_value; break;
            case 3 : this->paddingTop->pixels = this->paddingTop->f_value;break;
            case 4 : this->paddingTop->pixels = node->innerHeight->pixels * this->paddingTop->f_value / 100; break;
            default : break;
        }
    }
    if(!this->paddingBottom->is_set) {
        this->paddingBottom->pixels = this->padding->pixels;
    } else {
        switch(this->paddingBottom->unit) {
            case 1 : this->paddingBottom->pixels = node->innerWidth->pixels * this->paddingBottom->f_value / 100; break;
            case 2 : this->paddingBottom->pixels = node->fontSize->pixels * this->paddingBottom->f_value; break;
            case 3 : this->paddingBottom->pixels = this->paddingBottom->f_value;break;
            case 4 : this->paddingBottom->pixels = node->innerHeight->pixels * this->paddingBottom->f_value / 100; break;
            default : break;
        }
    }
    
    this->width->pixels = this->width->pixels - (this->marginLeft->pixels + this->marginRight->pixels);
    this->height->pixels = this->height->pixels - (this->marginTop->pixels + this->marginBottom->pixels);
    this->innerWidth->pixels = this->width->pixels - (this->paddingRight->pixels + this->paddingLeft->pixels + this->borderWidth->pixels*2);
    this->innerHeight->pixels = this->height->pixels - (this->paddingTop->pixels + this->paddingBottom->pixels + this->borderWidth->pixels*2);
    if(this->borderRadius->is_set) {
        switch(this->borderRadius->unit) {
            case 1 : this->borderRadius->pixels = this->width->pixels * this->borderRadius->f_value / 100;break;
            case 2 : this->borderRadius->pixels = this->fontSize->pixels * this->borderRadius->f_value;break;
            case 3 : this->borderRadius->pixels = this->borderRadius->f_value;break;
            case 4 : this->borderRadius->pixels = this->height->pixels * this->borderRadius->f_value / 100;break;
            default : break;
        }
    }
}

#define EQUALS(str1,str2) ((strcmp(str1,str2)==0))

static double _layoutNodes( UIStructure *node, UIRenderPosition *render_pos )  {
    if(node->lineBreak->b_value) { node->calculated.lineBreak = 1; }
    double elem_h  = node->paddingTop->pixels + node->paddingBottom->pixels;
    if(node->height->is_set) { elem_h += node->innerHeight->pixels; }
    UIRenderPosition *child_render_pos = UIRenderPosition_With( node->paddingLeft->pixels, node->paddingTop->pixels, render_pos->scale);
    
    // calculating the text size : calculateTextDimensions
    
    double child_heights = 0.0;
    double line_height   = 0.0;
    double row_width     = 0.0;
    double col_height    = 0.0;
    double current_y     = child_render_pos->y;
    double current_x     = child_render_pos->x;
    double inner_width   = node->innerWidth->pixels;
    double inner_height   = node->innerHeight->pixels;
    UIStructure *childNode = node->firstChild;
    UIStructure *lineStart = node->firstChild;
    UIStructure *lineEnd   = NULL;
    UIStructure *row_item  = NULL;
    if (node->direction->is_set && EQUALS(node->direction->s_value,"bottom-to-top")) {
        while(childNode) {
            child_render_pos->y = current_y;
            child_render_pos->x = current_x;
            child_render_pos = calculateUIStructureLayout(childNode, node, child_render_pos);
            if( childNode->calculated.absolute ) { childNode = childNode->nextSibling; continue;  };
            childNode->calculated.y = current_y + (inner_height - col_height - childNode->calculated.height);
            col_height += childNode->calculated.height;
            if( childNode->calculated.lineBreak ||  (col_height > inner_height && (col_height - inner_height > 0.5))) {
                child_heights += line_height;
                current_x += row_width;
                line_height   = 0;
                col_height    = 0;
                row_width     = 0;
                child_render_pos->x = current_x;
                child_render_pos->y = node->paddingTop->pixels;
                child_render_pos->scale = render_pos->scale;
                child_render_pos = calculateUIStructureLayout( childNode, node, child_render_pos);
                childNode->calculated.y = current_y + (inner_height - col_height - childNode->calculated.height);
                lineStart = childNode;
                lineEnd   = childNode;
                line_height   = childNode->calculated.height;
                row_width     = childNode->calculated.width;
            } else {
                if(childNode->calculated.width > row_width) { row_width = childNode->calculated.width; }
                lineEnd   = childNode;
            }
            childNode = childNode->nextSibling;
        };
        if(node->align->is_set && (EQUALS(node->align->s_value,"right") || EQUALS(node->align->s_value,"center"))) {
            if(lineStart && lineEnd) {
                row_item = lineStart;
                while( row_item ) {
                    double deltaX = row_width - (row_item->calculated.width);
                    if(EQUALS(node->align->s_value, "center")) { deltaX = deltaX / 2; } // vertical align center
                    row_item->calculated.x += deltaX;
                    if(row_item == lineEnd) break;
                    row_item = row_item->nextSibling;
                };
            }
        };
    } else {
        while(childNode) {
            child_render_pos->y = current_y;
            child_render_pos->scale = render_pos->scale;
            child_render_pos = calculateUIStructureLayout(childNode, node, child_render_pos);
            if( childNode->calculated.absolute) { childNode = childNode->nextSibling; continue; }
            row_width     += childNode->calculated.width;
            if( childNode->calculated.lineBreak ||  (row_width > inner_width && (row_width - inner_width > 0.5))) {
                if(node->align->is_set && (EQUALS(node->align->s_value,"right") || EQUALS(node->align->s_value,"center"))) {
                    // align right
                    double deltaX = node->paddingLeft->pixels + inner_width + 0.5*lineEnd->marginLeft->pixels - lineEnd->calculated.x - lineEnd->calculated.width;
                    if(node->align->is_set && (EQUALS(node->align->s_value,"center"))) { deltaX = deltaX / 2; } // align center
                    row_item = lineStart;
                    while( row_item ) {
                        row_item->calculated.x += deltaX;
                        if(row_item == lineEnd) break;
                        row_item = row_item->nextSibling;
                    }
                }
                if(node->verticalAlign->is_set && ( EQUALS(node->verticalAlign->s_value, "bottom") || EQUALS(node->verticalAlign->s_value, "center") )) {
                    if(lineStart && lineEnd ) {
                        row_item = lineStart;
                        while( row_item ) {
                            double deltaY = line_height - (row_item->calculated.height);
                            if(EQUALS(node->verticalAlign->s_value,"center" )) { deltaY = deltaY / 2; } // vertical align center
                            row_item->calculated.y += deltaY;
                            if(row_item == lineEnd) break;
                            row_item = row_item->nextSibling;
                        };
                    }
                }
                child_heights += line_height;
                current_y += line_height;
                line_height   = 0;
                row_width     = 0;
                child_render_pos->x = node->paddingLeft->pixels;
                child_render_pos->y = current_y;
                child_render_pos = calculateUIStructureLayout(childNode, node,  child_render_pos);
                lineStart = childNode;
                lineEnd   = childNode;
                line_height = childNode->calculated.height;
                row_width     = childNode->calculated.width;
            } else {
                if((childNode->calculated.height > line_height) && (childNode->height->unit != 5)) { 
                    line_height = childNode->calculated.height; 
                }
                lineEnd = childNode;
                
                // fix: overriding the size
                if(!node->calculated.size_override  || (node->calculated.width_override < row_width)) {
                    
                    node->calculated.size_override  = 1;
                    node->calculated.width_override = row_width + node->paddingLeft->pixels + node->paddingRight->pixels;
                }
                
            }
            childNode = childNode->nextSibling;
        };
        if(node->align->is_set && (EQUALS(node->align->s_value,"right") || EQUALS(node->align->s_value,"center"))) {
            // align right
            if(lineStart && lineEnd) {
                UIStructure *lastItem = lineEnd;
                double deltaX = node->paddingLeft->pixels + inner_width + lastItem->marginLeft->pixels - lastItem->calculated.x - lastItem->calculated.width;
                if(node->align->is_set && (EQUALS(node->align->s_value,"center") )) { deltaX = deltaX / 2; } // align center
                row_item = lineStart;
                while(row_item) {
                    row_item->calculated.x += deltaX;
                    if(row_item == lineEnd) break;
                    row_item = row_item->nextSibling;
                };
            }
        }
        if(node->verticalAlign->is_set && ( EQUALS(node->verticalAlign->s_value,"bottom") || EQUALS(node->verticalAlign->s_value, "center") )) {
            if(lineStart && lineEnd) {
                row_item = lineStart;
                while( row_item ) {
                    double deltaY = line_height - (row_item->calculated.height);
                    if(EQUALS(node->verticalAlign->s_value,"center")) { deltaY = deltaY / 2; } // vertical align center
                    row_item->calculated.y += deltaY;
                    if(row_item == lineEnd) break;
                    row_item = row_item->nextSibling;
                };
            }
        }
    } 
    if(line_height > 0) { child_heights = child_heights + line_height; }
    if(!node->height->is_set) {
        elem_h += child_heights;
        // FIX: override the size if text font...
        if(strcmp(node->tagName, "Label") == 0) {
            // calculated width override
            
            if(node->text->is_set) {
                UITextDimensions *dim = calculateTextDimensions( node, inner_width );
                if(dim) {
                
                    node->calculated.size_override = 1;
                    node->calculated.width_override = dim->width;
                    
                    elem_h += dim->height;
                    
                    free(dim);
                }
            }
            
            /*
             var size = node.renderer.customSize( node.innerWidth.pixels )
             if(size) {
             elem_h += size.height;
             // fix : ??? overried width
             node.calculated.width_override = size.width;
             }
             */
        }
    }
    UIRenderPosition_Free(child_render_pos);
    return elem_h;
} 

UIRenderPosition* calculateUIStructureLayout( UIStructure *this, UIStructure *parentNode, UIRenderPosition *render_pos  ) { 
    UIRenderPosition *newPOS = UIRenderPosition_With( render_pos->x,  render_pos->y, this->scale->is_set ? this->scale->f_value : render_pos->scale );
    double render_start_y = render_pos->y;
    UIStructure *node = this;
    adjustLayoutParams(this, parentNode);
    double elem_h = _layoutNodes(this, render_pos);
    node->calculated.render_height = elem_h;    
    node->calculated.render_width  = node->width->pixels;
    node->calculated.height = elem_h + node->marginTop->pixels + node->marginBottom->pixels;
    node->calculated.width  = node->width->pixels + node->marginLeft->pixels + node->marginRight->pixels;
    node->calculated.scale  = newPOS->scale;

    double left_margin = node->marginLeft->pixels;
    double top_margin = node->marginTop->pixels;
    double bottom_margin = node->marginBottom->pixels;

    if( node->left->is_set ) {
        node->calculated.x = left_margin + (parentNode->calculated.scale * parentNode->paddingLeft->pixels) + node->left->pixels;
        node->calculated.absolute = 1;
    } else {
        node->calculated.x = render_pos->x + left_margin;
    }
    if( node->top->is_set ) {
        node->calculated.y = top_margin + (parentNode->calculated.scale * parentNode->paddingTop->pixels) + node->top->pixels;
        node->calculated.absolute = 1;
    } else {
        node->calculated.y = render_pos->y + top_margin;
    }
    if ( !node->left->is_set && !node->top->is_set) {
        newPOS->x += node->calculated.width;
        newPOS->y = render_start_y + ( elem_h + top_margin + bottom_margin );
    }

    node->calculated.height *= node->scale->is_set ? node->scale->f_value : 1;
    node->calculated.width *= node->scale->is_set ? node->scale->f_value : 1;
    UIRenderPosition_Free( render_pos );
    return newPOS;
}

