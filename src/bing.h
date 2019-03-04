
/**
 * 
 * Encoding: utf-8
 * Wangbei
 * bing.h
 * 2019/03/03
 * 
 * This is the file to access bing.cn to get wallpaper
 * 
**/


#ifndef BING_H
#define BING_H

#include <stdio.h>

struct String
{
    size_t len;
    char *ptr;
};

void initString(struct String *s);

size_t writeFunc(void *ptr, size_t size, size_t nmemb, struct String *s);

size_t writeImage(void *ptr, size_t size, size_t nmemb, void *stream);

char *getImagesJson(char *url, char *agent);

void getImageFile(char *url, char *path, char *agent);


#endif