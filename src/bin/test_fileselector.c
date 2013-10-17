#ifdef HAVE_CONFIG_H
# include "elementary_config.h"
#endif


#include <Elementary.h>
#ifndef ENABLE_NLS
# ifndef setlocale
#  define setlocale(c, l)
# endif
# ifndef libintl_setlocale
#  define libintl_setlocale(c, l)
# endif
#endif

#include <Elementary.h>
#ifndef ELM_LIB_QUICKLAUNCH
static void
my_fileselector_done(void            *data,
                     Evas_Object *obj EINA_UNUSED,
                     void            *event_info)
{
   /* event_info conatin the full path of the selected file
    * or NULL if none is selected or cancel is pressed */
    const char *selected = event_info;

    if (selected)
      printf("Selected file: %s\n", selected);
    else
      evas_object_del(data);  /* delete the test window */
}

static void
my_fileselector_selected(void *data   EINA_UNUSED,
                         Evas_Object *obj,
                         void        *event_info)
{
   /* event_info conatin the full path of the selected file */
   const char *selected = event_info;
   printf("Selected file: %s\n", selected);

   /* or you can query the selection */
   if (elm_fileselector_multi_select_get(obj))
     {
        const Eina_List *li;
        const Eina_List *paths = elm_fileselector_selected_paths_get(obj);
        char *path;
        printf("All selected files are:\n");
        EINA_LIST_FOREACH(paths, li, path)
          printf(" %s\n", path);
     }
   else
     printf("or: %s\n", elm_fileselector_selected_get(obj));
}

static void
_popup_close_cb(void *data, Evas_Object *obj EINA_UNUSED,
                void *event_info EINA_UNUSED)
{
   evas_object_del(data);
}

static void
my_fileselector_invalid(void *data   EINA_UNUSED,
                        Evas_Object *obj EINA_UNUSED,
                        void        *event_info)
{
   Evas_Object *popup;
   Evas_Object *btn;
   char error_msg[256];

   snprintf(error_msg, 256, "No such file or directory: %s", (char *)event_info);

   popup = elm_popup_add(data);
   elm_popup_content_text_wrap_type_set(popup, ELM_WRAP_CHAR);
   elm_object_part_text_set(popup, "title,text", "Error");
   elm_object_text_set(popup, error_msg);

   btn = elm_button_add(popup);
   elm_object_text_set(btn, "OK");
   elm_object_part_content_set(popup, "button1", btn);
   evas_object_smart_callback_add(btn, "clicked", _popup_close_cb, popup);

   evas_object_show(popup);
}

static void
my_fileselector_activated(void *data EINA_UNUSED,
                          Evas_Object *obj EINA_UNUSED,
                          void *event_info)
{
   printf("Activated file: %s\n", (char *)event_info);
}

static void
_is_save_clicked(void            *data,
                 Evas_Object *obj EINA_UNUSED,
                 void *event_info EINA_UNUSED)
{
   Evas_Object *fs = data;
   printf("Toggle Is save\n");
   if (elm_fileselector_is_save_get(fs))
     elm_fileselector_is_save_set(fs, EINA_FALSE);
   else
     elm_fileselector_is_save_set(fs, EINA_TRUE);
}

static void
_folder_only_clicked(void            *data,
                     Evas_Object *obj EINA_UNUSED,
                     void *event_info EINA_UNUSED)
{
   Evas_Object *fs = data;
   printf("Toggle Folder only\n");
   if (elm_fileselector_folder_only_get(fs))
     elm_fileselector_folder_only_set(fs, EINA_FALSE);
   else
     elm_fileselector_folder_only_set(fs, EINA_TRUE);
}

static void
_expandable_clicked(void            *data,
                    Evas_Object *obj EINA_UNUSED,
                    void *event_info EINA_UNUSED)
{
   Evas_Object *fs = data;
   printf("Toggle Expandable\n");
   if (elm_fileselector_expandable_get(fs))
     elm_fileselector_expandable_set(fs, EINA_FALSE);
   else
     elm_fileselector_expandable_set(fs, EINA_TRUE);
}

static void
_multi_clicked(void            *data,
               Evas_Object *obj EINA_UNUSED,
               void *event_info EINA_UNUSED)
{
   Evas_Object *fs = data;
   Eina_Bool enabled = elm_fileselector_multi_select_get(fs);
   printf("Toggle Multiple selection to: %s\n", !enabled ? "On" : "Off");
   elm_fileselector_multi_select_set(fs, !enabled);
}

static void
_buttons_clicked(void            *data,
                    Evas_Object *obj EINA_UNUSED,
                    void *event_info EINA_UNUSED)
{
   Evas_Object *fs = data;
   printf("Toggle Buttons\n");
   if (elm_fileselector_buttons_ok_cancel_get(fs))
     elm_fileselector_buttons_ok_cancel_set(fs, EINA_FALSE);
   else
     elm_fileselector_buttons_ok_cancel_set(fs, EINA_TRUE);
}

static void
_sel_get_clicked(void            *data,
                 Evas_Object *obj EINA_UNUSED,
                 void *event_info EINA_UNUSED)
{
   Evas_Object *fs = data;
   printf("Get Selected: %s\n", elm_fileselector_selected_get(fs));
}

