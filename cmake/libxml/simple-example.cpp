//#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <libxml2/libxml/parser.h>

int main() {
    xmlDocPtr doc;
    xmlNodePtr root;

    // open xml file
    doc = xmlParseFile("catalog.xml");
    if(doc == NULL) {
        //fprintf(stderr, "Bad XML Document\n");
        std::cout << "Bad XML Document" << std::endl;
        return EXIT_FAILURE;
    }

    // get root
    root = xmlDocGetRootElement(doc);
    if(root == NULL) {
        //fprintf(stderr, "empty document\n");
        std::cout << "empty document" << std::endl;
        xmlFreeDoc(doc);
        return EXIT_FAILURE;
    }

    //printf("Root document : %s\n", root->name);
    std::cout << "Root document : " << root->name << std::endl;

    //free memory
    xmlFreeDoc(doc);

    return EXIT_SUCCESS;
}