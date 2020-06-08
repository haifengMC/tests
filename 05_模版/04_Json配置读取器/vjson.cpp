#include <stack>
#include <string>
#include <set>
#include <cassert>

#include "vjson.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"

#include "vcommon.h"

using namespace rapidjson;

struct JsonReaderStackItem 
{
	enum State 
	{
		BeforeStart,    //!< An object/array is in the stack but it is not yet called by StartObject()/StartArray().
		Started,        //!< An object/array is called by StartObject()/StartArray().
		Closed          //!< An array is closed after read all element, but before EndArray().
	};

	JsonReaderStackItem(const Value* value, State state) : value(value), state(state), index() {}

	const Value* value;
	State state;
	SizeType index;   // For array iteration
};
typedef std::stack<JsonReaderStackItem> JsonReaderStack;

#define DOCUMENT reinterpret_cast<Document*>(mDocument)
#define STACK (reinterpret_cast<JsonReaderStack*>(mStack))
#define TOP (STACK->top())
#define CURRENT (*TOP.value)
#define RETERR(X) if (X)\
	{\
		mError = true;\
		return *this; \
	}
#define CHECK_FILTER() if (needFilter) return *this;

bool JsonReader::Reset(const char* json)
{
	Clear();
	return Init(json);
}

// Archive concept
JsonReader& JsonReader::StartObject()
{
	RETERR(mError);
	RETERR(!CURRENT.IsObject() || TOP.state != JsonReaderStackItem::BeforeStart)

	TOP.state = JsonReaderStackItem::Started;
	
	return *this;
}

JsonReader& JsonReader::Member(const char* name)
{
	RETERR(mError);
	RETERR(!CURRENT.IsObject() || TOP.state != JsonReaderStackItem::Started);
	
	needFilter = true;

	if (filterObj && filterObj->hasFilter(name))
		return *this;

	Value::ConstMemberIterator memberItr = CURRENT.FindMember(name);
	if (memberItr != CURRENT.MemberEnd())
	{
		STACK->push(JsonReaderStackItem(&memberItr->value, JsonReaderStackItem::BeforeStart));
		needFilter = false;
		return *this;
	}
		
	if (filterObj)
		filterObj->addFilter(name);
	else
		needFilter = false;

	return *this;
}

bool JsonReader::HasMember(const char* name) const 
{
	if (!mError && CURRENT.IsObject() && TOP.state == JsonReaderStackItem::Started)
		return CURRENT.HasMember(name);
	return false;
}

JsonReader& JsonReader::EndObject() 
{
	filterObj = NULL;
	needFilter = true;

	RETERR(mError);
	RETERR(!CURRENT.IsObject() || TOP.state != JsonReaderStackItem::Started)

	Next();
	
	return *this;
}

JsonReader& JsonReader::StartArray(size_t* size)
{
	RETERR(mError);
	RETERR(!CURRENT.IsArray() || TOP.state != JsonReaderStackItem::BeforeStart)

	TOP.state = JsonReaderStackItem::Started;
	if (size)
		*size = CURRENT.Size();

	if (CURRENT.Empty())
	{
		TOP.state = JsonReaderStackItem::Closed;
		return *this;
	}

	const Value* value = &CURRENT[TOP.index];
	STACK->push(JsonReaderStackItem(value, JsonReaderStackItem::BeforeStart));

	return *this;
}

JsonReader& JsonReader::EndArray() 
{
	RETERR(mError);
	RETERR(!CURRENT.IsArray() || TOP.state != JsonReaderStackItem::Closed)
	
	Next();
	return *this;
}

JsonReader& JsonReader::operator&(bool& b) 
{
	RETERR(mError);
	CHECK_FILTER();
	RETERR(!CURRENT.IsBool());

	b = CURRENT.GetBool();
	Next();

	return *this;
}

JsonReader& JsonReader::operator&(unsigned& u) 
{
	RETERR(mError);
	CHECK_FILTER();
	RETERR(!CURRENT.IsUint());

	u = CURRENT.GetUint();
	Next();

	return *this;
}

JsonReader& JsonReader::operator&(int& i) 
{
	RETERR(mError);
	CHECK_FILTER();
	RETERR(!CURRENT.IsInt());

	i = CURRENT.GetInt();
	Next();

	return *this;
}

