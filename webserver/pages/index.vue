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

const forecastData: Record<number, string> = {
    1: "Settled Fine",
    2: "Fine Weather",
    3: "Fine Becoming Less Settled",
    4: "Fairly Fine Showery Later",
    5: "Showery Becoming more unsettled",
    6: "Unsettled, Rain later",
    7: "Rain at times, worse later.",
    8: "Rain at times, becoming very unsettled",
    9: "Very Unsettled, Rain",
    10: "Settled Fine",
    11: "Fine Weather",
    12: "Fine, Possibly showers",
    13: "Fairly Fine , Showers likely",
    14: "Showery Bright Intervals",
    15: "Changeable some rain",
    16: "Unsettled, rain at times",
    17: "Rain at Frequent Intervals",
    18: "Very Unsettled, Rain",
    19: "Stormy, much rain",
    20: "Settled Fine",
    21: "Fine Weather",
    22: "Becoming Fine",
    23: "Fairly Fine, Improving",
    24: "Fairly Fine, Possibly showers, early",
    25: "Showery Early, Improving",
    26: "Changeable Mending",
    27: "Rather Unsettled Clearing Later",
    28: "Unsettled, Probably Improving",
    29: "Unsettled, short fine Intervals",
    30: "Very Unsettled, Finer at times",
    31: "Stormy, possibly improving",
    32: "Stormy, much rain",
    33: "Rainy",
    34: "Cloudy",
    35: "Sunny Cloudy",
    36: "Sunny"
};

function getForecastText(forecastNumber: number | null | undefined): string {
    if (!forecastNumber) return "Unknown Forecast";
    return forecastData[forecastNumber] || "Unknown Forecast";
}

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
            <v-card-item class="font-weight-light text-h3 text-right">{{ getForecastText(data?.message.zambretti) }} ({{
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
