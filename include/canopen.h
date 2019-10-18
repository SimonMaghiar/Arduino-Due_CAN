#ifndef openCan_h
#define openCan_h
#include "Arduino.h"
#include "CAN.h"

namespace canopen {


struct CANFrame {
    uint32_t id;
    uint8_t length;
    uint8_t data[8];
};

class CAN_DUINO
{
    private:
        void sdo(CANFrame &f, uint8_t id, uint16_t index, uint8_t multiplexer) {
            f.id = 0x600 | id;
            f.length = 8;
            f.data[1] = index & 0xff;
            f.data[2] = (index >> 8) & 0xff;
            f.data[3] = multiplexer;
            f.data[4] = f.data[5] = f.data[6] = f.data[7] = 0;
}
    public:
        void read(CANFrame &f, uint8_t id, uint16_t index, uint8_t multiplexer) {
            sdo(f, id, index, multiplexer);
            f.data[0] = 0x40;
        }
        
        void write(const CANFrame &frame){
                CAN_Frame f;
                f.id = frame.id;
                f.length = frame.length;
                for (int i = 0; i < 8; i++) f.data[i] = frame.data[i];
                if(CAN.write(f))
                    Serial.println("Can packet sent!");
        }
};


}

#endif /* openCan_h */
