run: compile
	qemu-system-x86_64 dist/boot_sect.bin

compile: dist
	nasm -f bin boot/boot_sect.asm -o dist/boot_sect.bin

dist:
	rm -rf dist/
	mkdir -p dist/
