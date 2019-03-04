
#include "configrure.h"
#include "bing.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    cJSON *root = NULL;
    root = loadConfigure(root);
    char *url = getStringConfigure(root,"bing-url");
    char *agent = getStringConfigure(root,"user-agent");

    char *html = getImagesJson(url,agent);

    char *iurl = imageUrl(html);
    char *path = imagePath();

    char *fpath = strAdd(homePath(),"/Bing");
    int flag = access(fpath,F_OK);
    if(flag == -1)
        createImagePath();
    free(fpath);

    getImageFile(iurl,path,agent);

    char *desktop = getStringConfigure(root,"desktop");
    char *baseCmd = getStringConfigure(root, desktop);
    char *lcmd = strAdd(baseCmd,"\"");
    char *ccmd = strAdd(lcmd,path);
    char *cmd = strAdd(ccmd,"\"");

    system(cmd);
    
    free(url);
    free(agent);
    free(html);
    free(iurl);
    free(path);
    free(desktop);
    free(baseCmd);
    free(lcmd);
    free(ccmd);
    free(cmd);
}