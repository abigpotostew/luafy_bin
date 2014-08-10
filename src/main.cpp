#include "ofMain.h"
#include "ofGLProgrammableRenderer.h"

#include "luaOfApp.h"

#include <getopt.h>
#include <stdio.h> //for printf

void print_usage(const char* prog_name){
   fprintf(stderr, "Usage: %s [-fw:h:pr:s] lua_script_path\n %s %s %s %s %s %s %s", prog_name,
       " -f: Supply this option to enable fullscreen.\n",
       " -w width: Set GL context width. Default 1024.\n",
       " -h height:  Set GL context height. Default 768.\n",
       " -p: Use OpenGL programmable renderer.\n",
       " -r data_path: Set the working directory root to another path. Default is this executable's path.\n",
       " -s \"Lua String\": Double quoted lua string to prerun before executing the main script.\n",
       " lua_script_path: Path to an ofxLua script for execution.\n"
           );
}

//========================================================================
int main( int argc, char** argv ){
   int width = 1024;
   int height = 768;
   bool fullscreen = false;
   string data_root = "";
   bool use_programmable_renderer = false;
   int opt;
   string script;
   string prerun_script("");
   
   while ((opt = getopt(argc, argv, "fw::h::pr::")) != -1) {
      string oa;
      if (optarg)
         oa = string(optarg);
      switch (opt) {
         case 'f':
            fullscreen = 1;
            break;
         case 'w':
            width = atoi(optarg);
            break;
         case 'h':
            height = atoi(optarg);
            break;
         case 'p':
            use_programmable_renderer = true;
            break;
         case 'r':
            data_root = string(optarg);
            break;
         case 's':
            prerun_script = string(optarg);
            break;
         default: /* '?' */
            print_usage(argv[0]);
            exit(EXIT_FAILURE);
      }
   }
   if (data_root.compare("") != 0){
      ofSetDataPathRoot(data_root);
   }
   //Error if script path isn't passed in
   if (optind >= argc) {
      print_usage(argv[0]);
      exit(EXIT_FAILURE);
   }else{
      script = string(argv[optind]);
   }
   
   // Now run our app with options ///////////////////////////////
   // Setup the GL context
   if ( use_programmable_renderer ){
      ofPtr<ofBaseRenderer> renderer(new ofGLProgrammableRenderer(false));
      ofSetCurrentRenderer(renderer, false);
   }
   ofSetupOpenGL (width, height, fullscreen? OF_FULLSCREEN: OF_WINDOW);
   
   // this kicks off the running of my app
   // can be OF_WINDOW or OF_FULLSCREEN
   // pass in width and height too:
   ofRunApp ( new LuaOfApp (&script, &prerun_script) );
   
   
   
   
   return 0;
}
