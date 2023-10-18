#include <glib.h>
#include <pulse/glib-mainloop.h>
#include <pulse/pulseaudio.h>

#include "pdbus_gen.h"

typedef struct pulse_userdata {
    PDPulseaudio *pd_pulse_skel;
    GMainLoop *glib_ml;
    char *default_sink_name;
    char *default_source_name;
    char *default_sink_description;
    char *default_source_description;
    double default_sink_volume;
    double default_source_volume;
} pulse_userdata;

void server_info_cb(pa_context *ctx, const pa_server_info *i, void *userdata);

void sink_info_cb(pa_context *ctx,
                  const pa_sink_info *i,
                  int eol,
                  void *userdata);

void source_info_cb(pa_context *ctx,
                    const pa_source_info *i,
                    int eol,
                    void *userdata);

void context_subscribe_cb(pa_context *ctx,
                          pa_subscription_event_type_t t,
                          unsigned int idx,
                          void *userdata);

void context_state_cb(pa_context *ctx, void *userdata);

void pulseaudio_init(pulse_userdata *p_userdata);

pulse_userdata *pulse_userdata_new(PDPulseaudio *pd_pulse_skel,
                                   GMainLoop *glib_ml);
