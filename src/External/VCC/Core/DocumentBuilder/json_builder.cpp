#include "json_builder.hpp"

#include <string>

#include "i_document.hpp"
#include "exception_type.hpp"
#include "exception_macro.hpp"
#include "json.hpp"
#include "memory_macro.hpp"
#include "string_helper.hpp"

const std::wstring nullStr = L"null";
const std::wstring trueStr = L"true";
const std::wstring falseStr = L"false";

namespace vcc
{    
    std::wstring JsonBuilder::GetCurrentIndent() const
    {
        if (!_IsBeautify)
            return L"";
        std::wstring result = L"";
        for (size_t i = 0; i < _Level; i++) {
            result += _Indent;
        }
        return result;
    }

    std::wstring JsonBuilder::GetErrorMessage(const std::wstring &str, const size_t &pos, const std::wstring &msg) const
    {
        size_t row = 0, column = 0;
        GetCharacterRowAndColumn(str, pos, row, column);
        
        size_t lengthOfPos = std::min(pos, _NumberOfCharactersBeforePosForErrorMessage);
        size_t lengthOfSub = std::min(str.length() - pos, _NumberOfCharactersAfterPosForErrorMessage);

        std::wstring preString = str.substr(pos - lengthOfPos, lengthOfPos);
        std::wstring subString = str.substr(pos + 1, lengthOfSub);
        return L"Error at position " + std::to_wstring(pos + 1) 
            + L", row " + std::to_wstring(row) 
            + L", column " + std::to_wstring(column) + L": " + preString + L"<<" + std::wstring(1, str[pos]) + L">>" + subString + L"\r\n "
            + L" Error message: " + msg;
    }

    std::wstring JsonBuilder::Serialize(const IDocument *doc) const
    {
        std::wstring result = L"";
        TRY_CATCH(
            std::wstring currentNewLineCharacter = _IsBeautify ? _NewLineCharacter : L"";
            std::wstring currentNameColonSpace = _IsBeautify ? _NameColonSpace : L"";
            std::wstring currentColonValueSpace = _IsBeautify ? _ColonValueSpace : L"";

            Json *jsonObj = dynamic_cast<Json *>(const_cast<IDocument *>(doc));
            assert(jsonObj != nullptr);
            switch (jsonObj->GetJsonInternalType())
            {
            // Value
            case JsonInternalType::Boolean:
            case JsonInternalType::Number:
                result = jsonObj->GetJsonInternalValue();
                break;
            case JsonInternalType::Null:
                result = L"null";
                break;
            case JsonInternalType::String:
                result = GetEscapeStringWithQuote(EscapeStringType::DoubleQuote, jsonObj->GetJsonInternalValue());
                break;
            // Object
            case JsonInternalType::Array: {
                _Level++;
                for (auto const &element : jsonObj->GetJsonInternalArray()) {
                    if (!result.empty())
                        result += L"," + currentNewLineCharacter;
                    result += GetCurrentIndent() + Serialize(element.get());
                }
                _Level--;
                result = L"[" + currentNewLineCharacter + result + currentNewLineCharacter + GetCurrentIndent() + L"]";
                break;
            }
            case JsonInternalType::Object:
                result = Serialize(jsonObj->GetJsonInternalArray().at(0).get());
                break;
            case JsonInternalType::Json: {
                _Level++;
                for (auto const &pair : jsonObj->GetJsonInternalNameValuePairs()) {
                    if (!result.empty())
                        result += L"," + currentNewLineCharacter;
                    result += GetCurrentIndent() + GetEscapeStringWithQuote(EscapeStringType::DoubleQuote, pair.first);
                    result += currentNameColonSpace + L":" + currentColonValueSpace;
                    result += Serialize(pair.second.get());
                }
                _Level--;
                result = L"{" + currentNewLineCharacter + result + currentNewLineCharacter + GetCurrentIndent() + L"}";
                break;
            }
            default:
                assert(false);
                break;
            }
        )
        return result;
    }

