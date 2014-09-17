/**
 * @enum Elm_Toolbar_Shrink_Mode
 * @typedef Elm_Toolbar_Shrink_Mode
 *
 * Set toolbar's items display behavior, it can be scrollable,
 * show a menu with exceeding items, or simply hide them.
 *
 * @note Default value is #ELM_TOOLBAR_SHRINK_MENU. It reads value
 * from elm config.
 *
 * Values <b> don't </b> work as bitmask, only one can be chosen.
 *
 * @see elm_toolbar_shrink_mode_set()
 * @see elm_toolbar_shrink_mode_get()
 *
 * @ingroup Toolbar
 */
typedef enum
{
   ELM_TOOLBAR_SHRINK_NONE, /**< Set toolbar minimum size to fit all the items. */
   ELM_TOOLBAR_SHRINK_HIDE, /**< Hide exceeding items. */
   ELM_TOOLBAR_SHRINK_SCROLL, /**< Allow accessing exceeding items through a scroller. */
   ELM_TOOLBAR_SHRINK_MENU, /**< Inserts a button to pop up a menu with exceeding items. */
   ELM_TOOLBAR_SHRINK_EXPAND, /**< Expand all items according the size of the toolbar. */
   ELM_TOOLBAR_SHRINK_LAST /**< Indicates error if returned by elm_toolbar_shrink_mode_get() */
} Elm_Toolbar_Shrink_Mode;

/**
 * Defines where to position the item in the toolbar.
 *
 * @ingroup Toolbar
 */
typedef enum
{
   ELM_TOOLBAR_ITEM_SCROLLTO_NONE = 0,   /**< no scrollto */
   ELM_TOOLBAR_ITEM_SCROLLTO_IN = (1 << 0),   /**< to the nearest viewport */
   ELM_TOOLBAR_ITEM_SCROLLTO_FIRST = (1 << 1),   /**< to the first of viewport */
   ELM_TOOLBAR_ITEM_SCROLLTO_MIDDLE = (1 << 2),   /**< to the middle of viewport */
   ELM_TOOLBAR_ITEM_SCROLLTO_LAST = (1 << 3)   /**< to the last of viewport */
} Elm_Toolbar_Item_Scrollto_Type;

typedef struct _Elm_Toolbar_Item_State Elm_Toolbar_Item_State;    /**< State of a Elm_Toolbar_Item. Can be created with elm_toolbar_item_state_add() and removed with elm_toolbar_item_state_del(). */

EAPI Elm_Object_Item             *elm_toolbar_item_next_get(const Elm_Object_Item *it);

EAPI Elm_Object_Item             *elm_toolbar_item_prev_get(const Elm_Object_Item *it);

EAPI void                         elm_toolbar_item_priority_set(Elm_Object_Item *it, int priority);

EAPI int                          elm_toolbar_item_priority_get(const Elm_Object_Item *it);

EAPI Eina_Bool                    elm_toolbar_item_selected_get(const Elm_Object_Item *it);

EAPI void                         elm_toolbar_item_selected_set(Elm_Object_Item *it, Eina_Bool selected);

EAPI void                         elm_toolbar_item_icon_set(Elm_Object_Item *it, const char *icon);

EAPI const char                  *elm_toolbar_item_icon_get(const Elm_Object_Item *it);

EAPI Evas_Object                 *elm_toolbar_item_object_get(const Elm_Object_Item *it);

EAPI Evas_Object                 *elm_toolbar_item_icon_object_get(Elm_Object_Item *it);

EAPI Eina_Bool                    elm_toolbar_item_icon_memfile_set(Elm_Object_Item *it, const void *img, size_t size, const char *format, const char *key);

EAPI Eina_Bool                    elm_toolbar_item_icon_file_set(Elm_Object_Item *it, const char *file, const char *key);

EAPI void                         elm_toolbar_item_separator_set(Elm_Object_Item *it, Eina_Bool separator);

EAPI Eina_Bool                    elm_toolbar_item_separator_get(const Elm_Object_Item *it);

EAPI void                         elm_toolbar_item_menu_set(Elm_Object_Item *it, Eina_Bool menu);

EAPI Evas_Object                 *elm_toolbar_item_menu_get(const Elm_Object_Item *it);

EAPI Elm_Toolbar_Item_State      *elm_toolbar_item_state_add(Elm_Object_Item *it, const char *icon, const char *label, Evas_Smart_Cb func, const void *data);

EAPI Eina_Bool                    elm_toolbar_item_state_del(Elm_Object_Item *it, Elm_Toolbar_Item_State *state);

EAPI Eina_Bool                    elm_toolbar_item_state_set(Elm_Object_Item *it, Elm_Toolbar_Item_State *state);

/**
 * Unset the state of @p it.
 *
 * @param it The toolbar item.
 *
 * The default icon and label from this item will be displayed.
 *
 * @see elm_toolbar_item_state_set() for more details.
 *
 * @ingroup Toolbar
 */
EAPI void                         elm_toolbar_item_state_unset(Elm_Object_Item *it);

EAPI Elm_Toolbar_Item_State      *elm_toolbar_item_state_get(const Elm_Object_Item *it);

EAPI Elm_Toolbar_Item_State      *elm_toolbar_item_state_next(Elm_Object_Item *it);

EAPI Elm_Toolbar_Item_State      *elm_toolbar_item_state_prev(Elm_Object_Item *it);

EAPI void                          elm_toolbar_item_show(Elm_Object_Item *it, Elm_Toolbar_Item_Scrollto_Type type);

EAPI void                          elm_toolbar_item_bring_in(Elm_Object_Item *it, Elm_Toolbar_Item_Scrollto_Type type);

