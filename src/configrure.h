
/**
 * Encoding:utf-8
 * Wangbei
 * Configure.h
 * 2019/03/03
 * 
 * This header file is for reading configure json
 * file to configure The Bing application, It contains
 * the desktop that user is using, the command that
 * set backgroud image, the base url to get image,
 * the User-Agent to get html and image from bing
 * and the bing url to get today wallpaper in bing
 * 
**/

#ifndef CONFIGURE_H
#define CONFIGURE_H

#include "cJSON.h"

char *configureFile();

cJSON *loadConfigure(cJSON *json);

char *getStringConfigure(cJSON *root, char *key);

void cJsonFree(cJSON *root);

// add two char array
char *strAdd(char *str1, char *str2);

void strFree(char *str);

//get user home path

char *homePath(void);

void createImagePath(void);

char *imagePath(void);

//parse html json to get image url

char *imageUrl(char *html);


#endif