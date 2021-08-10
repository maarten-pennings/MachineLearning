#include <EloquentTinyML.h> // From https://github.com/eloquentarduino/EloquentTinyML
#include "model.h"          // From https://github.com/maarten-pennings/MachineLearning/blob/main/sine/sine.ipynb

#define NUMBER_OF_INPUTS  1
#define NUMBER_OF_OUTPUTS 1
#define TENSOR_ARENA_SIZE 2*1024 // Trial and error

Eloquent::TinyML::TfLite<
    NUMBER_OF_INPUTS, 
    NUMBER_OF_OUTPUTS, 
    TENSOR_ARENA_SIZE
> ml;

void setup() {
    Serial.begin(115200);
    while( !Serial ) ; //skip
    Serial.printf( "Sine\n");
    ml.begin(model_data);
}

void loop() {
    float input[NUMBER_OF_INPUTS], output[NUMBER_OF_OUTPUTS];
    uint32_t time0, time1;
    float x, y1, y2;
    
    x  = 2 * 3.14159 * random(1000+1) / 1000;
    y1 = sin(x);

    input[0] = x;
    time0  = micros();
        ml.predict(input,output);
    time1 = micros();
    y2 = output[0];
    
    Serial.printf("x=%f, sine=%+f, model=%+f, error=%+f, time=%d\n",x,y1,y2,y2-y1,time1-time0);
    
    delay(1000);
}
