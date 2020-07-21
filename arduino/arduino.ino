/* 

Code to control the internal arduino of the pelicomputer

It has 4 main functions:
- control the LED strip (thinklight)
- send the position of the POT to the system over serial
- send the state of the mouse buttons to the system over serial
- send the measured battery voltage over serial

*/



int pot_value = 0;
int pot_value_8_bit = 0;
int battery_value = 0;
int left_mouse_state = 0;
int middle_mouse_state = 0;
int right_mouse_state = 0;
int r_switch_state = 0;
int g_switch_state = 0;
int b_switch_state = 0;

const int led_strip_r_pin  = 9;
const int led_strip_g_pin  = 10;
const int led_strip_b_pin  = 11;
const int led_strip_5v     = 13;

// battery input
const int battery_pin      = A4;

// rgb switches
const int r_switch_pin     = A2;
const int g_switch_pin     = 7;
const int b_switch_pin     = 8;
const int r_switch_led_pin = 3;
const int g_switch_led_pin = 5;
const int b_switch_led_pin = 6;

// pot
const int pot_pin          = A7;

// mouse buttons
const int mouse_left_pin   = 2;
const int mouse_middle_pin = A1;
const int mouse_right_pin  = A0;



void initialize_pins()
{
    // led strip
    pinMode ( led_strip_r_pin, OUTPUT );
    pinMode ( led_strip_g_pin, OUTPUT );
    pinMode ( led_strip_b_pin, OUTPUT );
    pinMode ( led_strip_5v,    OUTPUT );
    analogWrite ( led_strip_r_pin, 0 );
    analogWrite ( led_strip_g_pin, 0 );
    analogWrite ( led_strip_b_pin, 0 );
    digitalWrite ( led_strip_5v, 1 );

    // battery
    pinMode ( battery_pin, INPUT );

    // rgb switches
    pinMode ( r_switch_pin, INPUT );
    pinMode ( g_switch_pin, INPUT );
    pinMode ( b_switch_pin, INPUT );
    pinMode ( r_switch_led_pin, OUTPUT );
    pinMode ( g_switch_led_pin, OUTPUT );
    pinMode ( b_switch_led_pin, OUTPUT );
    analogWrite ( r_switch_led_pin, 0 );
    analogWrite ( g_switch_led_pin, 0 );
    analogWrite ( b_switch_led_pin, 0 );

    // pot
    pinMode ( pot_pin, INPUT );

    // digital pins
    pinMode ( mouse_left_pin, INPUT );
    pinMode ( mouse_middle_pin , INPUT );
    pinMode ( mouse_right_pin , INPUT );
}

void get_state()
{
    pot_value           = 1023-analogRead ( pot_pin );
    battery_value       = analogRead ( battery_pin );
    left_mouse_state   = digitalRead ( mouse_left_pin );
    middle_mouse_state = digitalRead ( mouse_middle_pin );
    right_mouse_state  = digitalRead ( mouse_right_pin );
    r_switch_state = digitalRead( r_switch_pin );
    g_switch_state = digitalRead( g_switch_pin );
    b_switch_state = digitalRead( b_switch_pin );
    }


void control_leds()
{
    if (r_switch_state + g_switch_state + b_switch_state > 0) {
        pot_value_8_bit = pot_value / 1023.0 * 255.0;
    } else {
        return;
    }
    if (r_switch_state > 0)
    {
        analogWrite(r_switch_led_pin, pot_value_8_bit);
        analogWrite(led_strip_r_pin, (255 - pot_value_8_bit));
    }
    if (g_switch_state > 0)
    {
        analogWrite(g_switch_led_pin, pot_value_8_bit);
        analogWrite(led_strip_g_pin, (255 - pot_value_8_bit));
    }
    if (b_switch_state > 0)
    {
        analogWrite(b_switch_led_pin, pot_value_8_bit);
        analogWrite(led_strip_b_pin, (255 - pot_value_8_bit));
    }
}


void send_to_up2()
{
    Serial.print(left_mouse_state);
    Serial.print(",");
    Serial.print(middle_mouse_state);
    Serial.print(",");
    Serial.print(right_mouse_state);
    Serial.print(",");
    Serial.print(pot_value);
    Serial.print(",");
    Serial.print(battery_value);
    Serial.println();
}


void setup() {
    initialize_pins();
    Serial.begin(9600);
}

void loop() {
    get_state();
    control_leds();
    send_to_up2();
}
