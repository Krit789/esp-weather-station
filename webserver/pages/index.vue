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
  36: "Sunny",
};

const forecastImage: Record<number, string> = {
  1: "/images/clear.jpg",
  2: "/images/clear.jpg",
  3: "/images/sunnycloudy.jpg",
  4: "/images/sunnycloudy.jpg",
  5: "/images/rainy.jpg",
  6: "/images/overcast.jpg",
  7: "/images/rainy.jpg",
  8: "/images/rainy.jpg",
  9: "/images/rainy.jpg",
  10: "/images/clear.jpg",
  11: "/images/sunnycloudy.jpg",
  12: "/images/cloudy.jpg",
  13: "/images/cloudy.jpg",
  14: "/images/sunnycloudy.jpg",
  15: "/images/rainy.jpg",
  16: "/images/overcast.jpg",
  17: "/images/rainy.jpg",
  18: "/images/rainy.jpg",
  19: "/images/rainy.jpg",
  20: "/images/clear.jpg",
  21: "/images/clear.jpg",
  22: "/images/cloudy.jpg",
  23: "/images/cloudy.jpg",
  24: "/images/cloudy.jpg",
  25: "/images/rainy.jpg",
  26: "/images/unknown.jpg",
  27: "/images/cloudy.jpg",
  28: "/images/stormclearing.jpg",
  29: "/images/stormclearing.jpg",
  30: "/images/rainy.jpg",
  31: "/images/stormclearing.jpg",
  32: "/images/rainy.jpg",
  33: "/images/rainy.jpg",
  34: "/images/overcast.jpg",
  35: "/images/sunnycloudy.jpg",
  36: "/images/clear.jpg",
};

const forecastImages: Record<number, string> = {
  1: "Clear blue sky with a bright sun.",
  2: "Bright sun with a few white clouds.",
  3: "Sun behind some thickening clouds.",
  4: "Sun with scattered clouds, chance of rain later.",
  5: "Increasingly cloudy with scattered showers.",
  6: "Overcast skies with rain expected later.",
  7: "Intermittent rain with worsening conditions.",
  8: "Rain at times, becoming very unsettled.",
  9: "Stormy weather with heavy rain.",
  10: "Clear blue sky with a bright sun.",
  11: "Bright sun with a few white clouds.",
  12: "Partly cloudy with a chance of showers.",
  13: "Partly cloudy with likely showers.",
  14: "Sunshine with brief periods of showers.",
  15: "Clouds with occasional rain.",
  16: "Overcast skies with intermittent rain.",
  17: "Frequent rain showers.",
  18: "Stormy weather with heavy rain.",
  19: "Dark storm clouds with heavy rain.",
  20: "Clear blue sky with a bright sun.",
  21: "Bright sun with a few white clouds.",
  22: "Improving weather with some sun.",
  23: "Partly cloudy, conditions getting better.",
  24: "Partly cloudy with a chance of early showers.",
  25: "Morning showers with improving conditions.",
  26: "Clouds clearing, conditions mending.",
  27: "Becoming clearer with scattered clouds.",
  28: "Improving conditions, unsettled but better.",
  29: "Unsettled with short periods of sun.",
  30: "Very unsettled with occasional improvement.",
  31: "Stormy, possibly improving.",
  32: "Dark storm clouds with heavy rain.",
  33: "Continuous rainfall.",
  34: "Overcast sky with no precipitation.",
  35: "Partly sunny with scattered clouds.",
  36: "Clear blue sky with bright sun.",
};

function getForecastText(forecastNumber: number | null | undefined): string {
  if (!forecastNumber) return "Unknown Forecast";
  return forecastData[forecastNumber] || "Unknown Forecast";
}

function getForecastDesc(forecastNumber: number | null | undefined): string {
  if (!forecastNumber) return "Unknown Forecast";
  return forecastImages[forecastNumber] || "Unknown Forecast";
}

function getForecastImage(forecastNumber: number | null | undefined): string {
  if (!forecastNumber) return "/images/unknown.jpg";
  return forecastImage[forecastNumber] || "/images/unknown.jpg";
}

