#include <cstdio>
#include <ctime>
#include <sstream>
#include <string>
#include <tchar.h>
#include <windows.h>
#include <winhttp.h>
#include <SDKDDKVer.h>

#include <json/json.h>

std::string getUpdates(const std::string& Token) {
    DWORD dwSize = 0;
    DWORD dwDownloaded = 0;
    LPSTR pszOutBuffer;
    BOOL  bResults = FALSE;
    HINTERNET  hSession = NULL, hConnect = NULL, hRequest = NULL;

    std::string fullAddress = "/bot";
    fullAddress.append(Token);
    fullAddress.append("/getUpdates");

    std::wstring stemp = std::wstring(fullAddress.begin(), fullAddress.end());
    LPCWSTR sw = stemp.c_str();
    //Request body
    LPSTR postdata = const_cast<char *>("{'offset': offset, 'timeout': 60}");

    // Use WinHttpOpen to obtain a session handle.
    hSession = WinHttpOpen(L"WinHTTP Example/1.0",
        WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS, 0);

    // Specify an HTTP server.
    if (hSession)
        hConnect = WinHttpConnect(hSession, L"api.telegram.org",
            INTERNET_DEFAULT_HTTPS_PORT, 0);
    
    // Create an HTTP request handle.
    if (hConnect)
        hRequest = WinHttpOpenRequest(hConnect, L"GET", sw,
            NULL, WINHTTP_NO_REFERER,
            WINHTTP_DEFAULT_ACCEPT_TYPES,
            WINHTTP_FLAG_SECURE);

    // Add a request header.
    if (hRequest)
        bResults = WinHttpAddRequestHeaders(hRequest,
            L"content-type:application/json",
            (ULONG)-1L,
            WINHTTP_ADDREQ_FLAG_ADD);

    // Send a request.
    if (hRequest)
        bResults = WinHttpSendRequest(hRequest,
            WINHTTP_NO_ADDITIONAL_HEADERS,
            -1L,
            postdata, strlen(postdata),
            strlen(postdata), 0);

    // End the request.
    if (bResults) bResults = WinHttpReceiveResponse(hRequest, NULL);

    std::string output = "";

    // Keep checking for data until there is nothing left.
    if (bResults)
    {
        do
        {
            // Check for available data.
            dwSize = 0;
            if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
                printf("Error %lu in WinHttpQueryDataAvailable.\n", GetLastError());

            // Allocate space for the buffer.
            pszOutBuffer = new char[dwSize + 1];
            if (!pszOutBuffer)
            {
                printf("Out of memory\n");
                dwSize = 0;
            }
            else
            {
                // Read the data.
                ZeroMemory(pszOutBuffer, dwSize + 1);

                if (!WinHttpReadData(hRequest, (LPVOID)pszOutBuffer, dwSize, &dwDownloaded))
                    printf("Error %lu in WinHttpReadData.\n", GetLastError());
                else {
                    std::string str_temp{pszOutBuffer};
                    if (!str_temp.empty()) output += str_temp;
                }

                // Free the memory allocated to the buffer.
                delete[] pszOutBuffer;
            }
        } while (dwSize > 0);
    }

    // Report any errors.
    if (!bResults) printf("Error %ld has occurred.\n", GetLastError());

    // Close any open handles.
    if (hRequest) WinHttpCloseHandle(hRequest);
    if (hConnect) WinHttpCloseHandle(hConnect);
    if (hSession) WinHttpCloseHandle(hSession);

    return output;
}

