#include "DataSender.h"
#include "QDebug"

#include <string>
#include <codecvt>
#include <locale>

using namespace rapidjson;

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <codecvt>
#include <locale>
#include <string>
#include <vector>
#include <QString>

void DataSender::sendData(std::vector<QString> data)
{
    using namespace rapidjson;

    Document doc;
    doc.SetObject();
    Document::AllocatorType& allocator = doc.GetAllocator();

    // Конвертер для преобразования std::wstring в UTF-8
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

    // Добавление данных в JSON
    doc.AddMember("login", Value(converter.to_bytes(data[3].toStdWString()).c_str(), allocator), allocator);
    doc.AddMember("password", Value(converter.to_bytes(data[4].toStdWString()).c_str(), allocator), allocator);
    doc.AddMember("name", Value(converter.to_bytes(data[0].toStdWString()).c_str(), allocator), allocator);
    doc.AddMember("surname", Value(converter.to_bytes(data[2].toStdWString()).c_str(), allocator), allocator);
    doc.AddMember("middlename", Value(converter.to_bytes(data[1].toStdWString()).c_str(), allocator), allocator);
    doc.AddMember("mac_address", Value(converter.to_bytes(data[5].toStdWString()).c_str(), allocator), allocator);

    // Генерация JSON строки
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    doc.Accept(writer);

    // Конечная строка в UTF-8
    std::string jsonString = buffer.GetString();

    // Отправка на сервер
    sendJsonToServerWithResponse(jsonString);
}


void DataSender::sendJsonToServerWithResponse(const std::string& jsonStr)
{
    if(_url == "") throw QString("URL NOT DECLARED!!!");
    CURL* curl = curl_easy_init();
    if (curl) {
        CURLcode res;
        std::string responseString;

        //Отрубаем нахер поддержку сертификата, так как у нас большие потные яйца
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        curl_easy_setopt(curl, CURLOPT_URL, _url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_slist_append(nullptr, "Content-Type: application/json"));
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonStr.c_str());

        // Установка callback для записи ответа
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, DataSender::WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseString);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) throw QString("Server send not OK");
        else qDebug() << "Server send OK";

        curl_easy_cleanup(curl);
    }
}