JsonReader& JsonReader::operator&(float& f)
{
	RETERR(mError);
	CHECK_FILTER();
	RETERR(!CURRENT.IsNumber());

	f = CURRENT.GetFloat();
	Next();

	return *this;
}

JsonReader& JsonReader::operator&(double& d)
{
	RETERR(mError);
	CHECK_FILTER();
	RETERR(!CURRENT.IsNumber());

	d = CURRENT.GetDouble();
	Next();

	return *this;
}

JsonReader& JsonReader::operator&(void* v)
{
	RETERR(mError);
	CHECK_FILTER();
	RETERR(!CURRENT.IsUint64());

	v = (void*)CURRENT.GetUint64();
	Next();

	return *this;
}

JsonReader& JsonReader::operator&(std::string& s) 
{
	RETERR(mError);
	CHECK_FILTER();
	RETERR(!CURRENT.IsString());

	s = CURRENT.GetString();
	Next();

	return *this;
}

JsonReader& JsonReader::SetNull() 
{
	// This function is for JsonWriter only.
	RETERR(true);
}

bool JsonReader::Init(const char* json)
{
	mError = false;

	mDocument = new Document;
	DOCUMENT->Parse(json);
	if (DOCUMENT->HasParseError())
		mError = true;
	else
	{
		mStack = new JsonReaderStack;
		STACK->push(JsonReaderStackItem(DOCUMENT, JsonReaderStackItem::BeforeStart));
	}

	return !mError;
}

void JsonReader::Clear()
{
	DEL(mDocument);
	DEL(mStack);
	mError = true;
	//delete DOCUMENT;
	//delete STACK;

	filterObj = NULL;
	needFilter = true;
}

void JsonReader::Next()
{
	if (mError) return;

	assert(!STACK->empty());
	STACK->pop();

	if (STACK->empty() || !CURRENT.IsArray())
		return;

	if (TOP.state != JsonReaderStackItem::Started)// Otherwise means reading array item pass end
	{
		mError = true;
		return;
	}

	if (TOP.index < CURRENT.Size() - 1) {
		const Value* value = &CURRENT[++TOP.index];
		STACK->push(JsonReaderStackItem(value, JsonReaderStackItem::BeforeStart));
	}
	else
		TOP.state = JsonReaderStackItem::Closed;
}

#undef DOCUMENT
#undef STACK
#undef TOP
#undef CURRENT
#undef RETERR

////////////////////////////////////////////////////////////////////////////////
// JsonWriter

#define WRITER reinterpret_cast<PrettyWriter<StringBuffer>*>(mWriter)
#define STREAM reinterpret_cast<StringBuffer*>(mStream)

const char* JsonWriter::GetString() const 
{
	return STREAM->GetString();
}

size_t JsonWriter::GetSize() const
{
	return STREAM->GetSize();
}

JsonWriter& JsonWriter::StartObject()
{
	needFilter = true;

	WRITER->StartObject();
	return *this;
}

JsonWriter& JsonWriter::EndObject()
{
	filterObj = NULL;
	needFilter = true;

	WRITER->EndObject();
	return *this;
}

JsonWriter& JsonWriter::Member(const char* name) 
{
	if (!filterObj || !filterObj->hasFilter(name))
	{
		needFilter = false;
		WRITER->String(name, static_cast<SizeType>(strlen(name)));
	}
	else
		needFilter = true;

	return *this;
}

bool JsonWriter::HasMember(const char*) const 
{
	// This function is for JsonReader only.
	assert(false);
	return false;
}

JsonWriter& JsonWriter::StartArray(size_t*)
{
	WRITER->StartArray();
	return *this;
}

JsonWriter& JsonWriter::EndArray()
{
	WRITER->EndArray();
	return *this;
}

JsonWriter& JsonWriter::operator&(bool& b) 
{
	CHECK_FILTER();
	WRITER->Bool(b);
	return *this;
}

JsonWriter& JsonWriter::operator&(unsigned& u) 
{
	CHECK_FILTER();
	WRITER->Uint(u);
	return *this;
}

JsonWriter& JsonWriter::operator&(int& i) 
{
	CHECK_FILTER();
	WRITER->Int(i);
	return *this;
}

JsonWriter& JsonWriter::operator&(float& f) 
{
	CHECK_FILTER();
	WRITER->Double(f);
	return *this;
}

