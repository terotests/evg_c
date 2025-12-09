#ifndef UIXMLPARSER_H_INCLUDED
#define UIXMLPARSER_H_INCLUDED

#include <string.h>
#include <stdint.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "UIStructure.h"

// function declarations
UIStructure *parseXMLNodes( xmlNode *node,  xmlNode *parentNode);
void test_walk_tree( UIStructure *node );

#endif