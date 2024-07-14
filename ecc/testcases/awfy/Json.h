#ifndef _JSON_
#define _JSON_

// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "OBX.Runtime.h"
#include "Benchmark.h"
#include "som.Vector.c92001da8c.h"
#include "som.Vector.71499f4dff.h"
#include "Out.h"

// Declaration of module Json

struct Json$ValueResult$Class$;
struct Json$ValueResult;
struct Json$JsonPureStringParser$Class$;
struct Json$JsonPureStringParser;
struct Json$HashIndexTable$Class$;
struct Json$HashIndexTable;
struct Json$JsonLiteral$Class$;
struct Json$JsonLiteral;
struct Json$JsonString$Class$;
struct Json$JsonString;
struct Json$Json$Class$;
struct Json$Json;
struct Json$JsonArray$Class$;
struct Json$JsonArray;
struct Json$JsonNumber$Class$;
struct Json$JsonNumber;
struct Json$JsonValue$Class$;
struct Json$JsonValue;
struct Json$JsonObject$Class$;
struct Json$JsonObject;
struct Json$ValueResult {
    struct Json$ValueResult$Class$* class$;
    struct Json$JsonValue * res;
};

extern void Json$ValueResult$init$(struct Json$ValueResult*);
struct Json$JsonPureStringParser {
    struct Json$JsonPureStringParser$Class$* class$;
    struct OBX$Array$1 input;
    int32_t index;
    int32_t line;
    int32_t column;
    char current;
    char captureBuffer[1024];
    int32_t captureStart;
    int32_t capturePos;
};

extern void Json$JsonPureStringParser$init$(struct Json$JsonPureStringParser*);
struct Json$HashIndexTable {
    struct Json$HashIndexTable$Class$* class$;
    int32_t hashTable[32];
};

extern void Json$HashIndexTable$init$(struct Json$HashIndexTable*);
struct Json$JsonLiteral {
    struct Json$JsonLiteral$Class$* class$;
    struct OBX$Array$1 value;
    uint8_t _null;
    uint8_t _true;
    uint8_t _false;
};

extern void Json$JsonLiteral$init$(struct Json$JsonLiteral*);
struct Json$JsonString {
    struct Json$JsonString$Class$* class$;
    struct OBX$Array$1 string;
};

extern void Json$JsonString$init$(struct Json$JsonString*);
struct Json$Json {
    struct Json$Json$Class$* class$;
};

extern void Json$Json$init$(struct Json$Json*);
struct Json$JsonArray {
    struct Json$JsonArray$Class$* class$;
    struct som$Vector$c92001da8c$Vector * values;
};

extern void Json$JsonArray$init$(struct Json$JsonArray*);
struct Json$JsonNumber {
    struct Json$JsonNumber$Class$* class$;
    struct OBX$Array$1 string;
};

extern void Json$JsonNumber$init$(struct Json$JsonNumber*);
struct Json$JsonValue {
    struct Json$JsonValue$Class$* class$;
};

extern void Json$JsonValue$init$(struct Json$JsonValue*);
struct Json$JsonObject {
    struct Json$JsonObject$Class$* class$;
    struct som$Vector$71499f4dff$Vector * names;
    struct som$Vector$c92001da8c$Vector * values;
    struct Json$HashIndexTable table;
};

