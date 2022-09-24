/*
 * Copyright (c) 24.09.2022, Teemu Latonen
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are are forbidden.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __TE_SM9000_H__
#define __TE_SM9000_H__

#include <Arduino.h>
#include <Wire.h>

class SM9000_sensor {
  public:
    SM9000_sensor(float _Pmax, float _Pmin, int _OUT_min, int _OUT_max);
    void readData(void);
    float getTemp(void);
    float getPressure(void);
    word getStatus();
    void sleep(void);
    void wake(void);
    void reset(void);

  private:
    byte I2C_address = 0x6C;
    byte reading[6];
    float Pmax = 0.0;
    float Pmin = 0.0;
    int OUT_min = 0;
    int OUT_max = 0;
};

#endif
