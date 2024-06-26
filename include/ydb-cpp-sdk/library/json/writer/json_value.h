#pragma once

#include <ydb-cpp-sdk/library/json/common/defs.h>

#include <ydb-cpp-sdk/util/generic/utility.h>
#include <ydb-cpp-sdk/util/generic/yexception.h>

#include <unordered_map>

namespace NJson {
    enum EJsonValueType {
        JSON_UNDEFINED /* "Undefined" */,
        JSON_NULL /* "Null" */,
        JSON_BOOLEAN /* "Boolean" */,
        JSON_INTEGER /* "Integer" */,
        JSON_DOUBLE /* "Double" */,
        JSON_STRING /* "String" */,
        JSON_MAP /* "Map" */,
        JSON_ARRAY /* "Array" */,
        JSON_UINTEGER /* "UInteger" */
    };

    class TJsonValue;

    class IScanCallback {
    public:
        virtual ~IScanCallback() = default;

        virtual bool Do(const std::string& path, TJsonValue* parent, TJsonValue& value) = 0;
    };

    class TJsonValue {
        void Clear() noexcept;

    public:
        typedef std::unordered_map<std::string, TJsonValue> TMapType;
        typedef std::deque<TJsonValue> TArray;

        TJsonValue() noexcept = default;
        TJsonValue(EJsonValueType type);
        TJsonValue(bool value) noexcept;
        TJsonValue(int value) noexcept;
        TJsonValue(unsigned int value) noexcept;
        TJsonValue(long value) noexcept;
        TJsonValue(unsigned long value) noexcept;
        TJsonValue(long long value) noexcept;
        TJsonValue(unsigned long long value) noexcept;
        TJsonValue(double value) noexcept;
        TJsonValue(const char* value);
        template <class T>
        TJsonValue(const T*) = delete;
        TJsonValue(std::string_view value);

        TJsonValue(const std::string& s)
            : TJsonValue(std::string_view(s))
        {
        }

        TJsonValue(const TJsonValue& vval);
        TJsonValue(TJsonValue&& vval) noexcept;

        TJsonValue& operator=(const TJsonValue& val);
        TJsonValue& operator=(TJsonValue&& val) noexcept;

        ~TJsonValue() {
            Clear();
        }

        EJsonValueType GetType() const noexcept;
        TJsonValue& SetType(EJsonValueType type);

        TJsonValue& SetValue(const TJsonValue& value);
        TJsonValue& SetValue(TJsonValue&& value);

        // for Map
        TJsonValue& InsertValue(const std::string& key, const TJsonValue& value);
        TJsonValue& InsertValue(std::string_view key, const TJsonValue& value);
        TJsonValue& InsertValue(const char* key, const TJsonValue& value);
        TJsonValue& InsertValue(const std::string& key, TJsonValue&& value);
        TJsonValue& InsertValue(std::string_view key, TJsonValue&& value);
        TJsonValue& InsertValue(const char* key, TJsonValue&& value);

        // for Array
        TJsonValue& AppendValue(const TJsonValue& value);
        TJsonValue& AppendValue(TJsonValue&& value);
        TJsonValue& Back();
        const TJsonValue& Back() const;

        bool GetValueByPath(std::string_view path, TJsonValue& result, char delimiter = '.') const;
        bool SetValueByPath(std::string_view path, const TJsonValue& value, char delimiter = '.');
        bool SetValueByPath(std::string_view path, TJsonValue&& value, char delimiter = '.');

        // returns NULL on failure
        const TJsonValue* GetValueByPath(std::string_view path, char delimiter = '.') const noexcept;
        TJsonValue* GetValueByPath(std::string_view path, char delimiter = '.') noexcept;

        void EraseValue(std::string_view key);
        void EraseValue(size_t index);

        TJsonValue& operator[](size_t idx);
        TJsonValue& operator[](const std::string_view& key);
        const TJsonValue& operator[](size_t idx) const noexcept;
        const TJsonValue& operator[](const std::string_view& key) const noexcept;

        bool GetBoolean() const;
        long long GetInteger() const;
        unsigned long long GetUInteger() const;
        double GetDouble() const;
        const std::string& GetString() const;
        const TMapType& GetMap() const;
        const TArray& GetArray() const;

        //throwing TJsonException possible
        bool GetBooleanSafe() const;
        long long GetIntegerSafe() const;
        unsigned long long GetUIntegerSafe() const;
        double GetDoubleSafe() const;
        const std::string& GetStringSafe() const;
        const TMapType& GetMapSafe() const;
        TMapType& GetMapSafe();
        const TArray& GetArraySafe() const;
        TArray& GetArraySafe();

        bool GetBooleanSafe(bool defaultValue) const;
        long long GetIntegerSafe(long long defaultValue) const;
        unsigned long long GetUIntegerSafe(unsigned long long defaultValue) const;
        double GetDoubleSafe(double defaultValue) const;
        std::string GetStringSafe(const std::string& defaultValue) const;

        bool GetBooleanRobust() const noexcept;
        long long GetIntegerRobust() const noexcept;
        unsigned long long GetUIntegerRobust() const noexcept;
        double GetDoubleRobust() const noexcept;
        std::string GetStringRobust() const;

