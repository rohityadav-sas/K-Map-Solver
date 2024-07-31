#include <curl/curl.h>
#include <iostream>
#include <string>
#include <sstream>
#include "http_request.h"

// This structure will be used to hold data in memory
struct MemoryStruct
{
    char *memory;
    size_t size;
};

// Callback function to write data to MemoryStruct
size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    char *ptr = (char *)realloc(mem->memory, mem->size + realsize + 1);
    if (ptr == NULL)
    {
        std::cerr << "Not enough memory (realloc returned NULL)" << std::endl;
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

void postRequest(const std::string &url, const std::string &body, const std::string &outputFileName)
{
    CURL *curl;
    CURLcode res;
    struct MemoryStruct chunk;

    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl)
    {
        // Initialize MemoryStruct
        chunk.memory = (char *)malloc(1); // Initial memory allocation
        chunk.size = 0;                   // No data at this point

        // Set the URL for the request
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Set the HTTP POST method
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        // Set the POST data
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());

        // Set the Content-Type header
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Set the write callback function to use MemoryStruct
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK)
        {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        else
        {
            // Only create and write to the file if data was received
            if (chunk.size > 0)
            {
                FILE *file = fopen(outputFileName.c_str(), "wb");
                if (file)
                {
                    fwrite(chunk.memory, 1, chunk.size, file);
                    fclose(file);
                }
                else
                {
                    std::cerr << "Failed to open file for writing." << std::endl;
                }
            }
        }

        // Clean up
        free(chunk.memory);
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        curl_global_cleanup();
    }
    else
    {
        std::cerr << "Failed to initialize curl." << std::endl;
        curl_global_cleanup();
    }
}