JsonWriter& JsonWriter::operator&(double& d) 
{
	CHECK_FILTER();
	WRITER->Double(d);
	return *this;
}

JsonWriter& JsonWriter::operator&(void* v)
{
	CHECK_FILTER();
	WRITER->Uint64((uint64_t)v);
	return *this;
}

JsonWriter& JsonWriter::operator&(std::string& s) 
{
	CHECK_FILTER();
	WRITER->String(s.c_str(), static_cast<SizeType>(s.size()));
	return *this;
}

JsonWriter& JsonWriter::SetNull() 
{
	WRITER->Null();
	return *this;
}

void JsonWriter::Init()
{
	mStream = new StringBuffer;
	mWriter = new PrettyWriter<StringBuffer>(*STREAM);
}

void JsonWriter::Clear()
{
	DEL(mWriter);
	DEL(mStream);
	filterObj = NULL;
	bool needFilter = true;
	//delete WRITER;
	//delete STREAM;
}

void JsonWriter::Reset()
{
	Clear();
	Init();
}

#undef STREAM
#undef WRITER
#undef CHECK_FILTER
////////////////////////////////////////////////////////////////////////////////
// JsonRW

#define WRITER reinterpret_cast<PrettyWriter<StringBuffer>*>(mWriter)
#define STREAM reinterpret_cast<StringBuffer*>(mStream)
#define DOCUMENT reinterpret_cast<Document*>(mDocument)
#define STACK (reinterpret_cast<JsonReaderStack*>(mStack))
#define BUFFER (reinterpret_cast<std::string*>(mBuffer))

using namespace Json;
#define TOP (STACK->top())
#define CURRENT (*TOP.value)
#define RETERR(X) if (X)\
	{\
		mError = true;\
		return *this; \
	}
#define CHECK_FILTER() if (needFilter) return *this;

JsonRW& Json::begObj(JsonRW& rw) { return rw.beginObject(); }
JsonRW& Json::endObj(JsonRW& rw) { return rw.endObject(); }

JsonRW& Json::end(JsonRW& rw)
{
	void*& mBuffer = rw.mBuffer;
	void*& mStream = rw.mStream;

	switch (rw.mode)
	{
	case Json::JsonRWMode::JsonRWMode_Read:
		break;
	case Json::JsonRWMode::JsonRWMode_Write:
		if (BUFFER)
			BUFFER->append(STREAM->GetString());
		break;
	default:
		break;
	}

	return rw;
}

JsonRW& JsonRW::member(const char* name)
{
	switch (mode)
	{
	case JsonRWMode::JsonRWMode_Read:
		{
			RETERR(mError);
			RETERR(!CURRENT.IsObject() || TOP.state != JsonReaderStackItem::Started);

			Value::ConstMemberIterator memberItr = CURRENT.FindMember(name);
			if (memberItr != CURRENT.MemberEnd())
				STACK->push(JsonReaderStackItem(&memberItr->value, JsonReaderStackItem::BeforeStart));
		}
		break;
	case JsonRWMode::JsonRWMode_Write:
		{
			WRITER->String(name, static_cast<SizeType>(strlen(name)));
		}
		break;
	default:
		break;
	}

	return *this;
}

bool JsonRW::hasMember(const char* name) const
{
	switch (mode)
	{
	case JsonRWMode::JsonRWMode_Read:
		{
			if (!mError && CURRENT.IsObject() && TOP.state == JsonReaderStackItem::Started)
				return CURRENT.HasMember(name);
		}
		break;
	case JsonRWMode::JsonRWMode_Write:
		{
			assert(false);
		}
		break;
	default:
		break;
	}

	return false;
}

JsonRW& JsonRW::beginObject()
{
	switch (mode)
	{
	case JsonRWMode::JsonRWMode_Read:
		{
			RETERR(mError);
			RETERR(!CURRENT.IsObject() || TOP.state != JsonReaderStackItem::BeforeStart)
			
			TOP.state = JsonReaderStackItem::Started;
		}
		break;
	case JsonRWMode::JsonRWMode_Write:
		{
			WRITER->StartObject();
		}
		break;
	default:
		break;
	}

	return *this;
}

JsonRW& JsonRW::endObject()
{
	switch (mode)
	{
	case JsonRWMode::JsonRWMode_Read:
		{
			RETERR(mError);
			RETERR(!CURRENT.IsObject() || TOP.state != JsonReaderStackItem::Started)

			next();
		}
	break;
	case JsonRWMode::JsonRWMode_Write:
		{
			WRITER->EndObject();
		}
	break;
	default:
		break;
	}

	return *this;
}