extern void Json$JsonObject$init$(struct Json$JsonObject*);
extern struct Json$JsonLiteral * Json$_NULL;
extern struct Json$JsonLiteral * Json$_TRUE;
extern struct Json$JsonLiteral * Json$_FALSE;
struct Json$Json * Json$create();
struct Benchmark$Result * Json$Json$benchmark(void* this);
uint8_t Json$Json$verifyResult(void* this, struct Benchmark$Result * result);
uint8_t Json$JsonValue$isObject(void* this);
uint8_t Json$JsonValue$isArray(void* this);
uint8_t Json$JsonValue$isNumber(void* this);
uint8_t Json$JsonValue$isString(void* this);
uint8_t Json$JsonValue$isBoolean(void* this);
uint8_t Json$JsonValue$isTrue(void* this);
uint8_t Json$JsonValue$isFalse(void* this);
uint8_t Json$JsonValue$isNull(void* this);
struct OBX$Array$1 Json$JsonValue$toString(void* this);
struct Json$JsonArray * Json$JsonValue$asArray(void* this);
struct Json$JsonObject * Json$JsonValue$asObject(void* this);
struct OBX$Array$1 Json$toString(struct OBX$Array$1 str);
struct Json$JsonString * Json$createString(struct OBX$Array$1 string);
uint8_t Json$JsonString$isString(void* this);
struct Json$JsonNumber * Json$createNumber(struct OBX$Array$1 string);
uint8_t Json$JsonNumber$isNumber(void* this);
struct OBX$Array$1 Json$JsonNumber$toString(void* this);
struct Json$JsonArray * Json$createArray();
struct Json$JsonArray * Json$JsonArray$add(void* this, struct Json$JsonValue * value);
int32_t Json$JsonArray$size(void* this);
struct Json$JsonValue * Json$JsonArray$get(void* this, int32_t index);
uint8_t Json$JsonArray$isArray(void* this);
struct Json$JsonArray * Json$JsonArray$asArray(void* this);
int32_t Json$stringHash(struct OBX$Array$1 s);
int32_t Json$hashSlotFor(struct OBX$Array$1 element);
void Json$HashIndexTable$add(void* this, struct OBX$Array$1 name, int32_t index);
int32_t Json$HashIndexTable$get(void* this, struct OBX$Array$1 name);
struct Json$JsonObject * Json$createObject();
struct Json$JsonObject * Json$JsonObject$add(void* this, struct OBX$Array$1 name, struct Json$JsonValue * value);
struct Json$JsonValue * Json$JsonObject$get(void* this, struct OBX$Array$1 name);
int32_t Json$JsonObject$indexOf(void* this, struct OBX$Array$1 name);
int32_t Json$JsonObject$size(void* this);
uint8_t Json$JsonObject$isEmpty(void* this);
uint8_t Json$JsonObject$isObject(void* this);
struct Json$JsonObject * Json$JsonObject$asObject(void* this);
struct Json$JsonLiteral * Json$createLiteral(struct OBX$Array$1 string);
uint8_t Json$JsonLiteral$isBoolean(void* this);
uint8_t Json$JsonLiteral$isTrue(void* this);
uint8_t Json$JsonLiteral$isFalse(void* this);
uint8_t Json$JsonLiteral$isNull(void* this);
struct OBX$Array$1 Json$JsonLiteral$toString(void* this);
struct Json$JsonPureStringParser * Json$createParser(struct OBX$Array$1 input);
struct Json$JsonValue * Json$JsonPureStringParser$parse(void* this);
struct Json$JsonValue * Json$JsonPureStringParser$readValue(void* this);
struct Json$JsonArray * Json$JsonPureStringParser$readArray(void* this);
struct Json$JsonObject * Json$JsonPureStringParser$readObject(void* this);
struct OBX$Array$1 Json$JsonPureStringParser$readName(void* this);
struct Json$JsonValue * Json$JsonPureStringParser$readNull(void* this);
struct Json$JsonValue * Json$JsonPureStringParser$readTrue(void* this);
struct Json$JsonValue * Json$JsonPureStringParser$readFalse(void* this);
void Json$JsonPureStringParser$readRequiredChar(void* this, char ch);
struct Json$JsonValue * Json$JsonPureStringParser$readString(void* this);
struct OBX$Array$1 Json$JsonPureStringParser$readStringInternal(void* this);
void Json$JsonPureStringParser$readEscape(void* this);
struct Json$JsonValue * Json$JsonPureStringParser$readNumber(void* this);
uint8_t Json$JsonPureStringParser$readFraction(void* this);
uint8_t Json$JsonPureStringParser$readExponent(void* this);
void Json$JsonPureStringParser$read(void* this);
uint8_t Json$JsonPureStringParser$readChar(void* this, char ch);
uint8_t Json$JsonPureStringParser$readDigit(void* this);
void Json$JsonPureStringParser$skipWhiteSpace(void* this);
void Json$JsonPureStringParser$startCapture(void* this);
void Json$JsonPureStringParser$pauseCapture(void* this);
struct OBX$Array$1 Json$JsonPureStringParser$endCapture(void* this);
void Json$JsonPureStringParser$captureInput(void* this);
void Json$JsonPureStringParser$captureChar(void* this, char ch);
void Json$JsonPureStringParser$expected(void* this, struct OBX$Array$1 expected);
void Json$JsonPureStringParser$error(void* this, struct OBX$Array$1 message);
uint8_t Json$JsonPureStringParser$isWhiteSpace(void* this);
uint8_t Json$JsonPureStringParser$isDigit(void* this);
uint8_t Json$JsonPureStringParser$isEndOfText(void* this);
struct Json$ValueResult$Class$ {
    struct Benchmark$Result$Class$* super$;
};
extern struct Json$ValueResult$Class$ Json$ValueResult$class$;

