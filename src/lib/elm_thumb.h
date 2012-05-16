/**
 * @defgroup Thumb Thumbnail
 * @ingroup Elementary
 *
 * @image html img/widget/thumb/preview-00.png
 * @image latex img/widget/thumb/preview-00.eps
 *
 * A thumbnail object is used for displaying the thumbnail of an image
 * or video. You must have compiled Elementary with @c Ethumb_Client
 * support. Also, Ethumb's DBus service must be present and
 * auto-activated in order to have thumbnails generated. You must also
 * have a @b session bus, not a @b system one.
 *
 * Once the thumbnail object becomes visible, it will check if there
 * is a previously generated thumbnail image for the file set on
 * it. If not, it will start generating this thumbnail.
 *
 * Different configuration settings will cause different thumbnails to
 * be generated even on the same file.
 *
 * Generated thumbnails are stored under @c $HOME/.thumbnails/. Check
 * Ethumb's documentation to change this path, and to see other
 * configuration options.
 *
 * This widget emits the following signals:
 * - @c "clicked" - This is called when a user has clicked the
 *                  thumbnail object without dragging it around.
 * - @c "clicked,double" - This is called when a user has double-clicked
 *                         the thumbnail object.
 * - @c "press" - This is called when a user has pressed down over the
 *                thumbnail object.
 * - @c "generate,start" - The thumbnail generation has started.
 * - @c "generate,stop" - The generation process has stopped.
 * - @c "generate,error" - The thumbnail generation failed.
 * - @c "load,error" - The thumbnail image loading failed.
 *
 * Available styles:
 * - @c "default"
 * - @c "noframe"
 *
 * An example of use of thumbnail:
 *
 * - @ref thumb_example_01
 */

/**
 * @addtogroup Thumb
 * @{
 */

/**
 * @enum Elm_Thumb_Animation_Setting
 * @typedef Elm_Thumb_Animation_Setting
 *
 * Used to set if a video thumbnail is animating or not.
 *
 * @ingroup Thumb
 */
typedef enum
{
   ELM_THUMB_ANIMATION_START = 0, /**< Play animation once */
   ELM_THUMB_ANIMATION_LOOP, /**< Keep playing animation until stop is requested */
   ELM_THUMB_ANIMATION_STOP, /**< Stop playing the animation */
   ELM_THUMB_ANIMATION_LAST
} Elm_Thumb_Animation_Setting;

/**
 * Add a new thumb object to the parent.
 *
 * @param parent The parent object.
 * @return The new object or NULL if it cannot be created.
 *
 * @see elm_thumb_file_set()
 * @see elm_thumb_ethumb_client_get()
 *
 * @ingroup Thumb
 */
EAPI Evas_Object                *elm_thumb_add(Evas_Object *parent);

/**
 * Reload thumbnail if it was generated before.
 *
 * @param obj The thumb object to reload
 *
 * This is useful if the ethumb client configuration changed, like its
 * size, aspect or any other property one set in the handle returned
 * by elm_thumb_ethumb_client_get().
 *
 * If the options didn't change, the thumbnail won't be generated again, but
 * the old one will still be used.
 *
 * @see elm_thumb_file_set()
 *
 * @ingroup Thumb
 */
EAPI void                        elm_thumb_reload(Evas_Object *obj);

/**
 * Set the file that will be used as thumbnail @b source.
 *
 * @param obj The thumb object.
 * @param file The path to file that will be used as thumbnail source.
 * @param key The key used in case of an EET file.
 *
 * The file can be an image or a video (in that case, acceptable
 * extensions are: avi, mp4, ogv, mov, mpg and wmv). To start the
 * video animation, use the function elm_thumb_animate().
 *
 * @see elm_thumb_file_get()
 * @see elm_thumb_reload()
 * @see elm_thumb_animate()
 *
 * @ingroup Thumb
 */
EAPI void                        elm_thumb_file_set(Evas_Object *obj, const char *file, const char *key);

/**
 * Get the image or video path and key used to generate the thumbnail.
 *
 * @param obj The thumb object.
 * @param file Pointer to filename.
 * @param key Pointer to key.
 *
 * @see elm_thumb_file_set()
 * @see elm_thumb_path_get()
 *
 * @ingroup Thumb
 */
