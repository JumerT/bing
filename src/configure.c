

#include "configrure.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

char *configureFile()
{
    char *home = homePath();
    char *path = strAdd(home,"/.bing/bing-configure.json");
    return path;
}

cJSON *loadConfigure(cJSON *json)
{
    char *filename = configureFile();
    long len = 0; 
    int temp; 
     
    char *JSON_content; 
    FILE* fp = fopen(filename, "rb+"); 
     
    if(!fp) 
    { 
        fprintf(stderr,"open file %s failed.\n", filename); 
        exit(EXIT_FAILURE);
    } 
    fseek(fp, 0, SEEK_END); 
    len = ftell(fp); 
    if(0 == len) { return NULL; } 
    fseek(fp, 0, SEEK_SET); 
    JSON_content = (char*) malloc(sizeof(char) * len); 
    temp = fread(JSON_content, 1, len, fp); 
    fclose(fp); 
    json = cJSON_Parse(JSON_content);

    if (json == NULL) { return NULL; } 

    free(JSON_content);
    free(filename);

    return json;
}

char *getStringConfigure(cJSON *root, char *key)
{
    cJSON *item = NULL;
    item = cJSON_GetObjectItem(root,key);
    long len = strlen(item->valuestring);
    char *value = malloc(len+1);
    memcpy(value,item->valuestring,len);
    value[len] = '\0';
    return value;
}

void cJsonFree(cJSON *root)
{
    cJSON_free(root);
}

char *strAdd(char *str1, char *str2)
{
    long len1 = strlen(str1);
    long len2 = strlen(str2);

    char *str = malloc(len1+len2+1);
    memcpy(str,str1,len1);
    memcpy(str+len1,str2,len2);

    str[len1+len2] = '\0';
    return str;
}

void strFree(char *str)
{
    free(str);
}

char *homePath(void)
{
    char *home = getenv("HOME");
    return home;
}

void createImagePath(void)
{
    char *home = homePath();
    char *bing_path = strAdd(home,"/Bing");
    int status;

    status = mkdir(bing_path,S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH);

    if(status != 0)
    {
        fprintf(stderr,"create folder %s failed",bing_path);
        exit(EXIT_FAILURE);
    }
    strFree(bing_path);
}

char *imagePath(void)
{
    time_t ntime;
    struct tm *tinfo;
    char ipath[128];

    time(&ntime);

    tinfo = localtime(&ntime);
    strftime(ipath,sizeof(ipath),"%Y_%m_%d.jpg",tinfo);

    char *home = homePath();
    home = strAdd(home,"/Bing/");

    char *path = strAdd(home,ipath);
    strFree(home);

    return path;
}


char *imageUrl(char *html)
{
    cJSON *root = NULL;
    cJSON *image = NULL;

    root = cJSON_Parse(html);
    image = cJSON_GetObjectItem(root,"images");
    image = cJSON_GetArrayItem(image,0);
    image = cJSON_GetObjectItem(image,"url");

    cJSON *croot = NULL;
    croot = loadConfigure(croot);

    char *base_url = getStringConfigure(croot,"base-url");
    char *full_url = strAdd(base_url,image->valuestring);

    free(base_url);
    cJSON_free(croot);
    cJSON_free(root);

    return full_url;
}