#include <iostream>
#include <string>
#include <curl/curl.h>
#include <jsoncpp/json/json.h>

static size_t WriteDataToVariable(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main(void)
{
  CURL *curl;
  std::string writeData;
  std::string result;
  curl = curl_easy_init();
      if(curl) {
	    curl_easy_setopt(curl, CURLOPT_URL, "https://publish.twitter.com/oembed?url=https://twitter.com/jack/status/20");
            
	    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteDataToVariable);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &writeData);
          
	    curl_easy_perform(curl);
            curl_easy_cleanup(curl);
      }
    Json::Reader readThenParse;
    Json::Value dataJson; 
    readThenParse.parse(writeData, dataJson); 
     result = "THE DATA RETRIEVED FROM THE URL WAS, " + dataJson["url"].asString() + 
	      " THE AUTHOR IS, "+dataJson["author_name"].asString()+ " AND WE ALL WANT A TYPE LIKE THIS " + dataJson["type"].asString()+ "$$";
    
    std::cout <<  result << std::endl;
  return 0;
}
