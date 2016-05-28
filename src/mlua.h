#include "./lua/lua.hpp"
#include <node.h>
#include <v8.h>
#include <string>
#include <iostream>

using namespace v8;
using namespace std;

class latteLua
{
public:
   latteLua();
   ~latteLua();
   bool loadScript(char *code);
   bool loadFile(char *fileName);
   bool loadFile(Local<Value> value);
   bool getMethod(Local<Value> value);
   bool getMethod(char *methodName);
   bool Push(Local<Value> value);
   bool pushNumber(Local<Value> value);
   bool pushString(Local<Value> value);
   bool pushBoolean(Local<Value> value);
   bool pushArray(Local<Value> value);
   bool pushObject(Local<Value> value);
   Local<Value> Pull();
   Local<Value> pullBoolean();
   Local<Value> pullString();
   Local<Value> pullObject();
   Local<Value> pullNumber();

   bool Call(int inNum, int OutNum);
 private:
   lua_State *lua;
   Isolate* isolate;

};
