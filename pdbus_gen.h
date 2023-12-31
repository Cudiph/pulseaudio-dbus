/*
 * This file is generated by gdbus-codegen, do not modify it.
 *
 * The license of this code is the same as for the D-Bus interface description
 * it was derived from. Note that it links to GLib, so must comply with the
 * LGPL linking clauses.
 */

#ifndef __PDBUS_GEN_H__
#define __PDBUS_GEN_H__

#include <gio/gio.h>

G_BEGIN_DECLS


/* ------------------------------------------------------------------------ */
/* Declarations for dev.cudiph.pulseaudio */

#define PD_TYPE_PULSEAUDIO (pd_pulseaudio_get_type ())
#define PD_PULSEAUDIO(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), PD_TYPE_PULSEAUDIO, PDPulseaudio))
#define PD_IS_PULSEAUDIO(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), PD_TYPE_PULSEAUDIO))
#define PD_PULSEAUDIO_GET_IFACE(o) (G_TYPE_INSTANCE_GET_INTERFACE ((o), PD_TYPE_PULSEAUDIO, PDPulseaudioIface))

struct _PDPulseaudio;
typedef struct _PDPulseaudio PDPulseaudio;
typedef struct _PDPulseaudioIface PDPulseaudioIface;

struct _PDPulseaudioIface
{
  GTypeInterface parent_iface;



  gboolean (*handle_get_all_default_information) (
    PDPulseaudio *object,
    GDBusMethodInvocation *invocation);

  const gchar * (*get_current_default_sink) (PDPulseaudio *object);

  const gchar * (*get_current_default_source) (PDPulseaudio *object);

  gdouble  (*get_default_sink_volume) (PDPulseaudio *object);

  gdouble  (*get_default_source_volume) (PDPulseaudio *object);

  void (*server_event) (
    PDPulseaudio *object);

  void (*sink_event) (
    PDPulseaudio *object);

  void (*source_event) (
    PDPulseaudio *object);

};

GType pd_pulseaudio_get_type (void) G_GNUC_CONST;

GDBusInterfaceInfo *pd_pulseaudio_interface_info (void);
guint pd_pulseaudio_override_properties (GObjectClass *klass, guint property_id_begin);


/* D-Bus method call completion functions: */
void pd_pulseaudio_complete_get_all_default_information (
    PDPulseaudio *object,
    GDBusMethodInvocation *invocation,
    const gchar *sink_name,
    const gchar *source_name,
    const gchar *sink_description,
    const gchar *source_description,
    gdouble sink_volume,
    gdouble source_volume);



/* D-Bus signal emissions functions: */
void pd_pulseaudio_emit_server_event (
    PDPulseaudio *object);

void pd_pulseaudio_emit_sink_event (
    PDPulseaudio *object);

void pd_pulseaudio_emit_source_event (
    PDPulseaudio *object);



