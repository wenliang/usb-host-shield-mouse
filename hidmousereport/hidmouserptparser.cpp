#include <Mouse.h>
#include <Keyboard.h>
#include "hidmouserptparser.h"

HIDMouseReportParser::HIDMouseReportParser(HIDMouseEvents *evt)
  : mouEvents(evt), oldButtons(0) {}

void HIDMouseReportParser::Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf) {
  // see all 8 bits of data
  // for (uint8_t i = 0; i < len; i++) {
  //       if(i > 0) Serial.print("\t");
  //       Serial.print(buf[i], BIN);
  //       Serial.print(",");
  // }
  // Serial.println("");
  // for (uint8_t i = 0; i < len; i++) {
  //       if(i > 0) Serial.print("\t");
  //       Serial.print(buf[i], DEC);
  //       Serial.print(",");
  // }
  // Serial.println("");
  // Serial.println("");
  
  //but_id 1,2,4,8,16
  for (uint8_t but_id = 1; but_id <= 16; but_id <<= 1) {
    if (buf[0] & but_id) {
      if (!(oldButtons & but_id)) {
        mouEvents->OnButtonDn(but_id);
      }
    } else {
      if (oldButtons & but_id) {
        mouEvents->OnButtonUp(but_id);
      }
    }
  }
  oldButtons = buf[0];

  xm = 0;
  ym = 0;
  scr = 0;
  tilt = 0;

  // NOTE: per mouse settings here. Turn on line 15~19 to see the MouseReport for you mouse
  xbrute = buf[1];
  ybrute = buf[3];
  scr = buf[5];
  tilt = buf[7];

  if (xbrute > 127) {
    xm = map(xbrute, 255, 128, -1, -127);
  } else if (xbrute > 0) {
    xm = xbrute;
  }
  if (ybrute > 127) {
    ym = map(ybrute, 255, 128, -1, -127);
  } else if (ybrute > 0) {
    ym = ybrute;
  }

  if ((xm != 0) || (ym != 0) || (scr != 0) || (tilt != 0)) {
    mouEvents->Move(xm, ym, scr, tilt);
  }
}

void HIDMouseEvents::OnButtonDn(uint8_t but_id) {

  // for minecraft,  quickly switch weapon for each click
  if (1 & but_id) {
    Keyboard.write('2');
  } else if (2 & but_id) {
    Keyboard.write('1');
  } else if (8 & but_id) {
    Keyboard.write('3');
  } else if (16 & but_id) {
    Keyboard.write('4');
  }
  Mouse.press(but_id);
}

void HIDMouseEvents::OnButtonUp(uint8_t but_id) {
  Mouse.release(but_id);
}

void HIDMouseEvents::Move(int8_t xm, int8_t ym, int8_t scr, int8_t tilt) {
  /*
  Serial.print("dx: ");
  Serial.print(xm);
  Serial.print(", dy: ");
  Serial.println(ym);
  */
  Mouse.move(xm, ym, scr);
}
