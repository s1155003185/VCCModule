#pragma once

#include <memory>

#include "base_document.hpp"
#include "class_macro.hpp"

namespace vcc
{
    enum class JsonType
    {
        Array,
        Boolean,
        Number,
        Null,
        Object,
        Json,
        String
    };

    class Json : public BaseDocument<Json>
    {
        GETSET(JsonType, Type, JsonType::Json);
        // Json
        ORDERED_MAP_SPTR_R(std::wstring, Json, NameValuePairs);
        // Json Object
        GETSET(std::wstring, Value, L"");
        VECTOR_SPTR(Json, Array);

        public:
            Json() : BaseDocument() {}
            virtual ~Json() {}
            
            virtual std::shared_ptr<IObject> Clone() const override;

            JsonType GetJsonType(const std::wstring &key) const;
            std::vector<std::wstring> GetKeys(/*bool isRecursive = false*/) const; // TODO: Recursive
            bool IsContainKey(const std::wstring &key/*, bool isRecursive = false*/) const; // TODO: Recursive

            bool IsNull(const std::wstring &key) const;
            void AddNull(const std::wstring &key) const;

            bool GetBool(const std::wstring &key) const;
            void AddBool(const std::wstring &key, bool value) const;

            double GetDouble(const std::wstring &key) const;
            size_t GetDecimalPlaces(const std::wstring &key) const;
            void AddDouble(const std::wstring &key, double value, size_t decimalPlaces) const;

            int GetInt32(const std::wstring &key) const;
            int64_t GetInt64(const std::wstring &key) const;
            void AddInt(const std::wstring &key, int value) const;

            std::wstring GetString(const std::wstring &key) const;
            void AddString(const std::wstring &key, const std::wstring &value) const;

            std::shared_ptr<Json> GetObject(const std::wstring &key) const;
            void AddObject(const std::wstring &key, std::shared_ptr<Json> object) const;

            std::vector<std::shared_ptr<Json>> &GetArray(const std::wstring &key) const;
            void AddArray(const std::wstring &key, std::shared_ptr<Json> array) const;
            
            // Array
            void AddArrayNull() const;
            void AddArrayBool(bool value) const;
            void AddArrayDouble(double value, size_t decimalPlaces) const;
            void AddArrayInt(int value) const;
            void AddArrayString(const std::wstring &value) const;
            void AddArrayObject(std::shared_ptr<Json> object) const;
            void AddArrayArray(std::shared_ptr<Json> array) const;
    };
}
