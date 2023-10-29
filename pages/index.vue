<script lang="ts" setup>
import "~/assets/stylesheets/global.css";
import "~/assets/stylesheets/index.css";

useHead({
  title: "The Forecaster Project",
  meta: [
    {
      name: "The Forecaster: Predict Accurately",
      content: "The Forecaster, A Physical Computing Project",
    },
  ],
});
useSeoMeta({
  title: "The Forecaster",
  ogTitle: "The Forecaster",
  description: "The Forecaster, High-Performance ESP-Based Weater Station.",
  ogDescription: "The Forecaster, High-Performance ESP-Based Weater Station.",
  ogImage: "/og_image.jpg",
  twitterCard: "summary_large_image",
});
</script>

<template>
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
      <img alt="" class="img" src="../assets/images/microcontroller1.jpg"/>
      <img alt="" class="img" src="../assets/images/microcontroller2.jpg"/>
    </div>
    <br/>

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
          <img alt="" class="img" src="../assets/images/BMP-680.png"/>
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
        ABSTRACT<img alt="" src="../assets/images/rainbow.svg" width="80px"/>
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
        INPUT<img alt="" src="../assets/images/rainbow.svg" width="80px"/>
      </p>
      <p class="ml-7">
        &emsp;รับข้อมูลจากสภาพแวดล้อมด้วย BME680 สำหรับวัดอุณหภูมิ ความดันอากาศ
        และแก๊ส เพื่อนำไปพยากรอากาศ
      </p>

      <p class="title">
        FORECASTING
        <img alt="" src="../assets/images/rainbow.svg" width="80px"/>
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
        โดยจะนำค่าต่างๆมาคำนวนหาหมายเลขตารางหมายเลขพยากรณ์ Z โดย <br/>-
        หากความดันมีค่าตกหล่นจะใช้สมการ Z = 130 - (P0 / 81) <br/>-
        หากความดันมีค่าเสถียรจะใช้สมการ Z = 130 - (P0 / 81) <br/>-
        หากความดันมีค่าเพิ่มขึ้นจะใช้สมการ Z = 130 - (P0 / 81) <br/>- โดยค่า P0
        คือค่าความดันที่ระดับน้ำทะเล หาได้จากสมการ
        <img
            alt=""
            class="m-2.5"
            src="../assets/images/formula.png"
            width="400px"
        />
        <br/>P0 = ค่าความดันที่ระดับน้ำทะเล <br/>P = ค่าความดันที่วัดได้
        <br/>h = ความสูงจากระดับน้ำทะเล <br/>T = อุนหภูมิที่วัดได้
      </p>

      <p class="title mt-10">
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
      <img class="mx-5 mb-10 w-auto" src="../assets/images/process.png">

      <p class="title">
        OUTPUT<img alt="" src="../assets/images/rainbow.svg" width="80px"/>
      </p>
      <p class="ml-7">
        &emsp;แสดงข้อมูลที่วัดไว้รวมถึงผลการพยากรณ์ในช่วงเวลาหนึ่งทั้งในปัจจุบันและประวัติการวัดที่ผ่านมาบนหน้าเว็บไซต์
        และ ข้อมูลที่วัดได้แบบ Real-Time รวมถึง Status ของเครื่องในหน้าจอ LCD
        บนตัวครื่อง
      </p>
      <div class="container mx-auto">
        <div class="grid grid-cols-1 gap-6 md:grid-cols-2  place-items-center text-6xl text-center m-10 mt-16">
          <div class="hover:border-dotted hover:border-2 hover:border-sky-500 hover:rounded-lg">
            <div class="flex flex-row flex-auto justify-center align-middle">
              <img alt="" class="w-12" src="../assets/icons/youtube.svg"/>
              <NuxtLink
                class="text-red-400 font-bold ml-0"
                target="_blank"
                to="https://youtu.be/Ta-5rEYYMiE"
                >Video Presentation
              </NuxtLink>
            </div>
            <NuxtLink to="https://youtu.be/Ta-5rEYYMiE">
              <p class="text-2xl">YouTube Video</p>
            </NuxtLink>
          </div>
          <div class="hover:border-dotted hover:border-2 hover:border-sky-500 hover:rounded-lg">
            <div class="flex flex-row flex-auto justify-center align-middle">
              <img alt="" class="w-12" src="../assets/icons/website.svg"/>
              <NuxtLink
                  class="text-amber-400 font-bold ml-5"
                  target="_blank"
                  to="https://forecast.jarukrit.net"
              >Project Website
              </NuxtLink>
            </div>
            <NuxtLink to="https://forecast.jarukrit.net">
              <p class="text-2xl">https://forecast.jarukrit.net</p>
            </NuxtLink>
          </div>
          <div class="hover:border-dotted hover:border-2 hover:border-sky-500 hover:rounded-lg">
            <div class="flex flex-row flex-auto justify-center">
              <img alt="" class="w-12 h-auto" src="../assets/icons/coding.svg"/>
              <NuxtLink
                  class="text-green-400 font-bold ml-5"
                  target="_blank"
                  to="https://github.com/Krit789/esp-weather-station"
              >Source Code
              </NuxtLink>
            </div>
            <NuxtLink to="https://github.com/Krit789/esp-weather-station">
              <p class="text-2xl">esp-weather-station Repository</p>
            </NuxtLink>
          </div>
          <div class="hover:border-dotted hover:border-2 hover:border-sky-500 hover:rounded-lg">
            <div class="flex flex-row flex-auto justify-center align-middle">
              <img alt="" class="w-12" src="../assets/icons/poster.svg"/>
              <NuxtLink
                  class="text-blue-400 font-bold ml-5"
                  target="_blank"
                  to="https://kmitlthailand-my.sharepoint.com/:b:/g/personal/65070089_kmitl_ac_th/Ec3I2u7Qo_FChGwzX1Z4QncB0vWxxmSHJdxlmFUT9Zi-BA?e=hz1Ym0"
              >Project Poster
              </NuxtLink>
            </div>
            <NuxtLink
                to="https://kmitlthailand-my.sharepoint.com/:b:/g/personal/65070089_kmitl_ac_th/Ec3I2u7Qo_FChGwzX1Z4QncB0vWxxmSHJdxlmFUT9Zi-BA?e=hz1Ym0">
              <p class="text-2xl">KMITL OneDrive</p>
            </NuxtLink>
          </div>
        </div>
      </div>
    </div>

    <Credit/>
    <div class="grid grid-cols-1 gap-6 md:grid-cols-2 mx-5">
      <div>
        <img
            alt=""
            class="img pt-3"
            src="../assets/images/teams/best.webp"
            width="80%"
        />
      </div>
      <div>
        <img
            alt=""
            class="img pt-3"
            src="../assets/images/teams/japan.webp"
            width="80%"
        /></div>
      <div>
        <img
            alt=""
            class="img pt-3"
            src="../assets/images/teams/krit.webp"
            width="80%"
        /></div>
      <div>
        <img
            alt=""
            class="img pt-3"
            src="../assets/images/teams/tae.webp"
            width="80%"
        /></div>
    </div>
  </div>
</template>
