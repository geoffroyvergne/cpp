#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include "gumbo.h"

class Tag {
    public:
        Tag(std::string name, std::string text);
        std::string name;
        std::string content;
        std::string toString();
};

Tag::Tag(std::string name, std::string content) {
    Tag::name = name;
    Tag::content = content;
}

std::string Tag::toString() {
    return "Name : " + Tag::name + " => Text : " + Tag::content;
}
 
void parse(GumboNode* node);
std::string getHtmlFromFile(std::string fileName);

std::vector<Tag> tagList;

int main() {    
    std::string contents = getHtmlFromFile("test.html");

    //std::string contents = "<div><b>test</b><b>test2</b><h1>Hello, World!</h1><h1>Hello agein</h1></div>";
    //std::cout << contents << std::endl;

    //GumboOutput* output = gumbo_parse(contents.c_str());
    GumboOutput* output = gumbo_parse_with_options(&kGumboDefaultOptions, contents.data(), contents.length());

    parse(output->root); 

    for (Tag tag: tagList){
        std::cout << tag.toString() << std::endl;
    }

    gumbo_destroy_output(&kGumboDefaultOptions, output);
}

void parse(GumboNode* node) {
    
    if(node->type == GUMBO_NODE_TEXT) {
        std::string name = gumbo_normalized_tagname(node->parent->v.element.tag);
        std::string content = node->v.text.text;

        Tag currentTag(name, content);
        //currentTag.tag = tag;
        //currentTag.text = content;

        //std::cout << "Tag : " << tag << " => Text : " << content << std::endl;
        //std::cout << currentTag.toString() << std::endl;

        tagList.push_back(currentTag);
    }

    if (node->type == GUMBO_NODE_ELEMENT) {
        GumboVector* children = &node->v.element.children;
        for (unsigned int i = 0; i < children->length; ++i) {
            parse((GumboNode*) children->data[i]);
        }
    }
}

std::string getHtmlFromFile(std::string fileName) {
    std::ifstream in(fileName, std::ios::in | std::ios::binary);
    if (!in) {
        std::cout << "File " << fileName << " not found!\n";
        exit(EXIT_FAILURE);
    }

    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();

    return contents;
}
