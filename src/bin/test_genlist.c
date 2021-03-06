#include <Elementary_Cursor.h>
#include "test.h"
#ifdef HAVE_CONFIG_H
#include "elementary_config.h"
#endif
#include <Elementary.h>

Evas_Object * _elm_min_set(Evas_Object *obj, Evas_Object *parent,
                           Evas_Coord w, Evas_Coord h);

struct _api_data
{
   unsigned int state;  /* What state we are testing       */
   void *box;           /* Use this to get box content     */

   Elm_Genlist_Item_Class *itc;
   Elm_Genlist_Item_Class *itc1;
   Elm_Genlist_Item_Class *itc2;
   void *gl;
};
typedef struct _api_data api_data;

enum _api_state
{
   HORIZONTAL_SET,
   NO_SELECT_MODE_SET,
   COMPRESS_MODE_SET,
   BOUNCE_SET,
   HOMOGENEOUS_SET,
   SCROLLER_POLICY_SET,
   TOOLTIP_TEXT_SET,
   ITEM_CURSOR_SET,
   API_STATE_LAST
};
typedef enum _api_state api_state;

static void
set_api_state(api_data *api)
{
   const Eina_List *items = elm_box_children_get(api->box);
   if (!eina_list_count(items))
     return;

   Evas_Object *gl = eina_list_nth(items, 0); /* Genlist is the first item */
   /* use elm_box_children_get() to get list of children */
   switch(api->state)
     {/* Put all api-changes under switch */
      case HORIZONTAL_SET: /* 0 */
         elm_genlist_mode_set(gl, ELM_LIST_LIMIT);
         break;

      case NO_SELECT_MODE_SET: /* 1 */
         elm_genlist_select_mode_set(gl, ELM_OBJECT_SELECT_MODE_NONE);
         elm_genlist_mode_set(gl, ELM_LIST_SCROLL); /* Back to default */
         break;

      case COMPRESS_MODE_SET: /* 2 */
         elm_genlist_select_mode_set(gl, ELM_OBJECT_SELECT_MODE_DEFAULT);
         elm_genlist_mode_set(gl, ELM_LIST_COMPRESS);
         break;

      case BOUNCE_SET: /* 3 */
         elm_scroller_bounce_set(gl, EINA_FALSE, EINA_FALSE);
         break;

      case HOMOGENEOUS_SET: /* 4 */
         elm_scroller_bounce_set(gl, EINA_TRUE, EINA_TRUE); /* Back to default */
         elm_genlist_homogeneous_set(gl, EINA_TRUE);
         break;

      case SCROLLER_POLICY_SET: /* 5 */
         elm_genlist_homogeneous_set(gl, EINA_FALSE); /* Back to default */
         elm_scroller_policy_set(gl, ELM_SCROLLER_POLICY_ON, ELM_SCROLLER_POLICY_ON);
         break;

      case TOOLTIP_TEXT_SET: /* 6 */
           {
              elm_genlist_item_tooltip_text_set(elm_genlist_first_item_get(gl), "Tooltip text from API");
              elm_genlist_item_bring_in(elm_genlist_first_item_get(gl),
                                         ELM_GENLIST_ITEM_SCROLLTO_IN);
           }
         break;

      case ITEM_CURSOR_SET: /* 7 */
         elm_genlist_item_cursor_set(elm_genlist_first_item_get(gl), ELM_CURSOR_HAND2);
         break;

      default:
         return;
     }
}

static void
_api_bt_clicked(void *data, Evas_Object *obj, void *event_info EINA_UNUSED)
{  /* Will add here a SWITCH command containing code to modify test-object */
   /* in accordance a->state value. */
   api_data *a = data;
   char str[128];

   INF("clicked event on API Button: api_state=<%d>", a->state);
   set_api_state(a);
   a->state++;
   sprintf(str, "Next API function (%u)", a->state);
   elm_object_text_set(obj, str);
   elm_object_disabled_set(obj, a->state == API_STATE_LAST);
}
/* Hint:
 * In this example some calls to elm_genlist_item_append() are used which give the
 * value of an int as 'item data' and 'func data' after casting into (void*). For
 * sure this works only on architectures where sizeof(int)==sizeof(void*).
 * For real world usage you should hold a data structure or value in your
 * application and then give only a pointer to this data as data pointer.
 */

typedef struct _Testitem
{
   Elm_Object_Item *item;
   int mode;
   int onoff;
   Eina_Bool checked;
} Testitem;

static char *
gl_text_get1(void *data, Evas_Object *obj EINA_UNUSED, const char *part EINA_UNUSED)
{
   char buf[256];
   int num = (int)(uintptr_t)data;

   if (num == 5)
     snprintf(buf, sizeof(buf), "Item # %i (Genlist Cleear on Select)", num);
   else
     snprintf(buf, sizeof(buf), "Item # %i", num);

   return strdup(buf);
}

Evas_Object *gl_content_get(void *data EINA_UNUSED, Evas_Object *obj, const char *part)
{
   char buf[PATH_MAX];
   Evas_Object *ic = elm_icon_add(obj);
   if (!strcmp(part, "elm.swallow.end"))
     snprintf(buf, sizeof(buf), "%s/images/bubble.png", elm_app_data_dir_get());
   else
     snprintf(buf, sizeof(buf), "%s/images/logo_small.png", elm_app_data_dir_get());
   elm_image_file_set(ic, buf, NULL);
   evas_object_size_hint_aspect_set(ic, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
   return ic;
}

static void on_bt_clicked(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   printf("button clicked\n");
}

static void on_ck_changed(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   printf("checkbox changed\n");
}

Evas_Object *gl_content_full_get(void *data EINA_UNUSED, Evas_Object *obj, const char *part)
{
   Evas_Object *fr, *bx, *ic, *bt, *ck;

   if (strcmp(part, "elm.swallow.content") != 0) return NULL;

   fr = elm_frame_add(obj);
   elm_layout_text_set(fr, NULL, "A Frame");

   bx = elm_box_add(fr);
   elm_box_horizontal_set(bx, EINA_TRUE);

   ic = elm_icon_add(bx);
   elm_icon_standard_set(ic, "home");
   evas_object_size_hint_min_set(ic,
                                 ELM_SCALE_SIZE(32),
                                 ELM_SCALE_SIZE(32));
   evas_object_size_hint_align_set(ic, 0.5, EVAS_HINT_FILL);
   evas_object_show(ic);
   elm_box_pack_end(bx, ic);

   bt = elm_button_add(bx);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_smart_callback_add(bt, "clicked", on_bt_clicked, NULL);
   elm_layout_text_set(bt, NULL, "Click Me");
   evas_object_show(bt);
   elm_box_pack_end(bx, bt);

   ck = elm_check_add(bx);
   evas_object_size_hint_align_set(ck, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(ck, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_smart_callback_add(ck, "changed", on_ck_changed, NULL);
   elm_layout_text_set(ck, NULL, "some checkbox");
   evas_object_show(ck);
   elm_box_pack_end(bx, ck);

   elm_layout_content_set(fr, NULL, bx);
   evas_object_size_hint_min_set(fr,
                                 ELM_SCALE_SIZE(100),
                                 ELM_SCALE_SIZE(100));

   return fr;
}


Eina_Bool gl_state_get(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, const char *part EINA_UNUSED)
{
   return EINA_FALSE;
}

static void
gl_sel(void *data, Evas_Object *obj, void *event_info)
{
   printf("sel item data [%p] on genlist obj [%p], item pointer [%p], index [%d]\n",
          data, obj, event_info, elm_genlist_item_index_get(event_info));
}

static void
gl_sel_clear_cb(void *data EINA_UNUSED, Evas_Object *obj,
                void *event_info EINA_UNUSED)
{
   elm_genlist_clear(obj);
}

static void
_move(void *data, Evas *evas EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info)
{
   Evas_Object *gl = data;
   Evas_Event_Mouse_Move *ev = event_info;
   int where = 0;
   Elm_Object_Item *gli;
   gli = elm_genlist_at_xy_item_get(gl, ev->cur.canvas.x, ev->cur.canvas.y, &where);
   if (gli)
     INF("<%s> over %p, where %i\n", __func__, elm_object_item_data_get(gli), where);
   else
     INF("<%s> over none, where %i\n", __func__,where);
}

static void
_bt50_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   elm_genlist_item_bring_in(data, ELM_GENLIST_ITEM_SCROLLTO_IN);
}

static void
_bt1500_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   elm_genlist_item_bring_in(data, ELM_GENLIST_ITEM_SCROLLTO_MIDDLE);
}

static void
_gl_selected(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info)
{
   printf("selected: %p\n", event_info);
}

static void
_gl_double_clicked(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info)
{
   printf("double clicked: %p\n", event_info);
}

static void
_gl_right_clicked(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info)
{
   printf("right clicked: %p\n", event_info);
}

static void
_gl_longpress(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info)
{
   printf("longpress %p\n", event_info);
}

static void
_cleanup_cb(void *data, Evas *e EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   free(data);
}

void
test_genlist(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Evas_Object *win, *gl, *bt_50, *bt_1500, *bx, *bxx, *bt;
   Evas_Object *over;
   Elm_Object_Item *gli;
   int i;
   api_data *api = calloc(1, sizeof(api_data));

   win = elm_win_util_standard_add("genlist", "Genlist");
   elm_win_autodel_set(win, EINA_TRUE);
   evas_object_event_callback_add(win, EVAS_CALLBACK_FREE, _cleanup_cb, api);

   bxx = elm_box_add(win);
   evas_object_size_hint_weight_set(bxx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, bxx);
   evas_object_show(bxx);

   bx = elm_box_add(win);
   evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(bx, EVAS_HINT_FILL, EVAS_HINT_FILL);
   api->box = bx;
   evas_object_show(bx);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Next API function");
   evas_object_smart_callback_add(bt, "clicked", _api_bt_clicked, (void *) api);
   elm_box_pack_end(bxx, bt);
   elm_object_disabled_set(bt, api->state == API_STATE_LAST);
   evas_object_show(bt);

   elm_box_pack_end(bxx, bx);

   gl = elm_genlist_add(win);
   evas_object_smart_callback_add(gl, "selected", _gl_selected, NULL);
   evas_object_smart_callback_add(gl, "clicked,double", _gl_double_clicked, NULL);
   evas_object_smart_callback_add(gl, "clicked,right", _gl_right_clicked, NULL);
   evas_object_smart_callback_add(gl, "longpressed", _gl_longpress, NULL);
   // FIXME: This causes genlist to resize the horiz axis very slowly :(
   // Reenable this and resize the window horizontally, then try to resize it back
   //elm_genlist_mode_set(gl, ELM_LIST_LIMIT);
   evas_object_size_hint_weight_set(gl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(gl, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(bx, gl);
   evas_object_show(gl);

   over = evas_object_rectangle_add(evas_object_evas_get(win));
   evas_object_color_set(over, 0, 0, 0, 0);
   evas_object_event_callback_add(over, EVAS_CALLBACK_MOUSE_MOVE, _move, gl);
   evas_object_repeat_events_set(over, EINA_TRUE);
   evas_object_show(over);
   evas_object_size_hint_weight_set(over, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, over);

   api->itc1 = elm_genlist_item_class_new();
   api->itc1->item_style = "default";
   api->itc1->func.text_get = gl_text_get1;
   api->itc1->func.content_get = gl_content_get;
   api->itc1->func.state_get = gl_state_get;
   api->itc1->func.del = NULL;

   bt_50 = elm_button_add(win);
   elm_object_text_set(bt_50, "Go to 50");
   evas_object_show(bt_50);
   elm_box_pack_end(bx, bt_50);

   bt_1500 = elm_button_add(win);
   elm_object_text_set(bt_1500, "Go to 1500");
   evas_object_show(bt_1500);
   elm_box_pack_end(bx, bt_1500);

   for (i = 0; i < 2000; i++)
     {
        if (i == 5)
          {
             gli = elm_genlist_item_append(gl, api->itc1,
                                           (void *)(uintptr_t)i/* item data */,
                                           NULL/* parent */,
                                           ELM_GENLIST_ITEM_NONE,
                                           gl_sel_clear_cb/* func */,
                                           (void *)(uintptr_t)(i * 10)/* func data */);
          }
        else
          {
             gli = elm_genlist_item_append(gl, api->itc1,
                                           (void *)(uintptr_t)i/* item data */,
                                           NULL/* parent */,
                                           ELM_GENLIST_ITEM_NONE,
                                           gl_sel/* func */,
                                           (void *)(uintptr_t)(i * 10)/* func data */);
          }

        if (i == 50)
          evas_object_smart_callback_add(bt_50, "clicked", _bt50_cb, gli);
        else if (i == 1500)
          evas_object_smart_callback_add(bt_1500, "clicked", _bt1500_cb, gli);
     }
   elm_genlist_item_class_free(api->itc1);

   evas_object_resize(win, 480, 800);
   evas_object_show(win);
}

/*************/

static void
my_gl_clear(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   elm_genlist_clear(data);
}

static char *
gl_text_get(void *data, Evas_Object *obj EINA_UNUSED, const char *part EINA_UNUSED)
{
   char buf[256];
   snprintf(buf, sizeof(buf), "Item # %i", (int)(uintptr_t)data);
   return strdup(buf);
}
static void
my_gl_add(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   api_data *api = data;
   Evas_Object *gl = api->gl;   
   static int i = 0;

   if (!api->itc1)
     {
        ERR("Genlist item class should not be null. Something very bad is happening!!");
        return;
     }

   api->itc1->item_style = "default";
   api->itc1->func.text_get = gl_text_get;
   api->itc1->func.content_get = gl_content_get;
   api->itc1->func.state_get = gl_state_get;
   api->itc1->func.del = NULL;

   elm_genlist_item_append(gl, api->itc1,
                           (void *)(uintptr_t)i/* item data */,
                           NULL/* parent */,
                           ELM_GENLIST_ITEM_NONE,
                           gl_sel/* func */,
                           (void *)(uintptr_t)(i * 10)/* func data */);
   i++;
}

static void
my_gl_insert_before(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   api_data *api = data;
   Evas_Object *gl = api->gl;
   static int i = 0;
   Elm_Object_Item *gli_selected;

   if (!api->itc1)
     {
        ERR("Genlist item class should not be null. Something very bad is happening!!");
        return;
     }

   api->itc1->item_style = "default";
   api->itc1->func.text_get = gl_text_get;
   api->itc1->func.content_get = gl_content_get;
   api->itc1->func.state_get = gl_state_get;
   api->itc1->func.del = NULL;

   gli_selected = elm_genlist_selected_item_get(gl);
   if (!gli_selected)
     {
        printf("no item selected\n");
        return ;
     }

   elm_genlist_item_insert_before(gl, api->itc1,
                                  (void *)(uintptr_t)i/* item data */,
                                  NULL/* parent */,
                                  gli_selected /* item before */,
                                  ELM_GENLIST_ITEM_NONE,
                                  gl_sel/* func */,
                                  (void *)(uintptr_t)(i * 10)/* func data */);
   i++;
}

static void
my_gl_insert_after(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   api_data *api = data;
   Evas_Object *gl = api->gl;
   static int i = 0;
   Elm_Object_Item *gli_selected;

   if (!api->itc1)
     {
        ERR("Genlist item class should not be null. Something very bad is happening!!");
        return;
     }

   api->itc1->item_style = "default";
   api->itc1->func.text_get = gl_text_get;
   api->itc1->func.content_get = gl_content_get;
   api->itc1->func.state_get = gl_state_get;
   api->itc1->func.del = NULL;

   gli_selected = elm_genlist_selected_item_get(gl);
   if (!gli_selected)
     {
        printf("no item selected\n");
        return ;
     }

   elm_genlist_item_insert_after(gl, api->itc1,
                                 (void *)(uintptr_t)i/* item data */,
                                 NULL/* parent */,
                                 gli_selected /* item after */,
                                 ELM_GENLIST_ITEM_NONE,
                                 gl_sel/* func */,
                                 (void *)(uintptr_t)(i * 10)/* func data */);
   i++;
}

static void
my_gl_del(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   api_data *api = data;
   Evas_Object *gl = api->gl;
   Elm_Object_Item *gli = elm_genlist_selected_item_get(gl);
   if (!gli)
     {
        printf("no item selected\n");
        return;
     }
   elm_object_item_del(gli);
}

static void
my_gl_disable(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   api_data *api = data;
   Evas_Object *gl = api->gl;
   Elm_Object_Item *gli = elm_genlist_selected_item_get(gl);
   if (!gli)
     {
        printf("no item selected\n");
        return;
     }
   elm_object_item_disabled_set(gli, EINA_TRUE);
   elm_genlist_item_selected_set(gli, EINA_FALSE);
   elm_genlist_item_update(gli);
}

static void
my_gl_update_all(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   api_data *api = data;
   Evas_Object *gl = api->gl;
   int i = 0;
   Elm_Object_Item *it = elm_genlist_first_item_get(gl);
   while (it)
     {
        elm_genlist_item_update(it);
        INF("%i", i);
        i++;
        it = elm_genlist_item_next_get(it);
     }
}

static void
my_gl_first(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   api_data *api = data;
   Evas_Object *gl = api->gl;
   Elm_Object_Item *gli = elm_genlist_first_item_get(gl);
   if (!gli) return;
   elm_genlist_item_show(gli, ELM_GENLIST_ITEM_SCROLLTO_IN);
   elm_genlist_item_selected_set(gli, 1);
}

static void
my_gl_last(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   api_data *api = data;
   Evas_Object *gl = api->gl;
   Elm_Object_Item *gli = elm_genlist_last_item_get(gl);
   if (!gli) return;
   elm_genlist_item_show(gli, ELM_GENLIST_ITEM_SCROLLTO_IN);
   elm_genlist_item_selected_set(gli, 1);
}

static Eina_Bool
my_gl_flush_delay(void *data EINA_UNUSED)
{
   elm_cache_all_flush();
   return ECORE_CALLBACK_CANCEL;
}

static void
my_gl_flush(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   ecore_timer_add(1.2, my_gl_flush_delay, NULL);
}

static void
_genlist_del_cb(void *data, Evas *evas EINA_UNUSED, Evas_Object *obj EINA_UNUSED,
                void *event_info EINA_UNUSED)
{
   if (!data) return;

   elm_genlist_item_class_free(data);
}

void
test_genlist2(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Evas_Object *win, *bg, *gl, *bx, *bx2, *bx3, *bt;
   Elm_Object_Item *gli[10];
   char buf[PATH_MAX];

   api_data *api = calloc(1, sizeof(api_data));
   win = elm_win_add(NULL, "genlist2", ELM_WIN_BASIC);
   elm_win_title_set(win, "Genlist 2");
   elm_win_autodel_set(win, EINA_TRUE);
   evas_object_event_callback_add(win, EVAS_CALLBACK_FREE, _cleanup_cb, api);

   bg = elm_bg_add(win);
   snprintf(buf, sizeof(buf), "%s/images/plant_01.jpg", elm_app_data_dir_get());
   elm_bg_file_set(bg, buf, NULL);
   evas_object_size_hint_weight_set(bg, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, bg);
   evas_object_show(bg);

   bx = elm_box_add(win);
   evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, bx);
   evas_object_show(bx);

   gl = elm_genlist_add(win);
   elm_genlist_mode_set(gl, ELM_LIST_COMPRESS);
   evas_object_size_hint_align_set(gl, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(gl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   api->gl = gl;
   evas_object_show(gl);

   api->itc1 = elm_genlist_item_class_new();
   api->itc1->item_style = "default";
   api->itc1->func.text_get = gl_text_get;
   api->itc1->func.content_get  = gl_content_get;
   api->itc1->func.state_get = gl_state_get;
   api->itc1->func.del = NULL;

   gli[0] = elm_genlist_item_append(gl, api->itc1,
                                    (void *)1001/* item data */, NULL/* parent */, ELM_GENLIST_ITEM_NONE, gl_sel/* func */,
                                    (void *)1001/* func data */);
   gli[1] = elm_genlist_item_append(gl, api->itc1,
                                    (void *)1002/* item data */, NULL/* parent */, ELM_GENLIST_ITEM_NONE, gl_sel/* func */,
                                    (void *)1002/* func data */);
   gli[2] = elm_genlist_item_append(gl, api->itc1,
                                    (void *)1003/* item data */, NULL/* parent */, ELM_GENLIST_ITEM_NONE, gl_sel/* func */,
                                    (void *)1003/* func data */);
   gli[3] = elm_genlist_item_prepend(gl, api->itc1,
                                     (void *)1004/* item data */, NULL/* parent */, ELM_GENLIST_ITEM_NONE, gl_sel/* func */,
                                     (void *)1004/* func data */);
   gli[4] = elm_genlist_item_prepend(gl, api->itc1,
                                     (void *)1005/* item data */, NULL/* parent */, ELM_GENLIST_ITEM_NONE, gl_sel/* func */,
                                     (void *)1005/* func data */);
   gli[5] = elm_genlist_item_insert_before(gl, api->itc1,
                                           (void *)1006/* item data */, NULL/* parent */, gli[2]/* rel */, ELM_GENLIST_ITEM_NONE,
                                           gl_sel/* func */, (void *)1006/* func data */);
   gli[6] = elm_genlist_item_insert_after(gl, api->itc1,
                                          (void *)1007/* item data */, NULL/* parent */, gli[2]/* rel */, ELM_GENLIST_ITEM_NONE,
                                          gl_sel/* func */, (void *)1007/* func data */);
   elm_box_pack_end(bx, gl);

   bx2 = elm_box_add(win);
   elm_box_horizontal_set(bx2, EINA_TRUE);
   elm_box_homogeneous_set(bx2, EINA_TRUE);
   evas_object_size_hint_weight_set(bx2, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(bx2, EVAS_HINT_FILL, EVAS_HINT_FILL);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "/\\");
   evas_object_smart_callback_add(bt, "clicked", my_gl_first, api);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "\\/");
   evas_object_smart_callback_add(bt, "clicked", my_gl_last, api);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "#");
   evas_object_smart_callback_add(bt, "clicked", my_gl_disable, api);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "U");
   evas_object_smart_callback_add(bt, "clicked", my_gl_update_all, api);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_show(bt);

   elm_box_pack_end(bx, bx2);
   evas_object_show(bx2);

   bx2 = elm_box_add(win);
   elm_box_horizontal_set(bx2, EINA_TRUE);
   elm_box_homogeneous_set(bx2, EINA_TRUE);
   evas_object_size_hint_weight_set(bx2, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(bx2, EVAS_HINT_FILL, EVAS_HINT_FILL);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "X");
   evas_object_smart_callback_add(bt, "clicked", my_gl_clear, gl);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "+");
   evas_object_smart_callback_add(bt, "clicked", my_gl_add, api);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "-");
   evas_object_smart_callback_add(bt, "clicked", my_gl_del, api);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_show(bt);

   elm_box_pack_end(bx, bx2);
   evas_object_show(bx2);

   bx3 = elm_box_add(win);
   elm_box_horizontal_set(bx3, EINA_TRUE);
   elm_box_homogeneous_set(bx3, EINA_TRUE);
   evas_object_size_hint_weight_set(bx3, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(bx3, EVAS_HINT_FILL, EVAS_HINT_FILL);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "+ before");
   evas_object_smart_callback_add(bt, "clicked", my_gl_insert_before, api);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx3, bt);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "+ after");
   evas_object_smart_callback_add(bt, "clicked", my_gl_insert_after, api);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx3, bt);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Flush");
   evas_object_smart_callback_add(bt, "clicked", my_gl_flush, api);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx3, bt);
   evas_object_show(bt);

   elm_box_pack_end(bx, bx3);
   evas_object_show(bx3);

   evas_object_event_callback_add(gl, EVAS_CALLBACK_DEL, _genlist_del_cb, api->itc1);
   
   evas_object_resize(win, 320, 320);
   evas_object_show(win);
}

