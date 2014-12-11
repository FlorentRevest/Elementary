
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

// EAPI void register_elm_win(v8::Handle<v8::Object> global, v8::Isolate* isolate);
// EAPI void register_elm_bg(v8::Handle<v8::Object> global, v8::Isolate* isolate);
// EAPI void register_elm_button(v8::Handle<v8::Object> global, v8::Isolate* isolate);
// EAPI void register_elm_access(v8::Handle<v8::Object> global, v8::Isolate* isolate);
// EAPI void register_elm_actionslider(v8::Handle<v8::Object> global, v8::Isolate* isolate);
// EAPI void register_elm_app(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_access(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_actionslider(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_app_client(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_app_client_view(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_app_server(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_app_server_view(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_atspi_app_object(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_bg(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_box(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_bubble(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_button(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_calendar(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_check(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_clock(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_colorselector(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_conformant(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_container(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_ctxpopup(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_datetime(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_dayselector(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_diskselector(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_entry(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_fileselector(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_fileselector_button(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_fileselector_entry(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_flip(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_flipselector(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_frame(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_gengrid(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_gengrid_pan(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_genlist(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_genlist_pan(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_gesture_layer(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_glview(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_grid(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_hover(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_hoversel(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_icon(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_image(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_index(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_interface_atspi_accessible(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_interface_atspi_action(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_interface_atspi_component(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_interface_atspi_editable_text(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_interface_atspi_image(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_interface_atspi_selection(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_interface_atspi_text(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_interface_atspi_value(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_interface_atspi_widget(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_interface_atspi_widget_action(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_interface_atspi_window(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_interface_fileselector(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_interface_scrollable(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_inwin(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_label(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_layout(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_list(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_map(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_map_pan(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_mapbuf(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_menu(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_multibuttonentry(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_naviframe(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_notify(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_pan(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_panel(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_panes(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_photo(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_photocam(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_photocam_pan(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_player(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_plug(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_popup(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_prefs(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_progressbar(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_radio(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_route(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_scroller(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_segment_control(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_separator(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_slider(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_slideshow(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_spinner(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_systray(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_table(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_thumb(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_toolbar(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_video(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_web(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_widget(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_win(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_widget_item(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_color_item(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_dayselector_item(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_hoversel_item(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_segment_control_item(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_slideshow_item(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_flipselector_item(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_menu_item(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_ctxpopup_item(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_index_item(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_multibuttonentry_item(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_naviframe_item(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_genlist_item(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_gengrid_item(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_list_item(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_toolbar_item(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_diskselector_item(v8::Handle<v8::Object> global, v8::Isolate* isolate);
EAPI void register_elm_popup_item(v8::Handle<v8::Object> global, v8::Isolate* isolate);

