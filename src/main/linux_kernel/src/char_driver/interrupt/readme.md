# To check list of module

$> lsmod

# Build the module
sudo make

# clean module

sudo make clean

# insert module
sudo insmod <Ko path>

# remove module
sudo rmmod <ko module name>

<i>Note: To check module use lsmod</i>

# while in module loaded, check out execution

dmesg

<i>Note: dmesg with tail and head. see example below <br>
	dmesg | tail -n 10</i>