JsonRW& JsonRW::beginArray(size_t* size /*= NULL*/)
{
	switch (mode)
	{
	case JsonRWMode::JsonRWMode_Read:
		{
			RETERR(mError);
			RETERR(!CURRENT.IsArray() || TOP.state != JsonReaderStackItem::BeforeStart)

			TOP.state = JsonReaderStackItem::Started;	
			if (size)
				*size = CURRENT.Size();

			if (CURRENT.Empty())
			{
				TOP.state = JsonReaderStackItem::Closed;
				return *this;
			}

			const Value* value = &CURRENT[TOP.index];
			STACK->push(JsonReaderStackItem(value, JsonReaderStackItem::BeforeStart));
		}
	break;
	case JsonRWMode::JsonRWMode_Write:
		{
			WRITER->StartArray();
		}
	break;
	default:
		break;
	}

	return *this;
}

JsonRW& JsonRW::endArray()
{
	switch (mode)
	{
	case JsonRWMode::JsonRWMode_Read:
	{
		RETERR(mError);
		RETERR(!CURRENT.IsArray() || TOP.state != JsonReaderStackItem::Closed)
		next();
	}
	break;
	case JsonRWMode::JsonRWMode_Write:
	{
		WRITER->EndArray();
	}
	break;
	default:
		break;
	}

	return *this;
}

JsonRW& JsonRW::operator()(const JsonRWMode& m)
{
	setMode(m);
	return *this;
}

JsonRW& JsonRW::operator()(const std::string& json)
{
	reset(json.c_str());
	return *this;
}

JsonRW& JsonRW::operator()(std::string& json)
{
	reset(json.c_str());
	if (mode == JsonRWMode::JsonRWMode_Write)
		mBuffer = &json;
	return *this;
}

JsonRW& JsonRW::operator&(bool& b)
{
	RETERR(mError);
	CHECK_FILTER();

	switch (mode)
	{
	case Json::JsonRWMode::JsonRWMode_Read:
		RETERR(!CURRENT.IsBool());
		b = CURRENT.GetBool();
		next();
		break;
	case Json::JsonRWMode::JsonRWMode_Write:
		WRITER->Bool(b);
		break;
	default:
		break;
	}

	return *this;
}

JsonRW& JsonRW::operator&(unsigned& u)
{
	RETERR(mError);
	CHECK_FILTER();

	switch (mode)
	{
	case Json::JsonRWMode::JsonRWMode_Read:
		RETERR(!CURRENT.IsUint());
		u = CURRENT.GetUint();
		next();
		break;
	case Json::JsonRWMode::JsonRWMode_Write:
		WRITER->Uint(u);
		break;
	default:
		break;
	}

	return *this;
}

JsonRW& JsonRW::operator&(int& i)
{
	RETERR(mError);
	CHECK_FILTER();

	switch (mode)
	{
	case Json::JsonRWMode::JsonRWMode_Read:
		RETERR(!CURRENT.IsInt());
		i = CURRENT.GetInt();
		next();
		break;
	case Json::JsonRWMode::JsonRWMode_Write:
		WRITER->Int(i);
		break;
	default:
		break;
	}

	return *this;
}

JsonRW& JsonRW::operator&(float& f)
{
	RETERR(mError);
	CHECK_FILTER();

	switch (mode)
	{
	case Json::JsonRWMode::JsonRWMode_Read:
		RETERR(!CURRENT.IsNumber());
		f = CURRENT.GetFloat();
		next();
		break;
	case Json::JsonRWMode::JsonRWMode_Write:
		WRITER->Double(f);
		break;
	default:
		break;
	}

	return *this;
}

JsonRW& JsonRW::operator&(double& d)
{
	RETERR(mError);
	CHECK_FILTER();

	switch (mode)
	{
	case Json::JsonRWMode::JsonRWMode_Read:
		RETERR(!CURRENT.IsNumber());
		d = CURRENT.GetDouble();
		next();
		break;
	case Json::JsonRWMode::JsonRWMode_Write:
		WRITER->Double(d);
		break;
	default:
		break;
	}

	return *this;
}

