#ifndef CPR_CURL_HOLDER_H
#define CPR_CURL_HOLDER_H

#include <memory>

#include <curl/curl.h>

namespace cpr {

    struct curl_slist_deleter {
        void operator()(struct curl_slist* ptr) {
            curl_slist_free_all(ptr);
        }
    };

    struct curl_form_deleter {
        void operator()(struct curl_httppost* ptr) {
            curl_formfree(ptr);
        }
    };

struct CurlHolder {
    CURL* handle;
    std::unique_ptr<struct curl_slist, curl_slist_deleter> chunk;
    std::unique_ptr<struct curl_httppost, curl_form_deleter> formdata;
    char error[CURL_ERROR_SIZE];
    CurlHolder(): chunk(nullptr), formdata(nullptr) {
    }
};

} // namespace cpr

#endif
