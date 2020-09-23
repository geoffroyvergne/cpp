#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include "gumbo.h"

class Tag {
    public:
        //Tag(std::string name, std::string text, std::string src);
        //Tag();
        std::string name;
        std::string content;
        std::string src;
        std::string href;
        std::string toString();
};

/*Tag::Tag(std::string name, std::string content, std::string src) {
    Tag::name = name;
    Tag::content = content;
    Tag::src = src;
}*/

std::string Tag::toString() {
    std::string result;

    !Tag::name.empty() ? result.append("'Name' : " + Tag::name + " ") : result.append(" ");
    !Tag::content.empty() ? result.append("'Content' : " + Tag::content + " ") : result.append(" ");
    !Tag::src.empty() ? result.append("'Src' : " + Tag::src + " ") : result.append(" ");
    !Tag::href.empty() ? result.append("'Href' : " + Tag::href + " ") : result.append(" ");

    return result;
}
 
void parse(GumboNode* node);
std::string getHtmlFromFile(std::string fileName);

std::vector<Tag*> tagList;

int main() {    
    std::string contents = getHtmlFromFile("test.html");

    //std::string contents = "<div><b>test</b><b>test2</b><h1>Hello, World!</h1><h1>Hello agein</h1></div>";
    //std::cout << contents << std::endl;

    //GumboOutput* output = gumbo_parse(contents.c_str());
    GumboOutput* output = gumbo_parse_with_options(&kGumboDefaultOptions, contents.data(), contents.length());

    parse(output->root); 

    for (Tag* tag: tagList){
        std::cout << tag->toString() << std::endl;
    }

    gumbo_destroy_output(&kGumboDefaultOptions, output);
}

void parse(GumboNode* node) {
    
    if(node->type == GUMBO_NODE_TEXT) {
        std::string name = gumbo_normalized_tagname(node->parent->v.element.tag);
        std::string content = node->v.text.text;

         Tag* currentTag = new Tag();
        
        // A Href
        if(node->parent->v.element.tag == GUMBO_TAG_A) {
            //std::string href;
            GumboAttribute* gumboAttributeHref;
            if((gumboAttributeHref = gumbo_get_attribute(&node->parent->v.element.attributes, "href"))) {
                //href = gumboAttributeHref->value;
                currentTag->href = gumboAttributeHref->value;
            }
        }

        currentTag->name = name;
        currentTag->content = content;
        

        //std::cout << "Tag : " << tag << " => Text : " << content << std::endl;
        //std::cout << currentTag.toString() << std::endl;

        tagList.push_back(currentTag);

        //delete(currentTag);
    }

    // META tag

    // Link tag

    // IMG tag
    if (node->type == GUMBO_NODE_ELEMENT && node->v.element.tag == GUMBO_TAG_IMG) {
        std::string name = gumbo_normalized_tagname(node->v.element.tag);
        std::string src;
        
        GumboAttribute* gumboAttributeSrc;
        if((gumboAttributeSrc = gumbo_get_attribute(&node->v.element.attributes, "src"))) {
            src = gumboAttributeSrc->value;
        }

        //std::cout << "Tag : " << name << " => src : " << src << std::endl;

        Tag* currentTag = new Tag();
        currentTag->name = gumbo_normalized_tagname(node->v.element.tag);
        currentTag->src = src;

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
