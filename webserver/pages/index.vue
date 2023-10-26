<script lang="ts" setup>
import { DateTime } from "luxon";
useHead({
  title: "The Forecaster",
  meta: [
    {
      name: "The Forecaster: Predict Accurately",
      content: "The Forecaster, High-Performance ESP-Based Weater Station.",
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
const { pending, data, error, refresh } = await useFetch("/api/sensor_current");
const z_forecast = new Array("Settled fine", "Fine weather", "Becoming fine", "Fine, becoming less settled", "Fine, possible showers", "Fairly fine, improving", "Fairly fine, possible showers early", "Fairly fine, showery later", "Showery early, improving", "Changeable, mending", "Fairly fine, showers likely", "Rather unsettled clearing later", "Unsettled, probably improving", "Showery, bright intervals", "Showery, becoming less settled", "Changeable, some rain", "Unsettled, short fine intervals", "Unsettled, rain later", "Unsettled, some rain", "Mostly very unsettled", "Occasional rain, worsening", "Rain at times, very unsettled", "Rain at frequent intervals", "Rain, very unsettled", "Stormy, may improve", "Stormy, much rain"); 

useIntervalFn(() => {
  console.log(`refreshing the data again ${new Date().toISOString()}`);
  refresh(); // will call the 'todos' endpoint, just above
}, 60000); // call it back every 3s
</script>
<template>
  <v-main class="ma-6 mb-15">
    <h1>Current Outlook</h1>
    <v-container>
      <v-row>
        <v-col cols="12">
          <v-card>
            <v-img
              src="https://cdn.vuetifyjs.com/images/cards/sunshine.jpg"
              height="300px"
              cover
            ></v-img>
            <v-card-title> Zambretti Forecast </v-card-title>
            <v-card-item class="font-weight-light text-h3 text-right">{{ z_forecast.at(data?.message.zambretti-1) }} ({{
              data?.message.zambretti
            }})</v-card-item>
          </v-card>
        </v-col>
      </v-row>
      <v-row>
        <v-col cols="12" md="4" sm="12">
          <v-card>
            <v-card-title> Temperature </v-card-title>
            <v-container class="pa-0 ma-0">
              <v-row class="mt-1">
                <v-col cols="1">
                  <v-icon size="50px" class="pl-5 pb-5">mdi-thermometer</v-icon>
                </v-col>
                <v-col cols="11">
                  <div class="font-weight-light text-h4 text-right mr-5 mb-5">
                    {{ data?.message.temperature.toPrecision(4) }}°C
                  </div>
                </v-col>
              </v-row>
            </v-container>
          </v-card>
        </v-col>
        <v-col cols="12" md="4" sm="12">
          <v-card>
            <v-card-title> Humidity </v-card-title>
            <v-container class="pa-0 ma-0">
              <v-row class="mt-1">
                <v-col cols="1">
                  <v-icon size="50px" class="pl-5 pb-5">mdi-water-percent</v-icon>
                </v-col>
                <v-col cols="11">
                  <div class="font-weight-light text-h4 text-right mr-5 mb-5">
                    {{ data?.message.humidity.toPrecision(4) }} %
                  </div>
                </v-col>
              </v-row>
            </v-container>
          </v-card>
        </v-col>
        <v-col cols="12" md="4" sm="12">
          <v-card>
            <v-card-title> Barometric Pressure </v-card-title>
            <v-container class="pa-0 ma-0">
              <v-row class="mt-1">
                <v-col cols="1">
                  <v-icon size="50px" class="pl-5 pb-5">mdi-gauge-low</v-icon>
                </v-col>
                <v-col cols="11">
                  <div class="font-weight-light text-h4 text-right mr-5 mb-5">
                    {{ data?.message.barometric_pressure }} hPa
                  </div>
                </v-col>
              </v-row>
            </v-container>
          </v-card>
        </v-col>
        <v-col cols="12" md="4" sm="12">
          <v-card>
            <v-card-title> VOC Gas </v-card-title>
            <v-container class="pa-0 ma-0">
              <v-row class="mt-1">
                <v-col cols="1">
                  <v-icon size="50px" class="pl-5 pb-5">mdi-weather-dust</v-icon>
                </v-col>
                <v-col cols="11">
                  <div class="font-weight-light text-h4 text-right mr-5 mb-5">
                    {{ data?.message.gas.toPrecision(4) }} kOhm
                  </div>
                </v-col>
              </v-row>
            </v-container>
          </v-card>
        </v-col>
        <v-col cols="12" md="8" sm="12">
          <v-card>
            <v-card-title> Updated At </v-card-title>
            <v-container class="pa-0 ma-0">
              <v-row class="mt-1">
                <v-col cols="1">
                  <v-icon size="50px" class="pl-5 pb-5">mdi-clock-outline</v-icon>
                </v-col>
                <v-col cols="11">
                  <div class="font-weight-light text-h4 text-right mr-5 mb-5">{{
                    DateTime.fromISO(data?.message.time).toFormat("ff")
                  }}</div>
                </v-col>
              </v-row>
            </v-container>
          </v-card>
        </v-col>
      </v-row>
    </v-container>
  </v-main>
</template>
