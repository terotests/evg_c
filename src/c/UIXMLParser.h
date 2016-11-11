#include <string.h>
#include <stdint.h>
#include "UIStructure.h"

// function declarations
UIStructure *parseXMLNodes( xmlNode *node,  xmlNode *parentNode);
void test_walk_tree( UIStructure *node );