useIntervalFn(() => {
  refresh();
}, 60000); // call it back every 1 min
</script>
<template>
  <v-main class="ma-3 pa-3 mb-15 rounded-lg" style="background-color: #f2fbff">
    <v-container>
      <v-row>
        <v-col cols="12"
          ><h1 class="font-weight-bold text-h3">Current Outlook</h1></v-col
        >
      </v-row>
      <v-row>
        
        <v-col cols="12">
          <v-hover v-slot="{ isHovering, props }">
            <v-card :elevation="isHovering ? 6 : 1" v-bind="props" class="rounded-lg">
            <v-img :src="getForecastImage(data?.message.zambretti)" height="300px" cover></v-img>
            <v-card-title> Zambretti Forecast </v-card-title>
            <v-card-item class="font-weight-light text-h3 text-right mb-0 pb-0"
              ><p class="pb-1">
                {{ getForecastText(data?.message.zambretti) }}
              </p></v-card-item
            >
            <v-card-item class="font-weight-medium text-right"
              >
                {{ getForecastDesc(data?.message.zambretti) }}
              </v-card-item
            >
          </v-card>
          </v-hover>
        </v-col>
      </v-row>
      <v-row>
        <v-col cols="12" md="4" sm="12">
          <v-hover v-slot="{ isHovering, props }">
            <v-card :elevation="isHovering ? 6 : 1" v-bind="props" class="rounded-lg">
              <v-card-title> Temperature </v-card-title>
              <v-container class="pa-0 ma-0">
                <v-row class="mt-1">
                  <v-col cols="1">
                    <v-icon size="50px" class="pl-5 pb-5"
                      >mdi-thermometer</v-icon
                    >
                  </v-col>
                  <v-col cols="11">
                    <div class="font-weight-light text-h4 text-right mr-5 mb-5">
                      {{ data?.message.temperature.toPrecision(4) }}°C
                    </div>
                  </v-col>
                </v-row>
              </v-container>
            </v-card>
          </v-hover>
        </v-col>
        <v-col cols="12" md="4" sm="12">
          <v-hover v-slot="{ isHovering, props }">
            <v-card :elevation="isHovering ? 6 : 1" v-bind="props" class="rounded-lg">
              <v-card-title> Humidity </v-card-title>
              <v-container class="pa-0 ma-0">
                <v-row class="mt-1">
                  <v-col cols="1">
                    <v-icon size="50px" class="pl-5 pb-5"
                      >mdi-water-percent</v-icon
                    >
                  </v-col>
                  <v-col cols="11">
                    <div class="font-weight-light text-h4 text-right mr-5 mb-5">
                      {{ data?.message.humidity.toPrecision(4) }} %
                    </div>
                  </v-col>
                </v-row>
              </v-container>
            </v-card>
          </v-hover>
        </v-col>
        <v-col cols="12" md="4" sm="12">
          <v-hover v-slot="{ isHovering, props }">
            <v-card :elevation="isHovering ? 6 : 1" v-bind="props" class="rounded-lg">
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
          </v-hover>
        </v-col>
        <v-col cols="12" md="4" sm="12">
          <v-hover v-slot="{ isHovering, props }">
            <v-card :elevation="isHovering ? 6 : 1" v-bind="props" class="rounded-lg">
              <v-card-title> VOC Gas </v-card-title>
              <v-container class="pa-0 ma-0">
                <v-row class="mt-1">
                  <v-col cols="1">
                    <v-icon size="50px" class="pl-5 pb-5"
                      >mdi-weather-dust</v-icon
                    >
                  </v-col>
                  <v-col cols="11">
                    <div class="font-weight-light text-h4 text-right mr-5 mb-5">
                      {{ data?.message.gas.toPrecision(4) }} kOhm
                    </div>
                  </v-col>
                </v-row>
              </v-container>
            </v-card>
          </v-hover>
        </v-col>
        <v-col cols="12" md="8" sm="12">
          <v-hover v-slot="{ isHovering, props }">
            <v-card :elevation="isHovering ? 6 : 1" v-bind="props" class="rounded-lg">
            <v-card-title> Updated At </v-card-title>
            <v-container class="pa-0 ma-0">
              <v-row class="mt-1">
                <v-col cols="1">
                  <v-icon size="50px" class="pl-5 pb-5"
                    >mdi-clock-outline</v-icon
                  >
                </v-col>
                <v-col cols="11">
                  <div class="font-weight-light text-h4 text-right mr-5 mb-5">
                    {{ DateTime.fromISO(data?.message.time).toFormat("ff") }}
                  </div>
                </v-col>
              </v-row>
            </v-container>
          </v-card>
        </v-hover>
        </v-col>
      </v-row>
    </v-container>
  </v-main>
</template>
