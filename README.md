# Zeon
A hobby x86, 32-bit kernel written in C.

#### Components
The Zeon kernel is for now very basic but here's what it implements:
- GRUB 2 Bootloader
- VGA writing support (Through tty.c)
- Segmentation with the Global Descriptor Table
- Interrupts with the Interrupt Descriptor Table (Still a Bug in it)
- That's it for now :)

I plan to add all the neccessary components such as paging, MMU, and _maybe_ user-space stuff.

## Building Zeon
Zeon is a Kernel designed to be on a x86 architecture. You will need to setup a GCC cross-compiler for any 32-bit x86 architecture (I used i686-elf, but it can be i386-elf or newer).
To see how to build the cross-compiler, please visit [this link](http://wiki.osdev.org/GCC_Cross-Compiler). Make sure you update the CC variable in Makefile to point to your cross-compiler.<br>

To proceed further, you should have these programs installed:
- GRUB 2 (For `grub-mkrescue` and `grub-file`)
- Xorriso (To generate the later ISO file)
- QEMU (The x86 emulator)
- The GCC cross-compiler (Should already be setup if you followed the steps from the link above)<br>

_Note: You may use different programs than I, such as Bochs or VirtualBox instead of QEMU. It is your responsibility to make sure everything is setup for your programs, such as in the Makefile._

To build zeon.kernel, the kernel binary, you can run `make` or `make zeon.kernel` from the terminal. There is only one Makefile for now and it's the one in the main "Zeon" directory.

Since it is only a file with all the kernel related code, there is no GRUB! If you wish to make this a bootable image, use `make iso`. It will generate zeon.iso in the Zeon directory.<br>

After you have created the ISO file, you can run `make run` to run QEMU on the ISO file. If all went well, you should see the GRUB menu with the "Zeon" entry on it. Select that one and the kernel should print a message for you :)

### License
This project is under the GNU General Public License v3, as it contains copyrighted material such as GRUB.
