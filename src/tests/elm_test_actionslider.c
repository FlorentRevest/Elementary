#ifdef HAVE_CONFIG_H
# include "elementary_config.h"
#endif

#define ELM_INTERFACE_ATSPI_ACCESSIBLE_PROTECTED
#include <Elementary.h>
#include "elm_suite.h"

START_TEST (elm_atspi_role_get)
{
   Evas_Object *win, *actionslider;
   Elm_Atspi_Role role;

   elm_init(1, NULL);
   win = elm_win_add(NULL, "actionslider", ELM_WIN_BASIC);

   actionslider = elm_actionslider_add(win);
   eo_do(actionslider, role = elm_interface_atspi_accessible_role_get());

   ck_assert(role == ELM_ATSPI_ROLE_SLIDER);

   elm_shutdown();
}
END_TEST

void elm_test_actionslider(TCase *tc)
{
 tcase_add_test(tc, elm_atspi_role_get);
}