/* D-Bus method calls: */
void pd_pulseaudio_call_get_all_default_information (
    PDPulseaudio *proxy,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean pd_pulseaudio_call_get_all_default_information_finish (
    PDPulseaudio *proxy,
    gchar **out_sink_name,
    gchar **out_source_name,
    gchar **out_sink_description,
    gchar **out_source_description,
    gdouble *out_sink_volume,
    gdouble *out_source_volume,
    GAsyncResult *res,
    GError **error);

gboolean pd_pulseaudio_call_get_all_default_information_sync (
    PDPulseaudio *proxy,
    gchar **out_sink_name,
    gchar **out_source_name,
    gchar **out_sink_description,
    gchar **out_source_description,
    gdouble *out_sink_volume,
    gdouble *out_source_volume,
    GCancellable *cancellable,
    GError **error);



/* D-Bus property accessors: */
gdouble pd_pulseaudio_get_default_sink_volume (PDPulseaudio *object);
void pd_pulseaudio_set_default_sink_volume (PDPulseaudio *object, gdouble value);

gdouble pd_pulseaudio_get_default_source_volume (PDPulseaudio *object);
void pd_pulseaudio_set_default_source_volume (PDPulseaudio *object, gdouble value);

const gchar *pd_pulseaudio_get_current_default_sink (PDPulseaudio *object);
gchar *pd_pulseaudio_dup_current_default_sink (PDPulseaudio *object);
void pd_pulseaudio_set_current_default_sink (PDPulseaudio *object, const gchar *value);

const gchar *pd_pulseaudio_get_current_default_source (PDPulseaudio *object);
gchar *pd_pulseaudio_dup_current_default_source (PDPulseaudio *object);
void pd_pulseaudio_set_current_default_source (PDPulseaudio *object, const gchar *value);


/* ---- */

#define PD_TYPE_PULSEAUDIO_PROXY (pd_pulseaudio_proxy_get_type ())
#define PD_PULSEAUDIO_PROXY(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), PD_TYPE_PULSEAUDIO_PROXY, PDPulseaudioProxy))
#define PD_PULSEAUDIO_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), PD_TYPE_PULSEAUDIO_PROXY, PDPulseaudioProxyClass))
#define PD_PULSEAUDIO_PROXY_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), PD_TYPE_PULSEAUDIO_PROXY, PDPulseaudioProxyClass))
#define PD_IS_PULSEAUDIO_PROXY(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), PD_TYPE_PULSEAUDIO_PROXY))
#define PD_IS_PULSEAUDIO_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), PD_TYPE_PULSEAUDIO_PROXY))

typedef struct _PDPulseaudioProxy PDPulseaudioProxy;
typedef struct _PDPulseaudioProxyClass PDPulseaudioProxyClass;
typedef struct _PDPulseaudioProxyPrivate PDPulseaudioProxyPrivate;

struct _PDPulseaudioProxy
{
  /*< private >*/
  GDBusProxy parent_instance;
  PDPulseaudioProxyPrivate *priv;
};

struct _PDPulseaudioProxyClass
{
  GDBusProxyClass parent_class;
};

GType pd_pulseaudio_proxy_get_type (void) G_GNUC_CONST;

#if GLIB_CHECK_VERSION(2, 44, 0)
G_DEFINE_AUTOPTR_CLEANUP_FUNC (PDPulseaudioProxy, g_object_unref)
#endif

void pd_pulseaudio_proxy_new (
    GDBusConnection     *connection,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GAsyncReadyCallback  callback,
    gpointer             user_data);
PDPulseaudio *pd_pulseaudio_proxy_new_finish (
    GAsyncResult        *res,
    GError             **error);
PDPulseaudio *pd_pulseaudio_proxy_new_sync (
    GDBusConnection     *connection,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GError             **error);

void pd_pulseaudio_proxy_new_for_bus (
    GBusType             bus_type,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GAsyncReadyCallback  callback,
    gpointer             user_data);
PDPulseaudio *pd_pulseaudio_proxy_new_for_bus_finish (
    GAsyncResult        *res,
    GError             **error);
PDPulseaudio *pd_pulseaudio_proxy_new_for_bus_sync (
    GBusType             bus_type,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GError             **error);


/* ---- */

#define PD_TYPE_PULSEAUDIO_SKELETON (pd_pulseaudio_skeleton_get_type ())
#define PD_PULSEAUDIO_SKELETON(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), PD_TYPE_PULSEAUDIO_SKELETON, PDPulseaudioSkeleton))
#define PD_PULSEAUDIO_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), PD_TYPE_PULSEAUDIO_SKELETON, PDPulseaudioSkeletonClass))
#define PD_PULSEAUDIO_SKELETON_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), PD_TYPE_PULSEAUDIO_SKELETON, PDPulseaudioSkeletonClass))
#define PD_IS_PULSEAUDIO_SKELETON(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), PD_TYPE_PULSEAUDIO_SKELETON))
#define PD_IS_PULSEAUDIO_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), PD_TYPE_PULSEAUDIO_SKELETON))

typedef struct _PDPulseaudioSkeleton PDPulseaudioSkeleton;
typedef struct _PDPulseaudioSkeletonClass PDPulseaudioSkeletonClass;
typedef struct _PDPulseaudioSkeletonPrivate PDPulseaudioSkeletonPrivate;

struct _PDPulseaudioSkeleton
{
  /*< private >*/
  GDBusInterfaceSkeleton parent_instance;
  PDPulseaudioSkeletonPrivate *priv;
};

struct _PDPulseaudioSkeletonClass
{
  GDBusInterfaceSkeletonClass parent_class;
};

GType pd_pulseaudio_skeleton_get_type (void) G_GNUC_CONST;

#if GLIB_CHECK_VERSION(2, 44, 0)
G_DEFINE_AUTOPTR_CLEANUP_FUNC (PDPulseaudioSkeleton, g_object_unref)
#endif

PDPulseaudio *pd_pulseaudio_skeleton_new (void);


/* ---- */

#define PD_TYPE_OBJECT (pd_object_get_type ())
#define PD_OBJECT(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), PD_TYPE_OBJECT, PDObject))
#define PD_IS_OBJECT(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), PD_TYPE_OBJECT))
#define PD_OBJECT_GET_IFACE(o) (G_TYPE_INSTANCE_GET_INTERFACE ((o), PD_TYPE_OBJECT, PDObject))

struct _PDObject;
typedef struct _PDObject PDObject;
typedef struct _PDObjectIface PDObjectIface;

struct _PDObjectIface
{
  GTypeInterface parent_iface;
};

GType pd_object_get_type (void) G_GNUC_CONST;

PDPulseaudio *pd_object_get_pulseaudio (PDObject *object);
PDPulseaudio *pd_object_peek_pulseaudio (PDObject *object);

#define PD_TYPE_OBJECT_PROXY (pd_object_proxy_get_type ())
#define PD_OBJECT_PROXY(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), PD_TYPE_OBJECT_PROXY, PDObjectProxy))
#define PD_OBJECT_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), PD_TYPE_OBJECT_PROXY, PDObjectProxyClass))
#define PD_OBJECT_PROXY_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), PD_TYPE_OBJECT_PROXY, PDObjectProxyClass))
#define PD_IS_OBJECT_PROXY(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), PD_TYPE_OBJECT_PROXY))
#define PD_IS_OBJECT_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), PD_TYPE_OBJECT_PROXY))

typedef struct _PDObjectProxy PDObjectProxy;
typedef struct _PDObjectProxyClass PDObjectProxyClass;
typedef struct _PDObjectProxyPrivate PDObjectProxyPrivate;

struct _PDObjectProxy
{
  /*< private >*/
  GDBusObjectProxy parent_instance;
  PDObjectProxyPrivate *priv;
};

struct _PDObjectProxyClass
{
  GDBusObjectProxyClass parent_class;
};

GType pd_object_proxy_get_type (void) G_GNUC_CONST;

#if GLIB_CHECK_VERSION(2, 44, 0)
G_DEFINE_AUTOPTR_CLEANUP_FUNC (PDObjectProxy, g_object_unref)
#endif

PDObjectProxy *pd_object_proxy_new (GDBusConnection *connection, const gchar *object_path);

#define PD_TYPE_OBJECT_SKELETON (pd_object_skeleton_get_type ())
#define PD_OBJECT_SKELETON(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), PD_TYPE_OBJECT_SKELETON, PDObjectSkeleton))
#define PD_OBJECT_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), PD_TYPE_OBJECT_SKELETON, PDObjectSkeletonClass))
#define PD_OBJECT_SKELETON_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), PD_TYPE_OBJECT_SKELETON, PDObjectSkeletonClass))
#define PD_IS_OBJECT_SKELETON(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), PD_TYPE_OBJECT_SKELETON))
#define PD_IS_OBJECT_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), PD_TYPE_OBJECT_SKELETON))

typedef struct _PDObjectSkeleton PDObjectSkeleton;
typedef struct _PDObjectSkeletonClass PDObjectSkeletonClass;
typedef struct _PDObjectSkeletonPrivate PDObjectSkeletonPrivate;

struct _PDObjectSkeleton
{
  /*< private >*/
  GDBusObjectSkeleton parent_instance;
  PDObjectSkeletonPrivate *priv;
};

struct _PDObjectSkeletonClass
{
  GDBusObjectSkeletonClass parent_class;
};

GType pd_object_skeleton_get_type (void) G_GNUC_CONST;

#if GLIB_CHECK_VERSION(2, 44, 0)
G_DEFINE_AUTOPTR_CLEANUP_FUNC (PDObjectSkeleton, g_object_unref)
#endif

PDObjectSkeleton *pd_object_skeleton_new (const gchar *object_path);
void pd_object_skeleton_set_pulseaudio (PDObjectSkeleton *object, PDPulseaudio *interface_);

/* ---- */

#define PD_TYPE_OBJECT_MANAGER_CLIENT (pd_object_manager_client_get_type ())
#define PD_OBJECT_MANAGER_CLIENT(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), PD_TYPE_OBJECT_MANAGER_CLIENT, PDObjectManagerClient))
#define PD_OBJECT_MANAGER_CLIENT_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), PD_TYPE_OBJECT_MANAGER_CLIENT, PDObjectManagerClientClass))
#define PD_OBJECT_MANAGER_CLIENT_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), PD_TYPE_OBJECT_MANAGER_CLIENT, PDObjectManagerClientClass))
#define PD_IS_OBJECT_MANAGER_CLIENT(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), PD_TYPE_OBJECT_MANAGER_CLIENT))
#define PD_IS_OBJECT_MANAGER_CLIENT_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), PD_TYPE_OBJECT_MANAGER_CLIENT))

typedef struct _PDObjectManagerClient PDObjectManagerClient;
typedef struct _PDObjectManagerClientClass PDObjectManagerClientClass;
typedef struct _PDObjectManagerClientPrivate PDObjectManagerClientPrivate;

struct _PDObjectManagerClient
{
  /*< private >*/
  GDBusObjectManagerClient parent_instance;
  PDObjectManagerClientPrivate *priv;
};

struct _PDObjectManagerClientClass
{
  GDBusObjectManagerClientClass parent_class;
};

#if GLIB_CHECK_VERSION(2, 44, 0)
G_DEFINE_AUTOPTR_CLEANUP_FUNC (PDObjectManagerClient, g_object_unref)
#endif

GType pd_object_manager_client_get_type (void) G_GNUC_CONST;

GType pd_object_manager_client_get_proxy_type (GDBusObjectManagerClient *manager, const gchar *object_path, const gchar *interface_name, gpointer user_data);

void pd_object_manager_client_new (
    GDBusConnection        *connection,
    GDBusObjectManagerClientFlags  flags,
    const gchar            *name,
    const gchar            *object_path,
    GCancellable           *cancellable,
    GAsyncReadyCallback     callback,
    gpointer                user_data);
GDBusObjectManager *pd_object_manager_client_new_finish (
    GAsyncResult        *res,
    GError             **error);
GDBusObjectManager *pd_object_manager_client_new_sync (
    GDBusConnection        *connection,
    GDBusObjectManagerClientFlags  flags,
    const gchar            *name,
    const gchar            *object_path,
    GCancellable           *cancellable,
    GError                **error);

void pd_object_manager_client_new_for_bus (
    GBusType                bus_type,
    GDBusObjectManagerClientFlags  flags,
    const gchar            *name,
    const gchar            *object_path,
    GCancellable           *cancellable,
    GAsyncReadyCallback     callback,
    gpointer                user_data);
GDBusObjectManager *pd_object_manager_client_new_for_bus_finish (
    GAsyncResult        *res,
    GError             **error);
GDBusObjectManager *pd_object_manager_client_new_for_bus_sync (
    GBusType                bus_type,
    GDBusObjectManagerClientFlags  flags,
    const gchar            *name,
    const gchar            *object_path,
    GCancellable           *cancellable,
    GError                **error);


G_END_DECLS

#endif /* __PDBUS_GEN_H__ */
