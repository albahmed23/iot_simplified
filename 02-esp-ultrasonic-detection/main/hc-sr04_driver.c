/*
    IoT Simplified (iotsimplified.com)
    
    Sensor Driver for the HC-SR04 Ultrasonic Range Finding Sensor

    Written by Ahmed Al Bayati
    


    Unless required by applicable law or agreed to in writing, this
    software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
    CONDITIONS OF ANY KIND, either express or implied.
    
*/

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_system.h"
#include "esp_err.h"
#include "esp_log.h"

#include "hc-sr04_driver.h"

#define HCSR_TRIG_GPIO_NUM GPIO_NUM_22
#define HCSR_ECHO_GPIO_NUM GPIO_NUM_23
#define HCSR_HIGH 1
#define HCSR_LOW 0


static const char *TAG = "hc-sr04_driver";

// Function Prototypes
int hcsr_setup_pins(); //Setup all the pins and such to get the GPIO ready to be used
esp_err_t hcsr_send_trig_signal(); //Send a 10uS trig signal HIGH to the sensor
int hcsr_echo_pulse_read(); //Read the returned pulse and update a variable



// Function Def's

int hcsr_setup_pins()
{
    ESP_LOGI(TAG,"Setting up GPIO Pins");
    //Config the Trig Pin
    gpio_pad_select_gpio(HCSR_TRIG_GPIO_NUM);
    gpio_set_direction(HCSR_TRIG_GPIO_NUM,GPIO_MODE_OUTPUT);

    //Config the Echo Pin
    gpio_pad_select_gpio(HCSR_ECHO_GPIO_NUM);
    gpio_set_direction(HCSR_ECHO_GPIO_NUM,GPIO_MODE_INPUT);

    ESP_LOGI(TAG,"GPIO Pins Setup Completed");
    return 0;
}

esp_err_t hcsr_send_trig_signal()
{
    //ESP_LOGI(TAG,"Sending Trig Signal to HCSR04 Sensor");
    esp_err_t err;
    //Signal sent needs to be on HIGH for 10 uS
    err = gpio_set_level(HCSR_TRIG_GPIO_NUM,HCSR_LOW);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG,"ERROR: Trig was unable to be sent");
        return err;
    }
    vTaskDelay(pdMS_TO_TICKS(0.002));

    err = gpio_set_level(HCSR_TRIG_GPIO_NUM,HCSR_HIGH);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG,"ERROR: Trig was unable to be sent");
        return err;
    }
    vTaskDelay(pdMS_TO_TICKS(0.01));

    err = gpio_set_level(HCSR_TRIG_GPIO_NUM,HCSR_LOW);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG,"ERROR: Trig was unable to be sent");
        return err;
    }

    //ESP_LOGI(TAG,"Trig Signal Sending Completed");
    return err;

}

int hcsr_echo_pulse_read()
{
    // ESP_LOGI(TAG,"Echo Reading");
    //Pulse Width Input - So we need to read how long is the input held up HIGH and return that value
    bool no_Signal = true;
    int pulse_Width = 0; // in uS
    int counter = 0;
    while(no_Signal)
    {
        if(gpio_get_level(HCSR_ECHO_GPIO_NUM) == HCSR_HIGH)
        {   
            no_Signal = false;
            while(gpio_get_level(HCSR_ECHO_GPIO_NUM) == HCSR_HIGH)
            {
                //Calculate the time in Microseconds
                pulse_Width += 1;
                vTaskDelay(pdMS_TO_TICKS(0.001));
            }
        }
        else if(counter > 100)
        {
            hcsr_send_trig_signal();
            counter = 0;
        }
        counter++;
        
    }
    // ESP_LOGI(TAG,"Echo Reading Completed");
    return pulse_Width;
}

double hcsr_get_distance_in()
{
    esp_err_t err;
    int pulse_readout = 0;
    double distance = 0.0;
    
    err = hcsr_send_trig_signal();
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG,"ERROR: within hcsr_send_trig_signal()");
        esp_restart();
    }

    pulse_readout = hcsr_echo_pulse_read();
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG,"ERROR: within hcsr_send_trig_signal()");
        esp_restart();
    }

    ESP_LOGI(TAG,"The Value of the Pulse Width is: %d",pulse_readout);
    distance = ((double)pulse_readout / 148.0) * 10;
    // ESP_LOGI(TAG,"Distance in Inches: %f",distance);
    return distance;
}

 
double hcsr_caliberate_sensor()
{
    ESP_LOGI(TAG,"Caliberating Sensor");

    double distance = 0.0;

    vTaskDelay(pdMS_TO_TICKS(10000)); // Wait 10 seconds for sensor stability

    for(int i = 0; i < 10; i++)
    {
        // Get 10 readings and average them
        distance += hcsr_get_distance_in();
        vTaskDelay(pdMS_TO_TICKS(HCSR_MEASUREMENT_CYCLE_MS));
    }

    return distance / 10.0;
}