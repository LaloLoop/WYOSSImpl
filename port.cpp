#include "port.h"

template<class port_size>
Port<port_size>::Port(uint16_t portnumber) {
	this->portnumber = portnumber;
}

template<class port_size>
Port<port_size>::~Port() { }

template<class port_size>
void Port<port_size>::Write(port_size data) {
	switch(sizeof(port_size)) {
		case sizeof(uint8_t):
            __asm__ volatile("outb %0, %1" : : "a" (data), "Nd" (portnumber));
            break;

	    case sizeof(uint16_t):
		    __asm__ volatile("outw %0, %1" : : "a" (data), "Nd" (portnumber));
		    break;

	    case sizeof(uint32_t):
		    __asm__ volatile("outl %0, %1" : : "a" (data), "Nd" (portnumber));
		    break;
	}
}

template<class port_size>
port_size Port<port_size>::Read() {
	port_size result;

    switch(sizeof(port_size)) {
		case sizeof(uint8_t):
            __asm__ volatile("inb %1, %0" : "=a" (result) : "Nd" (portnumber));
            break;

	    case sizeof(uint16_t):
		    __asm__ volatile("inw %1, %0" : "=a" (result) : "Nd" (portnumber));
		    break;

	    case sizeof(uint32_t):
		    __asm__ volatile("inl %1, %0" : "=a" (result) : "Nd" (portnumber));
		    break;
	}

	return result;
}

template<class port_size>
void PortSlow<port_size>::Write(port_size data) {
    switch(sizeof(port_size)) {
		case sizeof(uint8_t):
            __asm__ volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1:" : : "a" (data), "Nd" (this->portnumber));
            break;
	}
}