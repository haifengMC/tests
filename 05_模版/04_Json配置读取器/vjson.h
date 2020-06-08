#pragma once

class JsonData;
class JsonReader {
public:
    /// Constructor.
    /**
        \param json A non-const source json string for in-situ parsing.
        \note in-situ means the source JSON string will be modified after parsing.
    */
    JsonReader() {}
    JsonReader(const char* json) { Init(json); }

    /// Destructor.
    ~JsonReader() { Clear(); }

    bool Reset(const char* json);

    // Archive concept

	operator bool() const { return !mError; }

	//绑定数据对象
	void BindObject(JsonData& obj) { filterObj = &obj; }

    JsonReader& StartObject();
    JsonReader& Member(const char* name);
    bool HasMember(const char* name) const;
    JsonReader& EndObject();

    JsonReader& StartArray(size_t* size = 0);
    JsonReader& EndArray();

    JsonReader& operator[](const char* name) { return Member(name); }

    JsonReader& operator&(bool& b);
    JsonReader& operator&(unsigned& u);
	JsonReader& operator&(int& i);
	JsonReader& operator&(float& f);
    JsonReader& operator&(double& d);
    JsonReader& operator&(void* v);
	JsonReader& operator&(std::string& s);

    JsonReader& SetNull();

    static const bool IsReader = true;
    static const bool IsWriter = !IsReader;

private:
    JsonReader(const JsonReader&) = delete;
    JsonReader& operator=(const JsonReader&) = delete;

	bool Init(const char* json);
	void Clear();

    void Next();

    // PIMPL
    void* mDocument = NULL;              ///< DOM result of parsing.
    void* mStack = NULL;                 ///< Stack for iterating the DOM
	bool mError = true;                  ///< Whether an error has occurred.

	JsonData* filterObj = NULL;
	bool needFilter = true;
};

class JsonWriter {
public:
    /// Constructor.
    JsonWriter() { Init(); }

    /// Destructor.
    ~JsonWriter() { Reset(); }

    /// Obtains the serialized JSON string.
    const char* GetString() const;
    size_t GetSize() const;

    // Archive concept
    operator bool() const { return true; }

    //绑定数据对象
    void BindObject(const JsonData& obj) { filterObj = &obj; }

    JsonWriter& StartObject();
    JsonWriter& Member(const char* name);
    bool HasMember(const char* name) const;
    JsonWriter& EndObject();

    JsonWriter& StartArray(size_t* size = 0);
    JsonWriter& EndArray();

    JsonWriter& operator[](const char* name) { return Member(name); }

    JsonWriter& operator&(bool& b);
    JsonWriter& operator&(unsigned& u);
	JsonWriter& operator&(int& i);
    JsonWriter& operator&(float& f);
    JsonWriter& operator&(double& d);
    JsonWriter& operator&(void* v);
    JsonWriter& operator&(std::string& s);
    JsonWriter& SetNull();

    static const bool IsReader = false;
    static const bool IsWriter = !IsReader;

private:
    JsonWriter(const JsonWriter&) = delete;
    JsonWriter& operator=(const JsonWriter&) = delete;

    void Init();
    void Clear();
    void Reset();

    // PIMPL idiom
    void* mWriter = NULL;      ///< JSON writer.
    void* mStream = NULL;      ///< Stream buffer.

    const JsonData* filterObj = NULL;
    bool needFilter = true;
};

namespace Json
{
    class JsonRW;
	JsonRW& begObj(JsonRW& rw);
	JsonRW& endObj(JsonRW& rw);
    JsonRW& end(JsonRW& rw);
	//JsonRW& null(JsonRW& rw)
	//{
    //    return rw;
	//}

    template <typename T> struct JsonMem;
    template <typename T> JsonMem<T> mem(const char* const& name, T& t);
	template <typename T>
	struct JsonMem
	{
		const char* const& name;
		T& t;
    private:
		JsonMem(const char* const& name, T& t) : name(name), t(t) {}
		friend JsonMem mem<>(const char* const& name, T& t);
	};

	template <typename T>
    JsonMem<T> mem(const char* const& name, T& t)
	{
		return JsonMem <T>(name, t);
	}

    enum class JsonRWMode
    {
        JsonRWMode_Read,
        JsonRWMode_Write
    };
    class JsonRW
    {
        friend JsonRW& end(JsonRW& rw);
    public:
	    JsonRW() {}
	    JsonRW(const JsonRW&) = delete;
	    JsonRW& operator=(const JsonRW&) = delete;

        void setMode(const JsonRWMode& m) { mode = m; }

	    JsonRW& member(const char* name);
	    bool hasMember(const char* name) const;

	    JsonRW& beginObject();
	    JsonRW& endObject();
	    JsonRW& beginArray(size_t* size = NULL);
	    JsonRW& endArray();


        operator bool() const { return !mError; }
        JsonRW& operator()(const JsonRWMode& m);
	    JsonRW& operator()(const std::string& json);
	    JsonRW& operator()(std::string& json);
        JsonRW& operator[](const char* name) { return member(name); }

	    JsonRW& operator&(bool& b);
	    JsonRW& operator&(unsigned& u);
	    JsonRW& operator&(int& i);
	    JsonRW& operator&(float& f);
	    JsonRW& operator&(double& d);
	    JsonRW& operator&(void* v);
	    JsonRW& operator&(std::string& s);
		JsonRW& operator&(JsonRW& (*func)(JsonRW&));
		template<typename T>
        JsonRW& operator&(const JsonMem<T>& mem) { return (*this)[mem.name] & mem.t; }

        JsonRW& setNull();
    private:
	    bool init(const char* json = NULL);
	    bool reset(const char* json = NULL);
	    void clear();

        void next();

	    //ReaderData
	    // PIMPL
	    void* mDocument = NULL;              ///< DOM result of parsing.
	    void* mStack = NULL;                 ///< Stack for iterating the DOM
	    bool mError = true;                  ///< Whether an error has occurred.

	    //WriterData
	    // PIMPL idiom
	    void* mWriter = NULL;                ///< JSON writer.
	    void* mStream = NULL;                ///< Stream buffer.
        void* mBuffer = NULL;
	    JsonRWMode mode = JsonRWMode::JsonRWMode_Read;

	    void* filterObj = NULL;
	    bool needFilter = false;
    };
}


class JsonStream
{
	std::string fileName;
public:
    JsonStream(const std::string& fileName);

	bool operator>>(JsonReader& reader);
	bool operator<<(const JsonWriter& writer);

};

class JsonData
{
    std::set<std::string> ignoreNames;
public:
    bool addFilter(const std::string& name);
    bool delFilter(const std::string& name);
    bool hasFilter(const std::string& name) const;
};
