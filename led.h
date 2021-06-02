#ifndef LED_H
#define LED_H

//author ljy qq:874212844
class LED
{

private:
    static LED* Instance;
public:
    LED();

   static LED* getInstance();

   void extinguishAll();
   void brightAll();

   void brightSingle(int index);
   void extinguishSingle(int index);
};

#endif // LED_H
