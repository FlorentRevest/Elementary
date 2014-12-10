
//var efl = require('../../../efl-js/build/src/lib/eolian_js/.libs/efl')
var elm = require('../../build/src/lib/.libs/elm')

win = new elm.Elm_Win (null, 'name', 0);
win.title_set('title');

bg = new elm.Elm_Bg (win);
bg.size_hint_weight_set(1.0, 1.0);
win.resize_object_add(bg);
bg.visibility_set(true);

btn = new elm.Elm_Button (win);
btn.size_set(50, 20);
btn.text_set('elm.text', 'Botao');
btn.visibility_set(true);
btn.event_clicked(function()
                  {
                      process.stdout.write("Function called\n");
                  });

win.size_set(300, 320);
win.visibility_set(true);

process.stdout.write("Going to wait now\n");