void sendMessage(const std::string& mes, const std::string& Token, const std::string& ChatId) {
    DWORD dwSize = 0;
    DWORD dwDownloaded = 0;
    LPSTR pszOutBuffer;
    BOOL  bResults = FALSE;
    HINTERNET  hSession = NULL, hConnect = NULL, hRequest = NULL;

    std::string fullAddress = "/bot";
    fullAddress.append(Token);
    fullAddress.append("/sendMessage");

    std::wstring stemp = std::wstring(fullAddress.begin(), fullAddress.end());
    LPCWSTR sw = stemp.c_str();
    //Request body
    std::string message = "{\"text\":\"" + mes +"\", \"chat_id\":\"" + ChatId + "\"}";
    LPSTR postdata = const_cast<char *>(message.c_str());

    // Use WinHttpOpen to obtain a session handle.
    hSession = WinHttpOpen(L"WinHTTP Example/1.0",
        WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS, 0);

    // Specify an HTTP server.
    if (hSession)
        hConnect = WinHttpConnect(hSession, L"api.telegram.org",
            INTERNET_DEFAULT_HTTPS_PORT, 0);

    // Create an HTTP request handle.
    if (hConnect)
        hRequest = WinHttpOpenRequest(hConnect, L"GET", sw,
            NULL, WINHTTP_NO_REFERER,
            WINHTTP_DEFAULT_ACCEPT_TYPES,
            WINHTTP_FLAG_SECURE);

    // Add a request header.
    if (hRequest)
        bResults = WinHttpAddRequestHeaders(hRequest,
            L"content-type:application/json",
            (ULONG)-1L,
            WINHTTP_ADDREQ_FLAG_ADD);

    // Send a request.
    if (hRequest)
        bResults = WinHttpSendRequest(hRequest,
            WINHTTP_NO_ADDITIONAL_HEADERS,
            -1L,
            postdata, strlen(postdata),
            strlen(postdata), 0);


    // End the request.
    if (bResults) bResults = WinHttpReceiveResponse(hRequest, NULL);

    // Keep checking for data until there is nothing left.
    if (bResults)
    {
        do
        {
            // Check for available data.
            dwSize = 0;
            if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
                printf("Error %lu in WinHttpQueryDataAvailable.\n",
                    GetLastError());

            // Allocate space for the buffer.
            pszOutBuffer = new char[dwSize + 1];
            if (!pszOutBuffer)
            {
                printf("Out of memory\n");
                dwSize = 0;
            }
            else
            {
                // Read the data.
                ZeroMemory(pszOutBuffer, dwSize + 1);

                if (!WinHttpReadData(hRequest, (LPVOID)pszOutBuffer,
                    dwSize, &dwDownloaded))
                    printf("Error %lu in WinHttpReadData.\n", GetLastError());

                // Free the memory allocated to the buffer.
                delete[] pszOutBuffer;
            }
        } while (dwSize > 0);
    }

    // Report any errors.
    if (!bResults) printf("Error %ld has occurred.\n", GetLastError());

    // Close any open handles.
    if (hRequest) WinHttpCloseHandle(hRequest);
    if (hConnect) WinHttpCloseHandle(hConnect);
    if (hSession) WinHttpCloseHandle(hSession);
}

int main() {
    std::string json_data = "", UpdataId = "0", TmpId = "", command;
    Json::Reader reader;
    Json::Value j;
    int flag = 0, io = 0;

    /* BotのトークンとチャットIDを書き換えましょう */
    std::string TOKEN = "0000000000:AAA_AAAAAAAAAAAAAAAAAAAAAAA_AAAAAAA";
    std::string ChatId = "0000000000";

    while (1) {
        try {
            json_data = getUpdates(TOKEN);
            reader.parse(json_data, j);
            const Json::Value& k = j["result"];
            TmpId = k[k.size() - 1]["message"]["message_id"].asString();
            if (atoi(UpdataId.c_str()) < atoi(TmpId.c_str())) {
                UpdataId = TmpId;
                flag = 1;
            }
            if (io == 0) {
                flag = 0;
                io = 1;
                //sendMessage("Bot Started!", TOKEN, ChatId);
                printf("Bot Started!");
                continue;
            }
            if (flag) {
                flag = 0;
                command = k[k.size()-1]["message"]["text"].asString();
                sendMessage(command, TOKEN, ChatId);
            }
        }
        catch (...) {}
        Sleep(500);
    }

    return 0;
}