EAPI void                        elm_thumb_file_get(const Evas_Object *obj, const char **file, const char **key);

/**
 * Get the path and key to the image or video thumbnail generated by ethumb.
 *
 * One just needs to make sure that the thumbnail was generated before getting
 * its path; otherwise, the path will be NULL. One way to do that is by asking
 * for the path when/after the "generate,stop" smart callback is called.
 *
 * @param obj The thumb object.
 * @param file Pointer to thumb path.
 * @param key Pointer to thumb key.
 *
 * @see elm_thumb_file_get()
 *
 * @ingroup Thumb
 */
EAPI void                        elm_thumb_path_get(const Evas_Object *obj, const char **file, const char **key);

/**
 * Set the animation state for the thumb object. If its content is an animated
 * video, you may start/stop the animation or tell it to play continuously and
 * looping.
 *
 * @param obj The thumb object.
 * @param s The animation setting.
 *
 * @see elm_thumb_file_set()
 *
 * @ingroup Thumb
 */
EAPI void                        elm_thumb_animate_set(Evas_Object *obj, Elm_Thumb_Animation_Setting s);

/**
 * Get the animation state for the thumb object.
 *
 * @param obj The thumb object.
 * @return getting The animation setting or @c ELM_THUMB_ANIMATION_LAST,
 * on errors.
 *
 * @see elm_thumb_animate_set()
 *
 * @ingroup Thumb
 */
EAPI Elm_Thumb_Animation_Setting elm_thumb_animate_get(const Evas_Object *obj);

/**
 * Get the ethumb_client handle so custom configuration can be made.
 *
 * @return Ethumb_Client instance or NULL.
 *
 * This must be called before the objects are created to be sure no object is
 * visible and no generation started.
 *
 * Example of usage:
 *
 * @code
 * #include <Elementary.h>
 * #ifndef ELM_LIB_QUICKLAUNCH
 * EAPI_MAIN int
 * elm_main(int argc, char **argv)
 * {
 *    Ethumb_Client *client;
 *
 *    elm_need_ethumb();
 *
 *    // ... your code
 *
 *    client = elm_thumb_ethumb_client_get();
 *    if (!client)
 *      {
 *         ERR("could not get ethumb_client");
 *         return 1;
 *      }
 *    ethumb_client_size_set(client, 100, 100);
 *    ethumb_client_crop_align_set(client, 0.5, 0.5);
 *    // ... your code
 *
 *    // Create elm_thumb objects here
 *
 *    elm_run();
 *    elm_shutdown();
 *    return 0;
 * }
 * #endif
 * ELM_MAIN()
 * @endcode
 *
 * @note There's only one client handle for Ethumb, so once a configuration
 * change is done to it, any other request for thumbnails (for any thumbnail
 * object) will use that configuration. Thus, this configuration is global.
 *
 * @ingroup Thumb
 */
EAPI void                       *elm_thumb_ethumb_client_get(void);

/**
 * Get the ethumb_client connection state.
 *
 * @return EINA_TRUE if the client is connected to the server or EINA_FALSE
 * otherwise.
 */
EAPI Eina_Bool                   elm_thumb_ethumb_client_connected_get(void);

/**
 * Make the thumbnail 'editable'.
 *
 * @param obj Thumb object.
 * @param edit Turn on or off editability. Default is @c EINA_FALSE.
 *
 * This means the thumbnail is a valid drag target for drag and drop, and can be
 * cut or pasted too.
 *
 * @see elm_thumb_editable_get()
 *
 * @ingroup Thumb
 */
EAPI Eina_Bool                   elm_thumb_editable_set(Evas_Object *obj, Eina_Bool edit);

/**
 * Make the thumbnail 'editable'.
 *
 * @param obj Thumb object.
 * @return Editability.
 *
 * This means the thumbnail is a valid drag target for drag and drop, and can be
 * cut or pasted too.
 *
 * @see elm_thumb_editable_set()
 *
 * @ingroup Thumb
 */
EAPI Eina_Bool                   elm_thumb_editable_get(const Evas_Object *obj);

/**
 * @}
 */
