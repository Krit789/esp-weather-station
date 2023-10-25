// https://nuxt.com/docs/api/configuration/nuxt-config
export default defineNuxtConfig({
    devtools: {enabled: true},
    modules: ["@nuxtjs/tailwindcss", '@nuxt/image'],
    app: {
        baseURL: '/esp-weather-station/', // baseURL: '/<repository>/'
        buildAssetsDir: 'assets', // don't use "_" at the begining of the folder name to avoids nojkill conflict
    },
    image: {
        dir: 'assets/images',
        format: ['avif', 'webp', 'png'],
        quality: 90
    },
})