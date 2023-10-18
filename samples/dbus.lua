-- simple lua code to interact with pulsedbus service using dbusproxy class

local lgi = require("lgi")
local Gio, GLib = lgi.Gio, lgi.GLib


local main_loop = GLib.MainLoop(nil, false)

local proxy = Gio.DBusProxy.new_for_bus_sync(Gio.BusType.SESSION, Gio.DBusProxyFlags.NONE, nil, "dev.cudiph.pulsedbus",
    "/dev/cudiph/pulsedbus", "dev.cudiph.pulseaudio", nil, nil)


function proxy:on_g_signal(sender_name, signal_name, parameters, user_data)
    print(string.format("Signal received: %s", signal_name))
    local sink = self:get_cached_property("CurrentDefaultSink"):get_string()
    local sink_vol = self:get_cached_property("DefaultSinkVolume"):get_double() * 100
    sink_vol = sink_vol - math.floor(sink_vol) >= 0.5 and math.ceil(sink_vol) or math.floor(sink_vol)
    -- local source = self:get_cached_property("CurrentDefaultSource"):get_string()
    print(string.format("%s at %d%%\n", sink, sink_vol))
end

main_loop:run()
