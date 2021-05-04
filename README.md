# ps2busmouse98
# PS/2 - pc-98 bus mouse converter

秋月電子通商で販売されているArduino互換ボード(AE-ATMEGA328-MINI)を用いて作成した  
PS/2マウスをpc-9801用バスマウスに変換する変換器です。  
現状Alpha版という位置付けです。(少し不安定)

This is a converter to convert PS/2 mouse to pc-9801 bus mouse using Arduino compatible board (AE-ATMEGA328-MINI) sold in Akizukidenshi, Japan.  
Now it is alpha version. (a little unstable)  

<img src=ps2busmouse98_20210425.jpg width="320pix"> <img src=PS2BMOU.BMP width="320pix">

- Receiving PS/2 signal after sending a code to enable data reporting.
- Switching Hi-Z and zero output for XA/XB/YA/YB pulses and LR buttons.
- Watchdog timer for checking irregular PS/2 signal.
- LED for PS/2 signal receiving. (duplicated to the serial port, so always lights up if DEBUG is defined)
- No parity checking. (alpha version)
- No checking for acknowledge of enabling data reporting. (alpha version)

## Applications used to test the mouse
Circuit Editor : CE Version 2.5 (tested with MOUSE.COM, LIPS.COM)  
Driver : Microsoft Mouse Driver v7.06 (MOUSE.COM)  
Driver : Animation Mouse Driver "Lips" Revision 0.28 (LIPS.COM)  
Driver : OZMOUSE Original Mouse Driver Version 0.04C (OZMOUSE.COM)  

## References
PS/2 マウス/キーボード プロトコルとインターフェース  
http://ioiodesu.web.fc2.com/PS2/PS2.HTML  
USBマウス・USBキーボードをPC-9801に接続する変換器の製作  
http://www.suwa-koubou.jp/micom/USBtoPC98/usbtopc98.html  
資料室 (PC-98 マウス角コネクタ)  
http://nkmm.org/yagura/lib/  
秋月電子通商 (AE-ATMEGA328-MINI)  
https://akizukidenshi.com/catalog/g/gK-10347/  




