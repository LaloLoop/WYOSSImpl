#ifndef __PORT_H
#define __PORT_H

#include "types.h"

    // Purely virtual base class
    template<class port_size> 
    class Port {
    protected:
        uint16_t portnumber;
        Port(uint16_t portnumber);
        ~Port();

        void Write(port_size data);
    	port_size Read();
    };

    template<class port_size>
    class PortSlow: public Port<port_size> {
        void Write(port_size data);
    };

#endif