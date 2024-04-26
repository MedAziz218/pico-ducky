#include "Adafruit_TinyUSB.h"


#define LEFTCTRL (1UL << (0))
#define LEFTSHIFT (1UL << (1))
#define LEFTALT (1UL << (2))
#define LEFTGUI (1UL << (3))
#define RIGHTCTRL (1UL << (4))
#define RIGHTSHIFT (1UL << (5))
#define RIGHTALT (1UL << (6))
#define RIGHTGUI (1UL << (7))

#define HID_ASCII_TO_KEYCODE_FR_WITH_NUMPAD \
  { 0, 0 },                   /* 0x00 Null      */ \
    { 0, 0 },                 /* 0x01           */ \
    { 0, 0 },                 /* 0x02           */ \
    { 0, 0 },                 /* 0x03           */ \
    { 0, 0 },                 /* 0x04           */ \
    { 0, 0 },                 /* 0x05           */ \
    { 0, 0 },                 /* 0x06           */ \
    { 0, 0 },                 /* 0x07           */ \
    { 0, HID_KEY_BACKSPACE }, /* 0x08 Backspace */ \
    { 0, HID_KEY_TAB },       /* 0x09 Tab       */ \
    { 0, HID_KEY_ENTER },     /* 0x0A Line Feed */ \
    { 0, 0 },                 /* 0x0B           */ \
    { 0, 0 },                 /* 0x0C           */ \
    { 0, HID_KEY_ENTER },     /* 0x0D CR        */ \
    { 0, 0 },                 /* 0x0E           */ \
    { 0, 0 },                 /* 0x0F           */ \
    { 0, 0 },                 /* 0x10           */ \
    { 0, 0 },                 /* 0x11           */ \
    { 0, 0 },                 /* 0x12           */ \
    { 0, 0 },                 /* 0x13           */ \
    { 0, 0 },                 /* 0x14           */ \
    { 0, 0 },                 /* 0x15           */ \
    { 0, 0 },                 /* 0x16           */ \
    { 0, 0 },                 /* 0x17           */ \
    { 0, 0 },                 /* 0x18           */ \
    { 0, 0 },                 /* 0x19           */ \
    { 0, 0 },                 /* 0x1A           */ \
    { 0, HID_KEY_ESCAPE },    /* 0x1B Escape    */ \
    { 0, 0 },                 /* 0x1C           */ \
    { 0, 0 },                 /* 0x1D           */ \
    { 0, 0 },                 /* 0x1E           */ \
    { 0, 0 },                 /* 0x1F           */ \
\
    { 0, HID_KEY_SPACE },                   /* 0x20           */ \
    { 0, HID_KEY_SLASH },                   /* 0x21 !         */ \
    { 0, HID_KEY_3 },                       /* 0x22 "         */ \
    { RIGHTALT, HID_KEY_3 },                /* 0x23 #         */ \
    { 0, HID_KEY_BRACKET_RIGHT },           /* 0x24 $         */ \
    { LEFTSHIFT, HID_KEY_APOSTROPHE },      /* 0x25 %         */ \
    { 0, HID_KEY_1 },                       /* 0x26 &         */ \
    { 0, HID_KEY_4 },                       /* 0x27 '         */ \
    { 0, HID_KEY_5 },                       /* 0x28 (       here  */ \
    { 0, HID_KEY_MINUS },                   /* 0x29 )         */ \
    { LEFTSHIFT, HID_KEY_KEYPAD_MULTIPLY }, /* 0x2A *         */ \
    { LEFTSHIFT, HID_KEY_KEYPAD_ADD },      /* 0x2B +         */ \
    { 0, HID_KEY_M },                       /* 0x2C ,         */ \
    { 0, HID_KEY_KEYPAD_SUBTRACT },         /* 0x2D -         */ \
    { 0, HID_KEY_KEYPAD_DECIMAL },          /* 0x2E .         */ \
    { LEFTSHIFT, HID_KEY_KEYPAD_DIVIDE },   /* 0x2F /         */ \
    { 0, HID_KEY_KEYPAD_0 },                /* 0x30 0         */ \
    { 0, HID_KEY_KEYPAD_1 },                /* 0x31 1         */ \
    { 0, HID_KEY_KEYPAD_2 },                /* 0x32 2         */ \
    { 0, HID_KEY_KEYPAD_3 },                /* 0x33 3         */ \
    { 0, HID_KEY_KEYPAD_4 },                /* 0x34 4         */ \
    { 0, HID_KEY_KEYPAD_5 },                /* 0x35 5         */ \
    { 0, HID_KEY_KEYPAD_6 },                /* 0x36 6         */ \
    { 0, HID_KEY_KEYPAD_7 },                /* 0x37 7         */ \
    { 0, HID_KEY_KEYPAD_8 },                /* 0x38 8         */ \
    { 0, HID_KEY_KEYPAD_9 },                /* 0x39 9         */ \
    { 0, HID_KEY_PERIOD },                  /* 0x3A :         */ \
    { 0, HID_KEY_COMMA },                   /* 0x3B ;         */ \
    { 0, HID_KEY_EUROPE_2 },                /* 0x3C <         */ \
    { 0, HID_KEY_EQUAL },                   /* 0x3D =         */ \
    { LEFTSHIFT, HID_KEY_EUROPE_2 },        /* 0x3E >         */ \
    { LEFTSHIFT, HID_KEY_M },               /* 0x3F ?          */ \
