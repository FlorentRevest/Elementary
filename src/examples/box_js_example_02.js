
//var efl = require('../../../efl-js/build/src/lib/eolian_js/.libs/efl')
var elm = require('../../build/src/lib/.libs/elm')

win = new elm.Elm_Win (null, 'name', 0);
win.title_set('title');

bg = new elm.Elm_Bg (win);
bg.size_hint_weight_set(1.0, 1.0);
win.resize_object_add(bg);
//bg.show();
bg.color_set(0, 0, 0, 255);
bg.visibility_set(true);

win.size_set(100, 100);
win.visibility_set(true);

//win.show();
