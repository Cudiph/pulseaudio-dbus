#include <stdlib.h>
#include <string.h>

#include "pa_handler.h"

void server_info_cb(pa_context *ctx, const pa_server_info *i, void *userdata)
{
    if (!i)
        return;
    pulse_userdata *p_userdata = (pulse_userdata *)userdata;

    p_userdata->default_sink_name = realloc(p_userdata->default_sink_name,
                                            strlen(i->default_sink_name) + 1);
    strcpy(p_userdata->default_sink_name, i->default_sink_name);
    p_userdata->default_source_name = realloc(
        p_userdata->default_source_name, strlen(i->default_source_name) + 1);
    strcpy(p_userdata->default_source_name, i->default_source_name);

    pa_context_get_sink_info_by_name(ctx, i->default_sink_name, sink_info_cb,
                                     userdata);
    pa_context_get_source_info_by_name(ctx, i->default_source_name,
                                       source_info_cb, userdata);

    pd_pulseaudio_emit_server_event(p_userdata->pd_pulse_skel);
}

void sink_info_cb(pa_context *ctx,
                  const pa_sink_info *i,
                  int eol,
                  void *userdata)
{
    if (!i)
        return;
    pulse_userdata *p_userdata = (pulse_userdata *)userdata;
    int is_default = strcmp(p_userdata->default_sink_name, i->name) == 0;

    if (is_default) {
        p_userdata->default_sink_description = realloc(
            p_userdata->default_sink_description, strlen(i->description) + 1);
        strcpy(p_userdata->default_sink_description, i->description);

        double percent_vol = (double)pa_cvolume_avg(&i->volume) / 65536;
        p_userdata->default_sink_volume = percent_vol;
        pd_pulseaudio_set_default_sink_volume(p_userdata->pd_pulse_skel,
                                              percent_vol);

        pd_pulseaudio_set_current_default_sink(p_userdata->pd_pulse_skel,
                                               i->description);
    }

    pd_pulseaudio_emit_sink_event(p_userdata->pd_pulse_skel);
}

void source_info_cb(pa_context *ctx,
                    const pa_source_info *i,
                    int eol,
                    void *userdata)
{
    if (!i)
        return;
    pulse_userdata *p_userdata = (pulse_userdata *)userdata;
    int is_default = strcmp(p_userdata->default_source_name, i->name) == 0;

    if (is_default) {
        p_userdata->default_source_description = realloc(
            p_userdata->default_source_description, strlen(i->description) + 1);
        strcpy(p_userdata->default_source_description, i->description);

        double percent_vol = (double)pa_cvolume_avg(&i->volume) / 65536;
        p_userdata->default_source_volume = percent_vol;
        pd_pulseaudio_set_default_source_volume(p_userdata->pd_pulse_skel,
                                                percent_vol);

        pd_pulseaudio_set_current_default_source(p_userdata->pd_pulse_skel,
                                                 i->description);
    }

    pd_pulseaudio_emit_source_event(p_userdata->pd_pulse_skel);
}

void context_subscribe_cb(pa_context *ctx,
                          pa_subscription_event_type_t t,
                          unsigned int idx,
                          void *userdata)
{
    pulse_userdata *p_userdata = (pulse_userdata *)userdata;

    switch (t & PA_SUBSCRIPTION_EVENT_FACILITY_MASK) {
    case PA_SUBSCRIPTION_EVENT_SERVER:
        pa_context_get_server_info(ctx, server_info_cb, userdata);
        break;
    case PA_SUBSCRIPTION_EVENT_SINK:
        pa_context_get_sink_info_by_index(ctx, idx, sink_info_cb, userdata);
        break;
    case PA_SUBSCRIPTION_EVENT_SOURCE:
        pa_context_get_source_info_by_index(ctx, idx, source_info_cb, userdata);
        break;
    }
}

void context_state_cb(pa_context *ctx, void *userdata)
{
    pa_context_state_t state   = pa_context_get_state(ctx);
    pulse_userdata *p_userdata = (pulse_userdata *)userdata;

    switch (state) {
    case PA_CONTEXT_READY:
        g_message("Pulseaudio ready!");
        pa_context_get_server_info(ctx, server_info_cb, userdata);
        pa_context_subscribe(ctx,
                             PA_SUBSCRIPTION_MASK_SERVER
                                 | PA_SUBSCRIPTION_MASK_SINK
                                 | PA_SUBSCRIPTION_MASK_SOURCE,
                             NULL, userdata);
        pa_context_set_subscribe_callback(ctx, context_subscribe_cb, userdata);
        break;
    case PA_CONTEXT_FAILED:
        g_warning("Context failed.");
        g_main_loop_quit(p_userdata->glib_ml);
        break;
    case PA_CONTEXT_CONNECTING:
    case PA_CONTEXT_TERMINATED:
    case PA_CONTEXT_AUTHORIZING:
    case PA_CONTEXT_SETTING_NAME:
    default:
        break;
    }
}

void pulseaudio_init(pulse_userdata *p_userdata)
{
    GMainContext *g_ctx        = g_main_context_default();
    pa_glib_mainloop *pulse_ml = pa_glib_mainloop_new(g_ctx);
    pa_mainloop_api *ml_api    = pa_glib_mainloop_get_api(pulse_ml);
    pa_context *pa_ctx         = pa_context_new(ml_api, "pulsedbus");
    if (pa_context_connect(pa_ctx, NULL, PA_CONTEXT_NOFLAGS, NULL) < 0) {
        g_warning("pa_context_connect error: %s",
                  pa_strerror(pa_context_errno(pa_ctx)));
        g_main_loop_quit(p_userdata->glib_ml);
    }

    pa_context_set_state_callback(pa_ctx, context_state_cb, p_userdata);
}

pulse_userdata *pulse_userdata_new(PDPulseaudio *pd_pulse_skel,
                                   GMainLoop *glib_ml)
{
    pulse_userdata *p = malloc(sizeof(pulse_userdata));
    memset(p, 0, sizeof(pulse_userdata));
    p->pd_pulse_skel = pd_pulse_skel;
    p->glib_ml       = glib_ml;
    return p;
}