\
    { RIGHTALT, HID_KEY_0 },          /* 0x40 @         */ \
    { LEFTSHIFT, HID_KEY_Q },         /* 0x41 A         */ \
    { LEFTSHIFT, HID_KEY_B },         /* 0x42 B         */ \
    { LEFTSHIFT, HID_KEY_C },         /* 0x43 C         */ \
    { LEFTSHIFT, HID_KEY_D },         /* 0x44 D         */ \
    { LEFTSHIFT, HID_KEY_E },         /* 0x45 E         */ \
    { LEFTSHIFT, HID_KEY_F },         /* 0x46 F         */ \
    { LEFTSHIFT, HID_KEY_G },         /* 0x47 G         */ \
    { LEFTSHIFT, HID_KEY_H },         /* 0x48 H         */ \
    { LEFTSHIFT, HID_KEY_I },         /* 0x49 I         */ \
    { LEFTSHIFT, HID_KEY_J },         /* 0x4A J         */ \
    { LEFTSHIFT, HID_KEY_K },         /* 0x4B K         */ \
    { LEFTSHIFT, HID_KEY_L },         /* 0x4C L         */ \
    { LEFTSHIFT, HID_KEY_SEMICOLON }, /* 0x4D M         */ \
    { LEFTSHIFT, HID_KEY_N },         /* 0x4E N         */ \
    { LEFTSHIFT, HID_KEY_O },         /* 0x4F O         */ \
    { LEFTSHIFT, HID_KEY_P },         /* 0x50 P         */ \
    { LEFTSHIFT, HID_KEY_A },         /* 0x51 Q         */ \
    { LEFTSHIFT, HID_KEY_R },         /* 0x52 R         */ \
    { LEFTSHIFT, HID_KEY_S },         /* 0x53 S         */ \
    { LEFTSHIFT, HID_KEY_T },         /* 0x55 T         */ \
    { LEFTSHIFT, HID_KEY_U },         /* 0x55 U         */ \
    { LEFTSHIFT, HID_KEY_V },         /* 0x56 V         */ \
    { LEFTSHIFT, HID_KEY_Z },         /* 0x57 W         */ \
    { LEFTSHIFT, HID_KEY_X },         /* 0x58 X         */ \
    { LEFTSHIFT, HID_KEY_Y },         /* 0x59 Y         */ \
    { LEFTSHIFT, HID_KEY_W },         /* 0x5A Z         */ \
    { RIGHTALT, HID_KEY_5 },          /* 0x5B [         */ \
    { RIGHTALT, HID_KEY_8 },          /* 0x5C '\'       */ \
    { RIGHTALT, HID_KEY_MINUS },      /* 0x5D ]         */ \
    { LEFTSHIFT, HID_KEY_6 },         /* 0x5E ^         */ \
    { 0, HID_KEY_8 },                 /* 0x5F _         */ \
\
    { 0, HID_KEY_GRAVE },         /* 0x60 `      */ \
    { 0, HID_KEY_Q },             /* 0x61 a         */ \
    { 0, HID_KEY_B },             /* 0x62 b         */ \
    { 0, HID_KEY_C },             /* 0x63 c         */ \
    { 0, HID_KEY_D },             /* 0x66 d         */ \
    { 0, HID_KEY_E },             /* 0x65 e         */ \
    { 0, HID_KEY_F },             /* 0x66 f         */ \
    { 0, HID_KEY_G },             /* 0x67 g         */ \
    { 0, HID_KEY_H },             /* 0x68 h         */ \
    { 0, HID_KEY_I },             /* 0x69 i         */ \
    { 0, HID_KEY_J },             /* 0x6A j         */ \
    { 0, HID_KEY_K },             /* 0x6B k         */ \
    { 0, HID_KEY_L },             /* 0x6C l         */ \
    { 0, HID_KEY_SEMICOLON },     /* 0x6D m         */ \
    { 0, HID_KEY_N },             /* 0x6E n         */ \
    { 0, HID_KEY_O },             /* 0x6F o         */ \
    { 0, HID_KEY_P },             /* 0x70 p         */ \
    { 0, HID_KEY_A },             /* 0x71 q         */ \
    { 0, HID_KEY_R },             /* 0x72 r         */ \
    { 0, HID_KEY_S },             /* 0x73 s         */ \
    { 0, HID_KEY_T },             /* 0x75 t         */ \
    { 0, HID_KEY_U },             /* 0x75 u         */ \
    { 0, HID_KEY_V },             /* 0x76 v         */ \
    { 0, HID_KEY_Z },             /* 0x77 w         */ \
    { 0, HID_KEY_X },             /* 0x78 x         */ \
    { 0, HID_KEY_Y },             /* 0x79 y         */ \
    { 0, HID_KEY_W },             /* 0x7A z         */ \
    { RIGHTALT, HID_KEY_4 },      /* 0x7B {         */ \
    { RIGHTALT, HID_KEY_6 },      /* 0x7C |         */ \
    { RIGHTALT, HID_KEY_EQUAL },  /* 0x7D }         */ \
    { LEFTSHIFT, HID_KEY_GRAVE }, /* 0x7E ~         */ \
  { \
    0, HID_KEY_DELETE \
  } /* 0x7F Delete    */

