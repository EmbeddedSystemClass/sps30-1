# sps30

วัดค่าฝุ่นด้วยเซ็นเซอร์ Sensirion SPS30 ปลั๊กอินเสริมใช้งานกับ KidBrightIDE

[![สร้างเครื่องวัดฝุ่น PM2.5 ง่าย ๆ ด้วย KidBright + SPS30](https://img.youtube.com/vi/DIgbGQuMoeE/0.jpg)](https://www.youtube.com/watch?v=DIgbGQuMoeE)

## การติดตั้ง

กรณีใช้โปรแกรม KidBrightIDE (NewUI) เวอร์ชั่นเก่า หรือติดตั้งด้วย Gitlab
 1. ดาวน์โหลดไฟล์ปลั๊กอิน sps30_vx.x.zip จากด้านล่างของหน้านี้
 2. คลายไฟล์ออกมาด้วยโปรแกรม WinRAR หรือ 7-zip จะได้โฟลเดอร์ sps30
 3. ย้ายโฟลเดอร์ sps30 ไปไว้ในโฟลเดอร์ plugins ซึ่ง
    * หากติดตั้งโปรแกรม KidBrightIDE ด้วยไฟล์ .exe โฟลเดอร์ plugins อยู่ที่ `C:\Users\[USERNAME]\AppData\Local\KidBright\app-[VERSION]\resources\app\kbide`
    * หากติดตั้งโปรแกรม KidBrightIDE ผ่านการ Clone ใน Gitlab โฟลเดอร์ plugins จะอยู่ในโฟลเดอร์ kbide ณ ที่ ๆ สั่ง Clone มา
 4. เปิดโปรแกรม KidBrightIDE ขึ้นมา จะมีเมนู `เซ็นเซอร์ฝุ่น SPS30` เพิ่มขึ้นมา (สำหรับภาษาอังกฤษ เมนูชื่อ `PM2.5 Sensor (SPS30)`)
 
กรณีใช้โปรแกรม KidBright IDE (64bits, New UI, Plugins beta version)
 1. ดาวน์โหลดไฟล์ปลั๊กอิน sps30_vx.x.zip จากด้านล่างของหน้านี้
 2. เปิดโปรแกรม KidBrightIDE กด `Plugins > Install Plugins`
 3. เลือกไฟล์ปลั๊กอินที่ดาวน์โหลดไว้
 4. โปรแกรม KidBrightIDE จะปิดแล้วเปิดใหม่ บล็อกใหม่จะอยู่ในเมนู `เซ็นเซอร์ฝุ่น SPS30` หรือ `PM2.5 Sensor (SPS30)`
 
## การต่อสาย

![TGstzn.png](https://sv1.picz.in.th/images/2019/02/23/TGstzn.png)

ปลั๊กอินนี้รองรับการต่อเซ็นเซอร์ Sensirion SPS30 เข้าที่ช่อง KB Chain โดยต่อสายดังนี้

 * ต่อ Pin 1 ของ Sensirion SPS30 เข้ากับ 5V
 * ต่อ Pin 2 ของ Sensirion SPS30 เข้ากับ SDA
 * ต่อ Pin 3 ของ Sensirion SPS30 เข้ากับ SCL
 * ต่อ Pin 4 ของ Sensirion SPS30 เข้ากับ GND
 * ต่อ Pin 5 ของ Sensirion SPS30 เข้ากับ GND
 
**โปรดระวัง หากซื้อเซ็นเซอร์จากกราวิเทค สายสีแดงคือ GND และสายสีดำคือ 5V**

## บล็อกที่มีให้ใช้

| บล็อกภาษาไทย | บล็อกภาษาอังกฤษ |
|--|--|
| ![TGP2RW.png](https://sv1.picz.in.th/images/2019/02/23/TGP2RW.png) | ![TGPnwy.png](https://sv1.picz.in.th/images/2019/02/23/TGPnwy.png) |

### (1) บล็อกเซ็นเซอร์ฝุ่นพร้อมอ่านข้อมูล? (PM Sensor is ready?)

ใช้ตรวจสอบว่าเซ็นเซอร์ฝุ่น SPS30 มีข้อมูลฝุ่นให้อ่านหรือยัง คืนค่าเป็นข้อมูลจริง/เท็จ (true/false)

### (2) บล็อกรอจนกว่าเซ็นเซอร์ฝุ่นจะพร้อม (Wait PM sensor ready)

ใช้รอให้เซ็นเซอร์ฝุ่นพร้อมทำงานก่อน จึงจะไปทำงานต่อในบล็อกถัดไปได้

### (3) บล็อกอ่านค่าความเข้มข้นเชิงมวล (Read mass concentration)

ใช้อ่านค่าความเข้มข้นเชิงมวล (mass concentration) ของฝุ่น PM1.0 PM2.5 PM4.0 และ PM10 คืนค่าเป็นตัวเลขทศนิยม

### (4) บล็อกอ่านค่าความเข้มข้นเชิงจำนวน (Read number concentration)

ใช้อ่านค่าความเข้มข้นเชิงจำนวน (number concentration) ของฝุ่น PM0.5 PM1.0 PM2.5 PM4.0 และ PM10 คืนค่าเป็นตัวเลขทศนิยม

### (5) บล็อกอ่านค่า typical particle sizes (Read typical particle sizes)

ใช้อ่านค่า typical particle sizes คืนค่าเป็นตัวเลขทศนิยม

## ตัวอย่างโปรแกรม เครื่องวัดฝุ่น PM2.5

![TGAH8e.png](https://sv1.picz.in.th/images/2019/02/23/TGAH8e.png)

### หลักการทำงาน

![TGPhHa.png](https://sv1.picz.in.th/images/2019/02/23/TGPhHa.png)
