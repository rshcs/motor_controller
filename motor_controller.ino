
volatile boolean intstate = 0;
uint32_t t0; // to calc frequency
uint32_t t1;
uint32_t tmrp; // serial print tmr
//String instr = "";
int8_t motor_pin = 6;
uint8_t pwm_out = 0;

void setup()
{
    Serial.begin(9600);
    attachInterrupt(0, state_change, RISING);
    pinMode(motor_pin, OUTPUT);
    t0 = micros();
    tmrp = millis();
}

void loop()
{
    //sprinter(f(), 1000);
    
    if(Serial.available())
    {
        Serial.println(ser_read());
    }
    
   /*
   if(Serial.available())
   {
       analogWrite(motor_pin, ser_read_int());
   }
   */
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

uint16_t f() //frequency
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

int16_t ser_read_int()
{
    String instr = "";
    while (Serial.available())
    {
        instr += (char) Serial.read();
        delay(5);
        if (!Serial.available())
        {
            //Serial.println(instr.toInt());
            //instr = "";
            return instr.toInt();
        } 
    }
}

int8_t ser_read()
{
    String instr = "";
    while (Serial.available())
    {
        instr += (char) Serial.read();
        delay(5);
        if (!Serial.available())
        {
            if(instr.startsWith("p"))
                return 1;
            else if(instr.startsWith("i"))
                return 2;
            else if(instr.startsWith("d"))
                return 3;
        } 
    }
}