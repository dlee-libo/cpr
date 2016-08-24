#ifndef CPR_CURL_HOLDER_H
#define CPR_CURL_HOLDER_H

#include <memory>

#include <curl/curl.h>

namespace cpr {

struct CurlHolder {
    CURL* handle;
    std::unique_ptr<struct curl_slist, std::function<void(struct curl_slist*)>> chunk;
    std::unique_ptr<struct curl_httppost, std::function<void(struct curl_httppost*)>> formdata;
    char error[CURL_ERROR_SIZE];
    CurlHolder(): chunk(nullptr, [](struct curl_slist* ptr) {
        curl_slist_free_all(ptr);
    }), formdata(nullptr, [](struct curl_httppost* ptr) {
        curl_formfree(ptr);
    }) {
    }
};

} // namespace cpr

#endif