/*************/
char *gl2_text_get(void *data, Evas_Object *obj EINA_UNUSED, const char *part EINA_UNUSED)
{
   const Testitem *tit = data;
   char buf[256];
   snprintf(buf, sizeof(buf), "Item mode %i", tit->mode);
   return strdup(buf);
}

Evas_Object *gl2_content_get(void *data, Evas_Object *obj, const char *part)
{
   const Testitem *tit = data;
   char buf[PATH_MAX];
   Evas_Object *ic = elm_icon_add(obj);
   if (!strcmp(part, "elm.swallow.icon"))
     {
        if (!(tit->mode & 0x3))
          snprintf(buf, sizeof(buf), "%s/images/logo_small.png", elm_app_data_dir_get());
        else if ((tit->mode & 0x3) == 1)
          snprintf(buf, sizeof(buf), "%s/images/logo.png", elm_app_data_dir_get());
        else if ((tit->mode & 0x3) == 2)
          snprintf(buf, sizeof(buf), "%s/images/panel_01.jpg", elm_app_data_dir_get());
        else if ((tit->mode & 0x3) == 3)
          snprintf(buf, sizeof(buf), "%s/images/rock_01.jpg", elm_app_data_dir_get());
        elm_image_file_set(ic, buf, NULL);
     }
   else if (!strcmp(part, "elm.swallow.end"))
     {
        if (!(tit->mode & 0x3))
          snprintf(buf, sizeof(buf), "%s/images/sky_01.jpg", elm_app_data_dir_get());
        else if ((tit->mode & 0x3) == 1)
          snprintf(buf, sizeof(buf), "%s/images/sky_02.jpg", elm_app_data_dir_get());
        else if ((tit->mode & 0x3) == 2)
          snprintf(buf, sizeof(buf), "%s/images/sky_03.jpg", elm_app_data_dir_get());
        else if ((tit->mode & 0x3) == 3)
          snprintf(buf, sizeof(buf), "%s/images/sky_04.jpg", elm_app_data_dir_get());
        elm_image_file_set(ic, buf, NULL);
     }
   evas_object_size_hint_aspect_set(ic, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
   return ic;
}

Eina_Bool gl2_state_get(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, const char *part EINA_UNUSED)
{
   return EINA_FALSE;
}

static void
my_gl_update(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Testitem *tit = data;
   tit->mode++;
   elm_genlist_item_update(tit->item);
}

static void
my_gl_labels_update(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Testitem *tit = data;
   tit->mode++;
   elm_genlist_item_fields_update(tit->item, "*", ELM_GENLIST_ITEM_FIELD_TEXT);
}

static void
my_gl_contents_update(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Testitem *tit = data;
   tit->mode++;
   elm_genlist_item_fields_update(tit->item, "*", ELM_GENLIST_ITEM_FIELD_CONTENT);
}

void
test_genlist3(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Evas_Object *win, *gl, *bx, *bx2, *bt;
   static Testitem tit[3];

   api_data *api = calloc(1, sizeof(api_data));
   win = elm_win_util_standard_add("genlist3", "Genlist 3");
   elm_win_autodel_set(win, EINA_TRUE);
   evas_object_event_callback_add(win, EVAS_CALLBACK_FREE, _cleanup_cb, api);

   bx = elm_box_add(win);
   evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, bx);
   evas_object_show(bx);

   gl = elm_genlist_add(win);
   evas_object_size_hint_align_set(gl, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(gl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_show(gl);

   api->itc1 = elm_genlist_item_class_new();
   api->itc1->item_style = "default";
   api->itc1->func.text_get = gl2_text_get;
   api->itc1->func.content_get = gl2_content_get;
   api->itc1->func.state_get = gl2_state_get;
   api->itc1->func.del = NULL;

   tit[0].mode = 0;
   tit[0].item = elm_genlist_item_append(gl, api->itc1,
                                         &(tit[0])/* item data */, NULL/* parent */, ELM_GENLIST_ITEM_NONE, gl_sel/* func */,
                                         NULL/* func data */);
   tit[1].mode = 1;
   tit[1].item = elm_genlist_item_append(gl, api->itc1,
                                         &(tit[1])/* item data */, NULL/* parent */, ELM_GENLIST_ITEM_NONE, gl_sel/* func */,
                                         NULL/* func data */);
   tit[2].mode = 2;
   tit[2].item = elm_genlist_item_append(gl, api->itc1,
                                         &(tit[2])/* item data */, NULL/* parent */, ELM_GENLIST_ITEM_NONE, gl_sel/* func */,
                                         NULL/* func data */);

   elm_box_pack_end(bx, gl);
   evas_object_show(bx);

   bx2 = elm_box_add(win);
   elm_box_horizontal_set(bx2, EINA_TRUE);
   elm_box_homogeneous_set(bx2, EINA_TRUE);
   evas_object_size_hint_weight_set(bx2, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(bx2, EVAS_HINT_FILL, EVAS_HINT_FILL);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "[1]");
   evas_object_smart_callback_add(bt, "clicked", my_gl_update, &(tit[0]));
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "labels");
   evas_object_smart_callback_add(bt, "clicked", my_gl_labels_update, &(tit[1]));
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "contents");
   evas_object_smart_callback_add(bt, "clicked", my_gl_contents_update, &(tit[2]));
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_show(bt);

   elm_box_pack_end(bx, bx2);
   evas_object_show(bx2);

   elm_genlist_item_class_free(api->itc1);
   evas_object_resize(win, 320, 320);
   evas_object_show(win);
}

/*************/

static void
my_gl_item_check_changed(void *data, Evas_Object *obj, void *event_info EINA_UNUSED)
{
   Testitem *tit = data;
   tit->onoff = elm_check_state_get(obj);
   printf("item %p onoff = %i\n", tit, tit->onoff);
}

char *gl3_text_get(void *data, Evas_Object *obj EINA_UNUSED, const char *part EINA_UNUSED)
{
   const Testitem *tit = data;
   char buf[256];
   snprintf(buf, sizeof(buf), "Item mode %i", tit->mode);
   return strdup(buf);
}

Evas_Object *gl3_content_get(void *data, Evas_Object *obj, const char *part)
{
   const Testitem *tit = data;
   if (!strcmp(part, "elm.swallow.icon"))
     {
        Evas_Object *lb;

        lb = elm_label_add(obj);
        elm_label_line_wrap_set(lb, ELM_WRAP_CHAR);
        elm_label_wrap_width_set(lb, 201);
        elm_object_text_set(lb, "ashj ascjscjh n asjkl hcjlh ls hzshnn zjh sh zxjcjsnd h dfw sdv edev efe fwefvv vsd cvs ws wf  fvwf wd fwe f  we wef we wfe rfwewef wfv wswf wefg sdfws w wsdcfwcf wsc vdv  sdsd sdcd cv wsc sdcv wsc d sdcdcsd sdcdsc wdvd sdcsd wscxcv wssvd sd");
        return lb;
     }
   else if (!strcmp(part, "elm.swallow.end"))
     {
        Evas_Object *ck;
        ck = elm_check_add(obj);
        evas_object_propagate_events_set(ck, EINA_FALSE);
        elm_check_state_set(ck, tit->onoff);
        evas_object_smart_callback_add(ck, "changed", my_gl_item_check_changed, data);
        return ck;
     }
   return NULL;
}

Eina_Bool gl3_state_get(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, const char *part EINA_UNUSED)
{
   return EINA_FALSE;
}

static void _realized(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *ei)
{
   Evas_Object *check;
   Eina_List *items;
   items = NULL;

   if (!ei) return;
   Elm_Object_Item *item = ei;

   check = elm_object_item_part_content_get(item, "elm.swallow.end");

   if (!check) return;

   items = eina_list_append(items, check);
   elm_object_item_access_order_set(item, items);
}

void
test_genlist4(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Evas_Object *win, *gl, *bx, *bx2, *bt;
   static Testitem tit[3];

   api_data *api = calloc(1, sizeof(api_data));
   win = elm_win_util_standard_add("genlist4", "Genlist 4");
   elm_win_autodel_set(win, EINA_TRUE);
   evas_object_event_callback_add(win, EVAS_CALLBACK_FREE, _cleanup_cb, api);

   bx = elm_box_add(win);
   evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, bx);
   evas_object_show(bx);

   gl = elm_genlist_add(win);
   elm_genlist_mode_set(gl, ELM_LIST_COMPRESS);
   elm_genlist_multi_select_set(gl, EINA_TRUE);
   evas_object_size_hint_align_set(gl, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(gl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   api->gl = gl;
   evas_object_show(gl);

   evas_object_smart_callback_add(gl, "realized", _realized, NULL);

   api->itc1 = elm_genlist_item_class_new();
   api->itc1->item_style = "default";
   api->itc1->func.text_get = gl3_text_get;
   api->itc1->func.content_get = gl3_content_get;
   api->itc1->func.state_get = gl3_state_get;
   api->itc1->func.del = NULL;

   tit[0].mode = 0;
   tit[0].item = elm_genlist_item_append(gl, api->itc1,
                                         &(tit[0])/* item data */, NULL/* parent */, ELM_GENLIST_ITEM_NONE, gl_sel/* func */,
                                         NULL/* func data */);
   tit[1].mode = 1;
   tit[1].item = elm_genlist_item_append(gl, api->itc1,
                                         &(tit[1])/* item data */, NULL/* parent */, ELM_GENLIST_ITEM_NONE, gl_sel/* func */,
                                         NULL/* func data */);
   tit[2].mode = 2;
   tit[2].item = elm_genlist_item_append(gl, api->itc1,
                                         &(tit[2])/* item data */, NULL/* parent */, ELM_GENLIST_ITEM_NONE, gl_sel/* func */,
                                         NULL/* func data */);

   elm_genlist_item_class_free(api->itc1);
   elm_box_pack_end(bx, gl);
   evas_object_show(bx);

   bx2 = elm_box_add(win);
   elm_box_horizontal_set(bx2, EINA_TRUE);
   elm_box_homogeneous_set(bx2, EINA_TRUE);
   evas_object_size_hint_weight_set(bx2, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(bx2, EVAS_HINT_FILL, EVAS_HINT_FILL);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "[1]");
   evas_object_smart_callback_add(bt, "clicked", my_gl_update, &(tit[0]));
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "[2]");
   evas_object_smart_callback_add(bt, "clicked", my_gl_update, &(tit[1]));
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "[3]");
   evas_object_smart_callback_add(bt, "clicked", my_gl_update, &(tit[2]));
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_show(bt);

   elm_box_pack_end(bx, bx2);
   evas_object_show(bx2);

   evas_object_resize(win, 320, 320);
   evas_object_show(win);
}

/*************/

static void
my_gl_item_check_changed2(void *data, Evas_Object *obj, void *event_info EINA_UNUSED)
{
   Testitem *tit = data;
   tit->onoff = elm_check_state_get(obj);
   printf("item %p onoff = %i\n", tit, tit->onoff);
}

char *gl5_text_get(void *data, Evas_Object *obj EINA_UNUSED, const char *part)
{
   const Testitem *tit = data;
   char buf[256] = { 0 };
   if (!strcmp(part, "elm.text"))
     {
        snprintf(buf, sizeof(buf), "Item mode %i", tit->mode);
     }
   else if (!strcmp(part, "elm.text.sub"))
     {
        snprintf(buf, sizeof(buf), "%i bottles on the wall", tit->mode);
     }
   return strdup(buf);
}

Evas_Object *gl5_content_get(void *data, Evas_Object *obj, const char *part)
{
   const Testitem *tit = data;
   char buf[PATH_MAX];
   if (!strcmp(part, "elm.swallow.icon"))
     {
        Evas_Object *bx = elm_box_add(obj);
        Evas_Object *ic;
        elm_box_horizontal_set(bx, EINA_TRUE);
        ic = elm_icon_add(obj);
        snprintf(buf, sizeof(buf), "%s/images/logo_small.png", elm_app_data_dir_get());
        elm_image_file_set(ic, buf, NULL);
        elm_image_resizable_set(ic, EINA_FALSE, EINA_FALSE);
        evas_object_show(ic);
        elm_box_pack_end(bx, ic);
        ic = elm_icon_add(obj);
        elm_image_file_set(ic, buf, NULL);
        elm_image_resizable_set(ic, EINA_FALSE, EINA_FALSE);
        evas_object_show(ic);
        elm_box_pack_end(bx, ic);
        elm_box_horizontal_set(bx, EINA_TRUE);
        evas_object_show(bx);
        return bx;
     }
   else if (!strcmp(part, "elm.swallow.end"))
     {
        Evas_Object *ck;
        ck = elm_check_add(obj);
        evas_object_propagate_events_set(ck, EINA_FALSE);
        elm_check_state_set(ck, tit->onoff);
        evas_object_smart_callback_add(ck, "changed", my_gl_item_check_changed2, data);
        evas_object_show(ck);
        return ck;
     }
   return NULL;
}

Eina_Bool gl5_state_get(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, const char *part EINA_UNUSED)
{
   return EINA_FALSE;
}

static void
item_drag_up(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   INF("drag up");
}

static void
item_drag_down(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   INF("drag down");
}

static void
item_drag_left(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   INF("drag left");
}

static void
item_drag_right(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   INF("drag right");
}

static void
scroll_top(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   INF("Top edge!");
}

static void
scroll_bottom(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   INF("Bottom edge!");
}

static void
scroll_left(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   INF("Left edge!");
}

static void
scroll_right(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   INF("Right edge!");
}

static void
item_drag(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   INF("drag");
}

static void
item_drag_stop(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   INF("drag stop");
}

static void
item_longpress(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   INF("longpress");
}

void
test_genlist5(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Evas_Object *win, *gl, *bx, *bx2, *bt;
   static Testitem tit[3];

   api_data *api = calloc(1, sizeof(api_data));
   win = elm_win_util_standard_add("genlist5", "Genlist 5");
   elm_win_autodel_set(win, EINA_TRUE);
   elm_win_focus_highlight_enabled_set(win, EINA_TRUE);
   evas_object_event_callback_add(win, EVAS_CALLBACK_FREE, _cleanup_cb, api);

   bx = elm_box_add(win);
   evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, bx);
   evas_object_show(bx);

   gl = elm_genlist_add(win);
   elm_genlist_select_mode_set(gl, ELM_OBJECT_SELECT_MODE_ALWAYS);
   evas_object_size_hint_align_set(gl, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(gl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   api->gl = gl;
   evas_object_show(gl);

   api->itc1 = elm_genlist_item_class_new();
   api->itc1->item_style = "double_label";
   api->itc1->func.text_get = gl5_text_get;
   api->itc1->func.content_get = gl5_content_get;
   api->itc1->func.state_get = gl5_state_get;
   api->itc1->func.del = NULL;

   tit[0].mode = 0;
   tit[0].item = elm_genlist_item_append(gl, api->itc1,
                                         &(tit[0])/* item data */, NULL/* parent */, ELM_GENLIST_ITEM_NONE, gl_sel/* func */,
                                         NULL/* func data */);
   tit[1].mode = 1;
   tit[1].item = elm_genlist_item_append(gl, api->itc1,
                                         &(tit[1])/* item data */, NULL/* parent */, ELM_GENLIST_ITEM_NONE, gl_sel/* func */,
                                         NULL/* func data */);
   tit[2].mode = 2;
   tit[2].item = elm_genlist_item_append(gl, api->itc1,
                                         &(tit[2])/* item data */, NULL/* parent */, ELM_GENLIST_ITEM_NONE, gl_sel/* func */,
                                         NULL/* func data */);

   elm_box_pack_end(bx, gl);
   evas_object_show(bx);

   evas_object_smart_callback_add(gl, "drag,start,up", item_drag_up, NULL);
   evas_object_smart_callback_add(gl, "drag,start,down", item_drag_down, NULL);
   evas_object_smart_callback_add(gl, "drag,start,left", item_drag_left, NULL);
   evas_object_smart_callback_add(gl, "drag,start,right", item_drag_right, NULL);
   evas_object_smart_callback_add(gl, "drag", item_drag, NULL);
   evas_object_smart_callback_add(gl, "drag,stop", item_drag_stop, NULL);
   evas_object_smart_callback_add(gl, "longpressed", item_longpress, NULL);

   bx2 = elm_box_add(win);
   elm_box_horizontal_set(bx2, EINA_TRUE);
   elm_box_homogeneous_set(bx2, EINA_TRUE);
   evas_object_size_hint_weight_set(bx2, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(bx2, EVAS_HINT_FILL, EVAS_HINT_FILL);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "[1]");
   evas_object_smart_callback_add(bt, "clicked", my_gl_update, &(tit[0]));
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "[2]");
   evas_object_smart_callback_add(bt, "clicked", my_gl_update, &(tit[1]));
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "[3]");
   evas_object_smart_callback_add(bt, "clicked", my_gl_update, &(tit[2]));
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_show(bt);

   elm_box_pack_end(bx, bx2);
   evas_object_show(bx2);

   elm_genlist_item_class_free(api->itc1);
   evas_object_resize(win, 320, 320);
   evas_object_show(win);
}

/*************/

static void
gl4_sel(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info)
{
   Elm_Object_Item *glit = event_info;
   int depth = elm_genlist_item_expanded_depth_get(glit);
   printf("expanded depth for selected item is %d", depth);
}

