# ps2busmouse98
# PS/2 - pc-98 bus mouse converter

秋月電子通商で販売されているArduino互換ボード(AE-ATMEGA328-MINI)を用いて作成した  
PS/2マウスをpc-9801用バスマウスに変換する変換器です。  
現状Alpha版という位置付けです。(少し不安定)

This is a converter to convert PS/2 mouse to pc-9801 bus mouse using Arduino compatible board (AE-ATMEGA328-MINI) sold in Akizukidenshi, Japan.  
Now it is alpha version. (a little unstable)  

- Receiving PS/2 signal after sending a code to enable data reporting.
- Switching Hi-Z and zero output for XA/XB/YA/YB pulses and LR buttons.
- Watchdog timer for checking irreguler PS/2 signal.
- No parity checking. (alpha version)
- No checking for acknowledge of enabling data reporting. (alpha version)

## References
PS/2 マウス/キーボード プロトコルとインターフェース  
http://ioiodesu.web.fc2.com/PS2/PS2.HTML  
USBマウス・USBキーボードをPC-9801に接続する変換器の製作  
http://www.suwa-koubou.jp/micom/USBtoPC98/usbtopc98.html  
資料室 (PC-98 マウス角コネクタ)  
http://nkmm.org/yagura/lib/  
秋月電子通商 (AE-ATMEGA328-MINI)  
https://akizukidenshi.com/catalog/g/gK-10347/  




