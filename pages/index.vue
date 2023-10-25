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
    <h1 class="text-5xl font-bold pt-2">The Forecast Station</h1>
    <img alt="" class="rainbow-dash pt-2" src="/images/rainbow-line.webp">
    <p class="mt-3" style="font-size:16px;">Predicting weather from surrounding readings from sensors</p>
    <h1 class="text-5xl font-bold">The Forecast Station</h1>
    <img class="rainbow" style="border-width: 0px" width="25%" src="../asset_img/rainbow.svg">
    <p>Predicting weather from surrounding readings from sensors</p>
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
      <p class="text-sm">Photoresistor as a light detector</p><img alt="" class="img"
                                                                   src="../asset_img/Light_Sensor.svg" width="100%">
    </div>
    <div style="margin: auto">
      <div><span class="text-2xl">NodeMCU ESP8266</span><img class="rainbow" style="margin-top:-5px" width="154px" src="../asset_img/rainbow.svg"><p class="text-sm">NodeMCU V3 LUA based ESP8266-12E for wifi connection with a leg extender board</p></div>
      <div class="columns-2"><img class="img" src="../asset_img/NodeMCU%20ESP8266-1.svg" width="100%"><img class="img" src="../asset_img/NodeMCU%20ESP8266-2.svg" width="70%"></div>
    </div>
    <div class="invisible" style="margin: auto"><span class="text-2xl">GY-BMP280</span><p class="text-sm">High precision Atmospheric Pressure Sensor Module</p><img class="img" src="../asset_img/GY-BMP280.svg" width="96%"></div>
  </div>
  <div class="grid grid-cols-3 text-center" style="align-content: center;">
    <div style="margin: auto"><span class="text-2xl">GY-BMP280</span><img class="rainbow" style="margin-top:-5px" width="154px" src="../asset_img/rainbow.svg"><p class="text-sm">High precision Atmospheric Pressure Sensor Module</p><img class="img" src="../asset_img/GY-BMP280.svg" width="96%"></div>
    <div style="margin: auto"><span class="text-2xl">LCD module</span><img class="rainbow" width="154px" src="../asset_img/rainbow.svg"><p class="text-sm">Liquid crystal display as another output </p><img class="img" src="../asset_img/LCD%20module.svg" width="70%">
    </div>
    <div style="margin: auto"><span class="text-2xl">LDR Light Sensor</span><img class="rainbow" style="margin-top:-2px" width="154px" src="../asset_img/rainbow.svg"><p class="text-sm">Photoresistor as a light detector</p><img class="img" src="../asset_img/Light_Sensor.svg" width="100%"></div>
  </div>
  <br>
  <div>
    <svg width="25000" height="5">
      <line x1="0" y1="0" x2="25000" y2="0" style="stroke:rgb(0,0,0);stroke-width:5px"/>
    </svg>
  </div>
  <div style="margin:10px;margin-left:20px;margin-bottom:20px">
    <p class="text-3xl" style="margin-bottom:10px">INPUT<img width="80px" src="../asset_img/rainbow.svg"></p>
    <p style="margin-left:30px">รับข้อมูลจากสภาพแวดล้อมด้วย LDR Light sensor สำหรับระดับแสง และ GY-BMP280 สำหรับวัดอุณหภูมิ และ ความดันอากาศ รวมถึงระดับความสูงเหนือระดับน้ำทะเล</p>
  </div>

  <div style="margin:10px;margin-left:20px;margin-bottom:20px">
    <p class="text-3xl" style="margin-bottom:10px">Forecasting<img width="80px" src="../asset_img/rainbow.svg"></p>
    <p style="margin-left:30px">ใช้ระดับความสูงเหนือระดับน้ำทะเล อุณหภูมิ และ ความดันอากาศในการพยากรณ์อากาศ โดยใช้ Zembretti algorith ซึ่งมีความแม่นยำสูงภายในพื้นที่ท้องถิ่น โดยจะนำค่าต่างๆมาคำนวนหาหมายเลขตารางหมายเลขพยากรณ์ Z โดย
      <br>- หากความดันมีค่าตกหล่นจะใช้สมการ Z = 130 - (P0 / 81)
      <br>- หากความดันมีค่าเสถียรจะใช้สมการ Z = 130 - (P0 / 81)
      <br>- หากความดันมีค่าเพิ่มขึ้นจะใช้สมการ Z = 130 - (P0 / 81)
      <br>- โดยค่า P0 คือค่าความดันที่ระดับน้ำทะเล หาได้จากสมการ
      <img style="margin:10px" width="400px" src="../asset_img/formula.svg">
      <br>P0 = ค่าความดันที่ระดับน้ำทะเล
      <br>P = ค่าความดันที่วัดได้
      <br>h = ความสูงจากระดับน้ำทะเล
      <br>T = อุนหภูมิที่วัดได้
    </p>
  </div>

  <div style="margin:10px;margin-left:20px;margin-bottom:20px">
    <p class="text-3xl" style="margin-bottom:10px">INPUT<img width="80px" src="../asset_img/rainbow.svg"></p>
    <p style="margin-left:30px">รับข้อมูลจากสภาพแวดล้อมด้วย LDR Light sensor สำหรับระดับแสง และ GY-BMP280 สำหรับวัดอุณหภูมิ และ ความดันอากาศ รวมถึงระดับความสูงเหนือระดับน้ำทะเล</p>
  </div>

  <div style="margin:10px;margin-left:20px;margin-bottom:20px">
    <p class="text-3xl" style="margin-bottom:10px">INPUT<img width="80px" src="../asset_img/rainbow.svg"></p>
    <p style="margin-left:30px">รับข้อมูลจากสภาพแวดล้อมด้วย LDR Light sensor สำหรับระดับแสง และ GY-BMP280 สำหรับวัดอุณหภูมิ และ ความดันอากาศ รวมถึงระดับความสูงเหนือระดับน้ำทะเล</p>
  </div>
  <!--  <div>-->
  <!--    <svg width="25000" height="5">-->
  <!--      <line x1="0" y1="0" x2="25000" y2="0" style="stroke:rgb(0,0,0);stroke-width:5px"/>-->
  <!--    </svg>-->
  <!--  </div>-->
  <Credit/>

</template>
<script setup lang="ts">
</script>