static void
_path_get_clicked(void            *data,
                  Evas_Object *obj EINA_UNUSED,
                  void *event_info EINA_UNUSED)
{
   Evas_Object *fs = data;
   printf("Get Path: %s\n", elm_fileselector_path_get(fs));
}

static void
_mode_cycle_clicked(void            *data,
                    Evas_Object *obj EINA_UNUSED,
                    void *event_info EINA_UNUSED)
{
   Evas_Object *fs = data;
   Elm_Fileselector_Mode mode;

   mode = (elm_fileselector_mode_get(fs) + 1) % ELM_FILESELECTOR_LAST;
   elm_fileselector_mode_set(fs, mode);

   printf("Setting mode to: %d\n", mode);
}

void
test_fileselector(void *data       EINA_UNUSED,
                  Evas_Object *obj EINA_UNUSED,
                  void *event_info EINA_UNUSED)
{
   Evas_Object *win, *fs, *vbox, *hbox, *bt, *sep;

   /* Set the locale according to the system pref.
    * If you dont do so the file selector will order the files list in
    * a case sensitive manner
    */
   setlocale(LC_ALL, "");

   elm_need_ethumb();
   elm_need_efreet();

   win = elm_win_util_standard_add("fileselector", "File Selector");
   elm_win_autodel_set(win, EINA_TRUE);

   vbox = elm_box_add(win);
   evas_object_size_hint_weight_set(vbox, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, vbox);
   evas_object_show(vbox);

   fs = elm_fileselector_add(win);
   /* enable the fs file name entry */
   elm_fileselector_is_save_set(fs, EINA_TRUE);
   /* make the file list a tree with dir expandable in place */
   elm_fileselector_expandable_set(fs, EINA_FALSE);
   /* start the fileselector in the home dir */
   elm_fileselector_path_set(fs, getenv("HOME"));
   elm_fileselector_mime_types_filter_append(fs, "text/*", "Text Files");
   elm_fileselector_mime_types_filter_append(fs, "image/*", "Image Files");

   /* allow fs to expand in x & y */
   evas_object_size_hint_weight_set(fs, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(fs, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(vbox, fs);
   evas_object_show(fs); // TODO fix this is the widget

   /* the 'done' cb is called when the user press ok/cancel */
   evas_object_smart_callback_add(fs, "done", my_fileselector_done, win);
   /* the 'selected' cb is called when the user click on a file/dir */
   evas_object_smart_callback_add(fs, "selected", my_fileselector_selected,
                                  win);
   evas_object_smart_callback_add(fs, "selected,invalid",
                                  my_fileselector_invalid, win);
   evas_object_smart_callback_add(fs, "activated", my_fileselector_activated,
                                  win);

   /* test buttons */
   sep = elm_separator_add(win);
   elm_separator_horizontal_set(sep, EINA_TRUE);
   elm_box_pack_end(vbox, sep);
   evas_object_show(sep);

   hbox = elm_box_add(win);
   elm_box_horizontal_set(hbox, EINA_TRUE);
   elm_box_pack_end(vbox, hbox);
   evas_object_show(hbox);

   bt = elm_check_add(win);
   elm_object_text_set(bt, "is save");
   elm_check_state_set(bt, elm_fileselector_is_save_get(fs));
   evas_object_smart_callback_add(bt, "changed", _is_save_clicked, fs);
   elm_box_pack_end(hbox, bt);
   evas_object_show(bt);

   bt = elm_check_add(win);
   elm_object_text_set(bt, "folder only");
   elm_check_state_set(bt, elm_fileselector_folder_only_get(fs));
   evas_object_smart_callback_add(bt, "changed", _folder_only_clicked, fs);
   elm_box_pack_end(hbox, bt);
   evas_object_show(bt);

   bt = elm_check_add(win);
   elm_object_text_set(bt, "expandable");
   elm_check_state_set(bt, elm_fileselector_expandable_get(fs));
   evas_object_smart_callback_add(bt, "changed", _expandable_clicked, fs);
   elm_box_pack_end(hbox, bt);
   evas_object_show(bt);

   bt = elm_check_add(win);
   elm_object_text_set(bt, "multiple selection");
   elm_check_state_set(bt, elm_fileselector_multi_select_get(fs));
   evas_object_smart_callback_add(bt, "changed", _multi_clicked, fs);
   elm_box_pack_end(hbox, bt);
   evas_object_show(bt);

   bt = elm_check_add(win);
   elm_object_text_set(bt, "buttons");
   elm_check_state_set(bt, elm_fileselector_buttons_ok_cancel_get(fs));
   evas_object_smart_callback_add(bt, "changed", _buttons_clicked, fs);
   elm_box_pack_end(hbox, bt);
   evas_object_show(bt);

   hbox = elm_box_add(win);
   elm_box_horizontal_set(hbox, EINA_TRUE);
   elm_box_pack_end(vbox, hbox);
   evas_object_show(hbox);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "selected get");
   evas_object_smart_callback_add(bt, "clicked", _sel_get_clicked, fs);
   elm_box_pack_end(hbox, bt);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "path get");
   evas_object_smart_callback_add(bt, "clicked", _path_get_clicked, fs);
   elm_box_pack_end(hbox, bt);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "mode cycle");
   evas_object_smart_callback_add(bt, "clicked", _mode_cycle_clicked, fs);
   elm_box_pack_end(hbox, bt);
   evas_object_show(bt);

   evas_object_resize(win, 320, 500);
   evas_object_show(win);
}

#endif
