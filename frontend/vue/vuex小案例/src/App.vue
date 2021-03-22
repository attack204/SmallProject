<template>
  <div id="app">
    <axios/>
  </div>
</template>

<script>
import Axios from './pages/axios.vue'


export default {
  name: 'App',
  components: {
    Axios
  }
}
</script>

<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin-top: 60px;
}
</style>
