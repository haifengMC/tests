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

JsonReader::JsonReader(const char* json) : mDocument(), mStack(), mError(false)
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

JsonReader::~JsonReader() 
{
	delete DOCUMENT;
	delete STACK;
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

JsonReader& JsonReader::operator&(double& d)
{
	RETERR(mError);
	RETERR(!CURRENT.IsNumber());

	d = CURRENT.GetDouble();
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

JsonWriter::JsonWriter() : mWriter(), mStream() {
	mStream = new StringBuffer;
	mWriter = new PrettyWriter<StringBuffer>(*STREAM);
}

JsonWriter::~JsonWriter() {
	delete WRITER;
	delete STREAM;
}

const char* JsonWriter::GetString() const {
	return STREAM->GetString();
}

JsonWriter& JsonWriter::StartObject() {
	WRITER->StartObject();
	return *this;
}

JsonWriter& JsonWriter::EndObject() {
	WRITER->EndObject();
	return *this;
}

JsonWriter& JsonWriter::Member(const char* name) {
	WRITER->String(name, static_cast<SizeType>(strlen(name)));
	return *this;
}

bool JsonWriter::HasMember(const char*) const {
	// This function is for JsonReader only.
	assert(false);
	return false;
}

JsonWriter& JsonWriter::StartArray(size_t*) {
	WRITER->StartArray();
	return *this;
}

JsonWriter& JsonWriter::EndArray() {
	WRITER->EndArray();
	return *this;
}

JsonWriter& JsonWriter::operator&(bool& b) {
	WRITER->Bool(b);
	return *this;
}

JsonWriter& JsonWriter::operator&(unsigned& u) {
	WRITER->Uint(u);
	return *this;
}

JsonWriter& JsonWriter::operator&(int& i) {
	WRITER->Int(i);
	return *this;
}

JsonWriter& JsonWriter::operator&(double& d) {
	WRITER->Double(d);
	return *this;
}

JsonWriter& JsonWriter::operator&(std::string& s) {
	WRITER->String(s.c_str(), static_cast<SizeType>(s.size()));
	return *this;
}

JsonWriter& JsonWriter::SetNull() {
	WRITER->Null();
	return *this;
}

#undef STREAM
#undef WRITER



