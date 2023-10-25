<script lang="ts" setup>
import '~/assets/stylesheets/global.css';
import '~/assets/stylesheets/index.css';
import Credit from "~/components/Credit.vue";
</script>


<template>
  <div class="ma-10 text-center" style="margin-bottom: 50px">
    <h1 class="text-5xl font-bold">The Forecast Station</h1>
    <p>Predicting weather from surrounding readings from sensors</p>
  </div>
  <div class="columns-2 text-center">
    <p>asd;asp[d</p>
    <p>asd;asp[d</p>
  </div>
  <br>
  <div>
    <svg width="25000" height="5">
      <line x1="0" y1="0" x2="25000" y2="0" style="stroke:rgb(0,0,0);stroke-width:5px"/>
    </svg>
  </div>
  <div class="columns-4 text-center">
    <img src="../asset_img/GY-BMP280.svg">
    <img>
    <img>
  </div>
  <div id="Credit">
    <Credit/>
  </div>
</template>
