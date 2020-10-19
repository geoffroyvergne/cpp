#include <iostream>
#include <curl/curl.h>
#include <string>

#if !CURL_AT_LEAST_VERSION(7, 62, 0)
#error "this example requires curl 7.62.0 or later"
#endif

class WebPage {
    public:
        //WebPage();
        std::string url;
        int port;
        std::string sheme;
        std::string content;
        std::string header;
        std::string contentType;
        int httpCode;
        double elapsed;
        std::string toString();
};

std::string WebPage::toString() {
    std::string result = "WebPage => ";
    
    result.append("Content : " + std::to_string(WebPage::content.length()) + "\n");
    result.append("Header : " + std::to_string(WebPage::header.length()) + "\n");
    result.append("HTTP Code : " + std::to_string(WebPage::httpCode) + "\n");
    result.append("ContentType : " + WebPage::contentType + "\n");

    return result;
}

class WebUrl {
    public:
        //WebUrl();        
        std::string url;
        std::string host;
        std::string path;
        int port;
        std::string query;
        std::string sheme;
        std::string fragment;
        std::string toString();
};

std::string WebUrl::toString() {
    std::string result = "WebUrl => ";

    result.append("url : " + WebUrl::url + "\n");
    result.append("host : " + WebUrl::host + "\n");
    result.append("path : " + WebUrl::path + "\n");


    return result;
}

WebPage* httpGet(std::string url);
WebUrl* parseUrl(std::string url);
void fail(CURL *h);
size_t writefunc(void *ptr, size_t size, size_t nmemb, std::string *s);

int main() {
    //std::cout << "url get test " << std::endl;
    std::string url = "https://www.google.fr/";

    WebUrl* webUrl = parseUrl(url);
    WebPage* webPage = httpGet(url);

    std::cout << webUrl->toString() << std::endl;
    std::cout << webPage->toString() << std::endl;

    delete(webPage);
    delete(webUrl);
    
    return EXIT_SUCCESS;
}

WebUrl* parseUrl(std::string url) {
    WebUrl* webUrl = new WebUrl();
    webUrl->url = url;

    CURLU *curlu;
    CURLUcode ucode;

    char *host;
    //std::string host;
    char *path;

    curlu = curl_url();
    if(!curlu) return webUrl;

    ucode = curl_url_set(curlu, CURLUPART_URL, url.c_str(), 0);

    ucode = curl_url_get(curlu, CURLUPART_HOST, &host, 0);
    if(!ucode) {
        //printf("Host name : %s \n", host);
        //std::cout << "Hostname : " << host << std::endl;
        webUrl->host = host;
        curl_free(host);
    }

    ucode = curl_url_get(curlu, CURLUPART_PATH, &path, 0);
    if(!ucode) {
        //printf("Path : %s \n", path);
        //std::cout << "Path : " << path << std::endl;
        webUrl->path = path;
        curl_free(path);
    }

    //CURLUPART_PORT
    //CURLUPART_QUERY
    //CURLUPART_SCHEME
    //CURLUPART_FRAGMENT
    //CURLUPART_URL
    //CURLUPART_OPTIONS

    return webUrl;
}

WebPage* httpGet(std::string url) {
    WebPage* webPage = new WebPage();
    webPage->url = url;

    CURL *curl = curl_easy_init();

    if(curl) {        
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        //curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.42.0");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        
        std::string content;        
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);

        std::string headerString;        
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &headerString);

        CURLcode res = curl_easy_perform(curl);

        //std::cout << "content : " << content.length() << std::endl;
        //std::cout << "header : " << headerString.length() << std::endl;
        webPage->content = content;
        webPage->header = headerString;

        //std::string *contentType;
        char *contentType;
        curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &contentType);
        //std::cout << "Content type : " << contentType << std::endl;        
        webPage->contentType = contentType;

        int httpCode = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
        //std::cout << "HTTP result : " << httpCode << std::endl;
        webPage->httpCode = httpCode;

        double elapsed;
        curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
        //std::cout << "elapsed : " << elapsed << std::endl;
        webPage->elapsed = elapsed;

        char* effectiveUrl;
        curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &effectiveUrl);
        //std::cout << "url : " << url << std::endl;
        webPage->url = effectiveUrl;

        //CURLINFO_HTTP_VERSION
        //CURLINFO_SCHEME
        //CURLINFO_TOTAL_TIME
        
        curl_easy_cleanup(curl);
        
    }
    return webPage;
}

void fail(CURLU *curlu) {
    curl_url_cleanup(curlu); /* free url handle */
    EXIT_FAILURE;
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, std::string *s) {
  s->append(static_cast<char *>(ptr), size*nmemb);
  return size*nmemb;
}
