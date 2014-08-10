#include "luaOfApp.h"


//--------------------------------------------------------------
void LuaOfApp::setup(){
   
   ofSetVerticalSync (true);
   //ofSetLogLevel("ofxLua", OF_LOG_VERBOSE);
   
   // Clear lua state
   lua.init (true);
   
   // Set error catching
   lua.addListener (this);
   
   // Bind of api
   lua.bind<ofxLuaBindings>();
   
   // Add script path to lua path so require() works correctly
   std::string fullpath = ofFilePath::getAbsolutePath(ofToDataPath(*script));
   std::string folder = ofFilePath::getEnclosingDirectory(fullpath);
   std::string new_path("package.path = '");
   new_path.append(folder);
   new_path.append("?.lua;' .. package.path;");
   lua.doString(new_path);
   
   if( prerun_script->compare("") !=0 ){
      lua.doString(prerun_script->c_str());
   }
   
   lua.bind<ofPrintWrapper>();
   
   lua.doString("print = function (...) local msg=''; local arg={...}; "\
                "for i,v in ipairs(arg) do "\
                "msg = string.format('%s%s\t', msg, tostring(v)) end; "\
                "of.printToConsole(msg); end"
                );
   
   // Run a script for the first pass
   lua.doScript (*script);
   
   // Call script's setup()
   lua.scriptSetup();
}

//--------------------------------------------------------------
void LuaOfApp::update(){
   lua.scriptUpdate();
}

//--------------------------------------------------------------
void LuaOfApp::draw(){
   lua.scriptDraw();
}

//--------------------------------------------------------------
void LuaOfApp::keyPressed(int key){
   lua.scriptKeyPressed (key);
}

//--------------------------------------------------------------
void LuaOfApp::keyReleased(int key){
   lua.scriptKeyReleased (key);
}

//--------------------------------------------------------------
void LuaOfApp::mouseMoved(int x, int y){
   lua.scriptMouseMoved (x, y);
}

//--------------------------------------------------------------
void LuaOfApp::mouseDragged(int x, int y, int button){
   lua.scriptMouseDragged (x, y, button);
}

//--------------------------------------------------------------
void LuaOfApp::mousePressed(int x, int y, int button){
   lua.scriptMousePressed (x, y, button);
}

//--------------------------------------------------------------
void LuaOfApp::mouseReleased(int x, int y, int button){
   lua.scriptMouseReleased (x, y, button);
}

//--------------------------------------------------------------
void LuaOfApp::windowResized(int w, int h){
   
}

//--------------------------------------------------------------
void LuaOfApp::gotMessage(ofMessage msg){
   
}

//--------------------------------------------------------------
void LuaOfApp::dragEvent(ofDragInfo dragInfo){
   
}

void LuaOfApp::errorReceived(string& msg){
   ofLogError() << "script error: " << msg;
}

void LuaOfApp::exit(){
   lua.scriptExit();
   
   lua.clear();
}

void ofPrintWrapper::bind(ofxLua& _lua){
   using namespace luabind;
   
   module(_lua, "of")	// create an "of" table namespace
   [
    // bind a function
    def("printToConsole", &ofPrintWrapper::lua_print)
    ];
}

// Print using default log level, which can be set in lua script using:
// of.setLogLevelWrapper( of.LogLevel.[VERBOSE, ERROR, etc...] )
void ofPrintWrapper::lua_print(const char* msg){
   ofLog()<<msg;
}
