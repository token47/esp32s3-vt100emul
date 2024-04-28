#include <Arduino.h>
#include <esp32_smartdisplay.h>
#include "lvgl.h"
#include <ui/ui.h>

/*
TODO:
- fonte fixa
- slider mudar brilho e atualizar label
- teclado enviar chars serial
- usar serial1
*/

static void event_cb_keyboard(lv_obj_t * obj, lv_event_t event)
{
    if(event == LV_EVENT_CLICKED){
        // get the character that was pressed
        const char * txt = lv_btnm_get_active_btn_text(obj);
        Serial.write(txt[0]);
    }
}

void setup()
{
    //delay(1000);
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    //log_i("Board: %s", BOARD_NAME);
    //log_i("CPU: %s rev%d, CPU Freq: %d Mhz, %d core(s)", ESP.getChipModel(), ESP.getChipRevision(), getCpuFrequencyMhz(), ESP.getChipCores());
    //log_i("Free heap: %d bytes", ESP.getFreeHeap());
    //log_i("Free PSRAM: %d bytes", ESP.getPsramSize());
    //log_i("SDK version: %s", ESP.getSdkVersion());

    smartdisplay_init();
    smartdisplay_lcd_set_backlight(1);

    auto disp = lv_disp_get_default();
    lv_disp_set_rotation(disp, LV_DISP_ROT_180);

    ui_init();
}

void loop()
{
    if (Serial.available()) {
        char inByte = Serial.read();
        lv_textarea_add_text(ui_TerminalTextArea, &inByte);
    }
    lv_timer_handler();
}
