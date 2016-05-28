#include "./mlua.h"



latteLua::latteLua() {
    lua = luaL_newstate();
    luaL_openlibs(lua);
    if(NULL == lua) {
        cout << "luaL_newstate()没有足够的内存分配\n" << endl;
        return;
    }
    isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
}
latteLua::~latteLua() {
    lua_close(lua);
}

bool latteLua::loadScript(char *code) {
  return true;
}
bool latteLua::loadFile(Local<Value> value) {
  if(!value ->IsString() ){
      cout << "lua file name is not string"<< endl;
      return false;
  }
  String::Utf8Value args0(value -> ToString());
  char * filePath = *args0;
  loadFile(filePath);
  return true;
}

bool latteLua::loadFile(char *fileName) {
  int iRet = luaL_dofile(lua, fileName);
  return iRet == 0;
}
bool latteLua::getMethod(Local<Value> value) {
  if(!value-> IsString()) {
    cout << "lua method name is not string" <<endl;
    return false;
  }
  String::Utf8Value args1(value -> ToString());
  char * methodName = *args1;
  return getMethod(methodName);
}
bool latteLua::getMethod(char *methodName) {
  lua_getglobal(lua, methodName);
  return true;
}
bool latteLua::Push(Local<Value> value) {
  if(value -> IsString()) {
    return this -> pushString(value);
  }
  if(value -> IsNumber()) {
    return this -> pushNumber(value);
  }
  if(value -> IsBoolean()) {
    return this -> pushBoolean(value);
  }
  if(value ->IsArray()) {
    return this -> pushArray(value);
  }
  if(value->IsObject()) {
    return this -> pushObject(value);
  }
  return false;
}
bool latteLua::pushString(Local<Value> value) {
  String::Utf8Value value1(value -> ToString());
  char * value2 = *value1;
  lua_pushstring(lua, value2);
  return true;
}
bool latteLua::pushNumber(Local<Value> value) {
  lua_pushnumber(lua, value->NumberValue());
  return true;
}
bool latteLua::pushBoolean(Local<Value> value) {
  lua_pushboolean(lua, value ->  BooleanValue());
  return true;
}
bool latteLua::pushArray(Local<Value> value) {
  lua_newtable(lua);
  Local<Object> object = value  ->ToObject();
  int length = object -> Get(String::NewFromUtf8(isolate,"length"))->ToObject()->Uint32Value();
  for(int index = 0; index < length; index++)
  {
      Local<Value> element = object ->Get(index);
      lua_pushnumber(lua, index);
      this -> Push(element);
      lua_settable(lua, -3);
  }
  return true;
}
bool latteLua::pushObject(Local<Value> value) {
  lua_newtable(lua);
  Local<Object> object = value -> ToObject();
  Local<Array> array = object->GetPropertyNames();
  int length = array -> Get(String::NewFromUtf8(isolate, "length")) ->ToObject() ->Uint32Value();
  for(int index = 0; index < length; index++) {
    String::Utf8Value param(array ->Get(index) -> ToString());
    char *p = *param;
    lua_pushstring(lua, p);
    Local<Value> element = object ->Get(array ->Get(index) -> ToString());
    this->Push(element);
    lua_settable(lua, -3);
  }
  return true;
}
bool  latteLua::Call(int inNum, int outNum) {
  int iRet = lua_pcall(lua, inNum, outNum, 0);
  if(0 != iRet) {
      printf("lua_pcall failed:%s\n",lua_tostring(lua,-1));
      lua_close(lua);
      return false;
  }
  return true;
}

Local<Value> latteLua::Pull() {
  if(lua_isnumber(lua, -1) == 1) {
    return pullNumber();
  }
  if(lua_isstring(lua, -1) == 1) {
    return pullString();
  }
  if(lua_isboolean(lua, -1) ==1) {
      return pullBoolean();
  }
  if(lua_istable(lua , -1) == 1 ) {
      return pullObject();
  }
}
Local<Value> latteLua::pullNumber() {
  return Number::New(isolate, lua_tonumber(lua, -1));
}
Local<Value> latteLua::pullString() {
  return String::NewFromUtf8(isolate, lua_tostring(lua, -1));
}
Local<Value> latteLua::pullBoolean() {
  return Boolean::New(isolate, lua_toboolean(lua, -1));
}
//遍历算法
Local<Value> latteLua::pullObject() {
  lua_pushnil(lua);
  //Local<Array> array = Array::New(isolate);
  Local<Object> object = Object::New(isolate);
  bool isArray = true;
  while(lua_next(lua,-2)){
    if(lua_isnumber(lua,-2)) {
      //array->Set(Number::New(isolate, lua_tonumber(lua, -2)), Pull());
      object->Set(Number::New(isolate, lua_tonumber(lua, -2)), Pull());
    }else if(lua_isstring(lua,-2)){
      //array->Set(String::NewFromUtf8(isolate, lua_tostring(lua, -2)), Pull());
      object->Set(String::NewFromUtf8(isolate, lua_tostring(lua, -2)), Pull());
      isArray = false;
    }
    lua_pop(lua,1);
  }
  //lua_pop(lua,1);
  if(isArray) {
      //return array;
      return object;
  }else{
      return object;
      //return (((Local<Object>)array) ->ToObject()) -> Clone() ;
  }

}
