<script lang="ts" setup>
import '~/assets/stylesheets/global.css';
import '~/assets/stylesheets/index.css';
</script>


<template>
  <div class="ma-10 text-center" style="margin-bottom: 50px;margin-top:20px">
    <h1 class="text-5xl font-bold pt-2">The Forecast Station</h1>
    <img alt="" class="rainbow-dash pt-2" src="/images/rainbow-line.webp">
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
      <p class="text-sm">Photoresistor as a light detector</p><img alt="" class="img"
                                                                   src="../asset_img/Light_Sensor.svg" width="100%">
    </div>
    <div style="margin: auto">
      <div><span class="text-2xl">NodeMCU ESP8266</span>
        <p class="text-sm">NodeMCU V3 LUA based ESP8266-12E for wifi connection with a leg extender board</p></div>
      <div class="columns-2"><img alt="" class="img" src="../asset_img/NodeMCU%20ESP8266-1.svg" width="100%"><img alt=""
                                                                                                                  class="img"
                                                                                                                  src="../asset_img/NodeMCU%20ESP8266-2.svg"
                                                                                                                  width="70%">
      </div>
    </div>
    <div class="invisible" style="margin: auto"><span class="text-2xl">GY-BMP280</span>
      <p class="text-sm">High precision Atmospheric Pressure Sensor Module</p><img alt=""
                                                                                   class="img"
                                                                                   src="../asset_img/GY-BMP280.svg"
                                                                                   width="96%"></div>

    <div style="margin: auto"><span class="text-2xl">GY-BMP280</span>
      <p class="text-sm">High precision Atmospheric Pressure Sensor Module</p><img alt=""
                                                                                   class="img"
                                                                                   src="../asset_img/GY-BMP280.svg"
                                                                                   width="96%"></div>
    <div style="margin: auto">
      <div><span class="text-2xl">LCD module</span>
        <p class="text-sm">Liquid crystal display as another output </p></div>
      <img alt="" class="img" src="../asset_img/LCD%20module.svg" width="70%">
    </div>
    <div style="margin: auto"><span class="text-2xl">LDR Light Sensor</span>
      <p class="text-sm">Photoresistor as a light detector</p><img alt="" class="img"
                                                                   src="../asset_img/Light_Sensor.svg" width="100%">
    </div>
  </div>
  <!--  <div>-->
  <!--    <svg width="25000" height="5">-->
  <!--      <line x1="0" y1="0" x2="25000" y2="0" style="stroke:rgb(0,0,0);stroke-width:5px"/>-->
  <!--    </svg>-->
  <!--  </div>-->
  <Credit/>

</template>