static void
gl4_exp(void *data, Evas_Object *obj EINA_UNUSED, void *event_info)
{
   api_data *api = data;
   Elm_Object_Item *glit = event_info;
   Evas_Object *gl = elm_object_item_widget_get(glit);
   int val = (int)(uintptr_t) elm_object_item_data_get(glit);
   int i = 0;

   val *= 10;
   for (i = 0; i < 10; i++)
     {
        elm_genlist_item_append(gl, api->itc2,
                                (void *)(uintptr_t) (val + i)/* item data */,
                                glit/* parent */,
                                ELM_GENLIST_ITEM_TREE, gl4_sel/* func */,
                                NULL/* func data */);
     }
}

static void
gl4_con(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info)
{
   Elm_Object_Item *glit = event_info;
   const Eina_List *list = NULL, *l = NULL;
   Elm_Object_Item *it = NULL;

   printf("\n");

   list = elm_genlist_item_subitems_get(glit);
   EINA_LIST_FOREACH(list, l, it)
     {
        printf("sub item: %p %s\n", it, elm_object_item_text_get(it));
     }

   elm_genlist_item_subitems_clear(glit);
}

static void
gl4_exp_req(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info)
{
   Elm_Object_Item *glit = event_info;
   elm_genlist_item_expanded_set(glit, EINA_TRUE);
}

static void
gl4_con_req(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info)
{
   Elm_Object_Item *glit = event_info;
   elm_genlist_item_expanded_set(glit, EINA_FALSE);
}

char *gl4_text_get(void *data, Evas_Object *obj EINA_UNUSED, const char *part EINA_UNUSED)
{
   char buf[256];
   snprintf(buf, sizeof(buf), "Item mode %i", (int)(uintptr_t)data);
   return strdup(buf);
}

Evas_Object *gl4_content_get(void *data EINA_UNUSED, Evas_Object *obj, const char *part)
{
   char buf[PATH_MAX];
   if (!strcmp(part, "elm.swallow.icon"))
     {
        Evas_Object *ic = elm_icon_add(obj);
        snprintf(buf, sizeof(buf), "%s/images/logo_small.png", elm_app_data_dir_get());
        elm_image_file_set(ic, buf, NULL);
        evas_object_size_hint_aspect_set(ic, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
        evas_object_show(ic);
        return ic;
     }
   else if (!strcmp(part, "elm.swallow.end"))
     {
        Evas_Object *ck;
        ck = elm_check_add(obj);
        evas_object_propagate_events_set(ck, EINA_FALSE);
        evas_object_show(ck);
        return ck;
     }
   return NULL;
}

Eina_Bool gl4_state_get(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, const char *part EINA_UNUSED)
{
   return EINA_FALSE;
}

void gl4_del(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED)
{
   printf("item deleted.\n");
}

static void
_tree_effect_enable_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   elm_genlist_tree_effect_enabled_set(data, EINA_TRUE);
}

static void
_tree_effect_disable_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   elm_genlist_tree_effect_enabled_set(data, EINA_FALSE);
}

