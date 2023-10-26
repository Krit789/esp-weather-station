<script lang="ts" setup>
import { DateTime } from "luxon";
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
const times = ref(
  data?.value?.message.map((item) => DateTime.fromISO(item.time).toRelative())
);
const temperatures = ref(
  data?.value?.message.map((item) => item.temperature.toPrecision(4))
);
const humidity = ref(
  data?.value?.message.map((item) => item.humidity.toPrecision(4))
);
const pressure = ref(
  data?.value?.message.map((item) => item.barometric_pressure)
);
const gas = ref(data?.value?.message.map((item) => item.gas));
let tempData = ref({
  labels: times.value,
  datasets: [
    {
      label: "Temperature",
      data: temperatures.value,
      backgroundColor: "#FF5656",
      // borderWidth: 1,
    },
  ],
});
let humidData = ref({
  labels: times.value,
  datasets: [
    {
      label: "Humidity",
      data: humidity.value,
      backgroundColor: "#56C4FF",
      // borderWidth: 1,
    },
  ],
});
let pressureData = ref({
  labels: times.value,
  datasets: [
    {
      label: "Barometric Pressure",
      data: pressure.value,
      backgroundColor: "#56FFA8",
      // borderWidth: 1,
    },
  ],
});
let gasData = ref({
  labels: times.value,
  datasets: [
    {
      label: "VOC Gas",
      data: gas.value,
      backgroundColor: "#C756FF",
      // borderWidth: 1,
    },
  ],
});

const chartConfig1 = {
  responsive: true,
  maintainAspectRatio: false,
  scales: {
    x: {
      reverse: true,
    },
    y: {
      ticks: {
        // Include a dollar sign in the ticks
        callback: function (value: any) {
          return value + " °C";
        },
      },
    }
  },
};
const chartConfig2 = {
  responsive: true,
  maintainAspectRatio: false,
  scales: {
    x: {
      reverse: true,
    },
    y: {
      ticks: {
        // Include a dollar sign in the ticks
        callback: function (value: any) {
          return value + " %";
        },
      },
    }
  },
};
const chartConfig3 = {
  responsive: true,
  maintainAspectRatio: false,
  scales: {
    x: {
      reverse: true,
    },
    y: {
      ticks: {
        // Include a dollar sign in the ticks
        callback: function (value: any) {
          return value + " hPa";
        },
      },
    }
  },
};
const chartConfig4 = {
  responsive: true,
  maintainAspectRatio: false,
  scales: {
    x: {
      reverse: true,
    },
    y: {
      ticks: {
        // Include a dollar sign in the ticks
        callback: function (value: any) {
          return value + " kOhm";
        },
      },
    }
  },
};
useIntervalFn(() => {
  refresh();
}, 60000);
</script>

<template>
  <v-main class="ma-3 pa-3 mb-15 rounded-lg" style="background-color: #f2fbff">
    <v-container>
      <v-row>
        <v-col cols="12"
          ><h1 class="font-weight-bold text-h3">History</h1></v-col
        >
      </v-row>
      <v-row>
        <v-col cols="12" md="6" sm="12">
          <v-card class="rounded-lg">
            <v-card-title>Temperature</v-card-title>
            <v-card-item>
              <Line
                id="temperature"
                :key="data?.message"
                :data="tempData"
                :options="chartConfig1"
                height="400px"
              />
            </v-card-item>
          </v-card>
        </v-col>
        <v-col cols="12" md="6" sm="12">
          <v-card class="rounded-lg">
            <v-card-title>Humidity</v-card-title>
            <v-card-item>
              <Line
                id="humidity"
                :key="data?.message"
                :data="humidData"
                :options="chartConfig2"
                height="400px"
              />
            </v-card-item>
          </v-card>
        </v-col>
      </v-row>
      <v-row>
        <v-col cols="12" md="6" sm="12">
          <v-card class="rounded-lg">
            <v-card-title>Barometric Pressure</v-card-title>
            <v-card-item>
              <Line
                id="baropressure"
                :key="data?.message"
                :data="pressureData"
                :options="chartConfig3"
                height="400px"
              />
            </v-card-item>
          </v-card>
        </v-col>
        <v-col cols="12" md="6" sm="12">
          <v-card class="rounded-lg">
            <v-card-title>VOC Gas</v-card-title>
            <v-card-item>
              <Line
                id="gas"
                :key="data?.message"
                :data="gasData"
                :options="chartConfig4"
                height="400px"
              />
            </v-card-item>
          </v-card>
        </v-col>
      </v-row>
    </v-container>
  </v-main>
</template>
