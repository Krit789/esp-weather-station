<script lang="ts" setup>
function navNavigate(page: number) {
  switch (page) {
    case 0:
      navigateTo("/");
      break;
    case 1:
      navigateTo("/history");
      break;
  }
}
</script>

<script lang="ts">
export default {
  data: () => ({}),
  methods: {},
};
</script>

<template>
  <v-card>
    <v-layout>
      <v-navigation-drawer expand-on-hover location="bottom" permanent rail>
        <v-list>
          <v-list-item
              prepend-icon="mdi-weather-cloudy"
              subtitle="ESP-Based Weather Solutions"
              title="The Forcaster"
          ></v-list-item>
        </v-list>

        <v-divider></v-divider>

        <v-list density="compact" nav>
          <v-list-item
              prepend-icon="mdi-home"
              title="Home"
              value="home"
              @click="() => {navNavigate(0)}"
          ></v-list-item>
          <v-list-item
              prepend-icon="mdi-history"
              title="History"
              value="history"
              @click="() => {navNavigate(1)}"
          ></v-list-item>
        </v-list>
      </v-navigation-drawer>
      <slot/>
    </v-layout>
  </v-card>
</template>
