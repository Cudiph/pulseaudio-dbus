#include <gio/gio.h>
#include <glib.h>

#include "pa_handler.h"
#include "pdbus_gen.h"

static gboolean on_get_all_default_information(
    PDPulseaudio *p, GDBusMethodInvocation *invocation, gpointer userdata)
{
    pulse_userdata *p_userdata = (pulse_userdata *)userdata;
    pd_pulseaudio_complete_get_all_default_information(
        p, invocation, p_userdata->default_sink_name,
        p_userdata->default_source_name, p_userdata->default_sink_description,
        p_userdata->default_source_description, p_userdata->default_sink_volume,
        p_userdata->default_source_volume);
    return G_DBUS_METHOD_INVOCATION_HANDLED;
}

static void on_bus_acquired(GDBusConnection *connection,
                            const gchar *name,
                            gpointer user_data)
{
    GMainLoop *glib_ml = (GMainLoop *)user_data;

    PDPulseaudio *pd_pulse = pd_pulseaudio_skeleton_new();
    GError *error          = NULL;

    pulse_userdata *p_userdata = pulse_userdata_new(pd_pulse, glib_ml);

    pulseaudio_init(p_userdata);

    g_signal_connect(pd_pulse, "handle-get-all-default-information",
                     G_CALLBACK(on_get_all_default_information), p_userdata);
    g_dbus_interface_skeleton_export(G_DBUS_INTERFACE_SKELETON(pd_pulse),
                                     connection, "/dev/cudiph/pulsedbus",
                                     &error);
    return;
}

static void on_name_acquired(GDBusConnection *connection,
                             const gchar *name,
                             gpointer user_data)
{
    g_message("Acquired the name %s\n", name);
    return;
}

static void
on_name_lost(GDBusConnection *connection, const gchar *name, gpointer user_data)
{
    g_message("Lost the name %s\n", name);
    return;
}

int main()
{
    GMainLoop *glib_ml = g_main_loop_new(NULL, FALSE);

    guint owner_id = g_bus_own_name(
        G_BUS_TYPE_SESSION, "dev.cudiph.pulsedbus", G_BUS_NAME_OWNER_FLAGS_NONE,
        on_bus_acquired, on_name_acquired, on_name_lost, glib_ml, NULL);

    g_main_loop_run(glib_ml);
    g_bus_unown_name(owner_id);
    g_main_loop_unref(glib_ml);
    return 0;
}
