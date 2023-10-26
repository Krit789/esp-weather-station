<script lang="ts" setup>
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
            <v-card-item class="font-weight-light text-h3 text-right">{{
              data?.message.zambretti
            }}</v-card-item>
          </v-card>
        </v-col>
      </v-row>
      <v-row>
        <v-col cols="12" md="4" sm="12">
          <v-card>
            <v-card-title> Temperature </v-card-title>
            <v-card-item class="font-weight-light text-h4 text-right"
              >{{ data?.message.temperature.toPrecision(4) }}°C</v-card-item
            >
          </v-card>
        </v-col>
        <v-col cols="12" md="4" sm="12">
          <v-card>
            <v-card-title> Humidity </v-card-title>
            <v-card-item class="font-weight-light text-h4 text-right"
              >{{ data?.message.humidity.toPrecision(4) }} %</v-card-item
            >
          </v-card>
        </v-col>
        <v-col cols="12" md="4" sm="12">
          <v-card>
            <v-card-title> Barometric Pressure </v-card-title>
            <v-card-item class="font-weight-light text-h4 text-right"
              >{{ data?.message.barometric_pressure }} hPa</v-card-item
            >
          </v-card>
        </v-col>
        <v-col cols="12" md="4" sm="12">
          <v-card>
            <v-card-title> VOC Gas </v-card-title>
            <v-card-item class="font-weight-light text-h4 text-right"
              >{{ data?.message.gas.toPrecision(4) }} kOhm</v-card-item
            >
          </v-card>
        </v-col>
      </v-row>
    </v-container>
  </v-main>
</template>