JsonRW& JsonRW::operator&(void* v)
{
	RETERR(mError);
	CHECK_FILTER();

	switch (mode)
	{
	case Json::JsonRWMode::JsonRWMode_Read:
		RETERR(!CURRENT.IsUint64());
		v = (void*)CURRENT.GetUint64();
		next();
		break;
	case Json::JsonRWMode::JsonRWMode_Write:
		WRITER->Uint64((uint64_t)v);
		break;
	default:
		break;
	}

	return *this;
}

JsonRW& JsonRW::operator&(std::string& s)
{
	RETERR(mError);
	CHECK_FILTER();

	switch (mode)
	{
	case Json::JsonRWMode::JsonRWMode_Read:
		RETERR(!CURRENT.IsString());
		s = CURRENT.GetString();
		next();
		break;
	case Json::JsonRWMode::JsonRWMode_Write:
		WRITER->String(s.c_str(), static_cast<SizeType>(s.size()));
		break;
	default:
		break;
	}

	return *this;
}

JsonRW& JsonRW::operator&(JsonRW& (*func)(JsonRW&))
{
	return func(*this);
}


JsonRW& JsonRW::setNull()
{
	switch (mode)
	{
	case JsonRWMode::JsonRWMode_Read:
		mError = true;
		break;
	case JsonRWMode::JsonRWMode_Write:
		WRITER->Null();
		break;
	default:
		break;
	}
	return *this;
}

bool JsonRW::init(const char* json)
{
	mError = false;
	needFilter = false;

	switch (mode)
	{
	case JsonRWMode::JsonRWMode_Read:
		{
			mDocument = new Document;
			DOCUMENT->Parse(json);
			if (DOCUMENT->HasParseError())
				mError = true;
			else
			{
				mStack = new JsonReaderStack;
				STACK->push(JsonReaderStackItem(DOCUMENT, JsonReaderStackItem::BeforeStart));
			}

		}
		break;
	case JsonRWMode::JsonRWMode_Write:
		{
			mStream = new StringBuffer;
			mWriter = new PrettyWriter<StringBuffer>(*STREAM);
		}
		break;
	default:
		break;
	}

	return !mError;
}

bool JsonRW::reset(const char* json)
{
	clear();
	return init(json);
}

void JsonRW::clear()
{
	DEL(mDocument);
	DEL(mStack);
	DEL(mWriter);
	DEL(mStream);
	DEL(filterObj);

	mError = true;
	needFilter = true;
}

void JsonRW::next()
{
	if (mError) return;

	assert(!STACK->empty());
	STACK->pop();

	if (STACK->empty() || !CURRENT.IsArray())
		return;

	if (TOP.state != JsonReaderStackItem::Started)// Otherwise means reading array item pass end
	{
		mError = true;
		return;
	}

	if (TOP.index < CURRENT.Size() - 1) {
		const Value* value = &CURRENT[++TOP.index];
		STACK->push(JsonReaderStackItem(value, JsonReaderStackItem::BeforeStart));
	}
	else
		TOP.state = JsonReaderStackItem::Closed;
}

JsonStream::JsonStream(const std::string& fileName) : fileName(fileName) {}

bool JsonStream::operator>>(JsonReader& reader)
{
	if (fileName.empty())
		return false;

	FILE* infile;
	fopen_s(&infile, fileName.c_str(), "rb");
	if (!infile)
		return false;

	fseek(infile, 0, SEEK_END);
	int len = ftell(infile);
	fseek(infile, 0, SEEK_SET);

	char jsonBuf[65536] = "";
	fread(jsonBuf, 1, len, infile);
	fclose(infile);

	if (!reader.Reset(jsonBuf))
		return false;

	return true;
}

bool JsonStream::operator<<(const JsonWriter& writer)
{
	if (fileName.empty())
		return false;

	FILE* infile;
	fopen_s(&infile, fileName.c_str(), "wb");
	if (!infile)
		return false;

	fwrite(writer.GetString(), 1, writer.GetSize(), infile);
	fclose(infile);

	return true;
}

bool JsonData::addFilter(const std::string& name)
{
	return ignoreNames.insert(name).second; 
}

bool JsonData::delFilter(const std::string& name)
{
	return ignoreNames.erase(name);
}

bool JsonData::hasFilter(const std::string& name) const 
{
	return ignoreNames.find(name) != ignoreNames.end();
}
