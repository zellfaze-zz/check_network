#Network Checker

This software sends a single ICMP ping request and outputs the amount of time
it took for the round trip.

It is designed to be used in XFCE's panel.

##Installation

First you will need to download the software, you can either download the
[source](https://github.com/zellfaze/check_network/archive/master.zip) (and
build yourself), download the
[binary](https://github.com/zellfaze/check_network/raw/master/bin/Release/check_network),
or download the [.deb package](https://github.com/zellfaze/check_network_pkg/raw/master/check-network_1.0-1_amd64.deb).

On your XFCE panel add a new Launcher item.  Have this launcher button run
`check_network -t`. Now next to the Launcher item create a new Generic Monitor
item on your panel.  This should be set to run `check_network` every 5 seconds.

You should now be able to toggle the ping monitor on and off.

##Configuration

You can modify the .check_network file in your home directory to change the
settings for the software.

The first line of the configuration file specifies an alternative IP Address to
ping. If the config file file is blank, doesn't exist, or has a blank first
line then the software defaults to 8.8.8.8.

The second line of the configuration files specifies how long to wait before
the request times out. This should be set to one second less than what the
XFCE generic monitor's frequency is set to. If the config files is blank,
doesn't exist, or has a blank second line then the software defaults to 4.