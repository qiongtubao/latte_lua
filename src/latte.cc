#include "./lua/lua.hpp"
#include "./mlua.h"
#include <node.h>
#include <v8.h>
#include <string>
#include <iostream>

using namespace v8;
using namespace std;

void doFileSync(const v8::FunctionCallbackInfo<Value>& args) {
  latteLua* lua  = new latteLua();
  bool ok = lua->loadFile(args[0]);
  if(!ok) {
    delete lua;
    return;
  }
  ok = lua->getMethod(args[1]);
  if(!ok) {
    delete lua;
    return;
  }
  if(!args[2] -> IsNumber()) {
    cout << "lua params number" << endl;
    delete lua;
    return;
  }
  double params = args[2]->NumberValue();
  for(int i = 0; i < params; i++) {
      lua->Push(args[3+i]);
  }
  lua->Call(params, 1);
  args.GetReturnValue().Set(lua->Pull());
  delete lua;
}

void Init(Handle<Object>exports) {
  NODE_SET_METHOD(exports, "doFileSync", doFileSync);
}

NODE_MODULE(node_lua, Init);