void
test_genlist6(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Evas_Object *win, *gl, *bx, *fr, *bx2, *rd1, *rd2;

   api_data *api = calloc(1, sizeof(api_data));
   win = elm_win_util_standard_add("genlist-tree", "Genlist Tree");
   elm_win_autodel_set(win, EINA_TRUE);
   evas_object_event_callback_add(win, EVAS_CALLBACK_FREE, _cleanup_cb, api);

   bx = elm_box_add(win);
   evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, bx);
   evas_object_show(bx);

   fr = elm_frame_add(win);
   elm_object_text_set(fr, "Genlist Tree Effect");
   elm_box_pack_end(bx, fr);
   evas_object_show(fr);

   bx2 = elm_box_add(win);
   elm_box_horizontal_set(bx2, EINA_TRUE);
   elm_box_homogeneous_set(bx2, EINA_TRUE);
   evas_object_size_hint_weight_set(bx2, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(bx2, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_object_content_set(fr, bx2);
   evas_object_show(bx2);

   rd1 = elm_radio_add(win);
   elm_radio_state_value_set(rd1, 0);
   elm_object_text_set(rd1, "Enable    ");
   evas_object_show(rd1);
   elm_box_pack_end(bx2, rd1);

   rd2 = elm_radio_add(win);
   elm_radio_state_value_set(rd2, 1);
   elm_radio_group_add(rd1, rd2);
   elm_object_text_set(rd2, "Disable");
   evas_object_show(rd2);
   elm_box_pack_end(bx2, rd2);

   gl = elm_genlist_add(win);
   evas_object_size_hint_align_set(gl, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(gl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   api->gl = gl;
   evas_object_show(gl);
   elm_genlist_tree_effect_enabled_set(gl, EINA_TRUE);
   evas_object_smart_callback_add(gl, "edge,left", scroll_left, NULL);
   evas_object_smart_callback_add(gl, "edge,right", scroll_right, NULL);
   evas_object_smart_callback_add(gl, "edge,top", scroll_top, NULL);
   evas_object_smart_callback_add(gl, "edge,bottom", scroll_bottom, NULL);

   api->itc1 = elm_genlist_item_class_new();
   api->itc1->item_style = "default";
   api->itc1->func.text_get = gl4_text_get;
   api->itc1->func.content_get = gl4_content_get;
   api->itc1->func.state_get = gl4_state_get;
   api->itc1->func.del = gl4_del;

   api->itc2 = elm_genlist_item_class_new();
   api->itc2->item_style = "tree_effect";
   api->itc2->func.text_get = gl4_text_get;
   api->itc2->func.content_get = gl4_content_get;
   api->itc2->func.state_get = gl4_state_get;
   api->itc2->func.del = gl4_del;

   elm_genlist_item_append(gl, api->itc2,
                           (void *)1/* item data */, NULL/* parent */, ELM_GENLIST_ITEM_TREE, gl4_sel/* func */,
                           NULL/* func data */);
   elm_genlist_item_append(gl, api->itc2,
                           (void *)2/* item data */, NULL/* parent */, ELM_GENLIST_ITEM_TREE, gl4_sel/* func */,
                           NULL/* func data */);
   elm_genlist_item_append(gl, api->itc1,
                           (void *)3/* item data */, NULL/* parent */, ELM_GENLIST_ITEM_NONE, gl4_sel/* func */,
                           NULL/* func data */);

   elm_genlist_item_class_free(api->itc1);
   elm_genlist_item_class_free(api->itc2);

   evas_object_smart_callback_add(gl, "expand,request", gl4_exp_req, api);
   evas_object_smart_callback_add(gl, "contract,request", gl4_con_req, api);
   evas_object_smart_callback_add(gl, "expanded", gl4_exp, api);
   evas_object_smart_callback_add(gl, "contracted", gl4_con, api);

   elm_box_pack_end(bx, gl);

   evas_object_smart_callback_add(rd1, "changed", _tree_effect_enable_cb, gl);
   evas_object_smart_callback_add(rd2, "changed", _tree_effect_disable_cb, gl);

   evas_object_resize(win, 320, 320);
   evas_object_show(win);
}

/*************/

struct genlist7_data
{
   Evas_Object *win, *naviframe;
};

static void
gl_sel7(void *data, Evas_Object *obj, void *event_info)
{
   if (!event_info) return;
   api_data *api = data;
   elm_genlist_item_item_class_update(event_info, api->itc2);
   printf("sel item data [%p] on genlist obj [%p], item pointer [%p], new item style [%s] \n", data, obj, event_info, api->itc2->item_style);
}

static void
_gl7_back_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   struct genlist7_data *info = data;
   if (!info) return;

   elm_naviframe_item_pop(info->naviframe);
}

static void
_gl7_swipe_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info)
{
   struct genlist7_data *info = data;
   Evas_Object *box, *entry, *button;
   char item_data[] = "Just a simple test";

   if ((!event_info) || (!data)) return;

   box = elm_box_add(info->win);
   elm_box_homogeneous_set(box, EINA_FALSE);
   evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_show(box);

   entry = elm_entry_add(info->win);
   elm_entry_scrollable_set(entry, EINA_TRUE);
   elm_entry_editable_set(entry, EINA_FALSE);
   elm_object_text_set(entry, item_data);
   evas_object_size_hint_weight_set(entry, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(entry, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_show(entry);

   button = elm_button_add(info->win);
   elm_object_text_set(button, "back");
   evas_object_size_hint_weight_set(button, EVAS_HINT_EXPAND, 0);
   evas_object_size_hint_align_set(button, EVAS_HINT_FILL, 0);
   evas_object_smart_callback_add(button, "clicked", _gl7_back_cb,
                                  info);
   evas_object_show(button);

   elm_box_pack_start(box, entry);
   elm_box_pack_end(box, button);

   elm_naviframe_item_simple_push(info->naviframe, box);
}

void
test_genlist7(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Evas_Object *win, *gl, *naviframe;
   static struct genlist7_data info;
   static Testitem tit[3];

   api_data *api = calloc(1, sizeof(api_data));
   win = elm_win_util_standard_add("genlist7", "Genlist 7");
   elm_win_autodel_set(win, EINA_TRUE);
   evas_object_event_callback_add(win, EVAS_CALLBACK_FREE, _cleanup_cb, api);
   info.win = win;

   naviframe = elm_naviframe_add(win);
   elm_win_resize_object_add(win, naviframe);
   evas_object_size_hint_weight_set(naviframe, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(naviframe, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_show(naviframe);
   info.naviframe = naviframe;

   gl = elm_genlist_add(win);
   evas_object_size_hint_align_set(gl, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(gl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_smart_callback_add(gl, "swipe", _gl7_swipe_cb, &info);
   api->gl = gl;
   evas_object_show(gl);
   elm_naviframe_item_simple_push(naviframe, gl);

   api->itc1 = elm_genlist_item_class_new();
   api->itc1->item_style = "default";
   api->itc1->func.text_get = gl2_text_get;
   api->itc1->func.content_get = gl2_content_get;
   api->itc1->func.state_get = gl2_state_get;
   api->itc1->func.del = NULL;

   api->itc2 = elm_genlist_item_class_new();
   api->itc2->item_style = "double_label";
   api->itc2->func.text_get = gl5_text_get;
   api->itc2->func.content_get = gl5_content_get;
   api->itc2->func.state_get = gl5_state_get;
   api->itc2->func.del = NULL;

   tit[0].mode = 0;
   tit[0].item = elm_genlist_item_append(gl, api->itc1,
                                         &(tit[0])/* item data */, NULL/* parent */,
                                         ELM_GENLIST_ITEM_NONE, gl_sel7/* func */,
                                         api/* func data */);
   tit[1].mode = 1;
   tit[1].item = elm_genlist_item_append(gl, api->itc1,
                                         &(tit[1])/* item data */, NULL/* parent */,
                                         ELM_GENLIST_ITEM_NONE, gl_sel7/* func */,
                                         api/* func data */);
   tit[2].mode = 2;
   tit[2].item = elm_genlist_item_append(gl, api->itc1,
                                         &(tit[2])/* item data */, NULL/* parent */,
                                         ELM_GENLIST_ITEM_NONE, gl_sel7/* func */,
                                         api/* func data */);

   evas_object_resize(win, 320, 320);
   evas_object_show(win);
}

/*************/

char *gl8_text_get(void *data, Evas_Object *obj EINA_UNUSED, const char *part EINA_UNUSED)
{
   char buf[256];
   snprintf(buf, sizeof(buf), "Group Index # %i (Item # %i)", (int)((uintptr_t)data / 10), (int)(uintptr_t)data);
   return strdup(buf);
}

static void
_bt_show_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   elm_genlist_item_show(data, ELM_GENLIST_ITEM_SCROLLTO_TOP);
}

static void
_bt_bring_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   elm_genlist_item_bring_in(data, ELM_GENLIST_ITEM_SCROLLTO_TOP);
}

void
test_genlist8(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Evas_Object *win, *gl, *bt[8], *bx, *bx2, *bx3;
   Elm_Object_Item *gli = NULL, *git = NULL;
   int i, bt_num;

   api_data *api = calloc(1, sizeof(api_data));
   win = elm_win_util_standard_add("genlist-group", "Genlist Group");
   elm_win_autodel_set(win, EINA_TRUE);
   evas_object_event_callback_add(win, EVAS_CALLBACK_FREE, _cleanup_cb, api);

   bx = elm_box_add(win);
   evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, bx);
   evas_object_show(bx);

   gl = elm_genlist_add(win);
   evas_object_smart_callback_add(gl, "selected", _gl_selected, NULL);
   evas_object_smart_callback_add(gl, "clicked,double", _gl_double_clicked, NULL);
   evas_object_smart_callback_add(gl, "longpressed", _gl_longpress, NULL);
   evas_object_size_hint_weight_set(gl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(gl, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(bx, gl);
   api->gl = gl;
   evas_object_show(gl);

   // Use homogeneous mode for group index + homogeneous test.
   // Homogeneous is not mandatory for group index.
   elm_genlist_homogeneous_set(gl, EINA_TRUE);

   api->itc1 = elm_genlist_item_class_new();
   api->itc1->item_style = "default";
   api->itc1->func.text_get = gl_text_get;
   api->itc1->func.content_get = gl_content_get;
   api->itc1->func.state_get = gl_state_get;
   api->itc1->func.del = NULL;

   api->itc2 = elm_genlist_item_class_new();
   api->itc2->item_style = "group_index";
   api->itc2->func.text_get = gl8_text_get;
   api->itc2->func.content_get = NULL;
   api->itc2->func.state_get = NULL;
   api->itc2->func.del = NULL;

   bx2 = elm_box_add(win);
   elm_box_horizontal_set(bx2, EINA_TRUE);
   elm_box_homogeneous_set(bx2, EINA_TRUE);
   evas_object_size_hint_weight_set(bx2, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(bx2, EVAS_HINT_FILL, EVAS_HINT_FILL);

   bt_num = 0;
   bt[bt_num] = elm_button_add(win);
   elm_object_text_set(bt[bt_num], "Show 0");
   evas_object_size_hint_align_set(bt[bt_num], EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt[bt_num], EVAS_HINT_EXPAND, 0.0);
   evas_object_show(bt[bt_num]);
   elm_box_pack_end(bx2, bt[bt_num]);

   bt[++bt_num] = elm_button_add(win);
   elm_object_text_set(bt[bt_num], "Show 26");
   evas_object_size_hint_align_set(bt[bt_num], EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt[bt_num], EVAS_HINT_EXPAND, 0.0);
   evas_object_show(bt[bt_num]);
   elm_box_pack_end(bx2, bt[bt_num]);

   bt[++bt_num] = elm_button_add(win);
   elm_object_text_set(bt[bt_num], "Show 101");
   evas_object_size_hint_align_set(bt[bt_num], EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt[bt_num], EVAS_HINT_EXPAND, 0.0);
   evas_object_show(bt[bt_num]);
   elm_box_pack_end(bx2, bt[bt_num]);

   bt[++bt_num] = elm_button_add(win);
   elm_object_text_set(bt[bt_num], "Show 480");
   evas_object_size_hint_align_set(bt[bt_num], EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt[bt_num], EVAS_HINT_EXPAND, 0.0);
   evas_object_show(bt[bt_num]);
   elm_box_pack_end(bx2, bt[bt_num]);

   elm_box_pack_end(bx, bx2);
   evas_object_show(bx2);

   bx3 = elm_box_add(win);
   elm_box_horizontal_set(bx3, EINA_TRUE);
   elm_box_homogeneous_set(bx3, EINA_TRUE);
   evas_object_size_hint_weight_set(bx3, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(bx3, EVAS_HINT_FILL, EVAS_HINT_FILL);

   bt[++bt_num] = elm_button_add(win);
   elm_object_text_set(bt[bt_num], "Bring top 0");
   evas_object_size_hint_align_set(bt[bt_num], EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt[bt_num], EVAS_HINT_EXPAND, 0.0);
   evas_object_show(bt[bt_num]);
   elm_box_pack_end(bx3, bt[bt_num]);

   bt[++bt_num] = elm_button_add(win);
   elm_object_text_set(bt[bt_num], "Bring top 31");
   evas_object_size_hint_align_set(bt[bt_num], EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt[bt_num], EVAS_HINT_EXPAND, 0.0);
   evas_object_show(bt[bt_num]);
   elm_box_pack_end(bx3, bt[bt_num]);

   bt[++bt_num] = elm_button_add(win);
   elm_object_text_set(bt[bt_num], "Bring top 239");
   evas_object_size_hint_align_set(bt[bt_num], EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt[bt_num], EVAS_HINT_EXPAND, 0.0);
   evas_object_show(bt[bt_num]);
   elm_box_pack_end(bx3, bt[bt_num]);

   bt[++bt_num] = elm_button_add(win);
   elm_object_text_set(bt[bt_num], "Bring top 477");
   evas_object_size_hint_align_set(bt[bt_num], EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt[bt_num], EVAS_HINT_EXPAND, 0.0);
   evas_object_show(bt[bt_num]);
   elm_box_pack_end(bx3, bt[bt_num]);

   elm_box_pack_end(bx, bx3);
   evas_object_show(bx3);

   for (i = 0; i < 500; i++)
     {
        if (!(i % 10))
          {
             gli = git = elm_genlist_item_append(gl, api->itc2,
                                                 (void *)(uintptr_t)i/* item data */,
                                                 NULL/* parent */,
                                                 ELM_GENLIST_ITEM_GROUP,
                                                 gl_sel/* func */,
                                                 (void *)(uintptr_t)(i * 10)/* func data */);
             elm_genlist_item_select_mode_set(git, ELM_OBJECT_SELECT_MODE_DISPLAY_ONLY);
          }
        else if (git)
          {
             gli = elm_genlist_item_append(gl, api->itc1,
                                           (void *)(uintptr_t)i/* item data */,
                                           git/* parent */,
                                           ELM_GENLIST_ITEM_NONE,
                                           gl_sel/* func */,
                                           (void *)(uintptr_t)(i * 10)/* func data */);
          }
        switch (i)
          {
           case 0:
              evas_object_smart_callback_add(bt[0], "clicked", _bt_show_cb, gli);
              evas_object_smart_callback_add(bt[4], "clicked", _bt_bring_cb, gli);
              break;
           case 26:
              evas_object_smart_callback_add(bt[1], "clicked", _bt_show_cb, gli);
              break;
           case 31:
              evas_object_smart_callback_add(bt[5], "clicked", _bt_bring_cb, gli);
              break;
           case 101:
              evas_object_smart_callback_add(bt[2], "clicked", _bt_show_cb, gli);
              break;
           case 239:
              evas_object_smart_callback_add(bt[6], "clicked", _bt_bring_cb, gli);
              break;
           case 477:
              evas_object_smart_callback_add(bt[7], "clicked", _bt_bring_cb, gli);
              break;
           case 480:
              evas_object_smart_callback_add(bt[3], "clicked", _bt_show_cb, gli);
              break;
          }
     }

   elm_genlist_item_class_free(api->itc1);
   elm_genlist_item_class_free(api->itc2);

   evas_object_resize(win, 480, 800);
   evas_object_show(win);
}

/*************/

static void
gl9_exp(void *data, Evas_Object *obj EINA_UNUSED, void *event_info)
{
   api_data *api = data;
   Elm_Object_Item *glit = event_info;
   Evas_Object *gl = elm_object_item_widget_get(glit);
   int val = (int)(uintptr_t) elm_object_item_data_get(glit);
   val *= 10;
   elm_genlist_item_append(gl, api->itc1,
                           (void *)(uintptr_t) (val + 1)/* item data */,
                           glit/* parent */,
                           ELM_GENLIST_ITEM_NONE, gl4_sel/* func */,
                           NULL/* func data */);
   elm_genlist_item_append(gl, api->itc1,
                           (void *)(uintptr_t) (val + 2)/* item data */,
                           glit/* parent */,
                           ELM_GENLIST_ITEM_NONE, gl4_sel/* func */,
                           NULL/* func data */);
   elm_genlist_item_append(gl, api->itc1,
                           (void *)(uintptr_t) (val + 3)/* item data */,
                           glit/* parent */,
                           ELM_GENLIST_ITEM_TREE, gl4_sel/* func */,
                           NULL/* func data */);
}

static void
gl9_con(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info)
{
   Elm_Object_Item *glit = event_info;
   elm_genlist_item_subitems_clear(glit);
}

static void
gl9_exp_req(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info)
{
   Elm_Object_Item *glit = event_info;
   elm_genlist_item_expanded_set(glit, EINA_TRUE);
}

static void
gl9_con_req(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info)
{
   Elm_Object_Item *glit = event_info;
   elm_genlist_item_expanded_set(glit, EINA_FALSE);
}

void
test_genlist9(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Evas_Object *win, *gl, *bx;
   Elm_Object_Item *git;

   api_data *api = calloc(1, sizeof(api_data));
   win = elm_win_util_standard_add("genlist-group-tree", "Genlist Group Tree");
   elm_win_autodel_set(win, EINA_TRUE);
   evas_object_event_callback_add(win, EVAS_CALLBACK_FREE, _cleanup_cb, api);

   bx = elm_box_add(win);
   evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, bx);
   evas_object_show(bx);

   gl = elm_genlist_add(win);
   evas_object_smart_callback_add(gl, "selected", _gl_selected, NULL);
   evas_object_smart_callback_add(gl, "clicked,double", _gl_double_clicked, NULL);
   evas_object_smart_callback_add(gl, "longpressed", _gl_longpress, NULL);
   evas_object_size_hint_weight_set(gl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(gl, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(bx, gl);
   api->gl = gl;
   evas_object_show(gl);

   api->itc1 = elm_genlist_item_class_new();
   api->itc1->item_style = "default";
   api->itc1->func.text_get = gl_text_get;
   api->itc1->func.content_get = gl_content_get;
   api->itc1->func.state_get = gl_state_get;
   api->itc1->func.del = NULL;

   api->itc2 = elm_genlist_item_class_new();
   api->itc2->item_style = "group_index";
   api->itc2->func.text_get = gl8_text_get;
   api->itc2->func.content_get = NULL;
   api->itc2->func.state_get = NULL;
   api->itc2->func.del = NULL;

   git = elm_genlist_item_append(gl, api->itc2,
                                 (void *)0/* item data */, NULL/* parent */, ELM_GENLIST_ITEM_GROUP, gl4_sel/* func */,
                                 NULL/* func data */);
   elm_genlist_item_select_mode_set(git, ELM_OBJECT_SELECT_MODE_DISPLAY_ONLY);

   elm_genlist_item_append(gl, api->itc1,
                           (void *)1/* item data */, git/* parent */, ELM_GENLIST_ITEM_TREE, gl4_sel/* func */,
                           NULL/* func data */);
   elm_genlist_item_append(gl, api->itc1,
                           (void *)2/* item data */, git/* parent */, ELM_GENLIST_ITEM_NONE, gl4_sel/* func */,
                           NULL/* func data */);
   elm_genlist_item_append(gl, api->itc1,
                           (void *)3/* item data */, git/* parent */, ELM_GENLIST_ITEM_TREE, gl4_sel/* func */,
                           NULL/* func data */);
   git = elm_genlist_item_append(gl, api->itc2,
                                 (void *)4/* item data */, NULL/* parent */, ELM_GENLIST_ITEM_GROUP, gl4_sel/* func */,
                                 NULL/* func data */);
   elm_genlist_item_select_mode_set(git, ELM_OBJECT_SELECT_MODE_DISPLAY_ONLY);

   elm_genlist_item_append(gl, api->itc1,
                           (void *)5/* item data */, git/* parent */, ELM_GENLIST_ITEM_TREE, gl4_sel/* func */,
                           NULL/* func data */);
   elm_genlist_item_append(gl, api->itc1,
                           (void *)6/* item data */, git/* parent */, ELM_GENLIST_ITEM_NONE, gl4_sel/* func */,
                           NULL/* func data */);
   elm_genlist_item_append(gl, api->itc1,
                           (void *)7/* item data */, git/* parent */, ELM_GENLIST_ITEM_TREE, gl4_sel/* func */,
                           NULL/* func data */);
   elm_genlist_item_class_free(api->itc1);
   elm_genlist_item_class_free(api->itc2);

   evas_object_smart_callback_add(gl, "expand,request", gl9_exp_req, api);
   evas_object_smart_callback_add(gl, "contract,request", gl9_con_req, api);
   evas_object_smart_callback_add(gl, "expanded", gl9_exp, api);
   evas_object_smart_callback_add(gl, "contracted", gl9_con, api);

   evas_object_resize(win, 480, 800);
   evas_object_show(win);
}

/*************/
static char *mode_type[] = { "slide", "rotate" };

char *gl10_text_get(void *data, Evas_Object *obj EINA_UNUSED, const char *part)
{
   char buf[256];
   if (!strcmp(part, "elm.text.mode"))
     snprintf(buf, sizeof(buf), "Mode # %i", (int)(uintptr_t)data);
   else
     snprintf(buf, sizeof(buf), "Item # %i", (int)(uintptr_t)data);
   return strdup(buf);
}

Evas_Object *gl10_content_get(void *data EINA_UNUSED, Evas_Object *obj, const char *part)
{
   char buf[PATH_MAX];
   Evas_Object *ic = elm_icon_add(obj);
   if (!strcmp(part, "elm.swallow.end"))
     snprintf(buf, sizeof(buf), "%s/images/bubble.png", elm_app_data_dir_get());
   else
     snprintf(buf, sizeof(buf), "%s/images/logo_small.png", elm_app_data_dir_get());
   elm_image_file_set(ic, buf, NULL);
   evas_object_size_hint_aspect_set(ic, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
   return ic;
}

static void
_gl_sel10(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   if (!data) return;
   int v = elm_radio_value_get(data);
   if (v == 1)
     elm_genlist_item_decorate_mode_set(event_info, mode_type[v], EINA_TRUE);
}

static void
_my_gl_mode_right(void *data, Evas_Object *obj EINA_UNUSED, void *event_info)
{
   if (!data) return;
   int v = elm_radio_value_get(data);
   if (v == 0)
     elm_genlist_item_decorate_mode_set(event_info, mode_type[v], EINA_TRUE);
}

static void
_my_gl_mode_left(void *data, Evas_Object *obj EINA_UNUSED, void *event_info)
{
   if (!data) return;
   int v = elm_radio_value_get(data);
   if (v == 0)
     elm_genlist_item_decorate_mode_set(event_info, mode_type[v], EINA_FALSE);
}

static void
_my_gl_mode_cancel(void *data, Evas_Object *obj, void *event_info EINA_UNUSED)
{
   fprintf(stderr, "drag\n");
   if (!data) return;
   int v = elm_radio_value_get(data);
   Elm_Object_Item *glit = elm_genlist_decorated_item_get(obj);
   if (glit) elm_genlist_item_decorate_mode_set(glit, mode_type[v], EINA_FALSE);
}

void
test_genlist10(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Evas_Object *win, *fr, *bx, *bx2, *rd, *rdg, *gl;
   int i;

   api_data *api = calloc(1, sizeof(api_data));
   win = elm_win_util_standard_add("genlist-decorate-item-mode", "Genlist Decorate Item Mode");
   elm_win_autodel_set(win, EINA_TRUE);
   evas_object_event_callback_add(win, EVAS_CALLBACK_FREE, _cleanup_cb, api);

   bx = elm_box_add(win);
   evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, bx);
   evas_object_show(bx);

   fr = elm_frame_add(win);
   elm_object_text_set(fr, "Decorate Item Mode Type");
   elm_box_pack_end(bx, fr);
   evas_object_show(fr);

   bx2 = elm_box_add(win);
   elm_object_content_set(fr, bx2);
   evas_object_show(bx2);

   rd = elm_radio_add(win);
   evas_object_size_hint_weight_set(rd, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_radio_state_value_set(rd, 0);
   elm_object_text_set(rd, "Slide : Sweep genlist items to the right.");
   evas_object_show(rd);
   elm_box_pack_end(bx2, rd);
   rdg = rd;

   rd = elm_radio_add(win);
   evas_object_size_hint_weight_set(rd, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_radio_state_value_set(rd, 1);
   elm_object_text_set(rd, "Rotate : Click each item.");
   elm_radio_group_add(rd, rdg);
   evas_object_show(rd);
   elm_box_pack_end(bx2, rd);

   gl = elm_genlist_add(win);
   evas_object_size_hint_align_set(gl, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(gl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_smart_callback_add(gl, "drag,start,right", _my_gl_mode_right, rdg);
   evas_object_smart_callback_add(gl, "drag,start,left", _my_gl_mode_left, rdg);
   evas_object_smart_callback_add(gl, "drag,start,up", _my_gl_mode_cancel, rdg);
   evas_object_smart_callback_add(gl, "drag,start,down", _my_gl_mode_cancel, rdg);
   api->gl = gl;
   evas_object_show(gl);

   api->itc1 = elm_genlist_item_class_new();
   api->itc1->item_style = "default";
   api->itc1->decorate_item_style = "mode";
   api->itc1->func.text_get = gl10_text_get;
   api->itc1->func.content_get = gl10_content_get;
   api->itc1->func.state_get = gl_state_get;
   api->itc1->func.del = NULL;

   for (i = 0; i < 50; i++)
     elm_genlist_item_append(gl,
                             api->itc1,
                             (void *)(uintptr_t)(1000 + i)/* item data */,
                             NULL/* parent */,
                             ELM_GENLIST_ITEM_NONE/* flags */,
                             _gl_sel10/* func */,
                             rdg/* func data */);

   elm_box_pack_end(bx, gl);

   elm_genlist_item_class_free(api->itc1);
   evas_object_resize(win, 520, 520);
   evas_object_show(win);
}

/*************/

static void
_reorder_tg_changed_cb(void *data, Evas_Object *obj, void *event_info EINA_UNUSED)
{
   elm_genlist_reorder_mode_set(data, elm_check_state_get(obj));
}

/**
 * gl_moved is called after an item was reordered.
 * This is only called when reorder mode is enabled.
 *
 * @param obj          :  the genlist object.
 * @param event_info   :  the moved item.
 *
 * the item(event_info) had been moved
 *
 */
static void
_gl_reorder_moved_cb(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED,
                     void *event_info EINA_UNUSED)
{
   printf("\"moved\" it: %p\n", event_info);
}

/**
 * _gl_reorder_moved_after_cb is called after an item was reordered.
 * This is only called when reorder mode is enabled.
 *
 * @param obj          :  the genlist object.
 * @param event_info   :  the moved item.
 *
 *  the item(event_info) had been moved after the given relative item(*rel_item) in list.
 *
 */
static void
_gl_reorder_moved_after_cb(void *data EINA_UNUSED,
                           Evas_Object *obj EINA_UNUSED, void *event_info)
{
   // if needed, add application logic.
   Elm_Object_Item *it = elm_genlist_item_prev_get((Elm_Object_Item *)event_info);
   printf("it = %p, prev_it = %p\n", event_info, it);
}

/**
 * _gl_reorder_moved_before_cb is called after an item was reordered.
 * This is only called when reorder mode is enabled.
 *
 * @param obj          :  the genlist object.
 * @param event_info   :  the moved item.
 *
 *  the item(event_info) had been moved before the given relative item(*rel_item) in list.
 *
 */
static void
_gl_reorder_moved_before_cb(void *data EINA_UNUSED,
                            Evas_Object *obj EINA_UNUSED, void *event_info)
{
   // if needed, add application logic.
   Elm_Object_Item *it = elm_genlist_item_next_get((Elm_Object_Item *)event_info);
   printf("it = %p, next_it = %p\n", event_info, it);
}

static void
_gl_reorder_item_focused_cb(void *data EINA_UNUSED,
                            Evas_Object *obj EINA_UNUSED, void *event_info)
{
   printf("\"item,focused\" it: %p\n", event_info);
}

static void
_gl_reorder_item_unfocused_cb(void *data EINA_UNUSED,
                              Evas_Object *obj EINA_UNUSED, void *event_info)
{
   printf("\"item,unfocused\" it: %p\n", event_info);
}

static void
_gl_reorder_item_selected_cb(void *data EINA_UNUSED,
                             Evas_Object *obj EINA_UNUSED, void *event_info)
{
   printf("\"selected\" it: %p\n", event_info);
}

static void
_gl_reorder_item_unselected_cb(void *data EINA_UNUSED,
                               Evas_Object *obj EINA_UNUSED, void *event_info)
{
   printf("\"unselected\" it: %p\n", event_info);
}

void
test_genlist_reorder(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED,
                     void *event_info EINA_UNUSED)
{
   Evas_Object *win, *fr, *lb, *bx, *tg, *gl;
   int i;

   api_data *api = calloc(1, sizeof(api_data));
   win = elm_win_util_standard_add("genlist-reorder-mode", "Genlist Reorder Mode");
   elm_win_autodel_set(win, EINA_TRUE);
   evas_object_event_callback_add(win, EVAS_CALLBACK_FREE, _cleanup_cb, api);

   bx = elm_box_add(win);
   evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, bx);
   evas_object_show(bx);

   fr = elm_frame_add(win);

   elm_object_text_set(fr, "Reorder Mode");
   elm_box_pack_end(bx, fr);
   evas_object_show(fr);

   lb = elm_label_add(win);
   elm_object_text_set(lb,
                       "Enable reorder mode if you want to move item.<br/>"
                       "Then long press and drag item.");
   elm_object_content_set(fr, lb);
   evas_object_show(lb);

   gl = elm_genlist_add(win);
   evas_object_size_hint_align_set(gl, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(gl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   api->gl = gl;
   evas_object_show(gl);

   tg = elm_check_add(win);
   elm_object_style_set(tg, "toggle");
   elm_object_text_set(tg, "Reorder Mode:");
   elm_check_state_set(tg, elm_config_mirrored_get());
   evas_object_smart_callback_add(tg, "changed", _reorder_tg_changed_cb, gl);
   elm_box_pack_end(bx, tg);
   evas_object_show(tg);

   api->itc1 = elm_genlist_item_class_new();
   api->itc1->item_style = "default";
   api->itc1->func.text_get = gl_text_get;
   api->itc1->func.content_get = gl_content_get;
   api->itc1->func.state_get = gl_state_get;
   api->itc1->func.del = NULL;
   evas_object_smart_callback_add(gl, "moved", _gl_reorder_moved_cb, NULL);
   evas_object_smart_callback_add(gl, "moved,after", _gl_reorder_moved_after_cb, NULL);
   evas_object_smart_callback_add(gl, "moved,before", _gl_reorder_moved_before_cb, NULL);
   evas_object_smart_callback_add(gl, "item,focused", _gl_reorder_item_focused_cb, NULL);
   evas_object_smart_callback_add(gl, "item,unfocused", _gl_reorder_item_unfocused_cb, NULL);
   evas_object_smart_callback_add(gl, "selected", _gl_reorder_item_selected_cb, NULL);
   evas_object_smart_callback_add(gl, "unselected", _gl_reorder_item_unselected_cb, NULL);

   for (i = 0; i < 50; i++)
     elm_genlist_item_append(gl,
                             api->itc1,
                             (void *)(uintptr_t)(1 + i)/* item data */,
                             NULL/* parent */,
                             ELM_GENLIST_ITEM_NONE/* flags */,
                             NULL/* func */,
                             NULL/* func data */);

   elm_genlist_item_class_free(api->itc1);

   elm_box_pack_end(bx, gl);

   evas_object_resize(win, 400, 500);
   evas_object_show(win);
}

/*************/

char *gl12_text_get(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, const char *part EINA_UNUSED)
{
   return strdup("Enlightenment is not just a window manager for Linux/X11 and others, but also a whole suite of libraries to help you create beautiful user interfaces with much less work than doing it the old fashioned way and fighting with traditional toolkits, not to mention a traditional window manager. It covers uses from small mobile devices like phones all the way to powerful multi-core desktops (which are the primary development environment).");
}

void
test_genlist12(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Evas_Object *win, *bx, *gl;
   int i;
   api_data *api = calloc(1, sizeof(api_data));

   win = elm_win_util_standard_add("genlist-textblock", "Genlist Textblock");
   elm_win_autodel_set(win, EINA_TRUE);
   evas_object_event_callback_add(win, EVAS_CALLBACK_FREE, _cleanup_cb, api);

   bx = elm_box_add(win);
   evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, bx);
   evas_object_show(bx);

   gl = elm_genlist_add(win);
   elm_genlist_mode_set(gl, ELM_LIST_COMPRESS);
   evas_object_size_hint_weight_set(gl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(gl, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(bx, gl);
   api->gl = gl;
   evas_object_show(gl);

   api->itc1 = elm_genlist_item_class_new();
   api->itc1->item_style = "message";
   api->itc1->func.text_get = gl12_text_get;
   api->itc1->func.state_get = gl_state_get;
   api->itc1->func.del = NULL;

   for (i = 0; i < 1000; i++)
     {
        elm_genlist_item_append(gl, api->itc1,
                                (void *)(uintptr_t)i/* item data */,
                                NULL/* parent */,
                                ELM_GENLIST_ITEM_NONE,
                                gl_sel/* func */,
                                (void *)(uintptr_t)(i * 10)/* func data */);
     }
   elm_genlist_item_class_free(api->itc1);

   evas_object_resize(win, 400, 500);
   evas_object_show(win);
}

/*************/

static int
gl13_cmp(const void *pa, const void *pb)
{
   const Elm_Object_Item *ia = pa, *ib = pb;
   int a = (int)(uintptr_t) elm_object_item_data_get(ia);
   int b = (int)(uintptr_t) elm_object_item_data_get(ib);
   return a - b;
}

void
test_genlist13(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Elm_Object_Item *pi[6];
   Evas_Object *win, *bx, *gl; int i, base, idx[3] = {1, 10, 15};

   api_data *api = calloc(1, sizeof(api_data));
   win = elm_win_util_standard_add("genlist-tree-insert-sorted", "Genlist Tree, Insert Sorted");
   elm_win_autodel_set(win, EINA_TRUE);
   evas_object_event_callback_add(win, EVAS_CALLBACK_FREE, _cleanup_cb, api);

   bx = elm_box_add(win);
   evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, bx);
   evas_object_show(bx);

   gl = elm_genlist_add(win);
   evas_object_size_hint_align_set(gl, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(gl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_show(gl);

   api->itc2 = elm_genlist_item_class_new();
   api->itc2->item_style = "default";
   api->itc2->func.text_get = gl4_text_get;
   api->itc2->func.content_get = NULL;
   api->itc2->func.state_get = NULL;
   api->itc2->func.del = NULL;

   /* mixed order to test insert sorted */

   for (i = 0; i < 3; i++)
     {
        pi[i] = elm_genlist_item_sorted_insert
          (gl, api->itc2, (void *)(uintptr_t)idx[i]/* item data */, NULL/* parent */,
           ELM_GENLIST_ITEM_TREE, gl13_cmp/* cmp */,
           NULL/* func */, NULL/* func data */);
     }

   for (i = 0, base = 100; i < 3; i++, base += 100)
     {
        int j;
        for (j = 0; j < 3; j++)
          {
             elm_genlist_item_sorted_insert
               (gl, api->itc2, (void *)(uintptr_t)(idx[j] + base)/* item data */,
                pi[i]/* parent */, ELM_GENLIST_ITEM_NONE,
                gl13_cmp/* cmp */, NULL/* func */, NULL/* func data */);
          }
     }

   for (i = 0; i < 3; i++)
     {
        pi[i + 3] = elm_genlist_item_sorted_insert
          (gl, api->itc2, (void *)(uintptr_t)(idx[i] * 2)/* item data */, NULL/* parent */,
           ELM_GENLIST_ITEM_TREE, gl13_cmp/* cmp */, NULL/* func */,
           NULL/* func data */);
     }


   for (i = 0, base = 10000; i < 3; i++, base += 10000)
     {
        int j;
        for (j = 0; j < 3; j++)
          {
             elm_genlist_item_sorted_insert
               (gl, api->itc2, (void *)(uintptr_t)(idx[j] + base)/* item data */,
                pi[i + 3]/* parent */, ELM_GENLIST_ITEM_NONE,
                gl13_cmp/* cmp */, NULL/* func */, NULL/* func data */);
          }
     }
   elm_genlist_item_class_free(api->itc2);
   elm_box_pack_end(bx, gl);
   evas_object_show(bx);

   evas_object_resize(win, 320, 320);
   evas_object_show(win);
}

/*************/

static void
my_gl_insert_before_rel(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   api_data *api = data;
   Evas_Object *gl = api->gl;
   static int i = 1000;
   Elm_Object_Item *gli_selected;

   if (!api->itc1) api->itc1 = elm_genlist_item_class_new();
   api->itc1->item_style = "default";
   api->itc1->func.text_get = gl_text_get;
   api->itc1->func.content_get = NULL;
   api->itc1->func.state_get = NULL;
   api->itc1->func.del = NULL;

   gli_selected = elm_genlist_selected_item_get(gl);
   if (!gli_selected)
     {
        printf("no item selected\n");
        return;
     }

   elm_genlist_item_insert_before(gl, api->itc1,
                                  (void *)(uintptr_t)i/* item data */,
                                  elm_genlist_item_parent_get(gli_selected),
                                  gli_selected/* item before */,
                                  ELM_GENLIST_ITEM_NONE,
                                  NULL/* func */, NULL/* func data */);
   i++;
}

static void
my_gl_insert_after_rel(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   api_data *api = data;
   Evas_Object *gl = api->gl;
   static int i = 0;
   Elm_Object_Item *gli_selected;

   if (!api->itc1) api->itc1 = elm_genlist_item_class_new();
   api->itc1->item_style = "default";
   api->itc1->func.text_get = gl_text_get;
   api->itc1->func.content_get = NULL;
   api->itc1->func.state_get = NULL;
   api->itc1->func.del = NULL;

   gli_selected = elm_genlist_selected_item_get(gl);
   if (!gli_selected)
     {
        printf("no item selected\n");
        return;
     }

   elm_genlist_item_insert_after(gl, api->itc1,
                                  (void *)(uintptr_t)i/* item data */,
                                  elm_genlist_item_parent_get(gli_selected),
                                  gli_selected/* item after */,
                                  ELM_GENLIST_ITEM_NONE,
                                  NULL/* func */, NULL/* func data */);
   i++;
}

void
test_genlist14(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Elm_Object_Item *pi[6];
   Evas_Object *win, *bx, *bx2, *bt, *gl;
   int i, base;
   /* index: 0,  1,  2,  3,  4,  5
    * items: 1, 15, 11,  2, 33, 21
    * final: 1,  2, 11, 15, 21, 33
    */
   const int idx[6] = {1, 15, 11, 2, 33, 21};
   const int relative[6] = {
      0, /* item  '1' -  not used */
      0, /* item '15' - insert after pi[0], item '1' */
     -1, /* item '11' - insert before pi[1], item '15' */
     -2, /* item  '2' - insert before pi[2], item '11' */
      1, /* item '33' - insert after pi[1], item '15' */
     -4  /* item '21' - insert before pi[4], item '33' */
   };

   api_data *api = calloc(1, sizeof(api_data));
   win = elm_win_util_standard_add("genlist-tree-insert-relative", "Genlist Tree, Insert Relative");
   elm_win_autodel_set(win, EINA_TRUE);
   evas_object_event_callback_add(win, EVAS_CALLBACK_FREE, _cleanup_cb, api);

   bx = elm_box_add(win);
   evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, bx);
   evas_object_show(bx);

   gl = elm_genlist_add(win);
   evas_object_size_hint_align_set(gl, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(gl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   api->gl = gl;
   evas_object_show(gl);

   api->itc2 = elm_genlist_item_class_new();
   api->itc2->item_style = "default";
   api->itc2->func.text_get = gl4_text_get;
   api->itc2->func.content_get = NULL;
   api->itc2->func.state_get = NULL;
   api->itc2->func.del = NULL;

   /* mixed order to test insert sorted */

   // BUG1: should be able to insert before=NULL, prepend
   // BUG2: should be able to insert after=NULL, append

   pi[0] = elm_genlist_item_append
     (gl, api->itc2, (void *)(uintptr_t)idx[0]/* item data */,
      NULL/* parent */,
      ELM_GENLIST_ITEM_TREE, NULL/* func */, NULL/* func data */);

   for (i = 1; i < 3; i++)
     {
        if (relative[i] < 0)
          pi[i] = elm_genlist_item_insert_before
            (gl, api->itc2, (void *)(uintptr_t)idx[i]/* item data */,
             NULL/* parent */, pi[-relative[i]],
             ELM_GENLIST_ITEM_TREE, NULL/* func */, NULL/* func data */);
        else
          pi[i] = elm_genlist_item_insert_after
            (gl, api->itc2, (void *)(uintptr_t)idx[i]/* item data */,
             NULL/* parent */, pi[relative[i]],
             ELM_GENLIST_ITEM_TREE, NULL/* func */, NULL/* func data */);
     }

   for (i = 0; i < 3; i++)
     {
        Elm_Object_Item *sub_glit[6];
        int j;

        base = 1000 * (int)(uintptr_t) elm_object_item_data_get(pi[i]);

        sub_glit[0] = elm_genlist_item_append
          (gl, api->itc2, (void *)(uintptr_t) (idx[0] + base)/* item data */, pi[i]/* parent */,
           ELM_GENLIST_ITEM_TREE, NULL/* func */, NULL/* func data */);

        for (j = 1; j < 6; j++) {
           if (relative[j] < 0)
             sub_glit[j] = elm_genlist_item_insert_before
               (gl, api->itc2, (void *)(uintptr_t) (idx[j] + base)/* item data */,
                pi[i]/* parent */, sub_glit[-relative[j]],
                ELM_GENLIST_ITEM_TREE, NULL/* func */, NULL/* func data */);
           else
             sub_glit[j] = elm_genlist_item_insert_after
               (gl, api->itc2, (void *)(uintptr_t) (idx[j] + base)/* item data */,
                pi[i]/* parent */, sub_glit[relative[j]],
                ELM_GENLIST_ITEM_TREE, NULL/* func */, NULL/* func data */);
        }
     }

   for (i = 3; i < 6; i++)
     {
        if (relative[i] < 0)
          pi[i] = elm_genlist_item_insert_before
            (gl, api->itc2, (void *)(uintptr_t) idx[i]/* item data */,
             NULL/* parent */, pi[-relative[i]],
             ELM_GENLIST_ITEM_TREE, NULL/* func */, NULL/* func data */);
        else
          pi[i] = elm_genlist_item_insert_after
            (gl, api->itc2, (void *)(uintptr_t) idx[i]/* item data */,
             NULL/* parent */, pi[relative[i]],
             ELM_GENLIST_ITEM_TREE, NULL/* func */, NULL/* func data */);
     }

   for (i = 3; i < 6; i++)
     {
        Elm_Object_Item *sub_glit[6];
        int j;

        base = 1000 * (int)(uintptr_t) elm_object_item_data_get(pi[i]);

        sub_glit[0] = elm_genlist_item_append
          (gl, api->itc2, (void *)(uintptr_t) (idx[0] + base)/* item data */, pi[i]/* parent */,
           ELM_GENLIST_ITEM_TREE, NULL/* func */, NULL/* func data */);

        for (j = 1; j < 6; j++) {
           if (relative[j] < 0)
             sub_glit[j] = elm_genlist_item_insert_before
               (gl, api->itc2, (void *)(uintptr_t) (idx[j] + base)/* item data */,
                pi[i]/* parent */, sub_glit[-relative[j]],
                ELM_GENLIST_ITEM_TREE, NULL/* func */, NULL/* func data */);
           else
             sub_glit[j] = elm_genlist_item_insert_after
               (gl, api->itc2, (void *)(uintptr_t) (idx[j] + base)/* item data */,
                pi[i]/* parent */, sub_glit[relative[j]],
                ELM_GENLIST_ITEM_TREE, NULL/* func */, NULL/* func data */);
        }
     }

   elm_box_pack_end(bx, gl);
   evas_object_show(bx);

   bx2 = elm_box_add(win);
   elm_box_horizontal_set(bx2, EINA_TRUE);
   elm_box_homogeneous_set(bx2, EINA_TRUE);
   evas_object_size_hint_weight_set(bx2, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(bx2, EVAS_HINT_FILL, EVAS_HINT_FILL);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "+ before");
   evas_object_smart_callback_add(bt, "clicked", my_gl_insert_before_rel, api);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "+ after");
   evas_object_smart_callback_add(bt, "clicked", my_gl_insert_after_rel, api);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_show(bt);

   elm_box_pack_end(bx, bx2);
   evas_object_show(bx2);

   /* item_class_ref is needed for itc2. some items can be added in callbacks */
   elm_genlist_item_class_ref(api->itc2);
   elm_genlist_item_class_free(api->itc2);

   evas_object_resize(win, 320, 320);
   evas_object_show(win);
}

/*************/

static void _edit_icon_clicked_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Elm_Object_Item *item = (Elm_Object_Item *)data;
   elm_object_item_del(item);
}

char *gl15_text_get(void *data, Evas_Object *obj EINA_UNUSED, const char *part EINA_UNUSED)
{
   const Testitem *tit = data;
   char buf[256];
   snprintf(buf, sizeof(buf), "Item #%i", tit->mode);
   return strdup(buf);
}

Evas_Object *gl15_content_get(void *data, Evas_Object *obj, const char *part)
{
   Testitem *tit = data;
   char buf[PATH_MAX];

   // "edit" EDC layout is like below. each part is swallow part.
   // the existing item is swllowed to elm.swallow.edit.content part.
   // --------------------------------------------------------------------
   // | elm.edit.icon.1 | elm.swallow.decorate.content | elm.edit.icon,2 |
   // --------------------------------------------------------------------

   if (!strcmp(part, "elm.swallow.end"))
     {
        Evas_Object *ic = elm_icon_add(obj);
        snprintf(buf, sizeof(buf), "%s/images/bubble.png", elm_app_data_dir_get());
        elm_image_file_set(ic, buf, NULL);
        evas_object_size_hint_aspect_set(ic, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
        return ic;
     }
   else if (!strcmp(part, "elm.edit.icon.1"))
     {
        Evas_Object *ck;
        ck = elm_check_add(obj);
        elm_check_state_pointer_set(ck, &tit->checked);
        evas_object_propagate_events_set(ck, EINA_FALSE);
        evas_object_show(ck);
        return ck;
     }
   else if (!strcmp(part, "elm.edit.icon.2"))
     {
        Evas_Object *icn = elm_icon_add(obj);
        snprintf(buf, sizeof(buf), "%s/images/icon_06.png", elm_app_data_dir_get());
        elm_image_file_set(icn, buf, NULL);
        evas_object_propagate_events_set(icn, EINA_FALSE);
        evas_object_size_hint_aspect_set(icn, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
        evas_object_smart_callback_add(icn, "clicked", _edit_icon_clicked_cb, (void *)tit->item);
        return icn;
     }
   else return NULL;
}

static void
gl15_sel(void *data, Evas_Object *obj, void *event_info EINA_UNUSED)
{
   Testitem *tit = data;
   if (elm_genlist_decorate_mode_get(obj))
     {
        if (!tit->checked) tit->checked = EINA_TRUE;
        else tit->checked = EINA_FALSE;
     }
   elm_genlist_item_update(tit->item);
}

static void
gl15_deco_all_mode(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   elm_genlist_decorate_mode_set(data, EINA_TRUE);
   elm_genlist_select_mode_set(data, ELM_OBJECT_SELECT_MODE_ALWAYS);
}

static void
gl15_normal_mode(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   elm_genlist_decorate_mode_set(data, EINA_FALSE);
   elm_genlist_select_mode_set(data, ELM_OBJECT_SELECT_MODE_DEFAULT);
}

void gl15_del(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED)
{
   Testitem *ti = data;
   printf("item deleted. (# %d)\n", ti->mode);
}

void
test_genlist15(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Evas_Object *win, *bx, *bx2, *bt, *gl;
   int i;
   static Testitem tit[100];

   api_data *api = calloc(1, sizeof(api_data));
   win = elm_win_util_standard_add("genlist-decorate-all-mode", "Genlist Decorate All Mode");
   elm_win_autodel_set(win, EINA_TRUE);
   evas_object_event_callback_add(win, EVAS_CALLBACK_FREE, _cleanup_cb, api);

   bx = elm_box_add(win);
   evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, bx);
   evas_object_show(bx);

   gl = elm_genlist_add(win);
   evas_object_size_hint_align_set(gl, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(gl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   api->gl = gl;
   evas_object_show(gl);

   api->itc1 = elm_genlist_item_class_new();
   api->itc1->item_style = "default";
   api->itc1->func.text_get = gl15_text_get;
   api->itc1->func.content_get = gl15_content_get;
   api->itc1->func.state_get = gl_state_get;
   api->itc1->func.del = gl15_del;
   api->itc1->decorate_all_item_style = "edit";

   for (i = 0; i < 100; i++)
     {
        tit[i].mode = i;
        tit[i].item = elm_genlist_item_append(gl, api->itc1,
                                              &(tit[i])/* item data */,
                                              NULL/* parent */,
                                              ELM_GENLIST_ITEM_NONE/* flags */,
                                              gl15_sel/* func */,
                                              (void *)(uintptr_t)&(tit[i])/* func data */);
     }
   elm_genlist_item_class_free(api->itc1);
   elm_box_pack_end(bx, gl);
   evas_object_show(bx);

   bx2 = elm_box_add(win);
   elm_box_horizontal_set(bx2, EINA_TRUE);
   elm_box_homogeneous_set(bx2, EINA_TRUE);
   evas_object_size_hint_weight_set(bx2, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(bx2, EVAS_HINT_FILL, EVAS_HINT_FILL);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Decorate All mode");
   evas_object_smart_callback_add(bt, "clicked", gl15_deco_all_mode, gl);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Normal mode");
   evas_object_smart_callback_add(bt, "clicked", gl15_normal_mode,gl);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_show(bt);

   elm_box_pack_end(bx, bx2);
   evas_object_show(bx2);

   evas_object_resize(win, 520, 520);
   evas_object_show(win);
}

/*************/

static void _flip_icon_clicked_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   const Testitem *tit = data;

   if (elm_genlist_item_flip_get(tit->item))
     elm_genlist_item_flip_set(tit->item, EINA_FALSE);
   else
     elm_genlist_item_flip_set(tit->item, EINA_TRUE);
}

char *gl16_text_get(void *data, Evas_Object *obj EINA_UNUSED, const char *part EINA_UNUSED)
{
   const Testitem *tit = data;
   char buf[256];
   snprintf(buf, sizeof(buf), "Item #%i", tit->mode);
   return strdup(buf);
}

Evas_Object *gl16_content_get(void *data, Evas_Object *obj, const char *part)
{
   Testitem *tit = data;
   char buf[PATH_MAX];

   if (!strcmp(part, "elm.text.flip"))
     {
        Evas_Object *btn = elm_button_add(obj);
        elm_object_text_set(btn, "flipped content placement");
        evas_object_size_hint_align_set(btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
        evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, 0.0);
        evas_object_smart_callback_add(btn, "clicked", _flip_icon_clicked_cb, (void *)tit);
        evas_object_show(btn);
        return btn;
     }
   else if (!strcmp(part, "elm.edit.icon.1"))
     {
        Evas_Object *icn = elm_icon_add(obj);
        snprintf(buf, sizeof(buf), "%s/images/icon_04.png", elm_app_data_dir_get());
        elm_image_file_set(icn, buf, NULL);
        evas_object_propagate_events_set(icn, EINA_FALSE);
        evas_object_size_hint_aspect_set(icn, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
        return icn;
     }
   else if (!strcmp(part, "elm.edit.icon.2"))
     {
        Evas_Object *icn = elm_icon_add(obj);
        snprintf(buf, sizeof(buf), "%s/images/icon_09.png", elm_app_data_dir_get());
        elm_image_file_set(icn, buf, NULL);
        evas_object_propagate_events_set(icn, EINA_FALSE);
        evas_object_size_hint_aspect_set(icn, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
        evas_object_smart_callback_add(icn, "clicked", _flip_icon_clicked_cb, (void *)tit);
        return icn;
     }
   else return NULL;
}

void
test_genlist16(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Evas_Object *win, *bx, *gl;
   int i;
   static Testitem tit[100];

   api_data *api = calloc(1, sizeof(api_data));
   win = elm_win_util_standard_add("genlist-flip-mode", "Genlist Flip Mode");
   elm_win_autodel_set(win, EINA_TRUE);
   evas_object_event_callback_add(win, EVAS_CALLBACK_FREE, _cleanup_cb, api);

   bx = elm_box_add(win);
   evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, bx);
   evas_object_show(bx);

   gl = elm_genlist_add(win);
   evas_object_size_hint_align_set(gl, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(gl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   api->gl = gl;
   evas_object_show(gl);

   /* note: flip mode can be used with/without edit mode */
   elm_genlist_decorate_mode_set(gl, EINA_TRUE);
   elm_genlist_select_mode_set(gl, ELM_OBJECT_SELECT_MODE_ALWAYS);

   api->itc1 = elm_genlist_item_class_new();
   api->itc1->item_style = "default";
   api->itc1->func.text_get = gl16_text_get;
   api->itc1->func.content_get = gl16_content_get;
   api->itc1->func.state_get = gl_state_get;
   api->itc1->func.del = NULL;
   api->itc1->decorate_all_item_style = "edit";

   for (i = 0; i < 100; i++)
     {
        tit[i].mode = i;
        tit[i].item = elm_genlist_item_append(gl, api->itc1,
                                              &(tit[i])/* item data */,
                                              NULL/* parent */,
                                              ELM_GENLIST_ITEM_NONE/* flags */,
                                              gl_sel/* func */,
                                              (void *)(uintptr_t)&(tit[i])/* func data */);
     }
   elm_genlist_item_class_free(api->itc1);
   elm_box_pack_end(bx, gl);
   evas_object_show(bx);

   evas_object_resize(win, 520, 520);
   evas_object_show(win);
}

/*************/

char *
gl17_text_get(void *data, Evas_Object *obj EINA_UNUSED, const char *part)
{
   const Testitem *tit = data;
   char buf[256];
   if (!strcmp(part, "elm.text.mode"))
     snprintf(buf, sizeof(buf), "Mode # %i", tit->mode);
   else
     snprintf(buf, sizeof(buf), "Item # %i", (int)(uintptr_t)data);
   return strdup(buf);
}

Evas_Object *
_decorate_item_mode_frame_new(Evas_Object *win, Evas_Object **rdg)
{
   Evas_Object *fr, *bx, *rd;

   fr = elm_frame_add(win);
   evas_object_size_hint_weight_set(fr, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(fr, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_object_text_set(fr, "Decorate Item Mode Type");
   evas_object_show(fr);

   bx = elm_box_add(win);
   elm_object_content_set(fr, bx);
   evas_object_show(bx);

   rd = elm_radio_add(win);
   evas_object_size_hint_weight_set(rd, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_radio_state_value_set(rd, 0);
   elm_object_text_set(rd, "Slide : Sweep genlist items to the right.");
   evas_object_show(rd);
   elm_box_pack_end(bx, rd);
   *rdg = rd;

   rd = elm_radio_add(win);
   evas_object_size_hint_weight_set(rd, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_radio_state_value_set(rd, 1);
   elm_object_text_set(rd, "Rotate : Click each item.");
   elm_radio_group_add(rd, *rdg);
   evas_object_show(rd);
   elm_box_pack_end(bx, rd);

   return fr;
}

void
_decorate_all_set_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info EINA_UNUSED)
{
   if (!data) return;

   Evas_Object *gl;
   gl = evas_object_data_get(obj, "gl");
   if (!gl) return;

   if (evas_object_data_get(gl, "tree_effect"))
     elm_genlist_tree_effect_enabled_set(gl, EINA_FALSE);
   elm_genlist_decorate_mode_set(gl, EINA_TRUE);
}

void
_decorate_all_unset_btn_clicked_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   if (evas_object_data_get(data, "tree_effect"))
     elm_genlist_tree_effect_enabled_set(data, EINA_TRUE);
   elm_genlist_decorate_mode_set(data, EINA_FALSE);
}

Evas_Object *
_decorate_all_mode_frame_new(Evas_Object *win, Evas_Object *rdg, Evas_Object *gl)
{
   Evas_Object *fr, *bx, *btn;

   fr = elm_frame_add(win);
   evas_object_size_hint_weight_set(fr, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(fr, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_object_text_set(fr, "Decorate All Mode Type");
   evas_object_show(fr);

   bx = elm_box_add(win);
   elm_object_content_set(fr, bx);
   evas_object_show(bx);

   btn = elm_button_add(win);
   evas_object_data_set(btn, "gl", gl);
   elm_object_text_set(btn, "Set Decorate All Mode");
   evas_object_smart_callback_add(btn, "clicked", _decorate_all_set_btn_clicked_cb, rdg);
   elm_box_pack_end(bx, btn);
   evas_object_show(btn);

   btn = elm_button_add(win);
   elm_object_text_set(btn, "Unset Decorate All Mode");
   evas_object_smart_callback_add(btn, "clicked", _decorate_all_unset_btn_clicked_cb, gl);
   elm_box_pack_end(bx, btn);
   evas_object_show(btn);

   return fr;
}

void
test_genlist17(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Evas_Object *win, *fr1, *fr2, *bx, *bx2, *rdg = NULL, *gl;
   int i;
   static Testitem tit[50];

   api_data *api = calloc(1, sizeof(api_data));
   win = elm_win_util_standard_add("genlist-decorate-modes", "Genlist Decorate Modes");
   elm_win_autodel_set(win, EINA_TRUE);
   evas_object_event_callback_add(win, EVAS_CALLBACK_FREE, _cleanup_cb, api);

   bx = elm_box_add(win);
   evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, bx);
   evas_object_show(bx);

   bx2 = elm_box_add(win);
   evas_object_size_hint_align_set(bx2, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_horizontal_set(bx2, EINA_TRUE);
   elm_box_pack_end(bx, bx2);
   evas_object_show(bx2);

   fr1 = _decorate_item_mode_frame_new(win, &rdg);
   elm_box_pack_end(bx2, fr1);

   gl = elm_genlist_add(win);
   evas_object_size_hint_align_set(gl, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(gl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_smart_callback_add(gl, "drag,start,right", _my_gl_mode_right, rdg);
   evas_object_smart_callback_add(gl, "drag,start,left", _my_gl_mode_left, rdg);
   evas_object_smart_callback_add(gl, "drag,start,up", _my_gl_mode_cancel, rdg);
   evas_object_smart_callback_add(gl, "drag,start,down", _my_gl_mode_cancel, rdg);
   api->gl = gl;
   evas_object_show(gl);

   api->itc1 = elm_genlist_item_class_new();
   api->itc1->item_style = "default";
   api->itc1->decorate_item_style = "mode";
   api->itc1->func.text_get = gl15_text_get;
   api->itc1->func.content_get = gl15_content_get;
   api->itc1->func.state_get = gl_state_get;
   api->itc1->func.del = NULL;
   api->itc1->decorate_all_item_style = "edit";

   for (i = 0; i < 50; i++)
     {
        tit[i].checked = EINA_FALSE;
        tit[i].mode = i;
        tit[i].item = elm_genlist_item_append(gl,
                                              api->itc1,
                                              &(tit[i])/* item data */,
                                              NULL/* parent */,
                                              ELM_GENLIST_ITEM_NONE/* flags */,
                                              NULL/* select func */,
                                              NULL/* func data */);
     }

   elm_genlist_item_class_free(api->itc1);
   elm_box_pack_end(bx, gl);

   fr2 = _decorate_all_mode_frame_new(win, rdg, gl);
   elm_box_pack_end(bx2, fr2);

   evas_object_resize(win, 520, 520);
   evas_object_show(win);
}

/*************/
Evas_Object *
_tree_effect_frame_new(Evas_Object *win, Evas_Object **rdg, Evas_Object *gl)
{
   Evas_Object *fr, *bx, *rd;

   fr = elm_frame_add(win);
   elm_object_text_set(fr, "Genlist Tree Effect");
   evas_object_size_hint_weight_set(fr, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(fr, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_show(fr);

   bx = elm_box_add(win);
   elm_box_homogeneous_set(bx, EINA_TRUE);
   evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(bx, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_object_content_set(fr, bx);
   evas_object_show(bx);

   rd = elm_radio_add(win);
   elm_radio_state_value_set(rd, 0);
   elm_object_text_set(rd, "Enable");
   evas_object_smart_callback_add(rd, "changed", _tree_effect_enable_cb, gl);
   evas_object_show(rd);
   elm_box_pack_end(bx, rd);
   *rdg = rd;

   rd = elm_radio_add(win);
   elm_radio_state_value_set(rd, 1);
   elm_radio_group_add(rd, *rdg);
   elm_object_text_set(rd, "Disable");
   evas_object_smart_callback_add(rd, "changed", _tree_effect_disable_cb, gl);
   evas_object_show(rd);
   elm_box_pack_end(bx, rd);


   return fr;
}

static void
gl18_sel(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info)
{
   Elm_Object_Item *glit = event_info;
   int depth = elm_genlist_item_expanded_depth_get(glit);
   printf("expanded depth for selected item is %d\n", depth);
}

static void
gl18_del(void *data, Evas_Object *obj EINA_UNUSED)
{
   free(data);
}

static void
gl18_exp(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info)
{
   api_data *api = data;
   Elm_Object_Item *glit = event_info;
   Evas_Object *gl = elm_object_item_widget_get(glit);
   Testitem *tit = elm_object_item_data_get(glit);
   int i, j, val;

   val = tit->mode * 10;
   for (i = 0; i < 100; i++)
     {
        tit = calloc(1, sizeof(Testitem));
        tit->mode = val + i;
        tit->item = elm_genlist_item_append(gl,
                                            api->itc2,
                                            tit/* item data */,
                                            glit/* parent */,
                                            ELM_GENLIST_ITEM_TREE,
                                            gl18_sel/* func */,
                                            NULL/* func data */);
     }
   for (j = 0; j < 3; j++)
     {
        tit = calloc(1, sizeof(Testitem));
        tit->mode = i;
        tit->item = elm_genlist_item_append(gl,
                                            api->itc1,
                                            tit/* item data */,
                                            glit/* parent */,
                                            ELM_GENLIST_ITEM_NONE,
                                            gl18_sel/* func */,
                                            NULL/* func data */);
        i++;
     }
}

static void
gl18_con(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info)
{
   Elm_Object_Item *glit = event_info;
   elm_genlist_item_subitems_clear(glit);
}

static void
gl18_exp_req(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED,
             void *event_info)
{
   Elm_Object_Item *glit = event_info;
   elm_genlist_item_expanded_set(glit, EINA_TRUE);
}

static void
gl18_con_req(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED,
             void *event_info)
{
   Elm_Object_Item *glit = event_info;
   elm_genlist_item_expanded_set(glit, EINA_FALSE);
}

void
test_genlist18(void        *data EINA_UNUSED,
               Evas_Object *obj EINA_UNUSED,
               void        *event_info EINA_UNUSED)
{
   Evas_Object *win, *gl, *bx, *fr1, *fr2, *bx2, *rdg;
   Testitem *tit = NULL;
   int i, j;

   api_data *api = calloc(1, sizeof(api_data));
   win = elm_win_util_standard_add("genlist-tree-decorate-all",
                                   "Genlist Tree and Decorate All Mode");
   elm_win_autodel_set(win, EINA_TRUE);
   evas_object_event_callback_add(win, EVAS_CALLBACK_FREE, _cleanup_cb, api);

   bx = elm_box_add(win);
   evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, bx);
   evas_object_show(bx);

   bx2 = elm_box_add(win);
   evas_object_size_hint_align_set(bx2, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_horizontal_set(bx2, EINA_TRUE);
   elm_box_pack_end(bx, bx2);
   evas_object_show(bx2);

   gl = elm_genlist_add(win);
   evas_object_size_hint_align_set(gl, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(gl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   api->gl = gl;
   evas_object_show(gl);

   elm_genlist_tree_effect_enabled_set(gl, EINA_TRUE);
   evas_object_data_set(gl, "tree_effect", "true");

   /* normal item */
   api->itc1 = elm_genlist_item_class_new();
   api->itc1->item_style = "tree_effect"; /* item/tree_effect */
   api->itc1->func.text_get = gl15_text_get;
   api->itc1->func.content_get = gl15_content_get;
   api->itc1->func.state_get = gl_state_get;
   api->itc1->func.del = gl18_del;
   api->itc1->decorate_all_item_style = "edit";

   /* expandable item */
   api->itc2 = elm_genlist_item_class_new();
   api->itc2->item_style = "tree_effect"; /* tree/tree_effect */
   api->itc2->func.text_get = gl15_text_get;
   api->itc2->func.content_get = gl15_content_get;
   api->itc2->func.state_get = gl_state_get;
   api->itc2->func.del = gl18_del;
   api->itc2->decorate_all_item_style = "edit";

   for (i = 0; i < 5; i++)
     {
        tit = calloc(1, sizeof(Testitem));
        tit->mode = i;
        tit->item = elm_genlist_item_append(gl,
                                            api->itc2,
                                            tit/* item data */,
                                            NULL/* parent */,
                                            ELM_GENLIST_ITEM_TREE,
                                            gl18_sel/* func */,
                                            NULL/* func data */);
     }

   for (j = 0; j < 3; j++)
     {
        tit = calloc(1, sizeof(Testitem));
        tit->mode = i;
        tit->item = elm_genlist_item_append(gl,
                                            api->itc1,
                                            tit/* item data */,
                                            NULL/* parent */,
                                            ELM_GENLIST_ITEM_NONE,
                                            gl18_sel/* func */,
                                            NULL/* func data */);
        i++;
     }

   elm_genlist_item_class_free(api->itc1);
   elm_genlist_item_class_free(api->itc2);

   evas_object_smart_callback_add(gl, "expand,request", gl18_exp_req, api);
   evas_object_smart_callback_add(gl, "contract,request", gl18_con_req, api);
   evas_object_smart_callback_add(gl, "expanded", gl18_exp, api);
   evas_object_smart_callback_add(gl, "contracted", gl18_con, api);

   elm_box_pack_end(bx, gl);

   fr1 = _tree_effect_frame_new(win, &rdg, gl);
   elm_box_pack_end(bx2, fr1);

   fr2 = _decorate_all_mode_frame_new(win, rdg, gl);
   elm_box_pack_end(bx2, fr2);

   evas_object_resize(win, 400, 800);
   evas_object_show(win);
}

void
test_genlist19(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Evas_Object *win, *gl, *bt_50, *bt_1500, *bx, *bxx, *bt;
   Evas_Object *over;
   Elm_Object_Item *gli;
   int i;
   api_data *api = calloc(1, sizeof(api_data));

   win = elm_win_util_standard_add("genlist-full", "Genlist Full Widget");
   elm_win_autodel_set(win, EINA_TRUE);
   evas_object_event_callback_add(win, EVAS_CALLBACK_FREE, _cleanup_cb, api);

   bxx = elm_box_add(win);
   elm_win_resize_object_add(win, bxx);
   evas_object_size_hint_weight_set(bxx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_show(bxx);

   bx = elm_box_add(win);
   evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(bx, EVAS_HINT_FILL, EVAS_HINT_FILL);
   api->box = bx;
   evas_object_show(bx);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Next API function");
   evas_object_smart_callback_add(bt, "clicked", _api_bt_clicked, (void *) api);
   elm_box_pack_end(bxx, bt);
   elm_object_disabled_set(bt, api->state == API_STATE_LAST);
   evas_object_show(bt);

   elm_box_pack_end(bxx, bx);

   gl = elm_genlist_add(win);
   evas_object_smart_callback_add(gl, "selected", _gl_selected, NULL);
   evas_object_smart_callback_add(gl, "clicked,double", _gl_double_clicked, NULL);
   evas_object_smart_callback_add(gl, "longpressed", _gl_longpress, NULL);
   // FIXME: This causes genlist to resize the horiz axis very slowly :(
   // Reenable this and resize the window horizontally, then try to resize it back
   //elm_genlist_mode_set(gl, ELM_LIST_LIMIT);
   evas_object_size_hint_weight_set(gl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(gl, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(bx, gl);
   api->gl = gl;
   evas_object_show(gl);

   over = evas_object_rectangle_add(evas_object_evas_get(win));
   evas_object_color_set(over, 0, 0, 0, 0);
   evas_object_event_callback_add(over, EVAS_CALLBACK_MOUSE_MOVE, _move, gl);
   evas_object_repeat_events_set(over, EINA_TRUE);
   evas_object_show(over);
   evas_object_size_hint_weight_set(over, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, over);

   api->itc1 = elm_genlist_item_class_new();
   api->itc1->item_style = "full";
   api->itc1->func.text_get = NULL;
   api->itc1->func.content_get = gl_content_full_get;
   api->itc1->func.state_get = gl_state_get;
   api->itc1->func.del = NULL;

   bt_50 = elm_button_add(win);
   elm_object_text_set(bt_50, "Go to 50");
   evas_object_show(bt_50);
   elm_box_pack_end(bx, bt_50);

   bt_1500 = elm_button_add(win);
   elm_object_text_set(bt_1500, "Go to 1500");
   evas_object_show(bt_1500);
   elm_box_pack_end(bx, bt_1500);

   for (i = 0; i < 2000; i++)
     {
        gli = elm_genlist_item_append(gl, api->itc1,
                                      (void *)(uintptr_t)i/* item data */,
                                      NULL/* parent */,
                                      ELM_GENLIST_ITEM_NONE,
                                      gl_sel/* func */,
                                      (void *)(uintptr_t)(i * 10)/* func data */);
        if (i == 50)
          evas_object_smart_callback_add(bt_50, "clicked", _bt50_cb, gli);
        else if (i == 1500)
          evas_object_smart_callback_add(bt_1500, "clicked", _bt1500_cb, gli);
     }
   elm_genlist_item_class_free(api->itc1);

   evas_object_resize(win, 480, 800);
   evas_object_show(win);
}

/*************/

/* test genlist item styles */

const char *_genlist_styles[] = {
   "default", "full", "one_icon", "end_icon", "no_icon",
   "default_style", "double_label", "icon_top_text_bottom",
   "message", "media", "media-album", "media-preview",
   NULL
};

static void
_genlist_renew(Evas_Object *obj, const char *style)
{
   Elm_Genlist_Item_Class *ic;
   Evas_Object *check;
   int i;

   if (!obj) return;

   elm_genlist_clear(obj);

   check = evas_object_data_get(obj, "check");
   if (elm_check_state_get(check))
     elm_genlist_mode_set(obj, ELM_LIST_COMPRESS);
   else
     elm_genlist_mode_set(obj, ELM_LIST_SCROLL);

   ic = elm_genlist_item_class_new();
   ic->item_style = style;
   ic->func.text_get = gl_text_get;
   ic->func.content_get = gl_content_get;
   ic->func.state_get = NULL;
   ic->func.del = NULL;

   for (i = 0; i < 50; i++)
     {
        elm_genlist_item_append(obj, ic, (void *)(uintptr_t)i, NULL,
                                ELM_GENLIST_ITEM_NONE, NULL, NULL);
     }
   elm_genlist_item_class_free(ic);
}

static void
_item_style_sel_cb(void *data EINA_UNUSED, Evas_Object *obj, void *event_info)
{
   Evas_Object *gl = evas_object_data_get(obj, "genlist");
   if (gl)
     _genlist_renew(gl, elm_object_item_text_get(event_info));
}

static Evas_Object *
_item_styles_list_create(Evas_Object *parent)
{
   Evas_Object *list;
   int i = 0;

   list = elm_list_add(parent);
   evas_object_size_hint_weight_set(list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(list, EVAS_HINT_FILL, EVAS_HINT_FILL);

   while (_genlist_styles[i])
     {
        elm_list_item_append(list, _genlist_styles[i], NULL, NULL,
                             _item_style_sel_cb, _genlist_styles[i]);
        i++;
     }

   return list;
}

void
test_genlist_item_styles(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED,
                         void *event_info EINA_UNUSED)
{
   Evas_Object *win, *box, *gl, *list, *table, *check;

   win = elm_win_util_standard_add("genlist-item-styles", "Genlist Item Styles");
   elm_win_autodel_set(win, EINA_TRUE);

   box = elm_box_add(win);
   elm_box_horizontal_set(box, EINA_TRUE);
   evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, box);
   evas_object_show(box);

   list = _item_styles_list_create(box);
   evas_object_show(list);

   table = _elm_min_set(list, box, 200, 0);
   evas_object_size_hint_weight_set(table, 0.0, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(table, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(box, table);
   evas_object_show(table);

   gl = elm_genlist_add(box);
   evas_object_size_hint_weight_set(gl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(gl, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(box, gl);
   evas_object_show(gl);

   check = elm_check_add(win);
   elm_object_text_set(check, "Compress");
   elm_box_pack_end(box, check);
   evas_object_show(check);
   evas_object_data_set(gl, "check", check);
   _genlist_renew(gl, "default");

   evas_object_data_set(list, "genlist", gl);

   evas_object_resize(win, 600, 600);
   evas_object_show(win);
}

/***********/

typedef struct _Genlist_Multi_Data Genlist_Multi_Data;
struct _Genlist_Multi_Data
{
   Evas_Object *gl;
   Evas_Object *rd1;
   Evas_Object *rd2;
};

static void
_multi_select_changed_cb(void *data, Evas_Object *obj,
                         void *event_info EINA_UNUSED)
{
   Eina_Bool multi = elm_check_state_get(obj);
   Genlist_Multi_Data *gd = data;
   if (!gd) return;

   elm_genlist_multi_select_set(gd->gl, multi);
   elm_object_disabled_set(gd->rd1, !multi);
   elm_object_disabled_set(gd->rd2, !multi);
}

static void
_multi_select_mode_changed_cb(void *data, Evas_Object *obj,
                              void *event_info EINA_UNUSED)
{
   elm_genlist_multi_select_mode_set(data, elm_radio_value_get(obj));
}

static void
_multi_select_frame_create(Evas_Object *bx, Genlist_Multi_Data *gd)
{
   Evas_Object *fr, *bx2, *bx3, *tg, *rd, *rdg;
   if (!gd) return;

   fr = elm_frame_add(bx);
   evas_object_size_hint_weight_set(fr, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(fr, EVAS_HINT_FILL, 0.5);
   elm_object_text_set(fr, "Multi Select Option");
   elm_box_pack_end(bx, fr);
   evas_object_show(fr);

   bx2 = elm_box_add(fr);
   elm_object_content_set(fr, bx2);
   evas_object_show(bx2);

   tg = elm_check_add(bx2);
   elm_object_style_set(tg, "toggle");
   elm_object_text_set(tg, "Multi Select Mode");
   elm_box_pack_end(bx2, tg);
   evas_object_show(tg);

   bx3 = elm_box_add(bx2);
   elm_box_horizontal_set(bx3, EINA_TRUE);
   elm_box_pack_end(bx2, bx3);
   evas_object_show(bx3);

   gd->rd1 = rdg = rd = elm_radio_add(bx3);
   elm_radio_state_value_set(rd, ELM_OBJECT_MULTI_SELECT_MODE_DEFAULT);
   elm_object_text_set(rd, "Default Mode");
   elm_box_pack_end(bx3, rd);
   evas_object_show(rd);
   elm_object_disabled_set(rd, EINA_TRUE);
   evas_object_smart_callback_add(rd, "changed",
                                  _multi_select_mode_changed_cb, gd->gl);

   gd->rd2 = rd = elm_radio_add(bx3);
   elm_radio_state_value_set(rd, ELM_OBJECT_MULTI_SELECT_MODE_WITH_CONTROL);
   elm_radio_group_add(rd, rdg);
   elm_object_text_set(rd, "With Control Mode");
   elm_box_pack_end(bx3, rd);
   evas_object_show(rd);
   elm_object_disabled_set(rd, EINA_TRUE);
   evas_object_smart_callback_add(rd, "changed",
                                  _multi_select_mode_changed_cb, gd->gl);

   evas_object_smart_callback_add(tg, "changed",
                                  _multi_select_changed_cb, gd);
}

void
test_genlist_multi_select(void *data EINA_UNUSED,
                          Evas_Object *obj EINA_UNUSED,
                          void *event_info EINA_UNUSED)
{
   Evas_Object *win, *gl, *bx;
   Genlist_Multi_Data *gd = calloc(1, sizeof(Genlist_Multi_Data));
   Elm_Genlist_Item_Class *itc = NULL;
   int i = 0;

   win = elm_win_util_standard_add("genlist-multi-select", "Genlist Multi Select");
   elm_win_autodel_set(win, EINA_TRUE);
   evas_object_event_callback_add(win, EVAS_CALLBACK_FREE, _cleanup_cb, gd);

   bx = elm_box_add(win);
   evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, bx);
   evas_object_show(bx);

   gd->gl = gl = elm_genlist_add(bx);
   _multi_select_frame_create(bx, gd);

   evas_object_size_hint_weight_set(gl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(gl, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(bx, gl);
   evas_object_show(gl);

   itc = elm_genlist_item_class_new();
   itc->item_style = "default";
   itc->func.text_get = gl_text_get;
   itc->func.content_get = gl_content_get;
   itc->func.state_get = gl_state_get;
   itc->func.del = NULL;

   for (i = 0; i < 100; i++)
     {
        elm_genlist_item_append(gl, itc,
                                (void *)(uintptr_t)i/* item data */,
                                NULL/* parent */,
                                ELM_GENLIST_ITEM_NONE,
                                gl_sel/* func */,
                                (void *)(uintptr_t)(i * 10)/* func data */);
     }
   elm_genlist_item_class_free(itc);

   evas_object_resize(win, 320, 500);
   evas_object_show(win);
}

/* test genlist item search by text */

typedef struct _gl20_Event_Data gl20_Event_Data;
struct _gl20_Event_Data
{
   Evas_Object *gl_obj;
   Evas_Object *tg_obj;
   Evas_Object *en_obj;
   Elm_Object_Item *last_item_found;
};

static const char *_gl20_items_text[] = {
         "Albany",          "Annapolis",
         "Atlanta",         "Augusta",
         "Austin",          "Baton Rouge",
         "Bismarck",        "Boise",
         "Boston",          "Carson City",
         "Charleston",      "Cheyenne",
         "Columbia",        "Columbus",
         "Concord",         "Denver",
         "Des Moines",      "Dover",
         "Frankfort",       "Harrisburg",
         "Hartford",        "Helena",
         "Honolulu",        "Indianapolis",
         "Jackson",         "Jefferson City",
         "Juneau",          "Lansing",
         "Lincoln",         "Little Rock",
         "Madison",         "Montgomery",
         "Montpelier",      "Nashville",
         "Oklahoma City",   "Olympia",
         "Phoenix",         "Pierre",
         "Providence",      "Raleigh",
         "Richmond",        "Sacramento",
         "Saint Paul",      "Salem",
         "Salt Lake City",  "Santa Fe",
         "Springfield",     "Tallahassee",
         "Topeka",          "Trenton" };

static char *
_gl20_text_get(void *data, Evas_Object *obj EINA_UNUSED,
               const char *part EINA_UNUSED)
{
   char buf[32];
   int item_index = (int)(uintptr_t)data;

   if (item_index < 50)
     {
        snprintf(buf, sizeof(buf), "%s", _gl20_items_text[item_index]);
        return strdup(buf);
     }
   else if (item_index < 100)
     {
        snprintf(buf, sizeof(buf), "%X", (item_index - 50));
        return strdup(buf);
     }
   else if (item_index == 100)
     return strdup("Tree Item");

   return NULL;
}

static void
_gl20_search_item(gl20_Event_Data *event_data, Elm_Object_Item * it)
{
   const char *str = elm_entry_entry_get(event_data->en_obj);
   if (!str || !strlen(str)) return;

   Elm_Glob_Match_Flags flag = 0;
   if (!elm_check_state_get(event_data->tg_obj)) flag = ELM_GLOB_MATCH_NOCASE;

   printf("Looking for \"%s\". ", str);
   event_data->last_item_found = elm_genlist_search_by_text_item_get
   (event_data->gl_obj, it, NULL, str, flag);

   if (event_data->last_item_found)
     {
        printf("Found.\n");
        elm_genlist_item_selected_set(event_data->last_item_found, EINA_TRUE);
        elm_genlist_item_bring_in(event_data->last_item_found,
           ELM_GENLIST_ITEM_SCROLLTO_MIDDLE);
        elm_object_focus_set(event_data->en_obj, EINA_TRUE);
     }
   else
     printf("Not Found.\n");
}

static void
_gl20_search_settings_changed_cb(void *data, Evas_Object *obj EINA_UNUSED,
                                 void *einfo EINA_UNUSED)
{
   _gl20_search_item(data, NULL);
}

static Elm_Genlist_Item_Class *
_gl20_item_class_create(const char *item_style)
{
   Elm_Genlist_Item_Class * itc = elm_genlist_item_class_new();
   itc->item_style = item_style;
   itc->func.text_get = _gl20_text_get;
   itc->func.content_get = gl_content_get;
   itc->func.state_get = gl_state_get;
   itc->func.del = NULL;
   return itc;
}

static void
_gl20_expand_cb(void *data EINA_UNUSED, Evas_Object *o EINA_UNUSED,
                void *event_info)
{
   Elm_Object_Item *glit = event_info;
   Evas_Object *gl = elm_object_item_widget_get(glit);
   Elm_Genlist_Item_Class *itc = NULL;
   int i = 0;

   itc = _gl20_item_class_create("default");

   for (i = 50; i < 100; i++)
     {
        elm_genlist_item_append(gl, itc,
           (void *)(uintptr_t) i/* item data */,
           glit/* parent */,
           ELM_GENLIST_ITEM_NONE, NULL/* func */,
           NULL/* func data */);
     }
   elm_genlist_item_class_free(itc);
}

static void _gl20_on_keydown(void *data, Evas *evas EINA_UNUSED,
                             Evas_Object *o EINA_UNUSED, void *einfo)
{
   Evas_Event_Key_Down *ev = einfo;
   gl20_Event_Data * event_data = (gl20_Event_Data *)data;

   if (!strcmp(ev->key, "Return"))
     {
        printf("Looking for next item\n");
        _gl20_search_item(data, event_data->last_item_found);
     }
}

void
test_genlist20(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED,
               void *event_info EINA_UNUSED)
{
   Evas_Object *win, *bx, *gl;
   Evas_Object *fr, *lb_frame;            // info frame
   Evas_Object *bx_entry, *lb_entry, *en; // search line
   Evas_Object *tg;                       // "case sensitive" toggle
   Elm_Genlist_Item_Class *itc = NULL;
   gl20_Event_Data* event_data = NULL;
   int i = 0;

   win = elm_win_util_standard_add("genlist-item-search-by-text",
            "Genlist Item Search By Text");
   elm_win_autodel_set(win, EINA_TRUE);

   bx = elm_box_add(win);
   evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, bx);
   evas_object_show(bx);

   fr = elm_frame_add(bx);
   evas_object_size_hint_weight_set(fr, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(fr, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_object_text_set(fr, "Information");
   elm_box_pack_end(bx, fr);
   evas_object_show(fr);

   lb_frame = elm_label_add(fr);
   elm_object_text_set(lb_frame,
      "<align=left>This is an example of "
      "elm_genlist_search_by_text_item_get() usage.<br>"
      "Enter search string to the entry and press Enter to "
      "show next search result.<br>");
   elm_object_content_set(fr, lb_frame);
   evas_object_show(lb_frame);

   tg = elm_check_add(win);
   elm_object_style_set(tg, "toggle");
   elm_object_text_set(tg, " Case Sensitive Search");
   elm_check_state_set(tg, EINA_TRUE);
   elm_box_pack_end(bx, tg);
   evas_object_show(tg);

   bx_entry = elm_box_add(win);
   elm_box_horizontal_set(bx_entry, EINA_TRUE);
   evas_object_size_hint_weight_set(bx_entry, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(bx_entry, EVAS_HINT_FILL, 0.0);
   elm_box_pack_end(bx, bx_entry);
   evas_object_show(bx_entry);

   lb_entry = elm_label_add(win);
   elm_object_text_set(lb_entry, " Search:");
   evas_object_size_hint_weight_set(lb_entry, 0.0, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(lb_entry, 0.0, EVAS_HINT_FILL);
   elm_box_pack_end(bx_entry, lb_entry);
   evas_object_show(lb_entry);

   en = elm_entry_add(win);
   elm_entry_single_line_set(en, EINA_TRUE);
   elm_entry_scrollable_set(en, EINA_TRUE);
   elm_object_part_text_set(en, "guide", "Type item's name here to search.");
   evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(en, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(bx_entry, en);
   evas_object_show(en);
   elm_object_focus_set(en, EINA_TRUE);

   gl = elm_genlist_add(bx);

   evas_object_size_hint_weight_set(gl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(gl, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(bx, gl);
   evas_object_show(gl);

   event_data = calloc(1, sizeof(gl20_Event_Data));
   event_data->tg_obj = tg;
   event_data->en_obj = en;
   event_data->gl_obj = gl;
   event_data->last_item_found = NULL;

   evas_object_event_callback_add(en, EVAS_CALLBACK_KEY_DOWN,
      _gl20_on_keydown, (void*)event_data);
   evas_object_event_callback_add(gl, EVAS_CALLBACK_FREE,
      _cleanup_cb, (void*)event_data);
   evas_object_smart_callback_add(en, "changed,user",
      _gl20_search_settings_changed_cb, (void*)event_data);
   evas_object_smart_callback_add(tg, "changed",
      _gl20_search_settings_changed_cb, (void*)event_data);
   evas_object_smart_callback_add(gl, "expand,request", gl4_exp_req, gl);
   evas_object_smart_callback_add(gl, "contract,request", gl4_con_req, gl);
   evas_object_smart_callback_add(gl, "contracted", gl4_con, gl);
   evas_object_smart_callback_add(gl, "expanded", _gl20_expand_cb, gl);

   itc = _gl20_item_class_create("tree_effect");

   elm_genlist_item_append(gl, itc,
      (void *)100/* item data */,
      NULL/* parent */,
      ELM_GENLIST_ITEM_TREE,
      NULL/* func */,
      NULL/* func data */);

   itc->item_style = "default";

   for (i = 0; i < 50; i++)
     {
        elm_genlist_item_append(gl, itc,
           (void *)(uintptr_t)i/* item data */,
           NULL/* parent */,
           ELM_GENLIST_ITEM_NONE,
           NULL/* func */,
           NULL/* func data */);
     }

   elm_genlist_item_class_free(itc);

   evas_object_resize(win, 320, 500);
   evas_object_show(win);
}

/* test genlist deletion */

static void _gl_del_sel(void *data, Evas_Object *obj, void *event_info);

static void
_gl_del_win_del_cb(void *data, Evas *e EINA_UNUSED,
                   Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   if (!data) return;
   elm_genlist_item_class_free(data);
}

static void
_gl_del_unrealized_cb(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED,
                      void *event_info)
{
   int num = (int)(uintptr_t)elm_object_item_data_get(event_info);
   printf("unrealized item # %d\n", num);
}

static void
_gl_del_doubleclick_cb(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED,
                       void *event_info)
{
   int num = (int)(uintptr_t)elm_object_item_data_get(event_info);
   int num_category = num % 4;

   if (num_category == 3)
     elm_genlist_clear(obj);
}
static Evas_Object *
_gl_del_genlist_add(Evas_Object *bx)
{
   Evas_Object *gl = NULL;

   gl = elm_genlist_add(bx);
   evas_object_size_hint_weight_set(gl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(gl, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(bx, gl);
   evas_object_show(gl);
   evas_object_smart_callback_add(gl, "unrealized",
                                  _gl_del_unrealized_cb, NULL);
   evas_object_smart_callback_add(gl, "clicked,double",
                                  _gl_del_doubleclick_cb, NULL);

   return gl;
}

static void
_gl_del_item_append(Evas_Object *gl, Elm_Genlist_Item_Class *itc)
{
   int i = 0;
   for (i = 0; i < 1000; i++)
     {
        elm_genlist_item_append(gl, itc,
                                (void *)(uintptr_t)i/* item data */,
                                NULL/* parent */,
                                ELM_GENLIST_ITEM_NONE,
                                _gl_del_sel/* func */,
                                (void *)(uintptr_t)(i)/* func data */);
     }
}

char *_gl_del_text_get(void *data, Evas_Object *obj EINA_UNUSED,
                      const char *part EINA_UNUSED)
{
   char buf[256] = { 0 };
   int num = (int)(uintptr_t)data;
   int num_category = num % 4;

   if (num_category == 0)
     snprintf(buf, sizeof(buf),
              "Item #%.02i - 1. Item Del", num);
   else if (num_category == 1)
     snprintf(buf, sizeof(buf),
              "Item #%.02i - 2. Genlist Clear and Item Append", num);
   else if (num_category == 2)
     snprintf(buf, sizeof(buf),
              "Item #%.02i - 3. Genlist Del", num);
   else if (num_category == 3)
     snprintf(buf, sizeof(buf),
              "Item #%.02i - 4. Genlist Clear on double-click", num);

   return strdup(buf);
}

static void
_gl_del_sel(void *data, Evas_Object *obj, void *event_info)
{
   int num = (int)(uintptr_t)data;
   int num_category = num % 4;
   Elm_Object_Item *it = event_info;
   Elm_Genlist_Item_Class *itc =
      (Elm_Genlist_Item_Class *)elm_genlist_item_item_class_get(it);

   if (num_category == 0)
     elm_object_item_del(it);
   else if (num_category == 1)
     {
        elm_genlist_clear(obj);
        _gl_del_item_append(obj, itc);
     }
   else if (num_category == 2)
     {
        evas_object_del(obj);
     }
}

static void
_gl_del_del_cb(void *data, Evas_Object *obj EINA_UNUSED)
{
   printf("deleted item # %d\n", (int)(uintptr_t)data);
}

void
test_genlist_del(void *data EINA_UNUSED,
                 Evas_Object *obj EINA_UNUSED,
                 void *event_info EINA_UNUSED)
{
   Evas_Object *win, *bx, *fr, *lb, *gl;
   Elm_Genlist_Item_Class *itc = NULL;

   win = elm_win_util_standard_add("genlist-del", "Genlist Del");
   elm_win_autodel_set(win, EINA_TRUE);

   bx = elm_box_add(win);
   evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, bx);
   elm_box_align_set(bx, 0.5, 0.0);
   evas_object_show(bx);

   fr = elm_frame_add(bx);
   evas_object_size_hint_weight_set(fr, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(fr, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_object_text_set(fr, "Information");
   elm_box_pack_end(bx, fr);
   evas_object_show(fr);

   lb = elm_label_add(fr);
   elm_object_text_set(lb, "<align=left>This example tests the following cases"
                       " on item selection.<br/>"
                       "   1. genlist item deletion<br/>"
                       "   2. genlist clear and item append<br/>"
                       "   3. genlist del<br/>"
                       "   4. genlist clear on double-click</align>");
   elm_object_content_set(fr, lb);
   evas_object_show(lb);

   itc = elm_genlist_item_class_new();
   itc->item_style = "default";
   itc->func.text_get = _gl_del_text_get;
   itc->func.content_get = gl_content_get;
   itc->func.state_get = NULL;
   itc->func.del = _gl_del_del_cb;
   evas_object_event_callback_add(win, EVAS_CALLBACK_DEL,
                                  _gl_del_win_del_cb, itc);

   gl = _gl_del_genlist_add(bx);
   _gl_del_item_append(gl, itc);

   evas_object_resize(win, 320, 500);
   evas_object_show(win);
}

/*************/
static unsigned _gl_focus_objects = 3;
static const char *_gl_focus_object_names[] = {"None", "Square", "Button", "Check", "Box"};

// for the top genlist items
static char *
gl_focus_top_items_text_get(void *data, Evas_Object *obj EINA_UNUSED,
                            const char *part EINA_UNUSED)
{
   if (!data) return NULL;

   if (!strcmp(data, "do_nothing"))
     return strdup("Genlist Item");
   else if (!strcmp(data, "popup_sel"))
     return strdup("Create a popup on Select");
   else if (!strcmp(data, "popup_mouse_down"))
     return strdup("Create a popup on Mouse Down");
   else if (!strcmp(data, "clear_on_focus"))
     return strdup("Genlist Clear on Focus");
   else
     return NULL;
}

static char *
gl_focus_text_get(void *data, Evas_Object *obj EINA_UNUSED, const char *part EINA_UNUSED)
{
   char buf[256];
   unsigned char op = (uintptr_t)data % 100;
   unsigned char v1, v2;

   v1 = op / 10;
   if (v1 > 4) v1 = 4;
   v2 = op % 10;
   if (v2 > 4) v2 = 4;
   snprintf(buf, sizeof(buf), " %s / %s ",
            _gl_focus_object_names[v1], _gl_focus_object_names[v2]);
   return strdup(buf);
}

static Evas_Object *
gl_focus_content_get(void *data, Evas_Object *obj, const char *part)
{
   Evas_Object *cnt = NULL;

   char op = (uintptr_t)data % 100;
   char type = (!strcmp(part,"elm.swallow.icon")) ? op / 10 : op % 10;

   switch(type)
     {
      case 1:
         cnt = elm_bg_add(obj);
         evas_object_color_set(cnt, 128, 18, 128, 255);
         break;
      case 2:
         cnt = elm_button_add(obj);
         break;
      case 3:
         cnt = elm_check_add(obj);
         break;
      case 4:
         cnt = elm_box_add(obj);
         evas_object_size_hint_align_set(cnt, EVAS_HINT_FILL, EVAS_HINT_FILL);
         elm_box_horizontal_set(cnt, EINA_TRUE);
         elm_box_pack_end(cnt, gl_focus_content_get((void *)2, obj, ""));
         elm_box_pack_end(cnt, gl_focus_content_get((void *)3, obj, ""));
         elm_box_pack_end(cnt, gl_focus_content_get((void *)2, obj, ""));
         break;
      default:
         break;

     }
   if (cnt)
     {
        evas_object_size_hint_weight_set(cnt, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
        evas_object_show(cnt);
     }
   return cnt;
}

static void
_gl_focus_sel_popup_close_btn_cb(void *data, Evas_Object *obj EINA_UNUSED,
                                 void *event_info EINA_UNUSED)
{
   evas_object_del(data);
}

static void
_gl_focus_sel_popup_create(Evas_Object *parent)
{
   Evas_Object *popup = NULL, *btn = NULL;

   popup = elm_popup_add(parent);
   elm_object_text_set(popup, "Popup for the genlist focus test with popup creation.");

   // popup buttons
   btn = elm_button_add(popup);
   elm_object_text_set(btn, "Close");
   elm_object_part_content_set(popup, "button1", btn);
   evas_object_smart_callback_add(btn, "clicked", _gl_focus_sel_popup_close_btn_cb, popup);

   // popup show should be called after adding all the contents and the buttons
   // of popup to set the focus into popup's contents correctly.
   evas_object_show(popup);
}

static void
_gl_focus_0_item_sel_cb(void *data EINA_UNUSED, Evas_Object *obj,
                        void *event_info EINA_UNUSED)
{
   _gl_focus_sel_popup_create(obj);
}

static void
_gl_focus_item_loop_enable_changed_cb(void *data, Evas_Object *obj,
                                      void *event_info EINA_UNUSED)
{
   Evas_Object *gl = data;
   elm_object_scroll_item_loop_enabled_set(gl, elm_check_state_get(obj));
}

static void
_gl_focus_focus_on_selection_set(Evas_Object *gl,
                                 Evas_Object *chk, Eina_Bool focus)
{
   elm_genlist_focus_on_selection_set(gl, focus);
   elm_check_state_set(chk, focus);
   printf("genlist_focus_on_selection = %s\n", (focus) ? "true" : "false");
}

static void
_gl_focus_focus_on_selection_changed_cb(void *data, Evas_Object *obj,
                                        void *event_info EINA_UNUSED)
{
   Eina_Bool nextstate = !elm_genlist_focus_on_selection_get(data);
   _gl_focus_focus_on_selection_set(data, obj, nextstate);
}

static void
_gl_focus_focus_highlight_changed_cb(void *data, Evas_Object *obj,
                                     void *event_info EINA_UNUSED)
{
   elm_win_focus_highlight_enabled_set(data,
                                       elm_check_state_get(obj));
}

static void
_gl_focus_focus_animate_changed_cb(void *data, Evas_Object *obj,
                                   void *event_info EINA_UNUSED)
{
   elm_win_focus_highlight_animate_set(data,
                                       elm_check_state_get(obj));
}

static void
_gl_focus_move_policy_changed_cb(void *data EINA_UNUSED,
                                 Evas_Object *obj,
                                 void *event_info EINA_UNUSED)
{
   int val = elm_radio_value_get(obj);

   if (val == 0)
     elm_config_focus_move_policy_set(ELM_FOCUS_MOVE_POLICY_CLICK);
   else if (val == 1)
     elm_config_focus_move_policy_set(ELM_FOCUS_MOVE_POLICY_IN);
}

static void
_gl_focus_item_focus_cb(void *data, Evas_Object *obj, void *event_info)
{
   printf("item,focused: %p\n", event_info);

   if (event_info == data)
     elm_genlist_clear(obj);
}

static void
_gl_focus_item_unfocus_cb(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED,
                          void *event_info)
{
   printf("item,unfocused %p\n", event_info);
}

static void
_gl_focus_item_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info)
{
   printf("%s: %p\n", (char *)data, event_info);
}

static void
_gl_focus_key_down_cb(void *data EINA_UNUSED, Evas *e EINA_UNUSED,
                      Evas_Object *obj EINA_UNUSED, void *event_info)
{
   Evas_Event_Key_Down *ev = event_info;
   printf("\n=== Key Down : %s ===\n", ev->keyname);
}

static void
_gl_focus_mouse_down_cb(void *data EINA_UNUSED, Evas *e EINA_UNUSED,
                        Evas_Object *obj, void *event_info)
{
   Evas_Event_Mouse_Down *ev = event_info;
   Elm_Object_Item *it = NULL;
   int postret = 0;

   it = elm_genlist_at_xy_item_get(obj, ev->canvas.x, ev->canvas.y, &postret);
   if (!it) return;

   if (elm_genlist_item_index_get(it) == 4)
     _gl_focus_sel_popup_create(obj);
}

static Ecore_Timer *timer = NULL;
static void
_gl_focus_win_del_cb(void *data EINA_UNUSED, Evas *e EINA_UNUSED,
                     Evas_Object *obj EINA_UNUSED,
                     void *event_info EINA_UNUSED)
{
   ecore_timer_del(timer);
   timer = NULL;
}

static void
_gl_focus_item_select_on_focus_disable_changed_cb(void *data EINA_UNUSED, Evas_Object *obj,
                                                  void *event_info EINA_UNUSED)
{
   elm_config_item_select_on_focus_disabled_set(elm_check_state_get(obj));
}

static void
_gl_first_item_focus_on_first_focus_in_cb(void *data EINA_UNUSED, Evas_Object *obj,
                                          void *event_info  EINA_UNUSED)
{
   elm_config_first_item_focus_on_first_focusin_set(elm_check_state_get(obj));
}

static void
_gl_wheel_disabled_cb(void *data, Evas_Object *obj, void *event_info EINA_UNUSED)
{
   elm_scroller_wheel_disabled_set(data, elm_check_state_get(obj));
}

static Eina_Bool
_focus_timer_cb(void *data)
{
   elm_object_item_focus_set(data, EINA_TRUE);
   timer = NULL;

   return ECORE_CALLBACK_CANCEL;
}

static Eina_Bool
_select_timer_cb(void *data)
{
   elm_genlist_item_selected_set(data, EINA_TRUE);
   timer = NULL;

   return ECORE_CALLBACK_CANCEL;
}

static void
_focus_btn_cb(void *data, Evas_Object *obj EINA_UNUSED,
              void *event_info EINA_UNUSED)
{
   ecore_timer_del(timer);
   timer = ecore_timer_add(1.5, _focus_timer_cb, data);
}

static void
_sel_btn_cb(void *data, Evas_Object *obj EINA_UNUSED,
            void *event_info EINA_UNUSED)
{
   ecore_timer_del(timer);
   timer = ecore_timer_add(1.5, _select_timer_cb, data);
}

static void
_dis_btn_cb(void *data, Evas_Object *obj EINA_UNUSED,
            void *event_info EINA_UNUSED)
{
   elm_object_item_disabled_set(data, EINA_TRUE);
}

static void
_add_more_items_btn_cb(void *data, Evas_Object *obj EINA_UNUSED,
                       void *event_info EINA_UNUSED)
{
   Elm_Genlist_Item_Class *itc = NULL;
   int i = 0;

   itc = elm_genlist_item_class_new();
   itc->item_style = "default";
   itc->func.text_get = gl_text_get;
   itc->func.content_get = NULL;
   itc->func.state_get = NULL;
   itc->func.del = NULL;


   for (i = 0; i < 1000; i++)
     {
        elm_genlist_item_append(data, itc, (void *)(uintptr_t)i,
                                NULL, ELM_GENLIST_ITEM_NONE, NULL, NULL);
     }

   elm_genlist_item_class_free(itc);
}

static void
_focus_button_clicked_cb(void *data, Evas_Object *obj EINA_UNUSED,
                         void *event_info EINA_UNUSED)
{
   printf("Button clicked: %s\n", (char *)data);
}

void
_focus_autoscroll_changed_cb(void *data EINA_UNUSED,
                             Evas_Object *obj,
                             void *event_info EINA_UNUSED)
{
   elm_config_focus_autoscroll_mode_set(elm_radio_value_get(obj));
}

/* this function is used in another tests such as list, gengrid, and toolbar. */
Evas_Object *
_focus_autoscroll_mode_frame_create(Evas_Object *parent)
{
   Evas_Object *fr, *bx, *rdg, *rd;

   fr = elm_frame_add(parent);
   elm_object_text_set(fr, "Focus Autoscroll Mode");
   evas_object_size_hint_weight_set(fr, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(fr, EVAS_HINT_FILL, 0.5);
   evas_object_show(fr);

   bx = elm_box_add(fr);
   elm_object_content_set(fr, bx);
   evas_object_show(bx);

   rdg = rd = elm_radio_add(bx);
   elm_radio_state_value_set(rd, ELM_FOCUS_AUTOSCROLL_MODE_SHOW);
   elm_object_text_set(rd, "ELM_FOCUS_AUTOSCROLL_MODE_SHOW");
   elm_object_tooltip_text_set(rd, "Directly show the focused region<br/>"
                               "or item automatically inside a scroller.");
   evas_object_size_hint_weight_set(rd, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(rd, 0.0, EVAS_HINT_FILL);
   elm_box_pack_end(bx, rd);
   evas_object_show(rd);
   evas_object_smart_callback_add(rd, "changed",
                                  _focus_autoscroll_changed_cb,
                                  NULL);

   rd = elm_radio_add(bx);
   elm_radio_state_value_set(rd, ELM_FOCUS_AUTOSCROLL_MODE_NONE);
   elm_object_text_set(rd, "ELM_FOCUS_AUTOSCROLL_MODE_NONE");
   elm_object_tooltip_text_set(rd, "Do not show the focused region or<br/>"
                               "item automatically inside a scroller.");
   evas_object_size_hint_weight_set(rd, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(rd, 0.0, EVAS_HINT_FILL);
   elm_box_pack_end(bx, rd);
   elm_radio_group_add(rd, rdg);
   evas_object_show(rd);
   evas_object_smart_callback_add(rd, "changed",
                                  _focus_autoscroll_changed_cb,
                                  NULL);


   rd = elm_radio_add(bx);
   elm_radio_state_value_set(rd, ELM_FOCUS_AUTOSCROLL_MODE_BRING_IN);
   elm_object_text_set(rd, "ELM_FOCUS_AUTOSCROLL_MODE_BRING_IN");
   elm_object_tooltip_text_set(rd, "Bring in the focused region or item<br/>"
                               "automatically which might invole the scrolling.");
   evas_object_size_hint_weight_set(rd, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(rd, 0.0, EVAS_HINT_FILL);
   elm_box_pack_end(bx, rd);
   elm_radio_group_add(rd, rdg);
   evas_object_show(rd);
   evas_object_smart_callback_add(rd, "changed",
                                  _focus_autoscroll_changed_cb,
                                  NULL);

   elm_radio_value_set(rdg, elm_config_focus_autoscroll_mode_get());

   return fr;
}

static void
_test_genlist_focus_option_panel_create(Evas_Object *win, Evas_Object *bx,
                                        Evas_Object *gl, Elm_Object_Item *it_0,
                                        Elm_Object_Item *it_2)
{
   Evas_Object *fr = NULL, *bx_opt = NULL, *chk = NULL;
   Evas_Object *bx_mv = NULL, *rd = NULL, *rdg = NULL;
   Evas_Object *btn_box  = NULL, *btn = NULL;

   fr = elm_frame_add(bx);
   elm_object_text_set(fr, "Options");
   evas_object_size_hint_weight_set(fr, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(fr, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(bx, fr);
   evas_object_show(fr);

   bx_opt = elm_box_add(fr);
   elm_box_horizontal_set(bx_opt, EINA_TRUE);
   elm_object_content_set(fr, bx_opt);
   evas_object_show(bx_opt);

   chk = elm_check_add(bx_opt);
   elm_object_text_set(chk, "Focus Highlight");
   elm_check_state_set(chk, EINA_TRUE);
   evas_object_size_hint_weight_set(chk, EVAS_HINT_EXPAND, 0.0);
   evas_object_smart_callback_add(chk, "changed",
                                  _gl_focus_focus_highlight_changed_cb,
                                  win);
   elm_box_pack_end(bx_opt, chk);
   evas_object_show(chk);

   chk = elm_check_add(bx_opt);
   elm_object_text_set(chk, "Focus Animation");
   elm_check_state_set(chk, EINA_TRUE);
   evas_object_size_hint_weight_set(chk, EVAS_HINT_EXPAND, 0.0);
   evas_object_smart_callback_add(chk, "changed",
                                  _gl_focus_focus_animate_changed_cb,
                                  win);
   elm_box_pack_end(bx_opt, chk);
   evas_object_show(chk);

   chk = elm_check_add(bx_opt);
   elm_object_text_set(chk, "Focus on selection");
   evas_object_size_hint_weight_set(chk, EVAS_HINT_EXPAND, 0.0);
   evas_object_smart_callback_add(chk, "changed",
                                  _gl_focus_focus_on_selection_changed_cb, gl);
   elm_box_pack_end(bx_opt, chk);
   evas_object_show(chk);

   chk = elm_check_add(bx_opt);
   elm_object_text_set(chk, "Item Looping Enable");
   evas_object_size_hint_weight_set(chk, EVAS_HINT_EXPAND, 0.0);
   evas_object_smart_callback_add(chk, "changed",
                                  _gl_focus_item_loop_enable_changed_cb, gl);
   elm_box_pack_end(bx_opt, chk);
   evas_object_show(chk);

   chk = elm_check_add(bx_opt);
   elm_object_text_set(chk, "Item Select on Focus disable");
   elm_check_state_set(chk, elm_config_item_select_on_focus_disabled_get());
   evas_object_size_hint_weight_set(chk, EVAS_HINT_EXPAND, 0.0);
   evas_object_smart_callback_add(chk, "changed",
                                  _gl_focus_item_select_on_focus_disable_changed_cb,
                                  NULL);
   elm_box_pack_end(bx_opt, chk);
   evas_object_show(chk);

   chk = elm_check_add(bx_opt);
   elm_object_text_set(chk, "First item focus on first focus in");
   elm_check_state_set(chk, elm_config_first_item_focus_on_first_focusin_get());
   evas_object_size_hint_weight_set(chk, EVAS_HINT_EXPAND, 0.0);
   evas_object_smart_callback_add(chk, "changed",
                                  _gl_first_item_focus_on_first_focus_in_cb,
                                  NULL);
   elm_box_pack_end(bx_opt, chk);
   evas_object_show(chk);

   chk = elm_check_add(bx_opt);
   elm_object_text_set(chk, "Wheel Disabled");
   elm_check_state_set(chk, elm_scroller_wheel_disabled_get(gl));
   evas_object_size_hint_weight_set(chk, EVAS_HINT_EXPAND, 0.0);
   evas_object_smart_callback_add(chk, "changed", _gl_wheel_disabled_cb, gl);
   elm_box_pack_end(bx_opt, chk);
   evas_object_show(chk);

   // Focus Autoscroll Mode
   fr = _focus_autoscroll_mode_frame_create(bx);
   elm_box_pack_end(bx, fr);

   // Focus Movement Policy
   fr = elm_frame_add(bx);
   elm_object_text_set(fr, "Focus Movement Policy");
   evas_object_size_hint_weight_set(fr, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(fr, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(bx, fr);
   evas_object_show(fr);

   bx_mv = elm_box_add(fr);
   elm_box_horizontal_set(bx_mv, EINA_TRUE);
   elm_object_content_set(fr, bx_mv);
   evas_object_show(bx_mv);

   rdg = rd = elm_radio_add(bx_mv);
   elm_object_text_set(rd, "Focus Move by Click");
   elm_radio_state_value_set(rd, 0);
   evas_object_size_hint_weight_set(rd, EVAS_HINT_EXPAND, 0.0);
   evas_object_smart_callback_add(rd, "changed",
                                  _gl_focus_move_policy_changed_cb,
                                  NULL);
   elm_box_pack_end(bx_mv, rd);
   evas_object_show(rd);

   rd = elm_radio_add(bx_mv);
   elm_object_text_set(rd, "Focus Move by Mouse-In");
   elm_radio_group_add(rd, rdg);
   elm_radio_state_value_set(rd, 1);
   evas_object_size_hint_weight_set(rd, EVAS_HINT_EXPAND, 0.0);
   evas_object_smart_callback_add(rd, "changed",
                                  _gl_focus_move_policy_changed_cb,
                                  NULL);
   elm_box_pack_end(bx_mv, rd);
   evas_object_show(rd);

   // Options
   fr = elm_frame_add(bx);
   elm_object_text_set(fr, "Options");
   evas_object_size_hint_weight_set(fr, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(fr, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(bx, fr);
   evas_object_show(fr);

   btn_box = elm_box_add(fr);
   elm_object_content_set(fr, btn_box);
   evas_object_show(btn_box);

   btn = elm_button_add(btn_box);
   elm_object_text_set(btn, "Focus 2nd Item after 1.5 seconds.");
   evas_object_size_hint_weight_set(btn, 0.0, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(btn_box, btn);
   evas_object_show(btn);
   evas_object_smart_callback_add(btn, "clicked", _focus_btn_cb, it_2);

   btn = elm_button_add(btn_box);
   elm_object_text_set(btn, "Select 2nd Item after 1.5 seconds.");
   evas_object_size_hint_weight_set(btn, 0.0, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(btn_box, btn);
   evas_object_show(btn);
   evas_object_smart_callback_add(btn, "clicked", _sel_btn_cb, it_2);

   btn = elm_button_add(btn_box);
   elm_object_text_set(btn, "Disable 1st Item.");
   evas_object_size_hint_weight_set(btn, 0.0, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(btn_box, btn);
   evas_object_show(btn);
   evas_object_smart_callback_add(btn, "clicked", _dis_btn_cb, it_0);


   btn = elm_button_add(btn_box);
   elm_object_text_set(btn, "Add more Genlist items");
   evas_object_size_hint_weight_set(btn, 0.0, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(btn_box, btn);
   evas_object_show(btn);
   evas_object_smart_callback_add(btn, "clicked", _add_more_items_btn_cb, gl);
}

void
test_genlist_focus(void *data EINA_UNUSED,
                   Evas_Object *obj EINA_UNUSED,
                   void *event_info EINA_UNUSED)
{
   Evas_Object *win, *bx, *bx2, *gl, *btn;
   unsigned lhand, rhand;
   Elm_Object_Item *it = NULL, *it_1 = NULL, *it_2 = NULL;
   Elm_Genlist_Item_Class *itc = NULL, *itc1 = NULL, *itc2 = NULL;

   api_data *api = calloc(1, sizeof(api_data));
   win = elm_win_util_standard_add("genlist-focus", "Genlist Focus");
   elm_win_autodel_set(win, EINA_TRUE);
   evas_object_event_callback_add(win, EVAS_CALLBACK_FREE, _cleanup_cb, api);
   evas_object_event_callback_add(win, EVAS_CALLBACK_DEL,
                                  _gl_focus_win_del_cb, NULL);

   elm_win_focus_highlight_enabled_set(win, EINA_TRUE);
   elm_win_focus_highlight_animate_set(win, EINA_TRUE);

   bx = elm_box_add(win);
   evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, bx);
   evas_object_show(bx);

   btn = elm_button_add(bx);
   elm_object_text_set(btn, "Up");
   elm_box_pack_end(bx, btn);
   evas_object_smart_callback_add(btn, "clicked",
                                  _focus_button_clicked_cb, "Up");
   evas_object_show(btn);

   bx2 = elm_box_add(bx);
   elm_box_horizontal_set(bx2, EINA_TRUE);
   evas_object_size_hint_weight_set(bx2, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(bx2, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(bx, bx2);
   evas_object_show(bx2);

   btn = elm_button_add(bx2);
   elm_object_text_set(btn, "Left");
   elm_box_pack_end(bx2, btn);
   evas_object_smart_callback_add(btn, "clicked",
                                  _focus_button_clicked_cb, "Left");
   evas_object_show(btn);

   gl = elm_genlist_add(bx);
   evas_object_size_hint_weight_set(gl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(gl, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_genlist_select_mode_set(gl, ELM_OBJECT_SELECT_MODE_ALWAYS);
   elm_box_pack_end(bx2, gl);
   api->gl = gl;
   evas_object_show(gl);
   evas_object_smart_callback_add(gl, "selected", _gl_focus_item_cb, "selected");
   evas_object_smart_callback_add(gl, "unselected", _gl_focus_item_cb, "unselected");
   evas_object_smart_callback_add(gl, "activated", _gl_focus_item_cb, "activated");
   evas_object_smart_callback_add(gl, "highlighted", _gl_focus_item_cb, "highlighted");
   evas_object_smart_callback_add(gl, "unhighlighted", _gl_focus_item_cb, "unhighlighted");
   evas_object_event_callback_add(gl, EVAS_CALLBACK_KEY_DOWN, _gl_focus_key_down_cb, NULL);
   evas_object_event_callback_add(gl, EVAS_CALLBACK_MOUSE_DOWN, _gl_focus_mouse_down_cb, NULL);

   btn = elm_button_add(bx2);
   elm_object_text_set(btn, "Right");
   elm_box_pack_end(bx2, btn);
   evas_object_smart_callback_add(btn, "clicked",
                                  _focus_button_clicked_cb, "Right");
   evas_object_show(btn);

   btn = elm_button_add(bx);
   elm_object_text_set(btn, "Down");
   elm_box_pack_end(bx, btn);
   evas_object_smart_callback_add(btn, "clicked",
                                  _focus_button_clicked_cb, "Down");
   evas_object_show(btn);

   itc = elm_genlist_item_class_new();
   itc->item_style = "default";
   itc->func.text_get = gl_focus_top_items_text_get;
   itc->func.content_get = NULL;
   itc->func.state_get = NULL;
   itc->func.del = NULL;

   itc1 = elm_genlist_item_class_new();
   itc1->item_style = "default";
   itc1->func.text_get = gl_focus_text_get;
   itc1->func.content_get = gl_focus_content_get;
   itc1->func.state_get = NULL;
   itc1->func.del = NULL;

   itc2 = elm_genlist_item_class_new();
   itc2->item_style = "tree_effect";
   itc2->func.text_get = gl_focus_text_get;
   itc2->func.content_get = gl_focus_content_get;
   itc2->func.state_get = NULL;
   itc2->func.del = NULL;

   it_1 = elm_genlist_item_append(gl, itc, "do_nothing", NULL, ELM_GENLIST_ITEM_NONE,
                                  NULL, NULL);
   it_2 = elm_genlist_item_append(gl, itc, "do_nothing", NULL, ELM_GENLIST_ITEM_NONE,
                                  NULL, NULL);
   elm_genlist_item_append(gl, itc, "popup_sel", NULL, ELM_GENLIST_ITEM_NONE,
                           _gl_focus_0_item_sel_cb, NULL);
   elm_genlist_item_append(gl, itc, "popup_mouse_down", NULL, ELM_GENLIST_ITEM_NONE,
                           NULL, NULL);

   it = elm_genlist_item_append(gl, itc, "clear_on_focus", NULL, ELM_GENLIST_ITEM_NONE,
                                NULL, NULL);
   evas_object_smart_callback_add(gl, "item,focused", _gl_focus_item_focus_cb, it);
   evas_object_smart_callback_add(gl, "item,unfocused", _gl_focus_item_unfocus_cb, NULL);

   for (lhand = 0; lhand < _gl_focus_objects; lhand++)
     {
        for (rhand = 0; rhand < _gl_focus_objects; rhand++)
          {
             unsigned digit1 = lhand * 10 + rhand;
             elm_genlist_item_append(gl, itc1, (void*)(uintptr_t)digit1,
                                     NULL, ELM_GENLIST_ITEM_NONE, NULL, NULL);

             unsigned digit2 = (_gl_focus_objects - lhand -1) * 10 +
                (_gl_focus_objects - rhand -1);
             it = elm_genlist_item_append(gl, itc1, (void*)(uintptr_t)digit2,
                                          NULL, ELM_GENLIST_ITEM_NONE, NULL, NULL);
             if (rhand == 4)
               elm_object_item_disabled_set(it, EINA_TRUE);

             if (rhand == (_gl_focus_objects - 1))
               elm_genlist_item_append(gl, itc2, (void*)(uintptr_t)digit1,
                     NULL, ELM_GENLIST_ITEM_TREE, NULL, NULL);
          }
     }

   elm_genlist_item_class_free(itc);
   elm_genlist_item_class_free(itc1);
   elm_genlist_item_class_free(itc2);

   // Options
   _test_genlist_focus_option_panel_create(win, bx, gl, it_1, it_2);

   evas_object_resize(win, 420, 600);
   evas_object_show(win);
}

