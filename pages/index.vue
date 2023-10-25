<script lang="ts" setup>
import '~/assets/stylesheets/global.css';
import '~/assets/stylesheets/index.css';
</script>


<template>
  <div class="Sooksan_Header">
    <div class="sook_north">
      <div class="sook_text">King Mongkut's Institute of Technology Ladkrabang</div>
    </div>
    <div class="sook_south"></div>
  </div>

  <div class="ma-10 text-center" style="margin-bottom: 50px;margin-top:20px">
    <h1 class="text-5xl mb-4 font-bold pt-2">The Forecast Station</h1>
    <NuxtImg alt="" class="rainbow-dash" src="/rainbow-line.png" style="margin-top:-10px"/>

    <p class="mt-3" style="font-size:16px;">Predicting weather from surrounding readings from sensors</p>

  </div>
  <div class="columns-2 text-center">
    <p>asd;asp[d</p>
    <p>asd;asp[d</p>
  </div>
  <br>
  <div>
    <svg height="5" width="25000">
      <line style="stroke:rgb(0,0,0);stroke-width:5px" x1="0" x2="25000" y1="0" y2="0"/>
    </svg>
  </div>
  <div class="grid grid-cols-3 text-center" style="align-content: center;">
    <div class="invisible" style="margin: auto"><span class="text-2xl">LDR Light Sensor</span>
      <p class="text-sm">Photoresistor as a light detector</p>
      <NuxtImg alt="" class="img"
               src="/Light_Sensor.svg" width="100%"/>
    </div>
    <div style="margin: auto">
      <div><span class="text-2xl">NodeMCU ESP8266</span>
        <NuxtImg class="rainbow" src="/rainbow.svg" style="margin-top:-5px"
                 width="154px"/>
        <p class="text-sm">NodeMCU V3 LUA based ESP8266-12E for wifi connection with a leg extender board</p></div>
      <div class="columns-2">
        <NuxtImg class="img" src="/NodeMCU_ESP8266-1.svg" width="100%"/>
        <NuxtImg class="img"
                 src="/NodeMCU_ESP8266-2.svg"
                 width="70%"/>
      </div>
    </div>
    <div class="invisible" style="margin: auto"><span class="text-2xl">GY-BMP280</span>
      <p class="text-sm">High precision Atmospheric Pressure Sensor Module</p>
      <NuxtImg class="img"
               src="/GY-BMP280.svg"
               width="96%"/>
    </div>
  </div>
  <div class="grid grid-cols-3 text-center" style="align-content: center;">
    <div style="margin: auto"><span class="text-2xl">GY-BMP280</span>
      <NuxtImg class="rainbow" src="/rainbow.svg"
               style="margin-top:-5px" width="154px"/>
      <p class="text-sm">High precision Atmospheric Pressure Sensor Module</p>
      <NuxtImg class="img"
               src="/GY-BMP280.svg"
               width="96%"/>
    </div>
    <div style="margin: auto"><span class="text-2xl">LCD module</span>
      <NuxtImg class="rainbow" src="/rainbow.svg"
               width="154px"/>
      <p class="text-sm">Liquid crystal display as another output </p>
      <NuxtImg class="img"
               src="/LCD_module.svg"
               width="70%"/>
    </div>
    <div style="margin: auto"><span class="text-2xl">LDR Light Sensor</span>
      <NuxtImg class="rainbow" src="/rainbow.svg"
               style="margin-top:-2px"
               width="154px"/>
      <p class="text-sm">Photoresistor as a light detector</p>
      <NuxtImg class="img" src="/Light_Sensor.svg"
               width="100%"/>
    </div>
  </div>
  <br>
  <div>
    <svg height="5" width="25000">
      <line style="stroke:rgb(0,0,0);stroke-width:5px" x1="0" x2="25000" y1="0" y2="0"/>
    </svg>
  </div>
  <div style="margin:10px;margin-left:20px;margin-bottom:20px">
    <p class="text-3xl" style="margin-bottom:10px">INPUT
      <NuxtImg src="/rainbow.svg" width="80px"/>
    </p>
    <p style="margin-left:30px">รับข้อมูลจากสภาพแวดล้อมด้วย LDR Light sensor สำหรับระดับแสง และ GY-BMP280
      สำหรับวัดอุณหภูมิ และ ความดันอากาศ รวมถึงระดับความสูงเหนือระดับน้ำทะเล</p>
  </div>

  <div style="margin:10px;margin-left:20px;margin-bottom:20px">
    <p class="text-3xl" style="margin-bottom:10px">FORECASTING
      <NuxtImg src="/rainbow.svg" width="80px"/>
    </p>
    <NuxtImg class="rainbow" src="/table_forecast.svg" width="40%"/>
    <p style="margin-left:30px;margin-top:10px">ใช้วัดระดับความสูงเหนือระดับน้ำทะเล อุณหภูมิ และ
      ความดันอากาศในการพยากรณ์อากาศ โดยใช้ Zembretti algorith ซึ่งมีความแม่นยำสูงภายในพื้นที่ท้องถิ่น
      โดยจะนำค่าต่างๆมาคำนวนหาหมายเลขตารางหมายเลขพยากรณ์ Z โดย
      <br>- หากความดันมีค่าตกหล่นจะใช้สมการ Z = 130 - (P0 / 81)
      <br>- หากความดันมีค่าเสถียรจะใช้สมการ Z = 130 - (P0 / 81)
      <br>- หากความดันมีค่าเพิ่มขึ้นจะใช้สมการ Z = 130 - (P0 / 81)
      <br>- โดยค่า P0 คือค่าความดันที่ระดับน้ำทะเล หาได้จากสมการ
      <NuxtImg src="/formula.svg" style="margin:10px" width="400px"/>
      <br>P0 = ค่าความดันที่ระดับน้ำทะเล
      <br>P = ค่าความดันที่วัดได้
      <br>h = ความสูงจากระดับน้ำทะเล
      <br>T = อุนหภูมิที่วัดได้
    </p>
  </div>

  <div style="margin:10px;margin-left:20px;margin-bottom:20px">
    <p class="text-3xl" style="margin-bottom:10px">CONNECTIVITY
      <NuxtImg src="/rainbow.svg" width="80px"/>
    </p>
    <p style="margin-left:30px">เราทำการเชื่อมต่อเครื่องวัดสภาพอากาศเข้ากับ Webserver ที่สร้างไว้ด้วย wifi
      และส่งข้อมูลเข้าไปแสดงหน้าเว็บ</p>
  </div>

  <div style="margin:10px;margin-left:20px;margin-bottom:20px">
    <p class="text-3xl" style="margin-bottom:10px">OUTPUT
      <NuxtImg src="/rainbow.svg" width="80px"/>
    </p>
    <p style="margin-left:30px">
      แสดงข้อมูลที่วัดไว้รวมถึงผลการพยากรณ์ในช่วงเวลาหนึ่งทั้งในปัจจุบันและประวัติการวัดที่ผ่านมาบนหน้าเว็บไซต์ และ
      [some sort of data] ในหน้าจอ lcd บนตัวครื่อง</p>
  </div>
  <!--  <div>-->
  <!--    <svg width="25000" height="5">-->
  <!--      <line x1="0" y1="0" x2="25000" y2="0" style="stroke:rgb(0,0,0);stroke-width:5px"/>-->
  <!--    </svg>-->
  <!--  </div>-->
  <Credit/>

</template>
<script lang="ts" setup>
</script>