        // Exception-free accessors
        bool GetBoolean(bool* value) const noexcept;
        bool GetInteger(long long* value) const noexcept;
        bool GetUInteger(unsigned long long* value) const noexcept;
        bool GetDouble(double* value) const noexcept;
        bool GetMapPointer(const TMapType** value) const noexcept;
        bool GetArrayPointer(const TArray** value) const noexcept;

        bool GetString(std::string* value) const;
        bool GetMap(TMapType* value) const;
        bool GetArray(TArray* value) const;
        bool GetValue(size_t index, TJsonValue* value) const;
        bool GetValue(std::string_view key, TJsonValue* value) const;
        bool GetValuePointer(size_t index, const TJsonValue** value) const noexcept;
        bool GetValuePointer(std::string_view key, const TJsonValue** value) const noexcept;
        bool GetValuePointer(std::string_view key, TJsonValue** value) noexcept;

        // Checking for defined non-null value
        bool IsDefined() const noexcept {
            return Type != JSON_UNDEFINED && Type != JSON_NULL;
        }

        bool IsNull() const noexcept;
        bool IsBoolean() const noexcept;
        bool IsDouble() const noexcept;
        bool IsString() const noexcept;
        bool IsMap() const noexcept;
        bool IsArray() const noexcept;

        /// @return true if JSON_INTEGER or (JSON_UINTEGER and Value <= Max<long long>)
        bool IsInteger() const noexcept;

        /// @return true if JSON_UINTEGER or (JSON_INTEGER and Value >= 0)
        bool IsUInteger() const noexcept;

        bool Has(const std::string_view& key) const noexcept;
        bool Has(size_t key) const noexcept;

        void Scan(IScanCallback& callback);

        /// Non-robust comparison.
        bool operator==(const TJsonValue& rhs) const;

        void Swap(TJsonValue& rhs) noexcept;

        // save using src/util/ysaveload.h serialization (not to JSON stream)
        void Save(IOutputStream* s) const;

        // load using src/util/ysaveload.h serialization (not as JSON stream)
        void Load(IInputStream* s);

        static const TJsonValue UNDEFINED;

    private:
        EJsonValueType Type = JSON_UNDEFINED;
        union TValueUnion {
            bool Boolean;
            long long Integer;
            unsigned long long UInteger;
            double Double;
            std::string* String;
            TMapType* Map;
            TArray* Array;

            TValueUnion() noexcept {
                Zero(*this);
            }
            ~TValueUnion() noexcept {
            }
        };
        TValueUnion Value;
        void DoScan(const std::string& path, TJsonValue* parent, IScanCallback& callback);
        void SwapWithUndefined(TJsonValue& output) noexcept;

        /**
            @throw yexception if Back shouldn't be called on the object.
         */
        void BackChecks() const;
    };

    inline bool GetBoolean(const TJsonValue& jv, size_t index, bool* value) noexcept {
        return jv[index].GetBoolean(value);
    }

    inline bool GetInteger(const TJsonValue& jv, size_t index, long long* value) noexcept {
        return jv[index].GetInteger(value);
    }

    inline bool GetUInteger(const TJsonValue& jv, size_t index, unsigned long long* value) noexcept {
        return jv[index].GetUInteger(value);
    }

    inline bool GetDouble(const TJsonValue& jv, size_t index, double* value) noexcept {
        return jv[index].GetDouble(value);
    }

    inline bool GetString(const TJsonValue& jv, size_t index, std::string* value) {
        return jv[index].GetString(value);
    }

    bool GetMapPointer(const TJsonValue& jv, size_t index, const TJsonValue::TMapType** value);
    bool GetArrayPointer(const TJsonValue& jv, size_t index, const TJsonValue::TArray** value);

    inline bool GetBoolean(const TJsonValue& jv, std::string_view key, bool* value) noexcept {
        return jv[key].GetBoolean(value);
    }

    inline bool GetInteger(const TJsonValue& jv, std::string_view key, long long* value) noexcept {
        return jv[key].GetInteger(value);
    }

    inline bool GetUInteger(const TJsonValue& jv, std::string_view key, unsigned long long* value) noexcept {
        return jv[key].GetUInteger(value);
    }

    inline bool GetDouble(const TJsonValue& jv, std::string_view key, double* value) noexcept {
        return jv[key].GetDouble(value);
    }

    inline bool GetString(const TJsonValue& jv, std::string_view key, std::string* value) {
        return jv[key].GetString(value);
    }

    bool GetMapPointer(const TJsonValue& jv, const std::string_view key, const TJsonValue::TMapType** value);
    bool GetArrayPointer(const TJsonValue& jv, const std::string_view key, const TJsonValue::TArray** value);

    class TJsonMap: public TJsonValue {
    public:
        TJsonMap()
            : TJsonValue(NJson::JSON_MAP)
        {}

        TJsonMap(const std::initializer_list<std::pair<const std::string, TJsonValue>>& list)
            : TJsonValue(NJson::JSON_MAP)
        {
            GetMapSafe() = std::unordered_map<std::string, TJsonValue>(list);
        }
    };

    class TJsonArray: public TJsonValue {
    public:
        TJsonArray()
            : TJsonValue(NJson::JSON_ARRAY)
        {}

        TJsonArray(const std::initializer_list<TJsonValue>& list)
            : TJsonValue(NJson::JSON_ARRAY)
        {
            GetArraySafe() = TJsonValue::TArray(list);
        }
    };
}
