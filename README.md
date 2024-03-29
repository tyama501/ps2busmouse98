# ps2busmouse98
# PS/2 - pc-98 bus mouse converter

秋月電子通商で販売されているArduino互換ボード(AE-ATMEGA328-MINI)を用いて作成した  
PS/2マウスをpc-9801用バスマウスに変換する変換器です。  
現状Beta版という位置付けです。

This is a converter to convert PS/2 mouse to pc-9801 bus mouse using Arduino compatible board (AE-ATMEGA328-MINI) sold in Akizukidenshi, Japan.  
Now it is beta version.

<img src=ps2busmouse98_20210425.jpg width="320pix"> <img src=PS2BMOU.BMP width="320pix">

- Receiving PS/2 signal after sending a code to enable data reporting.
- Switching Hi-Z and zero output for XA/XB/YA/YB pulses and LR buttons.  (it seems to have distortion issue of the pulse)
- Limiter for the movement. (the maximum movement is limited to 20 per 10ms due to the slow output pulse) 
- Watchdog timer for checking irregular PS/2 signal.
- LED for PS/2 signal receiving. (duplicated to the serial port, so always lights up if DEBUG is defined)
- Checking for acknowledge of enabling data reporting.
- Parity checking.  

## PC used to test the mouse
PC-9801RX21  
PC-9801UV21  
  
## Applications used to test the mouse
Game : Brandish  
  
Circuit Editor : CE Version 2.5 (tested with MOUSE.COM, LIPS.COM)  
  
Driver : Microsoft Mouse Driver v7.06 (MOUSE.COM)  
Driver : Animation Mouse Driver "Lips" Revision 0.28 (LIPS.COM)  
Driver : OZMOUSE Original Mouse Driver Version 0.04C (OZMOUSE.COM)  

## See Also
For initialization of PS/2 mouse containing USB-and-PS/2 compatible controller chip  
https://github.com/barbeque/busmouse98-byou

## References
PS/2 マウス/キーボード プロトコルとインターフェース  
http://ioiodesu.web.fc2.com/PS2/PS2.HTML  
USBマウス・USBキーボードをPC-9801に接続する変換器の製作  
http://www.suwa-koubou.jp/micom/USBtoPC98/usbtopc98.html  
資料室 (PC-98 マウス角コネクタ)  
http://nkmm.org/yagura/lib/  
秋月電子通商 (AE-ATMEGA328-MINI)  
https://akizukidenshi.com/catalog/g/gK-10347/  




