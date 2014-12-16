
//var efl = require('../../../efl-js/build/src/lib/eolian_js/.libs/efl')
var elm = require('../../build/src/lib/.libs/elm')

win = new elm.Elm_Win (null, 'name', 0);
win.title_set('title');
win.autodel_set(true);

bg = new elm.Elm_Bg (win);
bg.size_hint_weight_set(1.0, 1.0);
win.resize_object_add(bg);
bg.visibility_set(true);

bx = new elm.Elm_Box(win);
bx.size_hint_weight_set(1.0, 1.0);
win.resize_object_add(bx);

entry = new elm.Elm_Label(win);
entry.size_set(100, 100);
entry.text_set(null, "Texto");

console.log('Texto: ', entry.text_get(null));

entry.size_hint_weight_set(1.0, 1.0);
entry.size_hint_align_set(-1.0, -1.0);
entry.wrap_width_set(50);
bx.pack_end(entry);
entry.visibility_set(true);

bx.visibility_set(true);

win.size_set(300, 320);
win.visibility_set(true);

console.log('twitter new');

// var util = require('util');
// var twitter = require('twitter');

// console.log('twitter new2');

// var twit = new twitter
// ({
//     consumer_key: 'hbKPGbDQaRAxhhOkhYoT78njJ',
//     consumer_secret: 'v78BnM0FChcv4cueA6anoOkEY1AD6dlfUgaUell8dbPU2iIzrr',
//     access_token_key: '2421100004-rY8RkslfoURYkSvJ82Wj8hoBrvB8vTZ67EORDCM',
//     access_token_secret: 'cq95ImdFSBnUlNVMs0GTaJ2Ed9eIFKYaCzU2y6uaFezkb',
// })

// console.log('twitter login');

// twit.verifyCredentials(function(data) {
//       console.log("Nome ", data['name']);
//     })

// twit.stream('user', {track:'leisecarj'}, function(stream) {
//     stream.on('data', function(data) {
//         console.log('stream.on');
//         if(data['text'])
//            {
//                console.log('Has text ', data['text']);
//                entry.text_set(null, data['text']);
//            }
//         console.log(util.inspect(data));
//     });
// });

console.log("Going to wait now\n");
