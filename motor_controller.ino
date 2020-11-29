
volatile boolean intstate = 0;
uint32_t t0; // to calc frequency
uint32_t t1;
uint32_t tmrp; // serial print tmr
uint32_t tp;

void setup()
{
    Serial.begin(9600);
    attachInterrupt(0, state_change, RISING);
    t0 = micros();
    tmrp = millis();
}

void loop()
{
   
    sprinter(f(), 1000);
    
    
    
    
    

}

void state_change()
{
    intstate = 1;

}

uint32_t tperiod()
{
    if (intstate)
    {
        intstate = 0;
        t1 = micros() - t0;
        t0 = micros();
    }
    if (micros() - t0 > 100000)
    {
        return 4294967295;
    }
    else
    {
        return t1;
    }
}

uint32_t f() //frequency
{

    return 1000000 / tperiod();
}

void sprinter(uint32_t inprint, uint16_t indly)
{
    if (millis() - tmrp > indly)
    {
        Serial.println(inprint);
        tmrp = millis();
    }
}
