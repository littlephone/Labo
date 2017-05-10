CSOURCECODE = $(wildcard kernel/*.c drivers/*.c include/*.c libc/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h include/*.c libc/*.h)

OBJECTS = ${CSOURCECODE:.c=.o include/interrupt.o}
qemu= qemu-system-x86_64

debug: boot.img kernel.elf
	qemu-system-i386 -s -fda boot.img -d guest_errors,int&
	i386-elf-gdb -ex "target remote localhost:1234" -ex "symbol-file kernel.elf

kernel.elf: kernel/asm2c.o ${OBJECTS}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ 

kernel.bin: kernel/asm2c.o ${OBJECTS}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

boot.img: boot/bootsect.bin kernel.bin
	cat $^ > boot.img

launch: boot.img
	$(qemu) -fda boot.img

clean:
	rm -rf *.bin boot.img *.o *.elf *.log
	rm -rf kernel/*.o boot/*.bin drivers/*.o include/*.o 

package: 
	tar -c * | xz -zf -> ../Labo-version-md5.tar.xz

#Compile everything in C and assembly to obj and
#Wildcard starts here... :)	

%.o: %.c ${HEADERS}
	i386-elf-gcc -g -c -ffreestanding -c $< -o $@

%.o: %.S
	nasm $< -f elf -o $@
%.bin: %.S
	nasm $< -f bin -o $@
