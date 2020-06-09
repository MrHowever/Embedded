//
// Created by mrhowever on 04.04.2020.
//

#ifndef RIGHTWINDOW_I2C_MASTER_H
#define RIGHTWINDOW_I2C_MASTER_H

class I2CMaster
{
    bool _running;
public:
    I2CMaster();
    unsigned char start(unsigned char);
    void startWait(unsigned char);
    void stop();
    unsigned char write(unsigned char);
};

#endif //RIGHTWINDOW_I2C_MASTER_H
