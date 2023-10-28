<script lang="ts" setup>
import "~/assets/stylesheets/global.css";
import "~/assets/stylesheets/index.css";
</script>

<template>
  <div class="Sooksan_Header">
    <div class="sook_north">
      <div class="sook_text">
        King Mongkut's Institute of Technology Ladkrabang
      </div>
    </div>
    <div class="sook_south"></div>
  </div>

  <div class="main-body select-none">
    <div class="ma-10 text-center mb-12 mt-5">
      <h1 class="text-5xl mb-4 font-bold pt-2">The Forecaster</h1>
      <img
        alt=""
        class="rainbow-dash"
        src="/images/rainbow-line.webp"
        style="margin-top: -10px"
      />

      <p class="mt-3 text-base">
        Predicting weather from surrounding readings from sensors
      </p>
    </div>
    <div
      class="grid grid-cols-2 gap-10 text-center"
      style="width: 90%; margin: 0 auto"
    >
      <img alt="" class="img" src="../assets/images/microcontroller1.jpg" />
      <img alt="" class="img" src="../assets/images/microcontroller2.jpg" />
    </div>
    <br />

    <div id="sensors" class="sensor-box">
      <div class="grid grid-cols-3 text-center" style="align-content: center">
        <div class="invisible" style="margin: auto">
          <span class="text-2xl">LDR Light Sensor</span>
          <p class="text-sm">Photoresistor as a light detector</p>
          <img
            alt=""
            class="img"
            src="../assets/images/Light_Sensor.png"
            width="100%"
          />
        </div>

        <div style="margin: auto">
          <div>
            <span class="text-2xl">NodeMCU ESP8266</span
            ><img
              alt=""
              class="rainbow"
              src="../assets/images/rainbow.svg"
              style="margin-top: -5px"
              width="154px"
            />
            <p class="text-sm">
              NodeMCU V3 LUA based ESP8266-12E for wifi connection with a leg
              extender board
            </p>
          </div>
          <div class="columns-2">
            <img
              alt=""
              class="img"
              src="../assets/images/NodeMCU_ESP8266-1.png"
              width="100%"
            /><img
              alt=""
              class="img"
              src="../assets/images/NodeMCU_ESP8266-2.png"
              width="70%"
            />
          </div>
        </div>
        <div class="invisible" style="margin: auto">
          <span class="text-2xl">BME680</span>
          <p class="text-sm">
            High-accuracy gas, pressure, humidity, and temperature sensor
          </p>
          <img
            alt=""
            class="img"
            src="../assets/images/GY-BMP280.png"
            width="96%"
          />
        </div>
      </div>
      <div class="grid grid-cols-2 text-center" style="align-content: center">
        <div style="margin: auto">
          <span class="text-2xl">BME680</span
          ><img
            alt=""
            class="rainbow"
            src="../assets/images/rainbow.svg"
            style="margin-top: -5px"
            width="154px"
          />
          <p class="text-sm">
            High-accuracy gas, pressure, humidity, and temperature sensor
          </p>
          <img alt="" class="img" src="../assets/images/BMP-680.png" />
        </div>
        <div style="margin: auto">
          <span class="text-2xl">LCD module</span
          ><img
            alt=""
            class="rainbow"
            src="../assets/images/rainbow.svg"
            width="154px"
          />
          <p class="text-sm">Liquid crystal display as another output</p>
          <img
            alt=""
            class="img"
            src="../assets/images/LCD_module.png"
            width="70%"
          />
        </div>
      </div>
    </div>

    <div class="px-3">
      <p class="title">
        ABSTRACT<img alt="" src="../assets/images/rainbow.svg" width="80px" />
      </p>
      <p class="ml-7">
        &emsp;โปรเจ็กนี้เป็นการสร้างโปรแกรมสำหรับ Microcontroller
        เพื่ออ่านค่าต่างๆในสภาพแวดล้อมและนำไปใช้พยากรณ์อากาศในพื้นที่ท้องถิ่นด้วย
        Zembretti Algorithm โดยจะแสดงค่าที่วัดได้บน Web server
        ที่สร้างขึ้นมาและบนตัวหน้าจอ LCD บนเครื่อง, Microcontroller คือ NodeMCU
        ESP8266, ค่าที่ทำการวัดคือ สภาพแวดล้อม ความดัน, อุณหภูมิ, สภาพอากาศ
        และแก้ส
      </p>

      <p class="title">
        INPUT<img alt="" src="../assets/images/rainbow.svg" width="80px" />
      </p>
      <p class="ml-7">
        &emsp;รับข้อมูลจากสภาพแวดล้อมด้วย BME680 สำหรับวัดอุณหภูมิ ความดันอากาศ
        และแก๊ส เพื่อนำไปพยากรอากาศ
      </p>

      <p class="title">
        FORECASTING
        <img alt="" src="../assets/images/rainbow.svg" width="80px" />
      </p>
      <img
        alt=""
        class="table-forecast"
        src="../assets/images/table_forecast.png"
      />
      <p class="ml-7 mt-2.5">
        &emsp;ใช้วัดระดับความสูงเหนือระดับน้ำทะเล อุณหภูมิ และ
        ความดันอากาศในการพยากรณ์อากาศ โดยใช้ Zembretti Algorithm
        ซึ่งมีความแม่นยำสูงภายในพื้นที่ท้องถิ่น
        โดยจะนำค่าต่างๆมาคำนวนหาหมายเลขตารางหมายเลขพยากรณ์ Z โดย <br />-
        หากความดันมีค่าตกหล่นจะใช้สมการ Z = 130 - (P0 / 81) <br />-
        หากความดันมีค่าเสถียรจะใช้สมการ Z = 130 - (P0 / 81) <br />-
        หากความดันมีค่าเพิ่มขึ้นจะใช้สมการ Z = 130 - (P0 / 81) <br />- โดยค่า P0
        คือค่าความดันที่ระดับน้ำทะเล หาได้จากสมการ
        <img
          alt=""
          src="../assets/images/formula.png"
          class="m-2.5"
          width="400px"
        />
        <br />P0 = ค่าความดันที่ระดับน้ำทะเล <br />P = ค่าความดันที่วัดได้
        <br />h = ความสูงจากระดับน้ำทะเล <br />T = อุนหภูมิที่วัดได้
      </p>

      <p class="title">
        CONNECTIVITY<img
          alt=""
          src="../assets/images/rainbow.svg"
          width="80px"
        />
      </p>
      <p class="ml-7">
        &emsp;เราทำการเชื่อมต่อเครื่องวัดสภาพอากาศเข้ากับ Webserver
        ที่สร้างไว้ด้วย Library-WifiManager และส่งข้อมูลเข้าไป แสดงหน้าเว็บด้วย
        Library-ESP8266HTTPClient
      </p>

      <p class="title">
        OUTPUT<img alt="" src="../assets/images/rainbow.svg" width="80px" />
      </p>
      <p class="ml-7">
        &emsp;แสดงข้อมูลที่วัดไว้รวมถึงผลการพยากรณ์ในช่วงเวลาหนึ่งทั้งในปัจจุบันและประวัติการวัดที่ผ่านมาบนหน้าเว็บไซต์
        และ ข้อมูลที่วัดได้แบบ Real Time รวมถึง Status ของเครื่องในหน้าจอ LCD
        บนตัวครื่อง
      </p>
      <div class="flex flex-col  text-6xl text-center m-10 mt-16">
        <div class="flex flex-col">
          <div class="flex flex-row flex-auto justify-center align-middle">
            <img alt="" class="w-12" src="../assets/icons/website.svg"/>
            <NuxtLink
                class="text-amber-400 font-bold ml-5"
                target="_blank"
                to="https://www.youtube.com/watch?v=MtTdZTJHwPA"
            >Link Website
            </NuxtLink>
          </div>
          <p class="text-2xl">link here</p>
        </div>

        <div class="flex flex-col">
          <div class="flex flex-row flex-auto justify-center align-middle">
            <img alt="" class="w-24" src="../assets/icons/youtube.svg"/>
            <NuxtLink
                class="text-amber-800 font-bold ml-2"
                target="_blank"
                to="https://www.youtube.com/watch?v=MtTdZTJHwPA"
            >Link Youtube
            </NuxtLink>
          </div>
          <p class="text-2xl">link here</p>
        </div>
      </div>
    </div>

    <Credit />
    <div class="flex flex-wrap">
      <img
        alt=""
        class="img pt-3"
        src="../assets/images/teams/best.webp"
        width="500"
      />
      <img
        alt=""
        class="img pt-3"
        src="../assets/images/teams/japan.webp"
        width="500"
      />

      <img
        alt=""
        class="img pt-3"
        src="../assets/images/teams/krit.webp"
        width="500"
      />
      <img
        alt=""
        class="img pt-3"
        src="../assets/images/teams/tae.webp"
        width="500"
      />
    </div>
  </div>
</template>
