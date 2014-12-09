
#ifdef HAVE_CONFIG_H
#include <elementary_config.h>
#endif

#include <Elementary.h>

#include <node/node.h>
#include <node/uv.h>

#include <iostream>

#include <Efl.h>
#include <Eo.h>
#include <Ecore.h>
#include <Ecore_Evas.h>

EAPI void register_elm_win(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_bg(v8::Handle<v8::Object> global, v8::Isolate* isolate);

namespace {

// Ecore_Evas* ee;
  
void init(v8::Handle<v8::Object> exports)
{
  std::cout << "init hey " << std::endl;
  static char* argv[] = {"node"};
  ::elm_init(1, argv);
  
  // ee = ecore_evas_new(NULL, 100, 100, 200, 200, NULL);
  // ecore_evas_show(ee);
  try
    {
      register_elm_win(exports, v8::Isolate::GetCurrent());
      register_elm_bg(exports, v8::Isolate::GetCurrent());
    }
  catch(...)
    {
      std::cout << "Exception" << std::endl;
    }

  std::cout << "inited " << std::endl;
}
  
}

NODE_MODULE(elm, init)


