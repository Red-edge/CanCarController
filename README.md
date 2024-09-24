# CanCarController

### Operation System on NUC trial

Due to author's lack of C++ knowledge, this program works on author's personal idea and therefore lack of systematic process, prealigned program line. I'll skip the hpp, launch.json part for further study and operation. Sry if u find out that the program is totally  unable to run. -24.7.31 Rededge

### Requirement

* can-utils
* cmake

You should use USB3 or above for usb2can module.

### How To Use

Now support cmake to build the program. If you're using Linux desktop, you could run bash file for fast test.

$ bash virruntest.sh  	// When no can module onhand, you could debug via this method, auto re-make. Only support gnome-terminal

$ bash realruntest.sh 	// When you have hung can modules onto a usb2can module, auto re-make, only support gnome-terminal

$ bash killtest.sh 		// Quick quit from current testing, only support gnome-terminal and may kill all terminals