namespace {

// Ecore_Evas* ee;
  
void init(v8::Handle<v8::Object> exports)
{
  std::cout << "init hey " << std::endl;
  static char* argv[] = {"node"};
  ::elm_init(1, argv);
  
  try
    {
      register_elm_access(exports, v8::Isolate::GetCurrent());
      register_elm_actionslider(exports, v8::Isolate::GetCurrent());
      register_elm_app_client(exports, v8::Isolate::GetCurrent());
      register_elm_app_client_view(exports, v8::Isolate::GetCurrent());
      register_elm_app_server(exports, v8::Isolate::GetCurrent());
      register_elm_app_server_view(exports, v8::Isolate::GetCurrent());
      register_elm_atspi_app_object(exports, v8::Isolate::GetCurrent());
      register_elm_bg(exports, v8::Isolate::GetCurrent());
      register_elm_box(exports, v8::Isolate::GetCurrent());
      register_elm_bubble(exports, v8::Isolate::GetCurrent());
      register_elm_button(exports, v8::Isolate::GetCurrent());
      register_elm_calendar(exports, v8::Isolate::GetCurrent());
      register_elm_check(exports, v8::Isolate::GetCurrent());
      register_elm_clock(exports, v8::Isolate::GetCurrent());
      register_elm_colorselector(exports, v8::Isolate::GetCurrent());
      register_elm_conformant(exports, v8::Isolate::GetCurrent());
      register_elm_container(exports, v8::Isolate::GetCurrent());
      register_elm_ctxpopup(exports, v8::Isolate::GetCurrent());
      register_elm_datetime(exports, v8::Isolate::GetCurrent());
      register_elm_dayselector(exports, v8::Isolate::GetCurrent());
      register_elm_diskselector(exports, v8::Isolate::GetCurrent());
      register_elm_entry(exports, v8::Isolate::GetCurrent());
      register_elm_fileselector(exports, v8::Isolate::GetCurrent());
      register_elm_fileselector_button(exports, v8::Isolate::GetCurrent());
      register_elm_fileselector_entry(exports, v8::Isolate::GetCurrent());
      register_elm_flip(exports, v8::Isolate::GetCurrent());
      register_elm_flipselector(exports, v8::Isolate::GetCurrent());
      register_elm_frame(exports, v8::Isolate::GetCurrent());
      register_elm_gengrid(exports, v8::Isolate::GetCurrent());
      register_elm_gengrid_pan(exports, v8::Isolate::GetCurrent());
      register_elm_genlist(exports, v8::Isolate::GetCurrent());
      register_elm_genlist_pan(exports, v8::Isolate::GetCurrent());
      register_elm_gesture_layer(exports, v8::Isolate::GetCurrent());
      register_elm_glview(exports, v8::Isolate::GetCurrent());
      register_elm_grid(exports, v8::Isolate::GetCurrent());
      register_elm_hover(exports, v8::Isolate::GetCurrent());
      register_elm_hoversel(exports, v8::Isolate::GetCurrent());
      register_elm_icon(exports, v8::Isolate::GetCurrent());
      register_elm_image(exports, v8::Isolate::GetCurrent());
      register_elm_index(exports, v8::Isolate::GetCurrent());
      register_elm_interface_atspi_accessible(exports, v8::Isolate::GetCurrent());
      register_elm_interface_atspi_action(exports, v8::Isolate::GetCurrent());
      register_elm_interface_atspi_component(exports, v8::Isolate::GetCurrent());
      register_elm_interface_atspi_editable_text(exports, v8::Isolate::GetCurrent());
      register_elm_interface_atspi_image(exports, v8::Isolate::GetCurrent());
      register_elm_interface_atspi_selection(exports, v8::Isolate::GetCurrent());
      register_elm_interface_atspi_text(exports, v8::Isolate::GetCurrent());
      register_elm_interface_atspi_value(exports, v8::Isolate::GetCurrent());
      register_elm_interface_atspi_widget(exports, v8::Isolate::GetCurrent());
      register_elm_interface_atspi_widget_action(exports, v8::Isolate::GetCurrent());
      register_elm_interface_atspi_window(exports, v8::Isolate::GetCurrent());
      register_elm_interface_fileselector(exports, v8::Isolate::GetCurrent());
      register_elm_interface_scrollable(exports, v8::Isolate::GetCurrent());
      register_elm_inwin(exports, v8::Isolate::GetCurrent());
      register_elm_label(exports, v8::Isolate::GetCurrent());
      register_elm_layout(exports, v8::Isolate::GetCurrent());
      register_elm_list(exports, v8::Isolate::GetCurrent());
      register_elm_map(exports, v8::Isolate::GetCurrent());
      register_elm_map_pan(exports, v8::Isolate::GetCurrent());
      register_elm_mapbuf(exports, v8::Isolate::GetCurrent());
      register_elm_menu(exports, v8::Isolate::GetCurrent());
      register_elm_multibuttonentry(exports, v8::Isolate::GetCurrent());
      register_elm_naviframe(exports, v8::Isolate::GetCurrent());
      register_elm_notify(exports, v8::Isolate::GetCurrent());
      register_elm_pan(exports, v8::Isolate::GetCurrent());
      register_elm_panel(exports, v8::Isolate::GetCurrent());
      register_elm_panes(exports, v8::Isolate::GetCurrent());
      register_elm_photo(exports, v8::Isolate::GetCurrent());
      register_elm_photocam(exports, v8::Isolate::GetCurrent());
      register_elm_photocam_pan(exports, v8::Isolate::GetCurrent());
      register_elm_player(exports, v8::Isolate::GetCurrent());
      register_elm_plug(exports, v8::Isolate::GetCurrent());
      register_elm_popup(exports, v8::Isolate::GetCurrent());
      register_elm_prefs(exports, v8::Isolate::GetCurrent());
      register_elm_progressbar(exports, v8::Isolate::GetCurrent());
      register_elm_radio(exports, v8::Isolate::GetCurrent());
      register_elm_route(exports, v8::Isolate::GetCurrent());
      register_elm_scroller(exports, v8::Isolate::GetCurrent());
      register_elm_segment_control(exports, v8::Isolate::GetCurrent());
      register_elm_separator(exports, v8::Isolate::GetCurrent());
      register_elm_slider(exports, v8::Isolate::GetCurrent());
      register_elm_slideshow(exports, v8::Isolate::GetCurrent());
      register_elm_spinner(exports, v8::Isolate::GetCurrent());
      register_elm_systray(exports, v8::Isolate::GetCurrent());
      register_elm_table(exports, v8::Isolate::GetCurrent());
      register_elm_thumb(exports, v8::Isolate::GetCurrent());
      register_elm_toolbar(exports, v8::Isolate::GetCurrent());
      register_elm_video(exports, v8::Isolate::GetCurrent());
      register_elm_web(exports, v8::Isolate::GetCurrent());
      register_elm_widget(exports, v8::Isolate::GetCurrent());
      register_elm_win(exports, v8::Isolate::GetCurrent());
      register_elm_widget_item(exports, v8::Isolate::GetCurrent());
      register_elm_color_item(exports, v8::Isolate::GetCurrent());
      register_elm_dayselector_item(exports, v8::Isolate::GetCurrent());
      register_elm_hoversel_item(exports, v8::Isolate::GetCurrent());
      register_elm_segment_control_item(exports, v8::Isolate::GetCurrent());
      register_elm_slideshow_item(exports, v8::Isolate::GetCurrent());
      register_elm_flipselector_item(exports, v8::Isolate::GetCurrent());
      register_elm_menu_item(exports, v8::Isolate::GetCurrent());
      register_elm_ctxpopup_item(exports, v8::Isolate::GetCurrent());
      register_elm_index_item(exports, v8::Isolate::GetCurrent());
      register_elm_multibuttonentry_item(exports, v8::Isolate::GetCurrent());
      register_elm_naviframe_item(exports, v8::Isolate::GetCurrent());
      register_elm_genlist_item(exports, v8::Isolate::GetCurrent());
      register_elm_gengrid_item(exports, v8::Isolate::GetCurrent());
      register_elm_list_item(exports, v8::Isolate::GetCurrent());
      register_elm_toolbar_item(exports, v8::Isolate::GetCurrent());
      register_elm_diskselector_item(exports, v8::Isolate::GetCurrent());
      register_elm_popup_item(exports, v8::Isolate::GetCurrent());
    }
  catch(...)
    {
      std::cout << "Exception" << std::endl;
    }

  std::cout << "inited " << std::endl;

  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
}
  
}

NODE_MODULE(elm, init)


