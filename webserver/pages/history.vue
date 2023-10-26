<script lang="ts" setup>
import {
  Chart as ChartJS,
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend,
} from "chart.js";
import { Line } from "vue-chartjs";
ChartJS.register(
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend
);
useHead({
  title: "Sensor History - The Forecaster",
  meta: [
    {
      name: "The Forecaster: Predict Accurately",
      content: "The Forecaster, High-Performance ESP-Based Weater Station.",
    },
  ],
});
const { pending, data, error, refresh } = await useFetch("/api/sensor");
const times = ref(data?.value?.message.map((item) => item.time));
const temperatures = ref(data?.value?.message.map((item) => item.temperature));
const humidity = ref(data?.value?.message.map((item) => item.humidity));
const pressure = ref(
  data?.value?.message.map((item) => item.barometric_pressure)
);
const gas = ref(data?.value?.message.map((item) => item.gas));
console.log(times.value, temperatures.value);
let tempData = ref({
  labels: times.value, // Will hold l_name values
  datasets: [
    {
      label: "Temperature",
      data: temperatures.value,
      backgroundColor: "#1E88E5", // Customize as needed
      // borderColor: 'rgba(75, 192, 192, 1)', // Customize as needed
      borderWidth: 1,
    },
  ],
});
let humidData = ref({
  labels: times.value, // Will hold l_name values
  datasets: [
    {
      label: "Humidity",
      data: humidity.value,
      backgroundColor: "#1E88E5", // Customize as needed
      // borderColor: 'rgba(75, 192, 192, 1)', // Customize as needed
      borderWidth: 1,
    },
  ],
});
let pressureData = ref({
  labels: times.value, // Will hold l_name values
  datasets: [
    {
      label: "Barometric Pressure",
      data: pressure.value,
      backgroundColor: "#1E88E5", // Customize as needed
      // borderColor: 'rgba(75, 192, 192, 1)', // Customize as needed
      borderWidth: 1,
    },
  ],
});
let gasData = ref({
  labels: times.value, // Will hold l_name values
  datasets: [
    {
      label: "VOC Gas",
      data: gas.value,
      backgroundColor: "#1E88E5", // Customize as needed
      // borderColor: 'rgba(75, 192, 192, 1)', // Customize as needed
      borderWidth: 1,
    },
  ],
});
useIntervalFn(() => {
  refresh(); // will call the 'todos' endpoint, just above
}, 60000); // call it back every 1 min
</script>

<template>
  <v-main class="ma-6 mb-15">
    <h1>History</h1>
    <v-container>
      <v-row>
        <v-col>
          <v-card>
            <v-card-title>Temperature</v-card-title>
            <v-card-item>
              <Line id="temperature" :key="data?.message" :data="tempData" />
            </v-card-item>
          </v-card>
        </v-col>
        <v-col>
          <v-card>
            <v-card-title>Humidity</v-card-title>
            <v-card-item>
              <Line id="humidity" :key="data?.message" :data="humidData" />
            </v-card-item>
          </v-card>
        </v-col>
      </v-row>
      <v-row>
        <v-col>
          <v-card>
            <v-card-title>Barometric Pressure</v-card-title>
            <v-card-item>
              <Line id="baropressure" :key="data?.message" :data="pressureData" />
            </v-card-item>
          </v-card>
        </v-col>
        <v-col>
          <v-card>
            <v-card-title>VOC Gas</v-card-title>.
            <v-card-item>
              <Line id="gas" :key="data?.message" :data="gasData" />
            </v-card-item>
          </v-card>
        </v-col>
      </v-row>
    </v-container>
  </v-main>
</template>