struct Json$JsonPureStringParser$Class$ {
    struct Json$JsonPureStringParser$Class$* super$;
    struct Json$JsonValue * (*parse)(void* this);
    struct Json$JsonValue * (*readValue)(void* this);
    struct Json$JsonArray * (*readArray)(void* this);
    struct Json$JsonObject * (*readObject)(void* this);
    struct OBX$Array$1 (*readName)(void* this);
    struct Json$JsonValue * (*readNull)(void* this);
    struct Json$JsonValue * (*readTrue)(void* this);
    struct Json$JsonValue * (*readFalse)(void* this);
    void (*readRequiredChar)(void* this, char ch);
    struct Json$JsonValue * (*readString)(void* this);
    struct OBX$Array$1 (*readStringInternal)(void* this);
    void (*readEscape)(void* this);
    struct Json$JsonValue * (*readNumber)(void* this);
    uint8_t (*readFraction)(void* this);
    uint8_t (*readExponent)(void* this);
    void (*read)(void* this);
    uint8_t (*readChar)(void* this, char ch);
    uint8_t (*readDigit)(void* this);
    void (*skipWhiteSpace)(void* this);
    void (*startCapture)(void* this);
    void (*pauseCapture)(void* this);
    struct OBX$Array$1 (*endCapture)(void* this);
    void (*captureInput)(void* this);
    void (*captureChar)(void* this, char ch);
    void (*expected)(void* this, struct OBX$Array$1 expected);
    void (*error)(void* this, struct OBX$Array$1 message);
    uint8_t (*isWhiteSpace)(void* this);
    uint8_t (*isDigit)(void* this);
    uint8_t (*isEndOfText)(void* this);
};
extern struct Json$JsonPureStringParser$Class$ Json$JsonPureStringParser$class$;

struct Json$HashIndexTable$Class$ {
    struct Json$HashIndexTable$Class$* super$;
    void (*add)(void* this, struct OBX$Array$1 name, int32_t index);
    int32_t (*get)(void* this, struct OBX$Array$1 name);
};
extern struct Json$HashIndexTable$Class$ Json$HashIndexTable$class$;

struct Json$JsonLiteral$Class$ {
    struct Json$JsonValue$Class$* super$;
    uint8_t (*isObject)(void* this);
    uint8_t (*isArray)(void* this);
    uint8_t (*isNumber)(void* this);
    uint8_t (*isString)(void* this);
    uint8_t (*isBoolean)(void* this);
    uint8_t (*isTrue)(void* this);
    uint8_t (*isFalse)(void* this);
    uint8_t (*isNull)(void* this);
    struct OBX$Array$1 (*toString)(void* this);
    struct Json$JsonArray * (*asArray)(void* this);
    struct Json$JsonObject * (*asObject)(void* this);
};
extern struct Json$JsonLiteral$Class$ Json$JsonLiteral$class$;

struct Json$JsonString$Class$ {
    struct Json$JsonValue$Class$* super$;
    uint8_t (*isObject)(void* this);
    uint8_t (*isArray)(void* this);
    uint8_t (*isNumber)(void* this);
    uint8_t (*isString)(void* this);
    uint8_t (*isBoolean)(void* this);
    uint8_t (*isTrue)(void* this);
    uint8_t (*isFalse)(void* this);
    uint8_t (*isNull)(void* this);
    struct OBX$Array$1 (*toString)(void* this);
    struct Json$JsonArray * (*asArray)(void* this);
    struct Json$JsonObject * (*asObject)(void* this);
};
extern struct Json$JsonString$Class$ Json$JsonString$class$;

