//#include "stdio.h"
#include <iostream>
#include <string>
#include "gumbo.h"

void displayText(GumboNode* node) {
    std::string tag = "NA";

    /*if(node->v.element.tag == GUMBO_TAG_H1) {
        tag = "H1";
        //std::cout << tag << std::endl;
    }*/

    if (node->type == GUMBO_NODE_ELEMENT && node->v.element.tag == GUMBO_TAG_H1) {
        std::cout << "tag : " << node->v.element.tag << " H1" << std::endl;
        tag = "H1";
    }

    //tag = node->v.element.tag;
    //tag = "h1";

    if (node->type == GUMBO_NODE_TEXT) {
        /*if(node->v.element.tag == GUMBO_TAG_H1) {
            std::cout << "H1" << std::endl;
            tag.append("H1");
        }*/
        
        std::cout 
        << "Tag : " << tag << " "
        << std::string(node->v.text.text) 
        << std::endl;
    } else {
        GumboVector* children = &node->v.element.children;
        for (unsigned int i = 0; i < children->length; ++i) {
            displayText((GumboNode*) children->data[i]);
        }
    }
}

int main() {
    GumboOutput* output = gumbo_parse("<div><b>test</b><b>test2</b><h1>Hello, World!</h1><h1>Hello agein</h1></div>");

    displayText(output->root);
    
    gumbo_destroy_output(&kGumboDefaultOptions, output);
}
