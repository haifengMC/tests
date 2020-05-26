#include <stack>
#include <string>
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
	//RETERR(mError);
	RETERR(!CURRENT.IsObject() || TOP.state != JsonReaderStackItem::Started);
	mError = false;

	Value::ConstMemberIterator memberItr = CURRENT.FindMember(name);
	RETERR(memberItr == CURRENT.MemberEnd());
	
	STACK->push(JsonReaderStackItem(&memberItr->value, JsonReaderStackItem::BeforeStart));
	
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
	RETERR(!CURRENT.IsBool());
	
	b = CURRENT.GetBool();
	Next();

	return *this;
}

JsonReader& JsonReader::operator&(unsigned& u) 
{
	RETERR(mError);
	RETERR(!CURRENT.IsUint());

	u = CURRENT.GetUint();
	Next();

	return *this;
}

JsonReader& JsonReader::operator&(int& i) 
{
	RETERR(mError);
	RETERR(!CURRENT.IsInt());

	i = CURRENT.GetInt();
	Next();

	return *this;
}

JsonReader& JsonReader::operator&(float& f)
{
	RETERR(mError);
	RETERR(!CURRENT.IsNumber());

	f = CURRENT.GetFloat();
	Next();

	return *this;
}

JsonReader& JsonReader::operator&(double& d)
{
	RETERR(mError);
	RETERR(!CURRENT.IsNumber());

	d = CURRENT.GetDouble();
	Next();

	return *this;
}

JsonReader& JsonReader::operator&(void* v)
{
	RETERR(mError);
	RETERR(!CURRENT.IsUint64());

	v = (void*)CURRENT.GetUint64();
	Next();

	return *this;
}

JsonReader& JsonReader::operator&(std::string& s) 
{
	RETERR(mError);
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
	WRITER->StartObject();
	return *this;
}

JsonWriter& JsonWriter::EndObject() 
{
	WRITER->EndObject();
	return *this;
}

JsonWriter& JsonWriter::Member(const char* name) 
{
	WRITER->String(name, static_cast<SizeType>(strlen(name)));
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
	WRITER->Bool(b);
	return *this;
}

JsonWriter& JsonWriter::operator&(unsigned& u) 
{
	WRITER->Uint(u);
	return *this;
}

JsonWriter& JsonWriter::operator&(int& i) 
{
	WRITER->Int(i);
	return *this;
}

JsonWriter& JsonWriter::operator&(float& f) 
{
	WRITER->Double(f);
	return *this;
}

JsonWriter& JsonWriter::operator&(double& d) 
{
	WRITER->Double(d);
	return *this;
}

JsonWriter& JsonWriter::operator&(void* v)
{
	WRITER->Uint64((uint64_t)v);
	return *this;
}

JsonWriter& JsonWriter::operator&(std::string& s) 
{
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
