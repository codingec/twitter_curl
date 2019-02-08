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
	    //AUTHENTICATION VIA URL
	    //curl_easy_setopt(curl, CURLOPT_URL, "https://api.twitter.com/oauth/authorize?oauth_token=Z6eEdO8MOmk394WozF5oKyuAv855l4Mlqo7hhlSLik");
            //CHANGE THE URL FOR  THIS TO GET THE TWEETS,  https://api.twitter.com/1.1/statuses/user_timeline.json?screen_name=twitterapi&count=2
	    curl_easy_setopt(curl, CURLOPT_URL, "https://publish.twitter.com/oembed?url=https://twitter.com/jack/status/20");
            //READ AND  STORE  DATA IN A VARIABLE
	    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteDataToVariable);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &writeData);
            //STORE IN MEMORY
	    curl_easy_perform(curl);
            curl_easy_cleanup(curl);
      }
    Json::Reader readThenParse;
    Json::Value dataJson;
    //THE DATA THAT WAS STORED IN A VARIABLE IS  GOING TO BE PARSED AS A JSON
    readThenParse.parse(writeData, dataJson);
    //MAKE A LONG STRING, SO YOU CAN PRINT ON SCREEN
     result = "THE DATA RETRIEVED FROM THE URL WAS, " + dataJson["url"].asString() + 
	      " THE AUTHOR IS, "+dataJson["author_name"].asString()+ " AND WE ALL WANT A TYPE LIKE THIS " + dataJson["type"].asString()+ "$$";
    //WRITE DATA ON THE CONSOLE
    std::cout <<  result << std::endl;
  return 0;
}