    void JsonBuilder::ParseJsonObject(const std::wstring &str, size_t &pos, std::shared_ptr<Json> doc) const
    {
        size_t startPos = pos;
        try {
            GetNextCharacterPos(str, pos, true);
            if (HasPrefix(str, nullStr, pos)) {
                doc->SetJsonInternalType(JsonInternalType::Null);
                pos += nullStr.length() - 1;
            } else if (HasPrefix(str, trueStr, pos)) {
                doc->SetJsonInternalType(JsonInternalType::Boolean);
                doc->SetJsonInternalValue(trueStr);
                pos += trueStr.length() - 1;
            } else if (HasPrefix(str, falseStr, pos)) {
                doc->SetJsonInternalType(JsonInternalType::Boolean);
                doc->SetJsonInternalValue(falseStr);
                pos += falseStr.length() - 1;
            } else if (str[pos] == L'"') {
                std::wstring value = GetNextQuotedString(str, pos, { L",", L"}", L"]" }, { L"\"", L"'", L"{", L"["}, { L"\"", L"'", L"}", L"]"}, { L"\\", L"\\", L"\\", L"\\"});
                value  = GetUnescapeStringWithQuote(EscapeStringType::DoubleQuote, value);
                doc->SetJsonInternalType(JsonInternalType::String);
                doc->SetJsonInternalValue(value);
            } else if (str[pos] == L'\'') {
                std::wstring value = GetNextQuotedString(str, pos, { L",", L"}", L"]" }, { L"\"", L"'", L"{", L"["}, { L"\"", L"'", L"}", L"]"}, { L"\\", L"\\", L"\\", L"\\"});
                value  = GetUnescapeStringWithQuote(EscapeStringType::SingleQuote, value);
                doc->SetJsonInternalType(JsonInternalType::String);
                doc->SetJsonInternalValue(value);
            } else if (str[pos] == L'{') {
                DECLARE_SPTR(Json, jsonObj);
                Deserialize(str, pos, jsonObj);
                doc->SetJsonInternalType(JsonInternalType::Object);
                doc->InsertJsonInternalArray(jsonObj);
            } else if (str[pos] == L'['){
                doc->SetJsonInternalType(JsonInternalType::Array);
                GetNextCharacterPos(str, pos, false);
                if (str[pos] != L']') {
                    while (pos < str.length()) {
                        DECLARE_SPTR(Json, obj);
                        ParseJsonObject(str, pos, obj);
                        doc->InsertJsonInternalArray(obj);
                        GetNextCharacterPos(str, pos, false);
                        if (str[pos] == L']')
                            break;
                        else if (str[pos] == L',')
                            GetNextCharacterPos(str, pos, false);
                        else
                            THROW_EXCEPTION_MSG(ExceptionType::ParserError, GetErrorMessage(str, pos, L"Array elements not end with , or ]"));
                    }
                }
            } else {
                std::wstring numStr = GetNextQuotedString(str, pos, { L",", L"}", L"]" }, { L"\"", L"'", L"{", L"["}, { L"\"", L"'", L"}", L"]"}, { L"\\", L"\\", L"\\", L"\\"});
                Trim(numStr);
                try
                {
                    std::stod(numStr);
                }
                catch(const std::exception& e)
                {
                    THROW_EXCEPTION_MSG(ExceptionType::ParserError, GetErrorMessage(str, startPos, L"Unknown json value format: " + numStr));
                }
                doc->SetJsonInternalType(JsonInternalType::Number);
                doc->SetJsonInternalValue(numStr);
            }
        }
        catch(const std::exception& e)
        {
            THROW_EXCEPTION_MSG(ExceptionType::ParserError, GetErrorMessage(str, startPos, L"Parse json object error: " + str2wstr(e.what())));
        }
    }

    void JsonBuilder::Deserialize(const std::wstring &str, size_t &pos, std::shared_ptr<IDocument> doc) const
    {
        TRY_CATCH(
            std::shared_ptr<Json> jsonObj = dynamic_pointer_cast<Json>(doc);
            assert(jsonObj != nullptr);
            GetNextCharacterPos(str, pos, true);
            if (str[pos] != L'{')
                THROW_EXCEPTION_MSG(ExceptionType::ParserError, GetErrorMessage(str, pos, L"Json Object not start with {"));
            GetNextCharacterPos(str, pos, false);
            while (pos < str.length())
            {
                // name
                std::wstring name = GetNextQuotedString(str, pos, {L":"}, { L"\"", L"'", L"{", L"["}, { L"\"", L"'", L"}", L"]"}, { L"\\", L"\\", L"\\", L"\\"});
                Trim(name);
                if (name.starts_with(L"\"")) {
                    name = GetUnescapeStringWithQuote(EscapeStringType::DoubleQuote, name);
                } else if (name.starts_with(L"\'")) {
                    name = GetUnescapeStringWithQuote(EscapeStringType::SingleQuote, name);
                }
                GetNextCharacterPos(str, pos, false);
                if (str[pos] != L':')
                    THROW_EXCEPTION_MSG(ExceptionType::ParserError, GetErrorMessage(str, pos, L"Json Object name " + name + L" not followed by :"));
                GetNextCharacterPos(str, pos, false);

                // value
                DECLARE_SPTR(Json, obj);
                ParseJsonObject(str, pos, obj);
                jsonObj->SetJsonInternalType(JsonInternalType::Json);
                jsonObj->InsertJsonInternalNameValuePairs(name, obj);

                GetNextCharacterPos(str, pos, false);
                if (str[pos] != L',')
                    break;
                GetNextCharacterPos(str, pos, false);
            }
        )
    }

    void JsonBuilder::Deserialize(const std::wstring &str, std::shared_ptr<IDocument> doc) const
    {
        TRY_CATCH(
            size_t pos = 0;
            this->Deserialize(str, pos, doc);
        )
    }
}