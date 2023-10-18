# PulseAudio DBus

Forward PulseAudio event to DBus

## Examples

Some example how to use it in code can be seen at [samples folder](./samples/).

## Compiling

```sh
make
```

## Usage

```console
$ ./pulsedbus & # running the program
$ busctl --user introspect dev.cudiph.pulsedbus /dev/cudiph/pulsedbus # list interface
$ busctl --user call dev.cudiph.pulsedbus /dev/cudiph/pulsedbus dev.cudiph.pulseaudio GetAllDefaultInformation # call a method
$ python samples/dbus.py # watch for properties changes
```

### Motivation

Updating audio volume value is not instant because I was using time interval
polling for my awesomeWM wibar. And in pipewire pulse, module-dbus-protocol is
not implemented yet. So now, I can just listen to a DBus event in lua and update
the interface every time the volume changed.
