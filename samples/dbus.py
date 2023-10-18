# simple script to show some info whenever properties chnaged
from gi.repository import GLib, Gio

def properties_changed_callback(
    connection,
    sender_name,
    object_path,
    interface_name,
    signal_name,
    parameters,
    user_data,
):
    print(
        f"sender: {sender_name}\n"
        f"object path: {object_path}\n"
        f"interface: {interface_name}\n"
        f"signal: {signal_name}"
    )

    default_props = connection.call_sync(
        "dev.cudiph.pulsedbus",
        object_path,
        "dev.cudiph.pulseaudio",
        "GetAllDefaultInformation",
        None,
        GLib.VariantType("(ssssdd)"),
        Gio.DBusCallFlags.NONE,
        -1,
        None,
    )

    _, _, sink_desc, source_desc, sink_vol, source_vol = default_props.unpack()
    print(
        f"{sink_desc} at {round(sink_vol * 100)}% volume\n"
        f"{source_desc} at {round(source_vol * 100)}% volume\n"
    )


main_loop = GLib.MainLoop()


bus = Gio.bus_get_sync(Gio.BusType.SESSION)

bus_id = bus.signal_subscribe(
    "dev.cudiph.pulsedbus",
    "org.freedesktop.DBus.Properties",
    "PropertiesChanged",
    "/dev/cudiph/pulsedbus",
    None,
    Gio.DBusSignalFlags.NONE,
    properties_changed_callback,
    None,
)


main_loop.run()
