#include <gio/gio.h>
#include <math.h>

static void on_properties_changed(GDBusProxy *proxy,
                                  GVariant *changed_properties,
                                  const gchar *const *invalidated_properties,
                                  gpointer user_data)
{
    /* Note that we are guaranteed that changed_properties and
     * invalidated_properties are never NULL
     */
    if (g_variant_n_children(changed_properties) > 0) {
        GVariantIter *iter;
        const gchar *key;
        GVariant *value;

        g_print(" *** Properties Changed:\n");
        g_variant_get(changed_properties, "a{sv}", &iter);
        while (g_variant_iter_loop(iter, "{&sv}", &key, &value)) {
            gchar *value_str;
            value_str = g_variant_print(value, TRUE);
            g_print("      %s -> %s\n", key, value_str);
            g_free(value_str);
        }
        g_variant_iter_free(iter);

        GVariant *default_info =
            g_dbus_proxy_call_sync(proxy, "GetAllDefaultInformation", NULL,
                                   G_DBUS_CALL_FLAGS_NONE, -1, NULL, NULL);

        gchar *sink_name, *source_name, *sink_desc, *source_desc;
        double sink_volume, source_volume;
        g_variant_get(default_info, "(ssssdd)", &sink_name, &source_name,
                      &sink_desc, &source_desc, &sink_volume, &source_volume);

        g_print("Default Sink: %s at %d%%\nDefault Source: %s at %d%%\n",
                sink_desc, (int)round(sink_volume * 100), source_desc,
                (int)round(source_volume * 100));

        g_free(sink_name);
        g_free(sink_desc);
        g_free(source_name);
        g_free(source_desc);
        g_variant_unref(default_info);
    }

    if (g_strv_length((GStrv)invalidated_properties) > 0) {
        guint n;
        g_print(" *** Properties Invalidated:\n");
        for (n = 0; invalidated_properties[n] != NULL; n++) {
            const gchar *key = invalidated_properties[n];
            g_print("      %s\n", key);
        }
    }
}

int main()
{
    GMainLoop *glib_ml         = g_main_loop_new(NULL, FALSE);
    const char *known_name     = "dev.cudiph.pulsedbus";
    const char *object_path    = "/dev/cudiph/pulsedbus";
    const char *interface_name = "dev.cudiph.pulseaudio";
    GError *error              = NULL;

    const GDBusArgInfo get_all_default_info_args[] = {
        {.name = "sink_name",          .signature = "s"},
        {.name = "source_name",        .signature = "s"},
        {.name = "sink_description",   .signature = "s"},
        {.name = "source_description", .signature = "s"},
        {.name = "sink_volume",        .signature = "d"},
        {.name = "source_volume",      .signature = "d"},
    };

    const GDBusMethodInfo pdbus_methods[] = {
        {.name     = "GetAllDefaultInformation",
         .out_args = (GDBusArgInfo **)get_all_default_info_args},
    };

    const GDBusPropertyInfo pdbus_props[] = {
        {.name = "CurrentDefaultSink",   .signature = "s"},
        {.name = "CurrentDefaultSource", .signature = "s"},
        {.name = "DefaultSinkVolume",    .signature = "d"},
        {.name = "DefaultSourceVolume",  .signature = "d"}
    };

    const GDBusSignalInfo pdbus_signals[] = {{.name = "ServerEvent"},
                                             {.name = " SinkEvent"},
                                             {.name = "SourceEvent"}};

    // not really necessary when using on the client side
    GDBusInterfaceInfo pdbus_interface_info = {
        .name       = (char *)interface_name,
        .methods    = (GDBusMethodInfo **)pdbus_methods,
        .properties = (GDBusPropertyInfo **)pdbus_props,
        .signals    = (GDBusSignalInfo **)pdbus_signals};

    GDBusProxy *proxy = g_dbus_proxy_new_for_bus_sync(
        G_BUS_TYPE_SESSION, G_DBUS_PROXY_FLAGS_NONE, &pdbus_interface_info,
        known_name, object_path, interface_name, NULL, &error);

    if (!proxy) {
        g_printerr("error: %s\n", error->message);
        g_error_free(error);
        goto out;
    }

    g_signal_connect(proxy, "g-properties-changed",
                     G_CALLBACK(on_properties_changed), NULL);

    g_main_loop_run(glib_ml);

out:
    g_free(proxy);
    g_main_loop_unref(glib_ml);
    return 0;
}