struct Json$Json$Class$ {
    struct Benchmark$Benchmark$Class$* super$;
    struct Benchmark$Result * (*benchmark)(void* this);
    uint8_t (*verifyResult)(void* this, struct Benchmark$Result * result);
    uint8_t (*innerBenchmarkLoop)(void* this, int32_t innerIterations);
};
extern struct Json$Json$Class$ Json$Json$class$;

struct Json$JsonArray$Class$ {
    struct Json$JsonValue$Class$* super$;
    uint8_t (*isObject)(void* this);
    uint8_t (*isArray)(void* this);
    uint8_t (*isNumber)(void* this);
    uint8_t (*isString)(void* this);
    uint8_t (*isBoolean)(void* this);
    uint8_t (*isTrue)(void* this);
    uint8_t (*isFalse)(void* this);
    uint8_t (*isNull)(void* this);
    struct OBX$Array$1 (*toString)(void* this);
    struct Json$JsonArray * (*asArray)(void* this);
    struct Json$JsonObject * (*asObject)(void* this);
    struct Json$JsonArray * (*add)(void* this, struct Json$JsonValue * value);
    int32_t (*size)(void* this);
    struct Json$JsonValue * (*get)(void* this, int32_t index);
};
extern struct Json$JsonArray$Class$ Json$JsonArray$class$;

struct Json$JsonNumber$Class$ {
    struct Json$JsonValue$Class$* super$;
    uint8_t (*isObject)(void* this);
    uint8_t (*isArray)(void* this);
    uint8_t (*isNumber)(void* this);
    uint8_t (*isString)(void* this);
    uint8_t (*isBoolean)(void* this);
    uint8_t (*isTrue)(void* this);
    uint8_t (*isFalse)(void* this);
    uint8_t (*isNull)(void* this);
    struct OBX$Array$1 (*toString)(void* this);
    struct Json$JsonArray * (*asArray)(void* this);
    struct Json$JsonObject * (*asObject)(void* this);
};
extern struct Json$JsonNumber$Class$ Json$JsonNumber$class$;

struct Json$JsonValue$Class$ {
    struct Json$JsonValue$Class$* super$;
    uint8_t (*isObject)(void* this);
    uint8_t (*isArray)(void* this);
    uint8_t (*isNumber)(void* this);
    uint8_t (*isString)(void* this);
    uint8_t (*isBoolean)(void* this);
    uint8_t (*isTrue)(void* this);
    uint8_t (*isFalse)(void* this);
    uint8_t (*isNull)(void* this);
    struct OBX$Array$1 (*toString)(void* this);
    struct Json$JsonArray * (*asArray)(void* this);
    struct Json$JsonObject * (*asObject)(void* this);
};
extern struct Json$JsonValue$Class$ Json$JsonValue$class$;

struct Json$JsonObject$Class$ {
    struct Json$JsonValue$Class$* super$;
    uint8_t (*isObject)(void* this);
    uint8_t (*isArray)(void* this);
    uint8_t (*isNumber)(void* this);
    uint8_t (*isString)(void* this);
    uint8_t (*isBoolean)(void* this);
    uint8_t (*isTrue)(void* this);
    uint8_t (*isFalse)(void* this);
    uint8_t (*isNull)(void* this);
    struct OBX$Array$1 (*toString)(void* this);
    struct Json$JsonArray * (*asArray)(void* this);
    struct Json$JsonObject * (*asObject)(void* this);
    struct Json$JsonObject * (*add)(void* this, struct OBX$Array$1 name, struct Json$JsonValue * value);
    struct Json$JsonValue * (*get)(void* this, struct OBX$Array$1 name);
    int32_t (*indexOf)(void* this, struct OBX$Array$1 name);
    int32_t (*size)(void* this);
    uint8_t (*isEmpty)(void* this);
};
extern struct Json$JsonObject$Class$ Json$JsonObject$class$;

extern void Json$init$(void);
extern OBX$Cmd Json$cmd$(const char* name);
#endif