
#include "bing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

void initString(struct String *s)
{
    s->len = 0;
    s->ptr = malloc(s->len + 1);
    if(s->ptr == NULL)
    {
        fprintf(stderr,"malloc() failed\n");
        exit(EXIT_FAILURE);
    }
    s->ptr[0] = '\0';
}

size_t writeFunc(void *ptr, size_t size, size_t nmemb, struct String *s)
{
    size_t new_len = s->len + size*nmemb;
    s->ptr = realloc(s->ptr,new_len+1);
    if(s->ptr == NULL)
    {
        fprintf(stderr,"malloc() failed\n");
        exit(EXIT_FAILURE);
    }

    memcpy(s->ptr+s->len,ptr,size*nmemb);
    s->ptr[new_len] = '\0';
    s->len = new_len;
    return size*nmemb;
}

size_t writeImage(void *ptr, size_t size, size_t nmemb, void *stream)
{
    int written = 0;
    written = fwrite(ptr,size,nmemb,stream);
    return written;
}

char *getImagesJson(char *url, char *agent)
{
    CURL *curl;
    CURLcode res;

    struct String s;
    initString(&s);

    curl = curl_easy_init();
    if(curl == NULL)
    {
        fprintf(stderr,"create curl object failed\n");
        exit(EXIT_FAILURE);
    }
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers,agent);

    curl_easy_setopt(curl,CURLOPT_URL,url);
    curl_easy_setopt(curl,CURLOPT_HTTPHEADER,headers);
    curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,writeFunc);
    curl_easy_setopt(curl,CURLOPT_WRITEDATA,&s);

    res = curl_easy_perform(curl);
    if(res != CURLE_OK)
    {
        fprintf(stderr,"curl_easy_perform() failed\n");
        exit(EXIT_FAILURE);
    }

    curl_easy_cleanup(curl);

    return s.ptr;
}

void getImageFile(char *url, char *path, char *agent)
{
    CURL *curl;
    CURLcode res;

    FILE *file = NULL;
    file = fopen(path, "wb");
    if(file == NULL)
    {
        fprintf(stderr, "create file %s failed",path);
        exit(EXIT_FAILURE);
    }

    curl = curl_easy_init();
    if(curl == NULL)
    {
        fprintf(stderr,"create curl object failed\n");
        exit(EXIT_FAILURE);
    }

    curl = curl_easy_init();

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers,agent);
    curl_easy_setopt(curl,CURLOPT_HTTPHEADER,headers);
    curl_easy_setopt(curl,CURLOPT_URL,url);
    curl_easy_setopt(curl,CURLOPT_WRITEDATA,(void *)file);
    curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,writeImage);

    res = curl_easy_perform(curl);
    if(res != CURLE_OK)
    {
        fprintf(stderr,"curl_easy_perform() failed\n");
        exit(EXIT_FAILURE);
    }

    curl_easy_cleanup(curl);

    fclose(file);

}