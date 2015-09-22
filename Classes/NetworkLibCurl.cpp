//
//  NetworkLibCurl.cpp
//  Card13
//
//  Created by Hiroki Ariji on 2015/08/23.
//
//

#include "NetworkLibCurl.h"
#include "curl.h"


using namespace cocos2d;

static char errorBuffer[CURL_ERROR_SIZE];
static std::string buffer;

static int writer(char *data, size_t size, size_t nmemb, std::string *buffer)
{
    int result = 0;
    
    if (buffer != NULL)
    {
        //バッファ追記
        buffer->append(data, size * nmemb);
        result = size * nmemb;
    }
    
    return result;
}

void Post(const char *post_command){
    CURL *curl;
    CURLcode res = CURLE_FAILED_INIT;
    
    // POSTするデータ
    const char *post_data = "";//"/send_message?type=4";
//    const char *post_command = "http://127.0.0.1:3000/send_message?type=4";
    
    // 初期化
    curl = curl_easy_init();
    
    // POSTす
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
        curl_easy_setopt(curl, CURLOPT_URL, post_command);
//        curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.1.5:1024");
        curl_easy_setopt(curl, CURLOPT_HEADER, 0);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(post_data));
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        
    
        // 実行
        res = curl_easy_perform(curl);
    
        curl_easy_cleanup(curl);

        if (res == CURLE_OK) {
            //レスポンス表示
            printf("hoge;;AUCCESS!");
        } else {
            //エラー表示
            printf("hoge;;ERROR!");
        }
    }
}


bool Get(const char *get_command){
    CURL *curl;
    CURLcode res = CURLE_FAILED_INIT;
    bool result = false;
    
    curl = curl_easy_init();    
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
        curl_easy_setopt(curl, CURLOPT_URL, get_command);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

        // 実行
        res = curl_easy_perform(curl);
        
        curl_easy_cleanup(curl);

        if (res == CURLE_OK) {
            printf("response data : %s",buffer.c_str());
            //レスポンス表示
            if(std::string::npos == buffer.find("ON")){
                result = false;
            }else{
                result = true;
            }
        } else {
            result = false;
        }
    }
    return result;
}


