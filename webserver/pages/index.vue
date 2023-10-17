<script setup lang=ts>
useHead({
  title: 'The Forecaster',
  meta: [
    {
      name: 'The Forecaster: Predict Accurately',
      content: 'The Forecaster, High-Performance ESP-Based Weater Station.',
    },
  ],
});
useSeoMeta({
  title: 'The Forecaster',
  ogTitle: 'The Forecaster',
  description: 'The Forecaster, High-Performance ESP-Based Weater Station.',
  ogDescription: 'The Forecaster, High-Performance ESP-Based Weater Station.',
  ogImage: '/og_image.jpg',
  twitterCard: 'summary_large_image',
});
</script>
<template>
  <v-main class="ma-6" style="height: 100vh">
    <h1>Current Outlook</h1>
  </v-main>
</template>
