AUTOMAKE_OPTIONS     = 1.4 foreign
MAINTAINERCLEANFILES = Makefile.in

include ../../Makefile_Elm_Helpers.am

EDJE_CC_FLAGS += -id $(top_srcdir)/data/themes/img -fd $(top_srcdir)/data/themes/fnt -sd $(top_srcdir)/data/themes/snd  -l $(top_srcdir)/COPYING -a $(top_srcdir)/AUTHORS

filesdir = $(datadir)/elementary/themes
files_DATA = default.edj

default.edj: Makefile $(EXTRA_DIST)
	$(AM_V_EDJ)$(EDJE_CC) \
        $(EDJE_CC_FLAGS) -fastdecomp \
	$(top_srcdir)/data/themes/default.edc \
	$(top_builddir)/data/themes/default.edj

clean-local:
	rm -f *.edj

EXTRA_DIST = \
default.edc \
\
colorclasses.edc \
fonts.edc \
macros.edc \
\
edc/about-e.edc \
edc/about-theme.edc \
edc/appmenu.edc \
edc/background.edc \
edc/backlight.edc \
edc/battery.edc \
edc/bluez4.edc \
edc/border.edc \
edc/border-icons.edc \
edc/button.edc \
edc/check.edc \
edc/clock.edc \
edc/colors.edc \
edc/colorwell.edc \
edc/comp.edc \
edc/comp_compat.edc \
edc/comp_effects.edc \
edc/conf.edc \
edc/connman.edc \
edc/cpufreq.edc \
edc/cslider.edc \
edc/desklock.edc \
edc/deskmirror.edc \
edc/deskpreview.edc \
edc/dialog.edc \
edc/edgebindings.edc \
edc/entry.edc \
edc/evrything.edc \
edc/fileman.edc \
edc/fontpreview.edc \
edc/frame.edc \
edc/gadman.edc \
edc/ibar-ibox.edc \
edc/icons.edc \
edc/ilist.edc \
edc/illume.edc \
edc/init.edc \
edc/label.edc \
edc/menu.edc \
edc/mixer.edc \
edc/music_control.edc \
edc/notification.edc \
edc/packagekit.edc \
edc/pager.edc \
edc/pager16.edc \
edc/pointer.edc \
edc/preview.edc \
edc/radio.edc \
edc/randr.edc \
edc/scrollframe.edc \
edc/shelf.edc \
edc/slider.edc \
edc/spectrum.edc \
edc/start.edc \
edc/syscon.edc \
edc/sys.edc \
edc/systray.edc \
edc/tasks.edc \
edc/temperature.edc \
edc/textblock.edc \
edc/toolbar.edc \
edc/transitions.edc \
edc/wallpaper.edc \
edc/winlist.edc \
edc/wizard.edc \
edc/xkbswitch.edc \
\
edc/elm/access.edc \
edc/elm/actionslider.edc \
edc/elm/bg.edc \
edc/elm/border.edc \
edc/elm/bubble.edc \
edc/elm/button.edc \
edc/elm/calendar.edc \
edc/elm/check.edc \
edc/elm/clock.edc \
edc/elm/colorsel.edc \
edc/elm/colorclass.edc \
edc/elm/conform.edc \
edc/elm/ctxpopup.edc \
edc/elm/cursor.edc \
edc/elm/datetime.edc \
edc/elm/dayselector.edc \
edc/elm/diskselector.edc \
edc/elm/entry.edc \
edc/elm/fileselector.edc \
edc/elm/flipselector.edc \
edc/elm/focus.edc \
edc/elm/frame.edc \
edc/elm/gengrid.edc \
edc/elm/genlist.edc \
edc/elm/hover.edc \
edc/elm/icon.edc \
edc/elm/index.edc \
edc/elm/inwin.edc \
edc/elm/label.edc \
edc/elm/layout.edc \
edc/elm/list.edc \
edc/elm/map.edc \
edc/elm/menu.edc \
edc/elm/multibuttonentry.edc \
edc/elm/naviframe.edc \
edc/elm/notify.edc \
edc/elm/panel.edc \
edc/elm/panes.edc \
edc/elm/photocam.edc \
edc/elm/photo.edc \
edc/elm/player.edc \
edc/elm/pointer.edc \
edc/elm/popup.edc \
edc/elm/progress.edc \
edc/elm/radio.edc \
edc/elm/scroller.edc \
edc/elm/segment_control.edc \
edc/elm/separator.edc \
edc/elm/slider.edc \
edc/elm/slideshow.edc \
edc/elm/spinner.edc \
edc/elm/thumb.edc \
edc/elm/toolbar.edc \
edc/elm/tooltip.edc \
edc/elm/video.edc \
edc/elm/win.edc \
\
edc/O/efm_icons.edc \
edc/O/icons.edc \
\
img/access_glow.png \
img/add_glow_small.png \
img/ball_small_glow_intense.png \
img/ball_small_glow.png \
img/bar_shine.png \
img/bat_base.png \
img/bat_bottom0.png \
img/bat_bottom1.png \
img/bat_shadow.png \
img/bat_shine.png \
img/bat_top0.png \
img/bat_top1.png \
img/bevel_curved_horiz_out.png \
img/bevel_curved_vert_out.png \
img/bevel_dark_in.png \
img/bevel_dark_out.png \
img/bevel_horiz_out.png \
img/bevel_in.png \
img/bevel_out.png \
img/bg_glow_in.png \
img/bg_radgrad.png \
img/big_arrow_down.png \
img/big_arrow_down_shadow.png \
img/big_arrow_left.png \
img/big_arrow_left_shadow.png \
img/big_arrow_right.png \
img/big_arrow_right_shadow.png \
img/big_arrow_up.png \
img/big_arrow_up_shadow.png \
img/box_glow.png \
img/box_outline.png \
img/bt_base.png \
img/bt_sig_1.png \
img/bt_sig_2.png \
img/btn_round_0.png \
img/btn_round_1.png \
img/btn_round_2.png \
img/bub_base_b0.png \
img/bub_base_b1.png \
img/bub_base_b2.png \
img/bub_base_bl.png \
img/bub_base_br.png \
img/bub_base_tl.png \
img/bub_base_tr.png \
img/bub_over_bot.png \
img/bub_over_top.png \
img/bulb_glow.png \
img/bulb_off.png \
img/bulb_on.png \
img/bulb_over.png \
img/button_clicked.png \
img/button_normal.png \
img/cell_base.png \
img/cell_sig_1.png \
img/cell_sig_2.png \
img/cell_sig_3.png \
img/cell_sig_4.png \
img/clock_base.png \
img/color_picker_alpha.png \
img/color_picker_brightness.png \
img/color_picker_color.png \
img/color_picker_opacity.png \
img/col_sel_end_bottom.png \
img/col_sel_end_left.png \
img/col_sel_end_right.png \
img/col_sel_end_top.png \
img/darken_rounded_square_half_h.png \
img/darken_rounded_square_half.png \
img/darken_rounded_square.png \
img/darken_square.png \
img/day_left_normal.png \
img/day_left_press.png \
img/day_left_selected.png \
img/day_middle_normal.png \
img/day_middle_press.png \
img/day_middle_selected.png \
img/day_right_normal.png \
img/day_right_press.png \
img/day_right_selected.png \
img/day_single_normal.png \
img/day_single_press.png \
img/day_single_selected.png \
img/diagonal_stripes.png \
img/digit_0.png \
img/digit_1.png \
img/digit_2.png \
img/digit_3.png \
img/digit_4.png \
img/digit_5.png \
img/digit_6.png \
img/digit_7.png \
img/digit_8.png \
img/digit_9.png \
img/digit_am.png \
img/digit_na.png \
img/digit_nm.png \
img/digit_pm.png \
img/dot_pattern.png \
img/downlight_glow_left.png \
img/downlight_glow.png \
img/downlight_glow_right.png \
img/downlight_glow_up.png \
img/efm_generic_icon_base_empty.png \
img/efm_generic_icon_base.png \
img/efm_generic_icon_content_audio.png \
img/efm_generic_icon_content_cad.png \
img/efm_generic_icon_content_code.png \
img/efm_generic_icon_content_db.png \
img/efm_generic_icon_content_doc.png \
img/efm_generic_icon_content_draw.png \
img/efm_generic_icon_content_executable.png \
img/efm_generic_icon_content_font.png \
img/efm_generic_icon_content_formula.png \
img/efm_generic_icon_content_image.png \
img/efm_generic_icon_content_inode_block.png \
img/efm_generic_icon_content_inode_char.png \
img/efm_generic_icon_content_inode_dir.png \
img/efm_generic_icon_content_inode_fifo.png \
img/efm_generic_icon_content_inode_file.png \
img/efm_generic_icon_content_inode_socket.png \
img/efm_generic_icon_content_install.png \
img/efm_generic_icon_content_iso.png \
img/efm_generic_icon_content_lib.png \
img/efm_generic_icon_content_logo.png \
img/efm_generic_icon_content_lo.png \
img/efm_generic_icon_content_pdf.png \
img/efm_generic_icon_content_perl.png \
img/efm_generic_icon_content_pres.png \
img/efm_generic_icon_content_ps.png \
img/efm_generic_icon_content_python.png \
img/efm_generic_icon_content_ruby.png \
img/efm_generic_icon_content_script.png \
img/efm_generic_icon_content_spread.png \
img/efm_generic_icon_content_template.png \
img/efm_generic_icon_content_text.png \
img/efm_generic_icon_content_translate.png \
img/efm_generic_icon_content_trash.png \
img/efm_generic_icon_content_unknown.png \
img/efm_generic_icon_content_video.png \
img/efm_generic_icon_content_web.png \
img/efm_generic_icon_over_empty.png \
img/efm_generic_icon_over.png \
img/efm_generic_icon_shadow_empty.png \
img/efm_generic_icon_shadow.png \
img/efm_generic_icon_content_cad.png \
img/efm_generic_icon_content_iso.png \
img/efm_generic_icon_content_lib.png \
img/efm_generic_icon_content_ruby.png \
img/efm_generic_icon_content_trash.png \
img/emo-angry.png \
img/emo-angry-shout.png \
img/emo-crazy-laugh.png \
img/emo-evil-laugh.png \
img/emo-evil.png \
img/emo-goggle-smile.png \
img/emo-grumpy.png \
img/emo-grumpy-smile.png \
img/emo-guilty.png \
img/emo-guilty-smile.png \
img/emo-haha.png \
img/emo-half-smile.png \
img/emo-happy-panting.png \
img/emo-happy.png \
img/emo-indifferent.png \
img/emo-kiss.png \
img/emo-knowing-grin.png \
img/emo-laugh.png \
img/emo-little-bit-sorry.png \
img/emo-love-lots.png \
img/emo-love.png \
img/emo-minimal-smile.png \
img/emo-not-happy.png \
img/emo-not-impressed.png \
img/emo-omg.png \
img/emo-opensmile.png \
img/emo-smile.png \
img/emo-sorry.png \
img/emo-squint-laugh.png \
img/emo-surprised.png \
img/emo-suspicious.png \
img/emo-tongue-dangling.png \
img/emo-tongue-poke.png \
img/emo-uh.png \
img/emo-unhappy.png \
img/emo-very-sorry.png \
img/emo-what.png \
img/emo-wink.png \
img/emo-worried.png \
img/emo-wtf.png \
img/eth.png \
img/exlclam.png \
img/flip_base_shad.png \
img/flip_shad.png \
img/frame_rounded.png \
img/glow_exclam.png \
img/glow_lock_double.png \
img/glow_lock_locked.png \
img/glow_lock_unlocked.png \
img/glow_med_white.png \
img/glow_round_corners.png \
img/glow_round_corners_small.png \
img/glow_small.png \
img/handle_pick_up_left.png \
img/handle_pick_up_right.png \
img/hole_pixel.png \
img/holes_horiz.png \
img/holes_tiny_glow_horiz.png \
img/holes_tiny_glow_vert.png \
img/holes_tiny_horiz.png \
img/holes_tiny_vert.png \
img/holes_vert.png \
img/hole_tiny.png \
img/home_glow.png \
img/home_hilight.png \
img/home_inset.png \
img/horiz_bar_inset.png \
img/horiz_glow_run_big.png \
img/horiz_glow_run.png \
img/horiz_glow_run_rev.png \
img/horizontal_separated_bar_glow.png \
img/horizontal_separated_bar_small_glow.png \
img/icon_apps.png \
img/icon_arrow_down_left.png \
img/icon_arrow_down.png \
img/icon_arrow_down_right.png \
img/icon_arrow_left.png \
img/icon_arrow_right.png \
img/icon_arrow_up_left.png \
img/icon_arrow_up.png \
img/icon_arrow_up_right.png \
img/icon_border_border.png \
img/icon_border_close.png \
img/icon_border_kill.png \
img/icon_border_lock.png \
img/icon_border_maximize.png \
img/icon_border_minimize.png \
img/icon_border_more.png \
img/icon_border_move.png \
img/icon_border_pager.png \
img/icon_border_pin.png \
img/icon_border_properties.png \
img/icon_border_remember.png \
img/icon_border_resize.png \
img/icon_border_sendto.png \
img/icon_border_shaded.png \
img/icon_border_skip.png \
img/icon_border_stack_bot.png \
img/icon_border_stack_norm.png \
img/icon_border_stack_top.png \
img/icon_chat.png \
img/icon_clock.png \
img/icon_close.png \
img/icon_delete.png \
img/icon_edit.png \
img/icon_eject_mono.png \
img/icon_eject.png \
img/icon_enlightenment.png \
img/icon_file.png \
img/icon_folder.png \
img/icon_forward_mono.png \
img/icon_forward.png \
img/icon_head.png \
img/icon_home.png \
img/icon_info_mono.png \
img/icon_info.png \
img/icon_mute_mono.png \
img/icon_mute.png \
img/icon_next_mono.png \
img/icon_next.png \
img/icon_pause_mono.png \
img/icon_pause.png \
img/icon_play_mono.png \
img/icon_play.png \
img/icon_preferences-applications-personal.png \
img/icon_preferences-applications-screen-lock.png \
img/icon_preferences-applications-screen-unlock.png \
img/icon_preferences-composite.png \
img/icon_preferences-desklock-locale.png \
img/icon_preferences-desktop-environments.png \
img/icon_preferences-desktop-signal-bindings.png \
img/icon_preferences-interaction.png \
img/icon_preferences-variables.png \
img/icon_prev_mono.png \
img/icon_prev.png \
img/icon_refresh.png \
img/icon_rewind_mono.png \
img/icon_rewind.png \
img/icon_search.png  \
img/icon_spanner.png  \
img/icon_splat.png \
img/icon_splat_half.png \
img/icon_stop_mono.png \
img/icon_stop.png \
img/icon_system-lock-screen.png \
img/icon_system-log-out.png \
img/icon_system.png \
img/icon_system-restart.png \
img/icon_system-shutdown.png \
img/icon_system-suspend-hibernate.png \
img/icon_system-suspend.png \
img/icon_volume_mono.png \
img/icon_volume.png \
img/icon_wallpaper_center.png \
img/icon_wallpaper_fill.png \
img/icon_wallpaper_pan.png \
img/icon_wallpaper_stretch.png \
img/icon_wallpaper_tile.png \
img/icon_wallpaper_within.png \
img/icon_warning.png \
img/ic_win_move.png \
img/ic_win_resize.png \
img/img_example_1.png \
img/img_example_2.png \
img/inset_bar_horiz_base.png \
img/inset_bar_horiz_glow_base_double.png \
img/inset_bar_horiz_glow_base.png \
img/inset_bar_horiz_glow_inv_base_double.png \
img/inset_bar_horiz_glow_inv_base.png \
img/inset_bar_horiz_glow_inv_light.png \
img/inset_bar_horiz_glow_light.png \
img/inset_bar_horiz_glow_mid_base.png \
img/inset_bar_horiz_glow_mid_light.png \
img/inset_bar_horiz_inside_base.png \
img/inset_bar_horiz_inside_light.png \
img/inset_bar_horiz_light.png \
img/inset_bar_vert_base.png \
img/inset_bar_vert_glow_base_double.png \
img/inset_bar_vert_glow_base.png \
img/inset_bar_vert_glow_inv_base_double.png \
img/inset_bar_vert_glow_inv_base.png \
img/inset_bar_vert_glow_inv_light.png \
img/inset_bar_vert_glow_light.png \
img/inset_bar_vert_glow_mid_base.png \
img/inset_bar_vert_glow_mid_light.png \
img/inset_bar_vert_inside_base.png \
img/inset_bar_vert_inside_light.png \
img/inset_bar_vert_light.png \
img/inset_circle_tiny.png \
img/inset_round_hilight.png \
img/inset_round_shading.png \
img/inset_round_shadow.png \
img/inset_shadow_circle_tiny.png \
img/inset_shadow.png \
img/inset_shadow_tiny.png \
img/kbd_glow.png \
img/kbd_hilight.png \
img/kbd_inset.png \
img/knob_round_busy.png \
img/knob_round_small_busy.png \
img/knob_round_small_normal.png \
img/knob_round_small_selected.png \
img/knob_sz_04.png \
img/knob_sz_06.png \
img/knob_sz_08.png \
img/knob_sz_10.png \
img/knob_sz_12.png \
img/knob_sz_14.png \
img/knob_sz_16.png \
img/knob_sz_18.png \
img/knob_sz_20.png \
img/knob_sz_22.png \
img/knob_sz_24.png \
img/led_dark.png \
img/led_dot_white.png \
img/led_light.png \
img/led_red_light.png \
img/led_square_base.png \
img/led_square_glow.png \
img/led_square_shading.png \
img/led_square_shadow.png \
img/led_square_shine.png \
img/led_strobe.png \
img/led_tiny_blue.png \
img/led_tiny_green.png \
img/led_tiny_orange.png \
img/logo_blue_bottom.png \
img/logo_blue_small_glow.png \
img/logo_blue_small.png \
img/map_circle.png \
img/map_marker.png \
img/map_scale.png \
img/media_busy_progress.png \
img/mini_blue_glow_arrow_0.png \
img/mini_blue_glow_arrow_1.png \
img/mini_blue_glow_arrow_2.png \
img/mini_blue_glow_arrow_3.png \
img/mini_box_bevel_shadow.png \
img/mini_box_glow.png \
img/music_control_icon.png \
img/outline_glow.png \
img/packagekit_base.png \
img/pointer_entry_bar.png \
img/pointer_glow.png \
img/pointer_mono.png \
img/pointer.png \
img/pointer_hand1.png \
img/ring_shadow.png \
img/ring_white_blue_glow.png \
img/ring_white_middle.png \
img/rounded_square.png \
img/runner_glow_horiz.png \
img/runner_glow_vert.png \
img/runner_horiz.png \
img/runner_vert.png \
img/screen_base.png \
img/screen_bg.png \
img/screen_circular_shadow.png \
img/screen_fg.png \
img/separator_horiz.png \
img/shadow_angled_in_light.png \
img/shadow_angled_in_sides.png \
img/shadow_horiz.png \
img/shadow_inset_bevels.png \
img/shadow_inset_light.png \
img/shadow_rounded_horiz.png \
img/shadow_rounded_vert.png \
img/shadow_square_tiny.png \
img/shadow_vertical_dark.png \
img/shadow_vert.png \
img/shine.png \
img/slider_run_base_horiz.png \
img/slider_run_base_light_horiz.png \
img/slider_run_base_light_vert.png \
img/slider_run_base_vert.png \
img/slider_run_bevel_horiz.png \
img/slider_run_bevel_vert.png \
img/slot_horiz_bottom.png \
img/slot_horiz_top.png \
img/spanner_glow.png \
img/spanner_hilight.png \
img/spanner_inset.png \
img/speaker.png \
img/split_h_glow.png \
img/split_h_hilight.png \
img/split_h_inset.png \
img/split_none_glow.png \
img/split_none_hilight.png \
img/split_none_inset.png \
img/split_v_glow.png \
img/split_v_hilight.png \
img/split_v_inset.png \
img/sym_check_alum.png \
img/sym_close_dark_normal.png \
img/sym_close_dark_selected.png \
img/sym_close_light_normal.png \
img/sym_close_light_selected.png \
img/sym_down_dark_normal.png \
img/sym_down_dark_selected.png \
img/sym_down_glow_normal.png \
img/sym_down_light_normal.png \
img/sym_down_light_selected.png \
img/sym_heart_glow_normal.png \
img/sym_heart_light_normal.png \
img/sym_icon_op_ask.png \
img/sym_icon_op_copy.png \
img/sym_icon_op_move.png \
img/sym_left_dark_normal.png \
img/sym_left_glow_normal.png \
img/sym_left_light_normal.png \
img/sym_radio_alum.png \
img/sym_reload_glow_normal.png \
img/sym_reload_light_normal.png \
img/sym_right_dark_normal.png \
img/sym_right_glow_normal.png \
img/sym_right_light_normal.png \
img/sym_up_dark_normal.png \
img/sym_up_dark_selected.png \
img/sym_up_glow_normal.png \
img/sym_up_light_normal.png \
img/sym_up_light_selected.png \
img/tacho_base.png \
img/tacho_hand_big2.png \
img/tacho_hand_big3.png \
img/tacho_hand_big4.png \
img/tacho_hand_big.png \
img/tacho_hand_big_shadow.png \
img/tacho_hand_small_min2.png \
img/tacho_hand_small_min3.png \
img/tacho_hand_small_min4.png \
img/tacho_hand_small_min.png \
img/tacho_hand_small_shadow.png \
img/therm_content.png \
img/therm_shadow.png \
img/therm_shine.png \
img/tooltip-base.png \
img/tooltip-corner-bottom-left-tip.png \
img/tooltip-corner-bottom-right-tip.png \
img/tooltip-corner-top-left-tip.png \
img/tooltip-corner-top-right-tip.png \
img/tooltip-edge-bottom-tip.png \
img/tooltip-edge-left-tip.png \
img/tooltip-edge-right-tip.png \
img/tooltip-edge-top-tip.png \
img/vert_bar_inset.png \
img/vert_glow_run.png \
img/vert_glow_run_rev.png \
img/vertical_separated_bar_glow.png \
img/vgrad_med_curved.png \
img/vgrad_med_darker.png \
img/vgrad_med_dark.png \
img/vgrad_med_dark_sparkle.png \
img/vgrad_med_lighter.png \
img/vgrad_med_lighter_sparkle.png \
img/vgrad_med.png \
img/vgrad_shadow_bi.png \
img/vgrad_tall.png \
img/white_bar_vert_glow.png \
img/wifi_base.png \
img/wifi_sig_1.png \
img/wifi_sig_2.png \
img/wifi_sig_3.png \
img/win_glow.png \
img/win_shadow.png \
\
img/O/about_bot.png \
img/O/about_mid.png \
img/O/about_top.png \
img/O/arrow_down.png \
img/O/arrow_up.png \
img/O/batt_base.png \
img/O/batt_level.png \
img/O/batt_over.png \
img/O/batt_power.png \
img/O/bg_shadow.png \
img/O/big_arrow_up.png \
img/O/bnw.png \
img/O/bt_base1.png \
img/O/bt_base2.png \
img/O/bt_dis_base.png \
img/O/bt_dis_hilight.png \
img/O/bt_dis_shine.png \
img/O/bt_glow.png \
img/O/bt_hilight.png \
img/O/bt_shine.png \
img/O/bt_sm_base1.png \
img/O/bt_sm_base2.png \
img/O/bt_sm_hilight.png \
img/O/bt_sm_shine.png \
img/O/bulb-0.png \
img/O/bulb-1.png \
img/O/bulb-2.png \
img/O/busy-1.png \
img/O/busy-2.png \
img/O/busy-3.png \
img/O/busy-4.png \
img/O/busy-5.png \
img/O/busy-6.png \
img/O/busy-7.png \
img/O/busy-8.png \
img/O/busy-9.png \
img/O/dia_botshad.png \
img/O/dia_grad.png \
img/O/e17_mini_button_shadow2.png \
img/O/everything_box.png \
img/O/everything_item_bg.png \
img/O/exq-bglight.png \
img/O/exq-dot-glow.png \
img/O/exq-dot.png \
img/O/exq-logo.png \
img/O/exq-vgrad.png \
img/O/gadman_border.png \
img/O/gadman_bottom.png \
img/O/gadman_frame.png \
img/O/gadman_left.png \
img/O/gadman_right.png \
img/O/gadman_top.png \
img/O/glow.png \
img/O/icon_active.png \
img/O/icon_add_fav.png \
img/O/icon_add.png \
img/O/icon_advanced.png \
img/O/icon_applications_ibar.png \
img/O/icon_applications_new.png \
img/O/icon_applications.png \
img/O/icon_applications_restart.png \
img/O/icon_applications_startup.png \
img/O/icon_autoscroll.png \
img/O/icon_behavior.png \
img/O/icon_border_border.png \
img/O/icon_border_close.png \
img/O/icon_border_kill.png \
img/O/icon_border_lock.png \
img/O/icon_border_maximize.png \
img/O/icon_border_minimize.png \
img/O/icon_border_more.png \
img/O/icon_border_pager.png \
img/O/icon_border_pin.png \
img/O/icon_border_properties.png \
img/O/icon_border_remember.png \
img/O/icon_border_sendto.png \
img/O/icon_border_shaded.png \
img/O/icon_border_skip.png \
img/O/icon_border_stack_bot.png \
img/O/icon_border_stack_norm.png \
img/O/icon_border_stack_top.png \
img/O/icon_check.png \
img/O/icon_close.png \
img/O/icon_colors.png \
img/O/icon_config.png \
img/O/icon_configuration.png \
img/O/icon_del.png \
img/O/icon_desklock_menu.png \
img/O/icon_desklock.png \
img/O/icon_desktops.png \
img/O/icon_directories.png \
img/O/icon_down_arrow.png \
img/O/icon_dummy.png \
img/O/icon_efm_arrange_name.png \
img/O/icon_efm_arrange.png \
img/O/icon_efm_arrange_time.png \
img/O/icon_efm_cd.png \
img/O/icon_efm_copy.png \
img/O/icon_efm_cut.png \
img/O/icon_efm_delete.png \
img/O/icon_efm_desktop.png \
img/O/icon_efm_dnd_ask.png \
img/O/icon_efm_dnd_copy.png \
img/O/icon_efm_dnd_move.png \
img/O/icon_efm_eject.png \
img/O/icon_efm_file_del.png \
img/O/icon_efm_file.png \
img/O/icon_efm_flash.png \
img/O/icon_efm_folder.png \
img/O/icon_efm_hdd.png \
img/O/icon_efm_home.png \
img/O/icon_efm_new_dir.png \
img/O/icon_efm_new.png \
img/O/icon_efm_open.png \
img/O/icon_efm_paste.png \
img/O/icon_efm_properties.png \
img/O/icon_efm_refresh.png \
img/O/icon_efm_rename.png \
img/O/icon_efm_root.png \
img/O/icon_efm_select.png \
img/O/icon_efm_sort.png \
img/O/icon_efm_tmp.png \
img/O/icon_efm_usbmedia.png \
img/O/icon_efm_view_details.png \
img/O/icon_efm_view_name.png \
img/O/icon_efm_view.png \
img/O/icon_efm_vol_mounted.png \
img/O/icon_efm_vol_unmounted.png \
img/O/icon_engine.png \
img/O/icon_evry_clipboard.png \
img/O/icon_extensions.png \
img/O/icon_favorites.png \
img/O/icon_file_icons.png \
img/O/icon_fonts.png \
img/O/icon_gadget.png \
img/O/icon_globe.png \
img/O/icon_gradient.png \
img/O/icon_halt.png \
img/O/icon_hibernate.png \
img/O/icon_icon_theme.png \
img/O/icon_illume.png \
img/O/icon_imc.png \
img/O/icon_interaction.png \
img/O/icon_intl.png \
img/O/icon_keyboard.png \
img/O/icon_keys.png \
img/O/icon_left_arrow.png \
img/O/icon_logout.png \
img/O/icon_look.png \
img/O/icon_lost_windows.png \
img/O/icon_menu_settings.png \
img/O/icon_menus.png \
img/O/icon_mime_audio_generic.png \
img/O/icon_mime_bdf.png \
img/O/icon_mime_c.png \
img/O/icon_mime_css.png \
img/O/icon_mime_deb.png \
img/O/icon_mime_doc.png \
img/O/icon_mime_executable_generic.png \
img/O/icon_mime_font_generic.png \
img/O/icon_mime_h.png \
img/O/icon_mime_html.png \
img/O/icon_mime_image_generic.png \
img/O/icon_mime_o.png \
img/O/icon_mime_package.png \
img/O/icon_mime_patch.png \
img/O/icon_mime_pcf.png \
img/O/icon_mime_pdf.png \
img/O/icon_mime_plain.png \
img/O/icon_mime_sh.png \
img/O/icon_mime_text_generic.png \
img/O/icon_mime_ttf.png \
img/O/icon_mime_video_generic.png \
img/O/icon_mime_xcf.png \
img/O/icon_mixer.png \
img/O/icon_modules.png \
img/O/icon_mouse_clean.png \
img/O/icon_mouse_extra.png \
img/O/icon_mouse_left.png \
img/O/icon_mouse_middle.png \
img/O/icon_mouse.png \
img/O/icon_mouse_right.png \
img/O/icon_mouse_wheel.png \
img/O/icon_new.png \
img/O/icon_pager.png \
img/O/icon_performance.png \
img/O/icon_power_management.png \
img/O/icon_profiles.png \
img/O/icon_reboot.png \
img/O/icon_reset.png \
img/O/icon_resize.png \
img/O/icon_right_arrow.png \
img/O/icon_run.png \
img/O/icon_scale.png \
img/O/icon_screen_around.png \
img/O/icon_screen_hflip.png \
img/O/icon_screen_left.png \
img/O/icon_screen_normal.png \
img/O/icon_screen_resolution.png \
img/O/icon_screen_right.png \
img/O/icon_screensaver.png \
img/O/icon_screen_setup.png \
img/O/icon_screenshot.png \
img/O/icon_screen_vflip.png \
img/O/icon_shelf_bottom_desk.png \
img/O/icon_shelf_bottom_left.png \
img/O/icon_shelf_bottom.png \
img/O/icon_shelf_bottom_right.png \
img/O/icon_shelf_custom.png \
img/O/icon_shelf_dock.png \
img/O/icon_shelf_left_bottom.png \
img/O/icon_shelf_left.png \
img/O/icon_shelf_left_top.png \
img/O/icon_shelf_menu_bar.png \
img/O/icon_shelf_panel.png \
img/O/icon_shelf.png \
img/O/icon_shelf_right_bottom.png \
img/O/icon_shelf_right.png \
img/O/icon_shelf_right_top.png \
img/O/icon_shelf_top_desk.png \
img/O/icon_shelf_top_left.png \
img/O/icon_shelf_top.png \
img/O/icon_shelf_top_right.png \
img/O/icon_startup.png \
img/O/icon_suspend.png \
img/O/icon_swap.png \
img/O/icon_system.png \
img/O/icon_theme.png \
img/O/icon_toolbar.png \
img/O/icon_transitions.png \
img/O/icon_up_arrow.png \
img/O/icon_wallpaper_center_flat.png \
img/O/icon_wallpaper_center.png \
img/O/icon_wallpaper_grad_screen.png \
img/O/icon_wallpaper.png \
img/O/icon_wallpaper_screen.png \
img/O/icon_warning.png \
img/O/icon_window_focus.png \
img/O/icon_window_geometry.png \
img/O/icon_window_manipulation.png \
img/O/icon_window_process_management.png \
img/O/icon_window_remembers.png \
img/O/icon_windows.png \
img/O/icon_winlist.png \
img/O/icon_win_move.png \
img/O/icon_win_resize.png \
img/O/illume-home.png \
img/O/illume-kbd-on.png \
img/O/illume-kbd.png \
img/O/illume-mode-dual-left.png \
img/O/illume-mode-dual-top.png \
img/O/illume-mode-single.png \
img/O/inset_raised.png \
img/O/inset_sunk.png \
img/O/logo_black_128.png \
img/O/logo_white_128.png \
img/O/mixer_high_left.png \
img/O/mixer_high_right.png \
img/O/mixer_low_left.png \
img/O/mixer_low_right.png \
img/O/mixer_med_left.png \
img/O/mixer_med_right.png \
img/O/mixer.png \
img/O/outline.png \
img/O/randr_icon_off.png \
img/O/randr_icon_on.png \
img/O/randr_monitor.png \
img/O/randr_stand.png \
img/O/sb_runnerh.png \
img/O/sb_runnerv.png \
img/O/silk.png \
img/O/t0.png \
img/O/t0-sh.png \
img/O/t1.png \
img/O/t1-sh.png \
img/O/t2.png \
img/O/tacho_bg.png \
img/O/tacho_fg.png \
img/O/temp_base.png \
img/O/temp_mid.png \
img/O/temp_over.png \
img/O/theme-label.png \
img/O/toolbar_sel.png \
img/O/topsh.png \
img/O/transition_vswipe.png \
img/O/vgrad_dark.png \
img/O/vgrad_light.png \
img/O/wizard_bt1.png \
img/O/wizard_bt2.png \
img/O/wizard_pattern.png \
img/O/wp-bot1.png \
img/O/wp-bot2.png \
img/O/wp-tb1.png \
img/O/wp-tb2.png \
img/O/wp-tb3.png \
img/O/wp-tbs.png \
\
snd/kbd-tap2.wav \
snd/kbd-tap3.wav \
snd/kbd-tap4.wav \
snd/kbd-tap5.wav \
snd/kbd-tap.wav
